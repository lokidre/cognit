/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include "../mtx.hpp"

#include "./mtx_format.hpp"
#include "./mtx_parse.hpp"

namespace cognit {

//
// Main stream functions: read and write
//

/*
// Write stream
template <class Stream, class It>
Stream& mtx_stream_out_it(Stream &stream, It aIt, Index M, Index N)
{
    const auto nl = '\n';

    stream << '[' << nl;

    for (int i = 0; i < M; ++i) {
        stream << '[';
        auto first = true;
        for (int j = 0; j < N; ++j, ++aIt ) {
            if (!first)
                stream << ' ' << ',';
            else
                first = false;
            //stream.width(12) ;
            //stream << *pa << '\t' ;
        }
        stream << ']' << nl;
        //stream << '\n' ;
    }

    stream << ']' << nl;

    return stream;
}
*/

template <class Stream, class Matrix>
Stream& mtx_stream_out(Stream& stream, const Matrix& m) {
    stream << mtx_fmt(m);
    return stream;
    //return mtx_stream_out_it(stream, m.begin(), m.M, m.N);
}

template <class Stream>
struct StreamSource {
    StreamSource(Stream& stream): stream_{stream}{}

    String readLine() {
    }

private:
    Stream& stream_;
};

template <class Stream, class Matrix>
Stream& mtx_stream_in(Stream& stream, Matrix& m)
{
    StreamSource src{stream};
    mtx_parse(src, m);
    return stream;
}



/*
template <class stream_type, class real_type>
stream_type& __mtx_matrix_in(stream_type& stream, real_type* pa, const int m, const int n)
{
    const int tot = m*n;
    for (int i = 0; i < tot; ++i, ++pa)
        stream >> *pa;
    return stream;
}
*/


// Mtx2<type>
template <class T>
std::istream& operator >> (std::istream&& stream, Mtx2<T>& m) {
    return mtx_stream_in(stream, m);
}

template <class T>
std::ostream& operator << (std::ostream& stream, const Mtx2<T>& m) {
    return mtx_stream_out(stream, m);
}

// Mtx3<type>
template <class T>
std::istream& operator >> (std::istream& stream, Mtx3<T>& m) {
    return mtx_stream_in(stream, m);
}

template <class T>
std::ostream& operator << (std::ostream& stream, const Mtx3<T>& m) {
    return mtx_stream_out(stream, m);
}

// Mtx4<type>
template <class T>
std::istream& operator >> (std::istream& stream, Mtx4<T>& m) {
    return mtx_stream_in(stream, m);
}

template <class T>
std::ostream& operator << (std::ostream& stream, const Mtx4<T>& m) {
    return mtx_stream_out(stream, m);
}

/*
// MtxN<type,n>
template <class T, int N>
std::istream& operator >> (std::istream& stream, MtxN<T, N>& m) {
    return mtx_stream_in(stream, m);
}

template <class T, int N>
std::ostream& operator << (std::ostream& stream, const MtxN<T, N>& m) {
    return mtx_stream_out(stream, m);
}
*/

/*
// MtxMN<T,m,n>
template <class T, int M, int N>
std::istream& operator >> (std::istream& stream, MtxMN<T, M, N>& m) {
    return mtx_stream_in(stream, m);
}

template <class T, int M, int N>
std::ostream& operator << (std::ostream& stream, const MtxMN<T, M, N>& m) {
    return mtx_stream_out(stream, m);
}
*/


// Mtx<type>
template <class T>
std::istream& operator>>(std::istream& stream, Mtx<T>& m) {
    return mtx_stream_in(stream, m);
}

template <class T>
std::ostream& operator << (std::ostream& stream, const Mtx<T>& m) {
    return mtx_stream_out(stream, m);
}


}  // namespace  cognit


