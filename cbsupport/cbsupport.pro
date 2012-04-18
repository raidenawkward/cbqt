#-------------------------------------------------
#
# Project created by QtCreator 2012-04-17T13:39:28
#
#-------------------------------------------------

QT       -= gui

TARGET = cbsupport
TEMPLATE = lib
CONFIG += staticlib

SOURCES += cbsupport.cpp \
    cbtagsset.cpp \
    cbid.cpp \
    cbdish.cpp \
    cborder.cpp \
    cbcustomer.cpp \
    cbmenuitem.cpp \
    cbmenuitemsset.cpp

HEADERS += cbsupport.h \
    cbifsethandler.h \
    cbtagsset.h \
    cbid.h \
    cbdish.h \
    cborder.h \
    cbcustomer.h \
    cbmenuitem.h \
    cbmenuitemsset.h
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
