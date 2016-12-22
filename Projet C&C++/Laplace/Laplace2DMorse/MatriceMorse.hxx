#include "Vecteur.hxx"
class MatriceMorse
{
 protected :
  int N;// Dimension de la matrice
  int L;// Taille de A: NombreDeDiagonales*N
  double * A;
  int * NombreColonnesNonNulles  ;
  int * ColonnesNonNulles ;

  int * PointeurLignes ;
  void Alloue();
  void Delete();
  void Initialise( double *);
  void CalculeTaille();
  void CalculPointeurLignes();

  void SetNombreColonnesNonNulles(int * NCNN ){NombreColonnesNonNulles =NCNN;}
  void SetColonnesNonNulles(int * CNN) {ColonnesNonNulles = CNN;}
 public :
  MatriceMorse(int = 0 , int * = NULL , int * = NULL); // Constructeur
  MatriceMorse(const MatriceMorse &); //Constructeur par recopie
  MatriceMorse & operator = (const MatriceMorse &); //Opérateur d'affectation
  double *  operator [](int) const ; // retourne le coefficient ij de la matrice
  Vecteur operator * (const Vecteur & );
  void Affiche();
  Vecteur GradientConjugue(const Vecteur & , double=1.e-06);
  ~MatriceMorse();// Destructeur
  friend ostream & operator << ( ostream &  ,const MatriceMorse & );
};

