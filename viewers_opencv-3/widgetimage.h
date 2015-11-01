/****************************************************************************************************
**   Impresario Library Viewers_opencv-3.0.0
**   This file is part of the Impresario Library Viewers_opencv-3.0.0.
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
#ifndef WIDGETIMAGE_H
#define WIDGETIMAGE_H

#include "paintwidget.h"
#include <QWidget>
#include <QToolBar>
#include <QStatusBar>
#include <QScrollArea>
#include <QSpinBox>
#include <opencv2/core.hpp>

class WidgetImage : public QWidget
{
  Q_OBJECT
public:
  explicit WidgetImage(QWidget *parent = 0);

  void updateImage(const cv::Mat* source) {
    Q_ASSERT(paintWnd != 0);
    paintWnd->updateImage(source);
  }

private slots:
  void toggleFitToWindow(bool on);

private:
  QToolBar*    toolbar;
  QStatusBar*  statusbar;
  PaintWidget* paintWnd;
  QScrollArea* scrollArea;
  QSpinBox*    zoomBox;
};

#endif // WIDGETIMAGE_H
