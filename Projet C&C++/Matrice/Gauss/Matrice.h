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
//MatricePtr  MatriceTableau ( int  , int , double A[][colonnes]);
int Gauss ( MatricePtr);
VecteurPtr ResoutSysteme( MatricePtr  M , VecteurPtr B) ;
void MatriceDestructeur( MatricePtr * );
MatricePtr  MatriceMultiplication( MatricePtr ,
				   MatricePtr);
void MatriceAffiche(MatricePtr);
MatricePtr MatriceCopie(MatricePtr);
VecteurPtr  MatriceVecteur( MatricePtr,
			    VecteurPtr);
