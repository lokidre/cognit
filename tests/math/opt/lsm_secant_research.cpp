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

#include <vector>


apl::ABuffer<double> x_data, y_data ;
int n ;


//
// define the function - distance from functions 
//
template <class T>
T f ( const T *a, const int m )
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
	

	AVector2<T> xn, xn_1, xn_2 ;
	const int N = 2 ;
	
	AMatrix2<T> J ;  // jacobian matrix
	AVector2<T> Fn, Fn_1 ;

	AVector2<T> dFn, dFn_1 ;

	// do the iteration: G(x) = x - J(x)^-1F(x)

	//AVector2<T> fxn, fyn, fxn_1, fyn_1 ;

	// give some starting approximation
	xn_2.a[0] = xn_2.a[1] = 0 ;
	xn_1.a[0] = xn_1.a[1] = 1 ;
	xn.a[0] = xn.a[1] = 2 ;

	Fn_1.a[0] = Fn_1.a[1] = f(xn_1.a,N) ;

	AVector2<T> x ;
	
	x.a[0] = xn_1.a[0], x.a[1] = xn_2.a[1] ;
	dFn_1.a[0] = f(x.a,N) - f(xn_2.a,N) ;

	x.a[0] = xn_2.a[0], x.a[1] = xn_1.a[1] ;
	dFn_1.a[1] = f(x.a,N) - f(xn_2.a,N) ;

	const int max_iter = 20 ;
	
	for ( int iter = 0 ; iter < max_iter ; iter++ ) {
	
		// calculate jacobian matrix and current value of F

		// calculate all partial first derivatives
		AVector2<T> x ;
		
		x.a[0] = xn.a[0], x.a[1] = xn_1.a[1] ;
		dFn.a[0] = f(x.a,N) - f(xn_1.a,N) ;

		x.a[0] = xn_1.a[0], x.a[1] = xn.a[1] ;
		dFn.a[1] = f(x.a,N) - f(xn_1.a,N) ;


		J.a[0][0] = dFn.a[0] - dFn_1.a[0] ;
		J.a[0][1] = dFn.a[0] - dFn_1.a[1] ;
		J.a[1][0] = dFn.a[1] - dFn_1.a[0] ;
		J.a[1][1] = dFn.a[1] - dFn_1.a[1] ;

		//}
	
		// calculate J(x)^-1 F
		if ( !mtx_inv(J) )
			break ;

		xn_1 = xn ;
		dFn_1 = dFn ;

		// xn = xn - J*dFn ; TODO: stuck here // find next x

		*output_stream << xn << endl ;

		int a= 0 ;
	}
	
	


}


#include "../common/common.cpp"
#include "../common/common_main.cpp"



