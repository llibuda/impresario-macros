/****************************************************************************************************
**   Impresario Library ImageProcessing_ltilib-2
**   This file is part of the Impresario Library ImageProcessing_ltilib-2.
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
#include "loadimages.h"
#include <opencv/cv.h>
#include "opencv2/imgcodecs.hpp"
#include <iostream>
#include <filesystem>

CvLoadImages::CvLoadImages() : MacroBase(), fileList(), fileIndex(0) {
  // set up macro description
  setName(L"cv::loadImages");
  setCreator(L"Lars Libuda");
  setGroup(L"Image Sources");
  setDescription(L"Loads images from a given directory in alphabetical order");
  addOutput<cv::Mat>(L"Image",L"Image currently loaded");
  addOutput<char *>(L"Image path",L"Full path of the currently loaded image");
  addParameter<std::string>(L"Source directory",L"Directory where to load images from","",L"StringDirSelector");
  addParameter<bool>(L"Repeat",L"Starts loading images from beginning when end was reached.",false,L"BoolComboBox");
  addParameter<std::string>(L"Current File",L"Current loaded image","",L"StringFileSelector");
}

CvLoadImages::~CvLoadImages() {
}

MacroBase::Status CvLoadImages::onInit() {
  fileIndex = 0;
  fileList.clear();
  const std::string& directory = getParameterValue<std::string>(0);
  if (directory.empty()) {
    setErrorMsg(L"No directory specified in parameters.");
    return Error;
  }
  std::filesystem::path p(directory);
  try  {
    if (!std::filesystem::exists(p)) {
      std::basic_ostringstream<wchar_t> errorMsg;
      errorMsg << L"Given path '" << directory.c_str() << L"' does not exist.";
      setErrorMsg(errorMsg.str());
      return Error;
    }
    if (!std::filesystem::is_directory(p)) {
      std::basic_ostringstream<wchar_t> errorMsg;
      errorMsg << L"Given path '" << directory.c_str() << L"' is not a valid directory.";
      setErrorMsg(errorMsg.str());
      return Error;
    }
    for (const std::filesystem::directory_entry& x : std::filesystem::directory_iterator(p)) {
      fileList.push_back(x.path().string());
    }
  }
  catch (const std::filesystem::filesystem_error& ex) {
    std::basic_ostringstream<wchar_t> errorMsg;
    errorMsg << L"Error while accessing file system: " << ex.what();
    setErrorMsg(errorMsg.str());
    return Error;
  }
  if (fileList.empty()) {
    std::basic_ostringstream<wchar_t> errorMsg;
    errorMsg << L"Given directory '" << directory.c_str() << L"' does not contain any files.";
    setErrorMsg(errorMsg.str());
    return Error;
  }
  return Ok;
}

MacroBase::Status CvLoadImages::onApply() {
  cv::Mat& output = accessOutput<cv::Mat>(0);
  char* & filename = accessOutput<char*>(1);
  if (fileIndex < fileList.size()) {
    filename = const_cast<char*>(fileList[fileIndex].c_str());
    setParameterValue<std::string>(2,std::string(fileList[fileIndex]));
    output = cv::imread(cv::String(fileList[fileIndex]), cv::IMREAD_COLOR);
    if (output.empty()) {
      std::basic_ostringstream<wchar_t> errorMsg;
      errorMsg << L"Failed to load file '" << fileList[fileIndex].c_str() << L"'.";
      setErrorMsg(errorMsg.str());
      return Error;
    }
    fileIndex++;
    if (fileIndex >= fileList.size()) {
      const bool& repeat = getParameterValue<bool>(1);
      if (repeat)
      {
        fileIndex = 0;
        return Ok;
      }
      else
      {
        return Stop;
      }
    }
  }
  return Ok;
}

MacroBase::Status CvLoadImages::onExit() {
  return Ok;
}
