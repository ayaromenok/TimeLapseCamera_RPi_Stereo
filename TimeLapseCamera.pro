# Copyright(C) 2019 Andrey Yaromenok, ayaromenok@gmail.com
# MIT License
# https://raw.githubusercontent.com/ayaromenok/TimeLapseCamera_Stereo/master/LICENSE

QT       += core gui widgets
QT       += multimedia multimediawidgets

TARGET = TimeLaspeCamera

TEMPLATE = app

CONFIG += c++11

SOURCES += \
        src/main.cpp \
        src/yastereowidget.cpp

HEADERS += \
        src/yastereowidget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


CVLINUX = /usr/local
#Darwin, Windows, Android, iOS
equals(QMAKE_HOST.os, Linux) {
    message("        Settings for Unix/Linux.")
    INCLUDEPATH += $${CVLINUX}/include/opencv4
    LIBS += -L$${CVLINUX}/lib
    LIBS += -lopencv_core -lopencv_imgcodecs -lopencv_imgproc
    LIBS += -lopencv_highgui -lopencv_videoio

    equals(QMAKE_HOST.arch, x86_64){
        DEFINES += DEBUG_PC
        message("        arch: amd64")
    }
    contains(QMAKE_HOST.arch, armv7l){
        DEFINES += DEBUG_RPI_V7L
        message("        arch: RPi/armv7l")
    }
    contains(QMAKE_HOST.arch, armv6l){
        DEFINES += DEBUG_RPI_V6L
        message("        arch: RPi/armv6l")
    }
    contains(QMAKE_HOST.arch, aarch64){
        DEFINES += DEBUG_RPI_ARM64
        message("        arch: RPi3/aarch64")
    }
}

RESOURCES += \
    res/res.qrc
