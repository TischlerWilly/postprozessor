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
    afb = "1";
    bezug = WST_BEZUG_OBSEI;
}

void fraesergerade::set_xs(double x)
{
    startpunkt.set_x(x);
}
void fraesergerade::set_xs(QString x)
{
    startpunkt.set_x(x);
}
void fraesergerade::set_xe(double x)
{
    endpunkt.set_x(x);
}
void fraesergerade::set_xe(QString x)
{
    endpunkt.set_x(x);
}

void fraesergerade::set_ys(double y)
{
    startpunkt.set_y(y);
}
void fraesergerade::set_ys(QString y)
{
    startpunkt.set_y(y);
}
void fraesergerade::set_ye(double y)
{
    endpunkt.set_y(y);
}
void fraesergerade::set_ye(QString y)
{
    endpunkt.set_y(y);
}

void fraesergerade::set_zs(double z)
{
    startpunkt.set_z(z);
}
void fraesergerade::set_zs(QString z)
{
    startpunkt.set_z(z);
}
void fraesergerade::set_ze(double z)
{
    endpunkt.set_z(z);
}
void fraesergerade::set_ze(QString z)
{
    endpunkt.set_z(z);
}

double fraesergerade::get_xs()
{
    return startpunkt.x();
}
QString fraesergerade::get_xs_qstring()
{
    return startpunkt.x_QString();
}
double fraesergerade::get_xe()
{
    return endpunkt.x();
}
QString fraesergerade::get_xe_qstring()
{
    return endpunkt.x_QString();
}

double fraesergerade::get_ys()
{
    return startpunkt.y();
}
QString fraesergerade::get_ys_qstring()
{
    return startpunkt.y_QString();
}
double fraesergerade::get_ye()
{
    return endpunkt.y();
}
QString fraesergerade::get_ye_qstring()
{
    return endpunkt.y_QString();
}

double fraesergerade::get_zs()
{
    return startpunkt.z();
}
QString fraesergerade::get_zs_qstring()
{
    return startpunkt.z_QString();
}
double fraesergerade::get_ze()
{
    return endpunkt.z();
}
QString fraesergerade::get_ze_qstring()
{
    return endpunkt.z_QString();
}

punkt3d fraesergerade::get_sp()
{
    return startpunkt;
}
punkt3d fraesergerade::get_ep()
{
    return endpunkt;
}

double fraesergerade::get_laenge_2d()
{
    strecke s;
    s.set_start(startpunkt);
    s.set_ende(endpunkt);

    return s.laenge2dim();
}

void fraesergerade::set_bezug(QString bezugsflaeche)
{
    bezug = bezugsflaeche;
}
void fraesergerade::set_afb(QString ausfuehrbedingung)
{
    afb = ausfuehrbedingung;
}

QString fraesergerade::get_bezug()
{
    return bezug;
}
QString fraesergerade::get_afb()
{
    return afb;
}

QString fraesergerade::get_text()
{
    QString msg = BEARBART_FRAESERGERADE;    //Zeile 1
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_bezug();                      //Zeile 2
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_xs_qstring();                 //Zeile 3
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_ys_qstring();                 //Zeile 4
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_zs_qstring();                 //Zeile 5
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_xe_qstring();                 //Zeile 6
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_ye_qstring();                 //Zeile 7
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_ze_qstring();                 //Zeile 8
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_afb();                        //Zeile 9

    return msg;
}
void fraesergerade::set_text(QString text)
{
    text_zeilenweise tz;
    tz.set_trennzeichen(TRENNZ_BEARB_PARAM);
    tz.set_text(text);
    if(tz.zeile(1) == BEARBART_FRAESERAUFRUF)
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














