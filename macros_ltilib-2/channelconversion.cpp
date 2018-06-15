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
#include "channelconversion.h"
#include "ltiChannel8.h"
#include "ltiChannel.h"

Channel8ToChannel::Channel8ToChannel() : MacroBase() {
  // set up macro description
  setName(L"lti::channel8_to_lti::channel");
  setCreator(L"Lars Libuda");
  setGroup(L"Conversion");
  setDescription(L"Convert an lti::channel8 gray scale image representation to an lti::channel gray scale image representation.");
  addInput<lti::channel8>(L"8-bit gray scale image",L"8-bit gray scale image to be converted");
  addOutput<lti::channel>(L"Floating point gray scale image",L"Floating point gray scale image containing conversion result");
}

Channel8ToChannel::~Channel8ToChannel() {
}

MacroBase::Status Channel8ToChannel::onInit() {
  const lti::channel8* input = accessInput<lti::channel8>(0);
  if (!input) {
    setErrorMsg(L"No input channel connected.");
    return Error;
  }
  else {
    return Ok;
  }
}

MacroBase::Status Channel8ToChannel::onApply() {
  const lti::channel8* input = accessInput<lti::channel8>(0);
  lti::channel& output = accessOutput<lti::channel>(0);
  output.castFrom(*input);
  return Ok;
}

MacroBase::Status Channel8ToChannel::onExit() {
  return Ok;
}


ChannelToChannel8::ChannelToChannel8() : MacroBase() {
  // set up macro description
  setName(L"lti::channel_to_lti::channel8");
  setCreator(L"Lars Libuda");
  setGroup(L"Conversion");
  setDescription(L"Convert an lti::channel gray scale image representation to an lti::channel8 gray scale image representation.");
  addInput<lti::channel>(L"Floating point gray scale image",L"Floating point gray scale image to be converted");
  addOutput<lti::channel8>(L"8-bit gray scale image",L"8-bit gray scale image containing conversion result");
  addParameter<bool>(L"Scale",L"Map minimum to black and maximum to white",true,L"BoolComboBox");
}

ChannelToChannel8::~ChannelToChannel8() {
}

MacroBase::Status ChannelToChannel8::onInit() {
  const lti::channel* input = accessInput<lti::channel>(0);
  if (!input) {
    setErrorMsg(L"No input channel connected.");
    return Error;
  }
  else {
    return Ok;
  }
}

MacroBase::Status ChannelToChannel8::onApply() {
  const lti::channel* input = accessInput<lti::channel>(0);
  lti::channel8& output = accessOutput<lti::channel8>(0);
  bool scale = getParameterValue<bool>(0);
  output.castFrom(*input,scale,scale);
  return Ok;
}

MacroBase::Status ChannelToChannel8::onExit() {
  return Ok;
}
