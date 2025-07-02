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
	Solving systems of linear equations

		A.x = B



	The methods in decreasing order of their speed and increasing order of their accuracy

		1. Cholesky
		2. LU
		3. QR
		4. SVD


	The usual tradeoff between speed and accuracy is LU decomposition.
	Although for higher accuracy and better diagnostics it is better to use SVD
*/

