#ifndef WERKSTUECK_H
#define WERKSTUECK_H

#include <QString>
#include <QMessageBox>

#include "Definitionen/werkzeug.h"

#include "../eigeneFunktionen/umwandeln.h"
#include "../Definitionen/def_fmc.h"
#include "../allgemKlassen/text_zeilenweise.h"
#include "bohrung.h"
#include "rechtecktasche.h"
#include "nut.h"


class werkstueck
{
public:
    werkstueck();

    void set_laenge(double l);
    void set_laenge(QString l);
    void set_breite(double b);
    void set_breite(QString b);
    void set_dicke(double d);
    void set_dicke(QString d);
    void neue_bearbeitung(QString text);

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

    QString get_fmc(text_zeilenweise werkzeugmagazin, QString& info, QString drehwinkel = "0");
    QString get_ganx(text_zeilenweise werkzeugmagazin, QString& info ,QString drehwinkel = "0");
    QString get_eigenses_format(QString drehwinkel);

private:
    //Variabeln:
    double laenge;
    double breite;
    double dicke;
    text_zeilenweise bearbeitungen;

    //Funktionen:
    QString get_wkz_nummer(text_zeilenweise wkz_magazin, QString wkz_typ, double dm = 0, double bearbeitungstiefe = 0);
    QString get_wkz_dm(text_zeilenweise wkz_magazin, QString wkz_nr);
    QString get_wkz_vorschub(text_zeilenweise wkz_magazin, QString wkz_nr);

    QString warnungen_ganx(text_zeilenweise bearbeit,double tmp_l, double tmp_b);
    QString warnungen_fmc(text_zeilenweise bearbeit,double tmp_l, double tmp_b);

    void bearb_sortieren();
    text_zeilenweise bearb_drehen_90(text_zeilenweise bearb, double& tmp_l, double& tmp_b);
    text_zeilenweise bearb_optimieren_ganx(text_zeilenweise bearb);

    QString get_fmc_dateitext(text_zeilenweise werkzeugmagazin,text_zeilenweise bearb ,double tmp_l, double tmp_b);
    QString get_ganx_dateitext(text_zeilenweise werkzeugmagazin,text_zeilenweise bearb ,double tmp_l, double tmp_b);
    QString get_eigen_dateitext(text_zeilenweise bearb ,double tmp_l, double tmp_b);

};

#endif // WERKSTUECK_H
