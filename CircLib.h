//Dilwsi twn structs 

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
//  double value;
  int area;
  // char *modelname; 				pedio model_name
  struct Diode *next;
  
}DiodeT;

//Τρανζίστορ MOS
typedef struct Mos{
  
  char *name;
  char *D;
  char *G;
  char *S;
  char *B;
  //char *modelname;					model_name
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


//Dilwsi twn katholikwn metavlitwn tou programmatos (roots kai elegxou gia geiwsi)
VoltT *rootV;
AmperT *rootI;
ResistanceT *rootR;
CapacitorT *rootC;
InductorT *rootL;
DiodeT *rootD;
MosT *rootM;
BjtT *rootB;
int groundflag;



#endif