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


template <class U, class V>
void median_3(const U* in_data, V* out_data, int length)
{
    const int total = length - 1;

    // leave first and last elements intact
    *out_data = *in_data;
    out_data[total] = in_data[total];

    const U* s0, * s1, * s2;

    s0 = &in_data[1], s1 = s0+1, s2 = s1+1;
    V* d = &out_data[1];

    for (int i = 1; i < total; ++i, ++s0, ++s1, ++s2, ++d) {
        if (*s0 < *s1)
            if (*s0 > *s2)
                *d = *s0;
            else
                *d = *s1 < *s2 ? *s1 : *s2;
        else
            if (*s0 < *s2)
                *d = *s0;
            else
                *d = *s1 < *s2 ? *s2 : *s1;
    }
}


template <class data_type>
void median_sort_5(const data_type* s, data_type* d)
{
    if (s[0] < s[1])
        d[0] = s[0], d[1] = s[1];
    else
        d[0] = s[1], d[1] = s[0];

    if (s[2] < d[0])
        d[2] = d[1], d[1] = d[0], d[0] = s[2];
    else if (s[2] < d[1])
        d[2] = d[1], d[1] = s[2];
    else
        d[2] = s[2];

    if (s[3] < d[0])
        d[3] = d[2], d[2] = d[1], d[1] = d[0], d[0] = s[3];
    else if (s[3] < d[1])
        d[3] = d[2], d[2] = d[1], d[1] = s[3];
    else if (s[3] < d[2])
        d[3] = d[2], d[2] = s[3];
    else
        d[3] = s[3];

    if (s[4] < d[0])
        d[4] = d[3], d[3] = d[2], d[2] = d[1], d[1] = d[0], d[0] = s[4];
    else if (s[4] < d[1])
        d[4] = d[3], d[3] = d[2], d[2] = d[1], d[1] = s[4];
    else if (s[4] < d[2])
        d[4] = d[3], d[3] = d[2], d[2] = s[4];
    else if (s[4] < d[3])
        d[4] = d[3], d[3] = s[4];
    else
        d[4] = s[4];
}


template <class data_type>
void median_5(const data_type* in_data, data_type* out_data, int length)
{
    int total = length - 2;
    data_type* d, * b;
    data_type buffer[5];

    const data_type* s = &in_data[2];
    d = &out_data[2];
    b = &buffer[3];

    for (int i = 2; i < total; i++, s++, d++) {
        median_sort_5(s, buffer);
        *d = *b;
    }

    out_data[0] = out_data[1] = out_data[2];
    out_data[length-1] = out_data[length-2] = out_data[length-3];
}



template <typename data_type>
data_type median_quick_select(data_type* arr, int n)
{
    int low, high;
    int median;
    int middle, ll, hh;
    data_type t;

#define swap_elem(_u,_v) (t=(_u),(_u)=(_v),(_v)=t)

    low = 0, high = n-1, median = (low + high) / 2;
    for (;;) {
        if (high <= low)  // one element
            return arr[median];

        if (high == low + 1) {  // two elements
            if (arr[low] > arr[high])
                swap_elem(arr[low], arr[high]);
            return arr[median];
        }

        // Find median of low, middle and high items; swap into position low
        middle = (low + high) / 2;
        if (arr[middle] > arr[high])
            swap_elem(arr[middle], arr[high]);
        if (arr[low] > arr[high])
            swap_elem(arr[low], arr[high]);
        if (arr[middle] > arr[low])
            swap_elem(arr[middle], arr[low]);

        // Swap low item (now in position middle) into position (low+1)
        swap_elem(arr[middle], arr[low+1]);

        // Nibble from each end towards middle, swapping items when stuck
        ll = low + 1, hh = high;
        for (;;) {
            do
                ll++;
            while (arr[low] > arr[ll]);
            do
                hh--;
            while (arr[hh] > arr[low]);
            if (hh < ll)
                break;
            swap_elem(arr[ll], arr[hh]);
        }

        // Swap middle item (in position low) back into correct position
        swap_elem(arr[low], arr[hh]);

        // Re-set active partition
        if (hh <= median)
            low = ll;
        if (hh >= median)
            high = hh - 1;
    }

#undef swap_elem
}


