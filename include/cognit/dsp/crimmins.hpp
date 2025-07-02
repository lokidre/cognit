/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once


namespace cognit {

template <class data_type>
void crimmins ( data_type *data, int width, int height )
{
	int i, j, k ;
	int ia, ja, ic, jc ;
	data_type *a, *b, *c ;

	int direction[4][4] = { { 0, -1, 0, 1 }, { -1, 0, 1, 0 }, { -1, -1, 1, 1 }, { -1, 1, 1, -1 } } ;


  // dark pixel adjustment
  for ( k = 0 ; k < 4 ; k++ ) {
    ia = direction[k][0], ja = direction[k][1], ic = direction[k][2], jc = direction[k][3] ;
    for ( j = 1 ; j < height - 1 ; j++ )
      for ( i = 1 ; i < width - 1 ; i++ ) {
        a = &data[(ja+j)*width+ia+i], c = &data[(jc+j)*width+ic+i], b = &data[j*width+i] ;

        // if a >= b + 2 then b++
        if ( *a >= *b + 2 )
          *b = *b + 1 ;
       }

    for ( j = 1 ; j < height - 1 ; j++ )
      for ( i = 1 ; i < width - 1 ; i++ ) {
        a = &data[(ja+j)*width+ia+i], c = &data[(jc+j)*width+ic+i], b = &data[j*width+i] ;

        // if a > b and b <= c then b++
        if ( *a > *b && *b <= *c )
          *b = *b + 1 ;
      }

    for ( j = 1 ; j < height - 1 ; j++ )
      for ( i = 1 ; i < width - 1 ; i++ ) {
        a = &data[(ja+j)*width+ia+i], c = &data[(jc+j)*width+ic+i], b = &data[j*width+i] ;

        // if c > b and b <= a then b++
        if ( *c > *b && *b <= *a )
          *b = *b + 1 ;
      }

    for ( j = 1 ; j < height - 1 ; j++ )
      for ( i = 1 ; i < width - 1 ; i++ ) {
        a = &data[(ja+j)*width+ia+i], c = &data[(jc+j)*width+ic+i], b = &data[j*width+i] ;

        // if a > b and b <= c then b++
        if ( *c >= *b + 2 )
          *b = *b + 1 ;
      }
  }


  // light pixel adjustment
  for ( k = 0 ; k < 4 ; k++ ) {
    ia = direction[k][0], ja = direction[k][1], ic = direction[k][2], jc = direction[k][3] ;
    for ( j = 1 ; j < height - 1 ; j++ )
      for ( i = 1 ; i < width - 1 ; i++ ) {
        a = &data[(ja+j)*width+ia+i], c = &data[(jc+j)*width+ic+i], b = &data[j*width+i] ;

        if ( *a <= *b - 2 )
          *b = *b - 1 ;
       }

    for ( j = 1 ; j < height - 1 ; j++ )
      for ( i = 1 ; i < width - 1 ; i++ ) {
        a = &data[(ja+j)*width+ia+i], c = &data[(jc+j)*width+ic+i], b = &data[j*width+i] ;

        if ( *a < *b && *b >= *c )
          *b = *b - 1 ;
      }

    for ( j = 1 ; j < height - 1 ; j++ )
      for ( i = 1 ; i < width - 1 ; i++ ) {
        a = &data[(ja+j)*width+ia+i], c = &data[(jc+j)*width+ic+i], b = &data[j*width+i] ;

        if ( *c < *b && *b >= *a )
          *b = *b - 1 ;
      }

    for ( j = 1 ; j < height - 1 ; j++ )
      for ( i = 1 ; i < width - 1 ; i++ ) {
        a = &data[(ja+j)*width+ia+i], c = &data[(jc+j)*width+ic+i], b = &data[j*width+i] ;

        if ( *c <= *b - 2 )
          *b = *b - 1 ;
      }
  }

}

}


