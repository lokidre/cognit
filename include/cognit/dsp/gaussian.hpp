/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#if Description__

Zero mean Gaussian distribution - 1D

    G(x) = 1 over { %sigma sqrt{2 %pi} } %e^{- {(x-%mu)^2 over {2 %sigma^2}} }

where
    $sigma$ - standard deviation of the distribution
    %mu - mean (further assume 0)


2-D isotropic zero mean Gaussian distribution has the form


                           2    2
                          x  + y
               1      - ---------
  G(x,y) = -------- e      2s^2
                 2
             2P s

    Property:

        G(x,y) = G(x)G(y)


First derivative has the form

        G'(x) = - {x over {%sigma^3 sqrt(2 %pi)} } %e^{- {x^2 over {2 %sigma^2 }}}


    G^(x,y)(x,y) = {x y} over {  }

                                 x^2 + y^2
                   x y        - -----------
  G'(x,y) = --------------  e       2s^2
              2 pi s^2 s^4

#endif


#include "convolution.hpp"
#include "normalize.hpp"
#include "gradient.hpp"
#include "../const.hpp"

namespace cognit {



// buffer size = aperture * aperture * sizeof(float_type)
// sigma - standard deviation

template <class T, class Idx>
void kernel_Gx(T* kernel, Idx aperture, T sigma) noexcept
{
    // sqrt(2*pi)
    auto sqrt_2pi = (T)2.50662827463100050241576528481105;

    // sqrt(2*pi) * sigma
    auto sqrt_2pi_s = sqrt_2pi * sigma;

    // 2 * sigma^2
    auto sqr_s_2 = sigma * sigma * 2;

    auto apertureHalf = aperture/2;

    T sum{};

    auto k = kernel;
    for (Idx i = 0; i <= apertureHalf; ++i, ++k) {
        auto x = static_cast<T>(i - apertureHalf);
        *k = std::exp(-x*x / sqr_s_2) / sqrt_2pi_s;
        sum += *k;
    }

    // the other half is symmetric
    k = kernel;
    auto kh = kernel + aperture - 1;
    for (Idx i = 0; i < apertureHalf; ++i, ++k, --kh) {
        *kh = *k;
        sum += *k;
    }

    // Normalize
    auto total = aperture;
    auto coeff = T(1) / sum;
    for (auto kk = kernel, end = kk + total; kk != end; ++kk) {
        *kk *= coeff;
    }

}

template <class T, class Idx>
void kernel_Gxy(T* kernel, Idx aperture, T sigma) noexcept
{
    // 2pi
    auto _2pi = constants::pi<T> * 2;

    // 2*pi*sigma^2
    auto _2pi_s2 = _2pi * sigma * sigma;

    // 2 * sigma^2
    auto sqr_s_2 = sigma * sigma * 2;

    auto apertureHalf = aperture / 2 ;

    T sum{};

    auto k = kernel;
    for (Idx j = 0; j < aperture; ++j) {
        for (Idx i = 0; i < aperture; ++i, ++k) {
            auto x = T(i - apertureHalf);
            auto y = T(j - apertureHalf);
            *k = std::exp(-(x*x + y*y) / sqr_s_2) / _2pi_s2;
            sum += *k;
        }
    }

    // Normalize
    auto total = aperture * aperture;
    auto coeff = T(1) / sum;
    for (auto kk = kernel, end = kk + total; kk != end; ++kk) {
        *kk *= coeff;
    }

  
}





//
// First Derivative of Gaussian
//


//
// requirements:
// aperture odd
// sigma > 0
//

template <typename float_type>
void kernel_dGx(float_type* kernel, int aperture, float_type sigma)
{
    if (sigma == 0 || (aperture & 1) == 0)
        return; //throw std::runtime_error("invalid arguments dGx") ;

    // sqrt(2*pi)
    const float_type sqrt_2pi = sqrt(const_pi<float_type>()());  // needed const

    // sqrt(2*pi)*sigma*sigma*sigma
    const float_type sqrt_2pi_s3 = sqrt_2pi*sigma*sigma*sigma;

    // 2*sigma^2
    const float_type sqr_s_2 = sigma*sigma*2;

    const int aperture_half = aperture >> 1;

    int i;
    float_type x;

    float_type* k = kernel;

    for (i = 0; i < aperture; ++i, ++k) {
        x = (float_type)(i - aperture_half);
        *k = -x*exp(-x*x/sqr_s_2) / sqrt_2pi_s3;
    }
}


template <typename float_type>
bool kernel_dGxy(float_type* kernel, int aperture, float_type sigma)
{
    if (sigma == 0 || (aperture & 1) == 0)
        return false;

    // sqrt(2*pi)
    float_type _2pi = const_pi<float_type>()()*2;

    float_type _s2 = sigma*sigma;  // sigma^2
    float_type _s6 = _s2*_s2*_s2;  // sigma^6
    float_type _2s2 = 2*_s2;  // 2*sigma^2

    // 2*pi*sigma^6
    float_type _2pi_s6 = _2pi*_s6;


    int aperture_half = aperture >> 1;
    int i, j;
    float_type* k, x, y;

    k = kernel;
    for (j = 0; j < aperture; j++)
        for (i = 0; i < aperture; i++, k++) {
            x = (float_type)(i - aperture_half), y = (float_type)(j - aperture_half);
            *k = x*y * exp(-(x*x+y*y)/_2s2) / _2pi_s6;
        }

    return true;
}



//
// Second derivative of Gaussian
//


//
//                               x^2
//             (x-s)(x+s)    - --------
// G''(x) = --------------- e   2s^2
//           \/(2 pi) s^5
//
template <class T>
void kernel_ddGx(T* kernel, int aperture, T sigma) noexcept
{
    int aperture_half = aperture >> 1;

    T s = sigma;
    T s2 = s * s;
    T _2s2 = 2 * s2;
    T sqrt_2pi = (T)2.50662827463100050241576528481105;
    T sqrt_2pi_s5 = sqrt_2pi * s2 * s2 *s;

    auto k = kernel;
    for (auto i = 0; i < aperture; i++, ++k) {
        auto x = i - aperture_half;
        auto x2 = T(x * x);
        *k = (x2 - s2) * std::exp(-x2 / _2s2) / sqrt_2pi_s5;
    }
}


//
//                                       x^2+y^2
//             (s^2-x^2)(s^2-y^2)    - -----------
// G''(x,y) = -------------------- e       2s^2
//                  2 pi s^10
//
template <typename float_type>
bool kernel_ddGxy(float_type* kernel, int aperture, float_type sigma)
{
    if (sigma == 0 || (aperture & 1) == 0)
        return false;

    float_type _2pi = (float_type)6.28318530717958647692528676655901;
    float_type s = sigma;
    float_type s2 = s*s;
    float_type _2s2 = 2*s2;
    float_type _2pi_s10 = _2pi*s2*s2*s2*s2*s2;

    int aperture_half = aperture >> 1;
    int i, j;
    float_type* k, x, y, x2, y2;

    k = kernel;
    for (j = 0; j < aperture; j++)
        for (i = 0; i < aperture; i++, k++) {
            x = i - aperture_half, y = j - aperture_half;
            x2 = x*x, y2 = y*y;
            *k = std::exp(-(x2+y2)/_2s2) * (s2-x2)*(s2-y2) / _2pi_s10;
        }

    return true;
}




/*
template <typename float_type, typename data_type>
bool gaussian_1d ( data_type *x_data, data_type *y_data, int width, int height, int aperture, float_type sigma, float_type *kernel )
{
  if ( !kernel_Gx ( kernel, aperture, sigma ) )
    return false ;

  if ( !convolve_1d_y ( x_data, y_data, width, height, aperture, kernel ) )
    return false ;

  return true ;
}


template <typename float_type, typename data_type>
inline
bool gaussian_2d ( data_type *in_data, data_type *out_data, int width, int height, int aperture, float_type sigma, float_type *kernel )
{
  kernel_Gxy ( kernel, aperture, sigma ) ;
  convolution_2d ( in_data, out_data, width, height, aperture, kernel ) ;

  return true ;
}

template <typename float_type, typename data_type>
inline
bool gaussian_1d_xy ( data_type *in_data, data_type *out_data, int width, int height, int aperture, float_type sigma, data_type *image_buffer, float_type *kernel )
{
  if ( !kernel_Gx ( kernel, aperture, sigma ) )
    return false ;

  convolve_1d_x ( in_data, image_buffer, width, height, aperture, kernel ) ;
  convolve_1d_y ( image_buffer, out_data, width, height, aperture, kernel ) ;

  return true ;
}



template <typename float_type, typename data_type>
void gaussian_2d_derivative_1 ( data_type *in_data, data_type *out_data, int width, int height, int aperture, float_type sigma, float_type *kernel, float_type *image_buffer )
{
  filter_kernel_Gxyd ( kernel, aperture, sigma ) ;
  convolution_2d ( in_data, image_buffer, width, height, aperture, kernel ) ;
  image_normalize ( image_buffer, out_data, width*height, 0.0, 255.0 ) ;
}


template <typename float_type, typename data_type>
void gaussian_2d_derivative_2 ( data_type *in_data, data_type *out_data, int width, int height, int aperture, float_type sigma, float_type *kernel, float_type *image_buffer )
{
  filter_kernel_Gxyd2 ( kernel, aperture, sigma ) ;
  convolution_2d ( in_data, image_buffer, width, height, aperture, kernel ) ;
  image_normalize ( image_buffer, out_data, width*height, 0.0, 255.0 ) ;
}


template <typename float_type, typename data_type>
void gaussian_norm_of_gradient ( data_type *in_data, data_type *out_data,
                                 int width, int height,
                                 int aperture, float_type sigma,
                                 float_type *kernel,
                                float_type *dx, float_type *dy, float_type *norm )
{
  int total = width * height ;

  filter_kernel_Gxd ( kernel, aperture, sigma ) ;

  convolve_1d_x ( in_data, dx, width, height, aperture, kernel ) ;
  convolve_1d_y ( in_data, dy, width, height, aperture, kernel ) ;

  gradient_norm ( dx, dy, norm, total ) ;

  image_normalize ( norm, out_data, total, 0.0, 255.0 ) ;
}
*/



}
