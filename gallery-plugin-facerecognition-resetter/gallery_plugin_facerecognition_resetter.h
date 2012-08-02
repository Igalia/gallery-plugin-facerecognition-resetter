/*
 * gallery_plugin_facerecognition_resetter.h
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

#ifndef GALLERY_PLUGIN_FACERECOGNITION_RESETTER_H
#define GALLERY_PLUGIN_FACERECOGNITION_RESETTER_H

#include <galleryeditplugin.h>

class MMessageBox;
class MBanner;
class GalleryPluginFacerecognitionResetterPrivate;

class GalleryPluginFacerecognitionResetter: public GalleryEditPlugin
{
    Q_OBJECT
    Q_INTERFACES(GalleryEditPlugin)

public:
    //! GalleryPluginFacerecognitionResetter constructor
    //! \param parent Optional parent
    GalleryPluginFacerecognitionResetter(QObject* parent = 0);

    //! GalleryPluginFacerecognitionResetter destructor
    virtual ~GalleryPluginFacerecognitionResetter();

    //! \reimp
    QString name() const;

    //! \reimp
    int menuIndex() const;

    //! \reimp
    QString iconID() const;

    //! \reimp
    bool containsUi() const;

    //! \reimp
    bool receiveMouseEvent(QGraphicsSceneMouseEvent* event);

    //! \reimp
    const QSize toolBarWidgetSize(const M::Orientation& orientation) const;

protected:
    //! \reimp
    QGraphicsWidget* createToolBarWidget(QGraphicsItem* parent = 0);

public Q_SLOTS:
    //! \reimp
    void performEditOperation();

    //! \reimp
    void activate();

    //! Invoked when pushed the reset DB button
    void onResetFacerecognitionDatabaseButtonClicked();

    //! Invoked when pushed the protect DB button
    void onProtectFacerecognitionDatabaseButtonClicked();

    //! Invoked when pushed the unprotect DB button
    void onUnprotectFacerecognitionDatabaseButtonClicked();

    //! Invoked when accepted the dialog for protecting the DB
    void protectDBOperation();

    //! Invoked when accepted the dialog for unprotecting DB
    void unprotectDBOperation();

    //! Invoked when a link in the about notice has been activated
    //! \param link The activated link
    void onAboutLinkActivated(const QString& link);

    //! Shows a message box with a given title and text
    //! \param title Text to be shown as a title in the message box
    //! \param text Text to be shown as the body in the message box
    //! \return The message box
    MMessageBox* showMessageBox(const QString& title, const QString& text) const;

    //! Shows an info banner with a given text
    //! \param title Text to be shown in the info banner
    //! \return The info banner
    MBanner* showInfoBanner(const QString& text) const;

private:
    Q_DISABLE_COPY(GalleryPluginFacerecognitionResetter)
    Q_DECLARE_PRIVATE(GalleryPluginFacerecognitionResetter)
    GalleryPluginFacerecognitionResetterPrivate* d_ptr;
};

#endif // GALLERY_PLUGIN_FACERECOGNITION_RESETTER_H

