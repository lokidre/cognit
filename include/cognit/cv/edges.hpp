/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include "../dsp/border.hpp"
#include "../dsp/gaussian.hpp"
#include "../dsp/gradient_norm.hpp"
#include "../dsp/convolution.hpp"
#include "../dsp/threshold.hpp"
#include "../dsp/hysteresis.hpp"
#include "../dsp/maxima.hpp"

#include "../geo/vector.hpp"

#include <apeal/buffer.hpp>

namespace cognit {


//
// Edges using convolution with first derivative of Gaussian
//
// Buffers must be supplied: gx_buffer, gy_buffer, norm_buffer - size width*height
// kernel - aperture*aperture

template <class T>
class EdgeDetector {

public :  // data types
	typedef T data_type ;
	typedef char mask_type ;
		
	// all the information about the edge
	struct edge_type {
		typedef T value_type ;
	
		bool edge;  // this is edge - the main flag
		int xx, yy ;  // column and row of the pixel containing the edge
		T gx, gy ;  // gradients among x and y directions
		T norm ;  // norm of gradient
		T x, y ;  // subpixel coordinates of the edge
		AVector2D<T> n ;  // normal vector to the edge direction
			
		// next and previous edges towards the direction of the edge
		AVector2D<int> next, prev ;
		
	} ;
		
	// iterator through the edge points
	struct iterator {
		typedef edge_type value_type ;
			
		const value_type *current_, *end_ ;
		//int length_ ;
			
		const value_type *operator ->() {  return current_ ;  }
		const int operator ==(const iterator &it) const {  return current_ == it.current_ ;  }
		const int operator !=(const iterator &it) const {  return current_ != it.current_ ;  }
		
		iterator &operator ++() 
		{  
			while ( ++current_ < end_ && !current_->edge )
				;
			return *this ;  
		}
		
		void set(const value_type *begin, const value_type *end )
		{
			current_ = begin, end_ = end ;
			while ( current_ < end_ && !current_->edge )
				++current_ ;
		}
		
		const value_type &operator *() const {  return *current_ ;  }
	} ;
		
	typedef iterator const_iterator ;
		
	iterator begin() 
	{
		iterator it ;
		it.current_ = edges_.get() ;
		it.end_ = edges_.get() + total_ ;
			
		while ( it.current_ != it.end_ && !it.current_->edge )
			++it.current_ ;
		return it ;
	}
		
	iterator end()
	{
		iterator it ;
		it.current_ = edges_.get() + total_ ;
		it.end_ = it.current_ ;
		return it ;
	}
		

private :
		
	// all the parameteres for edge detection application
	T sigma_ ;
	int aperture_ ;
		
		
public :   // parameters
	//bool hysteresis_ ;
	bool contours_ ;
	T threshold_low_, threshold_high_ ;  // higher - less sensitivity
	bool threshold_percent_ ;  // way to treat threshold (absolute or percent)
	bool hysteresis_thresholding_ ;  // using hysteresis thresholding
	bool build_edges_ ;
	bool subpixel_ ;
		
public :  // results
	T threshold_value_low_, threshold_value_high_ ;
	int width_, height_, total_ ;

private :
		
	// buffers
	apl::Buffer<T> gx_buffer_, gy_buffer_, norm_buffer_, kernel_buffer_ ;
	apl::Buffer<mask_type> maxima_buffer_, edges_mask_ ;
		
	apl::Buffer<edge_type> edges_ ;
		
		
public :
	void set_sigma ( T s ) noexcept {  sigma_ = s ;  }
	T sigma() const noexcept {  return sigma_ ;  }
		
	void set_aperture ( int a ) noexcept {  aperture_ = a ;  }
	int aperture() const noexcept {  return aperture_ ;  }


public :   // access to buffers and data
	const T *gx() const {  return gx_buffer_.get() ;  }
	const T *gy() const {  return gy_buffer_.get() ;  }
	const T *norm() const {  return norm_buffer_.get() ;  }
	
	const mask_type *edges_mask() const {  return edges_mask_.get() ;  }
	const edge_type *edges() const {  return edges_.get() ;  }
				
		
	
public :
	EdgeDetector()
	{
		sigma_ = 1 ;
		aperture_ = 11 ;
		hysteresis_thresholding_ = true ;
		//threshold_low_ = 5, threshold_high_ = 10 ;
		threshold_low_ = 10, threshold_high_ = 20 ;
		threshold_percent_ = true ;
		subpixel_ = true ;
		
		total_ = width_ = height_ = 0 ;
	}
	
	
	
public :

