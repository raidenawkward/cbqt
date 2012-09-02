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
    dishinfodialog.cpp \
    cbglobal.cpp \
    cbsetting.cpp \
    cbleftbuttonsetting.cpp \
    cblocationsettings.cpp \
    cbdeviceappsettings.cpp

HEADERS  += mainwindow.h \
    dishinfodialog.h \
    cbglobal.h \
    cbdefine.h \
    cbsetting.h \
    cbleftbuttonsetting.h \
    cblocationsettings.h \
    cbdeviceappsettings.h

FORMS    += mainwindow.ui \
    dishinfodialog.ui


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../cbsource/release/ -lcbsource
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../cbsource/debug/ -lcbsource
else:unix:!symbian: LIBS += -L$$OUT_PWD/../../cbsource/ -lcbsource

INCLUDEPATH += $$PWD/../../cbsource
DEPENDPATH += $$PWD/../../cbsource

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../cbsource/release/cbsource.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../cbsource/debug/cbsource.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../../cbsource/libcbsource.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../cbsupport/release/ -lcbsupport
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../cbsupport/debug/ -lcbsupport
else:unix:!symbian: LIBS += -L$$OUT_PWD/../../cbsupport/ -lcbsupport

INCLUDEPATH += $$PWD/../../cbsupport
DEPENDPATH += $$PWD/../../cbsupport

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../cbsupport/release/cbsupport.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../cbsupport/debug/cbsupport.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../../cbsupport/libcbsupport.a

RESOURCES += \
    cbsource.qrc

OTHER_FILES +=
