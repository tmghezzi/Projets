#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "CourbeBezier.h"

//Fonction Factorielle...........................................
int factorielle(int i){
  int j,result=1;
  for(j=1;j<=i;j++){
    result*=j;
  }
  return result;

}

//Constructeur Courbe de Bézier..................................
CourbeBezierPtr CourbeBezierConstructeur(int Dimension, int Degre){
  int i;
  CourbeBezierPtr CB;
  CB=(CourbeBezierPtr)malloc(sizeof(CourbeBezier));
  CB->Degre=Degre;
  CB->Dimension=Dimension;
  CB->Ordre=Degre+1;
  for(i=0;i<3;i++){
    (CB->Poles[i])=VecteurConstructeur(Degre+1);
  }
  return CB;
}

//Copie Courbe de Bézier.......................................................
CourbeBezierPtr CourbeBezierCopie( int dimension  , int degre , Vecteur P[] ){
  int i;
  CourbeBezierPtr CB;
  CB=CourbeBezierConstructeur(dimension,degre);
  for(i=0;i<3;i++){
    CB->Poles[i]=VecteurCopie(&P[i]);
  }
  return CB;
}

//Initialise Courbe de Bézier.................................................. 
void CourbeBezierInitialise(CourbeBezierPtr C , double P[][3] ){
  int i,j;
  for(i=0;i<3;i++){
    for(j=0;j<C->Ordre;j++){
      C->Poles[i]->Coord[j]=P[j][i]; 
    }
  
  }

}
//CourbeBezierdestructeur..........................................................
void CourbeBezierDestructeur(CourbeBezierPtr *C ){
  int i;
  for(i=0;i<3;i++){
    VecteurDestructeur(&((*C)->Poles[i]));
  }
  free(*C);
  *C=NULL;
}
//EvalueBernstein.....................................................................

double  EvalueBernstein(int k, int  i, double t){
  double C,result;
  result=(factorielle(k)/(factorielle(i)*factorielle(k-i)))*pow(t,i)*pow(1-t,k-i);
  return result;
}

//CourbeBezierEvalue................................................................
/*
  void CourbeBezierEvalue ( CourbeBezierPtr C , double t , double P[]){
  P[3]={0,0,0};
  int i,j;
  for(i=0;i<3;i++){
  for(j=0;j<C->Ordre;j++){
  P[i]+=EvalueBernstein(C->Degre,j,t)*C->Poles[j]->Coord[i];
  }
   
  }

 
  printf("\nLe vecteur évalue courbe de bézier vaut:(%lf,%lf,%lf)\n",P[0],P[1],P[2]);

  }
*/
void CourbeBezierEvalue (CourbeBezierPtr C, double  t, double P[])
{
  int i,j;
  double Px[C->Ordre];
  double Py[C->Ordre]; 
  double Pz[C->Ordre];
 
  for(i=0;i<=C->Ordre-1;i++)
    {
      Px[i]=C->Poles[0]->Coord[i];
      Py[i]=C->Poles[1]->Coord[i]; 
      Pz[i]=C->Poles[2]->Coord[i];
    }
  for(j=C->Ordre;j>0;j--)
    {

      for(i=0;i<=j-1;i++)
	{
	  Px[i]=(1-t)*Px[i]+t*Px[i+1];
	  Py[i]=(1-t)*Py[i]+t*Py[i+1]; 
	  Pz[i]=(1-t)*Pz[i]+t*Pz[i+1]; 
	}

    }

  P[0]=Px[0];
  P[1]=Py[0]; 
  P[2]=Pz[0];
  printf("\nLe vecteur évalue courbe de bézier vaut:(%lf,%lf,%lf)\n",P[0],P[1],P[2]);
}

//CourbeAffiche...........................................................................
void CourbeBezierAffiche(CourbeBezierPtr C){
  int i,j;
  printf("Les caractéristiques de la courbe de Bezier sont:\nDegre=%d\nDimension=%d\nOrdre=%d\n",C->Degre,C->Dimension,C->Ordre);
  for(i=0;i<3;i++){
    printf("Le poles %d vaut:\n{",i);
    for(j=0;j<C->Ordre;j++){
      printf("%lf,",C->Poles[i]->Coord[j]);
    }
    printf("}\n");
  }
} 
//CourbeBezierDessine......................................................................

