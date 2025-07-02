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

#include <cognit/mat/matrix/lu.cxx>
#include <cognit/mat/matrix/mul.cxx>
#include <cognit/mat/matrix/equ.cxx>


template <class matrix_type>
int matrix_test ( matrix_type &a )
{
	using namespace cognit ;
	using namespace apl ;
  
	int *idx = new int[a.size()] ;
  
	matrix_type lu, l, u, p ;
	matrix_type ldu, pda ;
  
	if ( !mtx_lu ( a, lu, idx ) )
		throw std::runtime_error("matrix A is singular") ;

   
	// the test is that it should be L.U = P.A
	mtx_lu_permutation ( idx, a.n(), p ) ;
	mtx_lu_breakup ( lu, l, u ) ;
    
	// ldu = l*u ;
	mtx_mul(l,u,ldu) ;
	mtx_mul(p,a,pda) ;

  
	if ( !opt_silent ) {
		*output_stream << lu << std::endl ;
    
     
		//  *output_stream << l << std::endl << u << std::endl ;
		*output_stream << "L.U \\\n" << ldu << std::endl ;
		*output_stream << "P.A \\\n" << pda << std::endl ;
    
		// *output_stream << "det = " << mtx_lu_det(lu,idx) << std::endl ;
	}
  
	delete[] idx ;
  
	// compare matrices
	if ( !mtx_equ_fuzzy(ldu,pda) )
		throw std::runtime_error("matrix restore test failed") ;

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
		throw std::runtime_error("matrix is not square") ;
      
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

