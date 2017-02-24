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
#include <gsl/gsl_linalg.h>

void CreateMna(){

	int i,j;
	int b=1;
	int n= hash_count-1;
	double temp;

	//Desmeush pinakwn eksiswsewn
	//Desmeush kai arxikopoihsh twn A,B,x
	sizeA = (hash_count-1)+m2;
	A = gsl_matrix_calloc(sizeA,sizeA);
	
	sizeB = (hash_count-1)+m2;
	B = gsl_vector_calloc(sizeB);

	x = gsl_vector_calloc(sizeB);
    
	//Diatrexoume ti lista twn antistasewn kai simplirwnoume katallila to 1o n-1 * n-1 kommati tou pinaka A
	
	ResistanceT *currentR=rootR;
	
	while(currentR!=NULL){
		i=atoi(ht_get(hashtable,currentR->node1));
		j=atoi(ht_get(hashtable,currentR->node2));
		
		if(i!=0){
		  temp=gsl_matrix_get (A, i-1, i-1);
		  gsl_matrix_set (A, i-1, i-1, temp + 1/currentR->value);
		}
		if(j!=0){
		  temp=gsl_matrix_get (A, j-1, j-1);
		  gsl_matrix_set (A, j-1, j-1, temp + 1/currentR->value);
		}
		if(i!=0&&j!=0){
			temp=gsl_matrix_get (A, i-1, j-1);
			gsl_matrix_set (A, i-1, j-1, temp - 1/currentR->value);
			temp=gsl_matrix_get (A, j-1, i-1);
			gsl_matrix_set (A, j-1, i-1, temp - 1/currentR->value);
		}
		currentR=currentR->next;
	}
	
	//Diatrexoume ti lista twn pigwn tasis kai simplirwnoume katallila to 2o n-1 * m2 kommati tou pinaka A
	// kai to 2o m2*1 kommati tou pinaka B
	
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
}

void lu(){

	int s,i,j;
	double current_value;
	FILE *fp;
	char filename[30];
	char str[12];

	p=gsl_permutation_alloc ((hash_count-1)+m2);
	gsl_permutation_init(p);
	gsl_linalg_LU_decomp(A,p,&s);				//s=signum: (-1)^n opou n #enallagwn

	printf("LU matrix\n");					//prints A=LU
	
	for(i=0;i<sizeA;i++){
		for(j=0;j<sizeA;j++){
			printf(" %.6lf ",gsl_matrix_get (A, i, j));
		}
		printf("\n");
	}

	printf("Permutation vector\n");				//prints permutation vector
	gsl_permutation_fprintf (stdout, p, " %u");
	printf("\n");

	if(dc_sweep==0){
		gsl_linalg_LU_solve(A,p,B,x);			//solve LU
		
		printf("X vector \n");
		for(i=0;i<sizeB;i++){
			printf(" %.6lf ",gsl_vector_get(x,i));
		}
		printf("\n");
	}else{
	  for(i=0;i<=plot_size;i++){	//Adeiasma twn arxeiwn
	    sprintf(str, "%d", plot_nodes[i]);
	    strcpy(filename,"Results-Node ");
	    strcat(filename,str);
	    fp = fopen(filename, "w");
	    fflush(fp);
	    fclose(fp);
	  }
		if(sweep_source!=-1){
		  for(current_value=start_value;current_value<=end_value+sweep_step;current_value+=sweep_step){

		    gsl_vector_set(B,sweep_source-1,current_value);
		    gsl_linalg_LU_solve(A,p,B,x);
		    
		    for(i=0;i<=plot_size;i++){	//Gemisma twn arxeiwn

		      sprintf(str, "%d", plot_nodes[i]);
		      strcpy(filename,"Results-Node ");
		      strcat(filename,str);
		      fp = fopen(filename, "a");
		      if (fp == NULL) {
			printf("Can't open output file %s!\n",filename);
			return;
		      }
		      fprintf(fp,"Sweep source voltage at %lf:\tNode %d value:\t%lf\n",current_value, plot_nodes[i],gsl_vector_get(x,plot_nodes[i]-1));
		      fflush(fp);
		      fclose(fp);
		    }
		  }
		}else{
		  //Anairesi twn praksewn + kai - apo tin arxiki timi tis pigis ston pinaka B
		  //kai praksi + kai - me to start_value
		  if(sweep_posNode!=0){
		    gsl_vector_set(B,sweep_posNode-1,gsl_vector_get(B,sweep_posNode-1)+sweep_value_I-start_value);
		  }
		  if(sweep_negNode!=0){
		    gsl_vector_set(B,sweep_negNode-1,gsl_vector_get(B,sweep_negNode-1)-sweep_value_I+start_value);
		  }
		  
		  for(current_value=start_value;current_value<=end_value+sweep_step;current_value+=sweep_step){

		   gsl_linalg_LU_solve(A,p,B,x);
		   
		   //Allagi twn timwn ston pinaka B gia to epomeno vima tou sweep
		   if(sweep_posNode!=0){
		     gsl_vector_set(B,sweep_posNode-1,gsl_vector_get(B,sweep_posNode-1)-sweep_step);
		    }
		   if(sweep_negNode!=0){
		     gsl_vector_set(B,sweep_negNode-1,gsl_vector_get(B,sweep_negNode-1)+sweep_step);
		   }

		    for(i=0;i<plot_size;i++){	//Gemisma twn arxeiwn

		      sprintf(str, "%d", plot_nodes[i]);
		      strcpy(filename,"Results-Node ");
		      strcat(filename,str);
		      fp = fopen(filename, "a");
		      if (fp == NULL) {
			printf("Can't open output file %s!\n",filename);
			return;
		      }
		      fprintf(fp,"Sweep source current at %lf:\tNode %d value:\t%.6e\n",current_value, plot_nodes[i],gsl_vector_get(x,plot_nodes[i]-1));
		      fflush(fp);
		      fclose(fp);
		    }
		  }
		  printf("\n");
		}
	}
}

