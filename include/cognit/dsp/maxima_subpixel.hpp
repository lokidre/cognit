/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once


namespace cognit {


//
// find maxima with subpixel accuracy
// requires the container with edges, gradients, norm of gradients
//
// replaces the container with subpixel values
// 
// lines - using linear approximation, otherwise using quadratic
//


//
// x_0=0.5, x_1=1.5, x_2=2.5
//
template <class T, class container_type>
void maxima_subpixel_y(container_type &maxima, const T *gy, const T *norm, int width, int height)
{
	int c, r ;  // column, row
	T x, y ;  // x, y coordinates
	T y0, y1, y2 ;  // previous, current, and next norms
	T maxy ;
	
	for (auto m = maxima.begin(), m_end = maxima.end() ; m != m_end ; ++m ) {
		c = int(m->x), r = int(m->y) ;
		
		if ( c <= 0 || c >= width-1 || r <= 0 || r >= height-1 )
			continue ;
			
		// take three values prev, current, next
		y0 = norm[(r-1)*width+c] ;
		y1 = norm[r*width+c] ;
		y2 = norm[(r+1)*width+c] ;
		
		maxy = (3*y0 - 4*y1 + y2)/(y0 - 2*y1 + y2)/2 - 1 ;
		
		m->y += maxy ;
	}
}

}  // namespace


