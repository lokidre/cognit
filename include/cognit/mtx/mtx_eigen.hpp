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

	Definition

		AX=lX
 
		a01*x1 + a01*x2 + a02*x3 = l*x1
		a11*x1 + a11*x2 + a12*x3 = l*x2
		a21*x1 + a21*x2 + a22*x3 = l*x3


	The values of lambda that these equations have solutions 
	are called eigenvalues (characteristic, latent roots). 
	The solutions are called eigenvectors (characteristic vectors)
	The eigenvalues of symmetric matrix are real
	In general the eigenvalues are complex





	Method - solving the system of equations of degree n

	AX=lX ==> AX==lIX ==> (A-lI)X==0 or

	e.g. for matrix of third degree

		| a01-l + a01   + a02   | 
		| a11   + a11-l + a12   | = 0
		| a21   + a21   + a22-l | 

	det(a) == l^3 - (a00+a11+a22)*l^2 - (a01*a10-a00*a11+a02*a20+a12*a21-a00*a22-a11*a22)*l
		           + a00*(a12*a21-a11*a22) + a01*(a10*a22-a12*a20) + a02*(a11*a20-a10*a21)




	Eigenvectors can be calculated by solving the following equation

		(A-lI)v = 0
 

#endif



#include "../def.hpp"
#include "../complex.hpp"


namespace cognit {




}  // namespace


#include "mtx_eigen_system_simm.hpp"

