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

template <class input_type, class output_type>
void conservative_2d(const input_type* in_data, output_type* out_data, int width, int height, int aperture) noexcept
{
    auto aperture_half = aperture / 2;
    input_type c, min, max;
    int i, j, k, l;

    for (j = aperture_half; j < height - aperture_half; ++j) {
        for (i = aperture_half; i < width - aperture_half; ++i) {
            min = max = in_data[(j-aperture_half)*width+(i-aperture_half)];
            for (k = 0; k < aperture; ++k) {
                for (l = 0; l < aperture; ++l) {
                    c = in_data[(j-aperture_half+k)*width+(i-aperture_half+l)];
                    if (c < min)
                        min = c;
                    if (c > max)
                        max = c;
                }
            }

            c = in_data[j*width + i];

            if (c < min)
                out_data[j*width + i] = output_type(min);
            else if (c > max)
                out_data[j*width + i] = output_type(max);
            else
                out_data[j*width + i] = output_type(c);
        }
    }
}

}  // namespace cognit

