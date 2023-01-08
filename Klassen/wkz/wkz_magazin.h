#ifndef WKZ_MAGAZIN_H
#define WKZ_MAGAZIN_H

#include "Klassen/wkz/wkz_bohrer.h"
#include "Klassen/wkz/wkz_fraeser.h"
#include "Klassen/wkz/wkz_saege.h"
#include "Defines/def_bearbeitungen.h"


class wkz_magazin
{
public:
    wkz_magazin();
    wkz_magazin(text_zw neues_magazin);

    //----------------------------------get:
    QString wkznummer(QString wkz_typ, \
                          double dm = 0, \
                          double bearbeitungstiefe = 0, \
                          double werkstueckdicke = 0, \
                          QString bezugskante = WST_BEZUG_OBSEI);
    QString wkznummer_von_alias(QString alias);

private:

    QString typ(QString wkz);
    bool istaktiv(QString wkz);

    text_zw Magazin;
};

#endif // WKZ_MAGAZIN_H
