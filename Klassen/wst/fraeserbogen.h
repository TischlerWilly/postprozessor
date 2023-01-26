#ifndef FRAESERBOGEN_H
#define FRAESERBOGEN_H

#include <QString>

#include "Klassen/text_zw.h"
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
        Startpunkt = p;
    }
    inline void set_endpunkt(punkt3d p)
    {
        Endpunkt = p;
    }

    double  xs();
    QString xs_qstring();
    double  xe();
    QString xe_qstring();
    double  ys();
    QString ys_qstring();
    double  ye();
    QString ye_qstring();
    double  zs();
    QString zs_qstring();
    double  ze();
    QString ze_qstring();
    punkt3d sp();
    punkt3d ep();
    QString bezug();
    QString afb();
    double  rad();
    QString rad_qstring();
    bool    uzs();
    QString uzs_qstring();

    inline punkt3d stapu()
    {
        return Startpunkt;
    }
    inline punkt3d endpu()
    {
        return Endpunkt;
    }

    QString text();
    void set_text(QString text);

private:
    punkt3d Startpunkt, Endpunkt;  //das Z-Maß ist die Frästiefe bezogen auf die WST-Oberfläche
    bool Uzs;
    double Radius;
    QString Afb;
    QString Bezug;

    void setup();

};

#endif // FRAESERBOGEN_H
