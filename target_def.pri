# define correct file name post fixes for various builds
BUILD_POSTFIX =
BUILD_EXT =
win32 {
  CONFIG(shared, shared|static):BUILD_EXT=dll
  if(win32-g++*) {
    CONFIG(static, shared|static):BUILD_EXT=a
    BUILD_POSTFIX = mingw$${system( g++ -dumpversion )}
  }
  else {
    if (win32-msvc*) {
      CONFIG(static, shared|static):BUILD_EXT=lib
      contains(QT_ARCH, i386) {
        BUILD_POSTFIX = vc$${MSVC_VER}_32
      }
      else {
        BUILD_POSTFIX = vc$${MSVC_VER}_64
      }
    }
  }
}

unix {
  CONFIG(shared, shared|static):BUILD_EXT=so
  CONFIG(static, shared|static):BUILD_EXT=a
  BUILD_POSTFIX = gcc$${system( g++ -dumpversion )}
  contains(QT_ARCH, i386) {
    BUILD_POSTFIX = $${BUILD_POSTFIX}_32
  }
  else {
    BUILD_POSTFIX = $${BUILD_POSTFIX}_64
  }
}

CONFIG(debug, release|debug) {
  BUILD_POSTFIX = $${BUILD_POSTFIX}d
}

# redefine target name
TARGET = $${TARGET}_$${BUILD_POSTFIX}
message(Target is $${TARGET}.$${BUILD_EXT})
