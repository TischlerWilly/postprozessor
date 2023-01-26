#ifndef NUT_H
#define NUT_H

#include <QString>

#include "Klassen/text_zw.h"
#include "Defines/def_bearbeitungen.h"
#include "Funktionen/umwandeln.h"


class nut
{
public:
    nut();
    nut(QString text);

    void set_tiefe(double ti);
    void set_tiefe(QString ti);
    void set_breite(double b);
    void set_breite(QString b);
    void set_xs(double x);
    void set_xs(QString x);
    void set_ys(double y);
    void set_ys(QString y);
    void set_zs(double z);
    void set_zs(QString z);
    void set_xe(double x);
    void set_xe(QString x);
    void set_ye(double y);
    void set_ye(QString y);
    void set_ze(double z);
    void set_ze(QString z);
    void set_bezug(QString bezugsflaeche);
    void set_afb(QString ausfuehrbedingung);

    double  tiefe();
    QString tiefe_qstring();
    double  breite();
    QString breite_qstring();
    double  xs();
    QString xs_qstring();
    double  ys();
    QString ys_qstring();
    double  zs();
    QString zs_qstring();
    double  xe();
    QString xe_qstring();
    double  ye();
    QString ye_qstring();
    double  ze();
    QString ze_qstring();
    QString bezug();
    QString afb();

    QString text();
    void set_text(QString text);

private:
    double Tiefe;
    double Breite;
    double Pos_xs, Pos_xe;
    double Pos_ys, Pos_ye;
    double Pos_zs, Pos_ze;
    QString Bezug;
    QString Afb;


    void setup();

};

#endif // NUT_H
