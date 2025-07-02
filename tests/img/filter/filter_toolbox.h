/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#ifndef __FILTER_TOOLBOX_H
#define __FILTER_TOOLBOX_H

#include <filter_post_toolbox.h>

#include <apl/ctl.h>
#include <apl/ui.h>


#include <filter.h>

#define MAX_FILTER_PARAMS   4

class tFilterToolbox : public tWindowCtl {
  private :
    tFilterPostToolbox FilterPostToolbox ;


  private :
    tUI ui ;

    tComboBoxCtl *FilterListCtl ;
    int CurrentFilter ;

    tLabelCtl *ParamNameCtl[MAX_FILTER_PARAMS] ;
    tEditCtl *ParamValueCtl[MAX_FILTER_PARAMS] ;
    tEditCtl *PassesCtl ;

    void UpdateCurrentFilterControls ( void ) ;
    void ReadCurrentFilterControls ( void ) ;

  public :
    tFilterToolbox ( void ) ;
    bool Create ( tWidget *ParentWidget ) ;

  private :  // slots
    signal_slot_decl(tFilterToolbox,SlotFilterSelect) ;
    signal_slot_decl(tFilterToolbox,SlotProcess) ;
    signal_slot_decl(tFilterToolbox,SlotSetOrigin) ;
    signal_slot_decl(tFilterToolbox,SlotOrigin) ;
    
} ;



#endif

