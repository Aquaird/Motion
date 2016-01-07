#-------------------------------------------------
#
# Project created by QtCreator 2016-01-05T05:00:25
#
#-------------------------------------------------

QT       += core gui opengl
LIBS    +=  -lglut -lGLU
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Motion
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp

HEADERS  += mainwindow.h \
    csvrow.h \
    pose.h \
    heads.h \
    glwidget.h

FORMS    += mainwindow.ui

DISTFILES += \
    queries.csv
