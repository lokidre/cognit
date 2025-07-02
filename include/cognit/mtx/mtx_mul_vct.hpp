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
	Multiplication of Vector and Matrix
	
	
	vct_mtx_mul - multiplication of the form v^T.A, produce vector 
	mtx_vct_mul - A.v
	

*/


namespace cognit {


// note: l = m
template <class V_iterator, class A_iterator, class X_iterator>
void vct_mtx_mul ( V_iterator v, int l, A_iterator a, const int m, const int n, X_iterator x )
{
	V_iterator vv ;
	A_iterator aa, ac = a ;
	
	for ( int i = 0 ; i < l ; ++i, ++x, ++ac ) {
		vv = v ;
		aa = ac ;
		*x = 0 ;
		for ( int j = 0 ; j < l ; ++j, ++vv, aa += n ) {
			*x += *vv * *aa ;
		}
	}
}



//
// Multiplication of Matrix by vector Au produces vector v
//

template <class T>
void mtx_vct_mul ( const T *a, const int m, const int n, const T *u, T *v )
{
	for ( int j = 0 ; j < n ; ++j ) {
		*v = 0 ;
		const T *pu = u ;
		
		for ( int i = 0 ;i < m ; ++i, ++a, *pu )
			*v += *a * *pu ;
	}
}


template <class T>
Vec2<T> &mtx_vct_mul ( const Mtx2<T> &a, const Vec2<T> &u, Vec2<T> &v )
{
	v.x = a.a[0][0]*u.x + a.a[0][1]*u.y ;
	v.y = a.a[1][0]*u.x + a.a[1][1]*u.y ;
	return v ;
}


template <class T>
Vec3<T> &mtx_vct_mul ( const Mtx3<T> &a, const Vec3<T> &u, Vec3<T> &v )
{
	v.x = a.a[0][0]*u.x + a.a[0][1]*u.y + a.a[0][2]*u.z ;
	v.y = a.a[1][0]*u.x + a.a[1][1]*u.y + a.a[1][2]*u.z ;
	v.z = a.a[2][0]*u.x + a.a[2][1]*u.y + a.a[2][2]*u.z ;
	return v ;
}

template <class T>
Vec4<T> &mtx_vct_mul ( const Mtx4<T> &a, const Vec4<T> &u, Vec4<T> &v )
{
	v.a[0] = a.a[0][0]*u.a[0] + a.a[0][1]*u.a[1] + a.a[0][2]*u.a[2] + a.a[0][3]*u.a[3] ;
	v.a[1] = a.a[1][0]*u.a[0] + a.a[1][1]*u.a[1] + a.a[1][2]*u.a[2] + a.a[1][3]*u.a[3] ;
	v.a[2] = a.a[2][0]*u.a[0] + a.a[2][1]*u.a[1] + a.a[2][2]*u.a[2] + a.a[2][3]*u.a[3] ;
	v.a[3] = a.a[3][0]*u.a[0] + a.a[3][1]*u.a[1] + a.a[3][2]*u.a[2] + a.a[3][3]*u.a[3] ;
	
	return v ;
}

//template <class T>
//Vec3<T> &mtx_vct_mul ( const MtxMN<T,3,4> &a, const Vec4<T> &u, Vec3<T> &v )
//{
//	v.a[0] = a.a[0][0]*u.a[0] + a.a[0][1]*u.a[1] + a.a[0][2]*u.a[2] + a.a[0][3]*u.a[3] ;
//	v.a[1] = a.a[1][0]*u.a[0] + a.a[1][1]*u.a[1] + a.a[1][2]*u.a[2] + a.a[1][3]*u.a[3] ;
//	v.a[2] = a.a[2][0]*u.a[0] + a.a[2][1]*u.a[1] + a.a[2][2]*u.a[2] + a.a[2][3]*u.a[3] ;
//	
//	return v ;
//}




//
// operator overloading
//

// remarks: not optimized - extra copying of c
template <class T>
Vec2<T> operator * ( const Mtx2<T> &a, const Vec2<T> &b )
{
	Vec2<T> c ;
	mul_mtx_vct(a,b,c) ;
	return c ;
}



}  // namespace




