#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "CircLib.h"
#include "hash.h"
#include "mna.h"
#include "options.h"
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_cblas.h>
#include "mna-sparse.h"

//Sinartisi arxikopoiisis twn katholikwn metavlitwn
void initCirc(){

	rootV=NULL;
	rootI=NULL;
	rootR=NULL;
	rootC=NULL;
	rootL=NULL;
	rootD=NULL;
	rootM=NULL;
	rootB=NULL;
	groundflag=0;
	SPD=0;
	ITER=0;
	SPARSE=0;
	TRAN=0;
	METHOD=0;
	itol_value=1e-3;
	plot=0;
	m2=0;
	sizeA_sparse=0;
	sizeD_sparse=0;
	hash_count=1;
	hashtable = ht_create( 10000 );	//Create Hash table,oso ligotero tosa ligotera collision 
	
	dc_sweep=0;
	sweep_value_I=0;

}

//Sinartisi pou dimiourgei ena neo komvo gia pigi tasis, apothikeuei ta stoixeia gia auti tin pigi apo to arxeio, kai to sindeei stin arxi tis listas pigwn tasis
void createV(FILE *k){

	char d[100];
	char *readElement;
	VoltT *new;
	struct PWL* new2;
	struct PWL* temp;
	
	new = (VoltT*) malloc(sizeof(VoltT));

	fscanf(k,"%s",d);
	new->name=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->name , d);
	
	fscanf(k,"%s",d);
	new->node1=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->node1 , d);
	NewHashEntry(d);
	if((d[0]=='0') && (d[1]=='\0')){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->node2=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->node2 , d);
	NewHashEntry(d);
	if((d[0]=='0') && (d[1]=='\0')){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->value=atof(d);
	
	fgets(d,10000,k);
	readElement = strtok (d, " ,()\t");
	if(strcmp(readElement,"EXP")==0||strcmp(readElement,"exp")==0){
	  strcpy(new->transient_spec,"EXP");
//	  printf("\n\t\t\t\tnew->transient_spec: %s\n",new->transient_spec);
	  new->exp=(struct EXP*)malloc(sizeof(struct EXP));
	  new->exp->i1 = atof(strtok (NULL, " ,\t()"));
//	  printf("\n\t\t\t\texp->i1: %lf\n",new->exp->i1);
	  new->exp->i2 = atof(strtok (NULL, " ,\t()"));
//	  printf("\n\t\t\t\texp->i2: %lf\n",new->exp->i2);
	  new->exp->td1 = atof(strtok (NULL, " ,\t()"));
//	  printf("\n\t\t\t\texp->td1: %lf\n",new->exp->td1);
	  new->exp->tc1 = atof(strtok (NULL, " ,\t()"));
//	  printf("\n\t\t\t\texp->tc1: %lf\n",new->exp->tc1);
	  new->exp->td2 = atof(strtok (NULL, " ,\t()"));
//	  printf("\n\t\t\t\texp->td2: %lf\n",new->exp->td2);
	  new->exp->tc2 = atof(strtok (NULL, " ,\t()"));
//	  printf("\n\t\t\t\texp->tc2: %lf\n",new->exp->tc2);
	}else if(strcmp(readElement,"SIN")==0||strcmp(readElement,"sin")==0){
	  strcpy(new->transient_spec,"SIN");
//	  printf("\n\t\t\t\tnew->transient_spec: %s\n",new->transient_spec);
	  new->sin=(struct SIN*)malloc(sizeof(struct SIN));
	  new->sin->i1 = atof(strtok (NULL, " ,\t()"));
//	  printf("\n\t\t\t\tsin->i1: %lf\n",new->sin->i1);
	  new->sin->ia = atof(strtok (NULL, " ,\t()"));
//	  printf("\n\t\t\t\tsin->ia: %lf\n",new->sin->ia);
	  new->sin->fr = atof(strtok (NULL, " ,\t()"));
//	  printf("\n\t\t\t\tsin->fr: %lf\n",new->sin->fr);
	  new->sin->td = atof(strtok (NULL, " ,\t()"));
//	  printf("\n\t\t\t\tsin->td: %lf\n",new->sin->td);
	  new->sin->df = atof(strtok (NULL, " ,\t()"));
//	  printf("\n\t\t\t\tsin->df: %lf\n",new->sin->df);
	  new->sin->ph = atof(strtok (NULL, " ,\t()"));
//	  printf("\n\t\t\t\tsin->ph: %lf\n",new->sin->ph);
	}else if(strcmp(readElement,"PULSE")==0||strcmp(readElement,"pulse")==0){
	  strcpy(new->transient_spec,"PULSE");
//	  printf("\n\t\t\t\tnew->transient_spec: %s\n",new->transient_spec);
	  new->pulse=(struct PULSE*)malloc(sizeof(struct PULSE));
	  new->pulse->i1 = atof(strtok (NULL, " ,\t()"));
//	  printf("\n\t\t\t\tpulse->i1: %lf\n",new->pulse->i1);
	  new->pulse->i2 = atof(strtok (NULL, " ,\t()"));
//	  printf("\n\t\t\t\tpulse->i2: %lf\n",new->pulse->i2);
	  new->pulse->td = atof(strtok (NULL, " ,\t()"));
//	  printf("\n\t\t\t\tpulse->td: %lf\n",new->pulse->td);
	  new->pulse->tr = atof(strtok (NULL, " ,\t()"));
//	  printf("\n\t\t\t\tpulse->tr: %lf\n",new->pulse->tr);
	  new->pulse->tf = atof(strtok (NULL, " ,\t()"));
//	  printf("\n\t\t\t\tpulse->tf: %lf\n",new->pulse->tf);
	  new->pulse->pw = atof(strtok (NULL, " ,\t()"));
//	  printf("\n\t\t\t\tpulse->pw: %lf\n",new->pulse->pw);
	  new->pulse->per = atof(strtok (NULL, " ,\t()"));
//	  printf("\n\t\t\t\tpulse->per: %lf\n",new->pulse->per);
	}else if(strcmp(readElement,"PWL")==0||strcmp(readElement,"pwl")==0){
	  strcpy(new->transient_spec,"PWL");
//	  printf("\n\t\t\t\tnew->transient_spec: %s\n",new->transient_spec);
	  new->pwl=(struct PWL*)malloc(sizeof(struct PWL));
	  new->pwl->t = atof(strtok (NULL, " ,\t()\n"));
//	  printf("\n\t\t\t\tpwl->t: %lf\n",new->pwl->t);
	  new->pwl->i = atof(strtok (NULL, " ,\t()\n"));
//	  printf("\n\t\t\t\tpwl->i: %lf\n",new->pwl->i);
	  new->pwl->next=NULL;
	  temp=new->pwl;
	  readElement = strtok (NULL, " ,\t()\n");
	  
	  while(readElement!=NULL){
	    new2=(struct PWL*)malloc(sizeof(struct PWL));
	    temp->next=new2;
	    new2->t=atof(readElement);
//	  printf("\n\t\t\t\tpwl->t: %lf\n",new2->t);
	    new2->i=atof(strtok (NULL, " ,\t()\r\n"));
//	  printf("\n\t\t\t\tpwl->i: %lf\n",new2->i);
	    readElement = strtok (NULL, " ,\t()\r\n");
//	  printf("\n\t\t\t\treadElement: %s\n",readElement);
	    temp=new2;
	  }
	}
	
	new->next = rootV;
	rootV = new;
	
	if(strcmp(new->node1,"0")){sizeA_sparse+=2;}
	if(strcmp(new->node2,"0")){sizeA_sparse+=2;}
	
}

