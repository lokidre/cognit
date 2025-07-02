/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#if 0

Straight line prepresentation
----

General Equation(Implicit)

    ax + by + c = 0

where a, b or both are not zero


Explicit Equation

    y = ax + b


Normalized equation when a^2 + b^2 = 1 then

    \mathbf{n} = (a, b)


Parametric equation

    \mathbf{r} = r_0 + t\mathbf{u}

where

    r = (x, y)
    r_0 = point through the line should go
    \mathbf{u} = parallel vector


Normal Form

    x \cos(t) + y \sin(t) = r

#endif


#include "../vec.hpp"

//#include "vector.hpp"
//#include "point.hpp"





namespace cognit {

//
// y=ax+b representation
//
template <class T>
struct ExplicitLine {
    T a, b;
};



//
// Line is represented as two vectors
//
template <class T>
struct ParametricLine {
    Vec2<T> p, u;  // u - colinear vector
};


// 
// Line is represented by angle of the norm (theta) and distance rho
//       
template <class T>
struct NormalLine {
    T r, t;  // rho, theta
};


//
// Canonic straight line equation ax + by + c = 0
//
template <class T>
struct ImplicitLine {
    T a, b, c;
};


//
// Line is given by two points
template <class T>
struct PointLine {
    Vec2<T> u, v;
};

}  // namespace cognit


