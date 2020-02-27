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
#include "viewerimage.h"
#include <QWidget>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv/cv.h>

ViewerImage::ViewerImage() : ViewerBase() {
  setName(L"OpenCV 3.0.0 Image viewer");
  setDescription(L"Displays image types in OpenCV 3.0.0. Currently supported are cv::Mat with types CV_8UC1, CV_8UC3, and CV_8UC4.");
  setCreator(L"Lars Libuda");
  setGroup(L"Viewers");
  addInput<cv::Mat>(L"OpenCV image",L"cv::Mat for rendering");
}

MacroBase::Status ViewerImage::onInit() {
  return Ok;
}

MacroBase::Status ViewerImage::onApply() {
  const cv::Mat* srcImg = accessInput<cv::Mat>(0);
  WidgetImage* widget = accessWidget();
  if (srcImg != 0) {
    if ((srcImg->depth() == CV_8U || srcImg->depth() == CV_8S || srcImg->depth() == CV_16U ||
         srcImg->depth() == CV_16S || srcImg->depth() == CV_32S || srcImg->depth() == CV_32F || srcImg->depth() == CV_64F) &&
        (srcImg->channels() == 1 || srcImg->channels() == 3 || srcImg->channels() == 4) && (srcImg->dims == 2)) {
      widget->updateImage(srcImg);
      return Ok;
    }
    else {
      setErrorMsg(L"cv::Mat type is not supported.");
      return Error;
    }
  }
  else {
    setErrorMsg(L"No image input set.");
    return Error;
  }
}

MacroBase::Status ViewerImage::onExit() {
  return Ok;
}
