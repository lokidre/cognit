/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#include <iostream>
#include <fstream>
#include <cmath>


template <class value_type>
int fuzzy_compare ( const value_type &a, const value_type &b )
{
  return fabs(a-b) < 0.0000007 ? 0 : 1 ;
}



int main ( int argc, char *argv[] )
{
  if ( argc < 3 )
    return -1 ;
    
    
  using namespace std ;
  
  ifstream sa(argv[1]), sb(argv[2]) ;
  
  if ( !sa.good() || !sb.good() )
    return -2 ;

  int test_result = 0 ;
  double a, b ;

  // read all the data
  while ( !sa.eof() && !sb.eof() ) {
    sa >> a ;
    sb >> b ;
    test_result = fuzzy_compare(a,b) ;
    
    if ( test_result != 0 )
      return test_result ;
  }
  
  
  return test_result ;
}
