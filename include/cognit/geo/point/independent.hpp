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

// finds arbitrary 4 independent points (not laying on one plane)
template <class type>
bool pts_select_independent_3d ( APoint3D<type> *pts, int npts, int *spts )
{
  APoint3D<type> *p, *q, *r, *s ;
  int ipt ;

  p = &pts[0] ;  // first and second points can be any
  q = &pts[1] ;
  spts[0] = 0, spts[1] = 1 ;
  r = s = NULL ;

  // the third point must be on the same line with first two
  for ( ipt = 2 ; ipt < npts ; ipt++ ) {
    if ( !PtsOnLine ( *p, *q, pts[ipt] ) ) {
      r = &pts[ipt] ;
      spts[2] = ipt ;
      break ;
    }
  }

  // if the point is not found, then error
  if ( r == NULL )
    return false ;


  // the fourth point shouldn't be on the same plane with first three
  for ( ipt = 3 ; ipt < npts ; ipt++ ) {
    if ( !PtsOnPlane ( *p, *q, *r, pts[ipt] ) ) {
      s = &pts[ipt] ;
      spts[3] = ipt ;
      break ;
    }
  }

  if ( s == NULL )
    return false ;

  return true ;
}



// selects some 3 points not on one line
template <class tPt>
bool pts_select_independent_2d ( tPt *pts, int npts, int *spts )
{
  tPt *p, *q, *r ;
  int ipt ;

  p = &pts[0] ;  // first two points are arbitraty
  q = &pts[1] ;
  spts[0] = 0, spts[1] = 1 ;
  r = NULL ;

  // the third point shouldn't be on the same line
  for ( ipt = 2 ; ipt < npts ; ipt++ ) {
    if ( !PtsOnLine2D ( *p, *q, pts[ipt] ) ) {
      r = &pts[ipt] ;
      spts[2] = ipt ;
      break ;
    }
  }

  // if the point is not found
  if ( r == NULL )
    return false ;

  return true ;
}

}  // namespace
