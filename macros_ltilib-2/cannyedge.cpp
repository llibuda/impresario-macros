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
#include "cannyedge.h"
#include "ltiChannel8.h"

LtiCannyEdge::LtiCannyEdge(void) : MacroBase{} {
  // set up macro description
  setName(L"lti::cannyEdges");
  setCreator(L"Lars Libuda");
  setGroup(L"Image Processing");
  setDescription(L"Detects edges in a lti::channel8");
  addInput<lti::channel8>(L"Input image",L"8-bit grey scale image for edge detection");
  addOutput<lti::channel8>(L"Output image",L"8-bit grey scale image with detected edges");
  addParameter<int>(L"Edge Treshold",L"Value used to denote an edge pixel",255,L"IntSpinBox",L"{ \"minValue\": 0, \"maxValue\": 255 }");
  addParameter<int>(L"No Edge Treshold",L"Value used to denote a no-edge pixel",0,L"IntSpinBox",L"{ \"minValue\": 0, \"maxValue\": 255 }");
}

MacroBase::Status LtiCannyEdge::onInit() {
  const auto* input = accessInput<lti::channel8>(0);
  if (input == nullptr) {
    setErrorMsg(L"Input is not connected.");
    return Error;
  }
  return Ok;
}

MacroBase::Status LtiCannyEdge::onApply() {
  const auto* input = accessInput<lti::channel8>(0);
  auto& output = accessOutput<lti::channel8>(0);
  return (cannyFunctor.apply(*input,output)) ? Ok : Error;
}

void LtiCannyEdge::onParametersChanged(ParameterSet & paramSet) {
  for(unsigned int index : paramSet)
  {
    switch (index)
    {
      case 0:
        params.edgeValue = static_cast<lti::ubyte>(getParameterValue<int>(0));
        break;
      case 1:
        params.noEdgeValue = static_cast<lti::ubyte>(getParameterValue<int>(1));
        break;
    }
  }
  cannyFunctor.setParameters(params);
}

