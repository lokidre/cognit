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

template <typename type>
struct Triangle2 {
    Vec2<type> a, b, c;
};

template <typename type>
struct Triangle2P {
    Vec2<type>* a, * b, * c;
};

template <class I>
struct Triangle2I {
    I a, b, c;
};


template <class T>
struct Triangle3 {
    Vec3<T> a, b, c;
};


template <class T>
struct Triangle3DP {
    Point3D<T>* a, * b, * c;
};


template <typename type>
char* unistr(ATriangle3D<type>& t, char* str, int flags = 0)
{
    int ofs = 0;
    ofs += strlen(unistr(t.a, &str[ofs], flags)), str[ofs++] = ' ', str[ofs++] = ' ';
    ofs += strlen(unistr(t.b, &str[ofs], flags)), str[ofs++] = ' ', str[ofs++] = ' ';
    ofs += strlen(unistr(t.c, &str[ofs], flags)), str[ofs++] = ' ', str[ofs++] = ' ';
    str[ofs++] = '\0';
    return str;
}

template <typename type>
char* unistr(tTriangle3DP<type>& t, char* str, int flags = 0)
{
    int ofs = 0;
    ofs += strlen(unistr(*t.a, &str[ofs], flags)), str[ofs++] = ' ', str[ofs++] = ' ';
    ofs += strlen(unistr(*t.b, &str[ofs], flags)), str[ofs++] = ' ', str[ofs++] = ' ';
    ofs += strlen(unistr(*t.c, &str[ofs], flags)), str[ofs++] = ' ', str[ofs++] = ' ';
    str[ofs++] = '\0';
    return str;
}





template <typename type>
bool TriEqu(ATriangle3D<type>& t1, ATriangle3D<type>& t2)
{
    return
        PtEqu(t1.a, t2.a) && PtEqu(t1.b, t2.b) && PtEqu(t1.c, t2.c) ||
        PtEqu(t1.a, t2.a) && PtEqu(t1.b, t2.c) && PtEqu(t1.c, t2.b) ||
        PtEqu(t1.a, t2.b) && PtEqu(t1.b, t2.a) && PtEqu(t1.c, t2.c) ||
        PtEqu(t1.a, t2.b) && PtEqu(t1.b, t2.c) && PtEqu(t1.c, t2.a) ||
        PtEqu(t1.a, t2.c) && PtEqu(t1.b, t2.a) && PtEqu(t1.c, t2.b) ||
        PtEqu(t1.a, t2.c) && PtEqu(t1.b, t2.b) && PtEqu(t1.c, t2.a);
}


template <typename type>
bool TriEquX(ATriangle3D<type>& t1, ATriangle3D<type>& t2)
{
    return
        PtEquX(t1.a, t2.a) && PtEquX(t1.b, t2.b) && PtEquX(t1.c, t2.c) ||
        PtEquX(t1.a, t2.a) && PtEquX(t1.b, t2.c) && PtEquX(t1.c, t2.b) ||
        PtEquX(t1.a, t2.b) && PtEquX(t1.b, t2.a) && PtEquX(t1.c, t2.c) ||
        PtEquX(t1.a, t2.b) && PtEquX(t1.b, t2.c) && PtEquX(t1.c, t2.a) ||
        PtEquX(t1.a, t2.c) && PtEquX(t1.b, t2.a) && PtEquX(t1.c, t2.b) ||
        PtEquX(t1.a, t2.c) && PtEquX(t1.b, t2.b) && PtEquX(t1.c, t2.a);
}


template <typename type>
bool TriEqu(ATriangle3DP<type>& t1, ATriangle3DP<type>& t2)
{
    return
        t1.a==t2.a && t1.b==t2.b && t1.c==t2.c || \
        t1.a==t2.a && t1.b==t2.c && t1.c==t2.b || \
        t1.a==t2.b && t1.b==t2.a && t1.c==t2.c || \
        t1.a==t2.b && t1.b==t2.c && t1.c==t2.a || \
        t1.a==t2.c && t1.b==t2.a && t1.c==t2.b || \
        t1.a==t2.c && t1.b==t2.b && t1.c==t2.a;
}



template <class type>
bool PtInTri2D(ATriangle3D<type>& t, APoint3D<type>& p, int* f = 0)
{
    return PtInTri2D(t.a, t.b, t.c, p, f);
}

