#ifndef WSTZUSTAND_H
#define WSTZUSTAND_H

#include <QVector>

#include "Klassen/text_zeilenweise.h"
#include "Klassen/werkzeugmagazin.h"
#include "Klassen/geo/geometrietext.h"
#include "Klassen/wst/fraesergerade.h"
#include "Klassen/wst/bohrung.h"
#include "Klassen/wst/bohrraster.h"
#include "Klassen/wst/gehrung.h"
#include "Klassen/wst/fraueseraufruf.h"
#include "Klassen/wst/fraesergerade.h"
#include "Klassen/wst/fraeserbogen.h"
#include "Klassen/wst/nut.h"
#include "Klassen/wst/rechtecktasche.h"

class wstzustand
{
public:
    wstzustand();
    void set_dicke(double d);
    void set_kante_vo(QString artiklenummer);
    void set_kante_hi(QString artiklenummer);
    void set_kante_li(QString artiklenummer);
    void set_kante_re(QString artiklenummer);
    void set_zugabe_gehrungen(double zugabe);



private:
    void clear();
    void erzeugen(QString format, werkzeugmagazin wkzmag, text_zeilenweise bearbeitung, QString drehung, \
                  double l, double b);
    void finde_drehwinkel_auto(int index);
    void fraesergeraden_zusammenfassen(text_zeilenweise& bearbeitung);
    void hbemiduebeltiefe(text_zeilenweise& bearbeitung);
    void gehr_3achs(text_zeilenweise& bearb, double& tmp_l, double& tmp_b, QString ausgabeformat);
    void drehen_um_b_halbe(text_zeilenweise& bearb, double &tmp_b);
    void bearb_drehen_90(text_zeilenweise& bearb, double& tmp_l, double& tmp_b);
    void bearb_optimieren_ganx(text_zeilenweise& bearb);
    void dubosplitten(text_zeilenweise& bearb, werkzeugmagazin wkzmag);
    QString warnungen_fmc(text_zeilenweise bearb, werkzeugmagazin wkzmag, double tmp_l, double tmp_b);
    QString warnungen_ganx(text_zeilenweise bearb, werkzeugmagazin wkzmag, double tmp_l, double tmp_b);

    QString kante_vo(QString drewi);
    QString kante_hi(QString drewi);
    QString kante_li(QString drewi);
    QString kante_re(QString drewi);
    QString kante_vo_ganx(QString drewi);
    QString kante_hi_ganx(QString drewi);
    QString kante_li_ganx(QString drewi);
    QString kante_re_ganx(QString drewi);

    QVector<QString> Format;
    QVector<werkzeugmagazin> Wkzmag;
    QVector<text_zeilenweise> Bearbeitung_bekommen;
    QVector<text_zeilenweise> Bearbeitung;
    QVector<QString> Drehung_bekommen;
    QVector<QString> Drehung;
    QVector<int> Bewertung;

    QVector<geometrietext> Geotext;
    QVector<double> Laenge_bekommen;
    QVector<double> Breite_bekommen;
    QVector<double> Laenge;
    QVector<double> Breite;


    QVector<double> Versatz_y;
    QVector<text_zeilenweise> CAD_fehler;
    QVector<QString> Warnungen;
    QVector<bool> Export_moeglich;

    double Zugabe_gehrungen;
    QString Kante_vo; //Kante an X
    QString Kante_hi;
    QString Kante_li; //Kante an Y
    QString Kante_re;
    double Schwellenwert_ay; //für fmc-Ausgabe, bis zu dieser Breite wird mit ay-Versatz ausgegeben
    double Dicke;
};

#endif // WSTZUSTAND_H
