/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once


//
// ln_sect - compute the intersection of two lines
//


namespace cognit {


template <class T, class P>
bool ln_sect ( const AImplicitLine<T> &p, const AImplicitLine<T> &q, P &s )
{
    T div = p.a*q.b - p.b*q.a ;

    if ( tiny(div) )
        return false ;

    s.x = (p.b*q.c - p.c*q.b)/div ;
    s.y = (p.c*q.a - p.a*q.c)/div ;

    return true ;
}


template <class T, class P>
bool ln_sect ( const ANormalLine<T> &p, const ANormalLine<T> &q, P &s )
{
    // TODO: do it better with direct solution
    AImplicitLine<T> pp, qq ;
    line_convert(p,pp) ;
    line_convert(q,qq) ;
    return ln_sect(pp,qq,s) ;
}

template <class T, class P>
bool ln_sect ( const APointLine<T> &p, const APointLine<T> &q, P &s )
{
    return ptln_sect_2d<T>(p.u,p.v,q.u,q.v,s) ;
}



template <class T, class A, class B, class U, class V, class X>
bool ptln_sect_2d ( const A &a, const B &b, const U &u, const V &v, X &x, T &l ) // , T &m )
{
    T abx = b.x-a.x, aby = b.y-a.y ;
    T uvx = v.x-u.x, uvy = v.y-u.y ;
    T aux = u.x-a.x, auy = u.y-a.y ;
    // T xm ;

    T d = abx*uvy - uvx*aby ;  // determinant

    if ( tiny(d) )  // lines don't intersect at all
        return false ;

    // use lambda
    l = ( aux*uvy - uvx*auy ) / d ;
    x.x = a.x + l*abx, x.y = a.y + l*aby ;  // linear combination


    // vct_combo(a,ab,l,x) ;  // get x

    // check for myu
    // m = ( aux*aby - abx*auy ) / d ;
    // vct_combo(c,cd,m,xm) ;  // check for m

    return true ;  // PtEqu(x,xm) ;
}


template <class T, class A, class B, class U, class V, class X>
inline
bool ptln_sect_2d ( const A &a, const B &b, const U &u, const V &v, X &x )
{
    T l ;
    return ptln_sect_2d(a,b,u,v,x,l) ;
}

/*
template <class T>
inline
bool ln_sect ( APoint2D<T> &a, APoint2D<T> &b, APoint2D<T> &u, APoint2D<T> &v, APoint2D<T> &x, T &l, T &m )
{
    AVector2D<T> ab = {b.x-a.x, b.y-a.y}, uv = {d.x-c.x, d.y-c.y}, au = {c.x-a.x, c.y-a.y}, xm ;

    // determinant of matrix
    T det = ab.x*cd.y - cd.x*ab.y ;

    if ( tiny(det) )
        return false ;

    l = ( ac.x*cd.y - cd.x*ac.y ) / det ;
    m = ( ac.x*ab.y - ab.x*ac.y ) / det ;

    vct_combo(a,ab,l,x) ;  // get x

    vct_combo(c,cd,m,xm) ;  // check for m

    return true ;  // PtEqu(x,xm) ;
}
*/





//
// TODO: obsolete need rewrete
//

//  x~ = a~ + l(b~-a~) = c~ + m(d~-c~)
template <typename type>
bool LnSect ( Vec3<type> &a, APoint3D<type> &b, APoint3D<type> &c, APoint3D<type> &d, APoint3D<type> &x, type &l, type &m )
{
  // a.x + l*ab.x = c.x + m*cd.x
  // a.y + l*ab.y = c.y + m*cd.y
  // a.z + l*ab.z = c.z + m*cd.z

  // m = ( a.x - c.x + l*ab.x ) / cd.x = ( a.y - c.y + l*ab.y ) / cd.y


  Vec3<type> ab = { b.x-a.x, b.y-a.y, b.z-a.z },
                  cd = { d.x-c.x, d.y-c.y, d.z-c.z },
                  ac = { c.x-a.x, c.y-a.y, c.z-a.z },
                  xm ;

  // determinant
  type det = ab.x*cd.y - cd.x*ab.y ;

  if ( !Zero(det) ) {
    l = ( ac.x*cd.y - cd.x*ac.y ) / det ;
    m = ( ac.x*ab.y - ab.x*ac.y ) / det ;
  } else {
    det = ab.x*cd.z - cd.x*ab.z ;
    if ( !Zero(det) ) {
      l = ( ac.x*cd.z - cd.x*ac.z ) / det ;
      m = ( ac.x*ab.z - ab.x*ac.z ) / det ;
    } else {
      det = ab.y*cd.z - cd.y*ab.z ;
      if ( !Zero(det) ) {
        l = ( ac.y*cd.z - cd.y*ac.z ) / det ;
        m = ( ac.y*ab.z - ab.y*ac.z ) / det ;
      } else {
        l = m = mat::const_inf<type>()() ;
        return false ;
      }
    }
  }

  VctCombo(a,ab,l,x) ;  // get x

  VctCombo(c,cd,m,xm) ;  // check for m

  return PtEqu(x,xm) ;
}


}
