/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
﻿// Generates identity matrix

#include <test_main_mtx.h>


template <class T, template <class T> class MT>
void bodyM(const cognit::Mtx<T>& a)
{
    MT<T> m;
    cognit::mtx_convert(a, m);

    dumpMtx(m);
    con_.nl();
}


template <class T>
void bodyT()
{
    auto mtcs = loadMtxArgs<T>(1);

    for (auto& mi: mtcs) {
        switch (mi.size) {
        case TextMtxSize::S2x2: bodyM<T, cognit::Mtx2>(mi.mtx); break;
        case TextMtxSize::S3x3: bodyM<T, cognit::Mtx3>(mi.mtx); break;
        case TextMtxSize::S4x4: bodyM<T, cognit::Mtx4>(mi.mtx); break;
        default: throw std::runtime_error("Unsupported Mtx Size");
        }
    }
}


void body()
{
    switch (testT_) {
    case TestT::Double: bodyT<double>(); break;
    default: throw std::runtime_error("Unsupported T");
    }
}


