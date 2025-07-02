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

#include "image_scene.h"

APEAL_QT_HEADERS_BEGIN
#include <QLabel>
#include <QPixmap>

//#include <QGraphicsView>
#include <QGraphicsWidget>

#include <QGraphicsPixmapItem>
APEAL_QT_HEADERS_END

namespace image_lab {

struct ImageInfo;

class ImageGraphicsView;
class MainWindow;


//class ImageWidget: public QScrollArea {
class ImageWidget: public QWidget {
    //class ImageWidget: public QGraphicsView {
    //class ImageWidget: public QGraphicsWidget {

public:
    ImageWidget(MainWindow* mainWindow);

    //void setImage(const QImage& image, PixelInfo* pixelInfo);
    void setImageContainer(const apl::ImageContainer* image);

    void setCurrentImageIndex(Index idx);
    void setZoom(int zoom);

    //void setImageData(uint8_t* data, int width, int height);

private:
    // Handling GUI
    MainWindow* mainWindow_{};

    void clearMouseHover();
    bool mouseMoveCleared_{true};


    QLabel* imageLabel_{};
    //QScrollArea* scrollArea_;

    //
    // Widget information
    //
    int widgetWidth_{}, widgetHeight_{};


    //
    // Image data
    //
    const ImageContainer* imageContainer_{};
    Index imageIndex_{};
    const ImageInfo* imageInfo_{};

    apl::ByteBuffer zoomedImageData_;
    int zoom_{1};


    //QPixmap* pixmap_{};
    QPixmap pixmap_;
    QGraphicsPixmapItem* pixmapItem_{};

    void updateImageData();

    //int imageWidth_{}, imageHeight_{};
    //PixelInfo* pixelInfo_{};

    ImageScene* imageScene_{};
    ImageGraphicsView* graphicsView_{};
    //QGraphicsView* graphicsView_{};


    void processResize(int width, int height);


public:  // Events
    void onMouseMove(int x, int y);
    void onMouseClick(int x, int y);

protected:
    void resizeEvent(QResizeEvent* event) override
    {
        widgetWidth_ = event->size().width();
        widgetHeight_ = event->size().height();
        processResize(widgetWidth_, widgetHeight_);
    }
};

}  // namespace image_lab
