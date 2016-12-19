// ========================================================================
// Plainblock utilities
// ========================================================================
#ifndef _PLAINBLOCK_H_
# define _PLAINBLOCK_H_
# include <cassert>
# include <cstring>
# include <vector>
using namespace std;
/*
  Store a non symmetric plain block
*/
template<typename T>
class PlainBlock
{
public:
  /* @name Constructors to build new plain block
   */
  //@{
  // Default constructor
  PlainBlock() : _nl(0), _nc(0), _coefs(NULL);
  // Build a new plain block of dimension nl x nc
  PlainBlock( int nl, int nc ) : _nl(nl), _nc(nc),
				 _coefs(new T[nl*nc])
  {
    memset(_coefs, 0, nl*nc*sizeof(T));
  }
  // Build the block as a subblock of a matrix A ( copy coefficients )
  // Remark : The object A must have the operator () defined.
  template<typename M>
  PlainBlock( const vector<int>& indLines, const vector<int>& indCols,
	      const M& A) : _nl(indLines.size()), _nc(indCols.size()),
			    _coefs(NULL)
  {
    _coefs = new T[_nl*_nc];
    for ( int i = 0; i < _nl; i++ )
      for ( int j = 0; j < _nc; j++ )
	_coefs[_nc*i+j] = A(indLines[i],indCols[j]);
  }
  // Copy constructor
  PlainBlock(const PlainBlock<T>& B) : _nl(B._nl), _nc(B._nc), _coefs(NULL)
  {
    _coefs= new T[_nl*_nc];
    memcpy(_coefs, B._coefs, _nl*_nc*sizeof(T));
  }
  // Destructor
  virtual ~PlainBlock()
  {
    delete [] _coefs;
  }
  //@}

  /* @name Accessors and modifiers
   */
  //@{
  // Return const ref on B(i,j)
  virtual const T& operator() ( int i, int j ) const
  {
    if ( (i<0) || ( i > _nl) )
    {
      fprintf(stderr, "Wrong line indice %d", i);
      return _coefs[0];
    }
    if ( (j<0) || ( j > _nl) )
    {
      fprintf(stderr, "Wrong col indice %d", j);
      return _coefs[0];
    }
    return _coefs[_nc*i+j];    
  }
  // Return ref on B(i,j)
  virtual T& operator() ( int i, int j )
  {
    if ( (i<0) || ( i > _nl) )
    {
      fprintf(stderr, "Wrong line indice %d", i);
      return _coefs[0];
    }
    if ( (j<0) || ( j > _nl) )
    {
      fprintf(stderr, "Wrong col indice %d", j);
      return _coefs[0];
    }
    return _coefs[_nc*i+j];        
  }
  int nl() const { return _nl; }
  int nc() const { return _nc; }  
  //@}

  /* @name Operators on Plainblock matrices
   */
  //@{
  /* Compute *this <- alpha.op(A).op(B) + beta.(*this)
     where
     Input :
       - alpha : Scalar
       - trA   : if trA == 'T' then op(A) = A^{T} else op(A) = A
       -   A   : plainblock matrix
       - trB   : if trB == 'T' then op(B) = B^{T} else op(B) = B
       -   B   : plainblock matrix B
       - beta  : scalar
     Return :
       At exit of the method, *this contains the result of the operation
   */
  virtual void axpy( const T& alpha, 
		     char trA, const PlainBlock<T>& A, 
		     char trB, const PlainBlock<T>& B,
		     const T& beta)
  {
    int i,j,k;
    // Some verifications :
    if ( (( trA != 'T' ) && ( _nl != A._nl )) || ( _nl != A._nc ) )
    {
      fprintf(stderr, "Dimension of A is incompatible with dimension of this\n");
      return;
    }
    if ( (( trB != 'T' ) && ( _nc != B._nc )) || ( _nc != B._nl ) )
    {
      fprintf(stderr, "Dimension of B is incompatible with dimension of this\n");
      return;
    }
    if ( trA != 'T' )
    {
      if ( trB != 'T' )
      {
	assert(B._nl = A._nc);
	for ( i = 0; i < _nl; i++ )
	{
	  for ( j = 0; j < _nc; j++ )
	  {
	    T& coef = _coefs[i*_nc+j];
	    T z = 0.;
	    for ( k = 0; k < A._nc; k++ )
	      z += A(i,k)*B(k,j);
	    coef = alpha*z + beta*coef;
	  }	  
	}	
      }
      else
      {
	assert(B._nc = A._nc);
	for ( i = 0; i < _nl; i++ )
	{
	  for ( j = 0; j < _nc; j++ )
	  {
	    T& coef = _coefs[i*_nc+j];
	    T z = 0.;
	    for ( k = 0; k < A._nc; k++ )
	      z += A(i,k)*B(j,k);
	    coef = alpha*z + beta*coef;
	  } 
	}		
      }
    }
    else
    { // trA == 'T'
      if ( trB != 'T' )
      {
	assert(B._nl = A._nl);
	for ( i = 0; i < _nl; i++ )
	{
	  for ( j = 0; j < _nc; j++ )
	  {
	    T& coef = _coefs[i*_nc+j];
	    T z = 0.;
	    for ( k = 0; k < A._nl; k++ )
	      z += A(k,i)*B(k,j);
	    coef = alpha*z + beta*coef;
	  }
	}
      }
      else
      {
	assert(B._nc = A._nl);
	for ( i = 0; i < _nl; i++ )
	{
	  for ( j = 0; j < _nc; j++ )
	  {
	    T& coef = _coefs[i*_nc+j];
	    T z = 0.;
	    for ( k = 0; k < A._nl; k++ )
	      z += A(k,i)*B(j,k);
	    coef = alpha*z + beta*coef;
	  }
	}	
      }
    }
  }
  /*
    Product y = op(A).x where op(A) = A^{T} if trA='T' else op(A) = A.    
    Return a new vector.
   */
  virtual T* gemv( char trA, const T* x ) const
  {
    T* y;
    if ( trA != 'T' )
    {
      y = new T[_nl];
      for ( int i = 0; i < _nl; i++ )
      {
	y[i] = T(0.);
	for ( int j = 0; j < _nc; j++ )
	  y[i] += _coefs[i*_nc+j]*x[j];
      }   
    }
    else
    {
      y = new T[_nc];
      for ( int i = 0; i < _nc; i++ )
      {
	y[i] = T(0.);
	for ( int j = 0; j < _nl; j++ )
	  y[i] += _coefs[j*_nc+i]*x[j];
      }
    }
  }
  //@}
protected:
  // Dimension of the block :
  int _nl, _nc;
  // Provides the indices of the subblock's matrix
  // If these vectors are empty, the Plainblock is not a subblock of a matrix
  vector<int> _indicesLine, _indicesCols;
  // Dimension of the matrix containing this subblock ( equal -1 if not a subblock )
  int _dimAL, _dimAC;
  // Coefficient of block ( if subblock's matrix, points only on coefficient of the matrix )
  T* _coefs;
};

#endif
