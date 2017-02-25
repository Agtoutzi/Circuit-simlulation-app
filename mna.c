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
#include <gsl/gsl_blas.h>


void CreateMna(){

	int i,j;
	int b=1;
	int n= hash_count-1;
	double temp;

	//Desmeush pinakwn eksiswsewn
	//Desmeush kai arxikopoihsh twn A,B,x

	sizeA = (hash_count-1)+m2;
	A = gsl_matrix_calloc(sizeA,sizeA);
	
	if (TRAN==1)
		C = gsl_matrix_calloc(sizeA,sizeA);	

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
	      i = atoi(ht_get(hashtable,currentV->node1));    			//vlepoume metaksu poiown komvwn vrisketai h phgh tashs 
	      j = atoi(ht_get(hashtable,currentV->node2));
	
	      if(i!=0){gsl_matrix_set (A, n-1+b, i-1, 1.000);}		   	//grammh-sthlh
	      if(j!=0){gsl_matrix_set (A, n-1+b, j-1, -1.000);}
	      
	      if(i!=0){gsl_matrix_set (A, i-1, n-1+b, 1.000);}			//sthlh-grammh
	      if(j!=0){gsl_matrix_set (A, j-1, n-1+b, -1.000);}
	      if((i!=0)||(j!=0)){gsl_vector_set (B, n-1+b, currentV->value);}	//vazw ston B tis times twn tasewn
	      
	      b++;
	      currentV= currentV ->next;
	
	}

	//Diatrexoume ti lista twn piniwn kai simplirwnoume katallila to 2o n-1 * m2 kommati tou pinaka A

	InductorT *currentL=rootL;
	while(currentL != NULL){
	      i = atoi(ht_get(hashtable,currentL->node1));    		   	//vlepoume metaksu poiown komvwn vrisketai to pinio 
	      j = atoi(ht_get(hashtable,currentL->node2));
	
	      if(i!=0){gsl_matrix_set (A, n-1+b, i-1, 1.000);}		   	//grammh-sthlh
	      if(j!=0){gsl_matrix_set (A, n-1+b, j-1, -1.000);}
	      
	      if(i!=0){gsl_matrix_set (A, i-1, n-1+b, 1.000);}		   	//sthlh-grammh
	      if(j!=0){gsl_matrix_set (A, j-1, n-1+b, -1.000);}
 
	      if (TRAN==1)		
			gsl_matrix_set (C, n-1+b, n-1+b, -currentL->value);	//-L sth 8esh k,k 
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
	
	
	//Diatrexoume ti lista twn puknwtwn kai simplirwnoume katallila to 1o n-1 * n-1 kommati tou pinaka C
	if (TRAN==1){
		CapacitorT *currentC=rootC;
	
		while(currentC!=NULL){
			i=atoi(ht_get(hashtable,currentC->node1));
			j=atoi(ht_get(hashtable,currentC->node2));
		
			if(i!=0){
			  temp=gsl_matrix_get (C, i-1, i-1);
			  gsl_matrix_set (C, i-1, i-1, temp + currentC->value);
			}
			if(j!=0){
			  temp=gsl_matrix_get (C, j-1, j-1);
			  gsl_matrix_set (C, j-1, j-1, temp + currentC->value);
			}
			if(i!=0&&j!=0){
				temp=gsl_matrix_get (C, i-1, j-1);
				gsl_matrix_set (C, i-1, j-1, temp - currentC->value);
				temp=gsl_matrix_get (C, j-1, i-1);
				gsl_matrix_set (C, j-1, i-1, temp - currentC->value);
			}
			currentC=currentC->next;
		}
	}
// 	//PRINT MATRICES
// 	
// 	printf("\nM2=%d\nN=%d\n\n",m2,hash_count);
// 	printf("Matrix A\n");
// 
// 	for(i=0;i<sizeA;i++){
// 		for(j=0;j<sizeA;j++){
// 
// 			printf(" %.3lf ",gsl_matrix_get (A, i, j));
// 		}
// 		printf("\n");
// 	}
// 
// 	if(TRAN==1){
// 		printf("Matrix C\n");
// 
// 		for(i=0;i<sizeA;i++){
// 			for(j=0;j<sizeA;j++){
// 
// 				printf(" %.3lf ",gsl_matrix_get (C, i, j));
// 			}
// 			printf("\n");
// 		}
// 	}
// 	printf("Matrix B\n");
// 	for(i=0;i<sizeB;i++){
// 		printf(" %.3lf ",gsl_vector_get(B,i));
// 	}
// 
// 	printf("\n");
}

