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

APEAL_QT_HEADERS_BEGIN
#include <QAction>
#include <QImage>
#include <QLabel>
#include <QMainWindow>
#include <QScrollArea>
#include <QScrollBar>
APEAL_QT_HEADERS_END

namespace image_lab {

class ImageViewer: public QMainWindow {
    Q_OBJECT

    using Self = ImageViewer;



public:
    ImageViewer(QWidget* parent = nullptr);
    bool loadFile(const QString&);

private Q_SLOTS:
    void onOpen();
    void onSaveAs();
    void print();
    void copy();
    void paste();
    void zoomIn();
    void zoomOut();
    void normalSize();
    void fitToWindow();
    void about();

private:
    void createActions();
    void createMenus();
    void updateActions();
    bool saveFile(const QString& fileName);
    void setImage(const QImage& newImage);
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar* scrollBar, double factor);

    QImage image;
    QLabel* imageLabel;
    QScrollArea* scrollArea;
    double scaleFactor = 1;

    QAction* saveAsAct;
    QAction* printAct;
    QAction* copyAct;
    QAction* zoomInAct;
    QAction* zoomOutAct;
    QAction* normalSizeAct;
    QAction* fitToWindowAct;
};

}  // namespace image_lab
