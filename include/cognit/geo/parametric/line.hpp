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


// x = x1 + cos(alpha) * lambda
// y = y1 + sin(alpha) * lambda
/*
class StreightParamAngle2D : public Parametric2D {
  private :
    double cosa, sina ;  // cos(a) ;

  private :
    double a ;

  public :  // Parameters
    double x, y ;

    void SetAlpha ( double alpha )
    {  a = alpha, cosa = cos(a), sina = sin(a) ;  }

  public :
    virtual double fx ( double l )
    {  return x + cosa * l ;  }
    virtual double fy ( double l )
    {  return y + sina * l ;  }
} ;
*/

class StraightImplicit2D : public Parametric2D {
} ;


/*
class StreightParam2D : public Param2D {
  public :
    tPoint2D<double> a, b ;

  public :
    virtual double fx ( double l ) 
} ;
*/


}  // namespace




