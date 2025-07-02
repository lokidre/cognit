/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
﻿#pragma once

#if 0 // Description__

Color definitions

#endif

namespace cognit {

template <class T>
struct ColorRGB {
    T r, g, b;
};

template <class T>
struct ColorRGBA {
    T r, g, b, a;
};

template <class T>
struct ColorHSV {
    T hue, sat, val;
};

template <class T>
struct ColorLAB {
    T l, a, b;
};

template <class T>
struct ColorYCC {
    T y, cb, cr;
};

} // namespace cognit
