/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include "../vec.hpp"
#include "../const.hpp"


namespace cognit {


//
// Euclidean norm
//
template <class T, class iterator>
T vct_norm2 ( iterator v, int n )
{
	if ( n <= 0 )
		return 0 ;
		
	if ( n == 1 )
		return abs(*v) ;
	
	T s(0) ;  // scale
	T eps = constants::epsilon<T>;
	T av ;
	T sum(0) ;
		
	for ( int i = 0 ; i < n ; ++i, ++v ) {
		av = abs(*v) ;
		if ( av < eps )  // dont' care about small values
			continue ;
		
		if ( av > s ) {
			sum = sum*sqr(s/av) + 1 ;
			s = av ;
		} else {
			sum += sqr(av/s) ;
		}
	}
	
	return s*sqrt(sum) ;
}

}
