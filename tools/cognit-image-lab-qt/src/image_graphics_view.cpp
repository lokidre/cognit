/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#include "image_graphics_view.h"

#include "image_widget.h"

APEAL_QT_HEADERS_BEGIN
#include <QMouseEvent>
APEAL_QT_HEADERS_END


namespace image_lab {

ImageGraphicsView::ImageGraphicsView(ImageScene* scene, ImageWidget* widget)
    : QGraphicsView(scene, widget), widget_(widget)
{
    setMouseTracking(true);
}


void ImageGraphicsView::mouseMoveEvent(QMouseEvent* event)
{
    const auto& pos = event->position();
    auto sp = mapToScene((int)pos.x(), (int)pos.y());
    widget_->onMouseMove((int)sp.x(), (int)sp.y());
}

void ImageGraphicsView::mousePressEvent(QMouseEvent* event)
{
    const auto& pos = event->position();
    auto sp = mapToScene((int)pos.x(), (int)pos.y());

    widget_->onMouseClick((int)sp.x(), (int)sp.y());
}


}  // namespace

