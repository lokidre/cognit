/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#if 0 

Test for Legendre polynomials


The main property of Legendre polynomials is their orthogonality

    \int_{-1}^{1} { P_l(x) P_m(x) dx} = \frac{2}{2m+1} \delta_{lm}

where 

    \delta_{mn} = 1, l = m \\ 0, l != m

#endif

#include "../common/common.h"

#include <cognit/mat/vector.cxx>
#include <cognit/mat/vector/io.cxx>
#include <cognit/mat/legendre.cxx>
#include <cognit/mat/horner.cxx>





template <class T>
void test()
{
	using namespace cognit ;
	using namespace std ;


	T Pl[legendre_polynomial_max_degree], Pm[legendre_polynomial_max_degree] ;

	// cycle through all combinations
	for ( int l = 0 ; l < legendre_polynomial_max_degree ; ++l ) {
		//legendre

		for ( int m = l ; m < legendre_polynomial_max_degree ; ++m ) {
		}
	}


	AVector<T> k ;
	AVector<T> x ;


	*input_stream_list[0] >> k ;

	*input_stream_list[1] >> x ;


	for ( int i = 0 ; i < x.N ; ++i ) {
		// evaluate using horner method
		T y = horner(k.p,k.N,x.p[i]) ;

		// evaluate using direct method
		T u = 0 ;
		for ( int j = 0 ; j < k.N ; ++j )
			u += pow(k.p[j],j) ;
	}


	cout << x[0] << ' ' << x[1] << ' ' << x[2] << endl ;
}




#include "../common/common.cpp"
#include "../common/common_main.cpp"


