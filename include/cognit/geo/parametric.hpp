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


//
// Base function for 2D parametric curve
//

template <class T>
struct ParametricCurve2 {
    virtual T fx(T lambda) = 0;
    virtual T fy(T lambda) = 0;
    virtual bool def(T lambda) noexcept { return true; }  // defined
    virtual bool cont(T lambda) noexcept { return true; }  // continuous
};

}  // namespace
