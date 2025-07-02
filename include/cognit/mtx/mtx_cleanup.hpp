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


template <class T, class matrix_type>
matrix_type &mtx_cleanup ( matrix_type &a, const T &delta )
{  
	typedef typename matrix_type::value_type value_type ;
	typedef typename matrix_type::iterator iterator ;
  
	const value_type zero = value_type(0) ;

	for ( iterator pa = a.begin(), pend = a.end() ; pa != pend ; pa++ )
		if ( abs(*pa) < delta )
			*pa = zero ;

	return a ; 
}

template <class matrix_type>
matrix_type &mtx_cleanup ( matrix_type &a )
{
	typedef typename matrix_type::value_type value_type ;
	
	return mtx_cleanup(a,const_delta<value_type>()()) ;
}



}  // namespace