// 0-ab, 1-bc, 2-ca, -1 - none
template <class type>
bool PtInTri2D(APoint3D<type>& a, APoint3D<type>& b, APoint3D<type>& c, APoint3D<type>& p, int& f)
{
    f = -1;

    type pax = a.x - p.x, pay = a.y - p.y,
        pbx = b.x - p.x, pby = b.y - p.y,
        pcx = c.x - p.x, pcy = c.y - p.y;

    type abz, bcz, caz, scal;

    abz = pax*pby - pay*pbx;
    bcz = pbx*pcy - pby*pcx;
    caz = pcx*pay - pcy*pax;

    if (Zero(abz)) {
        scal = pax*pbx + pay*pby;
        f = 0;
        return (scal <= 0) ? true : false;
    }

    if (Zero(bcz)) {
        scal = pbx*pcx + pby*pcy;
        f = 1;
        return (scal <= 0) ? true : false;
    }

    if (Zero(caz)) {
        scal = pcx*pax + pcy*pay;
        f = 2;
        return (scal <= 0) ? true : false;
    }

    return ((abz > 0 && bcz > 0 && caz > 0) || (abz < 0 && bcz < 0 && caz < 0)) ? true : false;
}


template <class type>
bool PtInTri2D(APoint2D<type>& a, APoint2D<type>& b, APoint2D<type>& c, APoint2D<type>& p, int& f)
{
    f = -1;

    type pax = a.x - p.x, pay = a.y - p.y,
        pbx = b.x - p.x, pby = b.y - p.y,
        pcx = c.x - p.x, pcy = c.y - p.y;

    type abz, bcz, caz, scal;

    abz = pax*pby - pay*pbx;
    bcz = pbx*pcy - pby*pcx;
    caz = pcx*pay - pcy*pax;

    if (Zero(abz)) {
        scal = pax*pbx + pay*pby;
        f = 0;
        return (scal <= 0) ? true : false;
    }

    if (Zero(bcz)) {
        scal = pbx*pcx + pby*pcy;
        f = 1;
        return (scal <= 0) ? true : false;
    }

    if (Zero(caz)) {
        scal = pcx*pax + pcy*pay;
        f = 2;
        return (scal <= 0) ? true : false;
    }

    return ((abz > 0 && bcz > 0 && caz > 0) || (abz < 0 && bcz < 0 && caz < 0)) ? true : false;
}



template <typename type>
bool PtInTri(APoint3D<type>& p, ATriangle3D<type>& t)
{
    Vec3<type> pa ={t.a.x - p.x, t.a.y - p.y, t.a.z - p.z},
        pb ={t.b.x - p.x, t.b.y - p.y, t.b.z - p.z},
        pc ={t.c.x - p.x, t.c.y - p.y, t.c.z - p.z};

    Vec3<type> pab, pbc, pca;

    // check for epsilon values
    if (Zero(pa.x)) pa.x = 0;
    if (Zero(pa.y)) pa.y = 0;
    if (Zero(pa.z)) pa.z = 0;
    if (Zero(pb.x)) pb.x = 0;
    if (Zero(pb.y)) pb.y = 0;
    if (Zero(pb.z)) pb.z = 0;
    if (Zero(pc.x)) pc.x = 0;
    if (Zero(pc.y)) pc.y = 0;
    if (Zero(pc.z)) pc.z = 0;

    VctProd(pa, pb, pab);
    VctProd(pb, pc, pbc);
    VctProd(pc, pa, pca);

    type x1 = pab.x*pbc.x, y1 = pab.y*pbc.y, z1 = pab.z*pbc.z;
    type x2 = pab.x*pca.x, y2 = pab.y*pca.y, z2 = pab.z*pca.z;
    type x3 = pca.x*pbc.x, y3 = pca.y*pbc.y, z3 = pca.z*pbc.z;

    return (x1>=0 && y1>=0 && z1>=0 && x2>=0 && y2>=0 && z2>=0 && x3>=0 && y3>=0 && z3>=0) ? true : false;
}


