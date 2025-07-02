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
	Replaces very small values with zeroes
*/

#include "../func.hpp"

namespace cognit {

template <class T, class iterator>
void vct_chop(iterator v, int n, const T& eps)
{
    for (int i = 0; i < n; ++i, ++v)
        if (abs(*v) < eps)
            *v = 0;
}


template <class T>
Vec4<T>& vct_chop(Vec4<T>& v)
{
    vct_chop(v.a, 4, constants::epsilon<T>);
    return v;
}


}  // namespace cognit
