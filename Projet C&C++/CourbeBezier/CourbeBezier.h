#ifndef COURBEBEZIER
#define COURBEBEZIER
#include "Vecteur.h"
#include "Matrice.h"
#include <unistd.h>
#include <pthread.h>
#include <math.h>
#include <GL/glut.h>
typedef struct Bezier
{
  int Degre ;
  int Dimension ;
  int Ordre; // degre + 1
  VecteurPtr Poles[3] ;
}CourbeBezier,*CourbeBezierPtr;
#endif
int GivenDegree;
double *P[3] ;
void * Trace( void *);
CourbeBezierPtr CourbeBezierConstructeur(int  , int  );
void CourbeBezierInitialise(CourbeBezierPtr  , double P[][3] );
CourbeBezierPtr CourbeBezierCopie( int  , int  , Vecteur P[] );
void CourbeBezierDestructeur(CourbeBezierPtr * );
void CourbeBezierEvalue ( CourbeBezierPtr , double  , double P[]) ;
void CourbeBezierDessine(CourbeBezierPtr ,char ** );
void CourbeBezierDessine(CourbeBezierPtr ,char ** );
CourbeBezierPtr ConstruitCourbe(int  , int , int  , VecteurPtr Points[] );
double * ConstruitParametres(int,int,VecteurPtr Q[]) ;
double DistancePoints(int ,double P[] , double Q[] );
double  EvalueBernstein(int , int  , double );
MatricePtr ConstruitMatriceBernstein(int,double * );
MatricePtr ConstruitMoindresCarresMatrice(int ,int , double * );
VecteurPtr SecondMembre( int, int, double *,VecteurPtr );
