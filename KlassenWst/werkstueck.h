#ifndef WERKSTUECK_H
#define WERKSTUECK_H

#include <QString>
#include <QMessageBox>

#include "Definitionen/werkzeug.h"

#include "../eigeneFunktionen/umwandeln.h"
#include "../eigeneFunktionen/runden.h"
#include "../eigeneFunktionen/myfunktion.h"
#include "../Definitionen/def_fmc.h"
#include "../Definitionen/def_ganx.h"
#include "../allgemKlassen/text_zeilenweise.h"
#include "../werkzeugmagazin.h"
#include "bohrung.h"
#include "rechtecktasche.h"
#include "nut.h"
#include "fraueseraufruf.h"
#include "fraesergerade.h"
#include "fraeserbogen.h"


class werkstueck
{
public:
    werkstueck();
    werkstueck(QString neuer_name);

    void set_laenge(double l);
    void set_laenge(QString l);
    void set_breite(double b);
    void set_breite(QString b);
    void set_dicke(double d);
    void set_dicke(QString d);
    void neue_bearbeitung(QString text);

    inline void set_name(QString neuer_name)
    {
        name = neuer_name;
    }

    inline double get_laenge() const
    {
        return laenge;
    }
    inline QString get_laenge_qstring() const
    {
        return double_to_qstring(laenge);
    }
    inline double get_breite() const
    {
        return breite;
    }
    inline QString get_breite_qstring() const
    {
        return double_to_qstring(breite);
    }
    inline double get_dicke() const
    {
        return dicke;
    }
    inline QString get_dicke_qstring() const
    {
        return double_to_qstring(dicke);
    }
    inline QString get_name()
    {
        return name;
    } 
    inline text_zeilenweise get_bearb()
    {
        return bearbeitungen;
    }

    QString get_fmc(text_zeilenweise wkzmagazin, QString& info, QString drehwinkel = "0", QString zust_fkon = "orgi");
    QString get_ganx(text_zeilenweise wkzmagazin, QString& info ,QString drehwinkel = "0");
    QString get_eigenses_format(QString drehwinkel);

    QString suche_cad_fehler();

private:
    //Variabeln:
    double laenge;  //X-Wert
    double breite;  //Y-Wert
    double dicke;   //Z-Wert
    text_zeilenweise bearbeitungen;
    QString name;
    double schwellenwert_ay = 230; //für fmc-Ausgabe, bis zu dieser Breite wird mit ay-Versatz ausgegeben

    //Funktionen:


    QString warnungen_ganx(text_zeilenweise bearbeit,double tmp_l, double tmp_b, text_zeilenweise wkzmagazin);
    QString warnungen_fmc(text_zeilenweise bearbeit,double tmp_l, double tmp_b, text_zeilenweise wkzmagazin);
    QString fehler_kein_WKZ(QString exportformat, text_zeilenweise bearbeitung);
    QString get_bearb_menschlich_lesbar(text_zeilenweise bearbeitung);

    void bearb_sortieren();
    text_zeilenweise bearb_drehen_90(text_zeilenweise bearb, double& tmp_l, double& tmp_b);
    text_zeilenweise bearb_optimieren_ganx(text_zeilenweise bearb);

    QString get_fmc_dateitext(text_zeilenweise wkzmagazin,text_zeilenweise bearb , \
                              double tmp_l, double tmp_b, QString zust_fkon);
    QString get_ganx_dateitext(text_zeilenweise wkzmagazin,text_zeilenweise bearb ,double tmp_l, double tmp_b);
    QString get_eigen_dateitext(text_zeilenweise bearb ,double tmp_l, double tmp_b);

    QString kommentar_fmc(QString kom);

    bool punkt_auf_wst(double x, double y, double l, double b, double tolleranz);
};

#endif // WERKSTUECK_H
