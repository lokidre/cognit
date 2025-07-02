/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include "dist.hpp"

#include "../point.hpp"

#include <map>


namespace cognit {

//
// collects all points in proximity to a straight line
//
template <class T, class point_iterator, class line_type, class point_container>
void collect_straight_points ( const point_iterator &begin, const point_iterator &end, const line_type &l, const T d, point_container &pts )
{
    for ( point_iterator p = begin ; p != end ; ++p ) {
        if ( dist(*p,l) <= d )
            pts.push_back(*p) ;
    }
}



//
// collects all points that belong to one segment (assumed they are on straight line)
// point container will be sorted
//
template <class point_iterator, class point_container>
void collect_segment_points ( const point_iterator &begin, const point_iterator &end, point_container &pts )
{
    // find boundary points - we need "first" and "last" points
    typedef typename point_iterator::value_type point_type ;
    typedef typename point_type::value_type T ;

    point_type a, b, c ;
    T u, v, w ;

    a = b = *begin ;
    w = pt_dist_2<T>(a,b) ;

    for ( point_iterator p = begin ; p != end ; ++p ) {
        u = pt_dist_2<T>(a,*p) ;
        v = pt_dist_2<T>(b,*p) ;

        if ( u <= w && v <= w )
            continue ;


        if ( u <= v ) {  // from left
            a = *p ;
        } else {
            b = *p ;
        }
        w = pt_dist_2<T>(a,b) ;
    }

    std::multimap<T,point_type> sorted_points ;

    // now collect all the points sorting them by distance from the first point
    for ( point_iterator p = begin ; p != end ; ++p ) {
        sorted_points.insert(std::pair<T,point_type>(pt_dist_2<T>(a,*p),*p)) ;
    }

    // find median of the distances between points

    // now select the largest chunk of close points
    auto prev_pt = sorted_points.begin(), curr_pt = prev_pt, end_pt = sorted_points.end() ;
    typename std::multimap<T,point_type>::iterator largest_begin, largest_end, largest_last, block_begin ;

    int max_count = 0, current_count = 0 ;

    T max_dist = 2 ;

    for ( block_begin = curr_pt, ++curr_pt ; curr_pt != end_pt ; ++curr_pt, ++prev_pt, ++current_count ) {
        T curr_dist = curr_pt->first - prev_pt->first ;
        if ( curr_dist < max_dist )  // distance
            continue ;

        // break the group
        //if ( current_count > max_count ) {
        if ( current_count > max_count ) {
            max_count = current_count ;
            largest_begin = block_begin ;
            largest_end = curr_pt ;
        }
        current_count = 0 ;
        block_begin = curr_pt ;
    }

    if ( current_count > max_count ) {
        max_count = current_count ;
        largest_begin = block_begin ;
        largest_end = curr_pt ;
    }

    // the last step - collect best points
    for ( auto p = largest_begin ; p != largest_end ; ++p ) {
        pts.push_back(p->second) ;
    }
}

}
