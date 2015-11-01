#-------------------------------------------------
#
# Project created by QtCreator 2015-02-16T20:17:06
#
#-------------------------------------------------

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
  INCLUDEPATH += $$quote(../../opencv-3.0.0-beta/build/include)

  CONFIG += dll
  DEFINES += _IMPRESARIO_WIN
  DESTDIR = ../lib
  CONFIG(release, release|debug) {
    if(win32-g++*) {
      LIBS += $$quote(-L../../../ltilib-2-build/MinGW_32bit-Release/lib) -lltilib-2_mingw
      LIBS += $$quote(-L../../../opencv-3.0.0-beta/build/x86/vc11/lib) -lopencv_world300
      TARGET = conversion_ltilib-2_opencv-3_mingw
    }
    if(win32-msvc*) {
      LIBS += $$quote(-L../../../ltilib-2-build/MSVC2012_32bit-Release/lib) -lltilib-2_msvc
      LIBS += $$quote(-L../../../opencv-3.0.0-beta/build/x86/vc11/lib) -lopencv_world300
      TARGET = conversion_ltilib-2_opencv-3_msvc
    }
  }
  CONFIG(debug, release|debug) {
    DEFINES += _IMPRESARIO_DEBUG
    if(win32-g++*) {
      LIBS += $$quote(-L../../../ltilib-2-build/MinGW_32bit-Debug/lib) -lltilib-2d_mingw
      LIBS += $$quote(-L../../../opencv-3.0.0-beta/build/x86/vc11/lib) -lopencv_world300d
      TARGET = conversion_ltilib-2_opencv-3d_mingw
    }
    if(win32-msvc*) {
      LIBS += $$quote(-L../../../ltilib-2-build/MSVC2012_32bit-Debug/lib) -lltilib-2d_msvc
      LIBS += $$quote(-L../../../opencv-3.0.0-beta/build/x86/vc11/lib) -lopencv_world300d
      TARGET = conversion_ltilib-2_opencv-3d_msvc
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
  INCLUDEPATH += $$quote(../../opencv-3.0.0-beta/include)
  INCLUDEPATH += $$quote(../../opencv-3.0.0-beta/modules/core/include)
  INCLUDEPATH += $$quote(../../opencv-3.0.0-beta/modules/imgproc/include)
  INCLUDEPATH += $$quote(../../opencv-3.0.0-beta/modules/photo/include)
  INCLUDEPATH += $$quote(../../opencv-3.0.0-beta/modules/video/include)
  INCLUDEPATH += $$quote(../../opencv-3.0.0-beta/modules/features2d/include)
  INCLUDEPATH += $$quote(../../opencv-3.0.0-beta/modules/flann/include)
  INCLUDEPATH += $$quote(../../opencv-3.0.0-beta/modules/objdetect/include)
  INCLUDEPATH += $$quote(../../opencv-3.0.0-beta/modules/calib3d/include)
  INCLUDEPATH += $$quote(../../opencv-3.0.0-beta/modules/imgcodecs/include)
  INCLUDEPATH += $$quote(../../opencv-3.0.0-beta/modules/videoio/include)
  INCLUDEPATH += $$quote(../../opencv-3.0.0-beta/modules/highgui/include)
  INCLUDEPATH += $$quote(../../opencv-3.0.0-beta/modules/ml/include)

  CONFIG += dll
  DEFINES += _IMPRESARIO_LINUX
  DESTDIR = ../lib
  CONFIG(release, release|debug) {
    LIBS += $$quote(-L../../../ltilib-2/lib) -lltir
    LIBS += $$quote(-L../../../opencv-3.0.0-beta/lib) -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_videoio
    TARGET = conversion_ltilib-2_opencv-3_gcc
  }

  CONFIG(debug, release|debug) {
    DEFINES += _IMPRESARIO_DEBUG
    LIBS += $$quote(-L../../../ltilib-2/lib) -lltid
    LIBS += $$quote(-L../../../opencv-3.0.0-beta/lib) -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_videoio
    TARGET = conversion_ltilib-2_opencv-3d_gcc
  }
}

SOURCES += \
    libinterface.cpp \
    cvmat2ltiimage.cpp

HEADERS += \
    libconfig.h \
    libinterface.h \
    macrobase.h \
    cvmat2ltiimage.h

