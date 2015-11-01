/****************************************************************************************************
**   Impresario Library Viewers_ltilib-2
**   This file is part of the Impresario Library Viewers_ltilib-2.
**
**   Copyright (C) 2015  Lars Libuda
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
#include "paintwidget.h"
#include "widgetimage.h"
#include <QMutexLocker>
#include <QPainter>
#include <QRgb>
#include <QFileDialog>

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent), image(), imgType(0), fitToWindow(true), zoomFactor(1.0), targetRect(), ltiChannel() {
  setMinimumSize(10,10);
  connect(this,SIGNAL(updateGUI()),this,SLOT(update()),Qt::QueuedConnection);
}

void PaintWidget::updateImage(const lti::image* source) {
  if (source == 0) return;

  QMutexLocker lock(&mutex);
  const int rows = source->rows();
  const int cols = source->columns();
  image = QImage(cols,rows, QImage::Format_ARGB32_Premultiplied);

  for(int y = 0; y < rows; ++y) {
    const lti::vector<lti::rgbaPixel>& srcRow = source->getRow(y);
    QRgb* destRow = (QRgb*)image.scanLine(y);
    for (int x = 0; x < cols; ++x) {
      const lti::rgbaPixel& px = srcRow.at(x);
      destRow[x] = qRgba(px.red,px.green,px.blue,255);
    }
  }
  imgType = 0;
  emit updateGUI();
  emit printImageSize(QString("%1x%2").arg(image.width()).arg(image.height()));
}

void PaintWidget::updateImage(const lti::channel8* source) {
  if (source == 0) return;

  QMutexLocker lock(&mutex);
  const int rows = source->rows();
  const int cols = source->columns();
  image = QImage(cols,rows, QImage::Format_ARGB32_Premultiplied);

  for(int y = 0; y < rows; ++y) {
    const lti::vector<lti::ubyte>& srcRow = source->getRow(y);
    QRgb* destRow = (QRgb*)image.scanLine(y);
    for (int x = 0; x < cols; ++x) {
      const lti::ubyte& px = srcRow.at(x);
      destRow[x] = qRgba(px,px,px,255);
    }
  }
  imgType = 1;
  emit updateGUI();
  emit printImageSize(QString("%1x%2").arg(image.width()).arg(image.height()));
}

void PaintWidget::updateImage(const lti::channel* source) {
  if (source == 0) return;

  QMutexLocker lock(&mutex);
  ltiChannel = *source;
  const int rows = source->rows();
  const int cols = source->columns();
  image = QImage(cols,rows, QImage::Format_ARGB32_Premultiplied);

  lti::channel8 temp;
  temp.castFrom(*source,true,true);
  for(int y = 0; y < rows; ++y) {
    const lti::vector<lti::ubyte>& srcRow = temp.getRow(y);
    QRgb* destRow = (QRgb*)image.scanLine(y);
    for (int x = 0; x < cols; ++x) {
      const lti::ubyte& px = srcRow.at(x);
      destRow[x] = qRgba(px,px,px,255);
    }
  }
  imgType = 2;
  emit updateGUI();
  emit printImageSize(QString("%1x%2").arg(image.width()).arg(image.height()));
}

void PaintWidget::saveImage() {
  QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"),
                             "", tr("Images (*.png *.jpg *.bmp)"));
  if (!fileName.isEmpty()) {
    QMutexLocker lock(&mutex);
    if (image.save(fileName)) {
      emit setStatusMsg(tr("Saved image to disk."),1500);
    }
    else {
      emit setStatusMsg(tr("Failed to save image!"),3000);
    }
  }
}

void PaintWidget::toggleFitToWindow(bool on) {
  fitToWindow = on;
  update();
}

void PaintWidget::zoomImage(int value) {
  zoomFactor = (double)(value/100.0);
  update();
}

void PaintWidget::zoomImage100() {
  zoomFactor = 1.0;
  emit setZoom(100);
  update();
}

void PaintWidget::paintEvent(QPaintEvent* /*event*/) {
  QPainter painter(this);
  QMutexLocker lock(&mutex);
  targetRect = this->rect();
  QRect imgRect = image.rect();
  if (fitToWindow) {
    double arImg = (double)imgRect.height() / (double)imgRect.width();
    double arTarget = (double)targetRect.height() / (double)targetRect.width();
    if (arTarget < arImg) {
      int height = targetRect.height();
      int width = height / arImg;
      int x = (targetRect.width() - width) / 2;
      targetRect = QRect(x,0,width,height);
      zoomFactor = (double)targetRect.width() / imgRect.width();
    }
    else {
      int width = targetRect.width();
      int height = width * arImg;
      int y = (targetRect.height() - height) / 2;
      targetRect = QRect(0,y,width,height);
      zoomFactor = (double)targetRect.height() / imgRect.height();
    }
    emit setZoom(int(zoomFactor * 100));
  }
  else {
    targetRect.setX(0);
    targetRect.setY(0);
    targetRect.setWidth((int)(imgRect.width() * zoomFactor));
    targetRect.setHeight((int)(imgRect.height() * zoomFactor));
    resize(targetRect.width(),targetRect.height());
  }
  painter.drawImage(targetRect,image,imgRect);
}

void PaintWidget::mouseMoveEvent(QMouseEvent * event) {
  int x = event->x();
  int y = event->y();
  x = int(double(x - targetRect.x()) / zoomFactor);
  y = int(double(y - targetRect.y()) / zoomFactor);
  mutex.lock();
  if (x >= 0 && y >= 0 && x < image.width() && y < image.height()) {
    if (imgType == 0) {
      QRgb pixel = image.pixel(x,y);
      emit printImagePos(QString("RGB(x:%1,y:%2)=(%3,%4,%5)").arg(x).arg(y).arg(qRed(pixel)).arg(qGreen(pixel)).arg(qBlue(pixel)));
    }
    else if (imgType == 1) {
      QRgb pixel = image.pixel(x,y);
      emit printImagePos(QString("G(x:%1,y:%2)=%3").arg(x).arg(y).arg(qRed(pixel)));
    }
    else {
      emit printImagePos(QString("G(x:%1,y:%2)=%3").arg(x).arg(y).arg(ltiChannel.at(y,x)));
    }
  }
  else {
    emit printImagePos(QString(""));
  }
  mutex.unlock();
  QWidget::mouseMoveEvent(event);
}

void PaintWidget::mousePressEvent(QMouseEvent *event) {
  int x = event->x();
  int y = event->y();
  x = int(double(x - targetRect.x()) / zoomFactor);
  y = int(double(y - targetRect.y()) / zoomFactor);
  mutex.lock();
  if (x >= 0 && y >= 0 && x < image.width() && y < image.height()) {
    if (imgType == 0) {
      QRgb pixel = image.pixel(x,y);
      emit printImagePos(QString("RGB(x:%1,y:%2)=(%3,%4,%5)").arg(x).arg(y).arg(qRed(pixel)).arg(qGreen(pixel)).arg(qBlue(pixel)));
    }
    else if (imgType == 1) {
      QRgb pixel = image.pixel(x,y);
      emit printImagePos(QString("G(x:%1,y:%2)=%3").arg(x).arg(y).arg(qRed(pixel)));
    }
    else {
      emit printImagePos(QString("G(x:%1,y:%2)=%3").arg(x).arg(y).arg(ltiChannel.at(y,x)));
    }
  }
  else {
    emit printImagePos(QString(""));
  }
  mutex.unlock();
  QWidget::mousePressEvent(event);
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *event) {
  emit printImagePos(QString(""));
  QWidget::mouseReleaseEvent(event);
}
