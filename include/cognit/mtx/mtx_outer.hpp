/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once


namespace cognit {


// 
// Mulitplication of vector by vector, giving matrix
// 
// A = a'b
//
// where a=(a_0, a_2, ... a_N) b=(b_0,b_1,...b_M)
//

//
// outer product of vector u_M by v_N produces the matrix m_NxN
//
template <class T>
void vct_outer ( const T *u, const int m, const T *v, const int n, T *a )
{
	for ( int i = 0 ; i < m ; ++i, ++u )
		for ( int j = 0 ; j < n ; ++j, ++v, ++a )
			*a = *u * *v ;
}

template <class T>
void vct_outer ( const Vec<T> &u, const Vec<T> &v, Matrix<T> &m )
{
	m.resize(v.n(), u.n()) ;
	vct_outer(u.p, u.N, v.p, v.N, m.p) ;
}

}  // namespace  cognit




