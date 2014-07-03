QT += core testlib

!win32-msvc2010 {
    QMAKE_CXXFLAGS_DEBUG += -std=c++11
    QMAKE_CXXFLAGS_RELEASE += -std=c++11
}

TARGET = tester
CONFIG += console

TEMPLATE = app

SOURCES += \
    main.cpp \
    testrunner.cpp \
    qqrencodetestsuite.cpp

HEADERS += \
    testrunner.h \
    qqrencodetestsuite.h

win32:CONFIG(release, debug|release) {
    # WINDOWS RELEASE
    PRE_TARGETDEPS += $$OUT_PWD/../qqrencode/release/qtqrencode.dll
    LIBS += -L$$OUT_PWD/../qqrencode/release/ -lqtqrencode

} else:win32:CONFIG(debug, debug|release) {
    # WINDOWS DEBUG
    PRE_TARGETDEPS += $$OUT_PWD/../qqrencode/debug/qtqrencode.dll
    LIBS += -L$$OUT_PWD/../qqrencode/debug/ -lqtqrencode
} else:CONFIG(release, debug|release) {
    PRE_TARGETDEPS += $$OUT_PWD/../qqrencode/libqtqrencode.so
    LIBS += -L$$OUT_PWD/../qqrencode/ -lqtqrencode
} else:CONFIG(debug, debug|release) {
    PRE_TARGETDEPS += $$OUT_PWD/../qqrencode/libqtqrencode.so
    LIBS += -L$$OUT_PWD/../qqrencode/ -lqtqrencode
}

INCLUDEPATH += $$PWD/../qqrencode
DEPENDPATH += $$PWD/../qqrencode
