/****************************************************************************************************
**   Impresario Interface - Image Processing Engineering System applying Reusable Interactive Objects
**   This file is part of the Impresario Interface.
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
#ifndef LIBCONFIG_H_
#define LIBCONFIG_H_
#include "libinterface.h"

#define LIB_CREATOR        L"Lars Libuda"
#define LIB_NAME           L"Viewers_ltilib-2"
#define LIB_VERSION_MAJOR  1
#define LIB_VERSION_MINOR  0
#define LIB_VERSION_PATCH  1
#define LIB_DESCRIPTION    L"<html><body>"\
  L"<p><b>Library with viewers for main types of ltilib-2.</b></p>"\
  L"<p>Copyright (C) 2015-2020  Lars Libuda</p>"\
  L"<p>All rights reserved.</p>"\
  L"<p>"\
  L"Redistribution and use in source and binary forms, with or without" \
  L"modification, are permitted provided that the following conditions are met:" \
  L"</p><ul>" \
  L"<li> Redistributions of source code must retain the above copyright" \
  L"     notice, this list of conditions and the following disclaimer.</li>" \
  L"<li> Redistributions in binary form must reproduce the above copyright" \
  L"     notice, this list of conditions and the following disclaimer in the" \
  L"     documentation and/or other materials provided with the distribution.</li>" \
  L"<li> Neither the name of the copyright holder nor the" \
  L"     names of its contributors may be used to endorse or promote products" \
  L"     derived from this software without specific prior written permission.</li>" \
  L"</ul><p>" \
  L"THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \"AS IS\" AND" \
  L"ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED" \
  L"WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE" \
  L"DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY" \
  L"DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES" \
  L"(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;" \
  L"LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND" \
  L"ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT" \
  L"(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS" \
  L"SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."\
  L"</p>"\
  L"</body></html>"

#include "viewerimage.h"

MACRO_REGISTRATION_BEGIN
  MACRO_ADD(ViewerImage)
MACRO_REGISTRATION_END

#endif // LIBCONFIG_H_
