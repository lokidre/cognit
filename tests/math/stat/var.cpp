/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#include "../common/common.h"
#include "../common/load.h"

#include <cognit/mat/stat.cxx>


template <class T>
void test()
{
	using namespace cognit ;

	apl::ABuffer<T> x ;


	load_x(*input_stream_list[0],x) ;

	T m = var(x.get(),x.size()) ;

	*output_stream << m << std::endl ;
}


#include "../common/common.cpp"
#include "../common/common_main.cpp"
