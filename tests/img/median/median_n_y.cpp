/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#include <iostream>

#include <apeal/str.cxx>
#include <apeal/parse.cxx>
#include <apeal/file.cxx>

#include <cognit/dsp/median.cxx>
#include <cognit/dsp/image_magick.cxx>


typedef double float_type ;

std::string input_file ;
std::string input_file_ext, input_file_name, output_file ;

int filter_size = 1 ;


int main(int argc, char *argv[])
{
	using namespace apl ;
	using namespace std ;
	using namespace cognit ;
	
	int ret_code = 1 ;

	try {
		// command line parsing
		if ( argc <= 2 )
			throw runtime_error("input parameter missing") ;
			
		input_file = argv[1] ;
		extract_file_ext(input_file,input_file_ext) ;
		if ( input_file_ext.empty() ) {
			input_file_ext = "png" ;
			input_file_name = input_file ;
		} else {
			input_file_name = input_file ;
			input_file_name.erase(input_file_name.find_last_of('.')) ;
		}
		
		parse_int(argv[2],filter_size) ;
		
		if ( (filter_size & 1) == 0 )
			throw runtime_error("filter size must be odd") ;
		
		
		ABuffer<float_type> image, filtered, buffer ;
		int width, height ;
		
		image_load(input_file,image,width,height) ;
		
		const int total = width * height ;
		
		filtered.resize(total) ;
		buffer.resize(filter_size) ;
		
		
		float_type *pi = image.get(), *pf = filtered.get() ;
		for ( int x = 0 ; x < width ; ++x, ++pi, ++pf ) {
			median_n_y(pi,pf,width,height,filter_size,buffer.get()) ;
		}

		
		image_save(filtered.get(),width,height,str_format(output_file,"%s-median-%d-y.%s",input_file_name,filter_size,input_file_ext)) ;
	
		
		ret_code = 0 ;
	}
	catch(exception &e) {
		cerr << e.what() << endl ;
	}
	catch(...) {
		cerr << "exception" << endl ;
	}


	return ret_code ;
}


