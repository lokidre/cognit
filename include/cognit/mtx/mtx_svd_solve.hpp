/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include "mtx_svd.hpp"


namespace cognit {



//
// finds x = V S^-1 U^T b
//
// as input needs U S V of SVD decomposition
//
// needs buffer t of size u (MxN)
//
template <class T, class V, class S, class U, class B, class X>
void svd_solve ( U pu, S ps, V pv, B pb, int m, int n, X px, T *buffer )
{
	T delta = const_delta<T>()() ;
	
	B b ;
	V v, vv ;
	U u ;
	S s ;
	T c, *t ;
	X x ;
	int i, j, k ;
	
	// v = V ^ S^-1
	for ( i = 0, v = pv ; i < n ; ++i ) {
		for ( j = 0, s = ps ; j < n ; ++j, ++v, ++s )
			*v = ( *s > delta )? *v / *s : 0 ;
	}
	
	
	// t = v.U^T
	/*
	for ( i = 0, t = buffer ; i < m ; ++i, vv += n ) {
		for ( j = 0, v = vv ; j < n ; ++j, ++t ) {
			for ( k = 0, c = 0 ; k < n ; ++k, ++v, ++u )
				c += *v * *u ;
			*t = c ;
		}
	}
	*/
			
	for ( i = 0, vv = pv, t = buffer ; i < n ; ++i, vv += n ) {  // for each row of V
		for ( j = 0, u = pu ; j < m ; ++j, ++t ) {  // for each column of U^T
			for ( k = 0, c = 0, v = vv ; k < n ; ++k, ++u, ++v )
				c += *v * *u ;
			*t = c ;
		}
	}
	
	
	
	// x = t.b
	for ( i = 0, x = px, t = buffer ; i < n ; ++i, ++x ) {
		for ( j = 0, c = 0, b = pb ; j < m ; ++j, ++t, ++b )
			c += *t * *b ;
		*x = c ;
	}
	
}


//template <class T>
//void svd_solve_sigma_inv ( T s, const int n )
//{
//}


//
// Solves Ax=b using SVD
// needs U of size A, s size m, v size MxN
// buffer must be of size: MxN
// destroys A
//
template <class A, class B, class X, class U>
void svd_solve ( A a, B b, int m, int n, X x, U s, U v, U buffer)
{
	// first have SVD decomposition of A
	svd_jacobi(a,m,n,s,v) ;
	
	// inverse sigma
	//svd_solve_sigma_inv ( s, const int n ) ;
	
	// find x
	svd_solve ( a, s, v, b, m, n, x, buffer ) ;
}


}  // namespace cognit

