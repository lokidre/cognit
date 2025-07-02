/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

/*
				Detecting straight lines

*/

#include <vector>

#include "edges.hpp"

#include "../geo/line.hpp"
#include "../dsp/hough.hpp"
#include "../geo/line/dist.hpp"

namespace cognit {



template <class T>
class LineDetector {

public :
	typedef T float_type ;

	typedef cognit::ANormalLine<T> normal_line_type ;

	typedef normal_line_type value_type ;


	typedef std::vector<value_type> line_container_type ;


public :  // options
	//T sigma_ ;
	int aperture_ ;
	T point_dispersion_ ;
	int hough_width_, hough_height_ ;
	T theta_min_, theta_max_ ;
	//T r_min_, r_max_ ;


private :  // used classes, buffers, etc.
	typedef std::vector<typename cognit::EdgeDetector<T>::edge_type> point_list_type ;


public :  // result
	EdgeDetector<T> edges_ ;
	line_container_type lines_ ;

public :
	void set_sigma(const T &s ) {  edges_.set_sigma(s) ;  }


public :

	LineDetector()
	{
		// sigma_ = 1 ;
		aperture_ = 11 ;
		point_dispersion_ = 5 ;
		//hough_width_ = 2000, hough_height_ = 2000 ;
		hough_width_ = 1000, hough_height_ = 1000 ;
		//hough_width_ = 100, hough_height_ = 100 ;
		theta_min_ = 0 ;
		theta_max_ = const_pi<T>()() ;
	}


public :
	template <class image_type>
	void detect(const image_type *image, const int width, const int height )
	{
		using namespace std ;
		using namespace apl ;

		// do edge detection
		edges_(image,width,height) ;

		const int total = width * height ;


		// Hough transform stuff
		int hough_width = hough_width_ ; // std::min(width/4,height/4) ;
		int hough_height = hough_height_ ;  // hough_width*2 ;
		int hough_total = hough_width*hough_height ;
		T theta_min = theta_min_ ;
		T theta_max = theta_max_ ; 
		
		T r_max = hypot(width,height) + T(10) ;
		T r_min = -r_max ;
			
		ABuffer<int> hough_data(hough_total) ;
		ABuffer<T> hough_buffer(hough_width*2) ;
		

		const T theta_step = (theta_max-theta_min)/hough_width ;
		const T r_step = (r_max-r_min)/hough_height ;
		T *cos_buffer = hough_buffer ;
		T *sin_buffer = cos_buffer + hough_width ;

		// prebuild sine and cosine buffers
		hough_build_cosin(hough_width,hough_height,theta_min,theta_max,r_min,r_max,cos_buffer,sin_buffer) ;

		// do Hough transform
		hough_cosin(edges_.begin(),edges_.end(),hough_data.get(),hough_width,hough_height,theta_min,theta_max,r_min,r_max,cos_buffer,sin_buffer) ;

		T max_angle = const_pi<T>()()/20 ;

		//
		// select good lines
		//
		for ( int iline = 0 ; iline < 100 ; iline++ ) {
			int max_hough, max_hough_x, max_hough_y ;
			//Line best_line ;
			normal_line_type best_line ;

			hough_best(hough_width,hough_height,theta_min,theta_max,r_min,r_max,hough_data.get(),best_line.r,best_line.t,max_hough_x,max_hough_y,max_hough) ;

			if ( max_hough < 200 )
				break ;

			point_list_type candidate_points ;

			ANormalLine<T> best_line_normal ;
			best_line_normal.r = best_line.r, best_line_normal.t = best_line.t ;
			for ( EdgeDetector<T>::iterator e = edges_.begin(), e_end = edges_.end() ; e != e_end ; ++e ) {
				if ( pt_dist(*e,best_line_normal) <= point_dispersion_ )
					candidate_points.push_back(*e) ;
			}
				
			if ( candidate_points.size() < 10 )
				break ;

			// verify if this is duplicate line due to noise
			bool found = false ;
			for ( line_container_type::iterator l = lines_.begin() ; l != lines_.end() ; ++l ) {
				if ( abs(best_line.r-l->r) < 20 && abs(best_line.t-l->t) < max_angle ) {
					found = true ;
					break ;
				}
			}
			if ( !found )
				lines_.push_back(best_line) ;

			unhough_cosin(candidate_points.begin(),candidate_points.end(),hough_data.get(),hough_width,hough_height,theta_min,theta_max,r_min,r_max,cos_buffer,sin_buffer) ;
		}


	}

} ;


}

