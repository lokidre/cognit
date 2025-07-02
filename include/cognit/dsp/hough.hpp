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
	                                 Hough Transform
	

	hough()               Hough Transform
	hough_build_cosin()   Build sine/cosine buffers 
	hough_cosin()         Hough transform using provided sine/cosine buffers
	unhough()             Remove given points from Hough transform
	unhough_cosin()       Same with using prebuilt sine and cosine buffers


	cos_buffer and sin_buffer must be not less than hough_width size
	cosin_buffer must be hough_width*2 size

	typical way to calculate r and theta
	T theta_min = 0 ;   // or -const_pi<T>()()/10
	T theta_max = const_pi<T>()() ;

	T r_max = hypot(width,height) + 10 ;
	T r_min = -r_max ;

*/



namespace cognit {


template <class T>
void hough_build_cosin ( 
				int hough_width, int hough_height,
				T theta_min, T theta_max,
				T r_min, T r_max,
				T *cos_buffer, T *sin_buffer ) noexcept
{
	const T delta_theta = (theta_max-theta_min)/hough_width;
	
	T theta ;
	
	T *cs = cos_buffer, *sn = sin_buffer ;
	for ( int tt = 0 ; tt < hough_width ; ++tt, ++cs, ++sn ) {
		theta = delta_theta*tt + theta_min ;
		*cs = cos(theta), *sn = sin(theta) ;
	}
}

template <class T, class point_iterator>
void hough_cosin (
			const point_iterator &pts_begin, const point_iterator &pts_end,
			int *hough,
			const int hough_width, const int hough_height,
			const T &theta_min, const T &theta_max,
			const T &r_min, const T &r_max,
			T *cos_buffer, T *sin_buffer )
{
	const T delta_r = (r_max-r_min)/hough_height ;

	T r, *cs, *sn ;
	int rr ;
	
	memset ( hough, 0, hough_width*hough_height*sizeof(int) ) ;

	for ( point_iterator p = pts_begin ; p != pts_end ; ++p ) {
								
		// do for all thetas
		cs = cos_buffer, sn = sin_buffer ;
			
		for ( int tt = 0 ; tt < hough_width ; ++tt, ++cs, ++sn ) {
					
			r = p->x * *cs + p->y * *sn ;
							
			//rr = int((r-r_min)/delta_r + 0.5) ;
			rr = int((r-r_min)/delta_r) ;
							
			if ( rr < 0 || rr >= hough_height )
				continue ;
							
			hough[rr*hough_width+tt]++ ;
		}

	}
}

template <class T, class point_iterator>
void unhough_cosin (
			const point_iterator &pts_begin, const point_iterator &pts_end,
			int *hough,
			const int hough_width, const int hough_height,
			const T &theta_min, const T &theta_max,
			const T &r_min, const T &r_max,
			T *cos_buffer, T *sin_buffer )
{
	const T delta_r = (r_max-r_min)/hough_height ;

	T r, *cs, *sn ;
	int rr ;

	for ( point_iterator p = pts_begin ; p != pts_end ; ++p ) {
								
		// do for all thetas
		cs = cos_buffer, sn = sin_buffer ;
			
		for ( int tt = 0 ; tt < hough_width ; ++tt, ++cs, ++sn ) {
					
			r = p->x * *cs + p->y * *sn ;
							
			//rr = int((r-r_min)/delta_r + 0.5) ;
			rr = int((r-r_min)/delta_r) ;
			//rr = int((r-r_min)/delta_r-0.5) ;
							
			if ( rr < 0 || rr >= hough_height )
				continue ;
							
			hough[rr*hough_width+tt]-- ;
		}

	}
}




//
// buffer must be 2*width length
//
template <class T, class point_iterator>
inline
void hough ( 
		point_iterator pts_begin, const point_iterator pts_end, 
		int *hough,
		const int hough_width, const int hough_height, 
		const T &theta_min, const T &theta_max,
		const T &r_min, const T &r_max,
		T *cosin_buffer )
{
	T *cos_buffer = csin_buffer ;
	T *sin_buffer = cos_buffer + hough_width ;

	hough_build_cosin(hough_width,hough_height,theta_min,theta_max,r_min,r_max,cos_buffer,sin_buffer) ;
	hough_cosin(pts_begin,pts_end,hough,hough_width,hough_height,theta_min,theta_max,r_min,r_max,cos_buffer,sin_buffer) ;
}

//
// buffer must be 2*width length
//
template <class T, class point_iterator>
void unhough ( 
		point_iterator pts_begin, const point_iterator pts_end, 
		int *hough,
		int hough_width, int hough_height, 
		T theta_min, T theta_max,
		T r_min, T r_max,
		T *cosin_buffer )
{
	T *cos_buffer = csin_buffer ;
	T *sin_buffer = cos_buffer + hough_width ;

	hough_build_cosin(hough_width, hough_height, theta_min, theta_max, r_min, r_max, cos_buffer, sin_buffer) ;
	unhough_cosin(pts_begin, pts_end, hough, hough_width, hough_height, theta_min, theta_max, r_min, r_max, cos_buffer, sin_buffer) ;
}


//
// selects the best line from hough transform
//
template <class T>
void hough_best ( int hough_width, int hough_height,
				  T theta_min, T theta_max,
				  T r_min, T r_max,
				  const int *hough_data,
				  T &best_r, T &best_t,
				  int &max_hough_x, int &max_hough_y,
				  int &max_hough ) noexcept
{
	const T delta_r = (r_max-r_min)/hough_height ;
	const T delta_theta = (theta_max-theta_min)/hough_width ;

	auto h = hough_data ;
	max_hough = 0 ;

	for ( int rr = 0 ; rr < hough_height ; ++rr ) {
		for ( int tt = 0 ; tt < hough_width ; ++tt, ++h ) {
			if ( *h <= max_hough  )
				continue ;
			best_t = delta_theta*tt + theta_min ;
			//best_r = delta_r*(T(rr)-0.5) + r_min ;
			//best_r = delta_r*(T(rr)+0.5) + r_min ;
			best_r = delta_r*(T(rr)) + r_min ;
					
			max_hough_x = tt, max_hough_y = rr ;
			max_hough = *h ;
		}
	}
}

}  // namespace cognit
