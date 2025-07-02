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
                Projection Matrices

*/

//#include "../../mat/matrix.hpp"


namespace cognit {


template <class T>
Mtx4<T>& mtx_frustum(Mtx4<T>& P, T left, T right, T bottom, T top, T znear, T zfar)
{
    P.zero();

    P.a[0][0] = 2*znear/(right-left);
    P.a[0][2] = (right+left)/(right-left);
    P.a[1][1] = 2*znear/(top-bottom);
    P.a[1][2] = (top+bottom)/(top-bottom);

    P.a[2][2] = -(zfar+znear)/(zfar-znear);
    P.a[2][3] = -2*zfar*znear/(zfar-znear);

    P.a[3][2] = -1;

    return P;
}


//}
