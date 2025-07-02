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

// a(x,y), b(x,y) - centers, r - radius

// d - 
// A(x1,y1), B(x2,y2) - 
// X(x,y) - 
// c - 
// l - 

// AX + BX = c
// x - x1 = AX * cos(lambda)
// y - y1 = AX * sin(lambda)
// BX^2 = AX^2 + d^2 - 2AX*d*cos(alpha)

// 
// cos(lambda-alpha) = (x2-x1)/d
// sin(lambda-alpha) = (y2-y1)/d
// cos(alpha) = (x2-x1)/d*cos(lambda) + (y2-y1)/d*sin(lambda)


// 
// 
// AX = (c^2-d^2)/(2*(c-d*cos(alpha)))

// x = AX*cos(lambda) + x1
// y = AX*sin(lambda) + y1



/*
class EllipseParam2D : public Parametric2D {

  private :
    double c ;
    double d ;
    double cosla, sinla ;

  private :  // Parameters
    double r ;  // apogey, perigey
    APoint2D<double> f1, f2 ;  // foci

  public :
    void Set ( APoint2D<double> if1, APoint2D<double> if2, double ir ) 
    {
      f1 = if1, f2 = if2 ;
      r = ir ;

      d = sqrt((f2.y-f1.y)*(f2.y-f1.y) + (f2.x-f1.x)*(f2.x-f1.x)) ;
      c = d + 2*r ;

      cosla = (f2.x-f1.x)/d, sinla = (f2.y-f1.y)/d ;
    }

  public :
    virtual double fx ( const double l )
    { 
      double cosa = cosla*cos(l) + sinla*sin(l) ;
      double AX = (c*c-d*d)/(2*(c-d*cosa)) ;

      return AX*cos(l) + f1.x ;
    }

    virtual double fy ( const double l )
    {  
      double cosa = cosla*cos(l) + sinla*sin(l) ;
      double AX = (c*c-d*d)/(2*(c-d*cosa)) ;

      return AX*sin(l) + f1.y ;
    }
} ;
*/

}  // namespace

