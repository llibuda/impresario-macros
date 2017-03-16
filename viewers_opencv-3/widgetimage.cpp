/****************************************************************************************************
**   Impresario Library Viewers_opencv-3
**   This file is part of the Impresario Library Viewers_opencv-3.
**
**   Copyright (C) 2015-2017  Lars Libuda
**   All rights reserved.
**
**   Redistribution and use in source and binary forms, with or without
**   modification, are permitted provided that the following conditions are met:
**       * Redistributions of source code must retain the above copyright
**         notice, this list of conditions and the following disclaimer.
**       * Redistributions in binary form must reproduce the above copyright
**         notice, this list of conditions and the following disclaimer in the
**         documentation and/or other materials provided with the distribution.
**       * Neither the name of the copyright holder nor the
**         names of its contributors may be used to endorse or promote products
**         derived from this software without specific prior written permission.
**
**   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
**   DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
**   ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
*****************************************************************************************************/
#include "widgetimage.h"
#include <QMutexLocker>
#include <QVBoxLayout>
#include <QIcon>
#include <QAction>
#include <QLabel>
#include <QSpinBox>

WidgetImage::WidgetImage(QWidget *parent) : QWidget(parent), toolbar(0),
  statusbar(0), paintWnd(0), scrollArea(0), zoomBox(0) {
  toolbar = new QToolBar(tr("Image"),this);
  statusbar = new QStatusBar(this);
  paintWnd = new PaintWidget();
  scrollArea = new QScrollArea(this);
  scrollArea->setWidget(paintWnd);
  scrollArea->setWidgetResizable(true);

  QAction* action = new QAction(QIcon(":/icons/resources/save.png"),tr("Save Image"),toolbar);
  connect(action,SIGNAL(triggered()),paintWnd,SLOT(saveImage()));
  toolbar->addAction(action);
  toolbar->addSeparator();
  action = new QAction(QIcon(":/icons/resources/arrow_in.png"),tr("Fit to Window"),toolbar);
  action->setCheckable(true);
  action->setChecked(true);
  connect(action,SIGNAL(triggered(bool)),this,SLOT(toggleFitToWindow(bool)));
  connect(action,SIGNAL(triggered(bool)),paintWnd,SLOT(toggleFitToWindow(bool)));
  toolbar->addAction(action);
  action = new QAction(QIcon(":/icons/resources/zoom_100.png"),tr("Zoom 100%"),toolbar);
  action->setEnabled(false);
  connect(action,SIGNAL(triggered()),paintWnd,SLOT(zoomImage100()));
  toolbar->addAction(action);
  zoomBox = new QSpinBox(toolbar);
  zoomBox->setToolTip(tr("Zoom Image"));
  zoomBox->setRange(0,999);
  zoomBox->setSingleStep(10);
  zoomBox->setSuffix("%");
  zoomBox->setButtonSymbols(QAbstractSpinBox::PlusMinus);
  zoomBox->setEnabled(false);
  connect(zoomBox,SIGNAL(valueChanged(int)),paintWnd,SLOT(zoomImage(int)));
  connect(paintWnd,SIGNAL(setZoom(int)),zoomBox,SLOT(setValue(int)));
  toolbar->addWidget(zoomBox);

  QLabel* typeLabel = new QLabel(statusbar);
  typeLabel->setTextFormat(Qt::PlainText);
  typeLabel->setTextInteractionFlags(Qt::NoTextInteraction);
  typeLabel->setFrameShadow(QFrame::Sunken);
  statusbar->addPermanentWidget(typeLabel);
  QLabel* sizeLabel = new QLabel(statusbar);
  sizeLabel->setTextFormat(Qt::PlainText);
  sizeLabel->setTextInteractionFlags(Qt::NoTextInteraction);
  sizeLabel->setFrameShadow(QFrame::Sunken);
  statusbar->addPermanentWidget(sizeLabel);
  QLabel* posLabel = new QLabel(statusbar);
  posLabel->setTextFormat(Qt::PlainText);
  posLabel->setTextInteractionFlags(Qt::NoTextInteraction);
  posLabel->setFrameShape(QFrame::NoFrame);
  statusbar->addWidget(posLabel,1);
  connect(paintWnd,SIGNAL(setStatusMsg(QString,int)),statusbar,SLOT(showMessage(QString,int)),Qt::QueuedConnection);
  connect(paintWnd,SIGNAL(printImageSize(QString)),sizeLabel,SLOT(setText(QString)),Qt::QueuedConnection);
  connect(paintWnd,SIGNAL(printImageType(QString)),typeLabel,SLOT(setText(QString)),Qt::QueuedConnection);
  connect(paintWnd,SIGNAL(printImagePos(QString)),posLabel,SLOT(setText(QString)),Qt::QueuedConnection);

  QVBoxLayout* layout = new QVBoxLayout();
  layout->addWidget(toolbar);
  layout->addWidget(scrollArea,1);
  layout->addWidget(statusbar);
  layout->setSpacing(0);
  layout->setContentsMargins(0,0,0,0);
  setLayout(layout);
}

void WidgetImage::toggleFitToWindow(bool on) {
  scrollArea->setWidgetResizable(on);
  zoomBox->setEnabled(!on);
  toolbar->actions().at(3)->setEnabled(!on);
  if (on) {
    zoomBox->setRange(0,999);
  }
  else {
    zoomBox->setRange(10,300);
  }
}


