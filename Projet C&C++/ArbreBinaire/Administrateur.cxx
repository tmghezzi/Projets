#include "Administrateur.hxx"

int Administrateur::SupprimerUtilisateur(string _name){
  ifstream in("bduser.txt");
  string mdp;
  string user;
  string level;
  string score;
  int flag=0;
  string Buffer="";
  string line="";
  string tmp="";
  if(in) //Si le fichier est trouvé
    {
      do
        {
	  in>>user>>mdp>>level>>score;
	  if(user!=_name&&tmp!=user) 
	    Buffer += user+" "+mdp+" "+level+" "+score+"\n"; 
	  if(user==_name){
	    flag=1;
	  cout<<"L'utilisateur "+_name+" a été supprimer"<<endl;
	  }
	  tmp=user;
        }
      while (getline(in,line)); 

      in.close(); 
    }
  ofstream out("bduser.txt"); 
  out<< Buffer; 
  out.close(); 
  return flag;
}
bool Administrateur::UtilisateurExiste(string user){
  int flag=0;
  string line;
  string username;
  string pass;
  string lvl;
  string sc;
  ifstream in("bduser.txt") ;
  while(getline(in,line)&&!flag)
    {
      in>>username>>pass>>lvl>>sc;
      if(username==user){
	flag=1;
      }
    }
  in.close();
return flag;
}

int Administrateur::CreerUtilisateur(string _username,string _pass,int _statut,int _score){
  ofstream out("bduser.txt",ios::app);
  _pass=(string)md5(_pass);
  if(out&&!UtilisateurExiste(_username)){
    out<<_username<<" "<<_pass<<" "<<_statut<<" "<<_score<<endl;
    return 1;  
}
  if(UtilisateurExiste(_username))
    cout<<"Utilisateur éxiste déja dans la base de donnée"<<endl;
  out.close();
  return 0;
}
void Administrateur::AfficheUtilisateur(){
  string line;
  string username,tmp;
  string pass;
  int lvl;
  int sc;
  ifstream in("bduser.txt") ;
  while(getline(in,line))
    {
      in>>username>>pass>>lvl>>sc;
      if(tmp!=username)
      cout<<"Username: "<<username<<" Status: "<<lvl<<" Score: "<<sc<<endl;
tmp=username;
    }
in.close();
}
