TEMPLATE = lib
CONFIG -= app_bundle
CONFIG -= qt

win32 {
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

  CONFIG += dll
  DEFINES += _IMPRESARIO_WIN
  DESTDIR = ../lib
  CONFIG(release, release|debug) {
    if(win32-g++*) {
      LIBS += $$quote(-L../../../ltilib-2-build/MinGW_32bit-Release/lib) -lltilib-2_mingw
      TARGET = imgproc_ltilib-2_mingw
    }
    if(win32-msvc*) {
      LIBS += $$quote(-L../../../ltilib-2-build/MSVC2012_32bit-Release/lib) -lltilib-2_msvc
      TARGET = imgproc_ltilib-2_msvc
    }
  }
  CONFIG(debug, release|debug) {
    DEFINES += _IMPRESARIO_DEBUG
    if(win32-g++*) {
      LIBS += $$quote(-L../../../ltilib-2-build/MinGW_32bit-Debug/lib) -lltilib-2d_mingw
      TARGET = imgproc_ltilib-2d_mingw
    }
    if(win32-msvc*) {
      LIBS += $$quote(-L../../../ltilib-2-build/MSVC2012_32bit-Debug/lib) -lltilib-2d_msvc
      TARGET = imgproc_ltilib-2d_msvc
    }
  }
}

unix {
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

  CONFIG += dll
  DEFINES += _IMPRESARIO_LINUX
  DESTDIR = ../lib
  CONFIG(release, release|debug) {
    LIBS += $$quote(-L../../../ltilib-2/lib) -lltir
    TARGET = imgproc_ltilib-2_gcc
  }

  CONFIG(debug, release|debug) {
    DEFINES += _IMPRESARIO_DEBUG
    LIBS += $$quote(-L../../../ltilib-2/lib) -lltid
    TARGET = imgproc_ltilib-2d_gcc
  }
}

HEADERS += \
    cannyedge.h \
    libinterface.h \
    macrobase.h \
    splitimagetoyuv.h \
    loadimages.h \
    splitimagetohsi.h \
    libconfig.h \
    convolution.h \
    channelconversion.h

SOURCES += \
    cannyedge.cpp \
    libinterface.cpp \
    splitimagetoyuv.cpp \
    loadimages.cpp \
    splitimagetohsi.cpp \
    convolution.cpp \
    channelconversion.cpp


