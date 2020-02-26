#****************************************************************************************************
#   Impresario Library Conversion_ltilib-2_opencv-3
#   This file is part of the Impresario Library Conversion_ltilib-2_opencv-3.
#
#   Copyright (C) 2015-2018  Lars Libuda
#   All rights reserved.
#
#   Redistribution and use in source and binary forms, with or without
#   modification, are permitted provided that the following conditions are met:
#       * Redistributions of source code must retain the above copyright
#         notice, this list of conditions and the following disclaimer.
#       * Redistributions in binary form must reproduce the above copyright
#         notice, this list of conditions and the following disclaimer in the
#         documentation and/or other materials provided with the distribution.
#       * Neither the name of the copyright holder nor the
#         names of its contributors may be used to endorse or promote products
#         derived from this software without specific prior written permission.
#
#   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
#   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
#   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
#   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
#   DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
#   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
#   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
#   ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
#   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#****************************************************************************************************/
TEMPLATE = lib
CONFIG += c++11
CONFIG += shared
CONFIG -= app_bundle
CONFIG -= qt

VERSION = 1.1.0
DESTDIR = ../lib

TARGET = conversion_ltilib-2_opencv-3
win32: TARGET = $${TARGET}_$${VERSION}

include(../target_def.pri)

win32 {
  CONFIG += skip_target_version_ext
  DEFINES += _IMPRESARIO_WIN

  INCLUDEPATH += $$quote(../../ltilib-2/ltilib-2/src/basics)
  INCLUDEPATH += $$quote(../../ltilib-2/ltilib-2/src/classifiers)
  INCLUDEPATH += $$quote(../../ltilib-2/ltilib-2/src/draw)
  INCLUDEPATH += $$quote(../../ltilib-2/ltilib-2/src/imgProc)
  INCLUDEPATH += $$quote(../../ltilib-2/ltilib-2/src/io)
  INCLUDEPATH += $$quote(../../ltilib-2/ltilib-2/src/ioBasics)
  INCLUDEPATH += $$quote(../../ltilib-2/ltilib-2/src/math)
  INCLUDEPATH += $$quote(../../ltilib-2/ltilib-2/src/system)
  INCLUDEPATH += $$quote(../../ltilib-2/ltilib-2/src/types)
  INCLUDEPATH += $$quote(../../ltilib-2/ltilib-2/src/viewer)
  INCLUDEPATH += $$quote(../../opencv-3.4.1/build/include)

  LIBS += $$quote(-L../../../ltilib-2-build/lib) -lltilib-2_$${BUILD_POSTFIX}

  # check support for open-cv
  OPENCV_BASE_PATH = "../../opencv-3.4.1/build"
  OPENCV_LIB_PATH =
  if(win32-msvc*) {
    contains(QT_ARCH, i386) {
      OPENCV_LIB_PATH = $${OPENCV_BASE_PATH}/x32/vc$${section(MSVC_VER,.,0,0)}/lib
    }
    else {
      OPENCV_LIB_PATH = $${OPENCV_BASE_PATH}/x64/vc$${section(MSVC_VER,.,0,0)}/lib
    }
  }
  OPENCV_LIB = opencv_world341
  CONFIG(debug, release|debug):OPENCV_LIB = $${OPENCV_LIB}d
  !exists($${OPENCV_LIB_PATH}/$${OPENCV_LIB}.lib) {
    error(Current Kit is not supported by OpenCV-3. Library $${OPENCV_LIB_PATH}/$${OPENCV_LIB}.lib does not exist.)
  }

  INCLUDEPATH += $$quote($${OPENCV_BASE_PATH}/include)
  LIBS += $$quote(-L../$${OPENCV_LIB_PATH}) -l$${OPENCV_LIB}
}

unix {
  QMAKE_LN_SHLIB = :
  DEFINES += _IMPRESARIO_LINUX

  INCLUDEPATH += $$quote(../../ltilib-2/src/basics)
  INCLUDEPATH += $$quote(../../ltilib-2/src/classifiers)
  INCLUDEPATH += $$quote(../../ltilib-2/src/draw)
  INCLUDEPATH += $$quote(../../ltilib-2/src/imgProc)
  INCLUDEPATH += $$quote(../../ltilib-2/src/io)
  INCLUDEPATH += $$quote(../../ltilib-2/src/ioBasics)
  INCLUDEPATH += $$quote(../../ltilib-2/src/math)
  INCLUDEPATH += $$quote(../../ltilib-2/src/system)
  INCLUDEPATH += $$quote(../../ltilib-2/src/types)
  INCLUDEPATH += $$quote(../../ltilib-2/src/viewer)

  INCLUDEPATH += $$quote(../../opencv-3.4.1-build)
  INCLUDEPATH += $$quote(../../opencv-3.4.1/include)
  INCLUDEPATH += $$quote(../../opencv-3.4.1/modules/core/include)
  INCLUDEPATH += $$quote(../../opencv-3.4.1/modules/imgproc/include)
  INCLUDEPATH += $$quote(../../opencv-3.4.1/modules/photo/include)
  INCLUDEPATH += $$quote(../../opencv-3.4.1/modules/video/include)
  INCLUDEPATH += $$quote(../../opencv-3.4.1/modules/features2d/include)
  INCLUDEPATH += $$quote(../../opencv-3.4.1/modules/flann/include)
  INCLUDEPATH += $$quote(../../opencv-3.4.1/modules/objdetect/include)
  INCLUDEPATH += $$quote(../../opencv-3.4.1/modules/calib3d/include)
  INCLUDEPATH += $$quote(../../opencv-3.4.1/modules/imgcodecs/include)
  INCLUDEPATH += $$quote(../../opencv-3.4.1/modules/videoio/include)
  INCLUDEPATH += $$quote(../../opencv-3.4.1/modules/highgui/include)
  INCLUDEPATH += $$quote(../../opencv-3.4.1/modules/ml/include)
  INCLUDEPATH += $$quote(../../opencv-3.4.1/modules/hal/include)

  CONFIG(release, release|debug) {
    LIBS += $$quote(-L../../../ltilib-2/lib) -lltir
    LIBS += $$quote(-L../../../opencv-3.4.1-build/lib) -lopencv_core #-lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_videoio
  }

  CONFIG(debug, release|debug) {
    LIBS += $$quote(-L../../../ltilib-2/lib) -lltid
    LIBS += $$quote(-L../../../opencv-3.4.1-build/lib) -lopencv_core #-lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_videoio
  }
}

CONFIG(debug, release|debug):DEFINES += _IMPRESARIO_DEBUG

SOURCES += \
    libinterface.cpp \
    cvmat2ltiimage.cpp

HEADERS += \
    libconfig.h \
    libinterface.h \
    macrobase.h \
    cvmat2ltiimage.h

