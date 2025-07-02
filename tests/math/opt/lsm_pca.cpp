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


#include <cognit/mat/opt/lsm_pca.cxx>

#include <cognit/mat/vector/io.cxx>

#include <cognit/geo/line.cxx>

#include <vector>


template <class T>
void test()
{
	using namespace cognit ;
	using namespace apl ;
	using namespace std ;

	ABuffer<T> x, y ;
	int n ;
	
	load_xy(*input_stream_list[0],x,y,n) ;

	AVector2<T> p, v ;
	

	if ( !lsm_pca(x.get(),y.get(),n,p,v) )
		throw runtime_error("Cannot fit to Least Squares") ;

	AParametricLine<T> l(p.a[0],p.a[1],v.a[0],v.a[1]) ;
	// normalize(l) ;  TODO: don't know what "normalize" meant

	*output_stream << "p=(" << l.p.x << ' ' << l.p.y << ")' " << "v=(" << l.u.x << ' ' << l.u.y << ")'" << std::endl ;
}


#include "../common/common.cpp"
#include "../common/common_main.cpp"


