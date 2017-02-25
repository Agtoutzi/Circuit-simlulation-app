#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "CircLib.h"
#include "hash.h"
#include "mna.h"
#include "options.h"
#include "mna-sparse.h"
#include "csparse.h"



void CreateMnaSparse(){
  
	int i,j,k;
	int b=1;
	int n= hash_count-1;
	double temp;

	//Desmeush pinakwn eksiswsewn
	//Desmeush kai arxikopoihsh twn A,B,x

	A_sparse = cs_spalloc(sizeA,sizeA,sizeA_sparse,1,1);
	A_sparse->nz=sizeA_sparse;
//	cs_print(A, "A-Sparse.txt", 0);
/*
	sizeB = (hash_count-1)+m2;
	B = gsl_vector_calloc(sizeB);

	x = gsl_vector_calloc(sizeB);
*/  
	//Diatrexoume ti lista twn antistasewn kai simplirwnoume katallila to 1o n-1 * n-1 kommati tou pinaka A
	
	ResistanceT *currentR=rootR;
	k=0;
	while(currentR!=NULL){
		i=atoi(ht_get(hashtable,currentR->node1));
		j=atoi(ht_get(hashtable,currentR->node2));
		
		if(i!=0){
		  A_sparse->i[k]=i;
		  A_sparse->p[k]=i;
		  A_sparse->x[k]=1/currentR->value;
		  k++;
//		  temp=gsl_matrix_get (A, i-1, i-1);
//		  gsl_matrix_set (A, i-1, i-1, temp + 1/currentR->value);
		}
		if(j!=0){
		  A_sparse->i[k]=j;
		  A_sparse->p[k]=j;
		  A_sparse->x[k]=1/currentR->value;
		  k++;
//		  temp=gsl_matrix_get (A, j-1, j-1);
//		  gsl_matrix_set (A, j-1, j-1, temp + 1/currentR->value);
		}
		if(i!=0&&j!=0){
			A_sparse->i[k]=i;
			A_sparse->p[k]=j;
			A_sparse->x[k]=-1/currentR->value;
			k++;
			A_sparse->i[k]=j;
			A_sparse->p[k]=i;
			A_sparse->x[k]=-1/currentR->value;
			k++;
//			temp=gsl_matrix_get (A, i-1, j-1);
//			gsl_matrix_set (A, i-1, j-1, temp - 1/currentR->value);
//			temp=gsl_matrix_get (A, j-1, i-1);
//			gsl_matrix_set (A, j-1, i-1, temp - 1/currentR->value);
		}
		currentR=currentR->next;
	}
	cs_print(A_sparse, "A-Sparse.txt", 0);
	//Diatrexoume ti lista twn pigwn tasis kai simplirwnoume katallila to 2o n-1 * m2 kommati tou pinaka A
	// kai to 2o m2*1 kommati tou pinaka B
/*	
	VoltT *currentV=rootV;

	while(currentV != NULL){
	      i = atoi(ht_get(hashtable,currentV->node1));    //vlepoume metaksu poiown komvwn vrisketai h phgh tashs 
	      j = atoi(ht_get(hashtable,currentV->node2));
	
	      if(i!=0){gsl_matrix_set (A, n-1+b, i-1, 1.000);}		   //grammh-sthlh
	      if(j!=0){gsl_matrix_set (A, n-1+b, j-1, -1.000);}
	      
	      if(i!=0){gsl_matrix_set (A, i-1, n-1+b, 1.000);}		//sthlh-grammh
	      if(j!=0){gsl_matrix_set (A, j-1, n-1+b, -1.000);}
	      if((i!=0)||(j!=0)){gsl_vector_set (B, n-1+b, currentV->value);}	//vazw ston B tis times twn tasewn
	      
	      b++;
	      currentV= currentV ->next;
	
	}

	//Diatrexoume ti lista twn piniwn kai simplirwnoume katallila to 2o n-1 * m2 kommati tou pinaka A

	InductorT *currentL=rootL;
	while(currentL != NULL){
	      i = atoi(ht_get(hashtable,currentL->node1));    //vlepoume metaksu poiown komvwn vrisketai to pinio 
	      j = atoi(ht_get(hashtable,currentL->node2));
	
	      if(i!=0){gsl_matrix_set (A, n-1+b, i-1, 1.000);}		   //grammh-sthlh
	      if(j!=0){gsl_matrix_set (A, n-1+b, j-1, -1.000);}
	      
	      if(i!=0){gsl_matrix_set (A, i-1, n-1+b, 1.000);}		//sthlh-grammh
	      if(j!=0){gsl_matrix_set (A, j-1, n-1+b, -1.000);}
 
	      b++;
	      currentL= currentL ->next;
	}

/*
	//Diatrexoume ti lista twn pigwn reumatwn kai simplirwnoume katallila to 1o n-1 * 1 kommati tou pinaka B
	
	AmperT *currentI=rootI;

	while(currentI != NULL){
	      i = atoi(ht_get(hashtable,currentI->node1));    //vlepoume metaksu poiown komvwn vrisketai h phgh tashs 
	      j = atoi(ht_get(hashtable,currentI->node2));
	
	      if(i!=0){
		temp=gsl_vector_get(B,i-1);
		gsl_vector_set (B, i-1, temp - currentI->value);
	      }
	      if(j!=0){
		temp=gsl_vector_get(B,j-1);
		gsl_vector_set (B, j-1, temp + currentI->value);
	      }
	      
	      currentI = currentI ->next;
	
	}
	
	
	printf("\nM2=%d\nN=%d\n\n",m2,hash_count);
	printf("Matrix A\n");

	for(i=0;i<sizeA;i++){
		for(j=0;j<sizeA;j++){

			printf(" %.3lf ",gsl_matrix_get (A, i, j));
		}
		printf("\n");
	}

	printf("Matrix B\n");
	for(i=0;i<sizeB;i++){
		printf(" %.3lf ",gsl_vector_get(B,i));
	}

	printf("\n");
  
  
  
  
	if(mode == C_MODE && type == 'C'){
		if(p){
			Mi[cnt] = p-1;
			Mj[cnt] = p-1;
			Mx[cnt] = value;
			cnt++;			
			if(m){
				Mi[cnt] = p-1;			
				Mj[cnt] = m-1;
				Mx[cnt] = -value;
				cnt++;			
			}			
			b[p-1] += value;
		}
		if(m){			
			Mi[cnt] = m-1;			
			Mj[cnt] = m-1;
			Mx[cnt] = value;
			cnt++;			
			if(p){
				Mi[cnt] = m-1;			
				Mj[cnt] = p-1;
				Mx[cnt] = -value;
				cnt++;
			}
			b[m-1] -= value;
		}
	}
	else if(mode == G_MODE){
		if(type == 'R'){
			if(p){
				Mi[cnt] = p-1;
				Mj[cnt] = p-1;
				Mx[cnt] = 1.0/value;
				cnt++;			
				if(m){
					Mi[cnt] = p-1;			
					Mj[cnt] = m-1;
					Mx[cnt] = -(1.0/value);
					cnt++;			
				}			
			}
			if(m){			
				Mi[cnt] = m-1;			
				Mj[cnt] = m-1;
				Mx[cnt] = 1.0/value;
				cnt++;			
				if(p){
					Mi[cnt] = m-1;			
					Mj[cnt] = p-1;
					Mx[cnt] = -(1.0/value);
					cnt++;
				}
			}
		}
		else if(type == 'L'){//pigi tasis 0
			type = 'V';
			value = 0.0;
		}
		else if(type == 'I'){
			if(p)
				b[p-1] -= value;
			if(m)
				b[m-1] += value;	
		}
		if(type == 'V'){
		       
			lookup_token = g_hash_table_lookup(hashed_nodes_g2, g_strdup(name));
			m2_index = N + atoi(lookup_token);

			if(p){
				Mi[cnt] = p-1;			
				Mj[cnt] = m2_index-1;
				Mx[cnt] = 1.0;
				cnt++;
	
				Mi[cnt] = m2_index-1;			
				Mj[cnt] = p-1;
				Mx[cnt] = 1.0;
				cnt++;
			}
			if(m){
				Mi[cnt] = m-1;			
				Mj[cnt] = m2_index-1;
				Mx[cnt] = -1.0;
				cnt++;
				Mi[cnt] = m2_index-1;			
				Mj[cnt] = m-1;
				Mx[cnt] = -1.0;
				cnt++;
			}
			b[m2_index-1] += value;
		}
	}
*/
}

void solveSparse(){}
void solve_spdSparse(){}