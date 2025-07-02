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

/*

  Recursive filter of degree n


          m            n
         ---          ---
    y  =  >  b x    -  >  a y
     i   ---  k i-k   ---  k i-k
         k=0          k=1


  Assume m = n-1
*/

//
// the filter requires 4x4 parameters a+ b+ a- b-
// 
// two buffers required (positive buffer, negative buffer)
//

template <typename float_type, typename data_type>
void recursive_filter_1d_4_x(const data_type* src, float_type* dst, int width, int height,
    const float_type* bp, const float_type* ap, const float_type* bn, const float_type* an,
    float_type* pos_buffer, float_type* neg_buffer) noexcept
{
    auto s = src;
    auto d = dst;
    for (int i = 0; i < height; ++i, s += width, d += width) {
        recursive_filter_1d_4(s, d, width, bp, ap, bn, an, pos_buffer, neg_buffer);
    }
}

template <typename float_type, typename data_type>
void recursive_filter_1d_4(const data_type* src, float_type* dst, int length,
    const float_type* bp, const float_type* ap, const float_type* bn, const float_type* an,
    float_type* pos_buffer, float_type* neg_buffer) noexcept
{
    int i;
    int n = 4;
    float_type* yp, * yn;
    auto x = src;
    auto y = dst;

    // prepare all coefficients (for fastest process)
    const float_type bp0 = *bp, bp1 = *(bp+1), bp2 = *(bp+2), bp3 = *(bp+3);
    const float_type bn1 = *bn, bn2 = *(bn+1), bn3 = *(bn+2), bn4 = *(bn+3);
    const float_type ap1 = *ap, ap2 = *(ap+1), ap3 = *(ap+2), ap4 = *(ap+3);
    const float_type an1 = *an, an2 = *(an+1), an3 = *(an+2), an4 = *(an+3);

    const data_type* x0, * x1, * x2, * x3;
    float_type* y0, * y1, * y2, * y3, * y4;


    // --- Walk from left to right (positive) y+
    y0 = pos_buffer, y1 = y0+1, y2 = y1+1, y3 = y2+1, y4 = y3+1;
    x0 = x, x1 = x0+1, x2 = x1+1, x3 = x2+1;

    *y0 = *x0;
    *y1 = bp0 * *x1 + bp1 * *x0            - *ap1**y0;
    *y2 = bp0 * *x2 + bp1 * *x1            - *ap1**y1 - *ap2**y0;
    *y3 = bp0 * *x3 + bp1 * *x2 + *bp2**x3 - *ap1**y2 - *ap2**y1 - *ap2**y0;

    for (i = n; i < length; i++, x0++, x1++, x2++, x3++, y0++, y1++, y2++, y3++, y4++)
        *y4 = bp0**x3 + bp1**x2 + bp2**x1 + bp3**x0 - ap1**y3 - ap2**y2 - ap3**y1 - ap4**y0;


    // --- Walk through right to left (negative) y-
    y0 = &yn[length-1], y1 = y0-1, y2 = y1-1, y3 = y2-1, y4 = y3-1;
    x0 = &x[length-1], x1 = x0-1, x2 = x1-1, x3 = x2-1;

    *y0 = 0;
    *y1 = bn1 * *x0;
    *y2 = bn1 * *x1 + bn2 * *x0             - an1 * *y1;
    *y3 = bn1 * *x2 + bn2 * *x1 + bn3 * *x0 - an1 * *y2 - an2 * *y1;

    for (i = length - n - 1; i >= 0; i--, y0--, y1--, y2--, y3--, y4--, x0--, x1--, x2--, x3--)
        *y4 = bn1 * *x3 + bn2 * *x2 + bn3 * *x1 + bn4 * *x0
        - an1 * *y3 - an2 * *y2 - an3 * *y1 - an4 * *y0;


    // Sum the components
    y = dst, yp = pos_buffer, yn = neg_buffer;
    for (i = 0; i < length; ++i, ++y, ++yp, ++yn)
        *y = *yp + *yn;
}


// among y
template <typename float_type, typename data_type>
void filter_recursive_1d_4_y(data_type* src, float_type* dst, int length, int step,
    float_type* bp, float_type* ap, float_type* bn, float_type* an,
    float_type* yp, float_type* yn) noexcept
{
    const int n = 4;
    float_type* pyp, * pyn; //, *py_1, *py_2, *py_3, *px, *px_1, *px_2, *px_3 ;
    data_type* x = src;
    data_type* y = dst;
    data_type* py;

    // --- first pass - positive y+
    pyp = yp;

    yp[0] = x[0];
    yp[1] = bp[0]*x[1*step] + bp[1]*x[0*step]                   - ap[1]*yp[0];
    yp[2] = bp[0]*x[2*step] + bp[1]*x[1*step]                   - ap[1]*yp[1] - ap[2]*yp[0];
    yp[3] = bp[0]*x[3*step] + bp[1]*x[2*step] + bp[2]*x[3*step] - ap[1]*yp[2] - ap[2]*yp[1] - ap[2]*yp[0];

    for (i = n; i < length; i++) {
        yp[i] = bp[0] * x[i*step] 
              + bp[1] * x[(i-1)*step] 
              + bp[2] * x[(i-2)*step] 
              + bp[3] * x[(i-3)*step] 
              - ap[1] * yp[i-1] 
              - ap[2] * yp[i-2] 
              - ap[3] * yp[i-3] 
              - ap[4] * yp[i-4];
    }


    // --- second pass - negative  y-
    yn[length-1] = 0; //x[length-1] ;
    yn[length-2] = bn[1]*x[(length-1)*step];
    yn[length-3] = bn[1]*x[(length-2)*step] + bn[2]*x[(length-1)]                                 - an[1]*yn[length-2];
    yn[length-4] = bn[1]*x[(length-3)*step] + bn[2]*x[(length-2)*step] + bn[3]*x[(length-3)*step] - an[1]*yn[length-3] - an[2]*yn[length-2];

    for (i = length - n - 1; i >= 0; i--) {
        yn[i] = bn[1] * x[(i+1)*step] 
              + bn[2] * x[(i+2)*step] 
              + bn[3] * x[(i+3)*step] 
              + bn[4] * x[(i+4)*step] 
              - an[1] * yn[i+1] 
              - an[2] * yn[i+2] 
              - an[3] * yn[i+3] 
              - an[4] * yn[i+4];
    }


    // sum the components
    py = y, pyp = yp, pyn = yn;
    for (i = 0; i < length; i++, py+=step, pyp++, pyn++)
        *py = (data_type)(*pyp + *pyn);
}


}  // namespace cognit

