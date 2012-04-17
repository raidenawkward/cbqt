#-------------------------------------------------
#
# Project created by QtCreator 2012-04-14T12:43:12
#
#-------------------------------------------------

QT       += core gui

TARGET = CBServerMonitor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dishinfodialog.cpp

HEADERS  += mainwindow.h \
    dishinfodialog.h

FORMS    += mainwindow.ui \
    dishinfodialog.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../cbsupport/release/ -lCBSupport
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../cbsupport/debug/ -lCBSupport
else:unix:!symbian: LIBS += -L$$OUT_PWD/../../cbsupport/ -lCBSupport

INCLUDEPATH += $$PWD/../../cbsupport
DEPENDPATH += $$PWD/../../cbsupport

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../cbsupport/release/CBSupport.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../cbsupport/debug/CBSupport.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../../cbsupport/libCBSupport.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../cbsource/release/ -lcbsource
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../cbsource/debug/ -lcbsource
else:unix:!symbian: LIBS += -L$$OUT_PWD/../../cbsource/ -lcbsource

INCLUDEPATH += $$PWD/../../cbsource
DEPENDPATH += $$PWD/../../cbsource

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../cbsource/release/cbsource.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../cbsource/debug/cbsource.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../../cbsource/libcbsource.a
