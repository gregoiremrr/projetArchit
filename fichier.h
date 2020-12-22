#ifndef FICHIER
#define FICHIER

#include "instruction.h"
#include <stdio.h>

void recupInstructions(FILE* fichier, Instruction** instruction, int len, int lenLigne, int* OK);

void ecritInstructions(FILE* fichier, Instruction** instruction, int len);

int sizeOfFile(FILE* fichier);

int sizeMaxOfLine(FILE* fichier, int len);

void scanLigne(FILE* fichier, char* instruction);

#endif