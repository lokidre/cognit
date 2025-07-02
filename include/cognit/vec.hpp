/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
// (C) Andrei Mirzoyan, see LICENSE for details

#pragma once


#include "def.hpp"

#include <apeal/geo.hpp>

namespace cognit {

template <class Val>
struct Vec1 {
    using T = Val;
    using value_type = T;
    T x;
};



template <class T>
using Vec2 = apl::Point<T>;

template <class T>
using Vec2A = const apl::Point<T>&;


template <class T>
using Vec3 = apl::Point3D<T>;

template <class T>
using Vec3A = const apl::Point3D<T>&;


template <class Val>
struct Vec4 {
    using T = Val;
    using value_type = T;
    T x, y, z, w;
};

template <class Val, int N>
struct VecN {
    using T = Val;
    using value_type = T;

    T a[N];
};


// Dynamic vector
// TODO: rewrite
template <class Val>
struct Vec {
    using T = Val;
    typedef T value_type;

    T* p;
    int N;

    typedef T* iterator;
    typedef const T* const_iterator;


    iterator begin() { return p; }
    iterator end() { return p + N; }

    const_iterator begin() const { return p; }
    const_iterator end() const { return p + N; }

    Vec() { p = 0, N = 0; }
    Vec(int n) { p = 0, N = 0, resize(n); }


    ~Vec()
    {
        if (p)
            delete[] p;
    }

    int n() const { return N; }

    void resize(Index sz)
    {
        if (N < sz) {
            if (p)
                delete[] p;
            p = 0;
            if (sz)
                p = new value_type[sz];
        }
        N = sz;
    }

    auto& operator[](std::size_t i) { return p[i]; }
};


}  // namespace cognit


#include "vec/vec_add.hpp"
#include "vec/vec_chop.hpp"
#include "vec/vec_cross.hpp"
#include "vec/vec_dot.hpp"
#include "vec/vec_len.hpp"
#include "vec/vec_minmax.hpp"
#include "vec/vec_norm.hpp"
#include "vec/vec_normalize.hpp"
#include "vec/vec_ortho.hpp"
#include "vec/vec_scale.hpp"
#include "vec/vec_zero.hpp"
