/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#include "types.h"


APEAL_QT_HEADERS_BEGIN
#include <QApplication>
#include <QMessageBox>
APEAL_QT_HEADERS_END


namespace image_lab {

struct MainApplication: public QApplication {
    MainApplication(int argc, char** argv)
        : QApplication(argc, argv)
    {
    }
    virtual ~MainApplication() {}

    bool notify(QObject* rec, QEvent* ev)
    {
        try {
            return QApplication::notify(rec, ev);
        } catch (std::exception& e) {
            QMessageBox::critical(0, "Error!", e.what());
        } catch (...) {
            QMessageBox::critical(0, "Error!", "Unhandled Exception!");
        }
        return false;
    }

    void on_quit() {}
};

}  // namespace image_lab
