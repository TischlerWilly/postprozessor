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
    Dialoge/dialog_bearb_bohrung.cpp \
    Dialoge/dialog_bearb_faufruf.cpp \
    Dialoge/dialog_bearb_fbogen.cpp \
    Dialoge/dialog_bearb_fgerade.cpp \
    Dialoge/dialog_bearb_nut.cpp \
    Dialoge/dialog_bearb_pkopf.cpp \
    Dialoge/dialog_bearb_rta.cpp \
    Dialoge/dialog_bearb_verschieben.cpp \
    Dialoge/dialog_einstellung_dxf.cpp \
    Dialoge/dialog_einstellung_dxf_klassen.cpp \
    Dialoge/dialog_einstellung_fmc.cpp \
    Dialoge/dialog_einstellung_ganx.cpp \
    Dialoge/dialog_einstellung_pfade.cpp \
    Dialoge/dialog_einstellung_wkz_pp.cpp \
    Dialoge/dialog_exportuebersicht.cpp \
    Dialoge/dialog_fraeserauswahl.cpp \
    Dialoge/dialog_programmtext.cpp \
    Funktionen/funktionen_prgtext.cpp \
    Klassen/einstellung.cpp \
    Klassen/einstellung_dxf.cpp \
    Klassen/einstellung_dxf_klassen.cpp \
    Klassen/einstellung_ganx.cpp \
    Klassen/geo/bogenac.cpp \
    Klassen/geo/geo_text.cpp \
    Klassen/geo/kreis.cpp \
    Klassen/geo/rechteck3d.cpp \
    Klassen/geo/vorschau.cpp \
    Klassen/geo/wuerfel.cpp \
    Klassen/geo/zylinder.cpp \
    Klassen/text_zw.cpp \
    Klassen/undo_redo.cpp \
    Klassen/wkz/wkz_bohrer.cpp \
    Klassen/wkz/wkz_fraeser.cpp \
    Klassen/wkz/wkz_magazin.cpp \
    Klassen/wkz/wkz_saege.cpp \
    Klassen/einstellung_fmc.cpp \
    Klassen/wst/cix_index.cpp \
    Klassen/wst/cix_index_geo.cpp \
    Klassen/wst/fraeseraufruf.cpp \
    Klassen/wst/gehrung.cpp \
    Klassen/wst/wstzustand.cpp \
    mainwin_wkzmagazin.cpp \
    mainwin_wst_bearbeiten.cpp \
        mainwindow.cpp \
    Klassen/formel.cpp \
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
    Dialoge/dialog_bohrer.cpp \
    Dialoge/dialog_fraeser.cpp \
    Dialoge/dialog_saege.cpp \
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
    Defines/def_cix.h \
    Defines/def_dxf.h \
    Dialoge/dialog_bearb_bohrung.h \
    Dialoge/dialog_bearb_faufruf.h \
    Dialoge/dialog_bearb_fbogen.h \
    Dialoge/dialog_bearb_fgerade.h \
    Dialoge/dialog_bearb_nut.h \
    Dialoge/dialog_bearb_pkopf.h \
    Dialoge/dialog_bearb_rta.h \
    Dialoge/dialog_bearb_verschieben.h \
    Dialoge/dialog_einstellung_dxf.h \
    Dialoge/dialog_einstellung_dxf_klassen.h \
    Dialoge/dialog_einstellung_fmc.h \
    Dialoge/dialog_einstellung_ganx.h \
    Dialoge/dialog_einstellung_pfade.h \
    Dialoge/dialog_einstellung_wkz_pp.h \
    Dialoge/dialog_exportuebersicht.h \
    Dialoge/dialog_fraeserauswahl.h \
    Dialoge/dialog_programmtext.h \
    Funktionen/funktionen_prgtext.h \
    Klassen/einstellung.h \
    Klassen/einstellung_dxf.h \
    Klassen/einstellung_dxf_klassen.h \
    Klassen/einstellung_ganx.h \
    Klassen/formel.h \
    Klassen/geo/bogenac.h \
    Klassen/geo/defines_geometrie.h \
    Klassen/geo/geo_text.h \
    Klassen/geo/kreis.h \
    Klassen/geo/makro_geometrie.h \
    Klassen/geo/rechteck3d.h \
    Klassen/geo/vorschau.h \
    Klassen/geo/wuerfel.h \
    Klassen/geo/zylinder.h \
    Klassen/text_zw.h \
    Klassen/undo_redo.h \
    Klassen/wenndannsonst.h \
    Funktionen/myfunktion.h \
    Funktionen/runden.h \
    Funktionen/text.h \
    Funktionen/umwandeln.h \
    Klassen/wkz/wkz_bohrer.h \
    Klassen/wkz/wkz_fraeser.h \
    Klassen/wkz/wkz_magazin.h \
    Klassen/wkz/wkz_saege.h \
    Klassen/einstellung_fmc.h \
    Klassen/wst/cix_index.h \
    Klassen/wst/cix_index_geo.h \
    Klassen/wst/fraeseraufruf.h \
    Klassen/wst/gehrung.h \
    Klassen/wst/wstzustand.h \
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
    Dialoge/dialog_bohrer.h \
    Dialoge/dialog_fraeser.h \
    Dialoge/dialog_saege.h \
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
    Dialoge/dialog_stdname.h \
    mainwin_wkzmagazin.h \
    mainwin_wst_bearbeiten.h

FORMS    += mainwindow.ui \
    Dialoge/dialog_bearb_bohrung.ui \
    Dialoge/dialog_bearb_faufruf.ui \
    Dialoge/dialog_bearb_fbogen.ui \
    Dialoge/dialog_bearb_fgerade.ui \
    Dialoge/dialog_bearb_nut.ui \
    Dialoge/dialog_bearb_pkopf.ui \
    Dialoge/dialog_bearb_rta.ui \
    Dialoge/dialog_bearb_verschieben.ui \
    Dialoge/dialog_einstellung_dxf.ui \
    Dialoge/dialog_einstellung_dxf_klassen.ui \
    Dialoge/dialog_einstellung_fmc.ui \
    Dialoge/dialog_einstellung_ganx.ui \
    Dialoge/dialog_einstellung_pfade.ui \
    Dialoge/dialog_einstellung_wkz_pp.ui \
    Dialoge/dialog_exportuebersicht.ui \
    Dialoge/dialog_fraeserauswahl.ui \
    Dialoge/dialog_programmtext.ui \
    Dialoge/dialog_bohrer.ui \
    Dialoge/dialog_fraeser.ui \
    Dialoge/dialog_saege.ui \
    Dialoge/dialog_stdnamen.ui \
    Dialoge/dialog_stdname.ui \
    mainwin_wkzmagazin.ui \
    mainwin_wst_bearbeiten.ui

DISTFILES += \
    Klassen/geo/makro_geometrie.h~ \
    Struncts/punkt.h~ \
    postprozessor.ico

RC_ICONS = postprozessor.ico

RESOURCES += \
    toolbaricons.qrc
