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

	p=gsl_permutation_alloc ((hash_count-1)+m2);
	gsl_permutation_init(p);
	if(ITER==0){
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
	}
	if(dc_sweep==0){
	  if (ITER == 0){
		gsl_linalg_LU_solve(A,p,B,x);			//solve LU
	  }else{
	    bi_conjugate_gradient(A,B,x,sizeA,itol_value);
	  }
	
	  printf("X vector \n");
	  for(i=0;i<sizeB;i++){
	    printf(" %.6lf ",gsl_vector_get(x,i));
	  }
	  printf("\n");
	}else{
	  for(i=0;i<plot_size;i++){	//Adeiasma twn arxeiwn
	    strcpy(filename,"./PlotFiles/Results-Node ");
	    strcat(filename,plot_names[i]);
	    fp = fopen(filename, "w");
	    fflush(fp);
	    fclose(fp);
	  }
		if(sweep_source!=-1){		//pigi tashs
		  for(current_value=start_value;current_value<=end_value+sweep_step;current_value+=sweep_step){

		    gsl_vector_set(B,sweep_source-1,current_value);
		    if(ITER == 0){
			gsl_linalg_LU_solve(A,p,B,x);
		    }else{
			bi_conjugate_gradient(A,B,x,sizeA,itol_value);
		    }
		    for(i=0;i<plot_size;i++){	//Gemisma twn arxeiwn
		      strcpy(filename,"./PlotFiles/Results-Node ");
		      strcat(filename,plot_names[i]);
		      fp = fopen(filename, "a");
		      if (fp == NULL) {
			printf("Can't open output file %s!\n",filename);
			return;
		      }
		      fprintf(fp,"Sweep source voltage at %lf:\tNode %s value:\t%lf\n",current_value, plot_names[i],gsl_vector_get(x,plot_nodes[i]-1));
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

		    for(i=0;i<plot_size;i++){	//Gemisma twn arxeiwn
		      strcpy(filename,"./PlotFiles/Results-Node ");
		      strcat(filename,plot_names[i]);
		      fp = fopen(filename, "a");
		      if (fp == NULL) {
			printf("Can't open output file %s!\n",filename);
			return;
		      }
		      fprintf(fp,"Sweep source current at %lf:\tNode %s value:\t%.6e\n",current_value, plot_names[i],gsl_vector_get(x,plot_nodes[i]-1));
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
	    strcpy(filename,"./PlotFiles/Results-Node ");
	    strcat(filename,plot_names[i]);
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
		      strcpy(filename,"./PlotFiles/Results-Node ");
		      strcat(filename,plot_names[i]);
		      fp = fopen(filename, "a");
		      if (fp == NULL) {
			printf("Can't open output file %s!\n",filename);
			return;
		      }
		      fprintf(fp,"Sweep source voltage at %lf:\tNode %s value:\t%lf\n",current_value, plot_names[i],gsl_vector_get(x,plot_nodes[i]-1));
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
		      strcpy(filename,"./PlotFiles/Results-Node ");
		      strcat(filename,plot_names[i]);
		      fp = fopen(filename, "a");
		      if (fp == NULL) {
			printf("Can't open output file %s!\n",filename);
			return;
		      }
		      fprintf(fp,"Sweep source current at %lf:\tNode %s value:\t%.6e\n",current_value, plot_names[i],gsl_vector_get(x,plot_nodes[i]-1));
		      fflush(fp);
		      fclose(fp);
		    }
		  }
		  printf("\n");
		}
	}
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

//	int i;
	
      	precond=preconditioner_diag(a,sizeA);
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
		
		gsl_blas_dcopy(r,z);						//gia na min allaksei o r
		gsl_vector_mul(z,precond);					
		
		/*printf("\n");
		
		printf("M-1 * r \n");
		for(i=0;i<n;i++){
			printf(" %.6lf ",gsl_vector_get(z,i));
				
		}*/

		gsl_blas_ddot(r,z,&rho);					//r^T * Z
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
		gsl_blas_dgemv(CblasNoTrans,1,a,p,0.0,q);				//q=A*p 
	
		/*printf("\n");
		printf("Q vector \n");
		for(i=0;i<n;i++){
			printf(" %.6lf ",gsl_vector_get(q,i));
	
		}
		printf("\n");
		*/
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
}

