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
#include <cognit/mat/opt/lsm.cxx>
#include <cognit/mat/opt/median.cxx>
#include <cognit/mat/matrix.cxx>
#include <cognit/mat/const.cxx>


#include <cognit/geo/io/pgm.cxx>
#include <cognit/geo/line.cxx>
#include <cognit/geo/render/line.cxx>
#include <cognit/geo/render/axes.cxx>

#include <vector>




template <class T>
class LMedS {

	public :
		T *x_data_, *y_data_, *buffer_ ;
		int n_ ;
		
		T b_ ;  // b parameter
		T abs_dev_ ;  // absolute deviation
		T eps_ ;  // epsilon value ;
		
		LMedS()
		{
			eps_ = cognit::const_eps<T>()() ;
			b_ = abs_dev_ = 0 ;
		}
		

	public :
	
		T operator () ( const T &a )
		{
			using namespace cognit ;
	
			const T eps = eps_ ;
			const int n = n_ ;
	
			int i ;

			T *p, *x, *y ;
	
			for ( i = 0, p = buffer_, x = x_data_, y = y_data_ ; i < n ; ++i, ++p, ++x, ++y )
				*p = *y - a* *x ;
		
			// two cases for odd and even
			if ( n & 1 ) {  // odd 
				b_ = median_select((n-1)>>1,buffer_,n) ;
			} else {  // even
				b_ = (median_select((n>>1)-1,buffer_,n) + median_select((n>>1),buffer_,n))/2 ;
			}
	
			abs_dev_ = 0 ;
	
			T s(0), d ;
	
			for ( i = 0, p = buffer_, x = x_data_, y = y_data_ ; i < n ; ++i, ++p, ++x, ++y ) {
				d = *y - (a* *x + b_) ;
				abs_dev_ += abs(b_) ;
				if ( !tiny(*y,eps) )
					d /= abs(*y) ;
				if ( !tiny(d,eps) )
					s += d >= 0 ? *x : - *x ;
			}
		
			return s ;
		}
} ;


template <class T>
void test()
{
	using namespace std ;
	using namespace cognit ;
	
	
	LMedS<T> ro ;
	
	apl::ABuffer<T> x_data, y_data, buffer ;
	int n ;
	
	load_xy(*input_stream_list[0],x_data,y_data,n) ;
	
	buffer.resize(n) ;
	
	ro.x_data_ = x_data.get() ;
	ro.y_data_ = y_data.get() ;
	ro.buffer_ = buffer.get() ;
	ro.n_ = n ;

	
	T lsm_a, lsm_b ;
	
	
	// approximate first by least squares method
	if ( !lsm(x_data.get(),y_data.get(),n,lsm_a,lsm_b) )
		throw runtime_error("cannot build least squares") ;
	
	cout << "lsm: " << lsm_a << " " << lsm_b << endl ;
	
	
	T eps = const_eps<T>()() ;
	
	// detect standard deviation - to detect 
	T *x = x_data.get(), *y = y_data.get() ;
	T chisq(0) ;
	for ( int i = 0 ; i < n ; ++i, ++x, ++y )
		chisq += sqr(*y - lsm_b - lsm_a* *x) ;
		
	T sigb = sqrt(chisq/T(n-1)) ;
	
	T aa = lsm_a ;
	ro.b_ = lsm_b ;
	
	
	T a1 = aa, a2 ;  // start
	T f, f1 = ro(a1), f2 ;
	T abs_dev ;  // absolute deviation
	
	if ( sigb > 0 ) {
		a2 = aa + (f1>=0?(sigb>=0?sigb:-sigb):(sigb>=0?-sigb:sigb))*3 ;
		f2 = ro(a2) ;
		if ( abs(a2-a1) > eps ) {
		
			// bracketing
			while ( f1*f2 > 0 ) {  // while functions have same sign
				aa = a2 + (a2-a1) * T(1.6) ;
				a1 = a2, a2 = aa ;
				f1 = f2 ;
				f2 = ro(a2) ;
			}
		
			sigb /= 100 ;
		
		
			// bisection
			while ( abs(a2-a1) > sigb ) {
		
				aa = a1 + (a2-a1)/2 ;
			
				if ( aa == a1 || aa == a2 )
					break ;
				
				f = ro(aa) ;
			
				if ( f*f1 > 0 ) 
					f1 = f, a1 = aa ;
				else
					f2 = f, a2 = aa ;
			}
		}
	}
	
	T lmeds_b = ro.b_ ;
	T lmeds_a = aa ;
	abs_dev = ro.abs_dev_/n ;



	// rendering for visual inspection
	{
		int minx, maxx, miny, maxy ;

		T *px = x_data.get(), *py = y_data.get() ;

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
		render_line(AExplicitLine<T>(lsm_a,lsm_b),image,width,height,char(2),-minx,-miny) ;
		render_line(AExplicitLine<T>(lmeds_a,lmeds_b),image,width,height,char(3),-minx,-miny) ;

		// render points
		px = x_data.get(), py = y_data.get() ;

		for ( int i = 0 ; i < n ; ++i, ++px, ++py ) {
			image[(int(*py)-miny)*width+(int(*px)-minx)] = 4 ;
		}

		save_pgm(image,width,height,"lmeds_research.pgm") ;
	}
	
	
	cout << "lmeds: " << lmeds_a << " "  << lmeds_b << endl ;
}


#include "../common/common.cpp"
#include "../common/common_main.cpp"



