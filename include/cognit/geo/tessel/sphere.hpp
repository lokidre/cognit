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

/*
  Starting from octahedron divide each triangle to the desired level
*/

template <typename float_type>
int SphTesselate ( Sphere<float_type> &sphere, int level, Triangle3D<float_type> *tris, int ntris )
{
  // calculate how many triangles we will generate
  // 8 * 4^n
  //
  int TotalTris = 2 * (4<<2*(level-1)) ;


  if ( ntris < TotalTris )
    return TotalTris ;

  // form first octahedron (first 8 triangles)
  {
    APoint3D<float_type> p[6] = {
      {  1,  0,  0 },
      { -1,  0,  0 },
      {  0,  1,  0 },
      {  0, -1,  0 },
      {  0,  0,  1 },
      {  0,  0, -1 }
    } ;

    tTriangle3D<float_type> *tri = tris ;

    tri->a = p[4], tri->b = p[0], tri->c = p[2], tri++ ;
    tri->a = p[4], tri->b = p[2], tri->c = p[1], tri++ ;
    tri->a = p[4], tri->b = p[1], tri->c = p[3], tri++ ;
    tri->a = p[4], tri->b = p[3], tri->c = p[0], tri++ ;
    tri->a = p[5], tri->b = p[2], tri->c = p[0], tri++ ;
    tri->a = p[5], tri->b = p[1], tri->c = p[2], tri++ ;
    tri->a = p[5], tri->b = p[3], tri->c = p[1], tri++ ;
    tri->a = p[5], tri->b = p[0], tri->c = p[3], tri++ ;
  }


  {
    int CurrentTris = 8, BeginTris = 8 ;
    ATriangle3D<float> *tri, *big_tri, new_tri ;

    // go through all the levels by dividing triangles
    for ( int ilevel = 1 ; ilevel < level ; ilevel++ ) {

      // go through the all triangles that are not yet tesselated
      for ( int itri = 0 ; itri < BeginTris ; itri++ ) {
        // generate three more triangles
        tri = &tris[CurrentTris] ;
        big_tri = &tris[itri] ;

        VctAdd(big_tri->a,big_tri->b,new_tri.a) ;
        VctScale(new_tri.a,(float_type)0.5) ;

        VctAdd(big_tri->b,big_tri->c,new_tri.b) ;
        VctScale(new_tri.b,(float_type)0.5) ;

        VctAdd(big_tri->c,big_tri->a,new_tri.c) ;
        VctScale(new_tri.c,(float_type)0.5) ;

        tri->a = new_tri.a, tri->b = new_tri.c, tri->c = big_tri->a, tri++, CurrentTris++ ;
        tri->a = new_tri.b, tri->b = new_tri.a, tri->c = big_tri->b, tri++, CurrentTris++ ;
        tri->a = new_tri.c, tri->b = new_tri.b, tri->c = big_tri->c, tri++, CurrentTris++ ;

        *big_tri = new_tri ;
      }

      //TotalTris -= CurrentTris ;
      BeginTris = CurrentTris ;

    }
  }



  // now project all triangles into the sphere
  {
    Point3D<float_type> *pp ;
    Triangle3D<float_type> *ptri = tris ;
    float_type length_coeff, length ;

    for ( int itri = 0 ; itri < TotalTris ; itri++, ptri++ ) {

      pp = (tPoint3D<float_type> *)ptri ;

      for ( int ipt = 0 ; ipt < 3 ; ipt++, pp++ ) {
        length = (float_type)sqrt(pp->x*pp->x + pp->y*pp->y + pp->z*pp->z);

        length_coeff = sphere.r / length ;

        VctScale ( *pp, length_coeff ) ;
        VctAdd ( *pp, sphere.o ) ;

      }  // for points in triangle

    }  // for triangles
  }

  return TotalTris ;
}


}
