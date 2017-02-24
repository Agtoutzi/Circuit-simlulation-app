
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_cblas.h>
#include <gsl/gsl_linalg.h>

#ifndef MNA_H
#define MNA_H

gsl_matrix *A;			// 2D pinakas aristerou melous eksiswshs A ( double, mege8ous : [(n-1)+m2] x [(n-1)+m2] )

//double *temp;			//ka8e grammi tou pinaka				
int sizeA;				//[(n-1)+m2]x[(n-1)+m2]

gsl_vector *B;			//pinakas deksiou melous eksiswshs B ( double, mege8ous : [(n-1)+m2] x 1 ) -> grammi!	
int sizeB;				//[(n-1)+m2] x 1

gsl_vector *x;

gsl_permutation * p;		//dianusma meta8esewn

void CreateMna();
void solve();
void solve_spd();
void conjugate_gradient(gsl_matrix *a,gsl_vector *b,gsl_vector *X,int n,double tolerance);
#endif
