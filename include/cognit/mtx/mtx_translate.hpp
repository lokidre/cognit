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

//
// translates the matrix
//
template <class T>
void mtx_translate ( Mtx4<T> &m, T x, T y, T z ) noexcept
{
  m.a[3][0] += x ;
  m.a[3][1] += y ;
  m.a[3][2] += z ;
}

template <class T>
void mtx_translate ( Mtx4<T> &m, const Vec3<T> &v ) noexcept
{
    mtx_translate(v.x, v.y, v.z, m) ;
}

}  // namespace cognit

