# include "blas1.h"

double dot( int dim, const double* u, const double* v )
{
  const double *ptU, *ptV;
  const double* endU= u+dim;
  double dotVal = 0.;
  for ( ptU = u, ptV = v; ptU != endU; ptU++, ptV++ )
    dotVal += (*ptU)*(*ptV);
  return dotVal;
}
// ------------------------------------------------------------------------
void daxpby( int dim, double alpha, const double* x, double beta, double* y )
{
  const double* ptX;
  double *ptY;
  const double* endX = x+dim;
  for ( ptX = x, ptY = y; ptX != endX; ptX++, ptY++ )
    (*ptY) = alpha*(*ptX) + beta*(*ptY);
}
// ------------------------------------------------------------------------
void printVector( FILE* out, int dim, const double* x )
{
  int i;
  for ( i = 0; i < dim; i++ )
    fprintf(out, "%7.5lg\t",x[i]);
}
