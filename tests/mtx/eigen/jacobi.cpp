/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#include "../common/common.h"

#include <cognit/mat/matrix/eigen_jacobi.cxx>

#include <cognit/io/matrix.cxx>
#include <cognit/io/vector.cxx>


template <class T>
void test()
{
	using namespace cognit ;
	using namespace std ;


	AMatrix<T> a ;

	*input_stream_list[0] >> a ;

	if ( a.N != a.M )
		throw runtime_error("must be square matrix") ;

	const int n = a.N ;


	AVector<T> e ;
	AMatrix<T> v ;

	AMatrix<T> b, z ;


	// allocate everything
	e.resize(n), v.resize(n,n) ;
	b.resize(n,n), z.resize(n,n) ;


	eigen_jacobi ( a.p, n, e.p, v.p, 10000, b.p, z.p ) ;

	cout << e << endl ;
	cout << endl ;
	cout << v << endl ;
}




#include "../common/common.cpp"
#include "../common/common_main.cpp"

