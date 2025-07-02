/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include "../../mat/matrix/svd.hpp"
#include "../../mat/vector/scale.hpp"
#include "../../mat/vector/len.hpp"

namespace cognit {
	

// generate 3D coordinates by 2D image and disparity
template <class T, class image_point_type, class spatial_point_type>
spatial_point_type &spatial_point_disparity ( const image_point_type &m, const T &d, spatial_point_type &x )
{
	// calculated based on disparity
	//{
		//T d = m2.x - m1.x ;  // disparity
		
		//if ( d > 4.3 ) {
		//	d = 1 ;
		//}
		//if ( d < 0.7 )
		//	d = 1 ;
		
		//if ( d <= 0 ) {
		//	int a = 0 ;
		//}
		T s = 8 ;  // pixel size
		T b = 1 ;  // base
		T f = 0.25 ;  // focus
		T k = 100 ; //f/s ;
		x.a[3] = 1 ; 
		x.a[2] = k * b / d ;  // z
		x.a[1] = m.y ; //* b / d ;
		x.a[0] = m.x ; //* b / d ;
	//}
	
	return x ;
}



// generate 3d coorditantes from two 2D image points and two matrices
template <class matrix_type, class image_point_type, class spatial_point_type, class T>
spatial_point_type &spatial_point ( const matrix_type &p1, const matrix_type &p2, const image_point_type &m1, const image_point_type &m2, spatial_point_type &x, T d )
{
	using namespace mat ;
	
	//typedef typename matrix_type::value_type T ;
	
	Mtx4<T> a, u, v ;
	Vec4<T> s ;
	int i ;
	
	// build matrix A
	for ( i = 0 ; i < 4 ; ++i )
		a.a[0][i] = -(m1.x*p1.a[2][i] - p1.a[0][i]) ;
	for ( i = 0 ; i < 4 ; ++i )
		a.a[1][i] = -(m1.y*p1.a[2][i] - p1.a[1][i]) ;
	for ( i = 0 ; i < 4 ; ++i )
		a.a[2][i] = m2.x*p2.a[2][i] - p2.a[0][i] ;
	for ( i = 0 ; i < 4 ; ++i )
		a.a[3][i] = m2.y*p2.a[2][i] - p2.a[1][i] ;
		
								
	svd_jacobi(a,u,s,v) ;
											
	// the solution is the smallest last row of V
	x.a[0] = v.a[0][3], x.a[1] = v.a[1][3], x.a[2] = v.a[2][3], x.a[3] = v.a[3][3] ;

	
	//T d = vct_len(x) ;
	
	vct_scale(x,T(1)/x.a[2]) ;
	
	
	// calculated based on disparity
	{
		//T d = m2.x - m1.x ;  // disparity
		
		//if ( d > 4.3 ) {
		//	d = 1 ;
		//}
		//if ( d < 0.7 )
		//	d = 1 ;
		
		//if ( d <= 0 ) {
		//	int a = 0 ;
		//}
		T s = 8 ;  // pixel size
		T b = 1 ;  // base
		T f = 0.25 ;  // focus
		T k = 10 ; //f/s ;
		x.a[3] = 1 ; 
		x.a[2] = k * b / d ;  // z
		x.a[1] = m1.y ; //* b / d ;
		x.a[0] = m1.x ; //* b / d ;
	}
	
	
	
	//vct_scale(x,T(1)/x.a[3]) ;
	
	// needed debug
	//x.a[0] = m1.x, x.a[1] = m1.y, x.a[2] = 0 ;
	
	return x ;
}



}
