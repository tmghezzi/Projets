#include "Matrice.h"
#include "Polynome.h"
int main()
{
  double C1[]={1.,2.,3.,4.};
  double C2[]={4.,3.,2.,1.};
  double T[] = {0.,1.,2.,3.};
  double B[] = {1.,10.,49.,142.};
  PolynomePtr P1 ;
  PolynomePtr P2 ;
  PolynomePtr P ;
  VecteurPtr S;
  int i;
 P1  = PolynomeConstructeur(3) ;
PolynomeInitialise(P1,C1);
P2  = PolynomeConstructeur(3) ;
PolynomeInitialise(P2,C2) ;
P=PolynomeAddition(P1,P2); 
printf("\nAddition de P1 et P2.........................................\n");
PolynomeAffiche(P); 
printf("..............................................................\n");
PolynomeDestructeur(&P);  
printf("\nMultiplication de P1 et P2...................................\n");
 P=PolynomeMultiplication(P1,P2);
PolynomeAffiche(P);
printf("..............................................................\n");
PolynomeDestructeur(&P);
P=PolynomeInterpolation(4,T,B) ; 
printf("\nInterpolation................................................\n");
PolynomeAffiche(P);
printf("..............................................................\n");
S=VecteurConstructeur(4); 
for ( i = 0 ; i < 4 ; i++) 
 S->Coord[i] = PolynomeEvalue(P,T[i]) ;
printf("\nVérification de l'interpolation à l'aide de PolynomeEvalue...\n");
VecteurAffiche(S); 
printf("Fin...........................................................\n");
PolynomeDestructeur(&P);
return 1;
}

