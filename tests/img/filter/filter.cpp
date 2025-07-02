/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#include <filter.h>

#include <filter/median.h>
#include <filter/mean.h>
#include <filter/gaussian.h>
#include <filter/conservative.h>
#include <filter/crimmins.h>
#include <filter/laplacian.h>
#include <filter/chessboard.h>

#include <filter/corner_beaudet.h>
#include <filter/corner_harris.h>

#include <memory.h>



// structure that contains information about all supported filters
extern t_filter_handler<filter_float_type>
filter_data[100] ;


// supported filters

// median filter
bool filter_handler_median ( t_filter_handler<filter_float_type> *handler, t_filter<filter_float_type> *filter, t_filter_config<filter_float_type> *filter_config )
{
  int aperture = (int)handler->param[0].param_value ;
  byte *src = filter->src ;
  filter_float_type *dst = filter->flt_dst ;
  int width = filter->width, height = filter->height, total = filter->total ;
  //--------------

  if ( aperture == 3 )
    filter_median_3x3 ( src, dst, width, height ) ;
  else
    filter_median_nxn ( src, dst, width, height, aperture, filter->fb[0] ) ;

  filter_clean_border ( dst, width, height, aperture/2+1) ;

  return true ;
}

// mean filter
bool filter_handler_mean ( t_filter_handler<filter_float_type> *handler, t_filter<filter_float_type> *filter, t_filter_config<filter_float_type> *filter_config )
{
  int aperture = (int)handler->param[0].param_value ;
  byte *src = filter->src ;
  filter_float_type *dst = filter->flt_dst ;
  int width = filter->width, height = filter->height, total = filter->total ;
  //---------


  if ( aperture == 3 )
    filter_mean_3x3 ( src, dst, width, height ) ;
  else 
    filter_mean_nxn ( src, dst, width, height, aperture ) ;

  filter_clean_border ( dst, width, height, aperture/2+1) ;

  return true ;
}

// crimmins
bool filter_handler_crimmins ( t_filter_handler<filter_float_type> *handler, t_filter<filter_float_type> *filter, t_filter_config<filter_float_type> *filter_config )
{
  int aperture = (int)handler->param[0].param_value ;
  byte *src = filter->src ;
  filter_float_type *dst = filter->flt_dst ;
  int width = filter->width, height = filter->height, total = filter->total ;
  //---------

  memcpy ( filter->ib[0], src, total ) ;
  filter_crimmins ( filter->ib[0], width, height ) ;
  filter_convert_buffer ( filter->ib[0], dst, total ) ;

  return true ;
}


#include <filters/fgaussian.cpp> // gaussian family
#include <filters/flaplacian_of_gaussian.cpp>  // LoG family
#include <filters/fharris.cpp>  // harris corner detector operator




//
// initialization
//
t_filter<filter_float_type>::t_filter ( void )
{
  notification_routine = NULL ;
  flags = 0 ;
  width = height = 0 ;
  image = data = 0 ;


  // fill up with supported filters
  t_filter_handler<filter_float_type> *fd = filter_data ;

  // Median Filter
  fd->filter_name = "Median" ;
  fd->param[0].param_name = "Aperture" ;
  fd->param[0].param_value = 3 ;
  fd->filter_func = filter_handler_median ;
  fd++ ;

  // Median Filter
  fd->filter_name = "Mean" ;
  fd->param[0].param_name = "Aperture" ;
  fd->param[0].param_value = 3 ;
  fd->filter_func = filter_handler_mean ;
  fd++ ;

  // Crimmins filter
  fd->filter_name = "Crimmins" ;
  fd->filter_func = filter_handler_crimmins ;
  fd++ ;




  #include <filters/fgaussian_decl.cpp>  // Gaussian family
  #include <filters/flaplacian_of_gaussian_decl.cpp>  // Laplacian of Gaussian family
  #include <filters/fharris_decl.cpp>  // Harris corner detector

  // the last one

  fd->filter_name = NULL ;
}


