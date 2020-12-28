#ifndef EXEC
#define EXEC

#include <stdio.h>

typedef struct {
    int var;
    short value;
} instructionHexa;

void remplitStruct(instructionHexa* structu, char* instruct);

void ReadLowLangageFile(FILE* fic, char** Prog);

void fonction(instructionHexa instruct, short* pile, int* ppc, int* psp);

void pop(instructionHexa instruct, short* pile, int* ppc, int* psp);

void push(instructionHexa instruct, short* pile, int* ppc, int* psp);

void iPop(instructionHexa instruct, short* pile, int* ppc, int* psp);

void iPush(instructionHexa instruct, short* pile, int* ppc, int* psp);

void push2(instructionHexa instruct, short* pile, int* ppc, int* psp);

void call(instructionHexa instruct, short* pile, int* ppc);

void ret(instructionHexa instruct, short* pile, int* ppc);

void jmp(instructionHexa instruct, short* pile, int* ppc);

void jpc(instructionHexa instruct, short* pile, int* ppc, int* psp);

void write(instructionHexa instruct, short* pile);

void read(instructionHexa instruct, short* pile);

void rnd(instructionHexa instruct, short* pile, int* ppc, int* psp);

void dup(instructionHexa instruct, short* pile, int* ppc, int* psp);

void op(instructionHexa instruct, short* pile, int* ppc, int* psp);

void halt(instructionHexa instruct, short* pile);

#endif