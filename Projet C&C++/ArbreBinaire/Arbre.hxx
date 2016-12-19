#ifndef _ARBRE_H
#define _ARBRE_H
#include <iostream>
#include "Noeud.hxx"
#include <fstream>
#include <list>
using namespace std;
typedef list<Noeud *>::iterator Itarbre;
class Arbre{
private:
 list<Noeud *> arb;
  int NombreAnimaux;
  string Fichierarbre;
public:
  Arbre(int NbAnimaux=0,string ficha="default.txt");
  Arbre(const Arbre &); 
  Noeud * Racine();
  Noeud *RechercheNode(const int&);
  void AddNoeud(Noeud *Rc,Noeud *F,bool b);
  void LoadFile();
  void SaveFile(Noeud *N);
  void GetNombreAnimaux();
  string GetNameFile() const;
};
#endif
