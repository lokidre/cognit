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
    Vector Dot (Scalar) Product

*/

namespace cognit {


template <class T, class iterator>
T vct_dot(iterator x, iterator y, Index n) noexcept
{
    T s{};

    for (Index i{}; i < n; ++i, ++x, ++y)
        s += *x * *y;

    return s;
}




template <class T>
T vct_dot(const Vec<T>& u, const Vec<T>& v) noexcept
{
    return vct_dot<T, T*>(u.p, v.p, u.N);
}


}  // namespace


