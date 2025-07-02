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

#include <cognit/mat/stat.cxx>


template <class T>
void test()
{
/*
	using namespace std ;
	using namespace mat ;


	typedef vector<AVector2<T> > points_list_type ;
	points_list_type pts ;


	load_2d(*input_stream_list[0],pts) ;


	const int n = int(pts.size()) ;
	T *x = new T[n], *y = new T[n] ;

	convert_2d(pts,x,y) ;


	T cov = stat_cov(x,y,n) ;
	*output_stream << cov << endl ;
	*/
}


#include "../common/common.cpp"
#include "../common/common_main.cpp"
