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

template <class u_iterator, class v_iterator>
void vct_add ( u_iterator u, v_iterator v, int n )
{
	for ( int i = 0 ; i < n ; ++i, ++u, ++v )
		*u += *v ;
}

template <class u_iterator, class v_iterator>
void vct_sub ( u_iterator u, v_iterator v, int n )
{
	for ( int i = 0 ; i < n ; ++i, ++u, ++v )
		*u -= *v ;
}


/*
template <class T>
Vec2<T> &vct_add ( const Vec2<T> &u, const Vec2<T> &v, Vec2<T> &x )
{
	x.a[0] = u.a[0] + v.a[0] ;
	x.a[1] = u.a[1] + v.a[1] ;
	return x ;
}


template <class T>
Vec2<T> &vct_add ( Vec2<T> &x, const Vec2<T> &v )
{
	x.a[0] += v.a[0] ;
	x.a[1] += v.a[1] ;
	return x ;
}

template <class T>
Vec2<T> &vct_sub ( const Vec2<T> &x, Vec2<T> &v )
{
	x.a[0] -= v.a[0] ;
	x.a[1] -= v.a[1] ;
	return x ;
}

template <class T>
Vec2<T> &vct_sub ( const Vec2<T> &u, const Vec2<T> &v, Vec2<T> &x )
{
	x.a[0] = u.a[0] - v.a[0] ;
	x.a[1] = u.a[1] - v.a[1] ;
	return x ;
}


template <class T>
Vec3<T> &vct_add ( const Vec3<T> &u, const Vec3<T> &v, Vec3<T> &x )
{
	x.x = u.x + v.x ;
	x.y = u.y + v.y ;
	x.z = u.z + v.z ;
	return x ;
}


template <class T>
Vec3<T> &vct_sub ( const Vec3<T> &u, const Vec3<T> &v, Vec3<T> &x )
{
	x.x = u.x - v.x ;
	x.y = u.y - v.y ;
	x.z = u.z - v.z ;
	return x ;
}
*/





//
// operator overloading
//
//
// remarks: not optimal, allocates in stack and copies extra element
//
/*
template <class T>
inline
Vec2<T> operator + ( const Vec2<T> &u, const Vec2<T> &v )
{
	Vec2<T> x ;
	vct_add(u,v,x) ;
	return x ;
}

template <class T>
inline
Vec2<T> operator - ( const Vec2<T> &u, const Vec2<T> &v )
{
	Vec2<T> x ;
	vct_sub(u,v,x) ;
	return x ;
}
*/

}  // namespace cognit

