/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include <geo/geo.c++>

#include <contain.h>

class tGeoScene ;

class tGeoFile {
  public :
    bool LoadScene ( char *file, tGeoScene *scene ) ;
} ;


bool geo_load ( char *file, tDynamicArray<tPoint3D<float> > &pts ) ;
bool geo_load ( char *file, tDynamicArray<tPoint3D<double> > &pts ) ;


