/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#include <iostream>

#include <Magick++.h>

#include <apeal/str.cxx>
#include <apeal/parse.cxx>
#include <apeal/file.cxx>


#include <cognit/dsp/gaussian.cxx>
#include <cognit/dsp/gradient_norm.cxx>
#include <cognit/dsp/maxima.cxx>
#include <cognit/dsp/conservative.cxx>
#include <cognit/dsp/median.cxx>
#include <cognit/dsp/image_magick.cxx>
#include <cognit/dsp/border.cxx>
#include <cognit/dsp/threshold.cxx>
#include <cognit/dsp/minmax.cxx>


typedef double float_type ;

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
		
		
		// load and analyze the image
		Magick::Image orig_img ;
		Magick::PixelPacket *pixels ;
		int width, height, total, channels ;
		
		{
			cout << "loading opt_input_file..." << flush ;
			orig_img.read(opt_input_file) ;
			cout << endl ;
			
			// get some information
			Magick::Geometry size = orig_img.size() ;
			
			width = size.width() ;
			height = size.height() ;
			total = width * height ;
			channels = 1 ;
			
			cout << "\twxh = " << size.width() << "x" << size.height() << endl ;
			cout << '\t' << "depth = " << orig_img.depth() << endl ;
			
			if ( orig_img.type() == Magick::GrayscaleType ) {
				cout << '\t' << "greyscale image" << endl ;
				channels = 1 ;
			} else {
				cout << '\t' << "color" << endl ;
			}
		
			orig_img.type(Magick::GrayscaleType) ;
			orig_img.type(Magick::TrueColorType) ;
			
			pixels = orig_img.getPixels(0,0,width,height) ;
		}
		
		ABuffer<int> image_buffer(total) ;
		
		int *img = image_buffer.get() ;
		int max_pixel = magick_max_pixel() ;
		
		cout << max_pixel << endl ;

		// load the original data
		{
			Magick::PixelPacket *pp = pixels ;
			int *d = img ;
			for ( int i = 0 ; i < total ; ++i, ++pp, ++d ) {
				//*d = (((unsigned int)pp->red)/(max_pixel/255)) ;
				*d = pp->red/256 ;
			}
		}
		
		
		
		// determine histogram image size
		// make it 2:1 512 to 255
		const int histo_width = 256, histo_height = histo_width*2, histo_total = histo_width*histo_height ;
		ABuffer<float_type> histo_data_buffer(histo_width) ;
		ABuffer<float_type> histo_image_buffer(histo_total) ;
		
		float_type *histo_image = histo_image_buffer.get() ;
		
		histo_image_buffer.fill(max_pixel) ;
		
		
		float_type *histo_data = histo_data_buffer.get() ;
		histo_data_buffer.zero() ;
		
		
		// get the histogram
		float_type *h = histo_data ;
		int *pi = img ;
		float_type alpha = float_type(1)/total ;
		for ( int i = 0 ; i < total ; ++i, ++pi ) {
			//histo_data[*pi]++ ;
			//cout << *pi << " " ;
			histo_data[*pi] += alpha ;
		}
		
		// now generate the final image
		normalize(histo_data,histo_width,float_type(0),float_type(histo_height)) ;
		
		for ( int i = 0 ; i < histo_width ; i++ ) {
			for ( int j = 0 ; j < histo_data[i] && j < histo_height; j++ )
				histo_image[(histo_height-1-j)*histo_width+i] = 0 ;
		}
		

		string file_name ;
		
		image_save(histo_image,histo_width,histo_height,str_format(file_name,"%s-histogram.%s",input_file_name,input_file_ext)) ;
		
		
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


