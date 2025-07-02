/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include <cmath>

#include "const.hpp"

namespace cognit {


//template <class T>
//T sqrt ( const T &x ) { return std::sqrt(x) ;  }

template <class T>
T hypot(T x, T y)
{
#if _MSC_VER >= 1400
    return (T)::_hypot(x, y);
#else
    return (T)::hypot(x, y);
#endif
}

template <class T>
T ln(T x) noexcept
{
    return std::log(x);
}

template <class T>
T exp(T x) noexcept
{
    return std::exp(x);
}

template <class T>
T pow(T x, T y) noexcept
{
    return std::pow(x, y);
}


template <class T>
constexpr T sqr(T x) noexcept { return x * x; }


template <class T>
T acos(T x) noexcept { return std::acos(x); }

template <class T>
T asin(T x) noexcept { return std::asin(x); }


template <class T>
T cos(T x) noexcept { return std::cos(x); }

template <typename T>
T sin(T x) noexcept
{
    return std::sin(x);
}

template <class T>
T tan(T x) noexcept
{
    return std::tan(x);
}


//#ifdef signbit
//template <class T>
//inline int sign ( const T &x ) {  return signbit(x) ;  }
//#else
//template <class T>
//inline int sign ( const T &x ) {  return x < 0 ? -1 : 1 ;  }


template <class T>
constexpr bool tiny(T x, T delta) noexcept
{
    return x <= delta && x >= -delta;
}

template <class T>
constexpr bool tiny(T x) noexcept
{
    return tiny(x, constants::delta<T>);
}


template <class T>
constexpr bool big(T x, T m) noexcept
{
    return x >= m || x <= -m;
}


//template <class type>
//bool close(const type& x, const type& y, const type& eps)
//{
//    return tiny(x-y, eps);
//}



}  // namespace cognit
