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

template <class type, class tDynArray>
bool convex_hull ( Point3D<type> *pts, int npts, ADynArray &tris, void (*verbose)(int,int) = nullptr)
{
  if ( npts < 4 )
    return false ;

  {
    int ip[4] ;
    ATriangle3DP<type> t1, t2, t3, t4 ;
    APoint3D<type> *p, *q, *r, *s ;

    if ( !PtSelectIndipendent3D ( pts, npts, ip) )
      return false ;

    p = &pts[ip[0]], q = &pts[ip[1]], r = &pts[ip[2]], s = &pts[ip[3]] ;

    t1.a = p, t1.b = q, t1.c = r, TriFacetP ( t1.a, t1.b, t1.c, s, false ) ;
    t2.a = p, t2.b = q, t2.c = s, TriFacetP ( t2.a, t2.b, t2.c, r, false ) ;
    t3.a = p, t3.b = r, t3.c = s, TriFacetP ( t3.a, t3.b, t3.c, q, false ) ;
    t4.a = q, t4.b = r, t4.c = s, TriFacetP ( t4.a, t4.b, t4.c, p, false ) ;

    tris.add(t1), tris.add(t2), tris.add(t3), tris.add(t4) ;
  }



  Point3D<type> *p ;
  Triangle3DP<type> *t, nt1, nt2, nt3, *t1, *t2 ;
  int ipt, itri, jtri ;
  int chktris ;

  for ( ipt = 0, p = pts ; ipt < npts ; ipt++, p++ ) {

    if ( verbose != 0 && (ipt&0xFF) == 0 )
      verbose(ipt,tris.n) ;

    chktris = tris.n ;

    for ( itri = 0 ; itri < chktris ; ) {

      t = &tris.v[itri] ;

      if ( !IsTriFacet ( *t->a, *t->b, *t->c, *p ) ) {
        itri++ ;
        continue ;
      }


      nt1.a = t->a, nt1.b = t->b, nt1.c = p ;
      nt2.a = t->b, nt2.b = t->c, nt2.c = p ;
      nt3.a = t->c, nt3.b = t->a, nt3.c = p ;

      tris.v[itri] = tris.v[--chktris] ;

      tris.v[chktris] = nt1 ;

      tris.add ( nt2 ) ;
      tris.add ( nt3 ) ;
    }  // for tris

    for ( itri = chktris ; itri < tris.n ; itri++ ) {
      for ( jtri = itri+1 ; jtri < tris.n ; jtri++ ) {
        t1 = &tris.v[itri], t2 = &tris.v[jtri] ;
        if ( TriEqu ( *t1, *t2 ) ) {
          tris.v[jtri--] = tris.v[--tris.n] ;
          tris.v[itri--] = tris.v[--tris.n] ;
          break ;
        }
      }
    }

  }  // for pts

  return true ;
}


}  // namespace
