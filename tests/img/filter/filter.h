/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#ifndef __FILTER_H
#define __FILTER_H

#include <apl/def.h>
#include <mat/mat.h>


#include <filter/normalize.h>
#include <filter/gradient.h>
#include <filter/maxima.h>
#include <filter/threshold.h>
#include <filter/zero_crossing.h>



typedef double filter_float_type ;

#define MAX_FILTER_PARAMS 4

template <typename float_type>
struct t_filter_config {

  int passes ;
  int current_filter ;

  t_filter_config ( void )
  {
    current_filter = 0 ;
    passes = 1 ;
  }

} ;


template <typename float_type>
struct t_filter_parameter {
  char *param_name ;
  float_type param_value ;
} ;


template <typename float_type>
class t_filter ;

template <typename float_type>
struct t_filter_handler {
  char *filter_name ;
  t_filter_parameter<float_type> param[MAX_FILTER_PARAMS] ;

  // post process configuration
  bool absolute ;

  bool threshold ;
  float_type threshold_min, threshold_max ;

  bool norm_of_gradient ;
  bool non_maxima_suppression ;
  bool zero_crossing ;

  bool (*filter_func)( t_filter_handler<float_type> *handler, t_filter<float_type> *filter, t_filter_config<float_type> *config ) ;
} ;



template <typename float_type>
class t_filter {
  public :
    void (* notification_routine)(t_filter *filter) ;
    int flags ;

    int width, height, total ;
    byte *image, *data ;


  public :  // buffers
    #define MAX_FILTER_BUFFERS 10
    float_type *fb[MAX_FILTER_BUFFERS] ;  // fp buffer
    byte *ib[4] ;  // image buffers

    byte *src, *dst2 ;
    float_type *flt_dst ;



  public :  // initialization
    t_filter ( void ) ;

  public :  // processing

    void post_process ( t_filter_config<float_type> *filter_config )
    {
      t_filter_handler<float_type> *pfh = &filter_data[filter_config->current_filter] ;

      total = width*height ;

      // absolute value
      if ( pfh->absolute ) {
        float_type *f = flt_dst ;
        for ( int i = 0 ; i < total ; i++, f++ )
          *f = m_abs(*f) ; //*100 ;
      }

      if ( pfh->norm_of_gradient ) {
        filter_gradient_x_2 ( flt_dst, fb[0], width, height ) ;
        filter_gradient_y_2 ( flt_dst, fb[1], width, height ) ;
        filter_norm_of_gradient ( fb[0], fb[1], flt_dst, total ) ;
      }

      if ( pfh->non_maxima_suppression ) {
        memcpy ( fb[0], flt_dst, total*sizeof(float_type) ) ;
        suppress_non_maxima ( fb[0], flt_dst, width, height ) ;
      }

      if ( pfh->zero_crossing ) {
        // needed temp
        memcpy ( fb[0], flt_dst, total*sizeof(float_type) ) ;
        filter_zero_crossing ( fb[0], flt_dst, width, height ) ;
      }

      // thresholding
      if ( pfh->threshold ) {
        filter_threshold ( flt_dst, total, pfh->threshold_min, pfh->threshold_max ) ;
      }

      // normalize
      filter_normalize ( flt_dst, flt_dst, total, float_type(0), float_type(255) ) ;
      filter_convert_buffer ( flt_dst, dst2, total ) ;
    }


    bool process ( t_filter_config<float_type> *filter_config )
    {
      total = width * height ;
      int i ;

      // integer buffers
      for ( i = 0 ; i < 4 ; i++ )
        ib[i] = (byte *)malloc ( total*4 ) ;

      // buffers
      for ( i = 0 ; i < MAX_FILTER_BUFFERS ; i++ )
        fb[i] = (float_type *)malloc ( total * sizeof(float_type) ) ;


      src = image, dst2 = data ;

      flt_dst = (float_type *)malloc ( total*sizeof(float_type) ) ;

      memset ( flt_dst, 0, total*sizeof(float_type) ) ;


      for ( int pass = 0 ; pass < filter_config->passes ; pass++ ) {
        t_filter_handler<float_type> *pfh = &filter_data[filter_config->current_filter] ;
        if ( pfh->filter_func == NULL || !pfh->filter_func(pfh,this,filter_config) )
          return false ;
      }


      post_process(filter_config) ;


      for ( i = MAX_FILTER_BUFFERS - 1 ; i >= 0 ; i-- )
        free(fb[i]) ;

      for ( i = 3 ; i >= 0 ; i-- )
        free(ib[i]) ;

      free(flt_dst) ;

      return true ;
    }

} ;



#endif

