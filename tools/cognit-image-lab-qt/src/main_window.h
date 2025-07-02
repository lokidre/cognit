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

#include <panels/filters_panel.h>
#include <panels/image_info_panel.h>
#include <panels/images_directory_panel.h>
#include <panels/pixel_info_panel.h>

#include <image_widget.h>

APEAL_QT_HEADERS_BEGIN
#include <QAction>
#include <QMainWindow>
APEAL_QT_HEADERS_END


namespace image_lab {

class MainWindow: public QMainWindow {
    Q_OBJECT
    using Self = MainWindow;
    using Base = QMainWindow;

public:
    MainWindow()
        : QMainWindow()
    {
        init();
    }

    void show();

public:
    ImageWidget* imageViewWidget{};

    FiltersPanel* filtersPanel_{};
    PixelInfoPanel* pixelInfoPanel{};

    ImageInfoPanel* imageInfoPanel{};
    ImagesDirectoryPanel* imagesDirPanel_{};


private:
    void init();
    void initLayout();
    void initActions();
    void updateActions();
    void initPanels();


    bool loadFile(const QString& filename);

private:
    QAction* saveAsAct;
    QAction* printAct;
    QAction* copyAct;
    QAction* zoomInAct;
    QAction* zoomOutAct;
    QAction* normalSizeAct;
    QAction* fitToWindowAct;


private Q_SLOTS:
    void onOpen();
    void onAbout();

    void onZoom1();
    void onZoom2();
    void onZoom4();
    void onZoom8();
    void onZoom16();


protected:  // events
    void closeEvent(QCloseEvent* e);

    //void mouseMoveEvent(QMouseEvent *event) override;
};

}  // namespace image_lab