void solve(){
  
	int s;
	double current_value;

	gsl_matrix *A_temp;
	A_temp=gsl_matrix_calloc(sizeA,sizeA);
	gsl_matrix_memcpy(A_temp,A);				//KRATAME TON A GIA NA TON XRHSIMOPOIHSOUME SE TRANSIENT!

	p=gsl_permutation_alloc ((hash_count-1)+m2);
	gsl_permutation_init(p);
	
	//Adeiasma twn arxeiwn    
	if(TRAN==0)initPlotFiles("Dense Results");
	
	if(ITER==0){
	  gsl_linalg_LU_decomp(A,p,&s);				//s=signum: (-1)^n opou n #enallagwn

// 	  printf("LU matrix\n");				//prints A=LU
// 	
// 	  for(i=0;i<sizeA;i++){
// 		for(j=0;j<sizeA;j++){
// 			printf(" %.6lf ",gsl_matrix_get (A, i, j));
// 		}
// 		printf("\n");
// 	  }

	}
	if(dc_sweep==0){
	  if (ITER == 0){
		gsl_linalg_LU_solve(A,p,B,x);			//solve LU
	  }else{
	    bi_conjugate_gradient(A,B,x,sizeA,itol_value);
	  }

	  if(TRAN==0){
	    plotFiles("Dense Results", gslvector2double(x,sizeA), -1.0, "DC analysis");
	  }else{
	    plotFiles("Dense Results", gslvector2double(x,sizeA), -1.0, "TRANSIENT analysis");
	  }
	}else{

		if(sweep_source!=-1){	//pigi tashs
		  for(current_value=start_value;current_value<=end_value+EPS;current_value+=sweep_step){

		    gsl_vector_set(B,sweep_source-1,current_value);
		    if(ITER == 0){
			gsl_linalg_LU_solve(A,p,B,x);
		    }else{
			bi_conjugate_gradient(A,B,x,sizeA,itol_value);
		    }
		    //Gemisma twn arxeiwn  
 		    plotFiles("Dense Results", gslvector2double(x,sizeB), current_value, "Sweep source voltage at");
		  }
		}else{			//pigi reumatos
		  //Anairesi twn praksewn + kai - apo tin arxiki timi tis pigis ston pinaka B
		  //kai praksi + kai - me to start_value
		  if(sweep_posNode!=0){
		    gsl_vector_set(B,sweep_posNode-1,gsl_vector_get(B,sweep_posNode-1)+sweep_value_I-start_value);
		  }
		  if(sweep_negNode!=0){
		    gsl_vector_set(B,sweep_negNode-1,gsl_vector_get(B,sweep_negNode-1)-sweep_value_I+start_value);
		  }
		  
		  for(current_value=start_value;current_value<=end_value+EPS;current_value+=sweep_step){
		    
		  if(ITER == 0){
		      gsl_linalg_LU_solve(A,p,B,x);
		  }else{
		      bi_conjugate_gradient(A,B,x,sizeA,itol_value);
		  }
		   //Allagi twn timwn ston pinaka B gia to epomeno vima tou sweep
		   if(sweep_posNode!=0){
		     gsl_vector_set(B,sweep_posNode-1,gsl_vector_get(B,sweep_posNode-1)-sweep_step);
		    }
		   if(sweep_negNode!=0){
		     gsl_vector_set(B,sweep_negNode-1,gsl_vector_get(B,sweep_negNode-1)+sweep_step);
		   }

		    //Gemisma twn arxeiwn 
		    plotFiles("Dense Results", gslvector2double(x,sizeB), current_value, "Sweep source current at");
		  }
		  printf("\n");
		}
	}
	gsl_matrix_memcpy(A,A_temp);
	gsl_matrix_free(A_temp);
}

