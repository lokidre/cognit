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



//
// Calculates the histogram of input
//
// The data must be normalized to 0-255
// 
//
template <class iT>
void histogram(const iT begin, const iT end, int histo_width, int* histo, int* histo_image)
{
}



template <class iT, class image_type>
void histogram_equalize(const iT begin, const iT end, image_type* image)
{
    typedef float T;

    //
    // find histogram
    //
    //const int total = width * height ;
    const int histo_width = 256;

    // two buffers - for histogram and cumulative frequency	
    int histo_data[histo_width];  // histogram buffer
    memset(histo_data, 0, histo_width*sizeof(int));  // zero the data

    T cum_freq[256];
    memset(cum_freq, 0, histo_width*sizeof(T));

    int total = 0;   // meanwhile calculate total
    for (iT d = begin; d != end; ++d, ++total)
        histo_data[int(*d)]++;


    cum_freq[0] = T(histo_data[0]); //+ 0.5 ;
    T* p = cum_freq, * c = p+1;
    int* h = histo_data+1;
    for (int i = 1; i < histo_width; ++i, ++h, ++c, ++p) {
        *c = *h + *p;
    }


    // generate final image
    const T alpha = T(255) / total;
    image_type* img = image;

    for (iT d = begin; d != end; ++d, ++img) {
        *img = image_type(cum_freq[int(*d)] * alpha);
    }

}


//
// Histogram equalization with background (background is not touched)
//
template <class iT, class image_type>
void histogram_equalize_bk(const iT begin, const iT end, image_type* image)
{
    typedef float T;

    //
    // find histogram
    //
    //const int total = width * height ;
    const int histo_width = 256;

    // two buffers - for histogram and cumulative frequency	
    int histo_data[histo_width];  // histogram buffer
    memset(histo_data, 0, histo_width*sizeof(int));  // zero the data

    T cum_freq[256];
    memset(cum_freq, 0, histo_width*sizeof(T));

    int total = 0;   // meanwhile calculate total
    for (iT d = begin; d != end; ++d, ++total)
        histo_data[int(*d)]++;


    // find background (maximum of histogram data)
    int max_histo = 0, max_histo_index = 0;
    int* h = histo_data;
    for (int i = 0; i < histo_width; ++i, ++h) {
        if (*h > max_histo) {
            max_histo = *h;
            max_histo_index = i;
        }
    }

    histo_data[max_histo_index] = 0;  // suppose there was no background


    cum_freq[0] = T(histo_data[0]); //+ 0.5 ;
    T* p = cum_freq, * c = p+1;
    h = histo_data+1;
    for (int i = 1; i < histo_width; ++i, ++h, ++c, ++p) {
        *c = *h + *p;
    }


    // generate final image
    //const T alpha = T(255) / total ;
    const T alpha = T(255) / (total - max_histo);
    // we need to adjust alpha - needed

    image_type* img = image;

    for (iT d = begin; d != end; ++d, ++img) {
        if (*d == max_histo_index)  // skip background
            *img = image_type(*d);
        else
            *img = image_type(cum_freq[int(*d)] * alpha);
    }

}



template <class T>
void histogram_equalize(T* data, int total)
{
    histogram_equalize(data, data+total, data);
}


}  // namespace 

