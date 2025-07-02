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


// builds diagonal matrix

template <class V_iterator, class D_iterator>
void mtx_diag ( V_iterator v, int n, D_iterator d )
{
	const int total = n*n, n1 = n+1 ;
	
	// zero matrix
	D_iterator a = d ;
	for ( int i = 0 ; i < total ; ++i, ++a )
		*a = 0 ;
		
	// fill diagonal
	a = d ;
	for ( int i = 0 ; i < n ; ++i, ++v, a += n1 )
		*a = *v ;
}


template <class T>
void mtx_diag ( const AVector<T> &v, Mtx<T> &d )
{
	d.resize(v.n(),v.n()) ;
	mtx_diag(v.p,v.n(),d.p) ;
}

}

