/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include "../vec.hpp"

namespace cognit {

template <class Pix, class Idx=Index>
struct RenderTarget {
	uint8_t *image;
	apl::Size<Idx> size;
	Idx bpr;
	Vec2<Idx> axis;
};

template <class Pix, class Idx=Index>
struct RenderLineValue {
	Pix val;
	Index width{1};

	enum class Style {
		Solid, Dot, Dash, DashDot
	};

	Style style{Style::Solid};
};

} // namespace