template <typename type>
bool PtInTriP(tPoint3D<type>& p, tTriangle3DP<type>& t)
{
    Vec3<type> pa ={t.a->x - p.x, t.a->y - p.y, t.a->z - p.z},
        pb ={t.b->x - p.x, t.b->y - p.y, t.b->z - p.z},
        pc ={t.c->x - p.x, t.c->y - p.y, t.c->z - p.z};

    Vec3<type> pab, pbc, pca;

    // check for epsilon values
    if (Zero(pa.x)) pa.x = 0;
    if (Zero(pa.y)) pa.y = 0;
    if (Zero(pa.z)) pa.z = 0;
    if (Zero(pb.x)) pb.x = 0;
    if (Zero(pb.y)) pb.y = 0;
    if (Zero(pb.z)) pb.z = 0;
    if (Zero(pc.x)) pc.x = 0;
    if (Zero(pc.y)) pc.y = 0;
    if (Zero(pc.z)) pc.z = 0;

    VctProd(pa, pb, pab);
    VctProd(pb, pc, pbc);
    VctProd(pc, pa, pca);

    type x1 = pab.x*pbc.x, y1 = pab.y*pbc.y, z1 = pab.z*pbc.z;
    type x2 = pab.x*pca.x, y2 = pab.y*pca.y, z2 = pab.z*pca.z;
    type x3 = pca.x*pbc.x, y3 = pca.y*pbc.y, z3 = pca.z*pbc.z;

    return (x1>=0 && y1>=0 && z1>=0 && x2>=0 && y2>=0 && z2>=0 && x3>=0 && y3>=0 && z3>=0) ? true : false;
}



template <typename type>
bool IsTriValid(APoint3D<type>& a, APoint3D<type>& b, APoint3D<type>& c)
{
    Vec3<type> ab, ac, nrm;

    VctSub(b, a, ab);
    VctSub(c, a, ac);

    VctProd(ab, ac, nrm);

    return Zero(nrm.x) && Zero(nrm.y) && Zero(nrm.z) ? false : true;
}

template <typename tPt>
bool IsTriValid2D(tPt a, tPt b, tPt c)
{
    b.x -= a.x, b.y -= a.y;
    c.x -= a.x, c.y -= a.y;

    a.x = b.x*c.y - b.y*c.x;

    return Zero(a.x) ? false : true;
}




template <typename type>
bool TriSect(ATriangle3D<type>& t, APoint3D<type>& a, APoint3D<type>& b, APoint3D<type>& x, type& l)
{
    if (!PlLineSect(t.a, t.b, t.c, a, b, x, l))
        return false;

    if (!PtInTri(x, t))
        return false;

    return true;
}



template <class type>
bool TriSectXY(ATriangle3D<type>& tri, APoint3D<type>& pt)
{
    type abx = tri.b.x-tri.a.x, aby = tri.b.y-tri.a.y, abz = tri.b.z-tri.a.z;
    type acx = tri.c.x-tri.a.x, acy = tri.c.y-tri.a.y, acz = tri.c.z-tri.a.z;
    type axx = pt.x-tri.a.x, axy = pt.y-tri.a.y, axz;

    type div = acx*aby - abx*acy;

    if (Zero(div))
        return false;

    //axz = ( axx*aby*acz - abx*acz*axy + acx*abz*axy - axx*abz*acy ) / div ;
    axz = ((axx*aby - abx*axy)*acz + (acx*axy - axx*acy)*abz) / div;

    pt.z = axz + tri.a.z;

    return true;
}


template <class type>
bool TriSectXY(ATriangle3DP<type>& tri, APoint3D<type>& pt)
{
    type abx = tri.b->x-tri.a->x, aby = tri.b->y-tri.a->y, abz = tri.b->z-tri.a->z;
    type acx = tri.c->x-tri.a->x, acy = tri.c->y-tri.a->y, acz = tri.c->z-tri.a->z;
    type axx = pt.x-tri.a->x, axy = pt.y-tri.a->y, axz;

    type div = acx*aby - abx*acy;

    if (Zero(div))
        return false;

    axz = ((axx*aby - abx*axy)*acz + (acx*axy - axx*acy)*abz) / div;

    pt.z = axz + tri.a->z;

    return true;
}



template <typename type>
type PrlSqr(APoint3D<type> a, APoint3D<type> b, tPoint3D<type> c)
{
    b.x -= a.x, b.y -= a.y, b.z -= a.z;
    c.x -= a.x, c.y -= a.y, c.z -= a.z;
    VctCross(b, c, a);
    return VctLen(a);
}



template <typename type>
type TriSqr(APoint3D<type> a, APoint3D<type> b, APoint3D<type> c)
{
    //     __      __
    // b = ab, c = ac
    //
    b.x -= a.x, b.y -= a.y, b.z -= a.z;
    c.x -= a.x, c.y -= a.y, c.z -= a.z;
    VctCross(b, c, a);
    return VctLen(a)/2;
}

template <typename type>
type TriSqr(ATriangle3D<type>& t)
{
    return TriSqr(t.a, t.b, t.c);
}

} // namespace 


