/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include "test_main.h"

#include <cognit/mtx.hpp>
#include <cognit/mtx/mtx_stream.hpp>
#include <cognit/mtx/mtx_parse.hpp>
#include <cognit/mtx/mtx_convert.hpp>
//#include <cognit/mtx/mtx_format.hpp>


#include <apeal/file.hpp>

template <class M>
void dumpMtx(const M& m, apl::StrView expr = {}) {
    //std::cout << m.M << 'x' << m.N << ":" << std::endl;
    //std::cout << std::endl;

    if (!expr.empty()) {
        //std::cout << std::endl;
        std::cout << expr << ":" << std::endl << "    ";
    }

    
    std::cout << m << std::endl;

    if (!expr.empty()) {
        std::cout << std::endl;
    }
}

enum class TextMtxSize {
    Unknown, S2x2, S3x3, S4x4, SMxN,
};

extern TextMtxSize testMtxSize_;

template <class T>
struct TestMtxInput {
    TextMtxSize size{TextMtxSize::Unknown};
    int M{}, N{};
    cognit::Mtx<T> mtx;
};

template <class T>
using TestMtxInputContainer = std::vector<TestMtxInput<T>>;

template <class T>
TestMtxInputContainer<T> loadMtxArgs(int minArgs) 
{
    TestMtxInputContainer<T> mtcs;

    for (auto& arg: cmdlineVector_) {
        if (arg.front() == '-')
            continue;

        auto& mi = mtcs.emplace_back();

        auto contents = apl::loadFile(arg);
        mi.mtx = cognit::mtx_parse<T>(contents);

        mi.M = mi.mtx.M;
        mi.N = mi.mtx.N;

        if (mi.M == 2 && mi.N == 2) {
            mi.size = TextMtxSize::S2x2;
            //processConvertArg<Mtx2<T>>(mtx, argIndex++);
        } else if (mi.M == 3 && mi.N == 3) {
            mi.size = TextMtxSize::S3x3;
            //processConvertArg<Mtx3<T>>(mtx, argIndex++);
        } else if (mi.M == 4 && mi.N == 4) {
            mi.size = TextMtxSize::S4x4;
            //processConvertArg<Mtx4<T>>(mtx, argIndex++);
        } else {
            mi.size = TextMtxSize::SMxN;
        }
    }

    apl::verify(std::ssize(mtcs) >= minArgs, "Required argument missing");


    return mtcs;
}

