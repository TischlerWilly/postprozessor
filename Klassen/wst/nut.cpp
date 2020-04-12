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
    tiefe = 0;
    breite = 0;
    pos_xs = 0;
    pos_ys = 0;
    pos_xe = 0;
    pos_ye = 0;
    bezug = WST_BEZUG_OBSEI;
    afb = "1";
}

void nut::set_tiefe(double ti)
{
    if(ti > 0)
    {
        tiefe = ti;
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
        breite = b;
    }
}
void nut::set_breite(QString b)
{
    set_breite(b.toDouble());
}
void nut::set_xs(double x)
{
    pos_xs = x;
}
void nut::set_xs(QString x)
{
    set_xs(x.toDouble());
}
void nut::set_ys(double y)
{
    pos_ys = y;
}
void nut::set_ys(QString y)
{
    set_ys(y.toDouble());
}
void nut::set_xe(double x)
{
    pos_xe = x;
}
void nut::set_xe(QString x)
{
    set_xe(x.toDouble());
}
void nut::set_ye(double y)
{
    pos_ye = y;
}
void nut::set_ye(QString y)
{
    set_ye(y.toDouble());
}
void nut::set_bezug(QString bezugsflaeche)
{
    bezug = bezugsflaeche;
}
void nut::set_afb(QString ausfuehrbedingung)
{
    afb = ausfuehrbedingung;
}

double nut::get_tiefe()
{
    return tiefe;
}
QString nut::get_tiefe_qstring()
{
    return double_to_qstring(tiefe);
}
double nut::get_breite()
{
    return breite;
}
QString nut::get_breite_qstring()
{
    return double_to_qstring(breite);
}
double nut::get_xs()
{
    return pos_xs;
}
QString nut::get_xs_qstring()
{
    return double_to_qstring(pos_xs);
}
double nut::get_ys()
{
    return pos_ys;
}
QString nut::get_ys_qstring()
{
    return double_to_qstring(pos_ys);
}
double nut::get_xe()
{
    return pos_xe;
}
QString nut::get_xe_qstring()
{
    return double_to_qstring(pos_xe);
}
double nut::get_ye()
{
    return pos_ye;
}
QString nut::get_ye_qstring()
{
    return double_to_qstring(pos_ye);
}
QString nut::get_bezug()
{
    return bezug;
}
QString nut::get_afb()
{
    return afb;
}







QString nut::get_text()
{
    QString msg = BEARBART_NUT;    //Zeile 1
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_bezug();            //Zeile 2
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_xs_qstring();       //Zeile 3
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_ys_qstring();       //Zeile 4
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_xe_qstring();       //Zeile 5
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_ye_qstring();       //Zeile 6
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_tiefe_qstring();    //Zeile 7
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_breite_qstring();   //Zeile 8
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_afb();              //Zeile 9

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
        set_xe(tz.zeile(5));
        set_ye(tz.zeile(6));
        set_tiefe(tz.zeile(7));
        set_breite(tz.zeile(8));
        set_afb(tz.zeile(9));
    }
}






