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

class Cartesian {
    /*
      private :
        tVid *Vid ;

        tPoint GetPixelCoord ( double x, double y, double z ) ;

      public :
        dword Color ;

      public :

        int Dimension ;   // 2 - 2D, 3 - 3D
        //int Style ;
        double XAxisAngle, YAxisAngle, ZAxisAngle ;
        int w, h, d ;  // size of cartesian coordinate
        int x, y, z ;  // origin of coord table base (0,0,0) point

        tCartesian ( void )
        {
          Dimension = 2 ;
          XAxisAngle = PI / 12 ;
          YAxisAngle = PI / 6 ;
          ZAxisAngle = PI / 2 ;

          Color = 0 ;
        }

        bool AttachVid ( tVid *iVid )
        {
          Vid = iVid ;
          return true ;
        }

        void Draw ( void ) ;
        //void DrawPoints ( tPoint2D<double> *Points, int nPoints ) ;


        //void DrawFunction ( tFunction2D<double> *F ) ;
        //void DrawFunction ( tFunction3D<double> *F ) ;

        //void DrawParametric ( tParametric2D *P ) ;
        //void DrawParam ( tParametric3D *P ) ;
        */
} ;




// Coordinate transforms

// coordinate transform
// &v != &x
template <class type>
Vec3<type> &coord_transform(const MtxN<type, 4> &m, const Vec3<type> &v, Vec3<type> &r)
{
    r.x = m.a[0][0] * v.x + m.a[0][1] * v.y + m.a[0][2] * v.z + m.a[0][3];
    r.y = m.a[1][0] * v.x + m.a[1][1] * v.y + m.a[1][2] * v.z + m.a[1][3];
    r.z = m.a[2][0] * v.x + m.a[2][1] * v.y + m.a[2][2] * v.z + m.a[2][3];

    return r;
}

template <class T>
void gen_transform_mtx(Vec3<T> &p, Vec3<T> &q, Vec3<T> &r, APoint3D<T> &o, MtxN<T, 4> &m)
{
    m.a[0][0] = p.x, m.a[0][1] = p.y, m.a[0][2] = p.z, m.a[0][3] = o.x;
    m.a[1][0] = q.x, m.a[1][1] = q.y, m.a[1][2] = q.z, m.a[1][3] = o.y;
    m.a[2][0] = r.x, m.a[2][1] = r.y, m.a[2][2] = r.z, m.a[2][3] = o.z;
    m.a[3][0] = 0, m.a[3][1] = 0, m.a[3][2] = 0, m.a[3][3] = 1;
}

// r - radius, a - alpha
template <class type>
void CoordRotateRY(APoint3D<type> X0, type r, type a, APoint3D<type> &X)
{
    type h = (type)(r * sqrt(2 - 2 * cos(a)));

    Vec3<type> s;
    s.x = (type)(h * cos(a / 2));
    s.y = 0;
    s.z = (type)(h * sin(a / 2));

    CoordRotateY(X0, a, X);

    if (s.z < 0)
        s.x = -s.x, s.z = -s.z;

    X.x += s.x, X.z += s.z;
}

// sin(cos)a = sin(cos)(a)
// sx = r*sqrt(2-2*cos(a))*cos(a/2)
// sz = r*sqrt(2-2*cos(a))*sin(a/2)
template <class type>
void CoordRotateSinRY(APoint3D<type> X0, type r, type sina, type cosa, type sx, type sz, APoint3D<type> &X)
{
    CoordRotateSinY(X0, sina, cosa, X);

    if (sz < 0)
        sx = -sx, sz = -sz;

    X.x += sx, X.z += sz;
}

}  // namespace

