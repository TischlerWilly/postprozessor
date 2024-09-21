#include "fraeserbogen.h"

fraeserbogen::fraeserbogen()
{
    setup();
}

fraeserbogen::fraeserbogen(QString text)
{
    setup();
    set_text(text);
}

void fraeserbogen::setup()
{
    Uzs = true;
    Radius = 0;
    Afb = "1";
    Bezug = WST_BEZUG_OBSEI;
}


void fraeserbogen::set_xs(double x)
{
    Startpunkt.set_x(x);
}
void fraeserbogen::set_xs(QString x)
{
    Startpunkt.set_x(x);
}
void fraeserbogen::set_xe(double x)
{
    Endpunkt.set_x(x);
}
void fraeserbogen::set_xe(QString x)
{
    Endpunkt.set_x(x);
}

void fraeserbogen::set_ys(double y)
{
    Startpunkt.set_y(y);
}
void fraeserbogen::set_ys(QString y)
{
    Startpunkt.set_y(y);
}
void fraeserbogen::set_ye(double y)
{
    Endpunkt.set_y(y);
}
void fraeserbogen::set_ye(QString y)
{
    Endpunkt.set_y(y);
}

void fraeserbogen::set_zs(double z)
{
    Startpunkt.set_z(z);
}
void fraeserbogen::set_zs(QString z)
{
    Startpunkt.set_z(z);
}
void fraeserbogen::set_ze(double z)
{
    Endpunkt.set_z(z);
}
void fraeserbogen::set_ze(QString z)
{
    Endpunkt.set_z(z);
}

void fraeserbogen::set_rad(double rad)
{
    if(rad > 0)
    {
        Radius = rad;
    }
}
void fraeserbogen::set_rad(QString rad)
{
    set_rad(rad.toDouble());
}

void fraeserbogen::set_uzs(bool ist_im_uzs)
{
    Uzs = ist_im_uzs;
}
void fraeserbogen::set_uzs(QString ist_im_uzs)
{
    if(ist_im_uzs == "1")
    {
        Uzs = true;
    }else if(ist_im_uzs == "0")
    {
        Uzs = false;
    }
}

void fraeserbogen::set_bezug(QString bezugsflaeche)
{
    Bezug = bezugsflaeche;
}
void fraeserbogen::set_afb(QString ausfuehrbedingung)
{
    Afb = ausfuehrbedingung;
}

void fraeserbogen::set_bogen(bogen bo)
{
    set_startpunkt(bo.start());
    set_endpunkt(bo.ende());
    set_rad(bo.rad());
    set_uzs(bo.im_uzs());
}

void fraeserbogen::set_tiSta(double tiefe)
{
    TiSta = tiefe;
}
void fraeserbogen::set_tiSta(QString tiefe)
{
    set_tiSta(tiefe.toDouble());
}
void fraeserbogen::set_tiEnd(double tiefe)
{
    TiEnd = tiefe;
}
void fraeserbogen::set_tiEnd(QString tiefe)
{
    set_tiEnd(tiefe.toDouble());
}
double fraeserbogen::xs()
{
    return Startpunkt.x();
}
QString fraeserbogen::xs_qstring()
{
    return Startpunkt.x_QString();
}
double fraeserbogen::xe()
{
    return Endpunkt.x();
}
QString fraeserbogen::xe_qstring()
{
    return Endpunkt.x_QString();
}

double fraeserbogen::ys()
{
    return Startpunkt.y();
}
QString fraeserbogen::ys_qstring()
{
    return Startpunkt.y_QString();
}
double fraeserbogen::ye()
{
    return Endpunkt.y();
}
QString fraeserbogen::ye_qstring()
{
    return Endpunkt.y_QString();
}

double fraeserbogen::zs()
{
    return Startpunkt.z();
}
QString fraeserbogen::zs_qstring()
{
    return Startpunkt.z_QString();
}
double fraeserbogen::ze()
{
    return Endpunkt.z();
}
QString fraeserbogen::ze_qstring()
{
    return Endpunkt.z_QString();
}

double fraeserbogen::rad()
{
    return Radius;
}
QString fraeserbogen::rad_qstring()
{
    return double_to_qstring(Radius);
}

bool fraeserbogen::uzs()
{
    return Uzs;
}
QString fraeserbogen::uzs_qstring()
{
    if(Uzs == true)
    {
        return "1";
    }else
    {
        return "0";
    }
}

bogen fraeserbogen::bog()
{
    bogen b(stapu(), endpu(), rad(), uzs());
    return b;
}

punkt3d fraeserbogen::sp()
{
    return Startpunkt;
}
punkt3d fraeserbogen::ep()
{
    return Endpunkt;
}

QString fraeserbogen::bezug()
{
    return Bezug;
}
QString fraeserbogen::afb()
{
    return Afb;
}

double fraeserbogen::tiSta()
{
    return TiSta;
}
QString fraeserbogen::tiSta_qstring()
{
    return double_to_qstring(TiSta);
}
double fraeserbogen::tiEnd()
{
    return TiEnd;
}
QString fraeserbogen::tiEnd_qstring()
{
    return double_to_qstring(TiEnd);
}

QString fraeserbogen::text()
{
    QString msg = BEARBART_FRAESERBOGEN;     //Zeile 0
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
    msg += rad_qstring();                //Zeile 8
    msg += TRENNZ_BEARB_PARAM_;
    msg += uzs_qstring();                //Zeile 9
    msg += TRENNZ_BEARB_PARAM_;
    msg += afb();                        //Zeile 10
    msg += TRENNZ_BEARB_PARAM_;
    msg += tiSta_qstring();              //Zeile 11
    msg += TRENNZ_BEARB_PARAM_;
    msg += tiEnd_qstring();              //Zeile 12

    return msg;
}
void fraeserbogen::set_text(QString text)
{
    text_zw tz;
    tz.set_text(text,TRENNZ_BEARB_PARAM);
    if(tz.at(0) == BEARBART_FRAESERBOGEN)
    {
        set_bezug(tz.at(1));
        set_xs(tz.at(2));
        set_ys(tz.at(3));
        set_zs(tz.at(4));
        set_xe(tz.at(5));
        set_ye(tz.at(6));
        set_ze(tz.at(7));
        set_rad(tz.at(8));
        set_uzs(tz.at(9));
        set_afb(tz.at(10));
        set_tiSta(tz.at(11));
        set_tiEnd(tz.at(12));
    }
}




















