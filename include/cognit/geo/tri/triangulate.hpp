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

// Triangulation
template <typename type, class list_type>
bool Triangulate2D ( APoint2D<type> *pts, int npts, list_type &tris )
{
  typedef ATriangle2DP<type> tTriP ;
  typedef APoint2D<type> tPt ;

  ADynamicStack<tTriP> tstk ;

  tstk.SetBlockSize(npts*10) ;


  type minx ;
  int iminx ;
  tPt *pminx, *pminan ;
  tPt *p ;

  {
    minx = pts[0].x, iminx = 0, pminx = &pts[0] ;
    
    for ( int ipt = 1 ; ipt < npts ; ipt++ ) {
      if ( pts[ipt].x < minx )
        minx = pts[ipt].x, iminx = ipt, pminx = &pts[ipt] ;
    }
  }

  int up = 0 ;
  {
    for ( int ipt = 0 ; ipt < npts ; ipt++ ) {
      if ( ipt == iminx )
        continue ;
      if ( pts[ipt].y == pminx->y )
        continue ;
      up = ( pts[ipt].y > pminx->y )? 1 : -1 ;
      break ;
    }

    if ( up == 0 )
      return 1 ;
  }

  int iminan = -1 ;
  type minan = 0 ;
  pminan = NULL ;
  {
    type div, curran ;

    for ( int ipt = 0 ; ipt < npts ; ipt++ ) {
      if ( ipt == iminx )
        continue ;

      p = &pts[ipt] ;

      if ( p->y >= pminx->y && up < 0 || p->y <= pminx->y && up > 0 )
        continue ;

      div = p->x - pminx->x ;

      if ( div == 0 ) {
        iminan = ipt, pminan = &pts[iminan] ;
        break ;
      }

      curran = (up > 0 ? p->y - pminx->y : pminx->y - p->y) / div ;

      if ( curran > minan )
        minan = curran, pminan = p, iminan = ipt ;
    }

    if ( pminan == NULL )
      return 1 ;
  }


  tPt dumbpt ;
  dumbpt.x = (pminx->x+pminan->x)/2 - 10, dumbpt.y = (pminx->y+pminan->y)/2 ;

  tTriP newtri ;
  newtri.a = pminx, newtri.b = pminan, newtri.c = &dumbpt ;

  tstk.Push(newtri) ;


  {
    tTriP ctri ;
    tTriP *t ;
    AVector2D<type> vpa, vpb ;
    type mincos, curcos ;
    tPt *minp ;
    int iminp ;

    AVector2D<type> vab, vac ;
    Vec3<type> vabc ;

    tTriP newtri, stri1, stri2, stri3 ;

    while ( tstk.n != 0 ) {
      ctri = tstk.Pop() ;

      bool TriFound = false ;
      for ( int itri = 0 ; itri < tris.n ; itri++ ) {
        t = &tris.v[itri] ;

        if( (ctri.a==t->a&&ctri.b==t->b||ctri.a==t->b&&ctri.b==t->a) && LnSide(*ctri.a,*ctri.b,*ctri.c,*t->c) == -1 ) {
          TriFound = true ;
          break ;
        }

        if( (ctri.a==t->a&&ctri.b==t->c||ctri.a==t->c&&ctri.b==t->a) && LnSide(*ctri.a,*ctri.b,*ctri.c,*t->b) == -1 ) {
          TriFound = true ;
          break ;
        }

        if( (ctri.a==t->b&&ctri.b==t->c||ctri.a==t->c&&ctri.b==t->b) && LnSide(*ctri.a,*ctri.b,*ctri.c,*t->a) == -1 ) {
          TriFound = true ;
          break ;
        }
      }

      if ( TriFound )
        continue ;

      mincos = 1 ;

      for ( int ipt = 0 ; ipt < npts ; ipt++ ) {
        p = &pts[ipt] ;

        if ( p == ctri.a || p == ctri.b || p == ctri.c )
          continue ;
        
        if ( LnSide ( *ctri.a, *ctri.b, *ctri.c, *p ) == 1 )
          continue ;

        vpa.x = ctri.a->x-p->x, vpa.y = ctri.a->y-p->y ; 
        vpb.x = ctri.b->x-p->x, vpb.y = ctri.b->y-p->y ; 

        curcos = VctCos(vpa,vpb) ;

        if ( curcos < mincos )
          mincos = curcos, minp = p, iminp = ipt ;
      }

      if ( Zero(mincos-1) )
        continue ;

      newtri.a = ctri.a, newtri.b = ctri.b, newtri.c = minp ;

      VctSub ( *newtri.b, *newtri.a, vab ) ;
      VctSub ( *newtri.c, *newtri.a, vac ) ;
      VctProd ( vab, vac, vabc ) ;
      if ( vabc.z < 0 )
        Swap(newtri.b,newtri.c) ;

      stri1.a = newtri.a, stri1.b = newtri.b, stri1.c = newtri.c ;
      stri2.a = newtri.a, stri2.b = newtri.c, stri2.c = newtri.b ;
      stri3.a = newtri.b, stri3.b = newtri.c, stri3.c = newtri.a ;

      if ( !tris.add(newtri) )
        return false ;

      tstk.Push(stri1), tstk.Push(stri2), tstk.Push(stri3) ;
    }  // while stack
  }


  return true ;
}

}  // namespace
