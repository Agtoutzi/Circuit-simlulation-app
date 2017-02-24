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

void solve(){

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
	  for(i=0;i<plot_size;i++){	//Adeiasma twn arxeiwn
	    sprintf(str, "%d", plot_nodes[i]);
	    strcpy(filename,"Results-Node ");
	    strcat(filename,str);
	    fp = fopen(filename, "w");
	    fflush(fp);
	    fclose(fp);
	  }
		if(sweep_source!=-1){		//pigi tashs
		  for(current_value=start_value;current_value<=end_value+sweep_step;current_value+=sweep_step){

		    gsl_vector_set(B,sweep_source-1,current_value);
		    gsl_linalg_LU_solve(A,p,B,x);
		    
		    for(i=0;i<plot_size;i++){	//Gemisma twn arxeiwn

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
		}else{				//pigi reumatos
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

void solve_spd(){
	
	int i,j;
	double current_value;
	FILE *fp;
	char filename[30];
	char str[12];
	
	if(ITER==0){
		gsl_linalg_cholesky_decomp(A);		//cholesky decomposition
	
		printf("CHOLESKY matrix\n ");
		for(i=0;i<sizeA;i++){
	 		for(j=0;j<sizeA;j++){
				printf(" %.6lf ",gsl_matrix_get (A, i, j));
	  		}
			printf("\n");
		}	
	}
	if(dc_sweep==0){
		if(ITER==0){
			gsl_linalg_cholesky_solve(A,B,x);			//solve cholesky
		}
		else{
			
			conjugate_gradient(A,B,x,sizeA,itol_value);
		}								//solve with Conjugated Gradient
		printf("X vector \n");
		for(i=0;i<sizeB;i++){
			printf(" %.15lf ",gsl_vector_get(x,i));
		}
		printf("\n");
	}else{
	  for(i=0;i<plot_size;i++){	//Adeiasma twn arxeiwn
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
		    if(ITER==0){
			gsl_linalg_cholesky_solve(A,B,x);			//solve cholesky
		    }
		    else{
			
			conjugate_gradient(A,B,x,sizeA,itol_value);		//Arxiki proseggish h lush ths prohgoumenhs.Mhpws exoume provlhma dioti sto sweep 8a dhlwnoume polles fores tous pinakes??'H oxi gt einai local gia ka8e klhsh ths sunarthshs?tzampa overhead.Persinoi dhlwnan sunexeia
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

void conjugate_gradient(gsl_matrix *a,gsl_vector *b,gsl_vector *X,int n,double tolerance){	//+O PRECONDITIONER SAN ORISMA

	//DOULEUOUN GIA APLOUS PINAKES..MHPWS OTAN EXOUME ITER NA TOUS DHLWNOUME WS APLOUS??
	/*int i,j,iter;
	double rho,rho1,alpha,beta,omega;
	
	double r[n]; 
	double z[n], temp_z[n];
	double q[n], temp_q[n]; 
	double p[n], temp_p[n];
	double res[n];

	double D[n*n];	//Preconditioner
	//double *x;
	//x = *res = (double *)malloc(n*sizeof(double));

	//Initializations		
	memset(D, 0, n*n*sizeof(double));
	memset(r, 0, n*sizeof(double));
	memset(z, 0, n*sizeof(double));
	memset(temp_z, 0, n*sizeof(double));
	memset(q, 0, n*sizeof(double));
	memset(temp_q, 0, n*sizeof(double));
	memset(p, 0, n*sizeof(double));
	memset(temp_p, 0, n*sizeof(double));

	/* Preconditioner (TODO 3exoristi synartisi sto mellon */
	/*double max;
	
	for(i = 0; i < n; i++){						//OK
		max = fabs(a[i*n]);
		for(j = 0; j < n; j++)
			if(fabs(a[i*n+j]) > max)
				max = a[i*n+j];
		D[i*n+i] = max;
	}		

	cblas_dcopy (n, X, 1, res, 1);					

	cblas_dcopy (n, b, 1, r, 1);					
	double r_norm = cblas_dnrm2 (n, r, 1);
	double b_norm = cblas_dnrm2 (n, b, 1);
	if(!b_norm)
		b_norm = 1;

	iter = 0;	
	
	while( r_norm/b_norm > tolerance && iter < n )
	{
		iter++;

		//SOLVE Mz = r;	-> z = inv(M)*r
		cblas_dcopy (n, r, 1, z, 1);			
		cblas_dtrsv (CblasRowMajor, CblasUpper, CblasNoTrans, CblasNonUnit, n, D, n, z, 1);	// z = MNA*z

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
		cblas_dgemv (CblasRowMajor,CblasNoTrans,n,n,1,a,n,p,1,0,q,1);

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
	cblas_dcopy (n, res, 1, X, 1);
*/
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

	gsl_vector_view d;						//gia na parw tin diagwnio

	d=gsl_matrix_diagonal(a);					//d=diagwnios tou A
	

	int i;
	
	for(i=0;i<n;i++){
		if(gsl_vector_get(&d.vector,i)==0){
			gsl_vector_set(&d.vector,i,1);			//an kapoio stoixeio ths diagwniou einai 0 tote to 8etoume 1
		}
	}

	gsl_blas_dcopy(&d.vector,precond);				//gia na min allaksei h diagwnios tou a to antigrafw allou
	
	/*printf("Diag \n");
	for(i=0;i<n;i++){
		printf(" %.6lf ",gsl_vector_get(precond,i));
	
	}*/

	printf("\n");
	for(i=0;i<n;i++){
		 gsl_vector_set(precond,i,1/gsl_vector_get(precond,i));	//precontitioner^-1 (M^-1) = 1/diag(A)

	}

	/*printf("\n");
	printf("PRECONTITIONER 1/Diag \n");
	for(i=0;i<n;i++){
		printf(" %.6lf ",gsl_vector_get(precond,i));
	
	}*/

	gsl_blas_dcopy(X,res);						//Store X sto temp res...Isws na mh xreiazetai!!!

	//r=b-Ax
	gsl_blas_dcopy(b,r);	
	gsl_blas_dgemv(CblasNoTrans,1,a,res,1,p);			//prosorina p=A*x 	
	gsl_vector_sub(r,p);	
	
	/*printf("R vector \n");
	for(i=0;i<n;i++){
		printf(" %.6lf ",gsl_vector_get(r,i));
	
	}
	*/
	int iter=0;
	
	double r_norm = gsl_blas_dnrm2(r);
	double b_norm = gsl_blas_dnrm2(b);
	if(!b_norm)
		b_norm = 1;

	while( r_norm/b_norm > tolerance && iter < n ){

		iter++;
		gsl_blas_dcopy(r,z);					//gia na min allaksei o r
		gsl_vector_mul(z,precond);				//douleuei
		
		/*printf("\n");
		
		printf("M-1 * r \n");
		for(i=0;i<n;i++){
			printf(" %.6lf ",gsl_vector_get(z,i));
				
		}*/

		gsl_blas_ddot(r,z,&rho);				//r^T * Z
		//printf("RHO:%lf\n",rho);

		if(iter==1){
			gsl_blas_dcopy(z,p);			
		}
	
		else{
			beta=rho/rho1;
			gsl_blas_dscal(beta,p);
			gsl_blas_daxpy(1,z,p);	
		}
		rho1=rho;
		gsl_blas_dgemv(CblasNoTrans,1,a,p,1,q);			//q=A*p douleuei
	
		/*printf("\n");
		printf("Q vector \n");
		for(i=0;i<n;i++){
			printf(" %.6lf ",gsl_vector_get(q,i));
	
		}
		printf("\n");
		*/
		gsl_blas_ddot(p,q,&alpha);				//p^T * q
		alpha=rho/alpha;					//alpha=rho/p^T*q
				
				
		gsl_blas_dcopy(p,temp_p);				//x=x+alpha*p
		gsl_blas_dscal(alpha,temp_p);
		gsl_blas_daxpy(1,temp_p,res);	

		gsl_blas_dcopy(q,temp_q);				//r=r-alpha*q
		gsl_blas_dscal(-alpha,temp_q);
		gsl_blas_daxpy(1,temp_q,r);	
		
		r_norm = gsl_blas_dnrm2(r);				//new r norm

	}
	gsl_blas_dcopy(res,X);						//Restore res back to X
}
