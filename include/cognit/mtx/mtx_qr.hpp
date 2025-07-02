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

//
// QR decomposition using Householder reduction
//


// A is being replaced by R
template <class matrix_T>
bool mtx_qr_householder_basic ( matrix_T &A, matrix_T &Q )
{
  typedef typename matrix_T::value_type value_type ;
  typedef typename matrix_T::iterator iterator_type ;
  
  iterator_type a_ij, a_00, a_01, a_kj, a_k0, a_j, xi, xj, q_00, q_j ;
  
  const int n=A.n(), m=A.m() ;
  int i, j, k ;
  value_type mx, tmp ;
  
  value_type xm, xm2 ;  // |x| |x|^2
  value_type xxj ;  // dot product xi.xj
  
  value_type sigma, tau, alpha, gamma ;  // greek stuff
  
  
  bool sing = false ;
  
  // initialize Q with identity matrix
  mtx_i(n,Q) ;
  

  for ( i=0, a_00=A.begin(), q_00=Q.begin() ; i < n ; i++, a_00+=n+1, q_00+=n+1 ) {

    // find the largest element and scale by it, to avoid overflows  
    for ( j=i, mx=0, a_ij=a_00 ; j < m ; j++, a_ij+=n )
      if ( (tmp=abs(*a_ij)) > mx )
        mx=tmp ;

    if ( mx > 0 ) {
    
      for ( j=i, xm=0, a_ij=a_00 ; j < m ; j++, a_ij+=n )
        //xm += sqr(*a_ij/=mx) ;
        xm+=sqr(*a_ij), mx=1 ;

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
      
      
      // here, the column of A is vector v
      // do the multiplication: Q - w wT Q
      // calculate wT.Q - this gives a vector
      for ( j=i, q_j=q_00 ; j < n ; j++, q_j++ ) {  // for each column of Qi
        for ( k=i, xi=a_00, xj=q_j, gamma=0 ; k < n ; k++, xi+=n, xj+=n )  // for each row of Q
	  gamma += *xi * *xj ;
	  
	gamma /= tau ;
	
	for ( k=i, xi=a_00, xj=q_j ; k<n ; k++, xi+=n, xj+=n )  // for each row
	  *xj -= gamma* *xi ;
      }
      
      
    
      *a_00 = -sigma*xm*mx ;
    
      // zero the column
      for ( j=i+1, a_j=a_00+n ; j<m ; j++, a_j+=n )
        *a_j = 0 ;

    } else {  // matrix is singular
      sing = true ;
    }

  }  // main loop
  
  return sing ;
}


template <class T>
bool mtx_qr ( Mtx<T> &A, Mtx<T> &Q ) {
	return mtx_qr_householder_basic(A,Q) ;
}


//
// note! extra copying
//
template <class T>
bool mtx_qr ( const Mtx<T> &A, Mtx<T> &Q, Mtx<T> &R ) {
	R = A;
	return mtx_qr_householder_basic(R, Q);
}


