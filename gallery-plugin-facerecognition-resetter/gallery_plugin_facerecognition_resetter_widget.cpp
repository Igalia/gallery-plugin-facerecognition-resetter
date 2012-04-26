/*
 * gallery_plugin_facerecognition_resetter_widget.cpp
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

#include "gallery_plugin_facerecognition_resetter_widget.h"
#include "gallery_plugin_facerecognition_resetter_widget_p.h"
#include "gallery_plugin_facerecognition_resetter_about_widget.h"

#include <MApplication>
#include <MButton>
#include <MLabel>
#include <MSeparator>
#include <MWidgetController>
#include <MWidgetCreator>

#include <QGraphicsLinearLayout>

M_REGISTER_WIDGET_NO_CREATE(GalleryPluginFacerecognitionResetterWidget)

GalleryPluginFacerecognitionResetterWidgetPrivate::GalleryPluginFacerecognitionResetterWidgetPrivate() :
    m_resetFacerecognitionDatabaseButton(new MButton),
    m_resultLabel(new MLabel),
    m_aboutSeparator(new MSeparator),
    m_aboutWidget(new GalleryPluginFacerecognitionResetterAboutWidget)
{
    m_resetFacerecognitionDatabaseButton->setText("Reset Facerecognition Database");
    m_resetFacerecognitionDatabaseButton->setObjectName("ResetFacerecognitionDatabaseButton");
    m_resetFacerecognitionDatabaseButton->setStyleName("CommonTopSplitButtonInverted");

    m_aboutSeparator->setStyleName("CommonHeaderDividerInverted");
}

GalleryPluginFacerecognitionResetterWidgetPrivate::~GalleryPluginFacerecognitionResetterWidgetPrivate()
{
    delete m_resetFacerecognitionDatabaseButton;
    delete m_resultLabel;
    delete m_aboutSeparator;
    delete m_aboutWidget;
}

GalleryPluginFacerecognitionResetterWidget::GalleryPluginFacerecognitionResetterWidget(QGraphicsItem* parent) :
    MWidgetController(parent),
    d_ptr(new GalleryPluginFacerecognitionResetterWidgetPrivate)
{
    setObjectName("GalleryPluginFacerecognitionResetterWidget");
    setStyleName("ImageEditorBcControl");
    setContentsMargins(0, 0, 0, 0);

    Q_D(GalleryPluginFacerecognitionResetterWidget);

    connect(d->m_resetFacerecognitionDatabaseButton,
            SIGNAL(clicked()),
            SIGNAL(resetFacerecognitionDatabaseButtonClicked()));
    connect(d->m_aboutWidget,
            SIGNAL(linkActivated(QString)),
            SIGNAL(aboutLinkActivated(QString)));

    QGraphicsLinearLayout* mainLayout = new QGraphicsLinearLayout(Qt::Vertical);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->addItem(d->m_resetFacerecognitionDatabaseButton);
    mainLayout->setAlignment(d->m_resetFacerecognitionDatabaseButton,
                             Qt::AlignCenter);
    mainLayout->addItem(d->m_resultLabel);
    mainLayout->setAlignment(d->m_resultLabel, Qt::AlignCenter);
    mainLayout->addItem(d->m_aboutSeparator);
    mainLayout->addItem(d->m_aboutWidget);

    setLayout(mainLayout);
}

GalleryPluginFacerecognitionResetterWidget::~GalleryPluginFacerecognitionResetterWidget()
{
    delete d_ptr;
    d_ptr = 0;
}

void GalleryPluginFacerecognitionResetterWidget::setResultLabelText(const QString& text)
{
    Q_D(GalleryPluginFacerecognitionResetterWidget);
    d->m_resultLabel->setText(text);
}
