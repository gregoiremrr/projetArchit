#include "execution.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void remplitStruct(instructionHexa* structu, char* instruct){
    char a[3], b[5];
    for (int i = 0; i<2; i++){
        a[i] = instruct[i];
    }
    a[2] = '\0';
    for (int i = 0; i<4; i++){
        b[i] = instruct[i+3];
    }
    b[4] = '\0';
    structu->var = strtol(a, NULL, 16);
    structu->value = strtol(b, NULL, 16);
}

void ReadLowLangageFile(FILE* fic, char** Prog){ // on presuppose que le fichier texte hexa.txt est deja ouvert
    char c = fgetc(fic);
    int i = 0, j = 0;
    while(c != EOF && c != -1){
        if(c == '\n' || c == EOF){
            Prog[i][j] = '\0';
            i++;
            j = 0;
        } else {
            Prog[i][j] = c;
            j++;
        }
        c = fgetc(fic);
    }
}

void fonction(instructionHexa instruct, short* pile, int* ppc, int* psp, int len, int* OK2){
    switch(instruct.var){ // le membre instruct.var correspond au numero de la fonction
        case 0: pop(instruct, pile, ppc, psp, OK2); break;
        case 1: push(instruct, pile, ppc, psp, OK2); break;
        case 2: iPop(instruct, pile, ppc, psp, OK2); break;
        case 3: iPush(instruct, pile, ppc, psp, OK2); break;
        case 4: push2(instruct, pile, ppc, psp, OK2); break;
        case 5: call(instruct, pile, ppc, psp, len, OK2); break;
        case 6: ret(instruct, pile, ppc, psp, OK2); break;
        case 7: jmp(instruct, pile, ppc, len, OK2); break;
        case 8: jpc(instruct, pile, ppc, psp, len, OK2); break;
        case 9: write(instruct, pile, ppc, OK2); break;
        case 10: read(instruct, pile, ppc, OK2); break;
        case 11: rnd(instruct, pile, ppc, psp, OK2); break;
        case 12: dup(instruct, pile, ppc, psp, OK2); break;
        case 13: op(instruct, pile, ppc, psp, OK2); break;
        case 99: halt(instruct, pile, ppc, len);
  }
}

void pop(instructionHexa instruct, short* pile, int* ppc, int* psp, int* OK2){
    if (*psp > 0 && instruct.value < 4000 && instruct.value > -1){
        (*psp)--;
        pile[instruct.value] = pile[*psp];
    } else {
        *OK2 = 0;
        printf("Segmentation fault (ligne %d)\n", *ppc);
    }
}

void push(instructionHexa instruct, short* pile, int* ppc, int* psp, int* OK2){
    if (*psp < 3999) {
        pile[*psp] = pile[instruct.value];
        (*psp)++;
    } else {
        *OK2 = 0;
        printf("Segmentation fault (ligne %d)\n", *ppc);
    }
}

void iPop(instructionHexa instruct, short* pile, int* ppc, int* psp, int* OK2){
    if (*psp > 1 && pile[*psp-1] < 4000 && pile[*psp-1] > -1) {
        pile[pile[*psp-1]] = pile[*psp-2];
        *psp -= 2;
    } else {
        *OK2 = 0;
        printf("Segmentation fault (ligne %d)\n", *ppc);
    }
}

void iPush(instructionHexa instruct, short* pile, int* ppc, int* psp, int* OK2){
    if (pile[*psp-1] < 4000 && pile[*psp-1] > -1){
        pile[*psp-1] = pile[pile[*psp-1]];
    } else {
        *OK2 = 0;
        printf("Segmentation fault (ligne %d)\n", *ppc);
    }
}

void push2(instructionHexa instruct, short* pile, int* ppc, int* psp, int* OK2){
    if (*psp < 3999) {
        pile[*psp] = instruct.value;
        (*psp)++;
    } else {
        *OK2 = 0;
        printf("Segmentation fault (ligne %d)\n", *ppc);
    }
}

void call(instructionHexa instruct, short* pile, int* ppc, int* psp, int len, int* OK2){
    if (*psp < 3999) {
        pile[*psp] = *ppc + 1;
        (*psp)++;
        if (*ppc + instruct.value <= len + 1 && *ppc + instruct.value >= -1) {
            *ppc += instruct.value;
        } else {
            *OK2 = 0;
            printf("Appel de procedure impossible : l'instruction %d n'existe pas\n", *ppc + instruct.value);
        }
    } else {
        *OK2 = 0;
        printf("Segmentation fault (ligne %d)\n", *ppc);
    }
}

void ret(instructionHexa instruct, short* pile, int* ppc, int* psp, int* OK2){
    if (*psp > 0) {
        (*ppc)--;
        *ppc = pile[*psp];
    } else {
        *OK2 = 0;
        printf("Segmentation fault (ligne %d)\n", *ppc);
    }
}

