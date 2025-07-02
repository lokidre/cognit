/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/

bool filter_handler_harris ( t_filter_handler<filter_float_type> *handler, t_filter<filter_float_type> *filter, t_filter_config<filter_float_type> *filter_config )
{
  int aperture = (int)handler->param[0].param_value ;
  filter_float_type sigma = (filter_float_type)handler->param[1].param_value ;
  filter_float_type kappa = (filter_float_type)handler->param[2].param_value ;
  byte *src = filter->src ;
  filter_float_type *dst = filter->flt_dst ;
  int width = filter->width, height = filter->height, total = filter->total ;
  filter_float_type *kernel = filter->fb[0] ;
  filter_float_type *data   = filter->fb[1] ;
  filter_float_type *gx     = filter->fb[2] ;
  filter_float_type *gy     = filter->fb[3] ;
  filter_float_type *gz     = filter->fb[4] ;
  filter_float_type *b1     = filter->fb[5] ;
  filter_float_type *b2     = filter->fb[6] ;
  filter_float_type *h      = filter->fb[7] ;
  //--------------

  filter_convert_buffer ( src, data, total ) ;


  filter_kernel_dGx ( kernel, aperture, sigma ) ;

  filter_convolution_1d_x ( data, b1, width, height, aperture, kernel ) ;
  filter_convolution_1d_y ( data, b2, width, height, aperture, kernel ) ;

  filter_gradient_x ( b1, width, height, gx ) ;
  filter_gradient_y ( b2, width, height, gy ) ;
  filter_dot ( gx, gx, total, gx ) ;
  filter_dot ( gy, gy, total, gy ) ;
  filter_dot ( gx, gy, total, gz ) ;

  filter_harris ( gx, gy, gz, kappa, total, h ) ;


  //filter_convert_buffer ( h, dst, total ) ;
  filter_normalize ( h, dst, total, filter_float_type(0), filter_float_type(255) ) ;

  return true ;
}

