/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

// (C) Andrey Mirzoyan, see LICENSE for details


#include <vector>

// #include <apl/parse.h>


namespace cognit {

template <class container_type=std::vector>
class tGeoScene {
  public :

    class tObject {
      
    } ;



  // --- everything about points ---
  public :

    // points as dynamic array
    tDynamicArray<tPoint3D<float> > pts ;


    tPoint3D<float> pts_bound[2] ;  // -x, +x, -y, +y, -z, +z


  // triangles
  public :
    tDynamicArray<tTriangle3D<float> > tris ;


  // -- scene manipulation ---
  public :
    //void Clear ( void ) ;

    //bool SetPts ( tPoint3D<float> *pts, int npts ) ;
    //bool SetTris ( tTriangle3DP<float> *tris, int ntris ) ;
} ;

}

