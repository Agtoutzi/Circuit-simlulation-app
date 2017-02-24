//dhmiourgw edw ola ta structs 

#ifndef STRUCTS_H
#define STRUCTS_H


//Πηγή Τάσης
typedef struct Volt{
  
  char *name;
  char *node1;
  char *node2;
  double value;
  struct Volt *next;
  
}VoltT;

//Πηγή Ρεύματος
typedef struct Amper{
  
  char *name;
  char *node1;
  char *node2;
  double value;
  struct Amper *next;
  
}AmperT;

//Αντίσταση
typedef struct Resistance{
  
  char *name;
  char *node1;
  char *node2;
  double value;
  struct Resistance *next;
  
}ResistanceT;

//Πυκνωτής
typedef struct Capacitor{
  
  char *name;
  char *node1;
  char *node2;
  double value;
  struct Capacitor *next;
  
}CapacitorT;

//Πηνίο
typedef struct Inductor{
  
  char *name;
  char *node1;
  char *node2;
  double value;
  struct Inductor *next;
  
}InductorT;

//Δίοδος
typedef struct Diode{
  
  char *name;
  char *node1;
  char *node2;
  double value;
  int area;
  //pedio model_name
  struct Diode *next;
  
}DiodeT;

//Τρανζίστορ MOS
typedef struct Mos{
  
  char *name;
  char *D;
  char *G;
  char *S;
  char *B;
  //model_name
  double L;//to opoio einai iso me value
  double W;//to oopoio einai iso me value 
  
  struct Mos *next;
  
}MosT;

//Τρανζίστορ BJT
typedef struct Bjt{
  
  char *name;
  char *C;
  char *B;
  char *E;
  //model_name
  int area;
  struct Bjt *next;
  
}BjtT;


VoltT *rootV;
AmperT *rootI;
ResistanceT *rootR;
CapacitorT *rootC;
InductorT *rootL;
DiodeT *rootD;
MosT *rootM;
BjtT *rootB;
int groundflag;

void initCirc(){

	VoltT *rootV=NULL;
	AmperT *rootI=NULL;
	ResistanceT *rootR=NULL;
	CapacitorT *rootC=NULL;
	InductorT *rootL=NULL;
	DiodeT *rootD=NULL;
	MosT *rootM=NULL;
	BjtT *rootB=NULL;
	groundflag=0;

}

#endif