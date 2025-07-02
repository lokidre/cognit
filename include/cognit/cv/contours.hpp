/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include <stack>

namespace cognit {

//
// note: mask is being destroyed
//

template <class contour_container_type>
void extract_contours ( const char *mask_input, int width, int height, contour_container_type &contours, char *mask, int aperture = 3 )
{
	typedef typename contour_container_type::value_type contour_type ;
	typedef typename contour_type::value_type point_type ;
	typedef std::stack<point_type> contour_stack_type ;
	typedef char mask_type ;
	
	
	contour_stack_type cstack ;

	int x, y ;
	char *m ;
	point_type p, n ;

	int start_row = 1 ;  // some sort of optimization - before this row everything is zero
	
	const int ap_half=aperture/2 ;
	const int ap_half1=ap_half+1 ;
	
	memcpy(mask,mask_input,width*height*sizeof(mask_type)) ;
	contours.clear() ;

	// main cycle for all contours
	for(;;) {
		// search for the first element
		bool pixel_found = false ;
		m = mask + start_row*width ;  // start from the second row
		for ( y = start_row ; y < height-1 ; ++y ) {
			++m ;  // start from the second column
			for ( x = 1 ; x < width-1 ; ++x, ++m ) {
				if ( *m == 0 )
					continue ;

				// check the neighboring pixels - always skip lone pixels
				if ( *(m+1) == 0 && *(m-1) == 0 && *(m-width) == 0 && *(m+width) == 0 && *(m-width-1) == 0 && *(m-width+1) == 0 && *(m+width-1) == 0 && *(m+width+1) == 0 ) {
					*m = 0 ;
					continue ;
				}
					
				// add current pixel to the contours list
				p.x = x, p.y = y ;
				contours.resize(contours.size()+1) ;
				contour_type &c = contours.back() ;
				c.push_back(p) ;
					
				// add pixel to the stack
				cstack.push(p) ;

				*m = 0 ;
					
				pixel_found = true ;
				// we know that all previous rows are 0
				if ( y > start_row + 1 )
					start_row = y - 1 ;
				break ;
			}
			++m ;  // skip last column
			
			if ( pixel_found )
				break ;
		}
		
		
		if ( !pixel_found )
			break ;
		
		
		contour_type &c = contours.back() ;
		
		// collect all pixels of current contour
		while ( !cstack.empty() ) {
			// pick the one from top
			p = cstack.top(), cstack.pop() ;
			
			// check all neighbors
			m = &mask[(p.y-1)*width+(p.x-1)] ;
			for ( y = -ap_half ; y <= ap_half ; ++y ) {
				for ( x = -ap_half ; x <= ap_half ; ++x, ++m ) {
					if ( p.x + x < 0 || p.y + y < 0 || p.x + x >= width || p.y + y >= height )
						continue ;
					if ( *m == 0 )
						continue ;
						
					n.x = p.x+x, n.y = p.y+y ;
					c.push_back(n) ;
					cstack.push(n) ;
					*m = 0 ;
				}
				m += width-aperture ;
			}
			
		}  // while there anything in stack
		
	}
}

}
