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


template <class T>
struct Circle {
  Vec2<T> o ;  // center ;
  T r ;  // radius
} ;



// inscribe, circumscribe
template <class T>
bool CirOutTriCtr ( const Vec2<T> &a, const Vec2<T> &b, const Vec2<T> &c, type &ctr )
{
  APoint2D<T> p, q ;
  APoint2D<T> u, v ;
  AVector2D<T> n1, n2 ;
  type l, m ;  // lambda & myu

  p.x = (a.x+b.x)/2, p.y = (a.y+b.y)/2 ;
  q.x = (b.x+c.x)/2, q.y = (b.y+c.y)/2 ;

  VctNrm(a,b,n1) ;
  VctNrm(b,c,n2) ;

  VctAdd(n1,p,u) ;
  VctAdd(n2,q,v) ;


  if ( !LnSect ( p, u, q, v, ctr, l, m ) )
    return false ;

  return true ;
}

}  // namespace

