#include "execution.h"

#include <stdio.h>
#include <stdlib.h>

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

void fonction(instructionHexa instruct, short* pile, int* ppc){
    switch(instruct.var){
        case 0: pop(instruct, pile); break;
        case 1: push(instruct, pile); break;
        case 2: iPop(instruct, pile); break;
        case 3: iPush(instruct, pile); break;
        case 4: push2(instruct, pile); break;
        case 5: call(instruct, pile, ppc); break;
        case 6: ret(instruct, pile, ppc); break;
        case 7: jmp(instruct, pile, ppc); break;
        case 8: jpc(instruct, pile, ppc); break;
        case 9: write(instruct, pile); break;
        case 10: read(instruct, pile); break;
        case 11: rnd(instruct, pile); break;
        case 12: dup(instruct, pile); break;
        case 13: op(instruct, pile); break;
        case 99: halt(instruct, pile);
  }
}

void pop(instructionHexa instruct, short* pile){

}

void push(instructionHexa instruct, short* pile){

}

void iPop(instructionHexa instruct, short* pile){

}

void iPush(instructionHexa instruct, short* pile){

}

void push2(instructionHexa instruct, short* pile){

}

void call(instructionHexa instruct, short* pile, int* ppc){

}

void ret(instructionHexa instruct, short* pile, int* ppc){

}

void jmp(instructionHexa instruct, short* pile, int* ppc){

}

void jpc(instructionHexa instruct, short* pile, int* ppc){

}

void write(instructionHexa instruct, short* pile){

}

void read(instructionHexa instruct, short* pile){

}

void rnd(instructionHexa instruct, short* pile){

}

void dup(instructionHexa instruct, short* pile){

}

void op(instructionHexa instruct, short* pile){

}

void halt(instructionHexa instruct, short* pile){

}