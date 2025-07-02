/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include <cfloat>
#include <cmath>  // standard headers

#include <apeal/def.hpp>
#include <apeal/index.hpp>
#include <apeal/string.hpp>

namespace cognit {

using Index = apl::Index;
using String = apl::String;
using StrView = apl::StrView;

}  // namespace cognit


/*
namespace cognit {

template <class T>
inline
void swap ( T &a, T &b, T &t )
{
	t = a, a = b, b = t ;
}


#ifndef min
template <class T>
inline T min ( const T &a, const T &b ) {  return a < b ? a : b ;  }
#endif


#ifndef max
template <class T>
inline T max ( const T &a, const T &b ) {  return a > b ? a : b ;  }
#endif


}  // namespace 

*/
