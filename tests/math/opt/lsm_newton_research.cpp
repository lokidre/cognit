/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#include "../common/common.h"
#include "../common/load.h"


#include <cognit/mat/vector.cxx>
#include <cognit/mat/vector/io.cxx>
#include <cognit/mat/opt/lsm.cxx>
#include <cognit/mat/matrix.cxx>
#include <cognit/mat/matrix/inv.cxx>
#include <cognit/mat/matrix/mul.cxx>
#include <cognit/mat/matrix/mul_vct.cxx>
#include <cognit/mat/matrix/add.cxx>


#include <vector>


apl::ABuffer<double> x_data, y_data ;
int n ;


//
// define the function - distance from functions 
//
template <class T>
T f ( const T *a, const int m, T *d )
{
	// determine the sum of squares
	T s = 0 ;
	
	const T *pa = a ;
	T t ;
	
	const double *px=x_data.get(), *py=y_data.get() ;
	
	for ( int i = 0 ; i < n ; ++i, ++px, ++py ) {
		t = *py - ( a[0]* *px + a[1] ) ;
		s += t*t ;
	}
	
	return s ;
}

template <class T>
T fx0 ( const T *a, const int m, T *d )
{
	// determine the sum of squares
	T s = 0 ;
	
	const T *pa = a ;
	T t ;
	
	const double *px=x_data.get(), *py=y_data.get() ;
	
	for ( int i = 0 ; i < n ; ++i, ++px, ++py ) {
		t = *py - ( a[0]* *px + a[1] ) ;
		s += t*t ;
	}
	
	return s ;
}




template <class T>
void test()
{
	using namespace std ;
	using namespace cognit ;
	
	
	
	load_xy(*input_stream_list[0],x_data,y_data,n) ;
	
	
	
	//
	// conditions
	// N variables
	// M functions
	//
	

	AVector2<T> x ;
	const int N = 2 ;
	AVector2<T> d ;  // derivatives
	
	AMatrix2<T> J, J1 ;  // jacobian matrix
	AVector2<T> F ;
	
	// do the iteration: G(x) = x - J(x)^-1F(x)
	

	// give some starting approximation
	x.a[0] = x.a[1] = 0 ;
	
	const int max_iter = 20 ;
	
	for ( int iter = 0 ; iter < max_iter ; iter++ ) {
	
		// calculate jacobian matrix and current value of F
		for ( int i = 0 ; i < N ; ++i ) {
			F.a[0] = F.a[1] = f(x.a,N,d.a) ;
		
			J.a[0][0] = d.a[0] ;
			J.a[0][1] = d.a[1] ;
			J.a[1][1] = d.a[0] ;
		
			J.a[1][0] = J.a[0][1] ;
		}
	
		// calculate J(x)^-1 F
		mtx_inv(J,J1) ;
		// x = x - J1*F ;  TODO: doesn't work
	}
	
	


	*output_stream << x << endl ;
}


#include "../common/common.cpp"
#include "../common/common_main.cpp"


