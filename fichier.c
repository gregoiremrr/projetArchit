#include "fichier.h"
#include "instruction.h"

#include <stdio.h>
#include <stdlib.h>

void recupInstructions(FILE* fichier, Instruction** instructions, int len, int lenLigne, int* OK){
    char* instruction = malloc((lenLigne+1)*sizeof(char));
    int i = 0;
    rewind(fichier);
    while(i <= len){
        scanLigne(fichier, instruction);
        convertInstruction(instruction, instructions[i], i, lenLigne, OK);
        i++;
    }
    free(instruction);
}

void ecritInstructions(FILE* fichier, Instruction** instructions, int len){
    for (int i = 0; i<=len; i++){
        fprintf(fichier, "%.2x %.4x\n", instructions[i]->commande->id, instructions[i]->commande->valeur);
    }
}

int sizeOfFile(FILE* fichier){
    int i = 0;
    char a = 'a';
    rewind(fichier);
    while(a != EOF){
        if (a == '\n')
            i++;
        a = fgetc(fichier);
    }
    return i;
}

int sizeMaxOfLine(FILE* fichier, int len){
    int max = 0;
    int compteur = 0;
    rewind(fichier);
    for (int i = 0; i<=len; i++){
        int j = 0;
        char a = fgetc(fichier);
        while (a != '\n' && a != EOF){
            compteur++;
            j++;
            a = fgetc(fichier);
        }
        if (compteur > max){
            max = compteur;
        }
        compteur = 0;
    }
    return max;
}

void scanLigne(FILE* fichier, char* instruction){
    int i = 0;
    char a = fgetc(fichier);
    while(a != '\n' && a != EOF){
        instruction[i] = a;
        a = fgetc(fichier);
        i++;
    }
    instruction[i] = '\0';
}