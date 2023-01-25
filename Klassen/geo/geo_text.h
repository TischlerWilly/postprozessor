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

class geo_text
{
public:
    geo_text();
    void clear();
    void zeilenvorschub();
    //--------------------------------------set:
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
