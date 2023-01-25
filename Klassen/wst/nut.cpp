#include "nut.h"

nut::nut()
{
    setup();
}
nut::nut(QString text)
{
    setup();
    set_text(text);
}

void nut::setup()
{
    Tiefe = 0;
    Breite = 0;
    Pos_xs = 0;
    Pos_ys = 0;
    Pos_zs = 0;
    Pos_xe = 0;
    Pos_ye = 0;
    Pos_ze = 0;
    Bezug = WST_BEZUG_OBSEI;
    Afb = "1";
}

void nut::set_tiefe(double ti)
{
    if(ti > 0)
    {
        Tiefe = ti;
    }
}
void nut::set_tiefe(QString ti)
{
    set_tiefe(ti.toDouble());
}
void nut::set_breite(double b)
{
    if(b > 0)
    {
        Breite = b;
    }
}
void nut::set_breite(QString b)
{
    set_breite(b.toDouble());
}
void nut::set_xs(double x)
{
    Pos_xs = x;
}
void nut::set_xs(QString x)
{
    set_xs(x.toDouble());
}
void nut::set_ys(double y)
{
    Pos_ys = y;
}
void nut::set_ys(QString y)
{
    set_ys(y.toDouble());
}
void nut::set_zs(double z)
{
    Pos_zs = z;
}
void nut::set_zs(QString z)
{
    set_zs(z.toDouble());
}
void nut::set_xe(double x)
{
    Pos_xe = x;
}
void nut::set_xe(QString x)
{
    set_xe(x.toDouble());
}
void nut::set_ye(double y)
{
    Pos_ye = y;
}
void nut::set_ye(QString y)
{
    set_ye(y.toDouble());
}
void nut::set_ze(double z)
{
    Pos_ze = z;
}
void nut::set_ze(QString z)
{
    set_ze(z.toDouble());
}
void nut::set_bezug(QString bezugsflaeche)
{
    Bezug = bezugsflaeche;
}
void nut::set_afb(QString ausfuehrbedingung)
{
    Afb = ausfuehrbedingung;
}

double nut::tiefe()
{
    return Tiefe;
}
QString nut::tiefe_qstring()
{
    return double_to_qstring(Tiefe);
}
double nut::breite()
{
    return Breite;
}
QString nut::breite_qstring()
{
    return double_to_qstring(Breite);
}
double nut::xs()
{
    return Pos_xs;
}
QString nut::xs_qstring()
{
    return double_to_qstring(Pos_xs);
}
double nut::ys()
{
    return Pos_ys;
}
QString nut::ys_qstring()
{
    return double_to_qstring(Pos_ys);
}
double nut::zs()
{
    return Pos_zs;
}
QString nut::zs_qstring()
{
    return double_to_qstring(Pos_zs);
}
double nut::xe()
{
    return Pos_xe;
}
QString nut::xe_qstring()
{
    return double_to_qstring(Pos_xe);
}
double nut::ye()
{
    return Pos_ye;
}
QString nut::ye_qstring()
{
    return double_to_qstring(Pos_ye);
}
double nut::ze()
{
    return Pos_ze;
}
QString nut::ze_qstring()
{
    return double_to_qstring(Pos_ze);
}
QString nut::bezug()
{
    return Bezug;
}
QString nut::afb()
{
    return Afb;
}







QString nut::text()
{
    QString msg = BEARBART_NUT;    //Zeile 1
    msg += TRENNZ_BEARB_PARAM_;
    msg += bezug();            //Zeile 2
    msg += TRENNZ_BEARB_PARAM_;
    msg += xs_qstring();       //Zeile 3
    msg += TRENNZ_BEARB_PARAM_;
    msg += ys_qstring();       //Zeile 4
    msg += TRENNZ_BEARB_PARAM_;
    msg += zs_qstring();       //Zeile 5
    msg += TRENNZ_BEARB_PARAM_;
    msg += xe_qstring();       //Zeile 6
    msg += TRENNZ_BEARB_PARAM_;
    msg += ye_qstring();       //Zeile 7
    msg += TRENNZ_BEARB_PARAM_;
    msg += ze_qstring();       //Zeile 8
    msg += TRENNZ_BEARB_PARAM_;
    msg += tiefe_qstring();    //Zeile 9
    msg += TRENNZ_BEARB_PARAM_;
    msg += breite_qstring();   //Zeile 10
    msg += TRENNZ_BEARB_PARAM_;
    msg += afb();              //Zeile 11

    return msg;
}
void nut::set_text(QString text)
{
    text_zeilenweise tz;
    tz.set_trennzeichen(TRENNZ_BEARB_PARAM);
    tz.set_text(text);
    if(tz.zeile(1) == BEARBART_NUT)
    {
        set_bezug(tz.zeile(2));
        set_xs(tz.zeile(3));
        set_ys(tz.zeile(4));
        set_zs(tz.zeile(5));
        set_xe(tz.zeile(6));
        set_ye(tz.zeile(7));
        set_ze(tz.zeile(8));
        set_tiefe(tz.zeile(9));
        set_breite(tz.zeile(10));
        set_afb(tz.zeile(11));
    }
}






