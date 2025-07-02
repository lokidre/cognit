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

Matrix formatting

TODO: options, different styles: csv, etc.

#endif

#include "../mtx.hpp"

#include <apeal/str/format.hpp>
#include <apeal/format/str_format_components.hpp>
#include <apeal/strview.hpp>

namespace cognit {


// Formatting matrix in Matlab style: "[1 2; 3 4]"
template <class S, class F, class T>
void mtx_str_fmt_it_matlab(S& str, F* f, F fend, const T* it, Index M, Index N) noexcept
{
    auto p = it;

    str += '[';

    for (Index j = 0; j < N; ++j) {
        if (j) {
            str += ';';
            str += ' ';
        }

        for (Index i = 0; i < M; ++i, ++p) {
            if (i) {
                str += ' ';
            }
            apl::str_format_append_it_body(str, f, fend, *p);
        }
    }

    str += ']';
}


template <class S, class F, class T>
void mtx_str_fmt_it(S& str, F* f, F fend, const T* it, Index M, Index N) noexcept {
    mtx_str_fmt_it_matlab(str, f, fend, it, M, N);
}


template <class S, class F, class M>
void mtx_str_fmt(S& str, F* f, F fend, const M& m) noexcept {
    mtx_str_fmt_it(str, f, fend, m.data(), m.M, m.N);
}


template <class F = char, class M>
String mtx_fmt(const M& m, StrView fmt = "%g") noexcept {
    String s;
    auto f = fmt.data();
    mtx_str_fmt(s, &f, fmt.data() + fmt.size(), m);
    return s;
}


template <class S, class F, class M>
void str_format_mtx(S& str, F* fmt, F fend, const M& m) noexcept {
    auto fcomp = apl::str_format_component(str, fmt, fend);
    auto fbegin = fcomp.first.begin();
    mtx_str_fmt(str, &fbegin, fcomp.first.end(), m);
}


}  // namespace cognit


//
// Specializations
//
namespace apl {

template <class S, class F, class T>
void str_format_type(S& str, F* f, F fend, const cognit::Mtx2<T>& u) noexcept {
    cognit::str_format_mtx(str, f, fend, u);
}

template <class S, class F, class T>
void str_format_type(S& str, F* f, F fend, const cognit::Mtx3<T>& u) noexcept {
    cognit::str_format_mtx(str, f, fend, u);
}

template <class S, class F, class T>
void str_format_type(S& str, F* f, F fend, const cognit::Mtx4<T>& u) noexcept {
    cognit::str_format_mtx(str, f, fend, u);
}

template <class S, class F, class T>
void str_format_type(S& str, F* f, F fend, const cognit::Mtx<T>& u) noexcept {
    cognit::str_format_mtx(str, f, fend, u);
}


}  // namespace apl

//#include <apeal/str/format.hpp>