void solve_spd(){
	
//	int i,j;
	double current_value;
	
	gsl_matrix *A_temp;
	A_temp=gsl_matrix_calloc(sizeA,sizeA);
	gsl_matrix_memcpy(A_temp,A);			//KRATAME TON A GIA NA TON XRHSIMOPOIHSOUME SE TRANSIENT!
	
	//Adeiasma twn arxeiwn
	if(TRAN==0)initPlotFiles("Dense Results");
	
	
	if(ITER==0){
		gsl_linalg_cholesky_decomp(A);		//cholesky decomposition
	
/*		printf("CHOLESKY matrix\n ");
		for(i=0;i<sizeA;i++){
	 		for(j=0;j<sizeA;j++){
				printf(" %.6lf ",gsl_matrix_get (A, i, j));
	  		}
			printf("\n");
		}*/	
	}
	if(dc_sweep==0){
		if(ITER==0){
			gsl_linalg_cholesky_solve(A,B,x);			//solve cholesky
		}
		else{
			conjugate_gradient(A,B,x,sizeA,itol_value);		//solve with Conjugated Gradient
		}	

		if(TRAN==0){
		  plotFiles("Dense Results", gslvector2double(x,sizeA), -1.0, "DC analysis");
		}else{
		  plotFiles("Dense Results", gslvector2double(x,sizeA), -1.0, "TRANSIENT analysis");
		}
	}else{
		if(sweep_source!=-1){
		  for(current_value=start_value;current_value<=end_value+EPS;current_value+=sweep_step){

		    gsl_vector_set(B,sweep_source-1,current_value);
		    if(ITER==0){
			gsl_linalg_cholesky_solve(A,B,x);			//solve cholesky
		    }
		    else{
			
			conjugate_gradient(A,B,x,sizeA,itol_value);		//Arxiki proseggish h lush ths prohgoumenhs
		    }
		    
		    //Gemisma twn arxeiwn
		    plotFiles("Dense Results", gslvector2double(x,sizeB), current_value, "Sweep source voltage at");
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
		  
		  for(current_value=start_value;current_value<=end_value+EPS;current_value+=sweep_step){

		   if(ITER==0){
			gsl_linalg_cholesky_solve(A,B,x);			//solve cholesky
		   }
		   else{
			
			conjugate_gradient(A,B,x,sizeA,itol_value);		//Arxiki proseggish h lush ths prohgoumenhs
		   }
		    
		   
		   //Allagi twn timwn ston pinaka B gia to epomeno vima tou sweep
		   if(sweep_posNode!=0){
		     gsl_vector_set(B,sweep_posNode-1,gsl_vector_get(B,sweep_posNode-1)-sweep_step);
		    }
		   if(sweep_negNode!=0){
		     gsl_vector_set(B,sweep_negNode-1,gsl_vector_get(B,sweep_negNode-1)+sweep_step);
		   }

		   //Gemisma twn arxeiwn
		    plotFiles("Dense Results", gslvector2double(x,sizeB), current_value, "Sweep source current at");
		  }
		  printf("\n");
		}
	}
	gsl_matrix_memcpy(A,A_temp);
	gsl_matrix_free(A_temp);
}

void conjugate_gradient(gsl_matrix *a,gsl_vector *b,gsl_vector *X,int n,double tolerance){	

	double rho,rho1,alpha,beta;	
	gsl_vector *r;	
	gsl_vector *z;	
	gsl_vector *p;
	gsl_vector *q;		
	gsl_vector *precond;
	gsl_vector *temp_p;
	gsl_vector *temp_q;
	gsl_vector *res;
	
	r = gsl_vector_calloc(n);
	z = gsl_vector_calloc(n);
	p = gsl_vector_calloc(n);
	q = gsl_vector_calloc(n);	
	precond = gsl_vector_calloc(n);
	temp_p = gsl_vector_calloc(n);
	temp_q = gsl_vector_calloc(n);
	res = gsl_vector_calloc(n);

	int i;
	

	preconditioner_diag(precond,a);
	for(i=0;i<n;i++){
		 gsl_vector_set(precond,i,1/gsl_vector_get(precond,i));	//precontitioner^-1 (M^-1) = 1/diag(A)

	}

 	/*printf("\n");
	printf("PRECONTITIONER 1/Diag \n");
	for(i=0;i<n;i++){
 		printf(" %.6lf ",gsl_vector_get(precond,i));
	
	}*/

	gsl_blas_dcopy(X,res);							//Store X sto temp res

	//r=b-Ax
	gsl_blas_dcopy(b,r);	
	gsl_blas_dgemv(CblasNoTrans,1,a,res,0.0,p);				//prosorina p=A*x 	
	gsl_vector_sub(r,p);	

	int iter=0;
	
	double r_norm = gsl_blas_dnrm2(r);
	double b_norm = gsl_blas_dnrm2(b);
	if(!b_norm)
		b_norm = 1;

	while( r_norm/b_norm > tolerance && iter < n ){

		iter++;
		
		gsl_blas_dcopy(r,z);						//gia na min allaksei o r
		gsl_vector_mul(z,precond);					

		gsl_blas_ddot(r,z,&rho);					//r^T * Z

		if(iter==1){
			gsl_blas_dcopy(z,p);			
		}
	
		else{
			beta=rho/rho1;
			gsl_blas_dscal(beta,p);
			gsl_blas_daxpy(1,z,p);	
		}
		rho1=rho;
		gsl_blas_dgemv(CblasNoTrans,1,a,p,0.0,q);			//q=A*p 

		gsl_blas_ddot(p,q,&alpha);					//p^T * q
		alpha=rho/alpha;						//alpha=rho/p^T*q		
				
		gsl_blas_dcopy(p,temp_p);					//x=x+alpha*p
		gsl_blas_dscal(alpha,temp_p);
		gsl_blas_daxpy(1,temp_p,res);	

		gsl_blas_dcopy(q,temp_q);					//r=r-alpha*q
		gsl_blas_dscal(-alpha,temp_q);
		gsl_blas_daxpy(1,temp_q,r);	
		
		r_norm = gsl_blas_dnrm2(r);					//new r norm

	}
	gsl_blas_dcopy(res,X);							//Restore res back to X

	gsl_vector_free(r);
	gsl_vector_free(z);
	gsl_vector_free(p);
	gsl_vector_free(q);
	gsl_vector_free(temp_q);
	gsl_vector_free(temp_p);
	gsl_vector_free(res);
	gsl_vector_free(precond);

}

void bi_conjugate_gradient(gsl_matrix *a,gsl_vector *b,gsl_vector *X,int n,double tolerance){

	int iter;
	//int n=x->size;
	double norm=0.0,norm_b=0.0;
	double rho=0.0,rho1=0.0,beta=0.0,alpha=0.0;
	double omega=0;

	gsl_vector *r;
	gsl_vector *z;
	gsl_vector *p;
	gsl_vector *precond;
	gsl_vector *r_t;
	gsl_vector *p_t;
	gsl_vector *z_t;
	gsl_vector *q;
	gsl_vector *q_t;
	gsl_vector *temp;
	
	r=gsl_vector_calloc(n);
	r_t=gsl_vector_calloc(n);
	z=gsl_vector_calloc(n);
	z_t=gsl_vector_calloc(n);
	p=gsl_vector_calloc(n);
	p_t=gsl_vector_calloc(n);
	temp=gsl_vector_calloc(n);
	q=gsl_vector_calloc(n);
	q_t=gsl_vector_calloc(n);
	precond=gsl_vector_calloc(n); 		//PRECONDITIONER
	
	preconditioner_diag(precond,a);
	//precond=preconditioner_diag(a,sizeA);	//upologismos preconditioner
	//int i;
	//for(i=0;i<n;i++){
	//	 gsl_vector_set(precond,i,1/gsl_vector_get(precond,i));	//precontitioner^-1 (M^-1) = 1/diag(A)

	//}
	

	gsl_blas_dgemv( CblasNoTrans, 1.0, a, X, 0.0, temp ); //temp=A*x
	gsl_vector_add(r,b);	//r=b
	gsl_vector_sub(r,temp);	//r=r-temp (r=b-A*x)
	gsl_vector_add(r_t,r);	//r_t=r

	norm_b=gsl_blas_dnrm2(b);
	if (norm_b == 0.0)
	  norm_b = 1;

	norm=gsl_blas_dnrm2(r)/norm_b;

	iter=0;
	while(norm>tolerance && iter<n){
		iter++;

		solveEquation(precond,r,z);	//solve Mz=r
		solveEquation(precond,r_t,z_t);	//solve Mz_t=r_t
		gsl_blas_ddot(z,r_t,&rho);
		if(fabs(rho)<EPS){
			printf("---------rho < EPS--------\n");
			break;
		}
		if(iter==1){
			gsl_vector_add(p,z);		//p=z
			gsl_vector_add(p_t,z_t);	//p bar=z_t
		}
		else{
			beta=rho/rho1;
			gsl_vector_scale(p,beta);	//beta*p
			gsl_vector_add(p,z);		//p=beta*p+z
			gsl_vector_scale(p_t,beta);	//beta*p_t
			gsl_vector_add(p_t,z_t);	//p_t=beta*p_t+z_t
		}
		rho1=rho;
		gsl_blas_dgemv( CblasNoTrans, 1.0, a,p,0.0,q);//q=A*p
		gsl_blas_dgemv( CblasTrans, 1.0, a,p_t,0.0,q_t);
		gsl_blas_ddot(p_t,q,&omega);
		if(fabs(omega)<EPS){
			printf("--------- omega < EPS --------\n"); 
			break;
		}
		alpha=rho/omega;
		gsl_blas_daxpy(alpha,p,X);
		gsl_blas_daxpy(-alpha,q,r);
		gsl_blas_daxpy(-alpha,q_t,r_t);
	}

	gsl_vector_free(r);
	gsl_vector_free(r_t);
	gsl_vector_free(temp);
	gsl_vector_free(precond);
	gsl_vector_free(z);
	gsl_vector_free(z_t);
	gsl_vector_free(p);
	gsl_vector_free(p_t);
	gsl_vector_free(q);
	gsl_vector_free(q_t);
}

void solveEquation(gsl_vector *preconditioner,gsl_vector *right,gsl_vector *left){

  int i;

  for(i=0;i<right->size;i++){
	 gsl_vector_set(left,i,gsl_vector_get(right,i)/gsl_vector_get(preconditioner,i));
  }

}

void preconditioner_diag(gsl_vector *preconditioner,gsl_matrix *matrix){
  int i;
  for(i=0;i<preconditioner->size;i++)
   	preconditioner->data[i*preconditioner->stride]=(matrix->data[i * matrix->tda + i]!=0)?matrix->data[i * matrix->tda + i]:1.0;
}

double *gslvector2double(gsl_vector *V, int size){
  
  int i;
  double *D;
  
  D = (double *)calloc(sizeof(double),size);
  
  for(i=0;i<size;i++){
    D[i] = gsl_vector_get(V,i);
  }
  return D;
}
