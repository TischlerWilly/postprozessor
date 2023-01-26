#ifndef RECHTECKTASCHE_H
#define RECHTECKTASCHE_H

#include <QString>

#include "Klassen/text_zw.h"
#include "Defines/def_bearbeitungen.h"
#include "Funktionen/umwandeln.h"


class rechtecktasche
{
public:
    rechtecktasche();
    rechtecktasche(QString text);

    void set_laenge(double l);
    void set_laenge(QString l);
    void set_breite(double b);
    void set_breite(QString b);
    void set_tiefe(double t);
    void set_tiefe(QString t);
    void set_x(double x);
    void set_x(QString x);
    void set_y(double y);
    void set_y(QString y);
    void set_z(double z);
    void set_z(QString z);
    void set_drewi(double wi);
    void set_drewi(QString wi);
    void set_rad(double r);
    void set_rad(QString r);
    void set_zustellmass(double mass);
    void set_zustellmass(QString mass);
    void set_ausraeumen(double ja);
    void set_ausraeumen(QString ja);
    void set_bezug(QString bezugsflaeche);
    void set_afb(QString ausfuehrbedingung);
    void set_wkznum(QString nummer);

    double  laenge();
    QString laenge_qstring();
    double  breite();
    QString breite_qstring();
    double  tiefe();
    QString tiefe_qstring();
    double  x();
    QString x_qstring();
    double  y();
    QString y_qstring();
    double  z();
    QString z_qstring();
    double  drewi();
    QString drewi_qstring();
    double  rad();
    QString rad_qstring();
    double  zustellmass();
    QString zustellmass_qstring();
    bool    ausraeumen();
    QString ausraeumen_qstring();
    QString bezug();
    QString afb();
    QString wkznum();

    QString text();
    void set_text(QString text);

private:
    double Laenge;
    double Breite;
    double Tiefe;
    double Pos_x;
    double Pos_y;
    double Pos_z;
    double Drewinkel;
    double Eckenradius;
    double Zustellmass;
    bool Ausraeumen;
    QString Bezug;
    QString Afb;
    QString Werkzeugnummer;

    void setup();

};

#endif // RECHTECKTASCHE_H
