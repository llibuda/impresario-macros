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

TARGET = viewers_general
win32: TARGET = $${TARGET}_$${VERSION}

include(../target_def.pri)

win32
{
  CONFIG += skip_target_version_ext
  DEFINES += _IMPRESARIO_WIN
}

unix
{
  DEFINES += _IMPRESARIO_LINUX
}

CONFIG(debug, release|debug):DEFINES += _IMPRESARIO_DEBUG

SOURCES += \
    libinterface.cpp \
    viewerbasetypes.cpp \
    widgetbasetypes.cpp

HEADERS += \
    libinterface.h \
    macrobase.h \
    libconfig.h \
    macroextended.h \
    viewerbasetypes.h \
    widgetbasetypes.h

RESOURCES +=
