/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

//#include "../mat/vec.cxx"

//#include <vector>


namespace cognit {


//
// case when we know the dimensions
//

/*
template <class stream_type, class T>
stream_type &input_vector ( stream_type &stream, T *pa, const int n )
{
	for ( int i = 0 ; i < n ; ++i, ++pa )
		stream >> *pa ;
	return stream ;
}


//
// case when we don't know the dimensions
//
template <class S, class T>
S &input_vector ( S &stream, Vec<T> &v )
{
	T t ;
	std::vector<T> tv ;

	while ( !stream.eof() && !stream.bad() ) {
		stream >> t ;
		tv.push_back(t) ;
	}

	if ( tv.empty() )
		throw std::runtime_error("invalid vector") ;

	const int n = int(tv.size()) ;

	v.resize(n) ;
	for ( int i = 0 ; i < n ; ++i )
		v.p[i] = tv[i] ;

	return stream ;
	// return input_vector(stream,v.p,n) ;
}



template <class stream_type, class T>
inline
stream_type &output_vector ( stream_type &stream, const T *pa, const int n )
{
	for ( int i = 0 ; i < n ; ++i, ++pa ) {
		if ( i )
			stream << ' ' ;
		stream << *pa ;
	}

	return stream ;
}
*/

/*
// tMatrix2<type>
template <typename type>
inline
istream& operator >> ( istream &stream, tVector2<type> &a )
{
  return __mtx_vector_in ( stream, (type *)a.a, 2 ) ;
}
*/

/*
template <class stream_type, class T>
inline
stream_type& operator << ( stream_type &stream, const Vec2<T> &a )
{
	return output_vector ( stream, (T *)a.a, 2 ) ;
}


template <class stream_type, class T>
inline
stream_type& operator << ( stream_type &stream, const Vec3<T> &a )
{
	return output_vector ( stream, (T *)a.a, 3 ) ;
}

template <class stream_type, class T>
inline
stream_type& operator << ( stream_type &stream, const Vec4<T> &a )
{
	return output_vector ( stream, (T *)a.a, 4 ) ;
}

template <class stream_type, class T>
inline
stream_type& operator >> ( stream_type &stream, Vec4<T> &a )
{
  return input_vector ( stream, (T *)a.a, 4 ) ;
}


template <class stream_type, class T>
inline
stream_type& operator >> ( stream_type &stream, Vec3<T> &a )
{
  return input_vector ( stream, (T *)a.a, 3 ) ;
}
*/


/*

// tMatrix4<type>

template <typename type>
inline
ostream& operator << ( ostream &stream, tVector4<type> &a )
{
  return __mtx_vector_out ( stream, (type *)a.a, 4 ) ;
}

// tMatrixN<type,n>
template <typename type,int n>
inline
istream& operator >> ( istream &stream, tVectorN<type,n> &a )
{
  return __mtx_vector_in ( stream, (type *)a.a, n ) ;
}

template <typename type,int n>
inline
ostream& operator << ( ostream &stream, tVectorN<type,n> &a )
{
  return __mtx_vector_out ( stream, (type *)a.a, n ) ;
}
*/


/*
template <class S, class T>
inline
S &operator >> ( S &stream, AVector<T> &v )
{
  return input_vector ( stream, v ) ;
}


template <class S, class T>
inline
S& operator << ( S &stream, const AVector<T> &a )
{
	return output_vector ( stream, a.p, a.N ) ;
}
*/

}

