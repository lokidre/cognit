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

template <class T>
T median_select ( const int k, T *arr, const int n )
{
	int low, high ;
	int median ;
	int middle, ll, hh ;
	T t ;

	#define swap_elem(_u,_v) (t=(_u),(_u)=(_v),(_v)=t)

	low = 0, high = n-1, median = (low + high) / 2 ;
	
	for (;;) {
		if ( high <= low )  // one element
			return arr[k] ;

		if ( high == low + 1 ) {  // two elements
			if (arr[low] > arr[high])
				swap_elem(arr[low],arr[high]) ;
			return arr[k] ;
		}

		// Find median of low, middle and high items; swap into position low
		middle = (low + high) >> 1 ;
		if ( arr[middle] > arr[high] ) 
			swap_elem(arr[middle],arr[high]) ;
		if ( arr[low] > arr[high] ) 
			swap_elem(arr[low],arr[high]) ;
		if ( arr[middle] > arr[low] ) 
			swap_elem(arr[middle], arr[low]) ;

		// Swap low item (now in position middle) into position (low+1)
		swap_elem(arr[middle],arr[low+1]) ;

		// Nibble from each end towards middle, swapping items when stuck
		ll = low + 1, hh = high ;
		t = arr[low] ;
		for (;;) {
			do {  ++ll ;  }  while ( t > arr[ll] ) ;
			do {  --hh ;  }  while ( t < arr[hh] ) ;
			if ( hh < ll )
				break ;
			swap_elem(arr[ll], arr[hh]) ;
		}

		// Swap middle item (in position low) back into correct position
		swap_elem(arr[low], arr[hh]) ;

		// Re-set active partition
		if ( hh <= k )
			low = ll ;
		if ( hh >= k )
			high = hh - 1 ;
	}

	#undef swap_elem
}

}

