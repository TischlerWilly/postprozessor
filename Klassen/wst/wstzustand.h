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
#include "Defines/def_fmc.h"
#include "Defines/def_ganx.h"

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
    void set_formartierungen_aufbrechen(bool jn);
    inline void set_name(QString neuer_name)
    {
        Name = neuer_name;
    }
    inline void set_zust_fkon(QString zust)
    {
        Zust_fkon = zust;
        //"wkz" == gemäß Werkzeugmagazin
        //"orgi" == gemäß Importdatei
    }

    inline double dicke()
    {
        return Dicke;
    }
    inline QString dicke_qstring()
    {
        return double_to_qstring(Dicke);
    }

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
    void rasterbohrungen_finden_fmc(text_zeilenweise& bearb, werkzeugmagazin wkzmag,double tmp_l, double tmp_b);
    void rasterbohrungen_finden_ganx(text_zeilenweise& bearb, werkzeugmagazin wkzmag,double tmp_l, double tmp_b);
    void formartierung_zu_einzelfkon(text_zeilenweise& bearb,double tmp_l, double tmp_b);
    void kurze_an_ab_geraden(text_zeilenweise& bearb, werkzeugmagazin wkzmag);
    QString kommentar_fmc(QString kom);
    QString kommentar_ggf(QString kom);
    QString fmc_kommentar_gute_seite(text_zeilenweise& bearb);
    bool punkt_auf_wst(double x, double y, double l, double b, double tolleranz);
    QString fehler_kein_WKZ(QString exportformat, text_zeilenweise bearbzeile);
    QString bearb_menschlich_lesbar(text_zeilenweise bearbzeile);
    void fmc_dateitext(int index);
    void geo(int index);

    QString kante_vo(QString drewi);
    QString kante_hi(QString drewi);
    QString kante_li(QString drewi);
    QString kante_re(QString drewi);
    QString kante_vo_ganx(QString drewi);
    QString kante_hi_ganx(QString drewi);
    QString kante_li_ganx(QString drewi);
    QString kante_re_ganx(QString drewi);

    QVector<QString>            Format;
    QVector<werkzeugmagazin>    Wkzmag;
    QVector<text_zeilenweise>   Bearbeitung_bekommen;
    QVector<QString>            Drehung_bekommen;
    QVector<double>             Laenge_bekommen;
    QVector<double>             Breite_bekommen;
    QVector<QString>            Drehung;
    QVector<int>                Bewertung;
    QVector<QString>            Warnungen;
    QVector<text_zeilenweise>   Bearbeitung;
    QVector<double>             Laenge;
    QVector<double>             Breite;
    QVector<QString>            Exporttext;
    QVector<QString>            Fehler_kein_wkz;
    QVector<bool>               Export_moeglich;



    QVector<geometrietext> Geotext;
    QVector<double> Versatz_y;
    QVector<text_zeilenweise> CAD_fehler;



    double Zugabe_gehrungen;
    bool Formartierungen_aufbrechen;
    QString Kante_vo; //Kante an X
    QString Kante_hi;
    QString Kante_li; //Kante an Y
    QString Kante_re;
    double Schwellenwert_ay; //für fmc-Ausgabe, bis zu dieser Breite wird mit ay-Versatz ausgegeben
    double Dicke;
    QString Name;
    QString Zust_fkon;
};

#endif // WSTZUSTAND_H
