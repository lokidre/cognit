/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#include <iostream>

#include <apl/str.cxx>
#include <apl/parse.cxx>
#include <apl/file.cxx>

#include <filter/corners.cxx>
#include <filter/image_magick.cxx>

typedef double float_type ;

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
	using namespace filter ;
	
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


		//
		// output image
		//
		const int total = width * height ;
		string output_file_name ;
		int max_pixel = magick_max_pixel() ;

		// first output just detected edges - for overall testing
		{
			ABuffer<int> edges_image(total) ;
			edges_image.zero() ;

			const edge_detector_type::mask_type *m = edges.edges_mask() ;
			int *p = edges_image.get() ;

			for ( int i = 0 ; i < total ; ++i, ++m, ++p )
				if ( *m )
					*p = max_pixel ;

			image_save(edges_image.get(),width,height,str_format(output_file_name,"%s-edges.%s",input_file_name,input_file_ext) ) ;
		}


		// output the data with subpixel accuracy - for that scale the original image
		{
			ABuffer<int> subpixel_image(total) ;  // do only 
			subpixel_image.zero() ;

			int scale = 8 ;
			int scale_width = width/scale ;
			int scale_height = height/scale ;
			//int start_x = (width-scale_width)/2 ;
			//int start_y = (height-scale_height)/2 ;

			int start_x = (width-scale_width)/2 ;
			int start_y = 0 ; //(height-scale_height)/2 ;

			// first prepare the target scaled image (take the center)
			int *m = image.get() + start_y*width + start_x ;
			const edge_detector_type::edge_type *e = edges.edges() + start_y*width + start_x ;
			int *p = subpixel_image.get() ;

			for ( int j = 0 ; j < scale_height ; ++j ) {

				m += (width-scale_width)/2 ;
				e += (width-scale_width)/2 ;

				// scale the original image
				for ( int i = 0 ; i < scale_width ; ++i, ++m ) {
					//*p = *m ;
					++p ;
					for ( int k = 1 ; k < scale ; ++k, ++p )
						; //*p = *(p-1) ;
				}

				// repeat everything
				for ( int k = 1 ; k < scale ; ++k ) {
					for ( int i = 0 ; i < width ; ++i, ++p )
						; //*p = *(p-width) ;
				}

				// now place edges
				for ( int i = 0 ; i < scale_width ; ++i, ++e ) {
					if ( e->edge == 0 )
						continue ;
					
					// first place the unadjusted edge
					//subpixel_image[(j*scale+scale/2)*width+i*scale+scale/2] = max_pixel ;

					// and adjusted edge
					if ( e->y != 0 || e->x != 0 ) {
						subpixel_image[(int(j*scale+scale/2+e->y*scale))*width+int(i*scale+scale/2+e->x*scale)] = max_pixel ;
					}
				}


				m += (width-scale_width)/2 ;
				e += (width-scale_width)/2 ;
			}

			image_save(subpixel_image.get(),width,height,str_format(output_file_name,"%s-subpixel.%s",input_file_name,input_file_ext) ) ;
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
