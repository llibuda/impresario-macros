/****************************************************************************************************
**   Impresario Library ImageProcessing_ltilib-2
**   This file is part of the Impresario Library ImageProcessing_ltilib-2.
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
#include "loadimages.h"
#include "ltiImage.h"
#include <iostream>

CvVideoInput::CvVideoInput() : MacroBase() {
  // set up macro description
  setName(L"lti::loadImages");
  setCreator(L"Lars Libuda");
  setGroup(L"Image Sources");
  setDescription(L"Loads images from a given directory in alphabetical order");
  addOutput<lti::image>(L"Image",L"Color image currently loaded");
  addOutput<char *>(L"Image path",L"Full path of the currently loaded image");
  addParameter<std::string>(L"Source directory",L"Directory where to load images from","",L"StringDirSelector");
  addParameter<bool>(L"Repeat",L"Starts loading images from beginning when end was reached.",false,L"BoolComboBox");
  addParameter<std::string>(L"Current File",L"Current loaded image","",L"StringFileSelector");
}

CvVideoInput::~CvVideoInput() {
}

MacroBase::Status CvVideoInput::onInit() {
  const std::string& directory = getParameterValue<std::string>(0);
  if (directory.empty()) {
    setErrorMsg(L"No directory specified in parameters.");
    return Error;
  }
  if (!loadFunctor.useDirectory(directory)) {
    std::basic_ostringstream<wchar_t> errorMsg;
    errorMsg << L"Directory '" << directory.c_str() << L"' does not exist.";
    setErrorMsg(errorMsg.str());
    return Error;
  }
  if (!loadFunctor.hasNext()) {
    setErrorMsg(L"Directory does not contain valid images.");
    return Error;
  }
  return Ok;
}

MacroBase::Status CvVideoInput::onApply() {
  lti::image& output = accessOutput<lti::image>(0);
  char* & filename = accessOutput<char*>(1);
  if (loadFunctor.hasNext()) {
    filename = const_cast<char*>(loadFunctor.getNextFilename().c_str());
    setParameterValue<std::string>(2,std::string(filename));
    if (!loadFunctor.load(output)) {
      std::basic_ostringstream<wchar_t> errorMsg;
      errorMsg << L"Failed to load image '" << filename << L"'.";
      setErrorMsg(errorMsg.str());
      return Error;
    }
    else {
      return Ok;
    }
  }
  else {
    const bool& repeat = getParameterValue<bool>(1);
    if (repeat)
    {
      loadFunctor.rewind();
      return Ok;
    }
    else
    {
      return Stop;
    }
  }
}

MacroBase::Status CvVideoInput::onExit() {
  return Ok;
}
