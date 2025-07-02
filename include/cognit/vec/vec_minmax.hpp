/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
﻿#pragma once


#include "../vec.hpp"


namespace cognit {

template <class T>
struct VecMinMax2 {
    using It = const Vec2<T> *;
    It minX, minY, maxX, maxY;
};

template <class T, class Idx>
VecMinMax2<T> minmax(const Vec2<T>* pts, Idx n) noexcept 
{
    VecMinMax2<T> mm{pts, pts, pts, pts};

    for (auto p = pts, end = p + n; p != end; ++p) {
        if (p->x > mm.maxX->x)
            mm.maxX = p;
        else if (p->x < mm.minX->x)
            mm.minX = p;

        if (p->y > mm.maxY->y)
            mm.maxY = p;
        else if (p->y < mm.minY->y)
            mm.minY = p;
    }

    return mm;
}

} // namespace cognit
