#include "Utilisateur.hxx"
#include <sstream>
bool Utilisateur::Connection(){
  int flag=1;
  int level;
  string user;
  string pwd;
  int sc;
  ifstream MonFichier("bduser.txt") ;
  if(MonFichier){
  while(getline(MonFichier,user)&&flag)
    {
      MonFichier>>user>>pwd>>level>>sc;
      if(pseudo==user){
	flag=0;
      }
    } 
  string tmpMD5=(string)md5(password);
  if(tmpMD5==pwd){
    cout<<"Connection Réussie"<<endl;
    cout<<"Chargement de vos paramétres"<<endl;
    statut=level;
    password=pwd;
    score=sc;
    return 1;
  }
  else{
    cout<<"Username/Mot de Passe Incorrect"<<endl;
    return 0;
  }
  MonFichier.close();
  }
  else
    cerr<<"Echec de la connection avec la Base de données"<<endl;
  return 0;
}
void Utilisateur::ChangePassword(string newpass){
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
	  if(user!=pseudo&&tmp!=user) 
	    Buffer += user+" "+mdp+" "+level+" "+score+"\n"; else if(user==pseudo&&tmp!=user){
	    Buffer += user+" "+newpass+" "+level+" "+score+"\n";
	    flag=1;
	  }
	  
	  tmp=user;
	}
     while (getline(in,line)); 
     if(flag){
       cout<<"Le changement c'est bien déroulé"<<endl;
       ofstream out("bduser.txt"); 
       out<< Buffer; 
       out.close(); 
     }
     else 
       cout<<"Probléme rencontré lors du changement de mot de passe"<<endl;
    }
  in.close(); 

}
void Utilisateur::ChangeScore(int sco){
  ifstream in("bduser.txt");
  string mdp;
  string user;
  string level;
  string sc,sc1;
  int flag=0;
  string Buffer="";
  string line="";
  string tmp="";
  if(in) //Si le fichier est trouvé
    {
      do
	{
	  in>>user>>mdp>>level>>sc   ;
	  if(user!=pseudo&&tmp!=user) 
	    Buffer += user+" "+mdp+" "+level+" "+sc+"\n";
	  else if(user==pseudo&&tmp!=user){

	    stringstream out;
	    out << sco;
	    sc1 = out.str();
 
        Buffer += user+" "+mdp+" "+level+" "+sc1+"\n";
	    flag=1;
	  }
	  
	  tmp=user;
	}
     while (getline(in,line)); 
     if(flag){
       cout<<"Le changement c'est bien déroulé"<<endl;
       ofstream out("bduser.txt"); 
       out<< Buffer; 
       out.close(); 
     }
     else 
       cout<<"Probléme rencontré lors du changement du score"<<endl;
    }
  in.close(); 

}
void Utilisateur::SeekUser(string _user){
  string line;
  string username;
  string pass;
  int lvl;
  int sc;
  int res=0;
  ifstream in("bduser.txt") ;
  while(getline(in,line)&&!res)
    {
      in>>username>>pass>>lvl>>sc;
      if(_user==username){
	cout<<"Username: "<<username<<" Score: "<<sc<<endl;   
	res=1;
      }
    }
  if(res==0)
    cout<<"Utilisateur inéxistant"<<endl;
  in.close();
}

int Utilisateur::GetStatut() const{
  return statut;
}
string Utilisateur::GetPseudo()const{
  return pseudo;
}
string Utilisateur::GetPassword()const{
  return password;
}
int Utilisateur::GetScore()const{
  return score;
}
void Utilisateur::Parti(){
 Arbre a(0,"default.txt");
  list<string> listeAnimaux;
  Noeud * n = a.Racine();
  Noeud * nfils = NULL;
  bool cond = true;
  int nbCoups = 0;
  string reponse;
  string tmp;
  while (Fin(n,cond))
    {
      if (nbCoups > 0)
	{
	  n = nfils;
	}
      tmp="Votre animal la caractéristique suivant: "+ n->GetCaracteristique() +"? "+ " y/n";
      Trace(tmp);
      cout<<tmp<<endl;
      cin >> reponse;
      Trace(reponse);
      if (reponse=="y")
	{
	  listeAnimaux.push_back(n->GetNom());
	  nfils = n->GetFg();
	  cond = true;
	}
      else
	{
	  nfils = n->GetFd();
	  cond = false;
	}
      nbCoups++;
    }
  int compteFaux = 0, nbAnimaux = 0;
  list<string>::reverse_iterator it;
  for (it = listeAnimaux.rbegin(); it != listeAnimaux.rend(); ++it)
    {
      nbAnimaux++;
      tmp= "Votre animal est-il "+*it+" ?"+" y/n";
      Trace(tmp);
      cout<<tmp<<endl;
      cin >> reponse;
      Trace(reponse);
      if (reponse=="y")
	{
	  tmp="L'animal est trouve ! C'est un "+ *it+ " !";
	  cout<<tmp<<endl;
	  Trace(tmp);
	  break;
	}
      compteFaux++;
    }

  if (compteFaux == nbAnimaux){
  string nom, caracter,tmp;
  Noeud * newNode = NULL;
  tmp="Quel est le Nom de l'animal ?";
  Trace(tmp);
  cout<<tmp<<endl;;
  cin >> nom;
  Trace(nom);
  tmp="Quelle est sa caracteristique ?";
  Trace(tmp);
  cout<<tmp<<endl;
  cin >> caracter;
  Trace(caracter);
  newNode = new Noeud(nom, caracter, n->GetId(), cond);
  a.AddNoeud(n,newNode, cond);
  }
  ChangeScore(nbCoups);
}
bool Utilisateur::Fin(Noeud * n, bool cond)
{
  if (cond && n->GetFg() == NULL)
    {
      return false;
    }
  else if (!cond && n->GetFd() == NULL)
    {
      return false;
    }
  return true;
}

void Utilisateur::UserAddAnimal(Arbre arb,Noeud * n, bool cond)
{
  string nom, caracter,tmp;
  Noeud * newNode = NULL;
  tmp="Quel est le Nom de l'animal ?";
  Trace(tmp);
  cout<<tmp<<endl;;
  cin >> nom;
  Trace(nom);
  tmp="Quelle est sa caracteristique ?";
  Trace(tmp);
  cout<<tmp<<endl;
  cin >> caracter;
  Trace(caracter);
  newNode = new Noeud(nom, caracter, n->GetId(), cond);
  arb.AddNoeud(n,newNode, cond);
}

void Utilisateur::Trace(string message){
  string fileLog=pseudo+".txt";
  ofstream out(fileLog.c_str(),ios::out|ios::app);
  if(out){
    message=message+"\n";
    out<<message;
  }
  else
    cout<<"Probléme lors de l'ouverture du fichier log"<<endl;
  out.close();
}
