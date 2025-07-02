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

    Detection if two points are on the same side of the straight line or not.
    Makes sense only in 2D case.

    Points given by u and v

    Line given by two points: a and b
    do two cross products va x vb and ua x ub - if they have same sign then points on one side.


    Line is given by its explicit equation (ax+b)



*/


#include "../../mat/func.hpp"
#include "../line.hpp"

namespace cognit {


//
// p q - line
// u v - two points
// return: 0 - one or both points on line, 1 - one side, -1 - diff sides
template <class T>
int line_side ( const APoint2D<T> &p, const APoint2D<T> &q, const APoint2D<T> &u, const APoint2D<T> &v )
{
    const T eps = mat::const_eps<T>()() ;

    const T upx = p.x-u.x, upy = p.y-u.y ;
    const T uqx = q.x-u.x, uqy = q.y-u.y ;
    const T vpx = p.x-v.x, vpy = p.y-v.y ;
    const T vqx = q.x-v.x, vqy = q.y-v.y ;

    const T upqz = upx*uqy - upy*uqx ;
    const T vpqz = vpx*vqy - vpy*vqx ;

    if ( mat::tiny(upqz,eps) || mat::tiny(vpqz,eps) )
        return 0 ;

    return ( upqz > 0 && vpqz > 0 || upqz < 0 && vpqz < 0 )? 1 : -1 ;
}


template <class T>
int line_side ( const ExplicitLine<T> &p, const Point2D<T> &u, const Point2D<T> &v )
{
    const T delta = mat::const_delta<T>()() ;

    const T uz = p.b + p.a*u.x - u.y ;
    const T vz = p.b + p.a*v.x - v.y ;

    if ( mat::tiny(uz,delta) || mat::tiny(vz,delta) )
        return 0 ;

    return uz > 0 && vz > 0 || uz < 0 && vz < 0 ? 1 : -1 ;
}

template <class T>
int line_side ( const AParametricLine<T> &l, const APoint2D<R> &u, const APoint2D<T> &v )
{
    const T delta = mat::const_delta<T>()() ;

    const T uz = l.q.x*(u.y-l.p.y)  - l.q.y*(u.x-l.p.x) ;
    const T vz = l.q.x*(v.y-l.p.y)  - l.q.y*(v.x-l.p.x) ;

    if ( mat::tiny(uz,delta) || mat::tiny(vz,delta) )
        return 0 ;

    return uz > 0 && vz > 0 || uz < 0 && vz < 0 ? 1 : -1 ;
}


}
