/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#include <genimg_window.h>

#include <dialog.h>


bool tGenimgWindow::SaveFile ( char *FileName )
{
  Pic.SaveColor = CC_RGB24 ;

  if ( !Pic.SaveFile ( FileName, PICTURE_FORMAT_BMP ) )
    return false ;

  return true ;
}

bool tGenimgWindow::OnCreate ( tFrameCreateInfo Info )
{
  if ( !tFrameWindowCtl::OnCreate(Info) )
    return false ;

  GenimgToolbox.genimg_config = genimg_config ;
  GenimgToolbox.genimg = genimg ;
  GenimgToolbox.Parent = this ;
  GenimgToolbox.Style |= WS_CHILD ;

  if ( !GenimgToolbox.Create() )
    return false ;

  
  return true ;
}


void tGenimgWindow::OnCommand ( int Id )
{
  switch ( Id ) {
    case IDC_FILE_SAVE :
      if ( !genimg->image_ready )
        break ;
      {
        char FileName[256] ;

        tSaveAsDlg dlg ;

        dlg.FileName = FileName ;
        dlg.Directory = "." ;
        dlg.DefExt = "bmp" ;

        if ( dlg.DoModal ( NULL ) != DLG_OK )
          break ;

        if ( !SaveFile ( dlg.FileName ) )
          MessageBox ( "Cannot Save File" ) ;
      }
      break ;

    case IDC_FILE_EXIT :
      tFrameWindowCtl::Destroy() ;
      break ;

    case IDC_GENERATE :
      genimg->generate ( genimg_config ) ;
      Invalidate() ;
      break ;

    default :
      break ;
  }
}

void tGenimgWindow::OnPaint ( tVid *Vid )
{
  if ( genimg->image_ready ) {

    Pic.Width = genimg->width ;
    Pic.Height = genimg->height ;
    Pic.Planes = 1 ;
    Pic.Bits = 8 ;
    Pic.ImageColor = CC_GREY8 ;
    Pic.Data = genimg->image ;

    Pic.Repaint ( Vid ) ;

  }

}

