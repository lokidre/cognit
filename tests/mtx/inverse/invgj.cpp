/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
// *mtx* [<a file>] [<b file>] [<c file>]


#include <mat/mat.h>
#include <mat/matrix/mio.h>
#include <iostream>
#include <fstream>

using namespace std ;

typedef double float_type ;



int m, n ;  // dimensions

AMatrix2<float_type>       a2, b2, c2 ;
AMatrix3<float_type>       a3, b3, c3 ;
AMatrix4<float_type>       a4, b4, c4 ;
AMatrixN<float_type,5>     a5, b5, c5 ;
AMatrix<float_type>        a6, b6, c6 ;


char a_file_name[256], b_file_name[256], c_file_name[256] ;


int main ( int argc, char *argv[] )
{                 
  strcpy ( a_file_name, argc > 1 ? argv[1] : "dat/a_inv6" ) ;
  strcpy ( c_file_name, argc > 3 ? argv[3] : "dat/c_inv" ) ;

  fstream a_stream, c_stream ;

  try {
    a_stream.open ( a_file_name, ios::in ) ;

    c_stream.open ( c_file_name, ios::out ) ;

    if ( !a_stream.good()  )
      throw a_file_name ;


    a_stream >> m >> n ;

    if ( m != n || m > 5 ) {
      a6.setup(m,n) ;
      a_stream >> a6 ;
      if ( !MtxInv(a6,c6) )
        cout << "matrix is singular" << endl ;
      c_stream << m << " " << n << endl << c6 ;
      cout << MtxCleanup(a6*c6) << endl ;  // visual test
    } else if ( m == 2 ) {
      a_stream >> a2 ;
      if ( !MtxInv(a2,c2) )
        cout << "matrix is singular" << endl ;
      c_stream << m << " " << n << endl << c2 ;
      cout << a2*c2 << endl ;  // visual test
    } else if ( m == 3 ) {
      a_stream >> a3 ;
      if ( !MtxInv(a3,c3) )
        cout << "matrix is singular" << endl ;
      c_stream << m << " " << n << endl << c3 ;
      cout << a3*c3 << endl ;  // visual test
    } else if ( m == 4 ) {
      a_stream >> a4 ;

      c4 = b4 = a4 ;
      //if ( !__mtx_gauss_jordan_inverse ( (float_type *)b4.a, n, (float_type *)c4.a ) )
      //if ( !__mtx_gauss_jordan_inverse ( (float_type *)c4.a, n ) )
      //if ( !__mtx_gauss_jordan_inverse_partial_pivot ( (float_type *)c4.a, n, (float_type *)b4.a ) )
      MtxInv(a4,c4) ;
        cout << "matrix is singular" << endl ;

      c_stream << m << " " << n << endl << c4 ;
      cout << a4*c4 << endl ;  // visual test
    } else if ( m == 5 ) {
      a_stream >> a5 ;
      if ( !MtxInv(a5,c5) )
        cout << "matrix is singular" << endl ;
      c_stream << m << " " << n << endl << c5 ;
      cout << a5*c5 << endl ;  // visual test
    } 

    a_stream.close() ;
    c_stream.close() ;
  }
  catch ( char *file_name ) {
    cout << "cannot open '" << file_name << "'" << endl ;
  }
  catch (...) {
    cout << "some error" << endl ;
  }

  return 0 ;
}

