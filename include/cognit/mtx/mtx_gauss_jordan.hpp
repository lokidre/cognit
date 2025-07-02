/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#if 0  //Header

Gauss elimination related algorithms

#endif

// TODO: determinant not calculate correctly


namespace cognit {

//
// General function for computing the inverse of square nxn matrix
// Partial pivoting
//

// Computation of the inverse of A without pivoting.
// The inverse is stored in D matrix. 
// Matrix `A' is replaced by identity matrix (eliminated)
// This implementation is just for experiments, 
// without pivoting the method is very unstable
template <class T, class Idx>
bool mtx_gauss_jordan_inverse_basic(T* a, Idx n, T* d) noexcept
{
    //int i, j, k;  // index variables
    auto tot = n * n;
    //T* pa, * pd;
    T zero = T(0), one = T(1);

    // make D unit
    auto pd = d;
    for (Idx j = 0, pd = d; j < n; j++)
        for (Idx i = 0; i < n; i++, pd++)
            *pd = T(i == j ? 1 : 0);

    // main cycle for columns of A matrix
    for (Idx k = 0; k < n; k++) {
        // make current element 1
        auto aa = a[k * n + k];

        if (aa == zero)  // matrix is singular
            return false;

        auto aainv = one / aa;

        for (Idx i = 0; i < n; i++) {
            a[k * n + i] *= aainv;
            d[k * n + i] *= aainv;
        }

        // make all rows zero
        for (Idx j = 0; j < n; j++) {
            if (j == k)
                continue;

            auto aa = a[j * n + k];

            for (Idx i = 0; i < n; i++) {
                a[j * n + i] -= a[k * n + i] * aa;
                d[j * n + i] -= d[k * n + i] * aa;
            }
        }
    }

    return true;
}


// same function as before, but just changes the first matrix
// again without pivoting
template <typename type>
bool mtx_gauss_jordan_inverse_basic(type* a, int n) noexcept
{
    int i, j, k;  // index variables
    int tot = n * n;
    type zero = type(0);

    // main cycle for columns of A matrix
    for (k = 0; k < n; k++) {
        // make current element 1
        type aa = a[k * n + k];

        if (aa == type(0))
            return false;

        type aainv = type(1) / aa;

        a[k * n + k] = type(1);
        for (i = 0; i < n; i++)
            a[k * n + i] *= aainv;

        // make all rows zero
        for (j = 0; j < n; j++) {
            if (j == k)
                continue;

            type aa = a[j * n + k];
            a[j * n + k] = zero;

            for (i = 0; i < n; i++)
                a[j * n + i] -= a[k * n + i] * aa;
        }
    }


    return true;
}


//
// Replaces A with its inverse using Gauss-Jordan elimination techinique
// With partial pivoting. partial pivoting is usually enough for most cases
// Needs a buffer for storing information about interchanged rows
//
// This is optimized version
// needed - do not exchange rows but indexes
template <typename type>
bool mtx_gauss_jordan_inverse_partial_pivot_basic(type* a, int n, type* buff) noexcept
{
    int i, j, k;  // index variables
    int tot = n * n;
    char* b = (char*)buff;
    type tmp, one = type(1), zero = type(0);

    type *pa, *pp, aa;

    // main cycle for columns of A matrix
    for (k = 0; k < n; k++) {

        // for current column find the largest element
        int ipiv = 0;
        type piv = a[k];
        for (j = 1, pa = &a[k * n + 1]; j < n; j++, pa++) {
            if ((tmp = abs(*pa)) > piv)
                piv = tmp, ipiv = j;
        }

        // interchange two rows
        b[k] = ipiv;
        if (ipiv != k)
            for (i = 0, pa = &a[k * n], pp = &a[ipiv * n]; i < n; i++, pa++, pp++)
                tmp = *pa, *pa = *pp, *pp = tmp;

        // make current element 1
        aa = a[k * n + k];

        if (aa == zero)
            return false;

        type aainv = one / aa;

        a[k * n + k] = type(1);
        for (i = 0, pa = &a[k * n]; i < n; i++, pa++)
            *pa *= aainv;

        // make all rows zero
        for (j = 0; j < n; j++) {
            if (j == k)
                continue;

            aa = a[j * n + k], a[j * n + k] = zero;

            for (i = 0, pa = &a[j * n], pp = &a[k * n]; i < n; i++, pa++, pp++)
                *pa -= *pp * aa;
        }
    }

    // restoring the rows in the reverse order
    for (k = n - 1; k >= 0; k--)
        if (b[k] != k)
            for (i = 0, pa = &a[k], pp = &a[b[k]]; i < n; i++, pa += n, pp += n)
                tmp = *pa, *pa = *pp, *pp = tmp;

    return true;
}


//
// Calculating determinant of square matrix
// using Gaussian elimination with partial pivoting
// requires buffer B which can be equal to A (then A will be destroyed)
// requires buffer idx[n] for storing row interchanges (to avoid real interchanges)
//
template <class T>
T mtx_det_gauss_partial_pivot(const T* aa, int n, T* a) noexcept
{
    int i, j, k;
    int ipiv;
    T piv, tmp;
    const T zero = T(0);
    T det = T(1);
    T *pa, *pb, *pc, *ppiv;
    int n1 = n + 1;

    if (a != aa)  // needed to work around classes as types
        std::memcpy(a, aa, n * n * sizeof(T));


    for (j = 0, ppiv = a; j < n; ++j, ppiv += n1) {  // for all rows

        // pivoting - find the largest element in column below
        ipiv = j, piv = abs(*ppiv);

        for (i = j + 1, pa = &a[i * n + j]; i < n; i++, pa += n)
            if ((tmp = abs(*pa)) > piv)
                piv = tmp, ipiv = i;

        if (piv == zero)  // if the largest element is zero then
            return zero;  // the matrix is singular, so det == 0


        // interchange two rows
        if (ipiv != j) {
            if (j > 0) {
                // we can use the first row as a buffer,
                // since we don't need the values anymore
                // but we can use memcpy routine which is faster
                int siz = (n - j) * sizeof(T);
                // needed to work around the case with class as types
                memcpy(&a[j], &a[j * n + j], siz);
                memcpy(&a[j * n + j], &a[ipiv * n + j], siz);
                memcpy(&a[ipiv * n + j], &a[j], siz);
            } else
                for (k = j, pa = &a[j * n + k], pb = &a[ipiv * n + k]; k < n;
                     ++k, ++pa, ++pb)
                    tmp = *pa, *pa = *pb, *pb = tmp;
            det = -det;  // change the sign of determinant
        }

        // linearly combine the rows
        for (i = j + 1, pa = &a[i * n + j]; i < n; i++, pa += n) {
            tmp = *pa / *ppiv;
            for (k = j + 1, pb = &a[i * n + k], pc = &a[j * n + k]; k < n;
                 k++, pb++, pc++)
                *pb -= *pc * tmp;
        }
    }

    // finally calculate the determinant
    // the product of diagonal elements

    // to avoid overflows - scale the diagonal by its largest element
    T scale = abs(*a);
    for (i = 0, pa = a; i < n; ++i, pa += n1)
        if ((tmp = abs(*pa)) > scale)
            scale = tmp;

    for (i = 0, pa = a; i < n; ++i, pa += n1)
        *pa /= scale;

    for (i = 0, pa = a; i < n; ++i, pa += n1)
        det *= *pa;

    return det * scale;
}



}  // namespace cognit
