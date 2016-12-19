#include<iostream>
#include "Arbre.hxx"
using namespace ArbreFichier;

void Fichier::NombreLignes(){
  ifstream in(nomfichier.c_str()); 
string ligne;
int nbLignes = 0;
while(getline(in, ligne))
nbLignes++;     
in.close(); 
 nombrelignes=nbLignes;
 cout<<nombrelignes<<endl;
}

void Fichier::LoadFile(list<Noeud *> & arbre){
  ifstream in(nomfichier.c_str());
  list<Noeud *>::iterator it;
  string ligne;
  int i=0;
  in.seekg(0, ios::beg);
  string NomAnimal;
  string Caracteristique;
  int id ;
  int Rcid;
  int relation;
    while (getline(in, ligne))
      {
	in>> id >> Rcid >> relation >> NomAnimal >> Caracteristique;
	arbre.push_back(new Noeud(NomAnimal,Caracteristique,Rcid,relation));
      }
    for(it=arbre.begin();it!=arbre.end();++it){
      Noeud *n=*it;
      Noeud* NP=Arbre::RechercheNode(n->GetRacineId());
      cout<<*n;
      if (NP!= NULL)
	{
	  if (n->GetRelation())
	    {
	      NP->SetFg(n);
	    }
	  else
	    {
	      NP->SetFd(n);

	    }
	}
    }
}

