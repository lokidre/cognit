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
#include <cognit/dsp/image_magick.cxx>

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
		edges.threshold_low_ = 20 ;
		edges.threshold_high_ = 40 ;
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
		if ( width < 100 ) {

			int scale = 8 ;
			int scale_width = width ; ///scale ;
			int scale_height = height ; ///scale ;
			
			int scaled_width = width*scale ;
			int scaled_height = height*scale ;
			
			//int start_x = (width-scale_width)/2 ;
			//int start_y = (height-scale_height)/2 ;

			ABuffer<int> subpixel_image_r(scaled_width*scaled_height), subpixel_image_g(scaled_width*scaled_height), subpixel_image_b(scaled_width*scaled_height) ;  // do only 
			subpixel_image_r.zero(), subpixel_image_g.zero(), subpixel_image_b.zero() ;

			int start_x = (width-scale_width) ; ///2 ;
			int start_y = 0 ; //(height-scale_height)/2 ;

			// first prepare the target scaled image (take the center)
			int *m = image.get() + start_y*width + start_x ;
			const edge_detector_type::edge_type *e = edges.edges() + start_y*width + start_x ;
			
			int *r = subpixel_image_r.get(), *g = subpixel_image_g.get(), *b = subpixel_image_b.get() ;

			for ( int j = 0 ; j < scale_height ; ++j ) {

				//m += (width-scale_width)/2 ;
				//e += (width-scale_width)/2 ;

				// scale the original image
				for ( int i = 0 ; i < scale_width ; ++i, ++m ) {
					*r = *g = *b = *m ;
					++r, ++g, ++b ;
					for ( int k = 1 ; k < scale ; ++k, ++r, ++g, ++b )
						*r = *g = *b = *(r-1) ;
				}

				// repeat everything
				for ( int k = 1 ; k < scale ; ++k ) {
					for ( int i = 0 ; i < scaled_width ; ++i, ++r, ++g, ++b )
						*r = *g = *b = *(r-scaled_width) ;
				}

				m += (width-scale_width) ;///2 ;
			}

			// now place all the edges
			int *rr = subpixel_image_r.get(), *gg = subpixel_image_g.get(), *bb = subpixel_image_b.get() ;


			for ( int j = 0 ; j < scale_height ; ++j ) {
				// now place edges
				for ( int i = 0 ; i < scale_width ; ++i, ++e ) {
					if ( e->edge == 0 )
						continue ;
					
					// first place the unadjusted edge
					int pixel_index = (j*scale+scale/2)*scaled_width+i*scale+scale/2 ; 
					rr[pixel_index] = 0 ;
					gg[pixel_index] = 0 ;
					bb[pixel_index] = max_pixel ;
					
					//if ( abs(e->x) > 0.5 || abs(e->y) > 0.5 )
					//	throw AException("invalid value") ;

					// and adjusted edge
					//if ( e->y != 0 || e->x != 0 ) {
						//if ( e->x > 0.5 || e->y || 0.5 )
						//	continue ;
					int subpixel_index = (int(e->y*scale+scale/2))*scaled_width+int(e->x*scale+scale/2) ;
					rr[subpixel_index] = max_pixel ;
					gg[subpixel_index] = 0 ;
					bb[subpixel_index] = 0 ;
					//}
				}
				e += (width-scale_width) ; ///2 ;
			}

			image_save(subpixel_image_r.get(), subpixel_image_g.get(), subpixel_image_b.get(),scaled_width,scaled_height,str_format(output_file_name,"%s-subpixel.%s",input_file_name,input_file_ext) ) ;
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
