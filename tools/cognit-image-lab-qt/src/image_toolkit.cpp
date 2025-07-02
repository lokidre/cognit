/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#include "image_toolkit.h"

#include "image_widget.h"

#include <cognit/dsp/image_hsv.hpp>
#include <cognit/dsp/image_lab.hpp>

namespace image_lab {

void ImageToolkit::setImage(ImageContainer&& img) 
{
    loadedImage_ = std::move(img);

    imageWidget_->setImageContainer(&loadedImage_);
}

void ImageToolkit::setZoom(int zoom)
{
    imageWidget_->setZoom(zoom);
}


const ImageInfo* ImageToolkit::selectImage(Index index)
{
    auto& image = loadedImage_.images[index];
    auto [width, height] = image.size;

    auto& ii = selectedImageInfo_;

    ii.width = width;
    ii.height = height;

    //selectedImageInfo_.bpr = 
    ii.bpr = width * 4;
    ii.argbData.alloc(height * ii.bpr);
    ii.pixels.alloc(width * height);

    // YCC information
    if (image.cm == Image::Model::YCC) {
        ii.haveYCC = true;

        auto planar = Image::make({.cm = image.cm, .size = image.size, .planes = 3});
        image.convert(planar);


        auto pixi = selectedImageInfo_.pixels.get();
        auto& ypl = planar.planes[0];  // Luma plane
        auto& cbpl = planar.planes[1];  // Chroma plane
        auto& crpl = planar.planes[2];  // Chroma

        for (Index y = 0; y < height; ++y) {
            auto yRow = &ypl.buffer[y * ypl.bpr];
            auto chIndex = y/2 * cbpl.bpr;
            auto cbRow = &cbpl.buffer[chIndex];
            auto crRow = &crpl.buffer[chIndex];

            for (Index x = 0; x < width; ++x) {
                auto& ycc = pixi->ycc;
                auto& yccn = pixi->yccn;

                ycc.y = yRow[x];
                ycc.cb = cbRow[x/2];
                ycc.cr = crRow[x/2];

                yccn.y = float(ycc.y) / 255;
                yccn.cb = float(ycc.cb) / 255;
                yccn.cr = float(ycc.cr) / 255;

                ++pixi;
            }
        }

    }

    auto rgbaImage = image.clone(Image::Model::RGBA);

    ii.haveRGB = true;

    auto destArgb = ii.argbData.get();
    auto pixi = ii.pixels.get();
    auto srcRgba = rgbaImage.data();

    for (Index y = 0; y < height; ++y) {
        for (Index x = 0; x < width; ++x) {

            pixi->rgb.r = srcRgba[0];
            pixi->rgb.g = srcRgba[1];
            pixi->rgb.b = srcRgba[2];
            pixi->alpha = srcRgba[3];

            if (pixi->alpha != 0xff)
                ii.haveAlpha = true;


            destArgb[0] = pixi->rgb.b;
            destArgb[1] = pixi->rgb.g;
            destArgb[2] = pixi->rgb.r;
            destArgb[3] = pixi->alpha;

            destArgb += 4;
            srcRgba += 4;


            pixi->rgbn.r = float(pixi->rgb.r) / 255; //float(r / 255);
            pixi->rgbn.g = float(pixi->rgb.g) / 255;
            pixi->rgbn.b = float(pixi->rgb.b) / 255;
            pixi->alphan = float(pixi->alpha) / 255;

            auto hsvi = cognit::rgb_to_hsv_int<int, int>((int)pixi->rgb.r, (int)pixi->rgb.g, (int)pixi->rgb.b);
            //pixi->hsv = std::make_from_tuple<cognit::ColorHSV<int>>(hsvi);
            pixi->hsv = cognit::ColorHSV<int>{std::get<0>(hsvi), std::get<1>(hsvi), std::get<2>(hsvi)};

            pixi->hsvn = cognit::rgb_to_hsv(pixi->rgbn);

            pixi->lab = cognit::rgb_to_lab(pixi->rgbn);



            ++pixi;
        }
    }


    return &selectedImageInfo_;
}




}  // namespace 


