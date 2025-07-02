/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

/*
                Rotation Matrices

*/

#include "../vec.hpp"
#include "../func.hpp"
#include "../mtx.hpp"


namespace cognit {


//
// Build 2x2 rotation matrix from angle theta for rotating counter clockwise
//
template <class T>
Mtx2<T>& mtx_rotation_x(Mtx2<T>& r, T rho) noexcept
{
    auto cs = std::cos(rho), sn = std::sin(rho);

    r.a[0][0] = cs, r.a[0][1] = -sn;
    r.a[1][0] = sn, r.a[1][1] = cs;

    return r;
}

template <class T>
Mtx4<T>& mtx_rotation_x(Mtx4<T>& Rx, T rho) noexcept
{
    auto cs = std::cos(rho), sn = std::sin(rho);

    Rx.zero();

    Rx.a[0][0] = 1;
    Rx.a[1][1] = cs;
    Rx.a[1][2] = -sn;
    Rx.a[2][1] = sn;
    Rx.a[2][2] = cs;
    Rx.a[3][3] = 1;

    return Rx;
}



//
// Builds the rotation matrix around vector v, for angle theta
// the vector must be unit
//
template <class T>
Mtx4<T>& mtx_rot_axis(const Vec3<T>& v, T theta, Mtx4<T>& R) noexcept
{
    T sn = sin(theta);
    T cs = cos(theta);
    T mc = T(1) - cs;


    R.zero();

    R.a[0][0] = v.x*v.x + (1-v.x*v.x)*cs;
    R.a[0][1] = v.x*v.y*mc + v.z*sn;
    R.a[0][2] = v.x*v.z*mc - v.y*sn;
    R.a[1][0] = v.x*v.y*mc - v.z*sn;
    R.a[1][1] = v.y*v.y*mc + cs;
    R.a[1][2] = v.y*v.z*mc + v.x*sn;
    R.a[2][0] = v.x*v.z*mc + v.y*sn;
    R.a[2][1] = v.y*v.z*mc - v.x*sn;
    R.a[2][2] = v.z*v.z*mc + cs;

    R.a[3][3] = 1;

    return R;
}

}  // namespace

