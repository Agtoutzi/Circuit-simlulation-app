#include "csparse.h"


#ifndef MNASPARSE_H
#define MNASPARSE_H

cs *A_sparse;			// Pinakas A (mna) se morfi triplet
cs *C_sparse;			// Pinakas A (mna) se morfi compressed-column
css *S;				// Pinakas S gia tin LU kai Cholesky
css *N;				// Pinakas N gia tin LU kai Cholesky

int sizeA_sparse;				//non zeros stoixeia tou pinaka A

//gsl_vector *B;			//pinakas deksiou melous eksiswshs B ( double, mege8ous : [(n-1)+m2] x 1 ) -> grammi!	
//int sizeB;				//[(n-1)+m2] x 1

//gsl_vector *x;

//gsl_permutation * p;		//dianusma meta8esewn

void CreateMnaSparse();
void solveSparse();
void solve_spdSparse();
//void conjugate_gradient(gsl_matrix *a,gsl_vector *b,gsl_vector *X,int n,double tolerance);
//void bi_conjugate_gradient(gsl_matrix *a,gsl_vector *b,gsl_vector *X,int n,double tolerance);
//gsl_vector* preconditioner_diag(gsl_matrix *A,int n);
#endif