#ifndef GEO_TEXT_H
#define GEO_TEXT_H

#include <QString>
#include <QMessageBox>
#include "Klassen/text_zw.h"
#include "Struncts/punkt.h"
#include "Funktionen/umwandeln.h"
#include "punkt3d.h"
#include "strecke.h"
#include "bogen.h"
#include "kreis.h"
#include "zylinder.h"
#include "rechteck3d.h"
#include "wuerfel.h"
#include "defines_geometrie.h"
#include "geofunktionen.h"
#include "Defines/def_bearbeitungen.h"
#include "Klassen/wst/bohrung.h"
#include "Klassen/wst/bohrraster.h"
#include "Klassen/wst/nut.h"
#include "Klassen/wst/rechtecktasche.h"
#include "Klassen/wst/fraeseraufruf.h"
#include "Klassen/wst/fraesergerade.h"
#include "Klassen/wst/fraeserbogen.h"
#include "Klassen/wst/gehrung.h"

class geo_text
{
public:
    geo_text();
    void clear();
    void zeilenvorschub();
    //--------------------------------------set:
    void add_leerzeile();
    void add_punkt(punkt3d p);
    void add_punkt(punkt3d p, uint index);
    void add_strecke(strecke s);
    void add_strecke(strecke s, uint index);
    void add_bogen(bogen b);
    void add_bogen(bogen b, uint index);
    void add_kreis(kreis k);
    void add_kreis(kreis k, uint index);
    void add_zylinder(zylinder z);
    void add_zylinder(zylinder z, uint index);
    void add_rechteck(rechteck3d rec);
    void add_rechteck(rechteck3d rec, uint index);
    void add_wuerfel(wuerfel w);
    void add_wuerfel(wuerfel w, uint index);
    //--------------------------------------get:
    uint akt_index();
    uint count();
    text_zw at();
    text_zw at(uint index);

private:
    void add(text_zw geometrie, uint index);    

    std::vector<text_zw>    Daten;
    uint                    AktIndex;
    bool                    Zeivor;//Zeilenvorschub

};

#endif // GEO_TEXT_H

//Funktionen außerhalb der Klasse:

geo_text geo_ermitteln(text_zw bearb, double wst_l, double wst_b, double wst_d, \
                       QString kante_v, QString kante_h, QString kante_l, QString kante_r, \
                       double versatz_x, double versatz_y);

geo_text geofkon_ermitteln(text_zw bearb, double versatz_x, double versatz_y);
