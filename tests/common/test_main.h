/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include <apeal/console.hpp>

#include <exception>

extern int cmdlineArgC_;
extern char **cmdlineArgV_;

extern std::vector<std::string_view> cmdlineVector_;

extern int retCode_;

extern apl::Console con_;


enum class TestT {
    Double, Float, LongDouble, Int, Int64, UInt, UInt64
};

extern TestT testT_;

void body();
