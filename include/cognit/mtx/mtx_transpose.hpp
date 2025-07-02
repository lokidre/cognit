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
	Transpose (Adjoint) T = adj A where t[i][j] = a[j][i]

*/



namespace cognit {


template <class II, class OI>  // Input and output iterators
void mtx_t ( const II a, int n, int m, OI t )
{
	II col = a, pt, pa ;
	int i, j ;

	for ( j = 0, col = t, pa = a ; j < m ; ++j, ++col )
		for ( i = 0, pt=col ; i < n ; ++i, ++pa, pt+=m )
			*pt = *pa ;
}

// remarks: &A must not be equal &T
template <class M>
M &mtx_t ( const M &a, M &b )
{
	b.resize(a.N,a.M) ;
	mtx_t ( a.p, a.N, a.M, b.p ) ;
	return b ;
}


// remarks: &A must not be equal &T
template <class M>
M &mtx2x2_t ( const M &a, M &t )
{
	t.a[0][0] = a.a[0][0] ;
	t.a[1][1] = a.a[1][1] ;
	t.a[0][1] = a.a[1][0] ;
	t.a[1][0] = a.a[0][1] ;
	return t ;
}

template <class M>
M &mtx2x2_t ( M &a )
{
	std::swap ( a.a[0][1], a.a[1][0] ) ;
	return a ;
}


template <class M>
M &mtx3x3_t ( const M &a, M &b )
{
	b.a[0][0] = a.a[0][0], b.a[0][1] = a.a[1][0], b.a[0][2] = a.a[2][0] ;
	b.a[1][0] = a.a[0][1], b.a[1][1] = a.a[1][1], b.a[1][2] = a.a[2][1] ;
	b.a[2][0] = a.a[0][2], b.a[2][1] = a.a[1][2], b.a[2][2] = a.a[2][2] ;
	return b ;
}


template <class M>
M &mtx3x3_t ( M &a )
{
	typename M::value_type t ;
	t = a.a[0][1], a.a[0][1] = a.a[1][0], a.a[1][0] = t ;
	t = a.a[0][2], a.a[0][2] = a.a[2][0], a.a[2][0] = t ;
	t = a.a[1][2], a.a[1][2] = a.a[2][1], a.a[2][1] = t ;
	return a ;
}



template <class M>
M &mtx4x4_t ( const M &a, M &b )
{
	b.a[0][0] = a.a[0][0] ;
	b.a[1][1] = a.a[1][1] ;
	b.a[2][2] = a.a[2][2] ;
	b.a[3][3] = a.a[3][3] ;
	b.a[0][1] = a.a[1][0] ;
	b.a[0][2] = a.a[2][0] ;
	b.a[0][3] = a.a[3][0] ;
	b.a[1][0] = a.a[0][1] ;
	b.a[1][2] = a.a[2][1] ;
	b.a[1][3] = a.a[3][1] ;
	b.a[2][0] = a.a[0][2] ;
	b.a[2][1] = a.a[1][2] ;
	b.a[2][3] = a.a[3][2] ;
	b.a[3][0] = a.a[0][3] ;
	b.a[3][1] = a.a[1][3] ;
	b.a[3][2] = a.a[2][3] ;
	return b ;
}


template <class M>
M &mtx4x4_t ( M &a )
{
	typename M::value_type t ;

	t = a.a[0][1], a.a[0][1] = a.a[1][0], a.a[1][0] = t ;
	t = a.a[0][2], a.a[0][2] = a.a[2][0], a.a[2][0] = t ;
	t = a.a[0][3], a.a[0][3] = a.a[3][0], a.a[3][0] = t ;
	t = a.a[1][2], a.a[1][2] = a.a[2][1], a.a[2][1] = t ;
	t = a.a[1][3], a.a[1][3] = a.a[3][1], a.a[3][1] = t ;
	t = a.a[2][3], a.a[2][3] = a.a[3][2], a.a[3][2] = t ;

	return a ;
}




// remarks: &A must not be equal &T
template <class M>
M &mtxN_t ( const M &a, M &b )
{
	for ( int i = 0 ; i < a.N ; i++ )
		for ( int j = 0 ; j < a.N ; j++ )
			b.a[i][j] = a.a[j][i] ;
	return b ;
}


template <class M>
M &mtxN_t ( M &a )
{
	typename M::value_type t ;

	for ( int i = 0 ; i < a.N - 1 ; i++ )
		for ( int j = i + 1 ; j < a.N ; j++ )
			t = a.a[i][j], a.a[i][j] = a.a[j][i], a.a[j][i] = t ;
	return a ;
}



}  // namespace cognit

