#ifndef ALGEBRA_H
# define ALGEBRA_H
# include <stdio.h>
/*
Compute the dot product
Input :
 - dim Dimension of the vectors
 - u   Coefficients of the first  vector
 - v   Coefficients of the second vector
Return :
 - The dot product <u,v>
*/
double dot( int dim, const double* u, const double* v );
/*
Compute y = alpha.x + beta.y
Input :
-------
 - dim    Dimension of vectors
 - alpha  Double scalar
 - x      Coefficients of the first vector
 - beta   Double scalar
 - y      Coefficients of the second vector
Output :
--------
 At return, y contains the value alpha.x + beta.y
*/
void daxpby( int dim, double alpha, const double* x, double beta, double* y );
/*
Display vector on output out
Input :
-------
  - dim   Dimension of the vector
  - x     Coefficients of the vector
Input/Output :
--------------
  - out   The output where write the vector
*/
void printVector( FILE* out, int dim, const double* x );

#endif
