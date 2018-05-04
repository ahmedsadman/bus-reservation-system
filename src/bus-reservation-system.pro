#-------------------------------------------------
#
# Project created by QtCreator 2018-04-10T09:22:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bus-reservation-system
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


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    addbusdialog.cpp \
    addlocationdialog.cpp \
    database.cpp \
    bus.cpp \
    reserveticket.cpp

HEADERS += \
        mainwindow.h \
    addbusdialog.h \
    addlocationdialog.h \
    database.h \
    bus.h \
    reserveticket.h

FORMS += \
        mainwindow.ui \
    addbusdialog.ui \
    addlocationdialog.ui \
    reserveticket.ui

win32:CONFIG(release, debug|release): LIBS += -LC:/Qt/Qt5.10.1/5.10.1/msvc2015/lib/ -lQt5Sql
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/Qt/Qt5.10.1/5.10.1/msvc2015/lib/ -lQt5Sqld
else:unix: LIBS += -LC:/Qt/Qt5.10.1/5.10.1/msvc2015/lib/ -lQt5Sql

INCLUDEPATH += C:/Qt/Qt5.10.1/5.10.1/msvc2015/include
DEPENDPATH += C:/Qt/Qt5.10.1/5.10.1/msvc2015/include