//Sinartisi pou dimiourgei ena neo komvo gia pigi reumatos, apothikeuei ta stoixeia gia auti tin pigi apo to arxeio, kai to sindeei stin arxi tis listas pigwn reumatos
void createI(FILE *k){

	char d[100];
	char *readElement;
	struct PWL* new2;
	struct PWL* temp;
	AmperT *new;

	new = (AmperT*) malloc(sizeof(AmperT));

	fscanf(k,"%s",d);
	new->name=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->name , d);
	
	fscanf(k,"%s",d);
	new->node1=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->node1 , d);
	NewHashEntry(d);
	if((d[0]=='0') && (d[1]=='\0')){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->node2=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->node2 , d);
	NewHashEntry(d);
	if((d[0]=='0') && (d[1]=='\0')){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->value=atof(d);
	
	fgets(d,10000,k);
	readElement = strtok (d, " ,()\t");
	if(strcmp(readElement,"EXP")==0){
	  strcpy(new->transient_spec,"EXP");
//	  printf("\n\t\t\t\tnew->transient_spec: %s\n",new->transient_spec);
	  new->exp=(struct EXP*)malloc(sizeof(struct EXP));
	  new->exp->i1 = atof(strtok (NULL, " ,\t()"));
//	  printf("\n\t\t\t\texp->i1: %lf\n",new->exp->i1);
	  new->exp->i2 = atof(strtok (NULL, " ,\t()"));
//	  printf("\n\t\t\t\texp->i2: %lf\n",new->exp->i2);
	  new->exp->td1 = atof(strtok (NULL, " ,\t()"));
//	  printf("\n\t\t\t\texp->td1: %lf\n",new->exp->td1);
	  new->exp->tc1 = atof(strtok (NULL, " ,\t()"));
//	  printf("\n\t\t\t\texp->tc1: %lf\n",new->exp->tc1);
	  new->exp->td2 = atof(strtok (NULL, " ,\t()"));
//	  printf("\n\t\t\t\texp->td2: %lf\n",new->exp->td2);
	  new->exp->tc2 = atof(strtok (NULL, " ,\t()"));
//	  printf("\n\t\t\t\texp->tc2: %lf\n",new->exp->tc2);
	}else if(strcmp(readElement,"SIN")==0){
	  strcpy(new->transient_spec,"SIN");
//	  printf("\n\t\t\t\tnew->transient_spec: %s\n",new->transient_spec);
	  new->sin=(struct SIN*)malloc(sizeof(struct SIN));
	  new->sin->i1 = atof(strtok (NULL, " ,\t()"));
//	  printf("\n\t\t\t\tsin->i1: %lf\n",new->sin->i1);
	  new->sin->ia = atof(strtok (NULL, " ,\t()"));
//	  printf("\n\t\t\t\tsin->ia: %lf\n",new->sin->ia);
	  new->sin->fr = atof(strtok (NULL, " ,\t()"));
//	  printf("\n\t\t\t\tsin->fr: %lf\n",new->sin->fr);
	  new->sin->td = atof(strtok (NULL, " ,\t()"));
//	  printf("\n\t\t\t\tsin->td: %lf\n",new->sin->td);
	  new->sin->df = atof(strtok (NULL, " ,\t()"));
//	  printf("\n\t\t\t\tsin->df: %lf\n",new->sin->df);
	  new->sin->ph = atof(strtok (NULL, " ,\t()"));
//	  printf("\n\t\t\t\tsin->ph: %lf\n",new->sin->ph);
	}else if(strcmp(readElement,"PULSE")==0){
	  strcpy(new->transient_spec,"PULSE");
//	  printf("\n\t\t\t\tnew->transient_spec: %s\n",new->transient_spec);
	  new->pulse=(struct PULSE*)malloc(sizeof(struct PULSE));
	  new->pulse->i1 = atof(strtok (NULL, " ,\t()"));
//	  printf("\n\t\t\t\tpulse->i1: %lf\n",new->pulse->i1);
	  new->pulse->i2 = atof(strtok (NULL, " ,\t()"));
//	  printf("\n\t\t\t\tpulse->i2: %lf\n",new->pulse->i2);
	  new->pulse->td = atof(strtok (NULL, " ,\t()"));
//	  printf("\n\t\t\t\tpulse->td: %lf\n",new->pulse->td);
	  new->pulse->tr = atof(strtok (NULL, " ,\t()"));
//	  printf("\n\t\t\t\tpulse->tr: %lf\n",new->pulse->tr);
	  new->pulse->tf = atof(strtok (NULL, " ,\t()"));
//	  printf("\n\t\t\t\tpulse->tf: %lf\n",new->pulse->tf);
	  new->pulse->pw = atof(strtok (NULL, " ,\t()"));
//	  printf("\n\t\t\t\tpulse->pw: %lf\n",new->pulse->pw);
	  new->pulse->per = atof(strtok (NULL, " ,\t()"));
//	  printf("\n\t\t\t\tpulse->per: %lf\n",new->pulse->per);
	}else if(strcmp(readElement,"PWL")==0){
	  strcpy(new->transient_spec,"PWL");
//	  printf("\n\t\t\t\tnew->transient_spec: %s\n",new->transient_spec);
	  new->pwl=(struct PWL*)malloc(sizeof(struct PWL));
	  new->pwl->t = atof(strtok (NULL, " ,\t()\n"));
//	  printf("\n\t\t\t\tpwl->t: %lf\n",new->pwl->t);
	  new->pwl->i = atof(strtok (NULL, " ,\t()\n"));
//	  printf("\n\t\t\t\tpwl->i: %lf\n",new->pwl->i);
	  new->pwl->next=NULL;
	  temp=new->pwl;
	  readElement = strtok (NULL, " ,\t()\n");
	  
	  while(readElement!=NULL){
	    new2=(struct PWL*)malloc(sizeof(struct PWL));
	    temp->next=new2;
	    new2->t=atof(readElement);
//	  printf("\n\t\t\t\tpwl->t: %lf\n",new2->t);
	    new2->i=atof(strtok (NULL, " ,\t()\r\n"));
//	  printf("\n\t\t\t\tpwl->i: %lf\n",new2->i);
	    readElement = strtok (NULL, " ,\t()\r\n");
//	  printf("\n\t\t\t\treadElement: %s\n",readElement);
	    temp=new2;
	  }
	}
	
	new->next = rootI;
	rootI = new;
}

