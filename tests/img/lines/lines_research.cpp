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
#include <cognit/dsp/border.cxx>

#include <cognit/geo/render/line.cxx>
#include <cognit/geo/line.cxx>
#include <cognit/geo/line/convert.cxx>
#include <cognit/geo/line/dist.cxx>



typedef double float_type ;

typedef float_type T ;

std::string opt_input_file ;
std::string input_file_ext, input_file_name ;

T opt_sigma = 1 ;
int opt_aperture = 11 ;
T norm_threshold_min = 30 ;
T hysteresis_threshold_max = norm_threshold_min*2 ;


void process()
{
	using namespace std ;
	using namespace apl ;
	using namespace cognit ;
	
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
	
	edges.threshold_low_ = 20 ;
	edges.threshold_high_ = 40 ;

	edges(image.get(),width,height) ;
	edges.clear_border(15) ;
	
	//edge_detector_type::edge_type null_edge ;
	//null_edge.edge = false ;
	//fill_border(edges.edges_,width,height,5,null_edge) ;
	
	// hough transform
	int hough_width = std::max(width,height) ;
	int hough_height = hough_width*2 ;
	int hough_total = hough_width*hough_height ;
	T theta_min = 0 ;
	T theta_max = const_pi<T>()() ;
	//T theta_min = const_pi<T>()()/2 ;
	//T theta_max = const_pi<T>()() ;
	
	T r_max = hypot(width,height) + 10 ;
	T r_min = -r_max ;
		
	ABuffer<int> hough_data(hough_total) ;
	ABuffer<T> hough_buffer(hough_width*2) ;
	
	cout << "hough transform..." << endl ;
	{
		hough(edges.begin(),edges.end(),hough_data.get(),hough_width,hough_height,theta_min,theta_max,r_min,r_max,hough_buffer.get()) ;
	}



	//
	// output hough image
	//
	const int total = width * height ;
	string output_file_name ;
	int max_pixel = magick_max_pixel() ;

	// first output just detected edges - for overall testing
	{
		ABuffer<int> hough_image(hough_total) ;
		normalize(hough_data.get(),hough_image.get(),hough_total,0,max_pixel) ;
		image_save(hough_image.get(),hough_width,hough_height,str_format(output_file_name,"%s-hough.%s",input_file_name,input_file_ext) ) ;
	}



	//
	// select good lines
	//
	cout << "selecting best lines..." << endl ;
	
	typedef ANormalLine<T> line_type ;
	typedef vector<line_type> line_container_type ;
	
	line_container_type lines ;

	typedef vector<APointLine<int> > point_line_container_type ;

	point_line_container_type segments ;

	{
		// select the maximum (the best line)
		// chose all the pixels belonging to that line
		// remove all these pixels from hough transform
		// repeat the process again until some criteria:
		//   1. specific number of lines detected 
		//   2. until value of maxima is above some threshold
		//   3. until dispersion is below some threshold

		const T theta_step = (theta_max-theta_min)/hough_width ;
		const T r_step = (r_max-r_min)/hough_height ;
		
		
		T r, theta ;
	
		T *cos_buffer = hough_buffer ;
		T *sin_buffer = cos_buffer + hough_width ;
					
		T *pcos = cos_buffer, *psin = sin_buffer ;
		for ( int x = 0 ; x < hough_width ; ++x, ++pcos, ++psin ) {
			theta = theta_step*x + theta_min ;
			*pcos = cos(theta) ;
			*psin = sin(theta) ;
		}

		
		while ( lines.size() < 100 ) {
			int max_hough = 0 ;
			int max_hough_x, max_hough_y ;
			line_type best_line ;
			
			int *h = hough_data.get() ;
			for ( int y = 0 ; y < hough_height ; ++y ) {
				for ( int x = 0 ; x < hough_width ; ++x, ++h ) {
					if ( *h <= max_hough  )
						continue ;
	
					best_line.t = theta_step*x + theta_min ;
					best_line.r = r_step*y + r_min ;
					
					max_hough_x = x, max_hough_y = y ;
					max_hough = *h ;
				}
			}
			
		
			if ( max_hough == 0 )
				break ;
	
			lines.push_back(best_line) ;
			
			
			// debug
			//cout << max_hough << " - " << best_line.r << " " << best_line.t << endl ;
			cout << max_hough << " - " << max_hough_x << " " << max_hough_y << endl ;
			
			//
			// now collect all the candidate pixels beloning to that line
			//
			// convert to implicit equation
			//AImplicitLine<T> implicit_line ;
			//convert(best_line,implicit_line) ;
			AParametricLine<T> parametric_line ;
			line_convert(best_line,parametric_line) ;
			vector<APoint2D<int> > candidate_points ;
			const Edge<T>::edge_type *e = edges.edges() ;
			APoint2D<int> pt ;
			T point_dispersion = 3 ;
			for ( int y = 0 ; y < height ; ++y ) {
				for ( int x = 0 ; x < width ; ++x, ++e ) {
					if ( !e->edge )
						continue ;
					
					if ( dist(*e,best_line) < point_dispersion ) {
						pt.x = x, pt.y = y ;
						candidate_points.push_back(pt) ;
					
						// cout << x << "," << y << " = " << dist(*e,best_line) << endl ;
					}
				}
			}
			
			if ( candidate_points.empty() )
				break ;
			
			// debug
			//for ( vector<APoint2D<int> >::iterator p = candidate_points.begin() ; p != candidate_points.end() ; ++p )
			//	cout << p->x << " " << p->y << endl ;
			
			// now select all those from candidate points who form a line
			// the largest chunk
			
			// sort the points by line - by the distance to some point
			multimap<T,APoint2D<int> > lined_points ;
			APoint2D<int> first_point = *(candidate_points.begin()) ;
			
			lined_points.insert(pair<T,APoint2D<int> >(0,first_point)) ;
			
			for ( vector<APoint2D<int> >::iterator p = candidate_points.begin() ; p != candidate_points.end() ; ++p ) {
				lined_points.insert(pair<T,APoint2D<int> >(pt_dist(first_point,*p),*p)) ;
			}
			
			// now find the largest group 
			multimap<T,APoint2D<int> >::iterator prev_pt = lined_points.begin(), curr_pt = prev_pt, end_pt = lined_points.end() ;
			multimap<T,APoint2D<int> >::iterator largest_begin, largest_end, largest_last, block_begin ;
			
			int max_count = 0, current_count = 0 ;
			size_t seg_prev = segments.size() ;
			
			for ( block_begin = curr_pt, ++curr_pt ; curr_pt != end_pt ; ++curr_pt, ++prev_pt, ++current_count ) {
				int curr_dist = curr_pt->first - prev_pt->first ;
				if ( curr_dist < 5 )  // distance
					continue ;
				
				// break the group
				//if ( current_count > max_count ) {
				if ( current_count > 30 ) {
					max_count = current_count ;
					largest_begin = block_begin ;
					largest_end = curr_pt ;
					
					APointLine<int> pl(largest_begin->second,prev_pt->second) ;
					segments.push_back(pl) ;
				}
				
				current_count = 0 ;
				block_begin = curr_pt ;
			}
			//if ( current_count > max_count ) {
			if ( current_count > 30 ) {
				largest_begin = block_begin, largest_end = end_pt ;
				
				APointLine<int> pl(largest_begin->second,prev_pt->second) ;
				segments.push_back(pl) ;
			}
			
			//cout << max_count << endl ;
			
			// check if we like this 
			
			int *hough = hough_data.get() ;
			
			// these points form the straight line
			//for ( multimap<T,APoint2D<int> >::iterator p = largest_begin ; p != largest_end ; ++p ) {
			for ( vector<APoint2D<int> >::iterator p = candidate_points.begin(), p_end = candidate_points.end() ; p != p_end ; ++p ) {
			//for ( vector<APoint2D<int> >::iterator p = segments[i].begin(), p_end = segments[i].end() ; p != p_end ; ++p ) {
					// remove these points from hough transform
									
					// do for all thetas
					pcos = cos_buffer ;
					psin = sin_buffer ;
				
					int y ;
					for ( int x = 0 ; x < hough_width ; ++x, ++pcos, ++psin ) {
						
						//r = p->second.x * *pcos + p->second.y * *psin ;
						r = p->x * *pcos + p->y * *psin ;
								
						y = int((r-r_min)/r_step+0.5) ;
								
						if ( x < 0 || x >= hough_width || y < 0 || y >= hough_height )
							continue ;
								
						hough[y*hough_width+x]-- ;
					}
					
					//largest_last = p ;  // remember the last valid memeber
			//	}
			}
			
			//for ( multimap<T,APoint2D<int> >::iterator p = largest_begin ; p != largest_end ; ++p ) {
			//	largest_last = p ;  // remember the last valid memeber
			//}
			
			// build all the line segments
			//APointLine<int> pl(largest_begin->second,largest_last->second) ;
			//segments.push_back(pl) ;
			

			//multimap<T,APoint2D<int> >::iterator group_begin = lined_points.begin(), group_end ;
			//for ( multimap<T,APoint2D<int> >::iterator 
			
			//break ;
		}
		
		cout << '\t' << "segments: " << segments.size() << endl ;
	}
	
	
	/*
	{
		// select only maximas from hough transform
		ABuffer<int> hough_maxima(hough_total) ;
		suppress_non_maxima(hough_data.get(),hough_maxima.get(),hough_width,hough_height) ;
		
		// have some hough threshold
		int hough_threshold_ = 270 ;
		

		const T theta_step = (theta_max-theta_min)/hough_width ;
		const T r_step = (r_max-r_min)/hough_height ;
		
		int *h = hough_data.get() ;
		for ( int y = 0 ; y < hough_height ; ++y ) {
			for ( int x = 0 ; x < hough_width ; ++x, ++h ) {
				if ( *h < hough_threshold_ )
					continue ;

				line_type l ;					
				l.t = theta_step*x + theta_min ;
				l.r = r_step*y + r_min ;
				//l.r = cos(l.t) * x + sin(l.t) * y ;
				
				//AParametricLine<T> p ;
				//line_convert(l,p) ;
				//cout << l.r << " " << l.t << " - " << p.p.x << "," << p.p.y << " " << p.u.x << "," << p.u.y << endl ;
				
				lines.push_back(l) ;
			}
		}
	}
	*/
	
	//
	// show the edges
	//
	{
		ABuffer<int> edges_image(total) ;
		edges_image.zero() ;
		
		const char *m = edges.edges_mask() ;
		int *p = edges_image.get() ;

		for ( int i = 0 ; i < total ; ++i, ++m, ++p )
			if ( *m )
				*p = max_pixel ;
		
	
		image_save(edges_image.get(),width,height,str_format(output_file_name,"%s-edges.%s",input_file_name,input_file_ext) ) ;
	}
	
	//
	// show the lines
	//
	{
		ABuffer<int> lines_image(total) ;
		normalize(image.get(),lines_image.get(),total,0,max_pixel) ;
		
		
		for ( line_container_type::const_iterator l = lines.begin() ; l != lines.end() ; ++l ) {
			render_line(*l,lines_image.get(),width,height,max_pixel) ;
		}
		
		image_save(lines_image.get(),width,height,str_format(output_file_name,"%s-lines.%s",input_file_name,input_file_ext) ) ;
	}
	

	//
	// show line segments
	//
	{
		ABuffer<int> lines_image(total) ;
		normalize(image.get(),lines_image.get(),total,0,max_pixel) ;
		
		
		for ( point_line_container_type::const_iterator l = segments.begin() ; l != segments.end() ; ++l ) {
			bresenham_line(l->u.x,l->u.y,l->v.x,l->v.y,lines_image.get(),width,height,max_pixel) ;
			
			// debug
			//cout << l->u.x << " " << l->u.y << ", " << l->v.x << " " << l->v.y << endl ;
		}
		
		image_save(lines_image.get(),width,height,str_format(output_file_name,"%s-segments.%s",input_file_name,input_file_ext) ) ;
	}
}



void cmdline(int argc, char *argv[] )
{
	using namespace std ;
	using namespace apl ;
	
	// command line parsing
	string name, value, arg ;
	for ( int iarg = 1 ; iarg < argc ; iarg++ ) {
		arg = argv[iarg] ;
		if ( arg[0] != '-' )
			opt_input_file = arg ;
		else {
			apl::str_split(arg,'=',name,value) ;
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

int main(int argc, char *argv[])
{
	using namespace apl ;
	using namespace std ;
	using namespace cognit ;
	
	int ret_code = 1 ;

	try {
		cmdline(argc,argv) ;
		process() ;

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
