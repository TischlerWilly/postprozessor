#ifndef FRAESERAUFRUF_H
#define FRAESERAUFRUF_H

#include <QString>

#include "Klassen/text_zw.h"
#include "Defines/def_bearbeitungen.h"
#include "Funktionen/umwandeln.h"
#include "Klassen/geo/punkt3d.h"

#define FAUFRUF_ANABTYP_NDEF   "-1"
#define FAUFRUF_ANABTYP_GARADE  "1"
#define FAUFRUF_ANABTYP_BOGEN   "2"
#define FAUFRUF_ANABWEG_AUTO   "AUTO"

class fraeseraufruf
{
public:
    fraeseraufruf();
    fraeseraufruf(QString text);

    void set_x(double x);
    void set_x(QString x);
    void set_y(double y);
    void set_y(QString y);
    void set_z(double z);
    void set_z(QString z);
    void set_pos(punkt3d p);
    void set_tiefe(double ti);
    void set_tiefe(QString ti);
    void set_bezug(QString bezugsflaeche);
    void set_afb(QString ausfuehrbedingung);
    void set_radkor(QString kor);
    void set_wkznum(QString nummer);
    void set_anfahrtyp(QString typ);
    void set_abfahrtyp(QString typ);
    void set_anfahrweg(QString laenge);
    void set_anfahrweg(double laenge);
    void set_abfahrweg(QString laenge);
    void set_abfahrweg(double laenge);

    double  x();
    QString x_qstring();
    double  y();
    QString y_qstring();
    double  z();
    QString z_qstring();
    double  tiefe();
    QString tiefe_qstring();
    QString bezug();
    QString afb();
    QString radkor();
    QString wkznum();
    punkt3d pos();
    QString anfahrtyp();
    QString abfahrtyp();
    double anfahrweg();
    QString anfahrweg_qstring();
    double abfahrweg();
    QString abfahrweg_qstring();

    QString text();
    void set_text(QString text);

private:
    punkt3d Pos; //Der Z-Wert wird benutzt für horizontale Fräsungen
    double Tiefe;   //ist die Eintauchtiefe = Oberfläche-Wst bis gesamte Bahntiefe
    QString Bezug;
    QString Afb;
    QString Korrektur;
    QString Werkzeugnummer;
    QString Anfahrtyp;
    QString Abfahrtyp;
    QString Anfahrweg;
    QString Abfahrweg;

    void setup();

};

#endif // FRAESERAUFRUF_H
