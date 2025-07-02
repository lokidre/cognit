/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

/*

				Legendre Polynomials


*/


namespace cognit {

enum {
	legendre_polynomial_max_degree = 6
} ;


//
// Returns n-th Legendre Polynomial
//
// k has to point to n+1 buffer
template <class T>
void legendre_polynomial ( const int n, T *k )
{
	switch ( n ) {

	case 0 :
		*k++ = 1 ;
		break ;

	case 1 :
		*k++ = 1 ;
		*k++ = 0 ;
		break ;

	case 2 :
		*k++ = T(3)/2 ;
		*k++ = 0 ;
		*k++ = -1 ;
		break ;

	default :
		throw std::runtime_error("unsupported Legendre Polynomial degree") ;
	}
}


}

