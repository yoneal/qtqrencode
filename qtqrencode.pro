QT  += core gui svg

!win32-msvc2010 {
  QMAKE_CXXFLAGS_DEBUG += -std=c++11 -Wno-write-strings
  QMAKE_CXXFLAGS_RELEASE += -std=c++11 -Wno-write-strings
}

TARGET = qtqrencode
TEMPLATE = lib

SOURCES += \
    qtqrencode.cpp

HEADERS += \
    qtqrencode.h \
    qtqrencode_p.h

