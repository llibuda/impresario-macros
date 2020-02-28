/****************************************************************************************************
**   Impresario Library ImageProcessing_opencv-3
**   This file is part of the Impresario Library ImageProcessing_opencv-3.
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
#include "cascadeclassifier.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

CvCascadeClassifier::CvCascadeClassifier() : MacroBase{}, classifier{nullptr} {
  // set up macro description
  setName(L"cv::CascadeClassifier");
  setCreator(L"Lars Libuda");
  setGroup(L"Object Detection");
  setDescription(L"Detects objects in a grey scale image by means of cascaded classifiers.");
  addInput<cv::Mat>(L"Input image",L"8-bit grey scale image for object detection");
  addOutput<cv::Mat>(L"Output image",L"Visualization of detected results");
  addParameter<std::string>(L"Classifier file",L"Path to classifier defition file","",L"StringFileSelector",L"{\"title\": \"Select classifier\", \"filters\": [\"Classifier files (*.xml)\",\"All files (*.*)\"]}");
  addParameter<double>(L"Scale factor",L"Parameter specifying how much the image size is reduced at each image scale.",1.1,L"RealSpinBox",L"{ \"minValue\": 1.1, \"maxValue\": 2.0, \"step\": 0.1, \"decimals\": 1 }");
  addParameter<int>(L"Min. Neighbors",L"Parameter specifying how many neighbors each candidate rectangle should have to retain it.",2,L"IntSpinBox",L"{ \"minValue\": 1, \"maxValue\": 5, \"step\": 1 }");
  addParameter<int>(L"Min. Size",L"Minimum size for detected object.",10,L"IntSpinBox",L"{ \"minValue\": 1, \"maxValue\": 1000, \"step\": 1 }");
  addParameter<int>(L"Max. Size",L"Maximum size for detected object.",50,L"IntSpinBox",L"{ \"minValue\": 1, \"maxValue\": 1000, \"step\": 1 }");
}

MacroBase::Status CvCascadeClassifier::onInit() {
  const auto* input = accessInput<cv::Mat>(0);
  if (input == nullptr) {
    setErrorMsg(L"Input image is not connected.");
    return Error;
  }
  return createAndLoadClassifier(getParameterValue<std::string>(0));
}

MacroBase::Status CvCascadeClassifier::onApply() {
  const auto* input = accessInput<cv::Mat>(0);
  if (!input || input->dims != 2 || input->type() != CV_8UC1) {
    setErrorMsg(L"Type of input is not supported. Type CV_8UC1 is required.");
    return Error;
  }
  auto& output = accessOutput<cv::Mat>(0);
  RegionsOfInterest regions;
  auto scaleFactor = getParameterValue<double>(1);
  auto minNeighbors = getParameterValue<int>(2);
  auto minSize = getParameterValue<int>(3);
  auto maxSize = getParameterValue<int>(3);
  try {
    classifier->detectMultiScale(*input,regions,scaleFactor,minNeighbors,0,cv::Size(minSize,minSize),cv::Size(maxSize,maxSize));
  }
  catch(cv::Exception& ex) {
    std::basic_ostringstream<wchar_t> errorMsg;
    errorMsg << ex.what();
    setErrorMsg(errorMsg.str());
    return Error;
  }
  std::cout << "Detected " << regions.size() << " regions of interest." << std::endl;

  // draw regions of interest
  const static cv::Scalar colors[] =
  {
      cv::Scalar(255,0,0),
      cv::Scalar(255,128,0),
      cv::Scalar(255,255,0),
      cv::Scalar(0,255,0),
      cv::Scalar(0,128,255),
      cv::Scalar(0,255,255),
      cv::Scalar(0,0,255),
      cv::Scalar(255,0,255)
  };
  cv::cvtColor(*input,output,CV_GRAY2RGB);
  int colorIndex = 0;
  for(const cv::Rect& region : regions)
  {
    cv::rectangle(output,region,colors[colorIndex++ % 8]);
  }
  return Ok;
}

void CvCascadeClassifier::onParametersChanged(ParameterSet & /*parameters*/) {
}

MacroBase::Status CvCascadeClassifier::onExit() {
  if (classifier)
  {
    delete classifier;
    classifier = nullptr;
  }
  return Ok;
}

MacroBase::Status CvCascadeClassifier::createAndLoadClassifier(const std::string &fileName) {
  if (classifier) {
    delete classifier;
    classifier = nullptr;
  }
  classifier = new cv::CascadeClassifier();
  if (!classifier) {
    setErrorMsg(L"Out of memory. Failed to create classifier.");
    return Error;
  }
  if (fileName.empty()) {
    setErrorMsg(L"No classifier specified in parameters.");
    return Error;
  }
  if (!classifier->load(fileName)) {
    std::wostringstream errorMsg;
    errorMsg << L"Failed to load classifier from '" << fileName.c_str() << "'";
    setErrorMsg(errorMsg.str());
    return Error;
  }
  return Ok;
}

