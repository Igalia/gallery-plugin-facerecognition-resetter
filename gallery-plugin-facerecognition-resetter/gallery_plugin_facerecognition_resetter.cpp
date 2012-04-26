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
#include <QDir>

#ifdef Q_OS_LINUX
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#endif // Q_OS_LINUX

static const char* xdg_data_home = getenv("XDG_DATA_HOME");
static const char* data_root_dir = GALLERYCORE_DATA_ROOT_DIR;
static const char* data_data_dir = GALLERYCORE_DATA_DATA_DIR;
static const char* database_filename = FACE_RECOGNITION_DATABASE_FILENAME;
static const char* database_journal_filename = FACE_RECOGNITION_DATABASE_FILENAME"-journal";
static const char* core_user = GALLERYCORE_USER;
static const char* core_group = GALLERYCORE_GROUP;
static const char* regular_user = REGULAR_USER;
static const char* regular_group = REGULAR_GROUP;
static const int MENU_INDEX             = 15;
static const int PORTRAIT_HEIGHT        = 475;
static const int LANDSCAPE_HEIGHT       = 250;
static const int TAP_DISTANCE           = 20;
static const int INFO_BANNER_TIMEOUT    = 2000;

M_LIBRARY


GalleryPluginFacerecognitionResetterPrivate::GalleryPluginFacerecognitionResetterPrivate()
{
}

GalleryPluginFacerecognitionResetterPrivate::~GalleryPluginFacerecognitionResetterPrivate()
{
}

