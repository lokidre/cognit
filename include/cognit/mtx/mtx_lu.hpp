/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include "mtx_zero.hpp"


namespace cognit {

// LU decomposition


//
// A=L*U
// where L is lower triangular and U is upper triangular
// It is always possible to choose L where all diagonal elements equ 1
//


//
// LU decomposition using Crout's method
//
// remark: &LU can be equal to &A
//
template <typename type>
bool mtx_lu_crout_basic ( const type *a, int n, type *lu )
{
  // this version without pivoting for experiments only
  // so we don't use any pointers for faster access.

  int i, j, k ;
  type sum ;
  type zero = type(0) ;

  for ( i = 0 ; i < n ; i++ ) {  // for all rows
    // calculate all Ls
    for ( j = 0 ; j < i ; j++ ) {  // for columns of L
      sum = zero ;
      for ( k = 0 ; k < j ; k++ )
        sum += lu[i*n+k]*lu[k*n+j] ;

      if ( lu[j*n+j] == zero )
        return false ;  // matrix is not strongly non-singular

      lu[i*n+j] = (a[i*n+j] - sum )/lu[j*n+j] ;
    }

    // calculate all Us
    for ( j = i ; j < n ; j++ ) {
      sum = zero ;
      for ( k = 0 ; k < i ; k++ )
        sum += lu[i*n+k]*lu[k*n+j] ;
      lu[i*n+j] = a[i*n+j] - sum ;
    }
  }

  return true ;
}

//
// LU decomposition, returns matrix LU with permutation array idx
// uses implicit pivoting
// remark: &LU cannot be equal to &A
// 

template <typename type>
bool mtx_lu_crout_partial_pivot_basic ( const type *a, int n, type *lu, int *idx )
{
  // this version without pivoting for experimentation only
  // so we don't use any pointers for faster cycles.

  int i, j, k ;
  type sum, piv, tmp, scale, maxel, pivel ;
  type zero = type(0), one = type(1) ;
  int ipiv, itmp ;
  int *pi ;
  const type *pa ;
  type *pl, *pu, *plu ;

  // initlialize indexes
  for ( i = 0, pi=idx ; i < n ; i++, pi++ )
    *pi = i ;

  for ( j = 0 ; j < n ; j++ ) {  // for all columns of a

    // scale the whole row of A by its largest element
    for ( k = 0, maxel=zero, pa=&a[idx[j]*n+k] ; k < n ; k++, pa++ )
      if ( (tmp=abs(*pa)) > maxel )
        maxel = tmp ;

    if ( maxel == zero )  // the matrix is singular
      return false ;

    // scale factor
    scale = one/maxel ;

    // calculate all u-s above the diagonal
    for ( i = 0, plu=&lu[i*n+j] ; i < j ; i++, plu+=n ) {
      for ( k = 0, sum=zero, pl=&lu[i*n+k], pu=&lu[k*n+j] ; k < i ; k++, pl++, pu+=n )
        sum += *pl**pu*scale ;
      *plu = a[idx[i]*n+j] - sum*maxel ;
    }

    // calculate all l-s below the diagonal (uncluding u_jj)
    // parallel we find the largest element (as pivot)
    piv = zero, ipiv = 0 ;
    for ( i = j, plu=&lu[i*n+j] ; i < n ; i++, plu+=n ) {
      for ( k = 0, sum=zero, pl=&lu[i*n+k], pu=&lu[k*n+j] ; k < j ; k++, pl++, pu+=n )
        sum += *pl**pu*scale ;
      *plu = a[idx[i]*n+j] - sum*maxel ;

      if ( (tmp=scale*abs(*plu)) > piv )
        ipiv = i, piv = tmp ;
    }

    if ( piv == zero )  // matrix is singular
      return false ;

    // now exchange rows
    for ( k = 0, pl=&lu[ipiv*n], pu=&lu[j*n] ; k < n ; k++, pl++, pu++ )
      tmp = *pl, *pl = *pu, *pu = tmp ;

    itmp = idx[ipiv], idx[ipiv]=idx[j], idx[j]=itmp ;

    // now divide all l's below by u_jj
    pivel = one/lu[j*n+j] ;
    for ( i = j+1, plu=&lu[i*n+j] ; i < n ; i++, plu+=n )
      *plu *= pivel ;
  }



  return true ;
}


//
// additional routines
//

// this routine break ups one lu composed matrices into two matrices
// rem: the address of L can be equal to LU
//

template <typename type>
void mtx_lu_breakup_basic ( const type *lu, int n, type *l, type *u )
{
  int i, j ;
  type zero = type(0), one = type(1) ;
  const type *lup ;
  type *lp, *up ;

  lup = lu, lp = l, up = u ;

  for ( i = 0 ; i < n ; i++ ) {  // for all rows
    // lower elements of
    for ( j = 0 ; j < i ; j++, lp++, up++, lup++ ) {
      *lp = *lup ; // optimized of l[i*n+j] = lu[i*n+j] ;
      *up = zero ; // u[i*n+j] = zero ;
    }

    // diagonal elements
    *up++ = *lup++, *lp++ = one ;  //u[i*n+i] = lu[i*n+i], l[i*n+i] = one ;

    // upper elements of l
    for ( j = i+1 ; j < n ; j++, lp++, up++, lup++ ) {
      *lp = zero ;  // l[i*n+j] = zero ;
      *up = *lup ; // u[i*n+j] = lu[i*n+j] ;
    }
  }
}

// 
// Form permutation matrix P from array idx.
// for saving memory permutation matrix P in equation PA=LU more convenient to store
// as an array of integers. 
template <typename matrix_T>
void mtx_lu_permutation_basic ( const int *idx, int n, matrix_T &p )
{
	const int *pi=idx ;
	typename matrix_T::value_type one = 1 ;
  
	p.setup(n,n) ;
	mtx_zero(p.p,n,n) ;
  
	typename matrix_T::iterator p_it=p.begin() ;
  
	for ( int i = 0 ; i < n ; i++, pi++, p_it+=n )
		*(p_it + *pi) = one ;
}


// Calculate determinant of LU matrix
// the matrix cannot have any zero on its diagonal
template <typename type>
type mtx_lu_determinant_basic ( const type *lu, int n, const int *idx )
{
  //
  // The determinant is the LU decomposed matrix is just a product
  // of its diagonal elements.
  //
  // In this version we don't do just multiplication to avoid overflow
  // Instead we will calculate the sum of logarithms
  //
  // We also won't divide all log's by largest
  // and then at the multiply the largest to found sum
  //
  // Since this version is not that much useful, we won't store temporary
  // logarithms in the buffer, so we will go through the diagonal elements twice
  //


  type zero = type(0) ;
  int i ;

  int pcnt = 0, sign = 1 ;  // permutation count
  type sum ;
  type det ;
  const type *plu ;
  const int *pi ;
  const int n1 = n+1 ;

  // find the maximum log
  for ( i = 0, sum=zero, plu=lu, pi=idx ; i < n ; i++, plu+=n1, pi++ ) {
    if ( *pi != i )  // parallel count the permutations
      pcnt++ ;
    // also keep track of sign changing
    if ( *plu < 0 )
      sign = -sign ;
    sum += ln(abs(*plu)) ;
  }

  // now calculate the determinant
  det = exp(sum) ;

  // check the sign (change if permutations count is odd or the sign of prod is neg)
  if ( (pcnt%2) ^ (sign<0) )
    det = -det ;

  return det ;
}



template <class type>
bool mtx_lu ( const Mtx<type> &a, Mtx<type> &lu, int *idx )
{
  if ( a.M != a.N )  // no LU for non-square matrices
    return false ;
  lu.resize(a.M,a.N) ;
  return mtx_lu_crout_partial_pivot_basic ( a.p, a.N, lu.p, idx ) ;
}

template <class type>
bool mtx_lu ( const Mtx2<type> &a, Mtx2<type> &lu, int *idx )
{
  return mtx_lu_crout_partial_pivot_basic ( (type *)a.a, 2, (type *)lu.a, idx ) ;
}

template <class type>
bool mtx_lu ( const Mtx3<type> &a, Mtx3<type> &lu, int *idx )
{
  return mtx_lu_crout_partial_pivot_basic ( (type *)a.a, 3, (type *)lu.a, idx ) ;
}

template <class type>
bool mtx_lu ( const Mtx4<type> &a, Mtx4<type> &lu, int *idx )
{
  return mtx_lu_crout_partial_pivot_basic ( (type *)a.a, 4, (type *)lu.a, idx ) ;
}

template <class type, int n>
bool mtx_lu ( const MtxN<type,n> &a, MtxN<type,n> &lu, int *idx )
{
  return mtx_lu_crout_partial_pivot_basic ( (type *)a.a, n, (type *)lu.a, idx ) ;
}





template <class type>
void mtx_lu_breakup ( Mtx<type> &lu, Mtx<type> &l, Mtx<type> &u )
{
  l.resize(lu.M,lu.N) ;
  u.resize(lu.M,lu.N) ;
  mtx_lu_breakup_basic ( lu.p, lu.N, l.p, u.p ) ;
}

template <class type>
void mtx_lu_breakup ( const Mtx2<type> &lu, Mtx2<type> &l, Mtx2<type> &u )
{
  mtx_lu_breakup_basic ( (type *)lu.a, 2, (type *)l.a, (type *)u.a ) ;
}


template <class type>
void mtx_lu_breakup ( const Mtx3<type> &lu, Mtx3<type> &l, Mtx3<type> &u )
{
  mtx_lu_breakup_basic ( (type *)lu.a, 3, (type *)l.a, (type *)u.a ) ;
}

template <class type>
void mtx_lu_breakup ( const Mtx4<type> &lu, Mtx4<type> &l, Mtx4<type> &u )
{
  mtx_lu_breakup_basic ( (type *)lu.a, 4, (type *)l.a, (type *)u.a ) ;
}


template <class type, int n>
void mtx_lu_breakup ( const MtxN<type,n> &lu, MtxN<type,n> &l, MtxN<type,n> &u )
{
  mtx_lu_breakup_basic ( (type *)lu.a, n, (type *)l.a, (type *)u.a ) ;
}



//
// Generates permutation matrix from indexes
//
template <class real_type>
Mtx<real_type> &mtx_lu_permutation ( const int *idx, const int &n, Mtx<real_type> &p )
{
  mtx_lu_permutation_basic ( idx, n, p ) ;
  return p ;
}

template <class real_type>
Mtx2<real_type> &mtx_lu_permutation ( const int *idx, const int &, Mtx2<real_type> &p )
{
  mtx_lu_permutation_basic ( idx, 2, p ) ;
  return p ;
}

template <class real_type>
Mtx3<real_type> &mtx_lu_permutation ( const int *idx, const int &, Mtx3<real_type> &p )
{
  mtx_lu_permutation_basic ( idx, 3, p ) ;
  return p ;
}


template <class real_type>
Mtx4<real_type> &mtx_lu_permutation ( const int *idx, const int &, Mtx4<real_type> &p )
{
  mtx_lu_permutation_basic ( idx, 4, p ) ;
  return p ;
}


template <class real_type, int n>
MtxN<real_type,n> &mtx_lu_permutation ( const int *idx, const int &, MtxN<real_type,n> &p )
{
  mtx_lu_permutation_basic ( idx, n, p ) ;
  return p ;
}



// calculates the determinant of LU decomposed matrix
template <class type>
type mtx_lu_det ( Mtx<type> &lu, int *idx )
{
  return mtx_lu_determinant_basic ( lu.p, lu.M, idx ) ;
}

template <class type>
type mtx_lu_det ( const Mtx2<type> &lu, int *idx )
{
  return mtx_lu_determinant_basic ( (type *)lu.a, 2, idx ) ;
}

template <class type>
type mtx_lu_det ( const Mtx3<type> &lu, int *idx )
{
  return mtx_lu_determinant_basic ( (type *)lu.a, 3, idx ) ;
}

template <class type>
type mtx_lu_det ( const Mtx4<type> &lu, int *idx )
{
  return mtx_lu_determinant_basic ( (type *)lu.a, 4, idx ) ;
}


template <class type, int n>
type mtx_lu_det ( const MtxN<type,n> &lu, int *idx )
{
  return mtx_lu_determinant_basic ( (type *)lu.a, n, idx ) ;
}


}  // namespace



