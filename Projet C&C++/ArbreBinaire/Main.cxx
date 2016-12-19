#include <iostream>
#include "Arbre.hxx"
#include "Utilisateur.hxx"
#include "Administrateur.hxx"
#include "md5.hxx"
using namespace std;
int main(){
  /* Noeud Noe("Chien","Poil",0,1);
     Noeud Noe1(Noe);
     cout<<Noe<<endl;
     cout<<Noe1<<endl;
     Noe1.SetNom("hh");
     cout<<Noe<<endl;
     cout<<Noe1<<endl;
     Arbre abr(0,"default.txt");
     cout<<*abr.Racine()<<endl;
     cout<<md5("@123456")<<endl;
     string m5=(string)md5("@123456");
     string m50=(string)md5("Admin1");
     if(m50==m5)
     cout<<"ok"<<endl;
     Utilisateur user("Admin","@123456");
     user.Connection();
     Administrateur admin("admin","@123456");
     admin.AfficheUtilisateur();
     if(!admin.CreerUtilisateur("tar","145632",0,3)){
     cout<<"Création ok";
     }
     if(admin.SupprimerUtilisateur("tars")){
     cout<<"Suppression de tahar ok"<<endl;
     }
  */
  int MenuUtilisateur(string _user,string _mdp);
int MenuAdministrateur(string _user,string _mdp);
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
    cout<<"Veuillez entré votre nom d'utilisateur :"<<endl;
    cin>>username;
    cout<<"Veuillez entré votre password : "<<endl;
    cin>>mdp; 
    if((mdp!="")&&(username!=""))
      int ret=MenuUtilisateur(username,mdp);
    break;
  case 1:
    cout<<"Veuillez entré votre nom d'administrateur: "<<endl;
    cin>>username;
    cout<<"Veuillez entré votre password: "<<endl;
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
      cout<<"Veuillez entré son Pseudo : "<<endl;
      cin>>tmp;
      Admin.SeekUser(tmp);

 break;
   case 3:
     Admin.AfficheUtilisateur();
      break;
    case 4:
      cout<<"Veuillez entré un Pseudo *: "<<endl;
      cin>>username;
      cout<<"Veuillez entré un Password* : "<<endl;
      cin>>pass;
      cout<<"Veuillez entré un status : "<<endl;
      cin>>level;
      cout<<"Veuillez entré un score par défaut : "<<endl;
      cin>>sco;
      Admin.CreerUtilisateur(username,pass,level,sco);
      break;
    case 5:
      cout<<"Veuillez entré un Pseudo  : "<<endl;
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
