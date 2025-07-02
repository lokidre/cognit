/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#ifndef __GENIMG_H
#define __GENIMG_H

#include <def.h>
#include <memory.h>
#include <geo/gvector.h>

#include <filter/gaussian.h>
#include <filter/convolution.h>
#include <filter/normalize.h>
#include <filter/laplacian.h>


typedef double genimg_float_type ;

template <typename float_type>
struct t_genimg_config {
  enum t_genimg_type {
    genimg_corner,
    genimg_chessboard,
  } type ;


  // corner configuration
  float_type corner_angle ;
  float_type corner_orient ;

  // chessboard configuration
  int chess_dimx, chess_dimy ;  // dimensions
  float_type chess_orient ;
  int chess_cell_sizex, chess_cell_sizey ;


  // gaussian smoothing filter data
  bool do_gaussian ;
  int gaussian_aperture ;
  float_type gaussian_sigma ;

  // laplacian of gaussian charpening filter data
  bool do_laplacian ;
  int laplacian_aperture ;
  float_type laplacian_sigma ;

  t_genimg_config ( void )
  {
    type = genimg_chessboard ; //genimg_corner ;

    corner_angle = float_type(90) ;
    corner_orient = float_type(45) ;

    chess_dimx = 9, chess_dimy = 7 ;
    chess_orient = float_type(0) ;
    chess_cell_sizex = chess_cell_sizey = 32 ;

    do_gaussian = 1 ;
    gaussian_aperture = 15 ;
    gaussian_sigma = float_type(1) ;

    do_laplacian = 0 ;
    laplacian_aperture = 5 ;
    laplacian_sigma = float_type(1) ;
  }

} ;

template <typename float_type>
class t_genimg {
  public :
    void (* notification_routine)(t_genimg *genimg) ;
    int flags ;

    int width, height, total ;
    byte *image, *data ;
    float_type *float_image ;

    bool image_ready ;

  public :
    t_genimg ( void )
    {
      notification_routine = NULL ;
      flags = 0 ;
      width = height = 0 ;
      image = data = 0 ;
      float_image = 0 ;

      image_ready = false ;
    }

    bool generate ( t_genimg_config<float_type> *genimg_config )
    {
      if ( image_ready )
        free(image), image = 0, image_ready = false ;

      switch ( genimg_config->type ) {
        case genimg_config->t_genimg_type::genimg_corner :
          if ( !generate_corner(genimg_config) )
            return false ;
          break ;
        case genimg_config->t_genimg_type::genimg_chessboard :
          if ( !generate_chessboard(genimg_config) )
            return false ;
          break ;
        default :
          return false ;
      }

      // blur with gaussian
      if ( genimg_config->do_gaussian ) {
        int aperture = genimg_config->gaussian_aperture ;
        float_type *gaussian_image = (float_type *)malloc(total*sizeof(float_type) ) ;
        float_type *gaussian_kernel = (float_type *)malloc(aperture*aperture*sizeof(float_type)) ;

        filter_kernel_Gxy ( gaussian_kernel, aperture, genimg_config->gaussian_sigma ) ;
        filter_convolution_2d ( float_image, gaussian_image, width, height, aperture, gaussian_kernel ) ;
        memcpy ( float_image, gaussian_image, total*sizeof(float_type) ) ;


        free(gaussian_kernel) ;
        free(gaussian_image) ;
      }

      // sharpen with laplacian of gaussian
      if ( genimg_config->do_laplacian ) {
        int aperture = genimg_config->laplacian_aperture ;
        float_type *log_image = (float_type *)malloc(total*sizeof(float_type)) ;
        float_type *log_kernel = (float_type *)malloc(aperture*aperture*sizeof(float_type)) ;

        filter_kernel_LoGxy ( log_kernel, aperture, genimg_config->laplacian_sigma ) ;
        filter_convolution_2d ( float_image, log_image, width, height, aperture, log_kernel ) ;
        filter_threshold ( log_image, total, float_type(-50), float_type(50) ) ;
        filter_subtract ( float_image, log_image, total ) ;

        free(log_kernel) ;
        free(log_image) ;
      }

      // add noise

      //
      // cleanup, normalize
      //
      filter_clean_border ( float_image, width, height, 2*genimg_config->gaussian_aperture ) ;
      filter_normalize ( float_image, image, total, float_type(0), float_type(255) ) ;

      free(float_image) ;

      return true ;
    }

