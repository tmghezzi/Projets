# include <iostream>
# include <memory.h>
# include <cstdio>
# include <sys/time.h>
# include <math.h>
# include <vector>
# include "SkylineMatrix.h"
# include "SparseMatrix.h"


using namespace std;



#define Aelt(i,j) Aelt[(i)*N+(j)]
#define MatrixLil SparseMatrixLil<double>

void AfficheMatrice(int dim, double * matrix)
{
int q = sqrt(dim);
	for( int i = 0 ; i < q ; i++)
	{
		for( int j = 0 ; j < q ; j++)
		{
		  printf(" %7.5lg\t ", matrix[i*q + j] );
		 
		}
		printf("\n");
	}

}

void AfficheVecteur(int dim, double * vecteur)
{
	for( int i = 0 ; i < dim ; i++)
	{
		printf(" %7.5lg\t ", vecteur[i] );
		printf("\n");
	}

}


//Stockage des noeuds pour chaque triangle 
//Numerotage en partant du bas de gauche à droite
void GetTriangleNode(int N,int M,int **Vecteur_Triangle)
{
  int T = 0, C = 0;
  int Boolean = 0;
  for(int j = 1 ; j<=N ; j++)
    {

      if(Boolean == 1)
	C = C + 1;

      for(int i = 1; i<=M ; i++)
	{
	  //Triangle inférieur
	  Vecteur_Triangle[T][0] = C;
	  Vecteur_Triangle[T][1] = M*j+i+j-1;
	  Vecteur_Triangle[T][2] = C+1;
	  T++;

	  //Triangle supérieur
	  Vecteur_Triangle[T][0] = M*j+i+j-1;
	  Vecteur_Triangle[T][1] = M*j+i+j;
	  Vecteur_Triangle[T][2] = C+1;
	  T++;

	  C++;
	}
      Boolean = 1;
    }
}

void LaplaceLocal(int ni, int nj , int NbDomaine,MatrixLil &sA)
{
  double dy,dx,L,M;

  //Largeur et hauteur
  L = 20.0;
  M = 10.0;
  //Taille d'une subdivision
  dx = L/ni;
  dy = M/nj;
  int N = 3;
  double *Aelt = new double[N*N];
  memset(Aelt,0,N*N*sizeof(double));
  
  Aelt(0,0) = (dx*dx+dy*dy)/(2*dx*dx*dy*dy);
  Aelt(0,1) = -1*(dx*dx*dy*dy)/(2*dx*dx);
  Aelt(0,2) = -1*(dx*dx*dy*dy)/(2*dy*dy);
  Aelt(1,0) = -1*(dx*dx*dy*dy)/(2*dx*dx);
  Aelt(1,1) =  (dx*dx*dy*dy)/(2*dy*dy);	
  Aelt(2,0) =  -1*(dx*dx*dy*dy)/(2*dy*dy);
  Aelt(2,2) =  (dx*dx*dy*dy)/(2*dy*dy);


  //Allocation de la matrice 
  int ** TriangleNode = new int* [6*ni*nj];
  for(int i = 0 ; i < 6*ni*nj/NbDomaine ; i++)
    TriangleNode[i] = new int[3];


  //Obtention des noeuds de chaques triangle
  GetTriangleNode(ni/NbDomaine,nj,TriangleNode);
  cout<<"\n\nNoeuds de chaques triangles :\n"<<endl;

  //Print triangle noeuds
  for(int i = 0 ; i < 2*ni*nj/NbDomaine; i++)
    {
      cout<<"Triangle N°:"<<i<<endl;
      for(int j = 0 ; j < 3 ; j++)
	cout<<"i: "<<TriangleNode[i][j]<<endl;
      cout<<"\n\n";
    }


  double val = 0;
  for(int t = 0 ; t < 2*ni*nj/(NbDomaine); t++)
    {
      for(int i = 0 ; i < 3 ; i++)
	for(int j = 0 ; j < 3 ; j++)
	  {
	    val = sA(TriangleNode[t][i],TriangleNode[t][j]);
	    sA.addEntry(TriangleNode[t][i], TriangleNode[t][j],val + Aelt(i,j));
	  }
    }
}



double gtime()
{
  struct timeval tv;
  double t;

  gettimeofday(&tv,NULL);
  t = tv.tv_sec + tv.tv_usec*1.E-6;
  return t;
}

int main(int nargc, char* argv[])
{

  char NameFile[256];

  int i,j;
  //Subdivision (ex:8 mailles)
  const int ni = 4;
  const int nj = 2;
  

  //Dim egale au nombre de noeuds sur tout le domaine (ex: 15 noeuds)
  int dim = (nj+1)*(ni+1);

  double t1, t2,tempstot = 0.;
  
  MatrixLil sA1(dim);

  LaplaceLocal(ni,nj ,1,sA1);


  t1 = gtime();
  Skyline<double> A(sA1);
  t2 = gtime()-t1;
  tempstot += t2;
  cout << "Time to convert sparse Lil matrix to skyline matrix : "
       << t2 << "sec.\n";

  
  t1 = gtime();
  A.factorize();
  t2 = gtime()-t1;
  tempstot += t2;
  cout << "Time to factorize skyline matrix : "
       << t2 << "sec.\n";

  printf("After factorization : nz(A) = %d\n",A.nz());
 
  // Second membre local
  double* b = new double[dim];
  memset(b ,0,dim*sizeof(double));

  for ( int i = 0; i < nj + 1; i++ )
    {
	  b[i] = 1.;

	  b[(nj+1)*(ni)+i] = 1.;

    }

cout<< "--------- Second membre ----------"<<endl; 
AfficheVecteur(dim, b);

  double *u = new double[dim];
  memcpy(u,b,dim*sizeof(double));

  t1 = gtime();
  A.solve(1,u);
  t2 = gtime()-t1;
  tempstot += t2;
  cout << "Time to solve one rhs with skyline matrix : "
       << t2 << "sec.\n";

 
  sprintf(NameFile,"SolutionDomTot.dat");
  FILE* file = fopen(NameFile, "w");
  for ( i = 0; i < ni+1; i++ )
  {
    for ( j = 0; j < nj+1; j++ )
    {
      fprintf(file,"%g\t %g\t %g\n",(i)/(1.*ni),j/(1.*nj),u[i*(nj+1)+j]);
    }
  }
  fclose(file);

  // Verification de la solution local :
  SparseMatrix<double> spA1(sA1);
  double* f = spA1*(u);
  double err = 0.;
  for ( int i = 0; i < dim; i++ )
    {
      f[i] -= b[i];
      err += f[i]*f[i];
    }
  cout <<"Error on solution : ||b-A.u||L2 = " << sqrt(err) << endl;

  cout<<"Temps total:"<< tempstot <<endl;


  //destructeur
  delete []b;
  delete []u;
  delete []f;
  
  return EXIT_SUCCESS;
}
