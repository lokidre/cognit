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

template <typename type>
struct ARun2D {
  tPoint2D<type> a, b ;
} ;


template <typename type>
struct ARun3D {
  tPoint3D<type> a, b ;
} ;


template <typename type>
struct ARun3DP {
  tPoint3D<type> *a, *b ;
} ;




template <typename run_type>
bool RunEqu ( run_type &p, run_type &q )
{
  return PtEqu(p.a,q.a) && PtEqu(p.b,q.b) || PtEqu(p.a,q.b) && PtEqu(p.b,q.a) ;
}


template <typename run_type>
bool RunEquX ( run_type &p, run_type &q )
{
  return PtEquX(p.a,q.a) && PtEquX(p.b,q.b) || PtEquX(p.a,q.b) && PtEquX(p.b,q.a) ;
}


//#define RunEquX3DP(_p,_q) 
//(  
//  (_p).a==(_q).a && (_p).b==(_q).b ||  
//  (_p).a==(_q).b && (_p).b==(_q).a     
//)

#define RunEquX3DP(_pa,_pb,_qa,_qb) \
(  \
  (_pa)==(_qa) && (_pb)==(_qb) ||  \
  (_pa)==(_qb) && (_pb)==(_qa)     \
)

#define RunEquPtX3D(_a,_b,_p,_q) \
(  \
  PtEquX3D((_a),(_p)) && PtEquX3D((_b),(_q)) ||  \
  PtEquX3D((_a),(_q)) && PtEquX3D((_b),(_p))     \
)


//// Run facet (2D) ////
template <typename type>
inline bool IsRunFacet ( tRun2D<type> r, tPoint2D<type> p )
{
  r.a.x -= p.x, r.a.y -= p.y ;
  r.b.x -= p.x, r.b.y -= p.y ;

  p.x = r.a.x * r.b.y - r.a.y * r.b.x ;

  return p.x > 0 ? true : false ;
}

template <class tPt>
void RunFacet2D ( tPt &a, tPt &b, tPt &p, bool facet = true )
{
  if ( IsRunFacet2D ( a, b, p ) != facet )
    Swap ( a, b ) ;
}

template <class tPt>
void RunFacetP ( tPt *&a, tPt *&b, tPt *&p, bool facet = true )
{
  if ( IsRunFacet ( *a, *b, *p ) != facet )
    Swap ( a, b ) ;
}

} // namespace

