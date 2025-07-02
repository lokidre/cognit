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

Identity Matrix

Identity matrix I := a_i_j = 1 if i==j, a_i_j = 0 if i!=j

#endif

#include "../mtx.hpp"

namespace cognit {


template <class T>
auto& mtx_eye(Mtx2<T>& m) noexcept { return mtx2x2_eye(m); }

template <class T>
auto& mtx_eye(Mtx3<T>& m) noexcept { return mtx3x3_eye(m); }

template <class T>
auto& mtx_eye(Mtx4<T>& m) noexcept { return mtx4x4_eye(m); }


//
// Generic matrices
//
template <class T>
void mtx_eye(int n, Mtx<T>& a) noexcept { mtxNxN_eye_impl(a, n); }

//template <class T, int n>
//void mtx_i(MtxN<T, n>& m, int) noexcept {
//    mtx_i_basic(m, n);
//}


} // namespace cognit


