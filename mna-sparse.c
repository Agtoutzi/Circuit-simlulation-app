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

	//Desmeush pinakwn eksiswsewn
	//Desmeush kai arxikopoihsh twn A,B,x

	A_sparse = cs_spalloc(sizeA_sparse,sizeA_sparse,4*sizeA_sparse,1,1);
	A_sparse->nz=4*sizeA_sparse;
	sizeB = (hash_count-1)+m2;
	B_sparse = (double *)calloc(sizeB,sizeof(double));
	x_sparse = (double *)calloc(sizeB,sizeof(double));
  
	//Diatrexoume ti lista twn antistasewn kai simplirwnoume katallila to 1o n-1 * n-1 kommati tou pinaka A
	
	ResistanceT *currentR=rootR;
	k=0;
	while(currentR!=NULL){
		i=atoi(ht_get(hashtable,currentR->node1));
		j=atoi(ht_get(hashtable,currentR->node2));
		
		if(i!=0){
		  A_sparse->i[k]=i-1;
		  A_sparse->p[k]=i-1;
		  A_sparse->x[k]=1/currentR->value;
		  k++;
		}
		if(j!=0){
		  A_sparse->i[k]=j-1;
		  A_sparse->p[k]=j-1;
		  A_sparse->x[k]=1/currentR->value;
		  k++;
		}
		if(i!=0&&j!=0){
			A_sparse->i[k]=i-1;
			A_sparse->p[k]=j-1;
			A_sparse->x[k]=-1/currentR->value;
			k++;
			A_sparse->i[k]=j-1;
			A_sparse->p[k]=i-1;
			A_sparse->x[k]=-1/currentR->value;
			k++;
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
		  A_sparse->i[k]=n-1+b;
		  A_sparse->p[k]=i-1;
		  A_sparse->x[k]=1.000;
		  k++;
		  A_sparse->i[k]=i-1;
		  A_sparse->p[k]=n-1+b;
		  A_sparse->x[k]=1.000;
		  k++;
		}
		if(j!=0){
		  A_sparse->i[k]=n-1+b;
		  A_sparse->p[k]=j-1;
		  A_sparse->x[k]=-1.000;
		  k++;
		  A_sparse->i[k]=j-1;
		  A_sparse->p[k]=n-1+b;
		  A_sparse->x[k]=-1.000;
		  k++;
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
		  A_sparse->i[k]=n-1+b;
		  A_sparse->p[k]=i-1;
		  A_sparse->x[k]=1.000;
		  k++;
		  A_sparse->i[k]=i-1;
		  A_sparse->p[k]=n-1+b;
		  A_sparse->x[k]=1.000;
		  k++;
		}
		if(j!=0){
		  A_sparse->i[k]=n-1+b;
		  A_sparse->p[k]=j-1;
		  A_sparse->x[k]=-1.000;
		  k++;
		  A_sparse->i[k]=j-1;
		  A_sparse->p[k]=n-1+b;
		  A_sparse->x[k]=-1.000;
		  k++;
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

	if(ITER==0){
	  S=cs_sqr(2,C_sparse,0);
	  N=cs_lu(C_sparse,S,1);
	  cs_spfree(C_sparse);
	}
	if(dc_sweep==0){
	  if (ITER == 0){
	    cs_ipvec(N->pinv, B_sparse, x_sparse, sizeA);
	    cs_lsolve(N->L, x_sparse);
	    cs_usolve(N->U, x_sparse);
	    cs_ipvec(S->q, x_sparse, B_sparse, sizeA);
	  }else{
//	    bi_conjugate_gradient(A,B,x,sizeA,itol_value);
	  }
	
	  printf("X vector \n");
	  for(i=0;i<sizeB;i++){
	    printf(" %.6lf ",B_sparse[i]);
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

		    B_sparse[sweep_source-1]=current_value;
		    if(ITER == 0){
		      cs_ipvec(N->pinv, B_sparse, x_sparse, sizeA);
		      cs_lsolve(N->L, x_sparse);
		      cs_usolve(N->U, x_sparse);
		      cs_ipvec(S->q, x_sparse, B_sparse, sizeA);
		    }else{
//			bi_conjugate_gradient(A,B,x,sizeA,itol_value);
		    }
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
		}else{				//pigi reumatos
		  //Anairesi twn praksewn + kai - apo tin arxiki timi tis pigis ston pinaka B
		  //kai praksi + kai - me to start_value
		  if(sweep_posNode!=0){
		    B_sparse[sweep_posNode-1]+=sweep_value_I-start_value;
		  }
		  if(sweep_negNode!=0){
		    B_sparse[sweep_negNode-1]-=sweep_value_I+start_value;
		  }
		  
		  for(current_value=start_value;current_value<=end_value+sweep_step;current_value+=sweep_step){
		    
		  if(ITER == 0){
		      cs_ipvec(N->pinv, B_sparse, x_sparse, sizeA);
		      cs_lsolve(N->L, x_sparse);
		      cs_usolve(N->U, x_sparse);
		      cs_ipvec(S->q, x_sparse, B_sparse, sizeA);
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

		    for(i=0;i<plot_size;i++){	//Gemisma twn arxeiwn
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
void solve_spdSparse(){
  	
	int i;
	double current_value;
	FILE *fp;
	char filename[30];
	
	if(ITER==0){
		//cholesky decomposition
		S=cs_schol(1, C_sparse);
		N=cs_chol(C_sparse, S);
		cs_spfree(C_sparse);	
	}
	if(dc_sweep==0){
		if(ITER==0){	
		  cs_ipvec(S->pinv, B_sparse, x_sparse, sizeA);
		  cs_lsolve(N->L, x_sparse);
		  cs_ltsolve(N->L, x_sparse);
		  cs_pvec(S->pinv, x_sparse, B_sparse, sizeA);			//solve cholesky
		}
		else{
			
//			conjugate_gradient(A,B,x,sizeA,itol_value);
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

		    B_sparse[sweep_source-1]=current_value;
		    if(ITER==0){		
		      cs_ipvec(S->pinv, B_sparse, x_sparse, sizeA);
		      cs_lsolve(N->L, x_sparse);
		      cs_ltsolve(N->L, x_sparse);
		      cs_pvec(S->pinv, x_sparse, B_sparse, sizeA);			//solve cholesky
		    }
		    else{
			
//			conjugate_gradient(A,B,x,sizeA,itol_value);		

//Arxiki proseggish h lush ths prohgoumenhs.Mhpws exoume provlhma dioti sto sweep 8a dhlwnoume polles fores tous pinakes??'H oxi gt einai local gia ka8e klhsh ths sunarthshs?tzampa overhead.Persinoi dhlwnan sunexeia
		    }
		    
		    for(i=0;i<plot_size;i++){	//Gemisma twn arxeiwn
		      strcpy(filename,"./PlotFiles/Results-Node ");
		      strcat(filename,plot_names[i]);
		      fp = fopen(filename, "a");
		      if (fp == NULL) {
			printf("Can't open output file %s!\n",filename);
			return;
		      }
		      fprintf(fp,"Sweep source voltage at %lf:\tNode %s value:\t%lf\n",current_value, plot_names[i],B_sparse[plot_nodes[i]-1]);
		      fflush(fp);
		      fclose(fp);
		    }
		  }
		}else{
		  //Anairesi twn praksewn + kai - apo tin arxiki timi tis pigis ston pinaka B
		  //kai praksi + kai - me to start_value
		  if(sweep_posNode!=0){
		    B_sparse[sweep_posNode-1]+=sweep_value_I-start_value;
		  }
		  if(sweep_negNode!=0){
		    B_sparse[sweep_negNode-1]-=sweep_value_I-start_value;
		  }
		  
		  for(current_value=start_value;current_value<=end_value+sweep_step;current_value+=sweep_step){

		   if(ITER==0){
		      cs_ipvec(S->pinv, B_sparse, x_sparse, sizeA);
		      cs_lsolve(N->L, x_sparse);
		      cs_ltsolve(N->L, x_sparse);
		      cs_pvec(S->pinv, x_sparse, B_sparse, sizeA);			//solve cholesky
		   }
		   else{
			
//			conjugate_gradient(A,B,x,sizeA,itol_value);
			//Arxiki proseggish h lush ths prohgoumenhs
		   }
		    
		   
		   //Allagi twn timwn ston pinaka B gia to epomeno vima tou sweep
		   if(sweep_posNode!=0){
		     B_sparse[sweep_posNode-1]-=sweep_step;
		    }
		   if(sweep_negNode!=0){
		     B_sparse[sweep_negNode-1]+=sweep_step;
		   }

		    for(i=0;i<plot_size;i++){	//Gemisma twn arxeiwn
		      strcpy(filename,"./PlotFiles/Results-Node ");
		      strcat(filename,plot_names[i]);
		      fp = fopen(filename, "a");
		      if (fp == NULL) {
			printf("Can't open output file %s!\n",filename);
			return;
		      }
		      fprintf(fp,"Sweep source current at %lf:\tNode %s value:\t%.6e\n",current_value, plot_names[i],B_sparse[plot_nodes[i]-1]);
		      fflush(fp);
		      fclose(fp);
		    }
		  }
		  printf("\n");
		}
	}

}



void compute_precontitioner_from_sparce_matrix(const cs *A, double *preconditioner)
{
    int p, j, n, *Ap, *Ai ;
    double *Ax ;
   
    n = A->n ; Ap = A->p ; Ai = A->i ; Ax = A->x ;
    for (j = 0 ; j < n ; j++)
    {
        for (p = Ap [j] ; p < Ap [j+1] ; p++)
        {
            if (j == Ai[p])  //me ton rapt eixame pei j==p
	    {
		    if ( Ax[p] !=0 )
			  preconditioner[j] = 1/Ax[p];
		    else
		    {
			  preconditioner[j]=1.0;
		    }
	    }
        }
    }
   
}

void preconditioner_solve_for_sparce_matrix(const double *r, const double *preconditioner, double *z, int n)
{
    int i=0;
  
    for(i=0;i<n;i++)
    {
	  z[i]=preconditioner[i]*r[i]; 
    }
}


void mul_sparce_matrix_with_vector(const cs *A, const double *x , double *y ,  int reverse_sparce )
{
    int p,i, j, n, *Ap, *Ai ;
    double *Ax ;
    
    n = A->n ; Ap = A->p ; Ai = A->i ; Ax = A->x ;
    
    for (j = 0 ; j < n ; j++)  // e3w apth for!!
    {
	y[ j ]=0.0;
    }
    
    for (j = 0 ; j < n ; j++)
    {
       
        for (p = Ap [j] ; p < Ap [j+1] ; p++)
	{
	    if ( reverse_sparce )
	    {
		y[i] = y[i] + A->x[p]*x[ A->i[p] ];
	    }
	    else
	    {
		y[ Ai[p] ] += Ax[ p ] * x[ j ];
	    }
        }
    }
}

 
double *bi_conjugate_gradient_with_sparce_matrix( const cs *A, int n, double *b , double itol , double *x )
{
      

	int iter=0,i,j;
	double   k;
	double  *r1=NULL , *r2=NULL, *p1=NULL, *p2=NULL, *z1=NULL,*z2=NULL   ,*q1=NULL,*q2=NULL;
	double *preconditioner=NULL;
	double rho=0.0, rho1=0.0, beta=0.0,  eps=1e-20 ,omega=0.0,norm_r=0.0, norm_b=0.0,alpha=0.0;
	double *Ax=NULL;
	int t1,t2;
	  
	//printf("solve system with bi_conjugate_gradient_with_sparce_matrix\n");
	
	preconditioner = (double*)malloc( sizeof(double) * n );
	for ( i=0 ; i< n ; i++ )
	{
	      preconditioner[i]=1.0;
	      x[i]=1.0;
	 }
	
	if ( !x )
	{
	      x  = (double*)malloc( sizeof(double) * n );
	      for ( i=0 ; i< n ; i++ )
	      {
		    x[i]=1.0;
	      }
	}

	r1 = (double*)malloc( sizeof(double) * n );
	r2 = (double*)malloc( sizeof(double) * n );
	p1 = (double*)malloc( sizeof(double) * n );
	p2 = (double*)malloc( sizeof(double) * n );
	q1 = (double*)malloc( sizeof(double) * n );
	q2 = (double*)malloc( sizeof(double) * n );
	z1 = (double*)malloc( sizeof(double) * n );
	z2 = (double*)malloc( sizeof(double) * n );
	
	//Ax=preconditioner_solve ( a , x , n );
	Ax = (double*)malloc( sizeof(double) * n );	
	mul_sparce_matrix_with_vector( A, x , Ax , 0 );
	
	for ( i=0 ; i< n ; i++ )
	{
		//x[i]=0.0;
		p1[i]=0.0;
		p2[i]=0.0;
		q1[i]=0.0;
		q2[i]=0.0;
		
		z1[i]=0.0;
		z2[i]=0.0;
		
		r2[i]=b[i] - Ax[i];
		r1[i]=r2[i];
		
		/*
		for(j=0;j<n;j++)
		{
	    		preconditioner[i][j] = 0.0;
		}
		if ( a[i][i]!=0 )
		{
		    preconditioner[i][i] = 1.0 / a[i][i];
		}
		else
		{
		    preconditioner[i][i]=1.0 ;
		}
		*/
	}
	compute_precontitioner_from_sparce_matrix( A, preconditioner);
	
	
	norm_r = norm( r1 , n );
    	norm_b = norm( b , n );

 	if (norm_b==0.0)
    	{
		norm_b=1.0;
    	}
    	
	while( (norm_r / norm_b) > itol  )
    	{ 
		
		iter++;
		
		//z1=preconditioner_solve ( preconditioner , r1 , n );
		//z2=preconditioner_solve ( preconditioner , r2 , n );
		preconditioner_solve_for_sparce_matrix( r1, preconditioner, z1,  n );
		preconditioner_solve_for_sparce_matrix( r2, preconditioner, z2,  n );
		
		//rho=vector_mul_vector( z1 , r2 , n );
		scalar_product(z1,r2,&rho,n);
		if( fabs(rho) < eps )
		{
			printf("FAILURE RHO LESS THAN EPS\n");
			return;
		}
		if(iter == 1)
		{
			for ( i=0;i<n;i++)
			{
				p1[i]=z1[i];
				p2[i]=z2[i];
			}
		}
		else
		{

			beta=rho/rho1;
			
			for ( i=0;i<n;i++)
			{
				p1[i]=z1[i]+beta*p1[i];
				p2[i]=z2[i]+beta*p2[i];
			}
		}
		rho1=rho;
		//q1=preconditioner_solve (a,p1,n);
		mul_sparce_matrix_with_vector( A , p1 , q1 , 0 );
		
		//q2=preconditioner_solve (a,p2,n);
		mul_sparce_matrix_with_vector( A , p2 , q2 , 0 );

		
		for(i=0; i<n; i++){

		    printf("q1[%d]=%lf\n",i,q1[i]);
		}
		
		for(i=0; i<n; i++){

		    printf("q2[%d]=%lf\n",i,q2[i]);
		}
		
		//omega=vector_mul_vector(p2,q1,n);
		scalar_product(p1,q1,&omega,n);
		if( fabs(omega) < eps )
		{
			printf("FAILURE OMEGA LESS THAN EPS\n");
			return;		
		}
		alpha=rho/omega;
		printf("alpha=%lf\n",alpha);
		for (i=0;i<n;i++){
			x[i] = x[i]  + alpha*p1[i];
			r1[i]= r1[i] - alpha*q1[i];
			r2[i]= r2[i] - alpha*q2[i];
		}

		norm_r = norm( r1 , n );

		for(i=0; i<n; i++){

		    printf("r[%d]=%lf\n",i,r1[i]);
		}
		norm_b = norm( b , n );
		for(i=0; i<n; i++){

		    printf("b[%d]=%lf\n",i,b[i]);
		}
		
		if (norm_b==0.0)
		{
	    		norm_b=1.0;
		}
	  
		for(i=0; i<Komvoi+M2; i++){
		  printf("to x einai %lf\n",x[i]);

		}
		k=norm_r / norm_b;
		printf("\n\n\n\n\nnormr/normb=%lf  norm_r=%lf, norm_b =%lf\n",k,norm_r,norm_b);
		
	}   //end while	
	
	free( preconditioner );
	free ( r1 );
	free ( r2 );
	free ( p1 );
	free ( p2 );
	free ( q1 );
	free ( q2 );
	free ( z1 );
	free ( z2 ); 
	
	return x;
}

