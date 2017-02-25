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
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_cblas.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>


void CreateMnaSparse(){

	int i,j;
	int b=1;
	int n= hash_count-1;

	//Desmeush pinakwn eksiswsewn
	//Desmeush kai arxikopoihsh twn A,B,x

	A_sparse = cs_spalloc((hash_count-1)+m2,(hash_count-1)+m2, sizeA_sparse, 1, 1);
		
//	A_sparse->nz=sizeA_sparse;
	sizeB = (hash_count-1)+m2;
	B_sparse = (double *)calloc(sizeB,sizeof(double));
	x_sparse = (double *)calloc(sizeB,sizeof(double));

	//Diatrexoume ti lista twn antistasewn kai simplirwnoume katallila to 1o n-1 * n-1 kommati tou pinaka A
	
	ResistanceT *currentR=rootR;

	while(currentR!=NULL){
		i=atoi(ht_get(hashtable,currentR->node1));
		j=atoi(ht_get(hashtable,currentR->node2));

		if(i!=0){
		  cs_entry(A_sparse,i-1,i-1,1/currentR->value);
		}
		if(j!=0){
		  cs_entry(A_sparse,j-1,j-1,1/currentR->value);
		}
		if(i!=0&&j!=0){
		  cs_entry(A_sparse,i-1,j-1,-1/currentR->value);
		  cs_entry(A_sparse,j-1,i-1,-1/currentR->value);
		}
		currentR=currentR->next;
	}

	//Diatrexoume ti lista twn pigwn tasis kai simplirwnoume katallila to 2o n-1 * m2 kommati tou pinaka A
	// kai to 2o m2*1 kommati tou pinaka B
	
	VoltT *currentV=rootV;
	while(currentV != NULL){
		//vlepoume metaksu poiown komvwn vrisketai h phgh tashs 
		i=atoi(ht_get(hashtable,currentV->node1));
		j=atoi(ht_get(hashtable,currentV->node2));
		
		if(i!=0){
		  cs_entry(A_sparse,n-1+b,i-1,1.000);
		  cs_entry(A_sparse,i-1,n-1+b,1.000);
		}
		if(j!=0){
		  cs_entry(A_sparse,n-1+b,j-1,-1.000);
		  cs_entry(A_sparse,j-1,n-1+b,-1.000);
		}
	      
	      if((i!=0)||(j!=0)){B_sparse[n-1+b]=currentV->value;}	//vazw ston B tis times twn tasewn
	      b++;
	      currentV= currentV ->next;
	}

	//Diatrexoume ti lista twn piniwn kai simplirwnoume katallila to 2o n-1 * m2 kommati tou pinaka A

	InductorT *currentL=rootL;
	while(currentL != NULL){
	      i = atoi(ht_get(hashtable,currentL->node1));    //vlepoume metaksu poiown komvwn vrisketai to pinio 
	      j = atoi(ht_get(hashtable,currentL->node2));
	
	      if(i!=0){
		  cs_entry(A_sparse,n-1+b,i-1,1.000);
		  cs_entry(A_sparse,i-1,n-1+b,1.000);
		}
		if(j!=0){
		  cs_entry(A_sparse,n-1+b,j-1,-1.000);
		  cs_entry(A_sparse,j-1,n-1+b,-1.000);
		}
	      b++;
	      currentL= currentL ->next;
	}

	//Diatrexoume ti lista twn pigwn reumatwn kai simplirwnoume katallila to 1o n-1 * 1 kommati tou pinaka B
	
	AmperT *currentI=rootI;
	while(currentI != NULL){
	      i = atoi(ht_get(hashtable,currentI->node1));    //vlepoume metaksu poiown komvwn vrisketai h phgh tashs 
	      j = atoi(ht_get(hashtable,currentI->node2));
	
	      if(i!=0){
		B_sparse[i-1]-=currentI->value;
	      }
	      if(j!=0){
		B_sparse[j-1]+=currentI->value;
	      }
	      
	      currentI = currentI ->next;
	
	}

	cs_print(A_sparse, "./SparseOutput/A-Sparse.txt", 0);

	//Afou exoume ftiaksei ton A (mna) se triplet morfi, ton metatrepoume se
	//compressed-column morfi kai eleutherwnoume ton xwro me tin palia morfi kai
	//sigxwneuoume ta diaforetika non zeros pou vriskontai stin idia thesi

	C_sparse = cs_compress(A_sparse);
	cs_spfree(A_sparse);
	cs_dupl(C_sparse);
	cs_print(C_sparse, "./SparseOutput/C-Sparse-nondupl.txt", 0);
}

