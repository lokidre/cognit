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
#include <string>

#include <stdio.h>

#include <cognit/mat/matrix.cxx>
#include <cognit/mat/matrix/io.cxx>


using namespace std ;


template <class matrix_type>
void matrix_torture ( fstream &file, int n, matrix_type &a )
{
  a.resize(n,n) ;
  file >> a ;

  cout << mtx_det(a) << endl ;
}



template <class float_type>
int det_torture ( void )
{
  using namespace mat ;

  fstream file ;
  char file_path[256] ;
  int m, n ;
  
  // do for all files
  for ( int matrix_index = 1 ; ; matrix_index++ ) {
    sprintf(file_path,"torture/det.%d",matrix_index) ;
    file.open(file_path,ios::in) ;
    
    if ( !file.good() )
      break ;
      
    cout << file_path << " " << flush ;
    
    file >> m >> n ;
    
    if ( m != n ) {
      cerr << "square matrix required" << endl ;
      return 1 ;
    }

    if ( n == 2 ) {  
      AMatrix2<float_type> a ;
      matrix_torture(file,n,a) ;
    } else if ( n == 3 ) {
      AMatrix3<float_type> a ;
      matrix_torture(file,n,a) ;
    } else if ( n == 4 ) {
      AMatrix4<float_type> a ;
      matrix_torture(file,n,a) ;
    } else if ( n == 5 ) {
      AMatrixN<float_type,5> a ;
      matrix_torture(file,n,a) ;
    } else {
      AMatrix<float_type> a ;
      matrix_torture(file,n,a) ;
    }
    
    file.close() ;
  
  }

  return 0 ;
}



int main ( void )
{
  return det_torture<double>() ;
}