//Sinartisi pou dimiourgei ena neo komvo gia antistasi, apothikeuei ta stoixeia gia auti tin antistasi apo to arxeio, kai to sindeei stin arxi tis listas antistasewn
void createR(FILE *k){

	char d[100];
	
	ResistanceT *new;
	
	new = (ResistanceT*)malloc(sizeof(ResistanceT));
	
	fscanf(k,"%s",d);
	new->name=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->name , d);
	
	fscanf(k,"%s",d);
	new->node1=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->node1 , d);
	NewHashEntry(d);
	if((d[0]=='0') && (d[1]=='\0')){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->node2=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->node2 , d);
	NewHashEntry(d);
	if((d[0]=='0') && (d[1]=='\0')){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->value=atof(d);

	new->next=rootR;
	rootR=new;
	
	while((d[0]=fgetc(k))!='\n'&&(d[0]!=EOF)){}
	if(strcmp(new->node1,"0")){sizeA_sparse++;}
	if(strcmp(new->node2,"0")){sizeA_sparse++;}
	if(strcmp(new->node1,"0")&&strcmp(new->node2,"0")){sizeA_sparse+=2;}


}

//Sinartisi pou dimiourgei ena neo komvo gia piknwti, apothikeuei ta stoixeia gia auto ton piknwti apo to arxeio, kai to sindeei stin arxi tis listas piknwtwn
void createC(FILE *k){

	char d[100];
	CapacitorT *new;

	new = (CapacitorT*) malloc(sizeof(CapacitorT));

	fscanf(k,"%s",d);
	new->name=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->name , d);
	
	fscanf(k,"%s",d);
	new->node1=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->node1 , d);
	NewHashEntry(d);
	if((d[0]=='0') && (d[1]=='\0')){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->node2=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->node2 , d);
	NewHashEntry(d);
	if((d[0]=='0') && (d[1]=='\0')){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->value=atof(d);
	
	new->next = rootC;
	rootC = new;
	
	while((d[0]=fgetc(k))!='\n'&&(d[0]!=EOF)){}
	if(strcmp(new->node1,"0")){sizeD_sparse++;}
	if(strcmp(new->node2,"0")){sizeD_sparse++;}
	if(strcmp(new->node1,"0")&&strcmp(new->node2,"0")){sizeD_sparse+=2;}

}

