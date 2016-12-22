#include <iostream>
using namespace std;
#include "MatriceBande.hxx"


int Maximum(int x,int y) {return ((x<y)?y:x);}
int Minimum(int x,int y) {return ((x<y)?x:y);}

MatriceBande::MatriceBande(int n , int d):N(n),D(d)  //instancie N et D
{
  L=(2*D+1)*N;
  if(n==0){
    A=NULL;  
  }
  else{
    A=new double[L];
    Initialise(NULL);
  }
}


MatriceBande::MatriceBande(const MatriceBande &R)
{
  cout<<"Constructeur par recopie"<<endl;
  N=R.N;
  D=R.D;
  L=R.L;
  A=new double[L];
  Initialise(R.A);
}


MatriceBande::~MatriceBande()
{
  cout<<"MatriceBande destructeur"<<endl;
  delete [] A;
}

double & MatriceBande::operator ()( int i,int j) 
{
  return A[N*(D+i-j)+j];
}

int MatriceBande::Indice(int i,int j)
{  
  return N*(D+i-j)+j;
}

Vecteur MatriceBande::operator * (const Vecteur &V)
{    

  MatriceBande & M=*this;
  Vecteur Resultat(N);
  double Som;
  if(M.N==V.GetN())
    {
      for(int i=0;i<N;i++)
	{
	  Som = 0.;
	  for(int k=0;k<N;k++)
	    {	  
	      if(Indice(i,k)<M.L)
		{
		  Som=Som+(i,k)*V[k];
	 
		}
	      else
		{
		  Som=Som;
		} 
	    }
	  Resultat[i]=Som;
	}
    }

  return Resultat;
}

void MatriceBande::Factorise()
{
  int i,j,k;
  double quotien;

  for(i=0;i<=N-1;i++){

    for(k=i+1;k<=Minimum(N-1,i+D);k++){

      quotien=((*this)(k,i)/(*this)(i,i));
      (*this)(k,i)=quotien;
      for(j=i+1;j<=Minimum(N-1,i+D);j++){
	(*this)(k,j)=(*this)(k,j)- quotien*((*this)(i,j));
      }
    }
  }

}

Vecteur MatriceBande::Resoudre( const Vecteur & V)
{
  cout<<"resout"<<endl;
  Vecteur X(N);
  (*this).Factorise();
  int k,i;
  double somme=0;
  //Descente
  for(i=0;i<=N-1;i++){
    somme=0.;
    for(k=Maximum(0,i-D);k<=Minimum(N-1,i-1);k++){
      somme+=(*this)(i,k)*X[k];
    }
    X[i]=V[i]-somme;
  }
  //Remonter
  for(i=N-1;i>=0;i--){
    somme=0;
    for(k=i+1;k<=Minimum(N-1,i+D);k++){
      somme+=(*this)(i,k)*X[k];
    }
    X[i]=(X[i]-somme)/(*this)(i,i);
  }
  cout<<"FinResout"<<endl;
  return X;
}


void  MatriceBande::Affiche()
{
 
  cout <<"Dimension="<<N<<endl;
  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      if((j>=i-D)&&(j<=i+D)){
	cout<<(*this)(i,j)<<" ";
      }
      else{
	cout<<"0 ";
      }
    }
    cout<<endl;
  }
} 

MatriceBande & MatriceBande::operator = (const MatriceBande &M)
{
  if(this!=&M){
    delete []A;
    N=M.N;
    D=M.D;
    L=M.L;
    A=new double[L];
    Initialise(M.A);
  }
  return *this;
}

Vecteur MatriceBande::GradientConjugue(const Vecteur & B , double epsilon)
{
  MatriceBande & M=*this;  
 
  Vecteur X(B); 
  Vecteur R0(N);  
  Vecteur R1(N);
  Vecteur P(N); 
  double Beta=0.;  
  double Alpha=0.;
  int i=0;
R0=B-M*X;
 
  P=R0;
  while((R0.NormeCarree()<=(epsilon*epsilon))&&i<N)
    { 
 
      Alpha=(R0.NormeCarree()/(M*P*P));
      X=X+Alpha*P;
      R1=R0;
      R0=R0-Alpha*(M*P);
      P=R0+Beta*P;
      Beta=(R1.NormeCarree()/R0.NormeCarree());
      i++;
    }
  return X;
}

void MatriceBande::Initialise(double *X){
  MatriceBande &M=*this;
  if(X!=NULL){
    for(int i=0;i<L;i++){
      M.A[i]=X[i];
    }
  }
  else{
    for(int i=0;i<L;i++){
      M.A[i]=0;

    }
  }
}

