/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include "../complex.hpp"
#include "../vec.hpp"
#include "../mtx.hpp"


namespace cognit {

//
// Real Valued Matrices
//


template <class T>
void eigen_values(const Mtx2<T>& a, Vec2<Complex<T>>& e)
{
    // direct calculation - solving quadratic equation

    auto t = a.a[0][0] - a.a[1][1];
    auto p = a.a[0][0] + a.a[1][1];
    auto d = 4*a.a[0][1]*a.a[1][0] + t*t;  // discriminant



    if (d < 0) {
        e.a[0].a = e.a[1].a = p/2;

        d = sqrt(-d);

        e.a[0].b = d/2;  // take first eigen value with positive imaginary part
        e.a[1].b = -d/2;  // just for the sake of consistency
    } else
        if (d == 0) {
            e.a[0].a = e.a[1].a = p/2;  // both roots are same
        } else {

            d = std::sqrt(d);

            e.a[0].b = e.a[1].b = 0;


            e.a[0].a = (p+d)/2;
            e.a[1].a = (p-d)/2;


            if (abs(e.a[0].a) < abs(e.a[1].a))  // real roots
                swap(e.a[0], e.a[1], t);
        }
}



template <class T>
void eigen_values(const Mtx3<T>& a, Vec3<Complex<T> >& e)
{
    // coefficients for 3-d degree matrix
    // do direct calculation - solving cubic equation
    T k[3];

    k[0] = -(a.a[0][0] + a.a[1][1] + a.a[2][2]);

    k[1] = -(a.a[0][1]*a.a[1][0] 
           - a.a[0][0]*a.a[1][1] 
           + a.a[0][2]*a.a[2][0] 
           + a.a[1][2]*a.a[2][1] 
           - a.a[0][0]*a.a[2][2] 
           - a.a[1][1]*a.a[2][2]);

    k[2] = a.a[0][0] * (a.a[1][2]*a.a[2][1] - a.a[1][1]*a.a[2][2]) 
         + a.a[0][1] * (a.a[1][0]*a.a[2][2] - a.a[1][2]*a.a[2][0]) 
         + a.a[0][2] * (a.a[1][1]*a.a[2][0] - a.a[1][0]*a.a[2][1]);

    // solve the equation of 3-d degree
    EquSolvePoly3(k, e.a);

    // sort eigen values
}





}