void jmp(instructionHexa instruct, short* pile, int* ppc, int len, int* OK2){
    if (*ppc + instruct.value <= len+1 && *ppc + instruct.value >= -1) {
        *ppc += instruct.value;
    } else {
        *OK2 = 0;
        printf("Appel de procedure impossible : l'instruction %d n'existe pas\n", *ppc + instruct.value);
    }
}

void jpc(instructionHexa instruct, short* pile, int* ppc, int* psp, int len, int* OK2){
    (*psp)--;
    if (pile[*psp] != 0){
        if (*ppc + instruct.value <= len+1 && *ppc + instruct.value >= -1) {
            *ppc += instruct.value;
        } else {
            *OK2 = 0;
            printf("Appel de procedure impossible : l'instruction %d n'existe pas\n", *ppc + instruct.value);
        }
    }
}

void write(instructionHexa instruct, short* pile, int* ppc, int* OK2){
    if (instruct.value < 4000 && instruct.value > -1) {
        printf("%d\n", pile[instruct.value]);
    } else {
        *OK2 = 0;
        printf("Segmentation fault (ligne %d)\n", *ppc);
    }
}

void read(instructionHexa instruct, short* pile, int* ppc, int* OK2){
    if (instruct.value < 4000 && instruct.value > -1) {
        printf("Rentrer une valeur qui sera mise dans la variable a l'adresse %d : ",instruct.value);
        scanf("%hd", pile + instruct.value);
    } else {
        *OK2 = 0;
        printf("Segmentation fault (ligne %d)\n", *ppc);
    }
}

void rnd(instructionHexa instruct, short* pile, int* ppc, int* psp, int* OK2){
    if (*psp < 3999){
        srand(time(NULL));
        pile[*psp] = rand() % instruct.value;
        (*psp)++;;
    } else {
        *OK2 = 0;
        printf("Segmentation fault (ligne %d)\n", *ppc); 
    }
}

void dup(instructionHexa instruct, short* pile, int* ppc, int* psp, int* OK2){
    if (*psp < 3999){
        pile[*psp]=pile[*psp-1];
        (*psp)++;
    } else {
        *OK2 = 0;
        printf("Segmentation fault (ligne %d)\n", *ppc);
    }
}

void op(instructionHexa instruct, short* pile, int* ppc, int* psp, int* OK2){
    if (*psp > 0 || instruct.value == 9 || instruct.value == 10) {
        switch(instruct.value){
            case 0:
                (*psp)--;
                if (pile[(*psp)-1]==pile[*psp]){
                    pile[(*psp)-1]=1;
                } else {
                    pile[(*psp)-1]=0;
                }
                break;
            case 1:
                (*psp)--;
                if (pile[(*psp)-1]!=pile[*psp]){
                    pile[(*psp)-1]=1;
                } else {
                    pile[(*psp)-1]=0;
                }
                break;
            case 2:
                (*psp)--;
                if (pile[(*psp)-1]>pile[*psp]){
                    pile[(*psp)-1]=1;
                } else {
                    pile[(*psp)-1]=0;
                }
                break;
            case 3:
                (*psp)--;
                if (pile[(*psp)-1]>=pile[*psp]){
                    pile[(*psp)-1]=1;
                } else {
                    pile[(*psp)-1]=0;
                }
                break;
            case 4:
                (*psp)--;
                if (pile[(*psp)-1] < pile[*psp]){
                    pile[(*psp)-1]=1;
                } else {
                    pile[(*psp)-1]=0;
                }
                break;
            case 5:
                (*psp)--;
                if (pile[(*psp)-1] <= pile[*psp]){
                    pile[(*psp)-1]=1;
                } else {
                    pile[(*psp)-1]=0;
                }
                break;
            case 6:
                (*psp)--;
                pile[(*psp)-1]=pile[(*psp)-1]&pile[*psp];
                break;
            case 8:
                (*psp)--;
                pile[(*psp)-1]=pile[(*psp)-1] ^ pile[*psp];
                break;
            case 9:
                pile[(*psp)-1]= ~ pile[(*psp)-1];
                break;
            case 10:
                pile[(*psp)-1] = -pile[(*psp)-1];
                break;
            case 11:
                (*psp)--;
                pile[(*psp)-1]=pile[(*psp)-1] + pile[*psp];
                break;
            case 12:
                (*psp)--;
                pile[(*psp)-1]=pile[(*psp)-1] - pile[*psp];
                break;
            case 13:
                (*psp)--;
            pile[(*psp)-1]=pile[(*psp)-1] * pile[*psp];
                break;
            case 14:
                (*psp)--;
                pile[(*psp)-1]=pile[(*psp)-1] / pile[*psp];
                break;
            case 15:
                (*psp)--;
                pile[(*psp)-1]=pile[(*psp)-1] % pile[*psp];
                break;
            default:
                *OK2 = 0;
                printf("Le code d operation est incorrect : %d\n", instruct.value);
        }
    } else {
        *OK2 = 0;
        printf("Segmentation fault (ligne %d)\n", *ppc);
    }
}

void halt(instructionHexa instruct, short* pile, int* ppc, int len){
    *ppc = len;
}
