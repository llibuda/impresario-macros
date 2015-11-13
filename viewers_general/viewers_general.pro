#-------------------------------------------------
#
# Project created by QtCreator 2014-02-27T21:37:09
#
#-------------------------------------------------

TEMPLATE = lib
QT       += core widgets gui

win32 {
  CONFIG += dll
  DEFINES += _IMPRESARIO_WIN
  DESTDIR = ../lib
  CONFIG(release, release|debug) {
    if(win32-g++*) {
      TARGET = viewers_general_mingw
    }
    if(win32-msvc*) {
      TARGET = viewers_general_msvc
    }
  }
  CONFIG(debug, release|debug) {
    DEFINES += _IMPRESARIO_DEBUG
    if(win32-g++*) {
      TARGET = viewers_generald_mingw
    }
    if(win32-msvc*) {
      TARGET = viewers_generald_msvc
    }
  }
}

unix {
  CONFIG += dll
  DEFINES += _IMPRESARIO_LINUX
  DESTDIR = ../lib
  CONFIG(release, release|debug) {
    TARGET = viewers_general_gcc
  }

  CONFIG(debug, release|debug) {
    DEFINES += _IMPRESARIO_DEBUG
    TARGET = viewers_generald_gcc
  }
}

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
