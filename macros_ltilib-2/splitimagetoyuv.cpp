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
#include "splitimagetoyuv.h"
#include "ltiImage.h"
#include "ltiChannel8.h"

LtiSplitImageToYUV::LtiSplitImageToYUV() : MacroBase() {
  // set up macro description
  setName(L"lti::splitImageToYUV");
  setCreator(L"Lars Libuda");
  setGroup(L"Image Processing");
  setDescription(L"Splits a color image into its YUV components");
  addInput<lti::image>(L"Input image",L"color image to be split");
  addOutput<lti::channel8>(L"Y-component",L"8-bit grey scale image denoting the Y-component");
  addOutput<lti::channel8>(L"U-component",L"8-bit grey scale image denoting the U-component");
  addOutput<lti::channel8>(L"V-component",L"8-bit grey scale image denoting the V-component");
}

LtiSplitImageToYUV::~LtiSplitImageToYUV() {
}

MacroBase::Status LtiSplitImageToYUV::onInit() {
  const lti::image* input = accessInput<lti::image>(0);
  if (input == 0) {
    setErrorMsg(L"Input is not connected.");
    return Error;
  }
  return Ok;
}

MacroBase::Status LtiSplitImageToYUV::onApply() {
  const lti::image* input = accessInput<lti::image>(0);
  lti::channel8& outputY = accessOutput<lti::channel8>(0);
  lti::channel8& outputU = accessOutput<lti::channel8>(1);
  lti::channel8& outputV = accessOutput<lti::channel8>(2);
  return (splitFunctor.apply(*input,outputY,outputU,outputV)) ? Ok : Error;
}

