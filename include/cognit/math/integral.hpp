/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include "gquad.hpp"




/*
        Calculate Definite Integral


*/

namespace cognit {

template <class T, class F>
T integral(F& f, T a, T b)
{
    auto n = gquad_max_degree;  // degree of Gaussian Quadrature

    return gquad(f, a, b, n);
}

}


