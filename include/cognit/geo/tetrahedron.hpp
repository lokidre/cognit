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

namespace cognit {

template <class type>
struct Tetrahedron {
    Vec3<type> a, b, c, d;
};

template <class T>
struct TetrahedronP {
    using VecP = Vec3<T>*;
    VecP a, b, c, d;
};



#define TetEqu(_t1,_t2) \
(  \
  PtEqu3D((_t1).a,(_t2).a) && PtEqu3D((_t1).b,(_t2).b) && PtEqu3D((_t1).c,(_t2).c) && PtEqu3D((_t1).d,(_t2).d) || \
  PtEqu3D((_t1).a,(_t2).a) && PtEqu3D((_t1).b,(_t2).b) && PtEqu3D((_t1).c,(_t2).d) && PtEqu3D((_t1).d,(_t2).c) || \
  PtEqu3D((_t1).a,(_t2).a) && PtEqu3D((_t1).b,(_t2).c) && PtEqu3D((_t1).c,(_t2).b) && PtEqu3D((_t1).d,(_t2).d) || \
  PtEqu3D((_t1).a,(_t2).a) && PtEqu3D((_t1).b,(_t2).c) && PtEqu3D((_t1).c,(_t2).d) && PtEqu3D((_t1).d,(_t2).b) || \
  PtEqu3D((_t1).a,(_t2).a) && PtEqu3D((_t1).b,(_t2).d) && PtEqu3D((_t1).c,(_t2).b) && PtEqu3D((_t1).d,(_t2).c) || \
  PtEqu3D((_t1).a,(_t2).a) && PtEqu3D((_t1).b,(_t2).d) && PtEqu3D((_t1).c,(_t2).c) && PtEqu3D((_t1).d,(_t2).b) || \
  PtEqu3D((_t1).a,(_t2).b) && PtEqu3D((_t1).b,(_t2).a) && PtEqu3D((_t1).c,(_t2).c) && PtEqu3D((_t1).d,(_t2).d) || \
  PtEqu3D((_t1).a,(_t2).b) && PtEqu3D((_t1).b,(_t2).a) && PtEqu3D((_t1).c,(_t2).d) && PtEqu3D((_t1).d,(_t2).c) || \
  PtEqu3D((_t1).a,(_t2).b) && PtEqu3D((_t1).b,(_t2).c) && PtEqu3D((_t1).c,(_t2).a) && PtEqu3D((_t1).d,(_t2).d) || \
  PtEqu3D((_t1).a,(_t2).b) && PtEqu3D((_t1).b,(_t2).c) && PtEqu3D((_t1).c,(_t2).d) && PtEqu3D((_t1).d,(_t2).a) || \
  PtEqu3D((_t1).a,(_t2).b) && PtEqu3D((_t1).b,(_t2).d) && PtEqu3D((_t1).c,(_t2).a) && PtEqu3D((_t1).d,(_t2).c) || \
  PtEqu3D((_t1).a,(_t2).b) && PtEqu3D((_t1).b,(_t2).d) && PtEqu3D((_t1).c,(_t2).c) && PtEqu3D((_t1).d,(_t2).a) || \
  PtEqu3D((_t1).a,(_t2).c) && PtEqu3D((_t1).b,(_t2).a) && PtEqu3D((_t1).c,(_t2).b) && PtEqu3D((_t1).d,(_t2).d) || \
  PtEqu3D((_t1).a,(_t2).c) && PtEqu3D((_t1).b,(_t2).a) && PtEqu3D((_t1).c,(_t2).d) && PtEqu3D((_t1).d,(_t2).b) || \
  PtEqu3D((_t1).a,(_t2).c) && PtEqu3D((_t1).b,(_t2).b) && PtEqu3D((_t1).c,(_t2).a) && PtEqu3D((_t1).d,(_t2).d) || \
  PtEqu3D((_t1).a,(_t2).c) && PtEqu3D((_t1).b,(_t2).b) && PtEqu3D((_t1).c,(_t2).d) && PtEqu3D((_t1).d,(_t2).a) || \
  PtEqu3D((_t1).a,(_t2).c) && PtEqu3D((_t1).b,(_t2).d) && PtEqu3D((_t1).c,(_t2).a) && PtEqu3D((_t1).d,(_t2).b) || \
  PtEqu3D((_t1).a,(_t2).c) && PtEqu3D((_t1).b,(_t2).d) && PtEqu3D((_t1).c,(_t2).b) && PtEqu3D((_t1).d,(_t2).a) || \
  PtEqu3D((_t1).a,(_t2).d) && PtEqu3D((_t1).b,(_t2).a) && PtEqu3D((_t1).c,(_t2).b) && PtEqu3D((_t1).d,(_t2).c) || \
  PtEqu3D((_t1).a,(_t2).d) && PtEqu3D((_t1).b,(_t2).a) && PtEqu3D((_t1).c,(_t2).c) && PtEqu3D((_t1).d,(_t2).b) || \
  PtEqu3D((_t1).a,(_t2).d) && PtEqu3D((_t1).b,(_t2).b) && PtEqu3D((_t1).c,(_t2).a) && PtEqu3D((_t1).d,(_t2).c) || \
  PtEqu3D((_t1).a,(_t2).d) && PtEqu3D((_t1).b,(_t2).b) && PtEqu3D((_t1).c,(_t2).c) && PtEqu3D((_t1).d,(_t2).a) || \
  PtEqu3D((_t1).a,(_t2).d) && PtEqu3D((_t1).b,(_t2).c) && PtEqu3D((_t1).c,(_t2).a) && PtEqu3D((_t1).d,(_t2).b) || \
  PtEqu3D((_t1).a,(_t2).d) && PtEqu3D((_t1).b,(_t2).c) && PtEqu3D((_t1).c,(_t2).b) && PtEqu3D((_t1).d,(_t2).a)    \
)





template <class type>
bool IsPtInTetra(APoint3D<type>& p, ATetrahedron<type>& t)
{
    return false;
}




template <class type>
bool PtInTetXY(APoint3D<type>& pt, ATetrahedron<type>& tet)
{
    if (pt.x < tet.a.x && pt.x < tet.b.x && pt.x < tet.c.x && pt.x < tet.d.x ||
        pt.x > tet.a.x && pt.x > tet.b.x && pt.x > tet.c.x && pt.x > tet.d.x ||
        pt.y < tet.a.x && pt.y < tet.b.y && pt.y < tet.c.y && pt.y < tet.d.y ||
        pt.y > tet.a.x && pt.y > tet.b.y && pt.y > tet.c.y && pt.y > tet.d.y)
        return false;

    ATriangle3D<type> abc(tet.a, tet.b, tet.c),
        acd(tet.a, tet.c, tet.d),
        abd(tet.a, tet.b, tet.d),
        bcd(tet.b, tet.c, tet.d);

    return (PtInTriXY(pt, abc) || PtInTriXY(pt, acd) || PtInTriXY(pt, abd) || PtInTriXY(pt, bcd));
}


template <class type>
bool TetSectXY(ATetrahedron<type>& tet, APoint3D<type>& pt)
{
    ATriangle3D<type> abc(tet.a, tet.b, tet.c),
        acd(tet.a, tet.c, tet.d),
        abd(tet.a, tet.b, tet.d),
        bcd(tet.b, tet.c, tet.d);

    APoint3D<type> tpt[4];
    type MinZ = const_inf<type>()();

    tpt[0] = tpt[1] = tpt[2] = tpt[3] = pt;

    if (TriSectXY(abc, tpt[0]))
        MinZ = Min(MinZ, tpt[0].z);

    if (TriSectXY(acd, tpt[1]))
        MinZ = Min(MinZ, tpt[1].z);

    if (TriSectXY(abd, tpt[2]))
        MinZ = Min(MinZ, tpt[2].z);

    if (TriSectXY(bcd, tpt[3]))
        MinZ = Min(MinZ, tpt[3].z);

    if (MinZ == const_inf<type>()())
        return false;

    pt.z = MinZ;


    /*
    type abx = tri.b.x-tri.a.x, aby = tri.b.y-tri.a.y, abz = tri.b.z-tri.a.z ;
    type acx = tri.c.x-tri.a.x, acy = tri.c.y-tri.a.y, acz = tri.c.z-tri.a.z ;
    type adx = tri.d.x-tri.a.x, ady = tri.d.y-tri.a.y, adz = tri.d.z-tri.a.z ;
    type bcx = tri.c.x-tri.b.x, bcy = tri.c.y-tri.b.y, bcz = tri.c.z-tri.b.z ;
    type bdx = tri.d.x-tri.b.x, bdy = tri.d.y-tri.b.y, bdz = tri.d.z-tri.b.z ;

    pt.z = INIFINITE ;

    type axx = pt.x-tri.a.x, axy = pt.y-tri.a.y, axz ;
    type div = acx*aby - abx*acy ;

    if ( !Zero(div) ) {
      axz = ( (axx*aby - abx*axy)*acz + (acx*axy - axx*acy)*abz ) / div ;
      pt.z = axz + tri.a.z ;
    }
    */

    return true;
}



template <class type>
void TetRight(Tetrahedron<type> tet, ATriangle3D<type>* tri)
{
    tri[0].a = tet.a, tri[0].b = tet.b, tri[0].c = tet.c;
    tri[1].a = tet.a, tri[1].b = tet.c, tri[1].c = tet.d;
    tri[2].a = tet.a, tri[2].b = tet.d, tri[2].c = tet.b;
    tri[3].a = tet.b, tri[3].b = tet.d, tri[3].c = tet.c;

    TriFacet(tri[0], tet.d, false);
    TriFacet(tri[1], tet.b, false);
    TriFacet(tri[2], tet.c, false);
    TriFacet(tri[3], tet.a, false);


    /*
    APoint3D<type> meanpt ;

    meanpt.x = ( tet.a.x + tet.b.x + tet.c.x + tet.d.x ) / 4 ;
    meanpt.y = ( tet.a.y + tet.b.y + tet.c.y + tet.d.y ) / 4 ;
    meanpt.z = ( tet.a.z + tet.b.z + tet.c.z + tet.d.z ) / 4 ;



    APoint3D<type> vpt ;

    for ( int itri = 0 ; itri < 4 ; itri++ ) {

      Vec3<type> ab (tri[itri].b.x-tri[itri].a.x,tri[itri].b.y-tri[itri].a.y,tri[itri].b.z-tri[itri].a.z),
                      ac (tri[itri].c.x-tri[itri].a.x,tri[itri].c.y-tri[itri].a.y,tri[itri].c.z-tri[itri].a.z),
                      vabc ;

      VctProd3D(ab,ac,vabc) ;

      vpt.x = vabc.x + tri[itri].a.x, vpt.y = vabc.y + tri[itri].a.y, vpt.z = vabc.z + tri[itri].a.z ;

      if ( !PlOneSide ( meanpt, vpt, tri[itri].a, tri[itri].b, tri[itri].c ) )
        Swap ( tri[itri].b, tri[itri].c ) ;
    }
    */


}


template <class type>
void TetRightP(TetrahedronP<type> tet, ATriangle3DP<type>* tri)
{
    tri[0].a = tet.a, tri[0].b = tet.b, tri[0].c = tet.c;
    tri[1].a = tet.a, tri[1].b = tet.c, tri[1].c = tet.d;
    tri[2].a = tet.a, tri[2].b = tet.d, tri[2].c = tet.b;
    tri[3].a = tet.b, tri[3].b = tet.d, tri[3].c = tet.c;

    TriFacetP(tri[0].a, tri[0].b, tri[0].c, tet.d, false);
    TriFacetP(tri[1].a, tri[1].b, tri[1].c, tet.b, false);
    TriFacetP(tri[2].a, tri[2].b, tri[2].c, tet.c, false);
    TriFacetP(tri[3].a, tri[3].b, tri[3].c, tet.a, false);
}

}  // namespace

