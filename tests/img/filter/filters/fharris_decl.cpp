/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/


  // G(x,y) - convolution with gaussian
  fd->filter_name = "Harris Corner Detector" ;
  fd->param[0].param_name = "Aperture" ;
  fd->param[0].param_value = 11 ;
  fd->param[1].param_name = "Sigma" ;
  fd->param[1].param_value = 1 ;
  fd->param[2].param_name = "Kappa" ;
  fd->param[2].param_value = 0.04 ;
  fd->filter_func = filter_handler_harris ;
  fd++ ;

