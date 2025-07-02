/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
﻿#include "image_info_panel.h"

//APEAL_QT_HEADERS_BEGIN
//#include <QGridLayout>
//APEAL_QT_HEADERS_END

namespace image_lab {

void ImageInfoPanel::init()
{
    setVBoxLayout();

    addGrid();

    addGridField("Size", imageSize);
    addGridField("Color", imageColorModel);

    addStretch();
}

}  // namespace