void solveSparse(){
  
	int i;
	double current_value;
	FILE *fp;
	char filename[30];
	double *B_sparse_temp;

	if(ITER==0){			//LU decomposition
	  S=cs_sqr(2,C_sparse,0);
	  N=cs_lu(C_sparse,S,1);
	  cs_spfree(C_sparse);
	}
	if(dc_sweep==0){		//An den exoume sweep
	  if (ITER == 0){		//LU solve
	    cs_ipvec(N->pinv, B_sparse, x_sparse, (hash_count-1)+m2);
	    cs_lsolve(N->L, x_sparse);
	    cs_usolve(N->U, x_sparse);
	    cs_ipvec(S->q, x_sparse, B_sparse, (hash_count-1)+m2);
	  }else{
//	    bi_conjugate_gradient(A,B,x,sizeA,itol_value);
	  }
	
	  printf("X vector \n");
	  for(i=0;i<sizeB;i++){
	    printf(" %.6lf ",B_sparse[i]);
	  }
	  printf("\n");
	}else{					//An exoume sweep
	
		//Adeiasma twn arxeiwn sta opoia tha apothikeutoun ta apotelesmata tis analysis gia tous komvous PLOT
	  for(i=0;i<plot_size;i++){
	    strcpy(filename,"./PlotFiles/Results-Node ");
	    strcat(filename,plot_names[i]);
	    fp = fopen(filename, "w");
	    fflush(fp);
	    fclose(fp);
	  }
	  
	  
	  B_sparse_temp = (double *)calloc(sizeB,sizeof(double));		//Proswrini pothikeusi tou apotelesmatos tis LU solve anamesa sta loop
		if(sweep_source!=-1){		//pigi tashs ginetai sweep
		  for(current_value=start_value;current_value<end_value+sweep_step;current_value+=sweep_step){

		    B_sparse[sweep_source-1]=current_value;
		    if(ITER == 0){
		      cs_ipvec(N->pinv, B_sparse, x_sparse, (hash_count-1)+m2);
		      cs_lsolve(N->L, x_sparse);
		      cs_usolve(N->U, x_sparse);
		      cs_ipvec(S->q, x_sparse, B_sparse_temp, (hash_count-1)+m2);
		    }else{
//			bi_conjugate_gradient(A,B,x,sizeA,itol_value);
		    }
			
		//Apothikeusi twn apotelesmatwn tis analysis gia tous komvous PLOT
		    for(i=0;i<plot_size;i++){
		      strcpy(filename,"./PlotFiles/Results-Node ");
		      strcat(filename,plot_names[i]);
		      fp = fopen(filename, "a");
		      if (fp == NULL) {
			printf("Can't open output file %s!\n",filename);
			return;
		      }
		      fprintf(fp,"Sweep source voltage at %lf:\tNode %s value:\t%lf\n",current_value, plot_names[i],B_sparse_temp[plot_nodes[i]-1]);
		      fflush(fp);
		      fclose(fp);
		    }
			
		  }
		  
		}else{				//pigi reumatos ginetai sweep
		
		  //Anairesi twn praksewn + kai - apo tin arxiki timi tis pigis ston pinaka B
		  //kai praksi + kai - me to start_value
		  if(sweep_posNode!=0){
		    B_sparse[sweep_posNode-1]+=sweep_value_I-start_value;
		  }
		  if(sweep_negNode!=0){
		    B_sparse[sweep_negNode-1]-=sweep_value_I+start_value;
		  }
		  
		  for(current_value=start_value;current_value<end_value+sweep_step;current_value+=sweep_step){
		    
		  if(ITER == 0){
		      cs_ipvec(N->pinv, B_sparse, x_sparse, (hash_count-1)+m2);
		      cs_lsolve(N->L, x_sparse);
		      cs_usolve(N->U, x_sparse);
		      cs_ipvec(S->q, x_sparse, B_sparse_temp, (hash_count-1)+m2);
		  }else{
//		      bi_conjugate_gradient(A,B,x,sizeA,itol_value);
		  }
		  
		   //Allagi twn timwn ston pinaka B gia to epomeno vima tou sweep
		   if(sweep_posNode!=0){
		     B_sparse[sweep_posNode-1]-=sweep_step;
		    }
		   if(sweep_negNode!=0){
		     B_sparse[sweep_negNode-1]+=sweep_step;
		   }
		   
			//Apothikeusi twn apotelesmatwn tis analysis gia tous komvous PLOT se arxeia
		    for(i=0;i<plot_size;i++){
		      strcpy(filename,"./PlotFiles/Results-Node ");
		      strcat(filename,plot_names[i]);
		      fp = fopen(filename, "a");
		      if (fp == NULL) {
			printf("Can't open output file %s!\n",filename);
			return;
		      }
		      fprintf(fp,"Sweep source current at %lf:\tNode %s value:\t%.6e\n",current_value, plot_names[i],B_sparse_temp[plot_nodes[i]-1]);
		      fflush(fp);
		      fclose(fp);
		    }
			
			
		  }
		  printf("\n");
		}
	}
}

