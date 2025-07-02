/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#ifndef __GENIMG_TOOLBOX_H
#define __GENIMG_TOOLBOX_H

#include <ctl.h>
#include <resource.h>
#include <genimg.h>

class tGenimgToolbox : public tDialogCtl {
  public :
    t_genimg_config<genimg_float_type> *genimg_config ;
    t_genimg<genimg_float_type> *genimg ;

  public :
    tGenimgToolbox ( void )
    {
      Idd = IDD_GENIMG_TOOLBOX ;
    }

  public :
    bool OnInitDialog ( void ) ;
    void OnCommand ( int Id ) ;
    
} ;



#endif

