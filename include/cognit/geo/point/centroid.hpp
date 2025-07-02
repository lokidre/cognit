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


template <class type>
Point3D<type> &pts_centroid ( const Point3D<type> *pts, size_t npts, Point3D<type> &c )
{
  // needed rewrite, overflow may occur

  c.x = c.y = c.z = 0 ;
  auto p = pts ;

  for ( int i = 0 ; i < npts ; i++, p++ )
    c.x += p->x, c.y += p->y, c.z += p->z ;

  c.x /= npts, c.y /= npts, c.z /= npts ;
  return c ;
}


template <class type>
Point3D<type> &pts_centroid ( const Point2D<type> *pts, size_t npts, Point2D<type> &c )
{
  c.x = c.y = 0 ;
  auto p = pts ;

  for ( int i = 0 ; i < npts ; i++, p++ )
    c.x += p->x, c.y += p->y ;

  c.x /= npts, c.y /= npts ;

  return c ;
}

}  // namespace  cognit
