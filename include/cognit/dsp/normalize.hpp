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



// needed move somewhere else
template <typename type>
void dot(type* a, type* b, int length, type* c) noexcept
{
    for (int i = 0; i < length; i++, a++, b++, c++)
        *c = (*a) * (*b);
}

// needed to move somewhere else
template <typename src_data_type, typename dst_data_type>
void convert_buffer(const src_data_type* src, dst_data_type* dst, int length) noexcept
{
    for (int i = 0; i < length; ++i, ++src, ++dst)
        *dst = (dst_data_type)*src;
}


// needed to move somewhere else
template <typename data_type>
void subtract(data_type* dst, data_type* src, int total) noexcept
{
    data_type* s=src, * d=dst;
    for (int i = 0; i < total; ++i, ++s, ++d)
        *d -= *s;
}


template <class T, class U, class W, class X>
void normalize(const T* src, U* dst, const int length, W min_val, X max_val) noexcept
{
    T smin = src[0], smax = src[0];
    int i;
    const T* ps;
    U* pd;

    ps = src;
    for (i = 0; i < length; ++i, ++ps) {
        if (*ps < smin) 
            smin = *ps;
        if (*ps > smax) 
            smax = *ps;
    }

    if (smax == smin) {
        convert_buffer(src, dst, length);
        return;
    }

    T scale = (max_val - min_val) / (smax - smin);
    U umin_val = U(min_val);
    U umax_val = U(max_val);

    ps = src, pd = dst;
    for (i = 0; i < length; ++i, ++ps, ++pd) {
        //*pd = U(( *ps - smin ) * ( max_val - min_val ) / (smax - smin)) ;
        *pd = U((*ps-smin) * scale);
        if (*pd < umin_val)
            *pd = umin_val;
        if (*pd > max_val)
            *pd = umax_val;
    }
}


template <class T, class U, class W, class X>
void normalize_int(const T* src, U* dst, int length, W min_val, X max_val) noexcept
{
    T smin, smax;

    int i;
    const T* ps;
    U* pd;

    smin = smax = *src;

    ps = src;
    for (i = 0; i < length; ++i, ++ps) {
        if (*ps < smin) 
            smin = *ps;
        if (*ps > smax) 
            smax = *ps;
    }

    if (smax == smin)
        return;

    //scale = ( max_val - min_val ) / ( smax - smin ) ;

    ps = src, pd = dst;
    for (i = 0; i < length; ++i, ++ps, ++pd)
        *pd = U((*ps - smin) * (max_val - min_val) / (smax - smin));
}



template <typename src_data_type, typename dst_data_type, typename param_type>
void normalize_bound(src_data_type* src, dst_data_type* dst,
    int width, int height,
    int bound,
    param_type min_val, param_type max_val) noexcept

{
    // needed optimize

    param_type scale = 0;
    auto min = (param_type)src[bound*width+bound];
    auto max = (param_type)src[bound*width+bound];
    int i, j;
    src_data_type* ps;
    dst_data_type* pd;
    ps = src;
    for (j = bound; j < height-bound-1; j++) {
        for (i = bound; i < width-bound-1; i++, ps++) {
            ps = &src[(j)*height+i];
            if (((param_type)*ps) < min) 
                min = (param_type)*ps;
            if (((param_type)*ps) > max
                ) max = (param_type)*ps;
        }
    }

    if (max == min)
        return;

    scale = (max_val - min_val) / (max - min);

    for (j = bound; j < height-bound-1; j++) {
        for (i = bound; i < width-bound-1; i++) {
            ps = &src[(j)*height+i];
            pd = &dst[(j)*height+i];
            *pd = (dst_data_type)((*ps - min) * scale);
        }
    }

    //ps = src, pd = dst ;
    //for ( i = 0 ; i < length ; i++, ps++, pd++ )
    //  *pd = (dst_data_type)(( *ps - min ) * scale) ;

    return;
}


template <class T, class W>
void normalize(T* data, int length, W val) noexcept {
    normalize(data, data, length, W(0), val);
}

template <class T, class W>
void normalize_int(T* p, int length, W val) noexcept {
    normalize_int(p, p, length, W(0), val);
}

template <class T, class W, class X>
void normalize(T* data, int length, W min_val, X max_val) noexcept {
    normalize(data, data, length, min_val, max_val);
}

template <class T, class W, class X>
void normalize_int(T* data, int length, W min_val, X max_val) noexcept {
    normalize_int(data, data, length, min_val, max_val);
}


}  // namespace


