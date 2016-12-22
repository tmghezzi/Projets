//#include "Vecteur.hxx"
enum Methode {GAUSS,GRADIENTCONJUGUE};
class Laplace2D :public MatriceBande
{

 private :
  Vecteur Solution;
  int N; //nombre de subdivisions
  double (*F)(double,double);// fonction source
  double (*G)(double,double);// fonction dirichlet

 public :
  Laplace2D(int n= 0, double (*f)(double,double)=NULL,double (*g) (double,double)=NULL);
  void SecondMembre(); // Calcule le second membre du systeme
  void InitialiseMatrice();//Calcule la matrice
  void Calcul(int,double =1.e-06);
  double operator [](int i) const { return Solution[i];}
  void CalculErreur(int) ;
};

