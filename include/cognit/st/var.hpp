/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#if HeaderDescription__

Variance is a measure of its statistical dispersion

Discrete variation is defined as sum of squares of values and mean value

#endif


#include "mean.hpp"

namespace cognit {

//
// With this version user has to supply the mean value
//
template <class T>
T var ( const T *a, int n, T m )
{
	if ( n <= 1 )
		return T(0) ;

	const T *pa = a ;
	T var = 0 ;
	const T n_1 = T(n-1) ;

	for ( int i = 0 ; i < n ; ++i, ++pa )
		var += (*pa-m)*(*pa-m)/n_1 ;

	return var ;
}


//
// Calculates variance
//
template <class T>
T var(const T *a, int n) {
    return var(a,n,mean(a,n)) ;
}

}  // namespace

