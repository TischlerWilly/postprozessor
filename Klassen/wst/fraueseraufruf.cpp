#include "fraueseraufruf.h"

fraueseraufruf::fraueseraufruf()
{
    setup();
}
fraueseraufruf::fraueseraufruf(QString text)
{
    setup();
    set_text(text);
}

void fraueseraufruf::setup()
{
    Pos_x = 0;
    Pos_y = 0;
    Pos_z = 0;
    Tiefe = 0;
    Bezug = WST_BEZUG_OBSEI;
    Afb = "1";
    Korrektur = "M";
    Werkzeugnummer = "123456789";

}

void fraueseraufruf::set_x(double x)
{
    Pos_x = x;
}
void fraueseraufruf::set_x(QString x)
{
    set_x(x.toDouble());
}
void fraueseraufruf::set_y(double y)
{
    Pos_y = y;
}
void fraueseraufruf::set_y(QString y)
{
    set_y(y.toDouble());
}
void fraueseraufruf::set_z(double z)
{
    Pos_z = z;
}
void fraueseraufruf::set_z(QString z)
{
    set_z(z.toDouble());
}
void fraueseraufruf::set_tiefe(double ti)
{
    Tiefe = ti;
}
void fraueseraufruf::set_tiefe(QString ti)
{
    set_tiefe(ti.toDouble());
}
void fraueseraufruf::set_bezug(QString bezugsflaeche)
{
    Bezug = bezugsflaeche;
}
void fraueseraufruf::set_afb(QString ausfuehrbedingung)
{
    Afb = ausfuehrbedingung;
}
void fraueseraufruf::set_radkor(QString kor)
{
    if(kor == FRKOR_L || \
       kor == FRKOR_M || \
       kor == FRKOR_R)
    {
        Korrektur = kor;
    }
}
void fraueseraufruf::set_wkznum(QString nummer)
{
    Werkzeugnummer = nummer;
}

//------------------------------------------------------------
double fraueseraufruf::x()
{
    return Pos_x;
}
QString fraueseraufruf::x_qstring()
{
    return double_to_qstring(Pos_x);
}
double fraueseraufruf::y()
{
    return Pos_y;
}
QString fraueseraufruf::y_qstring()
{
    return double_to_qstring(Pos_y);
}
double fraueseraufruf::z()
{
    return Pos_z;
}
QString fraueseraufruf::z_qstring()
{
    return double_to_qstring(Pos_z);
}
double fraueseraufruf::tiefe()
{
    return Tiefe;
}
QString fraueseraufruf::tiefe_qstring()
{
    return double_to_qstring(Tiefe);
}
QString fraueseraufruf::bezug()
{
    return Bezug;
}
QString fraueseraufruf::afb()
{
    return Afb;
}
QString fraueseraufruf::radkor()
{
    return Korrektur;
}
QString fraueseraufruf::wkznum()
{
    return Werkzeugnummer;
}
punkt3d fraueseraufruf::pos_vertikal()
{
    punkt3d p;
    p.set_x(Pos_x);
    p.set_y(Pos_y);
    p.set_z(Tiefe);
    return p;
}

QString fraueseraufruf::text()
{
    QString msg = BEARBART_FRAESERAUFRUF;    //Zeile 1
    msg += TRENNZ_BEARB_PARAM_;
    msg += bezug();                      //Zeile 2
    msg += TRENNZ_BEARB_PARAM_;
    msg += x_qstring();                  //Zeile 3
    msg += TRENNZ_BEARB_PARAM_;
    msg += y_qstring();                  //Zeile 4
    msg += TRENNZ_BEARB_PARAM_;
    msg += z_qstring();                  //Zeile 5
    msg += TRENNZ_BEARB_PARAM_;
    msg += tiefe_qstring();              //Zeile 6
    msg += TRENNZ_BEARB_PARAM_;
    msg += radkor();                     //Zeile 7
    msg += TRENNZ_BEARB_PARAM_;
    msg += wkznum();                     //Zeile 8
    msg += TRENNZ_BEARB_PARAM_;
    msg += afb();                        //Zeile 9

    return msg;
}
void fraueseraufruf::set_text(QString text)
{
    text_zeilenweise tz;
    tz.set_trennzeichen(TRENNZ_BEARB_PARAM);
    tz.set_text(text);
    if(tz.zeile(1) == BEARBART_FRAESERAUFRUF)
    {
        set_bezug(tz.zeile(2));
        set_x(tz.zeile(3));
        set_y(tz.zeile(4));
        set_z(tz.zeile(5));
        set_tiefe(tz.zeile(6));
        set_radkor(tz.zeile(7));
        set_wkznum(tz.zeile(8));
        set_afb(tz.zeile(9));
    }
}


