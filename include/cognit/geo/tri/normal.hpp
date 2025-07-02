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

// Generates normal for each triangle vertex
template <class type>
void GenNormals ( APoint3D<type> *vtxs, int nvtxs, ATriangle3DP<type> *tris, int ntris, Vec3<type> *trinrms, Vec3<type> *vnrms )
{
  int itri, ivtx ;
  ATriangle3DP<type> *t ;
  Vec3<type> *n ;
  Point3D<type> *v ;

  {
    Vec3<type> tmpnrm ;

    n = trinrms ;
    for ( t = tris, itri = 0 ; itri < ntris ; itri++, t++ ) {
      t = &tris[itri] ;
      VctUnitNrm3D(*t->a,*t->b,*t->c,trinrms[itri]) ;
    }
  }

  {
    Vec3<type> cnrm ;

    for ( v = vtxs, ivtx = 0 ; ivtx < nvtxs ; ivtx++, v++ ) {
      cnrm.x = cnrm.y = cnrm.z = 0 ;

      n = trinrms ;
      for ( t = tris, itri = 0 ; itri < ntris ; itri++, t++ ) {
        if ( v == t->a )
          VctAdd3D ( cnrm, *n, cnrm ) ;
        else if ( v == t->b )
          VctAdd3D ( cnrm, *n, cnrm ) ;
        else if ( v == t->c )
          VctAdd3D ( cnrm, *n, cnrm ) ;

        n++ ;
      }

      VctUnit3D ( cnrm ) ;

      vnrms[ivtx] = cnrm ;
    }  // for vtxs
  }

}

}  // namespace
