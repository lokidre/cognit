/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include <apl/ctl.h>
#include <apl/pic.h>
#include <apl/mm.h>

#include <filter.h>

#include <filter_toolbox.h>
#include <filter_post_toolbox.h>


class tFilterWindow : public tApplicationWindowCtl {
  public :
    tFilterToolbox FilterToolbox ;

  public :
    bool LoadFile ( std::string &FileName ) ;

  public :
    bool Create ( tWidget *ParentWidget ) ;
    bool OnCreate ( void ) ;
    void OnPaint ( tVid *Vid ) ;

  private :
    tPicture Pic ; //, FilteredPic ;
    tMM Mem ;
    bool ImageLoaded ;
    bool ImageFiltered ;
    byte *FilteredImage ;
    byte *OriginalImage ;

  private :  // Slots
    signal_slot_decl(tFilterWindow,SlotFileOpen) ;
    signal_slot_decl(tFilterWindow,SlotProcessFilter) ;
    signal_slot_decl(tFilterWindow,SlotOrigin) ;
    signal_slot_decl(tFilterWindow,SlotSetOrigin) ;
} ;


