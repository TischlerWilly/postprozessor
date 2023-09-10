#include "gehrung.h"

gehrung::gehrung()
{
    setup();
}

gehrung::gehrung(QString text)
{
    setup();
    set_text(text);
}

void gehrung::setup()
{
    Winkel          = 0;
    Bezug           = WST_BEZUG_OBSEI;
    Afb             = 1;
    Werkzeugnummer  = "";
}

void gehrung::set_pfad(strecke s)
{
    Pfad = s;
}
void gehrung::set_stapu(punkt3d sp)
{
    Pfad.set_stapu(sp);
}
void gehrung::set_endpu(punkt3d ep)
{
    Pfad.set_endpu(ep);
}
void gehrung::set_winkel(double w)
{
    if( (w >= 0) && (w <= 90) )
    {
        Winkel = w;
    }
}
void gehrung::set_winkel(QString w)
{
    set_winkel(w.toDouble());
}
void gehrung::set_riti(double ritz_tiefe)
{
    if(ritz_tiefe > 0)
    {
        Ritztiefe = ritz_tiefe;
    }else
    {
        Ritztiefe = 0;
    }
}
void gehrung::set_riti(QString ritz_tirefe)
{
    set_riti(ritz_tirefe.toDouble());
}
void gehrung::set_sti(double schnitt_tiefe)
{
    if(schnitt_tiefe > 0)
    {
        Schnittiefe = schnitt_tiefe;
    }else
    {
        Schnittiefe = 0;
    }
}
void gehrung::set_sti(QString schnitt_tiefe)
{
    set_sti(schnitt_tiefe.toDouble());
}
void gehrung::set_bezug(QString bezugsflaeche)
{
    Bezug = bezugsflaeche;
}
void gehrung::set_afb(QString ausfuehrbedingung)
{
    Afb = ausfuehrbedingung;
}
void gehrung::set_wkznum(QString nummer)
{
    Werkzeugnummer = nummer;
}

strecke gehrung::pfad()
{
    return Pfad;
}
punkt3d gehrung::stapu()
{
    return Pfad.stapu();
}
punkt3d gehrung::endpu()
{
    return Pfad.endpu();
}
double gehrung::winkel()
{
    return Winkel;
}
QString gehrung::winkel_qstring()
{
    return double_to_qstring(winkel());
}
double gehrung::riti()
{
    return Ritztiefe;
}
QString gehrung::riti_qstring()
{
    return double_to_qstring(riti());
}
double gehrung::sti()
{
    return Schnittiefe;
}
QString gehrung::sti_qstring()
{
    return double_to_qstring(sti());
}
QString gehrung::bezug()
{
    return Bezug;
}
QString gehrung::afb()
{
    return Afb;
}
QString gehrung::wkznum()
{
    return Werkzeugnummer;
}

QString gehrung::text()
{
    QString msg = BEARBART_GEHRUNG;    //Zeile 1
    msg += TRENNZ_BEARB_PARAM_;
    msg += bezug();             //Zeile 2
    msg += TRENNZ_BEARB_PARAM_;
    msg += stapu().x_QString(); //Zeile 3
    msg += TRENNZ_BEARB_PARAM_;
    msg += stapu().y_QString(); //Zeile 4
    msg += TRENNZ_BEARB_PARAM_;
    msg += endpu().x_QString(); //Zeile 5
    msg += TRENNZ_BEARB_PARAM_;
    msg += endpu().y_QString(); //Zeile 6
    msg += TRENNZ_BEARB_PARAM_;
    msg += winkel_qstring();    //Zeile 7
    msg += TRENNZ_BEARB_PARAM_;
    msg += afb();               //Zeile 8
    msg += TRENNZ_BEARB_PARAM_;
    msg += wkznum();            //Zeile 9
    msg += TRENNZ_BEARB_PARAM_;
    msg += riti_qstring();      //Zeile 10
    msg += TRENNZ_BEARB_PARAM_;
    msg += sti_qstring();       //Zeile 11

    return msg;
}
void gehrung::set_text(QString text)
{
    text_zw tz;
    tz.set_text(text,TRENNZ_BEARB_PARAM);
    if(tz.at(0) == BEARBART_GEHRUNG)
    {
        punkt3d sp, ep;
        set_bezug(tz.at(1));
        sp.set_x(tz.at(2));
        sp.set_y(tz.at(3));
        ep.set_x(tz.at(4));
        ep.set_y(tz.at(5));
        set_stapu(sp);
        set_endpu(ep);
        set_winkel(tz.at(6));
        set_afb(tz.at(7));
        set_wkznum(tz.at(8));
        set_riti(tz.at(9));
        set_sti(tz.at(10));
    }
}

