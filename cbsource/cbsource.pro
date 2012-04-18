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
    cbpathwalker.cpp \
    cbdishesscanner.cpp \
    cbdishparser.cpp

HEADERS += \
    cbxmlwriter.h \
    cbxmlreader.h \
    cbpathwalker.h \
    cbdishesscanner.h \
    cbdishparser.h
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../cbsupport/release/ -lcbsupport
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../cbsupport/debug/ -lcbsupport
else:unix:!symbian: LIBS += -L$$OUT_PWD/../cbsupport/ -lcbsupport

INCLUDEPATH += $$PWD/../cbsupport
DEPENDPATH += $$PWD/../cbsupport

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../cbsupport/release/cbsupport.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../cbsupport/debug/cbsupport.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../cbsupport/libcbsupport.a
