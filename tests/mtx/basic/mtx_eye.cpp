/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
// Generates identity matrix

#include <test_main_mtx.h>

template <class T, template <class TT> class Mtx>
void bodyM()
{
    Mtx<T> m{};

    m.eye();

    dumpMtx(m);
}

template <class T>
void bodyT()
{
    switch (testMtxSize_) {
    case TextMtxSize::S2x2: bodyM<T, cognit::Mtx2>(); break;
    case TextMtxSize::S3x3: bodyM<T, cognit::Mtx3>(); break;
    case TextMtxSize::S4x4: bodyM<T, cognit::Mtx4>(); break;
    default: throw std::runtime_error("Unsupported Mtx Size");
    }
}


void body()
{
    switch (testT_) {
    case TestT::Double: bodyT<double>(); break;
    default: throw std::runtime_error("Unsupported T");
    }
}
