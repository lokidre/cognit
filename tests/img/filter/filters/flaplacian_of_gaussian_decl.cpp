/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/

  // Laplacian of Gaussian
  fd->filter_name = "Laplacian of Gaussian LoG(x,y)" ;
  fd->param[0].param_name = "Aperture" ;
  fd->param[0].param_value = 11 ;
  fd->param[1].param_name = "Sigma" ;
  fd->param[1].param_value = 1 ;

  fd->filter_func = filter_handler_LoGxy ;

  fd->absolute = false ;
  fd->threshold = false ; //true ;
  fd->threshold_min = 0 ;
  fd->threshold_max = 20 ;
  fd->zero_crossing = true ;

  fd++ ;


  /*
  // LoG sharpening - subtract the image from LoG
  fd->filter_name = "LoG Sharpening" ;
  fd->param[0].param_name = "Aperture" ;
  fd->param[0].param_value = 7 ;
  fd->param[1].param_name = "Sigma" ;
  fd->param[1].param_value = 1 ;
  fd->param[2].param_name = "Threshold" ;
  fd->param[2].param_value = 20 ;
  fd++ ;

  // LoG edges (zero crossing of LoG)
  fd->filter_name = "LoG Edge Detection" ;
  fd->param[0].param_name = "Aperture" ;
  fd->param[0].param_value = 7 ;
  fd->param[1].param_name = "Sigma" ;
  fd->param[1].param_value = 1 ;
  */