void CourbeBezierDessine(CourbeBezierPtr C,char ** argv)
{

  int code;
  pthread_t tid;

  GivenDegree=C->Degre;
  P[0]= C->Poles[0]->Coord;
  P[1]= C->Poles[1]->Coord;
  P[2]= C->Poles[2]->Coord;
  
  code= pthread_create(&tid, NULL, Trace, argv);
  if(code < 0)
    {
      perror("creation du thread failed");
      exit(EXIT_FAILURE);
    }
  // attente des threads
  code= pthread_join(tid, NULL);
  if(code < 0)
    {
      perror("l union du thread failed");
      exit(EXIT_FAILURE);
    }
}

//CourbeConstruit...........................................................................

CourbeBezierPtr ConstruitCourbe(int Dimension , int NbPoints , int Degre , VecteurPtr Points[] ){
  int i,j,m;
  CourbeBezierPtr CB;
  if(NbPoints==Degre+1){
    CB=CourbeBezierConstructeur(Dimension,Degre);
    double *t =ConstruitParametres(Dimension,NbPoints,Points);
    MatricePtr MatriceBernstein=ConstruitMatriceBernstein(Degre,t);
    for(i=0;i<NbPoints;i++){
      printf("Points T  %lf",t[i]);
    }
    printf("bernstein");
    MatriceAffiche(MatriceBernstein);
 
    int *P=(int*)malloc((Degre+1)*sizeof(int));
    int **PP=(int**)malloc((Degre+1)*sizeof(int*));
    //Initialisation du double Pointeur
    for(m=0;m<Degre+1;m++){
      P[m]=m; 
    } 
    for(i=0;i<Degre+1;i++){
      PP[i]=&P[i];
    }
    Gauss(MatriceBernstein,PP);
    VecteurPtr v;
    for(i=0;i<Dimension;i++){
 
 
      v=ResoutSysteme(MatriceBernstein,P,Points[i]);

      CB->Poles[i]=VecteurCopie(v);

      VecteurPtr B=MatriceProduitVecteur(MatriceBernstein,v);
      printf("Verification---------------------------");
      VecteurAffiche(B);
      printf("Points[i]-------------------------------");
      VecteurAffiche(Points[i]);
    }
    CourbeBezierAffiche(CB);
  }

  //Moindre Carré---------------------------------------------
  if(NbPoints>Degre+1){
    CB=CourbeBezierConstructeur(Dimension,Degre);
    double *t =ConstruitParametres(Dimension,NbPoints,Points);

    MatricePtr MatriceMoindreCarre=ConstruitMoindresCarresMatrice(Degre,NbPoints,t);
    printf("Matrice Moindre carre\n");
    MatriceAffiche(MatriceMoindreCarre);
 
    int *P=(int*)malloc((Degre+1)*sizeof(int));
    int **PP=(int**)malloc((Degre+1)*sizeof(int*));
    //Initialisation du double Pointeur
    for(m=0;m<Degre+1;m++){
      P[m]=m; 
    } 
    for(i=0;i<Degre+1;i++){
      PP[i]=&P[i];
    }
    Gauss(MatriceMoindreCarre,PP);

    for(i=0;i<Dimension;i++){
      VecteurPtr v = ResoutSysteme(MatriceMoindreCarre,P,SecondMembre(Degre ,NbPoints ,t,Points[i]));
      VecteurAffiche(v);
      CB->Poles[i]=VecteurCopie(v);
    }

  }

  return CB;
}

double * ConstruitParametres(int Dimension,int NbPoints,VecteurPtr Q[])
{

  int i,j;
  double total=0;
  double *T=(double*)malloc(NbPoints*sizeof(double));
  for(i=0;i<NbPoints;i++){
    T[i] = 0.;
  }
  double P1[Dimension];
  double P2[Dimension];
  
  for(i=0;i<NbPoints-1;i++)
    {
      for(j=0;j<Dimension;j++)
	{
	  P1[j]= Q[j]->Coord[i+1];
	  P2[j]= Q[j]->Coord[i] ;

	}
      T[i+1]=T[i]+DistancePoints(Dimension,P1,P2);
    }
  for (i = 0; i < NbPoints; i++)
    {
      T[i] = T[i]/T[NbPoints-1];
      printf("T[%d]=%lf\n",i,T[i]);
    }
  return T;
}





