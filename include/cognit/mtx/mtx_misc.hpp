/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/

namespace cognit {




// needed rethink everything below



// checks if matrix is symmetric
// Matrix m simmetric if transpose m == m
// m called skew-simmetric if transpose m == -m
template <typename type, int n>
bool MtxIsSimm ( MtxN<type,n> &m )
{
  int i, j ;

  for ( i = 0 ; i < n - 1 ; i++ )
    for ( j = i + 1 ; j < n ; j++ )
      if ( m.a[i][j] != m.a[j][i] )
        return false ;

  return true ;
}


template <typename type>
bool MtxIsSimm ( Mtx2<type> &m )
{
  return m.a[0][1] == m.a[1][0] ;
}

template <typename type>
bool MtxIsSimm ( const Mtx3<type> &m )
{
  return m.a[0][1]==m.a[1][0] && m.a[0][2]==m.a[2][0] && m.a[1][2]==m.a[2][1] ;
}



template <typename type, int n>
bool MtxIsDiag ( MtxN<type,n> &m )
{
  int i, j ;
  for ( i = 0 ; i < n ; i++ )
    for ( j = i + 1 ; j < n ; j++ )
      if ( !UniZero(m.a[i][j]) || !UniZero(m.a[j][i]) )
        return false ;
  return true ;
}

template <typename type, int n>
bool MtxIsDiag ( Mtx2<type> &m )
{
  return UniZero(m.a[0][1]) && UniZero(m.a[1][0]) ;
}

template <typename type, int n>
bool MtxIsDiag ( Mtx3<type> &m )
{
  return UniZero(m.a[0][1]) && UniZero(m.a[0][2]) && UniZero(m.a[1][2]) && 
         UniZero(m.a[1][0]) && UniZero(m.a[2][0]) && UniZero(m.a[2][1]) ;
}


template <class type, int n>
bool MtxIsZero ( MtxN<type,n> &m )
{
  int i, j ;
  for ( i = 0 ; i < n ; i++ )
    for ( j = 0 ; j < n ; j++ )
      if ( !UniZero(m.a[i][j]) )
        return false ;
  return true ;
}


// exchanges two rows

template <class type, int n>
void MtxXchgRow ( MtxN<type,n> &m, int row1, int row2 )
{
  int j ;
  type tmp ;

  for ( j = 0 ; j < n ; j++ )
    tmp = m.a[row1][j], m.a[row1][j] = m.a[row2][j], m.a[row2][j] = tmp ;
}




// checks if column or row is zero
template <class type, int n>
void MtxZeroRow ( MtxN<type,n> &m, int row )
{
  for ( int j = 0 ; j < n ; j++ )
    if ( !UniZero(m.a[row][j]) )
      return false ;
  return true ;
}


// More general case, checks if on row or column is virojdena
// returns dependend row or -1
template <class type, int n>
bool MtxDependendRow ( MtxN<type,n> &m, int i, int row, type *depk )
{
  AVectorN<type,n> v ;
  int j ;
  type k ;

  // find non zero element in both rows
  for ( j = 0 ; j < n ; j++ )
    if ( !UniZero(m.a[i][j]) && !UniZero(m.a[row][j]) )
      break ;

  // if there is no such element pair - check for all zeroes
  if ( j == n )
    for ( j = 0 ; j < n ; j++ )
      if ( !UniZero(m.a[i][j]) )
        break ;

  // if all zero - the row is dependend
  if ( j == n )
    return true ;

  // calculate coeff
  k = -m.a[row][j]/m.a[i][j] ;

  // change the row
  for ( j = 0 ; j < n ; j++ )
    v.a[j] = m.a[i][j] + k * m.a[row][j] ;

  // check for zero
  for ( j = 0 ; j < n ; j++ )
    if ( !UniZero(v.a[j]) )
      break ;

  if ( j == n ) {
    if ( depk )
      *depk = k ;
    return true ;
  }

  return false ;
}

// through any
template <class type, int n>
bool MtxDependendRow ( MtxN<type,n> &m, int i, int *deprow=0, type *depk=0 )
{
  // for each row
  for ( int row = 0 ; row < n ; row++ ) {
    if ( i == row )
      continue ;

    if ( MtxDependendRow(m,i,row,depk) ) {
      if ( deprow )
        *deprow = row ;
      return true ;
    }
  }

  return false ;  // didn't find dependent row
}


}  // namespace
