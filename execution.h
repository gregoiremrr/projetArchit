#ifndef EXEC
#define EXEC

#include <stdio.h>

typedef struct {
    int var;
    short value;
} instructionHexa;

void remplitStruct(instructionHexa* structu, char* instruct);

void ReadLowLangageFile(FILE* fic, char** Prog);

void fonction(instructionHexa instruct, short* pile, int* ppc, int* psp, int len, int* OK2);

void pop(instructionHexa instruct, short* pile, int* ppc, int* psp, int* OK2);

void push(instructionHexa instruct, short* pile, int* ppc, int* psp, int* OK2);

void iPop(instructionHexa instruct, short* pile, int* ppc, int* psp, int* OK2);

void iPush(instructionHexa instruct, short* pile, int* ppc, int* psp, int* OK2);

void push2(instructionHexa instruct, short* pile, int* ppc, int* psp, int* OK2);

void call(instructionHexa instruct, short* pile, int* ppc, int* psp, int len, int* OK2);

void ret(instructionHexa instruct, short* pile, int* ppc, int* psp, int* OK2);

void jmp(instructionHexa instruct, short* pile, int* ppc, int len, int* OK2);

void jpc(instructionHexa instruct, short* pile, int* ppc, int* psp, int len, int* OK2);

void write(instructionHexa instruct, short* pile, int* ppc, int* OK2);

void read(instructionHexa instruct, short* pile, int* ppc, int* OK2);

void rnd(instructionHexa instruct, short* pile, int* ppc, int* psp, int* OK2);

void dup(instructionHexa instruct, short* pile, int* ppc, int* psp, int* OK2);

void op(instructionHexa instruct, short* pile, int* ppc, int* psp, int* OK2);

void halt(instructionHexa instruct, short* pile, int* ppc, int len);

#endif