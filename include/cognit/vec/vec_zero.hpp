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

template <class iterator, class Idx>
void vct_zero(iterator x, Idx n)
{
    for (Idx i = 0; i < n; ++i, ++x)
        *x = 0;
}

}  // namespace cognit
