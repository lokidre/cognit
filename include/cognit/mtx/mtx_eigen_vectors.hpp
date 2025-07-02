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
	Finding Eigen Vectors when eigen values are already known

*/

namespace cognit {

//template <class T>
//using EigenVectorsRet = std::tuple<Vec2<T>, Mtx2<T>>;

template <class T>
Mtx2<T> eigen_vectors_simm(const Mtx2<T>& a, const Vec2<T>& e) noexcept
{
	using std::min, std::max, std::abs;

    Mtx2<T> sm;
	Mtx2<T> v;

	// find eigen vectors
	for (int il = 0 ; il < 2 ; ++il) {
		auto l = il == 0 ? e.x : e.y;

		// Decide from which element of matrix to start (select the largest one)
		int maxI{}, maxJ{};
		T m{}, maxM{}, a0{}, a1{};

		for (int i = 0 ; i < 2 ; ++i) {
			for (int j = 0 ; j < 2 ; j++ ) {
				sm.a[i][j] = a.a[i][j] - (i == j ? l : 0);

				if (abs(sm.a[i][j]) > m) {
					m = abs(a.a[i][j]);
					maxI = i;
					maxJ = j ;
				}
			}

			if (min(abs(sm.a[i][0]), abs(sm.a[i][1])) > maxM) {
				maxM = min(abs(sm.a[i][0]), abs(sm.a[i][1]));
				a0 = sm.a[i][0];
				a1 = sm.a[i][1];
			}
		}


		// in case of 0 - we just take one unit vector
		if (tiny(m)) {
			if (il == 0) {
				v.a[0][0] = 1;
				v.a[1][0] = 0;
			} else {
				v.a[0][1] = v.a[1][0];
				v.a[1][1] = v.a[0][0];
			}
		} else {
			if (tiny(maxM)) {
				if ( tiny(a0) ) {
					v.a[0][il] = 1;
					v.a[1][il] = 0;
				} else {
					v.a[0][il] = 0;
					v.a[1][il] = 1;
				}
			} else {
				// select the best combination - where both are not zero
				if (abs(a0) > abs(a1)) {
					v.a[0][il] = -a1 / a0;
					v.a[1][il] = 1;
				} else {
					v.a[0][il] = 1;
					v.a[1][il] = -a0 / a1;
				}
			}
		}


		// normalize eigen vector
		l = std::hypot(v.a[0][il], v.a[1][il]);

		v.a[0][il] /= l;
		v.a[1][il] /= l;
	}

	return v;
}



}  // namespace cognit

