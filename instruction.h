#ifndef COMPIL
#define COMPIL

#include <stdio.h>

typedef struct {
	int value;
	char* nom;
} Adresse;

typedef struct {
	int id;
	int valeur;
	char* nomValeur;
} Commande;

typedef struct {
	Commande* commande;
	Adresse* adresse;
} Instruction;

int max(int a, int b);

void convertInstruction(char* strg, Instruction* instruction, int num, int lenLigne, int* OK);

void changeValueAdresse(Instruction** instructions, int len, int* OK);

int findValue(Instruction** instructions, char* nom, int len, int* OK, int num);

void strIntoStr(char* str, char* str2);

int compareStr(char* str1, char* str2, int len);

int strlength(char* str);

int valeur(int i);

int isNumber(char* strg);

int isNumberLetter(char* strg);

int chercheCarac(char* strg, char c);

#endif