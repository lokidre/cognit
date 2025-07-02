/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
// diagonalization by QR decomposition
// qr [<a file>] [<d file>] [<q file>] [<r file>]

#include "../common/common.h"

#include <cognit/io/matrix.cxx>


#include <cognit/mat/matrix.cxx>
#include <cognit/mat/matrix/qr.cxx>
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
void matrix_test ( matrix_type &a )
{
	using namespace cognit ;
	using namespace apl ;
  
	typedef typename matrix_type::value_type value_type ;


	AMatrix<value_type> D, Q, R ;

	D = a ;

	for ( int iter = 0 ; iter < 1000 ; iter++ ) {

		mtx_qr(D,Q,R) ;
		mtx_mul(R,Q,D) ;
	}

	mtx_cleanup(D) ;

	if ( !opt_silent )
		*output_stream << D << std::endl ;
}



template <class float_type>
void test()
{
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
		matrix_test<AMatrix<float_type> >(a) ;
	//}
}

#include "../common/common.cpp"
#include "../common/common_main.cpp"

