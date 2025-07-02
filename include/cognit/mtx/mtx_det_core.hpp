/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#if 0  //DocHeader

Matrix determinant

TODO: fix, not working

#endif


namespace cognit {

// Calculation of determinant by definition
// Very inefficient, overflows - just for experimentation
// needed - check
template <class T, class Idx>
T mtx_det_def_ptr(const T* a, Idx n) noexcept
{
    T det{};

    for (Idx k = 0; k < n; k++) {
        T t{1};  // = one;

        for (Idx i = 0; i < n; i++) {
            auto j = i + k;
            if (j >= n)
                j -= n;
            t *= a[i * n + j];
        }

        det += t;
    }

    for (Idx k = 0; k < n; k++) {
        T t{1};  // = one;
        for (Idx i = 0; i < n; i++) {
            auto j = i + k;
            if (j >= n)
                j -= n;
            t *= a[(n - 1 - i) * n + j];
        }
        det -= t;
    }

    return det;
}


}  // namespace cognit
