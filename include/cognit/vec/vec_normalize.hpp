/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include "vec_len.hpp"

namespace cognit {

template <class T>
Vec3<T> vct_normalize(Vec3A<T> v) noexcept
{
    auto len = v.norm();

    if (tiny(len))
        return v;

    return {v.x /= len, v.y /= len, v.z /= len};
}

}  // namespace cognit
