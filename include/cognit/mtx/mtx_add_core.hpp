/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#if 0 //DocHeader

Matrix addition and subtraction

mtx_add(a, b, c)

Computes c = a + b

a maybe be equal to c then it computes a += b


#endif

namespace cognit {

template <class SrcIt, class DstIt, class Idx>
constexpr void mtx_add_it(SrcIt a, SrcIt b, Idx m, Idx n, DstIt c) noexcept
{
    auto total = m * n;

    if (a == c) {
        for (Idx i = 0; i < total; ++i, ++a, ++b)
            *c = *a + *b;
    } else {
        for (Idx i = 0; i < total; ++i, ++a, ++b, ++c)
            *c = *a + *b;
    }
}

template <class SrcIt, class DstIt, class Idx>
constexpr void mtx_sub_it(SrcIt a, SrcIt b, Idx m, Idx n, DstIt c) noexcept
{
    auto total = m * n;

    if (a == c) {
        for (Idx i = 0; i < total; ++i, ++a, ++b)
            *c = *a - *b;
    } else {
        for (Idx i = 0; i < total; ++i, ++a, ++b, ++c)
            *c = *a - *b;
    }
}

template <class MT>
void mtx2x2_add(const MT& a, const MT& b, MT& c) noexcept
{
    c.a[0][0] = a.a[0][0] + b.a[0][0];
    c.a[0][1] = a.a[0][1] + b.a[0][1];
    c.a[1][0] = a.a[1][0] + b.a[1][0];
    c.a[1][1] = a.a[1][1] + b.a[1][1];
}


template <class MT>
void mtx2x2_sub(const MT& a, const MT& b, MT& c) noexcept
{
    c.a[0][0] = a.a[0][0] - b.a[0][0];
    c.a[0][1] = a.a[0][1] - b.a[0][1];
    c.a[1][0] = a.a[1][0] - b.a[1][0];
    c.a[1][1] = a.a[1][1] - b.a[1][1];
}

template <class MT>
void mtx3x3_add(const MT& a, const MT& b, MT& c) noexcept
{
    c.a[0][0] = a.a[0][0] + b.a[0][0];
    c.a[0][1] = a.a[0][1] + b.a[0][1];
    c.a[0][2] = a.a[0][2] + b.a[0][2];
    c.a[1][0] = a.a[1][0] + b.a[1][0];
    c.a[1][1] = a.a[1][1] + b.a[1][1];
    c.a[1][2] = a.a[1][2] + b.a[1][2];
    c.a[2][0] = a.a[2][0] + b.a[2][0];
    c.a[2][1] = a.a[2][1] + b.a[2][1];
    c.a[2][2] = a.a[2][2] + b.a[2][2];
}

template <class MT>
void mtx3x3_sub(const MT& a, const MT& b, MT& c) noexcept
{
    c.a[0][0] = a.a[0][0] - b.a[0][0];
    c.a[0][1] = a.a[0][1] - b.a[0][1];
    c.a[0][2] = a.a[0][2] - b.a[0][2];
    c.a[1][0] = a.a[1][0] - b.a[1][0];
    c.a[1][1] = a.a[1][1] - b.a[1][1];
    c.a[1][2] = a.a[1][2] - b.a[1][2];
    c.a[2][0] = a.a[2][0] - b.a[2][0];
    c.a[2][1] = a.a[2][1] - b.a[2][1];
    c.a[2][2] = a.a[2][2] - b.a[2][2];
}


template <class MT>
void mtx4x4_add(const MT& a, const MT& b, MT& c) noexcept
{
    c.a[0][0] = a.a[0][0] + b.a[0][0];
    c.a[0][1] = a.a[0][1] + b.a[0][1];
    c.a[0][2] = a.a[0][2] + b.a[0][2];
    c.a[0][3] = a.a[0][3] + b.a[0][3];
    c.a[1][0] = a.a[1][0] + b.a[1][0];
    c.a[1][1] = a.a[1][1] + b.a[1][1];
    c.a[1][2] = a.a[1][2] + b.a[1][2];
    c.a[1][3] = a.a[1][3] + b.a[1][3];
    c.a[2][0] = a.a[2][0] + b.a[2][0];
    c.a[2][1] = a.a[2][1] + b.a[2][1];
    c.a[2][2] = a.a[2][2] + b.a[2][2];
    c.a[2][3] = a.a[2][3] + b.a[2][3];
    c.a[3][0] = a.a[3][0] + b.a[3][0];
    c.a[3][1] = a.a[3][1] + b.a[3][1];
    c.a[3][2] = a.a[3][2] + b.a[3][2];
    c.a[3][3] = a.a[3][3] + b.a[3][3];
}

template <class MT>
void mtx4x4_sub(const MT& a, const MT& b, MT& c) noexcept
{
    c.a[0][0] = a.a[0][0] - b.a[0][0];
    c.a[0][1] = a.a[0][1] - b.a[0][1];
    c.a[0][2] = a.a[0][2] - b.a[0][2];
    c.a[0][3] = a.a[0][3] - b.a[0][3];
    c.a[1][0] = a.a[1][0] - b.a[1][0];
    c.a[1][1] = a.a[1][1] - b.a[1][1];
    c.a[1][2] = a.a[1][2] - b.a[1][2];
    c.a[1][3] = a.a[1][3] - b.a[1][3];
    c.a[2][0] = a.a[2][0] - b.a[2][0];
    c.a[2][1] = a.a[2][1] - b.a[2][1];
    c.a[2][2] = a.a[2][2] - b.a[2][2];
    c.a[2][3] = a.a[2][3] - b.a[2][3];
    c.a[3][0] = a.a[3][0] - b.a[3][0];
    c.a[3][1] = a.a[3][1] - b.a[3][1];
    c.a[3][2] = a.a[3][2] - b.a[3][2];
    c.a[3][3] = a.a[3][3] - b.a[3][3];
}




}  // namespace cognit
