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


// Multipliplication of matrix by constant (scaling)
// x = cm


template <class a_matrix_T, class scale_T, class x_matrix_T>
x_matrix_T &mtx_scale_basic ( const a_matrix_T &A, const scale_T &c, x_matrix_T &X )
{
  X.setup(A.N(),A.N()) ;
  typename x_matrix_T::iterator x = X.begin() ;
  for ( typename a_matrix_T::const_iterator a = A.begin(), a_end = A.end() ; a != a_end ; a++, x++ )
    *x = *a * c ;

  return X ;
}

template <class matrix_T, class scale_T>
matrix_T &mtx_scale_basic ( matrix_T &A, const scale_T &c )
{
  for ( typename matrix_T::iterator a = A.begin(), a_end = A.end() ; a != a_end ; a++ )
    *a *= c ;
  return A ;
}



template <typename type>
Mtx<type> mtx_scale ( const Mtx<type> &a, const type &c, Mtx<type> &x )
{
  return mtx_scale_basic(a,c,x) ;
}


template <typename type>
Mtx<type> &mtx_scale ( Mtx<type> &a, const type &c )
{
  return mtx_scale_basic(a,c) ;
}




template <typename type>
void mtx_scale ( const Mtx2<type> &m, const type &c, Mtx2<type> &x )
{
  x.a[0][0] = m.a[0][0]*c ;
  x.a[0][1] = m.a[0][1]*c ;
  x.a[1][0] = m.a[1][0]*c ;
  x.a[1][1] = m.a[1][1]*c ;
}

template <typename type>
void mtx_scale ( Mtx2<type> &m, const type &c )
{
  m.a[0][0] *= c ;
  m.a[0][1] *= c ;
  m.a[1][0] *= c ;
  m.a[1][1] *= c ;
}

template <typename type>
void mtx_scale ( const Mtx3<type> &m, const type &c, Mtx3<type> &x )
{
  x.a[0][0] = m.a[0][0]*c ;
  x.a[0][1] = m.a[0][1]*c ;
  x.a[0][2] = m.a[0][2]*c ;
  x.a[1][0] = m.a[1][0]*c ;
  x.a[1][1] = m.a[1][1]*c ;
  x.a[1][2] = m.a[1][2]*c ;
  x.a[2][0] = m.a[2][0]*c ;
  x.a[2][1] = m.a[2][1]*c ;
  x.a[2][2] = m.a[2][2]*c ;
}


template <typename type>
void mtx_scale ( Mtx3<type> &m, const type &c )
{
  m.a[0][0] *= c ;
  m.a[0][1] *= c ;
  m.a[0][2] *= c ;
  m.a[1][0] *= c ;
  m.a[1][1] *= c ;
  m.a[1][2] *= c ;
  m.a[2][0] *= c ;
  m.a[2][1] *= c ;
  m.a[2][2] *= c ;
}

template <typename type, int n>
MtxN<type,n> &mtx_scale ( MtxN<type,n> &m, type c, MtxN<type,n> &x )
{
  return mtx_scale_basic(m,c,x) ;
}

template <typename type, int n>
MtxN<type,n> &mtx_scale ( MtxN<type,n> &m, const type &c )
{
  return mtx_scale_basic(m,c) ;
}



}  // namespace

