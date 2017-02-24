
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_cblas.h>


#ifndef MNA_H
#define MNA_H

gsl_matrix *A;			// 2D pinakas aristerou melous eksiswshs A ( double, mege8ous : [(n-1)+m2] x [(n-1)+m2] )

//double *temp;			//ka8e grammi tou pinaka				
int sizeA;				//[(n-1)+m2]x[(n-1)+m2]

gsl_vector *B;			//pinakas deksiou melous eksiswshs B ( double, mege8ous : [(n-1)+m2] x 1 ) -> grammi!	
int sizeB;				//[(n-1)+m2] x 1

void CreateMna();

#endif
