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
    pos_x = 0;
    pos_y = 0;
    pos_z = 0;
    tiefe = 0;
    bezug = WST_BEZUG_OBSEI;
    afb = "1";
    korrektur = "M";
    werkzeugnummer = "123456789";

}

void fraueseraufruf::set_x(double x)
{
    pos_x = x;
}
void fraueseraufruf::set_x(QString x)
{
    set_x(x.toDouble());
}
void fraueseraufruf::set_y(double y)
{
    pos_y = y;
}
void fraueseraufruf::set_y(QString y)
{
    set_y(y.toDouble());
}
void fraueseraufruf::set_z(double z)
{
    pos_z = z;
}
void fraueseraufruf::set_z(QString z)
{
    set_z(z.toDouble());
}
void fraueseraufruf::set_tiefe(double ti)
{
    tiefe = ti;
}
void fraueseraufruf::set_tiefe(QString ti)
{
    set_tiefe(ti.toDouble());
}
void fraueseraufruf::set_bezug(QString bezugsflaeche)
{
    bezug = bezugsflaeche;
}
void fraueseraufruf::set_afb(QString ausfuehrbedingung)
{
    afb = ausfuehrbedingung;
}
void fraueseraufruf::set_radkor(QString kor)
{
    if(kor == FRKOR_L || \
       kor == FRKOR_M || \
       kor == FRKOR_R)
    {
        korrektur = kor;
    }
}
void fraueseraufruf::set_wkznum(QString nummer)
{
    werkzeugnummer = nummer;
}

//------------------------------------------------------------
double fraueseraufruf::get_x()
{
    return pos_x;
}
QString fraueseraufruf::get_x_qstring()
{
    return double_to_qstring(pos_x);
}
double fraueseraufruf::get_y()
{
    return pos_y;
}
QString fraueseraufruf::get_y_qstring()
{
    return double_to_qstring(pos_y);
}
double fraueseraufruf::get_z()
{
    return pos_z;
}
QString fraueseraufruf::get_z_qstring()
{
    return double_to_qstring(pos_z);
}
double fraueseraufruf::get_tiefe()
{
    return tiefe;
}
QString fraueseraufruf::get_tiefe_qstring()
{
    return double_to_qstring(tiefe);
}
QString fraueseraufruf::get_bezug()
{
    return bezug;
}
QString fraueseraufruf::get_afb()
{
    return afb;
}
QString fraueseraufruf::get_radkor()
{
    return korrektur;
}
QString fraueseraufruf::get_wkznum()
{
    return werkzeugnummer;
}

QString fraueseraufruf::get_text()
{
    QString msg = BEARBART_FRAESERAUFRUF;    //Zeile 1
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_bezug();                      //Zeile 2
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_x_qstring();                  //Zeile 3
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_y_qstring();                  //Zeile 4
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_z_qstring();                  //Zeile 5
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_tiefe_qstring();              //Zeile 6
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_radkor();                     //Zeile 7
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_wkznum();                     //Zeile 8
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_afb();                        //Zeile 9

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


