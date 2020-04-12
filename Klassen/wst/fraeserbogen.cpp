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
    uzs = true;
    radius = 0;
    afb = "1";
    bezug = WST_BEZUG_OBSEI;
}


void fraeserbogen::set_xs(double x)
{
    startpunkt.set_x(x);
}
void fraeserbogen::set_xs(QString x)
{
    startpunkt.set_x(x);
}
void fraeserbogen::set_xe(double x)
{
    endpunkt.set_x(x);
}
void fraeserbogen::set_xe(QString x)
{
    endpunkt.set_x(x);
}

void fraeserbogen::set_ys(double y)
{
    startpunkt.set_y(y);
}
void fraeserbogen::set_ys(QString y)
{
    startpunkt.set_y(y);
}
void fraeserbogen::set_ye(double y)
{
    endpunkt.set_y(y);
}
void fraeserbogen::set_ye(QString y)
{
    endpunkt.set_y(y);
}

void fraeserbogen::set_zs(double z)
{
    startpunkt.set_z(z);
}
void fraeserbogen::set_zs(QString z)
{
    startpunkt.set_z(z);
}
void fraeserbogen::set_ze(double z)
{
    endpunkt.set_z(z);
}
void fraeserbogen::set_ze(QString z)
{
    endpunkt.set_z(z);
}

void fraeserbogen::set_rad(double rad)
{
    if(rad > 0)
    {
        radius = rad;
    }
}
void fraeserbogen::set_rad(QString rad)
{
    set_rad(rad.toDouble());
}

void fraeserbogen::set_uzs(bool ist_im_uzs)
{
    uzs = ist_im_uzs;
}
void fraeserbogen::set_uzs(QString ist_im_uzs)
{
    if(ist_im_uzs == "1")
    {
        uzs = true;
    }else if(ist_im_uzs == "0")
    {
        uzs = false;
    }
}

void fraeserbogen::set_bezug(QString bezugsflaeche)
{
    bezug = bezugsflaeche;
}
void fraeserbogen::set_afb(QString ausfuehrbedingung)
{
    afb = ausfuehrbedingung;
}

double fraeserbogen::get_xs()
{
    return startpunkt.x();
}
QString fraeserbogen::get_xs_qstring()
{
    return startpunkt.x_QString();
}
double fraeserbogen::get_xe()
{
    return endpunkt.x();
}
QString fraeserbogen::get_xe_qstring()
{
    return endpunkt.x_QString();
}

double fraeserbogen::get_ys()
{
    return startpunkt.y();
}
QString fraeserbogen::get_ys_qstring()
{
    return startpunkt.y_QString();
}
double fraeserbogen::get_ye()
{
    return endpunkt.y();
}
QString fraeserbogen::get_ye_qstring()
{
    return endpunkt.y_QString();
}

double fraeserbogen::get_zs()
{
    return startpunkt.z();
}
QString fraeserbogen::get_zs_qstring()
{
    return startpunkt.z_QString();
}
double fraeserbogen::get_ze()
{
    return endpunkt.z();
}
QString fraeserbogen::get_ze_qstring()
{
    return endpunkt.z_QString();
}

double fraeserbogen::get_rad()
{
    return radius;
}
QString fraeserbogen::get_rad_qstring()
{
    return double_to_qstring(radius);
}

bool fraeserbogen::get_uzs()
{
    return uzs;
}
QString fraeserbogen::get_uzs_qstring()
{
    if(uzs == true)
    {
        return "1";
    }else
    {
        return "0";
    }
}

punkt3d fraeserbogen::get_sp()
{
    return startpunkt;
}
punkt3d fraeserbogen::get_ep()
{
    return endpunkt;
}

QString fraeserbogen::get_bezug()
{
    return bezug;
}
QString fraeserbogen::get_afb()
{
    return afb;
}



QString fraeserbogen::text()
{
    QString msg = BEARBART_FRAESERBOGEN;     //Zeile 1
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
    msg += get_rad_qstring();                //Zeile 9
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_uzs_qstring();                //Zeile 10
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_afb();                        //Zeile 11

    return msg;
}
void fraeserbogen::set_text(QString text)
{
    text_zeilenweise tz;
    tz.set_trennzeichen(TRENNZ_BEARB_PARAM);
    tz.set_text(text);
    if(tz.zeile(1) == BEARBART_FRAESERBOGEN)
    {
        set_bezug(tz.zeile(2));
        set_xs(tz.zeile(3));
        set_ys(tz.zeile(4));
        set_zs(tz.zeile(5));
        set_xe(tz.zeile(6));
        set_ye(tz.zeile(7));
        set_ze(tz.zeile(8));
        set_rad(tz.zeile(9));
        set_uzs(tz.zeile(10));
        set_afb(tz.zeile(11));
    }
}




















