/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include "render.hpp"
#include "../geo/line.hpp"
#include "bresenham.hpp"


namespace cognit {

//
// straight line rendering routines
//


#if 0
namespace impl {

template <class Pixel>
void render_bound_line(Vec2<Index> axis, Vec2<Index> axisSize, Pixel* image, Vec2<Index> dim, Index bpr, Pixel val)
{
    Index x0{}, y0{}, x1{}, y1{};

    //
    // deal with first point
    //
    if (y_axis < 0) {
        // check if the line crosses the ox axis
        if (x_axis < 0 || x_axis >= width)
            return;  // don't render

        x0 = x_axis, y0 = 0;

    } else if (y_axis >= height) {
        // check it the line crosses the height axis
        if (height_axis < 0 || height_axis >= width)
            return;  // don't render

        x0 = height_axis, y0 = height-1;
    } else
        x0 = 0, y0 = y_axis;


    //
    // deal with second point
    //
    if (width_axis < 0) {
        // check if the line crosses ox axis
        if (x_axis < 0 || x_axis >= width)
            return;  // don't render

        x1 = x_axis, y1 = 0;
    } else if (width_axis >= height) {
        // check it the line crosses the height axis
        if (height_axis < 0 || height_axis >= width)
            return;  // don't render

        x1 = height_axis, y1 = height-1;
    } else
        x1 = width - 1, y1 = width_axis;


    // check if the line should rendered at all
    if (x1 == x0 && y0 == y1)
        return;

    // use bresenham to render line
    bresenham_line(x0, y0, x1, y1, image, width, height, val);
}

}  // namespace impl


template <class T, class Pix, class Idx>
void render_line(const ExplicitLine<T>& l, const RenderTarget<Pix, Idx>& target, Pix val, Idx width) noexcept
{
    // detect first and last points
    // basically we have to find intersections with boundaries of rendering rectangle

    // separate treatment for horizontal line
    if (tiny(l.a)) {
        int b = int(l.b) + yo;
        if (b >= 0 && b < width) {
            pixel_type* p = image + b*width;
            for (int x = 0; x < width; ++x, ++p)
                *p = val;
        }
        return;
    }

    // find four intersections
    int x_axis, y_axis, height_axis, width_axis;

    x_axis = int((-yo-l.b)/l.a + xo);  // x,0
    y_axis = int(l.a*(-xo) + l.b + yo);

    height_axis = int((height - 1 - yo - l.b) / l.a + xo);  // height,y
    width_axis = int(l.a*(width-1-xo) + l.b + yo); //- minx ;  // x,width

    impl::render_bound_line(x_axis, y_axis, height_axis, width_axis, image, width, height, val);
}


//
// render parametric line
//
template <class T, class Pix, class Idx=Index>
void render_line(const ParametricLine<T>& l, const RenderTarget<Pix, Idx>& target, Pix val, Idx width=1)
{
    // handle separately vertical and horizontal cases
    if (tiny(l.u.x)) {  // vertical
        int x = int(l.p.x + ox);
        if (x >= 0 || x < width) {
            pixel_type* p = image + x;
            for (int i = 0; i < height; ++i, p += width)
                *p = val;
        }
        return;
    }

    if (tiny(l.u.y)) {
        int y = int(l.p.y + oy);
        if (y >= 0 && y < height) {
            pixel_type* p = image + y*width;
            for (int i = 0; i < width; ++i, ++p)
                *p = val;
        }

        return;
    }

    // find four intersections
    int x_axis, y_axis, height_axis, width_axis;

    // calculate form the following:
    // x = px + ux*t and y = py + uy*t
    // from here 
    //            ( x - px ) / ux = ( y - py ) / uy
    // so
    //             x = ( y - py ) * ux / uy + px
    //             y = ( x - px ) * uy / ux + py
    //

    x_axis = Idx((-oy - l.p.y) * l.u.x / l.u.y + l.p.x + ox);
    y_axis = Idx((-ox - l.p.x) * l.u.y / l.u.x + l.p.y + oy);

    height_axis = Idx((height-1-oy - l.p.y) * l.u.x / l.u.y + l.p.x + ox);
    width_axis = Idx((width-1-ox - l.p.x) * l.u.y / l.u.x + l.p.y + oy);


    impl::render_bound_line(x_axis, y_axis, height_axis, width_axis, image, width, height, val);
}

//
// render normal line
//
template <class T, class P>
void render_line(const NormalLine<T>& l, P* image, const int width, const int height, const P& val, const int ox=0, const int oy=0)
{
    // easiest is to convert to parametric and render parametric
    AParametricLine<T> p;
    line_convert(l, p);
    render_line(p, image, width, height, val, ox, oy);
}


template <class T, class P>
void render_line(const PointLine<T>& l, P* image, const int width, const int height, const P& val, const int ox=0, const int oy=0)
{
    // easiest is to convert to parametric and render parametric
    AParametricLine<T> p;
    line_convert(l, p);
    render_line(p, image, width, height, val, ox, oy);
}

#endif



template <class T, class Pix, class Idx=Index>
void render_segment(const PointLine<T>& l, const RenderTarget<Pix, Idx>& tgt, RenderLineValue<Pix, Idx> val) noexcept
// P* image, const int width, const int height, const P& val, const int ox=0, const int oy=0)
{
    //bresenham_line ( int(l.u.x+ox+0.5), int(l.u.y+oy+0.5), int(l.v.x+ox+0.5), int(l.v.y+oy+0.5), image, width, height, val ) ;
    bresenham_line<T>(l.u, l.v, tgt, val);
}

}  // namespace cognit

