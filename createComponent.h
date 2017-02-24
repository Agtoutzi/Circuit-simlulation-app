#include <stdio.h>
#include <math.h>
#include "CircLib.h"



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


void createV(FILE *k){

	char d[100];
	VoltT *new;

	new = (VoltT*) malloc(sizeof(VoltT));

	fscanf(k,"%s",d);
	new->name=d;
	fscanf(k,"%s",d);
	new->node1=d;
	if(d[0]=='0'){groundflag=1;}
	fscanf(k,"%s",d);
	new->node2=d;
	if(d[0]=='0'){groundflag=1;}
	fscanf(k,"%s",d);
	new->value=convertStringToDouble(d);
	new->next = rootV;
	rootV = new;
	while(fgetc(k)!='\n'){}

}


void createI(FILE *k){

	char d[100];
	AmperT *new;

	new = (AmperT*) malloc(sizeof(AmperT));

	fscanf(k,"%s",d);
	new->name=d;
	fscanf(k,"%s",d);
	new->node1=d;
	if(d[0]=='0'){groundflag=1;}
	fscanf(k,"%s",d);
	new->node2=d;
	if(d[0]=='0'){groundflag=1;}
	fscanf(k,"%s",d);
	new->value=convertStringToDouble(d);
	new->next = rootI;
	rootI = new;
	while(fgetc(k)!='\n'){}

}


void createR(FILE *k,ResistanceT *new1){

	char d[100];
	char d2[100];
	char d3[100];
	char d4[100];
	
//	ResistanceT *new1;
	
//	new1 = (ResistanceT*)malloc(sizeof(ResistanceT));
	
	
	fscanf(k,"%s ",d);
//	printf("d = %s\n",d);
	new1->name=d;
//	printf("name = %s\n",new1->name);
	fscanf(k,"%s ",d2);
//	printf("d = %s\n",d2);
	new1->node1=d2;
	if(d2[0]=='0'){groundflag=1;}
//	printf("name = %s\n",new1->name);
//	printf("node1 = %s\n",new1->node1);
	fscanf(k,"%s ",d3);
//	printf("d = %s\n",d3);
	new1->node2=d3;
	if(d3[0]=='0'){groundflag=1;}
//	printf("name = %s\n",new1->name);
//	printf("node1 = %s\n",new1->node1);
//	printf("node2 = %s\n",new1->node2);
	fscanf(k,"%s ",d4);
//	printf("d = %s\n",d4);
	new1->value=convertStringToDouble(d4);
//	printf("name = %s\n",new1->name);
//	printf("node1 = %s\n",new1->node1);
//	printf("node2 = %s\n",new1->node2);
//	printf("value = %e\n",new1->value);
//	new1->next = rootR;
//	rootR = new1;
	
//	printf("name = %s\n",rootR->name);
	
//	printf("node1 = %s\n",rootR->node1);
	
//	printf("node2 = %s\n",rootR->node2);
	
//	printf("value = %e\n",rootR->value);
	
//	while(fgetc(k)!='\n'){}

}

void createC(FILE *k){

	char d[100];
	CapacitorT *new;

	new = (CapacitorT*) malloc(sizeof(CapacitorT));

	fscanf(k,"%s",d);
	new->name=d;
	fscanf(k,"%s",d);
	new->node1=d;
	if(d[0]=='0'){groundflag=1;}
	fscanf(k,"%s",d);
	new->node2=d;
	if(d[0]=='0'){groundflag=1;}
	fscanf(k,"%s",d);
	new->value=convertStringToDouble(d);
	new->next = rootC;
	rootC = new;
	while(fgetc(k)!='\n'){}

}

void createL(FILE *k){

	char d[100];
	InductorT *new;

	new = (InductorT*) malloc(sizeof(InductorT));

	fscanf(k,"%s",d);
	new->name=d;
	fscanf(k,"%s",d);
	new->node1=d;
	if(d[0]=='0'){groundflag=1;}
	fscanf(k,"%s",d);
	new->node2=d;
	if(d[0]=='0'){groundflag=1;}
	fscanf(k,"%s",d);
	new->value=convertStringToDouble(d);
	new->next = rootL;
	rootL = new;
	while(fgetc(k)!='\n'){}

}

void createD(FILE *k){

	char d[100];
	char d1;
	DiodeT *new;

	new = (DiodeT*) malloc(sizeof(DiodeT));

	fscanf(k,"%s",d);
	new->name=d;
	fscanf(k,"%s",d);
	new->node1=d;
	if(d[0]=='0'){groundflag=1;}
	fscanf(k,"%s",d);
	new->node2=d;
	if(d[0]=='0'){groundflag=1;}
	fscanf(k,"%s",d);
	new->value=convertStringToDouble(d);
	
	new->area=1;
	while(d1=fgetc(k)!='\n'){
		if(d1!=' '){new->area= d1-'0';}
	}
	
	//Model Name
	
	new->next = rootD;
	rootD = new;
	
}

void createM(FILE *k){

	char d[100];
	MosT *new;

	new = (MosT*) malloc(sizeof(MosT));

	fscanf(k,"%s",d);
	new->name=d;
	fscanf(k,"%s",d);
	new->D=d;
	if(d[0]=='0'){groundflag=1;}
	fscanf(k,"%s",d);
	new->G=d;
	if(d[0]=='0'){groundflag=1;}
	fscanf(k,"%s",d);
	new->S=d;
	if(d[0]=='0'){groundflag=1;}
	fscanf(k,"%s",d);
	new->B=d;
	if(d[0]=='0'){groundflag=1;}
	
	//Model Name
	
	fscanf(k,"%s",d);
	new->L=convertStringToDouble(d);
	fscanf(k,"%s",d);
	new->W=convertStringToDouble(d);	
	new->next = rootM;
	rootM = new;
	while(fgetc(k)!='\n'){}

}

void createB(FILE *k){

	char d[100];
	char d1;
	BjtT *new;

	new = (BjtT*) malloc(sizeof(BjtT));

	fscanf(k,"%s",d);
	new->name=d;
	fscanf(k,"%s",d);
	new->C=d;
	if(d[0]=='0'){groundflag=1;}
	fscanf(k,"%s",d);
	new->B=d;
	if(d[0]=='0'){groundflag=1;}
	fscanf(k,"%s",d);
	new->E=d;
	if(d[0]=='0'){groundflag=1;}
	
	//Model Name
	
	new->area=1;
	
	while(d1=fgetc(k)!='\n'){
		if(d1!=' '){new->area= d1-'0';}
	}
	
	new->next = rootB;
	rootB = new;

}