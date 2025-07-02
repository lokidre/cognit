/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include "mean.hpp"
#include "../mtx.hpp"


namespace cognit {


//
// Calculates the covariance between x and y data
// Expects medians of mx and my
//

template <class T, class Idx>
T cov_impl(const T* xd, Idx xstride, const T* yd, Idx ystride, Idx n, T medx, T medy) noexcept
{
    T c{};
    auto N = T(n - 1);
    auto xinc = xstride / sizeof(T), yinc = ystride / sizeof(T);

    // Calculate the variance
    // Also we have to find the largest square
    // TODO: implement with accumulation and overflow checking
    for (auto px = xd, end = px + n * xinc, py = yd; px != end; px += xinc, py += yinc) {
        c += (*px - medx) * (*py - medy) / N;
    }

    return c;
}

template <class T, class Idx>
T cov_impl(const T* x, Idx xstride, const T* y, Idx ystride, Idx n) noexcept {
    auto medx = mean_impl(x, xstride, n);
    auto medy = mean_impl(y, ystride, n);
    return cov_impl(x, xstride, y, ystride, n, medx, medy);
}

template <class T, class Idx>
T cov(const T* px, const T* py, Idx n, T medx, T medy) noexcept {
    auto stride = (Idx)sizeof(T);
    return cov_impl(px, stride, py, stride, n, medx, medy);
}

template <class T, class Idx>
T cov(const T* x, const T* y, Idx n) noexcept {
    auto stride = (Idx)sizeof(T);
    auto medx = mean_impl(x, stride, n);
    auto medy = mean_impl(y, stride, n);
    return cov_impl(x, stride, y, stride, n, medx, medy);
}



//
// Build covariance matrix
//


template <class T, class Idx>
Mtx2<T> cov_mtx_impl(const T* x, Idx xstride, const T* y, Idx ystride, Idx n) noexcept
{
    Mtx2<T> m;

    // Build the right upper triangle of the matrix
    auto medx = mean_impl(x, xstride, n);
    auto medy = mean_impl(y, ystride, n);

    m.a[0][0] = cov_impl(x, xstride, x, xstride, n, medx, medx);
    m.a[0][1] = cov_impl(x, xstride, y, ystride, n, medx, medy);
    m.a[1][1] = cov_impl(y, ystride, y, ystride, n, medy, medy);

    // Since the matrix is symmetric, just copy the upper triangle to the lower
    m.a[1][0] = m.a[0][1];

    return m;
}

template <class T, class Idx>
Mtx2<T> cov_mtx(const T* x, const T* y, Idx n) noexcept {
    auto stride = sizeof(T);
    return cov_mtx_impl(x, stride, y, stride, n);
}


}  // namespace