void Cholesky(){
	
	int i,j;
	double current_value;
	FILE *fp;
	char filename[30];
	char str[12];
	
	gsl_linalg_cholesky_decomp(A);

	printf("CHOLESKY matrix\n ");
	for(i=0;i<sizeA;i++){
	 	for(j=0;j<sizeA;j++){
			printf(" %.6lf ",gsl_matrix_get (A, i, j));
	  	}
		printf("\n");
	}	

	if(dc_sweep==0){
		gsl_linalg_cholesky_solve(A,B,x);			//solve cholesky

		printf("X vector \n");
		for(i=0;i<sizeB;i++){
			printf(" %.6lf ",gsl_vector_get(x,i));
		}
		printf("\n");
	}else{
	  for(i=0;i<=plot_size;i++){	//Adeiasma twn arxeiwn
	    sprintf(str, "%d", plot_nodes[i]);
	    strcpy(filename,"Results-Node ");
	    strcat(filename,str);
	    fp = fopen(filename, "w");
	    fflush(fp);
	    fclose(fp);
	  }
		if(sweep_source!=-1){
		  for(current_value=start_value;current_value<=end_value+sweep_step;current_value+=sweep_step){

		    gsl_vector_set(B,sweep_source-1,current_value);
		    gsl_linalg_cholesky_solve(A,B,x);
		    
		    for(i=0;i<=plot_size;i++){	//Gemisma twn arxeiwn

		      sprintf(str, "%d", plot_nodes[i]);
		      strcpy(filename,"Results-Node ");
		      strcat(filename,str);
		      fp = fopen(filename, "a");
		      if (fp == NULL) {
			printf("Can't open output file %s!\n",filename);
			return;
		      }
		      fprintf(fp,"Sweep source voltage at %lf:\tNode %d value:\t%lf\n",current_value, plot_nodes[i],gsl_vector_get(x,plot_nodes[i]-1));
		      fflush(fp);
		      fclose(fp);
		    }
		  }
		}else{
		  //Anairesi twn praksewn + kai - apo tin arxiki timi tis pigis ston pinaka B
		  //kai praksi + kai - me to start_value
		  if(sweep_posNode!=0){
		    gsl_vector_set(B,sweep_posNode-1,gsl_vector_get(B,sweep_posNode-1)+sweep_value_I-start_value);
		  }
		  if(sweep_negNode!=0){
		    gsl_vector_set(B,sweep_negNode-1,gsl_vector_get(B,sweep_negNode-1)-sweep_value_I+start_value);
		  }
		  
		  for(current_value=start_value;current_value<=end_value+sweep_step;current_value+=sweep_step){

		   gsl_linalg_cholesky_solve(A,B,x);
		   
		   //Allagi twn timwn ston pinaka B gia to epomeno vima tou sweep
		   if(sweep_posNode!=0){
		     gsl_vector_set(B,sweep_posNode-1,gsl_vector_get(B,sweep_posNode-1)-sweep_step);
		    }
		   if(sweep_negNode!=0){
		     gsl_vector_set(B,sweep_negNode-1,gsl_vector_get(B,sweep_negNode-1)+sweep_step);
		   }

		    for(i=0;i<plot_size;i++){	//Gemisma twn arxeiwn

		      sprintf(str, "%d", plot_nodes[i]);
		      strcpy(filename,"Results-Node ");
		      strcat(filename,str);
		      fp = fopen(filename, "a");
		      if (fp == NULL) {
			printf("Can't open output file %s!\n",filename);
			return;
		      }
		      fprintf(fp,"Sweep source current at %lf:\tNode %d value:\t%.6e\n",current_value, plot_nodes[i],gsl_vector_get(x,plot_nodes[i]-1));
		      fflush(fp);
		      fclose(fp);
		    }
		  }
		  printf("\n");
		}
	}
}
