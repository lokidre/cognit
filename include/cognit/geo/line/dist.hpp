/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once


/*
    Distance from point to a line
*/


namespace cognit {

//
// Distance from point p to implicit line u (ax+bx+c=0)
// is calculated as d = |a p.x + b p.y + c | / ||n||
// where ||n|| = normalized vector (a,b)
//
template <class T>
T dist ( const APoint2D<T> &p, const AExplicitLine<T> &u )
{
    T n = hypot(u.a,T(-1)) ;
    T d(0) ;

    if ( tiny(n) )
        return d ;

    d = abs(-p.y + u.a*p.x + u.b) / n ;

    return d ;
}


// error needed
template <class P, class T>
T pt_dist ( const P &p, const AParametricLine<T> &l )
{
    // d = | p - (p.u)u |

    T b = p.x * l.u.x + p.y * l.u.y ;
    return hypot(p.x - b*l.u.x, p.y - b*l.u.y) ;
}


template <class P, class T>
T pt_dist ( const P &p, const ANormalLine<T> &l )
{
    return abs(p.x * cos(l.t) + p.y * sin(l.t) - l.r) ;
}


}
