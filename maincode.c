#include <stdio.h>
#include "CircLib.h"
#include "createComponent.c"
#include <stdlib.h>
#include <string.h>
#include <math.h>


//Omada ergasias
// Ioanna Pantelopoulou
// Dimitris Datsogiannis
// Dimitris Garyfallou
// Aggelos Toutziaris




int main(int argc, char *argv[]){

	FILE *f=NULL;
	VoltT *nodeV;
	AmperT *nodeI;
	ResistanceT *nodeR;
	CapacitorT *nodeC;
	InductorT *nodeL;
	DiodeT *nodeD;
	MosT *nodeM;
	BjtT *nodeB;
	char c;
	
	initCirc();
	
	f=fopen(argv[1],"r");			//Anoigma tou arxeiou
	if(f==NULL){printf("\nProblem opening file. Program terminated...\n");return(0);}		//Elegxos an to arxeio anoikse kanonika, alliws termatismos..
	
	
//Diavasma xaraktira kai antistoixi leitourgia analoga me auton (Provlepsi gia grammi sxoliwn kai gia telos arxeiou)
	c=fgetc(f);
	do{
		switch(c) {
			case 'R' :{createR(f);break;}
			case 'V':{createV(f);break;}
			case 'I':{createI(f);break;}
			case 'C':{createC(f);break;}
			case 'L':{createL(f);break;}
			case 'D':{createD(f);break;}
			case 'M':{createM(f);break;}
			case 'B':{createB(f);break;}
			case 'r' :{createR(f);break;}
			case 'v':{createV(f);break;}
			case 'i':{createI(f);break;}
			case 'c':{createC(f);break;}
			case 'l':{createL(f);break;}
			case 'd':{createD(f);break;}
			case 'm':{createM(f);break;}
			case 'b':{createB(f);break;}
			case '*':{
			c=fgetc(f);
			while(c!='\n'&&(c!=EOF)){c=fgetc(f);}/*MOVE TO NEXT LINE*/break;}
			default:{break;}
		}
		if(c!=EOF){c=fgetc(f);}
	}while(!feof(f));

	fclose(f);

//An den yparxei komvos 0 (geiwsi) to programma termatizei
	if(groundflag==0){printf("\nError: There is no ground node. Program terminated...\n");return(0);}
	
//Ektypwsi olwn twn stoixeiwn tou kyklwmatos pou diavastikan..	

	nodeV=rootV;
	printf("\n---Volt---\n");
	while(nodeV!=NULL){
		printf("name = %s  ",nodeV->name);
		printf("node1 = %s  ",nodeV->node1);
		printf("node2 = %s  ",nodeV->node2);
		printf("value = %e\n",nodeV->value);
	
		nodeV=nodeV->next;	
	}

	nodeI=rootI;
	printf("\n---Amper---\n");
	while(nodeI!=NULL){
		printf("name = %s  ",nodeI->name);
		printf("node1 = %s  ",nodeI->node1);
		printf("node2 = %s  ",nodeI->node2);
		printf("value = %e\n",nodeI->value);
	
		nodeI=nodeI->next;	
	}

	nodeR=rootR;
	printf("\n---Resistors---\n");
	while(nodeR!=NULL){
		printf("name = %s ",nodeR->name);
		printf("node1 = %s ",nodeR->node1);
		printf("node2 = %s ",nodeR->node2);
		printf("value = %e\n",nodeR->value);
	
		nodeR=nodeR->next;	
	}

	nodeC=rootC;
	printf("\n---Capacitors---\n");
	while(nodeC!=NULL){
		printf("name = %s ",nodeC->name);
		printf("node1 = %s  ",nodeC->node1);
		printf("node2 = %s  ",nodeC->node2);
		printf("value = %e\n",nodeC->value);
	
		nodeC=nodeC->next;	
	}

	nodeL=rootL;
	printf("\n---Inductors---\n");
	while(nodeL!=NULL){
		printf("name = %s  ",nodeL->name);
		printf("node1 = %s  ",nodeL->node1);
		printf("node2 = %s  ",nodeL->node2);
		printf("value = %e\n",nodeL->value);
	
		nodeL=nodeL->next;	
	}

	nodeD=rootD;
	printf("\n---Diodes---\n");
	while(nodeD!=NULL){
		printf("name = %s  ",nodeD->name);
		printf("node1 = %s  ",nodeD->node1);
		printf("node2 = %s  ",nodeD->node2);
//		printf("value = %e  ",nodeD->value);
		printf("area = %d\n",nodeD->area);
	
		nodeD=nodeD->next;	
	}

	nodeM=rootM;
	printf("\n---Transistors MOS---\n");
	while(nodeM!=NULL){
		printf("name = %s  ",nodeM->name);
		printf("drain = %s  ",nodeM->D);
		printf("gate = %s  ",nodeM->G);
		printf("source = %s  ",nodeM->S);
		printf("body = %s  ",nodeM->B);
		printf("lenght = %e  ",nodeM->L);
		printf("width = %e\n",nodeM->W);
		nodeM=nodeM->next;	
	}

	nodeB=rootB;
	printf("\n---Transistors BJT---\n");
	while(nodeB!=NULL){
		printf("name = %s  ",nodeB->name);
		printf("collector = %s  ",nodeB->C);
		printf("base = %s  ",nodeB->B);
		printf("emitter = %s  ",nodeB->E);
		printf("area = %d\n",nodeB->area);
	
		nodeB=nodeB->next;	
	};



}