// Symmetric plain block matrix
#ifndef _SYMMETRICPLAINBLOCK_H_
# define _SYMMETRICPLAINBLOCK_H_
# include <algorithm>
# include "PlainBlock.h"

template<typename T>
class SymPlainBlock : public PlainBlock<T>
{
public:
  /* @name Constructors and destructor
   */
  //@{
  /**
   *  @brief Construct a symmetric plain block matrix
   *  @param dim       The dimension of the matrix
   *
   *  Create a plain symmetric matrix of dimension dim.
   *  Set all coefficients at zeros.
   */
  SymPlainBlock( int dim ) : PlainBlock<T>()
  {
    _nl = _nc = dim;
    _coefs = new T[_nl*_nc];
    memset(_coefs, 0, _nl*_nc*sizeof(T));
  }
  /**
   *  @brief Construct a symmetric plain matrix as subblock of plain matrix A
   *  @param indices      Array of indices ( lines or columns ) where pick coefficients in A
   *  @param A            The matrix where pick the coefficients
   */
  template<typename M>
  SymPlainBlock( const vector<int>& indices, const M& A ) : PlainBlock<T>()
  {
    _coefs = new T[_nl*_nc];
    for ( int i = 0; i < _nl; i++ )
      for ( int j = 0; j <= i; j++ )
	_coefs[((i+1)*i)/2+j] = A(indices[i],indices[j]);
  }
  /**
   *  @brief Copy constructor
   *  @param B    Symmetric matrix to copy
   */
  SymPlainBlock( const SymPlainBlock<T>& B ) : _nl(B._nl), _nc(B._nc), _coefs(NULL)
  {
    _coefs = new T[_nl*_nc];
    memcpy(_coefs, B._coefs, _nl*_nc*sizeof(T));
  }
  /**
   *  @brief Destructor : Destroy all coefficients
   */
  virtual ~SymplainBlock()
  {}  
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
    if ( i < j ) swap(i,j);
    return _coefs[(i+1)*i/2+j];    
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
    if ( i < j ) swap(i,j);
    return _coefs[(i+1)*i/2+j];    
  }
  int dim() const
  {
    return _nl;
  }
  //@}
  /* @name Operators on Symmetric Plainblock matrices
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
	  for ( j = 0; j <= i; j++ )
	  {
	    T& coef = _coefs[i*(i+1)/2+j];
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
	  for ( j = 0; j <= i; j++ )
	  {
	    T& coef = _coefs[i*(i+1)/2+j];
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
	  for ( j = 0; j <= i; j++ )
	  {
	    T& coef = _coefs[i*(i+1)/2+j];
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
	  for ( j = 0; j <= i; j++ )
	  {
	    T& coef = _coefs[i*(i+1)/2+j];
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
    // Here, opA has no incidents;
    y = new T[_nl];
    for ( int i = 0; i < _nl; i++ )
    {
      y[i] = _coefs[i*(i+1)/2]*x[i];
      for ( int j = 0; j < i; j++ )
	y[i] += _coefs[i*(i+1)/2+j]*x[j];
    }
  }
  // CONTINUER AVEC FACTORISATION ET DESCENTE REMONTEE CROUTE
  //@}

};

#endif
