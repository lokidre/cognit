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
#include "settings.h"

APEAL_QT_HEADERS_BEGIN

#include <QFileDialog>
#include <QImageReader>
#include <QImageWriter>
#include <QStandardPaths>

#include <QMessageBox>

#include <QMouseEvent>
APEAL_QT_HEADERS_END


namespace image_lab {

void MainWindow::init()
{
    imageViewWidget = new ImageWidget(this);
    setCentralWidget(imageViewWidget);

    initLayout();
    initPanels();
    initActions();

    //setWindowTitle(
    setUnifiedTitleAndToolBarOnMac(true);

    ImageToolkit::instance()->setupGui(imageViewWidget);
}

void MainWindow::show()
{
    // Restore state, geometry
    auto settings = Settings::instance();

    restoreState(settings->mainWindowState.getQByteArray());
    restoreGeometry(settings->mainWindowGeometry.getQByteArray());

    Base::show();

    auto lastImage = settings->lastOpenImagePath.getQString();
    if (!lastImage.isEmpty()) {
        loadFile(lastImage);
    }
}

void MainWindow::closeEvent(QCloseEvent* e)
{
    auto settings = Settings::instance();

    settings->mainWindowState = this->saveState();
    settings->mainWindowGeometry = this->saveGeometry();
}


static void initializeImageFileDialog(QFileDialog& dialog, QFileDialog::AcceptMode acceptMode)
{
    auto settings = Settings::instance();

    static bool firstDialog = true;

    auto lastDir = settings->lastOpenImageDir.getQString();

    if (lastDir.isEmpty()) {
        if (firstDialog) {
            firstDialog = false;
            auto picturesLocations
                = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
            dialog.setDirectory(
                picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
        }
    } else {
        dialog.setDirectory(lastDir);
    }

    QStringList mimeTypeFilters;
    auto supportedMimeTypes = acceptMode == QFileDialog::AcceptOpen
        ? QImageReader::supportedMimeTypes()
        : QImageWriter::supportedMimeTypes();

    for (auto& mimeTypeName: supportedMimeTypes)
        mimeTypeFilters.append(mimeTypeName);

    mimeTypeFilters.sort();

    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/jpeg");
    dialog.setAcceptMode(acceptMode);

    if (acceptMode == QFileDialog::AcceptSave)
        dialog.setDefaultSuffix("jpg");
}

void MainWindow::onOpen()
{
    QFileDialog dialog(this, tr("Open File"));

    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

    if (dialog.exec() == QDialog::Accepted) {
        auto files = dialog.selectedFiles();
        const auto& filename = files.constFirst();
        if (loadFile(filename)) {
            auto settings = Settings::instance();
            settings->lastOpenImagePath = filename;
            settings->lastOpenImageDir = dialog.directory().absolutePath();
        }
    }
}

void MainWindow::onZoom1() { ImageToolkit::instance()->setZoom(1); }

void MainWindow::onZoom2() { ImageToolkit::instance()->setZoom(2); }

void MainWindow::onZoom4() { ImageToolkit::instance()->setZoom(4); }

void MainWindow::onZoom8() { ImageToolkit::instance()->setZoom(8); }

void MainWindow::onZoom16() { ImageToolkit::instance()->setZoom(16); }


void MainWindow::onAbout()
{
    QMessageBox::about(this, "About Cognit Image Toolkit",
        R"(
<p>Cognit Image Lab</p>
               )");
}


//void MainWindow::mouseMoveEvent(QMouseEvent *event)
//{
//
//
//    Base::mouseMoveEvent(event);
//}


}  // namespace image_lab
