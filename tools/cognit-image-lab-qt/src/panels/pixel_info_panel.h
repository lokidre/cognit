/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
﻿#pragma once

#include "panel.h"

#include <QLabel>
#include <QLineEdit>


namespace image_lab {


class PixelInfoPanel: public Panel {

public:
    PixelInfoPanel(QMainWindow* parent): Panel{"Pixel Info", parent} {
        init();
    }

    //ValueWidgetP yccValue;

    ValueWidgetP selPos;
    ValueWidgetP selRgb;//, selAlpha;
    ValueWidgetP selRgbNorm;

    ValueWidgetP selYcc;
    //ValueWidgetP selYccDec;
    ValueWidgetP selYccNorm;

    ValueWidgetP selHsv;
    ValueWidgetP selHsvNorm;

    ValueWidgetP selLab;



    ValueWidgetP hoverPos;
    ValueWidgetP hoverRgb;


private:
    void init();
};

}  // namespace 

