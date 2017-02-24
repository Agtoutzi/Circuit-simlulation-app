#include <stdio.h>
#include <stdlib.h>
#include "mna.h"
#include "CircLib.h"
#include "hash.h"



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


}