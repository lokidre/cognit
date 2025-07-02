/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include "../dsp/harris.hpp"
#include "../dsp/gaussian.hpp"

#include <apeal/buffer.hpp>

namespace cognit {


template <class T>
class CornerDetector {

public :  // data types
	typedef T data_type ;
	typedef char mask_type ;

	struct corner_type {
		typedef T value_type ;
	
		bool valid ;  // the main flag
		int xx, yy ;  // column and row of the pixel containing the corner
		T x, y ;  // subpixel coordinates of the corner
		T value ;  // value of the feature
		T gx, gy ;  // gradients among x and y directions
		// T norm ;  // norm of gradient
		//AVector2D<T> n ;  // normal vector to the corner direction
	} ;

	// iterator through the edge points
	struct iterator {
		typedef corner_type value_type ;
			
		const value_type *current_, *end_ ;
			
		const value_type *operator ->() {  return current_ ;  }
		const int operator ==(const iterator &it) const {  return current_ == it.current_ ;  }
		const int operator !=(const iterator &it) const {  return current_ != it.current_ ;  }
		
		iterator &operator ++() 
		{  
			while ( ++current_ < end_ && !current_->valid )
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
		it.current_ = corners_.get() ;
		it.end_ = corners_.get() + total_ ;
			
		while ( it.current_ != it.end_ && !it.current_->valid )
			++it.current_ ;
		return it ;
	}
		
	iterator end()
	{
		iterator it ;
		it.current_ = corners_.get() + total_ ;
		it.end_ = it.current_ ;
		return it ;
	}

	int size()
	{
		int count = 0 ;
		corner_type *m = corners_.get() ;
		for ( int i = 0 ; i < total_ ; ++i, ++m )
			if ( m->valid )
				count++ ;
		return count ;
	}


private :  // all the parameteres for the algorithm
	T sigma_, kappa_ ;
	int aperture_ ;
		
public :   // parameters
	int threshold_ ;
	bool threshold_percent_ ;  // way to treat threshold (absolute or percent)
	bool subpixel_ ;

public :  // results
	T threshold_value_ ;
	int width_, height_, total_ ;


private :
	// buffers
	apl::Buffer<T> gx_buffer_, gy_buffer_, gxy_buffer_, harris_buffer_, kernel_buffer_ ;
	apl::Buffer<mask_type> maxima_buffer_, corners_mask_ ;

	apl::Buffer<corner_type> corners_ ;

public :
	void set_sigma ( const T &s ) {  sigma_ = s ;  }
	const T &sigma() const {  return sigma_ ;  }

	void set_kappa ( const T &s ) {  kappa_ = s ;  }
	const T &kappa() const {  return kappa_ ;  }

	void set_aperture ( const int a ) {  aperture_ = a ;  }
	const int aperture() const {  return aperture_ ;  }


public :   // access to buffers and data
	const T *gx() const {  return gx_buffer_.get() ;  }
	const T *gy() const {  return gy_buffer_.get() ;  }
	const T *norm() const {  return norm_buffer_.get() ;  }
	
	const mask_type *corner_mask() const {  return corner_mask_.get() ;  }
	const corner_type *corners() const {  return corners_.get() ;  }


public :
	CornerDetector()
	{
		sigma_ = 1 ;
		kappa_ = T(0.04) ;
		aperture_ = 11 ;

		threshold_ = 5 ;
		threshold_percent_ = true ;
		subpixel_ = true ;
		
		total_ = width_ = height_ = 0 ;
	}


		
public :

	// main routine
	template <class image_type>
	void detect( const image_type *image, const int width, const int height )
	{
		const int total = width * height ;
			
		width_ = width, height_ = height ;
		total_ = total ;
		
		kernel_buffer_.resize(aperture_*2) ;
		gx_buffer_.resize(total) ;
		gy_buffer_.resize(total) ;
		gxy_buffer_.resize(total) ;
		harris_buffer_.resize(total) ;
		corners_.resize(total) ;

		corners_.zero() ;

		// build Gaussian kernel
		kernel_dGx ( kernel_buffer_.get(), aperture_, sigma_ ) ;

		// convolve with Gaussian
		convolve_1d_x ( image, gx_buffer_.get(), width, height, aperture_, kernel_buffer_.get() ) ;
		convolve_1d_y ( image, gy_buffer_.get(), width, height, aperture_, kernel_buffer_.get() ) ;

		// calculate gx*gy
		T *gx = gx_buffer_.get(), *gy = gy_buffer_.get(), *gxy = gxy_buffer_.get() ;
		for ( int i = 0 ; i < total ; ++i, ++gx, ++gy, ++gxy ) {
			*gxy = *gx * *gy ;
			*gx *= *gx ;  //  square
			*gy *= *gy ;
		}
	
		harris ( gx_buffer_.get(), gy_buffer_.get(), gxy_buffer_.get(), harris_buffer_.get(), kappa_, total ) ;

		// calculate the thresholds
		// determine thresholds
		if ( threshold_percent_ ) {
			T max_val = harris_buffer_.max() ;
			threshold_value_ = max_val * threshold_ / 100 ;
		} else {  // we use absolute values of thresholds
			threshold_value_ = threshold_ ;
		}


		// now do the thresholding and building the corner
		{
			corner_type *c = corners_.get() ;
			T *h = harris_buffer_.get() ;
			int xx = 0, yy = 0 ;

			// skip first row
			for ( int i = 0 ; i < width ; ++i, ++xx, ++c, ++h )
				c->xx = xx, c->yy = yy, c->valid = false ;
			++yy ;


			for ( int j = 2 ; j < height ; ++j, ++yy ) {
				// skip first column
				xx = 0 ;
				c->xx = xx, c->yy = yy, c->valid = false ;
				++xx, ++c, ++h ;

				// for all columns
				for ( int i = 2 ; i < width ; ++i, ++xx, ++c, ++h ) {
					c->xx = xx, c->yy = yy, c->valid = false ;

					// thresholding
					if ( *h < threshold_value_ )
						continue ;

					// maxima
					if ( *h < *(h-1) || *h <= *(h+1) || *h < *(h-width) || *h <= *(h+width) || *h < *(h-width-1) || *h <= *(h+width-1) || *h < *(h-width+1) || *h <= *(h+width+1) )
						continue ;

					c->valid = true ;  // seems like a corner
					c->x = T(xx), c->y = T(yy) ;
					c->value = *h ;

					if ( subpixel_ ) {  // detect the corner with subpixel accuracy
						// TODO: needed
					}
				}

				// skip last column
				c->xx = xx, c->yy = yy, c->valid = false ;

				++xx, ++c, ++h ;
			}

			// last row
			for ( int i = 0 ; i < width ; ++i, ++xx, ++c, ++h )
				c->xx = xx, c->yy = yy, c->valid = false ;
			++yy ;
		}
	}


} ;

}

