/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once
//
//	Conversion of matrices from one representation to another
//
// TODO: add dimension checks

#include "../mtx.hpp"

namespace cognit {


template <class AT, class BT>
void mtx_convert(const Mtx<AT>& a, Mtx2<BT>& b) noexcept
{
    mtx_copy_it(a.begin(), a.end(), b.begin());
}

template <class AT, class T>
auto mtx_convert(const Mtx<AT>& a, Mtx3<T>& b) noexcept
{
    mtx_copy_it(a.begin(), a.end(), b.begin());
}

template <class AT, class T>
void mtx_convert(const Mtx<AT>& a, Mtx4<T>& b) noexcept
{
    mtx_copy_it(a.begin(), a.end(), b.begin());
}

/*
template <class AT, class BT, int N>
void mtx_convert(const Mtx<AT>& a, MtxN<BT, N>& b) noexcept
{
    mtx_copy_it(a.begin(), a.end(), b.begin());
}
*/

} // namespace cognit
