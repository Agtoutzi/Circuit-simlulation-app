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
void compute_precontitioner_from_sparce_matrix(const cs *A, double *preconditioner);
void preconditioner_solve_for_sparce_matrix(const double *r, const double *preconditioner, double *z, int n);
void mul_sparce_matrix_with_vector(const cs *A, const double *x , double *y ,  int reverse_sparce );
double *bi_conjugate_gradient_with_sparce_matrix( const cs *A, int n, double *b , double itol , double *x );
//void conjugate_gradient(gsl_matrix *a,gsl_vector *b,gsl_vector *X,int n,double tolerance);
//void bi_conjugate_gradient(gsl_matrix *a,gsl_vector *b,gsl_vector *X,int n,double tolerance);
//gsl_vector* preconditioner_diag(gsl_matrix *A,int n);
#endif