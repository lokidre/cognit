/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include "pt.hpp"
#include "tri.hpp"


namespace cognit {

template <typename type>
struct ASphere {
  APoint3D<type> o ;  // center
  type r ;  // radius
} ;

template <class type>
bool sph_sect ( ASphere<type> &s, APoint3D<type> &p, APoint3D<type> &a, APoint3D<type> &b )
{
  // ox.x^2 + ox.y^2 + ox.z^2 = r^2
  // ox.x/op.x = ox.y/op.y = ox.z/op.z

  Vec3<type> op ;

  VctSub(p,s.o,op) ;

  type oplen = (type)sqrt(op.x*op.x+op.y*op.y+op.z*op.z) ;

  if ( Zero(oplen) )
    return false ;

  a.x = s.r * op.x / oplen ;
  a.y = s.r * op.y / oplen ;
  a.z = s.r * op.z / oplen ;

  b.x = -a.x, b.y = -a.y, b.z = -a.z ;

  VctAdd ( a, s.o, a ) ;
  VctAdd ( b, s.o, b ) ;

  return true ;
}


}

