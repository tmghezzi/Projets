#include "Noeud.hxx"
int Noeud::instance =1;
ostream & operator << (ostream &o, Noeud & N)
{
  o<<"Animal Numero : "<<N.GetId()<<endl<<"Le Nom de l'animal est: "<<N.GetNom()<<endl<<"La caractéristique de l'animal est: "<<N.GetCaracteristique()<< endl<<"Relation"<<N.GetLienParent()<<endl<<"Noeud Id: "<<N.GetRacineId()<<endl;
  return o;
}

Noeud::Noeud(const Noeud &N){
  Nom=N.GetNom();
  Caracteristique=N.GetCaracteristique();
  fg=N.GetFg();
  fd=N.GetFd();
  id=N.GetId() ;
  Racineid=N.GetRacineId();
  Lien=N.GetLienParent();
}

string Noeud::GetNom() const
{
  return Nom;
}

string Noeud::GetCaracteristique () const
{
  return Caracteristique;
}
Noeud * Noeud::GetFg() const
{
  return fg;
}

Noeud * Noeud::GetFd () const
{
  return fd;
}
int Noeud::GetId() const
{
  return id;
}

int Noeud::GetRacineId() const
{
  return Racineid;
}

int Noeud::GetLienParent() const
{
  return Lien;
}

void Noeud::SetFg(Noeud *NFG){
  if(fg==NULL)
    fg=NFG;
  else
    cout<<"Noeud non NULL"<<endl;
}

void Noeud::SetFd(Noeud *NFD){
  if(fd==NULL)
    fd=NFD;
  else
    cout<<"Noeud non NULL"<<endl;
}
void Noeud::SetNom(string _Nom){
  Nom=_Nom;
}
void Noeud::SetCaracteristique(string _Caracter){
Caracteristique=_Caracter;
}
