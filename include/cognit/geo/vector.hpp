/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

//#include "point.hpp"
//#include "../matrix.hpp"


namespace cognit {

/*
template <class T>
struct AVector2D {
	typedef T value_type ;
	value_type x, y ;
} ;

template <class T>
using Vec3 = Vec3<T> ;
*/

//template <class T>
//struct Vec3 : public Vec3<T> {
	//typedef T value_type ;
	//T &x, &y, &z ;
	//Vec3() : x(a[0]), y(a[1]), z(a[2]) {}

//} ;


/*
template <class T>
struct Vec3 {
	typedef T value_type ;
	value_type x, y, z ;
} ;
*/

//
// vector scalar (dot) product
//
/*
template <class T>
inline 
T vct_dot ( const Vec3<T> &p, const Vec3<T> &q )
{
	return p.x*q.x + p.y*q.y + p.z*q.z ;
}

template <class T>
inline 
T vct_dot ( const AVector2D<T> &p, const AVector2D<T> &q )
{
	return p.x*q.x + p.y*q.y ;
}
*/

//
// Vector Cross Product
//
/*
template <class T>
inline 
Vec3<T> &vct_cross ( const Vec3<T> &p, const Vec3<T> &q, Vec3<T> &r )
{
	r.x = p.y * q.z - p.z * q.y ;
	r.y = p.z * q.x - p.x * q.z ;
	r.z = p.x * q.y - p.y * q.x ;
	return r ;
}
*/
/*
// remarks: extra copying of Vector
template <typename type>
inline 
Vec3<type> vct_cross ( const Vec3<type> &p, const Vec3<type> &q )
{
	Vec3<type> r ;
	r.x = p.y * q.z - p.z * q.y ;
	r.y = p.z * q.x - p.x * q.z ;
	r.z = p.x * q.y - p.y * q.x ;
	return r ;
}
*/

/*
template <typename type>
inline 
AVector2D<type> &vct_cross ( const AVector2D<type> &p, const AVector2D<type> &q, Vec3<type> &r )
{
	// Vector product in 2d gives us vector in 3D
	r.x = r.y = 0 ;
	r.z = p.x * q.y - p.y * q.x ;
	return r ;
}
*/

/*
template <class T>
inline 
Vec3<T> &vct_add ( const Vec3<T> &p, const Vec3<T> &q, Vec3<T> &r )
{
	r.x = p.x + q.x, r.y = p.y + q.y, r.z = p.z + q.z ;
	return r ;
}

template <class T>
inline 
Vec3<T> &vct_add ( Vec3<T> &p, const Vec3<T> &q )
{
	p.x += q.x, p.y += q.y, p.z += q.z ;
	return p ;
}
*/

/*
template <typename type>
inline 
void vct_add ( AVector2D<type> &p, AVector2D<type> &q, AVector2D<type> &r )
{
 r.x = p.x + q.x, r.y = p.y + q.y ;
}

template <typename type>
inline 
void vct_add ( AVector2D<type> &p, AVector2D<type> &q )
{
  p.x += q.x, p.y += q.y ;
}


template <typename type>
inline 
void vct_sub ( Vec3<type> &p, Vec3<type> &q, Vec3<type> &r )
{
  r.x = p.x - q.x, r.y = p.y - q.y, r.z = p.z - q.z ;
}

template <typename type>
inline 
void vct_sub ( Vec3<type> &p, Vec3<type> &q )
{
  p.x -= q.x, p.y -= q.y, p.z -= q.z ;
}

template <typename type>
inline 
void vct_sub ( const AVector2D<type> &p, const AVector2D<type> &q, AVector2D<type> &r )
{
  r.x = p.x - q.x, r.y = p.y - q.y ;
}

template <typename type>
inline 
void vct_sub ( AVector2D<type> &p, AVector2D<type> &q )
{
  p.x -= q.x, p.y -= q.y ;
}



template <typename type>
inline void VctMul ( Vec3<type> &p, type q, Vec3<type> &r )
{
  r.x = p.x*q, r.y = p.y*q, r.z = p.z*q ;
}
template <typename type>
inline void VctMul ( AVector2D<type> &p, type q, AVector2D<type> &r )
{
  r.x = p.x*q, r.y = p.y*q ;
}


template <typename type>
inline 
void VctScale ( Vec3<type> &p, type q, Vec3<type> &r )
{
  r.x = p.x*q, r.y = p.y*q, r.z = p.z*q ;
}

template <typename type>
inline 
void VctScale ( Vec3<type> &p, type q )
{
  p.x *= q, p.y *= q, p.z *= q ;
}

template <typename type>
inline 
void VctScale ( AVector2D<type> &p, type q, AVector2D<type> &r )
{
  r.x = p.x*q, r.y = p.y*q ;
}

template <typename type>
inline 
void VctScale ( AVector2D<type> &p, type q )
{
  p.x *= q, p.y *= q ;
}
*/

/*
// the length of vector
template <class T>
inline 
T vct_len ( const Vec3<T> &v )
{
	return sqrt ( v.x*v.x + v.y*v.y + v.z*v.z ) ;
}

template <class T>
inline 
T vct_len ( const AVector2D<T> &v )
{
	return hypot(v.x,v.y) ;
}
*/
/*
// the square of vector length
template <class T>
inline 
T vct_len_sqr ( const Vec3<T> &v )
{
	return ( v.x*v.x + v.y*v.y + v.z*v.z ) ;
}

template <class T>
inline 
T VctLenSqr ( const AVector2D<T> &v )
{
	return ( v.x*v.x + v.y*v.y ) ;
}
*/




/*
template <class type>
inline 
void VctNrm ( Vec3<type> &a, Vec3<type> &b, Vec3<type> &c, Vec3<type> &n )
{
  n.x = a.y*(c.z - b.z) + b.y*(a.z - c.z) + c.y*(b.z - a.z) ;
  n.y = a.x*(b.z - c.z) + b.x*(c.z - a.z) + c.x*(a.z - b.z) ;
  n.z = a.x*(c.y - b.y) + b.x*(a.y - c.y) + c.x*(b.y - a.y) ;
}

template <class type>
inline 
void VctNrm ( AVector2D<type> &a, AVector2D<type> &b, AVector2D<type> &n )
{
  n.x = a.y - b.y, n.y = b.x - a.x ;
}

template <class T>
inline 
bool vct_unit ( AVector2D<T> &u )
{
	T l = vct_len(u) ;
	if ( tiny(l) )
		return false ;
	u.x /= l, u.y /= l ;
	return true ;
}

template <class T>
inline 
bool vct_unit ( Vec3<T> &v )
{
	T l = vct_len(v) ;
	if ( tiny(l) )
		return false ;
	v.x /= l, v.y /= l, v.z /= l ;
	return true ;
}

template <class type>
inline 
bool VctUnitNrm ( APoint3D<type> &a, APoint3D<type> &b, APoint3D<type> &c, Vec3<type> &n )
{
  VctNrm ( a, b, c, n ) ;
  return VctUnit(n) ;
}





template <typename type>
inline 
void VctCombo ( Vec3<type> &p, Vec3<type> &q, type &l, Vec3<type> &r )
{
  r.x = p.x + l*q.x, r.y = p.y + l*q.y, r.z = p.z + l*q.z ;
}

template <typename type>
inline 
void VctCombo ( AVector2D<type> &p, AVector2D<type> &q, type l, AVector2D<type> &r )
{
  r.x = p.x + l*q.x, r.y = p.y + l*q.y ;
}


template <class type>
inline 
bool VctDir ( Vec3<type> &p, Vec3<type> &q )
{
  type x=p.x*q.x, y=p.y*q.y, z=p.z*q.z ;
  return ( x>=0 && y>=0 && z>=0 )? true : false ;
}




/////// Angles ///////

template <typename type, typename vector_type>
inline 
type VctCosBody ( vector_type &p, vector_type &q )
{
  type pl, ql, pq ;
  pl = VctLenSqr(p) ;
  if ( Zero(pl) || Zero(ql) )
    return 1 ;

  pq = VctScalProd(p,q) ;
  return (type)(pq/sqrt(pl*ql)) ;
}

template <class type>
inline 
type VctCos ( Vec3<type> &p, Vec3<type> &q )
{
  return VctCosBody<type>(p,q) ;
}


template <class type>
inline 
type VctCos ( AVector2D<type> &p, AVector2D<type> &q )
{
  return VctCosBody<type>(p,q) ;
}



// calculates the sin of angle between two vectors
template <class T>
inline T vct_sin ( const Vec3<T> &p, const Vec3<T> &q )
{
	// p x q = n|p||q|sin(a)

	T pl, ql, pql ;
	Vec3<T> pq ;

	pl = vct_len_sqr(p) ;
	ql = vct_len_sqr(q) ;
	
	if ( tiny(pl) || tiny(ql) )
		return 1 ;

	vct_cross(p,q,pq) ;
	pql = vct_len(pq) ;

	return pql/sqrt(pl*ql) ;
}


template <class type>
inline 
type VctAngle ( const AVector2D<type> &p, const AVector2D<type> &q )
{
  type pl, ql ;
  Vec3<type> vct ;
  type scal ;
  type cosa, sina ;
  type lsqrt, vctl ;
  type alpha ;
  
  type pi = const_pi<type>()() ;

  pl = VctLenSqr(p) ;
  ql = VctLenSqr(q) ;
  if ( Zero(pl) || Zero(ql) )
    return const_inf<type>()() ;

  VctProd ( p, q, vct ) ;
  scal = VctScalProd ( p, q ) ;

  vctl = VctLen ( vct ) ;

  if ( vct.z < 0 )
    vctl = -vctl ;

  if ( Zero(vctl) )
    return scal > 0 ? 0 : pi ;


  lsqrt = sqrt(pl*ql) ;

  cosa = scal / lsqrt ;
  sina = vctl / lsqrt ;

  alpha = acos(cosa) ;

  if ( sina < 0 )
    alpha = pi + pi - alpha ;

  return alpha ;
}




//// Misc ////////

template <typename type>
inline 
bool VctGetOrto ( const Vec3<type> &v, const APoint3D<type> &p, APoint3D<type> &x )
{
  //type div = v.x*v.x + v.y*v.y + v.z*v.z ;
  //type num = v.x*p.x + v.y*p.y + v.z*p.z ;
  type div, num, mul ;
  type eps = const_eps<type>()() ;

  div = VctScalProd ( v, v ) ;
  num = VctScalProd ( v, p ) ;

  if ( tiny(div,eps) || tiny(num,eps) )
    return false ;

  mul = num / div ;

  VctMul ( v, mul, x ) ;

  //x.x = v.x * num / div ;
  //x.y = v.y * num / div ;
  //x.z = v.z * num / div ;

  return true ;
}
*/

}  // namespace




