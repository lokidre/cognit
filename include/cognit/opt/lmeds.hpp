/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

//
// Least Median Squares algorithm
//

#include "lsm.hpp"
#include "median.hpp"
#include "../const.hpp"


namespace cognit {


template <class T>
class LMedS {

public:
    const T *x_data_, *y_data_ ;
    T *buffer_ ;
    int n_ ;
    T b_{};  // b parameter
    T abs_dev_{};  // absolute deviation
    T eps_{constants::epsilon<T>};  // epsilon value ;


    T operator () ( const T &a )
    {
        const T eps = eps_ ;
        const int n = n_ ;

        int i ;

        T *p ;
        const T *x, *y ;

        for ( i = 0, p = buffer_, x = x_data_, y = y_data_ ; i < n ; ++i, ++p, ++x, ++y )
            *p = *y - a* *x ;
    
        // two cases for odd and even
        if ( n & 1 ) {  // odd 
            b_ = median_select((n-1)>>1,buffer_,n) ;
        } else {  // even
            b_ = (median_select((n>>1)-1,buffer_,n) + median_select((n>>1),buffer_,n))/2 ;
        }

        abs_dev_ = 0 ;

        T s(0), d ;

        for ( i = 0, p = buffer_, x = x_data_, y = y_data_ ; i < n ; ++i, ++p, ++x, ++y ) {
            d = *y - (a* *x + b_) ;
            abs_dev_ += abs(b_) ;
            if ( !tiny(*y,eps) )
                d /= abs(*y) ;
            if ( !tiny(d,eps) )
                s += d >= 0 ? *x : - *x ;
        }
    
        return s ;
    }
} ;


template <class T>
bool lmeds(const T *x_data, const T *y_data, Index n, T &a, T &b, T *buffer)
{
    LMedS<T> ro ;
    
    ro.x_data_ = x_data ;
    ro.y_data_ = y_data ;
    ro.buffer_ = buffer ;
    ro.n_ = n ;

    
    T lsm_a, lsm_b ;
    
    if ( !lsm(x_data,y_data,n,lsm_a,lsm_b) )
        return false ;
    
    T eps = cognit::constants::epsilon<T>;
    
    // detect standard deviation - to detect 
    const T *x = x_data, *y = y_data ;
    T chisq(0) ;
    for ( int i = 0 ; i < n ; ++i, ++x, ++y )
        chisq += sqr(*y - lsm_b - lsm_a* *x) ;
        
    T sigb = sqrt(chisq / T(n-1));
    
    T aa = lsm_a ;
    ro.b_ = lsm_b ;
    
    
    T a1 = aa, a2 ;  // start
    T f, f1 = ro(a1), f2 ;
    T abs_dev ;  // absolute deviation
    
    if ( sigb > 0 ) {
        a2 = aa + (f1>=0?(sigb>=0?sigb:-sigb):(sigb>=0?-sigb:sigb))*3 ;
        f2 = ro(a2) ;
        if ( abs(a2-a1) > eps ) {
        
            // bracketing
            while ( f1*f2 > 0 ) {  // while functions have same sign
                aa = a2 + (a2-a1) * 1.6 ;
                a1 = a2, a2 = aa ;
                f1 = f2 ;
                f2 = ro(a2) ;
            }
        
            sigb /= 100 ;
        
        
            // bisection
            while ( abs(a2-a1) > sigb ) {
        
                aa = a1 + (a2-a1)/2 ;
            
                if ( aa == a1 || aa == a2 )
                    break ;
                
                f = ro(aa) ;
            
                if ( f*f1 > 0 ) 
                    f1 = f, a1 = aa ;
                else
                    f2 = f, a2 = aa ;
            }
        }
    }
    
    b = ro.b_ ;
    a = aa ;
    abs_dev = ro.abs_dev_/n ;
    
    return true ;
}

}  // namespace cognit

