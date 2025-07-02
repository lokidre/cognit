/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

namespace cognit {

template <class T, class Idx, class U>
void image_fill(T* data, Idx total, U v) noexcept
{
    auto val = T(v);
    for (auto p = data, end = p + total; p != end; ++p)
        *p = val;
}

}  // namespace
