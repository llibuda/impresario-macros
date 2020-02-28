/****************************************************************************************************
**   Impresario Library Viewers_opencv-3
**   This file is part of the Impresario Library Viewers_opencv-3.
**
**   Copyright (C) 2015-2020  Lars Libuda
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
#include <opencv2/imgproc.hpp>
#include <opencv/cv.h>

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent), fitToWindow{true}, zoomFactor{1.0} {
  setMinimumSize(10,10);
  connect(this,SIGNAL(updateGUI()),this,SLOT(update()),Qt::QueuedConnection);
}

void PaintWidget::updateImage(const cv::Mat* source) {
  QMutexLocker lock(&mutex);
  if (!((source != nullptr) && (source->depth() == CV_8U || source->depth() == CV_8S || source->depth() == CV_16U ||
       source->depth() == CV_16S || source->depth() == CV_32S || source->depth() == CV_32F || source->depth() == CV_64F) &&
      (source->channels() == 1 || source->channels() == 3 || source->channels() == 4) && (source->dims == 2))) return;

  source->copyTo(cvImage);
  cv::Mat tempImage;
  QString type;
  switch(cvImage.depth()) {
    case CV_8U: {
      type = QString("CV_8UC%1").arg(cvImage.channels());
      tempImage = cvImage;
      break;
    }
    case CV_8S: {
      type = QString("CV_8SC%1").arg(cvImage.channels());
      double min, max;
      cv::minMaxLoc(cvImage, &min, &max);
      cvImage.convertTo(tempImage,CV_8U,255.0 / (max - min), -min * 255.0 / (max - min));
      break;
    }
    case CV_16U: {
      type = QString("CV_16UC%1").arg(cvImage.channels());
      double min, max;
      cv::minMaxLoc(cvImage, &min, &max);
      cvImage.convertTo(tempImage,CV_8U,255.0 / (max - min), -min * 255.0 / (max - min));
      break;
    }
    case CV_16S: {
      type = QString("CV_16SC%1").arg(cvImage.channels());
      double min, max;
      cv::minMaxLoc(cvImage, &min, &max);
      cvImage.convertTo(tempImage,CV_8U,255.0 / (max - min), -min * 255.0 / (max - min));
      break;
    }
    case CV_32S: {
      type = QString("CV_32SC%1").arg(cvImage.channels());
      double min, max;
      cv::minMaxLoc(cvImage, &min, &max);
      cvImage.convertTo(tempImage,CV_8U,255.0 / (max - min), -min * 255.0 / (max - min));
      break;
    }
    case CV_32F: {
      type = QString("CV_32FC%1").arg(cvImage.channels());
      double min, max;
      cv::minMaxLoc(cvImage, &min, &max);
      cvImage.convertTo(tempImage,CV_8U,255.0 / (max - min), -min * 255.0 / (max - min));
      break;
    }
    case CV_64F: {
      type = QString("CV_64FC%1").arg(cvImage.channels());
      double min, max;
      cv::minMaxLoc(cvImage, &min, &max);
      cvImage.convertTo(tempImage,CV_8U,255.0 / (max - min), -min * 255.0 / (max - min));
      break;
    }
  }
  switch(cvImage.channels()) {
    case 1: {
      cv::cvtColor(tempImage,imageBuffer,CV_GRAY2RGB);
      image = QImage(imageBuffer.data, imageBuffer.cols, imageBuffer.rows, static_cast<int>(imageBuffer.step[0]), QImage::Format_RGB888);
      break;
    }
    case 3: {
      cv::cvtColor(tempImage,imageBuffer,CV_BGR2RGB);
      image = QImage(imageBuffer.data, imageBuffer.cols, imageBuffer.rows, static_cast<int>(imageBuffer.step[0]), QImage::Format_RGB888);
      break;
    }
    case 4: {
      cv::cvtColor(tempImage,imageBuffer,CV_BGR2RGB);
      image = QImage(imageBuffer.data, imageBuffer.cols, imageBuffer.rows, static_cast<int>(imageBuffer.step[0]), QImage::Format_RGBA8888);
      break;
    }
  }
  emit printImageType(type);
  emit printImageSize(QString("%1x%2").arg(cvImage.cols).arg(cvImage.rows));
  emit updateGUI();
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
  QMutexLocker lock(&mutex);
  QPainter painter(this);
  targetRect = this->rect();
  QRect imgRect = image.rect();
  if (fitToWindow) {
    double arImg = (double)imgRect.height() / (double)imgRect.width();
    double arTarget = (double)targetRect.height() / (double)targetRect.width();
    if (arTarget < arImg) {
      int height = targetRect.height();
      int width = static_cast<int>(height / arImg);
      int x = (targetRect.width() - width) / 2;
      targetRect = QRect(x,0,width,height);
      zoomFactor = (double)targetRect.width() / imgRect.width();
    }
    else {
      int width = targetRect.width();
      int height = static_cast<int>(width * arImg);
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
  printValueAtPos(x,y);
  QWidget::mouseMoveEvent(event);
}

void PaintWidget::mousePressEvent(QMouseEvent *event) {
  int x = event->x();
  int y = event->y();
  x = int(double(x - targetRect.x()) / zoomFactor);
  y = int(double(y - targetRect.y()) / zoomFactor);
  printValueAtPos(x,y);
  QWidget::mousePressEvent(event);
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *event) {
  emit printImagePos(QString(""));
  QWidget::mouseReleaseEvent(event);
}

void PaintWidget::printValueAtPos(int x, int y) {
  QMutexLocker lock(&mutex);
  if (x >= 0 && y >= 0 && x < cvImage.cols && y < cvImage.rows) {
    QStringList values;
    switch(cvImage.depth()) {
      case CV_8U:
        for(int i = 0; i < cvImage.channels(); ++i) {
          uchar value = ((uchar*)(cvImage.data + cvImage.step.p[0] * y + cvImage.step.p[1] * x))[i];
          values.append(QString("%1").arg(value));
        }
        break;
      case CV_8S:
        for(int i = 0; i < cvImage.channels(); ++i) {
          schar value = ((schar*)(cvImage.data + cvImage.step.p[0] * y + cvImage.step.p[1] * x))[i];
          values.append(QString("%1").arg(value));
        }
        break;
      case CV_16U:
        for(int i = 0; i < cvImage.channels(); ++i) {
          ushort value = ((ushort*)(cvImage.data + cvImage.step.p[0] * y + cvImage.step.p[1] * x))[i];
          values.append(QString("%1").arg(value));
        }
        break;
      case CV_16S:
        for(int i = 0; i < cvImage.channels(); ++i) {
          short value = ((short*)(cvImage.data + cvImage.step.p[0] * y + cvImage.step.p[1] * x))[i];
          values.append(QString("%1").arg(value));
        }
        break;
      case CV_32S:
        for(int i = 0; i < cvImage.channels(); ++i) {
          int value = ((int*)(cvImage.data + cvImage.step.p[0] * y + cvImage.step.p[1] * x))[i];
          values.append(QString("%1").arg(value));
        }
        break;
      case CV_32F:
        for(int i = 0; i < cvImage.channels(); ++i) {
          float value = ((float*)(cvImage.data + cvImage.step.p[0] * y + cvImage.step.p[1] * x))[i];
          values.append(QString("%1").arg(value,0,'f',2));
        }
        break;
      case CV_64F:
        for(int i = 0; i < cvImage.channels(); ++i) {
          double value = ((double*)(cvImage.data + cvImage.step.p[0] * y + cvImage.step.p[1] * x))[i];
          values.append(QString("%1").arg(value,0,'f',2));
        }
        break;
    }
    switch(cvImage.channels()) {
      case 1:
        emit printImagePos(QString("G(x:%1,y:%2)=(%3)").arg(x).arg(y).arg(values.join(",")));
        break;
      case 3:
        emit printImagePos(QString("BGR(x:%1,y:%2)=(%3)").arg(x).arg(y).arg(values.join(",")));
        break;
      case 4:
        emit printImagePos(QString("BGRA(x:%1,y:%2)=(%3)").arg(x).arg(y).arg(values.join(",")));
        break;
    }
  }
  else {
    emit printImagePos(QString(""));
  }
}
