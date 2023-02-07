#include "bohrung.h"

bohrung::bohrung()
{
    setup();
}
bohrung::bohrung(QString text)
{
    setup();
    set_text(text);
}

void bohrung::setup()
{
    Durchmesser = 0;
    Tiefe = 0;
    Pos_x = 0;
    Pos_y = 0;
    Pos_z = 0;
    Bezug = WST_BEZUG_OBSEI;
    Afb = "1";
    Zustellmass = 0;
    Werkzeugnummer = "void";
}

void bohrung::set_dm(double dm)
{
    if(dm > 0)
    {
        Durchmesser = dm;
    }
}
void bohrung::set_dm(QString dm)
{
    set_dm(dm.toDouble());
}
void bohrung::set_tiefe(double ti)
{
    if(ti > 0)
    {
        Tiefe = ti;
    }
}
void bohrung::set_tiefe(QString ti)
{
    set_tiefe(ti.toDouble());
}
void bohrung::set_x(double x)
{
    Pos_x = x;
}
void bohrung::set_x(QString x)
{
    set_x(x.toDouble());
}
void bohrung::set_y(double y)
{
    Pos_y = y;
}
void bohrung::set_y(QString y)
{
    set_y(y.toDouble());
}
void bohrung::set_z(double z)
{
    Pos_z = z;
}
void bohrung::set_z(QString z)
{
    set_z(z.toDouble());
}
void bohrung::set_zustellmass(double mass)
{
    if(mass >= 0)
    {
        Zustellmass = mass;
    }
}
void bohrung::set_zustellmass(QString mass)
{
    set_zustellmass(mass.toDouble());
}
void bohrung::set_bezug(QString bezugsflaeche)
{
    Bezug = bezugsflaeche;
}
void bohrung::set_afb(QString ausfuehrbedingung)
{
    Afb = ausfuehrbedingung;
}
void bohrung::set_wkznum(QString nummer)
{
    Werkzeugnummer = nummer;
}

double bohrung::dm()
{
    return Durchmesser;
}
QString bohrung::dm_qstring()
{
    return double_to_qstring(Durchmesser);
}
double bohrung::tiefe()
{
    return Tiefe;
}
QString bohrung::tiefe_qstring()
{
    return double_to_qstring(Tiefe);
}
double bohrung::x()
{
    return Pos_x;
}
QString bohrung::x_qstring()
{
    return double_to_qstring(Pos_x);
}
double bohrung::y()
{
    return Pos_y;
}
QString bohrung::y_qstring()
{
    return double_to_qstring(Pos_y);
}
double bohrung::z()
{
    return Pos_z;
}
QString bohrung::z_qstring()
{
    return double_to_qstring(Pos_z);
}
punkt3d bohrung::mipu()
{
    punkt3d p(x(),y(),z());
    return p;
}
double bohrung::zustellmass()
{
    return Zustellmass;
}
QString bohrung::zustellmass_qstring()
{
    return double_to_qstring(Zustellmass);
}
QString bohrung::bezug()
{
    return Bezug;
}
QString bohrung::afb()
{
    return Afb;
}
QString bohrung::wkznum()
{
    return Werkzeugnummer;
}

QString bohrung::text()
{
    QString msg = BEARBART_BOHR;    //Zeile 0
    msg += TRENNZ_BEARB_PARAM_;
    msg += bezug();             //Zeile 1
    msg += TRENNZ_BEARB_PARAM_;
    msg += dm_qstring();        //Zeile 2
    msg += TRENNZ_BEARB_PARAM_;
    msg += tiefe_qstring();     //Zeile 3
    msg += TRENNZ_BEARB_PARAM_;
    msg += x_qstring();         //Zeile 4
    msg += TRENNZ_BEARB_PARAM_;
    msg += y_qstring();         //Zeile 5
    msg += TRENNZ_BEARB_PARAM_;
    msg += z_qstring();         //Zeile 6
    msg += TRENNZ_BEARB_PARAM_;
    msg += afb();               //Zeile 7
    msg += TRENNZ_BEARB_PARAM_;
    msg += zustellmass_qstring();               //Zeile 8
    msg += TRENNZ_BEARB_PARAM_;
    msg += wkznum();            //Zeile 9

    return msg;
}
void bohrung::set_text(QString text)
{
    text_zw tz;
    tz.set_text(text,TRENNZ_BEARB_PARAM);
    if(tz.at(0) == BEARBART_BOHR)
    {
        set_bezug(tz.at(1));
        set_dm(tz.at(2));
        set_tiefe(tz.at(3));
        set_x(tz.at(4));
        set_y(tz.at(5));
        set_z(tz.at(6));
        set_afb(tz.at(7));
        set_zustellmass(tz.at(8));
        set_wkznum(tz.at(9));
    }
}



















