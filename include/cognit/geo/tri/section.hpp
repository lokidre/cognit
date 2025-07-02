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

template <typename type>
bool TriSect ( ATriangle3D<type> &p, ATriangle3D<type> &q )
{
  if ( PtInTri(p.a,q) || PtInTri(p.b,q) || PtInTri(p.c,q) ||
       PtInTri(q.a,p) || PtInTri(q.b,p) || PtInTri(q.c,p) )
    return true ;

  type l, m ;  // lambda, myu
  APoint3D<type> x ;

  if ( LnSect ( p.a, p.b, q.a, q.b, x, l, m ) && l >= 0 && l <= 1 && m >= 0 && m <= 1 )
    return true ;
  if ( LnSect ( p.a, p.c, q.a, q.b, x, l, m ) && l >= 0 && l <= 1 && m >= 0 && m <= 1 )
    return true ;
  if ( LnSect ( p.b, p.c, q.a, q.b, x, l, m ) && l >= 0 && l <= 1 && m >= 0 && m <= 1 )
    return true ;

  if ( LnSect ( p.a, p.b, q.a, q.c, x, l, m ) && l >= 0 && l <= 1 && m >= 0 && m <= 1 )
    return true ;
  if ( LnSect ( p.a, p.c, q.a, q.c, x, l, m ) && l >= 0 && l <= 1 && m >= 0 && m <= 1 )
    return true ;
  if ( LnSect ( p.b, p.c, q.a, q.c, x, l, m ) && l >= 0 && l <= 1 && m >= 0 && m <= 1 )
    return true ;

  if ( LnSect ( p.a, p.b, q.b, q.c, x, l, m ) && l >= 0 && l <= 1 && m >= 0 && m <= 1 )
    return true ;
  if ( LnSect ( p.a, p.c, q.b, q.c, x, l, m ) && l >= 0 && l <= 1 && m >= 0 && m <= 1 )
    return true ;
  if ( LnSect ( p.b, p.c, q.b, q.c, x, l, m ) && l >= 0 && l <= 1 && m >= 0 && m <= 1 )
    return true ;

  return false ;
}

}  // namespace