//Sinartisi pou dimiourgei ena neo komvo gia pinio, apothikeuei ta stoixeia gia auto to pinio apo to arxeio, kai to sindeei stin arxi tis listas piniwn
void createL(FILE *k){

	char d[100];
	InductorT *new;

	new = (InductorT*) malloc(sizeof(InductorT));

	fscanf(k,"%s",d);
	new->name=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->name , d);
	
	fscanf(k,"%s",d);
	new->node1=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->node1 , d);
	NewHashEntry(d);
	if((d[0]=='0') && (d[1]=='\0')){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->node2=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->node2 , d);
	NewHashEntry(d);
	if((d[0]=='0') && (d[1]=='\0')){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->value=atof(d);
	
	new->next = rootL;
	rootL = new;
	
	while((d[0]=fgetc(k))!='\n'&&(d[0]!=EOF)){}
	if(strcmp(new->node1,"0")){sizeA_sparse+=2;}
	if(strcmp(new->node2,"0")){sizeA_sparse+=2;}
	sizeD_sparse++;

}

//Sinartisi pou dimiourgei ena neo komvo gia diodo, apothikeuei ta stoixeia gia auti tin diodo apo to arxeio, kai to sindeei stin arxi tis listas diodwn
void createD(FILE *k){

	char d[100];
	char *readElement;
	DiodeT *new;

	new = (DiodeT*) malloc(sizeof(DiodeT));

	fscanf(k,"%s",d);
	new->name=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->name , d);
	
	fscanf(k,"%s",d);
	new->node1=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->node1 , d);
	NewHashEntry(d);
	if((d[0]=='0') && (d[1]=='\0')){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->node2=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->node2 , d);
	NewHashEntry(d);
	if((d[0]=='0') && (d[1]=='\0')){groundflag=1;}
	
	fgets(d,10000,k);
	readElement = strtok (d, " ,\t()\n");
	new->modelname=strdup(readElement);
	readElement = strtok (NULL, " ,\t()\n");
	new->area=0.0;
	if(readElement!=NULL){new->area=atof(readElement);}

	new->next = rootD;
	rootD = new;
	
}

