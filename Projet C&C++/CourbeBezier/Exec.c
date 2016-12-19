#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void SauvegardeFonction(char f[], char g[]);
int main( int argc , char ** argv)
{
  char c[20] ;
  char d[20];
  char r[3]="non";
  char s[3]="oui";
  int count = 0 ;
  int ret = 0;
  while ( strncmp(r,"non",3) == 0)
    {
      if ( count > 0 )
	{
	  printf(" Voulez vous changer les fonctions ? oui ou non\n");
	  
	 scanf("%s",s); 
	}
      count++;
      if ( strncmp(s,"oui",3) == 0 ) 
	{
	  printf( "f(x)=");
	  scanf("%s",c);

	  printf("g(x)=");
	  scanf("%s",d);
	  SauvegardeFonction(c,d);
	  printf("Verification de la validite des fonctions F et G ...");
	  system("make clean");
 	  ret = system("make Main") ;
	}

      if(ret==0)
	{
	  printf("Verification terminee avec succes\n");
	  system("./Main");
	}
      else
	{
	  printf("Les fonctions doivent etre tapees comme en langage C/C++\n");
	  exit(1);
	}
      printf("Voulez vous arreter le programme ? oui ou non \n");
      scanf("%s",r);
    }
  return 0;
}
void SauvegardeFonction(char f[], char g[])
{
  FILE * IncludeFile ;
  FILE * SourceFile ;
  IncludeFile=fopen("Fonction.h","w");
  SourceFile=fopen("Fonction.c","w");
  fputs("#include <math.h>\n\ndouble F(double);\ndouble G(double);\n",IncludeFile);
  fputs("#include \"Fonction.h\"\ndouble F(double x)\n{\nreturn ",SourceFile);
  fputs(f,SourceFile);
  fputs(";\n}\n",SourceFile);
  fputs("\ndouble G(double x)\n{\nreturn ",SourceFile);
  fputs(g,SourceFile);
  fputs(";\n}\n",SourceFile);
  fclose(SourceFile);
  fclose(IncludeFile);
}
