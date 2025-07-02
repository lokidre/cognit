/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#include "../../common/main.hpp"


#include <iostream>
#include <typeinfo>

#include <cognit/mat/const.cxx>


template <class T>
void const_output()
{
    using namespace std ;
    using namespace cognit ;

    const char *type_name = typeid(T).name() ;

    cout << "   pi<" << type_name << "> = " << const_pi<T>()() << endl ;
    cout << "    e<" << type_name << "> = " << const_e<T>()() << endl ;
    cout << "  inf<" << type_name << "> = " << const_inf<T>()() << endl ;
    cout << "  eps<" << type_name << "> = " << const_eps<T>()() << endl ;
    cout << "sqrt2<" << type_name << "> = " << const_sqrt2<T>()() << endl ;
}


int main()
{
    using namespace std ;
    using namespace cognit ;

    cout.setf(cout.scientific) ;
    cout.precision(40) ;

    const_output<double>() ;
    cout << endl ;
    const_output<float>() ;
    cout << endl ;
    const_output<long double>() ;


    return 0 ;
}

#include "../../common/main.cpp"

