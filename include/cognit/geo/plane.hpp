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

// Plane f(x,y) = ax + by + c
template <class type>
struct APlaneF : public AFunction3D<type> {
  type a, b, c ;

  type f ( type x, type y )
    {  return a*x + b*y + c ;  }

  tPlaneF ( void )
  {
    a = b = 1 ;
    c = 0 ;
  }
} ;


// Canonic plane equation ax + by + cz + d = 0
template <typename type>
struct AImplicitPlane : public AEquation3D {
  union {
    struct {
      type a, b, c ;
    } ;
    Vec3<type> n ;  // normal to the plane
    type p[3] ;
  } ;

  type d ;
} ;


template <typename type>
char *unistr ( tImplicitPlane<type> &p, char *s, int f = 0 )
{
  int o = 0 ;
  o += strlen ( unistr ( p.a, &s[o], f ) ), s[o++] = ' ' ;
  o += strlen ( unistr ( p.b, &s[o], f ) ), s[o++] = ' ' ;
  o += strlen ( unistr ( p.c, &s[o], f ) ), s[o++] = ' ' ;
  o += strlen ( unistr ( p.d, &s[o], f ) ), s[o++] = ' ' ;
  s[o++] = '\0' ;
  return s ;
}

template <typename type>
char uniscan ( tImplicitPlane<type> &p, char *s, int f = 0 )
{
  int o = 0 ;
  o += uniscan ( p.a, &s[o], f ) ;
  o += uniscan ( p.b, &s[o], f ) ;
  o += uniscan ( p.c, &s[o], f ) ;
  o += uniscan ( p.d, &s[o], f ) ;
  return o ;
}


// d - det of matrix
// a, b, c - normal vector
template <typename type>
bool GetImplicitPlane ( APoint3D<type> &a, APoint3D<type> &b, APoint3D<type> &c, AImplicitPlane<type> &pl )
{
  Vec3<type> ab, ac ;

  VctSub(a,b,ab) ;
  VctSub(a,c,ac) ;

  VctProd(ab,ac,pl.n) ;
  pl.d = -VctScalProd(pl.n,a) ;

  return true ;
}

template <typename type>
bool GetImplicitPlane ( ATriangle3D<type> &t, AImplicitPlane<type> &p )
{
  return GetImplicitPlane ( t.a, t.b, t.c, p ) ;
}



// detects if four points are on plane
template <typename type>
bool PtsOnPlane ( const APoint3D<type> &a, const APoint3D<type> &b, const APoint3D<type> &c, const APoint3D<type> &d )
{
  tMatrix3<type> m ;

  m.a[0][0]=b.x-a.x, m.a[0][1]=b.y-a.y, m.a[0][2]=b.z-a.z ;
  m.a[1][0]=c.x-a.x, m.a[1][1]=c.y-a.y, m.a[1][2]=c.z-a.z ;
  m.a[2][0]=d.x-a.x, m.a[2][1]=d.y-a.y, m.a[2][2]=d.z-a.z ;

  return Zero(MtxDet(m)) ;
}




template <typename type>
bool PlLineSect ( AImplicitPlane<type> &p, APoint3D<type> &a, APoint3D<type> &b, APoint3D<type> &x )
{
  // 
  //(x-u.x)/(x-v.x) == (y-u.y)/(y-v.y) == (z-u.z)/(z-v.z)
  
  type div = p.a*(b.x-a.x) + p.b*(b.y-a.y) + p.c*(b.z-a.z) ;

  if ( Zero(div) )
    return false ;

  x.x = ( p.b*(a.x*b.y-a.y*b.x) + p.c*(a.x*b.z-a.z*b.x) - p.d*(b.x-a.x) ) / div ;
  x.y = ( p.a*(b.x*a.y-a.x*b.y) + p.c*(a.y*b.z-a.z*b.y) - p.d*(b.y-a.y) ) / div ;
  x.z = ( p.a*(b.x*a.z-b.z*a.x) + p.b*(b.y*a.z-b.z*a.y) - p.d*(b.z-a.z) ) / div ;

  return true ;
}


