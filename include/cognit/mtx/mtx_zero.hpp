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
// Generates zero matrix (fills up with zeroes)
// 
template <class iterator>
void mtx_zero ( iterator a, int m, int n )
{
	int total = m*n ;
	for ( int i = 0 ; i < total ; ++i, ++a )
		*a = 0 ;
}


template <class T>
Mtx2<T> &mtx_zero ( Mtx2<T> &a )
{
	a.a[0][0] = a.a[0][1] = 
	a.a[1][0] = a.a[1][1] = 0 ;
	
	return a ;
}

template <class T>
Mtx3<T> &mtx_zero ( Mtx3<T> &a )
{
	memset ( a.a, 0, a.size()*sizeof(T) ) ;
	
	return a ;
}

template <class T>
Mtx4<T> &mtx_zero ( Mtx4<T> &a )
{
	memset ( a.a, 0, a.size()*sizeof(T) ) ;
	
	return a ;
}


template <class T, int m, int n>
MtxMN<T,m,n> &mtx_zero ( MtxMN<T,m,n> &a )
{
	mtx_zero((T *)a.a,m,n) ;
	return a ;
}



template <class T>
Mtx<T> &mtx_zero ( const int n, Mtx<T> &a )
{
	a.resize(n,n) ;
	mtx_zero(a.p,n,n) ;
	
	return a ;
}



}

