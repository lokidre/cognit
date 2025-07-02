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


#include <cognit/mat/opt/lmeds_pca.cxx>

#include <cognit/mat/vector/io.cxx>

#include <cognit/geo/line.cxx>

#include <vector>


template <class T>
void test()
{
	using namespace cognit ;

	apl::ABuffer<T> x, y, x_buffer, y_buffer, buffer ;
	int n ;
	
	load_xy(*input_stream_list[0],x,y,n) ;

	x_buffer.resize(n), y_buffer.resize(n), buffer.resize(n) ;

	AVector2<T> p, v ;

	if ( !lmeds_pca(x.get(),y.get(),n,p,v,buffer.get()) )
		throw std::runtime_error("Cannot fit to Least Squares") ;
		
	AParametricLine<T> l(p.a[0],p.a[1],v.a[0],v.a[1]) ;
	// normalize(l) ;  TODO: don't know what normalize is

	*output_stream << "p=(" << l.p.x << ' ' << l.p.y << ")' " << "v=(" << l.u.x << ' ' << l.u.y << ")'" << std::endl ;
}


#include "../common/common.cpp"
#include "../common/common_main.cpp"


