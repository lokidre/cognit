/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#include "main_window.h"

namespace image_lab {

void MainWindow::initPanels()
{
    //auto dock = new QDockWidget("Customers", this);

    //dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    imageInfoPanel = new ImageInfoPanel(this);
    addDockWidget(Qt::LeftDockWidgetArea, imageInfoPanel);

    imagesDirPanel_ = new ImagesDirectoryPanel(this);
    addDockWidget(Qt::LeftDockWidgetArea, imagesDirPanel_);


    filtersPanel_ = new FiltersPanel(this);
    addDockWidget(Qt::RightDockWidgetArea, filtersPanel_);

    pixelInfoPanel = new PixelInfoPanel(this);
    addDockWidget(Qt::RightDockWidgetArea, pixelInfoPanel);
}


}  // namespace image_lab
