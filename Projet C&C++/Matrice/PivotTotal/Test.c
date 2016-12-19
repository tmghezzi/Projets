#include "Matrice.h"
 int n = 5; 
  int main ( )
{
  void TestGauss( int , double AA[][n] , double A[] );
  int i,j;
  double y;
  double x=0.;
  double A[n][n] ;
  double B[n] ;
  double B1[4] ;
  double BB1[4] ;

  for ( i = 0 ; i < n; i++)
    {
      y=1.;
      B[i]=0.;
      for ( j = 0 ; j <  n ; j++)
	{
          A[i][j] = y ;
	  B[i]+=(j + 1) * y ;
	  y*=x;
	}
      x+=1.;
    }

  //  TestGauss(n,A,B);
  
  double A1[4][4]={{10.,7.,8.,7.},
		  {7.,5.,6.,5.},
		  {8.,6.,10.,9.},
		  {7.,5.,9.,10.}};
  
  B1[0] = 32. ;
  B1[1] = 23. ;
  B1[2] = 33. ;
  B1[3] = 31.;

  // TestGauss(4,A1,B1);

  BB1[0] = 32.1 ;
  BB1[1] = 22.9 ;
  BB1[2] = 33.1 ;
  BB1[3] = 30.9;
  // TestGauss(4,A1,BB1);

  double A2[4][4]={{0.,0.,1.,0.},
		   {0.,0.,0.,1.},
		   {1.,0.,0.,0.},
		   {0.,1.,0.,0.}};

  double B2[4] = {1.,2.,3.,4.} ;
  //  TestGauss(4,A2,B2);
  double A3[5][5] = {{1.,2.,4.,8.,16.},
		     {2.,4.,8.,16.,31.},
		     {4.,8.,16.,31.,61.},
		     {8.,16.,31.,61.,120.},
		     {16.,31.,61.,120.,236.}};
  double B3[5]={31.,61.,120.,236.,464.};
  // TestGauss(5,A3,B3);

}










