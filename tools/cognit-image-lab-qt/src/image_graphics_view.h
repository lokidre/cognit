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
#include <QGraphicsView>
APEAL_QT_HEADERS_END


namespace image_lab {

class ImageWidget;
class ImageScene;

class ImageGraphicsView: public QGraphicsView {
public:

    ImageGraphicsView(ImageScene* scene, ImageWidget*);

private:
    ImageWidget* widget_{};


protected:
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
};

}  // namespace 


