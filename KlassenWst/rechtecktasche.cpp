#include "rechtecktasche.h"

rechtecktasche::rechtecktasche()
{
    setup();
}

rechtecktasche::rechtecktasche(QString text)
{
    setup();
    set_text(text);
}

void rechtecktasche::setup()
{
    laenge = 0;
    breite = 0;
    tiefe = 0;
    pos_x = 0;
    pos_y = 0;
    pos_z = 0;
    drewinkel = 0;
    eckenradius = 0;
    zustellmass = 0;
    ausraeumen = true;
    bezug = WST_BEZUG_OBSEI;
    afb = "1";
}

void rechtecktasche::set_laenge(double l)
{
    if(l > 0)
    {
        laenge = l;
    }
}
void rechtecktasche::set_laenge(QString l)
{
    set_laenge(l.toDouble());
}
void rechtecktasche::set_breite(double b)
{
    if(b > 0)
    {
        breite = b;
    }
}
void rechtecktasche::set_breite(QString b)
{
    set_breite(b.toDouble());
}
void rechtecktasche::set_tiefe(double t)
{
    if(t > 0)
    {
        tiefe = t;
    }
}
void rechtecktasche::set_tiefe(QString t)
{
    set_tiefe(t.toDouble());
}
void rechtecktasche::set_x(double x)
{
    pos_x = x;
}
void rechtecktasche::set_x(QString x)
{
    set_x(x.toDouble());
}
void rechtecktasche::set_y(double y)
{
    pos_y = y;
}
void rechtecktasche::set_y(QString y)
{
    set_y(y.toDouble());
}
void rechtecktasche::set_z(double z)
{
    pos_z = z;
}
void rechtecktasche::set_z(QString z)
{
    set_z(z.toDouble());
}
void rechtecktasche::set_drewi(double wi)
{
    while(wi > 180)
    {
        wi = wi -180;
    }
    drewinkel = wi;
}
void rechtecktasche::set_drewi(QString wi)
{
    set_drewi(wi.toDouble());
}
void rechtecktasche::set_rad(double r)
{
    if(r >= 0)
    {
        eckenradius = r;
    }
}
void rechtecktasche::set_rad(QString r)
{
    set_rad(r.toDouble());
}
void rechtecktasche::set_zustellmass(double mass)
{
    if(mass >= 0)
    {
        zustellmass = mass;
    }
}
void rechtecktasche::set_zustellmass(QString mass)
{
    set_zustellmass(mass.toDouble());
}
void rechtecktasche::set_ausraeumen(double ja)
{
    if(ja > 0)
    {
        ausraeumen = true;
    }else
    {
        ausraeumen = false;
    }
}
void rechtecktasche::set_ausraeumen(QString ja)
{
    set_ausraeumen(ja.toDouble());
}
void rechtecktasche::set_bezug(QString bezugsflaeche)
{
    bezug = bezugsflaeche;
}
void rechtecktasche::set_afb(QString ausfuehrbedingung)
{
    afb = ausfuehrbedingung;
}

double rechtecktasche::get_laenge()
{
    return laenge;
}
QString rechtecktasche::get_laenge_qstring()
{
    return double_to_qstring(laenge);
}
double rechtecktasche::get_breite()
{
    return breite;
}
QString rechtecktasche::get_breite_qstring()
{
    return double_to_qstring(breite);
}
double rechtecktasche::get_tiefe()
{
    return tiefe;
}
QString rechtecktasche::get_tiefe_qstring()
{
    return double_to_qstring(tiefe);
}
double rechtecktasche::get_x()
{
    return pos_x;
}
QString rechtecktasche::get_x_qstring()
{
    return double_to_qstring(pos_x);
}
double rechtecktasche::get_y()
{
    return pos_y;
}
QString rechtecktasche::get_y_qstring()
{
    return double_to_qstring(pos_y);
}
double rechtecktasche::get_z()
{
    return pos_z;
}
QString rechtecktasche::get_z_qstring()
{
    return double_to_qstring(pos_z);
}
double rechtecktasche::get_drewi()
{
    return drewinkel;
}
QString rechtecktasche::get_drewi_qstring()
{
    return double_to_qstring(drewinkel);
}
double rechtecktasche::get_rad()
{
    return eckenradius;
}
QString rechtecktasche::get_rad_qstring()
{
    return double_to_qstring(eckenradius);
}
double rechtecktasche::get_zustellmass()
{
    return zustellmass;
}
QString rechtecktasche::get_zustellmass_qstring()
{
    return double_to_qstring(zustellmass);
}
bool rechtecktasche::get_ausraeumen()
{
    return ausraeumen;
}
QString rechtecktasche::get_ausraeumen_qstring()
{
    if(ausraeumen == true)
    {
        return "1";
    }else
    {
        return "0";
    }
}

QString rechtecktasche::get_bezug()
{
    return bezug;
}
QString rechtecktasche::get_afb()
{
    return afb;
}

QString rechtecktasche::get_text()
{
    QString msg = BEARBART_RTA;    //Zeile 1
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_bezug();             //Zeile 2
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_laenge_qstring();    //Zeile 3
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_breite_qstring();    //Zeile 4
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_tiefe_qstring();     //Zeile 5
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_x_qstring();         //Zeile 6
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_y_qstring();         //Zeile 7
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_z_qstring();         //Zeile 8
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_drewi_qstring();     //Zeile 9
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_rad_qstring();       //Zeile 10
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_ausraeumen_qstring();//Zeile 11
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_afb();               //Zeile 12
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_zustellmass_qstring();//Zeile 13

    return msg;
}
void rechtecktasche::set_text(QString text)
{
    text_zeilenweise tz;
    tz.set_trennzeichen(TRENNZ_BEARB_PARAM);
    tz.set_text(text);
    if(tz.zeile(1) == BEARBART_RTA)
    {
        set_bezug(tz.zeile(2));
        set_laenge(tz.zeile(3));
        set_breite(tz.zeile(4));
        set_tiefe(tz.zeile(5));
        set_x(tz.zeile(6));
        set_y(tz.zeile(7));
        set_z(tz.zeile(8));
        set_drewi(tz.zeile(9));
        set_rad(tz.zeile(10));
        set_ausraeumen(tz.zeile(11));
        set_afb(tz.zeile(12));
        set_zustellmass(tz.zeile(13));
    }
}













