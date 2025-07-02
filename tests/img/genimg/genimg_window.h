/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#ifndef __FILTER_WINDOW_H
#define __FILTER_WINDOW_H

#include <ctl.h>
#include <pic.h>
#include <mm.h>

#include <resource.h>
#include <genimg.h>

#include <genimg_toolbox.h>


class tGenimgWindow : public tFrameWindowCtl {
  public :
    t_genimg_config<genimg_float_type> *genimg_config ;
    t_genimg<genimg_float_type> *genimg ;
    tGenimgToolbox GenimgToolbox ;

  public :
    tGenimgWindow ( void )
    {
      MenuId = IDR_MAIN_MENU ;
      FilteredImage = OriginalImage = NULL ;
    }

  public :
    bool SaveFile ( char *FileName ) ;

  public :
    bool OnCreate ( tFrameCreateInfo Info ) ;
    void OnCommand ( int Id ) ;
    void OnPaint ( tVid *Vid ) ;

  private :
    tPicture Pic ; //, FilteredPic ;
    tMM Mem ;
    bool ImageLoaded ;
    bool ImageFiltered ;
    byte *FilteredImage ;
    byte *OriginalImage ;
} ;



#endif
