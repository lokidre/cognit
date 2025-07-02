/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
﻿#pragma once

#include <types.h>


APEAL_QT_HEADERS_BEGIN
#include <QDockWidget>
#include <QMainWindow>

#include <QVBoxLayout>

//#include <QLineEdit>
//#include <QGridLayout>
APEAL_QT_HEADERS_END


class QLineEdit;
class QGridLayout;

namespace image_lab {


class Panel: public QDockWidget {
protected:

    //using ValueWidget = QLineEdit;
    //using ValueWidgetP = ValueWidget*;
    using ValueWidgetP = QLineEdit*;

    Panel(const QString& title, QMainWindow *parent): QDockWidget(title, parent) {
        setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    }


    //
    // Convenience for building the widgets
    //
    void setVBoxLayout();

    QWidget* widget_{};
    QVBoxLayout* vboxLayout_{};


    QGridLayout* iniGrid_{};
    int iniRow_{};

    void addGrid();
    void addGridField(const QString& name, ValueWidgetP& widget);
    void addStretch();

};

}  // namespace
