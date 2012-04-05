/*
 * gallery_plugin_facerecognition_resetter.cpp
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

#include "gallery_plugin_facerecognition_resetter.h"
#include "gallery_plugin_facerecognition_resetter_p.h"
#include "gallery_plugin_facerecognition_resetter_controller.h"
#include "gallery_plugin_facerecognition_resetter_widget.h"

#include <galleryedituiprovider.h>

#include <MApplication>
#include <MMessageBox>
#include <MBanner>
#include <MLabel>
#include <MLibrary>
#include <MSceneWindow>

#include <QuillImageFilter>
#include <QDesktopServices>
#include <QGraphicsLinearLayout>
#include <QGraphicsSceneMouseEvent>
#include <QUrl>
#include <QTextOption>

static const int MENU_INDEX             = 15;
static const int PORTRAIT_HEIGHT        = 250;
static const int LANDSCAPE_HEIGHT       = 214;
static const int TAP_DISTANCE           = 20;
static const int INFO_BANNER_TIMEOUT    = 2000;

M_LIBRARY


GalleryPluginFacerecognitionResetterPrivate::GalleryPluginFacerecognitionResetterPrivate() :
    m_controller(new GalleryPluginFacerecognitionResetterController())
{
}

GalleryPluginFacerecognitionResetterPrivate::~GalleryPluginFacerecognitionResetterPrivate()
{
    delete m_controller;
}

GalleryPluginFacerecognitionResetter::GalleryPluginFacerecognitionResetter(QObject* parent):
    GalleryEditPlugin(parent),
    d_ptr(new GalleryPluginFacerecognitionResetterPrivate())
{
}


GalleryPluginFacerecognitionResetter::~GalleryPluginFacerecognitionResetter()
{
    delete d_ptr;
}


QString GalleryPluginFacerecognitionResetter::name() const
{
    return QString("Facerecognition Resetter");
}

int GalleryPluginFacerecognitionResetter::menuIndex() const
{
    return MENU_INDEX;
}

QString GalleryPluginFacerecognitionResetter::iconID() const
{
    // XXX: Gallery plugins load their icons by ID, so they must be
    // placed in a location watched by the MThemeDaemon. However, it
    // seems that the MThemeDaemon only re-scans its content when
    // booting. As a consequence, the red icon corresponding to a
    // missing resource will appear until the device is rebooted.

    return QString("icon-m-image-edit-facerecognition-resetter");
}

bool GalleryPluginFacerecognitionResetter::containsUi() const
{
    return true;
}

QGraphicsWidget* GalleryPluginFacerecognitionResetter::createToolBarWidget(QGraphicsItem* parent)
{
    GalleryPluginFacerecognitionResetterWidget* pluginWidget =
        new GalleryPluginFacerecognitionResetterWidget(parent);
    connect(pluginWidget, SIGNAL(resetFacerecognitionDatabaseButtonClicked()),
            SLOT(performEditOperation()));
    connect(pluginWidget, SIGNAL(aboutLinkActivated(QString)),
            SLOT(onAboutLinkActivated(QString)));

    return pluginWidget;
}

bool GalleryPluginFacerecognitionResetter::receiveMouseEvent(QGraphicsSceneMouseEvent* event)
{
    if (event
        && event->type() == QEvent::GraphicsSceneMouseRelease
        && event->button() == Qt::LeftButton
        && (event->scenePos() - event->buttonDownScenePos(Qt::LeftButton)).manhattanLength() < TAP_DISTANCE) {
        showInfoBanner("Edition disabled.\nJust try to delete the Facerecognition database");
    }

    return false;
}

const QSize GalleryPluginFacerecognitionResetter::toolBarWidgetSize(const M::Orientation& orientation) const
{
    QSize size = GalleryEditPlugin::toolBarWidgetSize(orientation);

    if (M::Portrait == orientation) {
        size.setHeight(PORTRAIT_HEIGHT);
    } else {
        size.setHeight(LANDSCAPE_HEIGHT);
    }

    return size;
}

void GalleryPluginFacerecognitionResetter::performEditOperation()
{
    Q_D(GalleryPluginFacerecognitionResetter);
    if (d->m_controller) {
        GalleryPluginFacerecognitionResetterWidget* widget =
            static_cast<GalleryPluginFacerecognitionResetterWidget*>(toolBarWidget());
        QString infoText;

        if (d->m_controller->deleteDB(infoText)) {
            showInfoBanner(infoText + "\nPlease, close Gallery immediately");
            widget->setResultLabelText(infoText + "<br />Please, close Gallery immediately");
        } else {
            showInfoBanner(infoText);
            widget->setResultLabelText(infoText);
        }
    }
}

void GalleryPluginFacerecognitionResetter::activate()
{
    showMessageBox("Plugin instructions",
                   "This is just a dummy plugin for resetting "
                   "the Facerecognition database.<br />"
                   "Just click on the reset button");
}

void GalleryPluginFacerecognitionResetter::onAboutLinkActivated(const QString &link)
{
    Q_UNUSED(link)
    if (link.toLower().startsWith("http") || link.toLower().startsWith("mailto")) {
        QDesktopServices::openUrl(QUrl(link));
    } else {
        showMessageBox("About Facerecognition Resetter plugin",
                       "Copyright (c) 2012 Igalia S.L."
                       "<br /><br />"
                       "<a href=\"mailto:agomez@igalia.com\">agomez@igalia.com</a> | "
                       "<a href=\"http://www.igalia.com\">www.igalia.com</a>"
                       "<br /><br />"
                       "This library is free software; you can redistribute it and/or "
                       "modify it under the terms of the GNU Lesser General Public License "
                       "as published by the Free Software Foundation; version 2.1 of "
                       "the License, or (at your option) any later version.");
    }
}

MMessageBox* GalleryPluginFacerecognitionResetter::showMessageBox(const QString& title, const QString& text) const
{
    MMessageBox* messageBox = new MMessageBox(title, "");
    MLabel* innerLabel = new MLabel(messageBox);
    innerLabel->setWordWrap(true);
    innerLabel->setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    innerLabel->setStyleName("CommonQueryText");
    innerLabel->setText(text);
    innerLabel->setAlignment(Qt::AlignHCenter);
    messageBox->setCentralWidget(innerLabel);

    connect(innerLabel, SIGNAL(linkActivated(QString)),
            this, SLOT(onAboutLinkActivated(QString)));
    connect(this, SIGNAL(deactivated()),
            messageBox, SLOT(disappear()));

    messageBox->appear(MSceneWindow::DestroyWhenDone);

    return messageBox;
}

MBanner* GalleryPluginFacerecognitionResetter::showInfoBanner(const QString& title) const
{
    MBanner *infoBanner = new MBanner;
    infoBanner->setTitle(title);
    infoBanner->setStyleName(MBannerType::InformationBanner);
    infoBanner->model()->setDisappearTimeout(2000);
    connect(this, SIGNAL(deactivated()),
            infoBanner, SLOT(disappear()));

    infoBanner->appear(MApplication::activeWindow(), MSceneWindow::DestroyWhenDone);

    return infoBanner;
}

Q_EXPORT_PLUGIN2(gallery_plugin_facerecognition_resetter, GalleryPluginFacerecognitionResetter)

