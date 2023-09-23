#include "fraeseraufruf.h"

fraeseraufruf::fraeseraufruf()
{
    setup();
}
fraeseraufruf::fraeseraufruf(QString text)
{
    setup();
    set_text(text);
}

void fraeseraufruf::setup()
{
    Tiefe = 0;
    Bezug = WST_BEZUG_OBSEI;
    Afb = "1";
    Korrektur = "M";
    Werkzeugnummer = "void";
    Anfahrtyp = FAUFRUF_ANABTYP_NDEF;
    Abfahrtyp = FAUFRUF_ANABTYP_NDEF;
    Anfahrweg = FAUFRUF_ANABWEG_AUTO;
    Abfahrweg = FAUFRUF_ANABWEG_AUTO;
}

void fraeseraufruf::set_x(double x)
{
    Pos.set_x(x);
}
void fraeseraufruf::set_x(QString x)
{
    Pos.set_x(x);
}
void fraeseraufruf::set_y(double y)
{
    Pos.set_y(y);
}
void fraeseraufruf::set_y(QString y)
{
    Pos.set_y(y);
}

void fraeseraufruf::set_z(double z)
{
    Pos.set_z(z);
}
void fraeseraufruf::set_z(QString z)
{
    Pos.set_z(z);
}

void fraeseraufruf::set_pos(punkt3d p)
{
    Pos = p;
}
void fraeseraufruf::set_tiefe(double ti)
{
    Tiefe = ti;
}
void fraeseraufruf::set_tiefe(QString ti)
{
    set_tiefe(ti.toDouble());
}
void fraeseraufruf::set_bezug(QString bezugsflaeche)
{
    Bezug = bezugsflaeche;
}
void fraeseraufruf::set_afb(QString ausfuehrbedingung)
{
    Afb = ausfuehrbedingung;
}
void fraeseraufruf::set_radkor(QString kor)
{
    if(kor == FRKOR_L || \
       kor == FRKOR_M || \
       kor == FRKOR_R)
    {
        Korrektur = kor;
    }
}
void fraeseraufruf::set_wkznum(QString nummer)
{
    Werkzeugnummer = nummer;
}
void fraeseraufruf::set_anfahrtyp(QString typ)
{
    Anfahrtyp = typ;
}
void fraeseraufruf::set_abfahrtyp(QString typ)
{
    Abfahrtyp = typ;
}
void fraeseraufruf::set_anfahrweg(QString laenge)
{
    Anfahrweg = laenge;
}
void fraeseraufruf::set_anfahrweg(double laenge)
{
    Anfahrweg = double_to_qstring(laenge);
}
void fraeseraufruf::set_abfahrweg(QString laenge)
{
    Abfahrweg = laenge;
}
void fraeseraufruf::set_abfahrweg(double laenge)
{
    Abfahrweg = double_to_qstring(laenge);
}

//------------------------------------------------------------
double fraeseraufruf::x()
{
    return Pos.x();
}
QString fraeseraufruf::x_qstring()
{
    return Pos.x_QString();
}
double fraeseraufruf::y()
{
    return Pos.y();
}
QString fraeseraufruf::y_qstring()
{
    return Pos.y_QString();
}

double fraeseraufruf::z()
{
    return Pos.z();
}
QString fraeseraufruf::z_qstring()
{
    return Pos.z_QString();
}

double fraeseraufruf::tiefe()
{
    return Tiefe;
}
QString fraeseraufruf::tiefe_qstring()
{
    return double_to_qstring(Tiefe);
}
QString fraeseraufruf::bezug()
{
    return Bezug;
}
QString fraeseraufruf::afb()
{
    return Afb;
}
QString fraeseraufruf::radkor()
{
    return Korrektur;
}
QString fraeseraufruf::wkznum()
{
    return Werkzeugnummer;
}
punkt3d fraeseraufruf::pos()
{
    return Pos;
}
QString fraeseraufruf::anfahrtyp()
{
    return Anfahrtyp;
}
QString fraeseraufruf::abfahrtyp()
{
    return Abfahrtyp;
}
double fraeseraufruf::anfahrweg()
{
    return Anfahrweg.toDouble();
}
QString fraeseraufruf::anfahrweg_qstring()
{
    return Anfahrweg;
}
double fraeseraufruf::abfahrweg()
{
    return Abfahrweg.toDouble();
}
QString fraeseraufruf::abfahrweg_qstring()
{
    return Abfahrweg;
}

QString fraeseraufruf::text()
{
    QString msg = BEARBART_FRAESERAUFRUF;    //Zeile 0
    msg += TRENNZ_BEARB_PARAM_;
    msg += bezug();                      //Zeile 1
    msg += TRENNZ_BEARB_PARAM_;
    msg += x_qstring();                  //Zeile 2
    msg += TRENNZ_BEARB_PARAM_;
    msg += y_qstring();                  //Zeile 3
    msg += TRENNZ_BEARB_PARAM_;
    msg += z_qstring();                  //Zeile 4
    msg += TRENNZ_BEARB_PARAM_;
    msg += tiefe_qstring();              //Zeile 5
    msg += TRENNZ_BEARB_PARAM_;
    msg += radkor();                     //Zeile 6
    msg += TRENNZ_BEARB_PARAM_;
    msg += wkznum();                     //Zeile 7
    msg += TRENNZ_BEARB_PARAM_;
    msg += afb();                        //Zeile 8
    msg += TRENNZ_BEARB_PARAM_;
    msg += anfahrtyp();                  //Zeile 9
    msg += TRENNZ_BEARB_PARAM_;
    msg += anfahrtyp();                  //Zeile 10
    msg += TRENNZ_BEARB_PARAM_;
    msg += anfahrweg_qstring();          //Zeile 11
    msg += TRENNZ_BEARB_PARAM_;
    msg += abfahrweg_qstring();          //Zeile 12

    return msg;
}
void fraeseraufruf::set_text(QString text)
{
    text_zw tz;
    tz.set_text(text, TRENNZ_BEARB_PARAM);
    if(tz.at(0) == BEARBART_FRAESERAUFRUF)
    {
        set_bezug(tz.at(1));
        set_x(tz.at(2));
        set_y(tz.at(3));
        set_z(tz.at(4));
        set_tiefe(tz.at(5));
        set_radkor(tz.at(6));
        set_wkznum(tz.at(7));
        set_afb(tz.at(8));
        set_anfahrtyp(tz.at(9));
        set_abfahrtyp(tz.at(10));
        set_anfahrweg(tz.at(11));
        set_abfahrweg(tz.at(12));
    }
}


