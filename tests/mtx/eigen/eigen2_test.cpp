/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#include <mat.h>

#include <stdio.h>


typedef double float_type ;


AMatrix2<float_type> m ;
AMatrix2<tComplex<float_type> > v ;
tVector2<tComplex<float_type> > e ;


char s[2000] ;

void main ( void )
{
  m.a[0][0] = 1 ;
  m.a[0][1] = 100 ;
  m.a[1][0] = -333 ;
  m.a[1][1] = -4 ;

  MtxEigenValues ( m, e ) ;
  MtxEigen ( m, e, v ) ;


  printf ( "Eigen values:\n" ) ;
  printf ( "%s\n", unistr ( e, s ) ) ;

  printf ( "Eigen vectors:\n" ) ;
  printf ( "%s\n", unistr ( v, s ) ) ;


  /*
  int nrot ;

  double m_[4][4], v_[4][4], e_[4] ;

  for ( int i = 0 ; i < 4 ; i++ )
    for ( int j = 0 ; j < 4 ; j++ )
      m_[i][j] = m.a[i][j] ;

  jacobi( m_, 4, e_, v_, &nrot) ;
  */
  


}

