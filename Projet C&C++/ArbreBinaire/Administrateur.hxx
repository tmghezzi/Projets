#ifndef ADMINISTRATEUR
#define ADMINISTRATEUR
#include <iostream>
#include <string>
#include <fstream>
#include "Utilisateur.hxx"
class Administrateur:public Utilisateur{
private:
int admin;
public:
 Administrateur(string logadm="root",string _pwd="@root",int _stat=0,int _sc=0):Utilisateur(logadm,_pwd,_stat,_sc){};
  //void GestionUtilisateur();
  int SupprimerUtilisateur(string);
  void AfficheUtilisateur();
  int CreerUtilisateur(string,string,int,int);
  bool UtilisateurExiste(string);
  Utilisateur GetAdmin();
};
#endif
