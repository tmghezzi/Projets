//#include "Vecteur.hxx"
#include "MatriceBande.hxx"
#include "Laplace1D.hxx"
#include "Fonction.hxx"
#include <stdlib.h>
int main ()
{

  int test = 1;
  int noeud = 0;
  int ask = 0;
  int impr=0;
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
	  cout<<"Entrez le nombre de noeud du segment: "<<endl;
	  cin >> noeud;
	  Laplace1D LP1(noeud,f,g);
	  LP1.SecondMembre();
	  LP1.InitialiseMatrice();
	  LP1.Calcul();
 cout << " Voulez vous l impression de la solution [0] non"<<endl;
          cout << "                                         [1] oui"<<endl;
	  cin>>impr;
	  LP1.CalculErreur(impr);
	  cin>>ask;
	}
    }

 return 0;
}
