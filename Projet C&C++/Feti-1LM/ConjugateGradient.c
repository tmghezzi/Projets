# include <string.h>
# include <stdlib.h>
# include <math.h>
# include "ConjugateGradient.h"
# include "blas1.h"


void PrintVecteur(int dim, double * vecteur)
{
	for( int i = 0 ; i < dim ; i++)
	{
		printf(" %7.5lg\t ", vecteur[i] );
		printf("\n");
	}

}

int GradConj( void* A, int *noeud_interf, int dim, int myrank, double* x, const double* b, 
	void (*prodAx)(void* A, int *noeud_interf, int dim, int myrank, const double* u, double* v /*sorti*/),
	int niterMax, double eps, double* err)
{
  int niter;
  double nrmR, nrmR0, nrm;
  double alpha, beta;
  double *r, *p, *q, *ptR;
  
  /* Memory reservation for locate vectors */
  r = (double*)calloc(dim,sizeof(double));
  p = (double*)malloc(dim*sizeof(double));
  q = (double*)malloc(dim*sizeof(double));
  /* Compute the residual r0 = b - A.x0 */
  (*prodAx)(A,noeud_interf,dim,myrank,x,q);

  if ( b != NULL )
    memcpy(r, b, dim*sizeof(double));

  daxpby( dim, -1., q, 1., r );
  /* Compute the square of the norm of the initial residual */
  nrmR = dot(dim,r,r);
  nrmR0 = nrmR;  
  /* Initial direction of descent : p = r */
  memcpy( p, r, dim*sizeof(double));
  /* Beginning of the iteration loop with counter for number of iterations : */
  niter = 0;

  /* While ||r||L2 < eps*||r0||_L2 and niter < niterMax : */
  while ( (nrmR > nrmR0*eps*eps) && ( niter < niterMax ) )
  {
    /* q_{n} = A.p_{n} */
    (*prodAx)(A,noeud_interf,dim,myrank,p,q);
    /* alpha = <r_{n-1},r_{n-1}>/<q_{n},p_{n}> */
    alpha = nrmR/dot(dim,q,p);
    /* x_{n+1} = x_{n} + alpha.p_{n} */
    daxpby(dim, alpha, p, 1., x);
    /* r_{n+1} = r_{n} - alpha.q_{n} */
    daxpby(dim, -alpha, q, 1.,r);
    /* beta = <r_{n+1},r_{n+1}>/<r_{n},r_{n}> */
    nrm  = dot(dim,r,r); 
    //printf("---- dot (R,R) = %7.5g it: %d , myrank: %d -----\n",nrm,niter,myrank);
    //PrintVecteur(dim, r);
    beta = nrm/nrmR;
    nrmR = nrm;
    /* p_{n+1} = r + beta.p_{n} */
    daxpby(dim, 1., r, beta, p);
    /* Next iteration */
    niter++;
  }
  printf("Debug: Rank: %d, nrmR %f, nrmR0 %f\n",myrank, nrmR,nrmR0);

  *err = sqrt(nrmR/nrmR0);
  printf("Debug: Rank: %d, gradientConj: iter: %d err= %7.5g \n",myrank,niter, *err);
  return niter;
}
