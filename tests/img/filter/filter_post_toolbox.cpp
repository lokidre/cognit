/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#include <filter_post_toolbox.h>

tFilterPostToolbox::tFilterPostToolbox ( void )
{
  #include <post_filter_toolbox.ccs>

  ui.LoadqT(_ccs_post_filter_toolbox,this) ;

  try {
    AbsoluteCheck = ((tCheckBoxCtl *)ui.GetWidget("AbsoluteCheck")) ;
    ThresholdCheck = ((tCheckBoxCtl *)ui.GetWidget("ThresholdCheck")) ;
    ThresholdMinEdit = ((tEditCtl *)ui.GetWidget("ThresholdMinEdit")) ;
    ThresholdMaxEdit = ((tEditCtl *)ui.GetWidget("ThresholdMaxEdit")) ;

    NormOfGradientCheck = ((tCheckBoxCtl *)ui.GetWidget("NormOfGradientCheck")) ;
    NonMaximaCheck = ((tCheckBoxCtl *)ui.GetWidget("NonMaximaCheck")) ;
    ZeroCrossingCheck = ((tCheckBoxCtl *)ui.GetWidget("ZeroCrossingCheck")) ;
  }
  catch(...) {
    InternalError() ;
  }
}

bool tFilterPostToolbox::Create ( tWidget *ParentWidget )
{
  ExStyle |= WS_EX_TOOLWINDOW ;

  if ( !tWindowCtl::Create(ParentWidget) )
    return false ;


  return true ;
}
