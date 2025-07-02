/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#include <string>


#include <cognit/cv/edges.cxx>
#include <cognit/io/magick.cxx>

#include <iostream>


// used types
typedef double float_type ;
typedef std::string string_type ;

// options
string_type input_file_name ;
int magnify = 0 ;  // auto

cognit::EdgeDetector<float_type> edges_ ;



// processing command line options
int cmdline ( int argc, char *argv[] )
{
	return 0 ;
}


int main(int argc, char *argv[])
{
	using namespace apl ;
	using namespace std ;
	using namespace cognit ;
	
	int ret_code = 1 ;

	try {
		ret_code = cmdline(argc,argv) ;
		if ( !ret_code )
			return ret_code ;

		// load the image file
		int width, height ;
		ABuffer<int> image ;
		magick_load(input_file_name,image,width,height) ;

		// show some info
		cout << input_file_name << endl ;
		cout << "   " << width << " x " << height << endl ;

		// detecting edges
		//edges_.process(image.get(),width,height) ;


		// decide if we want to magnify the image

		
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

