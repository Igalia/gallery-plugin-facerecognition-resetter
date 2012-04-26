/*
 * gallery_plugin_facerecognition_resetter_widget.h
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

#ifndef GALLERY_PLUGIN_FACERECOGNITION_RESETTER_WIDGET_H
#define GALLERY_PLUGIN_FACERECOGNITION_RESETTER_WIDGET_H

#include <MWidgetController>

class GalleryPluginFacerecognitionResetterWidgetPrivate;

class GalleryPluginFacerecognitionResetterWidget : public MWidgetController
{
    Q_OBJECT
public:
    //! GalleryPluginFacerecognitionResetterWidget constructor
    //! \param parent Optional parent
    GalleryPluginFacerecognitionResetterWidget(QGraphicsItem* parent = 0);

    //! GalleryPluginFacerecognitionResetterWidget destructor
    virtual ~GalleryPluginFacerecognitionResetterWidget();

public Q_SLOTS:
    //! Called to set the result label text
    //! \param text Text to be shown in the result label
    void setResultLabelText(const QString& text);

Q_SIGNALS:
    //! Emitted when the button for resetting the facerecognition
    //! database is clicked
    void resetFacerecognitionDatabaseButtonClicked();

    //! Emitted when a link in the about notice was activated
    void aboutLinkActivated(const QString& link);

private:
    Q_DISABLE_COPY(GalleryPluginFacerecognitionResetterWidget)
    Q_DECLARE_PRIVATE(GalleryPluginFacerecognitionResetterWidget)
    GalleryPluginFacerecognitionResetterWidgetPrivate* d_ptr;
};

#endif // GALLERY_PLUGIN_FACERECOGNITION_RESETTER_WIDGET_H
