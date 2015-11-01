/****************************************************************************************************
**   Impresario Library Conversion_ltilib-2_opencv-3
**   This file is part of the Impresario Library Conversion_ltilib-2_opencv-3.
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
#include "cvmat2ltiimage.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv/cv.h>
#include "ltiImage.h"

Channel8ToChannel::Channel8ToChannel() : MacroBase() {
  // set up macro description
  setName(L"cv::Mat_to_lti::image");
  setCreator(L"Lars Libuda");
  setGroup(L"Conversion");
  setDescription(L"Convert a cv::Mat image representation to an lti::image representation.");
  addInput<cv::Mat>(L"OpenCV image",L"cv::Mat to be converted");
  addOutput<lti::image>(L"LTILib image",L"lti::image containing conversion result");
}

Channel8ToChannel::~Channel8ToChannel() {
}

MacroBase::Status Channel8ToChannel::onInit() {
  const cv::Mat* input = accessInput<cv::Mat>(0);
  if (!input) {
    setErrorMsg(L"No input image connected.");
    return Error;
  }
  else {
    return Ok;
  }
}

MacroBase::Status Channel8ToChannel::onApply() {
  const cv::Mat* input = accessInput<cv::Mat>(0);
  lti::image& output = accessOutput<lti::image>(0);
  output.resize(input->rows,input->cols);
  if (input->type() == CV_8UC3) {
    typedef cv::Vec<uchar, 3> VT;
    cv::MatConstIterator_<VT> it1 = input->begin<VT>(), it1_end = input->end<VT>();
    lti::image::iterator dst_it = output.begin();
    for( ; it1 != it1_end; ++it1, ++dst_it ) {
      VT pixel = *it1;
      *dst_it = lti::rgbaPixel(pixel[2],pixel[1],pixel[0]);
    }
    return Ok;
  }
  else {
    setErrorMsg(L"Type of input is not yet supported. Only type CV_8UC3 currently works.");
    return Error;
  }
}

MacroBase::Status Channel8ToChannel::onExit() {
  return Ok;
}
