/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#if Description__

Multiply 3 vector by 4x4 matrix

         v = (x y z), v~ = (x y z 1)

         x = vM = (u v w p), x = (u v w)

#endif


namespace cognit {


template <class T>
Vec3<T>& vct_mtx_mul(const Vec3<T>& v, const Mtx4<T>& m, Vec3<T>& x) noexcept
{
    x.x = v.x*m.a[0][0] + v.y*m.a[1][0] + v.z*m.a[2][0] + m.a[3][0];
    x.y = v.x*m.a[0][1] + v.y*m.a[1][1] + v.z*m.a[2][1] + m.a[3][1];
    x.z = v.x*m.a[0][2] + v.y*m.a[1][2] + v.z*m.a[2][2] + m.a[3][2];

    return x;
}


template <class T>
Vec3<T>& mtx_vct_mul(const Mtx4<T>& a, const Vec3<T>& u, Vec3<T>& v) noexcept
{
    v.x = a.a[0][0]*u.x + a.a[0][1]*u.y + a.a[0][2]*u.z + a.a[0][3];
    v.y = a.a[1][0]*u.x + a.a[1][1]*u.y + a.a[1][2]*u.z + a.a[1][3];
    v.z = a.a[2][0]*u.x + a.a[2][1]*u.y + a.a[2][2]*u.z + a.a[2][3];
    return v;
}

template <class M, class V>
V& mtx4x4_vct3_mul(const M& m, const V& u, V& v) noexcept
{
    v.x = m.a[0][0]*u.x + m.a[0][1]*u.y + m.a[0][2]*u.z + m.a[0][3];
    v.y = m.a[1][0]*u.x + m.a[1][1]*u.y + m.a[1][2]*u.z + m.a[1][3];
    v.z = m.a[2][0]*u.x + m.a[2][1]*u.y + m.a[2][2]*u.z + m.a[2][3];
    return v;
}

template <class M, class V>
V mtx4x4_vct3_mul(const M& m, const V& u) noexcept
{
    V v;
    v.x = m.a[0][0]*u.x + m.a[0][1]*u.y + m.a[0][2]*u.z + m.a[0][3];
    v.y = m.a[1][0]*u.x + m.a[1][1]*u.y + m.a[1][2]*u.z + m.a[1][3];
    v.z = m.a[2][0]*u.x + m.a[2][1]*u.y + m.a[2][2]*u.z + m.a[2][3];
    return v;
}



}  // namespace
