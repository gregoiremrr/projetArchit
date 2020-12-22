#ifndef EXEC
#define EXEC

#include <stdio.h>

typedef struct {
    int var;
    short value;
} instructionHexa;

void remplitStruct(instructionHexa* structu, char* instruct);

void ReadLowLangageFile(FILE* fic, char** Prog);

void fonction(instructionHexa instruct, short* pile, int* ppc);

#endif