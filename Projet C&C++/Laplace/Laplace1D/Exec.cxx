#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
using namespace std;
void SauvegardeFonction(string,string);

int main( int argc , char ** argv)
{
  string c;
  string d;
  string r="n";
  string s="y";
  int count = 0 ;
  int ret = 0;
  while ( r == "n")
    {
      if ( count > 0 )
	{
	  cout << " Voulez vous changer les fonctions ? " << endl;
	  cin >> s ;
	}
      count++;
      if ( s == "y" ) 
	{
	  cout << "f(x)=";
	  cin >> c;
	  cout << "g(x)=";
	  cin >> d;
	  SauvegardeFonction(c,d);
	  cout << "Verification de la validite des fonctions F et G ..." << endl;
	  system("make clean");
	  ret = system("make Main") ;
	}

      if(ret==0)
	{
	  cout << "Verification terminee avec succes" << endl;
	  system("./Main");
	}
      else
	{
	  cout << "Les fonctions doivent etre tapees comme en langage C/C++" << endl;
	  exit(1);
	}
      cout << "Voulez vous arreter le programme y or n"<< endl;
	cin >>r ;
    }
  return 0;
}
void SauvegardeFonction(string f,string g)
{
  ofstream fhxx("Fonction.hxx");
  ofstream fcc("Fonction.cxx");
  fhxx << "#include <math.h>\n\ndouble f(double);\ndouble g(double);\n";
  fcc << "#include \"Fonction.hxx\"\ndouble PI =atan(1.);\ndouble f(double x)\n{\nreturn ";
  fcc << f << ";\n}\n";
  fcc <<"\ndouble g(double x)\n{\nreturn ";
  fcc << g << ";\n}\n";
  fhxx.close();
  fcc.close();
}
