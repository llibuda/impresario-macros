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
#include "camerainput.h"
#include <opencv2/core.hpp>

CvCameraInput::CvCameraInput() : MacroBase(), ptrCapture(0) {
  // set up macro description
  setName(L"cv::CameraInput");
  setCreator(L"Lars Libuda");
  setGroup(L"Image Sources");
  setDescription(L"Loads images from a camera supported by ffmpeg library");
  addOutput<cv::Mat>(L"Frame",L"Currently loaded video frame");
  addParameter<int>(L"Camera device ID",L"Camera device id as given by system",0,L"IntSpinBox",L"{\"minValue\": 0, \"maxValue\": 1}");
}

CvCameraInput::~CvCameraInput() {
}

MacroBase::Status CvCameraInput::onInit() {
  const int& deviceId= getParameterValue<int>(0);
  ptrCapture = new cv::VideoCapture(deviceId);
  if (!ptrCapture || !ptrCapture->isOpened()) {
    setErrorMsg(L"Failed to open camera capture interface.");
    return Error;
  }
  return Ok;
}

MacroBase::Status CvCameraInput::onApply() {
  cv::Mat& output = accessOutput<cv::Mat>(0);
  if (ptrCapture) {
    if (!ptrCapture->read(output)) {
      setErrorMsg(L"Failed to read frame from camera capture interface. Was the camera disconnected?");
      return Error;
    }
    else {
      return Ok;
    }
  }
  return Error;
}

MacroBase::Status CvCameraInput::onExit() {
  delete ptrCapture;
  ptrCapture = 0;
  return Ok;
}
