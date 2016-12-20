#include <iostream>
#include "Arbre.hxx"
#include "Utilisateur.hxx"
#include "Administrateur.hxx"
#include "md5.hxx"
using namespace std;

int MenuUtilisateur(string _user,string _mdp);
int MenuAdministrateur(string _user,string _mdp);
int main(){
  int choix[3];
  string username="";
  string mdp="";
  int quit=0;
 while(quit!=1){
  cout<<"/****************Menu Principal****************/"<<endl;
  cout<<"/ 0: Connection Utilisateur                    /"<<endl;
  cout<<"/ 1: Panneaux d'administation                  /"<<endl;
  cout<<"/ 2: Quitter l'application                     /"<<endl;
  cout<<"/**********************************************/"<<endl;
  cout<<"Votre choix: ";
  cin>>choix[0];
  cout<<endl;
  switch(choix[0]){
  case 0:
    cout<<"Veuillez entrer votre nom d'utilisateur :"<<endl;
    cin>>username;
    cout<<"Veuillez entrer votre password : "<<endl;
    cin>>mdp; 
    if((mdp!="")&&(username!=""))
      int ret=MenuUtilisateur(username,mdp);
    break;
  case 1:
    cout<<"Veuillez entrer votre nom d'administrateur: "<<endl;
    cin>>username;
    cout<<"Veuillez entrer votre password: "<<endl;
    cin>>mdp;
	MenuAdministrateur(username,mdp);
    break;
 case 2:
    cout<<"A bientôt"<<endl;
    quit=1;
    break;
  }
 }
  return 0;
}
int MenuUtilisateur(string _user,string _mdp){
  int res=0;
  string tmp;
  Utilisateur User(_user,_mdp);
   int choixUser=-1;
  if(User.Connection()){
while(res!=1){
    cout<<"/****************  Menu Utilisateur  ****************/"<<endl;
    cout<<"/ 0: Jouer à une partie d'Akanimal                   /"<<endl;
    cout<<"/ 1: Changer de Mot de passe                         /"<<endl;
    cout<<"/ 2: Voir le score d'un Joueur                       /"<<endl;
    cout<<"/ 3: Retourner au Menu Principal                     /"<<endl;
    cout<<"/****************************************************/"<<endl;
    cout<<"Votre choix: ";
    cin>>choixUser;
    cout<<endl;
   
    switch(choixUser){
    case 0:
      cout<<"C Parti"<<endl;
      User.Parti();
      break;
    case 1:
      cout<<"Veuillez entrer votre ancien Mot de passe :"<<endl;
      cin>>tmp;
      tmp=(string)md5(tmp);
      if(User.GetPassword()==tmp){
	cout<<"Veuillez entrer le Nouveau mot de passe : "<<endl;
	cin>>tmp;
	tmp=(string)md5(tmp);
	User.ChangePassword(tmp);
      }
      else{
	cout<<"Echec lors du changement de mot de passe"<<endl;	
      }
 break;
    case 2:
      cout<<"Veuillez entré son Pseudo : "<<endl;
      cin>>tmp;
      User.SeekUser(tmp);

 break;
    case 3:
      cout<<"Retour"<<endl;
      res=1;
      break;
    }
      
  }
  }
  
  return res;
}

int MenuAdministrateur(string _user,string _mdp){
  int res=0;
  string tmp;
  Administrateur Admin(_user,_mdp);
   string username;
      string pass;
      int level=0;
      int sco  =0;
      int choixUser=-1;
  if(Admin.Connection()&&Admin.GetStatut()){
while(res!=1){
    cout<<"/****************  Menu Administrateur  ****************/"<<endl;
    cout<<"/ 0: Jouer à une partie d'Akanimal                      /"<<endl;
    cout<<"/ 1: Changer de Mot de passe                            /"<<endl;
    cout<<"/ 2: Voir le score d'un Joueur                          /"<<endl;
    cout<<"/ 3: Afficher tout les joueurs                          /"<<endl;
    cout<<"/ 4: Créer un Utilisateur                               /"<<endl;
    cout<<"/ 5: Supprimer un Utilisateur                           /"<<endl;
    cout<<"/ 6: Retourner au Menu Principal                        /"<<endl;
    cout<<"/*******************************************************/"<<endl;
    cout<<"Votre choix: ";
    cin>>choixUser;
    cout<<endl;
   
    switch(choixUser){
    case 0:
      Admin.Parti();
      break;
    case 1:
      cout<<"Veuillez entrer votre ancien Mot de passe :"<<endl;
      cin>>tmp;
      tmp=(string)md5(tmp);
      if(Admin.GetPassword()==tmp){
	cout<<"Veuillez entrer le Nouveau mot de passe : "<<endl;
	cin>>tmp;
	tmp=(string)md5(tmp);
	Admin.ChangePassword(tmp);
      }
      else{
	cout<<"Echec lors du changement de mot de passe"<<endl;	
      }
 break;
    case 2:
      cout<<"Veuillez entrer son Pseudo : "<<endl;
      cin>>tmp;
      Admin.SeekUser(tmp);

 break;
   case 3:
     Admin.AfficheUtilisateur();
      break;
    case 4:
      cout<<"Veuillez entrer un Pseudo *: "<<endl;
      cin>>username;
      cout<<"Veuillez entrer un Password* : "<<endl;
      cin>>pass;
      cout<<"Veuillez entrer un status : "<<endl;
      cin>>level;
      cout<<"Veuillez entrer un score par défaut : "<<endl;
      cin>>sco;
      Admin.CreerUtilisateur(username,pass,level,sco);
      break;
    case 5:
      cout<<"Veuillez entrer un Pseudo  : "<<endl;
      cin>>tmp;
      if(tmp!="")
	Admin.SupprimerUtilisateur(tmp);
	  
      break;
    case 6:
      cout<<"Retour"<<endl;
      res=1;
      break;
    }
      
  }
  }
  
  return res;
}
