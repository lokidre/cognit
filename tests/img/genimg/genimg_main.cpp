/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#include <genimg_window.h>
#include <genimg_toolbox.h>
#include <genimg.h>


#include <cmdline.h>
#include <oswin.h>


tGenimgWindow GenimgWindow ;
t_genimg_config<genimg_float_type> genimg_config ;
t_genimg<genimg_float_type> genimg ;

int main ( void )
{
  GenimgWindow.genimg_config = &genimg_config ;
  GenimgWindow.genimg = &genimg ;

  GenimgWindow.Rect.x = 40 ;
  GenimgWindow.Rect.y = 40 ;
  GenimgWindow.Rect.w = 512 ;
  GenimgWindow.Rect.h = 512 ;

  if ( !GenimgWindow.Create() )
    return 1 ;

  GenimgWindow.Show(), GenimgWindow.Update() ;

  WinDispatchRoutine() ;

  return 0 ;
}

