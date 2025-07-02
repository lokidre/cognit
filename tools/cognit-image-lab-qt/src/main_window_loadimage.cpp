/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#include "main_window.h"

#include "image_toolkit.h"

#include <QGuiApplication>
#include <QImageReader>
#include <QMessageBox>
#include <QStatusBar>

namespace image_lab {


bool MainWindow::loadFile(const QString& filename)
{
    try {
        auto image = apl::ImageFile::load(filename.toStdString());
        //auto& image = imageContainer.firstByHeight();
        auto& first = image.firstByHeight();

        setWindowFilePath(filename);
        auto message = tr("%1: %2x%3, Depth: %4")
                           .arg(filename)
                           .arg(first.width())
                           .arg(first.height())
                           .arg(first.depth);

        ImageToolkit::instance()->setImage(std::move(image));

        statusBar()->showMessage(message);

    }
    catch (const std::exception& e) {
        auto&& title = QGuiApplication::applicationDisplayName();
        auto&& text = QString("Cannot load %1: %2").arg(filename, e.what());
        QMessageBox::critical(this, title, text);
        return false;
    }

    /*
    QImageReader reader(filename);
    reader.setAutoTransform(true);

    auto image = reader.read();

    if (image.isNull()) {
        auto&& title = QGuiApplication::applicationDisplayName();
        auto&& text = QString("Cannot load %1: %2").arg(filename, reader.errorString());
        QMessageBox::critical(this, title, text);
        return false;
    }
    */


    return true;
}


}  // namespace image_lab
