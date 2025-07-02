/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include <apeal/arithm.hpp>

#include "../func.hpp"
#include "../vec.hpp"


namespace cognit {


//
// The square of vector length
//


template <class vector_T>
typename vector_T::value_type vct_norm_basic(const vector_T& v)
{
    typedef typename vector_T::value_type value_type;

    typename vector_T::const_iterator a, a_end;

    // find the max element
    value_type tmp, mx = 0, x = 0;

    for (a = v.begin(), a_end = v.end(); a != a_end; a++)
        if ((tmp = abs(*a)) > mx)
            mx = tmp;

    if (mx == 0)
        return 0;

    for (a = v.begin(), a_end = v.end(); a != a_end; a++)
        x += sqr(*a/mx);

    return sqrt(x) * mx;
}



template <class vector_T>
typename vector_T::value_type vct_norm_sqr_basic(const vector_T& v)
{
    typedef typename vector_T::value_type value_type;
    typedef typename vector_T::const_iterator const_iterator;

    // find the max element
    value_type x = 0;

    for (auto a = v.begin(), a_end = v.end(); a != a_end; a++)
        x += sqr(*a);

    return x;
}



template <class T>
T vct_norm(const Vec<T>& v) { return vct_norm_basic(v); }

template <class T>
T vct_norm(const Vec3<T>& v) noexcept
{
    using namespace std;

    T mx = abs(v.x);
    T a = abs(v.y);
    if (a > mx)
        mx = a;
    a = abs(v.z);
    if (a > mx)
        mx = a;

    return sqrt(sqr(v.x/mx) + sqr(v.y/mx) + sqr(v.z/mx))*mx;
}


template <class T>
T vct_norm(const Vec4<T>& v) noexcept
{
    auto mx = abs(v.x);
    auto a = abs(v.y);
    if (a > mx)
        mx = a;
    a = abs(v.z);
    if (a > mx)
        mx = a;
    a = abs(v.w);
    if (a > mx)
        mx = a;


    auto xx = v.x/mx;
    auto yy = v.y/mx;
    auto zz = v.z/mx;
    auto ww = v.w/mx;

    return sqrt(xx*xx + yy*yy + zz*zz + ww*ww) * mx;
}


/*
template <class vector_T>
inline
typename vector_T::value_type vct_len_sqr ( const vector_T &v )
{
  return v.a[0]*v.a[0] + v.a[1]*v.a[1] ;
}

template <typename type>
inline
type VctLenSqr ( tVector3<type> &v )
{
  return v.a[0]*v.a[0] + v.a[1]*v.a[1] + v.a[2]*v.a[2] ;
}


template <typename type>
inline
type VctLenSqr ( tVector4<type> &v )
{
  return v.a[0]*v.a[0] + v.a[1]*v.a[1] + v.a[2]*v.a[2] + v.a[3]*v.a[3] ;
}


template <typename type, int n>
inline
type VctLenSqr ( tVectorN<type,n> &v )
{
  type t = type(0) ;
  for ( int i = 0 ; i < n ; i++ )
    t += v.a[i]*v.a[i] ;

  return t ;
}



// The length of vector
//

template <typename type>
inline
type vtc_len ( tVector2<type> &v )
{
  return hypot(v.a[0],v.a[1]) ;
}

template <typename type>
inline
type VctLen ( tVector3<type> &v )
{
  return sqrt ( v.a[0]*v.a[0] + v.a[1]*v.a[1] + v.a[2]*v.a[2] ) ;
}


template <typename type>
inline
type VctLen ( tVector4<type> &v )
{
  return sqrt ( v.a[0]*v.a[0] + v.a[1]*v.a[1] + v.a[2]*v.a[2] + v.a[3]*v.a[3] ) ;
}


template <typename type, int n>
inline
type VctLen ( tVectorN<type,n> &v )
{
  return sqrt(VctLenSqr(v)) ;
}

*/


}
