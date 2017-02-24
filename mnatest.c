#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "CircLib.h"
#include "hash.h"
#include "mna.h"

int main(int argc, char* argv[]){


//Desmeush pinakwn eksiswsewn

//Desmeush kai arxikopoihsh aristerou merous eksiswshs A
	int hash_count=9;
	int m2=3;
	int i,j;

	sizeA = (hash_count-1)+m2;
	
	A = (double**)calloc(sizeA, sizeof(double*));				//na mpei elegxos gia calloc
	temp = (double*)calloc((sizeA*sizeA), sizeof(double));
	
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
		if(j!=0){A[i-1][i-1]+=1/current->value;}
		if(i!=0&&j!=0){
			A[i-1][j-1]-=1/current->value;
			A[j-1][i-1]-=1/current->value;
		}
		current=current->next;
	}
	
	printf(" \n M2= %d \n N=%d \n",m2,hash_count);
	printf(" A\n");

	for(i=0;i<sizeA;i++){
		for(j=0;j<sizeA;j++){

			printf(" %.2lf ",A[i][j]);
		}
		printf("\n");
	}

	printf(" B\n");
	for(i=0;i<sizeB;i++){
		printf(" %.2lf ",B[i]);
	}


}