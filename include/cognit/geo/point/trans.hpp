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
        Point Translation
*/

#include "../../mat/matrix.hpp"


namespace cognit {





//
// calculates m = Rp
//
template <class T, class P, class U>
U &pt_rot ( P &p, const mat::Mtx2<T> &R, U &m )
{
    m.x = R.a[0][0]*p.x + R.a[0][1]*p.y ;
    m.y = R.a[1][0]*p.x + R.a[1][1]*p.y ;

    return m ;
}


// apply v'=R(v+t)
template <class T, class P, class U, class V>
V &pt_Rt_ ( const P &p, const mat::Mtx2<T> &R, const U &t, V &m )
{
    V v ;
    v.x = p.x + t.x, v.y = p.y + t.y ;
    pt_rot(v,R,m) ;

    return m ;
}

template <class T, class P, class U>
P &pt_Rt_ ( P &p, const mat::Mtx2<T> &R, const U &t )
{
    P v ;
    v.x = p.x + t.x, v.y = p.y + t.y ;
    pt_rot(v,R,p) ;

    return p ;
}

template <class T, class P, class U, class V>
V &pt_R_t_ ( const P &p, const mat::Mtx2<T> &R, const U &t, V &m )
{
    pt_rot(p,R,m) ;
    m.x -= t.x, m.y -= t.y ;

    return m ;
}

template <class T, class P, class U>
P &pt_R_t_ ( P &p, const mat::Mtx2<T> &R, const U &t )
{
    P v ;
    pt_rot(p,R,v) ;
    p.x = v.x - t.x, p.y = v.y - t.y ;

    return p ;
}

}

