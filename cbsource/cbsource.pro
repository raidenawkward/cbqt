#-------------------------------------------------
#
# Project created by QtCreator 2012-04-13T14:24:17
#
#-------------------------------------------------

QT       += xml

QT       -= gui

TARGET = cbsource

#TEMPLATE = app
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    cbxmlwriter.cpp \
    main.cpp \
    cbxmlreader.cpp \
    cbpathwalker.cpp

HEADERS += \
    cbxmlwriter.h \
    cbxmlreader.h \
    cbpathwalker.h
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
