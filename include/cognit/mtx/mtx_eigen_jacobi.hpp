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


namespace cognit {


//
// input: 
//       a - symmetric nxn matrix
//
// params:
//       max_iter - maximum number of iterations (optional)
//
// output:
//       e - eigen values (the diagonal of a)
//       v - matrix containing eigen vectors of a
//
// b, z - buffers sizeof matrix
//
// ret: false if too many iterations performed
//
// Note: This is not optimized version, since it uses classic technique for finding
//       largest a[pq].
//

template <class T>
bool eigen_jacobi(T* a, int n, T* e, T* v, int max_iter, T* b, T* z)
{
    // local vars
    int p, q;  // indexes of the new found element
    T s, c, t, theta, tau;  // as described in algorithm
    T max_a;
    int i, j, r;  // iteration vars
    T tmp, h, rp, pr, rq, qr;  // temporary vars
    T* pa, * pe, * pv;  // pointers for faster access
    const int tot = n*n;
    auto small_value = T(1E-10);  // needed better
    auto big_value = T(10E9);  // needed better
    auto zero = T(0), one = T(1), half = T(0.5);

    // initialize v to identity matrix
    for (i = 0, pv = v; i < tot; ++i, ++pv)
        *pv = zero;
    for (i = 0, pv = v; i < n; ++i, pv += n+1)
        *pv = one;

    // initialize the diagonal elements of matrix D
    for (i = 0; i < n; ++i) {
        b[i] = e[i] = a[i*n + i];
        z[i] = zero;
    }


    //
    // In this version we don't use any extensions for fast finding the a[pq] element
    // instead we use the original method used by Jacobi 
    // for finding the largest a[pq]
    //
    int iter = 0;
    for (iter = 0; iter < max_iter; ++iter) {
        // find the largest off-diagonal element
        max_a = zero;
        for (i = 0; i < n-1; i++) {
            for (j = i+1; j < n; j++) {
                if (tmp = abs(a[i*n+j]); tmp > max_a) {
                    max_a = tmp;
                    p = i;
                    q = j;
                }
            }
        }


        // now it's time to check the stop condition
        if (max_a < small_value)
            break;

        // theta
        h = e[q] - e[p];

        // check the condition for very big theta
        if (abs(h) > big_value) { // needed better number ;
            t = a[p*n+q]/h;  // t = 1/(2theta) ;
        } else {
            theta = half*h/a[p*n+q];  // th = (a[qq]-a[pp])/2a[p][q]
            t = one/(abs(theta) + sqrt(theta*theta+one));  // t = 1/(th+sqrt(th^2+1))
            if (theta < zero)
                t = -t;
        }

        c = one/sqrt(t*t+one);
        s = t*c;
        tau = s/(c+one);
        h = t*a[p*n+q];

        // new a[pp] and a[qq]
        e[p] -= h;
        e[q] += h;

        // accumulate zs
        z[p] -= h;
        z[q] += h;

        a[p*n+q] = zero;  // our goal to set the chosen element to zero

        // now change the matrix for all columns and rows of p and q
        // all elements in up tri until p
        // use symmetry properties
        // a[rp] = a[rp]-s(a[rq]+tau a[rp])
        for (r = 0; r < p; r++) {
            rp = a[r*n+p];
            rq = a[r*n+q];
            a[r*n+p] -= s*(rq+tau*rp);
            a[r*n+q] += s*(rp-tau*rq);
        }

        // all elements between p and q
        for (r = p+1; r < q; r++) {
            pr = a[p*n+r];
            rq = a[r*n+q];
            a[p*n+r] -= s*(rq+tau*pr);
            a[r*n+q] += s*(pr-tau*rq);
        }

        // all elements over q
        for (r = q+1; r < n; r++) {
            pr = a[p*n+r];
            qr = a[q*n+r];
            a[p*n+r] -= s*(qr+tau*pr);
            a[q*n+r] += s*(pr-tau*qr);
        }

        // also interchange the eigen vector matrix
        for (r = 0; r < n; r++) {
            rp = v[r*n + p];
            rq = v[r*n + q];

            v[r*n + p] -= s*(rq + tau*rp);
            v[r*n + q] += s*(rp - tau*rq);
        }

        // update buffers
        for (i = 0; i < n; i++) {
            b[i] += z[i];
            e[i] = b[i];
            z[i] = zero;
        }
    }

    // restore the original matrix
    for (i = 0; i < n - 1; i++)
        for (j = i+1; j < n; j++)
            a[i*n+j] = a[j*n+i];

    return iter == max_iter ? false : true;
}






template <class T, int n>
bool eigen_jacobi(MtxN<T, n>& a, AVectorN<T, n>& e, MtxN<T, n>& v, int max_iter = 10000)
{
    // buffers
    AVectorN<T, n> b, z;  // buffers
    return eigen_jacobi((const T*)a.a, n, (const T*)e.a, (const T*)v.a, max_iter, (T*)b.a, (T*)z.a);
}


template <class T>
bool eigen_jacobi(Mtx<T>& a, AVector<T>& e, Mtx<T>& v, int max_iter = 10000)
{
    // buffers
    AVector<T> b, z;  // buffers
    b.resize(a.n()), z.resize(a.n());
    return eigen_jacobi(a.p, a.n(), e.p, v.p, max_iter, b.p, z.p);
}




}  // namespace


