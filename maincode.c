#include <stdio.h>
#include "CircLib.h"
#include "createComponent.h"

int main(int argc, char *argv[]){

	FILE *f;
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
	f=fopen(argv[1],"r");
	
	c=fgetc(f);
	do{
		switch(c) {
			case 'R':{
				nodeR=(ResistanceT*)malloc(sizeof(ResistanceT));
				createR(f,nodeR);
				nodeR->next = rootR;
				rootR = nodeR;
				break;
			}
			case 'V':{createV(f);break;}
			case 'I':{createI(f);break;}
			case 'C':{createC(f);break;}
			case 'L':{createL(f);break;}
			case 'D':{createD(f);break;}
			case 'M':{createM(f);break;}
			case 'B':{createB(f);break;}
			case '*':{while(fgetc(f)!='\n'){}/*MOVE TO NEXT LINE*/break;}
			default:{break;}
		}
		c=fgetc(f);
	}while(!feof(f));
	
	fclose(f);
	
	
	if(groundflag==0){printf("\nError: There is no ground node. Program discontinued...\n");return(0);}
	
	nodeV=rootV;
	while(nodeV!=NULL){
		printf("\nname = %s\n",nodeV->name);
		printf("node1 = %s\n",nodeV->node1);
		printf("node2 = %s\n",nodeV->node2);
		printf("value = %e\n",nodeV->value);
	
		nodeV=nodeV->next;	
	}

	nodeI=rootI;
	while(nodeI!=NULL){
		printf("\nname = %s\n",nodeI->name);
		printf("node1 = %s\n",nodeI->node1);
		printf("node2 = %s\n",nodeI->node2);
		printf("value = %e\n",nodeI->value);
	
		nodeI=nodeI->next;	
	}

	nodeR=rootR;
	while(nodeR!=NULL){
		printf("\nname = %s\n",nodeR->name);
		printf("node1 = %s\n",nodeR->node1);
		printf("node2 = %s\n",nodeR->node2);
		printf("value = %e\n",nodeR->value);
	
		nodeR=nodeR->next;	
	}

	nodeC=rootC;
	while(nodeC!=NULL){
		printf("\nname = %s\n",nodeC->name);
		printf("node1 = %s\n",nodeC->node1);
		printf("node2 = %s\n",nodeC->node2);
		printf("value = %e\n",nodeC->value);
	
		nodeC=nodeC->next;	
	}

	nodeL=rootL;
	while(nodeL!=NULL){
		printf("\nname = %s\n",nodeL->name);
		printf("node1 = %s\n",nodeL->node1);
		printf("node2 = %s\n",nodeL->node2);
		printf("value = %e\n",nodeL->value);
	
		nodeL=nodeL->next;	
	}

	nodeD=rootD;
	while(nodeD!=NULL){
		printf("\nname = %s\n",nodeD->name);
		printf("node1 = %s\n",nodeD->node1);
		printf("node2 = %s\n",nodeD->node2);
		printf("value = %e\n",nodeD->value);
		printf("area = %d\n",nodeD->area);
	
		nodeD=nodeD->next;	
	}

	nodeM=rootM;
	while(nodeM!=NULL){
		printf("\nname = %s\n",nodeM->name);
		printf("drain = %s\n",nodeM->D);
		printf("gate = %s\n",nodeM->G);
		printf("source = %s\n",nodeM->S);
		printf("body = %s\n",nodeM->B);
		printf("width = %e\n",nodeM->W);
		printf("lenght = %e\n",nodeM->L);
	
		nodeM=nodeM->next;	
	}

	nodeB=rootB;
	while(nodeB!=NULL){
		printf("\nname = %s\n",nodeB->name);
		printf("collector = %s\n",nodeB->C);
		printf("base = %s\n",nodeB->B);
		printf("emitter = %s\n",nodeB->E);
		printf("area = %d\n",nodeB->area);
	
		nodeB=nodeB->next;	
	};



}