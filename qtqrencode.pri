INCLUDEPATH += \
    $$PWD

LIBS += \
    -L../qtqrencode -lqtqrencode

mac {
    # This is where brew puts the lib in
    LIBS += -L/usr/local/lib/
}

LIBS += -lqrencode

