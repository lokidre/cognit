/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
// Copyright (C) 2003-2004, 2007 Andrey Mirzoyan
// For conditions of distribution and use, see LICENSE file

#pragma once


namespace cognit {



//
// Convolve source image with kernel
//

// Note: These functions in general are slow
// they should be used mostly for experiments


template <class T, class U, class Idx>
void convolve(const T* input, Idx length, const T* kernel, Idx aperture, U* output)
{
    auto apertureHalf = aperture / 2;

    T sum;

    auto s = input + apertureHalf;
    U* d = output + apertureHalf;

    for (int i = aperture; i < length; ++i, ++s, ++d) {
        sum = 0;

        auto k = kernel;
        auto ss = s;

        for (int l = 0; l < aperture; ++l, ++k, ++ss) {
            sum += *k * *ss;
        }

        *d = U(sum);
    }

    // boundary - needed better
    U v1 = *(output + apertureHalf+1), v2 = *(output + length - apertureHalf - 1);
    U* d1 = output, * d2 = output + length - apertureHalf;
    for (int i = 0; i < apertureHalf; ++i, ++d1, ++d2)
        *d1 = v1, * d2 = v2;
}


// needed - some bug in here
template <class T, class U, class Idx>
void convolve_1d_x(const T* input, Idx width, Idx height, const T* kernel, Idx aperture, U* output) noexcept
{
    auto apertureHalf = aperture / 2;
    auto skip = apertureHalf;
    auto endW = width - apertureHalf;

    auto inRow = input;
    auto outRow = output;
    for (Idx row = 0; row < height; ++row, inRow += width, outRow += width) {
        auto in = inRow;
        auto out = outRow + skip;

        for (Idx col = skip; col < endW; ++col, ++in, ++out) {
            T sum{};

            for (auto pk = kernel, ps = in, end = pk + aperture; pk != end; ++pk, ++ps) {
                sum += *pk * *ps;
            }

            *out = static_cast<U>(sum);
        }
    }

    // Process the skipped data
    inRow = input;
    outRow = output;
    for (Idx row = 0; row < height; ++row, inRow += width, outRow += width) {
        auto ps1 = inRow;
        auto pd1 = outRow;
        auto ps2 = inRow + width - 1;
        auto pd2 = outRow + width - 1;

        for (Idx col = 0; col < apertureHalf; ++col) {
            *pd1 = static_cast<U>(*ps1);
            *pd2 = static_cast<U>(*ps2);

            ++pd1, ++ps1;
            --pd2, --ps2;
        }
    }
}



template <class T, class Idx, class U>
void convolve_1d_y(const T* input, Idx width, Idx height, const T* kernel, Idx aperture, U* output) noexcept
{
    auto apertureHalf = aperture / 2;
    auto skip = apertureHalf;
    auto endH = height - apertureHalf;

    auto inCol = input;
    auto outCol = output;

    for (Idx col = 0; col < width; ++col, ++inCol, ++outCol) {
        auto in = inCol;
        auto out = outCol + skip * width;

        for (Idx row = skip; row < endH; ++row, in += width, out += width) {
            T sum{};

            for (auto pk = kernel, ps = in, end = pk + aperture; pk != end; ++pk, ps += width) {
                sum += *pk * *ps;
            }

            *out = static_cast<U>(sum);
        }
    }

    // Process the skipped data
    inCol = input;
    outCol = output;
    for (Idx col = 0; col < width; ++col, ++inCol, ++outCol) {
        auto ps1 = inCol;
        auto pd1 = outCol;
        //auto ps2 = inCol + (height - 1 - apertureHalf) * width;
        //auto pd2 = outCol + (height - 1 - apertureHalf) * width;
        auto ps2 = inCol + (height - 1) * width;
        auto pd2 = outCol + (height - 1) * width;

        for (Idx row = 0; row < apertureHalf; ++row) {
            *pd1 = static_cast<U>(*ps1);
            *pd2 = static_cast<U>(*ps2);

            pd1 += width, ps1 += width;
            pd2 -= width, ps2 -= width;
        }
    }
}




template <class T, class Idx, class D>
void convolve_2d(const T* input, Idx width, Idx height, const T* kernel, Idx aperture, D* output) noexcept
{
    auto apertureHalf = aperture / 2;
    auto begin = apertureHalf;
    auto endW = width - apertureHalf;
    auto endH = height - apertureHalf;

    auto dd = output + apertureHalf * width;

    // Skip the borders
    for (Idx j = begin; j < endH; j++) {
        dd += apertureHalf;

        for (Idx i = begin; i < endW; i++, dd++) {
            T sum{};

            auto pk = kernel;
            auto ps = input + (j - apertureHalf)*width + i - apertureHalf;

            for (Idx k = 0; k < aperture; k++) {
                for (Idx l = 0; l < aperture; l++, pk++, ps++) {
                    sum += *pk * *ps;
                }

                ps += width - aperture;
            }

            *dd = (D)sum;
        }

        dd += apertureHalf;
    }


    // Horizontal borders
    for (Idx j = 0; j < apertureHalf; j++) {
        // Bottom border
        auto s1 = output + (apertureHalf+1)*width;
        auto d1 = output + j*width;

        // Top border
        auto s2 = output + (height-apertureHalf-2)*width;
        auto d2 = output + (height-j-1)*width;

        for (Idx i = 0; i < width; i++, s1++, s2++, d1++, d2++) {
            *d1 = *s1; 
            *d2 = *s2;
        }
    }

    // Vertical borders
    for (Idx i = 0; i < apertureHalf; i++) {
        // Left border
        auto s1 = output + apertureHalf+1;
        auto d1 = output + i;

        // Right border
        auto s2 = output + width-apertureHalf-2;
        auto d2 = output + width-i-1;

        for (Idx j = 0; j < height; j++, s1 += width, s2 += width, d1 += width, d2 += width) {
            *d1 = *s1;
            *d2 = *s2;
        }
    }
}

}  // namespace
