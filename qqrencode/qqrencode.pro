QT  += core gui svg

!win32-msvc2010 {
  QMAKE_CXXFLAGS_DEBUG += -std=c++11 -Wno-write-strings
  QMAKE_CXXFLAGS_RELEASE += -std=c++11 -Wno-write-strings
}

TARGET = libqtqrencode
TEMPLATE = lib

DEFINES += LIBQTQRENCODE_LIBRARY

SOURCES += qqrencode.cpp

HEADERS += qqrencode.h \
    libqtqrencode_global.h \
    qqrencode_p.h

win32 {
  LIBS += -L$$PWD/../lib/qrencode -lqrencode
} else {
  target.path = /usr/lib
  INSTALLS += target
  macx {
      LIBS += -L/usr/local/lib -lqrencode
  } else {
      LIBS += -lqrencode
  }
}

INCLUDEPATH += $$PWD/../lib/qrencode/include
DEPENDPATH += $$PWD/../lib/qrencode/include
