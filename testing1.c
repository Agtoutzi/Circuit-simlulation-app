#include <stdio.h>

#include "createComponent.h"

int main(int argc, char *argv[]){

	FILE *f;
	ResistanceT *node;
	char c;
	
	f = fopen(argv[1],"r");
	
	initCirc();
	
	do{
		c=fgetc(f);
		switch(c) {
			case 'R':{createR(f);break;}
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
	}while(!feof(f));
	
	
	node=rootR;
	do{
		printf("\nname = %s\n",node->name);
		printf("node1 = %s\n",node->node1);
		printf("node2 = %s\n",node->node2);
		printf("value = %e\n",node->value);
	
		node=node->next;	
	}while(node!=NULL);

	fclose(f);
	
}