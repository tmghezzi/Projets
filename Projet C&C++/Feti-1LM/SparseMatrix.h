#ifndef _SPARSEMATRIX_H_
# define _SPARSEMATRIX_H_
# include "SparseMatrixLiL.h"

/*
  Store symmetric sparse matrix as morse convention :

  ptLines [][]...[][]_____________
          | |___  |______         |
          |     |        |        |
          v     v        v        v
  indCols [][][][][][]...[][][][] x <- adress just after last elements
  coefs   [][][][][][]...[][][][] x
*/
template<typename T>
class SparseMatrix
{
public:
  // Initialize sparse matrix from a list sparse matrix
  SparseMatrix( const SparseMatrixLil<T>& slA ) :
    _ptLines(NULL), _indColumns(NULL), _coefs(NULL)
  {
    int i;
    _ptLines = vector<int>(slA.dim()+1);
    _ptLines[0] = 0;
    for ( i = 0; i < slA.dim(); i++ )
      _ptLines[i+1] = _ptLines[i] + slA._matCoef[i].size();
    _indColumns = vector<int>(_ptLines[slA.dim()]);
    _coefs      = vector<T>(_ptLines[slA.dim()]);
    for ( i = 0; i < slA.dim(); i++ )
    {
      const list<matElt<T> >& spLine = slA._matCoef[i];  
      typename list<matElt<T> >::const_iterator itL = spLine.begin();
      for ( int j = _ptLines[i]; j < _ptLines[i+1]; j++, itL++ )
      {
	_indColumns[j] = (*itL).col;
	_coefs[j]      = (*itL).coef;
	if ( i == _indColumns[j] ) // To be sure than first entry on each line is diagonal :
	{
	  swap(_indColumns[j],_indColumns[_ptLines[i]]);
	  swap(_coefs[j],_coefs[_ptLines[i]]);
	}
      }
    }
  }
  // Initialize the sparse matrix directly with arrays :
  SparseMatrix( int dim, const int* ptLines, const int* indCols, const T* coefs ) :
    _ptLines(NULL), _indColumns(NULL), _coefs(NULL)
  {
    _ptLines    = new int[dim+1];
    memcpy(&_ptLines[0], ptLines, (dim+1)*sizeof(int));
    _indColumns = new int[_ptLines[dim]];
    memcpy(&_indColumns[0], indCols, _ptLines[dim]*sizeof(int)); 
    _coefs      = new T  [_ptLines[dim]];
    memcpy(&_coefs[0], coefs, _ptLines[dim]*sizeof(T)); 
  }

  int dim() const
  {
    return _ptLines.size()-1;
  }

  // Return the number of non zeros coefficients
  int nz() const
  {
    return _indColumns.size();
  }

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

    int k;
    for ( k = _ptLines[i]; k < _ptLines[i+1]; k++ )
      if ( _indColumns[k] == j )
	return _coefs[k];
    return T(0.);
  }



  // Product the result of matrix--vector as a new vector
  T* operator * ( const T* u ) const
  {
    int i;
    T *v = new T[dim()];
    for ( i = 0; i < dim(); i++ )
      // First coefficient in line i is the diagonal :
      v[i] = _coefs[_ptLines[i]]*u[i];
    for ( i = 0; i < dim(); i++ )
    {
      for ( int j = _ptLines[i]+1; j < _ptLines[i+1]; j++ )
      {
	v[i] += _coefs[j]*u[_indColumns[j]];
	// Care about symmetry :
	v[_indColumns[j]] += _coefs[j]*u[i];
      }
    }
    return v;
  }
private:
  vector<int> _ptLines;
  vector<int> _indColumns;
  vector<T>   _coefs;  
};

#endif
