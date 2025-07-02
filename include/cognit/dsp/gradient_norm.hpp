/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include <cmath>

namespace cognit {


//
//  Norm of Gradient
//

template <class input_type, class output_type>
void norm_of_gradient_2d(const input_type* dx, const input_type* dy, output_type* norm, int length)
{
    for (int i = 0; i < length; ++i, ++norm, ++dx, ++dy)
        *norm = std::hypot(*dx, *dy);
}

template <class input_type, class output_type>
void norm_of_gradient_1d(const input_type* dx, output_type* norm, int length)
{
    for (int i = 0; i < length; ++i, ++norm, ++dx)
        *norm = *dx > 0 ? *dx : -*dx;
}



//
//  The square of the norm of gradient
//

template <class input_type, class output_type>
void norm_of_gradient_sqr_2d(const input_type* dx, const input_type* dy, output_type* norm, int length)
{
    for (int i = 0; i < length; ++i, ++norm, ++dx, ++dy)
        *norm = *dx * *dx + *dy * *dy;
}




//
// version with iterators
//
/*
template <class input_iterator, class output_iterator, class size_type>
inline
void norm_of_gradient_2d ( const input_iterator &dx, const input_iterator &dy, output_iterator &norm, const size_type length )
{
    typedef input_iterator::value_type input_type ;
    typedef output_iterator::value_type output_type ;

    typename input_container_type::const_iterator dx_it(dx.begin()), dy_it(dy.begin()), dx_end(dx.end()), dy_end(dy.end()) ;

    norm.resize(std::min(dx.size(),dy.size())) ;

    typename output_container_type::iterator norm_it(norm.begin()) ;


    for ( ; dx_it != dx_end() && dy != dy_end ; ++dx_it, ++dy_it, ++norm_it )
        *norm_it = hypot(*dx_it,*dy_it) ;
}
*/


//
// version with containers
//



}  // namespace