//Sinartisi pou dimiourgei ena neo komvo gia transistor MOS, apothikeuei ta stoixeia gia auto to transistor MOS apo to arxeio, kai to sindeei stin arxi tis listas transistor MOS
void createM(FILE *k){

	char d[100];
	MosT *new;

	new = (MosT*) malloc(sizeof(MosT));

	fscanf(k,"%s",d);
	new->name=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->name , d);
	
	fscanf(k,"%s",d);
	new->D=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->D , d);
	NewHashEntry(d);
	if((d[0]=='0') && (d[1]=='\0')){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->G=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->G , d);
	NewHashEntry(d);
	if((d[0]=='0') && (d[1]=='\0')){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->S=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->S , d);
	NewHashEntry(d);
	if((d[0]=='0') && (d[1]=='\0')){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->B=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->B , d);
	NewHashEntry(d);
	if((d[0]=='0') && (d[1]=='\0')){groundflag=1;}
	
//	Model Name
	fscanf(k,"%s",d);
	new->modelname=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->modelname , d);

	fscanf(k,"%s",d);
	new->L=atof(d);
	
	fscanf(k,"%s",d);
	new->W=atof(d);	
	
	new->next = rootM;
	rootM = new;
	
	while((d[0]=fgetc(k))!='\n'&&(d[0]!=EOF)){}

}

