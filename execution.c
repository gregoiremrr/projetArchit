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

void fonction(instructionHexa instruct, short* pile, int* ppc, int* psp){
    switch(instruct.var){ // le membre instruct.var correspond au numero de la fonction
        case 0: pop(instruct, pile, ppc, psp); break;
        case 1: push(instruct, pile, ppc, psp); break;
        case 2: iPop(instruct, pile, ppc, psp); break;
        case 3: iPush(instruct, pile, ppc, psp); break;
        case 4: push2(instruct, pile, ppc, psp); break;
        case 5: call(instruct, pile, ppc); break;
        case 6: ret(instruct, pile, ppc); break;
        case 7: jmp(instruct, pile, ppc); break;
        case 8: jpc(instruct, pile, ppc, psp); break;
        case 9: write(instruct, pile); break;
        case 10: read(instruct, pile); break;
        case 11: rnd(instruct, pile, ppc, psp); break;
        case 12: dup(instruct, pile, ppc, psp); break;
        case 13: op(instruct, pile, ppc, psp); break;
        case 99: halt(instruct, pile);
  }
}

void pop(instructionHexa instruct, short* pile, int* ppc, int* psp){
    short x=instruct.value;
    if (*psp > 0){
        (*psp)--;
        pile[x] = pile[*psp];
    } else {
        printf("Segmentation fault (ligne %d)", *ppc);
    }
}

void push(instructionHexa instruct, short* pile, int* ppc, int* psp){
    if ((*psp+1)>3999){
      printf("Segmentation fault (ligne %d)",*ppc);
    } else{
    short v=instruct.value;
    pile[*psp]= pile[v];
    (*psp)++;
    }
}

void iPop(instructionHexa instruct, short* pile, int* ppc, int* psp){
    int n=pile[(*psp)-1]; //n est le contenu de la tete de pile
    pile[n]= pile[(*psp)-1];
}

void iPush(instructionHexa instruct, short* pile, int* ppc, int* psp){
  if ((*psp+1)>3999){
    printf("Segmentation fault (ligne %d)",*ppc);}
  else
  {
  int n=pile[(*psp)-1];
  pile[(*psp)]=pile[n];
  (*psp)++;
    }
}

void push2(instructionHexa instruct, short* pile, int* ppc, int* psp){
  if ((*psp+1)>3999){
    printf("Segmentation fault (ligne %d)",*ppc);}
  else
  {
    short v=instruct.value;
    pile[*psp]=v;
    (*psp)++;
  }
}
void call(instructionHexa instruct, short* pile, int* ppc){
    short v=instruct.value;
    (*ppc)++;
    *ppc= *ppc + v;
}

void ret(instructionHexa instruct, short* pile, int* ppc){
    (*ppc)--;
}

void jmp(instructionHexa instruct, short* pile, int* ppc){
    *ppc=*ppc+(instruct.value);
}

void jpc(instructionHexa instruct, short* pile, int* ppc, int* psp){
    (*ppc)--; //accede a la valeur sur le tas
    int v= pile[--(*psp)];
    if (v!=0){
        *ppc=*ppc+instruct.value;
    }
}

void write(instructionHexa instruct, short* pile){
    printf("%d", pile[instruct.value]);
}

void read(instructionHexa instruct, short* pile){
    short x;
    printf("rentrer une valeur qui sera mise dans la variable a l adresse %d : ",instruct.value);
    scanf("%hd",&x);
    pile[instruct.value]=x;
}

void rnd(instructionHexa instruct, short* pile, int* ppc, int* psp){
  if ((*psp+1)>3999){
    printf("Segmentation fault (ligne %d)",*ppc);}
  else
  {
    int nb=0;
    srand(time(NULL));
    nb=rand()%(instruct.value);
    pile[*psp]=nb;
    (*psp)++;;
  }
}
void dup(instructionHexa instruct, short* pile, int* ppc, int* psp){

    if ((*psp+1)<=3999){
      pile[*(psp)]=pile[*(psp)-1];
      (*psp)++;
    } else{
        printf("Segmentation fault (ligne %d)", *ppc);
    }
}

void op(instructionHexa instruct, short* pile, int* ppc, int* psp){
    switch(instruct.value){
    case 0:
            (*psp)--;
            if (pile[(*psp)-1]==pile[*psp]){
                pile[(*psp)-1]=1;
            } else {pile[(*psp)-1]=0;}
            break;
    case 1:
            (*psp)--;
            if (pile[(*psp)-1]!=pile[*psp]){
                pile[(*psp)-1]=1;
            } else {pile[(*psp)-1]=0;}
            break;

    case 2:
            (*psp)--;
            if (pile[(*psp)-1]>pile[*psp]){
                pile[(*psp)-1]=1;
            } else {pile[(*psp)-1]=0;}
            break;
    case 3:
            (*psp)--;
            if (pile[(*psp)-1]>=pile[*psp]){
                pile[(*psp)-1]=1;
            } else {pile[(*psp)-1]=0;}
            break;
    case 4:
            (*psp)--;
            if (pile[(*psp)-1] < pile[*psp]){
                pile[(*psp)-1]=1;
            } else {pile[(*psp)-1]=0;}
            break;
    case 5:
            (*psp)--;
            if (pile[(*psp)-1] <= pile[*psp]){
                pile[(*psp)-1]=1;
            } else {pile[(*psp)-1]=0;}
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
            printf("Le code d operation est incorrect, %d doit etre un entier compris entre 0 et 15 inclus", instruct.value);
  }
}

void halt(instructionHexa instruct, short* pile){

}
