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


// mean filter
// calculates the average of 9 points around
template <typename src_data_type, typename dst_data_type>
void filter_mean_3x3(src_data_type* in_data, dst_data_type* out_data, int width, int height)
{
    int i, j;
    src_data_type* id, * d1, * d2, * d3, * d;
    dst_data_type* od;
    dst_data_type sum;  // warning!!! for byte type will be error!!! needed

    id = in_data, od = out_data;

    id += width;
    od += width;

    for (j = 1; j < height - 1; j++, id += width) {
        d1 = id, d2 = d1+width, d3=d2+width;

        for (i = 1, ++od; i < width - 1; ++i, ++d1, ++d2, ++d3, ++od) {
            sum = 0;

            d = d1, sum += *d++, sum += *d++, sum += *d++;
            d = d2, sum += *d++, sum += *d++, sum += *d++;
            d = d3, sum += *d++, sum += *d++, sum += *d++;

            *od = dst_data_type(sum / 9);
        }

        od++;
    }
}


// needed
template <typename src_data_type, typename dst_data_type>
void filter_mean_nxn(src_data_type* in_data, dst_data_type* out_data, int width, int height, int aperture)
{
}

}  // namespace


