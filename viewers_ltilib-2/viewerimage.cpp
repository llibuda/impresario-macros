/****************************************************************************************************
**   Impresario Library Viewers_ltilib-2
**   This file is part of the Impresario Library Viewers_ltilib-2.
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
#include "viewerimage.h"
#include <QWidget>
#include <iostream>

ViewerImage::ViewerImage() : ViewerBase{} {
  setName(L"LTI-Lib-2 Image viewer");
  setDescription(L"Displays image types used in ltilib-2");
  setCreator(L"Lars Libuda");
  setGroup(L"Viewers");
  addInput<lti::image>(L"24 bit Color image",L"lti::image for rendering");
  addInput<lti::channel8>(L"8 bit Gray scale image",L"lti::channel8 for rendering");
  addInput<lti::channel>(L"Floating point gray scale image",L"lti::channel for rendering");
}

MacroBase::Status ViewerImage::onInit() {
  return Ok;
}

MacroBase::Status ViewerImage::onApply() {
  auto srcImg = accessInput<lti::image>(0);
  auto srcChannel8 = accessInput<lti::channel8>(1);
  auto srcChannel = accessInput<lti::channel>(2);
  auto widget = accessWidget();
  if (srcImg != nullptr) {
    widget->updateImage(srcImg);
  }
  else if (srcChannel8 != nullptr) {
    widget->updateImage(srcChannel8);
  }
  else if (srcChannel != nullptr) {
    widget->updateImage(srcChannel);
  }
  return (srcImg != nullptr || srcChannel8 != nullptr || srcChannel != nullptr) ? Ok : Error;
}

MacroBase::Status ViewerImage::onExit() {
  return Ok;
}
