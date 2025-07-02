/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#if 0

Trace of Matrix


Definition:
The trace of matrix is the sum of all its diagonal elements

#endif



namespace cognit {


template <class T>
T mtx_trace ( const *p, const int n )
{
	const int n1 = n+1 ;
	T t = 0 ;
	for ( int i = 0 ; i < n ; ++i, p += n1 )
		t += *p ;
}



template <class T>
T mtx_trace ( const Mtx2<T> &a )
{
	return a.a[0][0] + a.a[1][1] ;
}

template <class T>
T mtx_trace ( const Mtx3<T> &a )
{
	return a.a[0][0] + a.a[1][1] + a.a[2][2] ;
}


template <class T>
T mtx_trace ( const Mtx4<T> &a )
{
	return a.a[0][0] + a.a[1][1] + a.a[2][2] + a.a[3][3] ;
}


template <class T, int n>
T mtx_trace ( const MtxN<T,n> &a )
{
	T t = 0 ;

	for ( int i = 0 ; i < n ; i++ )
		t += a.a[i][i] ;

	return t ;
}


template <class T>
T mtx_trace ( const Mtx<T> &a )
{
	// the trace is defined for a square matrix
	if ( a.m != a.n )
		return 0 ;

	return mtx_trace(a.p,a.n) ;
}


}  // namespace cognit

