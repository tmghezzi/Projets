#include "Arbre.hxx"

Arbre::Arbre(int NbAnimaux,string ficha):NombreAnimaux(NbAnimaux),Fichierarbre(ficha)
{
  GetNombreAnimaux();
  LoadFile();
}
/*Arbre::Arbre(const Arbre&Arb)
{
 Fichierarbre=Arb.GetNameFile();
 GetNombreAnimaux();
 LoadFile();
 }*/
string Arbre::GetNameFile() const{
  return Fichierarbre; 
}

void Arbre::GetNombreAnimaux(){
  ifstream in(Fichierarbre.c_str()); 
  string ligne;
  int nbLignes = 1;
  while(getline(in, ligne))
    nbLignes++;     
  in.close(); 
  NombreAnimaux=nbLignes-2;
  cout<<"Il y a :"<<NombreAnimaux<<" Animaux"<<endl;
}

Noeud * Arbre::RechercheNode(const int & racineid)
{
  Itarbre it;  
  for (it=arb.begin(); it != arb.end(); ++it)
    {
      Noeud * n = *it;
      if (n->GetId() == racineid)
	return n;
    }

  return NULL; 
}
void Arbre::LoadFile(){
  ifstream in(Fichierarbre.c_str());
  Itarbre it;
  string ligne;
  int i=0;
  string NomAnimal;
  string Caracteristique;
  int id ;
  int Rcid;
  int Lien;
  int nb=NombreAnimaux;
  if(in){
    while (nb)
      {
	getline(in, ligne);
	in>> id >> Rcid >> Lien >> NomAnimal >> Caracteristique;
	arb.push_back(new Noeud(NomAnimal,Caracteristique,Lien,Rcid));
	nb--;
      }
    for(it=arb.begin();it!=arb.end();++it){
      Noeud *n=*it;
      Noeud* NP=RechercheNode(n->GetRacineId());
      if (NP!= NULL)
	{
	  if (n->GetLienParent())
	    NP->SetFg(n);
	  else
	    NP->SetFd(n);
	}
    }
  }
  in.close();
}

Noeud * Arbre::Racine()
{
  Itarbre it = arb.begin();
  return *it;
}

void Arbre::SaveFile(Noeud *n)
{
  ofstream out(Fichierarbre.c_str(),ios::app);
  
  if(out)
    {
      string Nom=n->GetNom();
      string Caracteristique=n->GetCaracteristique();
      int id =n->GetId();
      int Rcid=n->GetRacineId();
      int Fils=n->GetLienParent();
 
      out<<id<<" "<<Fils<<" "<<Rcid<<" "<<Nom<<" "<<Caracteristique<<endl;
    }
  else
    cerr << "Un probleme est survenue lors de l'ouverture du fichier" << endl;
  out.close();
}


void Arbre::AddNoeud(Noeud *Rc,Noeud *addF, bool lien)
{
  if(addF!=NULL){
    if (lien)
      Rc->SetFg(addF);
    else
      Rc->SetFg(addF);
    SaveFile(addF);
  }

}
