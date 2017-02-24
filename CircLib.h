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
  double area;
  char *modelname;
  struct Diode *next;
  
}DiodeT;

//Τρανζίστορ MOS
typedef struct Mos{
  
  char *name;
  char *D;
  char *G;
  char *S;
  char *B;
  char *modelname;
  double L;
  double W; 
  
  struct Mos *next;
  
}MosT;

//Τρανζίστορ BJT
typedef struct Bjt{
  
  char *name;
  char *C;
  char *B;
  char *E;
  char *modelname;
  double area;
  struct Bjt *next;
  
}BjtT;


//Dilwsi katholikwn metavlitwn

//Root twn listwn opou apothikeuetai kathe stoixeio tou kiklwmatos
VoltT *rootV;
AmperT *rootI;
ResistanceT *rootR;
CapacitorT *rootC;
InductorT *rootL;
DiodeT *rootD;
MosT *rootM;
BjtT *rootB;

int groundflag;	//arxikopoieitai me 0 kai ginetai isi me 1 otan diavasoume komvo '0' (geiwsi).
int SPD;	//einai isi me 1 an exoume diavasei SPD sta OPTIONS. Alliws =0
int ITER;	//einai isi me 1 an exoume diavasei ITER sta OPTIONS. Alliws =0
double itol_value;	//timi tis itol value an tin diavasoume
int plot;	//einai isi me 1 otan tha kanoume PLOT kapoia dinamika komvwn
int m2; 	//plh8os autepagwgwn kai phgwn tashs
int hash_count;	//plithos komvwn -> voithaei stin antistoixisi twn komvwn me akeraies times
int dc_sweep;	// einai isi me 1 an tha kanoume sweep. Alliws =0
int sweep_source;	//An kanoume sweep me pigi tasis, mas deixnei ti thesis tis pigis ston pinaka B. An kanoume sweep me pigi reumatos einai isi me -1
int sweep_posNode;	//An kanoume sweep me pigi reumatos mas deixnei ton positive komvo pou sindeetai auti i pigi(tin akeraia timi tou komvou apo to hashtable)
int sweep_negNode;	//An kanoume sweep me pigi reumatos mas deixnei ton negative komvo pou sindeetai auti i pigi(tin akeraia timi tou komvou apo to hashtable)
double start_value;	//krata to start value gia to sweep(an ginetai)
double end_value;	//krata to end value gia to sweep(an ginetai)
double sweep_step;	//krata to sweep step gia to sweep(an ginetai)
int *plot_nodes;	//einai o pinakas pou apothikeuontai ta ids ton komvwn pou ginontai PLOT
int plot_size;		//megethos tou pinaka pou apothikeuontai ta ids ton komvwn pou ginontai PLOT
double sweep_value_I;	//krataei to value tis pigis reumatos pou tha ginei sweep to opoio diavazetai apo to netlist

//Declaration twn sinartisewn tou arxeiou CircLib.c
void initCirc();
void createV(FILE *k);
void createI(FILE *k);
void createR(FILE *k);
void createC(FILE *k);
void createL(FILE *k);
void createD(FILE *k);
void createM(FILE *k);
void createB(FILE *k);
void NewHashEntry(char *string);
void printLists();
void printHash();

#endif
