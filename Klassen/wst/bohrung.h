#ifndef BOHRUNG_H
#define BOHRUNG_H

#include <QString>

#include "Klassen/text_zeilenweise.h"
#include "Defines/def_bearbeitungen.h"
#include "Funktionen/umwandeln.h"
#include "Klassen/geo/punkt3d.h"

class bohrung
{
public:
    bohrung();
    bohrung(QString text);

    void set_dm(double dm);
    void set_dm(QString dm);
    void set_tiefe(double ti);
    void set_tiefe(QString ti);
    void set_x(double x);
    void set_x(QString x);
    void set_y(double y);
    void set_y(QString y);
    void set_z(double z);
    void set_z(QString z);
    void set_zustellmass(double mass);
    void set_zustellmass(QString mass);
    void set_bezug(QString bezugsflaeche);
    void set_afb(QString ausfuehrbedingung);
    void set_wkznum(QString nummer);

    double  dm();
    QString dm_qstring();
    double  tiefe();
    QString tiefe_qstring();
    double  x();
    QString x_qstring();
    double  y();
    QString y_qstring();
    double  z();
    QString z_qstring();
    punkt3d  mipu();
    double  zustellmass();
    QString zustellmass_qstring();
    QString bezug();
    QString afb();
    QString wkznum();

    QString text();
    void set_text(QString text);


protected:
    double Durchmesser;
    double Tiefe;
    double Pos_x;
    double Pos_y;
    double Pos_z;
    QString Bezug;
    QString Afb;
    double Zustellmass;
    QString Werkzeugnummer;

    void setup();

};

#endif // BOHRUNG_H
