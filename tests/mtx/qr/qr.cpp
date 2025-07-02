/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#include "../common/common.h"

#include <cognit/io/matrix.cxx>


#include <cognit/mat/vector/len.cxx>
#include <cognit/mat/vector/dot.cxx>


#include <cognit/mat/matrix.cxx>
#include <cognit/mat/matrix/convert.cxx>
#include <cognit/mat/matrix/equ.cxx>
#include <cognit/mat/matrix/eye.cxx>
#include <cognit/mat/matrix/scale.cxx>
#include <cognit/mat/matrix/add.cxx>
#include <cognit/mat/matrix/cleanup.cxx>
#include <cognit/mat/matrix/trans.cxx>
#include <cognit/mat/matrix/outer.cxx>
#include <cognit/mat/matrix/mul.cxx>



template <class matrix_type>
int matrix_test ( matrix_type &a )
{
	using namespace cognit ;
	using namespace apl ;
  
	typedef typename matrix_type::value_type value_type ;
  
  
	int M = a.m(), N = a.n() ;
	AMatrix<value_type> A, B, C, I, H, V, Q, R ;
	AVector<value_type> v, x ;
	value_type xm, vd, two=2 ;
  
  R = a ;
  
  mtx_i(N,B) ;  // matrix B will contain the vectors v
  
  int i, j, k ;

  for ( i = 0 ; i < N-1 ; i++ ) {
    // generation of vector x, take lower elements
    for ( j = i, v.resize(N-i), x.resize(N-i) ; j < M ; ++j )
      v[j-i] = x[j-i] = R[j][i] ;
      
    if ( R[i][i] > 0 )
      v[0] += vct_len(x) ;
    else
      v[0] -= vct_len(x) ;
      
    // remember the vector
    for ( j = i ; j < M ; j++ )
      B[j][i] = v[j-i] ;

    if ( (vd = vct_dot(v,v)) != 0 ) {

      // building householder matrix
      mtx_i(N-i,I), mtx_i(N,H) ;
      mtx_sub(I,mtx_scale(vct_outer(v,v,V),two/vd),V) ;
    
      for ( k = i ; k < N ; k++ )
        for ( j = i ; j < N ; j++ )
          H[j][k] = V[j-i][k-i] ;

      // applying householder matrix
      mtx_mul(H,R,C) ;
      R = C ;
    }
    
  }
  
  // build the Q matrix
  mtx_i(N,Q) ;
  for ( i = N-2 ; i >= 0 ; i-- ) {
    // form vector v
    for ( j = i, v.resize(N-i) ; j < M ; j++ )
      v[j-i] = B[j][i] ;
    
    if ( (vd = vct_dot(v,v)) != 0 ) {
    
      // building householder matrix
      mtx_i(N-i,I), mtx_i(N,H) ;
      mtx_sub(I,mtx_scale(vct_outer(v,v,V),two/vd),V) ;
    
      for ( k = i ; k < N ; k++ )
        for ( j = i ; j < N ; j++ )
          H[j][k] = V[j-i][k-i] ;

     
      mtx_mul(H,Q,C) ;
      Q = C ;
    }
  }
  
  mtx_mul(Q,R,A) ;  // the multiplication must give the same matrix
  
  mtx_cleanup(A) ;
  mtx_cleanup(R) ;
  mtx_cleanup(Q) ;
  
  
  
  
  

/*  
  matrix_type A, Q, R, S, I ;
  matrix_type ldu, pda ;
  
  R = a ;
  
  mtx_qr ( R, Q ) ;
*/  


  if ( !opt_silent ) {
    *output_stream << "Q:" << std::endl << Q << std::endl ;
    *output_stream << "R:" << std::endl << R << std::endl ;
  }
  

	if ( !mtx_equ_fuzzy(A,a) )
		throw std::runtime_error("error: A != QR") ;
    
  // R has to be right-upper triangular
  
	// Q has to be orthonormal
	mtx_mul(Q,mtx_t(Q,B),I) ;
  
	//mtx_cleanup(I) ;
  
  
	if ( !mtx_equ_i_fuzzy(I) )
  		throw std::runtime_error("error: Q is not orthonormal") ;
  
  
	return 0 ;
}



template <class T>
int test()
{
	int ret_code = 0 ;
  
	using namespace cognit ;

	AMatrix<T> a ;

	// read matrix
	input_matrix(*input_stream_list[0],a) ;
    
	if ( a.m() != a.n() )
		throw apl::AException("matrix is not square") ;
      
	//if ( a.m() == 2 ) {
	//  AMatrix2<float_type> m ;
	//  ret_code = matrix_test<AMatrix2<float_type> >(mtx_convert(a,m)) ;
	//} else if ( a.m() == 3 ) {
	//  AMatrix3<float_type> m ;
	//  ret_code = matrix_test<AMatrix3<float_type> >(mtx_convert(a,m)) ;
	//} else if ( a.m() == 4 ) {
	//  AMatrix4<float_type> m ;
	//  ret_code = matrix_test<AMatrix4<float_type> >(mtx_convert(a,m)) ;
	//} else if ( a.m() == 5 ) {
	//  AMatrixN<float_type,5> m ;
	//  ret_code = matrix_test<AMatrixN<float_type,5> >(mtx_convert(a,m)) ;
	//} else {
		ret_code = matrix_test<AMatrix<T> >(a) ;
	//}

	return ret_code ;
}


#include "../common/common.cpp"
#include "../common/common_main.cpp"

