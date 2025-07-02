/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

/*

		Minor & Cofactor

	Minor of the element a[i][j] of matrix A is matrix Am which can be given by
	removing from matrix A the column and row containg a[i][j]

	Cofactor of element a[i][j] is called the determinant of minor 
	multiplied by (-1)^(i+j)

*/


namespace cognit {




template <typename type, int n, typename matrix_type>
void mtx_minor ( Mtx2<type> &a, int i, int j, matrix_type &p )
{
    p = a.a[i==0?1:0][j==0?1:0] ;
}

template <typename type, int n, typename minor_type>
void mtx_minor ( Mtx3<type> &a, int i, int j, minor_type &p )
{
    int di = 0, dj = 0, ci, cj ;

  for ( cj = 0 ; cj < 3 ; cj++ ) {
    di = 0 ;
    if ( cj == j )
      continue ;

    for ( ci = 0 ; ci < 3 ; ci++ ) {
      if ( ci == i )
        continue ;
      p.a[di][dj] = a.a[ci][cj] ;
      di++ ;
    }

    dj++ ;
  }

}


// remarks: must be m == n-1
template <typename type, int n, typename minor_type>
void mtx_minor ( MtxN<type,n> &a, int i, int j, minor_type &p )
{
  int di = 0, dj = 0, ci, cj ;

  for ( cj = 0 ; cj < n ; cj++ ) {
    di = 0 ;
    if ( cj == j )
      continue ;

    for ( ci = 0 ; ci < n ; ci++ ) {
      if ( ci == i )
        continue ;
      p.a[di][dj] = a.a[ci][cj] ;
      di++ ;
    }

    dj++ ;
  }
}




/*
template <typename type, int n, int m>
inline 
void MtxMinor ( Mtx2<type> &a, int i, int j, type &p )
{
  p = a.a[i==0?1:0][j==0?1:0] ;
}


template <typename type, int n, int m>
void MtxMinor ( Mtx3<type> &a, int i, int j, Mtx2<type> &p )
{
  int di = 0, dj = 0, ci, cj ;

  for ( cj = 0 ; cj < 3 ; cj++ ) {
    di = 0 ;
    if ( cj == j )
      continue ;

    for ( ci = 0 ; ci < 3 ; ci++ ) {
      if ( ci == i )
        continue ;
      p.a[di][dj] = a.a[ci][cj] ;
      di++ ;
    }

    dj++ ;
  }

}


// remarks: must be m == n-1
template <typename type, int n, int m>
void MtxMinor ( MtxN<type,n> &a, int i, int j, MtxN<type,m> &p )
{
  int di = 0, dj = 0, ci, cj ;

  for ( cj = 0 ; cj < n ; cj++ ) {
    di = 0 ;
    if ( cj == j )
      continue ;

    for ( ci = 0 ; ci < n ; ci++ ) {
      if ( ci == i )
        continue ;
      p.a[di][dj] = a.a[ci][cj] ;
      di++ ;
    }

    dj++ ;
  }
}
*/

}  // namespace

