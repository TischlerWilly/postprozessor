#ifndef WKZ_BOHRER_H
#define WKZ_BOHRER_H

#include <QString>
#include "Klassen/text_zw.h"
#include "Funktionen/umwandeln.h"

class wkz_bohrer
{
public:
    wkz_bohrer();
    wkz_bohrer(text_zw wkz);

    //----------------------------------set:

    //----------------------------------get:
    text_zw daten();

private:
    QString Wkznr;
    double  DMimport;
    double  DMexport;
    double  Nutzlaenge;
    double  Zustellmass;
    bool    IstDuBo;
    QString Lage;
        //vertikal
        //horizontal
    bool    IstAktiv;

};

#endif // WKZ_BOHRER_H
