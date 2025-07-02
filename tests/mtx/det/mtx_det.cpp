/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#include <test_main_mtx.h>

#include <cognit/mtx/mtx_det.hpp>



template <class T, template <class T> class MT>
void bodyM(const cognit::Mtx<T>& m)
{
    using namespace cognit;

    auto a = m.convert<MT<T>>();

    auto detA = mtx_det(a);
    con_("det<MtxN>(a): %g", detA);

    auto detM = mtx_det(m);
    con_("det<Mtx>(m): %g", detM);

    auto detDef = mtx_det_def_ptr(m.data(), m.M);
    con_("det_def<Mtx>(m): %g", detDef);

}

template <class T>
void bodyMtx(const cognit::Mtx<T>& m)
{
    using namespace cognit;

    auto detM = mtx_det(m);
    con_("det<Mtx>(m): %g", detM);

    auto detDef = mtx_det_def_ptr(m.data(), m.M);
    con_("det_def(m): %g", detDef);
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
        default: 
            apl::verify(mi.mtx.M == mi.mtx.N, "Matrix is not square");
            bodyMtx(mi.mtx);
            break;
        }
    }
}


void body()
{
    switch (testT_) {
    case TestT::Double: bodyT<double>(); break;
    case TestT::Float: bodyT<float>(); break;
    default: throw std::runtime_error("Unsupported T");
    }
}
