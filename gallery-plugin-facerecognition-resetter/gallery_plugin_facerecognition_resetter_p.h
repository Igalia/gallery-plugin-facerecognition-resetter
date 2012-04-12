/*
 * gallery_plugin_facerecognition_resetter_p.h
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

#ifndef GALLERY_PLUGIN_FACERECOGNITION_RESETTER_P_H
#define GALLERY_PLUGIN_FACERECOGNITION_RESETTER_P_H

class GalleryPluginFacerecognitionResetterPrivate
{
public:
    //! GalleryPluginFacerecognitionResetterPrivate constructor
    GalleryPluginFacerecognitionResetterPrivate();

    //! GalleryPluginFacerecognitionResetterPrivate destructor
    virtual ~GalleryPluginFacerecognitionResetterPrivate();

    //! Deletes the facerecognition dabatase.
    //!
    //! \param infoText in which to store the result message.
    //! \return true on success, false otherwise
    bool deleteDB(QString &infoText) const;

    //! Protects the facerecognition dabatase.
    //!
    //! \param protect whether to protect the database or not.
    //! \param infoText in which to store the result message.
    //! \return true on success, false otherwise
    bool protectDB(bool protect, QString &infoText) const;
};

#endif // GALLERY_PLUGIN_FACERECOGNITION_RESETTER_P_H
