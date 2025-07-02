/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/


// Laplacian of Gaussian
bool filter_handler_LoGxy ( t_filter_handler<filter_float_type> *handler, t_filter<filter_float_type> *filter, t_filter_config<filter_float_type> *filter_config )
{
  int aperture = (int)handler->param[0].param_value ;
  filter_float_type sigma = (filter_float_type)handler->param[1].param_value ;
  byte *src = filter->src ;
  filter_float_type *dst = filter->flt_dst ;
  int width = filter->width, height = filter->height, total = filter->total ;
  filter_float_type *kernel = filter->fb[0] ;
  filter_float_type *b1 = filter->fb[1] ;
  filter_float_type *b2 = filter->fb[2] ;
  //--------------

  filter_kernel_LoGxy ( kernel, aperture, sigma ) ;
  filter_convert_buffer ( src, b1, total ) ;
  filter_convolution_2d ( b1, dst, width, height, aperture, kernel ) ;

  return true ;
}


/*
// gaussian family
bool filter_handler_dGxy ( t_filter_handler<filter_float_type> *handler, t_filter<filter_float_type> *filter, t_filter_config<filter_float_type> *filter_config )
{
  int aperture = (int)handler->param[0].param_value ;
  filter_float_type sigma = (filter_float_type)handler->param[1].param_value ;
  byte *src = filter->src ;
  filter_float_type *dst = filter->flt_dst ;
  int width = filter->width, height = filter->height, total = filter->total ;
  filter_float_type *kernel = filter->fb[0] ;
  filter_float_type *b1 = filter->fb[1] ;
  filter_float_type *b2 = filter->fb[2] ;
  //--------------

  filter_kernel_dGxy ( kernel, aperture, sigma ) ;
  filter_convert_buffer ( src, b1, total ) ;
  filter_convolution_2d ( b1, dst, width, height, aperture, kernel ) ;

  return true ;
}

*/

