/****************************************************************************************************
**   Impresario Library ImageProcessing_ltilib-2
**   This file is part of the Impresario Library ImageProcessing_ltilib-2.
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
#include "loadimages.h"
#include <opencv/cv.h>
#include "opencv2/imgcodecs.hpp"
#include <iostream>
#include <regex>

#ifndef INCLUDE_STD_FILESYSTEM_EXPERIMENTAL // We haven't checked which filesystem to include yet
  #if defined(__cpp_lib_filesystem) // Check for feature test macro for <filesystem>
    #define INCLUDE_STD_FILESYSTEM_EXPERIMENTAL 0
  #elif defined(__cpp_lib_experimental_filesystem) // Check for feature test macro for <experimental/filesystem>
    #define INCLUDE_STD_FILESYSTEM_EXPERIMENTAL 1
  #elif !defined(__has_include) // We can't check if headers exist... Let's assume experimental to be safe
    #define INCLUDE_STD_FILESYSTEM_EXPERIMENTAL 1
  #elif __has_include(<filesystem>) // Check if the header "<filesystem>" exists
    #ifdef _MSC_VER // If we're compiling on Visual Studio and are not compiling with C++17, we need to use experimental
      #if defined(_HAS_CXX17) && _HAS_CXX17 // Check for enabled C++17 support
        #define INCLUDE_STD_FILESYSTEM_EXPERIMENTAL 0 // We're using C++17, so let's use the normal version
      #endif
      #ifndef INCLUDE_STD_FILESYSTEM_EXPERIMENTAL // If the marco isn't defined yet, that means any of the other VS specific checks failed, so we need to use experimental
        #define INCLUDE_STD_FILESYSTEM_EXPERIMENTAL 1
      #endif
    #else // Not on Visual Studio. Let's use the normal version
      #define INCLUDE_STD_FILESYSTEM_EXPERIMENTAL 0
    #endif
  #elif __has_include(<experimental/filesystem>) // Check if the header "<experimental/filesystem>" exists
    #define INCLUDE_STD_FILESYSTEM_EXPERIMENTAL 1
  #else // Fail if neither header is available with a nice error message
    #error Could not find system header "<filesystem>" or "<experimental/filesystem>"
  #endif
  #if INCLUDE_STD_FILESYSTEM_EXPERIMENTAL // We priously determined that we need the exprimental version
    #include <experimental/filesystem>
    namespace fs = std::experimental::filesystem;
  #else // We have a decent compiler and can use the normal version
    #include <filesystem>
    namespace fs = std::filesystem;
  #endif
#endif // #ifndef INCLUDE_STD_FILESYSTEM_EXPERIMENTAL

CvLoadImages::CvLoadImages() : MacroBase{}, fileIndex{0} {
  // set up macro description
  setName(L"cv::loadImages");
  setCreator(L"Lars Libuda");
  setGroup(L"Image Sources");
  setDescription(L"Loads images from a given directory in alphabetical order");
  addOutput<cv::Mat>(L"Image",L"Image currently loaded");
  addOutput<char *>(L"Image path",L"Full path of the currently loaded image");
  addParameter<std::string>(L"Source directory",L"Directory where to load images from","",L"StringDirSelector");
  addParameter<std::string>(L"File pattern",L"Regular expression for matching file names (including suffix) found in source directory",".*\\.(jpg|png)",L"StringLineEdit");
  addParameter<bool>(L"Repeat",L"Starts loading images from beginning when end was reached.",false,L"BoolComboBox");
  addParameter<std::string>(L"Current File",L"Current loaded image (read-only)","",L"StringLineEdit",L"{ \"readOnly\": true }");
}

MacroBase::Status CvLoadImages::onInit() {
  fileList.clear();
  const auto& directory = getParameterValue<std::string>(0);
  const auto& pattern = getParameterValue<std::string>(1);
  if (directory.empty()) {
    setErrorMsg(L"No directory specified in parameters.");
    return Error;
  }
  fs::path p(directory);
  try  {
    if (!fs::exists(p)) {
      std::basic_ostringstream<wchar_t> errorMsg;
      errorMsg << L"Given path '" << directory.c_str() << L"' does not exist.";
      setErrorMsg(errorMsg.str());
      return Error;
    }
    if (!fs::is_directory(p)) {
      std::basic_ostringstream<wchar_t> errorMsg;
      errorMsg << L"Given path '" << directory.c_str() << L"' is not a valid directory.";
      setErrorMsg(errorMsg.str());
      return Error;
    }
    const std::regex filter(pattern, std::regex_constants::icase);

    for (const fs::directory_entry& x : fs::directory_iterator(p)) {
      if (fs::is_regular_file(x.path()) && std::regex_match(x.path().filename().string(),filter)) {
        fileList.push_back(x.path().generic_string());
      }
    }
  }
  catch (const fs::filesystem_error& ex) {
    std::basic_ostringstream<wchar_t> errorMsg;
    errorMsg << L"Error while accessing file system: " << ex.what();
    setErrorMsg(errorMsg.str());
    return Error;
  }
  catch (const std::regex_error& ex) {
    std::basic_ostringstream<wchar_t> errorMsg;
    errorMsg << L"Error in regular expression for parameter 'File pattern': " << ex.what();
    setErrorMsg(errorMsg.str());
    return Error;
  }
  if (fileList.empty()) {
    std::basic_ostringstream<wchar_t> errorMsg;
    errorMsg << L"Given directory '" << directory.c_str() << L"' does not contain any files matching pattern '" << pattern.c_str() << "'.";
    setErrorMsg(errorMsg.str());
    return Error;
  }
  if (fileIndex >= fileList.size()) fileIndex = 0;
  return Ok;
}

MacroBase::Status CvLoadImages::onApply() {
  auto& output = accessOutput<cv::Mat>(0);
  auto& filename = accessOutput<char*>(1);
  if (fileIndex < fileList.size()) {
    filename = const_cast<char*>(fileList[fileIndex].c_str());
    setParameterValue<std::string>(3,std::string(fileList[fileIndex]));
    output = cv::imread(cv::String(fileList[fileIndex]), cv::IMREAD_COLOR);
    if (output.empty()) {
      std::basic_ostringstream<wchar_t> errorMsg;
      errorMsg << L"Failed to load file '" << fileList[fileIndex].c_str() << L"'.";
      setErrorMsg(errorMsg.str());
      fileIndex = 0;
      return Error;
    }
    fileIndex++;
    if (fileIndex >= fileList.size()) {
      auto repeat = getParameterValue<bool>(2);
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
