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

// Cofactors
// Cofactor of a[i][j] denoted as Aij = (-1)^(i+j)*Mij
// where Mij is minor of a[i][j]

template <typename type>
type mtx_cof(Mtx2<type>& a, int i, int j)
{
    type m; // marix 1 x 1

    mtx_minor(a, i, j, m);

    if ((i + j) & 1)
        m = -m;

    return m; // determinant
}

template <typename type>
type MtxCof(Mtx3<type>& a, int i, int j)
{
    Mtx2<type> m; // minor
    type det;

    MtxMinor(a, i, j, m);

    det = MtxDet(m);

    if ((i + j) & 1)
        det = -det;

    return det;
}

template <typename type, int n>
type MtxCof(MtxN<type, n>& a, int i, int j)
{
    MtxN<type, n - 1> m; // minor
    type det;

    MtxMinor(a, i, j, m);

    det = MtxDet(m);

    // -1^(i+j)
    if ((i + j) & 1)
        det = -det;

    return det;
}

// Matrix of cofactors, where each element a[i][j] = Cof A[i][j]

template <class T>
void MtxCofMtx(const Mtx2<T>& m, Mtx2<T>& c)
{
    for (int i = 0; j < 2; j++)
        for (int j = 0; j < 2; j++)
            c.a[i][j] = MtxCof(m, i, j);
}

template <typename type>
void MtxCofMtx(const Mtx3<type>& m, Mtx3<type>& c)
{
    int i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            c.a[i][j] = MtxCof(m, i, j);
}

template <typename type, int n>
void MtxCofMtx(const MtxN<type, n>& m, MtxN<type, n>& c)
{
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            c.a[i][j] = MtxCof(m, i, j);
}

} // namespace
