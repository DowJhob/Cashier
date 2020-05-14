#-------------------------------------------------
#
# Project created by QtCreator 2019-11-13T22:48:42
#
#-------------------------------------------------

QT       += core gui network sql printsupport qml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = newCashier
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_CFLAGS += -O3
QMAKE_CXXFLAGS += -O3
CONFIG += c++11

SOURCES += \
#        mail.cpp \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        common_types.h \
        controller.h \
        eventselector.h \
        https.h \
#        mail.h \
        mainwindow.h \
    report_widget.h \
        settings.h \
        viewwidget.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/limereportLIB/x64/release/ -llimereport
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/limereportLIB/x64/debug/ -llimereportd
else:unix: LIBS += -L$$PWD/limereportLIB/x64/ -llimereportd

INCLUDEPATH += $$PWD/limereportLIB/x64/include
DEPENDPATH += $$PWD/limereportLIB/x64/include
