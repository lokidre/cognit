/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include "./mtx_add_core.hpp"


namespace cognit {

//
// Matrix addition/subtraction

// Def:
// The sum of matrices A and B is a matrix C, such that every element of C is a sum of
// corresponding elements of A and B.
//

// template <class matrix_type>
// matrix_type& mtx_add_basic(const matrix_type& a, const matrix_type& b, matrix_type& c)
// {
//     typename matrix_type::const_iterator a_it, a_end, b_it;
//     typename matrix_type::iterator c_it;

//     c.setup(a.n(), a.m());

//     for (a_it = a.begin(), a_end = a.end(), b_it = b.begin(), c_it = c.begin(); a_it != a_end;
//          a_it++, b_it++, c_it++)
//         *c_it = *a_it + *b_it;

//     return c;
// }


// template <class matrix_type>
// matrix_type& mtx_add_basic(matrix_type& a, const matrix_type& b)
// {
//     typename matrix_type::const_iterator b_it;
//     typename matrix_type::iterator a_it, a_end;

//     for (a_it = a.begin(), a_end = a.end(), b_it = b.begin(); a_it != a_end; a_it++, b_it++)
//         *a_it += *b_it;

//     return a;
// }


// template <class matrix_type>
// matrix_type& mtx_sub_basic(const matrix_type& a, const matrix_type& b, matrix_type& c)
// {
//     typename matrix_type::const_iterator a_it, a_end, b_it;
//     typename matrix_type::iterator c_it;

//     c.setup(a.n(), a.m());

//     for (a_it = a.begin(), a_end = a.end(), b_it = b.begin(), c_it = c.begin(); a_it != a_end;
//          a_it++, b_it++, c_it++)
//         *c_it = *a_it - *b_it;

//     return c;
// }


// template <class matrix_type>
// matrix_type& mtx_sub_basic(matrix_type& a, const matrix_type& b)
// {
//     typename matrix_type::const_iterator b_it;
//     typename matrix_type::iterator a_it, a_end;

//     for (a_it = a.begin(), a_end = a.end(), b_it = b.begin(); a_it != a_end; a_it++, b_it++)
//         *a_it -= *b_it;

//     return a;
// }



template <class T>
Mtx<T>& mtx_add(const Mtx<T>& a, const Mtx<T>& b, Mtx<T>& c) noexcept
{
    mtx_add_it(a.data(), b.data(), a.M, a.N, c.data());
    return c;
}


template <class T>
Mtx<T>& mtx_add(Mtx<T>& a, const Mtx<T>& b)
{
    return mtx_add_basic(a, b);
}


template <class T>
Mtx<T>& mtx_sub(const Mtx<T>& a, const Mtx<T>& b, Mtx<T>& c)
{
    return mtx_sub_basic(a, b, c);
}



template <class T>
Mtx<T>& mtx_sub(Mtx<T>& a, const Mtx<T>& b)
{
    return mtx_sub_basic(a, b);
}



template <typename type>
void mtx_add(Mtx<type>& a, Mtx<type>& b)
{
    // the dimensions of two matrices must be equal
    if (a.m != b.m || a.n != b.n)
        return;

    int total = a.m * a.n;

    type *pa = a.p, *pb = b.p;
    for (int i = 0; i < total; i++, pa++, pb++)
        *pa += *pb;
}



// Mtx2<type>
template <class type>
Mtx2<type>& mtx_add(const Mtx2<type>& a, const Mtx2<type>& b, Mtx2<type>& c)
{
    c.a[0][0] = a.a[0][0] + b.a[0][0];
    c.a[0][1] = a.a[0][1] + b.a[0][1];
    c.a[1][0] = a.a[1][0] + b.a[1][0];
    c.a[1][1] = a.a[1][1] + b.a[1][1];
    return c;
}

template <class type>
void mtx_sub(Mtx2<type>& a, Mtx2<type>& b, Mtx2<type>& c)
{
    c.a[0][0] = a.a[0][0] - b.a[0][0];
    c.a[0][1] = a.a[0][1] - b.a[0][1];
    c.a[1][0] = a.a[1][0] - b.a[1][0];
    c.a[1][1] = a.a[1][1] - b.a[1][1];
}


template <typename type>
void mtx_add(Mtx2<type>& a, Mtx2<type>& b)
{
    a.a[0][0] += b.a[0][0];
    a.a[0][1] += b.a[0][1];
    a.a[1][0] += b.a[1][0];
    a.a[1][1] += b.a[1][1];
}

template <typename type>
void mtx_sub(Mtx2<type>& a, Mtx2<type>& b)
{
    a.a[0][0] -= b.a[0][0];
    a.a[0][1] -= b.a[0][1];
    a.a[1][0] -= b.a[1][0];
    a.a[1][1] -= b.a[1][1];
}


// t_matrix3<type>
template <typename type>
void mtx_add(Mtx3<type>& a, Mtx3<type>& b, Mtx3<type>& c)
{
    c.a[0][0] = a.a[0][0] + b.a[0][0];
    c.a[0][1] = a.a[0][1] + b.a[0][1];
    c.a[0][2] = a.a[0][2] + b.a[0][2];
    c.a[1][0] = a.a[1][0] + b.a[1][0];
    c.a[1][1] = a.a[1][1] + b.a[1][1];
    c.a[1][2] = a.a[1][2] + b.a[1][2];
    c.a[2][0] = a.a[2][0] + b.a[2][0];
    c.a[2][1] = a.a[2][1] + b.a[2][1];
    c.a[2][2] = a.a[2][2] + b.a[2][2];
}

template <typename type>
void mtx_sub(Mtx3<type>& a, Mtx3<type>& b, Mtx3<type>& c)
{
    c.a[0][0] = a.a[0][0] - b.a[0][0];
    c.a[0][1] = a.a[0][1] - b.a[0][1];
    c.a[0][2] = a.a[0][2] - b.a[0][2];
    c.a[1][0] = a.a[1][0] - b.a[1][0];
    c.a[1][1] = a.a[1][1] - b.a[1][1];
    c.a[1][2] = a.a[1][2] - b.a[1][2];
    c.a[2][0] = a.a[2][0] - b.a[2][0];
    c.a[2][1] = a.a[2][1] - b.a[2][1];
    c.a[2][2] = a.a[2][2] - b.a[2][2];
}

template <typename type>
void mtx_add(Mtx3<type>& a, Mtx3<type>& b)
{
    a.a[0][0] += b.a[0][0];
    a.a[0][1] += b.a[0][1];
    a.a[0][2] += b.a[0][2];
    a.a[1][0] += b.a[1][0];
    a.a[1][1] += b.a[1][1];
    a.a[1][2] += b.a[1][2];
    a.a[2][0] += b.a[2][0];
    a.a[2][1] += b.a[2][1];
    a.a[2][2] += b.a[2][2];
}

template <typename type>
void mtx_sub(Mtx3<type>& a, Mtx3<type>& b)
{
    a.a[0][0] -= b.a[0][0];
    a.a[0][1] -= b.a[0][1];
    a.a[0][2] -= b.a[0][2];
    a.a[1][0] -= b.a[1][0];
    a.a[1][1] -= b.a[1][1];
    a.a[1][2] -= b.a[1][2];
    a.a[2][0] -= b.a[2][0];
    a.a[2][1] -= b.a[2][1];
    a.a[2][2] -= b.a[2][2];
}



// t_matrix4<type>
template <class T>
void mtx_add(Mtx4<T>& a, Mtx4<T>& b, Mtx4<T>& c) noexcept
{
    mtx4x4_add(a, b, c);
}

template <typename type>
void mtx_sub(Mtx4<type>& a, Mtx4<type>& b, Mtx4<type>& c) noexcept
{
    mtx4x4_sub(a, b, c);
}

//template <class T>
//Mtx4<T>& mtx_add(Mtx4<T>& a, const Mtx4<T>& b)
//{
//    a.a[0][0] += b.a[0][0];
//    a.a[0][1] += b.a[0][1];
//    a.a[0][2] += b.a[0][2];
//    a.a[0][3] += b.a[0][3];
//    a.a[1][0] += b.a[1][0];
//    a.a[1][1] += b.a[1][1];
//    a.a[1][2] += b.a[1][2];
//    a.a[1][3] += b.a[1][3];
//    a.a[2][0] += b.a[2][0];
//    a.a[2][1] += b.a[2][1];
//    a.a[2][2] += b.a[2][2];
//    a.a[2][3] += b.a[2][3];
//    a.a[3][0] += b.a[3][0];
//    a.a[3][1] += b.a[3][1];
//    a.a[3][2] += b.a[3][2];
//    a.a[3][3] += b.a[3][3];
//    return a;
//}

//template <typename type>
//void mtx_sub(Mtx4<type>& a, Mtx4<type>& b)
//{
//    a.a[0][0] -= b.a[0][0];
//    a.a[0][1] -= b.a[0][1];
//    a.a[0][2] -= b.a[0][2];
//    a.a[0][3] -= b.a[0][3];
//    a.a[1][0] -= b.a[1][0];
//    a.a[1][1] -= b.a[1][1];
//    a.a[1][2] -= b.a[1][2];
//    a.a[1][3] -= b.a[1][3];
//    a.a[2][0] -= b.a[2][0];
//    a.a[2][1] -= b.a[2][1];
//    a.a[2][2] -= b.a[2][2];
//    a.a[2][3] -= b.a[2][3];
//    a.a[3][0] -= b.a[3][0];
//    a.a[3][1] -= b.a[3][1];
//    a.a[3][2] -= b.a[3][2];
//    a.a[3][3] -= b.a[3][3];
//}



// t_matrixn<type,n>
/*
template <typename type, int n>
void mtx_add ( MtxN<type,n> &a, MtxN<type,n> &b, MtxN<type,n> &c )
{
  int i, tot = n*n ;

  type *pa = (type *)&a, *pb = (type *)&b, *pc = (type *)&c ;
  for ( i = 0 ; i < tot ; i++, pa++, pb++, pc++ )
    *pc = *pa + *pb ;
}
*/


/*
template <typename type, int n>
void mtx_sub(MtxN<type, n>& a, MtxN<type, n>& b, MtxN<type, n>& c)
{
    int i, tot = n * n;

    type *pa = (type*)&a, *pb = (type*)&b, *pc = (type*)&c;
    for (i = 0; i < tot; i++, pa++, pb++, pc++)
        *pc = *pa - *pb;
}
*/


/*
template <typename type, int n>
void mtx_add(MtxN<type, n>& a, MtxN<type, n>& b)
{
    int i, tot = n * n;

    type *pa = (type*)&a, *pb = (type*)&b;
    for (i = 0; i < tot; i++, pa++, pb++)
        *pa += *pb;
}


template <class T, int n>
void mtx_sub(MtxN<T, n>& a, const MtxN<T, n>& b)
{
    int i, tot = n * n;

    T* pa = (T*)a.a;
    const T* pb = (T*)b.a;
    for (i = 0; i < tot; ++i, ++pa, ++pb)
        *pa -= *pb;
}
*/

// Mtx<type>



//
// Operator overloading
//

/*
//
// remarks: not optimal, allocates in stack and copies extra matrix
//
template <class T>
Mtx2<T> operator + ( const Mtx2<T> &A, const Mtx2<T> &B )
{
	Mtx2<T> C ;
	mtx_add(A,B,C) ;
	return C ;
}

template <class T>
Mtx2<T> operator - ( const Mtx2<T> &A, const Mtx2<T> &B )
{
	Mtx2<T> C ;
	mtx_sub(A,B,C) ;
	return C ;
}


template <class T, int n>
MtxN<T,n> operator + ( const MtxN<T,n> &a, const MtxN<T,n> &b )
{
	MtxN<T,n> c ;
	mtx_add ( a, b, c ) ;
	return c ;
}

// remarks: not optimal, allocates in stack and copies extra matrix
template <class T, int n>
MtxN<T,n> operator - ( const MtxN<T,n> &a, const MtxN<T,n> &b )
{
	MtxN<T,n> c ;
	mtx_sub ( a, b, c ) ;
	return c ;
}
*/

}  // namespace cognit
