/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once


/*

        Mtx Product

    Def:
    The product of lxn matrix A and mxl matrix B is mxn matrix C such that

            c_{ij} = sum from {k=1} to {N} { a_{ik}*b_{kj} }

*/

#include "../mtx.hpp"


namespace cognit {




// input:
//    a - lxn matrix
//    b - mxl matrix
// dimensions of c will be mxn
//
template <class It>
It mtx_mul(It a, int am, int an, It b, int bm, int bn, It c) noexcept
{
    It a_row, b_col, pa, pb;

    int i, j, k;
    int N = bn, M = am, K = an;

    for (i = 0, a_row = a; i < M; ++i, a_row += K)
        for (j = 0, b_col = b; j < N; ++j, ++c, ++b_col)
            for (k = 0, *c = 0, pb = b_col, pa = a_row; k < K; ++k, ++pa, pb += N)
                *c += *pa * *pb;

    return c;
}

template <class T>
Mtx<T>& mtx_mul(const Mtx<T>& a, const Mtx<T>& b, Mtx<T>& c)
{
    c.resize(a.m(), b.n());
    mtx_mul(a.p, a.m(), a.n(), b.p, b.m(), b.n(), c.p);
    return c;
}


// c = a.b
// remarks: must be &c != &a && &c != &b
template <class T>
Mtx2<T>& mtx_mul(const Mtx2<T>& a, const Mtx2<T>& b, Mtx2<T>& c) noexcept
{
    c.a[0][0] = a.a[0][0]*b.a[0][0] + a.a[0][1]*b.a[1][0];
    c.a[0][1] = a.a[0][0]*b.a[0][1] + a.a[0][1]*b.a[1][1];
    c.a[1][0] = a.a[1][0]*b.a[0][0] + a.a[1][1]*b.a[1][0];
    c.a[1][1] = a.a[1][0]*b.a[0][1] + a.a[1][1]*b.a[1][1];
    return c;
}


// a = a.b
// remarks: extra copying B = X
template <class T>
Mtx<T>& mtx_mul(Mtx2<T>& a, const Mtx2<T>& b) noexcept
{
    T t00, t01, t10, t11;

    t00 = a.a[0][0]*b.a[0][0] + a.a[0][1]*b.a[1][0];
    t01 = a.a[0][0]*b.a[0][1] + a.a[0][1]*b.a[1][1];
    t10 = a.a[1][0]*b.a[0][0] + a.a[1][1]*b.a[1][0];
    t11 = a.a[1][0]*b.a[0][1] + a.a[1][1]*b.a[1][1];

    a.a[0][0] = t00, a.a[0][1] = t01, a.a[1][0] = t10, a.a[1][1] = t11;

    return a;
}


// c = a.b
// remarks: &C must not be equal &A or &B
template <class T>
Mtx3<T>& mtx_mul(const Mtx3<T>& a, const Mtx3<T>& b, Mtx3<T>& c) noexcept
{
    c.a[0][0] = a.a[0][0]*b.a[0][0] + a.a[0][1]*b.a[1][0] + a.a[0][2]*b.a[2][0];
    c.a[0][1] = a.a[0][0]*b.a[0][1] + a.a[0][1]*b.a[1][1] + a.a[0][2]*b.a[2][1];
    c.a[0][2] = a.a[0][0]*b.a[0][2] + a.a[0][1]*b.a[1][2] + a.a[0][2]*b.a[2][2];
    c.a[1][0] = a.a[1][0]*b.a[0][0] + a.a[1][1]*b.a[1][0] + a.a[1][2]*b.a[2][0];
    c.a[1][1] = a.a[1][0]*b.a[0][1] + a.a[1][1]*b.a[1][1] + a.a[1][2]*b.a[2][1];
    c.a[1][2] = a.a[1][0]*b.a[0][2] + a.a[1][1]*b.a[1][2] + a.a[1][2]*b.a[2][2];
    c.a[2][0] = a.a[2][0]*b.a[0][0] + a.a[2][1]*b.a[1][0] + a.a[2][2]*b.a[2][0];
    c.a[2][1] = a.a[2][0]*b.a[0][1] + a.a[2][1]*b.a[1][1] + a.a[2][2]*b.a[2][1];
    c.a[2][2] = a.a[2][0]*b.a[0][2] + a.a[2][1]*b.a[1][2] + a.a[2][2]*b.a[2][2];

    return c;
}


// a = a.b
// remarks: extra copying A = X
template <class T>
Mtx3<T>& mtx_mul(Mtx3<T>& a, const Mtx3<T>& b) noexcept
{
    Mtx3<T> x;

    x.a[0][0] = a.a[0][0]*b.a[0][0] + a.a[0][1]*b.a[1][0] + a.a[0][2]*b.a[2][0];
    x.a[0][1] = a.a[0][0]*b.a[0][1] + a.a[0][1]*b.a[1][1] + a.a[0][2]*b.a[2][1];
    x.a[0][2] = a.a[0][0]*b.a[0][2] + a.a[0][1]*b.a[1][2] + a.a[0][2]*b.a[2][2];
    x.a[1][0] = a.a[1][0]*b.a[0][0] + a.a[1][1]*b.a[1][0] + a.a[1][2]*b.a[2][0];
    x.a[1][1] = a.a[1][0]*b.a[0][1] + a.a[1][1]*b.a[1][1] + a.a[1][2]*b.a[2][1];
    x.a[1][2] = a.a[1][0]*b.a[0][2] + a.a[1][1]*b.a[1][2] + a.a[1][2]*b.a[2][2];
    x.a[2][0] = a.a[2][0]*b.a[0][0] + a.a[2][1]*b.a[1][0] + a.a[2][2]*b.a[2][0];
    x.a[2][1] = a.a[2][0]*b.a[0][1] + a.a[2][1]*b.a[1][1] + a.a[2][2]*b.a[2][1];
    x.a[2][2] = a.a[2][0]*b.a[0][2] + a.a[2][1]*b.a[1][2] + a.a[2][2]*b.a[2][2];

    a = x;
    return a;
}



// c = a.b
// remarks: &C must not be equal &A or &B
template <class T>
Mtx4<T>& mtx_mul(const Mtx4<T>& a, const Mtx4<T>& b, Mtx4<T>& c) noexcept
{
    c.a[0][0] = a.a[0][0]*b.a[0][0] + a.a[0][1]*b.a[1][0] + a.a[0][2]*b.a[2][0] + a.a[0][3]*b.a[3][0];
    c.a[0][1] = a.a[0][0]*b.a[0][1] + a.a[0][1]*b.a[1][1] + a.a[0][2]*b.a[2][1] + a.a[0][3]*b.a[3][1];
    c.a[0][2] = a.a[0][0]*b.a[0][2] + a.a[0][1]*b.a[1][2] + a.a[0][2]*b.a[2][2] + a.a[0][3]*b.a[3][2];
    c.a[0][3] = a.a[0][0]*b.a[0][3] + a.a[0][1]*b.a[1][3] + a.a[0][2]*b.a[2][3] + a.a[0][3]*b.a[3][3];
    c.a[1][0] = a.a[1][0]*b.a[0][0] + a.a[1][1]*b.a[1][0] + a.a[1][2]*b.a[2][0] + a.a[1][3]*b.a[3][0];
    c.a[1][1] = a.a[1][0]*b.a[0][1] + a.a[1][1]*b.a[1][1] + a.a[1][2]*b.a[2][1] + a.a[1][3]*b.a[3][1];
    c.a[1][2] = a.a[1][0]*b.a[0][2] + a.a[1][1]*b.a[1][2] + a.a[1][2]*b.a[2][2] + a.a[1][3]*b.a[3][2];
    c.a[1][3] = a.a[1][0]*b.a[0][3] + a.a[1][1]*b.a[1][3] + a.a[1][2]*b.a[2][3] + a.a[1][3]*b.a[3][3];
    c.a[2][0] = a.a[2][0]*b.a[0][0] + a.a[2][1]*b.a[1][0] + a.a[2][2]*b.a[2][0] + a.a[2][3]*b.a[3][0];
    c.a[2][1] = a.a[2][0]*b.a[0][1] + a.a[2][1]*b.a[1][1] + a.a[2][2]*b.a[2][1] + a.a[2][3]*b.a[3][1];
    c.a[2][2] = a.a[2][0]*b.a[0][2] + a.a[2][1]*b.a[1][2] + a.a[2][2]*b.a[2][2] + a.a[2][3]*b.a[3][2];
    c.a[2][3] = a.a[2][0]*b.a[0][3] + a.a[2][1]*b.a[1][3] + a.a[2][2]*b.a[2][3] + a.a[2][3]*b.a[3][3];
    c.a[3][0] = a.a[3][0]*b.a[0][0] + a.a[3][1]*b.a[1][0] + a.a[3][2]*b.a[2][0] + a.a[3][3]*b.a[3][0];
    c.a[3][1] = a.a[3][0]*b.a[0][1] + a.a[3][1]*b.a[1][1] + a.a[3][2]*b.a[2][1] + a.a[3][3]*b.a[3][1];
    c.a[3][2] = a.a[3][0]*b.a[0][2] + a.a[3][1]*b.a[1][2] + a.a[3][2]*b.a[2][2] + a.a[3][3]*b.a[3][2];
    c.a[3][3] = a.a[3][0]*b.a[0][3] + a.a[3][1]*b.a[1][3] + a.a[3][2]*b.a[2][3] + a.a[3][3]*b.a[3][3];

    return c;
}


// a = a.b
// remarks: extra copying A = X
template <class T>
Mtx4<T>& mtx_mul(Mtx4<T>& a, const Mtx4<T>& b)
{
    Mtx4<T> x;

    x.a[0][0] = a.a[0][0]*b.a[0][0] + a.a[0][1]*b.a[1][0] + a.a[0][2]*b.a[2][0] + a.a[0][3]*b.a[3][0];
    x.a[0][1] = a.a[0][0]*b.a[0][1] + a.a[0][1]*b.a[1][1] + a.a[0][2]*b.a[2][1] + a.a[0][3]*b.a[3][1];
    x.a[0][2] = a.a[0][0]*b.a[0][2] + a.a[0][1]*b.a[1][2] + a.a[0][2]*b.a[2][2] + a.a[0][3]*b.a[3][2];
    x.a[0][3] = a.a[0][0]*b.a[0][3] + a.a[0][1]*b.a[1][3] + a.a[0][2]*b.a[2][3] + a.a[0][3]*b.a[3][3];
    x.a[1][0] = a.a[1][0]*b.a[0][0] + a.a[1][1]*b.a[1][0] + a.a[1][2]*b.a[2][0] + a.a[1][3]*b.a[3][0];
    x.a[1][1] = a.a[1][0]*b.a[0][1] + a.a[1][1]*b.a[1][1] + a.a[1][2]*b.a[2][1] + a.a[1][3]*b.a[3][1];
    x.a[1][2] = a.a[1][0]*b.a[0][2] + a.a[1][1]*b.a[1][2] + a.a[1][2]*b.a[2][2] + a.a[1][3]*b.a[3][2];
    x.a[1][3] = a.a[1][0]*b.a[0][3] + a.a[1][1]*b.a[1][3] + a.a[1][3]*b.a[2][3] + a.a[1][3]*b.a[3][3];
    x.a[2][0] = a.a[2][0]*b.a[0][0] + a.a[2][1]*b.a[1][0] + a.a[2][2]*b.a[2][0] + a.a[2][3]*b.a[3][0];
    x.a[2][1] = a.a[2][0]*b.a[0][1] + a.a[2][1]*b.a[1][1] + a.a[2][2]*b.a[2][1] + a.a[2][3]*b.a[3][1];
    x.a[2][2] = a.a[2][0]*b.a[0][2] + a.a[2][1]*b.a[1][2] + a.a[2][2]*b.a[2][2] + a.a[2][3]*b.a[3][2];
    x.a[2][3] = a.a[2][0]*b.a[0][3] + a.a[2][1]*b.a[1][3] + a.a[2][2]*b.a[2][3] + a.a[2][3]*b.a[3][3];
    x.a[3][0] = a.a[3][0]*b.a[0][0] + a.a[3][1]*b.a[1][0] + a.a[3][2]*b.a[2][0] + a.a[3][3]*b.a[3][0];
    x.a[3][1] = a.a[3][0]*b.a[0][1] + a.a[3][1]*b.a[1][1] + a.a[3][2]*b.a[2][1] + a.a[3][3]*b.a[3][1];
    x.a[3][2] = a.a[3][0]*b.a[0][2] + a.a[3][1]*b.a[1][2] + a.a[3][2]*b.a[2][2] + a.a[3][3]*b.a[3][2];
    x.a[3][3] = a.a[3][0]*b.a[0][3] + a.a[3][1]*b.a[1][3] + a.a[3][2]*b.a[2][3] + a.a[3][3]*b.a[3][3];

    a = x;
    return a;
}






//// remarks: &C most not be equal &A or &B
//template <class T, int n>
//MtxN<T, n>& mtx_mul(const MtxN<T, n>& a, const MtxN<T, n>& b, MtxN<T, n>& c)
//{
//    mtx_mul((T*)a.a, n, n, (T*)b.a, n, n, (T*)c.a);
//    return c;
//}



//// remarks: extra copying A = X
//template <class T, int n>
//MtxN<T, n>& mtx_mul(MtxN<T, n>& a, const MtxN<T, n>& b)
//{
//    MtxN<T, n> x;
//    mtx_mul(a, b, x);
//    a = x;
//    return a;
//}
//
//
//template <class T>
//MtxMN<T, 3, 4>& mtx_mul(const Mtx3<T>& a, const MtxMN<T, 3, 4>& b, MtxMN<T, 3, 4>& c)
//{
//    c.a[0][0] = a.a[0][0]*b.a[0][0] + a.a[0][1]*b.a[1][0] + a.a[0][2]*b.a[2][0];
//    c.a[0][1] = a.a[0][0]*b.a[0][1] + a.a[0][1]*b.a[1][1] + a.a[0][2]*b.a[2][1];
//    c.a[0][2] = a.a[0][0]*b.a[0][2] + a.a[0][1]*b.a[1][2] + a.a[0][2]*b.a[2][2];
//    c.a[0][3] = a.a[0][0]*b.a[0][3] + a.a[0][1]*b.a[1][3] + a.a[0][2]*b.a[2][3];
//    c.a[1][0] = a.a[1][0]*b.a[0][0] + a.a[1][1]*b.a[1][0] + a.a[1][2]*b.a[2][0];
//    c.a[1][1] = a.a[1][0]*b.a[0][1] + a.a[1][1]*b.a[1][1] + a.a[1][2]*b.a[2][1];
//    c.a[1][2] = a.a[1][0]*b.a[0][2] + a.a[1][1]*b.a[1][2] + a.a[1][2]*b.a[2][2];
//    c.a[1][3] = a.a[1][0]*b.a[0][3] + a.a[1][1]*b.a[1][3] + a.a[1][2]*b.a[2][3];
//    c.a[2][0] = a.a[2][0]*b.a[0][0] + a.a[2][1]*b.a[1][0] + a.a[2][2]*b.a[2][0];
//    c.a[2][1] = a.a[2][0]*b.a[0][1] + a.a[2][1]*b.a[1][1] + a.a[2][2]*b.a[2][1];
//    c.a[2][2] = a.a[2][0]*b.a[0][2] + a.a[2][1]*b.a[1][2] + a.a[2][2]*b.a[2][2];
//    c.a[2][3] = a.a[2][0]*b.a[0][3] + a.a[2][1]*b.a[1][3] + a.a[2][2]*b.a[2][3];
//
//    return c;
//}





// multiplication for arbitrary matrix
// c = a.b


// Note! - extra copying of matrix
template <class T>
Mtx<T>& mtx_mul(Mtx<T>& a, const Mtx<T>& b)
{
    Mtx<T> x;
    mtx_mul(a, b, x);
    a = x;
    return a;
}




//
// Multiplication of matrix and vector
//
// x = m.v
//

// remarks: &R most not be equal &V
template <class T>
Vec2<T>& mtx_mul(const Mtx2<T>& m, const Vec2<T>& v, Vec2<T>& x)
{
    x.a[0] = m.a[0][0]*v.a[0] + m.a[0][1]*v.a[1];
    x.a[1] = m.a[1][0]*v.a[0] + m.a[1][1]*v.a[1];
    return x;
}

// v = m.v
// Note: not optimize, extra copying
//template <class T>
//inline 
//AVector<T> &mtx_mul ( Vec2<type> &v, const Mtx2<type> &m )
//{
//	T t0, t1 ;

//	t0 = m.a[0][0]*v.a[0] + m.a[0][1]*v.a[1] ;
//	t1 = m.a[1][0]*v.a[0] + m.a[1][1]*v.a[1] ;

//	v.a[0] = t0, v.a[1] = t1 ;

//	return v ;
//}


template <class T>
Vec3<T>& mtx_mul(const Mtx3<T>& m, const Vec3<T>& v, Vec3<T>& x)
{
    x.a[0] = m.a[0][0]*v.a[0] + m.a[0][1]*v.a[1] + m.a[0][2]*v.a[2];
    x.a[1] = m.a[1][0]*v.a[0] + m.a[1][1]*v.a[1] + m.a[1][2]*v.a[2];
    x.a[2] = m.a[2][0]*v.a[0] + m.a[2][1]*v.a[1] + m.a[2][2]*v.a[2];

    return x;
}



//template <typename type>
//inline 
//void mtx_mul ( Mtx3<type> &m, Vec3<type> &v )
//{
//  type t0, t1, t2 ;

//  t0 = m.a[0][0]*v.a[0] + m.a[0][1]*v.a[1] + m.a[0][2]*v.a[2] ;
//  t1 = m.a[1][0]*v.a[0] + m.a[1][1]*v.a[1] + m.a[1][2]*v.a[2] ;
//  t2 = m.a[2][0]*v.a[0] + m.a[2][1]*v.a[1] + m.a[2][2]*v.a[2] ;

//  v.a[0] = t0, v.a[1] = t1, v.a[2] = t2 ;
//}




//// remarks: &R most not be equal &V
//template <class T, int N>
//void mtx_mul(const MtxN<T, N>& m, const VecN<T, N>& v, VecN<T, N>& r)
//{
//    VecN<T, N> t, * x = (&v == &r) ? &t : &r;
//    int i, j;  // column row
//
//    for (i = 0; i < N; i++) {
//        x->a[i] = 0;
//        for (j = 0; j < N; j++) {
//            x->a[i] += m.a[i][j] * v.a[j];
//        }
//    }
//
//    if (x != &r)
//        r = *x;
//}


//// remarks: extra copying V = T
//template <class T, int N>
//void mtx_mul(MtxN<T, N>& m, VecN<T, N>& v)
//{
//    VecN<T, N> t;
//    int i, j;  // column row
//
//    for (i = 0; i < N; ++i) {
//        t.a[i] = 0;
//        for (j = 0; j < N; ++j)
//            t.a[i] += m.a[i][j] * v.a[j];
//    }
//
//    v = t;
//}





//// remarks: not optimized - extra copying of c
//template <class T>
//Mtx2<T> operator * (const Mtx2<T>& a, const Mtx2<T>& b)
//{
//    Mtx2<T> c;
//    mtx_mul(a, b, c);
//    return c;
//}
//
//template <typename type>
//Mtx3<type> operator * (const Mtx3<type>& a, const Mtx3<type>& b)
//{
//    Mtx3<type> c;
//    mtx_mul(a, b, c);
//    return c;
//}
//
//template <class T>
//Mtx4<T> operator * (const Mtx4<T>& a, const Mtx4<T>& b)
//{
//    Mtx4<T> c;
//    mtx_mul(a, b, c);
//    return c;
//}
//
//template <class type, int n>
//MtxN<type, n> operator * (const MtxN<type, n>& a, const MtxN<type, n>& b)
//{
//    MtxN<type, n> c;
//    mtx_mul(a, b, c);
//    return c;
//}
//
//
//// note: memory leak, needed better
//template <class T>
//Mtx<T> operator * (const Mtx<T>& a, const Mtx<T>& b)
//{
//    Mtx<T> c;
//    mtx_mul(a, b, c);
//    return c;
//}


}  // namespace

