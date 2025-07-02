/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once


#if 0

Gram-Schmidt orthogonalization method

Suppose we have n linearly independent vectors u[0] - u[n-1]
We have to find the set of orthonormal vectors v[i] that spans the same space

Let v[0] = u[0]
Find unit vector e[0] = u[0]/l[0], where
l[0] - length of u[0]
Find the next vector v[1]=u[1] - c*e[0]
The requirement of orth of v[1] and v[0] can be written as
(v[1],e[0]) = (u[1],e[0]) - c*(e[0],e[0]) = 0
then
c = (u[1],e[0])
i.e 
v[1] = u[1] - (u[1],e[0])*e[0]

find unit vector
	e[1] = v[1]/l[1]

continue the same way, we can find
	v[2] = u[2] - (u[2],e[0])*e[0] - (u[2],e[1])*e[1]

for all
	v[i] = u[i] - sum(j=0..i-1,(u[i],e[j])*e[j])

#endif

	/*
template <class T>
void vct_ortho_gram_schmidt ( Vec3<T> *u, int n, Vec3<T> *v, Vec3<T> *e, T *l )
{
  T st, vt, vt2 ;  // temp vars

  // for the first vector
  v[0] = u[0] ;
  l[0] = vct_len(v[0]) ;
  vct_scale(v[0],l[0],1/e[0]) ;


  // for the second vector
  st = VctScalarProd3(u[1],e[0]) ;
  VctProd3(e[0],st,vt) ;
  VctSub3(u[1],vt,v[1]) ;
  l[1] = VctLen3(v[1]) ;
  VctDiv3(v[1],l[1],e[1]) ;

  // for the third vector
  st = VctScalarProd3(u[2],e[0]) ;
  VctProd3(e[0],st,vt) ;
  VctSub3(u[2],vt,vt2) ;

  st = VctScalarProd3(u[2],e[1]) ;
  VctProd3(e[1],st,vt) ;
  VctSub3(vt2,vt,v[2]) ;
  l[2] = VctLen3(v[2]) ;
  VctDiv3(v[2],l[2],e[2]) ;


}
*/



namespace cognit {

}  // namespace
