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

Bresenham algorithm for drawing line
---

#endif


#include "render.hpp"


namespace cognit {

template <class Pix, class Idx=Index>
void bresenham_line(Vec2<Idx> a, Vec2<Idx> b, const RenderTarget<Pix, Idx>& tgt, RenderLineValue<Pix, Idx> lv) noexcept
{
    auto dx = b.x - a.x;
    auto dy = b.y - a.y;

    Idx error{};
    Idx ix{1}, iy{Idx(tgt.bpr/sizeof(Pix))};  // increments

    if (dx < 0) {
        ix = -ix;
        dx = -dx;
    }

    if (dy < 0) {
        iy = -iy;
        dy = -dy;
    }

    auto dx2 = dx*2;
    auto dy2 = dy*2;

    auto row = tgt.image + a.y * tgt.bpr;

    auto p = reinterpret_cast<Pix *>(row) + a.x;

    Idx x{}, y{};

    if (dx >= dy) {
        error = dy2 - dx;
        for (Idx i{}; i < dx; ++i, p += ix) {
            *p = lv.val;
            if (error >= 0) {
                error -= dx2;
                p += iy;
                ++y;
            }
            error += dy2;
        }
    } else {
        error = dx2 - dy;

        for (Idx j{}; j < dy; ++j, p += iy) {
            *p = lv.val;
            if (error >= 0) {
                error -= dy2;
                p += ix;
                ++x;
            }
            error += dx2;
        }
    }
}

}  // namespace