template <class type>
bool PlLineSect ( APoint3D<type> p, APoint3D<type> q, APoint3D<type> r, APoint3D<type> a, APoint3D<type> b, APoint3D<type> &x, type &l )
{
  Vec3<type> ap = {p.x-a.x,p.y-a.y,p.z-a.z},
                  aq = {q.x-a.x,q.y-a.y,q.z-a.z},
                  ar = {r.x-a.x,r.y-a.y,r.z-a.z},
                  ab = {b.x-a.x,b.y-a.y,b.z-a.z} ;

  type div = ab.x*(ap.z*(ar.y-aq.y)+ap.y*(aq.z-ar.z)+aq.y*ar.z-aq.z*ar.y) + ap.x*(ab.z*(aq.y-ar.y)+ab.y*(ar.z-aq.z)) + aq.x*(ab.y*(ap.z-ar.z)+ab.z*(ar.y-ap.y)) + ar.x*(ab.z*(ap.y-aq.y)+ab.y*(aq.z-ap.z)) ;

  if ( Zero(div) )
    return false ;

  l = ( aq.x*(ap.z*ar.y-ap.y*ar.z) + ar.x*(ap.y*aq.z-ap.z*aq.y) + ap.x*(aq.y*ar.z-aq.z*ar.y) ) / div ;

  VctCombo(a,ab,l,x) ;

  return true ;
}


// needed
template <typename type>
bool PlLineSect ( AImplicitPlane<type> &p, APoint3D<type> a, APoint3D<type> b, APoint3D<type> &x, type &l )
{
  Vec3<type> v ;
  VctSub ( b, a, v ) ;

  return PlVctSect ( p, a, v, x, l ) ;
}


template <typename type>
bool PlVctSect ( AImplicitPlane<type> &p, Vec3<type> &o, Vec3<type> &v, type &l )
{
  type pv, po, pod ;

  po = VctScalProd ( p.n, o ) ;

  pod = po + p.d ;

  if ( Zero(pod) ) {
    l = 0 ;
    return false ;
  }

  pv = VctScalProd ( p.n, v ) ;

  if ( Zero(pv) ) {
    l = const_inf<type>()() ;
    return false ;
  }

  l = - pod / pv ;

  return true ;
}


template <typename type>
bool PlVctSect ( AImplicitPlane<type> &p, Vec3<type> &o, Vec3<type> &v, Vec3<type> &x, type &l )
{
  if ( !PlVctSect(p,o,v,l) )
    return false ;

  VctCombo(o,v,l,x) ;
  return true ;
}



template <typename type>
bool PlSect ( AImplicitPlane<type> &u, AImplicitPlane<type> &v, AImplicitPlane<type> &w, APoint3D<type> &p )
{
  MtxN<type,3> a ;
  AVectorN<type,3> r, x ;

  a.a[0][0] = u.p[0], a.a[0][1] = u.p[1], a.a[0][2] = u.p[2], r.a[0] = -u.p[3] ;
  a.a[1][0] = v.p[0], a.a[1][1] = v.p[1], a.a[1][2] = v.p[2], r.a[1] = -v.p[3] ;
  a.a[2][0] = w.p[0], a.a[2][1] = w.p[1], a.a[2][2] = w.p[2], r.a[2] = -w.p[3] ;

  if ( !SysEquLinearSolve ( a, r, x ) )
    return false ;

  p.x = x.a[0], p.y = x.a[1], p.z = x.a[2] ;

  return true ;
}


template <typename type>
bool PlParalProj ( AImplicitPlane<type> &p, APoint3D<type> &a, APoint3D<type> &x )
{
  // ax-x/a = ay-y/b = az-z/c
  // a*x + b*y + c*z + d = 0

  type l = p.a*p.a + p.b*p.b + p.c*p.c ;

  if ( tiny(l,const_eps<type>()()) )
    return false ;

  x.x = ( a.x*(p.b*p.b+p.c*p.c) - p.a*(a.y*p.b+a.z*p.c+p.d) ) / l ;
  x.y = ( a.y*(p.a*p.a+p.c*p.c) - p.b*(a.x*p.a+a.z*p.c+p.d) ) / l ;
  x.z = ( a.z*(p.a*p.a+p.b*p.b) - p.c*(a.x*p.a+a.y*p.b+p.d) ) / l ;

  return true ;
}


// find the square of distance from point to plane
template <typename type>
type PlPtDistSqr ( AImplicitPlane<type> &pl, APoint3D<type> &pt )
{
  APoint3D<type> x ;
  if ( !PlParalProj ( pl, pt, x ) )
    return type(0) ;

  return PtDistSqr ( pt, x ) ;
}

// find the distance from point to plane
template <typename type>
type PlPtDist ( AImplicitPlane<type> &pl, APoint3D<type> &pt )
{
  return Sqrt ( PlPtDistSqr ( pl, pt ) ) ;
}



