/****************************************************************************************************
**   Impresario Library Viewers_BasicTypes
**   This file is part of the Impresario Library Viewers_BasicTypes.
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
#include "viewerbasetypes.h"
#include <string>

ViewerBaseTypes::ViewerBaseTypes() : ViewerBase() {
  setName(L"Base type viewer");
  setDescription(L"Displays values of base types");
  setCreator(L"Lars Libuda");
  setGroup(L"Viewers");
  addInput<int>(L"Integer value",L"int value to display");
  addInput<bool>(L"Boolean value",L"bool value to display");
  addInput<char*>(L"String value (C)",L"string to display");
  addInput<float>(L"Float value",L"float value to display");
  addInput<double>(L"Double value",L"double value to display");
}

MacroBase::Status ViewerBaseTypes::onInit() {
  return Ok;
}

MacroBase::Status ViewerBaseTypes::onApply() {
  const int* srcInt = accessInput<int>(0);
  const bool* srcBool = accessInput<bool>(1);
  const char* const* srcCString = accessInput<char*>(2);
  const float* srcFloat = accessInput<float>(3);
  const double* srcDouble = accessInput<double>(4);
  WidgetBaseTypes* widget = accessWidget();
  if (srcInt != 0) {
    widget->updateValue(srcInt);
  }
  else if (srcBool != 0) {
    widget->updateValue(srcBool);
  }
  else if (srcCString != 0) {
    widget->updateValue(srcCString);
  }
  else if (srcFloat != 0) {
    widget->updateValue(srcFloat);
  }
  else if (srcDouble != 0) {
    widget->updateValue(srcDouble);
  }
  return (srcInt != 0 || srcBool != 0 || srcCString != 0 ||
          srcFloat != 0 || srcDouble != 0) ? Ok : Error;
}

MacroBase::Status ViewerBaseTypes::onExit() {
  return Ok;
}

