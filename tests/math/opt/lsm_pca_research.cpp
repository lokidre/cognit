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
#include <cognit/mat/vector/io.cxx>
#include <cognit/mat/matrix/eigen.cxx>
#include <cognit/mat/matrix.cxx>
#include <cognit/mat/stat/cov.cxx>
#include <cognit/mat/stat/mean.cxx>
#include <cognit/mat/matrix/io.cxx>

#include <cognit/mat/opt/lsm.cxx>

#include <cognit/geo/io/pgm.cxx>
#include <cognit/geo/line.cxx>
#include <cognit/geo/render/line.cxx>
#include <cognit/geo/render/axes.cxx>

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

	
	// build covariance matrix
	AMatrix2<T> c ;
	
	cov(x.get(),y.get(),n,c) ;
	
	*output_stream << "covariance matrix: " << endl << c << endl ;
	
	// find eigenvalues with eigen vectors
	AVector2<T> e ;
	AMatrix2<T> m ;
	eigen_system_simm(c,e,m) ;
	
	*output_stream << "eigen values: " << endl << e << endl ;
	*output_stream << "eigen vectors: " << endl << m << endl ;
	

	// calculate centroid
	AVector2<T> p ;
	p.a[0] = mean(x.get(),n), p.a[1] = mean(y.get(),n) ;
	*output_stream << "centroid: " << endl << p << endl ;

	// normalize vector
	AVector2<T> v ;
	const T l = hypot(m.a[0][0],m.a[0][1]) ;
	const T eps = const_eps<T>()() ;
	
	if ( l < eps )
		throw runtime_error("cannot find direction") ;
		
	v.a[0] = m.a[0][0]/l, v.a[1] = m.a[0][1]/l ;


	// rendering for visual inspection
	{
		AParametricLine<T> l ;
		l.p.x = p.a[0], l.p.y = p.a[1] ;
		l.u.x = v.a[0], l.u.y = v.a[1] ;

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

		int width = maxx - minx ;
		int height = maxy - miny ;

		char *image = new char[width*height] ;

		memset(image,0,width*height) ;

		render_axes(image,width,height,char(1),-minx,-miny) ;
		render_line(l,image,width,height,char(2),-minx,-miny) ;

		// render points
		px = x.get(), py = y.get() ;

		for ( int i = 0 ; i < n ; ++i, ++px, ++py ) {
			image[(int(*py)-miny)*width+(int(*px)-minx)] = 4 ;
		}

		save_pgm(image,width,height,"lsm_pca_research.pgm") ;
	}


	*output_stream << "vector: " << endl << v << endl ;
}


#include "../common/common.cpp"
#include "../common/common_main.cpp"


