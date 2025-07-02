/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#include "../common/common.h"

#include <cognit/mat/complex.cxx>
#include <cognit/mat/complex/io.cxx>


template <class T>
void test()
{
	using namespace std ;
	using namespace cognit ;

	AComplex<T> a, b, c ;

	*input_stream_list[0] >> a ;
	*input_stream_list[0] >> b ;

	cpx_add(a,b,c) ;

	*output_stream << c << endl ;
}


#include "../common/common.cpp"
#include "../common/common_main.cpp"

