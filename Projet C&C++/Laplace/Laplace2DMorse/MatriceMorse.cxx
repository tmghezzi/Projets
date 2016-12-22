#include <iostream>
using namespace std;
#include "MatriceMorse.hxx"

void MatriceMorse::CalculeTaille()
{
  
}

void MatriceMorse::Alloue()
{
}

void MatriceMorse::Delete()
{
}

void MatriceMorse::Initialise( double * B)
{
}

MatriceMorse::MatriceMorse(int n , int  * NCNN ,  int * CNN ):N(n),NombreColonnesNonNulles(NCNN),ColonnesNonNulles(CNN)
{
}


MatriceMorse::MatriceMorse(const MatriceMorse &M):N(M.N),NombreColonnesNonNulles(M.NombreColonnesNonNulles),ColonnesNonNulles(M.ColonnesNonNulles),L(M.L)
{
}

void MatriceMorse::CalculPointeurLignes()
{
} 

MatriceMorse & MatriceMorse::operator = (const MatriceMorse &M)
{
}

MatriceMorse::~MatriceMorse()
{
}


Vecteur MatriceMorse::operator * (const Vecteur &V)
{
}



Vecteur MatriceMorse::GradientConjugue(const Vecteur & B , double epsilon)
{

}

ostream & operator << ( ostream & sortie ,const MatriceMorse & M)
{
  return sortie ;
}
