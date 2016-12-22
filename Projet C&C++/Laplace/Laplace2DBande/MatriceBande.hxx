#include "Vecteur.hxx"
class MatriceBande
{
 protected :
  int N;// Dimension de la matrice
  int D;// largeur de bande
  int L;// Taille de A:(2*D+1)*N
  double *A;

 public :
  MatriceBande(int, int); //Constructeur arguments : n = dimension et d = largeur de bande
  MatriceBande(const MatriceBande &); //Constructeur par recopie
  MatriceBande & operator = (const MatriceBande &); //Opérateur d'affectation
  double & operator() (int,int); // retourne le coefficient ij de la matrice
  int Indice(int ,int );
  Vecteur operator * (const Vecteur & );
   void Factorise();
  Vecteur Resoudre (const Vecteur &);
  void Affiche();
  Vecteur GradientConjugue(const Vecteur & , double epsilon=1.e-06); 
  ~MatriceBande();// Destructeur
void Initialise(double *B);
};

