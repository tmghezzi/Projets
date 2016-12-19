#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#ifndef POLYNOME
#define POLYNOME
typedef struct Poly
{
  int Degre;
  int Ordre;
  double * Coef;
} Polynome,*PolynomePtr;
#endif
void PolynomeInitialise ( PolynomePtr  , double * );
PolynomePtr PolynomeConstructeur(int );
void PolynomeDestructeur(PolynomePtr * );
PolynomePtr PolynomeCopie(PolynomePtr );
double PolynomeEvalue( PolynomePtr , double );
PolynomePtr PolynomeAddition( PolynomePtr  , PolynomePtr ) ;
PolynomePtr PolynomeMultiplication( PolynomePtr , PolynomePtr);
PolynomePtr PolynomeInterpolation(int , double* , double* ); 
void PolynomeAffiche( PolynomePtr );
