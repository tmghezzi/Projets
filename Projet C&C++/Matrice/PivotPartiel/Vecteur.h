#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#ifndef VECTEUR
#define VECTEUR
typedef struct Vect {
  int N ;
  double * Coord ;
} Vecteur , *VecteurPtr;
#endif
VecteurPtr VecteurConstructeur(int);
VecteurPtr VecteurCopie( VecteurPtr);
void VecteurDestructeur(VecteurPtr *);
void VecteurInitialise ( VecteurPtr , double *);
void VecteurAffiche( VecteurPtr); 