double DistancePoints(int Dimension,double P[] , double Q[] )
{
  double Result=0;
  int i;
  
  for(i=0;i<Dimension;i++)
    {
      Result += pow( P[i]-Q[i],2);
    }

  
  return sqrt(Result);
}

//MatriceBernstien.............................................................................
MatricePtr ConstruitMatriceBernstein(int Degre,double * Param){
  int i,k;
  MatricePtr B=MatriceConstructeur(Degre+1,Degre+1);
  for(i=0;i<Degre+1;i++){
    for(k=0;k<Degre+1;k++){
      B->Coef2d[k][i]=EvalueBernstein(Degre,i,Param[k]);
    }
  }
  return B;
}

//ConstruitMoindre Carré......................................................................
MatricePtr ConstruitMoindresCarresMatrice(int degre ,int nbpoints , double * Param){
  int i,j,l;
  MatricePtr MoindreC=MatriceConstructeur(degre+1,degre+1);
  for(i=0;i<degre+1;i++){
    for(j=0;j<degre+1;j++){
      MoindreC->Coef2d[j][i]=0;
      for(l=0;l<nbpoints;l++){
	MoindreC->Coef2d[j][i]+=EvalueBernstein(degre,i,Param[l])*EvalueBernstein(degre,j,Param[l]);
      }
    }
  }
  return MoindreC;
}
//SecondMembre.................................................................................

VecteurPtr SecondMembre(int degre ,int nbpoints , double * Param,VecteurPtr Q){
  VecteurPtr Second;
  Second = VecteurConstructeur(degre+1);
  int i,l;
  for(i=0;i<degre+1;i++){
    Second->Coord[i]=0;
    for(l=0;l<nbpoints;l++){
      Second->Coord[i]+=EvalueBernstein(degre,i,Param[l])*Q->Coord[l];
    }
  }
  return Second;
}
//Programme Pincipal.................................................................... 
/*
  int main(){ 
  int i=0,j=0; 
  double P[5][3] ; 
  for(i=0;i<3;i++){ 
  for(j=0;j<5;j++){ 
  P[j][i]=j+1; 
  } 
  } 
  for(i=0;i<5;i++){ 
  for(j=0;j<3;j++){ 
  printf("%lf\n",P[i][j]); 
  } 
  } 
  printf("%d\n",factorielle(3)); 
  CourbeBezierPtr CB = CourbeBezierConstructeur(5,5); 
  printf("Dimension%d ,%d\n",CB->Dimension,CB->Degre); 
  CourbeBezierInitialise(CB,P); 
  CourbeBezierAffiche(CB); 
  printf("Evalue bersntein %lf\n",EvalueBernstein(3,1,0)); 
  //test parametre
  VecteurPtr Q[3]; 
  for(i=0;i<3;i++){ 
  Q[i]=VecteurConstructeur(3); 
  } 
  for(i=0;i<3;i++){ 
  for(j=0;j<3;j++){ 
  Q[i]->Coord[j]=P[j][i]+i;  
  } 
  } 
  for(i=0;i<3;i++){ 
  for(j=0;j<3;j++){ 
  printf("Q %lf\n",Q[i]->Coord[j]);  
  } 
  } 
  printf("Test distance 0,1 %lf \n",DistancePoints(3,Q[0]->Coord,Q[1]->Coord)); 
  double *T=ConstruitParametres(3,3,Q); 
  for(i=0;i<3;i++){ 
  printf("T[%d] vaut %lf\n",i,T[i]); 
  } 
  CourbeBezierPtr cb=ConstruitCourbe(3 ,5, 2 ,Q);
  CourbeBezierAffiche(cb);
  MatricePtr MatriceBernstein=ConstruitMatriceBernstein(3,T); 

  MatricePtr Mc=ConstruitMoindresCarresMatrice(3 ,3 ,T);
  MatriceAffiche(MatriceBernstein); 
  MatriceAffiche(Mc);
  MatriceDestructeur(&MatriceBernstein); 
  MatriceDestructeur(&Mc); 

  } 



*/
