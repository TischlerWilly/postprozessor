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
    Stapu.set_x(x);
}
void nut::set_xs(QString x)
{
    Stapu.set_x(x);
}
void nut::set_ys(double y)
{
    Stapu.set_y(y);
}
void nut::set_ys(QString y)
{
    Stapu.set_y(y);
}
void nut::set_zs(double z)
{
    Stapu.set_z(z);
}
void nut::set_zs(QString z)
{
    Stapu.set_z(z);
}
void nut::set_xe(double x)
{
    Endpu.set_x(x);
}
void nut::set_xe(QString x)
{
    Endpu.set_x(x);
}
void nut::set_ye(double y)
{
    Endpu.set_y(y);
}
void nut::set_ye(QString y)
{
    Endpu.set_y(y);
}
void nut::set_ze(double z)
{
    Endpu.set_z(z);
}
void nut::set_ze(QString z)
{
    Endpu.set_z(z);
}
void nut::set_stapu(punkt3d p)
{
    Stapu = p;
}
void nut::set_endpu(punkt3d p)
{
    Endpu = p;
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
    return Stapu.x();
}
QString nut::xs_qstring()
{
    return Stapu.x_QString();
}
double nut::ys()
{
    return Stapu.y();
}
QString nut::ys_qstring()
{
    return Stapu.y_QString();
}
double nut::zs()
{
    return Stapu.z();
}
QString nut::zs_qstring()
{
    return Stapu.z_QString();
}
double nut::xe()
{
    return Endpu.x();
}
QString nut::xe_qstring()
{
    return Endpu.x_QString();
}
double nut::ye()
{
    return Endpu.y();
}
QString nut::ye_qstring()
{
    return Endpu.y_QString();
}
double nut::ze()
{
    return Endpu.z();
}
QString nut::ze_qstring()
{
    return Endpu.z_QString();
}
punkt3d nut::stapu()
{
    return Stapu;
}
punkt3d nut::endpu()
{
    return Endpu;
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
    text_zw tz;
    tz.set_text(text,TRENNZ_BEARB_PARAM);
    if(tz.at(0) == BEARBART_NUT)
    {
        set_bezug(tz.at(1));
        set_xs(tz.at(2));
        set_ys(tz.at(3));
        set_zs(tz.at(4));
        set_xe(tz.at(5));
        set_ye(tz.at(6));
        set_ze(tz.at(7));
        set_tiefe(tz.at(8));
        set_breite(tz.at(9));
        set_afb(tz.at(10));
    }
}






