/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

// Copyright (C) 2007 Andrey Mirzoyan
// See LICENCE for details


namespace cognit {


//
// Hysteresis thresholding
//
//template <class T, class M>
//void hysteresis_threshold_mask ( const T *norm,  

template <class T, class M>
void hysteresis_threshold(const T* norm, const M* maxima, M* edges, int width, int height, T high_threshold, T low_threshold)
{
    auto total = width * height;

    auto n = norm;
    auto e = edges;
    auto m = maxima;

    // first load all data with higher threshold
    for (int i = 0; i < total; ++i, ++n, ++e, ++m) {
        if (*m && *n >= high_threshold)
            *e = 1;
        else
            *e = 0;
    }

    // now load all with lower threshold
    bool found_threshold{};

    do {
        found_threshold = false;

        n = norm, m = maxima, e = edges;

        n += width, e += width, m += width;  // start from the second row

        for (int j = 2; j < height; ++j) {
            ++n, ++m, ++e;  // start from second column
            for (int i = 2; i < width; ++i, ++n, ++m, ++e) {
                if (*e || !*m)  // skip selected and not maxima
                    continue;

                if (*n < low_threshold)  // skip with low threshold
                    continue;

                // now check the backgrounds
                if (*(e-1) || *(e+1) || *(e+width) || *(e-width) || *(e+width+1) || *(e+width-1) || *(e-width+1) || *(e-width-1)) {
                    *e = 1;
                    found_threshold = true;
                }
            }
            ++n, ++m, ++e;
        }

    } while (found_threshold);
}


}

