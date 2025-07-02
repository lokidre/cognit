/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#include "main.h"
#include "main_application.h"
#include "main_window.h"

#include "image_view.h"

APEAL_QT_HEADERS_BEGIN
#include <QApplication>
#include <QCommandLineParser>
APEAL_QT_HEADERS_END


int main(int argc, char* argv[])
{
    using namespace image_lab;

    auto retCode = 1;

    try {
        auto app = std::make_unique<MainApplication>(argc, argv);

        QGuiApplication::setApplicationDisplayName(PackageTitle);

        //QCommandLineParser cmdline;
        //cmdline.addHelpOption();
        //cmdline.addPositionalArgument("[file]", "Image file to open.");
        //cmdline.process(QCoreApplication::arguments());
        //auto&& args = cmdline.positionalArguments();

        //auto imageViewer = std::make_unique<ImageViewer>();
        auto mainWindow = std::make_unique<MainWindow>();



        //if (!args.isEmpty() && !imageViewer->loadFile(args.constFirst())) {
        //    return -1;
        //}

        //imageViewer->show();

        mainWindow->show();


        retCode = app->exec();
    } catch (const std::exception& e) {
        QMessageBox::critical(0, "Error!", e.what());
    } catch (...) {
        QMessageBox::critical(0, "Error!", "Unhandled Exception!");
    }

    return retCode;
}
