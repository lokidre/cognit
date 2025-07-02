/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include "../vec.hpp"
//#include "../func.hpp"

//#include <apeal/geo.hpp>


namespace cognit {


// comparing points
template <class T>
bool pt_equ_fuzzy(const Vec3<T>& u, const Vec3<T>& v)
{
    return Equ(u.x, v.x) && Equ(u.y, v.y) && Equ(u.z, v.z);
}

template <typename type>
bool pt_equ_fuzzy(const APoint2D<type>& u, const APoint2D<type>& v)
{
    return Equ(u.x, v.x) && Equ(u.y, v.y);
}


template <typename T>
bool pt_equ(const Point3D<T>& u, const Point3D<T>& v)
{
    return u.x==v.x && u.y==v.y && u.z==v.z;
}

template <typename T>
bool pt_equ(const APoint2D<T>& u, const APoint2D<T>& v)
{
    return u.x==v.x && u.y==v.y;
}


// the distance between two points
template <class T>
T pt_dist(const Point3D<T>& p, const Point3D<T>& q)
{
    T x = p.x - q.x, y = p.y - q.y, z = p.z - q.z;

    // avoiding overflow
    T m = x>y ? (x>z ? x : z) : (y>z ? y : z);
    if (m == 0) // needed fuxxy
        return 0;
    x /= m, y /= m, z /= m;
    return sqrt(x*x + y*y + z*z)*m;
}

template <class T>
T pt_dist(const APoint2D<T>& p, const APoint2D<T>& q)
{
    T x = p.x - q.x, y = p.y - q.y;
    return std::hypot(x, y);
}

template <class T, class P1, class P2>
T pt_dist_2d(const P1& p, const P2& q)
{
    T x = p.x - q.x, y = p.y - q.y;
    return std::hypot(x, y);
}

// the square of disteance between two points
template <class T>
T pt_dist_sqr(const Point3D<T>& u, const Point3D<T>& v)
{
    T x = u.x - v.x, y = u.y - v.y, z = u.z - v.z;
    return x*x + y*y + z*z;
}

template <class T>
T pt_dist_sqr(const APoint2D<T>& u, const APoint2D<T>& v)
{
    T x = u.x - v.x, y = u.y - v.y;
    return x*x + y*y;
}

template <class T, class point_type>
T pt_dist_sqr_2d(const point_type& u, const point_type& v)
{
    T x = u.x - v.x, y = u.y - v.y;
    return x*x + y*y;
}

/*
template <class T, class point_type>
inline
T pt_dist_2 ( const point_type &u, const point_type &v )
{
    T x = u.x - v.x, y = u.y - v.y ;
    return hypot(x,y) ;
}
*/


//
// min max points
//
template <class iT, class T>
void minmax_x(const iT begin, const iT end, T& minx, T& maxx)
{
    iT p = begin;
    if (p == end)
        return;

    minx = maxx = p->x;
    for (++p; p != end; ++p) {
        if (p->x < minx)
            minx = p->x;
        else
            if (p->x > maxx)
                maxx = p->x;
    }
}

template <class iT, class T>
void minmax_y(const iT begin, const iT end, T& miny, T& maxy)
{
    iT p = begin;
    if (p == end)
        return;

    miny = maxy = p->y;
    for (++p; p != end; ++p) {
        if (p->y < miny)
            miny = p->y;
        else
            if (p->y > maxy)
                maxy = p->y;
    }
}


}  // namespace
