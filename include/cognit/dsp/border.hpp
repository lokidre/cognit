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

template <class T, class W, class Idx>
void fill_border(T* data, Idx width, Idx height, int border, W v_) noexcept
{
    auto p = data;
    auto v = T(v_);
    Idx i, j;

    for (j = 0, p = data; j < border; ++j)
        for (i = 0; i < width; ++i, ++p)
            *p = v;

    for (j = 0, p = data + (height - border)*width; j < border; ++j)
        for (i = 0; i < width; ++i, ++p)
            *p = v;

    for (i = 0; i < border; ++i) {
        p = data + i;
        for (j = 0; j < height; ++j, p += width)
            *p = v;
    }

    for (i = 0; i < border; ++i) {
        p = data + width - border + i;
        for (j = 0; j < height; ++j, p += width)
            *p = v;
    }
}


}  // namespace