template <typename src_data_type, typename dst_data_type>
void median_3x3(const src_data_type* in_data, dst_data_type* out_data, int width, int height)
{
    int i, j;
    src_data_type buffer[3*3];
    const src_data_type* d, * d1, * d2, * d3, * id;
    dst_data_type* od;

    id = in_data, od = out_data;

    id += width;
    od += width;

    for (j = 1; j < height - 1; j++, id += width) {
        d1 = id, d2 = d1+width, d3=d2+width;

        for (i = 1, od++; i < width - 1; i++, d1++, d2++, d3++, od++) {
            d=d1, buffer[0] = *d++, buffer[1] = *d++, buffer[2] = *d++;
            d=d2, buffer[3] = *d++, buffer[4] = *d++, buffer[5] = *d++;
            d=d3, buffer[6] = *d++, buffer[7] = *d++, buffer[8] = *d++;

            *od = median_quick_select(buffer, 9);
        }

        od++;
    }
}



//
// Requires buffer aperture*aperture size
//

template <typename src_data_type, typename dst_data_type>
void median_nxn(const src_data_type* in_data, dst_data_type* out_data, int width, int height, int aperture, dst_data_type* buffer)
{
    int begin = aperture/2;
    int width_end = width - aperture/2;
    int height_end = height - aperture/2;
    int aperture_half = aperture/2;
    int aperture_sqr = aperture*aperture;
    int i, j, k, l;

    dst_data_type* od;
    dst_data_type* bd;
    const src_data_type* id;

    od = out_data;

    od += aperture_half*width;

    for (j = begin; j < height_end; j++) {
        od += aperture_half;
        for (i = begin; i < width_end; i++, od++) {
            bd = buffer;

            for (k = 0; k < aperture; k++) {
                id = &in_data[(j-aperture_half+k)*width+(i-aperture_half)];
                for (l = 0; l < aperture; l++, bd++, id++)
                    *bd = *id;
            }

            *od = median_quick_select(buffer, aperture_sqr);
        }
        od += aperture_half;
    }
}



//
// requires buffer of aperture size
//

template <class T, class U>
void median_n(const T* in_data, U* out_data, int length, int aperture, U* buffer) noexcept
{
    auto begin = aperture/2;
    auto aperture_half = aperture/2;

    U* bd;

    const T* id = in_data, * p;
    U* od = out_data + aperture_half;

    for (int i = aperture; i < length; ++i, ++od, ++id) {
        bd = buffer;
        p = id;

        for (int k = 0; k < aperture; ++k, ++bd, ++p) {
            *bd = *p;
        }

        *od = median_quick_select(buffer, aperture);
    }

    // end and beginning
    // boundary - needed better
    U v1 = *(out_data + aperture_half), v2 = *(out_data + length - aperture_half - 2);
    U* d1 = out_data, * d2 = out_data + length - aperture_half - 1;
    for (int i = 0; i < aperture_half; ++i, ++d1, ++d2) {
        *d1 = v1, * d2 = v2;
    }
    *d2 = v2;  // one more for the right end
}

template <class src_data_type, class dst_data_type>
void median_n_y(const src_data_type* in_data, dst_data_type* out_data, int width, int height, int aperture, dst_data_type* buffer) noexcept
{
    int begin = aperture/2;
    const int aperture_half = aperture/2;


    dst_data_type* bd;

    const src_data_type* id = in_data, * p;
    dst_data_type* od = out_data + aperture_half*width;

    for (int i = aperture; i < height; ++i, od += width, id += width) {
        bd = buffer;
        p = id;

        for (int k = 0; k < aperture; ++k, ++bd, p += width) {
            *bd = *p;
        }

        *od = median_quick_select(buffer, aperture);
    }
}


}  // namespace

