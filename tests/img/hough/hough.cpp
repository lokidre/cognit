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

#include <cognit/dsp/edges.cxx>
#include <cognit/dsp/hough.cxx>
#include <cognit/dsp/image_magick.cxx>

typedef double float_type ;

typedef float_type T ;

std::string opt_method ;

const char *methods[] = { "dGx", "dGy", "dGxy", "dGxGy", 0 } ;

std::string opt_input_file ;
std::string input_file_ext, input_file_name ;


float_type opt_sigma = 1 ;
int opt_aperture = 11 ;
float_type norm_threshold_min = 30 ;
float_type hysteresis_threshold_max = norm_threshold_min*2 ;


int main(int argc, char *argv[])
{
	using namespace apl ;
	using namespace std ;
	using namespace cognit ;
	
	int ret_code = 1 ;

	try {
		// command line parsing
		{  
			string name, value, arg ;
			for ( int iarg = 1 ; iarg < argc ; iarg++ ) {
				arg = argv[iarg] ;
				if ( arg[0] != '-' )
					opt_input_file = arg ;
				else {
					if ( arg == "--dGxy" )
						opt_method = "dGxy" ;
					else if ( arg == "--dGxGy" )
						opt_method = "dGxGy" ;
					else
						str_split(arg,'-',name,value) ;
				}
			}
			
			if ( opt_input_file.empty() )
				throw runtime_error("input file is missing") ;
			
			// do some games with file name/extension
			extract_file_ext(opt_input_file,input_file_ext) ;
			if ( input_file_ext.empty() ) {
				input_file_ext = "png" ;
				input_file_name = opt_input_file ;
			} else {
				input_file_name = opt_input_file ;
				input_file_name.erase(input_file_name.find_last_of('.')) ;
			}
		}

		ABuffer<int> image ;
		int width, height ;

		image_load(opt_input_file,image,width,height) ;

		//
		// do edge detection
		//
		typedef Edge<float_type> edge_detector_type ;
		edge_detector_type edges ;

		//edges.set_sigma(2) ;
		//edges.histeresis_thresholding_ = false ;
		//edges.threshold_high_ = 5 ;

		edges(image.get(),width,height) ;
		
		// hough transform
		int hough_width = 640*2, hough_height = 480 ;
		int hough_total = hough_width*hough_height ;
		T theta_min = 0 ;
		T theta_max = const_pi<T>()() ;
		T r_min = -hypot(width,height) - 10 ;
		T r_max = -r_min ;
		
		ABuffer<int> hough_data(hough_total) ;
		ABuffer<float_type> hough_buffer(hough_width*2) ;
		
		hough(edges.begin(),edges.end(),hough_data.get(),hough_width,hough_height,theta_min,theta_max,r_min,r_max,hough_buffer.get()) ;


		//
		// output image
		//
		const int total = width * height ;
		string output_file_name ;
		int max_pixel = magick_max_pixel() ;

		// first output just detected edges - for overall testing
		{
			//normalize(hough_image.get(),hough_total,0,max_pixel) ;
			//image_save(hough_image.get(),hough_width,hough_height,str_format(output_file_name,"%s-hough.%s",input_file_name,input_file_ext) ) ;


			ABuffer<T> hough_image(hough_total) ;
			normalize(hough_data.get(),hough_image.get(),hough_total,0,max_pixel) ;
			image_save(hough_image.get(),hough_width,hough_height,str_format(output_file_name,"%s-hough.%s",input_file_name,input_file_ext) ) ;
		}


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
