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
#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QImage>
#include <QMutex>
#include <QRect>
#include <opencv2/core.hpp>

class PaintWidget : public QWidget {
  Q_OBJECT
public:
  explicit PaintWidget(QWidget *parent = nullptr);

  void updateImage(const cv::Mat* source);

signals:
  void setStatusMsg(const QString msg, int timeout = 0);
  void setZoom(int value);
  void printImageSize(const QString size);
  void printImageType(const QString type);
  void printImagePos(const QString pos);
  void updateGUI();

public slots:
  void saveImage();
  void toggleFitToWindow(bool on);
  void zoomImage(int value);
  void zoomImage100();

protected:
  void paintEvent(QPaintEvent* event) override;
  void mouseMoveEvent(QMouseEvent * event) override;
  void mousePressEvent(QMouseEvent * event) override;
  void mouseReleaseEvent(QMouseEvent * event) override;

  void printValueAtPos(int x, int y);

private:
  cv::Mat        cvImage;
  cv::Mat        imageBuffer;
  QImage         image;
  QRect          targetRect;
  bool           fitToWindow;
  double         zoomFactor;
  mutable QMutex mutex;
};

#endif // PAINTWIDGET_H
