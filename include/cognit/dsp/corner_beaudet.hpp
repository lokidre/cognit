/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
// Copyright (C) 2003-2004 Andrey Mirzoyan
// For conditions of distribution and use, see LICENSE file


#pragma once


/*
  Beaudet DET operator

                  2
  DET = IxxIyy-Ixy

*/

namespace cognit {


template <typename in_data_type, typename out_data_type, typename float_type>
bool beaudet_det ( in_data_type *src, out_data_type *dst, 
                   int width, int height,
                   int aperture, float_type sigma,
                   float_type *kernel, float_type *det,
                   float_type *gx, float_type *gy, float_type *gxy )
{
  int i ;
  int total = width * height ;

  filter_kernel_Gxd2 ( kernel, aperture, sigma ) ;

  filter_convolution_1d_x ( src, gx, width, height, aperture, kernel ) ;
  filter_convolution_1d_y ( src, gy, width, height, aperture, kernel ) ;


  filter_kernel_Gxyd ( kernel, aperture, sigma ) ;

  filter_convolution_2d ( src, gxy, width, height, aperture, kernel ) ;


  // det_i = gx_i*gy_i - gxy_i*gxy_i ;
  float_type *pdet, *pgx, *pgy, *pgxy ;
  pdet = det, pgx = gx, pgy = gy, pgxy = gxy ;
  for ( i = 0 ; i < total ; i++, pdet++, pgx++, pgy++, pgxy++ )
    //*pdet = (float_type)fabs((*pgx)*(*pgy) - (*pgxy)*(*pgxy)) ;
    *pdet = (*pgx)*(*pgy) - (*pgxy)*(*pgxy) ;

  image_normalize ( det, dst, total, 0.0, 255.0 ) ;

  return true ;
}





template <typename in_data_type, typename out_data_type, typename float_type>
bool corner_beaudet ( in_data_type *src, out_data_type *dst, 
                      int width, int height,
                      int aperture, float_type sigma,
                      float_type *kernel, float_type *det,
                      float_type *gx, float_type *gy, float_type *gxy )
{
  filter_det ( src, dst, width, height, aperture, sigma, kernel, det, gx, gy, gxy ) ;

  for ( int i = 1 ; i < width - 1 ; i++ )
    for ( int j = 1 ; j < height - 1 ; j++ ) {
      //float_type d = det[j*width+i] ;
      dst[j*width+i] = dst[j*width+i] < 128 ? 0 : 255 ; 



      /*
      if ( d <= det[(j-1)*width+(i-1)] ||
           d <= det[(j-1)*width+(i-0)] ||
           d <= det[(j-1)*width+(i+1)] ||
           d <= det[(j-0)*width+(i-1)] ||
           d <= det[(j-0)*width+(i+1)] ||
           d <= det[(j+1)*width+(i-1)] ||
           d <= det[(j+1)*width+(i-0)] ||
           d <= det[(j+1)*width+(i+1)] )
        dst[j*width+i] = 0 ;
      else
        dst[j*width+i] = 255 ;
        */
    }

  return true ;
}


}  // namespace

