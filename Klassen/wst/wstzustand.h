#ifndef WSTZUSTAND_H
#define WSTZUSTAND_H

#include <QVector>
#include <QMessageBox>

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
#include "Funktionen/umwandeln.h"
#include "Klassen/wst/ganx_gruppen.h"
#include "Funktionen/runden.h"
#include "Klassen/einstellung_ganx.h"

class wstzustand
{
public:
    wstzustand();
    //----------------------------------set_xy:
    void set_bearb(text_zeilenweise bearb);
    void set_laenge(double l);
    void set_breite(double b);
    void set_dicke(double d);
    void set_kante_vo(QString artiklenummer);
    void set_kante_hi(QString artiklenummer);
    void set_kante_li(QString artiklenummer);
    void set_kante_re(QString artiklenummer);
    void set_zugabe_gehrungen(double zugabe);
    void set_formartierungen_aufbrechen(bool jn);
    void set_name(QString neuer_name);
    void set_zust_fkon(QString zust);
    void set_einst_ganx(einstellung_ganx e);

    //----------------------------------get_xy:
    inline int count()
    {
        return Format.count();
    }
    inline geometrietext geo()
    {
        if(Akt_zust != -1 && Akt_zust<Geotext.count())
        {
            return Geotext.at(Akt_zust);
        }else
        {
            geometrietext tmp;
            return tmp;
        }
    }
    inline QString exporttext()
    {
        if(Akt_zust != -1 && Akt_zust<Exporttext.count())
        {
            return Exporttext.at(Akt_zust);
        }else
        {
            return "";
        }
    }
    inline QString format()
    {
        if(Akt_zust != -1 && Akt_zust<Exporttext.count())
        {
            return Format.at(Akt_zust);
        }else
        {
            return "";
        }
    }
    inline QString warnungen()
    {
        if(Akt_zust != -1 && Akt_zust<Exporttext.count())
        {
            return Warnungen.at(Akt_zust);
        }else
        {
            return "";
        }
    }
    inline double l()
    {
        if(Akt_zust != -1 && Akt_zust<Laenge.count())
        {
            return Laenge.at(Akt_zust);
        }else
        {
            return 0;
        }
    }
    inline double b()
    {
        if(Akt_zust != -1 && Akt_zust<Breite.count())
        {
            return Breite.at(Akt_zust);
        }else
        {
            return 0;
        }
    }
    inline double dicke()
    {
        return Dicke;
    }
    inline QString dicke_qstring()
    {
        return double_to_qstring(Dicke);
    }

    //----------------------------------Manipulationen:
    void anfordern(QString format, werkzeugmagazin wkzmag, QString drehung);

private:
    void clear();
    void erzeugen(QString format, werkzeugmagazin wkzmag, QString drehung);
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
    void eigen_dateitext(int index);
    void ganx_dateitext(int index);
    void ggf_dateitext(int index);
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
    QVector<QString>            Drehung_bekommen;    
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

    text_zeilenweise    Bearbeitung_bekommen;
    double              Laenge_bekommen;
    double              Breite_bekommen;
    double              Zugabe_gehrungen;
    bool                Formartierungen_aufbrechen;
    QString             Kante_vo; //Kante an X
    QString             Kante_hi;
    QString             Kante_li; //Kante an Y
    QString             Kante_re;
    double              Schwellenwert_ay; //für fmc-Ausgabe, bis zu dieser Breite wird mit ay-Versatz ausgegeben
    double              Dicke;
    QString             Name;
    QString             Zust_fkon;
    int                 Akt_zust;
    einstellung_ganx    Eganx;
};

#endif // WSTZUSTAND_H
