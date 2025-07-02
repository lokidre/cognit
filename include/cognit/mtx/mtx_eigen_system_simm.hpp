/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include "mtx_eigen_vectors.hpp"


/*
    Eigen System for Simmetrical matrices

*/

namespace cognit {


//
// Eigen System for simmetrical matrices
//
template <class T>
using EigenSystemRet = std::tuple<bool, Vec2<T>, Mtx2<T>>;

template <class T>
EigenSystemRet<T> eigen_system_simm(const Mtx2<T>& a) noexcept
{
    using std::swap;

    // Solve quadratic equation
    auto p = a.a[0][0] - a.a[1][1];

    auto d = a.a[0][1] * a.a[1][0] * 4 + p*p;
    auto t = a.a[0][0] + a.a[1][1];

    // This might happen if the matrix is not symmetric, check just in case
    if (d < 0)  
        return {};

    d = std::sqrt(d);

    // Center
    Vec2<T> e{(t - d) / 2, (t + d) / 2};

    // Sort eigenvalues
    if (std::abs(e.y) > std::abs(e.x))
        swap(e.x, e.y);

    auto v = eigen_vectors_simm(a, e);

    return {true, e, v};
}



/*
//
// same for simmetric matrices
//
template <class T>
bool eigen_system_simm(const Mtx3<T>& a, Vec3<T>& e, Mtx3<T>& v)
{
    MtxEigenValuesSimm(a, e);
    MtxEigenVectors(a, e, v);

    return true;
}
*/

}  // namespace cognit

