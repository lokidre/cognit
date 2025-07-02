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

	Eigen Values for Complex Valued Matrices

#endif


namespace cognit {

//
// Complex Valued Matrices
//

template <class T>
void eigen_values ( const Mtx3<Complex<T>> &a, Vec3<Complex<T>> &e ) noexcept
{
	// coefficients for 3-d degree matrix
    T k[3];

    k[0] = -(a.a[0][0] + a.a[1][1] + a.a[2][2]);

    k[1] = -(a.a[0][1]*a.a[1][0] - a.a[0][0]*a.a[1][1] + 
             a.a[0][2]*a.a[2][0] + a.a[1][2]*a.a[2][1] -
             a.a[0][0]*a.a[2][2] - a.a[1][1]*a.a[2][2]);

	k[2] = a.a[0][0]*a.a[1][2]*a.a[2][1] - 
           a.a[0][0]*a.a[1][1]*a.a[2][2] + 
           a.a[0][1]*a.a[1][0]*a.a[2][2] - 
           a.a[0][1]*a.a[1][2]*a.a[2][0] + 
           a.a[0][2]*a.a[1][1]*a.a[2][0] -
           a.a[0][2]*a.a[1][0]*a.a[2][1];


	// solve the equation of 3-d degree
	EquSolvePoly3 ( k, e.a ) ;
}



}  // namespace cognit

