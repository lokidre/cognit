/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include "../const.hpp"


namespace cognit {

// Matrix Comparison

//
// Def:
// Two matrices are called equal if all the corresponding elements are equal
//


template <class matrix_T>
bool mtx_equ_basic(const matrix_T& a, const matrix_T& b)
{
    if (a.size() != b.size())
        return false;

    for (typename matrix_T::const_iterator a_it=a.begin(), b_it=b.begin(), a_end=a.end(); a_it != a_end; a_it++, b_it++)
        if (*a_it != *b_it)
            return false;

    return true;
}


template <class matrix_T>
bool mtx_equ_fuzzy_basic(const matrix_T& a, const matrix_T& b, const typename matrix_T::value_type& delta)
{
    if (a.size() != b.size())
        return false;

    typedef typename matrix_T::value_type value_type;

    for (typename matrix_T::const_iterator a_it = a.begin(), a_end = a.end(), b_it = b.begin(); a_it != a_end; a_it++, b_it++)
        if (abs(*a_it - *b_it) > delta)
            return false;

    return true;
}

//
// determine if matrix is identity
//
template <class matrix_T>
bool mtx_equ_i_basic(const matrix_T& a)
{
    if (a.n() != a.m())  // the matrix has to be square
        return false;

    int N = a.n();
    int ones=N+1, one_pos = 0;

    for (auto a_it = a.begin(), a_end = a.end(); a_it != a_end; a_it++, one_pos++) {
        if (one_pos == ones) {
            if (*a_it != 1)
                return false;
            one_pos = 0;
        } else {
            if (*a_it != 0)
                return false;
        }
    }

    return true;
}


template <class matrix_T>
bool mtx_equ_i_fuzzy_basic(const matrix_T& a, const typename matrix_T::value_type& delta)
{
    if (a.n() != a.m())  // the matrix has to be square
        return false;

    int N = a.n();
    int ones=N+1, one_pos = ones;

    for (typename matrix_T::const_iterator a_it = a.begin(), a_end = a.end(); a_it != a_end; a_it++, one_pos++) {
        if (one_pos == ones) {
            if (abs(*a_it-1)>delta)
                return false;
            one_pos = 0;
        } else {
            if (abs(*a_it)>delta)
                return false;
        }
    }

    return true;
}



//
// mtx_equ(A,B)
//

template <class T>
bool mtx_equ(const Mtx<T>& a, const Mtx<T>& b)
{
    return mtx_equ_basic(a, b);
}


template <typename T>
bool mtx_equ(const Mtx2<T>& u, Mtx2<T>& v)
{
    return bool(u.a[0][0]==v.a[0][0] && u.a[0][1]==v.a[0][1] &&
        u.a[1][0]==v.a[1][0] && u.a[1][1]==v.a[1][1]);
}

template <class T>
bool mtx_equ(const Mtx3<T>& u, Mtx3<T>& v)
{
    return bool(u.a[0][0]==v.a[0][0] && u.a[0][1]==v.a[0][1] && u.a[0][2]==v.a[0][2] &&
        u.a[1][0]==v.a[1][0] && u.a[1][1]==v.a[1][1] && u.a[1][2]==v.a[1][2] &&
        u.a[2][0]==v.a[2][0] && u.a[2][1]==v.a[2][1] && u.a[2][2]==v.a[2][2]);
}

template <class real_type, int n>
bool mtx_equ(const MtxN<real_type, n>& a, const MtxN<real_type, n>& b)
{
    return mtx_equ_basic(a, b);
}



//
// mtx_equ_fuzzy
//

template <typename T>
inline
bool mtx_equ_fuzzy(const Mtx<T>& a, const Mtx<T>& b)
{
    const_delta<T> delta;
    return mtx_equ_fuzzy_basic(a, b, delta());
}




//
// mtx_equ_i - Equality to I
//

template <class type>
bool mtx_equ_i(const Mtx<type>& a)
{
    return mtx_equ_i_basic(a);
}


template <class type>
bool mtx_equ_i(const Mtx2<type>& a)
{
    return a.a[0][0]==1 && a.a[0][1]==0 &&
        a.a[1][0]==0 && a.a[1][1]==1;
}

template <class type>
bool mtx_equ_i(const Mtx3<type>& a)
{
    return a.a[0][0]==1 && a.a[0][1]==0 && a.a[0][2]==0 &&
        a.a[1][0]==0 && a.a[1][1]==1 && a.a[1][2]==0 &&
        a.a[2][0]==0 && a.a[2][1]==0 && a.a[2][2]==1;
}

template <class type>
bool mtx_equ_i(const Mtx4<type>& a)
{
    return a.a[0][0]==1 && a.a[0][1]==0 && a.a[0][2]==0 && a.a[0][3]==0 &&
        a.a[1][0]==0 && a.a[1][1]==1 && a.a[1][2]==0 && a.a[1][3]==0 &&
        a.a[2][0]==0 && a.a[2][1]==0 && a.a[2][2]==1 && a.a[2][3]==0 &&
        a.a[3][0]==0 && a.a[3][1]==0 && a.a[3][2]==0 && a.a[3][3]==1;
}

template <class type, int n>
bool mtx_equ_i(const MtxN<type, n>& a)
{
    return mtx_equ_i_basic(a);
}


//
// Fuzzy equal
//

// mtx_equ_i_fuzzy(Mtx,delta)

template <class type>
bool mtx_equ_i_fuzzy(const Mtx<type>& a, const type& delta) {
    return mtx_equ_i_fuzzy_basic(a, delta);
}

template <class type>
bool mtx_equ_i_fuzzy(const Mtx2<type>& a, const type& delta) {
    return abs(a.a[0][0]-1)<delta && abs(a.a[0][1])<delta &&
        abs(a.a[1][0])<delta && abs(a.a[1][1]-1)<delta;
}

template <class type>
bool mtx_equ_i_fuzzy(const Mtx3<type>& a, const type& delta) {
    return abs(a.a[0][0]-1)<delta && abs(a.a[0][1])  <delta && abs(a.a[0][2])  <delta &&
        abs(a.a[1][0])  <delta && abs(a.a[1][1]-1)<delta && abs(a.a[1][2])  <delta &&
        abs(a.a[2][0])  <delta && abs(a.a[2][1])  <delta && abs(a.a[2][2]-1)<delta;
}

template <class type>
bool mtx_equ_i_fuzzy(const Mtx4<type>& a, const type& delta) {
    return abs(a.a[0][0]-1)<delta && abs(a.a[0][1])  <delta && abs(a.a[0][2])  <delta && abs(a.a[0][3])  <delta &&
        abs(a.a[1][0])  <delta && abs(a.a[1][1]-1)<delta && abs(a.a[1][2])  <delta && abs(a.a[1][3])  <delta &&
        abs(a.a[2][0])  <delta && abs(a.a[2][1])  <delta && abs(a.a[2][2]-1)<delta && abs(a.a[2][3])  <delta &&
        abs(a.a[3][0])  <delta && abs(a.a[3][1])  <delta && abs(a.a[3][2])  <delta && abs(a.a[3][3]-1)<delta;
}

template <class type, int n>
bool mtx_equ_i_fuzzy(const MtxN<type, n>& a, const type& delta) {
    return mtx_equ_i_fuzzy_basic(a.begin(), a.end(), a.size(), delta);
}


//
// bool mtx_equ_i_fuzzy(Mtx)
//

template <class type>
bool mtx_equ_i_fuzzy(const Mtx<type>& a) {
    const_delta<type> delta;
    return mtx_equ_i_fuzzy(a, delta());
}

template <class type>
bool mtx_equ_i_fuzzy(const Mtx2<type>& a) {
    const_delta<type> delta;
    return mtx_equ_i_fuzzy(a, delta());
}

template <class type>
bool mtx_equ_i_fuzzy(const Mtx3<type>& a) {
    const_delta<type> delta;
    return mtx_equ_i_fuzzy(a, delta());
}

template <class type>
bool mtx_equ_i_fuzzy(const Mtx4<type>& a) {
    const_delta<type> delta;
    return mtx_equ_i_fuzzy(a, delta());
}

template <class type, int n>
bool mtx_equ_i_fuzzy(const MtxN<type, n>& a) {
    const_delta<type> delta;
    return mtx_equ_i_fuzzy(a, delta());
}






template <typename type, int n>
int operator == (const MtxN<type, n>& a, const MtxN<type, n>& b)
{
    return mtx_equ(a, b);
}

template <typename type, int n>
int operator != (const MtxN<type, n>& a, const MtxN<type, n>& b)
{
    return !mtx_equ(a, b);
}

}  // namespace

