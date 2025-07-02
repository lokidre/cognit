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

#include <stdlib.h>
#include <stdio.h>

#include <mat/matrix.c++>
#include <mat/matrix/io.c++>


using namespace std ;
using namespace mat ;


template <class float_type>
void random_matrix_gen ( int n, AMatrix<float_type> &m )
{
  int max_rand = 3000 ;
  int u, v ;
  
  m.resize(n,n) ;
  float_type *p = m.p ;
  for ( int i = 0 ; i < n ; i++ )
    for ( int j = 0 ; j < n ; j++, p++ ) {
      u = rand()%max_rand - max_rand/2 ;
      do {
        v = rand()%max_rand - max_rand/2 ;
      } while ( v == 0 ) ;
      
      *p = (float_type(u))/v ;
      
      cout << *p << " "  ;
    }
}


template <class float_type>
void det_torture ( void )
{
  cout << "generating det torture " << flush ;
  
  AMatrix<float_type> a ;
  char file_name[100] ;
  fstream file ;
  int matrix_index = 1 ;
  
  // do for all matrices from 2 to 10
  for ( int n = 2 ; n < 10 ; n++ ) {
    
    // do some number of matrices of current size
    for ( int imx = 0 ; imx < 50 ; imx++ ) {
      sprintf(file_name,"det.%d",matrix_index) ;
      string file_path = "torture/" ;
      file_path += file_name ;
      
      file.open(file_path.c_str(),ios::out) ;
      
      random_matrix_gen(n,a) ;
      
      file << a ;
      file.close() ;
      matrix_index++ ;
    }
  
  }
  
  cout << "ok" << endl ;
}


template <class float_type>
int torture_gen ( void )
{
  try {
    det_torture<float_type>() ;
  }
  catch(...) {
    cout << "error generating torture files" << endl ;
    return 1 ;
  }
  
  return 0 ;
}


int main()
{
    return torture_gen<double>() ;
}


