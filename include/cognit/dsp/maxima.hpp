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


template <class M, class T>
void suppress_non_maxima_mask(const T* gx_data, const T* gy_data, const T* norm_data, M* maxima, int width, int height)
{
    const T eps = const_eps<T>()();

    M* m = maxima;  // main pointer to mask
    const T* gx = gx_data, * gy = gy_data, * n = norm_data;  // gradients and norms
    int i, j;  // indices
    const T* nn[9];  // we have to maintain 6 neighbors of current norm

    // Initialize pointers
    nn[4] = n;
    nn[5] = n + 1;
    nn[6] = n + width-1;
    nn[7] = nn[6]+1;
    nn[8] = nn[7]+1;
    nn[3] = n-1;
    nn[0] = n-width-1;
    nn[1] = nn[0]+1;
    nn[2] = nn[1]+1;

    // Skip the first and last rows.
    // We will never know if there is any maxima on borders.
    for (i = 0; i < width; ++i, ++m, ++gx, ++gy, ++n, ++nn[0], ++nn[1], ++nn[2], ++nn[3], ++nn[4], ++nn[5], ++nn[6], ++nn[7], ++nn[8])
        *m = 0;

    int x1, y1;
    T sign_value;  // variable to determine the sign
    T gx_abs, gy_abs, g_ratio;

    // go for all rows (except first and last)
    for (j = 2; j < height; ++j) {
        // skip first column
        *m = 0;
        ++m, ++gx, ++gy, ++n, ++nn[0], ++nn[1], ++nn[2], ++nn[3], ++nn[4], ++nn[5], ++nn[6], ++nn[7], ++nn[8];

        // do for all columns except first and last
        for (i = 2; i < width; ++i, ++m, ++gx, ++gy, ++n, ++nn[0], ++nn[1], ++nn[2], ++nn[3], ++nn[4], ++nn[5], ++nn[6], ++nn[7], ++nn[8]) {

            // skip already suppressed
            if (*m == 0)
                continue;

            // check the direction of the gradient
            if (tiny(*gx, eps)) {
                x1 = 0, y1 = 1;
            } else if (tiny(*gy, eps)) {
                x1 = 1, y1 = 0;
            } else {
                // now find the half quarter
                gx_abs = abs(*gx), gy_abs = abs(*gy);

                // check the ratio (keep it under 1)
                if (gx_abs >= gy_abs)
                    g_ratio = gy_abs / gx_abs;
                else
                    g_ratio = gx_abs / gy_abs;

                if (g_ratio < 0.5) {
                    if (gx_abs > gy_abs)
                        x1 = 1, y1 = 0;
                    else
                        x1 = 0, y1 = 1;
                } else {
                    // here we will have basically two cases - first or second quarter based on signs
                    sign_value = *gx * *gy;

                    // determined the quarter
                    if (sign_value > 0)
                        x1 = y1 = 1;
                    else
                        x1 = 1, y1 = -1;
                }
            }

            // now suppress if this is not maxima
            if (*n <= *nn[(1+y1)*3+(1+x1)] || *n <= *nn[(1-y1)*3+(1-x1)])
                *m = 0;
        }

        // skip last column
        *m = 0;
        ++m, ++gx, ++gy, ++n, ++nn[0], ++nn[1], ++nn[2], ++nn[3], ++nn[4], ++nn[5], ++nn[6], ++nn[7], ++nn[8];
    }

    // last row
    for (i = 0; i < width; ++i, ++m)
        *m = 0;

}


template <class T, class C>
void gradient_maxima(const T* gx_data, const T* gy_data, const T* norm_of_gradient, C& maxima, int width, int height) noexcept
{
    typename C::value_type p;

    const T eps = const_eps<T>()();
    const T pi = const_eps<T>()();
    T n, n_1, n1;  // norm, norm-1, norm+1
    T maxy;
    T gamma;

    for (int j = 1; j < height - 1; ++j) {
        for (int i = 1; i < width - 1; ++i) {
            auto gx = &gx_data[j*width+i];
            auto gy = &gy_data[j*width+i];
            auto norm = &norm_of_gradient[j*width+i];
            int x1, x2, y1, y2;


            // skip very small values
            if (*norm < eps)
                continue;

            if (tiny(*gx, eps)) {
                x1 = x2 = 0;
                y1 = -1, y2 = 1;
                gamma = pi/2;
            } else if (tiny(*gy, eps)) {
                x1 = -1, x2 = 1;
                y1 = y2 = 0;
                gamma = 0;
            } else {

                // determine the direction of gradient
                // needed - get rid of atan
                gamma = abs(atan2(*gy, *gx));

                if (gamma <= (pi/4/2) || gamma >= (pi/4/2+3*pi/4)) {
                    x1 = -1, x2 = 1;
                    y1 = y2 = 0;
                } else if (gamma > (pi/4/2) && gamma <= (pi/4/2+pi/4)) {
                    x1 = 1, x2 = -1;
                    y1 = 1, y2 = -1;
                } else if (gamma > (pi/4/2+pi/4) && gamma <= (pi/4/2+2*pi/4)) {
                    x1 = x2 = 0;
                    y1 = -1, y2 = 1;
                } else if (gamma > (pi/4/2+2*pi/4) && gamma <= (pi/4/2+3*pi/4)) {
                    x1 = 1, x2 = -1;
                    y1 = -1, y2 = 1;
                }
            }

            n = *norm;
            n_1 = norm_of_gradient[(j+y1)*width+i+x1];
            n1 = norm_of_gradient[(j+y2)*width+i+x2];

            // check if gradient is maxima
            //if ( *norm < norm_of_gradient[(j+y1)*width+i+x1] || *norm < norm_of_gradient[(j+y2)*width+i+x2] )
            //	continue ;

            if (n < n_1 || n < n1)
                continue;

            // calculate the coordinate of current maxima (shift to 0.5)
            p.x = T(i), p.y = T(j);

            // find the shift among gradient direction
            //maxy = (3*n_1 - 4*n + n1)/(n_1 - 2*n + n1)/2 - 1 ;
            maxy = (n_1-n1)/(n_1-2*n+n1)/2;

            // correct the value among gradient direction
            if (!tiny(maxy, eps)) {
                p.x += maxy*sin(gamma);
                p.y += maxy*cos(gamma);
            }


            //p.x += 0.5, p.y += 0.5 ;



            // now do subpixel evaluation

            //p.x = float_type(i), p.y = float_type(j) ;

            maxima.push_back(p);
        }
    }
}




