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
			Linear Least Squares Method
*/


#include "../const.hpp"
#include "../func.hpp"


namespace cognit {


//
// returns least squares minimization
// 
//


//
// X and Y are provided as one iterator with ->x and ->y elements
//
template <class iT, class T>
bool lsm ( iT p, const iT p_end, T &a, T &b )
{
	T sx(0), sy(0), sxy(0), sxx(0) ;
	int n(0) ;
	
	for ( ; p != p_end ; ++p ) {
		sx += p->x ;
		sy += p->y ;
		sxx += p->x * p->x ;
		sxy += p->x * p->y ;
		++n ;
	}
	
	T s = n*sxx - sx*sx ;
	
	if ( abs(s) < const_eps<T>()() )
		return false ;
		
	a = (n*sxy - sx*sy)/s ;
	b = (sxx*sy - sx*sxy)/s ;
	
	return true ;
}


template <class iT, class T>
bool lsm ( iT p, int n, T &a, T &b )
{
	T sx(0), sy(0), sxy(0), sxx(0) ;
	
	for ( int i = 0 ; i < n ; ++i, ++p ) {
		sx += p->x ;
		sy += p->y ;
		sxx += p->x * p->x ;
		sxy += p->x * p->y ;
	}
	
	T s = n*sxx - sx*sx ;
	
	if ( abs(s) < const_eps<T>()() )
		return false ;
		
	a = (n*sxy - sx*sy)/s ;
	b = (sxx*sy - sx*sxy)/s ;
	
	return true ;
}


//
// X and Y are provided as separate arrays
//
template <class iT, class T>
bool lsm ( const iT x_it, const iT y_it, int n, T &a, T &b )
{
	iT px = x_it, py = y_it ;

	// fight overflow - first find boundaries of data
	T minx(*x_it), maxx(*x_it), miny(*y_it), maxy(*y_it) ;

	for ( int i = 0 ; i < n ; ++i, ++px, ++py ) {
		if ( *px < minx )
			minx = *px ;
		else
			if ( *px > maxx )
				maxx = *px ;
		if ( *py < miny )
			miny = *py ;
		else
			if ( *py > maxy )
				maxy = *py ;
	}

	// we can do 2 things - scale and shift
	T scale = std::abs(std::max(maxx - minx, maxy - miny)) ;
	T shiftx = (maxx + minx) / 2;
	T shifty = (maxy + miny) / 2;
	
	T sx(0), sy(0), sxy(0), sxx(0) ;

	px = x_it, py = y_it ;

	T x, y ;
	
	// maybe we don't want to scale
	if ( tiny(scale) ) {
		for ( int i = 0 ; i < n ; ++i, ++px, ++py ) {
			sx += *px ;
			sy += *py ;
			sxx += *px * *px ;
			sxy += *px * *py ;
		}
	} else {
		for ( int i = 0 ; i < n ; ++i, ++px, ++py ) {
			x = ( *px - shiftx ) / scale;
			y = ( *py - shifty ) / scale ;
			sx += x ;
			sy += y ;
			sxx += x*x ;
			sxy += x*y ;
		}
	}
	
	T s = n*sxx - sx*sx ;
	
	if ( tiny(s) )
		return false ;
		
	a = (n*sxy - sx*sy)/s ;
	b = (sxx*sy - sx*sxy)/s ;

	if ( !tiny(scale) ) {  // correct scaling
		b = b - (a*shiftx-shifty) ;
	} 
	
	return true ;
}

}

