/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

/*
	Routines to support ImageMagick packages

*/

#pragma once

#include <Magick++.h>

#include <apeal/buffer.cxx>


namespace cognit {


// maximum pixel value
inline
int magick_max_pixel()
{
	return (int)Magick::Quantum(-1) ;
}


template <class data_type>
inline
void image_export ( const data_type *data, const int width, const int height, Magick::Image &image )
{
	using namespace Magick ;

	image.size(Geometry(width,height)) ;
	image.type(TrueColorType) ;
	image.backgroundColor(ColorRGB(0,0,0)) ;
	image.depth(8) ;
	image.modifyImage() ;
	const data_type *d = data ;

/*	
	// normalize the data
	data_type min(*data), max(*data) ;
	const int total = width * height ;
	for ( int i = 0 ; i < total ; ++i, ++d ) {
		if ( *d > max )
			max = *d ;
		if ( *d < min )
			min = *d ;
	}
	
	const MagickLib::Quantum range = MagickLib::Quantum(-1) ;
	const MagickLib::Quantum denom = MagickLib::Quantum(max - min) ;

*/
	
	PixelPacket *pixs = image.getPixels(0,0,width,height) ;
	
	PixelPacket *p = pixs ;
	
	//if ( denom == 0 ) {
	//	for ( int i = 0 ; i < total ; ++i, ++p )
	//		p->red = p->green = p->blue = 0 ;
	//} else {
	
		d = data ;
	
		for ( int j = 0 ; j < height ; ++j )
			for ( int i = 0 ; i < width ; ++i, ++p, ++d )
				p->red = p->green = p->blue = Quantum(*d) ; // MagickLib::Quantum(( *d - min ) * range / denom) ;
	//}

	//image.flip() ;

	image.syncPixels() ;
}

template <class T>
inline
void image_export ( const T *r_data, const T *g_data, const T *b_data, const int width, const int height, Magick::Image &image )
{
	using namespace Magick ;

	image.size(Geometry(width,height)) ;
	image.type(TrueColorType) ;
	image.backgroundColor(ColorRGB(0,0,0)) ;
	image.depth(8) ;
	image.modifyImage() ;

	const T *r = r_data, *g = g_data, *b = b_data ;

	
	PixelPacket *pixs = image.getPixels(0,0,width,height) ;
	
	PixelPacket *p = pixs ;
	
	for ( int j = 0 ; j < height ; ++j )
		for ( int i = 0 ; i < width ; ++i, ++p, ++r, ++g, ++b )
			p->red = Quantum(*r), p->green = Quantum(*g), p->blue = Quantum(*b) ;
	
	//image.flip() ;

	image.syncPixels() ;
}



template <class T>
inline
void magick_save ( const T *data, const int width, const int height, const std::string &filename )
{
	Magick::Image image ;
	image_export(data,width,height,image) ;
	image.write(filename) ;
}


template <class T>
inline
void magick_save ( const T *r, const T *g, const T *b, const int width, const int height, const std::string &filename )
{
	Magick::Image image ;
	image_export(r,g,b,width,height,image) ;
	image.write(filename) ;
}



inline 
void image_dimensions ( Magick::Image &image, int &width, int &height, int &channels, int &range )
{
}


template <class data_type>
void magick_load ( const std::string &filename, apl::ABuffer<data_type> &data, int &width, int &height )
{
	using namespace Magick ;
	
	Image image ;
	
	image.read(filename) ;
	Geometry size = image.size() ;
	width = size.width() ;
	height = size.height() ;
	
	const int total = width * height ;
	
	image.type(GrayscaleType) ;
	image.type(TrueColorType) ;

	//image.flip() ;

	image.modifyImage() ;

	PixelPacket *pixels = image.getPixels(0,0,width,height) ;
	
	data.resize(total) ;
	
	PixelPacket *p = pixels ;
	data_type *d = data.get() ;
	
	for ( int i = 0 ; i < total ; ++i, ++p, ++d ) {
		*d = data_type((unsigned long)(p->red)) ;
	}
}


#ifdef _MSC_VER
#pragma comment(lib, "ws2_32.lib")

#ifdef _DEBUG
#pragma comment ( lib, "CORE_DB_Magick++_.lib" )
#pragma comment ( lib, "CORE_DB_bzlib_.lib" )
#pragma comment ( lib, "CORE_DB_coders_.lib" )
#pragma comment ( lib, "CORE_DB_filters_.lib" )
#pragma comment ( lib, "CORE_DB_jbig_.lib" )
#pragma comment ( lib, "CORE_DB_jp2_.lib" )
#pragma comment ( lib, "CORE_DB_jpeg_.lib" )
#pragma comment ( lib, "CORE_DB_lcms_.lib" )
#pragma comment ( lib, "CORE_DB_libxml_.lib" )
#pragma comment ( lib, "CORE_DB_magick_.lib" )
#pragma comment ( lib, "CORE_DB_png_.lib" )
#pragma comment ( lib, "CORE_DB_tiff_.lib" )
#pragma comment ( lib, "CORE_DB_ttf_.lib" )
#pragma comment ( lib, "CORE_DB_wand_.lib" )
#pragma comment ( lib, "CORE_DB_wmf_.lib" )
#pragma comment ( lib, "CORE_DB_xlib_.lib" )
#pragma comment ( lib, "CORE_DB_zlib_.lib" )
#pragma comment ( lib, "X11.lib" )
#pragma comment ( lib, "Xext.lib" )
#else
#pragma comment ( lib, "CORE_RL_Magick++_.lib" )
#pragma comment ( lib, "CORE_RL_bzlib_.lib" )
#pragma comment ( lib, "CORE_RL_coders_.lib" )
#pragma comment ( lib, "CORE_RL_filters_.lib" )
#pragma comment ( lib, "CORE_RL_jbig_.lib" )
#pragma comment ( lib, "CORE_RL_jp2_.lib" )
#pragma comment ( lib, "CORE_RL_jpeg_.lib" )
#pragma comment ( lib, "CORE_RL_lcms_.lib" )
#pragma comment ( lib, "CORE_RL_libxml_.lib" )
#pragma comment ( lib, "CORE_RL_magick_.lib" )
#pragma comment ( lib, "CORE_RL_png_.lib" )
#pragma comment ( lib, "CORE_RL_tiff_.lib" )
#pragma comment ( lib, "CORE_RL_ttf_.lib" )
#pragma comment ( lib, "CORE_RL_wand_.lib" )
#pragma comment ( lib, "CORE_RL_wmf_.lib" )
#pragma comment ( lib, "CORE_RL_xlib_.lib" )
#pragma comment ( lib, "CORE_RL_zlib_.lib" )
#endif

#endif // MSC



}  // namespace


