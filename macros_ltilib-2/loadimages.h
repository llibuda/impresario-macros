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
#ifndef LOADIMAGES_H_
#define LOADIMAGES_H_

#include "macrobase.h"
#include "ltiLoadImageList.h"

class CvVideoInput : public MacroBase {
public:
  // standard constructor
  CvVideoInput(void);
  // standard destructor
  virtual ~CvVideoInput(void);

  // override clone method to provide correct class instance
  virtual MacroBase* clone() const { return new CvVideoInput(); }

protected:
  virtual Status onInit();
  virtual Status onApply();
  virtual Status onExit();

private:
  lti::loadImageList loadFunctor;
};

#endif // LOADIMAGES_H_
