#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "CircLib.h"
#include "hash.h"
#include "mna.h"
#include "mna-sparse.h"
#include "options.h"
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_cblas.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>
#include "transient.h"
#include "csparse.h"
#define pi 3.14159265359

void transient(){

	double TRAN_time_step;
	gsl_vector *temp_e;
	int i,j;
	double *e_sparse;
	double *e_prev_sparse;
	gsl_vector *e;
	gsl_vector *e_prev;

	if(SPARSE){
	  e_sparse=calloc(sizeB,sizeof(double));
	  e_prev_sparse=calloc(sizeB,sizeof(double));
	  initPlotFiles("Sparse Results");
	}else{
	  e = gsl_vector_calloc(sizeB);
	  e_prev = gsl_vector_calloc(sizeB);
	  initPlotFiles("Dense Results");
	}

	if(SPARSE){
	  for(i = 0; i < sizeB; ++i){
	    e_prev_sparse[i] = e_sparse[i] = B_sparse[i];
	  }
	}else{
	  gsl_blas_dcopy(B,e);
	  gsl_blas_dcopy(B,e_prev);
	}

	if(SPARSE){
	  
	  //TRAPEZODIAL
	  if(METHOD==0){
	    C_sparse = cs_add(C_sparse, E_sparse,1, 2/time_step);	//E_sparse=G-2/h*E=G-2/H*E
	    E_sparse =cs_add(C_sparse,E_sparse,1,-4/time_step);
	  }else{
	    E_sparse =cs_add(E_sparse,E_sparse,0,1/time_step); 		//E_sparse=1/h*E=1/h*C
	    C_sparse = cs_add (C_sparse, E_sparse, 1, 1);
	  }
	}else{

	  //TRAPEZODIAL
	  if(METHOD==0){
	    for(i = 0; i < sizeA; i++)
	      for(j = 0; j < sizeA; j++){
		gsl_matrix_set(A,i,j,gsl_matrix_get(A,i,j) + (2/time_step)*gsl_matrix_get(C,i,j));					
		gsl_matrix_set(C,i,j,gsl_matrix_get(A,i,j) - (4/time_step)*gsl_matrix_get(C,i,j));	//C=G-(2/h)*C
	      }
	  }else{
	    for(i = 0; i < sizeA; i++)
	      for(j = 0; j < sizeA; j++){
		gsl_matrix_set(C,i,j,(1/time_step)*gsl_matrix_get(C,i,j));		//C=1/h*C
		gsl_matrix_set(A,i,j,gsl_matrix_get(A,i,j) + gsl_matrix_get(C,i,j));	//A=G+1/h*C=A+1/h*C	
	      }
	  }
	}

	for(TRAN_time_step=0; TRAN_time_step<=end_time; TRAN_time_step+=time_step){
	  printf("time:%g\n",TRAN_time_step);
	  if(SPARSE){
	    for(i = 0; i < sizeB; ++i){
	      e_prev_sparse[i] = e_sparse[i];
	    }
	  }else{
	    gsl_blas_dcopy(e,e_prev);
	  }

	  //COMPUTE NEW e(tk)
	  temp_e=compute_E(TRAN_time_step);

	  if(SPARSE){
	    free(e_sparse);
	    e_sparse=gslvector2double(temp_e,sizeB);
	  }else{
	    gsl_blas_dcopy(temp_e,e);
	  }

	  gsl_vector_free(temp_e);
	  
	  if(METHOD == 1){
	    printf("BE\n");		
	    if(SPARSE){
	      TRAN_backward_euler_sparse(x_sparse,E_sparse,e_sparse);
/// 	      for(i=0;i<sizeB;i++){						//Efoson energopoih8oun mas vgazoun diaforetika apotelesmata se ka8e time_step alla argei h ektelesh
/// 		x_sparse[i]=0.0;
/// 	      }
	      memset(x_sparse,0.0,sizeB*(sizeof(double)));
	    }else{
	      TRAN_backward_euler(x, C,e);
 	      for(i=0;i<sizeB;i++){
		gsl_vector_set(x,i,0.0);
 	      }
	    }
	  }else{
	    printf("TRAP\n");
	    if(SPARSE){
	      TRAN_trapezoidial_sparse(x_sparse,E_sparse,e_sparse,e_prev_sparse);
	      memset(x_sparse,0.0,sizeB*(sizeof(double)));
	    }else{
	      TRAN_trapezoidial(x, C, e, e_prev);
	      for(i=0;i<sizeB;i++){						//Efoson energopoih8oun mas vgazoun diaforetika apotelesmata se ka8e time_step alla argei h ektelesh
 		gsl_vector_set(x,i,0.0);
 	   	 }
	    }
	  }
	  
	  /*EPILUSH SUSTHMATOS*/
	  if(SPARSE==0){
	    if(SPD==0)
	      solve();
	    else
	      solve_spd();
	  }else{
	    if(SPD==0)
	      solveSparse();
	    else	
	      solve_spdSparse(); 
	  }
//	  getchar();
	}
	if(SPARSE){
	  free(e_sparse);
	  free(e_prev_sparse);	
	}
	else{
	  gsl_vector_free(e);
	  gsl_vector_free(e_prev);
	}

}

