#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "CircLib.h"
#include "hash.h"
#include "mna.h"

void CreateMna(){


//Desmeush pinakwn eksiswsewn

//Desmeush kai arxikopoihsh aristerou merous eksiswshs A


	int i,j;
	int b=1;
	int n= hash_count-1;

	sizeA = (hash_count-1)+m2;
	
	A = (double**)calloc(sizeA, sizeof(double*));				//na mpei elegxos gia calloc
	temp = (double*)calloc(pow(sizeA,2), sizeof(double));
	
	for (i = 0; i < sizeA; i++) {
  		A[i] = temp + (i * sizeA);
	}
		
	sizeB = (hash_count-1)+m2;
	B = (double*)calloc(sizeB, sizeof(double));		//na mpei elegxos gia calloc
	
	
	//Diatrexoume ti lista twn antistasewn kai simplirwnoume katallila to 1o n-1 * n-1 kommati tou pinaka A
	
	ResistanceT *currentR=rootR;
	
	while(currentR!=NULL){
		i=atoi(ht_get(hashtable,currentR->node1));
		j=atoi(ht_get(hashtable,currentR->node2));
		
		if(i!=0){A[i-1][i-1]+=1/currentR->value;}
		if(j!=0){A[j-1][j-1]+=1/currentR->value;}
		if(i!=0&&j!=0){
			A[i-1][j-1]-=1/currentR->value;
			A[j-1][i-1]-=1/currentR->value;
		}
		currentR=currentR->next;
	}
	
	//Diatrexoume ti lista twn pigwn tasis kai simplirwnoume katallila to 2o n-1 * m2 kommati tou pinaka A
	// kai to 2o m2*1 kommati tou pinaka B
	
	VoltT *currentV=rootV;

	while(currentV != NULL){
	      i = atoi(ht_get(hashtable,currentV->node1));    //vlepoume metaksu poiown komvwn vrisketai h phgh tashs 
	      j = atoi(ht_get(hashtable,currentV->node2));
	
	      if(i!=0){A[n-1+b][i-1]=1;}		   //grammh-sthlh
	      if(j!=0){A[n-1+b][j-1]=-1;}
	      
	      if(i!=0){A[i-1][n-1+b]=1;}		//sthlh-grammh
	      if(j!=0){A[j-1][n-1+b]=-1;}
	      if((i!=0)||(j!=0)){B[n-1+b]=currentV->value;}	//vazw ston B tis times twn tasewn
	      
	      b++;
	      currentV= currentV ->next;
	
	}

	//Diatrexoume ti lista twn piniwn kai simplirwnoume katallila to 2o n-1 * m2 kommati tou pinaka A

	InductorT *currentL=rootL;
	while(currentL != NULL){
	      i = atoi(ht_get(hashtable,currentL->node1));    //vlepoume metaksu poiown komvwn vrisketai to pinio 
	      j = atoi(ht_get(hashtable,currentL->node2));
	
	      if(i!=0){A[n-1+b][i-1]=1;}		   //grammh-sthlh
	      if(j!=0){A[n-1+b][j-1]=-1;}
	      
	      if(i!=0){A[i-1][n-1+b]=1;}		//sthlh-grammh
	      if(j!=0){A[j-1][n-1+b]=-1;}
 
	      b++;
	      currentL= currentL ->next;
	}
	
	//Diatrexoume ti lista twn pigwn reumatwn kai simplirwnoume katallila to 1o n-1 * 1 kommati tou pinaka B
	
	AmperT *currentI=rootI;

	while(currentI != NULL){
	      i = atoi(ht_get(hashtable,currentI->node1));    //vlepoume metaksu poiown komvwn vrisketai h phgh tashs 
	      j = atoi(ht_get(hashtable,currentI->node2));
	
	      if(i!=0){B[i-1]-=currentI->value;}
	      if(j!=0){B[j-1]+=currentI->value;}
	      
	      currentI = currentI ->next;
	
	}
	
	
	printf(" \n M2= %d \n N=%d \n",m2,hash_count);
	printf(" A\n");

	for(i=0;i<sizeA;i++){
		for(j=0;j<sizeA;j++){

			printf(" %.3lf ",A[i][j]);
		}
		printf("\n");
	}

	printf(" B\n");
	for(i=0;i<sizeB;i++){
		printf(" %.3lf ",B[i]);
	}

	printf("\n");
}
