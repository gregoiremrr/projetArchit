#ifndef FONCTIONS_H
#define FONCTIONS_H
#include<stdio.h>


typedef struct instructionHexa{
    int var;
    short value;
}instructionHexa;


//le pointeur sur pile SP sera nomme par pile
//le pointeur sur instruction pcc est initialisé à l'adresse 1
// on simule une mémoire comptenant le programme (instruction) grace à un tableau
//
void pop(instructionHexa *instruct,short* pile);
void push(instructionHexa *instruct, short* pile);
void iPop(instructionHexa *instruct, short* pile);
void iPush(instructionHexa *instruct, short* pile);
void push2(instructionHexa *instruct, short* pile);
void call( instructionHexa *instruct, short* pile, int* ppc);
void ret(instructionHexa *instruct,short* pile, int *ppc);
void jmp(instructionHexa *instruct, short* pile,int* ppc);
void jpc(instructionHexa *instruct, short* pile,int* ppc);
void write(instructionHexa *instruct, short* pile);
void read(instructionHexa *instruct, short* pile);
void rnd(instructionHexa  *instruct, short* pile);
void dup(instructionHexa *instruct, short* pile);
void op(instructionHexa *instruct, short* pile);
void halt(instructionHexa *instruct, short* pile);

void operation(int i, instructionHexa *instruct, short* pile);
#endif
