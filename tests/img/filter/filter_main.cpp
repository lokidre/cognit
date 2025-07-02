/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#include <filter_window.h>
#include <filter_toolbox.h>
#include <filter.h>


#include <apl/app.h>
#include <apl/cmdline.h>
#include <apl/oswin.h>
#include <apl/ui.h>


class tFilterApplication : public tApplication {
  private :
    tFilterWindow FilterWindow ;
    tUI ui ;
    tCommandLine CmdLine ;

  public :
    bool init ( void ) ;
} ;



t_filter_config<filter_float_type> filter_config ;
t_filter_handler<filter_float_type> filter_data[100] ;
t_filter<filter_float_type> filter ;


tFilterApplication FilterApplication ;

int main ( void )
{
  //CmdLine.Process() ;

  //if ( !FilterWindow.Create() )
  //  return 1 ;

  //if ( CmdLine.nArg )
  //  FilterWindow.LoadFile ( CmdLine.Arg[0].string ) ;

  if ( !FilterApplication.init() )
    return 1 ;

  return FilterApplication.exec() ;
}


bool tFilterApplication::init ( void )
{
  #include <filter.ccs>

  if ( !ui.LoadqT(_ccs_filter,&FilterWindow) )
    return false ;

  //FilterWindow.Center() ;
  FilterWindow.Move(10, 40) ;
  FilterWindow.Create(NULL) ;

  return true ;
}

