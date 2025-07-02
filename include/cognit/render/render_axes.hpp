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


template <class pixel_type>
void render_axes ( pixel_type *image, int width, int height, const pixel_type &val, int xo=0, int yo=0 )
{
    pixel_type *p ;

    if ( xo >= 0 && xo < width ) {
        p = image + xo ;
        for ( int i = 0 ; i < height ; ++i, p += width )
            *p = val ;
    }

    if ( yo >= 0 && yo < height ) {
        p = image + yo*width ;
        for ( int i = 0 ; i < width ; ++i, ++p )
            *p = val ;
    }
}



}
