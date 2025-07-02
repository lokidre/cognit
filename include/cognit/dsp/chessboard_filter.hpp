/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

// Copyright (C) 2003-2004 Andrey Mirzoyan
// For conditions of distribution and use, see LICENSE file

#include "gaussian.hpp"
#include "convolution.hpp"
#include "maxima.hpp"


namespace cognit {

template <typename float_type, typename src_data_type, typename dst_data_type>
void chessboard ( src_data_type *src, dst_data_type *dst, 
                  int width, int height, int aperture, 
                 float_type sigma, float_type curly_kappa, float_type kappa,
                 float_type *kernel,
                 float_type *Ixx, float_type *Iyy, float_type *Ixxyy, 
                 float_type *Ix, float_type *Iy, float_type *Ixy,
                 float_type *buffer )
{
  filter_kernel_Gxd2 ( kernel, aperture, sigma ) ;
  filter_convolution_1d_x ( src, Ixx, width, height, aperture, kernel ) ;
  filter_convolution_1d_y ( src, Iyy, width, height, aperture, kernel ) ;

  filter_kernel_Gxyd2 ( kernel, aperture, sigma ) ;
  filter_convolution_2d ( src, Ixxyy, width, height, aperture, kernel ) ;


  filter_kernel_Gxd ( kernel, aperture, sigma ) ;
  filter_convolution_1d_x ( src, Ix, width, height, aperture, kernel ) ;
  filter_convolution_1d_y ( src, Iy, width, height, aperture, kernel ) ;

  filter_kernel_Gxyd ( kernel, aperture, sigma ) ;
  filter_convolution_2d ( src, Ixy, width, height, aperture, kernel ) ;



  int total = width * height ;
  float_type *pIxx = Ixx, *pIyy = Iyy, *pIxxyy = Ixxyy, *pIx = Ix, *pIy = Iy, *pIxy = Ixy ;
  float_type *b = buffer ;
  
  for ( int i = 0 ; i < total ; i++, b++, pIxx++, pIyy++, pIxxyy++, pIx++, pIy++, pIxy++ ) {
    *b = ((*pIxx)*(*pIxx)*(*pIyy)*(*pIyy) -(*pIxxyy)*(*pIxxyy)*(*pIxxyy)*(*pIxxyy)) 
         -curly_kappa*((*pIx)*(*pIx)*(*pIy)*(*pIy)-(*pIxy)*(*pIxy)*(*pIxy)*(*pIxy))
         -kappa*((*pIx)*(*pIx)+(*pIy)*(*pIy))*((*pIx)*(*pIx)+(*pIy)*(*pIy)) ;

    if ( *b < 0 )
      *b = 0 ;
  }

  if ( sizeof(dst_data_type) == 1 )
    image_normalize ( buffer, dst, total, 0.0, 255.0 ) ;
  else
    image_normalize ( buffer, dst, total, 0.0, 1.0 ) ;
}

template <typename float_type, typename data_type>
void filter_find_chessboard ( data_type *src, data_type *dst, 
                              int width, int height, int aperture, 
                              float_type sigma, float_type curly_kappa, float_type kappa, float_type delta,
                              float_type *kernel,
                              float_type *Ixx, float_type *Iyy, float_type *Ixxyy, 
                              float_type *Ix, float_type *Iy, float_type *Ixy,
                              float_type *buffer, float_type *buffer2 )
{
  filter_isection ( src, buffer, width, height, aperture, sigma, curly_kappa, kappa, kernel, Ixx, Iyy, Ixxyy, Ix, Iy, Ixy, buffer2 ) ;
  suppress_non_maxima ( buffer, buffer2, width, height ) ;

  int total = width * height ;
  for ( int i = 0 ; i < total ; i++ )
    dst[i] = buffer2[i] > delta ? 255 : 0 ;  // needed

  //image_normalize ( buffer, dst, total, 0.0, 255.0 ) ;
}

template <typename float_type, 
          typename data_type, 
          typename container_type, 
          typename point_type>
void filter_find_chessboard_sub_pix ( data_type *src, container_type &maxima, 
                            int width, int height, int aperture, 
                            float_type sigma, float_type curly_kappa, float_type kappa, float_type delta,
                            float_type *kernel,
                            float_type *Ixx, float_type *Iyy, float_type *Ixxyy, 
                            float_type *Ix, float_type *Iy, float_type *Ixy,
                            float_type *buffer, float_type *buffer2 )
{
	filter_chessboard ( src, buffer, width, height, aperture, sigma, curly_kappa, kappa, kernel, Ixx, Iyy, Ixxyy, Ix, Iy, Ixy, buffer2 ) ;
	find_maxima<float_type,float_type,container_type,point_type> ( buffer, maxima, width, height, delta ) ;
}

}  // namespace cognit


