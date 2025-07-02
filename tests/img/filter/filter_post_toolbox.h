/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#ifndef __FILTER_POST_TOOLBOX_H
#define __FILTER_POST_TOOLBOX_H


#include <apl/ctl.h>
#include <apl/ui.h>


class tFilterPostToolbox : public tWindowCtl {

  private :
    tUI ui ;


  public :
    tCheckBoxCtl *AbsoluteCheck ;

    tCheckBoxCtl *ThresholdCheck ;
    tEditCtl *ThresholdMinEdit, *ThresholdMaxEdit ;

    tCheckBoxCtl *NonMaximaCheck, *NormOfGradientCheck ;

    tCheckBoxCtl *ZeroCrossingCheck ;

  public :
    tFilterPostToolbox ( void ) ;
    bool Create ( tWidget *ParentWidget ) ;
    
} ;




#endif
