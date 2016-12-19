#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Vecteur.h"
#ifndef MATRICE
#define MATRICE
typedef struct Mat {
  int L;
  int C;
  int Taille ;
  double * Coef ;
  double ** Coef2d ;
} Matrice, *MatricePtr;
#endif
MatricePtr  MatriceConstructeur( int  , int);
int Gauss ( MatricePtr  , int ** , int **);
VecteurPtr ResoutSysteme( MatricePtr  M , int * , int * , VecteurPtr B) ;
void MatriceDestructeur( MatricePtr * );
MatricePtr  MatriceMultiplication( MatricePtr ,
				   MatricePtr);
void MatriceAffiche(MatricePtr);
MatricePtr MatriceCopie(MatricePtr);
VecteurPtr  MatriceVecteur( MatricePtr,
			    VecteurPtr);
