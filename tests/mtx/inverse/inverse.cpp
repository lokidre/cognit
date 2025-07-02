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

#include <cognit/mat/matrix.cxx>
#include <cognit/mat/matrix/convert.cxx>

#include <cognit/mat/equ.cxx>

#include <cognit/mat/matrix/equ.cxx>
#include <cognit/mat/matrix/inv.cxx>
#include <cognit/mat/matrix/mul.cxx>


template <class matrix_type>
void matrix_test ( matrix_type &A )
{
	using namespace std ;
	using namespace cognit ;

	matrix_type T, I ;
  
	if ( !mtx_inv(A,T) )
		throw runtime_error("matrix A is singular") ;


	// the product of matrix and its inverse should give identity matrix
	mtx_mul(A,T,I) ;
  
  
	if ( !opt_silent ) {
		*output_stream << T << std::endl ;    
	}
  
	if ( !mtx_equ_i_fuzzy(I) )
		throw runtime_error("Error calculating inverse") ;
}


template <class float_type>
void test ()
{
	using namespace cognit ;

	AMatrix<float_type> a ;

	// read matrix
	input_matrix(*input_stream_list[0],a) ;
    
	if ( a.m() != a.n() )
		throw std::runtime_error("matrix is not square") ;
      
	if ( a.m() == 2 ) {
		AMatrix2<float_type> m ;
		matrix_test<AMatrix2<float_type> >(mtx_convert(a,m)) ;
	} else if ( a.m() == 3 ) {
		AMatrix3<float_type> m ;
		matrix_test<AMatrix3<float_type> >(mtx_convert(a,m)) ;
	} else if ( a.m() == 4 ) {
		AMatrix4<float_type> m ;
		matrix_test<AMatrix4<float_type> >(mtx_convert(a,m)) ;
// needed - some error  } else if ( a.m() == 5 ) {
//    AMatrixN<float_type,5> m ;
//    matrix_test<AMatrixN<float_type,5> >(mtx_convert(a,m)) ;
	} else {
		matrix_test<AMatrix<float_type> >(a) ;
	}
}


#include "../common/common.cpp"
#include "../common/common_main.cpp"

