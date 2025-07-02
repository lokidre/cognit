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

template <class T>
Vec3<T> vct_cross(Vec3A<T> p, Vec3A<T> q) noexcept {
    return {
        p.y * q.z - p.z * q.y,
        p.z * q.x - p.x * q.z,
        p.x * q.y - p.y * q.x,
    };
}

template <class T>
Vec3<T> vct_cross(Vec2A<T> p, Vec2A<T> q) noexcept {
    return {0, 0, p.x * q.y - p.y * q.x};
}

}  // namespace cognit