void solve_spdSparse(){
  	
	int i;
	double current_value;
	FILE *fp;
	char filename[30];
	double *B_sparse_temp;
	
	if(ITER==0){
		//cholesky decomposition
		S=cs_schol(1, C_sparse);
		N=cs_chol(C_sparse, S);
		cs_spfree(C_sparse);
	}
	if(dc_sweep==0){		//An den exoume sweep
		if(ITER==0){	
		  cs_ipvec(S->pinv, B_sparse, x_sparse, (hash_count-1)+m2);
		  cs_lsolve(N->L, x_sparse);
		  cs_ltsolve(N->L, x_sparse);
		  cs_pvec(S->pinv, x_sparse, B_sparse, (hash_count-1)+m2);			//solve cholesky
		}
		else{
			conjugate_gradient_sparse(C_sparse,B_sparse, sizeB, x_sparse, itol_value);			//solve with Conjugated Gradient
		}
		
		//Ektypwsi olou tou dianysmatos x stin konsola
		printf("X vector \n");
		for(i=0;i<sizeB;i++){
			printf(" %.15lf ",x_sparse[i]);
		}
		printf("\n");
		
	}else{		//An exoume sweep
		
		
		//Adeiasma twn arxeiwn sta opoia tha apothikeutoun ta apotelesmata tis analysis gia tous komvous PLOT
	  for(i=0;i<plot_size;i++){
	    strcpy(filename,"./PlotFiles/Results-Node ");
	    strcat(filename,plot_names[i]);
	    fp = fopen(filename, "w");
	    fflush(fp);
	    fclose(fp);
	  }
	  
	  
	  B_sparse_temp = (double *)calloc(sizeB,sizeof(double));		//Proswrini apothikeusi tou apotelesmatos anamesa sta loop
		if(sweep_source!=-1){				//pigi tasis ginetai sweep
		  for(current_value=start_value;current_value<end_value+sweep_step;current_value+=sweep_step){

		    B_sparse[sweep_source-1]=current_value;
		    if(ITER==0){		
		      cs_ipvec(S->pinv, B_sparse, x_sparse, (hash_count-1)+m2);
		      cs_lsolve(N->L, x_sparse);
		      cs_ltsolve(N->L, x_sparse);
		      cs_pvec(S->pinv, x_sparse, B_sparse_temp, (hash_count-1)+m2);		//solve cholesky
		    }
		    else{
			
			conjugate_gradient_sparse(C_sparse,B_sparse, sizeB, x_sparse, itol_value);		

		    }
		    
			//Apothikeusi twn apotelesmatwn tis analysis gia tous komvous PLOT se arxeia
		    for(i=0;i<plot_size;i++){	//Gemisma twn arxeiwn
		      strcpy(filename,"./PlotFiles/Results-Node ");
		      strcat(filename,plot_names[i]);
		      fp = fopen(filename, "a");
		      if (fp == NULL) {
			printf("Can't open output file %s!\n",filename);
			return;
		      }
		      fprintf(fp,"Sweep source voltage at %lf:\tNode %s value:\t%lf\n",current_value, plot_names[i],x_sparse[plot_nodes[i]-1]);
		      fflush(fp);
		      fclose(fp);
		    }
		  }
		}else{		//pigi reumatos ginetai sweep
		  //Anairesi twn praksewn + kai - apo tin arxiki timi tis pigis ston pinaka B
		  //kai praksi + kai - me to start_value
		  if(sweep_posNode!=0){
		    B_sparse[sweep_posNode-1]+=sweep_value_I-start_value;
		  }
		  if(sweep_negNode!=0){
		    B_sparse[sweep_negNode-1]-=sweep_value_I-start_value;
		  }
		  
		  for(current_value=start_value;current_value<end_value+sweep_step;current_value+=sweep_step){

		   if(ITER==0){
		      cs_ipvec(S->pinv, B_sparse, x_sparse, (hash_count-1)+m2);
		      cs_lsolve(N->L, x_sparse);
		      cs_ltsolve(N->L, x_sparse);
		      cs_pvec(S->pinv, x_sparse, B_sparse_temp, (hash_count-1)+m2);		//solve cholesky
		   }
		   else{
			
			conjugate_gradient_sparse(C_sparse,B_sparse, sizeB, x_sparse, itol_value);	
			//Arxiki proseggish h lush ths prohgoumenhs
		   }
		    
		   
		   //Allagi twn timwn ston pinaka B gia to epomeno vima tou sweep
		   if(sweep_posNode!=0){
		     B_sparse[sweep_posNode-1]-=sweep_step;
		    }
		   if(sweep_negNode!=0){
		     B_sparse[sweep_negNode-1]+=sweep_step;
		   }

			//Apothikeusi twn apotelesmatwn tis analysis gia tous komvous PLOT se arxeia
		    for(i=0;i<plot_size;i++){
		      strcpy(filename,"./PlotFiles/Results-Node ");
		      strcat(filename,plot_names[i]);
		      fp = fopen(filename, "a");
		      if (fp == NULL) {
			printf("Can't open output file %s!\n",filename);
			return;
		      }
		      fprintf(fp,"Sweep source current at %lf:\tNode %s value:\t%.6e\n",current_value, plot_names[i],x_sparse[plot_nodes[i]-1]);
		      fflush(fp);
		      fclose(fp);
		    }
			
			
		  }
		  printf("\n");
		}
	}

}

