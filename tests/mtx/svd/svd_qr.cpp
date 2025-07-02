/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
// Find SVD using QR algorithm
// svd_qr [<a file>] [<b file>]


#include <mat/mat.h>
#include <mat/matrix/mio.h>
#include <mat/matrix/convert.cxx>

#include <iostream>
#include <fstream>

using namespace std ;

typedef double float_type ;



int m, n ;  // dimensions

AMatrix<float_type>        a, aT, c, b, bT, h, hT, t ;


char a_file_name[256], u_file_name[256], s_file_name[256], v_file_name[256] ;


int main ( int argc, char *argv[] )
{                 
  strcpy ( a_file_name, argc > 1 ? argv[1] : "dat/svd6x7_a" ) ;
  strcpy ( u_file_name, argc > 2 ? argv[2] : "dat/svd6x7_u" ) ;
  strcpy ( s_file_name, argc > 3 ? argv[3] : "dat/svd6x7_s" ) ;
  strcpy ( v_file_name, argc > 4 ? argv[4] : "dat/svd6x7_v" ) ;

  
  fstream a_stream, u_stream, s_stream, v_stream ;

  try {
    a_stream.open ( a_file_name, ios::in ) ;

    u_stream.open ( u_file_name, ios::out ) ;
    s_stream.open ( s_file_name, ios::out ) ;
    v_stream.open ( v_file_name, ios::out ) ;

    if ( !a_stream.good()  )
      throw a_file_name ;


    a_stream >> m >> n ;


    a.setup(m,n) ;
    a_stream >> a ;

    mtx_t(a,aT) ;
    mtx_mul(aT,a,c) ;

    /*
    b.copy(a) ;
    bT.setup(b.n,b.m) ;
    t.setup(m,n) ;
    h.setup(n,n) ;
    hT.setup(m,m) ;

    // do for all columns of the original matrix
    {
      int j = 0 ;
      for ( ; j < n-1 ; j++ ) {
        __mtx_householder ( b.p, b.m, b.n, h.p, n, j, j ) ;        // H - Householder matrix

        mtx_mul(h,b,t) ;                                          // A=HA

        b = t ;


        if ( j < m-2 ) {
          mtx_t(b,bT) ;
        
          __mtx_householder ( bT.p, bT.m, bT.n, hT.p, hT.n, j+1, j ) ;

          mtx_mul(b,hT,t) ;

          b = t ;
        } 
        
      }
    }
    */


    //cout << h.m << " " << h.n << endl << h << endl ;
    //b_stream << b.m << " " << b.n << endl << MtxCleanup(b) ;

    cout << MtxCleanup(b) << endl ;


    a_stream.close(), u_stream.close(), s_stream.close(), v_stream.close() ;
  }

  
  catch ( char *file_name ) {
    cout << "cannot open '" << file_name << "'" << endl ;
  }
  catch (...) {
    cout << "some error" << endl ;
  }
  

  return 0 ;
}

