#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Vecteur.h"
#include "Matrice.h"
#define zero 1e-14
MatricePtr MatriceConstructeur(int l, int c){

  int i;
  MatricePtr M;
  M=(MatricePtr)malloc(sizeof(Matrice));
  M->L=l;
  M->C=c;
  M->Coef=(double*)malloc(sizeof(double)*l*c);
  M->Coef2d=(double**)malloc(sizeof(double*)*l);
  for(i=0;i<l;i++){
    M->Coef2d[i]=&(M->Coef[i*c]);
  }
  return M;
}

//Destructeur................................................................
void MatriceDestructeur(MatricePtr *M){
  free((*M)->Coef2d);
  free((*M)->Coef);
  free(*M);
  *M=NULL;
}

//Initialisation de la matrice.............................................
MatricePtr MatriceInitialise(int lignes,int colonnes,double A[][colonnes]){
  int i,j;
  MatricePtr M;
  M=MatriceConstructeur(lignes,colonnes);
  for(i=0;i<=lignes-1;i++){
    for(j=0;j<=colonnes-1;j++){
      M->Coef2d[i][j]=A[i][j];
    }
  }
  return M;
}
//Matrice Multiplication...........................................

MatricePtr MatriceMultiplication(MatricePtr M1,MatricePtr M2){
  MatricePtr M3;
  if(M1->C==M2->L){
  M3=MatriceConstructeur(M1->L,M1->C);

  int i=0,j=0,n=0;
  double somme=0;

  for(i=0;i<M1->L;i++){

    for(j=0;j<M1->C;j++){
      somme=0;
      for(n=0;n<M2->L;n++){

	somme=somme+(M1->Coef2d[i][n])*(M2->Coef2d[n][j]);
      }
      M3->Coef2d[i][j]=somme;
    }
  }
  }
  return M3;
}

//MatriceProduitVecteur..............................................

VecteurPtr MatriceProduitVecteur(MatricePtr M,VecteurPtr V){
VecteurPtr V1;
V1=VecteurConstructeur(V->N);
int i,j;

for(i=0;i<V1->N;i++){

for(j=0;j<V1->N;j++){

V1->Coord[i]+=(M->Coef2d[i][j])*(V->Coord[j]);
}
}
return V1;
}

//MAtriceAFFiche.........................................................
void MatriceAffiche(MatricePtr M){
int i,j;
  for(i=0;i<M->L;i++){
    for(j=0;j<M->C;j++){
      printf("%lf ",M->Coef2d[i][j]);
    }
    printf("\n");
}
}
//MAtrice Copie .........................................................
MatricePtr MatriceCopie(MatricePtr M){
MatricePtr M1;
M1=MatriceConstructeur(M->L,M->C);
int i,j;
  for(i=0;i<M->L;i++){
    for(j=0;j<M->C;j++){
M1->Coef[i*(M1->C)+j]=M->Coef2d[i][j];
    }
}
return M1;
}



//Gauss ..................................................................
int Gauss(MatricePtr M,int **PP){
  int i,j,k,result=0;
  double quotien;
  int imax=0,temp=0;

  for(k=0;k<=M->L-1;k++){
 if(M->Coef2d[*PP[k]][k]-zero<=0){
int imax=k;
int max=M->Coef2d[*PP[k]][k];
for(i=k;i<M->L;i++){
if(max<M->Coef2d[*PP[i]][k]){
imax=i;
}
}
temp=*PP[imax];
*PP[imax]=k;
*PP[k]=temp;
}
  for(i=k+1;i<=M->L-1;i++){
   

quotien=(M->Coef2d[*PP[i]][k]/M->Coef2d[*PP[k]][k]);
M->Coef2d[*PP[i]][k]=quotien;
      for(j=k+1;j<=M->L-1;j++){
	M->Coef2d[*PP[i]][j]-=quotien*(M->Coef2d[*PP[k]][j]);
	}
      }
    }
 

return result;
}

//Gauss 2.......................................................
int Gauss2(MatricePtr M){;
  int i=0,j=0,k=0,n;
int result=0;
  for(i=0;i<(M->L);i++){

    for(j=1;j<=i;j++){

      for(k=0;k<=j-1;k++){
if(M->Coef2d[j][i]==0 ){
result=1;
}
	M->Coef2d[j][i]-=M->Coef2d[j][k]*M->Coef2d[k][i];
      }
    } 

    for(j=i+1;j<(M->L);j++){
      for(k=0;k<=i-1;k++){
	M->Coef2d[j][i]-=M->Coef2d[j][k]*M->Coef2d[k][i];
      }
      M->Coef2d[j][i]=(M->Coef2d[j][i])*(1/(M->Coef2d[i][i]));
    }
  }
return result;
}

//ResoutSysteme................................................
VecteurPtr ResoutSysteme(MatricePtr M,int *P,VecteurPtr B){
int k,i;
double somme=0,somme2=0;
int **PP=(int**)malloc((M->L)*sizeof(int*));
//Initialisation du double Pointeur
for(i=0;i<M->L;i++){
PP[i]=&P[i];
}
Gauss(M,PP);
VecteurPtr X;
X=VecteurConstructeur(B->N);
//Descente
for(i=0;i<=M->L-1;i++){
somme=0;
for(k=0;k<=i-1;k++){
somme+=M->Coef2d[P[i]][k]*X->Coord[k];
}
X->Coord[i]=B->Coord[i]-somme;
}
//Remonter
for(i=M->L-1;i>=0;i--){
somme2=0;
for(k=i+1;k<=M->L-1;k++){
somme2+=M->Coef2d[P[i]][k]*X->Coord[k];
}
X->Coord[i]=(X->Coord[i]-somme2)/M->Coef2d[P[i]][i];
}
return X;
}
//TEST GAUSS .....................................................
void TestGauss (int n,double AA[][n] ,double A[]){
int i,j;
VecteurPtr B,B1,verif;
B=VecteurConstructeur(n);
MatricePtr M1,M2;
M1=MatriceInitialise(n,n,AA);
int *P=(int*)malloc((M1->L)*sizeof(int));
for(i=0;i<M1->L;i++){
P[i]=i;
}
printf("Initialisation de la Matrice M1\n\n");
MatriceAffiche(M1);
VecteurInitialise(B,A);
printf("Initialisation du Vecteur B\n\n");
VecteurAffiche(B);
M2=MatriceCopie(M1);
printf("Copie de M1 Dans M2\n\n");
MatriceAffiche(M2);
printf("Resoud M2 B\n\n");
B1=ResoutSysteme(M2,P,B);
//Affiche aprés pivot partiel de la matrice
printf("Gauss M2\n\n");
 for(i=0;i<M2->L;i++){
    for(j=0;j<M2->C;j++){
      printf("%lf ",M2->Coef2d[P[i]][j]);
    }
    printf("\n");
}
VecteurAffiche(B1);
printf("Produit [M1] {X} \n\n"); 
verif=MatriceProduitVecteur(M1,B1);
//Affiche du vecteur aprés pivotpartiel
printf("La dimension de N est: %d\n",verif->N);
printf("Les valeurs du vecteur vérification sont: \n");
for(i=0;i<verif->N;i++){
printf("%f\n",verif->Coord[P[i]]);
}
printf("---------------------------------\n\n");

}

