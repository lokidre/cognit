/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/

  // G(x,y) - convolution with gaussian
  fd->filter_name = "Gaussian G(x,y)" ;
  fd->param[0].param_name = "Aperture" ;
  fd->param[0].param_value = 11 ;
  fd->param[1].param_name = "Sigma" ;
  fd->param[1].param_value = 1 ;
  fd->filter_func = filter_handler_Gxy ;
  fd++ ;


  // dG(x,y) - first derivative
  fd->filter_name = "Gaussian dG(x,y)" ;
  fd->param[0].param_name = "Aperture" ;
  fd->param[0].param_value = 11 ;
  fd->param[1].param_name = "Sigma" ;
  fd->param[1].param_value = 1 ;
  fd->filter_func = filter_handler_dGxy ;

  fd->absolute = false ;
  fd->threshold = false ;
  fd->threshold_min = 0 ;
  fd->threshold_max = 20 ;

  fd->norm_of_gradient = true ;
  fd->non_maxima_suppression = true ;

  fd++ ;


  /*
  // G(x) - among the x axis
  fd->filter_name = "Gaussian G(x)" ;
  fd->param[0].param_name = "Aperture" ;
  fd->param[0].param_value = 11 ;
  fd->param[1].param_name = "Sigma" ;
  fd->param[1].param_value = 1 ;
  fd++ ;


  // G(x) - among the y axis
  fd->filter_name = "Gaussian G(y)" ;
  fd->param[0].param_name = "Aperture" ;
  fd->param[0].param_value = 11 ;
  fd->param[1].param_name = "Sigma" ;
  fd->param[1].param_value = 1 ;
  fd++ ;

  // G(x)G(y) - multiple of two gaussians
  fd->filter_name = "Gaussian G(x)G(y)" ;
  fd->param[0].param_name = "Aperture" ;
  fd->param[0].param_value = 11 ;
  fd->param[1].param_name = "Sigma" ;
  fd->param[1].param_value = 1 ;
  fd++ ;
  */


  // dG(x) - first derivative
  fd->filter_name = "Gaussian dG(x)" ;
  fd->param[0].param_name = "Aperture" ;
  fd->param[0].param_value = 11 ;
  fd->param[1].param_name = "Sigma" ;
  fd->param[1].param_value = 1 ;
  fd->filter_func = filter_handler_dGx ;
  fd++ ;

  // dG(y) - first derivative
  fd->filter_name = "Gaussian dG(y)" ;
  fd->param[0].param_name = "Aperture" ;
  fd->param[0].param_value = 11 ;
  fd->param[1].param_name = "Sigma" ;
  fd->param[1].param_value = 1 ;
  fd->filter_func = filter_handler_dGy ;
  fd++ ;


  /*
  // d2G(x,y) - second derivative
  fd->filter_name = "Gaussian d2G(x,y)" ;
  fd->param[0].param_name = "Aperture" ;
  fd->param[0].param_value = 11 ;
  fd->param[1].param_name = "Sigma" ;
  fd->param[1].param_value = 1 ;
  fd++ ;

  */