    bool generate_corner ( t_genimg_config<float_type> *genimg_config )
    {
      // for corner generate small, 256x256 image
      width = height = 300 ;
      total = width*height ;

      // allocate memory
      image = (byte *)malloc(total) ;
      float_image = (float_type *)malloc(total*sizeof(float_type)) ;

      if ( !image || !float_image )
        return false ;

      {
        // generate two vectors
        tVector3D<float_type> x, a, b, v, w ;

        x.x = 1, x.y = 0, x.z = 0 ;
        VctRotZ ( x, -((genimg_config->corner_orient)-genimg_config->corner_angle/2)*PI/180, a ) ;
        VctRotZ ( x, -((genimg_config->corner_orient)+genimg_config->corner_angle/2)*PI/180, b ) ;

        // generate an ideal corner
        float_type *pi = float_image ;
        for ( int j = 0 ; j < height ; j++ ) {
          for ( int i = 0 ; i < width ; i++ ) {
            v.x = i-width/2 + float_type(0.5) ;
            v.y = /*height-1-*/(j-height/2) + float_type(0.5) ;
            v.z = 0 ;


            VctCross ( v, a, x ) ;
            VctCross ( v, b, w ) ;

            if ( x.z < 0 && w.z > 0 )
              if ( v.x*v.x+v.y*v.y > width*width/16 )
                *pi = 255 ;
              else
                *pi = 0 ;
            else
              *pi = 255 ;

            pi++ ;
          }
        }
      }

      image_ready = true ;

      return true ;
    }

    bool generate_chessboard ( t_genimg_config<float_type> *genimg_config )
    {
      // local vars for easier access
      int dimx = genimg_config->chess_dimx, dimy = genimg_config->chess_dimy ;
      int sizex = genimg_config->chess_cell_sizex, sizey = genimg_config->chess_cell_sizey ;
      float_type gamma = genimg_config->chess_orient*PI/180 ;

      // calculate the size of image
      width = dimx*sizex*2 ;
      height = dimy*sizey*2 ;
      total = width*height ;


      // allocate mem
      image = (byte *)malloc(total) ;
      float_image = (float_type *)malloc(total*sizeof(float_type)) ;

      if ( !image || !float_image )
        return false ;

      // easiest to make first integer image and then rotate it
      memset ( image, 255, total ) ;

      {
        int sx=(width - sizex*dimx)/2, sy=(height - sizey*dimy)/2 ;

        for ( int jcell = 0 ; jcell < dimy ; jcell++ ) {
          for ( int icell = 0 ; icell < dimx ; icell++ ) {
            if ( (jcell&1)^(icell&1) )
              continue ;

            for ( int j = 0 ; j < sizey ; j++ ) {
              for ( int i = 0 ; i < sizex ; i++ ) {
                image[(j+jcell*sizey+sy)*width+(i+icell*sizex+sx)] = 0 ;
              }  // inside cell x
            }  // inside cell y
          }  // cells among x
        }  // cells among y
      }



      // now rotate the given image
      {
        int i, j, x, y ;

        // fillup with white color
        for ( i = 0 ; i < total ; i++ )
          float_image[i] = float_type(255) ;

        // do transform and rotation
        tVector2<float_type> t, u ;  // transform vector
        tMatrix2<float_type> r ;  // rotation matrix

        t.a[0] = width/2, t.a[1] = height/2 ;

        float_type sing = (float_type)sin(gamma), cosg = (float_type)cos(gamma) ;
        r.a[0][0] =  cosg, r.a[0][1] = sing ;
        r.a[1][0] = -sing, r.a[1][1] = cosg ;
        
        for ( j = 0 ; j < height ; j++ ) {
          for ( i = 0 ; i < width ; i++ ) {
            u.a[0] = float_type(0.5+i), u.a[1] = float_type(0.5+j) ;
            VctSub ( u, t ) ;
            MtxMul ( r, u ) ;
            VctAdd ( u, t ) ;

            x = int(u.a[0]), y = int(u.a[1]) ;

            if ( x < 0 || x >= width || y < 0 || y >= height ) {
              float_image[j*width+i] = float_type(255) ;
            } else {
              float_image[j*width+i] = float_type(image[y*width+x]) ;
            }
          }
        }
      }

      image_ready = true ;

      return true ;
    }
} ;



#endif

