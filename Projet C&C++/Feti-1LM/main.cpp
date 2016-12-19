# include <iostream>
# include <memory.h>
# include <cstdio>
# include <sys/time.h>
# include <math.h>
# include <vector>
# include "ConjugateGradient.h"
# include "SkylineMatrix.h"
# include "SparseMatrix.h"
# include <mpi.h>

using namespace std;



#define Aelt(i,j) Aelt[(i)*N+(j)]
#define MatrixLil SparseMatrixLil<double>

void AfficheMatrice(int dim, Skyline<double> &matrix)
{
	int q = dim;
	for( int i = 0 ; i < q ; i++)
	{
		for( int j = 0 ; j < q ; j++)
		{
			printf(" %7.5lg\t ", matrix(i,j) );
			
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

	//Largeur et hauteur du domaine
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

//Décomposition pour le préconditionneur
void DecompositionParBloc(int ni, int nj, int myrank, Skyline<double> &sA, MatrixLil &Aii,MatrixLil &Aif,MatrixLil &Afi,MatrixLil &Aff)
{      
	//Aii: bloc interaction noeud interne
	//Aif & Afi: bloc interaction noeud interne-interface
	//Aff:bloc interface

	//Aff:bloc interface
	int coeff = (ni+1)*nj;
	int pointeur = (myrank%2)?coeff:0;

	for(int i = 0; i < nj+1 ; i++)
	{
		for(int j = 0; j < nj+1 ; j++)
		{
			Aff.addEntry(coeff+i,coeff+j,sA(pointeur+i,pointeur+j));
		}
	}

	coeff = nj+1;
	pointeur = (myrank%2)?0:coeff;
	//Aii:bloc interaction noeud interne
	for(int i = 0; i < ni*(nj+1) ; i++)
	{
		for(int j = 0; j < ni*(nj+1) ; j++)
		{
			Aii.addEntry(i,j,sA(pointeur+i,pointeur+j));
		}
	}


	coeff = ni*(nj+1);
	//Afi:bloc interaction noeud interne-interf
	if(myrank == 0)
	{
		pointeur = ni*(nj+1);
		for(int i = 0; i < nj ; i++)
		{
			Afi.addEntry(coeff+i,coeff+i-(nj+1),sA(pointeur+i,pointeur+i-(nj+1)));
			Afi.addEntry(coeff+i,coeff+i-nj,sA(pointeur+i,pointeur+i-nj));

			Aif.addEntry(coeff+i-(nj+1),coeff+i,sA(pointeur+i-(nj+1),pointeur+i));
			Aif.addEntry(coeff+i-nj,coeff+i,sA(pointeur+i-nj,pointeur+i));
		}
		Afi.addEntry(coeff+nj,coeff-1,sA(pointeur+nj,pointeur-1));
		Aif.addEntry(coeff-1,coeff+nj,sA(pointeur-1,pointeur+nj));
	}
	else if( myrank == 1)
	{
		pointeur = 0;
		Afi.addEntry(coeff,coeff+(nj+1),sA(pointeur,pointeur+(nj+1)));
		Aif.addEntry(coeff+(nj+1),coeff,sA(pointeur+(nj+1),pointeur));
		for(int i = 1; i < nj+1 ; i++)
		{
			Afi.addEntry(coeff+i,coeff+i+(nj+1),sA(pointeur+i,pointeur+i+(nj+1)));
			Afi.addEntry(coeff+i,coeff+i+nj,sA(pointeur+i,pointeur+i+nj));

			Aif.addEntry(coeff+i+(nj+1),coeff+i,sA(pointeur+i+(nj+1),pointeur+i));
			Aif.addEntry(coeff+i+nj,coeff+i,sA(pointeur+i+nj,pointeur+i));
		}
	}

}

void prodAx(void* ptrA, int *noeud_interf, int dim, int myrank, const double* u, double* v /*sorti*/)
{

	Skyline<double>& A = *(Skyline<double>*)ptrA;

	double *w1 = new double[dim*dim];
	double *d1 = new double[dim];
	memset(v,0.,dim*sizeof(double));
	memset(d1,0.,dim*sizeof(double));
	memset(w1,0.,dim*dim*sizeof(double));

	int coeff =  (myrank%2)? 1:-1; 
	//Résolution linéaire par rapport à lambda
	//Calcul produit Bt*u
	for(int i = 0; i < dim ; i++)
	w1[noeud_interf[i]] = coeff*u[i];

	//Résolution par la méthode directe
	A.solve(1,w1);

	for(int i = 0; i < dim ; i++)
	d1[i] = coeff*w1[noeud_interf[i]];

	MPI_Allreduce((double*)d1,v,dim,MPI_DOUBLE,MPI_SUM, MPI_COMM_WORLD);

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

	int myrank, nbprocs;
	MPI_Init(&nargc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &nbprocs); 

	char NameFile[256];

	int i,j;
	//Subdivision (ex:8 mailles)
	const int ni = 4;
	const int nj = 2;

	//Nombre de Domaine
	const int NbDomaine = nbprocs;
	const int ni_loc = ni/NbDomaine;
	const int xglobal = (ni_loc)*myrank;

	//Dim egale au nombre de noeuds sur tout le domaine (ex: 15 noeuds)
	int dim = (nj+1)*(ni+1);

	//dim_loc egale au nombre de noeuds dans chaque sous domaine (ex: 9 noeuds)
	//Deux fois les noeuds à l'interface?!
	int dim_loc = (ni_loc+1)*(nj+1);
	double t1, t2, tempstot = 0.;

	MatrixLil sA1(dim_loc);

	LaplaceLocal(ni, nj,NbDomaine,sA1);


	t1 = gtime();
	Skyline<double> A(sA1);
	t2 = gtime()-t1;
	tempstot += t2;

	cout << "Time to convert sparse Lil matrix to skyline matrix : " << t2 << "sec.\n";
	sprintf(NameFile,"Matrix%d.dat",myrank);
	FILE*file = fopen(NameFile, "w");
	for( int i = 0 ; i < dim_loc ; i++)
	{
		for( int j = 0 ; j < dim_loc ; j++)
		{
			fprintf(file," %7.5lg\t ", A(i,j) );
			
		}
		fprintf(file,"\n");
	}
	fclose(file);

	t1 = gtime();
	A.factorize();
	t2 = gtime()-t1;
	cout << "Time to factorize skyline matrix : "
	<< t2 << "sec.\n";
	tempstot += t2;

	printf("After factorization : nz(A) = %d\n",A.nz());

	// Second membre local
	double* b_loc = new double[dim_loc];
	int* noeud_interf = new int[nj+1];
	memset(b_loc ,0,dim_loc*sizeof(double));

	for ( int i = 0; i < nj + 1; i++ )
	{
		if(myrank == 0)
		{
			b_loc[i] = 1.;
			noeud_interf[i] = (ni_loc)*(nj+1)+i; 
		}
		if(myrank == 1)
		{
			b_loc[(ni_loc)*(nj+1)+i] = 1.;
			noeud_interf[i] = i;
		}

	}
	cout<< "--------- Second membre ----------"<<endl; 
	AfficheVecteur(dim_loc, b_loc);


	double *u_loc = new double[dim_loc];
	memcpy(u_loc,b_loc,dim_loc*sizeof(double));

	t1 = gtime();
	A.solve(1,u_loc);
	t2 = gtime()-t1;
	tempstot += t2;
	cout << "Time to solve one rhs with skyline matrix : " << t2 << "sec.\n";

	//Sauvegarde de la solution local
	if(myrank == 0)
	{
		printf("Saving solution of -lapl.u = 0 with BC u|left = 1 :\n");
	}
	else
	{
		printf("Saving solution of -lapl.u = 0 with BC u|right = 1 :\n");
	}

	sprintf(NameFile,"SolutionDom%d.dat",myrank);
	file = fopen(NameFile, "w");
	for ( i = 0; i < ni_loc+1; i++ )
	{
		for ( j = 0; j < nj+1; j++ )
		{
			fprintf(file,"%g\t %g\t %g\n",(i+xglobal)/(1.*ni),j/(1.*nj),u_loc[i*(nj+1)+j]);
		}
	}
	fclose(file);

	// Verification de la solution local :
	SparseMatrix<double> spA1(sA1);
	double* f = spA1*(u_loc);

	double err = 0.;
	for ( int i = 0; i < dim_loc; i++ )
	{
		f[i] -= b_loc[i];
		err += f[i]*f[i];
	}
	cout << "Myrank: "<<myrank<<" Error on solution : ||b-A.u||L2 = " << sqrt(err) << endl;



	//----- Systéme linéaire par rapport à lambda -----
	double *b_interface_loc = new double[nj+1];
	double *b_interface_tot = new double[nj+1];

	int coeff =  (myrank %2 )? 1:-1; 

	//B*A{-1}*f
	for(int i = 0; i < nj+1 ; i++)
	b_interface_loc[i] = coeff*u_loc[noeud_interf[i]];



	MPI_Allreduce((double*)b_interface_loc,b_interface_tot,nj+1,MPI_DOUBLE,MPI_SUM, MPI_COMM_WORLD);
	cout<< "--------- b_interface_tot ----------"<<endl; 
	AfficheVecteur(nj+1, b_interface_tot);

	int nbiter = 0;
	int niterMax = 500;

	double eps = 1.e-5;
	double graderr = 0.;
	double *x =  new double[nj+1];
	memset(x,0.,(nj+1)*sizeof(double));

	printf("\n------ Debut Calcul gradientConj ----- rank: %d \n", myrank);
	t1 = gtime();
	nbiter = GradConj(&A, noeud_interf, nj+1 ,myrank, x, (const double*)b_interface_tot, prodAx,niterMax, eps, &graderr);
	t2 = gtime()-t1;
	tempstot += t2;
	cout <<"Myrank: " << myrank << " Temps de résolution du probléme à l'interface: "<< t2 << endl;


	cout<< "--------- blambda ----------"<<endl; 
	AfficheVecteur(nj+1, x);

	//--------Nouvelle resolution mais cette fois avec lambda-----------

	// ulambda_loc contient temporairement f-Bt*lambda
	double *ulambda_loc =  new double[dim_loc];
	memcpy(ulambda_loc,b_loc,dim_loc*sizeof(double));

	coeff = (myrank%2)?-1:1;

	for(int i = 0 ; i < nj+1 ; i++)
	ulambda_loc[noeud_interf[i]] = coeff*x[i];

	t1 = gtime();
	A.solve(1,ulambda_loc);
	t2 = gtime()-t1;
	tempstot += t2;

	sprintf(NameFile,"SolutionLambdaDom%d.dat",myrank);
	file = fopen(NameFile, "w");
	for ( i = 0; i < ni_loc+1; i++ )
	{
		for ( j = 0; j < nj+1; j++ )
		{
			fprintf(file,"%g\t %g\t %g\n",(i+xglobal)/(1.*ni),j/(1.*nj),ulambda_loc[i*(nj+1)+j]);
		}
	}
	fclose(file);

	sprintf(NameFile,"SolutionInterfaceDom%d.dat",myrank);
	file = fopen(NameFile, "w");
	for ( i = 0; i < nj+1; i++ )
	{

		fprintf(file,"%g\n",ulambda_loc[noeud_interf[i]]);
	}
	fclose(file);

	cout <<"Myrank: " << myrank << " Temps total:" << tempstot << endl;
	//destructeur
	delete []noeud_interf;
	delete []b_interface_loc;
	delete []b_interface_tot;
	delete []u_loc;
	delete []b_loc;
	delete []f;
	delete []x;

	MPI_Finalize();
	return EXIT_SUCCESS;
}
