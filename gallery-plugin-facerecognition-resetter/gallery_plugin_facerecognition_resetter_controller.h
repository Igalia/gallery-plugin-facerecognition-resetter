/*
 * gallery_plugin_facerecognition_resetter_controller.h
 *
 * Copyright (C) 2012 Igalia, S.L.
 *
 * Author: Andres Gomez <agomez@igalia.com>
 *
 * This file is part of the Gallery Facerecognition Resetter Plugin.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; version 2.1 of the
 * License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see
 * http://www.gnu.org/licenses/
 */

#ifndef GALLERY_PLUGIN_FACERECOGNITION_RESETTER_CONTROLLER_H
#define GALLERY_PLUGIN_FACERECOGNITION_RESETTER_CONTROLLER_H

#include <QObject>
#include <QString>

class GalleryPluginFacerecognitionResetterController : public QObject
{
    Q_OBJECT
public:
    explicit GalleryPluginFacerecognitionResetterController();

public Q_SLOTS:
    bool deleteDB(QString &infoText) const;

};

#endif // GALLERY_PLUGIN_FACERECOGNITION_RESETTER_CONTROLLER_H

