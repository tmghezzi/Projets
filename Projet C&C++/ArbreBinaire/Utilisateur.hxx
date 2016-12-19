#ifndef _UTILISATEUR_H
#define _UTILISATEUR_H
#include <iostream>
#include <string>
#include <fstream>
#include "md5.hxx"
#include "Arbre.hxx"
using namespace std;

class Utilisateur
{
protected :
  int statut;
  string pseudo;
  string password;
  int score;

public :
  //Constructeur
  Utilisateur(string user="invité",string pwd="invit",int level=0,int sc=0):pseudo(user),password(pwd),statut(level),score(sc){};
  bool Connection();
  int GetStatut()const;
  string GetPseudo()const;
  string GetPassword()const;
  int GetScore()const;
  void SeekUser(string _user);
  void ChangePassword(string);
  void ChangeScore(int sco);
  void Parti();
  void UserAddAnimal(Arbre arb,Noeud * n, bool cond);
  bool Fin(Noeud * n, bool cond);
  void Trace(string);
};

#endif
