#-------------------------------------------------
#
# Project created by QtCreator 2016-09-05T17:47:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = portJesus
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui

RESOURCES += \
    icons.qrc

linux {
    QMAKE_LFLAGS += -Wl,-rpath,\\$\$ORIGIN

    unix:!macx: LIBS += -lusb-1.0
    INCLUDEPATH += -L$$PWD libusb-1.0
    DEPENDPATH += -L$$PWD libusb-1.0
#    unix:!macx: PRE_TARGETDEPS += $$PWD libusb.a
}

windows {
    LIBS += -L$$PWD libusb-1.0
}
