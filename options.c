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

  char printable[10000];
  char printable2[10000];
  char *readElement;
  const char delimiters[] = " ,\t()\n";
  char *sweep_source_name;
  VoltT *nodeV;
  AmperT *nodeI;
  int cnt,i,fid;
  char *gt_id;

  fgets(printable,10000,f);
  strcpy(printable2,printable);

  readElement = strtok (printable, delimiters);
  
  if(!(strcmp(readElement,"OPTIONS"))){
	  readElement = strtok (NULL, delimiters);
	  if ((readElement!=NULL) && !(strcmp(readElement,"SPD"))){
	    cholesky =1;
	  }
	  return;
  }
  else if(!(strcmp(readElement,"DC"))){
    
    readElement = strtok (NULL, delimiters);
    
    if(readElement==NULL){return;}
    
    if(readElement[0]=='V'){
 //     sweep_source_name = strtok (NULL, delimiters);
      nodeV=rootV;
      cnt=hash_count;
      while(nodeV!=NULL){
	if(!(strcmp(nodeV->name,readElement+1))){
	  sweep_source=cnt;
	  break;
	}
	cnt++;
	nodeV=nodeV->next;	
      }
      start_value = atof(strtok (NULL, delimiters));
      end_value = atof(strtok (NULL, delimiters));
      sweep_step = atof(strtok (NULL, delimiters));      
      dc_sweep=1;
      printf("Voltage source %s is in position %d\n",readElement+1,sweep_source);
      printf("start_value is %lf\n",start_value);
      printf("end_value %lf\n",end_value);
      printf("step is %lf\n",sweep_step);
      return;
    }else if(readElement[0]=='I'){
 //     sweep_source_name = strtok (NULL, delimiters);
      nodeI=rootI;
      cnt=1;
      while(nodeI!=NULL){
	if(!(strcmp(nodeI->name,(readElement+1)))){
	  sweep_source=cnt;
	  break;
	}
	cnt++;
	nodeI=nodeI->next;	
      }
      start_value = atof(strtok (NULL, delimiters));
      end_value = atof(strtok (NULL, delimiters));
      sweep_step = atof(strtok (NULL, delimiters));
      printf("Current source %s is in position %d\n",readElement+1,sweep_source);
      printf("start_value is %lf\n",start_value);
      printf("end_value %lf\n",end_value);
      printf("step is %lf\n",sweep_step);
      dc_sweep=1;
      return;
    }
    
    
  }
  else if(!(strcmp(readElement,"TRAN"))){
    return;
  }
  else if(!(strcmp(readElement,"PLOT"))){

	  readElement = strtok (NULL, delimiters);
	  readElement = strtok (NULL, delimiters);
	  plot_size=0;
	  while(readElement!=NULL){
	      //save printable elements
		readElement = strtok (NULL, delimiters);
		plot_size++;
	 }
	 plot_nodes= (int *)calloc(plot_size,sizeof(int)) ;
	 
	 readElement = strtok (printable2, delimiters);
	 readElement = strtok (NULL, delimiters);
	 readElement = strtok (NULL, delimiters);
	 cnt=0;
	 while(readElement!=NULL){
	      //save printable elements
	      gt_id=ht_get(hashtable, readElement);
	      fid=atoi (gt_id);
	      plot_nodes[cnt]=fid;
	      readElement = strtok (NULL, delimiters);
	      cnt++;
	 }
	 plot=1;
	 return;
  }/*
  else if(!(strcmp(readElement,"PRINT"))){

	  readElement = strtok (NULL, delimiters);
	  readElement = strtok (NULL, delimiters);
	  cnt=0;
	  while(readElement!=NULL){
	      //save printable elements
		readElement = strtok (NULL, delimiters);
		cnt++;
	 }
	 plot_nodes= (int *)calloc(cnt,sizeof(int)) ;
	 
	 
	 strcpy(printable2,printable);
	 readElement = strtok (printable2, delimiters);
	 readElement = strtok (NULL, delimiters);
	 readElement = strtok (NULL, delimiters);
	 cnt=0;
	 while(readElement!=NULL){
	      //save printable elements
	      gt_id=ht_get(hashtable, readElement);
	      fid=atoi (gt_id);
	      plot_nodes[i]=fid;
	      readElement = strtok (NULL, delimiters);
	      cnt++;
	      printf("-----------------------------------------%d\n",plot_nodes[i]);
	 }
	 print=1;
	 return;
  }*/
}
