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

template <class stream_T, class pt_container_T>
stream_T &input_pts ( stream_T &stream, pt_container_T &pts )
{
  typedef typename pt_container_T::value_type point_type ;
  
  
  while ( stream.good() && !stream.eof() ) {
    pts.resize(pts.size()+1) ;
    point_type &p = pts.back() ;
    
    stream >> p.x >> p.y ;
  }
  
  return stream ;
}

}

