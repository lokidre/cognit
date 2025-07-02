/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#include <filter_window.h>

#include <apl/dialog.h>

extern t_filter_config<filter_float_type> filter_config ;
extern t_filter_handler<filter_float_type> filter_data[100] ;
extern t_filter<filter_float_type> filter ;


bool tFilterWindow::Create ( tWidget *ParentWidget )
{
  // menu
  {
    SetMenu(new tMenuCtl) ;

    {
      tPopupMenuCtl *p = new tPopupMenuCtl ;
      p->InsertItem ( "&Open", this, SIGNAL_SLOT2(SlotFileOpen) ) ;
      p->InsertSeparator() ;
      p->InsertItem ( "E&xit", this, SIGNAL_SLOT(SlotDestroy) ) ;
      GetMenu()->InsertItem ( "&File", p ) ;
    }
  }

  // signals
  {
    SignalConnect ( NULL, "filter_process", this, SIGNAL_SLOT2(SlotProcessFilter) ) ;
    SignalConnect ( NULL, "filter_origin", this, SIGNAL_SLOT2(SlotOrigin) ) ;
    SignalConnect ( NULL, "filter_set_origin", this, SIGNAL_SLOT2(SlotSetOrigin) ) ;
  }


  SetVisible(false) ;

  if ( !tWindowCtl::Create(ParentWidget) )
    return false ;

  // toolbars
  {
    tRect r ;
    GetRect ( &r ) ;

    FilterToolbox.Move ( r.x+r.w, r.y ) ;
    FilterToolbox.Create(this) ;
  }

  SetVisible() ;

  return true ;
}

bool tFilterWindow::OnCreate ( void )
{
  if ( !tWindowCtl::OnCreate() )
    return false ;


  return true ;
}

void tFilterWindow::OnPaint ( tVid *Vid )
{
  if ( !ImageLoaded )
    return ;

  if ( ImageFiltered ) {
    Pic.Data = FilteredImage ;
    Pic.Repaint ( Vid ) ;
    Pic.Data = OriginalImage ;
  } else
    Pic.Repaint ( Vid ) ;
}




bool tFilterWindow::LoadFile ( std::string &FileName )
{
  Pic.ImageColor = CC_GREY ;

  if ( !Pic.LoadFile ( FileName.c_str() ) )
    return false ;

  ImageLoaded = true ;
  OriginalImage = Pic.Data ;
  FilteredImage = Mem.Free ( FilteredImage ) ;
  FilteredImage = Mem.Alloc ( Pic.Width * Pic.Height * 4 ) ;

  ImageFiltered = false ;

  if ( filter.data )
    Mem.Free ( filter.data ) ;


  Invalidate() ;

  return true ;
}

void tFilterWindow::SlotFileOpen ( void )
{
  tOpenFileDlg dlg ;

  dlg.Directory = "/srcdat" ;

  if ( dlg.Modal(this) != DLG_OK )
    return ;

  if ( !LoadFile ( dlg.FileName ) )
    MessageBox ( "Cannot load file" ) ;
}


void tFilterWindow::SlotProcessFilter ( void )
{
  if ( !ImageLoaded )
    return ;

  filter.width = Pic.Width ;
  filter.height = Pic.Height ;
  filter.image = OriginalImage ;
  filter.data = FilteredImage ;
  filter.process ( &filter_config ) ;

  ImageFiltered = true ;

  Invalidate() ;
}


void tFilterWindow::SlotOrigin ( void )
{
  ImageFiltered = false ;
  Invalidate() ;
}

void tFilterWindow::SlotSetOrigin ( void )
{
  //ImageFiltered = false ;
  Invalidate() ;
}

