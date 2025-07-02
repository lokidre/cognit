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

Matrix determinant

TODO: fix det def and Gauss Jordan

#endif

#include "../func.hpp"

#include "./mtx_det_core.hpp"
#include "./mtx_gauss_jordan.hpp"


namespace cognit {

// Determinant of Matrix


// For 2x2 and 3x3 matrices determinant is easier by definition
template <class T>
T mtx_det(const Mtx2<T>& m) noexcept
{
    return m.a[0][0]*m.a[1][1] - m.a[0][1]*m.a[1][0];
}


template <class T>
T mtx_det(const Mtx3<T>& m) noexcept
{
    return m.a[0][0] * (m.a[1][1]*m.a[2][2] - m.a[1][2]*m.a[2][1])
         + m.a[1][0] * (m.a[0][2]*m.a[2][1] - m.a[0][1]*m.a[2][2])
         + m.a[2][0] * (m.a[0][1]*m.a[1][2] - m.a[0][2]*m.a[1][1]);
}


template <class T>
T mtx_det(const Mtx4<T>& a) noexcept
{
    Mtx4<T> b;
    return mtx_det_gauss_partial_pivot((T*)a.a, 4, (T*)b.a);
}


template <class T, int n>
T mtx_det(const MtxN<T, n>& a, MtxN<T, n>& b) noexcept
{
    return mtx_det_gauss_partial_pivot((T*)a.a, n, (T*)b.a);
}

// this version allocates temporary local buffer for matrix
// note! may be dangerous for stack overflows, but useful
template <class T, int n>
T mtx_det(const MtxN<T, n>& a) noexcept
{
    MtxN<T, n> b;
    return mtx_det_gauss_partial_pivot((T*)a.a, n, (T*)b.a);
}


template <class T>
T mtx_det(const Mtx<T>& a, Mtx<T>& b) noexcept
{
    if (a.M != a.N)  // do we have det for non-square matrices?
        return T(0);

    b.resize(a.M, a.N);

    return mtx_det_gauss_partial_pivot(a.data(), a.M, b.data());
}



// allocates local matrix, might be dangerous 
// but useful for not so big matrices
template <class T>
T mtx_det(const Mtx<T>& a)
{
    if (a.M != a.N)
        return T(0);

    Mtx<T> b;
    b.resize(a.M, a.N);

    return mtx_det(a, b);
}


}  // namespace


