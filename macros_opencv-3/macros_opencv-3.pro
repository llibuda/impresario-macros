#-------------------------------------------------
#
# Project created by QtCreator 2015-02-15T11:35:57
#
#-------------------------------------------------

TEMPLATE = lib
CONFIG -= app_bundle
CONFIG -= qt

win32 {
  INCLUDEPATH += $$quote(../../opencv-3.0.0-beta/build/include)

  CONFIG += dll
  DEFINES += _IMPRESARIO_WIN
  DESTDIR = ../lib
  CONFIG(release, release|debug) {
    if(win32-g++*) {
      LIBS += $$quote(-L../../../opencv-3.0.0-beta/build/x86/vc11/lib) -lopencv_world300
      TARGET = imgproc_opencv-3_mingw
    }
    if(win32-msvc*) {
      LIBS += $$quote(-L../../../opencv-3.0.0-beta/build/x86/vc11/lib) -lopencv_world300
      TARGET = imgproc_opencv-3_msvc
    }
  }
  CONFIG(debug, release|debug) {
    DEFINES += _IMPRESARIO_DEBUG
    if(win32-g++*) {
      LIBS += $$quote(-L../../../opencv-3.0.0-beta/build/x86/vc11/lib) -lopencv_world300d
      TARGET = imgproc_opencv-3d_mingw
    }
    if(win32-msvc*) {
      LIBS += $$quote(-L../../../opencv-3.0.0-beta/build/x86/vc11/lib) -lopencv_world300d
      TARGET = imgproc_opencv-3d_msvc
    }
  }
}

unix {
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
    LIBS += $$quote(-L../../../opencv-3.0.0-beta/lib) -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_videoio
    TARGET = imgproc_opencv-3_gcc
  }

  CONFIG(debug, release|debug) {
    DEFINES += _IMPRESARIO_DEBUG
    LIBS += $$quote(-L../../../opencv-3.0.0-beta/lib) -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_videoio
    TARGET = imgproc_opencv-3d_gcc
  }
}

SOURCES += \
    libinterface.cpp \
    videoinput.cpp \
    camerainput.cpp \
    cvtcolor.cpp \
    cvmatconvert.cpp \
    cannyedge.cpp

HEADERS +=\
    libconfig.h \
    libinterface.h \
    macrobase.h \
    videoinput.h \
    camerainput.h \
    cvtcolor.h \
    cvmatconvert.h \
    cannyedge.h
