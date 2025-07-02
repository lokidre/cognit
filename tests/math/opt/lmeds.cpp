/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#include "../common/common.h"
#include "../common/load.h"


#include <cognit/mat/vector.cxx>
#include <cognit/mat/opt/lmeds.cxx>

#include <vector>


template <class T>
void test()
{
	using namespace std ;
	using namespace cognit ;
	
	
	apl::ABuffer<T> x, y, buffer ;
	int n ;
	
	load_xy(*input_stream_list[0],x,y,n) ;

	T a, b ;
	buffer.resize(n) ;
	

	if ( !lmeds(x.get(),y.get(),n,a,b,buffer.get()) )
		throw runtime_error("Cannot fit to Least Squares") ;

	*output_stream << a << ' ' << b << endl ;
}


#include "../common/common.cpp"
#include "../common/common_main.cpp"


