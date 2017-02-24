//project eumorfopoulou
//dhmiourgw arxika 8 structs ta opoia to kathe ena tha perigrafei ena tupo stoixeiou dld ena gia V,I,R
#include<stdio.h>
#include "projectE.h"
#include <stdlib.h>


//tis root dld thn arxikh thesh pou deixnei h lista thn vazw global metavlith
VoltT *rootV;
AmperT *rootA;
ResistanceT *rootR;
CapacityT *rootC;
IndustanceT *rootI;
PassageT *rootP;
MosT *rootM;
BjtT *rootB;

//dhmhiourgw 8 listes mia gia kathe tupo struct  h lista pou tha dhmiourgisw eina aplh
//arxikopoiw tis listes 
void init_list(){
  rootV = NULL;
  rootA = NULL;
  rootR = NULL;
  rootC = NULL;
  rootI = NULL;
  rootP = NULL;
  rootM = NULL;
  rootB = NULL;
  
} 

//Dhmiourgia listas aplhs diasundedemenhs opou ton root koitazei ton komvo pou eiserxetai kathe fora ws neos
//volt

void insert_listV(char newname[],char newnode1[],char newnode2[],char newvalue[]){
  VoltT *curr;
  curr = (VoltT*) malloc(sizeof(VoltT));
  curr->name = newname;
  curr->node1 = newnode1;
  curr->node2 = newnode2;
  curr->value = newvalue;
/* εισαγωγή νέου κόμβου στην αρχή της λίστας */
  curr->next = rootV;
  rootV = curr;

}
  
//amper   
void insert_listA(char newname[],char newnode1[],char newnode2[],char newvalue[]){
  AmperT *curr;
  curr = (AmperT*) malloc(sizeof(AmperT));
  curr->name = newname;
  curr->node1 = newnode1;
  curr->node2 = newnode2;
  curr->value = newvalue;
/* εισαγωγή νέου κόμβου στην αρχή της λίστας */
  curr->next = rootA;
  rootA = curr;

}
//capacity
void insert_listC(char newname[],char newnode1[],char newnode2[],char newvalue[]){
  CapacityT *curr;
  curr = (CapacityT*) malloc(sizeof(CapacityT));
  curr->name = newname;
  curr->node1 = newnode1;
  curr->node2 = newnode2;
  curr->value = newvalue;
/* εισαγωγή νέου κόμβου στην αρχή της λίστας */
  curr->next = rootC;
  rootC = curr;

}
//industance
void insert_listI(char newname[],char newnode1[],char newnode2[],char newvalue[]){
  IndustanceT *curr;
  curr = (IndustanceT*) malloc(sizeof(IndustanceT));
  curr->name = newname;
  curr->node1 = newnode1;
  curr->node2 = newnode2;
  curr->value = newvalue;
/* εισαγωγή νέου κόμβου στην αρχή της λίστας */
  curr->next = rootI;
  rootI = curr;

}
//passage
void insert_listP(char newname[],char newnode1[],char newnode2[],char newvalue[],int newarea){
  PassageT *curr;
  curr = (PassageT*) malloc(sizeof(PassageT));
  curr->name = newname;
  curr->node1 = newnode1;
  curr->node2 = newnode2;
  curr->value = newvalue;
  curr->area = newarea;
/* εισαγωγή νέου κόμβου στην αρχή της λίστας */
  curr->next = rootP;
  rootP = curr;

}
void insert_listM(char newname[],char newD,char newG,char newS,char newB,char newL[],char newW[]){
  MosT *curr;
  curr = (MosT*) malloc(sizeof(MosT));
  curr->name = newname;
  curr->D = newD;
  curr->G = newG;
  curr->S = newS;
  curr->B = newB;
  curr->L = newL;
  curr->W = newW;
/* εισαγωγή νέου κόμβου στην αρχή της λίστας */
  curr->next = rootM;
  rootM = curr;

}
void insert_listB(char newname[],char newC,char newB,char newE,int newarea){
  BjtT *curr;
  curr = (BjtT*) malloc(sizeof(BjtT));
  curr->name = newname;
  curr->C = newC;
  curr->B = newB;
  curr->E = newE;
  curr->area = newarea;
/* εισαγωγή νέου κόμβου στην αρχή της λίστας */
  curr->next = rootB;
  rootB = curr;

}

int main(int argc,char **argv){
    VoltT *V1;  
    



    
  printf("eimai omorfhhhhhhhhhhhhhhhhhhhhhhh");
return(0);
}



