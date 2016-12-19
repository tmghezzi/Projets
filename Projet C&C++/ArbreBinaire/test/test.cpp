 #include<fstream>
#include<iostream>
#include<string>
using namespace std;

int SupprimerUtilisateur(string _name){
  ifstream in("Utilisateur.txt");
  string mdp;
  string user;
  int flag=0;
  string Buffer="";
  string line="";
  string tmp="";
  if(in) //Si le fichier est trouvé
    {
      do
        {
	  in>>user>>mdp;
	  cout<<user<<mdp<<endl;
	  if(user!=_name&&tmp!=user) 
	    Buffer += user+" "+mdp+"\n"; 
	  if(user==_name)
	    flag=1;
	  tmp=user;
        }
      while (getline(in,line)); 

      in.close(); 
    }
  ofstream out("Utilisateur.txt"); 
  out<< Buffer; 
  out.close(); 
  return flag;
}
bool UtilisateurExiste(string user){
  int flag=1;
  string line;
  string username;
  string pass;
  ifstream in("Utilisateur.txt") ;
  while(getline(in,line)&&flag)
    {
      in>>username>>pass;
      if(username==user){
	flag=0;
      }
      in.close();
      return flag;
    }
}
int CreerUtilisateur(string _username,string _pass,int _statut,int _score){
  ofstream out("Utilisateur.txt",ios::app);
  if(out&&!UtilisateurExiste(_username)){
    out<<_username<<" "<<_pass;
    return 1;  
}
  out.close();
  return 0;
}
 int main()
 {
   int flag=1;
   string pseudo;
string password;
         ifstream MonFichier("phrase.txt") ;
while(getline(MonFichier,pseudo)&&flag)
    {
      MonFichier>>pseudo>>password;
      cout<<pseudo<<endl;
      if(pseudo=="tahar"){
	flag=0;
      }
} 
  
if(password=="1545"){
  cout<<"Pass Ok"<<endl;
 }
 else
   cout<<"Mot de Passe Incorrect"<<endl;
  MonFichier.close();


  if( SupprimerUtilisateur("user3")){
    cout<<"Reussi"<<endl;
  }
  else
    cout<<"Erreur lors de la suppression"<<endl;
  if(CreerUtilisateur("Mell","123456",0,0)){
    cout<<"Création réussie"<<endl;
  }
  else
    cout<<"création echoué"<<endl;
	 return 0;
}
