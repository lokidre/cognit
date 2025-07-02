/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#if Description__

RGB <-> LAB conversion

#endif

#include <algorithm>
#include <tuple>

#include "../color.hpp"

namespace cognit {

//
// https://en.wikipedia.org/wiki/SRGB
//
template <class F>
F invGammaCorr(F t) noexcept {
    return (t <= 0.0405f)? t/12.92f : std::pow((t + 0.055f) / 1.055f, 2.4f);
}


template <class F>
F labF(F t) noexcept {
    constexpr F delta{6.f/29.f};

    return (t > delta*delta*delta) ? std::pow(t, 1.f/3.f) : t * (1.f / (delta * delta *3)) + (4.f/29.f);
}


//
// Converts three RGB values in (0 - 1) floating point values to
// LAB normalized to 0-1
//
template <class F>
std::tuple<F, F, F> rgb_to_lab(F r, F g, F b) noexcept
{
    // XYZ color of D65 white point
    constexpr F wpX{0.950456f};
    constexpr F wpY{1.f};
    constexpr F wpZ{1.088754f};

    r = invGammaCorr(r);
    g = invGammaCorr(g);
    b = invGammaCorr(b);

    // D65 sRGB
    auto x = 0.4124564f * r + 0.3575761f * g + 0.1804375f * b;
    auto y = 0.2126729f * r + 0.7151522f * g + 0.0721750f * b;
    auto z = 0.0193339f * r + 0.1191920f * g + 0.9503041f * b;


    x = labF(x / wpX);
    y = labF(y / wpY);
    z = labF(z / wpZ);

    auto labL = 116.f*y - 16.f;
    auto labA = 500.f*(x - y);
    auto labB = 200.f*(y - z);

    return {labL / 100.f, labA / 100.f, labB / 100.f};
}


template <class F>
ColorLAB<F> rgb_to_lab(const ColorRGB<F> rgb) noexcept
{
    //return std::make_from_tuple<ColorLAB<F>>(rgb_to_lab(rgb.r, rgb.g, rgb.b));
    auto labt = rgb_to_lab(rgb.r, rgb.g, rgb.b);
    return {std::get<0>(labt), std::get<1>(labt), std::get<2>(labt)};
}



} // namespace cognit
