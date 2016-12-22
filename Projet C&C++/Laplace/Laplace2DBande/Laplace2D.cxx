#include <math.h>
#include <iostream>
using namespace std;


#include "MatriceBande.hxx"
#include "Laplace2D.hxx"


Laplace2D::Laplace2D(int n, double (*f)(double,double), double(*g)(double,double)):MatriceBande(n*n,n)
{
  cout<<"Constructeur"<<endl;
  N=n*n;
  G=g;
  F=f;
Solution=(n*n);
}   


void Laplace2D::SecondMembre() 
{
cout<<"----------Second Membre----------"<<endl;
int Nx=sqrt(N);
  int h1= Nx-1;
  Solution[0]=G(0.,0);
  Solution[N-1]=G(1,0);
double h=1./h1;

  for(int i=0; i<=h1; i++)
    {
      for(int j=0; j<=h1; j++)
	{
	  if(i==0||j==0||i==h1||j==h1){
	    Solution[(h1+1)*i+j]=G(i*h,j*h);
	  }
	  else{
	    Solution[(h1+1)*i+j]=F(i*h,j*h);
	  }	
}
    }

  Solution.Affiche();
}


void Laplace2D::InitialiseMatrice()//Calcule la matrice
{
 
  cout<< "------------Initialisation de la Matrice--------"<<endl; 
int Nx=sqrt(N);
  double h2=(Nx-1)*(Nx-1);
  //Bord inférieur
  for (int j=0;j<Nx;j++)
    {
      (*this)(j,j)=1.; 
    }

  for (int i=Nx;i<(N-(Nx+1));i++)
    { 

      if ( i%Nx==0 ){
	(*this)(i,i)=1.;
}
    

  else if (i%Nx==(Nx-1))
    {
      (*this)(i,i)=1.;
    }

  else
    {

      (*this)(i,i-1)=-1.*h2;
      (*this)(i,i-Nx)=-1.*h2;
      (*this)(i,i)=4.*h2;
      (*this)(i,i+1)=-1.*h2;
      (*this)(i,i+Nx)=-1.*h2;
    }
}

//Bord Supérieur
for (int k=N-(Nx+1);k<=(N-1);k++)
  {
    (*this)(k,k)=1.;
  }

(*this).Affiche(); 
}


void Laplace2D::Calcul(int choix,double epsilon)
{
if(choix==0){
  cout<<"Calcul de la solution par la méthode de Gauss"<<endl;
  Solution=Resoudre(Solution); 
  Solution.Affiche();
}
else{
  Solution=GradientConjugue(Solution,epsilon);  
  Solution.Affiche();
}
}

void  Laplace2D::CalculErreur(int impre)
{
int Nx=sqrt(N);
  double h=1./(Nx-1);
  double ErreurMax=0.;
  double ErreurMoy=0.;
  double diff;
  if (impre ==1)
    {
cout<<"Solution calculé"<<"\t"<<"Solution éxacte" <<"\t\t"<<"Erreur"<<endl;
      for(int i=0; i<Nx; i++)
	{
	  for(int j=0; j<Nx; j++)
	    {    
diff=fabs(G(i*h,j*h)-Solution[(Nx)*i+j]); 
ErreurMoy+=diff;
      if(diff>ErreurMax)
	{
	  ErreurMax=diff;

	}
	     
	      cout<<Solution[(Nx)*i+j]<< " \t\t\t"<<G(i*h,j*h)<<" \t \t\t"<<diff<<endl ;
	
	    }
	}
  ErreurMoy/= N;
cout<<" "<<endl;
  cout <<"L'erreur Maximal = " << ErreurMax << " L'erreurMoyenne = " << ErreurMoy << endl;
    }
}
