#include "instruction.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int max(int a, int b){
    return (a>=b?a:b);
} 

void convertInstruction(char* strg, Instruction* instruction, int num, int lenLigne, int* OK){

    instruction->adresse->value = num;
    char* a = malloc(lenLigne*sizeof(char));
    int i = 0, j = 0;

    if (strchr(strg, ':')){
        i = 0;
        if(!islower(strg[0])){
            *OK = 0;
            if(strg[0] == ' '){
                printf("Erreur d'indentation avant l'etiquette (ligne %d)\n", num + 1);
                while (strg[i] == ' '){
                    i++;
                }
            } else {
                printf("Caractere interdit dans le nom de l'etiquette (ligne %d)\n", num + 1);
            }
        }
        char* etiquette = malloc(lenLigne*sizeof(char));
        j = 0;
        do{
            etiquette[j] = strg[i];
            i++;
            j++;
        }while (strg[i] != ':');
        etiquette[j] = '\0';
        strIntoStr(instruction->adresse->nom, etiquette);
        i++;
        while(strg[i] == ' ' || strg[i] == 9){
            i++;
        }
        j = 0;

        char* instr = malloc(lenLigne*sizeof(char));
        while (strg[i] != ' ' && strg[i] != '\0'){
            instr[j] = strg[i];
            j++;
            i++;
        }
        instr[j] = '\0';
        if (!(memcmp(instr, "pop", max(strlen(instr), strlen("pop"))))){
            instruction->commande->id = 0;
        }else if (!(memcmp(instr, "push", max(strlen(instr), strlen("push"))))){
            instruction->commande->id = 1;
        }else if (!(memcmp(instr, "iPop", max(strlen(instr), strlen("iPop"))))){
            instruction->commande->id = 2;
            instruction->commande->valeur = 0;
        }else if (!(memcmp(instr, "iPush", max(strlen(instr), strlen("iPush"))))){
            instruction->commande->id = 3;
            instruction->commande->valeur = 0;
        }else if (!(memcmp(instr, "push#", max(strlen(instr), strlen("push#"))))){
            instruction->commande->id = 4;
        }else if (!(memcmp(instr, "call", max(strlen(instr), strlen("call"))))){
            instruction->commande->id = 5;
        }else if (!(memcmp(instr, "ret", max(strlen(instr), strlen("ret"))))){
            instruction->commande->id = 6;
            instruction->commande->valeur = 0;
        }else if (!(memcmp(instr, "jmp", max(strlen(instr), strlen("jmp"))))){
            instruction->commande->id = 7;
        }else if (!(memcmp(instr, "jpc", max(strlen(instr), strlen("jpc"))))){
            instruction->commande->id = 8;
        }else if (!(memcmp(instr, "write", max(strlen(instr), strlen("write"))))){
            instruction->commande->id = 9;
        }else if (!(memcmp(instr, "read", max(strlen(instr), strlen("read"))))){
            instruction->commande->id = 10;
        }else if (!(memcmp(instr, "rnd", max(strlen(instr), strlen("rnd"))))){
            instruction->commande->id = 11;
        }else if (!(memcmp(instr, "dup", max(strlen(instr), strlen("dup"))))){
            instruction->commande->id = 12;
            instruction->commande->valeur = 0;
        }else if (!(memcmp(instr, "op", max(strlen(instr), strlen("op"))))){
            instruction->commande->id = 13;
        }else if (!(memcmp(instr, "halt", max(strlen(instr), strlen("halt"))))){
            instruction->commande->id = 99;
            instruction->commande->valeur = 0;
        }else {
            instruction->commande->id = -1;
            *OK = 0;
            printf("Erreur sur la commande : %s (ligne %d)\n", instr, num + 1);
        }

        if (strg[i] != '\0'){
            i++;
            j = 0;
            
            char* value = malloc(lenLigne*sizeof(char));
            while (strg[i] != '\0'){
                value[j] = strg[i];
                i++;
                j++;
            }
            value[j] = '\0';
            if (isNumber(value)){
                instruction->commande->valeur = strtol(value, NULL, 10);
                instruction->commande->nomValeur = NULL;
            } else if (isNumberLetter(value)) {
                strIntoStr(instruction->commande->nomValeur, value);
            } else {
                *OK = 0;
                instruction->commande->nomValeur = NULL;
                if (chercheCarac(value, ' ') || chercheCarac(value, 9)){
                    printf("Erreur sur le nombre d'arguments (ligne %d)\n", num + 1);
                } else {
                    printf("Erreur sur la valeur : %s (ligne %d)\n", value, num + 1);
                }
            }
            free(value);
        } else {
            if (instruction->commande->id == 2 ||
            instruction->commande->id == 3 ||
            instruction->commande->id == 6 ||
            instruction->commande->id == 12 ||
            instruction->commande->id == 99) {
                instruction->commande->valeur = 0;
                instruction->commande->nomValeur = NULL;
            } else {
                *OK = 0;
                instruction->commande->valeur = 0;
                instruction->commande->nomValeur = NULL;
                printf("Erreur sur le nombre d'arguments (ligne %d)\n", num + 1);
            }
        }
        free(etiquette);
        free(instr);
    } else {

        while (strg[i] == ' ' || strg[i] == 9){
            i++;
        }
        while (strg[i] != '\0'){
            a[j] = strg[i];
            j++;
            i++;
        }
        a[j] = '\0';

        instruction->adresse->nom = NULL;
        i = 0;
        j = 0;
        char* instr2 = malloc(lenLigne*sizeof(char));
        while (a[i] != ' ' && a[i] != '\0'){
            instr2[j] = a[i];
            j++;
            i++;
        }
        instr2[j] = '\0';
        if (!(memcmp(instr2, "pop", max(strlen(instr2), strlen("pop"))))){
            instruction->commande->id = 0;
        }else if (!(memcmp(instr2, "push", max(strlen(instr2), strlen("push"))))){
            instruction->commande->id = 1;
        }else if (!(memcmp(instr2, "iPop", max(strlen(instr2), strlen("iPop"))))){
            instruction->commande->id = 2;
            instruction->commande->valeur = 0;
        }else if (!(memcmp(instr2, "iPush", max(strlen(instr2), strlen("iPush"))))){
            instruction->commande->id = 3;
            instruction->commande->valeur = 0;
        }else if (!(memcmp(instr2, "push#", max(strlen(instr2), strlen("push#"))))){
            instruction->commande->id = 4;
        }else if (!(memcmp(instr2, "call", max(strlen(instr2), strlen("call"))))){
            instruction->commande->id = 5;
        }else if (!(memcmp(instr2, "ret", max(strlen(instr2), strlen("ret"))))){
            instruction->commande->id = 6;
            instruction->commande->valeur = 0;
        }else if (!(memcmp(instr2, "jmp", max(strlen(instr2), strlen("jmp"))))){
            instruction->commande->id = 7;
        }else if (!(memcmp(instr2, "jpc", max(strlen(instr2), strlen("jpc"))))){
            instruction->commande->id = 8;
        }else if (!(memcmp(instr2, "write", max(strlen(instr2), strlen("write"))))){
            instruction->commande->id = 9;
        }else if (!(memcmp(instr2, "read", max(strlen(instr2), strlen("read"))))){
            instruction->commande->id = 10;
        }else if (!(memcmp(instr2, "rnd", max(strlen(instr2), strlen("rnd"))))){
            instruction->commande->id = 11;
        }else if (!(memcmp(instr2, "dup", max(strlen(instr2), strlen("dup"))))){
            instruction->commande->id = 12;
            instruction->commande->valeur = 0;
        }else if (!(memcmp(instr2, "op", max(strlen(instr2), strlen("op"))))){
            instruction->commande->id = 13;
        }else if (!(memcmp(instr2, "halt", max(strlen(instr2), strlen("halt"))))){
            instruction->commande->id = 99;
            instruction->commande->valeur = 0;
        }else {
            instruction->commande->id = -1;
            *OK = 0;
            printf("Erreur sur la commande : %s (ligne %d)\n", instr2, num + 1);
        }
        if (a[i] != '\0'){
            i++;
            j = 0;
            char* value2 = malloc(lenLigne*sizeof(char));
            while (a[i] != '\0'){
                value2[j] = a[i];
                i++;
                j++;
            }
            value2[j] = '\0';
            if (isNumber(value2)){
                instruction->commande->valeur = strtol(value2, NULL, 10);
                instruction->commande->nomValeur = NULL;
            } else if (isNumberLetter(value2)) {
                strIntoStr(instruction->commande->nomValeur, value2);
            } else {
                *OK = 0;
                instruction->commande->nomValeur = NULL;
                if (chercheCarac(value2, ' ') || chercheCarac(value2, 9)){
                    printf("Erreur sur le nombre d'arguments (ligne %d)\n", num + 1);
                } else {
                    printf("Erreur sur la valeur : %s (ligne %d)\n", value2, num + 1);
                }
            }
            free(value2);
        } else {
            if (instruction->commande->id == 2 ||
            instruction->commande->id == 3 ||
            instruction->commande->id == 6 ||
            instruction->commande->id == 12 ||
            instruction->commande->id == 99) {
                instruction->commande->valeur = 0;
                instruction->commande->nomValeur = NULL;
            } else {
                *OK = 0;
                instruction->commande->valeur = 0;
                instruction->commande->nomValeur = NULL;
                printf("Erreur sur le nombre d'arguments (ligne %d)\n", num + 1);
            }
        }
        free(instr2);
    }
    free(a);
}

