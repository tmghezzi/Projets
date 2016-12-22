#include <iostream>
using namespace std;

class Vecteur 
{
private :
  int N;
  double * Coor;
  
public:
  

  Vecteur(int = 0, double * = NULL); 
  Vecteur(const Vecteur &); 
  ~Vecteur(); 
  int GetN();
  void SetN(int);
  void Affiche()const ;
  void Initialise(double * = NULL);
  friend Vecteur operator+(const Vecteur & , const Vecteur & );
  friend Vecteur operator-(const Vecteur & , const Vecteur & );
  Vecteur & operator=(const Vecteur &);
  Vecteur & operator+=(const Vecteur &);
  Vecteur & operator-=(const Vecteur &);
  friend Vecteur operator * ( double  , const Vecteur &  );
  double operator * ( const Vecteur &  );
  double & operator[](int) const;
  double NormeCarree() const ;
  double Norme() const ;

};
