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


template <class T, class iterator>
void vct_scale ( iterator x, int n, T s )
{
    for ( int i = 0 ; i < n ; ++i, ++x )
        *x *= s ;
}


template <class T, class U_iterator, class V_iterator>
void vct_scale ( U_iterator u, V_iterator v, int n, T s )
{
    for ( int i = 0 ; i < n ; ++i, ++u, ++v )
        *v = *v * s ;
}


template <class T, class U>
Vec3<T> &vct_scale(Vec3<T> &v, const U &s )
{
    v.a[0] *= s, v.a[1] *= s, v.a[2] *= s ;
    return v ;
}

template <class T, class U>
Vec3<T> &vct_scale(const Vec3<T> &u, Vec3<T> &v, U s )
{
    v.a[0] = u.a[0]*s, v.a[1] = u.a[1]*s, v.a[2] = u.a[2]*s ;
    return v ;
}


template <class T, class U>
Vec4<T> &vct_scale(Vec4<T> &v, U s )
{
    v.a[0] *= s, v.a[1] *= s, v.a[2] *= s, v.a[3] *= s ;
    return v ;
}

template <class T, class U>
Vec4<T> &vct_scale(const Vec4<T> &u, Vec4<T> &v, U s )
{
    v.a[0] = u.a[0]*s, v.a[1] = u.a[1]*s, v.a[2] = u.a[2]*s, v.a[3] = u.a[3]*s ;
    return v ;
}



}
