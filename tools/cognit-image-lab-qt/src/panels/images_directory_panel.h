/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
﻿#pragma once

#include "panel.h"

namespace image_lab {

struct ImagesDirectoryPanel: Panel {
    ImagesDirectoryPanel(QMainWindow* parent): Panel("Directory", parent){}
};

}  // namespace 
