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

//Sinartisi pou diavazei ta options, diladi diavazei o,ti yparxei meta apo '.'
//sto netlist kai kathorizei ti tha ginei.
//
//Diavazei: OPTIONS, DC, TRAN, PLOT
//
//Diavazei prwta olokliri ti grammi apo to netlist kai meta vlepei se poia apo
//tis panw periptwseis eimaste opote prattei ta analoga...

void read_options(FILE *f){

  char printable[10000];
  char printable2[10000];
  char *readElement;
  const char delimiters[] = "\n ,\t()=";
  VoltT *nodeV;
  AmperT *nodeI;
  int cnt,fid;
  char *gt_id;

  fgets(printable,10000,f);	//diavazei olokliri ti grammi
  strcpy(printable2,printable);	//tin antigrafei se allo ena string gia tis anagkes tis periptwsis PLOT
  readElement = strtok (printable, delimiters);	//diavazei tin prwti leksi tis grammis meta to '.'
  
  if(!(strcmp(readElement,"OPTIONS"))){	// periptwsi pou diavase OPTIONS
	    if (strstr(printable2,"SPD")!=NULL){
		SPD=1;
	    }
	    if (strstr(printable2,"SPARSE")!=NULL){
		SPARSE=1;
	    }
	    if (strstr(printable2,"ITER")!=NULL){
		ITER=1;
	    }
	    if (strstr(printable2,"ITOL")!=NULL){
		readElement = strtok (NULL, delimiters);
		while((strcmp(readElement,"ITOL"))){readElement = strtok (NULL, delimiters);}
		itol_value=atof(strtok (NULL, delimiters));
	    }	//an meta to itol den yparxei kati, to programma tha skasei... (core dumped)(emeis ypothetoume oti tha yparxei sigoura..)

	  return;
  }
  else if(!(strcmp(readElement,"DC"))){	//periptwsi pou diavase DC
    
    readElement = strtok (NULL, delimiters);
    
    if(readElement==NULL){return;} //an den yparxei kati meta to DC tote termatizei

    if(readElement[0]=='V'){	//an meta to DC yparxei V, tote kanoume DC sweep allazontas kapoia pigi tasis

      nodeV=rootV;
      cnt=hash_count;
  
      while(nodeV!=NULL){	//psaxnoume na vroume pou vrisketai i pigi tasis pou tha allazoume sto sweep, mesa sti lista twn pigwn tasis
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
      printf("\n");
      printf("---Sweeping details---\n");
      printf("Voltage source:\t%s\nPosition of source in matrix B: %d\n",readElement+1,sweep_source);
      printf("Start value:\t%lf\n",start_value);
      printf("End value:\t%lf\n",end_value);
      printf("Sweep step:\t%lf\n",sweep_step);
      printf("----------------------\n\n");
      return;
    }else if(readElement[0]=='I'){//an meta to DC yparxei I, tote kanoume DC sweep allazontas kapoia pigi reumatos

      nodeI=rootI;

      while(nodeI!=NULL){
	if(!(strcmp(nodeI->name,(readElement+1)))){//psaxnoume na tin pigi reumatos pou tha allazoume sto sweep, mesa sti lista twn pigwn reumatos
	  sweep_source=-1;	// simatodotei oti to sweep einai me pigi reumatos
	  sweep_posNode=atoi(ht_get(hashtable, nodeI->node1));	//pairnoume ton kwdiko tou positive node tis pigis
	  sweep_negNode=atoi(ht_get(hashtable, nodeI->node2));	//pairnoume ton kwdiko tou negative node tis pigis
	  sweep_value_I=nodeI->value;
	  break;
	}
	nodeI=nodeI->next;	
      }
      start_value = atof(strtok (NULL, delimiters));
      end_value = atof(strtok (NULL, delimiters));
      sweep_step = atof(strtok (NULL, delimiters));
      dc_sweep=1;
      printf("\n");
      printf("---Sweeping details---\n");
      printf("Current source:\t%s\nPositive node of source: %d\nNegative node of source: %d\n", readElement+1, sweep_posNode, sweep_negNode);
      printf("Start value:\t%.3e\n",start_value);
      printf("End value:\t%.3e\n",end_value);
      printf("Sweep step:\t%.3e\n",sweep_step);
      printf("----------------------\n\n");
      return;
    }
    
    
  }
  else if(!(strcmp(readElement,"TRAN"))){
    return;
  }
  else if(!(strcmp(readElement,"PLOT"))){

	  readElement = strtok (NULL, delimiters);
	  if((readElement==NULL) || (strcmp(readElement,"V"))!=0){return;}
	  readElement = strtok (NULL, delimiters);
	  plot_size=1;
	  while(readElement!=NULL){
		//save printable elements
		readElement = strtok (NULL, delimiters);
		if((readElement==NULL) || (strcmp(readElement,"V"))!=0){break;}
		readElement = strtok (NULL, delimiters);
		plot_size++;
	 }

	 printf("PLOT_SIZE=%d\n",plot_size);
	 plot_nodes= (int *)calloc(plot_size,sizeof(int));			
	 plot_names= (char **)calloc(plot_size,sizeof(char *));
	 //AN PLOT_SIZE=0 -->PROVLIMA
	 
	 readElement = strtok (printable2, delimiters);
	 readElement = strtok (NULL, delimiters);
	 if((readElement==NULL) || (strcmp(readElement,"V"))!=0){return;}
	 readElement = strtok (NULL, delimiters);
	 cnt=0;
	 
	 while(readElement!=NULL){
	      //save printable elements
	      gt_id=ht_get(hashtable, readElement);
	      if(gt_id==NULL){printf("PLOT node does not exist\nProgram terminated\n");exit(1);}
	      fid=atoi (gt_id);
	      plot_nodes[cnt]=fid;
	      plot_names[cnt]=strdup(readElement);
	      readElement = strtok (NULL, delimiters);
	      if((readElement==NULL) || (strcmp(readElement,"V"))!=0){break;}
	      readElement = strtok (NULL, delimiters);
	      cnt++;
	 }
	 plot=1;
	 return;
  }
}