bool GalleryPluginFacerecognitionResetterPrivate::deleteDB(QString &infoText) const
{
    bool result = false;

    infoText = QString("");

    QDir dir(xdg_data_home);
    if (!dir.exists(data_root_dir)) {
        infoText.append("Directory didn't exist beforehand.");
        goto clean;
    }

    dir.cd(data_root_dir);
    if (!dir.exists(data_data_dir)) {
        infoText.append("Directory didn't exist beforehand.");
        goto clean;
    }

    dir.cd(data_data_dir);
    if (dir.exists(database_filename)) {
        if (!dir.remove(database_filename)) {
            infoText.append("Failed deleting the DB.");
            return result;
        } else {
            infoText.append("Succeeded deleting the DB.");
            result = true;
        }
    } else {
        infoText.append("DB didn't exist beforehand.");
    }

    if (dir.exists(database_journal_filename)) {
        if (!dir.remove(database_journal_filename)) {
            infoText.append("Failed deleting the DB journal.");
            result = false;
            return result;
        } else {
            infoText.append("Succeeded deleting the DB journal.");
            result = true;
        }
    } else {
        infoText.append(" DB journal didn't exist beforehand.");
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

bool GalleryPluginFacerecognitionResetterPrivate::protectDB(bool protect, QString &infoText) const
{
    bool result = false;
    struct passwd *pwd = 0;
    struct group *grd = 0;
    mode_t mode = 0;
    QFile::Permissions directoryPermissions;
    QFile::Permissions filePermissions;

    if (protect) {

#ifdef Q_OS_LINUX

        pwd = getpwnam(core_user);
        grd = getgrnam(core_group);
        mode = S_ISGID | S_IRGRP | S_IWGRP | S_IXGRP;

#endif // Q_OS_LINUX

        directoryPermissions = QFile::ReadGroup
            | QFile::WriteGroup
            | QFile::ExeGroup;
        filePermissions = QFile::ReadOwner
            | QFile::WriteOwner
            | QFile::ReadGroup
            | QFile::WriteGroup;
    } else {

#ifdef Q_OS_LINUX

        pwd = getpwnam(regular_user);
        grd = getgrnam(regular_group);
        mode = S_IRUSR | S_IWUSR | S_IXUSR
            | S_IRGRP | S_IWGRP | S_IXGRP
            | S_IROTH | S_IWOTH | S_IXOTH;

#endif // Q_OS_LINUX

        directoryPermissions = QFile::ReadOwner
            | QFile::WriteOwner
            | QFile::ExeOwner
            | QFile::ReadGroup
            | QFile::WriteGroup
            | QFile::ExeGroup
            | QFile::ReadOther
            | QFile::WriteOther
            | QFile::ExeOther;
        filePermissions = QFile::ReadOwner
            | QFile::WriteOwner
            | QFile::ReadGroup
            | QFile::WriteGroup
            | QFile::ReadOther
            | QFile::WriteOther;
    }

    infoText = QString("");

    QDir dir(xdg_data_home);
    if (!dir.exists(data_root_dir)) {
        infoText.append("Directory didn't exist beforehand.");
        goto clean;
    }

    dir.cd(data_root_dir);
    if (!dir.exists(data_data_dir)) {
        infoText.append("Directory didn't exist beforehand.");
        goto clean;
    }

#ifdef Q_OS_LINUX

    if (NULL != pwd) {
        if (NULL != grd) {
            if (0 == chown(dir.absoluteFilePath(data_data_dir).toUtf8().constData(),
                           pwd->pw_uid,
                           grd->gr_gid)) {
                infoText.append("Owner of the parent directory changed.");
            } else {
                infoText.append("Failed changing owner of the parent directory.");
                goto clean;
            }
        }
    }

    if (0 == chmod(dir.absoluteFilePath(data_data_dir).toUtf8().constData(),
                   mode)) {
        infoText.append(" Permissions of the parent directory changed.");
    } else {
        infoText.append(" Failed changing the permissions of the parent directory.");
        goto clean;
    }

#else

    if (QFile::setPermissions(dir.absoluteFilePath(data_data_dir),
                              directoryPermissions)) {
        infoText.append(" Permissions of the parent directory changed.");
    } else {
        infoText.append(" Failed changing the permissions of the parent directory.");
        goto clean;
    }

#endif // Q_OS_LINUX

    dir.cd(data_data_dir);
    if (dir.exists(database_filename)) {

#ifdef Q_OS_LINUX

        if (NULL != pwd) {
            if (NULL != grd) {
                if (0 == chown(dir.absoluteFilePath(database_filename).toUtf8().constData(),
                               pwd->pw_uid,
                               grd->gr_gid)) {
                    infoText.append(" Owner of the DB changed.");
                } else {
                    infoText.append(" Failed changing the owner of the DB.");
                    goto clean;
                }
            }
        }

#endif // Q_OS_LINUX

        if (QFile::setPermissions(dir.absoluteFilePath(database_filename),
                                  filePermissions)) {
            infoText.append(" Permissions of the DB changed.");
            result = true;
        } else {
            infoText.append(" Failed changing the permissions of the DB.");
            goto clean;
        }

    } else {
        infoText.append(" DB didn't exist beforehand.");
        goto clean;
    }

    // Journal file
    if (dir.exists(database_journal_filename)) {

#ifdef Q_OS_LINUX

        if (NULL != pwd) {
            if (NULL != grd) {
                if (0 == chown(dir.absoluteFilePath(database_journal_filename).toUtf8().constData(),
                               pwd->pw_uid,
                               grd->gr_gid)) {
                    infoText.append(" Owner of the DB journal changed.");
                } else {
                    infoText.append(" Failed changing the owner of the DB journal.");
                    goto clean;
                }
            }
        }

#endif // Q_OS_LINUX

        if (QFile::setPermissions(dir.absoluteFilePath(database_journal_filename),
                                  filePermissions)) {
            infoText.append(" Permissions of the DB journal changed.");
        } else {
            infoText.append(" Failed changing the permissions of the DB journal.");
            goto clean;
        }

    } else {
        infoText.append(" DB journal didn't exist beforehand.");
        goto clean;
    }


clean:

    return result;
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
    connect(pluginWidget, SIGNAL(protectFacerecognitionDatabaseButtonClicked()),
            SLOT(protectDBOperation()));
    connect(pluginWidget, SIGNAL(unprotectFacerecognitionDatabaseButtonClicked()),
            SLOT(unprotectDBOperation()));
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
        showInfoBanner("Edition disabled.\nJust try to delete, "
                       "and/or un/protect "
                       "the Facerecognition database");
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
    GalleryPluginFacerecognitionResetterWidget* widget =
        static_cast<GalleryPluginFacerecognitionResetterWidget*>(toolBarWidget());
    QString infoText;

    if (d->deleteDB(infoText)) {
        showInfoBanner("Success!!!\nPlease, close Gallery immediately");
        widget->setResultLabelText(infoText + "<br />Please, close Gallery immediately");
    } else {
        showInfoBanner("Failed. :(");
        widget->setResultLabelText(infoText);
    }
}

void GalleryPluginFacerecognitionResetter::activate()
{
    showMessageBox("Plugin instructions",
                   "This is just a dummy plugin for resetting "
                   "or un/protecting "
                   "the Facerecognition database.<br />"
                   "Just click on the Reset, "
                   "Protect and/or Unprotect button/s.");
}

void GalleryPluginFacerecognitionResetter::protectDBOperation()
{
    Q_D(GalleryPluginFacerecognitionResetter);
    GalleryPluginFacerecognitionResetterWidget* widget =
        static_cast<GalleryPluginFacerecognitionResetterWidget*>(toolBarWidget());
    QString infoText;

    if (d->protectDB(true, infoText)) {
        showInfoBanner("Success!!!");
        widget->setResultLabelText(infoText);
    } else {
        showInfoBanner("Failed. :(");
        widget->setResultLabelText(infoText);
    }
}

void GalleryPluginFacerecognitionResetter::unprotectDBOperation()
{
    Q_D(GalleryPluginFacerecognitionResetter);
    GalleryPluginFacerecognitionResetterWidget* widget =
        static_cast<GalleryPluginFacerecognitionResetterWidget*>(toolBarWidget());
    QString infoText;

    if (d->protectDB(false, infoText)) {
        showInfoBanner("Success!!!");
        widget->setResultLabelText(infoText);
    } else {
        showInfoBanner("Failed. :(");
        widget->setResultLabelText(infoText);
    }
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

