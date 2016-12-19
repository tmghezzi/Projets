#ifndef _NOEUD_H
#define _NOEUD_H
#include <iostream>
#include <string>
using namespace std;
class Noeud
{
  friend ostream &operator<<(ostream &,Noeud &);

private:
  string Nom;
  string Caracteristique;
  Noeud * fg,* fd;
  int id;
  int Racineid;
  int Lien;
 static int instance;
public:
  //Contructeur Noeud
  Noeud(string _Nom="",string _Caracteristique="",int _Lien=0,int _Racineid=0):Nom(_Nom),Caracteristique(_Caracteristique),Lien(_Lien),Racineid(_Racineid),fg(NULL),fd(NULL),id(instance++){};

  //Constructeur par recopie
  Noeud(const Noeud &N);
  
  //Getteur
  string GetNom() const;
  string GetCaracteristique() const;
  Noeud * GetFg() const;
  Noeud * GetFd() const;
  int GetId() const;
  int GetRacineId()const;
  int GetLienParent() const;

  //Setteur
  void SetFg(Noeud *N);
  void SetFd(Noeud *N);
  void SetNom(string);
  void SetCaracteristique(string);
  //Destructeur
  ~Noeud(){ delete fg; delete fd;};
};
#endif
