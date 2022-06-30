#-------------------------------------------------
#
# Project created by QtCreator 2022-06-30T15:03:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NoNameNotes
TEMPLATE = app


SOURCES += main.cpp\
        nonamenotes.cpp \
    mainwindow.cpp \
    eraser.cpp \
    file.cpp \
    folder.cpp \
    mypushbutton.cpp \
    otherpushbutton.cpp \
    otherscene.cpp \
    pencilpushbutton.cpp \
    pencilscene.cpp \
    show.cpp \
    writepushbutton.cpp \
    writescene.cpp

HEADERS  += nonamenotes.h \
    mainwindow.h \
    eraser.h \
    file.h \
    folder.h \
    mycolor.h \
    mypushbutton.h \
    otherpushbutton.h \
    otherscene.h \
    pencilpushbutton.h \
    pencilscene.h \
    show.h \
    writepushbutton.h \
    writescene.h

FORMS    += nonamenotes.ui \
    mainwindow.ui

RESOURCES += \
    buttons.qrc \
    res.qrc \
    res2.qrc \
    res3.qrc \
    res4.qrc