template <class type>
bool PlOneSideX ( APoint3D<type> &u, APoint3D<type> &v, APoint3D<type> &a, APoint3D<type> &b, APoint3D<type> &c )
{
  Mtx3<type> m ;
  type det1, det2 ;

  m.a[0][0]=b.x-a.x, m.a[0][1]=b.y-a.y, m.a[0][2]=b.z-a.z ;
  m.a[1][0]=c.x-a.x, m.a[1][1]=c.y-a.y, m.a[1][2]=c.z-a.z ;

  m.a[2][0]=u.x-a.x, m.a[2][1]=u.y-a.y, m.a[2][2]=u.z-a.z ;
  det1 = MtxDet(m) ;

  m.a[2][0]=v.x-a.x, m.a[2][1]=v.y-a.y, m.a[2][2]=v.z-a.z ;
  det2 = MtxDet(m) ;

  return bool( det1 > 0 && det2 > 0 || det1 < 0 && det2 < 0 ) ;
}


template <typename type>
bool PlOneSide ( APoint3D<type> &u, APoint3D<type> &v, APoint3D<type> &a, APoint3D<type> &b, APoint3D<type> &c )
{
  Mtx3<type> m ;
  type det1, det2 ;

  m.a[0][0]=b.x-a.x, m.a[0][1]=b.y-a.y, m.a[0][2]=b.z-a.z ;
  m.a[1][0]=c.x-a.x, m.a[1][1]=c.y-a.y, m.a[1][2]=c.z-a.z ;

  m.a[2][0]=u.x-a.x, m.a[2][1]=u.y-a.y, m.a[2][2]=u.z-a.z ;
  det1 = MtxDet(m) ;

  m.a[2][0]=v.x-a.x, m.a[2][1]=v.y-a.y, m.a[2][2]=v.z-a.z ;
  det2 = MtxDet(m) ;

  return bool( det1 >= 0 && det2 >= 0 || det1 <= 0 && det2 <= 0 ) ;
}




// ( ~ab x ~ac ) * ~x = 0
// |x| = 1
// ( ~i x ~k ) * ~x = 0  
// for oxz

template <typename type>
void PlGetProj ( APoint3D<type> &a, APoint3D<type> &b, APoint3D<type> &c, Vec3<type> &oxy, Vec3<type> &oxz, Vec3<type> &oyz )
{
  Vec3<type> ab, ac ;
  VctSub(b,a,ab) ;
  VctSub(c,a,ac ) ;
  type div ;
  type eps = const_eps<type>()() ;


  oxy.z = oxz.y = oyz.x = 0 ;


  div = ab.z*ab.z*ac.x*ac.x 
      - ab.z*ac.x*ab.x*ac.z * 2
      + ab.x*ab.x*ac.z*ac.z 
      + ab.y*ab.y*ac.z*ac.z 
      - ab.y*ac.z*ab.z*ac.y * 2
      + ab.z*ab.z*ac.y*ac.y ;

  if ( !tiny(div,eps) ) {
    oxy.x = ( ab.x*ac.z - ab.z*ac.x ) / div ;
    oxy.y = ( ab.y*ac.z - ab.z*ac.y ) / div ;

    if ( oxy.y < 0 )
      oxy.y = -oxy.y, oxy.x = -oxy.x ;

  } else {
    oxy.x = oxy.y = 0 ;
  }



  div = ab.x*ab.x*ac.y*ac.y - 2*ab.x*ac.y*ab.y*ac.x + ab.y*ab.y*ac.x*ac.x + ab.y*ab.y*ac.z*ac.z - 2*ab.y*ac.z*ab.z*ac.y + ab.z*ab.z*ac.y*ac.y ;
  if ( !tiny(div,eps) ) {
    div = sqrt(div) ;
    oxz.x = ( ab.y*ac.x - ab.x*ac.y ) / div ;
    oxz.z = ( ab.y*ac.z - ab.z*ac.y ) / div ;

    if ( oxz.z < 0 )
      oxz.z = -oxz.z, oxz.x = -oxz.x ;

  } else
    oxz.x = oxz.z = 0 ;



  div = ab.x*ab.x*ac.y*ac.y - 2*ab.x*ac.y*ab.y*ac.x + ab.y*ab.y*ac.x*ac.x + ab.z*ab.z*ac.x*ac.x - 2*ab.z*ac.x*ab.x*ac.z + ab.x*ab.x*ac.z*ac.z ;
  if ( !tiny(div,eps) ) {
    div = sqrt(div) ;
    oyz.y = ( ab.x*ac.y - ab.y*ac.x ) / div ;
    oyz.z = ( ab.x*ac.z - ab.z*ac.x ) / div ;

    if ( oyz.z < 0 )
      oyz.z = -oyz.z, oyz.y = -oyz.y ;

  } else
    oyz.y = oyz.z = 0 ;
}

template <typename type>
void PlGetProj ( ATriangle3D<type> &t, Vec3<type> &oxy, Vec3<type> &oxz, Vec3<type> &oyz )
{
  return PlGetProj ( t.a, t.b, t.c, oxy, oxz, oyz ) ;
}

}  // namespace 
