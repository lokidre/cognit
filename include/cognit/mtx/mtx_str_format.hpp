/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

//#include <apeal/str_format.hpp>

#include "./mtx_format.hpp"


namespace apl {

// TODO: in the future implement concepts

// Matrix 2x2
template <class S, class F, class T>
void str_format_type(S& str, F& fmt, const F& fend, const ::cognit::Mtx2<T>& m) {
    ::cognit::str_format_mtx(str, fmt, fend, m);
    //str_format_matrix(str, fmt, fmtEnd, m.M, m.N, m.data());
}


// Matrix 3x3
template <class S, class F, class T>
void str_format_type(S& str, F& fmt, const F& fend, const ::cognit::Mtx3<T>& m) {
    ::cognit::str_format_mtx(str, fmt, fend, m);
    //str_format_matrix(str, fmt, fmtEnd, m.M, m.N, m.data());
}


// Matrix 4x4
template <class S, class F, class T>
void str_format_type(S& str, F& fmt, const F& fend, const ::cognit::Mtx4<T>& m) {
    ::cognit::str_format_mtx(str, fmt, fend, m);
    //str_format_matrix(str, fmt, fmtEnd, m.M, m.N, m.data());
}

}  // namespace apeal

