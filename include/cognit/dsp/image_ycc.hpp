/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include <algorithm>
#include <tuple>


namespace cognit {



// Convert YCbCr to RGB
template <class F, class Y>
std::tuple<F, F, F> ycbcr_to_rgb(Y y, Y cb, Y cr) noexcept
{
    auto r = y                               + 1.402f * (cr - 128.f);
    auto g = y - 0.344136f * (cb - 128.f) - 0.714136f * (cr - 128.f);
    auto b = y +    1.772f * (cb - 128.f);

    return {r, g, b};
}


template <class T, class Y>
std::tuple<T, T, T> ycbcr_to_rgb_int(Y y, Y cb, Y cr) noexcept
{
    int k{65536};
    int shift = 16;
    int cbi = (int)cb;
    int cri = (int)cr;
    auto yk = y * k;

    auto r = yk                        + 91881 * (cri - 128);
    auto g = yk -  22553 * (cbi - 128) - 46801 * (cri - 128);
    auto b = yk + 116129 * (cbi - 128);

    
    return {r >> shift, g >> shift, b >> shift};
}


}  // namespace cognit
