#-------------------------------------------------
#
# Project created by QtCreator 2017-12-03T15:07:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = postprozessor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    allgemKlassen/formel.cpp \
    allgemKlassen/text_zeilenweise.cpp \
    allgemKlassen/wenndannsonst.cpp \
    eigeneFunktionen/myfunktion.cpp \
    eigeneFunktionen/runden.cpp \
    eigeneFunktionen/text.cpp \
    eigeneFunktionen/umwandeln.cpp

HEADERS  += mainwindow.h \
    allgemKlassen/formel.h \
    allgemKlassen/text_zeilenweise.h \
    allgemKlassen/wenndannsonst.h \
    eigeneFunktionen/myfunktion.h \
    eigeneFunktionen/runden.h \
    eigeneFunktionen/text.h \
    eigeneFunktionen/umwandeln.h

FORMS    += mainwindow.ui
