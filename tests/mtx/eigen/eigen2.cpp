/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#include "../common/common.h"

#include <cognit/mat/matrix/eigen_values.cxx>

#include <cognit/io/complex.cxx>
#include <cognit/io/matrix.cxx>
#include <cognit/io/vector.cxx>


template <class T>
void test()
{
	using namespace cognit ;
	using namespace std ;


	AMatrix2<T> a ;

	*input_stream_list[0] >> a ;


	AVector2<AComplex<T> > e ;

	eigen_values(a,e) ;

	cout << e << endl ;
}




#include "../common/common.cpp"
#include "../common/common_main.cpp"

