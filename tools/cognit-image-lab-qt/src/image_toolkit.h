/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include "types.h"

#include <apeal/buffer.hpp>
#include <apeal/image.hpp>
#include <apeal/singleton.hpp>

#include <cognit/color.hpp>


APEAL_QT_HEADERS_BEGIN
#include <QImage>
APEAL_QT_HEADERS_END


namespace image_lab {

class ImageWidget;


struct PixelInfo {
    // RGB and alpha
    cognit::ColorRGB<uint8_t> rgb;
    cognit::ColorRGB<float> rgbn;  // Normalized
    uint8_t alpha;
    float alphan;


    // YCbCr
    cognit::ColorYCC<uint8_t> ycc;
    cognit::ColorYCC<float> yccn;

    // HSV
    cognit::ColorHSV<int> hsv;
    cognit::ColorHSV<float> hsvn;

    // LAB
    cognit::ColorLAB<float> lab;
};

struct ImageInfo {
    Index width, height;
    Index bpr;

    bool haveRGB{};
    bool haveAlpha{};

    bool haveYCC{};


    apl::ByteBuffer argbData;
    apl::Buffer<PixelInfo> pixels;
};


class ImageToolkit: public apl::Singleton<ImageToolkit> {

public:
    void setupGui(ImageWidget* imageWidget) { imageWidget_ = imageWidget; }

    //void setImage(QImage&& img);
    void setImage(ImageContainer&& img);
    void setZoom(int zoom);

    const ImageInfo* selectImage(Index index);


private:
    // Setup
    ImageWidget* imageWidget_{};

    // Image data
    ImageContainer loadedImage_;
    ImageInfo selectedImageInfo_;

    //QImage loadedImage_;
    //QImage qImage_;

    //apl::ByteBuffer imageData_;

    //apl::Image image_;
};

}  // namespace image_lab
