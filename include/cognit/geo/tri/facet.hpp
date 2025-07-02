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

// Calculate the z of vector product of ab & bc
//   Vec3<type> ab, bc, v ;
//   ab.x = tri.b.x - tri.a.x, ab.y = tri.b.y - tri.a.y, ab.z = 0 ;
//   bc.x = tri.c.x - tri.b.x, bc.y = tri.c.y - tri.b.y, bc.z = 0 ;
//   VectorProduct3D ( ab, bc, v ) ;
//   return v.z > 0 ? true : false ;
#define IsTriFacet2D(_a,_b,_c) \
(  \
  (((_b).x-(_a).x)*((_c).y-(_b).y)-((_c).x-(_b).x)*((_b).y-(_a).y)) > 0 \
)


//inline void TriFacet2D ( tTri &t, bool f = true )
//{
//  if ( f != IsTriFacet2D(t.a,t.b,t.c) )
//    Swap(t.b,t.c) ;
//}



template <class type>
bool IsTriFacet(const Vec3<type>& a, const Vec3<type>& b, const Vec3<type>& c, const APoint3D<type>& p) noexcept
{
    mat::Mtx3<type> m;

    m.a[0][0] = b.x-a.x, m.a[0][1] = b.y-a.y, m.a[0][2] = b.z-a.z;
    m.a[1][0] = c.x-a.x, m.a[1][1] = c.y-a.y, m.a[1][2] = c.z-a.z;
    m.a[2][0] = p.x-a.x, m.a[2][1] = p.y-a.y, m.a[2][2] = p.z-a.z;

    return mtx_det(m) < 0;
}

template <class type>
bool IsTriFacet(ATriangle3D<type>& t, APoint3D<type>& p)
{
    return IsTriFacet(t.a, t.b, t.c, p);
}



template <class type>
void TriFacet(APoint3D<type>& a, APoint3D<type>& b, APoint3D<type>& c, APoint3D<type>& p, bool face)
{
    if (IsTriFacet(a, b, c, p) != face)
        Swap(b, c);
}

template <class type>
void TriFacetP(Point3D<type>*& a, Vec3<type>*& b, Point3D<type>*& c, Point3D<type>*& p, bool face)
{
    if (IsTriFacet(*a, *b, *c, *p) != face)
        Swap(b, c);
}


template <class type>
void TriFacet(ATriangle3D<type>& t, Vec3<type>& p, bool face)
{
    if (IsTriFacet(t.a, t.b, t.c, p) != face)
        Swap(t.b, t.c);
}

}  // namespace
