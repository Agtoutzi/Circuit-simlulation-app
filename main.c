// Omada ergasias
// Ioanna Pantelopoulou
// Dimitris Datsogiannis
// Dimitris Garyfallou
// Aggelos Toutziaris


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "CircLib.h"
#include "hash.h"
#include "mna.h"
#include "options.h"
#include "free.h"
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_cblas.h>
#include <gsl/gsl_linalg.h>
#include "csparse.h"
#include "mna-sparse.h"
#include "transient.h"

int main(int argc, char *argv[]){

	FILE *f=NULL;

	char c;
	
	initCirc();

	f=fopen(argv[1],"r");		//Anoigma tou arxeiou
	if(f==NULL){printf("\nProblem opening file. Program terminated...\n");return(0);}		//Elegxos an to arxeio anoikse kanonika, alliws termatismos..
	
	
//Diavasma xaraktira kai antistoixi leitourgia analoga me auton (Provlepsi gia grammi sxoliwn kai gia telos arxeiou)
	c=fgetc(f);
	do{
		switch(c) {
			case 'R':{createR(f);break;}
			case 'V':{createV(f);m2++;break;}
			case 'I':{createI(f);break;}
			case 'C':{createC(f);break;}
			case 'L':{createL(f);m2++;break;}
			case 'D':{createD(f);break;}
			case 'M':{createM(f);break;}
			case 'B':{createB(f);break;}
			case 'r':{createR(f);break;}
			case 'v':{createV(f);m2++;break;}
			case 'i':{createI(f);break;}
			case 'c':{createC(f);break;}
			case 'l':{createL(f);m2++;break;}
			case 'd':{createD(f);break;}
			case 'm':{createM(f);break;}
			case 'b':{createB(f);break;}
			case '.':{read_options(f);break;}
			case '*':{
			c=fgetc(f);
			while(c!='\n'&&(c!=EOF)){c=fgetc(f);}/*MOVE TO NEXT LINE*/break;}
			default:{break;}
		}
		if(c!=EOF){c=fgetc(f);}
	}while(!feof(f));

	fclose(f);
	
//An den yparxei komvos 0 (geiwsi) to programma termatizei
	if(groundflag==0){
	  printf("\nError: There is no ground node. Program terminated...\n");
	  return(0);
	}

	printf("TRAN:%d\n",TRAN);
	printf("METHOD:%d\n",METHOD);
	printf("SPARSE:%d\n",SPARSE);
	printf("SPD:%d\n",SPD);
	printf("ITER:%d\n",ITER);
	printf("PLOT:%d\n",plot);
	
//	printLists();
//	printHash();

	//DC MODE

	if(SPARSE==0)
		CreateMna();
	else
		CreateMnaSparse();	
	
	/*EPILUSH SUSTHMATOS*/
	if(SPARSE==0){
	  if(SPD==0)
		solve();	  
	  else
		solve_spd();	  
	}else{
	  if(SPD==0)
		solveSparse();	  
	  else	
		solve_spdSparse();		
	}

	//TRANSIENT MODE
	
	if(TRAN==1) transient();

	freeAllmem();
	getchar();
	return(0);
}
