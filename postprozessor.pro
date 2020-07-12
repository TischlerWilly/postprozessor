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
    Klassen/geo/geometrietext.cpp \
    Klassen/geo/kreis.cpp \
    Klassen/geo/rechteck3d.cpp \
    Klassen/geo/wuerfel.cpp \
    Klassen/geo/zylinder.cpp \
    Klassen/wst/gehrung.cpp \
        mainwindow.cpp \
    Klassen/formel.cpp \
    Klassen/text_zeilenweise.cpp \
    Klassen/wenndannsonst.cpp \
    Funktionen/myfunktion.cpp \
    Funktionen/runden.cpp \
    Funktionen/text.cpp \
    Funktionen/umwandeln.cpp \
    Klassen/wst/werkstueck.cpp \
    Klassen/wst/werkstuecke.cpp \
    Klassen/wst/bohrung.cpp \
    Klassen/wst/rechtecktasche.cpp \
    Klassen/wst/nut.cpp \
    Klassen/prgpfade.cpp \
    Klassen/werkzeugmagazin.cpp \
    Dialoge/dialog_wkz.cpp \
    Dialoge/dialog_bohrer.cpp \
    Dialoge/dialog_fraeser.cpp \
    Dialoge/dialog_saege.cpp \
    Klassen/wst/fraueseraufruf.cpp \
    Klassen/geo/bogen.cpp \
    Klassen/geo/punkt3d.cpp \
    Klassen/geo/strecke.cpp \
    Klassen/wst/fraesergerade.cpp \
    Klassen/geo/darstellungsatribute.cpp \
    Klassen/geo/geofunktionen.cpp \
    Klassen/geo/punkt2d.cpp \
    Klassen/wst/fraeserbogen.cpp \
    Klassen/wst/bohrraster.cpp \
    Klassen/wst/ganx_gruppen.cpp \
    Dialoge/dialog_stdnamen.cpp \
    Dialoge/dialog_stdname.cpp

HEADERS  += mainwindow.h \
    Klassen/formel.h \
    Klassen/geo/defines_geometrie.h \
    Klassen/geo/geometrietext.h \
    Klassen/geo/kreis.h \
    Klassen/geo/makro_geometrie.h \
    Klassen/geo/rechteck3d.h \
    Klassen/geo/wuerfel.h \
    Klassen/geo/zylinder.h \
    Klassen/text_zeilenweise.h \
    Klassen/wenndannsonst.h \
    Funktionen/myfunktion.h \
    Funktionen/runden.h \
    Funktionen/text.h \
    Funktionen/umwandeln.h \
    Klassen/wst/gehrung.h \
    Struncts/punkt.h \
    ToDo.h \
    Defines/dateinamen.h \
    Defines//werkzeug.h \
    Klassen/wst/werkstueck.h \
    Klassen/wst/werkstuecke.h \
    Defines//def_fmc.h \
    Klassen/wst/bohrung.h \
    Defines/def_bearbeitungen.h \
    Klassen/wst/rechtecktasche.h \
    Klassen/wst/nut.h \
    Defines//def_ganx.h \
    Klassen/prgpfade.h \
    Klassen/werkzeugmagazin.h \
    Dialoge/dialog_wkz.h \
    Dialoge/dialog_bohrer.h \
    Dialoge/dialog_fraeser.h \
    Dialoge/dialog_saege.h \
    Klassen/wst/fraueseraufruf.h \
    Klassen/geo/bogen.h \
    Klassen/geo/punkt3d.h \
    Klassen/geo/strecke.h \
    Klassen/wst/fraesergerade.h \
    Klassen/geo/darstellungsatribute.h \
    Klassen/geo/geofunktionen.h \
    Klassen/geo/punkt2d.h \
    Klassen/wst/fraeserbogen.h \
    Klassen/wst/bohrraster.h \
    Klassen/wst/ganx_gruppen.h \
    Defines//def_vw.h \
    Dialoge/dialog_stdnamen.h \
    Dialoge/dialog_stdname.h

FORMS    += mainwindow.ui \
    Dialoge/dialog_wkz.ui \
    Dialoge/dialog_bohrer.ui \
    Dialoge/dialog_fraeser.ui \
    Dialoge/dialog_saege.ui \
    Dialoge/dialog_stdnamen.ui \
    Dialoge/dialog_stdname.ui

DISTFILES += \
    Klassen/geo/makro_geometrie.h~ \
    Struncts/punkt.h~ \
    postprozessor.ico

RC_ICONS = postprozessor.ico
