#ifndef _SPARSEMATRIXLIL_H_
# define _SPARSEMATRIXLIL_H_
# include <list>
# include <vector>
# include <algorithm>
# include <cstdio>
using namespace std;

template<typename T>
struct matElt
{
  int    col;
  T      coef;

  matElt(int j, T val ) : col(j), coef(val) {}
};

/* Sparse List Symmetric matrix ( only diagonal + upper part stored ) */
template<typename T>
class SparseMatrixLil
{
public:
  /* Initialize the SparseMatrixLil with his dimension */
  SparseMatrixLil( int dim ) : _matCoef(dim){}

  /* Add a new non zero entry to the matrix or replace old value. */
  void addEntry( int line, int col, const T& coef );

  T operator() ( int i, int j ) const
  {
    if ( ( i < 0 ) or ( i > dim() ) )
    {
      fprintf(stderr, "Wrong line indice !\n");
      return 0;
    }
    if ( ( j < 0 ) or ( j > dim() ) )
    {
      fprintf(stderr, "Wrong col indice !\n");
      return 0;
    }
    
    if ( i > j )
      swap(i,j);
    const list<matElt<T> >& spLine = _matCoef[i];
    typename list<matElt<T> >::const_iterator itL;
    for ( itL = spLine.begin(); itL != spLine.end(); itL++ )
    {
      if ( (*itL).col == j )
      { // ok, non null coefficient
	return (*itL).coef;
      }
    }
    if ( itL == spLine.end() )
    { // Null coefficient.
      return T(0.);
    }
  }

  /* Return the dimension of the matrix : */
  int dim() const
  {
    return _matCoef.size();
  }
  /* Return the number of non zero coefficient of the matrix */
  int nz() const;
public:
  vector<list<matElt<T> > > _matCoef;

};

template<typename T> void
SparseMatrixLil<T>::addEntry( int line, int col, const T& coef )
{
  if ( ( line < 0 ) || ( line >= dim() ) )
  {
    printf("Bad indice line = %d in addEntry method of SparseMatrixLil !\n",line);
    return;
  }
  if ( ( col < 0 ) || ( col >= dim() ) )
  {
    printf("Bad indice col = %d in addEntry method of SparseMatrixLil !\n",col);
    return;
  }

  if ( line > col )
    swap(line,col);
  list<matElt<T> >& spLine = _matCoef[line];  
  typename list<matElt<T> >::iterator itL;
  for ( itL = spLine.begin(); itL != spLine.end(); itL++ )
  {
    if ( (*itL).col == col )
    { // ok, old entry. Update only the coefficient :
      (*itL).coef = coef;
      break;
    }
  }
  if ( itL == spLine.end() )
  {
    // It's a new entry
    spLine.push_back(matElt<T>(col,coef));
  }
}
// ------------------------------------------------------------------------
template<typename T> int
SparseMatrixLil<T>::nz() const
{ 
  int i;
  int nbZ = 0;
  for ( i = 0; i < _matCoef.size(); i++ )
    nbZ += _matCoef[i].size(); 
  return nbZ;
}

#endif
