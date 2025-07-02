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


template <class src_data_type, class dst_data_type>
void zero_crossing(const src_data_type* src, dst_data_type* dst, int width, int height)
{
    const src_data_type* s, * sx, * sy;
    dst_data_type* d;

    sx = src, s = src+1, sy = src+width;
    d = dst;

    for (int i = 0; i < width; ++i, ++d)
        *d = 0;

    // needed more left right top bottom
    for (int j = 1; j < height; j++) {

        *d++ = 0;

        for (int i = 1; i < width; ++i, ++d, ++s, ++sx, ++sy) {
            if (*s > 0 && *sx < 0)
                *d = (dst_data_type)(*s - *sx);
            else if (*s < 0 && *sx > 0)
                *d = (dst_data_type)(*sx - *s);
            else if (*s > 0 && *sy < 0)
                *d = (dst_data_type)(*s - *sy);
            else if (*s < 0 && *sy > 0)
                *d = (dst_data_type)(*sy - *s);
            else
                *d = dst_data_type(0);
        }

        *d++ = 0;

        ++s, ++sx, ++sy;
    }


}

}  // namespace


