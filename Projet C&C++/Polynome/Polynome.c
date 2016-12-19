#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Vecteur.h"
#include "Matrice.h"
#include "Polynome.h"

//Polynomeconstructeur.......................................................
PolynomePtr PolynomeConstructeur(int Deg){
  PolynomePtr P;
  P=(PolynomePtr)malloc(sizeof(Polynome));
  P->Degre=Deg;
  P->Ordre=Deg+1;
  P->Coef=(double*)malloc((Deg+1)*sizeof(double));
  return P;
}

//PolynoemDestructeur.......................................................
void PolynomeDestructeur(PolynomePtr *P){
  free((*P)->Coef);
  free(*P);
  *P=NULL;
}

//PolynomeInitialise.......................................................
void PolynomeInitialise ( PolynomePtr P , double * A){
  int i;
  for(i=0;i<=P->Degre;i++){
    P->Coef[i]=A[i];
  }
}

//PolynomeCopie.............................................................
PolynomePtr PolynomeCopie(PolynomePtr P){
  PolynomePtr P1;
  int i=0;
  P1=PolynomeConstructeur(P->Degre);
  for(i=0;i<=P->Degre;i++){
    P1->Coef[i]=P->Coef[i];
  }
  return P1;
}

//PolynomeAffiche...........................................................
void PolynomeAffiche(PolynomePtr P){
  int i=0;
  printf("Les Coefficient du polynomes sont:\n");
  for(i=0;i<=P->Degre;i++){
    printf("%lf\n",P->Coef[i]);  
  }
}
//Régle de Hörner.............................................................
double PolynomeEvalue( PolynomePtr P , double x ){
  int i=0;
  double p=P->Coef[(P->Degre)];

  for(i=(P->Degre)-1;i>=0;i--){
    p=p*x+P->Coef[i];
  }
 
  return p;
}
//PolynomeAddition..............................................................
PolynomePtr PolynomeAddition( PolynomePtr P1 , PolynomePtr P2){
  int i=0 ,max=0;
  PolynomePtr P3;
  max=(P1->Degre)>(P2->Degre)?(P1->Degre):(P2->Degre);
  P3=PolynomeConstructeur(max);
  for(i=0;i<=P3->Degre;i++){
    P3->Coef[i]=P1->Coef[i]+P2->Coef[i];
  }
  return P3;
}
//PolynomeMultiplication........................................................
PolynomePtr PolynomeMultiplication( PolynomePtr P1 , PolynomePtr P2){
  int i,j;
  PolynomePtr PM;
  PM=PolynomeConstructeur(P1->Degre+P2->Degre);
  for(i=0;i<=PM->Degre;i++){
    PM->Coef[i]=0;
  }
  for(i=0;i<=P1->Degre;i++){
    for(j=0;j<=P2->Degre;j++){
      PM->Coef[i+j]+=P1->Coef[i]*P2->Coef[j];
    }  
  }
  return PM;
}

//PolynomeInterpolation.........................................................
PolynomePtr PolynomeInterpolation(int n, double* T, double *B){
  int i,j;
  PolynomePtr PI;
  VecteurPtr V,B1;
  V=VecteurConstructeur(n);
  B1=VecteurConstructeur(n);
  PI=PolynomeConstructeur(n-1);
  MatricePtr M=MatriceConstructeur(n,n);
  for(i=0;i<n;i++){

    M->Coef2d[i][0]=1;
  }
  for(i=0;i<n;i++){
    for(j=1;j<n;j++){
      M->Coef2d[i][j]=T[i]*M->Coef2d[i][j-1];
    }
  }
  int *P=(int*)malloc((M->L)*sizeof(int));
  for(i=0;i<M->L;i++){
    P[i]=i;
  }

  VecteurInitialise(B1,B);
  V=ResoutSysteme(M,P,B1);

  double *A;
  A=(double*)malloc(V->N*sizeof(double));
  for(i=0;i<V->N;i++){
    A[i]=V->Coord[P[i]];
  }
  PolynomeInitialise(PI,A);
  return PI;
}

