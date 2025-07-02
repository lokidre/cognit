/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

/*
        General Linear Least Squares Method
*/

#include "../mtx/mtx_svd.hpp"

namespace cognit {

/*

    F *phi - is M array of pointers to funtions phi of argument from x

    The solution will be placed into x

    buffer has to be of size: MxN + M + MxN + NxN + MxN
*/

template <class T, class P, class F>
void lsmg(P data, int m, F* phi, int n, T* x, T* buffer)
{
    // First build matrix A
    auto am = buffer;   // A matrix: MxN
    auto bm = am + m*n;	// b vector: M
    auto um = bm + m;	// U matrix: MxN
    auto vm = um + n*n;	// V matrix: NxN
    auto bb = vm + m*n;  // U buffer: MxN

    auto p = data;

    auto a = am;
    auto b = bm;

    for (int i = 0; i < m; ++i, ++p, ++b) {
        for (int j = 0; j < n; ++j, ++a) {
            *a = phi[j](p->x);
        }
        *b = p->y;
    }

    // now solve equation using SVD
    svd_solve(am, bm, m, n, x, um, vm, bb);
}

}  // namespace cognit

