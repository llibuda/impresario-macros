#-------------------------------------------------
#
# Project created by QtCreator 2015-02-16T20:17:06
#
#-------------------------------------------------

TEMPLATE = lib
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
  INCLUDEPATH += $$quote(../../opencv-3.1.0/build/include)

  LIBS += $$quote(-L../../../ltilib-2-build/lib) -lltilib-2_$${BUILD_POSTFIX}

  # check support for open-cv
  OPENCV_BASE_PATH = "../../opencv-3.1.0/build"
  OPENCV_LIB_PATH =
  if(win32-msvc*) {
    contains(QT_ARCH, i386) {
      OPENCV_LIB_PATH = $${OPENCV_BASE_PATH}/x86/vc$${section(MSVC_VER,.,0,0)}/lib
    }
    else {
      OPENCV_LIB_PATH = $${OPENCV_BASE_PATH}/x64/vc$${section(MSVC_VER,.,0,0)}/lib
    }
  }
  OPENCV_LIB = opencv_world310
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

  CONFIG(release, release|debug) {
    LIBS += $$quote(-L../../../ltilib-2/lib) -lltir
    LIBS += $$quote(-L../../../opencv-3.1.0/lib) -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_videoio
  }

  CONFIG(debug, release|debug) {
    LIBS += $$quote(-L../../../ltilib-2/lib) -lltid
    LIBS += $$quote(-L../../../opencv-3.1.0/lib) -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_videoio
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

