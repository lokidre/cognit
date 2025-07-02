/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include <cerrno>
#include <cfenv>
#include <cmath>

namespace cognit {


template <class T, class Idx>
T mean_impl(const T* data, Idx stride, Idx n) noexcept
{
	T m{}, curr{}, last{};
	auto nt = T(n);
	auto inc = stride / sizeof(T);

	std::feclearexcept(FE_ALL_EXCEPT);
	errno = 0;

	auto p = data;
	for (Idx i = 0; i < n; ++i, p += inc) {
		curr += *p;

		if (errno == EOVERFLOW && std::fetestexcept(FE_OVERFLOW)) {
			m += last / nt;
			curr = *p;

			std::feclearexcept(FE_ALL_EXCEPT);
			errno = 0;
		}

		last = curr;
	}

	m += curr / nt;

	return m;
}

template <class T, class Idx>
T mean(const T* xd, Idx n) noexcept {
	return mean_impl(xd, sizeof(T), n);
}



template <class T, class Idx>
Vec2<T> centroid_impl(const T* xd, Idx xstride, const T* yd, Idx ystride, Idx n) noexcept
{
	Vec2<T> p{}, curr{}, last{};
	auto nt = T(n);
	auto xinc = xstride / sizeof(T);
	auto yinc = ystride / sizeof(T);

	std::feclearexcept(FE_ALL_EXCEPT);
	errno = 0;

	auto px = xd, py = yd;
	for (Idx i = 0; i < n; ++i, px += xinc, py += yinc) {
		curr.x += *px;
		curr.y += *py;

		if (errno == EOVERFLOW && std::fetestexcept(FE_OVERFLOW)) {
			p.x += last.x / nt;
			p.y += last.y / nt;

			curr = {*px, *py};

			std::feclearexcept(FE_ALL_EXCEPT);
			errno = 0;
		}

		last = curr;
	}

	p.x += curr.x / nt;
	p.y += curr.y / nt;

	return p;
}

template <class T, class Idx>
Vec2<T> centroid(const T* xd, const T* yd, Idx n) noexcept {
	auto stride = (Idx)sizeof(T);
	return centroid_impl(xd, stride, yd, stride, n);
}

template <class T, class Idx>
Vec2<T> centroid(const Vec2<T>* pts, Idx n) noexcept {
	auto stride = (Idx)sizeof(Vec2<T>);
	return centroid_impl(&pts->x, stride, &pts->y, stride, n);
}


}  // namespace

