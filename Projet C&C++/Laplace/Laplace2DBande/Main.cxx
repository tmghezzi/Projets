#include <iostream>
#include "MatriceBande.hxx"
#include "Laplace2D.hxx"
#include "Fonction.hxx"
#include <stdlib.h>
using namespace std;

int main ()
{

  int test = 1;
  int noeud = 0;
  int ask = 0;
  int choix ;
  int impre = 0;
  double epsilon;
  while (test == 1)
    {

      system("clear");
      cout <<"##################################################################"<<endl;
      cout <<"######              Projet Differences finies               ######"<<endl;
      cout <<"##################################################################"<<endl;
      
      cout << "[0] Quitter le programme " << endl;
      cout << "[1] Tester une nouvelle grille " << endl;

      cin >> ask;
      cout << "Votre choix:" << ask << endl;      
      if (ask == 0)
	{
	  test = 0;
	}
      else if (ask == 1)
	{
	  cout << "Entrez le nombre de noeud sur le cote du carre: " << endl;
	  cin >> noeud ;
	  Laplace2D LP2(noeud,F,G);
	  LP2.SecondMembre();
	  LP2.InitialiseMatrice();
	  cout << " Entrer la methode de resolution [0] Gauss"  << endl ;
	  cout << " Entrer la methode de resolution [1] GC"  << endl ;
          cin>> choix ;
	  if ( choix == 1 ) 
	    {
              cout << " Entrer la valeur du test d arret"  << endl ;
	      cin>>epsilon;
	    }
	      LP2.Calcul(choix,epsilon);
	  cout << " Voulez vous l impression de la solution [0] non"<<endl;
          cout << "                                         [1] oui"<<endl;
	  cin>>impre;    
	  LP2.CalculErreur(impre);
	}
    }

  
 return 0;
}
