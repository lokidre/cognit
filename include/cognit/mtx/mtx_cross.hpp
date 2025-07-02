/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#if 0
	Matrix representation of vector cross product

		[a]_x = [0 -a3 a2; a3 0 -a1; -a2 a1 0]
		
		a X b = [a]_x b

#endif


namespace cognit {


template <class T>
Mtx3<T> mtx_cross(const Vec3<T> &v) noexcept
{
    Mtx3<T> a;

	a.a[0][0] =       0, a.a[0][1] = -v.a[2], a.a[0][2] =  v.a[1];
	a.a[1][0] =  v.a[2], a.a[1][1] =       0, a.a[1][2] = -v.a[0];
	a.a[2][0] = -v.a[1], a.a[2][1] =  v.a[0], a.a[2][2] =       0;

	return a ;	
}

}  // namespace

