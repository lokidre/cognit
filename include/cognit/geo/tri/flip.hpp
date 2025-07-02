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

// in: tris, ntris, buffer(ntris*3), passes
// out: tris-flipped
template <class type>
int TriFlip3D ( ATriangle3D<type> *tris, int ntris, ATriangle3DP<type> *tbuf, int passes = 1 ) 
{
  int FlipCount = 0 ;

  tPoint3D<type> *p, *q, *r, *s, *p1, *q1 ;
  tVector3D<type> pr, qr, ps, qs, pq, qp ;
  type cosrqp, cosrpq, cosspq, cospqs ;

  {
    int ibuf = 0 ;
    for ( int itri = 0 ; itri < ntris ; itri++ ) {
      tbuf[ibuf].a = &tris[itri].a, tbuf[ibuf].b = &tris[itri].b, tbuf[ibuf].c = &tris[itri].c, ibuf++ ;
      tbuf[ibuf].a = &tris[itri].b, tbuf[ibuf].b = &tris[itri].c, tbuf[ibuf].c = &tris[itri].a, ibuf++ ;
      tbuf[ibuf].a = &tris[itri].c, tbuf[ibuf].b = &tris[itri].a, tbuf[ibuf].c = &tris[itri].b, ibuf++ ;
    }
  }

  int nbuf = ntris*3 ;

  bool TriFound ;
  int NewFlips ;


  for ( int ipass = 0 ; ipass < passes ; ipass++ ) {
    NewFlips = 0 ;

    for ( int itri = 0 ; itri < nbuf ; itri++ ) {
      for ( int jtri = itri + 1 ; jtri < nbuf ; jtri++ ) {


        TriFound = false ;
        if ( !TriFound && PtEquX3D(*tbuf[itri].a,*tbuf[jtri].a) && PtEquX3D(*tbuf[itri].b,*tbuf[jtri].b) ) {
          p = tbuf[itri].a, q = tbuf[itri].b, r = tbuf[itri].c ;
          p1 = tbuf[jtri].a, q1 = tbuf[jtri].b, s = tbuf[jtri].c ;
          TriFound = true ;
        }

        if ( !TriFound && PtEquX3D(*tbuf[itri].a,*tbuf[jtri].b) && PtEquX3D(*tbuf[itri].b,*tbuf[jtri].a) ) {
          p = tbuf[itri].a, q = tbuf[itri].b, r = tbuf[itri].c ;
          p1 = tbuf[jtri].b, q1 = tbuf[jtri].a, s = tbuf[jtri].c ;
          TriFound = true ;
        }


        if ( !TriFound )
          continue ;


        VctSub3D(*r,*p,pr) ;
        VctSub3D(*s,*p,ps) ;
        VctSub3D(*q,*p,pq) ;
        VctSub3D(*r,*q,qr) ;
        VctSub3D(*s,*q,qs) ;
        VctSub3D(*p,*q,qp) ;


        cosrqp = VctCos3D(qr,qp) ;
        cospqs = VctCos3D(qp,qs) ;
        cosrpq = VctCos3D(pr,pq) ;
        cosspq = VctCos3D(ps,pq) ;

        if ( cosrqp+cospqs <= -1 )
          continue ;
        if ( cosrpq+cosspq <= -1 )
          continue ;


        if ( PtSqrDist3D(*p,*q) > PtSqrDist3D(*r,*s) ) {

          *p = *s ;
          *q1 = *r ;
          //  *q = *s ;
          //  *p1 = *r ;


          FlipCount++ ;
          NewFlips++ ;
        }
      }  // for jtri

    }  // for itri ;
    if ( NewFlips == 0 )
      break ;
  }  // for passes

  return FlipCount ;
}

}  // namespace

