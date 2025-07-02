/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#include "../common/common.h"

#include <cognit/mat/polynom/poly3.cxx>
#include <cognit/mat/complex/io.cxx>


template <class T>
void test()
{
	using namespace cognit ;
	using namespace std ;


	T k[3] ;
	AComplex<T> x[3] ;

	*input_stream_list[0] >> k[0] ;
	*input_stream_list[0] >> k[1] ;
	*input_stream_list[0] >> k[2] ;

	solve_poly_3(k,x) ;

	cout << x[0] << ' ' << x[1] << ' ' << x[2] << endl ;
}




#include "../common/common.cpp"
#include "../common/common_main.cpp"

