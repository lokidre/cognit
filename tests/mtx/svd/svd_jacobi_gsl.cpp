/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#include "../common/common.h"

#include <gsl/gsl_linalg.h>

#include <cognit/io/matrix.cxx>
#include <cognit/io/vector.cxx>



#include <cognit/mat/matrix.cxx>
#include <cognit/mat/matrix/equ.cxx>
#include <cognit/mat/matrix/convert.cxx>
#include <cognit/mat/matrix/cleanup.cxx>
#include <cognit/mat/matrix/diag.cxx>
#include <cognit/mat/matrix/trans.cxx>
#include <cognit/mat/matrix/mul.cxx>

#include <cognit/mat/matrix/svd.cxx>


template <class matrix_type>
int matrix_test ( matrix_type &a )
{
	using namespace cognit ;
	using namespace apl ;
  
	typedef typename matrix_type::value_type T ;
  
  
	int M = a.m(), N = a.n() ;

	gsl_matrix *gsl_a = gsl_matrix_alloc(M,N) ;


	for ( int i = 0 ; i < M*N ; ++i )
		gsl_a->data[i] = a.p[i] ;

	gsl_matrix *gsl_v = gsl_matrix_alloc(N,N) ;
	gsl_vector *gsl_s = gsl_vector_alloc(N) ;
	gsl_vector *gsl_w = gsl_vector_alloc(N) ;

	gsl_linalg_SV_decomp_jacobi(gsl_a,gsl_v,gsl_s) ;
	//gsl_linalg_SV_decomp(gsl_a,gsl_v,gsl_s,gsl_w) ;




	AMatrix<T> U(M,N), V(N,N) ;
	AVector<T> s(N) ;

	// V.resize(N,N) ;

	for ( int i = 0 ; i < M*N ; ++i )
		U.p[i] = gsl_a->data[i] ;

	// U.p[2] = 1 ;


	for ( int i = 0 ; i < N*N ; ++i )
		V.p[i] = gsl_v->data[i] ;

	for ( int i = 0 ; i < N ; ++i )
		s.p[i] = gsl_s->data[i] ;
	
	// svd_jacobi(a,U,s,V) ;  // decomposition
	


	// A = U*S*V ;
  
	mtx_cleanup(U) ;
	mtx_cleanup(s) ;
	mtx_cleanup(V) ;
  
  
	if ( !opt_silent ) {
		*output_stream << "U:" << std::endl << U << std::endl ;
		*output_stream << "s:" << '\t' << s << std::endl ;
		*output_stream << "V:" << std::endl << V << std::endl ;
	}
  
  
  
	// verify decomposition
	AMatrix<T> A, VT, S, X ;

	// A = U * diag(s) * V^T	
	mtx_diag(s,S) ;
	mtx_t(V,VT) ;
	mtx_mul(U,S,X) ;
	mtx_mul(X,VT,A) ;
	
	if ( !opt_silent ) {
		*output_stream << "U S V^T:" << std::endl << A << std::endl ;
	}
	
	if ( !mtx_equ_fuzzy(A,a) )
		throw std::runtime_error("error: A != USV") ;
  
    
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
    
	//if ( a.m() != a.n() )
	//	throw apl::AException("matrix is not square") ;
      
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

