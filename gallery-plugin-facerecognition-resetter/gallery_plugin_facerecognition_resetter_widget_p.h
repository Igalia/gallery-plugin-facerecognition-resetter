/*
 * gallery_plugin_facerecognition_resetter_widget_p.h
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

#ifndef GALLERY_PLUGIN_FACERECOGNITION_RESETTER_WIDGET_P_H
#define GALLERY_PLUGIN_FACERECOGNITION_RESETTER_WIDGET_P_H

class MLayout;
class MLinearLayoutPolicy;
class MButton;
class MLabel;
class MSeparator;
class MSlider;
class GalleryPluginFacerecognitionResetterAboutWidget;

class GalleryPluginFacerecognitionResetterWidgetPrivate
{
public:
    //! GalleryPluginFacerecognitionResetterWidgetPrivate constructor
    GalleryPluginFacerecognitionResetterWidgetPrivate();

    //! GalleryPluginFacerecognitionResetterWidgetPrivate destructor
    virtual ~GalleryPluginFacerecognitionResetterWidgetPrivate();

public:
    //! Focus area layout
    MLayout* m_orientationLayout;

    //! Landscape policy for the focus area layout
    MLinearLayoutPolicy* m_landscapePolicy;

    //! Portrait policy for the focus area layout
    MLinearLayoutPolicy* m_portraitPolicy;

    //! Button to remove the facerecognition database
    MButton* m_resetFacerecognitionDatabaseButton;

    //! Button to protect the facerecognition database
    MButton* m_protectFacerecognitionDatabaseButton;

    //! Button to unprotect the facerecognition database
    MButton* m_unprotectFacerecognitionDatabaseButton;

    //! Label with the result of the operation
    MLabel* m_resultLabel;

    //! Separator dividing the widget from the about claim
    MSeparator* m_aboutSeparator;

    //! Widget containing the about disclaimer
    GalleryPluginFacerecognitionResetterAboutWidget* m_aboutWidget;
};

#endif // GALLERY_PLUGIN_FACERECOGNITION_RESETTER_WIDGET_P_H
