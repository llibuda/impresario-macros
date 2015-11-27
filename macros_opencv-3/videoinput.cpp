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
#include "videoinput.h"
#include <opencv2/core.hpp>
#include <iostream>

CvVideoInput::CvVideoInput() : MacroBase(), ptrCapture(0) {
  // set up macro description
  setName(L"cv::VideoInput");
  setCreator(L"Lars Libuda");
  setGroup(L"Image Sources");
  setDescription(L"Loads images from a video");
  addOutput<cv::Mat>(L"Frame",L"Currently loaded video frame");
  addParameter<std::string>(L"Video file",L"Path to video file for playback","",L"StringFileSelector",L"{\"title\": \"Select video file\", \"filters\": [\"Video files (*.mp4 *.avi *.mkv)\",\"All files (*.*)\"]}");
}

CvVideoInput::~CvVideoInput() {
}

MacroBase::Status CvVideoInput::onInit() {
  const std::string& videoFilePath = getParameterValue<std::string>(0);
  if (videoFilePath.empty()) {
    setErrorMsg(L"No video file specified in parameters.");
    return Error;
  }
  ptrCapture = new cv::VideoCapture(videoFilePath);
  if (!ptrCapture || !ptrCapture->isOpened()) {
    setErrorMsg(L"Failed to open video capture interface.");
    return Error;
  }
  return Ok;
}

MacroBase::Status CvVideoInput::onApply() {
  cv::Mat& output = accessOutput<cv::Mat>(0);
  if (ptrCapture) {
    return (ptrCapture->read(output)) ? Ok : Stop;
  }
  return Error;
}

MacroBase::Status CvVideoInput::onExit() {
  delete ptrCapture;
  ptrCapture = 0;
  return Ok;
}
