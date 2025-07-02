/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
// Copyright (C) 2003-2005, 2007 Andrey Mirzoyan
// For conditions of distribution and use see LICENSE file

#if Description__

Standard Deviation measures the spread of the values
SD is defined as square root of variance

#endif

#pragma once

#include "var.hpp"

namespace cognit {

template <class T, class Idx>
T sd(const T *a, Idx n) {
    return std::sqrt(var(a, n)) ;
}


template <class T, class Idx>
T sd(const T *a, Idx n, const T &m) {
    return std::sqrt(var(a,n,m)) ;
}

}  // namespace
