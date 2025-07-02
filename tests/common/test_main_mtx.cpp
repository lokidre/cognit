/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#include "test_main_mtx.h"

TextMtxSize testMtxSize_{TextMtxSize::S4x4};



/*

#include <apeal/file.hpp>
#include <apeal/verify.hpp>

#include <cognit/mtx/mtx_parse.hpp>
#include <cognit/mtx/mtx_convert.hpp>

//#include <iostream>

#if COGNIT_TEST_MTX_READ_ARG_FILE

template <class M>
void processMtx(const M& m, int argIndex)
{
    testBodyMtxArg(m, argIndex);
}

template <class M, class T>
void processConvertArg(const cognit::Mtx<T>& from, int argIndex) {
    M m;
    cognit::mtx_convert(from, m);
    processMtx(m, argIndex);
}


#else

template <class M>
void processMtx()
{
    testBodyMtx<M>();
}

#endif

template <class T>
void processType()
{
    using namespace cognit;

#if COGNIT_TEST_MTX_2x2
    processMtx<Mtx2<T>>();
#elif COGNIT_TEST_MTX_3x3
    processMtx<Mtx3<T>>();
#elif COGNIT_TEST_MTX_4x4
    processMtx<Mtx4<T>>();
#else
    // TODO: analyze command line parameters
    processMtx<Mtx2<T>>();
    processMtx<Mtx3<T>>();
    processMtx<Mtx4<T>>();
#endif
}



int main(int argc, char* argv[])
{
#ifdef COGNIT_TEST_FLOAT_TYPE
    using T = COGNIT_TEST_FLOAT_TYPE;
#else        
    using T = double;
#endif


    try {
        cmdlineArgC_ = argc;
        cmdlineArgV_ = argv;

        for (auto i = 1; i < argc; ++i) {
            cmdlineVector_.push_back(argv[i]);
        }

        // TODO: analyze command line parameters

#if COGNIT_TEST_MTX_READ_ARG_FILE
        using namespace cognit;

        apl::verify(!cmdlineVector_.empty(), "Required parameter missing");

        for (auto& arg: cmdlineVector_) {
            if (arg.front() == '-')
                continue;

            auto contents = apl::loadFile(arg);
            auto mtx = cognit::mtx_parse<T>(contents);
            int argIndex{};

            if (mtx.M == 2 && mtx.N == 2) {
                processConvertArg<Mtx2<T>>(mtx, argIndex++);
            } else if (mtx.M == 3 && mtx.N == 3) {
                processConvertArg<Mtx3<T>>(mtx, argIndex++);
            } else if (mtx.M == 4 && mtx.N == 4) {
                processConvertArg<Mtx4<T>>(mtx, argIndex++);
            } else {
                apl::throwError("Unsupported matrix size: %s", arg);
            }
        }
#else        

        processType<T>();

#endif  // If reading from files

        //processType<float>();
        //processType<long double>();
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        retCode_ = 1;
    }
    catch (...) {
        std::cout << "Exception!" << std::endl;
        retCode_ = 2;
    }

    return retCode_;
}
*/
