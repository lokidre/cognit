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

RGB <-> HSV conversion

#endif

#include <algorithm>
#include <tuple>

#include "../color.hpp"

namespace cognit {


//
// Converts three RGB values in (0 - 1) floating point values to
// HSV normalized to 0-1
//
template <class F>
std::tuple<F, F, F> rgb_to_hsv(F r, F g, F b) noexcept
{
    F mn, mx;
    //auto [mn, mx] = std::minmax({r, g, b});
    if (r > b) {
        if (r > g) {
            mx = r;
            mn = g < b ? g : b;
        } else {
            mx = g;
            mn = b;
        }
    } else {  // r < b;
        if (r < g) {
            mn = r;
            mx = g > b ? g : b;
        } else {
            mn = g;
            mx = b;
        }
    }


    auto c = mx - mn;

    // Black color returns (0, 0, 0)
    if (mx == 0)
        return {};

    // Grey color has only "Value" component of HSV
    if (c == 0)
        return {F(0), F(0), mx - mn / 2};

    F h{};

    if (mx == r) {
        auto seg = (g - b) / c;
        auto shift = 0;
        if (seg < 0)
            shift = 6;  // 360/6
        h = seg + shift;
    } else if (mx == g)
        h = (b - r) / c + 2;  // 120/60
    else if (mx == b) {
        h = (r - g) / c + 4;  // 240/60
    }

    h *= 60.f;
    h /= 360.f;

    auto s = c / mx;
    //auto v = (mx + mn) / 2;
    auto v = mx;

    return {h, s, v};
}

template <class F>
ColorHSV<F> rgb_to_hsv(const ColorRGB<F> rgb) noexcept
{
    auto hsvt = rgb_to_hsv(rgb.r, rgb.g, rgb.b);
    return {std::get<0>(hsvt), std::get<1>(hsvt), std::get<2>(hsvt)};
    
    //return std::make_from_tuple<ColorHSV<F>>(rgb_to_hsv(rgb.r, rgb.g, rgb.b));
}

//
// Converts three RGB values in (0 - 255) to
// HSV
//
template <class Hue, class V>
std::tuple<Hue, V, V> rgb_to_hsv_int(int r, int g, int b) noexcept
{
    auto [mn, mx] = std::minmax({r, g, b});
    auto c = mx - mn;

    // Black color returns (0, 0, 0)
    if (mx == 0)
        return {};

    // Grey color has only "Value" component of HSV
    if (c == 0)
        return {0, 0, static_cast<V>(mx - mn / 2)};

    Hue h{};

    if (mx == r) {
        auto seg = (g - b) * 60 / c;
        auto shift = 0;
        if (seg < 0)
            shift = 360;  // 360/6
        h = seg + shift;
    } else if (mx == g)
        h = (b - r) * 60 / c + 2 * 60;  // 120/60
    else if (mx == b) {
        h = (r - g) * 60 / c + 4 * 60;  // 240/60
    }

    auto s = c * 255 / mx;
    auto v = (mx + mn) / 2;

    return {h, (V)s, (V)v};
}



//
// Converts Hue value to RGB for visualization
// Hue is given as value in 0-360 range, could be float or integer
// RGB is returned as 3-tuple of 0-1 floats
//
template <class F, class H>
std::tuple<F, F, F> hue_to_rgb_int_float(H hue) noexcept
{
    constexpr F O{0}, I{1};
    auto h = F(hue);

    if (hue >= 0 && hue < 60) {
        auto l = h / 60;
        return {I, l, O};
    }

    if (hue >= 60 && hue < 120) {
        auto l = (h - 60)/ 60;
        return {I - l, I, O};
    }

    if (hue >= 120 && hue < 180) {
        auto l = (h - 120) / 60;
        return {O, I, l};
    }

    if (hue >= 180 && hue < 240) {
        auto l = (h - 180) / 60;
        return {O, I - l, I};
    }

    if (hue >= 240 && hue < 300) {
        auto l = (h - 240) / 60;
        return {l, O, I};
    }

    if (hue >= 300 && hue <= 360) {
        auto l = (h - 300) / 60;
        return {I, O, I - l};
    }

    // This shouldn't happen
    return {};
}


// 
template <class F>
std::tuple<F, F, F> hue_to_rgb(F hue) noexcept
{
    return hue_to_rgb_int_float<F>(hue * 360);
}


//
// RGB is returned as 3-tuple of 0-255 integers
//
template <class T, class H>
std::tuple<T, T, T> hue_to_rgb_int(H hue) noexcept
{
    constexpr T O{0}, I{255};
    auto h = (int)hue;// * 255;

    if (hue >= 0 && hue < 60) {
        auto l = static_cast<T>(h * 255 / 60);
        return {I, l, O};
    }

    if (hue >= 60 && hue < 120) {
        auto l = static_cast<T>(I - (h - 60) * 255 / 60);
        return {l, I, O};
    }

    if (hue >= 120 && hue < 180) {
        auto l = static_cast<T>((h - 120) * 255 / 60);
        return {O, I, l};
    }

    if (hue >= 180 && hue < 240) {
        auto l = static_cast<T>(I - (h - 180) * 255 / 60);
        return {O, l, I};
    }

    if (hue >= 240 && hue < 300) {
        auto l = static_cast<T>((h - 240) * 255 / 60);
        return {l, O, I};
    }

    if (hue >= 300 && hue <= 360) {
        auto l = static_cast<T>(I - (h - 300) * 255 / 60);
        return {I, O, l};
    }

    // This shouldn't happen
    return {};
}


} // namespace cognit

