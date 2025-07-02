/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once


namespace cognit {


//
// normalization routines
//
template <class T>
AParametricLine<T> &normalize ( AParametricLine<T> &a )
{
    // first make the colinar vector unit
    const T l = hypot(a.u.x,a.u.y) ;
    if ( mat::tiny(l) )
        return a ;
    a.u.x /= l, a.u.y /= l ;

    // make it directing in first or second quarters
    if ( a.u.x < 0 && a.u.y < 0 ) {
        a.u.x = -a.u.x, a.u.y = -a.u.y ;
    } else {
        if ( a.u.x >= 0 && a.u.y <= 0 )
            a.u.x = -a.u.x, a.u.y = -a.u.y ;
    }


    // now make p going orthogonal to p
    // find the point on line on which is perpendicular to axis 0
    // use two conditions:
    // r~ = p~ + tu~
    // r~.p~ = 0

    const T t = a.u.x * a.p.y - a.u.y * a.p.x ;

    a.p.x = -a.u.y * t ;
    a.p.y = a.u.x * t ;

    return a ;
}


//
// normalization routines
//
//TODO :
template <class T>
ANormalLine<T> &normalize ( ANormalLine<T> &u )
{
    // keep theta between 0 and pi
    // T pi = const_pi<T>()() ;
    //T pi2 = pi/2 ;

    // while ( u.t < 0 )
    return u ;
}


}
