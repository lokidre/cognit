/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#include "../common/common.h"

#include <cognit/mat/matrix/eigen.cxx>
#include <cognit/mat/matrix/io.cxx>
#include <cognit/mat/vector/io.cxx>


template <class T>
void test()
{
	using namespace mat ;
	using namespace std ;


	AMatrix2<T> a ;

	*input_stream_list[0] >> a ;


	AVector2<T> e ;
	AMatrix2<T> v ;

	eigen_system_simm(a,e,v) ;

	cout << e << endl ;
	cout << v << endl ;
}




#include "../common/common.cpp"
#include "../common/common_main.cpp"