void bi_conjugate_gradient(gsl_matrix *a,gsl_vector *b,gsl_vector *X,int n,double tolerance){

//	int i;
//	int j;
	double EPS = 1e-12;
	double rho,rho1,alpha,beta,omega;
	gsl_vector *r;
	gsl_vector *z;
	gsl_vector *p;
	gsl_vector *q;
	gsl_vector *precond;
	gsl_vector *temp_p;
	gsl_vector *temp_q,*temp_qt;
	gsl_vector *res;
	
	//transport
	gsl_vector *r_t,*z_t,*q_t,*p_t;
	gsl_matrix *aT;
	
	r = gsl_vector_calloc(n);
	z = gsl_vector_calloc(n);
	p = gsl_vector_calloc(n);
	q = gsl_vector_calloc(n);
	precond = gsl_vector_calloc(n);
	temp_p = gsl_vector_calloc(n);
	temp_q = gsl_vector_calloc(n);
	res = gsl_vector_calloc(n);
	aT = gsl_matrix_calloc(n,n);
	
	//transport
	r_t = gsl_vector_calloc(n);
	z_t = gsl_vector_calloc(n);
	p_t = gsl_vector_calloc(n);
	q_t = gsl_vector_calloc(n);
	temp_qt = gsl_vector_calloc(n);
	
	precond=preconditioner_diag(a,sizeA);
	 	
	/*printf("PRECONTITIONER 1/Diag \n");
	for(i=0;i<n;i++){
 		printf(" %.6lf ",gsl_vector_get(precond,i));
	
	}*/
	
	gsl_blas_dcopy(X,res);						//Store X sto temp res

	//r=b-Ax
	gsl_blas_dcopy(b,r);	
	gsl_blas_dgemv(CblasNoTrans,1,a,res,0.0,p);			//prosorina p=A*x 	
	gsl_vector_sub(r,p);	
	
	//transport r_t = r	
	gsl_blas_dcopy(r,r_t);
	
	int iter=0;
	
	double r_norm = gsl_blas_dnrm2(r);
	double b_norm = gsl_blas_dnrm2(b);
	if(!b_norm){b_norm = 1;}


	while(((r_norm/b_norm) > tolerance) && (iter < n)){
		iter++;
		gsl_blas_dcopy(r,z);					//gia na min allaksei o r
		gsl_vector_mul(z,precond);				


		// transport
		// z_t = MNA * z_t
		gsl_blas_dcopy(r_t,z_t);
		gsl_vector_mul(z_t,precond);

/*		printf("Vector z:\n");
		for(i=0;i<n;i++){
		 printf("%.9lf \n",gsl_vector_get(z,i));
		}
		printf("\n");

		
		printf("Vector r_t:\n");
		for(i=0;i<n;i++){
		 printf("%.9lf \n",gsl_vector_get(r_t,i));
		}
		printf("\n");
*/
		gsl_blas_ddot(z,r_t,&rho);				//r^T * Z
//		printf("RHO:%e\n",rho);
//		printf("yes rho: %f\n",rho);

		if(fabs(rho)<EPS){ printf("---------rho < EPS--------\n"); exit(0);}
		if (iter == 1){
			gsl_blas_dcopy(z,p);
			gsl_blas_dcopy(z_t,p_t);
		}
	
		else{
			beta=rho/rho1;
			
			gsl_blas_dscal(beta,p);
			gsl_blas_daxpy(1,z,p);	
			
			gsl_blas_dscal(beta,p_t);
			gsl_blas_daxpy(1,z_t,p_t);
			
		}

		gsl_matrix_memcpy(aT,a);
		gsl_matrix_transpose(aT);
/*		printf("aT:\n");
		for(i=0;i<n;i++){
		  for(j=0;j<n;j++){
		    printf("%.9lf ",gsl_matrix_get(aT,i,j));
		  }
		  printf("\n");
		}
		printf("\n");
*/		rho1=rho;
		gsl_blas_dgemv(CblasNoTrans,1,a,p,0.0,q);			//q=A*p 
		
		gsl_blas_dgemv(CblasNoTrans,1,aT,p_t,0.0,q_t); 		//q_t = trans(A)*p_t
		
		
		gsl_blas_ddot(p_t,q,&omega);				//omega = trasn(p_t)*q
//		printf("omega: %e p_t: %e q: %e\n",omega, p_t, q);
		if(fabs(omega)<EPS){printf("--------- omega < EPS --------\n"); exit(0);}
		alpha = rho/omega;
			
		gsl_blas_dcopy(p,temp_p);				//x=x+alpha*p
		gsl_blas_dscal(alpha,temp_p);
		gsl_blas_daxpy(1,temp_p,res);

		gsl_blas_dcopy(q,temp_q);				//r=r-alpha*q
		gsl_blas_dscal(-alpha,temp_q);
		gsl_blas_daxpy(1,temp_q,r);

		gsl_blas_dcopy(p,temp_qt);				//r_t = r_t-alpha*q_t
		gsl_blas_dscal(-alpha,temp_qt);
		gsl_blas_daxpy(1,temp_qt,r_t);
		
		r_norm = gsl_blas_dnrm2(r);				//new r norm

	}
	gsl_blas_dcopy(res,X);						//Restore res back to X
}

gsl_vector* preconditioner_diag(gsl_matrix *A,int n){
  
	gsl_vector *precond;
	precond = gsl_vector_calloc(n);
	
	gsl_vector_view d;						//gia na parw tin diagwnio

	d=gsl_matrix_diagonal(A);					//d=diagwnios tou A
	

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


	for(i=0;i<n;i++){
		 gsl_vector_set(precond,i,1.0/gsl_vector_get(precond,i));	//precontitioner^-1 (M^-1) = 1/diag(A)

	}

	return precond;

}
