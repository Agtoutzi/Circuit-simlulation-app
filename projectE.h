//dhmiourgw edw ola ta structs 

#ifndef STRUCTS_H
#define STRUCTS_H
//tash
typedef struct Volt{
  
  char *name;
  char *node1;
  char *node2;
  char *value;//auto einai string?????
  struct Volt *next;
  
}VoltT;
//reuma
typedef struct Amper{
  
  char *name;
  char *node1;
  char *node2;
  char *value;//auto einai string?????
  struct Amper *next;
  
}AmperT;
//antistash
typedef struct Resistance{
  
  char *name;
  char *node1;
  char *node2;
  char *value;//auto einai string?????
  struct Resistance *next;
  
}ResistanceT;

//xwrhtikithta
typedef struct Capacity{
  
  char *name;
  char *node1;
  char *node2;
  char *value;//auto einai string?????
  struct Capacity *next;
  
}CapacityT;

//autepagwgh
typedef struct Industance{
  
  char *name;
  char *node1;
  char *node2;
  char *value;//auto einai string?????
  struct Industance *next;
  
}IndustanceT;

//diodos
typedef struct Passage{
  
  char *name;
  char *node1;
  char *node2;
  char *value;//auto einai string?????
  int area;
  //pedio model_name
  struct Passage *next;
  
}PassageT;
//tranzistor mos
typedef struct Mos{
  
  char *name;;
  char D;
  char G;
  char S;
  char B;
  //model_name
  char *L;//to opoio einai iso me value
  char *W;//to oopoio einai iso me value 
  
  struct Mos *next;
  
}MosT;

typedef struct Bjt{
  
  char *name;;
  char C;
  char B;
  char E;
  //model_name
  int area;
  struct Bjt *next;
  
}BjtT;

#endif