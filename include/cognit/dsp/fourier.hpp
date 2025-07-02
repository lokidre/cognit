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

/*

  Fourier transform

            oo      2 pi ii f t
     H(f) = S h(t) e           dt
           -oo


  Fourier inverse transform

            oo      -2 pi ii f t
     h(f) = S H(t) e            dt
           -oo



  Discrete Fourier transform

          N-1
          ---     -2 pi ii k n / N
     H  =  >  h  e
      n   ---  k
          k=0


  Inverse Discrete Fourier Transform

              N-1
           1  ---      -2 pi ii k n / N
     h  = ---  >  H  e
      k    N  ---  n
              n=0


  2-D Fourier transform



*/


}  // namespace


