/*
 * gallery_plugin_facerecognition_resetter_controller.cpp
 *
 * Copyright (C) 2012 Igalia, S.L.
 *
 * Author: Andres Gomez <agomez@igalia.com>
 *         Simon Pena <spena@igalia.com>
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


#include "gallery_plugin_facerecognition_resetter_controller.h"

#ifdef Q_OS_LINUX
#include <stdlib.h>
#endif // Q_OS_LINUX

#include <QDir>

static const char* xdg_data_home = getenv("XDG_DATA_HOME");
static const char* data_root_dir = GALLERYCORE_DATA_ROOT_DIR;
static const char* data_data_dir = GALLERYCORE_DATA_DATA_DIR;
static const char* database_filename = FACE_RECOGNITION_DATABASE_FILENAME;

GalleryPluginFacerecognitionResetterController::GalleryPluginFacerecognitionResetterController() :
    QObject()
{
}

bool GalleryPluginFacerecognitionResetterController::deleteDB(QString &infoText) const
{
    bool result = false;

    QDir dir(xdg_data_home);
    if (!dir.exists(data_root_dir)) {
        infoText = QString("Directory didn't exist beforehand.");
        goto clean;
    }

    dir.cd(data_root_dir);
    if (!dir.exists(data_data_dir)) {
        infoText = QString("Directory didn't exist beforehand.");
        goto clean;
    }

    dir.cd(data_data_dir);
    if (dir.exists(database_filename)) {
        if (!dir.remove(database_filename)) {
            infoText = QString("Failed deleting the DB.");
            return result;
        } else {
            infoText = QString("Succeeded deleting the DB.");
            result = true;
        }
    } else {
        infoText = QString("Face Recognition data base "
                         "didn't exist beforehand.");
    }

    dir.cdUp();
    if (!dir.rmdir(data_data_dir)) {
        infoText.append(" Failed deleting the parent directory.");
        return result;
    }

    infoText.append(" Succeeded deleting the parent directory.");


clean:

    return result;
}
