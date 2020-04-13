#ifndef WERKZEUGMAGAZIN_H
#define WERKZEUGMAGAZIN_H

#include <QMessageBox>

#include "Klassen/text_zeilenweise.h"
#include "Defines/werkzeug.h"
#include "Defines/def_bearbeitungen.h"

/*
 * Jede Zeile einthällt ein Werkzeug
 * Die einzelnen Parameter des Werkzeuges sind mit \t getrennt
 * Diese sind:
    1 : Werkzeigtyp
        B | S | M
    2 : Nummer
    3 : Durchmesser des realen Werkzeuges
    4 : Nutzlänge
    5 : Vorschub
    6 : Zustellmaß
    7 : Durchmesser aus Import
    8 : ist Durchgangsbohrer
        1 | 0
    9 : Sägeblattbreite
    10: Lage
        hori | verti
    11: Alias-Name
    12: Mindest Zustellmaß
        0 | 12 etc (wenn 0 dann nicht relevant)
    13: Spiegelwerkzeug

*/


class werkzeugmagazin
{
public:
    werkzeugmagazin();
    werkzeugmagazin(text_zeilenweise neues_magazin);

    QString wkznummer(QString wkz_typ, \
                          double dm = 0, \
                          double bearbeitungstiefe = 0, \
                          double werkstueckdicke = 0, \
                          QString bezugskante = WST_BEZUG_OBSEI);
    QString wkznummer_von_alias(QString alias);
    QString dm(QString wkz_nr);
    QString vorschub(QString wkz_nr);
    QString zustellmass(QString wkz_nr);
    QString zustellmass_min(QString wkz_nr);
    QString tabellenkopf();
    QString saegeblattbreite(QString wkz_nr);
    QString nutzlaenge(QString wkz_nr);
    text_zeilenweise alle_bodm(QString hori_oder_vert);
    QString spiegelwkz(QString wkz_nr);


private:
    text_zeilenweise Magazin;









};

#endif // WERKZEUGMAGAZIN_H
