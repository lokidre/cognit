/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include "main.h"
#include "types.h"

#include <apeal/singleton.hpp>

APEAL_QT_HEADERS_BEGIN
#include <QSettings>
APEAL_QT_HEADERS_END

namespace image_lab {

class Setting {
public:
    Setting(const QString& key, const QString& def = {})
        : key_{key}
        , def_{def}
    {
    }

    //
    // Setting values
    //
    Setting& operator=(const QString& val)
    {
        qset_.setValue(key_, val);
        return *this;
    }

    Setting& operator=(const QByteArray& val)
    {
        qset_.setValue(key_, val);
        return *this;
    }


    //
    // Reading values
    //
    QString getQString()
    {  //return loadQString(key_, def_); }
        return qset_.value(key_, def_).toString();
    }

    QByteArray getQByteArray() { return qset_.value(key_, def_).toByteArray(); }

private:
    QString key_, def_;
    QSettings qset_{PackageOrganization, PackageApplication};


    //QString loadQString(const QString& key, const QString& def = {}) {
    //    //auto var = qset_.value(key, def);
    //    auto var = qset_.value(key);
    //    if (var.isNull())
    //        return def;

    //    auto s = var.toString();
    //    return var.toString();
    //}
};

class Settings: public apl::Singleton<Settings> {
public:
    Setting mainWindowState{"main_window_state"};
    Setting mainWindowGeometry{"main_window_geomtry"};

    Setting lastOpenImageDir{"last_open_image_dir"};
    Setting lastOpenImagePath{"last_open_image_file"};


private:
};

}  // namespace image_lab
