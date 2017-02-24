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

	sizeA = (hash_count-1)+m2;
	
	A = (double**)calloc(sizeA, sizeof(double*));				//na mpei elegxos gia calloc
	temp = (double*)calloc(pow(sizeA,2), sizeof(double));
	
	for (i = 0; i < sizeA; i++) {
  		A[i] = temp + (i * sizeA);
	}
		
	sizeB = (hash_count-1)+m2;
	B = (double*)calloc(sizeB, sizeof(double));		//na mpei elegxos gia calloc
	
	
	//Diatrexoume ti lista twn antistasewn kai simplirwnoume katallila to 1o n-1 * n-1 kommati tou pinaka A
	
	ResistanceT *current=rootR;
	
	while(current!=NULL){
		i=atoi(ht_get(hashtable,current->node1));
		j=atoi(ht_get(hashtable,current->node2));
		
		if(i!=0){A[i-1][i-1]+=1/current->value;}
		if(j!=0){A[j-1][j-1]+=1/current->value;}
		if(i!=0&&j!=0){
			A[i-1][j-1]-=1/current->value;
			A[j-1][i-1]-=1/current->value;
		}
		current=current->next;
	}
	
	//diko mou emfanish twn phgwn tashs ston pinaka A
	
	VoltT *runner=rootV;
	int k,l;
	int b=1;
	int n= hash_count-1;
	while(runner != NULL){
	      k = atoi(ht_get(hashtable,runner->node1));    //vlepoume metaksu poiown komvwn vrisketai h phgh tashs 
	      l = atoi(ht_get(hashtable,runner->node2));
	
	      if(k!=0){A[n-1+b][k-1]+=1;}		   //grammh-sthlh
	      if(l!=0){A[n-1+b][l-1]-=1;}
	      
	      if(k!=0){A[k-1][n-1+b]+=1;}		//sthlh-grammh
	      if(l!=0){A[l-1][n-1+b]-=1;}
	      if((k!=0)||(l!=0)){B[n-1+b]=runner->value;}	//vazw ston B tis times twn tasewn
	      
	      b++;
	      runner= runner ->next;
	
	}
	
	//diko mou phges reumatos sto deksi melos tis prosthetw
	
	AmperT *run=rootI;
	int p,q;
	//int n= hash_count-1;
	while(run != NULL){
	      p = atoi(ht_get(hashtable,run->node1));    //vlepoume metaksu poiown komvwn vrisketai h phgh tashs 
	      q = atoi(ht_get(hashtable,run->node2));
	
	      if((p!=0){B[p-1]+=run->value;}
	      if(q!=0){B[q-1]-=run->value;}
	      
	     // printf("p = %d q = %d\n",p,q);
	      run = run ->next;
	
	}
	
	
	printf(" \n M2= %d \n N=%d \n",m2,hash_count);
	printf(" A\n");

	for(i=0;i<sizeA;i++){
		for(j=0;j<sizeA;j++){

			printf(" %lf ",A[i][j]);
		}
		printf("\n");
	}

	printf(" B\n");
	for(i=0;i<sizeB;i++){
		printf(" %lf ",B[i]);
	}

	printf("\n");
}