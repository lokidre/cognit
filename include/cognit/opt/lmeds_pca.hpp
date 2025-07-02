/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
//
// Least Median Squares algorithm
//

#pragma once

#include "lsm_pca.hpp"
#include "lmeds.hpp"

namespace cognit {

template <class T>
LsmPcaRet<T> lmeds_pca(const T *x_data, const T *y_data, Index n, T *buffer)
{
	auto pca = lsm_pca(x_data, y_data, n);
	if (!pca.success)
		return pca;

	const T *x_ptr, *y_ptr ;
	T lmedsA, lmedsB;
	
	// approximate first by least squares method using principal component analysis
	//if ( !lsm_pca(x_data,y_data,n,p,v) )
	//	return false ;
		
		
	// rotate points if they are aligned vertically
	bool rotate = abs(pca.vector.x) < abs(pca.vector.y);  // needed bizaar
	
	//rotate = false ;

	if (rotate)
		x_ptr = y_data, y_ptr = x_data ;
	else
		x_ptr = x_data, y_ptr = y_data ;
	

	// now approximate by least median of squares
	if (!lmeds(x_ptr, y_ptr, n, lmedsA, lmedsB, buffer)) {
		pca.success = false;
		return pca;
	}

	if (rotate) {
		pca.vector.x = -lmedsA;
		pca.vector.y = 1;

		pca.center.x = lmedsB;
		pca.center.y = 0;
	} else {
		pca.vector.x = 1;
		pca.vector.y = lmedsA;

		pca.center.x = 0;
		pca.center.y = lmedsB;
	}

	return pca;
}

}  // namespace 

