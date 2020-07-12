#ifndef WERKSTUECK_H
#define WERKSTUECK_H

#include <QString>
#include <QMessageBox>

#include "Defines/werkzeug.h"

#include "Funktionen/umwandeln.h"
#include "Funktionen/runden.h"
#include "Funktionen/myfunktion.h"
#include "Defines/def_fmc.h"
#include "Defines/def_ganx.h"
#include "Klassen/text_zeilenweise.h"
#include "../werkzeugmagazin.h"
#include "bohrung.h"
#include "rechtecktasche.h"
#include "nut.h"
#include "fraueseraufruf.h"
#include "fraesergerade.h"
#include "fraeserbogen.h"
#include "bohrraster.h"
#include "Defines/dateinamen.h"
#include "ganx_gruppen.h"
#include "gehrung.h"


class werkstueck
{
public:
    werkstueck();
    werkstueck(QString neuer_name);

    //--------------------------------------------------set_xy:
    void set_laenge(double l);
    void set_laenge(QString l);
    void set_breite(double b);
    void set_breite(QString b);
    void set_dicke(double d);
    void set_dicke(QString d);
    void neue_bearbeitung(QString text);
    void set_kante_vo(QString artiklenummer);
    void set_kante_hi(QString artiklenummer);
    void set_kante_li(QString artiklenummer);
    void set_kante_re(QString artiklenummer);

    inline void set_name(QString neuer_name)
    {
        Name = neuer_name;
    }

    //--------------------------------------------------get_xy:
    QString kante_vo(QString drewi = "0");
    QString kante_hi(QString drewi = "0");
    QString kante_li(QString drewi = "0");
    QString kante_re(QString drewi = "0");
    QString kante_vo_ganx(QString drewi = "0");
    QString kante_hi_ganx(QString drewi = "0");
    QString kante_li_ganx(QString drewi = "0");
    QString kante_re_ganx(QString drewi = "0");
    QString cad_fehler();
    QString fmc(text_zeilenweise wkzmagazin, QString& info, \
                    QString drehwinkel = "0", QString zust_fkon = "orgi",\
                    bool formartierungen_aufbrechen = false,\
                    bool fkon_kantenschonend = false);
    QString ganx(text_zeilenweise wkzmagazin, QString& info ,QString drehwinkel = "0");
    QString ggf(text_zeilenweise wkzmagazin, QString& info ,QString drehwinkel = "0");
    QString eigenses_format(QString drehwinkel, QString ausgabeformat, \
                                text_zeilenweise wkzmagazin,\
                                bool formartierungen_aufbrechen = false,\
                                bool fkon_kantenschonend = false);

    inline double   laenge() const
    {
        return Laenge;
    }
    inline QString  laenge_qstring() const
    {
        return double_to_qstring(Laenge);
    }
    inline double   breite() const
    {
        return Breite;
    }
    inline QString  breite_qstring() const
    {
        return double_to_qstring(Breite);
    }
    inline double   dicke() const
    {
        return Dicke;
    }
    inline QString  dicke_qstring() const
    {
        return double_to_qstring(Dicke);
    }
    inline QString  name()
    {
        return Name;
    }
    inline text_zeilenweise bearb()
    {
        return Bearbeitungen;
    }

    //--------------------------------------------------Manipulationen:

    //--------------------------------------------------

private:
    //Variabeln:
    double Laenge;  //X-Wert
    double Breite;  //Y-Wert
    double Dicke;   //Z-Wert
    text_zeilenweise Bearbeitungen;
    QString Name;
    double Schwellenwert_ay; //für fmc-Ausgabe, bis zu dieser Breite wird mit ay-Versatz ausgegeben
    QString Kante_vo; //Kante an X
    QString Kante_hi;
    QString Kante_li; //Kante an Y
    QString Kante_re;

    //Funktionen:
    //--------------------------------------------------set_xy:

    //--------------------------------------------------get_xy:
    QString warnungen_ganx(text_zeilenweise bearbeit,double tmp_l, double tmp_b, text_zeilenweise wkzmagazin);
    QString warnungen_fmc(text_zeilenweise bearbeit,double tmp_l, double tmp_b, text_zeilenweise wkzmagazin);
    QString warnungen_ggf(text_zeilenweise bearbeit,double tmp_l, double tmp_b, text_zeilenweise wkzmagazin);
    QString fehler_kein_WKZ(QString exportformat, text_zeilenweise bearbeitung);
    QString bearb_menschlich_lesbar(text_zeilenweise bearbeitung);
    QString fmc_dateitext(text_zeilenweise wkzmagazin,text_zeilenweise bearb , \
                          double tmp_l, double tmp_b, QString zust_fkon,\
                          QString drewi, bool formartierungen_aufbrechen,\
                          bool fkon_kantenschonend);
    QString ganx_dateitext(text_zeilenweise wkzmagazin,text_zeilenweise bearb ,\
                           double tmp_l, double tmp_b);
    QString ggf_dateitext(text_zeilenweise wkzmagazin,text_zeilenweise bearb ,\
                          double tmp_l, double tmp_b);
    QString eigen_dateitext(text_zeilenweise bearb ,double tmp_l, double tmp_b, \
                            QString ausgabeformat, text_zeilenweise wkzmagazin,\
                            bool formartierungen_aufbrechen,\
                            bool fkon_kantenschonend);
    QString kommentar_fmc(QString kom);
    QString kommentar_ggf(QString kom);
    QString fmc_kommentar_gute_seite(text_zeilenweise bearb);
    bool punkt_auf_wst(double x, double y, double l, double b, double tolleranz);

    //--------------------------------------------------Manipulationen:
    void bearb_sortieren();
    text_zeilenweise bearb_drehen_90(text_zeilenweise bearb, double& tmp_l, double& tmp_b);
    text_zeilenweise bearb_optimieren_ganx(text_zeilenweise bearb);
    text_zeilenweise rasterbohrungen_finden_ganx(text_zeilenweise bearb, text_zeilenweise wkzmagazin,double tmp_l, double tmp_b);
    text_zeilenweise rasterbohrungen_finden_fmc(text_zeilenweise bearb, text_zeilenweise wkzmagazin,double tmp_l, double tmp_b);
    text_zeilenweise formartierung_zu_einzelfkon(text_zeilenweise bearb,double tmp_l, double tmp_b);
    text_zeilenweise kurze_an_ab_geraden(text_zeilenweise bearb, text_zeilenweise wkzmagazin);
    text_zeilenweise dubosplitten(text_zeilenweise bearb, text_zeilenweise wkzmagazin, double wstdicke);
    text_zeilenweise fkon_kantengut(text_zeilenweise bearb, text_zeilenweise wkzmagazin,double tmp_l, double tmp_b);
    void hbemiduebeltiefe();
    void fraesergeraden_zusammenfassen();
    text_zeilenweise gehr_3achs(text_zeilenweise bearb, double& tmp_l, double& tmp_b);
    text_zeilenweise drehen_um_b_halbe(text_zeilenweise bearb, double &tmp_l, double &tmp_b);
    //--------------------------------------------------

};

#endif // WERKSTUECK_H
