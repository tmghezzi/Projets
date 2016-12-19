/* Implementation of a symmetric skyline matrix */
#ifndef _SKYLINEMATRIX_H_
# define _SKYLINEMATRIX_H_
# include "SparseMatrixLiL.h"

template<typename T>
class Skyline
{
public:
  /* Build Skyline matrix from Sparse List matrix */
  Skyline( const SparseMatrixLil<T>& spA );

  /* Dimension of the matrix */
  int dim() const { return _skylines.size(); }

  /* Number of potential non zero entries in Skyline matrix */
  int nz() const;

  /* Return the line indice of the first non zero entry at column c */
  int firstLine( int column ) const 
  {
    return column-_skylines[column].size()+1;
  }

  T operator()( int i, int j ) const;

  T& operator ()( int i, int j );

  /* Crout LDLt factorization */
  void factorize();

  /* Solve multi second member problems ( must be called only after factorization call !!!! ) 
     The Rhs are stored as follows :
       Rhs[dim*n] is the first element of the nth rhs.
   */
  void solve( int nrhs, T* rhs ) const;
private:
  vector<vector<T> > _skylines;
};

template<typename T>
Skyline<T>::Skyline( const SparseMatrixLil<T>& spA ) : _skylines(spA.dim())
{
  int i;
  /* For each column, search the minimal line indice of non zero entry */
  int* indMinLines = new int[spA.dim()];
  for ( i = 0; i < spA.dim(); i++ )
    indMinLines[i] = i;

  for ( i = 0; i < spA.dim(); i++ )
  {
    typename list<matElt<T> >::const_iterator itL;
    const list<matElt<T> >& spLine = spA._matCoef[i];  

    for ( itL = spLine.begin(); itL != spLine.end(); itL++ )
    {
      int c = (*itL).col;
      indMinLines[c] = min(indMinLines[c], i);
    }
  }
  /* Allocate and fills non zeros entries of Skyline matrix */
  for ( i = 0; i < dim(); i++ )
    _skylines[i] = vector<T>(i-indMinLines[i]+1, T(0.));
  delete [] indMinLines;
  for ( i = 0; i < spA.dim(); i++ )
  {
    typename list<matElt<T> >::const_iterator itL;
    const list<matElt<T> >& spLine = spA._matCoef[i];  

    for ( itL = spLine.begin(); itL != spLine.end(); itL++ )
    {
      int c = (*itL).col;
      const T& val = (*itL).coef;
      (*this)(i,c) = val;
    }
  }
}
// ========================================================================
template<typename T>
int Skyline<T>::nz() const
{
  int i;
  int nbZ = 0;
  for ( i = 0; i < _skylines.size(); i++ )
    nbZ += _skylines[i].size(); 
  return nbZ;
}
// ========================================================================
template<typename T>
T Skyline<T>::operator()( int i, int j ) const
{
  if (( i >= dim() ) || ( i < 0 ) )
  {
    printf("Wrong line indice = %d !\n",i);
    return T(0.);
  }
  if (( j >= dim() ) || ( j < 0 ) )
  {
    printf("Wrong col indice = %d !\n",j);
    return T(0.);
  }
  // Care about symmetry
  if ( i > j ) swap(i,j);

  if (j-i+1 > _skylines[j].size())
  {
    return T(0.);
  }

  return _skylines[j][j-i];
}
// ========================================================================
template<typename T>
T& Skyline<T>::operator()( int i, int j )
{
  static T zeros(0.);
  if (( i >= dim() ) || ( i < 0 ) )
  {
    printf("Wrong line indice = %d !\n",i);
    return zeros;
  }
  if (( j >= dim() ) || ( j < 0 ) )
  {
    printf("Wrong col indice = %d !\n",j);
    return zeros;
  }
  // Care about symmetry
  if ( i > j ) swap(i,j);

  if (j-i+1 > _skylines[j].size())
  {
    //fprintf(stderr, "Trying to access null entry of skyline matrix !\n");
    return zeros;
  }

  return _skylines[j][j-i];
}
// ========================================================================
/* Crout LDLt factorization for skyline symmetric matrix */
template<typename T>
void Skyline<T>::factorize()
{
  int i,j,k;

  for ( i = 0; i < dim(); i++ )
  {
    T* Ai_ = &_skylines[i][0];
    int fstl = firstLine(i);
    for ( j = fstl+1; j < i; j++ )
    {
      T& Aij = Ai_[i-j];
      T* Aj_ = &_skylines[j][0];
      int fstc = firstLine(j);
      for ( k = max(fstl,fstc); k < j; k++ )
	Aij -= Ai_[i-k]*Aj_[j-k];
    }
    T& Aii = Ai_[0];
    for ( j = firstLine(i); j < i; j++ )
    {
      T S = Ai_[i-j]/_skylines[j][0];
      Aii -= S*Ai_[i-j];
      Ai_[i-j] = S;
    }
  }
}

/* Solve multi second member problems ( must be called only after factorization call !!!! ) 
   The Rhs are stored as follows :
   Rhs[dim*n] is the first element of the nth rhs.
   Output :
      rhs contains the solutions.
*/
template<typename T>
void  Skyline<T>::solve( int nrhs, T* rhs ) const
{
  int n;
  for ( n = 0; n < nrhs; n++ )
  {
    int i,j;
    T* ptR = rhs + n*dim();
    // Forward algorithm :
    for ( i = 1; i < dim(); i++ )
    {
      for ( j = 1; j < _skylines[i].size(); j++ )
	{
	  ptR[i] -= _skylines[i][j]*ptR[i-j];
	}
    }
    // Diagonal inverse :
    for ( i = 0; i < dim(); i++ )
      ptR[i] /= _skylines[i][0];
    // Backward algorithm :
    for ( i = dim()-1; i > 0; i-- )
    {
      for ( j = 1; j < _skylines[i].size(); j++ )
      {
	ptR[i-j] -= _skylines[i][j]*ptR[i];
      }
    }
  }
}

#endif
