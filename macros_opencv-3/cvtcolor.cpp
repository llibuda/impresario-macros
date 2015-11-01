/****************************************************************************************************
**   Impresario Library ImageProcessing_opencv-3.0.0
**   This file is part of the Impresario Library ImageProcessing_opencv-3.0.0.
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
#include "cvtcolor.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv/cv.h>

CvtColor::CvtColor() : MacroBase() {
  // set up macro description
  setName(L"cv::cvtColor");
  setCreator(L"Lars Libuda");
  setGroup(L"Image Processing");
  setDescription(L"Converts images from one color space to another");
  addInput<cv::Mat>(L"Image input",L"Input image for color conversion");
  addOutput<cv::Mat>(L"Image output",L"Image in new color space");
  addParameter<int>(L"Conversion",L"Color space conversion",0,L"IntComboBox",
                    L"{ \"items\": [\"CV_BGR2GRAY\",\"CV_RGB2GRAY\",\"CV_GRAY2BGR\",\"CV_GRAY2RGB\","
                    L"\"CV_BGR2XYZ\",\"CV_RGB2XYZ\",\"CV_XYZ2BGR\",\"CV_XYZ2RGB\","
                    L"\"CV_BGR2YCrCb\",\"CV_RGB2YCrCb\",\"CV_YCrCb2BGR\",\"CV_YCrCb2RGB\","
                    L"\"CV_BGR2HSV\",\"CV_RGB2HSV\",\"CV_HSV2BGR\",\"CV_HSV2RGB\","
                    L"\"CV_BGR2HLS\",\"CV_RGB2HLS\",\"CV_HLS2BGR\",\"CV_HLS2RGB\","
                    L"\"CV_BGR2Lab\",\"CV_RGB2Lab\",\"CV_Lab2BGR\",\"CV_Lab2RGB\","
                    L"\"CV_BGR2Luv\",\"CV_RGB2Luv\",\"CV_Luv2BGR\",\"CV_Luv2RGB\"] }");
}

CvtColor::~CvtColor() {
}

MacroBase::Status CvtColor::onInit() {
  const cv::Mat* input = accessInput<cv::Mat>(0);
  if (!input) {
    setErrorMsg(L"Input image not connected.");
    return Error;
  }
  return Ok;
}

MacroBase::Status CvtColor::onApply() {
  const cv::Mat* input = accessInput<cv::Mat>(0);
  if (input->depth() != CV_8U && input->depth() != CV_16U && input->depth() != CV_32F) {
    setErrorMsg(L"Input image not supported. Supported types are CV_8U, CV_16U, and CV_32F.");
    return Error;
  }
  cv::Mat& output = accessOutput<cv::Mat>(0);
  const int& space = getParameterValue<int>(0);
  int conversion;
  switch(space) {
    case 0:
      conversion = CV_BGR2GRAY;
      break;
    case 1:
      conversion = CV_RGB2GRAY;
      break;
    case 2:
      conversion = CV_GRAY2BGR;
      break;
    case 3:
      conversion = CV_GRAY2RGB;
      break;
    case 4:
      conversion = CV_BGR2XYZ;
      break;
    case 5:
      conversion = CV_RGB2XYZ;
      break;
    case 6:
      conversion = CV_XYZ2BGR;
      break;
    case 7:
      conversion = CV_XYZ2RGB;
      break;
    case 8:
      conversion = CV_BGR2YCrCb;
      break;
    case 9:
      conversion = CV_RGB2YCrCb;
      break;
    case 10:
      conversion = CV_YCrCb2BGR;
      break;
    case 11:
      conversion = CV_YCrCb2RGB;
      break;
    case 12:
      conversion = CV_BGR2HSV;
      break;
    case 13:
      conversion = CV_RGB2HSV;
      break;
    case 14:
      conversion = CV_HSV2BGR;
      break;
    case 15:
      conversion = CV_HSV2RGB;
      break;
    case 16:
      conversion = CV_BGR2HLS;
      break;
    case 17:
      conversion = CV_RGB2HLS;
      break;
    case 18:
      conversion = CV_HLS2BGR;
      break;
    case 19:
      conversion = CV_HLS2RGB;
      break;
    case 20:
      conversion = CV_BGR2Lab;
      break;
    case 21:
      conversion = CV_RGB2Lab;
      break;
    case 22:
      conversion = CV_Lab2BGR;
      break;
    case 23:
      conversion = CV_Lab2RGB;
      break;
    case 24:
      conversion = CV_BGR2Luv;
      break;
    case 25:
      conversion = CV_RGB2Luv;
      break;
    case 26:
      conversion = CV_Luv2BGR;
      break;
    case 27:
      conversion = CV_Luv2RGB;
      break;
    default:
      setErrorMsg(L"Unsupported conversion type.");
      return Error;
  }
  try {
    cv::cvtColor(*input,output,conversion);
  }
  catch(cv::Exception& ex) {
    std::basic_ostringstream<wchar_t> errorMsg;
    errorMsg << ex.what();
    setErrorMsg(errorMsg.str());
    return Error;
  }
  return Ok;
}

MacroBase::Status CvtColor::onExit() {
  return Ok;
}