void changeValueAdresse(Instruction** instructions, int len, int* OK){
    for (int i = 0; i<=len; i++){
        if (instructions[i]->commande->nomValeur != NULL){
            instructions[i]->commande->valeur = valeur(findValue(instructions, instructions[i]->commande->nomValeur, len, OK, i)-i-1);
        } else if (instructions[i]->commande->id == 5 || instructions[i]->commande->id == 7 || instructions[i]->commande->id == 8){
            instructions[i]->commande->valeur = valeur(instructions[i]->commande->valeur-i-1);
        }
    }
}

int findValue(Instruction** instructions, char* nom, int len, int* OK, int num){
    int i = 0;
    while(i<len+1 && !compareStr(instructions[i]->adresse->nom, nom, max(strlength(instructions[i]->adresse->nom), strlen(nom)))){
        i++;
    }
    if (i==len+1){
        *OK = 0;
        printf("Erreur sur l'etiquette : %s (ligne %d)\n", nom, num + 1);
        return 0;
    }
    return i;
}

void strIntoStr(char* str, char* str2){
    for (int i = 0; i<=strlen(str2); i++){
        str[i] = str2[i];
    }
}

int compareStr(char* str1, char* str2, int len){
    if(str1 == NULL || str2 == NULL)
        return 0;
    for(int i = 0; i<len; i++){
        if (str1[i] != str2[i]){
            return 0;
        }
    }
    return 1;
}

int strlength(char* str){
    if (str == NULL)
        return 0;
    return strlen(str);
}

int valeur(int i){
	if (i<0){
	    return i+pow(2,16);
	}
	return i;
}

int isNumber(char* strg){
    int i = 0;
    while(strg[i] != '\0'){
        if(!isdigit(strg[i])){
            return 0;
        }
        i++;
    }
    return 1;
}

int isNumberLetter(char* strg){
    int i = 0;
    while(strg[i] != '\0'){
        if(!isdigit(strg[i]) && !isalpha(strg[i])){
            return 0;
        }
        i++;
    }
    return 1;
}

int chercheCarac(char* strg, char c){
    if (strchr(strg, c)==NULL){
        return 0;
    }
    return 1;
}