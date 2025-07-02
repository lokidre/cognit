/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include "../def.hpp"
#include "../func.hpp"
#include "../complex.hpp"


namespace cognit {


// find roots of equation
//
//    x^3 + k_0 x^2 + k_1 x + k_2  == 0
//


// Cardano method
//
// x_container_type::value_type must be of complex type
//

template <class T>
void solve_poly_3(const T* k, Complex<T>* x) noexcept
{
    T q, r, q3, r2, t, a, b;

    const T pi = const_pi<T>()();
    const T sqrt3 = const_sqrt3<T>()();


    q = (k[0]*k[0]-3*k[1])/9;
    r = (2*k[0]*k[0]*k[0]-9*k[0]*k[1]+27*k[2])/54;

    q3 = q*q*q, r2 = r*r;

    if (r2 <= q3) {  // the equation has three real roots
        t = acos(r/sqrt(q3))/3;
        a = k[0] / 3, q=-2*sqrt(q);
        x[0].a = q*cos(t) - a;
        x[1].a = q*cos(t+2*pi/3) - a;
        x[2].a = q*cos(t-2*pi/3) - a;
        x[0].b = x[1].b = x[2].b = 0;
    } else {
        a = -sign(r) * pow(abs(r)+sqrt(r2-q3), T(1)/3);

        b = (tiny(a)) ? 0 : q/a;

        // real root
        x[0].a = (a+b)-k[0]/3;
        x[0].b = 0;

        // complex roots
        x[1].a = x[2].a = -(a+b)/2 - k[0]/3;
        x[1].b = (a-b)*sqrt3/2;
        x[2].b = -x[1].b;
    }

}


// finds only real roots of cubic equation
// returns number of distinct real roots 
template <class T>
int solve_poly_3_real(const T* k, T* x) noexcept
{
    T q, r, q3, r2, t, a;

    const T pi = const_pi<T>()();

    q = (k[0]*k[0]-3*k[1])/9;
    r = (2*k[0]*k[0]*k[0]-9*k[0]*k[1]+27*k[2])/54;

    q3 = q*q*q, r2 = r*r;

    t = acos(r/sqrt(q3))/3;
    a = k[0]/3, q = sqrt(q)*(-2);
    x[0] = q*cos(t) - a;

    if (r2 > q3)
        return 1;

    x[1] = q*cos(t+2*pi/3) - a;
    x[2] = q*cos(t-2*pi/3) - a;

    return x[1] == x[2] ? 2 : 3;
}



}  // namespace