	// main edge detection routine
	template <class image_type>
	void operator()(const image_type *image, int width, int height)
	{
		const int total = width * height ;
			
		width_ = width, height_ = height ;
		total_ = total ;
		
		// build Gaussian kernel
		kernel_buffer_.resize(aperture_*2) ;
		kernel_dGx ( kernel_buffer_.get(), aperture_, sigma_ ) ;

		gx_buffer_.resize(total) ;
		gy_buffer_.resize(total) ;
		norm_buffer_.resize(total) ;

		edges_.resize(total) ;
		edges_.zero() ;

			
		// convolve with Gaussian
		convolve_1d_x ( image, gx_buffer_.get(), width, height, aperture_, kernel_buffer_.get() ) ;
		convolve_1d_y ( image, gy_buffer_.get(), width, height, aperture_, kernel_buffer_.get() ) ;

		// calculate norm of gradient (needed option for square of norm)
		norm_of_gradient_2d ( gx_buffer_.get(), gy_buffer_.get(), norm_buffer_.get(), total ) ;

		// determine thresholds
		if ( threshold_percent_ ) {
			T max_norm = norm_buffer_.max() ;
			threshold_value_low_ = max_norm * threshold_low_ / 100 ;
			threshold_value_high_ = max_norm * threshold_high_ / 100 ;
		} else {  // we use absolute values of thresholds
			threshold_value_low_ = threshold_low_ ;
			threshold_value_high_ = threshold_high_ ;
		}
			

		// fill up the edge data
		{
			edge_type *e = edges_.get() ;
			T *gx = gx_buffer_.get(), *gy = gy_buffer_.get(), *norm = norm_buffer_.get() ;
			for ( int i = 0 ; i < total ; ++i, ++e, ++gx, ++gy, ++norm ) {
				e->gx = *gx ;
				e->gy = *gy ;
				e->norm = *norm ;
			}
		}
			
			
		maxima_buffer_.resize(total) ;
		edges_mask_.resize(total) ;

		// fill up all with ones, then keep filtering the data
		{
			mask_type *m = maxima_buffer_.get() ;
			mask_type *em = edges_mask_.get() ;
			for ( int i = 0 ; i < total ; ++i, ++m, ++em )
				*m = *em = 1 ;
		}

		//std::cout << threshold_value_high_ << " " << norm_buffer_.max() << std::endl ;

		// do threshold with the lowest value to never consider those low values
		if ( hysteresis_thresholding_ ) {
			threshold_low_mask ( norm_buffer_.get(), maxima_buffer_.get(), total, threshold_value_low_ ) ;
		} else {
			threshold_low_mask ( norm_buffer_.get(), maxima_buffer_.get(), total, threshold_value_high_ ) ;
		}

		//normalize ( maxima_buffer_.get(), total, float_type(255) ) ;
		//image_save(maxima_buffer_.get(),width,height,"debug.png" ) ;

		// suppress non-maxima
		if ( !subpixel_ ) {

			suppress_non_maxima_mask ( gx_buffer_.get(), gy_buffer_.get(), norm_buffer_.get(), maxima_buffer_.get(), width, height ) ;

		} else {  // do subpixel edge detection with maxima update

			const T eps = const_eps<T>()() ;

			//const mask_type *m = edges_mask_.get() ;
			mask_type *m = maxima_buffer_.get() ;
			edge_type *e = edges_.get() ;
			const T *gx = gx_buffer_.get(), *gy = gy_buffer_.get(), *n = norm_buffer_.get() ;

			T n_1, np1 ;  // y-1, y+1
			T maxy, k, g_ratio, g_sratio, sign_value ;
			T gx_abs, gy_abs ;
			int xp0, xp1, xp2, yp0, yp1, yp2 ;  // quadratic equations
			int xn0, xn1, xn2, yn0, yn1, yn2 ;  // quadratic equations
			T qa, qb, qc ;  // quadratic equations coefficients
			T ny0, ny1, ny2 ;


			// skip the first row
			for ( int i = 0 ; i < width ; ++i, ++e, ++m, ++gx, ++gy, ++n )
				*m = 0 ;

			int y = 1 ;
			for ( int j = y+1 ; j < height ; ++j, ++y ) {
				// skip first column
				*m = 0 ;
				++e, ++m, ++gx, ++gy, ++n ;

				int x = 1 ;
				for ( int i = x+1 ; i < width ; ++i, ++x, ++e, ++m, ++gx, ++gy, ++n ) {
					if ( *m == 0 )  // don't bother with small values
						continue ;

					// determine ratio (from that will depend whether we will goind horizontal or vertial)
					gx_abs = abs(*gx), gy_abs = abs(*gy) ;
							
					// check the ratio (keep it under 1)
					if ( gx_abs >= gy_abs ) {
						g_sratio = *gy / *gx ;
						g_ratio = gy_abs / gx_abs ;
					} else {
						g_sratio = *gx / *gy ;
						g_ratio = gx_abs / gy_abs ;
					}
								
					sign_value = *gx * *gy ;
							
					// we have two cases - vertical and horizontal
					if ( gx_abs >= gy_abs ) {  // vertical
						xp0 = xp1 = xp2 = 1 ;
						xn0 = xn1 = xn2 = -1 ;
						yp0 = -1, yp1 = 0, yp2 = 1 ;
						yn0 = -1, yn1 = 0, yn2 = 1 ;
					} else {  // horizontal
						xp0 = -1, xp1 = 0, xp2 = 1 ;
						xn0 = -1, xn1 = 0, xn2 = 1 ;
						yp0 = yp1 = yp2 = 1 ;
						yn0 = yn1 = yn2 = -1 ;
					}

					// now we can come up with two quadratic equations
					ny0 = n[yp0*width+xp0], ny1 = n[yp1*width+xp1], ny2 = n[yp2*width+xp2] ;
					qa = (ny0-2*ny1+ny2)/2, qb = (ny2-ny0)/2, qc = ny1 ;
							
					// value at intersection
					np1 = qa*g_sratio*g_sratio + qb*g_sratio + qc ;
							
							
					// same for the other side
					ny0 = n[yn0*width+xn0], ny1 = n[yn1*width+xn1], ny2 = n[yn2*width+xn2] ;
					qa = (ny0-2*ny1+ny2)/2, qb = (ny2-ny0)/2, qc = ny1 ;
							
					// value at intersection
					n_1 = qa*g_sratio*g_sratio + qb*(-g_sratio) + qc ;
							

					// check if this is maxima
					//if ( *n <= n_1 || *n <= np1 ) {
					if ( *n < n_1 || *n <= np1 ) {
						*m = 0 ;
						continue ;
					}
							
						
					// calculate next and previous pixel values
					if ( gx_abs > gy_abs )
						k = *n * 1 / gx_abs ;
					else
						k = *n * 1 / gy_abs ;
							
					maxy = (n_1 - np1)/(n_1 - 2* *n + np1)/2 ;
							
					maxy *= k ;
							
					// now do the final adjustment
					e->x += maxy*gx_abs / *n ;
					e->y += maxy*gy_abs / *n ;
					
					// temporary - needed remove - this shouldn't be happening
					if ( abs(e->x) >= 0.5 ) {
						k = abs(e->x/(float_type)0.5) ; //+0.00000000001 ;
						e->y /= k ;
						e->x /= k ;
					}

					if ( abs(e->y) >= 0.5 ) {
						k = abs(e->y/(float_type)0.5) ; //+0.00000000001 ;
						e->y /= k ;
						e->x /= k ;
					}
							
					e->x += x ;
					e->y += y ;
				}

				// skip last column
				*m = 0 ;

				++e, ++m, ++gx, ++gy, ++n ;
			}

			// last row
			for ( int i = 0 ; i < width ; ++i, ++e, ++m, ++gx, ++gy, ++n )
				*m = 0 ;
		}
			
		
		if ( hysteresis_thresholding_ ) {
			// now do hysteresis thresholding - to add low thresholds
			hysteresis_threshold ( norm_buffer_.get(), maxima_buffer_.get(), edges_mask_.get(), width, height, threshold_value_high_, threshold_value_low_ ) ;
		} else {
			memcpy(edges_mask_.get(),maxima_buffer_.get(),total*sizeof(mask_type)) ;
		}

		//normalize ( edges_mask_.get(), total, float_type(255) ) ;
		//image_save(edges_mask_.get(),width,height,"debug.png" ) ;

		// needed - countour connection thresholding (hyperhysteresis)
		// if we see that the new maxima will connect two contours - use that maxima also
			
			
		// update edges data
		{
			edge_type *e = edges_.get() ;
			mask_type *m = edges_mask_.get() ;
			for ( int i = 0 ; i < total ; ++i, ++e, ++m ) {
				e->edge = bool(*m != 0) ;
			}

			e = edges_.get() ;
			for ( int yy = 0 ; yy < height ; ++yy ) {
				for ( int xx = 0 ; xx < width ; ++xx, ++e ) {
					e->xx = xx, e->yy = yy ;
				}
			}
		}
		
	}


	void clear_border(int border)
	{
		edge_type null_edge ;
		null_edge.edge = false ;
		fill_border(edges_.get(),width_,height_,border,null_edge) ;
		fill_border(edges_mask_.get(),width_,height_,border,0) ;
	}
	
	int size()
	{
		int count = 0 ;
		auto m = edges_mask_ ;
		for ( int i = 0 ; i < total_ ; ++i, ++m )
			if ( *m )
				count++ ;
		return count ;
	}
	
} ;

}  // namespace cognit

