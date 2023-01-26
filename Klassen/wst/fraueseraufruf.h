#ifndef FRAUESERAUFRUF_H
#define FRAUESERAUFRUF_H

#include <QString>

#include "Klassen/text_zw.h"
#include "Defines/def_bearbeitungen.h"
#include "Funktionen/umwandeln.h"
#include "Klassen/geo/punkt3d.h"

class fraueseraufruf
{
public:
    fraueseraufruf();
    fraueseraufruf(QString text);

    void set_x(double x);
    void set_x(QString x);
    void set_y(double y);
    void set_y(QString y);
    void set_z(double z);
    void set_z(QString z);
    void set_tiefe(double ti);
    void set_tiefe(QString ti);
    void set_bezug(QString bezugsflaeche);
    void set_afb(QString ausfuehrbedingung);
    void set_radkor(QString kor);
    void set_wkznum(QString nummer);

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
    punkt3d pos_vertikal();

    QString text();
    void set_text(QString text);

private:
    double Pos_x;
    double Pos_y;
    double Pos_z;   //für horizontale Fräseraufrufe
    double Tiefe;   //ist die Eintauchtiefe = Oberfläche-Wst bis gesamte Bahntiefe
    QString Bezug;
    QString Afb;
    QString Korrektur;
    QString Werkzeugnummer;

    void setup();

};

#endif // FRAUESERAUFRUF_H
