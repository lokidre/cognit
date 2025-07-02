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
#include "../line.hpp"




namespace cognit {

template <class T>
bool on_line ( const APoint3D<T> &a, const APoint3D<T> &b, const APoint3D<T> &c )
{
    const eps = mat::const_delta<T>()() ;

    Vec3<type>
            bv = { b.x-a.x, b.y-a.y, b.z-a.z },
            cv = { c.x-a.x, c.y-a.y, c.z-a.z },
            nv ;

    vct_cross ( bv, cv, nv ) ;

    return mat::tiny(nv.x,eps) && mat::tiny(nv.y,eps) && mat::tiny(nv.z,eps) ? true : false ;
}

template <class T>
bool on_line_x ( const APoint3D<T> &a, const APoint3D<T> &b, const APoint3D<T> &c )
{
    Vec3<T>
            bv = {b.x-a.x,b.y-a.y,b.z-a.z},
            cv = {c.x-a.x,c.y-a.y,c.z-a.z},
            nv ;
    vct_cross ( bv, cv, nv ) ;
    return nv.x==0 && nv.y==0 && nv.z==0 ? true : false ;
}


template <class T>
bool on_line ( APoint2D<T> a, APoint2D<T> b, APoint2D<T> c )
{
    b.x -= a.x, b.y -= a.y ;
    c.x -= a.x, c.y -= a.y ;

    a.x = b.x*c.y - c.x*b.y ;

    return mat::tiny(a.x) ? true : false ;
}

}

