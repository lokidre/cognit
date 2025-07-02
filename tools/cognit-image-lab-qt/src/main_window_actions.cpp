/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#include "main_window.h"

APEAL_QT_HEADERS_BEGIN
#include <QMenuBar>
APEAL_QT_HEADERS_END


namespace image_lab {


void MainWindow::initActions()
{
    QMenu* menu{};

    auto addMenu = [&](auto text) { menu = menuBar()->addMenu(text); };

    auto addAction
        = [&](auto text, auto slot) { return menu->addAction(text, this, slot); };

    addMenu("&File");

    addAction("&Open...", &Self::onOpen)->setShortcut(tr("Ctrl+O"));
    //->setEnabled(false);

    //saveAsAct = addAction("&Save As...", &Self::onSaveAs);
    //saveAsAct->setEnabled(false);

    //printAct = fileMenu->addAction(tr("&Print..."), this, &ImageViewer::print);
    //printAct->setShortcut(QKeySequence::Print);
    //printAct->setEnabled(false);

    menu->addSeparator();

    addAction("E&xit", &QWidget::close)->setShortcut(tr("Ctrl+Q"));


    addMenu("&Zoom");
    addAction("1:1", &Self::onZoom1);
    addAction("1:2", &Self::onZoom2);
    addAction("1:4", &Self::onZoom4);
    addAction("1:8", &Self::onZoom8);
    addAction("1:16", &Self::onZoom16);


    /*
    addMenu("&Edit");

    copyAct = addAction("&Copy", &Self::onCopy);
    copyAct->setShortcut(QKeySequence::Copy);
    copyAct->setEnabled(false);

    auto pasteAct = addAction("&Paste", &Self::onPaste);
    pasteAct->setShortcut(QKeySequence::Paste);

    addMenu("&View");

    zoomInAct = addAction("Zoom &In (25%)", &Self::onZoomIn);
    zoomInAct->setShortcut(QKeySequence::ZoomIn);
    zoomInAct->setEnabled(false);

    zoomOutAct = addAction("Zoom &Out (25%)", &Self::onZoomOut);
    zoomOutAct->setShortcut(QKeySequence::ZoomOut);
    zoomOutAct->setEnabled(false);

    normalSizeAct = addAction("&Normal Size", &Self::onNormalSize);
    normalSizeAct->setShortcut(tr("Ctrl+S"));
    normalSizeAct->setEnabled(false);

    menu->addSeparator();

    fitToWindowAct = addAction("&Fit to Window", &Self::onFitToWindow);
    fitToWindowAct->setEnabled(false);
    fitToWindowAct->setCheckable(true);
    fitToWindowAct->setShortcut(tr("Ctrl+F"));
    */

    addMenu("&Help");

    addAction("&About", &Self::onAbout);
    //addAction(tr("About &Qt"), this, &QApplication::aboutQt);
}

void MainWindow::updateActions()
{
    //saveAsAct->setEnabled(!image.isNull());
    //copyAct->setEnabled(!image.isNull());
    //zoomInAct->setEnabled(!fitToWindowAct->isChecked());
    //zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
    //normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
}



}  // namespace image_lab
