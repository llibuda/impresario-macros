/****************************************************************************************************
**   Impresario Library ImageProcessing_opencv-3
**   This file is part of the Impresario Library ImageProcessing_opencv-3.
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
#include "cvmatconvert.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv/cv.h>

CvMatConvert::CvMatConvert() : MacroBase() {
  // set up macro description
  setName(L"cv::Mat::convertTo");
  setCreator(L"Lars Libuda");
  setGroup(L"Conversion");
  setDescription(L"Performs a pixel type conversion of the given image.");
  addInput<cv::Mat>(L"Image input",L"Input image for pixel type conversion");
  addOutput<cv::Mat>(L"Image output",L"Image with converted pixels.");
  addParameter<int>(L"Conversion type",L"New type pixel shall be be converted to.",0,L"IntComboBox",
                    L"{ \"items\": [\"CV_8U\",\"CV_8S\",\"CV_16U\",\"CV_16S\","
                    L"\"CV_32S\",\"CV_32F\",\"CV_64F\"] }");
}

CvMatConvert::~CvMatConvert() {
}

MacroBase::Status CvMatConvert::onInit() {
  const cv::Mat* input = accessInput<cv::Mat>(0);
  if (!input) {
    setErrorMsg(L"Input image not connected.");
    return Error;
  }
  return Ok;
}

MacroBase::Status CvMatConvert::onApply() {
  const cv::Mat* input = accessInput<cv::Mat>(0);
  cv::Mat& output = accessOutput<cv::Mat>(0);
  const int& type = getParameterValue<int>(0);
  int conversion;
  switch(type) {
    case 0:
      conversion = CV_8U;
      break;
    case 1:
      conversion = CV_8S;
      break;
    case 2:
      conversion = CV_16U;
      break;
    case 3:
      conversion = CV_16S;
      break;
    case 4:
      conversion = CV_32S;
      break;
    case 5:
      conversion = CV_32F;
      break;
    case 6:
      conversion = CV_64F;
      break;
    default:
      setErrorMsg(L"Unsupported conversion type.");
      return Error;
  }
  if (conversion != input->depth()) {
    input->convertTo(output,conversion);
  }
  else {
    input->copyTo(output);
  }
  return Ok;
}

MacroBase::Status CvMatConvert::onExit() {
  return Ok;
}
