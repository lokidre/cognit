/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
// Copyright (C) 2003-2004 Andrey Mirzoyan
// For conditions of distribution and use, see LICENSE file

#pragma once


#include "../geo/geo.hpp"
#include "../mat/mat.hpp"

namespace cognit {

// Chessboard error estimate
template <class T>
T ChError (Vec2<T> *ch, int chw, int chh, Vec2<T> *pts, int npts, Vec2<T> *board )
{
    T ch_err{};
    auto chtot = chw * chh ;

  for ( int ich = 0 ; ich < chtot ; ich++ ) {
    int iclosest = PtFindClosest ( pts, npts, ch[ich] ) ;

    ch_err += PtDistSqr ( ch[ich], pts[iclosest] ) ;
  
    if ( board )
      board[ich] = pts[iclosest] ;
  }

  return ch_err ;
}



// Builds chessboard by 9 points
template <typename float_type>
bool BuildChBoard ( tPoint2D<float_type> *pts, int chw, int chh, int ich, int jch, tPoint2D<float_type> *ChPoints )
{
  int i, j ;
  tImplicitLine<float_type> hl[3], vl[3] ;
  tPoint2D<float_type> apx_pts[3] ;

  apx_pts[0] = pts[0], apx_pts[1] = pts[1], apx_pts[2] = pts[2] ;
  ApxLineEigen ( apx_pts, 3, hl[0] ) ;

  apx_pts[0] = pts[3], apx_pts[1] = pts[4], apx_pts[2] = pts[5] ;
  ApxLineEigen ( apx_pts, 3, hl[1] ) ;

  apx_pts[0] = pts[6], apx_pts[1] = pts[7], apx_pts[2] = pts[8] ;
  ApxLineEigen ( apx_pts, 3, hl[2] ) ;


  apx_pts[0] = pts[0], apx_pts[1] = pts[3], apx_pts[2] = pts[6] ;
  ApxLineEigen ( apx_pts, 3, vl[0] ) ;

  apx_pts[0] = pts[1], apx_pts[1] = pts[4], apx_pts[2] = pts[7] ;
  ApxLineEigen ( apx_pts, 3, vl[1] ) ;

  apx_pts[0] = pts[2], apx_pts[1] = pts[5], apx_pts[2] = pts[8] ;
  ApxLineEigen ( apx_pts, 3, vl[2] ) ;


  for ( j = 0 ; j < 3 ; j++ ) {
    for ( i = 0 ; i < 3 ; i++ )
      LnSect ( hl[j], vl[i], ChPoints[(jch+j-1)*chw+ich+i-1] ) ;
  }


  float_type lambda1 = PtDistSqr(ChPoints[jch*chw+ich],ChPoints[jch*chw+ich-1]) ;
  float_type lambda  = PtDistSqr(ChPoints[jch*chw+ich+1],ChPoints[jch*chw+ich])/lambda1 ;
  float_type myu1    = PtDistSqr(ChPoints[jch*chw+ich],ChPoints[(jch-1)*chw+ich]) ;
  float_type myu     = PtDistSqr(ChPoints[(jch+1)*chw+ich],ChPoints[jch*chw+ich])/myu1 ;

  // build all horizontal boards
  Vec2<float_type> p ;
  Vec2<float_type> v ;
  for ( j = jch-1 ; j <= jch+1 ; j++ ) {
    for ( i = ich+2 ; i < chw ; i++ ) {
      VctSub ( ChPoints[j*chw+i-1], ChPoints[j*chw+i-2], v ) ;
      VctScale ( v, lambda ) ;
      VctAdd ( v, ChPoints[j*chw+i-1], p ) ;
    
      ChPoints[j*chw+i] = p ;
    }

    for ( i = ich-2 ; i >=0 ; i-- ) {
      VctSub ( ChPoints[j*chw+i+1], ChPoints[j*chw+i+2], v ) ;
      VctScale ( v, lambda ) ;
      VctAdd ( v, ChPoints[j*chw+i+1], p ) ;
    
      ChPoints[j*chw+i] = p ;
    }
  }

  // build all vertical boards
  for ( i = 0 ; i < chw ; i++ ) {
    for ( j = jch + 2 ; j < chh ; j++ ) {
      VctSub ( ChPoints[(j-1)*chw+i], ChPoints[(j-2)*chw+i], v ) ;
      VctScale ( v, myu ) ;
      VctAdd ( v, ChPoints[(j-1)*chw+i], p ) ;
    
      ChPoints[j*chw+i] = p ;
    }

    for ( j = jch - 2 ; j >= 0 ; j-- ) {
      VctSub ( ChPoints[(j+1)*chw+i], ChPoints[(j+2)*chw+i], v ) ;
      VctScale ( v, myu ) ;
      VctAdd ( v, ChPoints[(j+1)*chw+i], p ) ;
    
      ChPoints[j*chw+i] = p ;
    }
  }

  return true ;
}



// The main algorithm
template <typename float_type>
float_type MatchChBoard ( tPoint2D<float_type> *pts, int npts, int chw, int chh, tPoint2D<float_type> *ChPoints, 
                          tPoint2D<float_type> *board )
{
  int ipt ;
  tPoint2D<float_type> node[9] ;  // chessboard nodes
  float_type err = 1e300 ;  // some real big number

  // Walk through all points
  for ( ipt = 0 ; ipt < npts ; ipt++ ) {
  //for ( ipt = 4 ; ipt < 5 ; ipt++ ) {
    // Find candidates, if we can't, go to the next
    if ( !FindCandidates ( ipt, pts, npts, node ) )
      continue ;

    // Build chessboard model (for all position variants)
    for ( int jch = 1 ; jch < chh - 1 ; jch++ ) {
      for ( int ich = 1 ; ich < chw - 1 ; ich++ ) {
        // build board for current position, we should be able to do it always
        if ( !BuildChBoard ( node, chw, chh, ich, jch, board ) )
          break ;

        // find poitns and the error for selected error
        float_type curr_err = ChError ( board, chw, chh, pts, npts, board ) ;

        // if error is smaller, remember current error
        if ( curr_err < err ) {
          err = curr_err ;
          memcpy ( ChPoints, board, chw*chh*sizeof(tPoint2D<float_type>) ) ;
        }

      }
    }
  }

  return err ;  // return the smalles error
}


// Finds 9 candidates of chessboard nodes
template <typename float_type>
bool FindCandidates ( int ipoint, tPoint2D<float_type> *pts, int npts, tPoint2D<float_type> *node_pts )
{
  //tPoint2D<float_type> hp[4], vp[4] ;
  int ip ;
  int cand[8] = { -1, -1, -1, -1, -1, -1, -1, -1 } ;
  int node[9] ;

  // Find 4 closest points and 4 closest points
  // needed optimization
  for ( ip = 0 ; ip < 8 ; ip++ ) {
    float_type min_distance = 1e60 ;
    for ( int ipt = 0 ; ipt < npts ; ipt++ ) {
      if ( ipt == ipoint || ipt == cand[0] || ipt == cand[1] || ipt == cand[2] || ipt == cand[3] || ipt == cand[4] || ipt == cand[5] || ipt == cand[6] || ipt == cand[7] )
        continue ;
      
      float_type curr_distance = PtDistSqr ( pts[ipoint], pts[ipt] ) ;

      if ( curr_distance < min_distance ) {
        cand[ip] = ipt ;
        min_distance = curr_distance ;
      }
    }
  }


  // Now check all the coordinates
  // - the current point must be in intersection of two (in some delta)
  // - current point must be somewhere in the middle
  // - the lines must be somewhat perpendicular
  // - the quarts of lines must be turned on 45% (approx)
  {
    int i ;
    
    // build the node
    for ( i = 0 ; i < 9 ; i++ )
      node[i] = -1 ;


    float_type minx = 10000 ;
    for ( i = 4 ; i < 8 ; i++ ) {
      if ( pts[cand[i]].x < minx )
        minx = pts[cand[i]].x, node[0] = cand[i] ;
    }

    node[0] = cand[5] ;  // needed debug

    node[4] = ipoint ;

    float_type cos_delta = 0.1 ;
    tVector2D<float_type> a, b ;
    VctSub ( pts[node[0]], pts[ipoint], a ) ;
    float_type vct_cos ;
    tVector3D<float_type> vct_cross ;

    // build all points, calculate angle pi/4
    for ( i = 0 ; i < 8 ; i++ ) {

      if ( cand[i] == node[0] )
        continue ;

      VctSub ( pts[cand[i]], pts[ipoint], b ) ;
      VctCross ( b, a, vct_cross ) ;
      vct_cos = VctCos ( b, a ) ;

      if ( fabs(vct_cos-0.7071067811865475) < cos_delta ) {  // pi/4
        if ( i > 3 )
          return false ;
        node[(vct_cross.z>0)?1:3] = cand[i] ;
      }

      if ( fabs(vct_cos) < cos_delta ) {  // pi/2
        if ( i < 4 )
          return false ;
        node[(vct_cross.z>0)?2:6] = cand[i] ;
      }

      if ( fabs(vct_cos+0.707106781186547524) < cos_delta ) {  // 3pi/4
        if ( i > 3 )
          return false ;
        node[(vct_cross.z>0)?5:7] = cand[i] ;
      }

      if ( fabs(vct_cos+1) < cos_delta ) {  // pi
        if ( i < 4 )
          return false ;
        node[8] = cand[i] ;
      }

      if ( fabs(vct_cos-1) < cos_delta )  // 0 
        return false ;
    }

    // Check everything we find
    for ( i = 0 ; i < 8 ; i++ ) {
      if ( node[i] == -1 )
        return false ;
    }

    // needed verify the distance

    for ( i = 0 ; i < 9 ; i++ )
      node_pts[i] = pts[node[i]] ;

  }


  return true ;
}

}  // namespace


