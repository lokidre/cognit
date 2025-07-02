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
                        Harris Corner Detector


*/


namespace cognit {



// Harris corner detector operator
//
// gxs - square of gradient among x
// gys - square of gradient among y
// gxy - gx*gy
// 
template <class T>
void harris(const T* gxs, const T* gys, const T* gxy, T* h, T kappa, int length) noexcept
{
    for (int i = 0; i < length; ++i, ++gxs, ++gys, ++gxy, ++h) {
        *h = *gxs * *gys - sqr(*gxy * *gxy) - kappa * sqr(*gxs + *gys);
        if (*h < 0)
            *h = -*h;
    }
}



/*
  Harris corner detector filter
// kappa = 0.04
*/
/*
template <typename in_data_type, typename out_data_type, typename float_type>
inline
bool harris ( in_data_type *src, out_data_type *dst,
                     int width, int height,
                     int aperture, float_type sigma, float_type kappa,
                     float_type *kernel, float_type *det,
                     float_type *gx, float_type *gy, float_type *gxy )
{
  int i ;
  int total = width * height ;

  filter_kernel_Gxd ( kernel, aperture, sigma ) ;

  filter_convolution_1d_x ( src, gx, width, height, aperture, kernel ) ;
  filter_convolution_1d_y ( src, gy, width, height, aperture, kernel ) ;

  // needed temp
  tVector3D<float_type> *grad = (tVector3D<float_type> *)malloc(width*height*sizeof(tVector3D<float_type>) ) ;


  for ( i = 0 ; i < total ; i++ )
    grad[i].x = grad[i].y = grad[i].z = 0 ;


  calculate_gradient_x ( gx, width, height, grad ) ;
  calculate_gradient_y ( gy, width, height, grad ) ;
  for ( i = 0 ; i < total ; i++ ) {
    grad[i].z = grad[i].x * grad[i].y ;
    grad[i].x *= grad[i].x ;
    grad[i].y *= grad[i].y ;
  }

  float_type *pdet, *pgx, *pgy, *pgxy ;
  pdet = det, pgx = gx, pgy = gy, pgxy = gxy ;
  for ( i = 0 ; i < total ; i++, pdet++, pgx++, pgy++, pgxy++ ) {
    //gx2 = (*pgx)*(*pgx), gy2 = (*pgy)*(*pgy), gxy2 = (*pgxy)*(*pgxy) ;
    *pdet = grad[i].x*grad[i].y - grad[i].z*grad[i].z - kappa * (grad[i].x+grad[i].y)*(grad[i].x+grad[i].y);

    if ( grad[i].x != 0 && grad[i].y != 0 ) {
      int a = 0 ;
    }
  }


  //int i ;
  //int total = width * height ;

  //filter_kernel_Gxd ( kernel, aperture, sigma ) ;

  //filter_convolution_1d_x ( src, gx, width, height, aperture, kernel ) ;
  //filter_convolution_1d_y ( src, gy, width, height, aperture, kernel ) ;


  //filter_kernel_Gxyd ( kernel, aperture, sigma ) ;

  //filter_convolution_2d ( src, gxy, width, height, aperture, kernel ) ;


  // det[i] = gx[i]*gx[i]*gy[i]*gy[i] - gxy[i]*gxy[i]*gxy[i]*gxy[i] - kappa * hypot(gx[i]*gx[i],gy[i]*gy[i]) ;
  //float_type gx2, gy2, gxy2 ;
  //float_type *pdet, *pgx, *pgy, *pgxy ;
  //pdet = det, pgx = gx, pgy = gy, pgxy = gxy ;
  //for ( i = 0 ; i < total ; i++, pdet++, pgx++, pgy++, pgxy++ ) {
  //  gx2 = (*pgx)*(*pgx), gy2 = (*pgy)*(*pgy), gxy2 = (*pgxy)*(*pgxy) ;
  //  *pdet = gx2*gy2 - gxy2*gxy2 - kappa * (gx2+gy2)*(gx2+gy2);
  //}


  image_normalize ( det, dst, total, 0.0, 255.0 ) ;

  return true ;
}
*/


/*
template <typename in_data_type, typename out_data_type, typename float_type>
inline
bool corner_harris ( in_data_type *src, out_data_type *dst, //tPoint3D<float_type> *corners, int &n,
                     int width, int height,
                     int aperture, float_type sigma, float_type kappa,
                     float_type *kernel, float_type *det,
                     float_type *gx, float_type *gy, float_type *gxy )
{
  int i, j ;
  int total = width * height ;
  float_type s = sigma ;
  float_type sqrt_2p = (float_type)2.506628274631 ;
  float_type x, y ;
  int aperture_half = aperture/2 ;

  for ( i = 0 ; i < aperture ; i++ ) {
    x = i-aperture_half ;
    kernel[i] = (float_type)(-x*exp(-x*x/(2*s*s))/(sqrt_2p*s*s*s)) ;
  }

  filter_convolution_1d_x ( src, gx, width, height, aperture, kernel ) ;
  filter_convolution_1d_y ( src, gy, width, height, aperture, kernel ) ;


  for ( i = 0 ; i < aperture ; i++ )
    for ( j = 0 ; j < aperture ; j++ ) {
      x = i - aperture_half, y = j - aperture_half ;
      kernel[j*aperture+i] = (float_type)(exp(-(x*x+y*y)/(2*s*s))*x*y/(2*3.14159265358*s*s*s*s*s*s)) ;
    }

  filter_convolution_2d ( src, gxy, width, height, aperture, kernel ) ;

  for ( i = 0 ; i < total ; i++ )
    det[i] = gx[i]*gx[i]*gy[i]*gy[i] - gxy[i]*gxy[i]*gxy[i]*gxy[i] - kappa * hypot(gx[i]*gx[i],gy[i]*gy[i]) ;

  for ( i = 0 ; i < width ; i++ ) {
    for ( j = 0 ; j < height ; j++ ) {
      dst[j*width+i] = 0 ;

      if ( det[j*width+i] < 8200500 ) //128 )
        continue ;

      float_type d = det[j*width+i] ;

      if ( d <= det[(j-1)*width+(i-1)] ||
           d <= det[(j-1)*width+(i-0)] ||
           d <= det[(j-1)*width+(i+1)] ||
           d <= det[(j-0)*width+(i-1)] ||
           d <= det[(j-0)*width+(i+1)] ||
           d <= det[(j+1)*width+(i-1)] ||
           d <= det[(j+1)*width+(i-0)] ||
           d <= det[(j+1)*width+(i+1)] )
        continue ;


      dst[j*width+i] = 255 ;

    }
  }

  return true ;
}
*/

}

