#ifndef WKZ_MAGAZIN_H
#define WKZ_MAGAZIN_H

#include "Klassen/wkz/wkz_bohrer.h"
#include "Klassen/wkz/wkz_fraeser.h"
#include "Klassen/wkz/wkz_saege.h"
#include "Defines/def_bearbeitungen.h"

#include <QMessageBox>


class wkz_magazin
{
public:
    wkz_magazin();
    wkz_magazin(text_zw neues_magazin);

    //----------------------------------set:
    void set_text(QString werkzeuge);
    void set_text(text_zw werkzeuge);
    //----------------------------------get:
    text_zw *magazin_ptr();
    text_zw magazin();
    QString text();
    QString wkznummer(QString wkz_typ, \
                          double dm = 0, \
                          double bearbeitungstiefe = 0, \
                          double werkstueckdicke = 0, \
                          QString bezugskante = WST_BEZUG_OBSEI);
    QString wkznummer_von_alias(QString alias);
    QString dm(QString wkz_nr);
    bool ist_dubo(QString wkz_nr);
    QString vorschub(QString wkz_nr);
    QString zustmasvert(QString wkz_nr);
    QString zustmashori(QString wkz_nr);
    QString zustellmass_min(QString wkz_nr);
    QString saegeblattbreite(QString wkz_nr);
    QString nutzlaenge(QString wkz_nr);
    text_zw alle_bodm_hori();
    text_zw alle_bodm_verti();
    QString spiegelwkz(QString wkz_nr);
    //----------------------------------manipulation:
    void item_down(uint index);
    void item_up(uint index);
    void entf(uint index);

private:
    QString typ(text_zw wkz);
    bool istaktiv(text_zw wkz);
    QString wkznr(text_zw wkz);

    text_zw Magazin;
};
//-------------------Funktionen nicht innerhalb der Klasse:
bool operator ==(wkz_magazin w1, wkz_magazin w2);
bool operator !=(wkz_magazin w1, wkz_magazin w2);

#endif // WKZ_MAGAZIN_H
