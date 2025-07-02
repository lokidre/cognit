/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include "render.cxx"


namespace cognit {



template <class Pixel>
void render_point ( const int x, const int y, Pixel *image, const int width, const int height, const Pixel &p )
{
	int xx, yy ;

	for ( int i = -3 ; i <= 3 ; ++i ) {
		yy = y + i, xx = x + i ;
		if ( yy >= 0 && yy < height && xx >= 0 && xx < width )
			image[yy*width+xx] = p ;

		yy = y + i, xx = x - i ;
		if ( yy >= 0 && yy < height && xx >= 0 && xx < width )
			image[yy*width+xx] = p ;
	}
}


template <class float_type, class pixel_type>
void render_points ( const float_type *px, const float_type *py, const int n, pixel_type *image, const int width, const int height, const pixel_type &val, const int ox=0, const int oy=0 )
{
	const float_type *x = px, *y = py ;
	const float_type half(0.5) ;

	int i, j ;


	for ( int k = 0 ; k < n ; ++k, ++x, ++y ) {
		j = int(*y + half + oy) ;
		i = int(*x + half + ox) ;

		if ( i < 0 || i >= width || j < 0 || j >= height )
			continue ;

		image[j*width+i] = val ;
	
	}

}




template <class C>
void render_point ( ARender &ctx, const C x, const C y )
{
}



template <class Point>
inline
void render_point_2d ( ARender &ctx, const Point &p )
{
	render_point ( ctx, p.x, p.y ) ;
}


// void render_point_x ( ARender *ctx, const 

}

