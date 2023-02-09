#include "fraesergerade.h"

fraesergerade::fraesergerade()
{
    setup();
}

fraesergerade::fraesergerade(QString text)
{
    setup();
    set_text(text);
}

void fraesergerade::setup()
{
    Afb = "1";
    Bezug = WST_BEZUG_OBSEI;
}

void fraesergerade::set_xs(double x)
{
    Startpunkt.set_x(x);
}
void fraesergerade::set_xs(QString x)
{
    Startpunkt.set_x(x);
}
void fraesergerade::set_xe(double x)
{
    Endpunkt.set_x(x);
}
void fraesergerade::set_xe(QString x)
{
    Endpunkt.set_x(x);
}

void fraesergerade::set_ys(double y)
{
    Startpunkt.set_y(y);
}
void fraesergerade::set_ys(QString y)
{
    Startpunkt.set_y(y);
}
void fraesergerade::set_ye(double y)
{
    Endpunkt.set_y(y);
}
void fraesergerade::set_ye(QString y)
{
    Endpunkt.set_y(y);
}

void fraesergerade::set_zs(double z)
{
    Startpunkt.set_z(z);
}
void fraesergerade::set_zs(QString z)
{
    Startpunkt.set_z(z);
}
void fraesergerade::set_ze(double z)
{
    Endpunkt.set_z(z);
}
void fraesergerade::set_ze(QString z)
{
    Endpunkt.set_z(z);
}

double fraesergerade::xs()
{
    return Startpunkt.x();
}
QString fraesergerade::xs_qstring()
{
    return Startpunkt.x_QString();
}
double fraesergerade::xe()
{
    return Endpunkt.x();
}
QString fraesergerade::xe_qstring()
{
    return Endpunkt.x_QString();
}

double fraesergerade::ys()
{
    return Startpunkt.y();
}
QString fraesergerade::ys_qstring()
{
    return Startpunkt.y_QString();
}
double fraesergerade::ye()
{
    return Endpunkt.y();
}
QString fraesergerade::ye_qstring()
{
    return Endpunkt.y_QString();
}

double fraesergerade::zs()
{
    return Startpunkt.z();
}
QString fraesergerade::zs_qstring()
{
    return Startpunkt.z_QString();
}
double fraesergerade::ze()
{
    return Endpunkt.z();
}
QString fraesergerade::ze_qstring()
{
    return Endpunkt.z_QString();
}

punkt3d fraesergerade::sp()
{
    return Startpunkt;
}
punkt3d fraesergerade::ep()
{
    return Endpunkt;
}

double fraesergerade::laenge_2d()
{
    strecke s;
    s.set_stapu(Startpunkt);
    s.set_endpu(Endpunkt);

    return s.laenge2d();
}

void fraesergerade::set_bezug(QString bezugsflaeche)
{
    Bezug = bezugsflaeche;
}
void fraesergerade::set_afb(QString ausfuehrbedingung)
{
    Afb = ausfuehrbedingung;
}

QString fraesergerade::bezug()
{
    return Bezug;
}
QString fraesergerade::afb()
{
    return Afb;
}

QString fraesergerade::text()
{
    QString msg = BEARBART_FRAESERGERADE;    //Zeile 0
    msg += TRENNZ_BEARB_PARAM_;
    msg += bezug();                      //Zeile 1
    msg += TRENNZ_BEARB_PARAM_;
    msg += xs_qstring();                 //Zeile 2
    msg += TRENNZ_BEARB_PARAM_;
    msg += ys_qstring();                 //Zeile 3
    msg += TRENNZ_BEARB_PARAM_;
    msg += zs_qstring();                 //Zeile 4
    msg += TRENNZ_BEARB_PARAM_;
    msg += xe_qstring();                 //Zeile 5
    msg += TRENNZ_BEARB_PARAM_;
    msg += ye_qstring();                 //Zeile 6
    msg += TRENNZ_BEARB_PARAM_;
    msg += ze_qstring();                 //Zeile 7
    msg += TRENNZ_BEARB_PARAM_;
    msg += afb();                        //Zeile 8

    return msg;
}
void fraesergerade::set_text(QString text)
{
    text_zw tz;
    tz.set_text(text,TRENNZ_BEARB_PARAM);
    if(tz.at(0) == BEARBART_FRAESERGERADE)
    {
        set_bezug(tz.at(1));
        set_xs(tz.at(2));
        set_ys(tz.at(3));
        set_zs(tz.at(4));
        set_xe(tz.at(5));
        set_ye(tz.at(6));
        set_ze(tz.at(7));
        set_afb(tz.at(8));
    }
}

strecke fraesergerade::strecke_()
{
    strecke s;
    s.set_stapu(Startpunkt);
    s.set_endpu(Endpunkt);
    return s;
}













