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

#include <cognit/geo/io/pgm.cxx>
#include <cognit/geo/line.cxx>
#include <cognit/geo/render/line.cxx>
#include <cognit/geo/render/axes.cxx>


#include <cognit/mat/vector.cxx>
#include <cognit/mat/opt/lsm.cxx>

#include <vector>


template <class T>
void test()
{
	using namespace std ;
	using namespace apl ;
	using namespace cognit ;
	
	
	ABuffer<T> x, y ;
	int n ;
	
	load_xy(*input_stream_list[0],x,y,n) ;

	T a, b ;
	

	if ( !lsm(x.get(),y.get(),n,a,b) )
		throw runtime_error("Cannot fit to Least Squares") ;


	// rendering for visual inspection
	{
		int minx, maxx, miny, maxy ;

		T *px = x.get(), *py = y.get() ;

		minx = maxx = int(*px), miny = maxy = int(*py) ;

		for ( int i = 0 ; i < n ; ++i, ++px, ++py ) {
			if ( *px < minx )
				minx = int(*px) ;
			if ( *px > maxx )
				maxx = int(*px) ;
			if ( *py < miny )
				miny = int(*py) ;
			if ( *py > maxy )
				maxy = int(*py) ;
		}

		minx -= 20, maxx += 20 ;
		miny -= 20, maxy += 20 ;

		//minx = 0, miny = 0 ;

		int width = maxx - minx ;
		int height = maxy - miny ;

		char *image = new char[width*height] ;

		memset(image,0,width*height) ;

		AExplicitLine<T> l ;
		l.a = a, l.b = b ;

		render_axes(image,width,height,char(1),-minx,-miny) ;
		render_line(l,image,width,height,char(2),-minx,-miny) ;

		// render points
		px = x.get(), py = y.get() ;

		for ( int i = 0 ; i < n ; ++i, ++px, ++py ) {
			image[(int(*py)-miny)*width+(int(*px)-minx)] = 4 ;
		}

		save_pgm(image,width,height,"lsm_research.pgm") ;

	}

	*output_stream << a << ' ' << b << endl ;
}


#include "../common/common.cpp"
#include "../common/common_main.cpp"