void TRAN_backward_euler_sparse(double *x_sparse, cs *E_sparse,double *e){

	printf("BE SPARSE\n");
	int i;
	double temp[sizeA];
	
	memset(temp, 0, sizeA*sizeof(double));
	
	cs_gaxpy (E_sparse, x_sparse, temp);
	
	for(i=0;i<sizeB;i++){
		B_sparse[i]=e[i]+temp[i];
	}
	

}

void TRAN_backward_euler(gsl_vector *x, gsl_matrix *C,gsl_vector *e){
	
	printf("BE DENSE\n");

	gsl_vector *temp;
	
	temp=gsl_vector_calloc(sizeB);

	gsl_blas_dgemv(CblasNoTrans,1.0,C,x,0.0,temp);	//C=C*X=(1/h)*C*x(tk-1)
	gsl_vector_add(temp,e);				//C=e(tk) + (1/h)*C*x(tk-1)
	gsl_blas_dcopy(temp,B);
	
	gsl_vector_free(temp);
}

void TRAN_trapezoidial_sparse(double *x_sparse, cs *E_sparse,double *e,double *e_prev){

	printf("TR\n");

	int i;	
	double temp[sizeA];
	memset(temp, 0, sizeA*sizeof(double));
	cs_gaxpy (E_sparse, x_sparse, temp);
	
	for(i=0;i<sizeB;i++){
		B_sparse[i]=e[i]+e_prev[i]-temp[i];
	}


}

void TRAN_trapezoidial(gsl_vector *x, gsl_matrix *C,gsl_vector *e,gsl_vector *e_prev){

	printf("TR DENSE\n");

	gsl_vector *temp_e;
	temp_e=gsl_vector_calloc(sizeB);
	gsl_vector *temp;
	temp=gsl_vector_calloc(sizeB);
		
	gsl_blas_dgemv(CblasNoTrans,1.0,C,x,0.0,temp);	//C=C*x=(G-(2/h)*C)*x(tk-1)
	gsl_vector_add(temp_e,e_prev);
	gsl_vector_add(temp_e,e);
	gsl_vector_sub(temp_e,temp);
	gsl_blas_dcopy(temp_e,B);	
	
	gsl_vector_free(temp_e);
	gsl_vector_free(temp);
}

