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
			Least Squares Method for Surface

*/


namespace cognit {


/*
	Input:
		array of (x,y,z) points

	Output:

	Accepts 3x3 array of values, fits surface and finds maxima

*/
template <class P, class T>
void lsm_surface ( const P *pts, int n, T *data, T &x, T &y )
{
	
}


}
