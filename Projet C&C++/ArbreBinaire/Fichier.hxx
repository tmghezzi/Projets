#ifndef FICHIER
#define FICHIER
#include <fstream>
#include <list>
#include<string>
#include "Noeud.hxx"
typedef list<Noeud *> Arbre;
using namespace std;
class Fichier{
private:
  string nomfichier;
  int nombrelignes;
public:
  Fichier(string _file="stock.txt",int _nbl=0):nomfichier(_file),nombrelignes(_nbl){}
  void NombreLignes();
  void LoadFile(Arbre &_arbre);
  void SaveFile(const Noeud &N);
  void SetNomFichier(string name);
  void SetNbLignes(int);
  string GetNomFichier();
  int GetNbLignes();
};
#endif