/*

template <typename type>
void __mtx_qr_householder_square ( type *aa, int n, type *q, type *r )
{
  int i, j, k, l ;
  type zero = type(0), one = type(1), tmp ;
  int tot = n*n ;

  type s ;
  type sigma, tau, ro, ksi, khi, psi, psi_, phi ;

  type *pr ;

  // copy A to R
  if ( aa != r )
    memcpy ( r, aa, n*n*sizeof(type) ) ;

  // Q=I
  __mtx_i ( q, n ) ;


  for ( l = 0 ; l < n ; l++ ) {  // for all columns

    // [1] scale the first column
    // walk through the rest of the rows and find the largest element
    for ( i = l, s = zero, pr = &r[i*n+l] ; i < n ; i++, pr+=n )
      if ( (tmp=m_abs(*pr)) > s )
        s = tmp ;

    // if the scale is zero then the matrix is singular
    if ( s == zero ) {
      // just set the matrix Q
      continue ;
    }

    s = one ;

    for ( k = l+1, pr = &r[k*n+l] ; k < n ; k++, pr+=n )
      *pr /= s ;

    // [2] Calculate xi, sigma, tau (with scaling)
    for ( i = l, ksi=zero, pr=&r[i*n+l] ; i < n ; i++, pr+=n )
      ksi += *pr * *pr ;
    sigma = ksi - m_sqr(r[l*n+l]) ;
    ksi = m_sqrt(ksi) ;
    tau = ksi - r[l*n+l] ;

    // [3] for all rows of Q
    for ( i = 0 ; i < n ; i++ ) {
      // [3.1] calculate psi, psi_, phi
      for ( k = l+1, psi_=zero ; k < n ; k++ )
        psi_ += r[k*n+l]*q[i*n+k] ;
      psi = psi_ + r[l*n+l]*q[i*n+l] ;
      phi = (sigma*q[i*n+l] + (ksi-r[l*n+l])*psi_)/(sigma*ksi) ;
      // [3.2] for all columns of submatrix
      for ( j = l+1 ; j < n ; j++ )
        q[i*n+j] -= r[j*n+l]*phi ;  // [3.2.2]
      // [3.3] first element of the column
      q[i*n+l] = -psi/ksi ;
    }

    // [4] for all columns of submatrix
    for ( j = l+1 ; j < n ; j++ ) {
      // [4.1] calculate ro
      for ( k = l+1, khi=zero ; k < n ; k++ )
        khi += r[k*n+l]*r[k*n+j] ;
      ro = ( r[l*n+j]*sigma + khi*tau ) / ( sigma * ksi ) ;
      // [4.2]
      for ( i = l+1 ; i < n ; i++ )
        r[i*n+j] -= r[i*n+l]*ro ;
      // [2.3]
      r[l*n+j] = -(khi+r[l*n+l]*r[l*n+j])/ksi ;
    }
    // [5] form the first element
    r[l*n+l] = -ksi*s ;
    // [6] zero the rest
    for ( i = l+1, pr=&r[i*n+l] ; i < n ; i++, pr+=n )
      *pr = zero ;


  } // cycle for all columns

}


// aa must not be r
template <typename type>
void __mtx_qr_householder_general ( type *aa, int n, int m, 
                                    type *q, int qn, int qm, 
                                    type *r, int rn, int rm )
{
  int i, j, k, l ;
  type zero = type(0), one = type(1), tmp ;
  int tot = n*n ;

  type s ;
  type sigma, tau, ro, ksi, khi, psi, psi_, phi ;

  type *pr ;

  // calculate the dimensions of q and r

  // copy A to R
  //for ( i = 0 ; i < 
  if ( aa != r )
    memcpy ( r, aa, n*n*sizeof(type) ) ;

  // Q=I
  __mtx_i ( q, n ) ;


  for ( l = 0 ; l < n ; l++ ) {  // for all columns

    // [1] scale the first column
    // walk through the rest of the rows and find the largest element
    for ( i = l, s = zero, pr = &r[i*n+l] ; i < n ; i++, pr+=n )
      if ( (tmp=m_abs(*pr)) > s )
        s = tmp ;

    // if the scale is zero then the matrix is singular
    if ( s == zero ) {
      // just set the matrix Q
      continue ;
    }

    s = one ;

    for ( k = l+1, pr = &r[k*n+l] ; k < n ; k++, pr+=n )
      *pr /= s ;

    // [2] Calculate xi, sigma, tau (with scaling)
    for ( i = l, ksi=zero, pr=&r[i*n+l] ; i < n ; i++, pr+=n )
      ksi += *pr * *pr ;
    sigma = ksi - m_sqr(r[l*n+l]) ;
    ksi = m_sqrt(ksi) ;
    tau = ksi - r[l*n+l] ;

    // [3] for all rows of Q
    for ( i = 0 ; i < n ; i++ ) {
      // [3.1] calculate psi, psi_, phi
      for ( k = l+1, psi_=zero ; k < n ; k++ )
        psi_ += r[k*n+l]*q[i*n+k] ;
      psi = psi_ + r[l*n+l]*q[i*n+l] ;
      phi = (sigma*q[i*n+l] + (ksi-r[l*n+l])*psi_)/(sigma*ksi) ;
      // [3.2] for all columns of submatrix
      for ( j = l+1 ; j < n ; j++ )
        q[i*n+j] -= r[j*n+l]*phi ;  // [3.2.2]
      // [3.3] first element of the column
      q[i*n+l] = -psi/ksi ;
    }

    // [4] for all columns of submatrix
    for ( j = l+1 ; j < n ; j++ ) {
      // [4.1] calculate ro
      for ( k = l+1, khi=zero ; k < n ; k++ )
        khi += r[k*n+l]*r[k*n+j] ;
      ro = ( r[l*n+j]*sigma + khi*tau ) / ( sigma * ksi ) ;
      // [4.2]
      for ( i = l+1 ; i < n ; i++ )
        r[i*n+j] -= r[i*n+l]*ro ;
      // [2.3]
      r[l*n+j] = -(khi+r[l*n+l]*r[l*n+j])/ksi ;
    }
    // [5] form the first element
    r[l*n+l] = -ksi*s ;
    // [6] zero the rest
    for ( i = l+1, pr=&r[i*n+l] ; i < n ; i++, pr+=n )
      *pr = zero ;


  } // cycle for all columns

}



template <typename type>
inline
void MtxQR ( Mtx2<type> &a, Mtx2<type> &q, Mtx2<type> &r )
{
  __mtx_qr_householder_square ( (type *)a.a, 2, (type *)q.a, (type *)r.a ) ;
}


template <typename type>
inline
void MtxQR ( Mtx3<type> &a, Mtx3<type> &q, Mtx3<type> &r )
{
  __mtx_qr_householder_square ( (type *)a.a, 3, (type *)q.a, (type *)r.a ) ;
}

template <typename type>
inline
void MtxQR ( Mtx4<type> &a, Mtx4<type> &q, Mtx4<type> &r )
{
  __mtx_qr_householder_square ( (type *)a.a, 4, (type *)q.a, (type *)r.a ) ;
}

template <typename type, int n>
inline
void MtxQR ( MtxN<type,n> &a, MtxN<type,n> &q, MtxN<type,n> &r )
{
  __mtx_qr_householder_square ( (type *)a.a, n, (type *)q.a, (type *)r.a ) ;
}


template <typename type>
inline
void MtxQR ( Mtx<type> &a, Mtx<type> &q, Mtx<type> &r )
{
  // check if the matrix is square
  if ( a.m == a.n ) {
    q.setup(a.m,a.n) ;
    r.setup(a.m,a.n) ;
    __mtx_qr_householder_square ( a.p, a.m, q.p, r.p ) ;
  } else {  // if it is rectangular
    if ( a.m<a.n )
      q.setup(a.m,a.n), r.setup(a.m,a.m) ;
    else
      q.setup(a.n,a.n), r.setup(a.n,a.m) ;
    //__mtx_qr_householder_general ( a.p, a.m, a.n, q.p, q.m, q.n, r.p, r.m, r.n ) ;
  }
}

*/

}  // namespace

