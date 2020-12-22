#include "fichier.h"
#include "instruction.h"

#include <stdio.h>
#include <stdlib.h>

unsigned short tab[4000] = {0};

int main(int argc, char *argv[]){

	FILE* fichierAssembleur = NULL;
	fichierAssembleur = fopen(argv[1], "r");

	if (fichierAssembleur != NULL){

		int len = sizeOfFile(fichierAssembleur);
		int lenLigne = sizeMaxOfLine(fichierAssembleur, len);
		
		int* OK = malloc(sizeof(int));
		*OK = 1;

		Instruction** instructions = malloc((len+1)*sizeof(Instruction*));
		for (int i = 0; i<=len; i++){
			instructions[i] = malloc(sizeof(Instruction));
			instructions[i]->commande = malloc(sizeof(Commande));
			instructions[i]->adresse = malloc(sizeof(Adresse));
			instructions[i]->commande->nomValeur = malloc(lenLigne*sizeof(char));
			instructions[i]->adresse->nom = malloc(lenLigne*sizeof(char));
		}

		recupInstructions(fichierAssembleur, instructions, len, lenLigne, OK);

		fclose(fichierAssembleur);
		changeValueAdresse(instructions, len, OK);

		if (*OK==1){
			printf("Compilation reussie ! Fichier hexa.txt cree !\n");
			FILE* fichierMachine = fopen("hexa.txt","w");
			ecritInstructions(fichierMachine, instructions, len);
			fclose(fichierMachine);
		}
		
		free(OK);
		for (int i = 0; i<len; i++){
			free(instructions[i]->adresse->nom);
			free(instructions[i]->commande->nomValeur);
			free(instructions[i]->adresse);
			free(instructions[i]->commande);
			free(instructions[i]);
		}
		free(instructions);
	}
	else
		printf("Erreur lors de l'ouverture du fichier");

	return 0;
}