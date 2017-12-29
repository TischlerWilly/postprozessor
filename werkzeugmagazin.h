#ifndef WERKZEUGMAGAZIN_H
#define WERKZEUGMAGAZIN_H

#include "./allgemKlassen/text_zeilenweise.h"
#include "./Definitionen/werkzeug.h"

/*
 * Jede Zeile einthällt ein Werkzeug
 * Die einzelnen Parameter des Werkzeuges sind mit \t getrennt
 * Diese sind:
    1 : Werkzeigtyp
    2 : Nummer
    3 : Durchmesser
    4 : Nutzlänge
    5 : Vorschub
    6 : Zustellmaß

*/


class werkzeugmagazin
{
public:
    werkzeugmagazin();
    werkzeugmagazin(text_zeilenweise neues_magazin);

    QString get_wkznummer(QString wkz_typ, double dm = 0, double bearbeitungstiefe = 0);
    QString get_dm(QString wkz_nr);
    QString get_vorschub(QString wkz_nr);
    QString get_zustellmass(QString wkz_nr);


private:
    text_zeilenweise magazin;









};

#endif // WERKZEUGMAGAZIN_H
