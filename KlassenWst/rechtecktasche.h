#ifndef RECHTECKTASCHE_H
#define RECHTECKTASCHE_H

#include <QString>

#include "../allgemKlassen/text_zeilenweise.h"
#include "../Definitionen/def_bearbeitungen.h"
#include "../eigeneFunktionen/umwandeln.h"


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

    double get_laenge();
    QString get_laenge_qstring();
    double get_breite();
    QString get_breite_qstring();
    double get_tiefe();
    QString get_tiefe_qstring();
    double get_x();
    QString get_x_qstring();
    double get_y();
    QString get_y_qstring();
    double get_z();
    QString get_z_qstring();
    double get_drewi();
    QString get_drewi_qstring();
    double get_rad();
    QString get_rad_qstring();
    double get_zustellmass();
    QString get_zustellmass_qstring();
    bool get_ausraeumen();
    QString get_ausraeumen_qstring();
    QString get_bezug();
    QString get_afb();
    QString get_wkznum();

    QString get_text();
    void set_text(QString text);

private:
    double laenge;
    double breite;
    double tiefe;
    double pos_x;
    double pos_y;
    double pos_z;
    double drewinkel;
    double eckenradius;
    double zustellmass;
    bool ausraeumen;
    QString bezug;
    QString afb;
    QString werkzeugnummer;

    void setup();

};

#endif // RECHTECKTASCHE_H
