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
#include "../geo/line.hpp"

#include "../mtx.hpp"
#include "../mtx/mtx_eigen_system_simm.hpp"

#include "../st/cov.hpp"
#include "../st/mean.hpp"


namespace cognit {

//
// Finding least squares approximation using Principal Component Analysis
//


// Returns tuple: <success/fail, center, vector>
template <class T>
struct LsmPcaRet {
    bool success;
    Vec2<T> center, vector;
};

//template <class T>
//using LsmPcaRet = std::tuple<bool, Vec2<T>, Vec2<T>>;

template <class T, class Idx>
LsmPcaRet<T> lsm_pca_impl(const T* xd, Idx xstride, const T* yd, Idx ystride, Idx n) noexcept
{
    // Build covariance matrix
    auto c = cov_mtx_impl(xd, xstride, yd, ystride, n);

    // Find eigenvalues with eigen vectors
    auto eigen = eigen_system_simm(c);
    if (!std::get<0>(eigen))
        return {};

    auto& m = std::get<2>(eigen);

    // Calculate centroid
    auto p = centroid_impl(xd, xstride, yd, ystride, n);

    // Normalize the vector
    auto l = std::hypot(m.a[0][0], m.a[1][0]);

    if (l < constants::delta<T>)
        return {};

    Vec2<T> v{m.a[0][0] / l, m.a[1][0] / l};

    return {true, p, v};
}

template <class T, class Idx>
LsmPcaRet<T> lsm_pca(const T* xd, const T* yd, Idx n) noexcept {
    auto stride = (Idx)sizeof(T);
    return lsm_pca_impl(xd, stride, yd, stride, n);
}

template <class T, class Idx>
LsmPcaRet<T> lsm_pca(const Vec2<T>* pts, Idx n) noexcept {
    auto stride = (Idx)sizeof(Vec2<T>);
    return lsm_pca_impl(&pts->x, stride, &pts->y, stride, n);
}



template <class T>
using LsmPcaPLineRet = std::tuple<bool, ParametricLine<T>>;

template <class T, class Idx>
LsmPcaPLineRet<T> lsm_pca_pline_impl(const T* x, Idx xstride, const T* y, Idx ystride, Idx n) noexcept
{
    auto pca = lsm_pca_impl(x, xstride, y, ystride, n);

    if (!pca.success)
        return {};

    auto& p = pca.center;
    auto& v = pca.vector;

    ParametricLine<T> l;

    l.p = {p.a[0], p.a[1]};
    l.u = {v.a[0], v.a[1]};

    return {true, l};
}

template <class T, class Idx>
LsmPcaPLineRet<T> lsm_pca_pline(const T* x, const T* y, Idx n) noexcept {
    auto stride = sizeof(T);
    return lsm_pca_pline_impl(x, stride, y, stride, n);
}


}  // namespace cognit
