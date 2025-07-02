/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include <string>
#include <iostream>

namespace cognit {

template <class pixel_type>
void save_pgm ( const pixel_type *image, const int width, const int height, const std::string &filename )
{
	using namespace std ;


	// search for minimum and maximum elements
	pixel_type max_value = *image, min_value = *image ;

	const pixel_type *p = image ;
	const int total = width * height ;

	for ( int i = 0 ; i < total ; ++i, ++p ) {
		if ( *p < min_value )
			min_value = *p ;
		if ( *p > max_value )
			max_value = *p ;
	}

	int range = int(max_value) - int(min_value) ;
	bool normalize = false ;

	if ( range > 65534 ) {
		normalize = true ;
		range = 65535 ;
	} else if ( range == 0 ) {
		range = 2 ;
	}

	// generate the stream
	ofstream file(filename.c_str(),ios_base::out|ios_base::binary) ;

	if ( !file.good() )
		throw std::runtime_error((std::string("error writing to ") + filename).c_str() ) ;

	file << "P2" << endl ;
	file << width << ' ' << height << endl ;

	file << range << endl ;
	pixel_type d = abs(max_value - min_value) ;
	if ( d == 0 )
		d = 2 ;

	// max string size for one pixel
	int max_pixel = 0 ;
	int r = range ;
	while ( !r )
		r /= 10, max_pixel++ ;
	max_pixel++ ;


	p = image ;
	int cur_pixel = 0 ;
	for ( int j = 0 ; j < height ; ++j ) {
		p = &image[(height-1-j)*width] ;  // slip vertical
		for ( int i = 0 ; i < width ; ++i, ++p ) {

			file << ' ' << int((*p - min_value)*range/d) ;

			cur_pixel += max_pixel + 1 ;
			if ( cur_pixel >= 70 ) {
				file << endl ;
				file << endl ;
				cur_pixel = 0 ;
			}
		}
	}
}

}