// 
// non maxima suppression
//
// notes: must src != dst
//
template <class input_type, class output_type>
void suppress_non_maxima(const input_type* src, output_type* dst, int width, int height) noexcept
{
    const input_type* p = src;
    output_type* q = dst;
    int i, j;

    output_type z(0);

    // suppress first row
    for (i = 0; i < width; ++i, ++q)
        *q = 0;
    p += width;


    // suppress non-maxima
    for (j = 2; j < height; ++j) {
        *q = 0;
        ++p, ++q;

        for (i = 2; i < width; ++i, ++p, ++q) {
            const auto& x = *p;

            if (x >*(p-1) && x > *(p+1) && x > *(p-width) && x > *(p+width) && x > *(p-width-1) && x > *(p-width+1) && x > *(p+width-1) && x > *(p+width+1)) {
                *q = x;
            } else {
                *q = z;
            }
        }
        *q = 0;
        ++p, ++q;
    }

    // last row
    for (i = 0; i < width; ++i, ++q)
        *q = 0;
    p += width;
}

template <class T, class U>
void suppress_non_maxima_all(const T* src, T* dst, int width, int height) noexcept
{
    suppress_non_maxima(src, dst, width, height);
}

template <class T, class U>
void suppress_non_maxima_y(const T* data, U* maxima, int width, int height) noexcept
{
    const T* py, * ppy, * pny;
    U* m;

    // suppress non-maxima on gy
    for (int x = 0; x < width; x++) {
        ppy = data + x;
        py = ppy + width;
        pny = py + width;

        m = maxima + x;
        *m = 0;  // first row (no maxima)
        m += width; // start from the second row

        for (int y = 2; y < height; ++y, ppy += width, py += width, pny += width, m += width) {
            if (*py <= *ppy || *py <= *pny)
                *m = 0;
            else
                *m = 1; //U(*py) ;
        }
        *m = 0;   // last row (no maxima)
    }

}

template <class T, class U>
void suppress_non_maxima_x(const T* data, U* maxima, int width, int height) noexcept
{
    const T* px=data, * px_1=px-1, * pxx1=px+1;
    U* m = maxima;

    for (int j = 0; j < height; ++j) {

        // first column has no maxima
        *m = 0;
        ++m, ++px, ++px_1, ++pxx1;

        for (int i = 2; i < width; ++i, ++m, ++px, ++px_1, ++pxx1) {
            if (*px <= *px_1 || *px <= *pxx1)
                *m = 0;
            else
                *m = U(*px);
        }

        // last column has no maxima
        *m = 0;
        ++m, ++px, ++px_1, ++pxx1;
    }

}


//
// approximate maxima using quadratic equation
//
// on output all non maxima elements are zero
// all maxima elements contain approximated y values
//
/*
template <class T, class mask_type>
void approx_maxima_quad_y ( const input_type *gy, const input_type *mask, output_type *maxima )
{
}
*/


template <typename data_type, typename float_type, typename container_type, typename point_type>
int find_maxima(data_type* data, container_type& maxima, int width, int height, data_type delta) noexcept
{
    point_type pt;

    for (int j = 1; j < height - 1; j++) {
        for (int i = 1; i < width - 1; i++) {
            data_type f = data[j*width+i];

            if (f < delta)
                continue;

            if ((f-data[j*width+i-1])>=0 && (data[j*width+i+1]-f)<=0 &&
                (f-data[(j-1)*width+i])>=0 && (data[(j+1)*width+i]-f)<=0) {

                float_type x1 = i-1, x2 = i, x3 = i+1;
                float_type y1 = data[j*width+i-1], y2 = data[j*width+i], y3 = data[j*width+i+1];

                float_type a = -(x3*(-y1+y2) + x2*(y1-y3) + x1*(-y2+y3))/((x1 - x2)*(x1 - x3)*(x2 - x3));
                float_type b = -(x3*x3*(y1-y2)+x1*x1*(y2-y3)+x2*x2*(-y1+y3))/((x1 - x2)*(x1 - x3)*(x2 - x3));

                if (a == 0) {
                    pt.x = 0.5 + i;
                } else {
                    pt.x = 0.5 + -b/(2*a);
                }

                x1 = j-1, x2 = j, x3 = j+1;
                y1 = data[(j-1)*width+i], y2 = data[j*width+i], y3 = data[(j+1)*width+i];

                a = -(x3*(-y1+y2) + x2*(y1-y3) + x1*(-y2+y3))/((x1-x2)*(x1-x3)*(x2-x3));
                b = -(x3*x3*(y1-y2)+x1*x1*(y2-y3)+x2*x2*(-y1+y3))/((x1-x2)*(x1-x3)*(x2-x3));

                if (a == 0) {
                    pt.y = 0.5 + j;
                } else {
                    pt.y = 0.5 + -b/(2*a);
                }

                maxima.add(pt);
            }
        }
    }

    return maxima.n;
}


}  // namespace


