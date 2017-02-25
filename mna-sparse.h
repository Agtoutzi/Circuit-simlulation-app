#include "csparse.h"


#ifndef MNASPARSE_H
#define MNASPARSE_H

cs *A_sparse;			// Pinakas A (mna) se morfi triplet
cs *C_sparse;			// Pinakas A (mna) se morfi compressed-column
css *S;				// Pinakas S gia tin LU kai Cholesky
csn *N;				// Pinakas N gia tin LU kai Cholesky

int sizeA_sparse;				//non zeros stoixeia tou pinaka A

double *B_sparse;			//pinakas deksiou melous eksiswshs B ( double, mege8ous : [(n-1)+m2] x 1 ) -> grammi!	

double *x_sparse;

//gsl_permutation * p;		//dianusma meta8esewn

void CreateMnaSparse();
void solveSparse();
void solve_spdSparse();
void conjugate_gradient_sparse(cs *A, double *b, int n, double *x, double itol);
//void conjugate_gradient(gsl_matrix *a,gsl_vector *b,gsl_vector *X,int n,double tolerance);
//void bi_conjugate_gradient(gsl_matrix *a,gsl_vector *b,gsl_vector *X,int n,double tolerance);
//gsl_vector* preconditioner_diag(gsl_matrix *A,int n);
#endif