/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#include <genimg_toolbox.h>

struct {
  int ControlId ;
  t_genimg_config<genimg_float_type>::t_genimg_type Type ;
} GenimgTypeTable[] = {
  {  IDC_GENERATE_CORNER, t_genimg_config<genimg_float_type>::t_genimg_type::genimg_corner  },
  {  IDC_GENERATE_CHESSBOARD, t_genimg_config<genimg_float_type>::t_genimg_type::genimg_chessboard  },

  {  0, t_genimg_config<genimg_float_type>::t_genimg_type::genimg_corner }
} ;

bool tGenimgToolbox::OnInitDialog ( void )
{
  //
  // Move the toolbox to the right side
  //
  tRect ParentRect ;
  Parent->GetRect ( &ParentRect ) ;
  Move ( ParentRect.x+ParentRect.w, ParentRect.y ) ;


  //
  // Fill with initial data
  //

  // choose the operation type
  for ( int itype = 0 ; GenimgTypeTable[itype].ControlId ; itype++ )
    SetItemCheck ( GenimgTypeTable[itype].ControlId, GenimgTypeTable[itype].Type == genimg_config->type ? true : false ) ;

  // corner data
  SetItemFloat ( IDC_CORNER_ANGLE, genimg_config->corner_angle ) ;
  SetItemFloat ( IDC_CORNER_ORIENTATION, genimg_config->corner_orient ) ;

  // chessboard data
  SetItemInt   ( IDC_CHESSBOARD_DIMX, genimg_config->chess_dimx ) ;
  SetItemInt   ( IDC_CHESSBOARD_DIMY, genimg_config->chess_dimy ) ;
  SetItemFloat ( IDC_CHESSBOARD_ORIENT, genimg_config->chess_orient ) ;
  SetItemInt   ( IDC_CHESSBOARD_SIZEX, genimg_config->chess_cell_sizex ) ;
  SetItemInt   ( IDC_CHESSBOARD_SIZEY, genimg_config->chess_cell_sizey ) ;



  // gaussian filter data
  SetItemCheck ( IDC_GAUSSIAN_CHECK, genimg_config->do_gaussian ) ;
  SetItemInt   ( IDC_GAUSSIAN_APERTURE, genimg_config->gaussian_aperture ) ;
  SetItemFloat ( IDC_GAUSSIAN_SIGMA, genimg_config->gaussian_sigma ) ;

  // laplacian of gaussian filter data
  SetItemCheck ( IDC_LAPLACIAN_CHECK, genimg_config->do_laplacian ) ;
  SetItemInt ( IDC_LAPLACIAN_APERTURE, genimg_config->laplacian_aperture ) ;
  SetItemFloat ( IDC_LAPLACIAN_SIGMA, genimg_config->laplacian_sigma ) ;

  return true ;
}

void tGenimgToolbox::OnCommand ( int Id )
{
  switch ( Id ) {
    case IDC_GENERATE :

      // chose the generator type
      {
        bool checked ;

        GetItemCheck ( IDC_GENERATE_CORNER, &checked ) ;
        if ( checked )
          genimg_config->type = genimg_config->t_genimg_type::genimg_corner ;

        GetItemCheck ( IDC_GENERATE_CHESSBOARD, &checked ) ;
        if ( checked )
          genimg_config->type = genimg_config->t_genimg_type::genimg_chessboard ;
      }

      // corner
      GetItemFloat ( IDC_CORNER_ANGLE, &genimg_config->corner_angle ) ;
      GetItemFloat ( IDC_CORNER_ORIENTATION, &genimg_config->corner_orient ) ;

      // chessboard
      GetItemInt   ( IDC_CHESSBOARD_DIMX, &genimg_config->chess_dimx ) ;
      GetItemInt   ( IDC_CHESSBOARD_DIMY, &genimg_config->chess_dimy ) ;
      GetItemFloat ( IDC_CHESSBOARD_ORIENT, &genimg_config->chess_orient ) ;
      GetItemInt   ( IDC_CHESSBOARD_SIZEX, &genimg_config->chess_cell_sizex ) ;
      GetItemInt   ( IDC_CHESSBOARD_SIZEY, &genimg_config->chess_cell_sizey ) ;

      // gaussian
      GetItemCheck ( IDC_GAUSSIAN_CHECK, &genimg_config->do_gaussian ) ;
      GetItemInt ( IDC_GAUSSIAN_APERTURE, &genimg_config->gaussian_aperture ) ;
      GetItemFloat ( IDC_GAUSSIAN_SIGMA, &genimg_config->gaussian_sigma ) ;

      // laplacian of gaussian
      GetItemCheck ( IDC_LAPLACIAN_CHECK, &genimg_config->do_laplacian ) ;
      GetItemInt ( IDC_LAPLACIAN_APERTURE, &genimg_config->laplacian_aperture ) ;
      GetItemFloat ( IDC_LAPLACIAN_SIGMA, &genimg_config->laplacian_sigma ) ;

      SendMessage ( Parent->Handle, WM_COMMAND, IDC_GENERATE, 0 ) ;
      break ;
    default :
      break ;
  }
}

