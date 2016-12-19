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

//Recherche Max Pivot partiel
int RechercheMaxPartiel(MatricePtr M,int k){
int i;
int imax=k;
int max=M->Coef2d[k][k];
for(i=k;i<M->L;i++){
if(max<M->Coef2d[i][k]){
imax=i;
}
}
return imax;
}

//Recherche MAx Pivot Total
void RechercheMaxTotal(MatricePtr M,int k,int *imax,int *jmax,int **LP){
int i,j;
*imax=k;
int max=M->Coef2d[k][k];
for(i=k;i<M->L;i++){
for(j=k;j<M->C;j++){
if(max<=M->Coef2d[*LP[i]][j]){
max=M->Coef2d[*LP[i]][j];
*imax=i;
*jmax=j;
}
}
}
}
//Gauss ..................................................................
int Gauss(MatricePtr M,int **LP,int **CP){
  int i,j,k,result=0;
  double quotien,max;
  int imax=0,jmax=0,temp=0;

  for(k=0;k<=M->L-1;k++){
 if(fabs(M->Coef2d[*LP[k]][*CP[k]])<zero){
double  max=M->Coef2d[*LP[k]][*CP[k]];
for(i=k;i<M->L;i++){
for(j=k;j<M->C;j++){
if(fabs(max)<fabs(M->Coef2d[*LP[i]][*CP[j]])){
max=M->Coef2d[*LP[i]][*CP[j]];
imax=*LP[i];
jmax=*CP[j];
}
}
}
printf("max %d %d\n",imax,jmax);
temp=*LP[imax];
*LP[imax]=*LP[k];
*LP[k]=temp;
temp=*CP[jmax];
*CP[jmax]=*CP[k];
*CP[k]=temp;
}
  for(i=k+1;i<=M->L-1;i++){
   

quotien=(M->Coef2d[*LP[i]][*CP[k]]/M->Coef2d[*LP[k]][*CP[k]]);
M->Coef2d[*LP[i]][*CP[k]]=quotien;
      for(j=k+1;j<=M->L-1;j++){
	M->Coef2d[*LP[i]][*CP[j]]-=quotien*(M->Coef2d[*LP[k]][*CP[j]]);
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
VecteurPtr ResoutSysteme(MatricePtr M,int *PI,int *PJ,VecteurPtr B){
int k,i;
double somme=0,somme2=0;
int **LP=(int**)malloc((M->L)*sizeof(int*));
int **CP=(int**)malloc((M->L)*sizeof(int*));
//Initialisation du double Pointeur
for(i=0;i<M->L;i++){
LP[i]=&PI[i];
CP[i]=&PJ[i];
}
Gauss(M,LP,CP);
VecteurPtr X;
X=VecteurConstructeur(B->N);
//Descente
for(i=0;i<=M->L-1;i++){
  X->Coord[PJ[i]]=B->Coord[PI[i]];
somme=0;
for(k=0;k<=i-1;k++){
somme+=M->Coef2d[PI[i]][PJ[k]]*X->Coord[PJ[k]];
}
X->Coord[PJ[i]]=B->Coord[PI[i]]-somme;
}
//Remonter
for(i=M->L-1;i>=0;i--){
somme2=0;
for(k=i+1;k<=M->L-1;k++){
somme2+=M->Coef2d[PI[i]][PJ[k]]*X->Coord[PJ[k]];
}
X->Coord[PI[i]]=(X->Coord[PJ[i]]-somme2)/M->Coef2d[PI[i]][PJ[i]];
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
int *PI=(int*)malloc((M1->L)*sizeof(int));
int *PJ=(int*)malloc((M1->L)*sizeof(int));
for(i=0;i<M1->L;i++){
PI[i]=i;
PJ[i]=i;
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
B1=ResoutSysteme(M2,PI,PJ,B);
//Affiche aprés pivot partiel de la matrice
printf("Gauss M2\n\n");
 for(i=0;i<M2->L;i++){
    for(j=0;j<M2->C;j++){
      printf("%lf ",M2->Coef2d[PI[i]][PJ[j]]);
    }
    printf("\n");
}
VecteurAffiche(B1);
printf("Produit [M1] {X} \n\n"); 
verif=MatriceProduitVecteur(M1,B1);
//Affiche du vecteur aprés pivotpartiel
 VecteurAffiche(verif);

}

/*
//Programme PRINCIPAL..........................................
 int n = 5; 
  int main ( )
{

  void TestGauss( int , double AA[][n] , double A[] );
  int i,j;
  double y;
  double x=0.;
  double A[n][n] ;
  double B[n] ;
  double B1[4] ;
  double BB1[4] ;

  for ( i = 0 ; i < n; i++)
    {
      y=1.;
      B[i]=0.;
      for ( j = 0 ; j <  n ; j++)
	{
          A[i][j] = y ;
	  B[i]+=(j + 1) * y ;
	  y*=x;
	}
      x+=1.;
    }

   //TestGauss(n,A,B);
  
  double A1[4][4]={{10.,7.,8.,7.},
		  {7.,5.,6.,5.},
		  {8.,6.,10.,9.},
		  {7.,5.,9.,10.}};
  
  B1[0] = 32. ;
  B1[1] = 23. ;
  B1[2] = 33. ;
  B1[3] = 31.;

   //TestGauss(4,A1,B1);

  BB1[0] = 32.1 ;
  BB1[1] = 22.9 ;
  BB1[2] = 33.1 ;
  BB1[3] = 30.9;
  //TestGauss(4,A1,BB1);

  double A2[4][4]={{0.,0.,1.,0.},
		   {0.,0.,0.,1.},
		   {1.,0.,0.,0.},
		   {0.,1.,0.,0.}};

  double B2[4] = {1.,2.,3.,4.} ;
    TestGauss(4,A2,B2);
  double A3[5][5] = {{1.,2.,4.,8.,16.},
		     {2.,4.,8.,16.,31.},
		     {4.,8.,16.,31.,61.},
		     {8.,16.,31.,61.,120.},
		     {16.,31.,61.,120.,236.}};
  double B3[5]={31.,61.,120.,236.,464.};
  TestGauss(5,A3,B3);

}



*/
