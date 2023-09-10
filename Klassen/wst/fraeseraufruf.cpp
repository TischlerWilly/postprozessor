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
    }
}


