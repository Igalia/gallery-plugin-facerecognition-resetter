/*
 * gallery_plugin_facerecognition_resetter_about_widget.cpp
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

#include "gallery_plugin_facerecognition_resetter_about_widget.h"

#include <MLabel>
#include <MWidgetCreator>
#include <QGraphicsLinearLayout>

M_REGISTER_WIDGET_NO_CREATE(GalleryPluginFacerecognitionResetterAboutWidget)

GalleryPluginFacerecognitionResetterAboutWidget::GalleryPluginFacerecognitionResetterAboutWidget() :
    MWidgetController(),
    m_aboutLabel(new MLabel),
    m_disclaimerLabel(new MLabel)
{
    m_disclaimerLabel->setStyleName("FacerecognitionResetterAboutDisclaimer");
    m_disclaimerLabel->setText("Facerecognition Resetter plugin<br />has been proudly brought to you "
                               "by <a href=\"http://www.igalia.com\">Igalia</a>");

    m_aboutLabel->setStyleName("FacerecognitionResetterAboutLink");
    m_aboutLabel->setText("<br /><a href=\"about\">About</a>");


    connect(m_disclaimerLabel, SIGNAL(linkActivated(QString)),
            this, SIGNAL(linkActivated(QString)));
    connect(m_aboutLabel, SIGNAL(linkActivated(QString)),
            this, SIGNAL(linkActivated(QString)));

    QGraphicsLinearLayout* mainLayout = new QGraphicsLinearLayout(Qt::Horizontal);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addItem(m_disclaimerLabel);
    mainLayout->addStretch();
    mainLayout->addItem(m_aboutLabel);

    setLayout(mainLayout);
}

GalleryPluginFacerecognitionResetterAboutWidget::~GalleryPluginFacerecognitionResetterAboutWidget()
{
    delete m_aboutLabel;
    delete m_disclaimerLabel;
}

void GalleryPluginFacerecognitionResetterAboutWidget::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    emit linkActivated("noLink");
}
