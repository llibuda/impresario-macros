/****************************************************************************************************
**   Impresario Library ImageProcessing_opencv-3
**   This file is part of the Impresario Library ImageProcessing_opencv-3.
**
**   Copyright (C) 2015-2018  Lars Libuda
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
#include "cannyedge.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv/cv.h>
#include <iostream>

CvCannyEdge::CvCannyEdge(void) : MacroBase() {
  // set up macro description
  setName(L"cv::Canny");
  setCreator(L"Lars Libuda");
  setGroup(L"Image Processing");
  setDescription(L"Detects edges in an 8-bit Image (cv::Mat of type CV_8U).");
  addInput<cv::Mat>(L"Input image",L"8-bit grey scale image for edge detection");
  addOutput<cv::Mat>(L"Output image",L"8-bit black/white image with detected edges");
  addParameter<double>(L"High threshold",L"High threshold for the hysteresis procedure.",100.0,L"RealSpinBox",L"{ \"minValue\": 0.0, \"maxValue\": 1000.0, \"step\": 0.1, \"decimals\": 1 }");
  addParameter<double>(L"Low threshold",L"Low threshold for the hysteresis procedure.",80.0,L"RealSpinBox",L"{ \"minValue\": 0.0, \"maxValue\": 1000.0, \"step\": 0.1, \"decimals\": 1 }");
  addParameter<int>(L"Sobel kernel size",L"Size of Sobel kernel used for edge filtering (3, 5, or 7)",3,L"IntSpinBox",L"{ \"minValue\": 3, \"maxValue\": 7, \"step\": 2 }");
  addParameter<int>(L"Gradient norm",L"Gradient norm to be used.",0,L"IntComboBox",L"{ \"items\": [\"L1 norm\", \"L2 norm\"]}");
}

CvCannyEdge::~CvCannyEdge(void) {
}

MacroBase::Status CvCannyEdge::onInit() {
  const cv::Mat* input = accessInput<cv::Mat>(0);
  if (input == 0) {
    setErrorMsg(L"Input is not connected.");
    return Error;
  }
  return Ok;
}

MacroBase::Status CvCannyEdge::onApply() {
  const cv::Mat* input = accessInput<cv::Mat>(0);
  if (!input || input->dims != 2 || input->type() != CV_8UC1) {
    setErrorMsg(L"Type of input is not supported. Type CV_8UC1 is required.");
    return Error;
  }
  cv::Mat& output = accessOutput<cv::Mat>(0);
  const double& threshold1 = getParameterValue<double>(0);
  const double& threshold2 = getParameterValue<double>(1);
  const int& kernelSize = getParameterValue<int>(2);
  bool L2gradient = (getParameterValue<int>(3) == 1);
  try {
    cv::Canny(*input,output,threshold1,threshold2,kernelSize,L2gradient);
  }
  catch(cv::Exception& ex) {
    std::basic_ostringstream<wchar_t> errorMsg;
    errorMsg << ex.what();
    setErrorMsg(errorMsg.str());
    return Error;
  }
  return Ok;
}

void CvCannyEdge::onParametersChanged(ParameterSet &) {

}

