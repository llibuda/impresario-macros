#-------------------------------------------------
#
# Project created by QtCreator 2014-02-27T21:37:09
#
#-------------------------------------------------

TEMPLATE = lib
CONFIG += shared
QT += core widgets gui

VERSION = 1.0.0
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
