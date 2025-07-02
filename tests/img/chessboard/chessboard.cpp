/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/

#include <pic.h>

#include <approx.h>
#include <geo.h>

#include <filter_chessboard.h>
#include <chessboard.h>

// types
typedef double float_type ;


// params
int magnitude = 8 ;
int aperture = 21 ;
float_type delta = 0.2 ;
float_type sigma = 1 ;
float_type kappa = 0.04 ;
float_type curly_kappa = 2.5 ;

int chw = 9 ;
int chh = 7 ;


int Width, Height ;


tPicture Pic, OutPic ;
tMM Mem ( MM_ERROR_VERBOSE ) ;

tDynamicArray<tPoint2D<float_type> > Corners ;
tPoint2D<float_type> *ChCorners ;

tPoint2D<float_type> pts_v_buff[100], pts_h_buff[100] ;









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


  // ���� �����
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

  {  // �� �����������- ���������
    if ( Corners.n < chw * chh ) {
      printf ( "board not found\n" ) ;
      return 1 ;
    }
      
    // ������ ��� � �����������
    ChCorners = (tPoint2D<float_type> *)Mem.Alloc ( chw * chh * sizeof(tPoint2D<float_type>) ) ;
    tPoint2D<float_type> *ChBuffer = (tPoint2D<float_type> *)Mem.Alloc ( chw * chh * sizeof(tPoint2D<float_type>) ) ;
    tPoint2D<float_type> *ChCorners2 = (tPoint2D<float_type> *)Mem.Alloc ( chw * chh * sizeof(tPoint2D<float_type>) ) ;

    // needed swap chw, chh
    float_type err, err2 ;
    err = MatchChBoard ( Corners.v, Corners.n, chw, chh, ChCorners, ChBuffer ) ;
    if ( chw != chh )
      err2 = MatchChBoard ( Corners.v, Corners.n, chw, chh, ChCorners2, ChBuffer ) ;

    if ( err2 < err )
      memcpy ( ChCorners, ChCorners2, chw*chh*sizeof(tPoint2D<float_type>) ) ;

    printf ( "ch error: %lf\n", err ) ;

    //if ( chw != chh )
    //if ( ! ) {
    //  printf ( "cannot match\n" ) ;
    //  return 1 ;
    //}


    //
    // ���� ���4 ��� �� 
    //    1. �������� � �� ����
    //    2. � ������� ���� ����� ���
    //

    // for 

    //int ncand = chw*chh ;

    //tPoint2D<float_type> MinPoint, MaxPoint ;

    {
      //MinPoint = MaxPoint = Corners.v[0] ;
      //for ( int i = 1 ; i < Corners.n ; i++ ) {
        //if ( Corners.v[i].x < MinPoint.x )
        //  MinPoint.x
      //}
    }
    // 
    //int 


    //for ( int i = 0 ; i < chw ; i++ )
    //  for ( int j = 0 ; j < chh ; j++ )

  }


  // ���� ���
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


    // ������������
    {
      for ( int j = 0 ; j < Height ; j++ ) {
        for ( int i = 0 ; i < Width ; i++ ) {
          dword org_img = ((dword *)Pic.Data)[j*Width+i] ;
          for ( int k = 0 ; k < magnitude ; k++ ) {
            for ( int l = 0 ; l < magnitude ; l++ ) {
              ((dword *)CornerImage)[(j*magnitude+k)*Width*magnitude + i*magnitude+l] = org_img ;
            }
          }
        }
      }
    }

    // ��� ���� � �� ���
    {
      dword corner_color = 0xFF0000 ;
      int corner_col, corner_row ;
      for ( int i = 0 ; i < Corners.n ; i++ ) {
        corner_col = int(Corners.v[i].x * magnitude) ;
        corner_row = int(Corners.v[i].y * magnitude) ;

        ((dword *)CornerImage)[corner_row*Width*magnitude+corner_col] = corner_color ;

        for ( int j = -magnitude*2 ; j < magnitude*2 ; j++ ) {
          ((dword *)CornerImage)[(corner_row+j)*Width*magnitude+corner_col+j] = corner_color ;
          ((dword *)CornerImage)[(corner_row-j)*Width*magnitude+corner_col+j] = corner_color ;
        }
      }
    }


    // ��� ������ ���� ���
    {
      dword corner_color = 0x0000FF ;
      int corner_col, corner_row ;

      for ( int i = 0 ; i < chw*chh ; i++ ) {
        corner_col = int(ChCorners[i].x * magnitude) ;
        corner_row = int(ChCorners[i].y * magnitude) ;

        for ( int j = -magnitude*2 ; j < magnitude*2 ; j++ ) {
          ((dword *)CornerImage)[(corner_row+j)*Width*magnitude+corner_col+magnitude*2] = corner_color ;
          ((dword *)CornerImage)[(corner_row+j)*Width*magnitude+corner_col-magnitude*2] = corner_color ;

          ((dword *)CornerImage)[(corner_row+magnitude*2)*Width*magnitude+corner_col+j] = corner_color ;
          ((dword *)CornerImage)[(corner_row-magnitude*2)*Width*magnitude+corner_col-j] = corner_color ;
        }
      }
    }



    OutPic.Width = Width * magnitude ;
    OutPic.Height = Height * magnitude ;
    OutPic.SaveColor = OutPic.ImageColor = CC_RGB32 ;
    OutPic.Data = CornerImage ;

    OutPic.SaveFile ( "corners.bmp", PICTURE_FORMAT_BMP ) ;
  }

  {
    FILE *f = fopen ( "corners.pts", "wt+" ) ;

    if ( f ) {
      for ( int i = 0 ; i < Corners.n ; i++ ) {
        fprintf ( f, "%lf %lf %lf\n", Corners.v[i].x, Corners.v[i].y, 0 ) ;
      }

      fclose ( f ) ;
    }
  }



  return 0 ;
}

