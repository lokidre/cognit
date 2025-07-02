/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include "render_target.hpp"

#include "render_line.hpp"

namespace cognit {


template <class T, class Pix, class Idx=Index>
void render_rect(const apl::Rect<T>& r, const RenderTarget<Pix, Idx>& tgt, RenderLineValue<Pix, Idx> val) noexcept
{
    Vec2<Idx> a = r.pos();
    Vec2<Idx> b = a.off({.y=r.h});
    Vec2<Idx> c = a + r.size();
    Vec2<Idx> d = a.off({.x=r.w});

    if (b.y >= tgt.size.h)
        b.y = tgt.size.h - val.width;
    if (d.x >= tgt.size.w)
        d.x = tgt.size.w - val.width;
    
    if (c.x >= tgt.size.w)
        c.x = tgt.size.w - val.width;
    if (c.y >= tgt.size.h)
        c.y = tgt.size.h - val.width;


    bresenham_line(a, b, tgt, val);
    bresenham_line(b, c, tgt, val);
    bresenham_line(d, c, tgt, val);
    bresenham_line(a, d, tgt, val);
}

}  // namespace

