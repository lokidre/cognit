/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#include <test_main_mtx.h>

#include <cognit/mtx/mtx_add.hpp>



template <class T, template <class TT> class MT>
void bodyM(const cognit::Mtx<T>& am, const cognit::Mtx<T>& bm)
{
    using namespace cognit;

    auto a = am.template convert<MT<T>>();
    auto b = bm.template convert<MT<T>>();

    dumpMtx(a, "a");
    dumpMtx(b, "b");

    auto c = a + b;
    dumpMtx(c, "a + b");


    mtx_add(a, b, c);
    dumpMtx(c, "mtx_add(a, b)");

    c = a;
    c += b;
    dumpMtx(c, "a += b");



    c = a - b;
    dumpMtx(c, "a - b");

    mtx_sub(a, b, c);
    dumpMtx(c, "mtx_sub(a, b)");

    c = a;
    c -= b;
    dumpMtx(c, "a -= b");


}


template <class T>
void bodyT()
{
    auto mtcs = loadMtxArgs<T>(1);

//    for (auto& mi: mtcs) {
    const auto& a = mtcs[0].mtx;
    const auto& b = mtcs[1].mtx;

    apl::verify(a.M == b.M && a.N == b.N, "Matrix dimensions don't match");

        switch (mtcs[0].size) {
        case TextMtxSize::S2x2: bodyM<T, cognit::Mtx2>(a, b); break;
        case TextMtxSize::S3x3: bodyM<T, cognit::Mtx3>(a, b); break;
        case TextMtxSize::S4x4: bodyM<T, cognit::Mtx4>(a, b); break;
        default: throw std::runtime_error("Unsupported Mtx Size");
        }
//    }
}


void body()
{
    switch (testT_) {
    case TestT::Double: bodyT<double>(); break;
    case TestT::Float: bodyT<float>(); break;
    default: throw std::runtime_error("Unsupported T");
    }
}
