#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Vecteur.h"
#include "Matrice.h"

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
int Gauss(MatricePtr M){
  int i,j,k,result=0;
  double quotien;

  for(k=0;k<M->L-1;k++){

    for(i=k+1;i<=M->L-1;i++){
if(M->Coef2d[k][k]==0){
result=1;
}
quotien=(M->Coef2d[i][k]/M->Coef2d[k][k]);
M->Coef2d[i][k]=quotien;
      for(j=k+1;j<=M->L-1;j++){
	M->Coef2d[i][j]-=quotien*(M->Coef2d[k][j]);
	}
      }
    }
 

return result;
}

//Gauss 2.......................................................
int Gauss2(MatricePtr M){
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
VecteurPtr ResoutSysteme(MatricePtr M,VecteurPtr B){
Gauss(M);
VecteurPtr X;
X=VecteurConstructeur(B->N);
int k,i;
double somme=0,somme2=0;
//Descente
for(i=0;i<=M->L-1;i++){
somme=0;
for(k=0;k<=i-1;k++){
somme+=M->Coef2d[i][k]*X->Coord[k];
}
X->Coord[i]=B->Coord[i]-somme;
}
//Remonter
for(i=M->L-1;i>=0;i--){
somme2=0;
for(k=i+1;k<=M->L-1;k++){
somme2+=M->Coef2d[i][k]*X->Coord[k];
}
X->Coord[i]=(X->Coord[i]-somme2)/M->Coef2d[i][i];
}
return X;
}
//TEST GAUSS .....................................................
void TestGauss (int n,double AA[][n] ,double A[]){
VecteurPtr B,B1,verif;
B=VecteurConstructeur(n);
MatricePtr M1,M2;
M1=MatriceInitialise(n,n,AA);
printf("\n--------------------Initialisation de la Matrice M1-----------------------\n");
MatriceAffiche(M1);
VecteurInitialise(B,A);
printf("\n--------------------Initialisation du Vecteur B-----------------------------\n");
VecteurAffiche(B);
M2=MatriceCopie(M1);
printf("\n--------------------Copie de M1 Dans M2----------------------------------\n");
MatriceAffiche(M2);
printf("\n---------------------Resoud M2 B------------------------------------------\n");
B1=ResoutSysteme(M2,B);
printf("\n---------------------Gauss M2---------------------------------------------\n");
MatriceAffiche(M2);
VecteurAffiche(B1);
printf("\n--------------------Produit M1 X-------------------------------------------\n"); 
verif=MatriceProduitVecteur(M1,B1);
VecteurAffiche(verif);
}


//Programme PRINCIPAL..........................................
int main(){
  /*  
//Debut vecteur
//Testcontructeur
VecteurPtr v1,v2;
int k;
v1=VecteurConstructeur(20);
VecteurAffiche(v1);

//TEST Copie du vecteur v1 =>V2
v2=VecteurCopie(v1);
VecteurAffiche(v2);

//TEST Vecteur initialise
double *A;
A=(double*)malloc(20*sizeof(double));
for(k=0;k<20;k++){
A[k]+=k*2;
}
VecteurInitialise(v2,A);
v1=VecteurCopie(v2);
VecteurAffiche(v1);

//FIn vecteur.................................................. 


//Construction Matrice 4x4
MatricePtr M1=MatriceConstructeur(4,4);
MatricePtr M2=MatriceConstructeur(4,4);
MatricePtr M3=MatriceConstructeur(4,4);
MatricePtr M4=MatriceConstructeur(4,4);

//création du tableau pour initialiser M1
int i,j;
double Tableau[4][4];
for (i=0; i<=3; i++){

	for (j=0; j<=3; j++){
		Tableau[i][j] = 1;
}
}
M4=MatriceInitialise(4,4,Tableau);
Affichage du tableau 
printf("\nMatrice M1.........................\n");
MatriceAffiche(M1);
printf("\nMultiplication matrice m1 par m1...\n");
M2=MatriceMultiplication(M1,M1);
MatriceAffiche(M2);
double Mat[4][4]={{1,2,2,3},{0,7,5,6},{3,6,8,7},{2,10,8,9}};
M4=MatriceInitialise(4,4,Mat);
VecteurAffiche(v1);
v2=MatriceProduitVecteur(M1,v1);
VecteurAffiche(v2);

Gauss(M4);
MatriceAffiche(M4);
if(Gauss(M4)){
printf("L'un ou plusieurs terme s'annule\n");
}
MatriceDestructeur(&M4);
//ResoutSysteme...........................................
MatricePtr M5=MatriceConstructeur(4,4);
M5=MatriceInitialise(4,4,Mat);
MatriceAffiche(M5);
int imax=0,jmax=0;
RechercheMaxTotal(M5,0,&imax,&jmax);
printf("PPPPPP: %d et %d..............\n",imax,jmax);
PermutationLL(M5,0,imax);
MatriceAffiche(M5);
PermutationCC(M5,0,jmax);
printf("PPPPPP: %d et %d..............\n",imax,jmax);
MatriceAffiche(M5);

VecteurPtr v4;
VecteurAffiche(v1);
v4=ResoutSysteme(M5,v1);
VecteurAffiche(v4);
MatriceDestructeur(&M5);
  */
int n=5;
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

  TestGauss(n,A,B);
  
  double A1[4][4]={{10.,7.,8.,7.},
		  {7.,5.,6.,5.},
		  {8.,6.,10.,9.},
		  {7.,5.,9.,10.}};
  
  B1[0] = 32. ;
  B1[1] = 23. ;
  B1[2] = 33. ;
  B1[3] = 31.;

   TestGauss(4,A1,B1);

  BB1[0] = 32.1 ;
  BB1[1] = 22.9 ;
  BB1[2] = 33.1 ;
  BB1[3] = 30.9;
  TestGauss(4,A1,BB1);

  double A2[4][4]={{0.,0.,1.,0.},
		   {0.,0.,0.,1.},
		   {1.,0.,0.,0.},
		   {0.,1.,0.,0.}};

  double B2[4] = {1.,2.,3.,4.} ;
  //TestGauss(4,A2,B2);
  double A3[5][5] = {{1.,2.,4.,8.,16.},
		     {2.,4.,8.,16.,31.},
		     {4.,8.,16.,31.,61.},
		     {8.,16.,31.,61.,120.},
		     {16.,31.,61.,120.,236.}};
  double B3[5]={31.,61.,120.,236.,464.};
  // TestGauss(5,A3,B3);

}


