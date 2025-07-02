/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

//#include "../mat/func.hpp"


namespace cognit {


template <class input_type, class output_type>
void gradient_x_2d ( const input_type *in_buffer, output_type *gx_buffer, int width, int height )
{
    const input_type *pin, *nin, *in = in_buffer ;
    output_type *gx = gx_buffer ;
    int x, y ;
    const input_type zero(output_type(0)), two(output_type(2)) ;

    pin = in-1, nin = in+1 ;

    for ( y = 0 ; y < height ; ++y ) {
        *gx = 0 ;
        ++pin, ++nin, ++gx ;

        for ( x = 2 ; x < width ; ++x, ++gx, ++pin, ++nin )
            *gx = output_type((*nin - *pin)/two) ;

        *gx = 0 ;
        ++pin, ++nin, ++gx ;
    }
}


template <class input_type, class output_type>
void gradient_y_2d ( const input_type *in_buffer, output_type *gy_buffer, int width, int height )
{
    const input_type *pin, *nin, *in = in_buffer ;
    output_type *pgy, *gy = gy_buffer ;
    int x, y ;
    const input_type zero(output_type(0)), two(output_type(2)) ;


    for ( x = 0 ; x < width ; ++x, ++gy )
        *gy = 0 ;

    pin = in-width, nin=in+width ;

    for ( x = 0 ; x < width ; ++x, ++gy ) {
        ++gy, pin += width, nin += width ;

        pgy = gy ;

        for ( y = 2 ; y < height ; ++y, ++pgy, pin += width, nin += width )
            *pgy = output_type((*nin - *pin)/two) ;

        ++gy, pin += width, nin += width ;
    }

    for ( x = 0 ; x < width ; ++x, ++gy )
        *gy = 0 ;
}



/*

template <typename type>
inline
void gradient_x ( type *d, int width, int height, type *gx )
{
  int i, j, w1 = width - 1 ;
  type *g, *dn, *dp ;

  for ( j=0, g=gx, dp=d-1, dn=d+1 ; j < height ; j++ ) {
    *g = *dn - *(dp+1) ;
    g++, dp++, dn++ ;

    for ( i=1 ; i < w1 ; i++, dn++, dp++, g++ )
      *g = *dn - *dp ;

    *g = *(dn-1) - *dp ;
    dn++, dp++, g++ ;
  }
}


template <typename type>
inline
void gradient_y ( type *d, int width, int height, type *gy )
{
  int i, j, h1 = height-1 ;
  type *g, *dn, *dp ;

  g = gy, dn = d+width, dp = d-width ;


  dp += width ;
  for ( i = 0 ; i < width ; i++, g++, dp++, dn++ )
    *g = *dn - *dp ;
  dp -= width ;
     for ( j = 1 ; j < h1 ; j++ ) {
    for ( i = 0 ; i < width ; i++, g++, dp++, dn++ )
      *g = *dn - *dp ;
  }


  dn -= width ;
  for ( i = 0 ; i < width ; i++, g++, dp++, dn++ )
    *g = *dn - *dp ;

}
*/



/*
template <typename data_type, typename vector_type>
inline
void calculate_gradient_y ( data_type *data, int width, int height, vector_type *gradient )
{
  for ( int j = 1 ; j < height - 1 ; j++ ) {
    for ( int i = 0 ; i < width ; i++ ) {
      gradient[j*width+i].y = data[(j+1)*width+i] - data[(j-1)*width+i] ;
    }
  }
}
*/


/*
template <typename data_type, typename vector_type>
inline
void gradient_xy ( data_type *data, int width, int height, vector_type *gradient )
{
  for ( int j = 1 ; j < height - 1 ; j++ ) {
    for ( int i = 1 ; i < width - 1 ; i++ ) {
      gradient[j*width+i].x = data[j*width+(i+1)] - data[j*width+(i-1)] ;
      gradient[j*width+i].y = data[(j+1)*width+i] - data[(j-1)*width+i] ;
    }
  }
}

template <typename data_type, typename vector_type>
inline
void gradient_xy_sqr ( data_type *data, int width, int height, vector_type *gradient )
{
  data_type gx, gy ;

  for ( int j = 1 ; j < height - 1 ; j++ ) {
    for ( int i = 1 ; i < width - 1 ; i++ ) {
      gx = data[j*width+(i+1)] - data[j*width+(i-1)] ;
      gy = data[(j+1)*width+i] - data[(j-1)*width+i] ;
      gradient[j*width+i].x = gx*gx ;
      gradient[j*width+i].y = gy*gy ;
      gradient[j*width+i].z = gx*gy ;
    }
  }
}
*/

}  // namespace


