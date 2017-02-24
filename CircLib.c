#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "CircLib.h"


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
	rootN=NULL;
	groundflag=0;
	NodeCounter=1;
}

/*
//Sinartisi pou dexetai string se morfi scientific double, px 1.43e5, 4.23e-5, 3.224e+9, -324.2e4, +324.124e+2 ktl...
//kai epistrefei to antistoixo double arithmo
double convertStringToDouble(char* string1){

	int negative=1;
	int negativeExp=1;
	int i=0; int j=0; int exponent=0;
	char c;
	int d;
	double res = 0;
	char *string;
	strcpy(string,string1);
	
	if(string[i]=='-'){
		negative=-1;
		i++;
	}

	if(string[i]=='+'){
		i++;
	}
	
	do{
		res = res*10 +(string[i] - '0');
		i++;
	}while((string[i] != '.') && (string[i] != '\0') && (string[i] != 'e'));

	if(string[i]=='\0'){res=res*negative;return(res);}
	
	if(string[i]=='.'){
		i++;
		j=-1;
		while((string[i] != 'e') && (string[i] != '\0')){
			d = string[i] - '0';
			res = res + (double)d*(pow(10,j));
			j--;
			i++;
		}
	}
	
	if(string[i]=='\0'){res=res*negative;return(res);}
	
	res=res*negative;
	
	i++;
	
	if(string[i]=='-'){negativeExp=-1;i++;}
	if(string[i]=='+'){i++;}
	
	while((string[i] )!= '\0'){
		exponent = exponent*10 +(string[i] - '0');
		i++;
	}
	
	exponent=exponent*negativeExp;
	res=res*(pow(10,exponent));
	
	return(res);
}
*/
//Sinartisi pou dimiourgei ena neo komvo gia pigi tasis, apothikeuei ta stoixeia gia auti tin pigi apo to arxeio, kai to sindeei stin arxi tis listas pigwn tasis
void createV(FILE *k){

	char d[100];
	VoltT *new;
	
	new = (VoltT*) malloc(sizeof(VoltT));

	fscanf(k,"%s",d);
	new->name=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->name , d);
	
	fscanf(k,"%s",d);
	new->node1=(char*)malloc(sizeof(char)*(strlen(d)+1));
	CreateNode(d);
	strcpy(new->node1 , d);
	if((d[0]=='0') && (d[1]=='\0')){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->node2=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->node2 , d);
	CreateNode(d);
	if((d[0]=='0') && (d[1]=='\0')){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->value=atof(d);
	
	new->next = rootV;
	rootV = new;
	
	while((d[0]=fgetc(k))!='\n'&&(d[0]!=EOF)){}
}

