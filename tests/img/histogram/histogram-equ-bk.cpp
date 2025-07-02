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

#include <cognit/dsp/histogram.cxx>


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
		
		
		ABuffer<float_type> equ_image_buffer(total) ;
		float_type *equ_image = equ_image_buffer.get() ;
		
		histogram_equalize_bk(img,img+total,equ_image) ;
		
		
		for ( int i = 0 ; i < total ; i++ ) {
			equ_image[i] *= 256 ;
		}
		
		

		string file_name ;
		
		image_save(equ_image,width,height,str_format(file_name,"%s-equ.%s",input_file_name,input_file_ext)) ;
		
		
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


