#-------------------------------------------------
#
# Project created by QtCreator 2017-08-26T18:08:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets sql

TARGET = tag-a-file
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    editpage.cpp \
    searchpage.cpp \
    taglineedit.cpp \
    taglistwidget.cpp \
    dataaccess.cpp \
    browsepage.cpp

HEADERS  += mainwindow.h \
    editpage.h \
    searchpage.h \
    taglineedit.h \
    taglistwidget.h \
    dataaccess.h \
    browsepage.h

FORMS    += mainwindow.ui \
    editpage.ui \
    searchpage.ui \
    browsepage.ui
