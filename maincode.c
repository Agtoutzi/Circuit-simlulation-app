#include <stdio.h>
#include "CircLib.h"
#include "createComponent.h"

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
			case 'R':{createR(f);break;}
			case 'V':{createV(f);break;}
			case 'I':{createI(f);break;}
			case 'C':{createC(f);break;}
			case 'L':{createL(f);break;}
			case 'D':{createD(f);break;}
			case 'M':{createM(f);break;}
			case 'B':{createB(f);break;}
			case '*':{
			c=fgetc(f);
			while(c!='\n'&&(c!=EOF)){c=fgetc(f);}/*MOVE TO NEXT LINE*/break;}
			default:{break;}
		}
		if(c!=EOF){c=fgetc(f);putchar(c);}
	}while(!feof(f));
	printf("point16\n");
	fclose(f);
	printf("point17\n");
//An den yparxei komvos 0 (geiwsi) to programma termatizei
	if(groundflag==0){printf("\nError: There is no ground node. Program terminated...\n");return(0);}
	
printf("point18\n");
//Ektypwsi olwn twn stoixeiwn tou kyklwmatos pou diavastikan..	

	nodeV=rootV;
	while(nodeV!=NULL){
		printf("\n---Volt---\n");
		printf("name = %s\n",nodeV->name);
		printf("node1 = %s\n",nodeV->node1);
		printf("node2 = %s\n",nodeV->node2);
		printf("value = %e\n",nodeV->value);
	
		nodeV=nodeV->next;	
	}
printf("point19\n");
	nodeI=rootI;
	while(nodeI!=NULL){
		printf("\n---Amper---\n");
		printf("name = %s\n",nodeI->name);
		printf("node1 = %s\n",nodeI->node1);
		printf("node2 = %s\n",nodeI->node2);
		printf("value = %e\n",nodeI->value);
	
		nodeI=nodeI->next;	
	}

	nodeR=rootR;
	while(nodeR!=NULL){
		printf("\n---Resistance---\n");
		printf("name = %s\n",nodeR->name);
		printf("node1 = %s\n",nodeR->node1);
		printf("node2 = %s\n",nodeR->node2);
		printf("value = %e\n",nodeR->value);
	
		nodeR=nodeR->next;	
	}

	nodeC=rootC;
	while(nodeC!=NULL){
		printf("\n---Capacitor---\n");
		printf("name = %s\n",nodeC->name);
		printf("node1 = %s\n",nodeC->node1);
		printf("node2 = %s\n",nodeC->node2);
		printf("value = %e\n",nodeC->value);
	
		nodeC=nodeC->next;	
	}

	nodeL=rootL;
	while(nodeL!=NULL){
		printf("\n---Inductor---\n");
		printf("name = %s\n",nodeL->name);
		printf("node1 = %s\n",nodeL->node1);
		printf("node2 = %s\n",nodeL->node2);
		printf("value = %e\n",nodeL->value);
	
		nodeL=nodeL->next;	
	}

	nodeD=rootD;
	while(nodeD!=NULL){
		printf("\n---Diode---\n");
		printf("name = %s\n",nodeD->name);
		printf("node1 = %s\n",nodeD->node1);
		printf("node2 = %s\n",nodeD->node2);
		printf("value = %e\n",nodeD->value);
		printf("area = %d\n",nodeD->area);
	
		nodeD=nodeD->next;	
	}

	nodeM=rootM;
	while(nodeM!=NULL){
		printf("\n---Transistor MOS---\n");
		printf("name = %s\n",nodeM->name);
		printf("drain = %s\n",nodeM->D);
		printf("gate = %s\n",nodeM->G);
		printf("source = %s\n",nodeM->S);
		printf("body = %s\n",nodeM->B);
		printf("lenght = %e\n",nodeM->L);
		printf("width = %e\n",nodeM->W);
		nodeM=nodeM->next;	
	}

	nodeB=rootB;
	while(nodeB!=NULL){
		printf("\n---Transistor BJT---\n");
		printf("name = %s\n",nodeB->name);
		printf("collector = %s\n",nodeB->C);
		printf("base = %s\n",nodeB->B);
		printf("emitter = %s\n",nodeB->E);
		printf("area = %d\n",nodeB->area);
	
		nodeB=nodeB->next;	
	};



}