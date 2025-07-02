/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
/*

		Gaussian Quadrature

	Approximation to definite integral by weighted sum

		\int_{-1}^1 {f(x) dx} ~ \sum_{i=1}^n{w_i f(x_i)}


	Gaussian quadrature is exact for polynomials of 2n-1 degree



	Weights can be calculated as

		w_i = \frac{2}{ (1-x_i^2) (P_n(x_i))^2 }

	where
		P_n - Legendre polynomical of degree n normalized to give P_n(1) = 1
		x_i is the i-th root of P_n



	Change of interval is as following

		\int_a^b{f(x) dx} = \frac{b-a}{2} \int_{-1}^1 {f(\frac{b-a}{2}t + \frac{b+a}{2} dt}


*/

#pragma once

namespace cognit {

enum {
	// maximum supported Gaussian Quadrature Degree
	gquad_max_degree = 5
} ;


template <class T, class F>
T gquad ( F &f, T a, T b, int n )
{
	T w[n], x[n] ;

	gquad_coeff(n,w,x) ;
	return gquad_sum(f,a,b,n,w,x) ;
}


// calculates gaussian quadrature sum
template <class T, class F>
T gquad_sum ( F &f, T a, T b, int n, const T *w, const T *x )
{
	T q = 0 ;

	for ( int i = 0 ; i < n ; ++i, ++w, ++x )
		q += *w * f( (b-a)/2 * *x + (b+a)/2 ) ;

	return (b-a)/2 * q ;
}

// calculates coefficients for gaussian quadrature
template <class T>
void gquad_coeff(int n, T *w, T *x)
{
	T a ;

	switch(n) {
	case 1 :
		x[0] = 0 ;
		
		w[0] = 2 ;
		break ;

	case 2 :
		x[0] = -sqrt(T(1)/3) ;
		x[1] = -x[0] ;
		
		w[0] = w[1] = 1 ;
		break ;

	case 3 :
		x[0] = -sqrt(T(3)/5) ;
		x[1] = 0 ;
		x[2] = -x[0] ;

		w[0] = T(5)/9 ;
		w[1] = T(8)/9 ;
		w[2] = w[0] ;
		break ;

	case 4 :
		x[0] = -sqrt( (T(3) + 2*sqrt(T(6)/5)) / 7 ) ;
		x[1] = -sqrt( (T(3) - 2*sqrt(T(6)/5)) / 7 ) ;
		x[2] = -x[1] ;
		x[3] = -x[0] ;

		w[0] = ( T(18) - sqrt(T(30)) ) / 36 ;
		w[1] = ( T(18) + sqrt(T(30)) ) / 36 ;
		w[2] = w[1] ;
		w[3] = w[0] ;
		break ;

	case 5 :
		a = T(2)*sqrt(T(10)/7) ;

		x[0] = - sqrt( T(5) + a ) / 3 ;
		x[1] = - sqrt( T(5) - a ) / 3 ;
		x[2] = 0 ;
		x[3] = -x[1] ;
		x[4] = -x[0] ;


		a = T(13)*sqrt(T(70)) ;

		w[0] = ( T(322) - a ) / 900 ;
		w[1] = ( T(322) + a ) / 900 ;
		w[2] = T(128)/225 ;
		w[3] = w[1] ;
		w[4] = w[0] ;

		break ;

	default:  
		throw std::runtime_error("Unsupported Gaussian Quadrature") ;
	}
}

}  // namespace cognit