//Sinartisi pou dimiourgei ena neo komvo gia pigi reumatos, apothikeuei ta stoixeia gia auti tin pigi apo to arxeio, kai to sindeei stin arxi tis listas pigwn reumatos
void createI(FILE *k){

	char d[100];
	AmperT *new;

	new = (AmperT*) malloc(sizeof(AmperT));

	fscanf(k,"%s",d);
	new->name=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->name , d);
	
	fscanf(k,"%s",d);
	new->node1=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->node1 , d);
	CreateNode(d);
	if((d[0]=='0') && (d[1]=='\0')){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->node2=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->node2 , d);
	CreateNode(d);
	if((d[0]=='0') && (d[1]=='\0')){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->value=atof(d);
	
	new->next = rootI;
	rootI = new;
	
	while((d[0]=fgetc(k))!='\n'&&(d[0]!=EOF)){}

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
	CreateNode(d);
	if((d[0]=='0') && (d[1]=='\0')){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->node2=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->node2 , d);
	CreateNode(d);
	if((d[0]=='0') && (d[1]=='\0')){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->value=atof(d);
//	printf("double = %e\n",convertStringToDouble(d));
	new->next=rootR;
	rootR=new;
	
	while((d[0]=fgetc(k))!='\n'&&(d[0]!=EOF)){}

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
	CreateNode(d);
	if((d[0]=='0') && (d[1]=='\0')){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->node2=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->node2 , d);
	CreateNode(d);
	if((d[0]=='0') && (d[1]=='\0')){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->value=atof(d);
	
	new->next = rootC;
	rootC = new;
	
	while((d[0]=fgetc(k))!='\n'&&(d[0]!=EOF)){}

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
	CreateNode(d);
	if((d[0]=='0') && (d[1]=='\0')){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->node2=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->node2 , d);
	CreateNode(d);
	if((d[0]=='0') && (d[1]=='\0')){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->value=atof(d);
	
	new->next = rootL;
	rootL = new;
	
	while((d[0]=fgetc(k))!='\n'&&(d[0]!=EOF)){}

}

//Sinartisi pou dimiourgei ena neo komvo gia diodo, apothikeuei ta stoixeia gia auti tin diodo apo to arxeio, kai to sindeei stin arxi tis listas diodwn
void createD(FILE *k){

	char d[100];
	char d1;
	DiodeT *new;

	new = (DiodeT*) malloc(sizeof(DiodeT));

	fscanf(k,"%s",d);
	new->name=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->name , d);
	
	fscanf(k,"%s",d);
	new->node1=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->node1 , d);
	CreateNode(d);
	if((d[0]=='0') && (d[1]=='\0')){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->node2=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->node2 , d);
	CreateNode(d);
	if((d[0]=='0') && (d[1]=='\0')){groundflag=1;}
	
	// fscanf(k,"%s",d);
	// new->value=convertStringToDouble(d);


//	Model Name
//	fscanf(k,"%s",d);
//	new->node2=(char*)malloc(sizeof(char)*(strlen(d)+1));
//	strcpy(new->modelname , d);
	
	
	new->area=1;
	d1=fgetc(k);
	while(d1!='\n'&&(d1!=EOF)){
		if(d1 != ' '){new->area=d1 - '0';}
		d1=fgetc(k);
	}
		
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
	CreateNode(d);
	if((d[0]=='0') && (d[1]=='\0')){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->G=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->G , d);
	CreateNode(d);
	if((d[0]=='0') && (d[1]=='\0')){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->S=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->S , d);
	CreateNode(d);
	if((d[0]=='0') && (d[1]=='\0')){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->B=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->B , d);
	CreateNode(d);
	if((d[0]=='0') && (d[1]=='\0')){groundflag=1;}
	
//	Model Name
//	fscanf(k,"%s",d);
//	new->node2=(char*)malloc(sizeof(char)*(strlen(d)+1));
//	strcpy(new->modelname , d);

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
	char d1;
	BjtT *new;

	new = (BjtT*) malloc(sizeof(BjtT));

	fscanf(k,"%s",d);
	new->name=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->name , d);
	
	fscanf(k,"%s",d);
	new->C=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->C , d);
	CreateNode(d);
	if((d[0]=='0') && (d[1]=='\0')){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->B=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->B , d);
	CreateNode(d);
	if((d[0]=='0') && (d[1]=='\0')){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->E=(char*)malloc(sizeof(char)*(strlen(d)+1));
	strcpy(new->E , d);
	CreateNode(d);
	if((d[0]=='0') && (d[1]=='\0')){groundflag=1;}
	
//	Model Name
//	fscanf(k,"%s",d);
//	new->node2=(char*)malloc(sizeof(char)*(strlen(d)+1));
//	strcpy(new->modelname , d);
	
	new->area=1;
	d1=fgetc(k);
	while(d1!='\n'&&(d1!=EOF)){
		if(d1 != ' '){new->area=d1 - '0';}
		d1=fgetc(k);
	}
	
	new->next = rootB;
	rootB = new;

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


void printNodeList(){

	NodeT *temp=rootN;

	while(temp!=NULL){
		printf("\nname=%s code=%d",temp->name,temp->code);
		temp=temp->next;
	}



}

void CreateNode(char *string){



	NodeT *temp=rootN;

	while(temp!=NULL){
		if(strcmp(string,temp->name)==0||(string[0]=='0' && string[1]=='\0')){return;}
		temp=temp->next;

	}

	temp = (NodeT*) malloc(sizeof(NodeT));
	temp->name=(char*)malloc(sizeof(char)*(strlen(string)+1));
	strcpy(temp->name ,string);

	temp->code=NodeCounter;
	NodeCounter++;
	
	temp->next=rootN;
	rootN=temp;
	
}