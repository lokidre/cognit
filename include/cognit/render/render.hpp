/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include "../def.hpp"
#include "../vec.hpp"

#include "render_target.hpp"

namespace cognit {


class ARender {
public :
	typedef double T ;


	enum PointStyle {
		point_x,
		point_dot,
		point_triangle,
		point_start,
		point_cross,
		point_square
	} ;


	enum LineStyle {
		line_solid,
		line_dot,
		line_dash,
		line_dash_dot
	} ;

	enum ColorMode {
		color_rgb,
		color_rgba,
		color_r_g_b,
		color_monochrome,		// greyscale
		color_bw  		// black and white color
	} ;


public :  // rendering surface setup
	void *gray_buffer_, *red_buffer_, *green_buffer_, *blue_buffer_, *rgb_buffer_, *rgba_buffer_ ;
	int width_, height_ ;  // the buffer size
	int depth_ ;  // depth in bits

	ColorMode color_mode_ ;



public :
	// point rendering
	PointStyle point_style_ ;
	T point_size_ ;

	// line rendering
	LineStyle line_style_ ;
	T line_width_ ;

	// colors
	int color_ ;

	// coordinate system



public :
	void set_surface_grey ( void *gray_buffer, int width, int height )
	{
		gray_buffer_ = gray_buffer ;
		width_ = width, height_ = height ;
		color_mode_ = color_monochrome ;
		depth_ = 8 ;
	}

	void set_surface_r_g_b ( void *r, void *g, void *b, int width, int height )
	{
		red_buffer_ = r, green_buffer_ = g, blue_buffer_ = b ;
		width_ = width, height_ = height ;
		color_mode_ = color_r_g_b ;
		depth_ = 8 ;
	}

	void set_surface_rgb ( void *rgb, int width, int height )
	{
		rgb_buffer_ = rgb ;
		width_ = width, height_ = height ;
		color_mode_ = color_rgb ;
		depth_ = 8 ;
	}

	void set_surface_rgba ( void *rgba, int width, int height )
	{
		rgba_buffer_ = rgba ;
		width_ = width, height_ = height ;
		color_mode_ = color_rgba ;
		depth_ = 8 ;
	}


} ;

}  // namespace cognit

