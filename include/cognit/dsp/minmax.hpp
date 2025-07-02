/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

namespace cognit {

template <class T, class iT>
T min_data_basic(iT begin, iT end)
{
    T t;
    iT it = begin;
    T val = *it++;

    while (it != end) {
        if (t = *it; t < val)
            val = t;
        ++it;
    }

    return val;
}


template <class T, class iT>
T max_data_basic(iT begin, iT end)
{
    T t;
    iT it = begin;
    T val = *it++;

    while (it != end) {
        if (t = *it; t >val)
            val = t;
        ++it;
    }

    return val;
}



/*
template <class iT>
inline
typename iT::value_type min_data ( const iT begin, const iT end )
{
    return min_data_basic<typename It::value_type,iT>(begin,end) ;
}
*/


template <class T>
T min_data(const T* begin, const T* end)
{
    return min_data_basic<T>(begin, end);
}


/*
template <class iT>
inline
typename iT::value_type max_data ( const iT begin, const iT end )
{
    return max_data_basic<typename It::value_type>(begin,end,t) ;
}
*/


template <class T>
T max_data(const T* begin, const T* end)
{
    return max_data_basic<T>(begin, end);
}

}  // namespace cognit
