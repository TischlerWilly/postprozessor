#ifndef FRAESERBOGEN_H
#define FRAESERBOGEN_H

#include <QString>

#include "Klassen/text_zeilenweise.h"
#include "Klassen/geo/punkt3d.h"
#include "Funktionen/umwandeln.h"
#include "Defines/def_bearbeitungen.h"

class fraeserbogen
{
public:
    fraeserbogen();
    fraeserbogen(QString text);

    void set_xs(double x);
    void set_xs(QString x);
    void set_xe(double x);
    void set_xe(QString x);
    void set_ys(double y);
    void set_ys(QString y);
    void set_ye(double y);
    void set_ye(QString y);
    void set_zs(double z);
    void set_zs(QString z);
    void set_ze(double z);
    void set_ze(QString z);
    void set_bezug(QString bezugsflaeche);
    void set_afb(QString ausfuehrbedingung);
    void set_rad(double rad);
    void set_rad(QString rad);
    void set_uzs(bool ist_im_uzs);
    void set_uzs(QString ist_im_uzs);

    inline void set_startpunkt(punkt3d p)
    {
        startpunkt = p;
    }
    inline void set_endpunkt(punkt3d p)
    {
        endpunkt = p;
    }

    double get_xs();
    QString get_xs_qstring();
    double get_xe();
    QString get_xe_qstring();
    double get_ys();
    QString get_ys_qstring();
    double get_ye();
    QString get_ye_qstring();
    double get_zs();
    QString get_zs_qstring();
    double get_ze();
    QString get_ze_qstring();
    punkt3d get_sp();
    punkt3d get_ep();
    QString get_bezug();
    QString get_afb();
    double get_rad();
    QString get_rad_qstring();
    bool get_uzs();
    QString get_uzs_qstring();

    QString text();
    void set_text(QString text);

private:
    punkt3d startpunkt, endpunkt;  //das Z-Maß ist die Frästiefe bezogen auf die WST-Oberfläche
    bool uzs;
    double radius;
    QString afb;
    QString bezug;

    void setup();

};

#endif // FRAESERBOGEN_H