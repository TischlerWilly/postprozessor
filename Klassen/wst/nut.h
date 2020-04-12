#ifndef NUT_H
#define NUT_H

#include <QString>

#include "Klassen/text_zeilenweise.h"
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
    void set_xe(double x);
    void set_xe(QString x);
    void set_ye(double y);
    void set_ye(QString y);
    void set_bezug(QString bezugsflaeche);
    void set_afb(QString ausfuehrbedingung);

    double get_tiefe();
    QString get_tiefe_qstring();
    double get_breite();
    QString get_breite_qstring();
    double get_xs();
    QString get_xs_qstring();
    double get_ys();
    QString get_ys_qstring();
    double get_xe();
    QString get_xe_qstring();
    double get_ye();
    QString get_ye_qstring();
    QString get_bezug();
    QString get_afb();

    QString text();
    void set_text(QString text);

private:
    double tiefe;
    double breite;
    double pos_xs, pos_xe;
    double pos_ys, pos_ye;
    QString bezug;
    QString afb;


    void setup();

};

#endif // NUT_H
