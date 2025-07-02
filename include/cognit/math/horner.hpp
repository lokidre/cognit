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
		Evaluation of Polynomial using Horner's Method

*/


namespace cognit {


//
// evaluates polynomial
// 
// input:
//	a - polynomial coefficients
//	n - polynomial degree
//	x - value where the polynomial has to be evaluated
//
// output:
// 	returns the value of polynomial
//	q - if not 0, then contains the coefficients of derivative
// 
template <class T>
T horner ( const T *a, int n, T x )
{
	int i ;
	const T *pa = a + (n-1) ;
	T b = *pa ;

	for ( i = 1, --pa ; i < n ; ++i, --pa )
		b = *pa + x * b ;

	return b ;
}

template <class T>
T horner ( const T *a, int n, T x, T *q )
{
	int i ;
	const T *pa = a + (n-1) ;
	T *pq = q + (n-2) ;
	T b = *pa ;

	for ( i = 1, --pa ; i < n ; ++i, --pa, --pq ) {
		b = *pa + x * b ;
		*pq = b ;
	}

	return b ;
}


}  // namespace cognit

