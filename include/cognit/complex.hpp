/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#if 0

Complex Numbers


Suppose p and q are complex numbers: p = a + ib, q = c + id


(a+ib)/(c+id) = (ac+bd)/(c^2+d^2) + i(bc-ad)/(c^2+d^2)

p + q = (a+c) + i(b+d)


e^p = e^a ( cos(b) + i sin(b) )


#endif



#include "func.hpp"


// The definition of operations on complex numbers

namespace cognit {

template <class T>
struct Complex {
    typedef T value_type;

    // Real and imaginary parts
    T a, b;


    /*
  int operator == ( const AComplex<type> &c )
  {
    return a == c.a && b == c.b ;
  }

  AComplex<type> operator + ( const AComplex<type> &c )
  {
    return AComplex<type> ( a + c.a, b + c.b ) ;
  }

  AComplex<type> operator - ( const AComplex<type> &c )
  {
    return AComplex<type> ( a - c.a, b - c.b ) ;
  }

  AComplex<type> operator - ( void )
  {
    AComplex<type> r ( a, b ) ;
    r.a = -r.a, r.b = -r.b ;
    return r ;
  }


  AComplex<type> operator * ( AComplex<type> &c )
  {
    return AComplex<type> ( a*c.a - b*c.b, a*c.b + b*c.a ) ;
  }

  AComplex<type> operator / ( AComplex<type> &c )
  {
    type den = a*c.a+b*c.b ;
    return AComplex<type> ( (a*c.a+b*c.b)/den, (b*c.a-a*c.b)/den ) ;
  }

  void operator += ( AComplex<type> &c )  {   a += c.a, b += c.b ;  }
  void operator -= ( AComplex<type> &c )  {   a -= c.a, b -= c.b ;  }
  void operator *= ( AComplex<type> &q )
  {
    AComplex<type> p ( a, b ) ;
    a = p.a*q.a - p.b*q.b, b = p.a*q.b + p.b*q.a ;
  }
  void operator /= ( AComplex<type> &q )
  {
    AComplex<type> p ( a, b ) ;
    type den = q.a*q.a+q.b*q.b ;
    a = (p.a*q.a+p.b*q.b)/den, b = (p.b*q.a-p.a*q.b)/den ;
  }
  */
};


// Function Argument
template <class T>
using ComplexA = const Complex<T>&;



// two complex numbers are equal iff their real & imaginary parts are equal
template <class T>
bool cpx_equ(ComplexA<T> p, ComplexA<T> q) noexcept
{
    return p.a == q.a && p.b == q.b;
}


template <class T>
Complex<T> cpx_add(ComplexA<T> p, ComplexA<T> q) noexcept
{
    return {p.a + q.a, p.b + q.b};
}

template <class T>
Complex<T> cpx_sub(ComplexA<T> p, ComplexA<T> q) noexcept
{
    return {p.a - q.a, p.b - q.b};
}


// (a+ib) * (c+id) = (ac-bd) + i(ad+bc)
template <class T>
Complex<T>& cpx_mul(const Complex<T>& p, const Complex<T>& q, Complex<T>& r)
{
    r.a = p.a * q.a - p.b * q.b;
    r.b = p.a * q.b + p.b * q.a;
    return r;
}

template <class T>
Complex<T>& cpx_mul(const Complex<T>& p, T q, Complex<T>& r)
{
    r.a = p.a * q, r.b = p.b * q;
    return r;
}



//
// Division by Complex Number
//
template <class T>
Complex<T> cpx_div(ComplexA<T> p, ComplexA<T>& q) noexcept
{
    auto d = q.a * q.a + q.b * q.b;
    return {(p.a * q.a + p.b * q.b) / d, (p.b * q.a - p.a * q.b) / d};
}



//
// Division by Real Number
//
template <class T>
Complex<T> cpx_div(ComplexA<T> p, T q) noexcept
{
    return {p.a / q, p.b / q};
}

//template <class T>
//Complex<T>& cpx_div(Complex<T>& p, T q)
//{
//    p.a /= q, p.b /= q;
//    return p;
//}



// norm of complex number
template <class T>
T cpx_norm(ComplexA<T> p) noexcept
{
    return std::hypot(p.a, p.b);
}



template <class T>
Complex<T>& cpx_exp(const Complex<T>& p, Complex<T>& q)
{
    auto ea = std::exp(p.a);

    q.a = ea * std::cos(p.b);
    q.b = ea * std::sin(p.b);

    return q;
}


// wrapper similar to standard exp() function
// Note: Extra compying of Complex class
template <class T>
Complex<T> exp(const Complex<T>& x)
{
    Complex<T> y;
    cpx_exp(x, y);
    return y;
}


//
// Raising to complex power
//
// needed
/*
// Real number into complex power
template <class T>
inline
AComplex<T> &cpx_pow ( const T &p, AComplex<T> &q )
{
    cpx_exp(`
}
*/

// Complex number into real power

// Complex number into complex power



//// absolute value of complex number
//template <class T>
//T cabs(const Complex<T>& p)
//{
//    return hypot(p.a, p.b);
//}
//



//
// Note: extra copying of class Complex<T>
//
template <class T>
Complex<T> operator*(const Complex<T>& p, const Complex<T>& q)
{
    return cpx_mul(p, q);
}

template <class T>
Complex<T> operator*(const Complex<T>& p, T q)
{
    return cpx_mul(p, q);
}



template <class T>
Complex<T>& operator+=(Complex<T>& p, const Complex<T>& q)
{
    return cpx_add(p, q);
}


template <class T>
Complex<T>& operator/=(Complex<T>& p, T q)
{
    return cpx_div(p, q);
}



template <class T>
int operator==(const Complex<T>& p, const Complex<T>& q)
{
    return cpx_equ(p, q);
}

template <class T>
int operator!=(const Complex<T>& p, const Complex<T>& q)
{
    return !cpx_equ(p, q);
}


//
// relational operators
//
template <class T>
int operator>(const Complex<T>& p, const Complex<T>& q)
{
    return cpx_norm(p) > cpx_norm(q);
}

template <class T>
int operator>=(const Complex<T>& p, const Complex<T>& q)
{
    return cpx_norm(p) >= cpx_norm(q);
}


template <class T>
int operator<(const Complex<T>& p, const Complex<T>& q)
{
    return cpx_norm(p) < cpx_norm(q);
}

template <class T>
int operator<=(const Complex<T>& p, const Complex<T>& q)
{
    return cpx_norm(p) <= cpx_norm(q);
}



//
// standard library functions
//

template <class T>
void swap(Complex<T>& p, Complex<T>& q)
{
    using std::swap;

    swap(p.a, q.a);
    swap(p.b, q.b);
}

//template <class T>
//inline const T abs ( const AComplex<T> &x ) {  return abs(x.a) ;  }


}  // namespace cognit
