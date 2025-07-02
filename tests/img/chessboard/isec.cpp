/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/

#include <pic.h>
#include <geo.h>

#include <filter_chessboard.h>

// types
typedef double float_type ;


// params
int magnitude = 16 ;
int aperture = 17 ;
float_type delta = 0.05 ;
float_type sigma = 1 ;
float_type kappa = 0.04 ;
float_type curly_kappa = 2.5 ;



int Width, Height ;


tPicture Pic, OutPic ;
tMM Mem ( MM_ERROR_VERBOSE ) ;

tDynamicArray<tPoint2D<float_type> > Corners ;


int main ( int argc, char *argv[] )
{
  if ( argc <= 1 ) {
    printf ( "param miss\n" ) ;
    return 1 ;
  }

  Pic.ImageColor = CC_RGB32 ;

  if ( !Pic.LoadFile ( argv[1] ) ) {
    printf ( "cannot load %s\n", argv[1] ) ;
    return 1 ;
  }

  Width = Pic.Width, Height = Pic.Height ;


  // �������� ���������
  {
    Corners.clear() ;


    byte *SourceImage = (byte *)Mem.Alloc ( Width * Height * sizeof(byte) ) ;
    float_type *buff1 = (float_type *)Mem.Alloc ( Width * Height * sizeof(float_type) ) ;
    float_type *buff2 = (float_type *)Mem.Alloc ( Width * Height * sizeof(float_type) ) ;
    float_type *buff3 = (float_type *)Mem.Alloc ( Width * Height * sizeof(float_type) ) ;
    float_type *buff4 = (float_type *)Mem.Alloc ( Width * Height * sizeof(float_type) ) ;
    float_type *buff5 = (float_type *)Mem.Alloc ( Width * Height * sizeof(float_type) ) ;
    float_type *buff6 = (float_type *)Mem.Alloc ( Width * Height * sizeof(float_type) ) ;
    float_type *buff7 = (float_type *)Mem.Alloc ( Width * Height * sizeof(float_type) ) ;
    float_type *buff8 = (float_type *)Mem.Alloc ( Width * Height * sizeof(float_type) ) ;
    float_type *buff9 = (float_type *)Mem.Alloc ( Width * Height * sizeof(float_type) ) ;

    Vid_ConvertImage ( Pic.ImageColor, CC_GREY, Pic.Data, SourceImage, Width, Height ) ;

    filter_find_isection_sub_pix<float_type,byte,tDynamicArray<tPoint2D<float_type> >,tPoint2D<float_type> > ( SourceImage, Corners, Width, Height, aperture, sigma, curly_kappa, kappa, delta, buff1, buff2, buff3, buff4, buff5, buff6, buff7, buff8, buff9 ) ;

  }


  // ��������� ������
  {
    byte *CornerImage = Mem.Alloc ( Width * Height * magnitude * magnitude * 4 ) ;
    
    {
      dword corner_color = 0x00FF00 ;
      int corner_col, corner_row ;
      for ( int i = 0 ; i < Corners.n ; i++ ) {
        corner_col = int(Corners.v[i].x) ;
        corner_row = int(Corners.v[i].y) ;

        ((dword *)Pic.Data)[corner_row*Width+corner_col] = corner_color ;
      }
    }


    for ( int j = 0 ; j < Height ; j++ )
      for ( int i = 0 ; i < Width ; i++ )
        for ( int k = 0 ; k < magnitude ; k++ )
          for ( int l = 0 ; l < magnitude ; l++ )
            ((dword *)CornerImage)[(j*magnitude+k)*Width*magnitude + i*magnitude+l] = ((dword *)Pic.Data)[j*Width+i] ;

    dword corner_color = 0xFF0000 ;
    int corner_col, corner_row ;
    for ( int i = 0 ; i < Corners.n ; i++ ) {
      corner_col = int(Corners.v[i].x * magnitude) ;
      corner_row = int(Corners.v[i].y * magnitude) ;

      ((dword *)CornerImage)[corner_row*Width*magnitude+corner_col] = corner_color ;

      for ( int j = -10 ; j < 10 ; j++ ) {
        ((dword *)CornerImage)[(corner_row+j)*Width*magnitude+corner_col+j] = corner_color ;
        ((dword *)CornerImage)[(corner_row-j)*Width*magnitude+corner_col+j] = corner_color ;
      }
    }


    OutPic.Width = Width * magnitude ;
    OutPic.Height = Height * magnitude ;
    OutPic.SaveColor = OutPic.ImageColor = CC_RGB32 ;
    OutPic.Data = CornerImage ;

    OutPic.SaveFile ( "corners.bmp", PICTURE_FORMAT_BMP ) ;
  }



  return 0 ;
}

