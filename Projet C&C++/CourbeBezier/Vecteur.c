#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Vecteur.h"

//Vecteur Constructeur
VecteurPtr VecteurConstructeur(int n){
  VecteurPtr v;
  v=(VecteurPtr)malloc(sizeof(Vecteur));
  v->N=n;
  v->Coord=(double*)malloc(n*sizeof(double));
  return v;
}

//Destructeur
void VecteurDestructeur(VecteurPtr *v){
  free((*v)->Coord);
  free(*v);
  *v=NULL;
}

//VecteurCopie
VecteurPtr VecteurCopie(VecteurPtr B){
  VecteurPtr V;
  int i=0;
  V=VecteurConstructeur(B->N);
  for(i=0;i<B->N;i++){
    V->Coord[i]=0;
  }
  for(i=0;i<B->N;i++){
    V->Coord[i]=B->Coord[i];
  }
  return V;
}

//VecteurInitialise
void VecteurInitialise(VecteurPtr V,double *A){
  int i;
  for(i=0;i<V->N;i++){
    V->Coord[i]=A[i];
  }
}

//VecteurAffiche
void VecteurAffiche(VecteurPtr V){
  int i;
  printf("\n");
  printf("La dimension de N est: %d\n",V->N);
  printf("Les valeurs du vecteur sont: \n");
  for(i=0;i<V->N;i++){
    printf("%f\n",V->Coord[i]);
  }
  printf("---------------------------------\n\n");
}

