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

template <class T, class U>
void threshold_low(T* data, int total, U value) noexcept
{
    T* p = data;
    const T val = T(value);
    for (int i = 0; i < total; ++i, ++p)
        if (*p < val)
            *p = 0;
}


//
// note: skips when mask is 0
template <class M, class T, class U>
void threshold_low_mask(const T* data, M* mask, int total, U value) noexcept
{
    auto m = mask;
    auto d = data;
    auto v = T(value);
    for (int i = 0; i < total; ++i, ++m, ++d) {
        if (*m && *d < v)
            *m = 0;
    }
}




template <typename data_type>
void threshold(data_type* data, int total, data_type tmin, data_type tmax) noexcept
{
    auto d = data;
    for (int i = 0; i < total; i++) {
        if (*d < tmin)
            *d = tmin;
        else if (*d > tmax)
            *d = tmax;
        d++;
    }
}


} // namespace 


