/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#include "image_view.h"

APEAL_QT_HEADERS_BEGIN
#include <QApplication>
#include <QMenuBar>
APEAL_QT_HEADERS_END

namespace image_lab {

void ImageViewer::createActions()
{
    QMenu* menu{};

    auto addMenu = [&](auto text) { menu = menuBar()->addMenu(text); };

    auto addAction = [&](auto text, auto slot) { return menu->addAction(text, this, slot); };

    addMenu("&File");

    addAction("&Open...", &Self::onOpen);
    //->setEnabled(false);

    saveAsAct = addAction("&Save As...", &Self::onSaveAs);
    saveAsAct->setEnabled(false);

    //printAct = fileMenu->addAction(tr("&Print..."), this, &ImageViewer::print);
    //printAct->setShortcut(QKeySequence::Print);
    //printAct->setEnabled(false);

    menu->addSeparator();

    auto exitAct = addAction("E&xit", &QWidget::close);
    exitAct->setShortcut(tr("Ctrl+Q"));

    addMenu("&Edit");

    copyAct = addAction("&Copy", &ImageViewer::copy);
    copyAct->setShortcut(QKeySequence::Copy);
    copyAct->setEnabled(false);

    auto pasteAct = addAction("&Paste", &ImageViewer::paste);
    pasteAct->setShortcut(QKeySequence::Paste);

    addMenu("&View");

    zoomInAct = addAction("Zoom &In (25%)", &ImageViewer::zoomIn);
    zoomInAct->setShortcut(QKeySequence::ZoomIn);
    zoomInAct->setEnabled(false);

    zoomOutAct = addAction("Zoom &Out (25%)", &ImageViewer::zoomOut);
    zoomOutAct->setShortcut(QKeySequence::ZoomOut);
    zoomOutAct->setEnabled(false);

    normalSizeAct = addAction("&Normal Size", &ImageViewer::normalSize);
    normalSizeAct->setShortcut(tr("Ctrl+S"));
    normalSizeAct->setEnabled(false);

    menu->addSeparator();

    fitToWindowAct = addAction("&Fit to Window", &ImageViewer::fitToWindow);
    fitToWindowAct->setEnabled(false);
    fitToWindowAct->setCheckable(true);
    fitToWindowAct->setShortcut(tr("Ctrl+F"));

    addMenu("&Help");

    addAction("&About", &ImageViewer::about);
    //addAction(tr("About &Qt"), this, &QApplication::aboutQt);
}

void ImageViewer::updateActions()
{
    saveAsAct->setEnabled(!image.isNull());
    copyAct->setEnabled(!image.isNull());
    zoomInAct->setEnabled(!fitToWindowAct->isChecked());
    zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
    normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
}

}  // namespace image_lab
