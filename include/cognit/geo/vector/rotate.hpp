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

// Vector Rotation 
//
//   1     0      0
//   0     cosa   sina
//   0    -sina   cosa
//
//  oy axis
//
//   cosb  0     -sinb
//   0     1     0
//   sinb  0     cosb
//
// oz axis
//
//   cosg  sing  0
//  -sing  cosg  0
//  0      0     1
//



template <class T, class P>
P &pt_rot_2d ( const P &u, T t, P &v )
{
	T cs = cos(t), sn = sin(t) ;

	v.x = u.x*cs - u.y*sn ;
	v.y = u.x*sn + u.y*cs ;

	return v ;
}



template <class type>
Vec3<type> &VctRotX ( const Vec3<type> &v, type a, Vec3<type> &x )
{
  type sina = sin(a), cosa = cos(a) ;

  x.x =  v.x ;
  x.y =  v.y*cosa + v.z*sina ;
  x.z = -v.y*sina + v.z*cosa ;
  return x ;
}

template <class type>
Vec3<type> &VctRotY ( const Vec3<type> &v, type b, Vec3<type> &x )
{
  type sinb = sin(b), cosb = cos(b) ;
 
  x.x =  v.x*cosb - v.z*sinb ;
  x.y =  v.y ;
  x.z =  v.x*sinb + v.z*cosb ;
  
  return x ;
}

template <class T>
Vec3<T> &VctRotZ ( const Vec3<T> &v, T g, Vec3<type> &x )
{
  auto sing = sin(g), cosg = cos(g) ;

  x.x =  v.x*cosg + v.y*sing ;
  x.y = -v.x*sing + v.y*cosg ;
  x.z =  v.z ;
  
  return x ;
}

}  // namespace

