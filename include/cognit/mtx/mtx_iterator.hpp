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


// needed move somewhere else
template <class T>
class mtx_column_iterator {
private :
	T *p_ ;
	int n_ ;

public :
	mtx_column_iterator(T *a, const int n): p_(a), n_(n) {}
	
	T &operator *() const {  return *p_ ;  }
	
	void operator++() {  p_ += n_ ;  }
} ;


}