void conjugate_gradient_sparse(cs *A, double *b, int n, double *x, double itol)
{	
	int i,j,iter;
	double rho,rho1,alpha,beta,omega;
	
	double r[n]; 
	double z[n], temp_z[n];
	double q[n], temp_q[n]; 
	double p[n], temp_p[n];
	double res[n];
	double precond[n];	//Preconditioner
	
	memset(precond, 0, n*sizeof(double));
	memset(r, 0, n*sizeof(double));
	memset(z, 0, n*sizeof(double));
	memset(temp_z, 0, n*sizeof(double));
	memset(q, 0, n*sizeof(double));
	memset(temp_q, 0, n*sizeof(double));
	memset(p, 0, n*sizeof(double));
	memset(temp_p, 0, n*sizeof(double));

/* Preconditioner */
	double max;
	int pp;
	for(j = 0; j < n; ++j){
		for(pp = A->p[j], max = fabs(A->x[pp]); pp < A->p[j+1]; pp++)
			if(fabs(A->x[pp]) > max)					//vriskei to diagonio stoixeio
				max = fabs(A->x[pp]);
		precond[j] = 1/max;		
	}	
	
	
 	printf("\n");
	printf("PRECONTITIONER 1/Diag \n");
	for(i=0;i<n;i++){
 		printf(" %.6lf ",precond[i]);
	
	}
	printf("\n");
	cblas_dcopy (n, x, 1, res, 1);

	//r=b-Ax
	cblas_dcopy (n, b, 1, r, 1);
	memset(p, 0, n*sizeof(double));
	cs_gaxpy (A, x_sparse, p);
	for(i=0;i<n;i++){
 		r[i]=r[i]-p[i];
	
	}
	
	double r_norm = cblas_dnrm2 (n, r, 1);
	double b_norm = cblas_dnrm2 (n, b, 1);
	if(!b_norm)
		b_norm = 1;

	iter = 0;	
	
	while( r_norm/b_norm > itol && iter < n )
	{
		iter++;

		cblas_dcopy (n, r, 1, z, 1);				//gia na min allaksei o r
		
		for(i=0;i<n;i++){
 			z[i]=precond[i]*z[i];
	
		}

		rho = cblas_ddot (n, z, 1, r, 1);
		if (fpclassify(fabs(rho)) == FP_ZERO){
			printf("RHO aborting CG due to EPS...\n");
			exit(42);
		}

		if (iter == 1){
			cblas_dcopy (n, z, 1, p, 1);
		}
		else{		
			beta = rho/rho1;
	
			//p = z + beta*p;
			cblas_dscal (n, beta, p, 1);	//rescale
			cblas_daxpy (n, 1, z, 1, p, 1);	//p = 1*z + p
			
		}		
		rho1 = rho;
		
		//q = Ap
		memset(q, 0, n*sizeof(double));
		cs_gaxpy (A, p, q);

		omega = cblas_ddot (n, p, 1, q, 1);
		if (fpclassify(fabs(omega)) == FP_ZERO){
			printf("OMEGA aborting CG due to EPS...\n");
			exit(42);
		}

		alpha = rho/omega;	

		//x = x + aplha*p;
		cblas_dcopy (n, p, 1, temp_p, 1);
		cblas_dscal (n, alpha, temp_p, 1);//rescale by alpha
		cblas_daxpy (n, 1, temp_p, 1, res, 1);// sum x = 1*x + temp_p

		//r = r - aplha*q;
		cblas_dcopy (n, q, 1, temp_q, 1);
		cblas_dscal (n, -alpha, temp_q, 1);//rescale by alpha
		cblas_daxpy (n, 1, temp_q, 1, r, 1);// sum r = 1*r - temp_p

		//next step
		r_norm = cblas_dnrm2 (n, r, 1);
	}
	cblas_dcopy (n, res, 1, x, 1);

}
