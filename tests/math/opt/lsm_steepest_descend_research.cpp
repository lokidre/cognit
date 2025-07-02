/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#include "../common/common.h"
//#include "../common/render.h"
#include "../common/load.h"


#include <cognit/mat/vector.cxx>
#include <cognit/mat/opt/lsm.cxx>

#include <vector>


apl::ABuffer<double> x, y ;
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
	
	const T *px=x, *py=y ;
	
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
	
	
	
	load_xy(*input_stream_list[0],x,y,n) ;

	T a[2] ;
	
	


	//*output_stream << a[0] << ' ' << a[1] << endl ;
}


#include "../common/common.cpp"
#include "../common/common_main.cpp"


