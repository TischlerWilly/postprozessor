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
    durchmesser = 0;
    tiefe = 0;
    pos_x = 0;
    pos_y = 0;
    pos_z = 0;
    bezug = WST_BEZUG_OBSEI;
    afb = "1";
    zustellmass = 0;
}

void bohrung::set_dm(double dm)
{
    if(dm > 0)
    {
        durchmesser = dm;
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
        tiefe = ti;
    }
}
void bohrung::set_tiefe(QString ti)
{
    set_tiefe(ti.toDouble());
}
void bohrung::set_x(double x)
{
    pos_x = x;
}
void bohrung::set_x(QString x)
{
    set_x(x.toDouble());
}
void bohrung::set_y(double y)
{
    pos_y = y;
}
void bohrung::set_y(QString y)
{
    set_y(y.toDouble());
}
void bohrung::set_z(double z)
{
    pos_z = z;
}
void bohrung::set_z(QString z)
{
    set_z(z.toDouble());
}
void bohrung::set_zustellmass(double mass)
{
    if(mass >= 0)
    {
        zustellmass = mass;
    }
}
void bohrung::set_zustellmass(QString mass)
{
    set_zustellmass(mass.toDouble());
}
void bohrung::set_bezug(QString bezugsflaeche)
{
    bezug = bezugsflaeche;
}
void bohrung::set_afb(QString ausfuehrbedingung)
{
    afb = ausfuehrbedingung;
}
void bohrung::set_wkznum(QString nummer)
{
    werkzeugnummer = nummer;
}

double bohrung::get_dm()
{
    return durchmesser;
}
QString bohrung::get_dm_qstring()
{
    return double_to_qstring(durchmesser);
}
double bohrung::get_tiefe()
{
    return tiefe;
}
QString bohrung::get_tiefe_qstring()
{
    return double_to_qstring(tiefe);
}
double bohrung::get_x()
{
    return pos_x;
}
QString bohrung::get_x_qstring()
{
    return double_to_qstring(pos_x);
}
double bohrung::get_y()
{
    return pos_y;
}
QString bohrung::get_y_qstring()
{
    return double_to_qstring(pos_y);
}
double bohrung::get_z()
{
    return pos_z;
}
QString bohrung::get_z_qstring()
{
    return double_to_qstring(pos_z);
}
double bohrung::get_zustellmass()
{
    return zustellmass;
}
QString bohrung::get_zustellmass_qstring()
{
    return double_to_qstring(zustellmass);
}
QString bohrung::get_bezug()
{
    return bezug;
}
QString bohrung::get_afb()
{
    return afb;
}
QString bohrung::get_wkznum()
{
    return werkzeugnummer;
}

QString bohrung::text()
{
    QString msg = BEARBART_BOHR;    //Zeile 1
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_bezug();             //Zeile 2
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_dm_qstring();        //Zeile 3
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_tiefe_qstring();     //Zeile 4
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_x_qstring();         //Zeile 5
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_y_qstring();         //Zeile 6
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_z_qstring();         //Zeile 7
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_afb();               //Zeile 8
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_zustellmass_qstring();               //Zeile 9
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_wkznum();            //Zeile 10

    return msg;
}
void bohrung::set_text(QString text)
{
    text_zeilenweise tz;
    tz.set_trennzeichen(TRENNZ_BEARB_PARAM);
    tz.set_text(text);
    if(tz.zeile(1) == BEARBART_BOHR)
    {
        set_bezug(tz.zeile(2));
        set_dm(tz.zeile(3));
        set_tiefe(tz.zeile(4));
        set_x(tz.zeile(5));
        set_y(tz.zeile(6));
        set_z(tz.zeile(7));
        set_afb(tz.zeile(8));
        set_zustellmass(tz.zeile(9));
        set_wkznum(tz.zeile(10));
    }
}



















