#-------------------------------------------------
#
# Project created by QtCreator 2014-02-27T21:37:09
#
#-------------------------------------------------

TEMPLATE = lib
QT       += core widgets gui

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
    contains(QT_ARCH, i386) {
      if(win32-g++*) {
        LIBS += $$quote(-L../../../ltilib-2-build/MinGW_32bit-Release/lib) -lltilib-2_mingw
        TARGET = viewers_ltilib-2_mingw
      }
      if(win32-msvc*) {
        LIBS += $$quote(-L../../../ltilib-2-build/MSVC2013_32bit-Release/lib) -lltilib-2_msvc
        TARGET = viewers_ltilib-2_msvc
      }
    }
    else {
      if(win32-msvc*) {
        LIBS += $$quote(-L../../../ltilib-2-build/MSVC2013_64bit-Release/lib) -lltilib-2_msvc
        TARGET = viewers_ltilib-2_msvc
      }
    }
  }
  CONFIG(debug, release|debug) {
    DEFINES += _IMPRESARIO_DEBUG
    contains(QT_ARCH, i386) {
      if(win32-g++*) {
        LIBS += $$quote(-L../../../ltilib-2-build/MinGW_32bit-Debug/lib) -lltilib-2d_mingw
        TARGET = viewers_ltilib-2d_mingw
      }
      if(win32-msvc*) {
        LIBS += $$quote(-L../../../ltilib-2-build/MSVC2013_32bit-Debug/lib) -lltilib-2d_msvc
        TARGET = viewers_ltilib-2d_msvc
      }
    }
    else {
      if(win32-msvc*) {
        LIBS += $$quote(-L../../../ltilib-2-build/MSVC2013_64bit-Debug/lib) -lltilib-2d_msvc
        TARGET = viewers_ltilib-2d_msvc
      }
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
    TARGET = viewers_ltilib-2_gcc
  }

  CONFIG(debug, release|debug) {
    DEFINES += _IMPRESARIO_DEBUG
    LIBS += $$quote(-L../../../ltilib-2/lib) -lltid
    TARGET = viewers_ltilib-2d_gcc
  }
}

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
