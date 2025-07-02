/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
// Implementation of identity matrix generation

namespace cognit {

//
//
template <class iterator>
void mtxNxN_eye_it(iterator a, int n) noexcept
{
    auto d = a;
    auto total = n*n;
    auto n1 = n+1;
    int i;

    for (i = 0; i < total; ++i, ++a)
        *a = 0;

    for (i = 0; i < n; ++i, d += n1)
        *d = 1;
}


template <class M>
M& mtxNxN_eye(M& a, int n) noexcept
{
    a.setup(n, n);

    for (auto aIt = a.begin(), aEnd = a.end(); aIt != aEnd; ++aIt)
        *aIt = 0;

    auto aIt = a.begin();
    int n1 = n+1;

    for (int i = 0; i < n; ++i, aIt += n1)
        *aIt = 1;

    return a;
}


//
// Simple cases
//
template <class M>
M& mtx2x2_eye(M& m) noexcept
{
    m.a[0][0] = m.a[1][1] = 1;
    m.a[0][1] = m.a[1][0] = 0;
    return m;
}

template <class M>
M& mtx3x3_eye(M& m) noexcept
{
    m.a[0][0] = m.a[1][1] = m.a[2][2] = 1;

    m.a[0][1] = m.a[0][2] =
    m.a[1][0] = m.a[1][2] =
    m.a[2][0] = m.a[2][1] = 0;
    return m;
}

template <class M>
M& mtx4x4_eye(M& m) noexcept
{
    m.a[0][0] = m.a[1][1] = m.a[2][2] = m.a[3][3] = 1;

    m.a[0][1] = m.a[0][2] = m.a[0][3] =
    m.a[1][0] =             m.a[1][2] = m.a[1][3] =
    m.a[2][0] = m.a[2][1] =             m.a[2][3] =
    m.a[3][0] = m.a[3][1] = m.a[3][2] =             0;

    return m;
}

}  // namespace
