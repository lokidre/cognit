/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#include <string>

#include <apeal/str.cxx>
#include <apeal/parse.cxx>
#include <apeal/file.cxx>

#include <cognit/cv/corners.cxx>
#include <cognit/io/magick.cxx>
#include <cognit/dsp/normalize.cxx>
#include <cognit/geo/render/line.cxx>


// used types
typedef double float_type ;
typedef std::string string_type ;

// options
string_type input_file ;
string_type input_file_name, output_file_name, input_file_ext ;
int magnify = 0 ;  // auto
float_type sigma_ = 0 ;  // auto

cognit::CornerDetector<float_type> corners_ ;



// processing command line options
int cmdline ( int argc, char *argv[] )
{
	using namespace std ;
	using namespace apl ;

	string name, value ;
	for ( int i = 1 ; i < argc ; ++i ) {
		if ( argv[i][0] == '-' ) {
			str_split(argv[i],'=',name,value) ;

			if ( name == "--sigma" ) {
				// needed float
				int s = 0 ;
				parse_int(value,s) ;
				sigma_ = float_type(s) ;
			}
			continue ;
		}

		input_file = argv[i] ;
	}

	if ( input_file.empty() )
		throw runtime_error("input file name is missing") ;

	// do some games with file name/extension
	extract_file_ext(input_file,input_file_ext) ;
	if ( input_file_ext.empty() ) {
		input_file_ext = "png" ;
		input_file_name = input_file ;
	} else {
		input_file_name = input_file ;
		input_file_name.erase(input_file_name.find_last_of('.')) ;
	}

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
		if ( ret_code )
			return ret_code ;

		// load the image file
		int width, height ;
		ABuffer<int> image ;
		magick_load(input_file,image,width,height) ;


		// show some info
		cout << "resolution: " << width << " x " << height << endl ;

		if ( sigma_ != 0 ) {
			cout << "sigma: " << sigma_ << endl ;
			corners_.set_sigma(sigma_) ;
		}

		// detecting edges
		corners_.detect(image.get(),width,height) ;

		cout << "corners: " << corners_.size() << endl ;

		// decide if we want to magnify the image
		int total = width * height ;
		int max_pixel = magick_max_pixel() ;


		// output the image with corners
		{
			ABuffer<int> lines_image_r(total), lines_image_g(total), lines_image_b(total) ;
			int *r = lines_image_r.get(), *g = lines_image_g.get(), *b = lines_image_b.get() ;
			
			normalize(image.get(),r,total,0,max_pixel) ;
			normalize(image.get(),g,total,0,max_pixel) ;
			normalize(image.get(),b,total,0,max_pixel) ;

		
			for ( CornerDetector<float_type>::const_iterator c = corners_.begin() ; c != corners_.end() ; ++c ) {
				APointLine<float_type> p, q ;
				p.u.x = c->x-3, p.u.y = c->y-3 ;
				p.v.x = c->x+4, p.v.y = c->y+4 ;
				q.u.x = c->x-3, q.u.y = c->y+3 ;
				q.v.x = c->x+4, q.v.y = c->y-4 ;

				render_segment(p,r,width,height,max_pixel) ;
				render_segment(p,g,width,height,0) ;
				render_segment(p,b,width,height,0) ;
				render_segment(q,r,width,height,max_pixel) ;
				render_segment(q,g,width,height,0) ;
				render_segment(q,b,width,height,0) ;
			}

			/*
			for ( CornerDetector<float_type>::const_iterator c = corners_.begin() ; c != corners_.end() ; ++c ) {
				r[c->yy*width+c->xx] = max_pixel ;
				g[c->yy*width+c->xx] = 0 ;
				b[c->yy*width+c->xx] = 0 ;
			}
			*/

			magick_save(r,g,b,width,height, str_format(output_file_name,"%s-corners.%s",input_file_name,input_file_ext) ) ;
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

