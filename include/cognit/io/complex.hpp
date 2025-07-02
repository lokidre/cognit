/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
//
// Complex Number input/output
//

#pragma once

#include "../mat/complex.cxx"

namespace cognit {


//
// output
//
template <class stream_type, class T>
stream_type &operator << ( stream_type &stream, const AComplex<T> &x )
{
	stream << x.a ;

	if ( x.b != 0 ) {
		if ( x.b < 0 ) {
			stream << '-' << 'i' << -x.b ;
		} else {
			stream << '+' << 'i' << x.b ;
		}
	}

	return stream ;
}



//
// input
//
template <class stream_type, class T>
stream_type &operator >> ( stream_type &stream, AComplex<T> &x )
{
	char c ;
	bool imag_neg = false ;

	x.a = x.b = T(0) ;

	stream >> x.a ;
	stream >> c ;
	if ( c == '-' )
		imag_neg = true ;

	stream >> c ;
	if ( c == 'i' ) {
		stream >> x.b ;
		if ( imag_neg )
			x.b = -x.b ;
	}

	return stream ;
}



}

