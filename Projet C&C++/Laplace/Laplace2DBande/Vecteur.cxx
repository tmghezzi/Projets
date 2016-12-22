#include "Vecteur.hxx"
#include <math.h>


//Constructeur
Vecteur::Vecteur(int n, double * A)
{
  cout<<"Taille de l'argument="<<sizeof(A)<<endl;
  N=n;
  if(n==0){
    Coor=NULL;  
  }
  else{
    Coor=new double[N];
    Initialise(A);

  }
}

//Constructeur par recopie
Vecteur::Vecteur(const Vecteur & V)
{
  cout<<"Constructeur par recopie"<<endl;
  N=V.N;
  Coor=new double[N];
  Initialise(V.Coor);
}

//Destructeur
Vecteur::~Vecteur()
{
cout<<"Vecteur destructeur"<<endl;
  delete [] Coor;
}


//Initialise le vecteur
void Vecteur::Initialise(double * F)
{
 if(F!=NULL){
    for(int i=0;i<N;i++){
      Coor[i]=F[i];
    }
  }
  else{
    for(int i=0;i<N;i++){
      Coor[i]=0;
    }
  }
}


double & Vecteur::operator[](int i) const
{
  return Coor[i];
}


Vecteur & Vecteur::operator+=(const Vecteur & V)
{
  for(int i=0;i<N;i++){
    Coor[i]+=V.Coor[i];
  }

  return *this;
}

Vecteur & Vecteur::operator-=(const Vecteur & V)
{
 for(int i=0;i<N;i++){
    Coor[i]-=V.Coor[i];
  }

  return *this;
}

Vecteur operator-(const Vecteur & V1, const Vecteur & V2)
{

  Vecteur R(V1.N);
  for(int i=0;i<V1.N;i++){
     R.Coor[i]=V1.Coor[i]-V2.Coor[i] ; 
}
  return R;
}

Vecteur operator+(const Vecteur & V1, const Vecteur & V2)
{
  Vecteur R(V1.N);
  for(int i=0;i<V1.N;i++){
     R.Coor[i]=V1.Coor[i]+V2.Coor[i] ; 
}
  return R;
}
// Produit scalaire
// ----------------
double Vecteur::operator * (const Vecteur & V)
{
  double Scalaire=0;
  for(int i=0;i<N;i++){
     Scalaire+=Coor[i]*V.Coor[i] ; 
}
  return Scalaire;
}

Vecteur operator * (double a , const Vecteur & V)
{
  Vecteur R(V.N);
  for(int i=0;i<V.N;i++){
     R.Coor[i]=a*V.Coor[i] ; 
}
  return R;
}

double 	Vecteur::Norme () const
{
    double somme=0;
  for(int i=0;i<N;i++){
     somme+=Coor[i]*Coor[i] ; 
}
return sqrt(somme);
}

double Vecteur::NormeCarree() const 
{
    double somme=0;
  for(int i=0;i<N;i++){
     somme+=Coor[i]*Coor[i] ; 
}
return somme;
}
 
Vecteur & Vecteur::operator = (const Vecteur & V)
{
  if(this!=&V){
  delete []Coor;
  N=V.N;
  Coor=new double[N];
  Initialise(V.Coor);
  }
  return *this;
}

void Vecteur::Affiche() const
{
  int i;
  cout <<"Dimension="<<N<<endl;
  for(int i=0;i<N;i++){
    cout<<""<<Coor[i]<<endl;
}
}
int Vecteur::GetN() const {
return N;
}
void Vecteur::SetN(int x){
N=x;
}
