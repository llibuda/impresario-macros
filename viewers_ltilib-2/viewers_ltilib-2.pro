#****************************************************************************************************
#   Impresario Library Viewers_ltilib-2
#   This file is part of the Impresario Library Viewers_ltilib-2.
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
CONFIG += c++11
QT += core widgets gui

VERSION = 1.0.2
DESTDIR = ../lib

TARGET = viewers-ltilib-2
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

  LIBS += $$quote(-L../../../ltilib-2-build/lib) -lltilib-2_$${BUILD_POSTFIX}
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

  CONFIG(release, release|debug) {
    LIBS += $$quote(-L../../../ltilib-2/lib) -lltir
  }
  CONFIG(debug, release|debug) {
    LIBS += $$quote(-L../../../ltilib-2/lib) -lltid
  }
}

CONFIG(debug, release|debug):DEFINES += _IMPRESARIO_DEBUG

SOURCES += \
    libinterface.cpp \
    viewerimage.cpp \
    widgetimage.cpp \
    paintwidget.cpp

HEADERS += \
    libinterface.h \
    macrobase.h \
    libconfig.h \
    viewerimage.h \
    widgetimage.h \
    macroextended.h \
    paintwidget.h

RESOURCES += \
    resources.qrc
