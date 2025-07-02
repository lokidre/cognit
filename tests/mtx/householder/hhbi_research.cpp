/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
// Householder reduction of matrix A to bidiagonal form B

#include "../common/common.h"

#include <cognit/io/matrix.cxx>

#include <cognit/mat/vector/len.cxx>
#include <cognit/mat/vector/dot.cxx>

#include <cognit/mat/matrix.cxx>
#include <cognit/mat/matrix/convert.cxx>

#include <cognit/mat/matrix/eye.cxx>
#include <cognit/mat/matrix/scale.cxx>
#include <cognit/mat/matrix/add.cxx>
#include <cognit/mat/matrix/cleanup.cxx>
#include <cognit/mat/matrix/trans.cxx>
#include <cognit/mat/matrix/outer.cxx>
#include <cognit/mat/matrix/mul.cxx>


#include <iostream>
#include <fstream>


template <class matrix_type>
int matrix_test ( matrix_type &a )
{
	using namespace cognit ;
  
	typedef typename matrix_type::value_type value_type ;
  
	// do householder diagonalization by its definition
	// then call the function from library 
	// and compare the results
  
	int M = a.m(), N = a.n() ;
	AMatrix<value_type> A, B, C, I, H, V ;
	AVector<value_type> v, x ;
	value_type xm, vd, two=2 ;
  
	A = a ;
  
	int i, j, k ;

	for ( i = 0 ; i < N ; i++ ) {
		// generation of vector x, take lower elements
		for ( j = i, v.resize(N-i), x.resize(N-i) ; j < M ; j++ )
			v[j-i] = x[j-i] = A[j][i] ;
      
		if ( A[i][i] > 0 )
			v[0] += vct_len(x) ;
		else
			v[0] -= vct_len(x) ;
      

    if ( (vd = vct_dot(v,v)) != 0 ) {

      // building householder matrix
      mtx_i(N-i,I), mtx_i(N,H) ;
      mtx_sub(I,mtx_scale(vct_outer(v,v,V),two/vd),V) ;
    
      for ( k = i ; k < N ; k++ )
        for ( j = i ; j < N ; j++ )
          H[j][k] = V[j-i][k-i] ;

      // applying householder matrix
      mtx_mul(H,A,C) ;
    }
    
    // do the same with transpose
    if ( i < N-2 ) {
      mtx_t(C,A) ;
      
      for ( j = 0, v.resize(N-i-1), x.resize(N-i-1) ; j < M-i-1 ; j++ )
        v[j] = x[j] = A[j+i+1][i] ;
      
      if ( A[i+1][i] > 0 )
        v[0] += vct_len(x) ;
      else
        v[0] -= vct_len(x) ;
        
      if ( (vd = vct_dot(v,v)) != 0 ) {
        mtx_i(N-i-1,I), mtx_i(N,H) ;
        mtx_sub(I,mtx_scale(vct_outer(v,v,V),two/vd),V) ;
    
        for ( k = i+1 ; k < N ; k++ )
          for ( j = i+1 ; j < N ; j++ )
            H[j][k] = V[j-i-1][k-i-1] ;
	    
        mtx_mul(H,A,C) ;
	
        mtx_t(C,A) ;
      }

      
    } else {
      A = C ;
    }
    
  }

/*  
	mtx_cleanup(A) ;
  
	B=a ;
	mtx_householder_bidiag_basic(B) ;
  
	mtx_cleanup(A) ;


	if ( !opt_silent ) {  
		*output_stream << A << std::endl ;
		*output_stream << B << std::endl ;
	}
  

	if ( !mtx_equ_fuzzy(A,B) )
		throw apl::AException("failed") ;
  */
	return 0 ;
}



template <class float_type>
int test()
{
	int ret_code = 0 ;
  
	using namespace cognit ;

	AMatrix<float_type> a ;

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
		ret_code = matrix_test<AMatrix<float_type> >(a) ;
	//}

	return ret_code ;
}


#include "../common/common.cpp"
#include "../common/common_main.cpp"
