#include "fichier.h"
#include "instruction.h"
#include "execution.h"

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
		
		for (int i = 0; i<len; i++){
			free(instructions[i]->adresse->nom);
			free(instructions[i]->commande->nomValeur);
			free(instructions[i]->adresse);
			free(instructions[i]->commande);
			free(instructions[i]);
		}
		free(instructions);

		if(*OK == 1){
			FILE* fic=NULL;
			fic= fopen("hexa.txt","r");

			if (fic != NULL){
				short pile[4000];

				char **Prog=malloc(len*sizeof(char*));

				for(int i=0;i<len;i++){
					Prog[i]=malloc(8*sizeof(char));
				}

				ReadLowLangageFile(fic,Prog);
				fclose(fic);

				instructionHexa* tab = malloc(len*sizeof(instructionHexa));

				for (int i = 0; i<len; i++){
					remplitStruct(tab+i, Prog[i]);
				}

				for (int pc = 0; pc<len; pc++){
					fonction(tab[pc], pile, &pc);
				}

				free(tab);
				for(int i = 0; i<len; i++){
					free(Prog[i]);
				}
				free(Prog);

			} else {
				printf("Erreur dans la lecture du fichier hexa.txt");
			}
		}
		free(OK);
	}
	else
		printf("Erreur lors de l'ouverture du fichier");

	return 0;
}