gsl_vector *compute_E(double t){
  VoltT *currentV;
  AmperT *currentI;
  struct PWL *currPwl;
  struct PWL *prevPwl;
  gsl_vector *E;
  int i,j,k=0,b=1;
  double value,t_temp;


  E = gsl_vector_calloc(sizeA);

  currentI = rootI;
  while(currentI!=NULL){
    i = atoi(ht_get(hashtable,currentI->node1));
    j = atoi(ht_get(hashtable,currentI->node2));
    
    if(strcmp(currentI->transient_spec,"EXP")==0){
      if(t<=currentI->exp->td1){
	value = currentI->exp->i1;
      }else if(t<=currentI->exp->td2){
	value = currentI->exp->i1 + (currentI->exp->i2 - currentI->exp->i1)*(1 - exp(-(t-currentI->exp->td1)/currentI->exp->tc1));
      }else if(t<=end_time){
	value = currentI->exp->i1 + (currentI->exp->i2 - currentI->exp->i1)*(exp(-(t-currentI->exp->td2)/currentI->exp->tc2) - exp(-(t-currentI->exp->td1)/currentI->exp->tc1));
      }
    }else if(strcmp(currentI->transient_spec,"SIN")==0){
      if(t<=currentI->sin->td){
	value = currentI->sin->i1 + currentI->sin->ia*sin(2*pi*currentI->sin->ph/360);
      }else if(t<=end_time){
	value = currentI->sin->i1 + currentI->sin->ia*sin(2*pi*currentI->sin->fr*(t-currentI->sin->td)+2*pi*currentI->sin->ph/360);
      }
    }else if(strcmp(currentI->transient_spec,"PULSE")==0){
      k=(t-currentI->pulse->td)/currentI->pulse->per;
      if(k<0)k=0;
      
      t_temp=t-k*currentI->pulse->per;
      
      if(t_temp<=currentI->pulse->td){
	value = currentI->pulse->i1;
      }else if(t_temp<=currentI->pulse->td+currentI->pulse->tr){
	//linear i1->i2
	value = linear_value(currentI->pulse->td, currentI->pulse->i1, currentI->pulse->td+currentI->pulse->tr, currentI->pulse->i2, t_temp);
      }else if(t_temp<=currentI->pulse->td+currentI->pulse->tr+currentI->pulse->pw){
	value = currentI->pulse->i2;
      }else if(t_temp<=currentI->pulse->td+currentI->pulse->tr+currentI->pulse->pw+currentI->pulse->tf){
	//linear i2->i1
	value = linear_value(currentI->pulse->td+currentI->pulse->tr+currentI->pulse->pw, currentI->pulse->i2, currentI->pulse->td+currentI->pulse->tr+currentI->pulse->pw+currentI->pulse->tf, currentI->pulse->i2, t_temp);
      }else if(t_temp<=currentI->pulse->td+currentI->pulse->per){
	value = currentI->pulse->i1;
      }
    }else if(strcmp(currentI->transient_spec,"PWL")==0){
      currPwl=currentI->pwl;
      if(t<=currPwl->t){
	value = currPwl->i;
      }else{
	prevPwl=currPwl;
	currPwl=currPwl->next;
	while(currPwl!=NULL){
	  if(t<=currPwl->t){
	    //linear
	    value = linear_value(prevPwl->t, prevPwl->i, currPwl->t, currPwl->i, t);
	    break;
	  }
	  prevPwl=currPwl;
	  currPwl=currPwl->next;
	}
	if(currPwl==NULL){
	  value = prevPwl->i;
	}
      }
      
    }else{
      value = currentI->value;
    }
    if(i!=0){
      gsl_vector_set (E, i-1, gsl_vector_get(E,i-1) - value);		
    }
    if(j!=0){

      gsl_vector_set (E, j-1, gsl_vector_get(E,j-1) + value);
    }
    currentI=currentI->next;
  }

  currentV = rootV;
  while(currentV!=NULL){
    if(strcmp(currentV->transient_spec,"EXP")==0){
      if(t<=currentV->exp->td1){
	value = currentV->exp->i1;
      }else if(t<=currentV->exp->td2){
	value = currentV->exp->i1 + (currentV->exp->i2 - currentV->exp->i1)*(1 - exp(-(t-currentV->exp->td1)/currentV->exp->tc1));
      }else if(t<=end_time){
	value = currentV->exp->i1 + (currentV->exp->i2 - currentV->exp->i1)*(exp(-(t-currentV->exp->td2)/currentV->exp->tc2) - exp(-(t-currentV->exp->td1)/currentV->exp->tc1));
      }
    }else if(strcmp(currentV->transient_spec,"SIN")==0){
      if(t<=currentV->sin->td){
	value = currentV->sin->i1 + currentV->sin->ia*sin(2*pi*currentV->sin->ph/360);
      }else if(t<=end_time){
	value = currentV->sin->i1 + currentV->sin->ia*sin(2*pi*currentV->sin->fr*(t-currentV->sin->td)+2*pi*currentV->sin->ph/360);
      }
    }else if(strcmp(currentV->transient_spec,"PULSE")==0){
      k=(t-currentV->pulse->td)/currentV->pulse->per;
      if(k<0)k=0;
      
      t_temp=t-k*currentV->pulse->per;
      
      if(t_temp<=currentV->pulse->td){
	value = currentV->pulse->i1;
      }else if(t_temp<=currentV->pulse->td+currentV->pulse->tr){
	//linear i1->i2
	value = linear_value(currentV->pulse->td, currentV->pulse->i1, currentV->pulse->td+currentV->pulse->tr, currentV->pulse->i2, t_temp);
      }else if(t_temp<=currentV->pulse->td+currentV->pulse->tr+currentV->pulse->pw){
	value = currentV->pulse->i2;
      }else if(t_temp<=currentV->pulse->td+currentV->pulse->tr+currentV->pulse->pw+currentV->pulse->tf){
	//linear i2->i1
	value = linear_value(currentV->pulse->td+currentV->pulse->tr+currentV->pulse->pw, currentV->pulse->i2, currentV->pulse->td+currentV->pulse->tr+currentV->pulse->pw+currentV->pulse->tf, currentV->pulse->i2, t_temp);
      }else if(t_temp<=currentV->pulse->td+currentV->pulse->per){
	value = currentV->pulse->i1;
      }
    }else if(strcmp(currentV->transient_spec,"PWL")==0){
      currPwl=currentV->pwl;
      if(t<=currPwl->t){
	value = currPwl->i;
      }else{
	prevPwl=currPwl;
	currPwl=currPwl->next;
	while(currPwl!=NULL){
	  if(t<=currPwl->t){
	    //linear
	    value = linear_value(prevPwl->t, prevPwl->i, currPwl->t, currPwl->i, t);
	    break;
	  }
	  prevPwl=currPwl;
	  currPwl=currPwl->next;
	}
	if(currPwl==NULL){
	  value = prevPwl->i;
	}
      }
      
    }else{
      value = currentV->value;
    }
    gsl_vector_set (E, hash_count-2+b, value);

    b++;
    currentV=currentV->next;
  }

  return E;
}

double linear_value(double x1, double y1, double x2, double y2, double x){
  double y;
  double m;
  
  m = (y2-y1)/(x2-x1);
  
  y = m*(x-x1) + y1;
  
  return y ;
}


