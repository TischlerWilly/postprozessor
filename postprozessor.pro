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
    eigeneFunktionen/umwandeln.cpp \
    KlassenWst/werkstueck.cpp \
    KlassenWst/werkstuecke.cpp \
    KlassenWst/bohrung.cpp \
    KlassenWst/rechtecktasche.cpp \
    KlassenWst/nut.cpp \
    werkzeugmagazin.cpp \
    dialog_wkz.cpp \
    dialog_bohrer.cpp \
    dialog_fraeser.cpp \
    dialog_saege.cpp

HEADERS  += mainwindow.h \
    allgemKlassen/formel.h \
    allgemKlassen/text_zeilenweise.h \
    allgemKlassen/wenndannsonst.h \
    eigeneFunktionen/myfunktion.h \
    eigeneFunktionen/runden.h \
    eigeneFunktionen/text.h \
    eigeneFunktionen/umwandeln.h \
    ToDo.h \
    Definitionen/dateinamen.h \
    Definitionen/werkzeug.h \
    KlassenWst/werkstueck.h \
    KlassenWst/werkstuecke.h \
    Definitionen/def_fmc.h \
    KlassenWst/bohrung.h \
    Definitionen/def_bearbeitungen.h \
    KlassenWst/rechtecktasche.h \
    KlassenWst/nut.h \
    Definitionen/def_ganx.h \
    werkzeugmagazin.h \
    dialog_wkz.h \
    dialog_bohrer.h \
    dialog_fraeser.h \
    dialog_saege.h

FORMS    += mainwindow.ui \
    dialog_wkz.ui \
    dialog_bohrer.ui \
    dialog_fraeser.ui \
    dialog_saege.ui
