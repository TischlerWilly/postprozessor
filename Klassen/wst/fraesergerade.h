#ifndef FRAESERGERADE_H
#define FRAESERGERADE_H

#include <QString>

#include "Klassen/text_zw.h"
#include "Klassen/geo/strecke.h"
#include "Funktionen/umwandeln.h"
#include "Defines/def_bearbeitungen.h"

class fraesergerade
{
public:
    fraesergerade();
    fraesergerade(QString text);

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
    void set_tiSta(double tiefe);
    void set_tiSta(QString tiefe);
    void set_tiEnd(double tiefe);
    void set_tiEnd(QString tiefe);

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
    double  laenge_2d();
    QString bezug();
    QString afb();
    double tiSta();
    QString tiSta_qstring();
    double tiEnd();
    QString tiEnd_qstring();

    QString text();
    void set_text(QString text);
    strecke strecke_();

private:
    punkt3d Startpunkt, Endpunkt;
    QString Afb;
    QString Bezug;
    double TiSta, TiEnd;

    void setup();


};

#endif // FRAESERGERADE_H
