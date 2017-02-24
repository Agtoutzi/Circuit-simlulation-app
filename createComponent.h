#include <stdio.h>
#include <math.h>
#include "CircLib.h"


//Sinartisi pou dexetai string se morfi scientific double, px 1.43e5, 4.23e-5, 3.224e+9, -324.2e4, +324.124e+2 ktl...
//kai epistrefei to antistoixo double arithmo
double convertStringToDouble(char* string){

	int negative=1;
	int negativeExp=1;
	int i=0,j=0,exponent=0;
	char c;
	int d;
	double res = 0;
	
	if(string[i]=='-'){
		negative=-1;
		i++;
	}
	
	if(string[i]=='+'){
		i++;
	}
	
	while((string[i] )!= '.'){
		res = res*10 +(string[i] - '0');
		i++;
	}
	i++;
	
	j=-1;
	while(string[i] != 'e'){
		d = string[i] - '0';
		res = res + (double)d*(pow(10,j));	
		j--;
		i++;
	}
	
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

//Sinartisi pou dimiourgei ena neo komvo gia pigi tasis, apothikeuei ta stoixeia gia auti tin pigi apo to arxeio, kai to sindeei stin arxi tis listas pigwn tasis
void createV(FILE *k){

	char d[100];
	VoltT *new;
	
	printf("point0\n");
	new = (VoltT*)malloc(sizeof(VoltT));
	printf("point1\n");
	fscanf(k,"%s",d);
	printf("point2\n");
	new->name=(char*)malloc(sizeof(char)*strlen(d));
	printf("point3\n");
	strcpy(new->name , d);
	printf("point4\n");
	fscanf(k,"%s",d);
	printf("point5\n");
//	new->node1=(char*)malloc(sizeof(char)*strlen(d));
	printf("point6\n");
	strcpy(new->node1 , d);
	printf("point7\n");
	if(d[0]=='0'){groundflag=1;}
	printf("point8\n");
	fscanf(k,"%s",d);
	printf("point9\n");
//	new->node2=(char*)malloc(sizeof(char)*strlen(d));
	printf("point10\n");
	strcpy(new->node2 , d);
	printf("point11\n");
	if(d[0]=='0'){groundflag=1;}
	printf("point12\n");
	fscanf(k,"%s",d);
	new->value=convertStringToDouble(d);
	printf("point13\n");
	new->next=rootV;
	rootV=new;
	printf("point14\n");
	while((d[0]=fgetc(k))!='\n'&&(d[0]!=EOF)){}
	printf("point15\n");
}

//Sinartisi pou dimiourgei ena neo komvo gia pigi reumatos, apothikeuei ta stoixeia gia auti tin pigi apo to arxeio, kai to sindeei stin arxi tis listas pigwn reumatos
void createI(FILE *k){

	char d[100];
	AmperT *new;

	new = (AmperT*) malloc(sizeof(AmperT));

	fscanf(k,"%s",d);
	new->name=(char*)malloc(sizeof(char)*strlen(d));
	strcpy(new->name , d);
	
	fscanf(k,"%s",d);
	new->node1=(char*)malloc(sizeof(char)*strlen(d));
	strcpy(new->node1 , d);
	if(d[0]=='0'){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->node2=(char*)malloc(sizeof(char)*strlen(d));
	strcpy(new->node2 , d);
	if(d[0]=='0'){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->value=convertStringToDouble(d);
	
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
	new->name=(char*)malloc(sizeof(char)*strlen(d));
	strcpy(new->name , d);
	
	fscanf(k,"%s",d);
	new->node1=(char*)malloc(sizeof(char)*strlen(d));
	strcpy(new->node1 , d);
	if(d[0]=='0'){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->node2=(char*)malloc(sizeof(char)*strlen(d));
	strcpy(new->node2 , d);
	if(d[0]=='0'){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->value=convertStringToDouble(d);
	
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
	new->name=(char*)malloc(sizeof(char)*strlen(d));
	strcpy(new->name , d);
	
	fscanf(k,"%s",d);
	new->node1=(char*)malloc(sizeof(char)*strlen(d));
	strcpy(new->node1 , d);
	if(d[0]=='0'){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->node2=(char*)malloc(sizeof(char)*strlen(d));
	strcpy(new->node2 , d);
	if(d[0]=='0'){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->value=convertStringToDouble(d);
	
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
	new->name=(char*)malloc(sizeof(char)*strlen(d));
	strcpy(new->name , d);
	
	fscanf(k,"%s",d);
	new->node1=(char*)malloc(sizeof(char)*strlen(d));
	strcpy(new->node1 , d);
	if(d[0]=='0'){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->node2=(char*)malloc(sizeof(char)*strlen(d));
	strcpy(new->node2 , d);
	if(d[0]=='0'){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->value=convertStringToDouble(d);
	
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
	new->name=(char*)malloc(sizeof(char)*strlen(d));
	strcpy(new->name , d);
	
	fscanf(k,"%s",d);
	new->node1=(char*)malloc(sizeof(char)*strlen(d));
	strcpy(new->node1 , d);
	if(d[0]=='0'){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->node2=(char*)malloc(sizeof(char)*strlen(d));
	strcpy(new->node2 , d);
	if(d[0]=='0'){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->value=convertStringToDouble(d);
	
	new->area=1;
	d1=fgetc(k);
	while(d1!='\n'&&(d1!=EOF)){
		if(d1 != ' '){new->area=d1 - '0';}
		d1=fgetc(k);
	}
	
	//Model Name
	
	new->next = rootD;
	rootD = new;
	
}

//Sinartisi pou dimiourgei ena neo komvo gia transistor MOS, apothikeuei ta stoixeia gia auto to transistor MOS apo to arxeio, kai to sindeei stin arxi tis listas transistor MOS
void createM(FILE *k){

	char d[100];
	MosT *new;

	new = (MosT*) malloc(sizeof(MosT));

	fscanf(k,"%s",d);
	new->name=(char*)malloc(sizeof(char)*strlen(d));
	strcpy(new->name , d);
	
	fscanf(k,"%s",d);
	new->D=(char*)malloc(sizeof(char)*strlen(d));
	strcpy(new->D , d);
	if(d[0]=='0'){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->G=(char*)malloc(sizeof(char)*strlen(d));
	strcpy(new->G , d);
	if(d[0]=='0'){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->S=(char*)malloc(sizeof(char)*strlen(d));
	strcpy(new->S , d);
	if(d[0]=='0'){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->B=(char*)malloc(sizeof(char)*strlen(d));
	strcpy(new->B , d);
	if(d[0]=='0'){groundflag=1;}
	
	//Model Name
	
	fscanf(k,"%s",d);
	new->L=convertStringToDouble(d);
	
	fscanf(k,"%s",d);
	new->W=convertStringToDouble(d);	
	
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
	new->name=(char*)malloc(sizeof(char)*strlen(d));
	strcpy(new->name , d);
	
	fscanf(k,"%s",d);
	new->C=(char*)malloc(sizeof(char)*strlen(d));
	strcpy(new->C , d);
	if(d[0]=='0'){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->B=(char*)malloc(sizeof(char)*strlen(d));
	strcpy(new->B , d);
	if(d[0]=='0'){groundflag=1;}
	
	fscanf(k,"%s",d);
	new->E=(char*)malloc(sizeof(char)*strlen(d));
	strcpy(new->E , d);
	if(d[0]=='0'){groundflag=1;}
	
	//Model Name
	
	new->area=1;
	d1=fgetc(k);
	while(d1!='\n'&&(d1!=EOF)){
		if(d1 != ' '){new->area=d1 - '0';}
		d1=fgetc(k);
	}
	
	new->next = rootB;
	rootB = new;

}