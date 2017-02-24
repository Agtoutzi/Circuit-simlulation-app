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



void read_options(FILE *f){
  char c[10000];
  char printable[1000];
  char *nodename;
  const char delimiters[] = " ,\t()\n";
  
  fscanf(f,"%s",c);
  if(!(strcmp(c,"OPTIONS"))){
	  fgets(printable,1000,f);
	  nodename = strtok (printable, delimiters);
	  if (!(strcmp(nodename,"SPD"))){
	    cholesky =1;
	  }
  }
  else if(!(strcmp(c,"DC"))){
    
  }
  else if(!(strcmp(c,"TRAN"))){
    
  }
  else if(!(strcmp(c,"PLOT"))){
	  fgets(printable,1000,f);
	  nodename = strtok (printable, delimiters);
	  nodename = strtok (NULL, delimiters);
	  while(nodename!=NULL){
	      //save printable elements
		nodename = strtok (NULL, delimiters);
		
	 }
	 plot=1;
  }
  else if(!(strcmp(c,"PRINT"))){
	  fgets(printable,1000,f);
	  nodename = strtok (printable, delimiters);
	  nodename = strtok (NULL, delimiters);
	  while(nodename!=NULL){
	       //save printable elements
		nodename = strtok (NULL, delimiters);
		
	  }
	  print=1;
  }
}