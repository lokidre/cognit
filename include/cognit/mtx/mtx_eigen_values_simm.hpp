/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once


/*

	Eigen Values of Symmetric Matrices


*/



#include "../matrix.hpp"


namespace cognit {



//
// Simmetric Matrices
//
template <class T>
bool eigen_values_simm ( const Mtx2<T> &a, Vec2<T> &e )
{
	// direct calculation

	T t = a.a[0][0] - a.a[1][1] ;
	T d = 4*a.a[0][1]*a.a[1][0]+t*t ;

	T p = a.a[0][0]+a.a[1][1] ;

	if ( d < 0 )
		return false ;

	d = sqrt(d) ;

	e.a[0] = (p-d)/2 ;
	e.a[1] = (p+d)/2 ;

	// sort eigen values
	if ( abs(e.a[1]) > abs(e.a[0]) )
		swap(e.a[0],e.a[1],t) ;

	return true ;
}



//
// The same for the symmetric matrices, but just real roots
// returns false, if real values are not found
//
template <class T>
bool eigen_values_simm ( const Mtx3<T> &a, Vec3<T> &e )
{
	// coefficients of 3-d degree equation
    T k[3];

    k[0] = -(a.a[0][0] + a.a[1][1] + a.a[2][2]);
	k[1] = -(a.a[0][1] * a.a[1][0]-a.a[0][0]*a.a[1][1]+a.a[0][2]*a.a[2][0]+a.a[1][2]*a.a[2][1]-a.a[0][0]*a.a[2][2]-a.a[1][1]*a.a[2][2]) ;
	k[2] = a.a[0][0]*a.a[1][2]*a.a[2][1]-a.a[0][0]*a.a[1][1]*a.a[2][2] + a.a[0][1]*a.a[1][0]*a.a[2][2]-a.a[0][1]*a.a[1][2]*a.a[2][0] + a.a[0][2]*a.a[1][1]*a.a[2][0]-a.a[0][2]*a.a[1][0]*a.a[2][1] ;

	// solve 3-d degree equation
	EquSolvePoly3Real ( k, e.a ) ;
}

}  // namespace

