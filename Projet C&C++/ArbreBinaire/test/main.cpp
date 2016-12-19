#include <string> //Permet de créer des chaines de caracteres
#include <fstream> //Permet la manipulation des fichiers
#include <iostream>
#include<limits>
using namespace std;
void Trace(string message){
  string fileLog=pseudo+".txt";
  ofstream out(fileLog.c_str(),ios::out|ios::app);
  if(out){
    out<<message;
}
else
  cout<<"Problé lors de l'ouverture du fichier log"<<endl;
}
int main(void){
  Trace("kkjijoko\n");
 Trace("kkjijoko\n");
return 0;
}
