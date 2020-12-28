// fichier comptenant les fonctions
#include"fonctions.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

void operation(int i, instructionHexa* instruct, short* pile){
  switch(i){
    case 0:
          pile--;
          if (*(pile-1)==*pile){
            *(pile-1)=1;
          } else {*(pile-1)=0;}
          break;
    case 1:
          pile--;
          if (*(pile-1)!=*pile){
            *(pile-1)=1;
          } else {*(pile-1)=0;}
          break;

    case 2:
          pile--;
          if (*(pile-1)> *pile){
            *(pile-1)=1;
          } else {*(pile-1)=0;}
          break;

    case 3:
          pile--;
          if (*(pile-1)>= *pile){
            *(pile-1)=1;
          } else {*(pile-1)=0;}
          break;
    case 4:
          pile--;
          if (*(pile-1)< *pile){
            *(pile-1)=1;
          } else {*(pile-1)=0;}
          break;

    case 5:
          pile--;
          if (*(pile-1)>= *pile){
            *(pile-1)=1;
          } else {*(pile-1)=0;}
          break;

    case 6:
          pile--;
          *(pile-1)=*(pile-1)&*pile;
          break;
    case 8:
          pile--;
          *(pile-1)=*(pile-1)|*pile;
          break;
    case 9:
          *(pile-1)= ~*(pile-1);
          break;
    case 10:
          *(pile-1)=-*(pile-1);
          break;
    case 11:
          pile--;
          *(pile-1)=*(pile-1)+*pile;
          break;

    case 12:
          pile--;
          *(pile-1)=*(pile-1) - *pile;
          break;
    case 13:
          pile--;
          *(pile-1)=*(pile-1)**pile;
          break;
    case 14:
          pile--;
          *(pile-1)=*(pile-1)/(*pile);
          break;
    case 15:
          pile--;
          *(pile-1)=*(pile-1)%(*pile);
          break;
  }
}


void  pop(instructionHexa* instruct,short* pile){

}
void push(instructionHexa *instruct, short* pile){
  short v=instruct->value;
  *pile= *(pile+v);
  pile++;
}
void iPop(instructionHexa * instruct, short* pile){
  *(pile+(*pile))= *(pile-1);
}
void iPush(instructionHexa *  instruct, short* pile){

}
void push2(instructionHexa * instruct, short* pile){
  short v=instruct->value;
  *(pile)=v;
}
void call( instructionHexa * instruct, short* pile, int* ppc){
  short v=instruct->value;
  ppc++;
  *ppc=*ppc+ v;
}
void ret(instructionHexa * instruct,short* pile, int* ppc){
  ppc--;
}
void jmp(instructionHexa *instruct, short* pile, int* ppc){
  *ppc=*ppc+(instruct->value);
}
void jpc(instructionHexa * instruct, short* pile,int* ppc){
  pile--; //accede a la valeur sur le tas
  int v= *pile;
  if (v!=0){
    *ppc=*ppc+instruct->value;
  }
}

void write(instructionHexa * instruct, short* pile){
  printf("%d", *(pile+(instruct->value)));
}
void read(instructionHexa * instruct, short* pile){
  short x;
  printf("rentrer une valeur qui sera mise dans la variable a l adresse %d : ",instruct->value);
  scanf("%hd",&x);
  *(pile+(instruct->value))=x;
}
void rnd(instructionHexa * instruct, short* pile){
  int nb=0;
  srand(time(NULL));
  nb=rand()%(instruct->value);
  *pile=nb;
  pile++;
}
void dup(instructionHexa * instruct, short* pile){
    *pile=*(pile-1);
    pile++;
}
void op(instructionHexa *instruct, short* pile){
  int i=instruct->value;
  if (i>=0 && i<=15){
    operation(i,instruct,pile);
  } else {printf("le code d operation est incorrect, c est un entier compris entre 0 et 15 inclus");
    }
}

void halt(instructionHexa * instruct, short* pile){

}