//Sinartisi pou dimiourgei ena neo komvo gia transistor BJT, apothikeuei ta stoixeia gia auto to transistor BJT apo to arxeio, kai to sindeei stin arxi tis listas transistor BJT
void createB(FILE *k){

	char d[100];
	char *readElement;
	BjtT *new;

	new = (BjtT*) malloc(sizeof(BjtT));

	fscanf(k,"%s",d);
	new->name=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->name , d);
	
	fscanf(k,"%s",d);
	new->C=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->C , d);
	NewHashEntry(d);
	if((d[0]=='0') && (d[1]=='\0')){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->B=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->B , d);
	NewHashEntry(d);
	if((d[0]=='0') && (d[1]=='\0')){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->E=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->E , d);
	NewHashEntry(d);
	if((d[0]=='0') && (d[1]=='\0')){groundflag=1;}
	
//	Model Name && area

	fgets(d,10000,k);
	readElement = strtok (d, " ,\t()\n");
	new->modelname=strdup(readElement);
	readElement = strtok (NULL, " ,\t()\n");
	new->area=0.0;
	if(readElement!=NULL){new->area=atof(readElement);}
		
	new->next = rootB;
	rootB = new;

}


void NewHashEntry(char *string){

	char str[12];
	
	if(strcmp(string,"0")==0){
		ht_set(hashtable, string, "0");
		return;
	}

	sprintf(str, "%d", hash_count);
	ht_set(hashtable, string, str);
}

//Ektypwsi olwn twn stoixeiwn tou kyklwmatos pou diavastikan..
void printLists(){

	VoltT *nodeV;
	AmperT *nodeI;
	ResistanceT *nodeR;
	CapacitorT *nodeC;
	InductorT *nodeL;
	DiodeT *nodeD;
	MosT *nodeM;
	BjtT *nodeB;

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

		printf("area = %.6lf\n",nodeD->area);
	
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
		printf("area = %.6lf\n",nodeB->area);
	
		nodeB=nodeB->next;	
	};
	
}

//Ektypwsi olwn twn stoixeiwn tou hashtable twn komvwn tou kyklwmatos..
void printHash(){
	int i;
	entry_t *next = NULL;
	for(i=0;i<hashtable->size;i++){
		next = hashtable->table[i];
		while(next != NULL) {
			printf("%s = %s\n",next->key,next->value);
			next = next->next;
		}
	}
}

//Arxikopoiisi twn arxeiwn pou tha apothikeutoun ta apotelesmata twn ploted komvwn
void initPlotFiles(char *str){
  
  int i;
  char filename[100];
  FILE *fp;
  
  for(i=0;i<plot_size;i++){	//Adeiasma twn arxeiwn
	    strcpy(filename,"./PlotFiles/");
	    strcat(filename,str);
	    strcat(filename,"-Node ");
	    strcat(filename,plot_names[i]);
	    fp = fopen(filename, "w");
	    fflush(fp);
	    fclose(fp);
	  }
}

//Apothikeusi sta arxeia apotelesmatwn
void plotFiles(char *str, double *plot_table, double current_value, char *msg){
  
  int i;
  char filename[100];
  FILE *fp;
  
  for(i=0;i<plot_size;i++){	//Gemisma twn arxeiwn
 	strcpy(filename,"./PlotFiles/");
	strcat(filename,str);
	strcat(filename,"-Node ");
 	strcat(filename,plot_names[i]);
 	fp = fopen(filename, "a");
 	if (fp == NULL) {
	  printf("Can't open output file %s!\n",filename);
	  return;
 	}
 	if(current_value!=-1){
	  fprintf(fp,"%s %lf:\tNode %s value:\t%lf\n",msg, current_value, plot_names[i], plot_table[plot_nodes[i]-1]);
	}else{
	  fprintf(fp,"%s Node %s value:\t%lf\n",msg, plot_names[i], plot_table[plot_nodes[i]-1]);
	}
 	fflush(fp);
 	fclose(fp);
 }
  
  
}


