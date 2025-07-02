/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include "../func.hpp"
#include "../complex.hpp"


namespace cognit {

/*
    Solving

    $$
        x^2 + bx + c == 0
    $$

*/


// 
// Returns all the roots of quadratic equasion
//

template <class T>
void solve_poly_2(T k1, T k2, Complex<T>& x0, Complex<T>& x1) noexcept
{
    T d = k1*k1 - k2*4;

    if (d < 0) {
        d = std::sqrt(-d);

        x0.a = x1.a = -k1/2;
        x0.b = -d/2, x1.b = d/2;

    } else {

        x0.b = x1.b = 0;

        if (d == 0) {
            x0.a = x1.a = -k1/2;
        } else {

            d = sqrt(d);

            x0.a = (-k1-d)/2;
            x1.a = (-k1+d)/2;
        }
    }

}


//
// Solve quadratic equasion. 
// Find only real roots. Returns number of real roots.
//

template <class T>
int solve_poly_2_real(T k1, T k2, T& x0, T& x1) noexcept
{
    T d = k1*k1 - k2*4;

    if (d < 0)
        return 0;

    if (d == 0) {
        x0 = -k1/2;
        return 1;
    }

    d = sqrt(d);

    x0 = (-k1-d)/2;
    x1 = (-k2+d)/2;

    return 2;
}

}  // namespace

