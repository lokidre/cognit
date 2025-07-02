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

// finds the closest point from the container
// returns point's index
template <typename type>
size_t pts_find_closest ( APoint3D<type> *pts, int npts, APoint3D<type> &pt, int igiven = -1 )
{
  if ( npts == 0 )
    return -1 ;

  int ibegin = 0 ;

  if ( igiven == ibegin )
    ibegin++ ;

  type MinDistSqr = PtDistSqr(pt,pts[ibegin]) ;
  int iClosest = ibegin ;

  type CurrDistSqr ;
  APoint3D<type> *ppt ;

  for ( int ipt = ibegin + 1 ; ipt < npts ; ipt++ ) {
    if ( ipt == igiven )
      continue ;
    ppt = &pts[ipt] ;
    CurrDistSqr = pt_dist_sqr(pt,*ppt) ;
    if ( CurrDistSqr < MinDistSqr )
      MinDistSqr = CurrDistSqr, iClosest = ipt ;
  }

  return iClosest ;
}


template <typename type>
int pts_find_closest ( APoint2D<type> *pts, int npts, APoint2D<type> &pt, int igiven = -1 )
{
  if ( npts == 0 )
    return -1 ;

  int ibegin = 0 ;

  if ( igiven == ibegin )
    ibegin++ ;

  type MinDistSqr = PtDistSqr(pt,pts[ibegin]) ;
  int iClosest = ibegin ;

  type CurrDistSqr ;
  APoint2D<type> *ppt ;

  for ( int ipt = ibegin + 1 ; ipt < npts ; ipt++ ) {
    if ( ipt == igiven )
      continue ;
    ppt = &pts[ipt] ;
    CurrDistSqr = pt_dist_sqr(pt,*ppt) ;
    if ( CurrDistSqr < MinDistSqr )
      MinDistSqr = CurrDistSqr, iClosest = ipt ;
  }

  return iClosest ;
}

}  // namespace
