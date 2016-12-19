#ifndef _CONJUGATEGRADIENT_H_
# define _CONJUGATEGRADIENT_H_
/*
  Conjugate gradient algorithm :
       An iterative method to solve the linear system A.x = b 
  Input :
    - A         Structure containing some datas useful for product matrix-vector. NULL if none datas useful
    - dim       Dimension of the problem
    - x         Initial guess value for the solution vector
    - b         Right hand side vector. If NULL, set with zeros as coefficients.
    - prodAX    Function which compute the product A.u and store result in v
    - niterMax  Maximal number of iteration to find solution of the linear system
    - eps       Relative tolerance on solution (||b-A.x_(n)||/||b-A.x_0|| < eps )
  Output :
    - err       Final relative error on the solution
    Return the number of iteration to converge on the solution
 */
int GradConj( void* A, int *noeud_interf, int dim, int myrank, double* x, const double* b, 
	void (*prodAx)(void* A, int *noeud_interf, int dim, int myrank, const double* u, double* v /*sorti*/),
	int niterMax, double eps, double* err); 


#endif
