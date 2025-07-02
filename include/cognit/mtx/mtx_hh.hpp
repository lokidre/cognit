/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

//#include "iterator.hpp"


/*

    Householder bidiagonalization

        A = U B V^T


    where

    A is mxn matrix
    B is upper bidiagonal matrix
    U and V are orthogonal matrices



*/


namespace cognit {


//
// Householder transform
//
// replaces v with Householder vector
// returns coefficient tau
//
// reference: Golub Algorithm 5.1.1
template <class iterator, class T>
T householder_transform(const iterator V, int n)
{
    int i;

    T sigma(0), tau(0);

    // sigma = x(2:n)^T x(2:n)
    // needed - scale v/max(v) to avoid overflow
    iterator v = V;
    T v0 = *v;
    for (++v, i = 1; i < n; ++i, ++v)
        sigma += *v * *v;

    v = V;
    *v = 1;

    if (sigma == 0)
        return tau;

    T myu = sqrt(v0*v0+sigma);
    if (v0 <= 0)
        *v = x0 - myu;
    else
        *v = -sigma/(x0+myu);

    T v0 = *v;
    T v2 = v0 * v0;
    tau = 2 * v2 / (sigma + v2);

    // v/v0
    for (i = 0; i < n; ++i, ++v)
        *v /= v0;

    return tau;
}



//
// Householder bidiagonalization
//
// the algorithm overwrites the matrix A with 
// m >= n 
// tau_U.size == n
// tau_V.size == n-1
template <class iterator, class T>
void householder_bidiag(const iterator a, int m, int n, T* tau_U, T* tau_V)
{
    int i, j, k;
    T tau;

    for (k = 0; k < n; ++k) {
        // apply householder tranform to current column
        // house(A(j:m,j))
        mtx_column_iterator v(a+k, n);
        tau = householder_transform<mtx_column_iterator, T>(v, m-k);

        // apply transformation to remaining columns
        // A(j:m,j:n) = (I_{m-j+1} - tau v v^T) A(j:m,j:n)
        if (k < n - 1) {
            for (i = k; i < n; ++i) {
                w = *(a + (k+1)*n + i);
                for (j = k + 1; j < m; ++j)
                    w += *(a+j*n+i) * *(v+j);

                *(a+(k+1)*n+j) -= tau * w;  // v_i = 1

                for (j = k + 1; j < m; ++j)
                    *(a+j*n+i) -= tau * w * v[j];
            }

        }

        tau_U[k] = tau;

        // apply Householder transformation to current row
        if (k < n -1) {
            iterator r = A + k*n;	// i-th row
            iterator v = r + k;
            tau = householder_transform<iterator, T>(v, n-j-1);

            // apply Householder transformation to remaining rows
            for (j = k + 1; j < m; ++j) {
                w = *(a + (j+1)*n + k+1);
                for (i = k + 1; i < n; ++i)
                    w += *(a+j*n+i) * *(v+i);

                *(a+(k+1)*n+j) -= tau * w;

                for (i = k + 1; i < n; ++i)
                    *(a+j*n+i) -= tau * w *v[i];
            }

            tau_V[k] = tau;
        }
    }
}


/* obsolete
template <class matrix_T>
matrix_T &mtx_householder_bidiag_basic ( matrix_T &A )
{
  typedef typename matrix_T::value_type value_type ;

  typename matrix_T::iterator a_ij, a_00, a_01, a_kj, a_k0, a_j, xi, xj ;

  const int n=A.n(), m=A.m() ;

  int i, j, k ;
  value_type mx, tmp ;

  value_type xm, xm2 ;  // |x| |x|^2
  value_type xxj ;  // dot product xi.xj

  value_type sigma, tau, alpha, gamma ;  // greek stuff


  for ( i=0, a_00=A.begin() ; i < n ; i++, a_00+=n+1 ) {

    // find the largest element and scale by it, to avoid overflows
    for ( j=i, mx=0, a_ij=a_00 ; j < m ; j++, a_ij+=n )
      if ( (tmp=abs(*a_ij)) > mx )
        mx=tmp ;

    if ( mx > 0 ) {

      // find |x| and scale the first column
      for ( j=i, xm=0, a_ij=a_00 ; j < m ; j++, a_ij+=n )
        xm += sqr(*a_ij/=mx) ;

      xm = sqrt(xm) ;

      alpha = *a_00 ;
      sigma = alpha > 0 ? 1 : -1 ;
      *a_00 += sigma*xm, tau = xm* *a_00 ;

      // for each column, starting from the second
      for ( j=i+1, a_j=a_00+1 ; j<n ; j++, a_j++ ) {

        // calculate gamma = (x.xj +- |x| a_0j)/tau
        for ( k=i+1, xi=a_00+n, xj=a_j+n, gamma=alpha* *a_j ; k<m ; k++, xi+=n, xj+=n )
          gamma += *xi * *xj ;

        gamma += sigma * xm * *a_j, gamma /= tau ;

        for ( k=i, a_k0=a_00, a_kj=a_j ; k<m ; k++, a_kj+=n, a_k0+=n )
          *a_kj -= sigma*gamma* *a_k0 ;
      }

      *a_00 = -sigma*xm*mx ;

      // zero the column
      for ( j=i+1, a_j=a_00+n ; j<m ; j++, a_j+=n )
        *a_j = 0 ;
    }  // if max(x)>0


    //
    // Now we do exactly the same with right side of the matrix
    // this is just reflection of the code above
    //
    if ( i < m - 2 ) {
      a_01=a_00+1 ;
      for ( j=i+1, mx=0, a_ij=a_01 ; j<n ; j++, a_ij++ )
        if ( (tmp=abs(*a_ij)) > mx )
          mx=tmp ;
      if ( mx > 0 ) {
        for ( j=i+1, xm=0, a_ij=a_01 ; j<n ; j++, a_ij++ )
          xm += sqr(*a_ij/=mx) ;
        xm = sqrt(xm) ;
        alpha = *a_01 ;
        sigma = alpha > 0 ? 1 : -1 ;
        *a_01 += sigma*xm, tau = xm* *a_01 ;

        for ( j=i+1, a_j=a_01+n ; j<m ; j++, a_j+=n ) { // for each row, starting from the second
          for ( k=i+2, xi=a_01+1, xj=a_j+1, gamma=alpha* *a_j ; k<n ; k++, xi++, xj++ )
            gamma += *xi * *xj ;
          gamma += sigma * xm * *a_j, gamma /= tau ;

          for ( k=i+1, a_k0=a_01, a_kj=a_j ; k<n ; k++, a_kj++, a_k0++ )
            *a_kj -= sigma*gamma* *a_k0 ;
        }

        *a_01 = -sigma*xm*mx ;

        // zero the column
        for ( j=i+2, a_j=a_01+1 ; j<n ; j++, a_j++ )
          *a_j = 0 ;
      }
    }  // horizontal elements
  }

}
*/




}

