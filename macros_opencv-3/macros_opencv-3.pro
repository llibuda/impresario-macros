#****************************************************************************************************
#   Impresario Library ImageProcessing_opencv-3
#   This file is part of the Impresario Library ImageProcessing_opencv-3.
#
#   Copyright (C) 2015-2020  Lars Libuda
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
CONFIG += shared
CONFIG -= app_bundle
CONFIG -= qt
#CONFIG += c++17 # not yet supported by QMAKE

VERSION = 1.1.3
DESTDIR = ../lib

TARGET = imgproc_opencv-3
win32: TARGET = $${TARGET}_$${VERSION}

include(../target_def.pri)

win32 {
  CONFIG += skip_target_version_ext
  DEFINES += _IMPRESARIO_WIN

  # C++17 support for MSVC
  QMAKE_CXXFLAGS += -std:c++17

  # check support for open-cv
  OPENCV_BASE_PATH = "../../opencv-3.4.1"
  OPENCV_LIB_PATH = $${OPENCV_BASE_PATH}-build/lib
  OPENCV_LIB = opencv_world341
  CONFIG(debug, release|debug):OPENCV_LIB = $${OPENCV_LIB}d
  !exists($${OPENCV_LIB_PATH}/$${OPENCV_LIB}.lib) {
    error(Library $${OPENCV_LIB_PATH}/$${OPENCV_LIB}.lib does not exist.)
  }

  INCLUDEPATH += $$quote($${OPENCV_BASE_PATH}-build)
  INCLUDEPATH += $$quote($${OPENCV_BASE_PATH}/include)
  INCLUDEPATH += $$quote($${OPENCV_BASE_PATH}/modules/core/include)
  INCLUDEPATH += $$quote($${OPENCV_BASE_PATH}/modules/imgproc/include)
  INCLUDEPATH += $$quote($${OPENCV_BASE_PATH}/modules/photo/include)
  INCLUDEPATH += $$quote($${OPENCV_BASE_PATH}/modules/video/include)
  INCLUDEPATH += $$quote($${OPENCV_BASE_PATH}/modules/features2d/include)
  INCLUDEPATH += $$quote($${OPENCV_BASE_PATH}/modules/flann/include)
  INCLUDEPATH += $$quote($${OPENCV_BASE_PATH}/modules/objdetect/include)
  INCLUDEPATH += $$quote($${OPENCV_BASE_PATH}/modules/calib3d/include)
  INCLUDEPATH += $$quote($${OPENCV_BASE_PATH}/modules/imgcodecs/include)
  INCLUDEPATH += $$quote($${OPENCV_BASE_PATH}/modules/videoio/include)
  INCLUDEPATH += $$quote($${OPENCV_BASE_PATH}/modules/highgui/include)
  INCLUDEPATH += $$quote($${OPENCV_BASE_PATH}/modules/ml/include)
  INCLUDEPATH += $$quote($${OPENCV_BASE_PATH}/modules/hal/include)

  LIBS += $$quote(-L../$${OPENCV_LIB_PATH}) -l$${OPENCV_LIB}
}

unix {
  # C++17 support for GCC
  QMAKE_CXXFLAGS += -std=c++17
  LIBS += -lstdc++fs

  QMAKE_LN_SHLIB = :
  DEFINES += _IMPRESARIO_LINUX

  OPENCV_BASE_PATH = "../../opencv-3.4.1"
  OPENCV_LIB_PATH = $${OPENCV_BASE_PATH}-build/lib

  INCLUDEPATH += $$quote($${OPENCV_BASE_PATH}-build)
  INCLUDEPATH += $$quote($${OPENCV_BASE_PATH}/include)
  INCLUDEPATH += $$quote($${OPENCV_BASE_PATH}/modules/core/include)
  INCLUDEPATH += $$quote($${OPENCV_BASE_PATH}/modules/imgproc/include)
  INCLUDEPATH += $$quote($${OPENCV_BASE_PATH}/modules/photo/include)
  INCLUDEPATH += $$quote($${OPENCV_BASE_PATH}/modules/video/include)
  INCLUDEPATH += $$quote($${OPENCV_BASE_PATH}/modules/features2d/include)
  INCLUDEPATH += $$quote($${OPENCV_BASE_PATH}/modules/flann/include)
  INCLUDEPATH += $$quote($${OPENCV_BASE_PATH}/modules/objdetect/include)
  INCLUDEPATH += $$quote($${OPENCV_BASE_PATH}/modules/calib3d/include)
  INCLUDEPATH += $$quote($${OPENCV_BASE_PATH}/modules/imgcodecs/include)
  INCLUDEPATH += $$quote($${OPENCV_BASE_PATH}/modules/videoio/include)
  INCLUDEPATH += $$quote($${OPENCV_BASE_PATH}/modules/highgui/include)
  INCLUDEPATH += $$quote($${OPENCV_BASE_PATH}/modules/ml/include)
  INCLUDEPATH += $$quote($${OPENCV_BASE_PATH}/modules/hal/include)

  LIBS += $$quote(-L../$${OPENCV_LIB_PATH}) -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -lopencv_videoio -lopencv_objdetect
}

CONFIG(debug, release|debug):DEFINES += _IMPRESARIO_DEBUG

SOURCES += \
    libinterface.cpp \
    videoinput.cpp \
    camerainput.cpp \
    cvtcolor.cpp \
    cvmatconvert.cpp \
    cannyedge.cpp \
    cascadeclassifier.cpp \
    loadimages.cpp

HEADERS +=\
    libconfig.h \
    libinterface.h \
    macrobase.h \
    videoinput.h \
    camerainput.h \
    cvtcolor.h \
    cvmatconvert.h \
    cannyedge.h \
    cascadeclassifier.h \
    loadimages.h
