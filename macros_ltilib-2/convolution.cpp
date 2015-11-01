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
#include "convolution.h"
#include "ltiChannel8.h"
#include "ltiChannel.h"
#include "ltiGradientKernels.h"
#include "ltiOgdKernels.h"
#include "ltiGaussKernels.h"

Convolution::Convolution() : MacroBase() {
  // set up macro description
  setName(L"lti::convolution");
  setCreator(L"Lars Libuda");
  setGroup(L"Image Processing");
  setDescription(L"Convolves a channel with the selected kernel");
  setPropertyWidgetComponent(L"PropertyWidgetConvolution.qml");
  addInput<lti::channel>(L"Input channel",L"Floating point gray scale image to be convolved");
  addOutput<lti::channel>(L"Output channel",L"Floating point gray scale image holding the convolution result");
  addParameter<int>(L"Kernel",L"Select the desired kernel type for convolution operation",0,L"IntComboBox",
                    L"{ \"items\": [\"lti::andoKernelX\",\"lti::andoKernelY\",\"lti::gaussKernel2D\","
                                  L"\"lti::harrisKernelX\",\"lti::harrisKernelY\",\"lti::kirschKernelX\",\"lti::kirschKernelY\","
                                  L"\"lti::ogd1Kernel\",\"lti::odg2Kernel\",\"lti::prewittKernelX\",\"lti::prewittKernelY\","
                                  L"\"lti::robinsonKernelX\",\"lti::robinsonKernelY\",\"lti::sobelKernelX\",\"lti::sobelKernelY\"] }");
  addParameter<int>(L"Kernel size",L"Size of kernel",3,L"IntSpinBox",L"{ \"minValue\": 3, \"maxValue\": 15 }");
  addParameter<float>(L"Kernel variance",L"Variance of kernel",1.3f,L"RealSpinBox",L"{ \"minValue\": 1.0, \"maxValue\": 150.0 }");
  addParameter<bool>(L"Normalize",L"Normalize result of convolution",true,L"BoolComboBox");
}

Convolution::~Convolution() {
}

MacroBase::Status Convolution::onInit() {
  const lti::channel* input = accessInput<lti::channel>(0);
  if (input == 0) {
    setErrorMsg(L"Input is not connected.");
    return Error;
  }
  return Ok;
}

MacroBase::Status Convolution::onApply() {

  const lti::channel* input = accessInput<lti::channel>(0);
  lti::channel& output = accessOutput<lti::channel>(0);
  if (convolveFunctor.apply(*input,output)) {
    return Ok;
  }
  else {
    setErrorMsg(L"lti::convolution failed.");
    return Error;
  }
}

void Convolution::onParametersChanged(ParameterSet &) {
  int kernelIndex = getParameterValue<int>(0);
  switch(kernelIndex) {
    case 0: {
      int size = getParameterValue<int>(1);
      if (size > 5) {
        size = 5;
        setParameterValue<int>(1,size);
      }
      else if (size < 3) {
        size = 3;
        setParameterValue<int>(1,size);
      }
      lti::andoKernelX<lti::channel::value_type> kernel(size);
      convolveFunctor.setKernel(kernel);
      break;
    }
    case 1: {
      int size = getParameterValue<int>(1);
      if (size > 5) {
        size = 5;
        setParameterValue<int>(1,size);
      }
      else if (size < 3) {
        size = 3;
        setParameterValue<int>(1,size);
      }
      lti::andoKernelY<lti::channel::value_type> kernel(size);
      convolveFunctor.setKernel(kernel);
      break;
    }
    case 2: {
      int size = getParameterValue<int>(1);
      float variance = getParameterValue<float>(2);
      lti::gaussKernel2D<lti::channel::value_type> kernel(size,variance);
      convolveFunctor.setKernel(kernel);
      break;
    }
    case 3: {
      lti::harrisKernelX<lti::channel::value_type> kernel;
      convolveFunctor.setKernel(kernel);
      break;
    }
    case 4: {
      lti::harrisKernelY<lti::channel::value_type> kernel;
      convolveFunctor.setKernel(kernel);
      break;
    }
    case 5: {
      lti::kirschKernelX<lti::channel::value_type> kernel;
      convolveFunctor.setKernel(kernel);
      break;
    }
    case 6: {
      lti::kirschKernelY<lti::channel::value_type> kernel;
      convolveFunctor.setKernel(kernel);
      break;
    }
    case 7: {
      int size = getParameterValue<int>(1);
      lti::ogd1Kernel<lti::channel::value_type> kernel(size);
      convolveFunctor.setKernel(kernel);
      break;
    }
    case 8: {
      int size = getParameterValue<int>(1);
      // Should lti::ogd2Kernel but this does not compile
      lti::ogd1Kernel<lti::channel::value_type> kernel(size);
      convolveFunctor.setKernel(kernel);
      break;
    }
    case 9: {
      bool normalize = getParameterValue<bool>(3);
      lti::prewittKernelX<lti::channel::value_type> kernel(normalize);
      convolveFunctor.setKernel(kernel);
      break;
    }
    case 10: {
      bool normalize = getParameterValue<bool>(3);
      lti::prewittKernelY<lti::channel::value_type> kernel(normalize);
      convolveFunctor.setKernel(kernel);
      break;
    }
    case 11: {
      lti::robinsonKernelX<lti::channel::value_type> kernel;
      convolveFunctor.setKernel(kernel);
      break;
    }
    case 12: {
      lti::robinsonKernelY<lti::channel::value_type> kernel;
      convolveFunctor.setKernel(kernel);
      break;
    }
    case 13: {
      bool normalize = getParameterValue<bool>(3);
      lti::sobelKernelX<lti::channel::value_type> kernel(normalize);
      convolveFunctor.setKernel(kernel);
      break;
    }
    case 14: {
      bool normalize = getParameterValue<bool>(3);
      lti::sobelKernelY<lti::channel::value_type> kernel(normalize);
      convolveFunctor.setKernel(kernel);
      break;
    }
  }
}

