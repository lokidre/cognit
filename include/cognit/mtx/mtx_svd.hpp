/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include "../matrix.hpp"

#include "iterator.hpp"
#include "eye.hpp"

#include "../const.hpp"

#include "../vector/dot.hpp"
#include "../vector/scale.hpp"
#include "../vector/zero.hpp"
#include "../vector/norm.hpp"



/*
            Singular Value Decomposition

    Let A be MxN matrix.

                A = U S V^T


    where

        A is mxn matrix
        U mxn matrix
        S diagonal matrix
        V nxn matrix

*/


namespace cognit {


//
// Make sure that matrix is orthogonal (add 1 if all elements are 0)
//
template <class T, class A_iterator>
void svd_ortho(A_iterator a, const int m, const int n)
{
    const T eps = const_eps<T>()();

    // for all columns
    for (int i = 0; i < n; ++i) {
        // check if current column is zero
        bool zero = true;

        for (int j = 0; j < m; ++j) {
            if (abs(a[j*n+i]) > eps) {
                zero = false;
                break;
            }
        }

        if (!zero)
            continue;

        // find empty row - we should be able to find one
        for (int j = 0; j < m; ++j) {
            bool zero = true;
            for (int k = 0; k < n; ++k) {
                if (abs(a[j*n+k]) > eps) {
                    zero = false;
                    break;
                }
            }

            if (!zero)
                continue;

            // set to 1
            a[j*n+i] = 1;
            break;
        }
    }
}



//
// Computes SVD using Jacobi iterations
//
// m >= n
// Q must be nxn
// S - n
template <class T, class A_iterator>
void svd_jacobi(A_iterator A, const int m, const int n, T* S, T* Q)
{
    typedef mtx_column_iterator<T> column_iterator;

    const T eps = const_eps<T>()();
    const T tol = 10 * m * eps;

    const int max_sweeps = max(12, n*5);

    mtx_i(Q, n);  // Q = I

    // column error estimates
    T* pa = A;
    T* ps = S;
    for (int j = 0; j < n; ++j, ++pa, ++ps) {
        column_iterator x(pa, n);
        *ps = vct_norm2<T>(x, m) * eps;
    }

    // rotations on A
    T p, v, q, a, b, ae_a, ae_b, sn, cs, ti, tj;
    int count, sweep;

    for (count = 1, sweep = 0; count > 0 && sweep < max_sweeps; sweep++) {
        count = n * (n-1) / 2;

        // for all pairs i < j
        for (int i = 0; i < n - 1; ++i) {
            for (int jj = i + 1; jj < n; ++jj) {


                /*
                // build matrix [ a c ; c b ]
                // v = sqrt((2x.y)^2 + (||x||^2 - ||y||^2)^2 ) ;
                a = vct_norm2<T>(ai,m), b = vct_norm2<T>(aj,m) ;
                c = vct_dot<T>(ai,aj,m) ; //*2 ;
                zeta = (b-a)*(b+a)/(c*2) ;  // attempt to avoid overflow a^2 - b^2 // b*b - a*a ;
                t = sign(zeta)/(abs(zeta) + sqrt(1+zeta*zeta)) ;
                cs = 1/sqrt(1+t*t) ;
                sn = cs*t ;
                // q =
                //v = hypot(p,q) ;

                // tests
                ae_a = S[j], ae_b = S[k] ;

                int sorted = (a >= b) ;
                int ortho = (abs(p) <= a * b * tol ) ;
                int na = (a <= ae_a) ;
                int nb = (b <= ae_b) ;

                */
                // p = 2 A(:,j).A(:,k)
                column_iterator ai(A+i, n), ajj(A+jj, n);

                // v = sqrt((2x.y)^2 + (||x||^2 - ||y||^2)^2 ) ;
                p = vct_dot<T>(ai, ajj, m)*2;
                a = vct_norm2<T>(ai, m), b = vct_norm2<T>(ajj, m);
                q = a*a - b*b;
                v = hypot(p, q);

                // tests
                ae_a = S[i], ae_b = S[jj];

                int sorted = (a >= b);
                int ortho = (abs(p) <= a * b * tol);
                int na = (a <= ae_a);
                int nb = (b <= ae_b);

                if (sorted && (ortho || na || nb)) {
                    count--;
                    continue;
                }

                // rotation sine and cosine
                if (v < eps || !sorted)
                    cs = 0, sn = 1;
                else
                    cs = sqrt((v+q)/(v*2)), sn = p/(v*2*cs);

                for (int k = 0; k < m; ++k) {
                    ti = A[k*n+i], tj = A[k*n+jj];
                    A[k*n+i] = ti*cs + tj*sn;
                    A[k*n+jj] = tj*cs - ti*sn;
                }

                S[i] = abs(cs) * ae_a + abs(sn) * ae_b;
                S[jj] = abs(sn) * ae_a + abs(cs) * ae_b;

                for (int k = 0; k < n; ++k) {
                    ti = Q[k*n+i], tj = Q[k*n+jj];
                    Q[k*n+i] = ti*cs + tj*sn;
                    Q[k*n+jj] = tj*cs - ti*sn;
                }
            }
        }
    }  // orthogonilaztion


    {  // singular values
        T prev_norm(0), norm;
        T* sj = S;

        for (int j = 0; j < n; ++j, ++sj) {
            column_iterator aj(A+j, n);
            norm = vct_norm2<T>(aj, m);

            if (norm < eps || (j>0 && prev_norm < eps) || (j>0 && norm <= prev_norm*tol)) {
                *sj = 0;
                vct_zero(aj, m);
                prev_norm = 0;
            } else {
                *sj = norm;
                vct_scale(aj, m, T(1)/norm);
                prev_norm = norm;
            }
        }
    }


    // checking
    if (count > 0)
        throw std::runtime_error("svd_jacobi: failed");


    // make sure U matrix is orthogonal
    svd_ortho<T, A_iterator>(A, m, n);
}





template <class T>
void svd_jacobi(Mtx<T>& a, AVector<T>& s, Mtx<T>& v)
{
    if (a.m() < a.n())
        throw std::runtime_error("svd_jacobi: m>=n");

    s.resize(a.n());
    v.resize(a.n(), a.n());
    svd_jacobi(a.p, a.m(), a.n(), s.p, v.p);
}


template <class T>
void svd_jacobi(const Mtx<T>& a, Mtx<T>& u, AVector<T>& s, Mtx<T>& v)
{
    u = a;
    svd_jacobi(u, s, v);
}


template <class T>
void svd_jacobi(Mtx3<T>& u, Vec3<T>& s, Mtx3<T>& v)
{
    svd_jacobi((T*)u.a, 3, 3, (T*)s.a, (T*)v.a);
}

// note: extra copying of matrix
template <class T>
void svd_jacobi(const Mtx3<T>& a, Mtx3<T>& u, Vec3<T>& s, Mtx3<T>& v)
{
    u = a;
    svd_jacobi(u, s, v);
}



template <class T>
void svd_jacobi(Mtx4<T>& u, Vec4<T>& s, Mtx4<T>& v)
{
    svd_jacobi((T*)u.a, 4, 4, (T*)s.a, (T*)v.a);
}

template <class T>
void svd_jacobi(const Mtx4<T>& a, Mtx4<T>& u, Vec4<T>& s, Mtx4<T>& v)
{
    u = a;
    svd_jacobi(u, s, v);
}


// computes SVD of input matrix a
//
/*
template <class T>
void svd ( T *a, const int m, const int n, T *w, T *v, T *buffer )
{

    int i, j, k, l ;  // indices

    //
    // Householder bidiagonalization
    //
    T g(0), scale(0), s(0), anorm(0) ;

    for ( i = 0 ; i < n ; ++i ) {
        l = i + 2 ;
        buffer[i] = scale*g ;
        g = s = scale = 0 ;
        if ( i < m ) {
            for ( k = i ; k < m ; ++k )
                scale += abs(a[k][i]) ;
            if ( scale > eps ) {  // check if we want to scale
                for ( k = i ; k < m ; ++k  ) {
                    a[k][i] /= scale ;
                    s += sqr(a[k][i]) ;
                }

                f = a[i][i] ;
                g = -sign(sqrt(s),f) ;
                h = f*g - s ;
                a[i][i] = f - g ;
                for ( j = l - 1 ; j < n ; ++j ) {
                    s = 0 ;
                    for ( k = i ; k < m ; ++k )
                        s += a[k][i] * a[k][j] ;
                    f = s/h ;
                    for ( k = i ; k < m ; ++k )
                        a[k][j] += f * a[k][j] ;
                }

                for ( k = i ; k < m ; ++k )
                    a[k][i] *= scale ;
            }  // scale
        }  // if i < m

        w[i] = scale * g ;

        g = s = scale = 0 ;
        if ( i + 1 <= m && i + 1 != n ) {
        }
    }



    //
    // Diagonalization
    //
    for ( int k = n-1 ; k >= 0 ; --k ) {
    }
}
*/

}


