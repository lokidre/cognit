/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include "../../mat/func.hpp"

namespace cognit {

// needed - convert to implicit line


//
// line conversion routines
//
template <class T>
AExplicitLine<T> &line_convert ( const AParametricLine<T> &p, AExplicitLine<T> &e )
{
    if ( tiny(p.u.x) )
        throw std::runtime_error("conversion error") ;
    e.a = p.u.y/p.u.x ;
    e.b = p.p.y - p.p.x * e.a ;
    return e ;
}

template <class T>
APointLine<T> &line_convert ( const AParametricLine<T> &p, APointLine<T> &e )
{
    e.u.x = p.p.x, e.u.y = p.p.y ;
    e.v.x = p.p.x + p.u.x, e.v.y = p.p.y + p.u.y ;
    return e ;
}


/*
template <class T>
inline
ANormalLine<T> &line_convert ( const AParametricLine<T> &p, ANormalLine<T> &e )
{
    //if ( p.u.x > p.u.y )  // chose the larger value to lessen the error
    //  e.t = acos(p.u.x) ;
    //else
    //  e.t = asin(p.u.y) ;

TODO: error !!!
    T x = p.u.x, y = p.u.y ;
    if ( x < 0 )
        x = -x, y = -y ;
    e.t = asin(y) + const_pi<T>()()/2 ;

    e.r = p.p.y * p.u.x + p.p.x * p.u.y ;
    return e ;
}
*/



template <class T>
inline
AParametricLine<T> &line_convert ( const ANormalLine<T> &p, AParametricLine<T> &e )
{
    e.u.x = -sin(p.t) ;
    e.u.y = cos(p.t) ;

    //
    // here there is no precise p, chose one that is orthogonal to u
    //

    e.p.x = e.u.y * p.r ;
    e.p.y = -e.u.x * p.r ;

    return e ;
}


// NOTE: 0 <= t <= pi
template <class T>
inline
AImplicitLine<T> &line_convert ( const ANormalLine<T> &u, AImplicitLine<T> &v )
{
    // first point is intersection or r~ vector the the line itself
    APoint2D<T> p, q ;
    T cs = cos(u.t), sn = sin(u.t) ;


    T pi = const_pi<T>()() ;

    // check for vertical and horizontal lines
    if ( tiny(u.t) ) {
        v.a = 1 ;
        v.b = 0 ;
        v.c = -u.r ;
        return v ;
    }

    if ( tiny(pi/2-u.t) ) {
        v.a = 0 ;
        v.b = 1 ;
        v.c = -u.r ;
        return v ;
    }

    if ( tiny(u.r) ) {
        // TODO: needed
        //if ( u.t < pi/4 || u.t > pi*3/4 ) {
        //  v.a = 1 ;
        //  v.b =
        //} else {
            v.a = -atan(u.t-pi/2) ;
            v.b = 1 ;
        //}

        v.c = 0 ;
        return v ;
    }

    p.x = cs*u.r ;
    p.y = sn*u.r ;

    // next is the intersection of either ox or oy axes
    // then we will have 2 points from which we will be able to deduce implicit equation
    if ( u.t < pi/4 || u.t > pi*3/4 ) { // line is more vertical (ox axis)
        q.x = u.r / cs ;
        q.y = 0 ;

        v.a = 1 ;
        v.b = ( p.x - q.x ) / ( q.y - p.y ) ;
        v.c = -v.b*p.y - p.x ;

    } else {
        q.x = 0 ;
        q.y = u.r / sn ;

        v.a = ( p.y - q.y ) / ( q.x - p.x ) ;
        v.b = 1 ; // y component
        v.c = -v.a*p.x - p.y ;
    }

    return v ;
}


template <class T>
ANormalLine<T> &line_convert ( const APointLine<T> &p, ANormalLine<T> &e )
{
    T lambda = ( (-p.u.x)*(p.v.x-p.u.x) + (-p.u.y)*(p.v.y-p.u.y) ) / ( sqr(p.v.x-p.u.x) + sqr(p.v.y-p.u.y) ) ;
    T x = p.u.x + lambda*(p.v.x-p.u.x) ;
    T y = p.u.y + lambda*(p.v.y-p.u.y) ;
    e.r = hypot(x,y) ;
    bool flip = false;

    if ( y < 0 )
        flip = true ;

    if ( flip )
        e.r = -e.r, y = -y ;

    if ( abs(x) > abs(y) )
        e.t = asin(y/x) ;
    else
        e.t = acos(x/y) ;

    if ( flip )
        e.t = const_pi<T>()() - e.t ;

    return e ;
}


}
