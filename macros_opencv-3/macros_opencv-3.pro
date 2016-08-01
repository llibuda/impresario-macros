#-------------------------------------------------
#
# Project created by QtCreator 2015-02-15T11:35:57
#
#-------------------------------------------------

TEMPLATE = lib
CONFIG -= app_bundle
CONFIG -= qt

win32 {
  INCLUDEPATH += $$quote(../../opencv-3.0.0/build/include)

  CONFIG += dll
  DEFINES += _IMPRESARIO_WIN
  DESTDIR = ../lib
  CONFIG(release, release|debug) {
    if(win32-msvc*) {
      TARGET = imgproc_opencv-3_msvc
      contains(QT_ARCH, i386) {
        LIBS += $$quote(-L../../../opencv-3.0.0/build/x86/vc12/lib) -lopencv_world300
      }
      else {
        LIBS += $$quote(-L../../../opencv-3.0.0/build/x64/vc12/lib) -lopencv_world300
      }
    }
  }
  CONFIG(debug, release|debug) {
    DEFINES += _IMPRESARIO_DEBUG
    if(win32-msvc*) {
      TARGET = imgproc_opencv-3d_msvc
      contains(QT_ARCH, i386) {
        LIBS += $$quote(-L../../../opencv-3.0.0/build/x86/vc12/lib) -lopencv_world300d
      }
      else {
        LIBS += $$quote(-L../../../opencv-3.0.0/build/x64/vc12/lib) -lopencv_world300d
      }
    }
  }
}

unix {
  INCLUDEPATH += $$quote(../../opencv-3.1.0/include)
  INCLUDEPATH += $$quote(../../opencv-3.1.0/modules/core/include)
  INCLUDEPATH += $$quote(../../opencv-3.1.0/modules/imgproc/include)
  INCLUDEPATH += $$quote(../../opencv-3.1.0/modules/photo/include)
  INCLUDEPATH += $$quote(../../opencv-3.1.0/modules/video/include)
  INCLUDEPATH += $$quote(../../opencv-3.1.0/modules/features2d/include)
  INCLUDEPATH += $$quote(../../opencv-3.1.0/modules/flann/include)
  INCLUDEPATH += $$quote(../../opencv-3.1.0/modules/objdetect/include)
  INCLUDEPATH += $$quote(../../opencv-3.1.0/modules/calib3d/include)
  INCLUDEPATH += $$quote(../../opencv-3.1.0/modules/imgcodecs/include)
  INCLUDEPATH += $$quote(../../opencv-3.1.0/modules/videoio/include)
  INCLUDEPATH += $$quote(../../opencv-3.1.0/modules/highgui/include)
  INCLUDEPATH += $$quote(../../opencv-3.1.0/modules/ml/include)
  INCLUDEPATH += $$quote(../../opencv-3.1.0/modules/hal/include)

  CONFIG += dll
  DEFINES += _IMPRESARIO_LINUX
  DESTDIR = ../lib
  CONFIG(release, release|debug) {
    LIBS += $$quote(-L../../../opencv-3.1.0/lib) -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_videoio
    TARGET = imgproc_opencv-3_gcc
  }

  CONFIG(debug, release|debug) {
    DEFINES += _IMPRESARIO_DEBUG
    LIBS += $$quote(-L../../../opencv-3.1.0/lib) -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_videoio
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
