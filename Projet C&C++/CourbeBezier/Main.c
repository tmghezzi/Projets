#include "CourbeBezier.h"
#include "Vecteur.h"
#include "Fonction.h"
int NbPoints ;
double *Q[3] ; 

int main (int argc , char** argv)
{
  int code_error = 0 ;
  int Degre ;
  int i,j;
  double x;
  VecteurPtr V[3] ;
  CourbeBezierPtr C ;
  double Pnt[3] ; 
  glutInit(&argc,argv);
  printf(" Entrer le degre de la courbe a construire \n" );
  scanf("%d",&Degre) ;
  printf(" Entre le nombre n de points a interpoler\n");
  printf(" si n >> degre + 1 alors approximation \n");
  scanf("%d",&NbPoints) ; 
  
  x = 0.;
  for (i = 0 ; i < 3 ; i++)
    Q[i] = (double *)malloc(sizeof(double)*NbPoints) ;


  for (i = 0 ; i < NbPoints ; i++)
    {
      Q[0][i] = x ;
      Q[1][i] = F(x);
      Q[2][i] = G(x) ;
      x+=1./(NbPoints-1) ;
    }

 for (j = 0 ; j < 3 ; j++) 
   {
V[j] = VecteurConstructeur(NbPoints); 
for ( i = 0 ; i < NbPoints ; i++) 
V[j]->Coord[i] = Q[j][i] ; 
 } 

C=ConstruitCourbe(3,NbPoints,Degre,V) ;
 CourbeBezierDessine(C,argv);

 
  return code_error;
}
