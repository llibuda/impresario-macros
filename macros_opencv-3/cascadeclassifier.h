/****************************************************************************************************
**   Impresario Library ImageProcessing_opencv-3
**   This file is part of the Impresario Library ImageProcessing_opencv-3.
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
#ifndef CASCADECLASSIFIER_H_
#define CASCADECLASSIFIER_H_

#include "macrobase.h"
#include <opencv/cv.h>
#include "opencv2/objdetect.hpp"
#include <vector>

class CvCascadeClassifier : public MacroBase {
public:
  // standard constructor
  CvCascadeClassifier(void);
  // standard destructor
  virtual ~CvCascadeClassifier(void);

  // override clone method to provide correct class instance
  virtual MacroBase* clone() const { return new CvCascadeClassifier(); }

  typedef std::vector<cv::Rect> RegionsOfInterest;

protected:
  virtual Status onInit();
  virtual Status onApply();
  virtual Status onExit();
  virtual void onParametersChanged(ParameterSet&);

private:
  Status createAndLoadClassifier(const std::string& fileName);

  cv::CascadeClassifier* classifier;
};

#endif /* CASCADECLASSIFIER_H_ */