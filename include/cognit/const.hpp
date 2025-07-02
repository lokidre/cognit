/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include "def.hpp"

//#if __has_include(<numbers>)
//#include <numbers>
//#endif

namespace cognit {

namespace constants {

//template <class T>
//constexpr T pi() {  return T(3.14159265358979323846) ;  }
template <class T>
inline constexpr T pi{T(3.141592653589793238462643383279502884L)};

template <class T>
inline constexpr T sqrt2{T(1.4142135623730950488)};
//constexpr T sqrt2() noexcept { return T(1.4142135623730950488); }
//constexpr T sqrt2() noexcept { return std::numbers::sqrt2_v<T>; }

// The smallest number representable by floating point number
template <class T>
inline constexpr T epsilon{std::numeric_limits<T>::epsilon()};

// A little larger than epsilon
template <class T>
inline constexpr T delta{std::numeric_limits<T>::epsilon() * 10};

}  // namespace constants

//template <class value_type>
//struct const_basic {
//    value_type value;
//    value_type& operator()() { return value; }
//};


//
// pi number
//
//template <class T>
//struct const_pi: public const_basic<T> {
//    const_pi() { this->value = T(3.14159265358979323846); }
//};

//template <class T>
//constexpr T pi() { return T(3.141592653589793238462643383279502884L); }


//
// e number
//
//template <class value_type>
//struct const_e: public const_basic<value_type> {
//    const_e() { this->value = value_type(2.71828182845904523536); }
//};


//
// infinity
//

//#ifdef _MSC_VER
//#ifndef HUGE_VALF
//#define HUGE_VALF float(HUGE_VAL)
//#define HUGE_VALL HUGE_VAL
//#endif
//#endif


//template <typename value_type>
//struct const_inf: public const_basic<value_type> {
//    const_inf() { this->value = value_type(2.71828182845904523536); }
//};
//
//template <>
//struct const_inf<double>: public const_basic<double> {
//    const_inf() { this->value = HUGE_VAL; }
//};
//
//template <>
//struct const_inf<float>: public const_basic<float> {
//    const_inf() { this->value = HUGE_VALF; }
//};
//
//template <>
//struct const_inf<long double>: public const_basic<long double> {
//    const_inf() { this->value = HUGE_VALL; }
//};



//
// epsilon
//

//template <class T>
//struct const_eps: public const_basic<T> {
//    const_eps() { this->value = DBL_EPSILON; }
//};
//
//template <>
//struct const_eps<double>: public const_basic<double> {
//    const_eps() { this->value = DBL_EPSILON; }
//};
//
//template <>
//struct const_eps<float>: public const_basic<float> {
//    const_eps() { this->value = FLT_EPSILON; }
//};
//
//template <>
//struct const_eps<long double>: public const_basic<long double> {
//    const_eps() { this->value = LDBL_EPSILON; }
//};


////
//// delta - a little bigger than epsilon
////
//template <class T>
//struct const_delta: public const_eps<T> {
//    const_delta(): const_eps<T>() { this->value *= 10000; }
//};
//
//
//template <class T>
//struct const_sqrt2: public const_basic<T> {
//    const_sqrt2() { this->value = (T)1.4142135623730950488; }
//};
//
//template <class T>
//struct const_sqrt3: public const_basic<T> {
//    const_sqrt3() { this->value = (T)1.7320508075688772935; }
//};
//
//
//template <class T>
//struct const_cbrt2: public const_basic<T> {
//    const_cbrt2() { this->value = (T)1.2599210498948731648; }
//};
//
//template <class T>
//struct const_cbrt3: public const_basic<T> {
//    const_cbrt3() { this->value = (T)1.4422495703074083823; }
//};


}  // namespace cognit
