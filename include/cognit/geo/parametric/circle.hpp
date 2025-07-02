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

// x, y - center, r - radius

template <class T>
struct ParametricCircle: public ParametricCurve2<T> {

    T x, y, r ;

    virtual T fx ( T l ) override
    {
        using std::cos;

      return x + cos(l) * r ;  
    }

    virtual type fy ( T l )
    {  
        using std::sin;
      return y + sin(l) * r ;  
    }
} ;

}  // namespace

