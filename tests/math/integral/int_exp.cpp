/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#include "../common/common.h"

#include <cognit/mat/func.cxx>
#include <cognit/mat/integral.cxx>


#include "common_integral.cpp"


template <class T>
struct F {

	T operator() ( const T x )
	{
		return cognit::exp(x) ;
	}

} ;


template <class T>
int test()
{
	using namespace cognit ;

	T a, b ;


	*input_stream_list[0] >> a ;
	*input_stream_list[0] >> b ;

	F<T> f ;

	T s = integral(f,a,b) ;
	*output_stream << s << std::endl ;


	// now test all the values of quadrature
	for ( int degree = 1 ; degree < gquad_max_degree ; degree++ ) {
		*output_stream << degree << " - " << gquad(f,a,b,degree) << std::endl ;
	}

	// print the integral calculated in closed form
	// TODO: 
	// verify_gaussian_quadrature(f,a,b,s) ;
}



#include "../common/common.cpp"
#include "../common/common_main.cpp"
