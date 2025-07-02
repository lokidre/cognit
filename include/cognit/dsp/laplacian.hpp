/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#if Comment_Description

Laplacian L(x,y) of function f(x,y) is defined as

    $$
    L_f(x,y) = \frac{{\partial{^2}f}}{\partial{x^2}} 
             + \frac{{\partial{^2}f}}{\partial{y^2}}
    $$

Then Laplacian of Gaussian (LoG) becomes

    $$
    LoG(x, y) = \Delta G_\sigma(x, y) =
        - 
        \frac{1}{\pi\sigma^4} 
        \left[1 -
            \frac{x^2 + y^2}{2\sigma^2}
        \right]
        e^{-\frac{x^2 + y^2}{2\sigma^2}}
    $$

#endif


#include "convolution.hpp"
#include "normalize.hpp"

namespace cognit {

template <class F>
void LoGxy_kernel (F *kernel, int aperture, F sigma) noexcept
{
    int aperture_half = aperture/2;
    auto pi = const_pi<F>()();
    F x, y ;
    auto s = sigma;
    auto s2 = s * s;
    auto s4 = s2 * s2;

    auto k = kernel;
    for (int j = 0 ; j < aperture; ++j) {
        for (int i = 0 ; i < aperture; ++i, ++k) {
            x = (F)(i - aperture_half);
            y = (F)(j - aperture_half);
            auto x2 = x*x;
            auto y2 = y*y;
            *k = (x2 + y2 - 2*s2) * exp(-(x2 + y2)/(2*s2)) / (2*pi*s*s*s*s*s*s);
        }
    }
}


// buffer - float_type[image_size]
// kernel - float_type[aperture^2]

template <class F, class D>
void LoGxy (D *src, D *dst, int width, int height, int aperture, F sigma, F *buffer, F *kernel )
{
    LoGxy_kernel(kernel, aperture, sigma);
    convolution_2d(src, buffer, width, height, aperture, kernel);
}



template <typename float_type, typename data_type>
bool laplacian_of_gaussian_sharpen_2d ( data_type *src, data_type *dst, int width, int height, int aperture, float_type sigma, float_type *buffer, float_type *kernel )
{
/*
  int i ;
  int aperture_half = aperture/2 ;
  int total = width * height ;

  filter_kernel_LoGxy ( kernel, aperture, sigma ) ;
  filter_convolution_2d ( src, buffer, width, height, aperture, kernel ) ;

  filter_threshold 


  // subtract from original image
  for ( i = 0 ; i < total ; i++ ) {
    buffer[i] = ((float_type)src[i])-buffer[i] ;
    // thresholding
    if ( buffer[i] > 250 )
      buffer[i] = 250 ;
    if ( buffer[i] < 50 )
      buffer[i] = 50 ;
  }

  image_normalize ( buffer, dst, total, 0.0, 255.0 ) ;
*/
  return true ;
}



template <typename float_type, typename data_type>
bool laplacian_of_gaussian_edges_2d ( data_type *src, data_type *dst, int width, int height, int aperture, float_type sigma, float_type *buffer, float_type *kernel )
{
  int i ;
  int total = width * height ;

  filter_kernel_LoGxy ( kernel, aperture, sigma ) ;

  filter_convolution_2d ( src, buffer, width, height, aperture, kernel ) ;

  for ( i = 0 ; i < total ; i++ )
    dst[i] = ( buffer[i] < -10 && buffer[i] > -40 ) ? 255 : 0 ;

  return true ;
}

}  // namespace


