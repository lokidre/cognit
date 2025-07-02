/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#if 0
Inverse of Matrix

The inverse is defined only for square matrices
The inverse of a square matrix A is matrix A~such that

A.A~= A~.A = I

where I is identity matrix

#endif


#include "mtx_gauss_jordan.hpp"
#include "mtx_det.hpp"

namespace cognit {



// Mtx2<type>
// for 2x2 matrices the inverse is straightforward
template <class T>
bool mtx_inv(Mtx2<T>& a)
{
    auto d = a.a[0][0]*a.a[1][1] - a.a[0][1]*a.a[1][0];  // finding determinant

    if (tiny(d))  // matrix is singular
        return false;

    T t;

    t = a.a[0][0], a.a[0][0] = a.a[1][1], a.a[1][1] = t;  // swap a00 and a11

    a.a[0][0] /= d, a.a[1][1] /= d;

    a.a[0][1] = -a.a[0][1] / d;
    a.a[1][0] = -a.a[1][0] / d;

    return true;
}


template <class T>
bool mtx_inv(const Mtx2<T>& a, Mtx2<T>& b)
{
    auto d = a.a[0][0]*a.a[1][1] - a.a[0][1]*a.a[1][0];

    if (tiny(d))
        return false;

    b.a[0][0] = a.a[1][1] / d;
    b.a[1][1] = a.a[0][0] / d;

    b.a[0][1] = -a.a[0][1] / d;
    b.a[1][0] = -a.a[1][0] / d;

    return true;
}


// Mtx3<type>
// for 3x3 matrix the inverse is straightforward too

template <class T>
bool mtx_inv(const Mtx3<T>& a, Mtx3<T>& b)
{
    // For 3x3 methods the direct method is faster and simpler
    T det = mtx_det(a);

    if (tiny(det))
        return false;

    b.a[0][0] = (a.a[1][1]*a.a[2][2] - a.a[1][2]*a.a[2][1])/det;
    b.a[0][1] = (a.a[0][2]*a.a[2][1] - a.a[0][1]*a.a[2][2])/det;
    b.a[0][2] = (a.a[0][1]*a.a[1][2] - a.a[0][2]*a.a[1][1])/det;
    b.a[1][0] = (a.a[1][2]*a.a[2][0] - a.a[1][0]*a.a[2][2])/det;
    b.a[1][1] = (a.a[0][0]*a.a[2][2] - a.a[0][2]*a.a[2][0])/det;
    b.a[1][2] = (a.a[0][2]*a.a[1][0] - a.a[0][0]*a.a[1][2])/det;
    b.a[2][0] = (a.a[1][0]*a.a[2][1] - a.a[1][1]*a.a[2][0])/det;
    b.a[2][1] = (a.a[0][1]*a.a[2][0] - a.a[0][0]*a.a[2][1])/det;
    b.a[2][2] = (a.a[0][0]*a.a[1][1] - a.a[0][1]*a.a[1][0])/det;

    return true;
}




// remarks: not optimal - extra copying
template <typename type>
bool mtx_inv(Mtx3<type>& a)
{
    // For 3x3 methods the direct method is faster and simpler

    Mtx3<type> b;
    if (!mtx_inv(a, b))
        return false;
    a = b;
    return true;
}


// Inverse for 4x4 matrix.
// Uses Gauss-Jordan elimination technique with partial pivoting

// Remarks: not optimal - extra copying
template <typename type>
bool mtx_inv(Mtx4<type>& a, Mtx4<type>& d)
{
    Mtx4<type> buff;
    d = a;
    return mtx_gauss_jordan_inverse_partial_pivot_basic((type*)d.a, 4, (type*)&buff.a);
}

template <typename type>
bool mtx_inv(Mtx4<type>& a)
{
    Mtx4<type> buff;
    return mtx_gauss_jordan_inverse_partial_pivot_basic((type*)a.a, 4, (type*)&buff.a);
}

// MtxN<type,n>
// notes: extra copying
template <typename type, int n>
bool mtx_inv(MtxN<type, n>& a, MtxN<type, n>& d)
{
    MtxN<type, n> buff;
    d = a;
    return mtx_gauss_jordan_inverse_partial_pivot_basic((type*)d.a, n, (type*)&buff.a);
}

template <typename type, int n>
bool mtx_inv(MtxN<type, n>& a)
{
    MtxN<type, n> buff;
    return mtx_gauss_jordan_inverse_partial_pivot_basic((type*)a.a, n, (type*)&buff.a);
}


// Mtx<type>
// Application can provide buffer of size = n*sizeof(type)
template <typename type>
bool mtx_inv(Mtx<type>& a, Mtx<type>& d, type* buffer=0)
{
    // the matrix has to be square
    if (a.M != a.N)
        return false;

    // allocate buffer (if neccessary)
    Mtx<type> b;
    if (buffer == 0)
        b.setup(a.M, a.N), buffer = b.p;

    d.copy(a);

    return mtx_gauss_jordan_inverse_partial_pivot_basic(d.p, d.M, buffer);
}

template <typename type>
bool mtx_inv(Mtx<type>& a, type* buffer=0)
{
    // the matrix has to be square
    if (a.M != a.N)
        return false;

    // allocate buffer (if neccessary)
    Mtx<type> b;
    if (buffer == 0)
        b.setup(a.M, a.N), buffer = b.p;

    return mtx_gauss_jordan_inverse_partial_pivot_basic(a.p, a.M, buffer);
}

}

