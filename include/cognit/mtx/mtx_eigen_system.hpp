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


template <class T>
void eigen_system(const Mtx2<T>& a, Vec2<Complex<T> >& e, Mtx2<Complex<T> >& v)
{
    eigen_values(a, e);
    eigen_vectors(a, e, v);
}




// calculation of eigen vectors

template <class T>
void eigen_system(Mtx3<T>& a, Vec3<Complex<T> >& e, Mtx3<Complex<T> >& v)
{
    int il, i, j;
    Mtx3<Complex<T> > t;
    Vec3<Complex<T> > r, x;


    for (il = 0; il < 3; il++) {
        // prepare the matrix
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++)
                //t.a[i][j].a = a.a[i][j], t.a[i][j].b = (type)0 ;
                t.a[i][j] = a.a[i][j];

            t.a[i][i] = t.a[i][i] - e.a[il];
            r.a[i] = 0;
            x.a[i] = 0;
        }


        // --- find the roots
        {
            // --- find one coordinate
            {
                // find the independent row
                for (i = 0; i < 3; i++) {
                    if (!MtxDependendRow(t, i))
                        break;
                }

                // if all other rows are zero, we have to choose one
                // others are zeroes
                if (i == 3)
                    x.a[il] = 1;
                else {
                    // find dependent row
                    for (i = 0; i < 3; i++) {
                        if (MtxDependendRow(t, i))
                            break;
                    }

                    // if the dependent is not found
                    // then the row can be expressed through other two
                    if (i == 3)
                        i = 2;

                    {
                        x.a[i] = 1;

                        { // go to the one less degree and calculate
                            MtxN<complextype, 2> t2;
                            AVectorN<complextype, 2> r2, x2;

                            // find minor
                            MtxMinor(t, i, i, t2);

                            r2.a[0] = -t.a[i<1 ? 1 : 0][i];
                            r2.a[1] = -t.a[i<2 ? 2 : 1][i];

                            SysEquLinearSolveGauss(t2, r2, x2);

                            x.a[i<1 ? 1 : 0] = x2.a[0];
                            x.a[i<2 ? 2 : 1] = x2.a[1];
                        }
                    }
                }
            }
        }
        // store roots
        for (i = 0; i < 3; i++)
            v.a[il][i] = x.a[i];
    }
}




}

