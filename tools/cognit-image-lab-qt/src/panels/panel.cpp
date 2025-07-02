/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
﻿#include "panel.h"

APEAL_QT_HEADERS_BEGIN
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
APEAL_QT_HEADERS_END

namespace image_lab {

void Panel::setVBoxLayout()
{
    widget_ = new QWidget;
    vboxLayout_ = new QVBoxLayout;

    widget_->setLayout(vboxLayout_);

    setWidget(widget_);
}


void Panel::addGrid()
{
    iniGrid_ = new QGridLayout();
    iniRow_ = 0;

    vboxLayout_->addLayout(iniGrid_);
}

void Panel::addGridField(const QString& name, ValueWidgetP& widget)
{
    auto label = new QLabel(QString("%1:").arg(name));
    iniGrid_->addWidget(label, iniRow_, 0, Qt::AlignRight);

    widget = new QLineEdit();
    widget->setReadOnly(true);
    iniGrid_->addWidget(widget, iniRow_, 1);

    ++iniRow_;

}

void Panel::addStretch()
{
    vboxLayout_->addStretch();
}


}  // namespace
