#include "bohrraster.h"

bohrraster::bohrraster()
{
    setup();
}
bohrraster::bohrraster(QString text)
{
    setup();
    set_text(text);
}

void bohrraster::setup()
{
    durchmesser = 0;
    tiefe = 0;
    bezug = WST_BEZUG_OBSEI;
    afb = "1";
    zustellmass = 0;
    pos_x = 0;
    pos_y = 0;
    pos_z = 0;
    anz_x = 1;
    anz_y = 1;
    anz_z = 1;
    raster_x = 32;
    raster_y = 32;
    raster_z = 32;
}

void bohrraster::set_anz_x(uint a)
{
    if(a >= 1)
    {
        anz_x = a;
    }
}
void bohrraster::set_anz_x(QString a)
{
    set_anz_x(a.toInt());
}
void bohrraster::set_anz_y(uint a)
{
    if(a >= 1)
    {
        anz_y = a;
    }
}
void bohrraster::set_anz_y(QString a)
{
    set_anz_y(a.toInt());
}
void bohrraster::set_anz_z(uint a)
{
    if(a >= 1)
    {
        anz_z = a;
    }
}
void bohrraster::set_anz_z(QString a)
{
    set_anz_z(a.toInt());
}

void bohrraster::set_raster_x(double rastermas)
{
    if(rastermas > 0)
    {
        raster_x = rastermas;
    }
}
void bohrraster::set_raster_x(QString rastermas)
{
    set_raster_x(rastermas.toDouble());
}
void bohrraster::set_raster_y(double rastermas)
{
    if(rastermas > 0)
    {
        raster_y = rastermas;
    }
}
void bohrraster::set_raster_y(QString rastermas)
{
    set_raster_y(rastermas.toDouble());
}
void bohrraster::set_raster_z(double rastermas)
{
    if(rastermas > 0)
    {
        raster_z = rastermas;
    }
}
void bohrraster::set_raster_z(QString rastermas)
{
    set_raster_z(rastermas.toDouble());
}

QString bohrraster::get_text()
{
    QString msg = BEARBART_BOHRRASTER;    //Zeile 1
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
    msg += get_zustellmass_qstring();//Zeile 9
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_wkznum();            //Zeile 10
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_anz_x_qstring();     //Zeile 11
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_anz_y_qstring();     //Zeile 12
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_anz_z_qstring();     //Zeile 13
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_raster_x_qstring();  //Zeile 14
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_raster_y_qstring();  //Zeile 15
    msg += TRENNZ_BEARB_PARAM_;
    msg += get_raster_z_qstring();  //Zeile 16
    return msg;
}

void bohrraster::set_text(QString text)
{
    text_zeilenweise tz;
    tz.set_trennzeichen(TRENNZ_BEARB_PARAM);
    tz.set_text(text);
    if(tz.zeile(1) == BEARBART_BOHRRASTER)
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
        set_anz_x(11);
        set_anz_y(12);
        set_anz_z(13);
        set_raster_x(14);
        set_raster_y(15);
        set_raster_z(16);
    }
}

bool bohrraster::finde_bohrraster(text_zeilenweise bearb, \
                                  QString bezug, double dm, \
                                  double tiefe, QString rasterrichtung,\
                                  double wst_L, double wst_B, double wst_D)
{
    //die Funktion gibt TRUE zurück, wenn ein passendes Raster gefunden wurde
    //die Funktion stoppt, wenn genau 1 Raster gefunden wurde
    //zum Ende der Funktion sind die internen Variablen gesetzt und können ausgelesen werden
    //ggf muss die Funktion erneut aufgerufen werden um ähnliche Raster mit den selben
    //Funktions-Eingabewerten zu finden
    bool returnwert = false;
    text_zeilenweise zeile;
    zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);

    text_zeilenweise potlora; //potentielles Lochraster

    for(uint i=1; i<=bearb.zeilenanzahl() ;i++)
    {
        zeile.set_text(bearb.zeile(i));
        if(zeile.zeile(1) == BEARBART_BOHR)
        {
            QString afb_text = zeile.zeile(8);
            afb_text.replace("L", double_to_qstring(wst_L));
            afb_text.replace("B", double_to_qstring(wst_B));
            afb_text.replace("D", double_to_qstring(wst_D));
            afb_text.replace(",", ".");
            afb_text = ausdruck_auswerten(afb_text);

            if(afb_text.toDouble() >= 0)
            {
                if(zeile.zeile(2) == bezug)
                {
                    if(zeile.zeile(3).toDouble() == dm)
                    {
                        if(zeile.zeile(4).toDouble() == tiefe)
                        {
                            potlora.zeilen_anhaengen(zeile.get_text());
                        }
                    }
                }
            }
        }
    }

    if(rasterrichtung == RASTERRICHTUNG_0_BIS_L)
    {

    }else if(rasterrichtung == RASTERRICHTUNG_0_BIS_B)
    {

    }else if(rasterrichtung == RASTERRICHTUNG_0_BIS_D)
    {
        return returnwert;//Dieser Filter wird vorerst noch nicht gebraucht, desshalb nur return
    }else
    {
        return false;
    }
    return returnwert;
}















