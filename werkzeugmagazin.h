#ifndef WERKZEUGMAGAZIN_H
#define WERKZEUGMAGAZIN_H

#include <QMessageBox>

#include "./allgemKlassen/text_zeilenweise.h"
#include "./Definitionen/werkzeug.h"
#include "./Definitionen/def_bearbeitungen.h"

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

*/


class werkzeugmagazin
{
public:
    werkzeugmagazin();
    werkzeugmagazin(text_zeilenweise neues_magazin);

    QString get_wkznummer(QString wkz_typ, \
                          double dm = 0, \
                          double bearbeitungstiefe = 0, \
                          double werkstueckdicke = 0, \
                          QString bezugskante = WST_BEZUG_OBSEI);
    QString get_dm(QString wkz_nr);
    QString get_vorschub(QString wkz_nr);
    QString get_zustellmass(QString wkz_nr);
    QString get_tabellenkopf();
    QString get_saegeblattbreite(QString wkz_nr);


private:
    text_zeilenweise magazin;









};

#endif // WERKZEUGMAGAZIN_H
