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


#include <cognit/mat/func.cxx>

#include <cognit/io/matrix.cxx>
#include <cognit/io/vector.cxx>
#include <cognit/io/pgm.cxx>

#include <cognit/render/axes.cxx>
#include <cognit/render/point.cxx>


template <class T>
void test()
{
	using namespace cognit ;
	using namespace std ;
	using namespace apl ;


	ABuffer<T> i_data, y_data, buffer ;
	
	load_x(*input_stream_list[0],y_data) ;

	int n = y_data.size() ;

	ABuffer<AComplex<T> > x_data ;

	i_data.resize(n), x_data.resize(n) ;

	for ( int i = 0 ; i < n ; ++i ) {
		i_data[i] = T(i) ;
		x_data[i].a = y_data[i] ;
		x_data[i].b = 0 ;
	}


	//
	// Discrete Fourier Transform
	//
	ABuffer<AComplex<T> > F ; // dfta, dftb ;

	{
		F.resize(n) ; //, dftb.resize(n) ;

		//const int k = n ;  // frequences
		const T pi = const_pi<T>()() ;
		const T w = -2*pi/n ;

		AComplex<T> *f = F.get() ;


		for ( int k = 0 ; k < n ; ++k, ++f ) {
		
			AComplex<T> *x = x_data.get() ;
		
			f->a = f->b = 0 ;

			for ( int i = 0 ; i < n ; ++i, ++x ) {
				*f += *x * exp(AComplex<T>(0,w*k*i)) ;
			}
		}
	}


	//
	// Inverse Transform
	//
	ABuffer<AComplex<T> > Fi ;

	{
		Fi.resize(n) ;

		AComplex<T> *x = Fi.get() ;

		const T pi = const_pi<T>()() ;
		const T w = 2*pi/n ;

		for ( int k = 0 ; k < n ; ++k, ++x ) {
		
			AComplex<T> *X = F.get() ;
		
			*x = 0 ;

			for ( int i = 0 ; i < n ; ++i, ++X ) {
				*x += *X * exp(AComplex<T>(0,w*k*i)) ;
			}
			*x /= T(n) ;
		}
	}


	// rendering for visual inspection
	{
		int minx, maxx, miny, maxy ;

		T mn, mx ;
		i_data.minmax(mn,mx), minx = int(mn), maxx = int(mx) ;
		y_data.minmax(mn,mx), miny = int(mn), maxy = int(mx) ;


		minx -= 20, maxx += 20 ;
		miny -= 20, maxy += 20 ;

		int width = maxx - minx ;
		int height = maxy - miny ;

		char *image = new char[width*height] ;

		memset(image,0,width*height) ;

		render_axes(image,width,height,char(1),-minx,-miny) ;
		render_points(i_data.get(),y_data.get(),n,image,width,height,char(4),-minx,-miny) ;

		save_pgm(image,width,height,"dft1_research_x.pgm") ;

	}

	// rendering for visual inspection
	{
		ABuffer<T> real_data, imag_data ;

		real_data.resize(n), imag_data.resize(n) ;

		for ( int i = 0 ; i < n ; ++i )
			real_data[i] = F[i].a, imag_data[i] = F[i].b ;


		int minx, maxx, minry, maxry, miniy, maxiy ;

		T mn, mx ;
		i_data.minmax(mn,mx), minx = int(mn), maxx = int(mx) ;
		real_data.minmax(mn,mx), minry = int(mn), maxry = int(mx) ;
		imag_data.minmax(mn,mx), miniy = int(mn), maxiy = int(mx) ;


		minx -= 20, maxx += 20 ;
		minry -= 20, maxry += 20 ;
		miniy -= 20, maxiy += 20 ;

		int width = maxx - minx ;
		int height = maxry - minry ;

		char *image = new char[width*height] ;



		memset(image,0,width*height) ;

		render_axes(image,width,height,char(1),-minx,-minry) ;
		render_points(i_data.get(),imag_data.get(),n,image,width,height,char(4),-minx,-minry) ;

		save_pgm(image,width,height,"dft1_research_F_real.pgm") ;


		width = maxx - minx ;
		height = maxiy - miniy ;

		image = new char[width*height] ;

		memset(image,0,width*height) ;

		render_axes(image,width,height,char(1),-minx,-miniy) ;
		render_points(i_data.get(),imag_data.get(),n,image,width,height,char(4),-minx,-miniy) ;

		save_pgm(image,width,height,"dft1_research_F_imag.pgm") ;
	}


	// rendering for visual inspection
	{
		ABuffer<T> real_data, imag_data ;

		real_data.resize(n), imag_data.resize(n) ;

		for ( int i = 0 ; i < n ; ++i )
			real_data[i] = Fi[i].a, imag_data[i] = Fi[i].b ;


		int minx, maxx, minry, maxry, miniy, maxiy ;

		T mn, mx ;
		i_data.minmax(mn,mx), minx = int(mn), maxx = int(mx) ;
		real_data.minmax(mn,mx), minry = int(mn), maxry = int(mx) ;
		imag_data.minmax(mn,mx), miniy = int(mn), maxiy = int(mx) ;


		minx -= 20, maxx += 20 ;
		minry -= 20, maxry += 20 ;
		miniy -= 20, maxiy += 20 ;

		int width = maxx - minx ;
		int height = maxry - minry ;

		char *image = new char[width*height] ;



		memset(image,0,width*height) ;

		render_axes(image,width,height,char(1),-minx,-minry) ;
		render_points(i_data.get(),real_data.get(),n,image,width,height,char(4),-minx,-minry) ;

		save_pgm(image,width,height,"dft1_research_fF_real.pgm") ;


		width = maxx - minx ;
		height = maxiy - miniy ;

		image = new char[width*height] ;

		memset(image,0,width*height) ;

		render_axes(image,width,height,char(1),-minx,-miniy) ;
		render_points(i_data.get(),imag_data.get(),n,image,width,height,char(4),-minx,-miniy) ;

		save_pgm(image,width,height,"dft1_research_fF_imag.pgm") ;
	}
}




#include "../common/common.cpp"
#include "../common/common_main.cpp"

