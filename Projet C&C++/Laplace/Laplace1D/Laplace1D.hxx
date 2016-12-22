
class Laplace1D :public MatriceBande
{

 private :

  int N; //nombre de subdivisions
  double (*F)(double);// fonction source
  double (*G)(double);// fonction dirichlet
  Vecteur Solution;

 public :
  Laplace1D(int n= 0, double (*f)(double)=NULL,double (*g) (double)=NULL);
  void SecondMembre(); // Calcule le second membre du systeme
  void InitialiseMatrice();//Calcule la matrice
  void Calcul();
  double operator [](int i) const { return Solution[i];}
void CalculErreur(int);
};

