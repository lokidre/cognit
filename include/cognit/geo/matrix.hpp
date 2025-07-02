/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include "../matrix.hpp"
#include "../vector.hpp"

#include "vector.hpp"


namespace cognit {


//
// builds lookat matrix from three vectors: eye, at, up
//
template <class T>
Mtx4<T> &mtx_lookat ( const Vec3<T> &eye, 
                          const Vec3<T> &at, 
                          const Vec3<T> &up,
			  Mtx4<T> &m )
{


  return m ;
}


//
// Builds left handed orthogonal projection matrix
//
template <typename type>
Mtx4<type> &mtx_ortho ( const type &xl, const type &xr, 
                            const type &yb, const type &yt, 
			    const type &zn, const type &zf,
                            Mtx4<type> )
{
  m.a[0][0] = type(2)/(xr-xl) ;
  m.a[1][1] = type(2)/(yt-yb) ;
  m.a[2][2] = type(1)/(zf-zn) ;
  m.a[3][3] = type(1) ;

  m.a[3][0] = (xl+xr)/(xl-xr) ;
  m.a[3][1] = (yb+yt)/(yb-yt) ;
  m.a[3][2] = zn/(zn-zf) ;

  m.a[0][1] = m.a[0][2] = m.a[0][3] = 
  m.a[1][0] = m.a[1][2] = m.a[1][3] =
  m.a[2][0] = m.a[2][1] = m.a[2][3] = 0 ;

  return m ;
}

}  // namespace


#include "trans.cxx"
#include "rotate.cxx"

