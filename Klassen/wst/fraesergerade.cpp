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
    s.set_start(Startpunkt);
    s.set_ende(Endpunkt);

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
    QString msg = BEARBART_FRAESERGERADE;    //Zeile 1
    msg += TRENNZ_BEARB_PARAM_;
    msg += bezug();                      //Zeile 2
    msg += TRENNZ_BEARB_PARAM_;
    msg += xs_qstring();                 //Zeile 3
    msg += TRENNZ_BEARB_PARAM_;
    msg += ys_qstring();                 //Zeile 4
    msg += TRENNZ_BEARB_PARAM_;
    msg += zs_qstring();                 //Zeile 5
    msg += TRENNZ_BEARB_PARAM_;
    msg += xe_qstring();                 //Zeile 6
    msg += TRENNZ_BEARB_PARAM_;
    msg += ye_qstring();                 //Zeile 7
    msg += TRENNZ_BEARB_PARAM_;
    msg += ze_qstring();                 //Zeile 8
    msg += TRENNZ_BEARB_PARAM_;
    msg += afb();                        //Zeile 9

    return msg;
}
void fraesergerade::set_text(QString text)
{
    text_zeilenweise tz;
    tz.set_trennzeichen(TRENNZ_BEARB_PARAM);
    tz.set_text(text);
    if(tz.zeile(1) == BEARBART_FRAESERGERADE)
    {
        set_bezug(tz.zeile(2));
        set_xs(tz.zeile(3));
        set_ys(tz.zeile(4));
        set_zs(tz.zeile(5));
        set_xe(tz.zeile(6));
        set_ye(tz.zeile(7));
        set_ze(tz.zeile(8));
        set_afb(tz.zeile(9));
    }
}

strecke fraesergerade::strecke_()
{
    strecke s;
    s.set_start(Startpunkt);
    s.set_ende(Endpunkt);
    return s;
}













