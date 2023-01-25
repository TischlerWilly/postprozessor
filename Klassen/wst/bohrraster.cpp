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
    Durchmesser = 0;
    Tiefe = 0;
    Bezug = WST_BEZUG_OBSEI;
    Afb = "1";
    Zustellmass = 0;
    Pos_x = 0;
    Pos_y = 0;
    Pos_z = 0;
    Anz_x = 1;
    Anz_y = 1;
    Anz_z = 1;
    Raster_x = 0;
    Raster_y = 0;
    Raster_z = 0;
    Werkzeugnummer = "";
}
void bohrraster::clear()
{
    setup();
}

void bohrraster::set_startbohrung(bohrung b)
{
    clear();
    set_dm(b.dm());
    set_tiefe(b.tiefe());
    set_bezug(b.bezug());
    set_afb(b.afb());
    set_zustellmass(b.zustellmass());
    set_x(b.x());
    set_y(b.y());
    set_z(b.z());
}

void bohrraster::set_anz_x(uint a)
{
    if(a >= 1)
    {
        Anz_x = a;
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
        Anz_y = a;
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
        Anz_z = a;
    }
}
void bohrraster::set_anz_z(QString a)
{
    set_anz_z(a.toInt());
}

void bohrraster::set_raster_x(double rastermas)
{
    Raster_x = rastermas;
}
void bohrraster::set_raster_x(QString rastermas)
{
    set_raster_x(rastermas.toDouble());
}
void bohrraster::set_raster_y(double rastermas)
{
    Raster_y = rastermas;
}
void bohrraster::set_raster_y(QString rastermas)
{
    set_raster_y(rastermas.toDouble());
}
void bohrraster::set_raster_z(double rastermas)
{
    Raster_z = rastermas;
}
void bohrraster::set_raster_z(QString rastermas)
{
    set_raster_z(rastermas.toDouble());
}

QString bohrraster::text()
{
    QString msg = BEARBART_BOHRRASTER;    //Zeile 1
    msg += TRENNZ_BEARB_PARAM_;
    msg += bezug();             //Zeile 2
    msg += TRENNZ_BEARB_PARAM_;
    msg += dm_qstring();        //Zeile 3
    msg += TRENNZ_BEARB_PARAM_;
    msg += tiefe_qstring();     //Zeile 4
    msg += TRENNZ_BEARB_PARAM_;
    msg += x_qstring();         //Zeile 5
    msg += TRENNZ_BEARB_PARAM_;
    msg += y_qstring();         //Zeile 6
    msg += TRENNZ_BEARB_PARAM_;
    msg += z_qstring();         //Zeile 7
    msg += TRENNZ_BEARB_PARAM_;
    msg += afb();               //Zeile 8
    msg += TRENNZ_BEARB_PARAM_;
    msg += zustellmass_qstring();//Zeile 9
    msg += TRENNZ_BEARB_PARAM_;
    msg += wkznum();            //Zeile 10
    msg += TRENNZ_BEARB_PARAM_;
    msg += anz_x_qstring();     //Zeile 11
    msg += TRENNZ_BEARB_PARAM_;
    msg += anz_y_qstring();     //Zeile 12
    msg += TRENNZ_BEARB_PARAM_;
    msg += anz_z_qstring();     //Zeile 13
    msg += TRENNZ_BEARB_PARAM_;
    msg += raster_x_qstring();  //Zeile 14
    msg += TRENNZ_BEARB_PARAM_;
    msg += raster_y_qstring();  //Zeile 15
    msg += TRENNZ_BEARB_PARAM_;
    msg += raster_z_qstring();  //Zeile 16
    return msg;
}

QString bohrraster::text_erste_bohrung()
{
    QString msg = BEARBART_BOHR;    //Zeile 1
    msg += TRENNZ_BEARB_PARAM_;
    msg += bezug();             //Zeile 2
    msg += TRENNZ_BEARB_PARAM_;
    msg += dm_qstring();        //Zeile 3
    msg += TRENNZ_BEARB_PARAM_;
    msg += tiefe_qstring();     //Zeile 4
    msg += TRENNZ_BEARB_PARAM_;
    msg += x_qstring();         //Zeile 5
    msg += TRENNZ_BEARB_PARAM_;
    msg += y_qstring();         //Zeile 6
    msg += TRENNZ_BEARB_PARAM_;
    msg += z_qstring();         //Zeile 7
    msg += TRENNZ_BEARB_PARAM_;
    msg += afb();               //Zeile 8
    msg += TRENNZ_BEARB_PARAM_;
    msg += zustellmass_qstring();               //Zeile 9
    msg += TRENNZ_BEARB_PARAM_;
    msg += wkznum();            //Zeile 10

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
        set_anz_x(tz.zeile(11));
        set_anz_y(tz.zeile(12));
        set_anz_z(tz.zeile(13));
        set_raster_x(tz.zeile(14));
        set_raster_y(tz.zeile(15));
        set_raster_z(tz.zeile(16));
    }
}

bool bohrraster::finde_bohrraster(text_zeilenweise *bearb, \
                                  QString Bezug, double dm, \
                                  double tiefe, QString rasterrichtung,\
                                  double wst_L, double wst_B, double wst_D,\
                                  uint mindanz, double rasterabst)
{
    clear();
    //die Funktion gibt TRUE zurück, wenn ein passendes Raster gefunden wurde
    //die Funktion stoppt, wenn genau 1 Raster gefunden wurde
    //zum Ende der Funktion sind die internen Variablen gesetzt und können ausgelesen werden
    //ggf muss die Funktion erneut aufgerufen werden um ähnliche Raster mit den selben
    //Funktions-Eingabewerten zu finden
    //bearb wird als Zeiger übergeben und ist somit zum Ende der Funktion auf dem aktuellen Stand
    text_zeilenweise zeile;
    zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);

    text_zeilenweise potlora; //potentielles Lochraster

    //potlora füllen:
    for(uint i=1; i<=bearb->zeilenanzahl() ;i++)
    {
        zeile.set_text(bearb->zeile(i));
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
                if(zeile.zeile(2) == Bezug)
                {
                    if(zeile.zeile(3).toDouble() == dm)
                    {
                        if(zeile.zeile(4).toDouble() == tiefe)
                        {
                            potlora.zeilen_anhaengen(zeile.text());
                        }
                    }
                }
            }
        }
    }

    if(rasterrichtung == RASTERRICHTUNG_0_BIS_L)
    {
        if(potlora.zeilenanzahl() >= 2)
        {
            if(Bezug == WST_BEZUG_OBSEI || Bezug == WST_BEZUG_UNSEI)
            {
                bohrung b;
                punkt3d pvor;
                punkt3d pnach;
                QString merkdirmal;

                set_raster_x(rasterabst);

                //----------------------------------------------------------------------
                //Raster suchen:
                //2 paarige Bohrungen suchen:
                for(uint i=1; i<=potlora.zeilenanzahl() ;i++)
                {
                    b.set_text(potlora.zeile(i));
                    merkdirmal = potlora.zeile(i);
                    pvor.set_x(b.x() - rasterabst);
                    pvor.set_y(b.y());
                    pvor.set_z(b.z());
                    pnach.set_x(b.x() + rasterabst);
                    pnach.set_y(b.y());
                    pnach.set_z(b.z());

                    for(uint ii=1; ii<=potlora.zeilenanzahl() ;ii++)
                    {
                        if(i==ii)
                        {
                            continue;
                        }
                        bohrung b2(potlora.zeile(ii));

                        if(pvor.x_QString() == b2.x_qstring()  &&  pvor.y_QString() == b2.y_qstring())
                        {
                            set_startbohrung(b2);
                            set_anz_x(anz_x() + 1);//anz der Bohrungen erhöhen
                            potlora.zeile_loeschen(ii);
                            break;
                        }else if(pnach.x_QString() == b2.x_qstring()  &&  pnach.y_QString() == b2.y_qstring())
                        {
                            set_startbohrung(b);
                            set_anz_x(anz_x() + 1);//anz der Bohrungen erhöhen
                            potlora.zeile_loeschen(ii);
                            break;
                        }
                    }
                    if(Anz_x > 1)
                    {
                        uint zeilennumer = 0;
                        for(uint i=1; i<=potlora.zeilenanzahl() ;i++)
                        {
                            if(merkdirmal == potlora.zeile(i))
                            {
                                zeilennumer = i;
                                break;
                            }
                        }
                        if(zeilennumer!=0)
                        {
                            potlora.zeile_loeschen(zeilennumer);
                        }
                        break;
                    }
                }
                //Restliche zugehörige Bohrungen suchen:
                if(Anz_x == 2)//wenn 2 paarige Bohrungen gefunden wurden
                {
                    uint anz_alt = 1;//anz_alt != anz_x  --> 1!=2
                    while(anz_alt != anz_x())
                    {
                        anz_alt = anz_x();

                        for(uint i=1; i<=potlora.zeilenanzahl() ;i++)
                        {
                            pvor.set_x(x() - rasterabst );
                            pnach.set_x(x() + (rasterabst * anz_x())  );

                            bohrung b2(potlora.zeile(i));

                            if(pvor.x_QString() == b2.x_qstring()  &&  pvor.y_QString() == b2.y_qstring())
                            {
                                set_x(x()-rasterabst);//erste Bohrung neu setzen
                                set_anz_x(anz_x() + 1);//anz der Bohrungen erhöhen
                                potlora.zeile_loeschen(i);
                                break;
                            }else if(pnach.x_QString() == b2.x_qstring()  &&  pnach.y_QString() == b2.y_qstring())
                            {
                                set_anz_x(anz_x() + 1);//anz der Bohrungen erhöhen
                                potlora.zeile_loeschen(i);
                                break;
                            }
                        }
                    }
                }

                //----------------------------------------------------------------------
                //Daten zurück speichern / Einzelbohrungen durch Raster ersetzen:
                set_raster_x(rasterabst);
                if(Anz_x >= mindanz)
                {
                    //erste Bohrung des Rasters in bearb finden und durch Bohrraster ersetzen (Damit Reihenfolge der Bearbeitungen stimmt):
                    for(uint i=1; i<=bearb->zeilenanzahl();i++)
                    {
                        zeile.set_text(bearb->zeile(i));
                        if(zeile.zeile(1) == BEARBART_BOHR)
                        {
                            bohrung b(zeile.text());
                            if(b.x_qstring() == x_qstring()  &&\
                               b.y_qstring() == y_qstring()  &&\
                               b.dm_qstring() == dm_qstring()  &&\
                               b.tiefe_qstring() == tiefe_qstring() &&\
                               b.bezug() == bezug())
                            {
                                bearb->zeile_ersaetzen(i, text());
                            }
                        }
                    }
                    //Restliche Bohrungen des Rasters finden und löschen
                    for(uint i = 1; i<Anz_x ;i++)
                    {
                        for(uint ii=1; ii<=bearb->zeilenanzahl() ;ii++)
                        {
                            zeile.set_text(bearb->zeile(ii));
                            if(zeile.zeile(1) == BEARBART_BOHR)
                            {
                                bohrung beinzeln(zeile.text());
                                bohrung bausraster(text_erste_bohrung());
                                bausraster.set_x(x()+i*rasterabst);
                                if(beinzeln.x_qstring() == bausraster.x_qstring() &&\
                                   beinzeln.y_qstring() == bausraster.y_qstring() &&\
                                   beinzeln.dm_qstring() == bausraster.dm_qstring() &&\
                                   beinzeln.tiefe_qstring() == bausraster.tiefe_qstring() &&\
                                   beinzeln.bezug() == bausraster.bezug()              )
                                {
                                    bearb->zeile_loeschen(ii);
                                    break;
                                }
                            }
                        }
                    }
                    return true;
                }else
                {
                    return false;
                }
            }else if(Bezug == WST_BEZUG_VO || Bezug == WST_BEZUG_HI)
            {
                bohrung b;
                punkt3d pvor;
                punkt3d pnach;
                QString merkdirmal;

                set_raster_x(rasterabst);

                //----------------------------------------------------------------------
                //Raster suchen:
                //2 paarige Bohrungen suchen:
                for(uint i=1; i<=potlora.zeilenanzahl() ;i++)
                {
                    b.set_text(potlora.zeile(i));
                    merkdirmal = potlora.zeile(i);
                    pvor.set_x(b.x() - rasterabst);
                    pvor.set_y(b.y());
                    pvor.set_z(b.z());
                    pnach.set_x(b.x() + rasterabst);
                    pnach.set_y(b.y());
                    pnach.set_z(b.z());

                    for(uint ii=1; ii<=potlora.zeilenanzahl() ;ii++)
                    {
                        if(i==ii)
                        {
                            continue;
                        }
                        bohrung b2(potlora.zeile(ii));

                        if(pvor.x_QString() == b2.x_qstring()  &&  pvor.z_QString() == b2.z_qstring())
                        {
                            set_startbohrung(b2);
                            set_anz_x(anz_x() + 1);//anz der Bohrungen erhöhen
                            potlora.zeile_loeschen(ii);
                            break;
                        }else if(pnach.x_QString() == b2.x_qstring()  &&  pnach.z_QString() == b2.z_qstring())
                        {
                            set_startbohrung(b);
                            set_anz_x(anz_x() + 1);//anz der Bohrungen erhöhen
                            potlora.zeile_loeschen(ii);
                            break;
                        }
                    }
                    if(Anz_x > 1)
                    {
                        uint zeilennumer = 0;
                        for(uint i=1; i<=potlora.zeilenanzahl() ;i++)
                        {
                            if(merkdirmal == potlora.zeile(i))
                            {
                                zeilennumer = i;
                                break;
                            }
                        }
                        if(zeilennumer!=0)
                        {
                            potlora.zeile_loeschen(zeilennumer);
                        }
                        break;
                    }
                }
                //Restliche zugehörige Bohrungen suchen:
                if(Anz_x == 2)//wenn 2 paarige Bohrungen gefunden wurden
                {
                    uint anz_alt = 1;//anz_alt != anz_x  --> 1!=2
                    while(anz_alt != anz_x())
                    {
                        anz_alt = anz_x();

                        for(uint i=1; i<=potlora.zeilenanzahl() ;i++)
                        {
                            pvor.set_x(x() - rasterabst );
                            pnach.set_x(x() + (rasterabst * anz_x())  );

                            bohrung b2(potlora.zeile(i));

                            if(pvor.x_QString() == b2.x_qstring()  &&  pvor.z_QString() == b2.z_qstring())
                            {
                                set_x(x()-rasterabst);//erste Bohrung neu setzen
                                set_anz_x(anz_x() + 1);//anz der Bohrungen erhöhen
                                potlora.zeile_loeschen(i);
                                break;
                            }else if(pnach.x_QString() == b2.x_qstring()  &&  pnach.z_QString() == b2.z_qstring())
                            {
                                set_anz_x(anz_x() + 1);//anz der Bohrungen erhöhen
                                potlora.zeile_loeschen(i);
                                break;
                            }
                        }
                    }
                }

                //----------------------------------------------------------------------
                //Daten zurück speichern / Einzelbohrungen durch Raster ersetzen:
                set_raster_x(rasterabst);
                if(Anz_x >= mindanz)
                {
                    //erste Bohrung des Rasters in bearb finden und durch Bohrraster ersetzen (Damit Reihenfolge der Bearbeitungen stimmt):
                    for(uint i=1; i<=bearb->zeilenanzahl();i++)
                    {
                        zeile.set_text(bearb->zeile(i));
                        if(zeile.zeile(1) == BEARBART_BOHR)
                        {
                            bohrung b(zeile.text());
                            if(b.x_qstring() == x_qstring()  &&\
                               b.z_qstring() == z_qstring()  &&\
                               b.dm_qstring() == dm_qstring()  &&\
                               b.tiefe_qstring() == tiefe_qstring() &&\
                               b.bezug() == bezug())
                            {
                                bearb->zeile_ersaetzen(i, text());
                            }
                        }
                    }
                    //Restliche Bohrungen des Rasters finden und löschen
                    for(uint i = 1; i<Anz_x ;i++)
                    {
                        for(uint ii=1; ii<=bearb->zeilenanzahl() ;ii++)
                        {
                            zeile.set_text(bearb->zeile(ii));
                            if(zeile.zeile(1) == BEARBART_BOHR)
                            {
                                bohrung beinzeln(zeile.text());
                                bohrung bausraster(text_erste_bohrung());
                                bausraster.set_x(x()+i*rasterabst);
                                if(beinzeln.x_qstring() == bausraster.x_qstring() &&\
                                   beinzeln.y_qstring() == bausraster.y_qstring() &&\
                                   beinzeln.dm_qstring() == bausraster.dm_qstring() &&\
                                   beinzeln.tiefe_qstring() == bausraster.tiefe_qstring() &&\
                                   beinzeln.bezug() == bausraster.bezug()           )
                                {
                                    bearb->zeile_loeschen(ii);
                                    break;
                                }
                            }
                        }
                    }
                    return true;
                }else
                {
                    return false;
                }
            }
        }
    }else if(rasterrichtung == RASTERRICHTUNG_0_BIS_B)
    {
        if(potlora.zeilenanzahl() >= 2)
        {
            if(Bezug == WST_BEZUG_OBSEI || Bezug == WST_BEZUG_UNSEI)
            {
                bohrung b;
                punkt3d pvor;
                punkt3d pnach;
                QString merkdirmal;

                set_raster_y(rasterabst);

                //----------------------------------------------------------------------
                //Raster suchen:
                //2 paarige Bohrungen suchen:
                for(uint i=1; i<=potlora.zeilenanzahl() ;i++)
                {
                    b.set_text(potlora.zeile(i));
                    merkdirmal = potlora.zeile(i);
                    pvor.set_x(b.x());
                    pvor.set_y(b.y() - rasterabst);
                    pvor.set_z(b.z());
                    pnach.set_x(b.x());
                    pnach.set_y(b.y() + rasterabst);
                    pnach.set_z(b.z());

                    for(uint ii=1; ii<=potlora.zeilenanzahl() ;ii++)
                    {
                        if(i==ii)
                        {
                            continue;
                        }
                        bohrung b2(potlora.zeile(ii));

                        if(pvor.x_QString() == b2.x_qstring()  &&  pvor.y_QString() == b2.y_qstring())
                        {
                            set_startbohrung(b2);
                            set_anz_y(anz_y() + 1);//anz der Bohrungen erhöhen
                            potlora.zeile_loeschen(ii);
                            break;
                        }else if(pnach.x_QString() == b2.x_qstring()  &&  pnach.y_QString() == b2.y_qstring())
                        {
                            set_startbohrung(b);
                            set_anz_y(anz_y() + 1);//anz der Bohrungen erhöhen
                            potlora.zeile_loeschen(ii);
                            break;
                        }
                    }
                    if(Anz_y > 1)
                    {
                        uint zeilennumer = 0;
                        for(uint i=1; i<=potlora.zeilenanzahl() ;i++)
                        {
                            if(merkdirmal == potlora.zeile(i))
                            {
                                zeilennumer = i;
                                break;
                            }
                        }
                        if(zeilennumer!=0)
                        {
                            potlora.zeile_loeschen(zeilennumer);
                        }
                        break;
                    }
                }
                //Restliche zugehörige Bohrungen suchen:
                if(Anz_y == 2)//wenn 2 paarige Bohrungen gefunden wurden
                {
                    uint anz_alt = 1;//anz_alt != anz_y  --> 1!=2
                    while(anz_alt != anz_y())
                    {
                        anz_alt = anz_y();

                        for(uint i=1; i<=potlora.zeilenanzahl() ;i++)
                        {
                            pvor.set_y(y() - rasterabst );
                            pnach.set_y(y() + (rasterabst * anz_y())  );

                            bohrung b2(potlora.zeile(i));

                            if(pvor.x_QString() == b2.x_qstring()  &&  pvor.y_QString() == b2.y_qstring())
                            {
                                set_y(y()-rasterabst);//erste Bohrung neu setzen
                                set_anz_y(anz_y() + 1);//anz der Bohrungen erhöhen
                                potlora.zeile_loeschen(i);
                                break;
                            }else if(pnach.x_QString() == b2.x_qstring()  &&  pnach.y_QString() == b2.y_qstring())
                            {
                                set_anz_y(anz_y() + 1);//anz der Bohrungen erhöhen
                                potlora.zeile_loeschen(i);
                                break;
                            }
                        }
                    }


                }

                //----------------------------------------------------------------------
                //Daten zurück speichern / Einzelbohrungen durch Raster ersetzen:
                set_raster_y(rasterabst);
                if(Anz_y >= mindanz)
                {
                    //erste Bohrung des Rasters in bearb finden und durch Bohrraster ersetzen (Damit Reihenfolge der Bearbeitungen stimmt):
                    for(uint i=1; i<=bearb->zeilenanzahl();i++)
                    {
                        zeile.set_text(bearb->zeile(i));
                        if(zeile.zeile(1) == BEARBART_BOHR)
                        {
                            bohrung b(zeile.text());
                            if(b.x_qstring() == x_qstring()  &&\
                               b.y_qstring() == y_qstring()  &&\
                               b.dm_qstring() == dm_qstring()  &&\
                               b.tiefe_qstring() == tiefe_qstring() &&\
                               b.bezug() == bezug())
                            {
                                bearb->zeile_ersaetzen(i, text());
                            }
                        }
                    }
                    //Restliche Bohrungen des Rasters finden und löschen
                    for(uint i = 1; i<Anz_y ;i++)
                    {
                        for(uint ii=1; ii<=bearb->zeilenanzahl() ;ii++)
                        {
                            zeile.set_text(bearb->zeile(ii));
                            if(zeile.zeile(1) == BEARBART_BOHR)
                            {
                                bohrung beinzeln(zeile.text());
                                bohrung bausraster(text_erste_bohrung());
                                bausraster.set_y(y()+i*rasterabst);
                                if(beinzeln.x_qstring() == bausraster.x_qstring() &&\
                                   beinzeln.y_qstring() == bausraster.y_qstring() &&\
                                   beinzeln.dm_qstring() == bausraster.dm_qstring() &&\
                                   beinzeln.tiefe_qstring() == bausraster.tiefe_qstring() &&\
                                   beinzeln.bezug() == bausraster.bezug()             )
                                {
                                    bearb->zeile_loeschen(ii);
                                    break;
                                }
                            }
                        }
                    }
                    return true;
                }else
                {
                    return false;
                }
            }else if(Bezug == WST_BEZUG_LI || Bezug == WST_BEZUG_RE)
            {
                bohrung b;
                punkt3d pvor;
                punkt3d pnach;
                QString merkdirmal;

                set_raster_y(rasterabst);

                //----------------------------------------------------------------------
                //Raster suchen:
                //2 paarige Bohrungen suchen:
                for(uint i=1; i<=potlora.zeilenanzahl() ;i++)
                {
                    b.set_text(potlora.zeile(i));
                    merkdirmal = potlora.zeile(i);
                    pvor.set_x(b.x());
                    pvor.set_y(b.y() - rasterabst);
                    pvor.set_z(b.z());
                    pnach.set_x(b.x());
                    pnach.set_y(b.y() + rasterabst);
                    pnach.set_z(b.z());

                    for(uint ii=1; ii<=potlora.zeilenanzahl() ;ii++)
                    {
                        if(i==ii)
                        {
                            continue;
                        }
                        bohrung b2(potlora.zeile(ii));

                        if(pvor.z_QString() == b2.z_qstring()  &&  pvor.y_QString() == b2.y_qstring())
                        {
                            set_startbohrung(b2);
                            set_anz_y(anz_y() + 1);//anz der Bohrungen erhöhen
                            potlora.zeile_loeschen(ii);
                            break;
                        }else if(pnach.z_QString() == b2.z_qstring()  &&  pnach.y_QString() == b2.y_qstring())
                        {
                            set_startbohrung(b);
                            set_anz_y(anz_y() + 1);//anz der Bohrungen erhöhen
                            potlora.zeile_loeschen(ii);
                            break;
                        }
                    }
                    if(Anz_y > 1)
                    {
                        uint zeilennumer = 0;
                        for(uint i=1; i<=potlora.zeilenanzahl() ;i++)
                        {
                            if(merkdirmal == potlora.zeile(i))
                            {
                                zeilennumer = i;
                                break;
                            }
                        }
                        if(zeilennumer!=0)
                        {
                            potlora.zeile_loeschen(zeilennumer);
                        }
                        break;
                    }
                }
                //Restliche zugehörige Bohrungen suchen:
                if(Anz_y == 2)//wenn 2 paarige Bohrungen gefunden wurden
                {
                    uint anz_alt = 1;//anz_alt != anz_y  --> 1!=2
                    while(anz_alt != anz_y())
                    {
                        anz_alt = anz_y();

                        for(uint i=1; i<=potlora.zeilenanzahl() ;i++)
                        {
                            pvor.set_y(y() - rasterabst );
                            pnach.set_y(y() + (rasterabst * anz_y())  );

                            bohrung b2(potlora.zeile(i));

                            if(pvor.z_QString() == b2.z_qstring()  &&  pvor.y_QString() == b2.y_qstring())
                            {
                                set_y(y()-rasterabst);//erste Bohrung neu setzen
                                set_anz_y(anz_y() + 1);//anz der Bohrungen erhöhen
                                potlora.zeile_loeschen(i);
                                break;
                            }else if(pnach.z_QString() == b2.z_qstring()  &&  pnach.y_QString() == b2.y_qstring())
                            {
                                set_anz_y(anz_y() + 1);//anz der Bohrungen erhöhen
                                potlora.zeile_loeschen(i);
                                break;
                            }
                        }
                    }


                }

                //----------------------------------------------------------------------
                //Daten zurück speichern / Einzelbohrungen durch Raster ersetzen:
                set_raster_y(rasterabst);
                if(Anz_y >= mindanz)
                {
                    //erste Bohrung des Rasters in bearb finden und durch Bohrraster ersetzen (Damit Reihenfolge der Bearbeitungen stimmt):
                    for(uint i=1; i<=bearb->zeilenanzahl();i++)
                    {
                        zeile.set_text(bearb->zeile(i));
                        if(zeile.zeile(1) == BEARBART_BOHR)
                        {
                            bohrung b(zeile.text());
                            if(b.z_qstring() == z_qstring()  &&\
                               b.y_qstring() == y_qstring()  &&\
                               b.dm_qstring() == dm_qstring()  &&\
                               b.tiefe_qstring() == tiefe_qstring() &&\
                               b.bezug() == bezug())
                            {
                                bearb->zeile_ersaetzen(i, text());
                            }
                        }
                    }
                    //Restliche Bohrungen des Rasters finden und löschen
                    for(uint i = 1; i<Anz_y ;i++)
                    {
                        for(uint ii=1; ii<=bearb->zeilenanzahl() ;ii++)
                        {
                            zeile.set_text(bearb->zeile(ii));
                            if(zeile.zeile(1) == BEARBART_BOHR)
                            {
                                bohrung beinzeln(zeile.text());
                                bohrung bausraster(text_erste_bohrung());
                                bausraster.set_y(y()+i*rasterabst);
                                if(beinzeln.x_qstring() == bausraster.x_qstring() &&\
                                   beinzeln.y_qstring() == bausraster.y_qstring() &&\
                                   beinzeln.dm_qstring() == bausraster.dm_qstring() &&\
                                   beinzeln.tiefe_qstring() == bausraster.tiefe_qstring() &&\
                                   beinzeln.bezug() == bausraster.bezug()            )
                                {
                                    bearb->zeile_loeschen(ii);
                                    break;
                                }
                            }
                        }
                    }
                    return true;
                }else
                {
                    return false;
                }
            }
        }
    }else if(rasterrichtung == RASTERRICHTUNG_0_BIS_D)
    {
        return false;//Dieser Filter wird vorerst noch nicht gebraucht, desshalb nur return
    }else
    {
        return false;
    }


    return false;//wird nie erreicht
}

bool bohrraster::finde_bohrraster(text_zw *bearb, \
                                  QString Bezug, double dm, \
                                  double tiefe, QString rasterrichtung,\
                                  double wst_L, double wst_B, double wst_D,\
                                  uint mindanz, double rasterabst)
{
    clear();
    //die Funktion gibt TRUE zurück, wenn ein passendes Raster gefunden wurde
    //die Funktion stoppt, wenn genau 1 Raster gefunden wurde
    //zum Ende der Funktion sind die internen Variablen gesetzt und können ausgelesen werden
    //ggf muss die Funktion erneut aufgerufen werden um ähnliche Raster mit den selben
    //Funktions-Eingabewerten zu finden
    //bearb wird als Zeiger übergeben und ist somit zum Ende der Funktion auf dem aktuellen Stand
    text_zw zeile;
    text_zeilenweise potlora; //potentielles Lochraster

    //potlora füllen:
    for(uint i=0; i<bearb->count() ;i++)
    {
        zeile.set_text(bearb->at(i), TRENNZ_BEARB_PARAM);
        if(zeile.at(0) == BEARBART_BOHR)
        {
            QString afb_text = zeile.at(7);
            afb_text.replace("L", double_to_qstring(wst_L));
            afb_text.replace("B", double_to_qstring(wst_B));
            afb_text.replace("D", double_to_qstring(wst_D));
            afb_text.replace(",", ".");
            afb_text = ausdruck_auswerten(afb_text);

            if(afb_text.toDouble() >= 0)
            {
                if(zeile.at(1) == Bezug)
                {
                    if(zeile.at(2).toDouble() == dm)
                    {
                        if(zeile.at(3).toDouble() == tiefe)
                        {
                            potlora.zeilen_anhaengen(zeile.text());
                        }
                    }
                }
            }
        }
    }

    if(rasterrichtung == RASTERRICHTUNG_0_BIS_L)
    {
        if(potlora.zeilenanzahl() >= 2)
        {
            if(Bezug == WST_BEZUG_OBSEI || Bezug == WST_BEZUG_UNSEI)
            {
                bohrung b;
                punkt3d pvor;
                punkt3d pnach;
                QString merkdirmal;

                set_raster_x(rasterabst);

                //----------------------------------------------------------------------
                //Raster suchen:
                //2 paarige Bohrungen suchen:
                for(uint i=1; i<=potlora.zeilenanzahl() ;i++)
                {
                    b.set_text(potlora.zeile(i));
                    merkdirmal = potlora.zeile(i);
                    pvor.set_x(b.x() - rasterabst);
                    pvor.set_y(b.y());
                    pvor.set_z(b.z());
                    pnach.set_x(b.x() + rasterabst);
                    pnach.set_y(b.y());
                    pnach.set_z(b.z());

                    for(uint ii=1; ii<=potlora.zeilenanzahl() ;ii++)
                    {
                        if(i==ii)
                        {
                            continue;
                        }
                        bohrung b2(potlora.zeile(ii));

                        if(pvor.x_QString() == b2.x_qstring()  &&  pvor.y_QString() == b2.y_qstring())
                        {
                            set_startbohrung(b2);
                            set_anz_x(anz_x() + 1);//anz der Bohrungen erhöhen
                            potlora.zeile_loeschen(ii);
                            break;
                        }else if(pnach.x_QString() == b2.x_qstring()  &&  pnach.y_QString() == b2.y_qstring())
                        {
                            set_startbohrung(b);
                            set_anz_x(anz_x() + 1);//anz der Bohrungen erhöhen
                            potlora.zeile_loeschen(ii);
                            break;
                        }
                    }
                    if(Anz_x > 1)
                    {
                        uint zeilennumer = 0;
                        for(uint i=1; i<=potlora.zeilenanzahl() ;i++)
                        {
                            if(merkdirmal == potlora.zeile(i))
                            {
                                zeilennumer = i;
                                break;
                            }
                        }
                        if(zeilennumer!=0)
                        {
                            potlora.zeile_loeschen(zeilennumer);
                        }
                        break;
                    }
                }
                //Restliche zugehörige Bohrungen suchen:
                if(Anz_x == 2)//wenn 2 paarige Bohrungen gefunden wurden
                {
                    uint anz_alt = 1;//anz_alt != anz_x  --> 1!=2
                    while(anz_alt != anz_x())
                    {
                        anz_alt = anz_x();

                        for(uint i=1; i<=potlora.zeilenanzahl() ;i++)
                        {
                            pvor.set_x(x() - rasterabst );
                            pnach.set_x(x() + (rasterabst * anz_x())  );

                            bohrung b2(potlora.zeile(i));

                            if(pvor.x_QString() == b2.x_qstring()  &&  pvor.y_QString() == b2.y_qstring())
                            {
                                set_x(x()-rasterabst);//erste Bohrung neu setzen
                                set_anz_x(anz_x() + 1);//anz der Bohrungen erhöhen
                                potlora.zeile_loeschen(i);
                                break;
                            }else if(pnach.x_QString() == b2.x_qstring()  &&  pnach.y_QString() == b2.y_qstring())
                            {
                                set_anz_x(anz_x() + 1);//anz der Bohrungen erhöhen
                                potlora.zeile_loeschen(i);
                                break;
                            }
                        }
                    }
                }

                //----------------------------------------------------------------------
                //Daten zurück speichern / Einzelbohrungen durch Raster ersetzen:
                set_raster_x(rasterabst);
                if(Anz_x >= mindanz)
                {
                    //erste Bohrung des Rasters in bearb finden und durch Bohrraster ersetzen (Damit Reihenfolge der Bearbeitungen stimmt):
                    for(uint i=0; i<bearb->count();i++)
                    {
                        zeile.set_text(bearb->at(i), TRENNZ_BEARB_PARAM);
                        if(zeile.at(0) == BEARBART_BOHR)
                        {
                            bohrung b(zeile.text());
                            if(b.x_qstring() == x_qstring()  &&\
                               b.y_qstring() == y_qstring()  &&\
                               b.dm_qstring() == dm_qstring()  &&\
                               b.tiefe_qstring() == tiefe_qstring() &&\
                               b.bezug() == bezug())
                            {
                                bearb->edit(i, text());
                            }
                        }
                    }
                    //Restliche Bohrungen des Rasters finden und löschen
                    for(uint i = 1; i<Anz_x ;i++)
                    {
                        for(uint ii=0; ii<bearb->count() ;ii++)
                        {
                            zeile.set_text(bearb->at(ii), TRENNZ_BEARB_PARAM);
                            if(zeile.at(0) == BEARBART_BOHR)
                            {
                                bohrung beinzeln(zeile.text());
                                bohrung bausraster(text_erste_bohrung());
                                bausraster.set_x(x()+i*rasterabst);
                                if(beinzeln.x_qstring() == bausraster.x_qstring() &&\
                                   beinzeln.y_qstring() == bausraster.y_qstring() &&\
                                   beinzeln.dm_qstring() == bausraster.dm_qstring() &&\
                                   beinzeln.tiefe_qstring() == bausraster.tiefe_qstring() &&\
                                   beinzeln.bezug() == bausraster.bezug()              )
                                {
                                    bearb->entf(ii);
                                    break;
                                }
                            }
                        }
                    }
                    return true;
                }else
                {
                    return false;
                }
            }else if(Bezug == WST_BEZUG_VO || Bezug == WST_BEZUG_HI)
            {
                bohrung b;
                punkt3d pvor;
                punkt3d pnach;
                QString merkdirmal;

                set_raster_x(rasterabst);

                //----------------------------------------------------------------------
                //Raster suchen:
                //2 paarige Bohrungen suchen:
                for(uint i=1; i<=potlora.zeilenanzahl() ;i++)
                {
                    b.set_text(potlora.zeile(i));
                    merkdirmal = potlora.zeile(i);
                    pvor.set_x(b.x() - rasterabst);
                    pvor.set_y(b.y());
                    pvor.set_z(b.z());
                    pnach.set_x(b.x() + rasterabst);
                    pnach.set_y(b.y());
                    pnach.set_z(b.z());

                    for(uint ii=1; ii<=potlora.zeilenanzahl() ;ii++)
                    {
                        if(i==ii)
                        {
                            continue;
                        }
                        bohrung b2(potlora.zeile(ii));

                        if(pvor.x_QString() == b2.x_qstring()  &&  pvor.z_QString() == b2.z_qstring())
                        {
                            set_startbohrung(b2);
                            set_anz_x(anz_x() + 1);//anz der Bohrungen erhöhen
                            potlora.zeile_loeschen(ii);
                            break;
                        }else if(pnach.x_QString() == b2.x_qstring()  &&  pnach.z_QString() == b2.z_qstring())
                        {
                            set_startbohrung(b);
                            set_anz_x(anz_x() + 1);//anz der Bohrungen erhöhen
                            potlora.zeile_loeschen(ii);
                            break;
                        }
                    }
                    if(Anz_x > 1)
                    {
                        uint zeilennumer = 0;
                        for(uint i=1; i<=potlora.zeilenanzahl() ;i++)
                        {
                            if(merkdirmal == potlora.zeile(i))
                            {
                                zeilennumer = i;
                                break;
                            }
                        }
                        if(zeilennumer!=0)
                        {
                            potlora.zeile_loeschen(zeilennumer);
                        }
                        break;
                    }
                }
                //Restliche zugehörige Bohrungen suchen:
                if(Anz_x == 2)//wenn 2 paarige Bohrungen gefunden wurden
                {
                    uint anz_alt = 1;//anz_alt != anz_x  --> 1!=2
                    while(anz_alt != anz_x())
                    {
                        anz_alt = anz_x();

                        for(uint i=1; i<=potlora.zeilenanzahl() ;i++)
                        {
                            pvor.set_x(x() - rasterabst );
                            pnach.set_x(x() + (rasterabst * anz_x())  );

                            bohrung b2(potlora.zeile(i));

                            if(pvor.x_QString() == b2.x_qstring()  &&  pvor.z_QString() == b2.z_qstring())
                            {
                                set_x(x()-rasterabst);//erste Bohrung neu setzen
                                set_anz_x(anz_x() + 1);//anz der Bohrungen erhöhen
                                potlora.zeile_loeschen(i);
                                break;
                            }else if(pnach.x_QString() == b2.x_qstring()  &&  pnach.z_QString() == b2.z_qstring())
                            {
                                set_anz_x(anz_x() + 1);//anz der Bohrungen erhöhen
                                potlora.zeile_loeschen(i);
                                break;
                            }
                        }
                    }
                }

                //----------------------------------------------------------------------
                //Daten zurück speichern / Einzelbohrungen durch Raster ersetzen:
                set_raster_x(rasterabst);
                if(Anz_x >= mindanz)
                {
                    //erste Bohrung des Rasters in bearb finden und durch Bohrraster ersetzen (Damit Reihenfolge der Bearbeitungen stimmt):
                    for(uint i=0; i<bearb->count();i++)
                    {
                        zeile.set_text(bearb->at(i), TRENNZ_BEARB_PARAM);
                        if(zeile.at(0) == BEARBART_BOHR)
                        {
                            bohrung b(zeile.text());
                            if(b.x_qstring() == x_qstring()  &&\
                               b.z_qstring() == z_qstring()  &&\
                               b.dm_qstring() == dm_qstring()  &&\
                               b.tiefe_qstring() == tiefe_qstring() &&\
                               b.bezug() == bezug())
                            {
                                bearb->edit(i, text());
                            }
                        }
                    }
                    //Restliche Bohrungen des Rasters finden und löschen
                    for(uint i = 1; i<Anz_x ;i++)
                    {
                        for(uint ii=0; ii<bearb->count() ;ii++)
                        {
                            zeile.set_text(bearb->at(ii), TRENNZ_BEARB_PARAM);
                            if(zeile.at(0) == BEARBART_BOHR)
                            {
                                bohrung beinzeln(zeile.text());
                                bohrung bausraster(text_erste_bohrung());
                                bausraster.set_x(x()+i*rasterabst);
                                if(beinzeln.x_qstring() == bausraster.x_qstring() &&\
                                   beinzeln.y_qstring() == bausraster.y_qstring() &&\
                                   beinzeln.dm_qstring() == bausraster.dm_qstring() &&\
                                   beinzeln.tiefe_qstring() == bausraster.tiefe_qstring() &&\
                                   beinzeln.bezug() == bausraster.bezug()           )
                                {
                                    bearb->entf(ii);
                                    break;
                                }
                            }
                        }
                    }
                    return true;
                }else
                {
                    return false;
                }
            }
        }
    }else if(rasterrichtung == RASTERRICHTUNG_0_BIS_B)
    {
        if(potlora.zeilenanzahl() >= 2)
        {
            if(Bezug == WST_BEZUG_OBSEI || Bezug == WST_BEZUG_UNSEI)
            {
                bohrung b;
                punkt3d pvor;
                punkt3d pnach;
                QString merkdirmal;

                set_raster_y(rasterabst);

                //----------------------------------------------------------------------
                //Raster suchen:
                //2 paarige Bohrungen suchen:
                for(uint i=1; i<=potlora.zeilenanzahl() ;i++)
                {
                    b.set_text(potlora.zeile(i));
                    merkdirmal = potlora.zeile(i);
                    pvor.set_x(b.x());
                    pvor.set_y(b.y() - rasterabst);
                    pvor.set_z(b.z());
                    pnach.set_x(b.x());
                    pnach.set_y(b.y() + rasterabst);
                    pnach.set_z(b.z());

                    for(uint ii=1; ii<=potlora.zeilenanzahl() ;ii++)
                    {
                        if(i==ii)
                        {
                            continue;
                        }
                        bohrung b2(potlora.zeile(ii));

                        if(pvor.x_QString() == b2.x_qstring()  &&  pvor.y_QString() == b2.y_qstring())
                        {
                            set_startbohrung(b2);
                            set_anz_y(anz_y() + 1);//anz der Bohrungen erhöhen
                            potlora.zeile_loeschen(ii);
                            break;
                        }else if(pnach.x_QString() == b2.x_qstring()  &&  pnach.y_QString() == b2.y_qstring())
                        {
                            set_startbohrung(b);
                            set_anz_y(anz_y() + 1);//anz der Bohrungen erhöhen
                            potlora.zeile_loeschen(ii);
                            break;
                        }
                    }
                    if(Anz_y > 1)
                    {
                        uint zeilennumer = 0;
                        for(uint i=1; i<=potlora.zeilenanzahl() ;i++)
                        {
                            if(merkdirmal == potlora.zeile(i))
                            {
                                zeilennumer = i;
                                break;
                            }
                        }
                        if(zeilennumer!=0)
                        {
                            potlora.zeile_loeschen(zeilennumer);
                        }
                        break;
                    }
                }
                //Restliche zugehörige Bohrungen suchen:
                if(Anz_y == 2)//wenn 2 paarige Bohrungen gefunden wurden
                {
                    uint anz_alt = 1;//anz_alt != anz_y  --> 1!=2
                    while(anz_alt != anz_y())
                    {
                        anz_alt = anz_y();

                        for(uint i=1; i<=potlora.zeilenanzahl() ;i++)
                        {
                            pvor.set_y(y() - rasterabst );
                            pnach.set_y(y() + (rasterabst * anz_y())  );

                            bohrung b2(potlora.zeile(i));

                            if(pvor.x_QString() == b2.x_qstring()  &&  pvor.y_QString() == b2.y_qstring())
                            {
                                set_y(y()-rasterabst);//erste Bohrung neu setzen
                                set_anz_y(anz_y() + 1);//anz der Bohrungen erhöhen
                                potlora.zeile_loeschen(i);
                                break;
                            }else if(pnach.x_QString() == b2.x_qstring()  &&  pnach.y_QString() == b2.y_qstring())
                            {
                                set_anz_y(anz_y() + 1);//anz der Bohrungen erhöhen
                                potlora.zeile_loeschen(i);
                                break;
                            }
                        }
                    }


                }

                //----------------------------------------------------------------------
                //Daten zurück speichern / Einzelbohrungen durch Raster ersetzen:
                set_raster_y(rasterabst);
                if(Anz_y >= mindanz)
                {
                    //erste Bohrung des Rasters in bearb finden und durch Bohrraster ersetzen (Damit Reihenfolge der Bearbeitungen stimmt):
                    for(uint i=0; i<bearb->count();i++)
                    {
                        zeile.set_text(bearb->at(i), TRENNZ_BEARB_PARAM);
                        if(zeile.at(0) == BEARBART_BOHR)
                        {
                            bohrung b(zeile.text());
                            if(b.x_qstring() == x_qstring()  &&\
                               b.y_qstring() == y_qstring()  &&\
                               b.dm_qstring() == dm_qstring()  &&\
                               b.tiefe_qstring() == tiefe_qstring() &&\
                               b.bezug() == bezug())
                            {
                                bearb->edit(i, text());
                            }
                        }
                    }
                    //Restliche Bohrungen des Rasters finden und löschen
                    for(uint i = 1; i<Anz_y ;i++)
                    {
                        for(uint ii=0; ii<bearb->count() ;ii++)
                        {
                            zeile.set_text(bearb->at(ii), TRENNZ_BEARB_PARAM);
                            if(zeile.at(0) == BEARBART_BOHR)
                            {
                                bohrung beinzeln(zeile.text());
                                bohrung bausraster(text_erste_bohrung());
                                bausraster.set_y(y()+i*rasterabst);
                                if(beinzeln.x_qstring() == bausraster.x_qstring() &&\
                                   beinzeln.y_qstring() == bausraster.y_qstring() &&\
                                   beinzeln.dm_qstring() == bausraster.dm_qstring() &&\
                                   beinzeln.tiefe_qstring() == bausraster.tiefe_qstring() &&\
                                   beinzeln.bezug() == bausraster.bezug()             )
                                {
                                    bearb->entf(ii);
                                    break;
                                }
                            }
                        }
                    }
                    return true;
                }else
                {
                    return false;
                }
            }else if(Bezug == WST_BEZUG_LI || Bezug == WST_BEZUG_RE)
            {
                bohrung b;
                punkt3d pvor;
                punkt3d pnach;
                QString merkdirmal;

                set_raster_y(rasterabst);

                //----------------------------------------------------------------------
                //Raster suchen:
                //2 paarige Bohrungen suchen:
                for(uint i=1; i<=potlora.zeilenanzahl() ;i++)
                {
                    b.set_text(potlora.zeile(i));
                    merkdirmal = potlora.zeile(i);
                    pvor.set_x(b.x());
                    pvor.set_y(b.y() - rasterabst);
                    pvor.set_z(b.z());
                    pnach.set_x(b.x());
                    pnach.set_y(b.y() + rasterabst);
                    pnach.set_z(b.z());

                    for(uint ii=1; ii<=potlora.zeilenanzahl() ;ii++)
                    {
                        if(i==ii)
                        {
                            continue;
                        }
                        bohrung b2(potlora.zeile(ii));

                        if(pvor.z_QString() == b2.z_qstring()  &&  pvor.y_QString() == b2.y_qstring())
                        {
                            set_startbohrung(b2);
                            set_anz_y(anz_y() + 1);//anz der Bohrungen erhöhen
                            potlora.zeile_loeschen(ii);
                            break;
                        }else if(pnach.z_QString() == b2.z_qstring()  &&  pnach.y_QString() == b2.y_qstring())
                        {
                            set_startbohrung(b);
                            set_anz_y(anz_y() + 1);//anz der Bohrungen erhöhen
                            potlora.zeile_loeschen(ii);
                            break;
                        }
                    }
                    if(Anz_y > 1)
                    {
                        uint zeilennumer = 0;
                        for(uint i=1; i<=potlora.zeilenanzahl() ;i++)
                        {
                            if(merkdirmal == potlora.zeile(i))
                            {
                                zeilennumer = i;
                                break;
                            }
                        }
                        if(zeilennumer!=0)
                        {
                            potlora.zeile_loeschen(zeilennumer);
                        }
                        break;
                    }
                }
                //Restliche zugehörige Bohrungen suchen:
                if(Anz_y == 2)//wenn 2 paarige Bohrungen gefunden wurden
                {
                    uint anz_alt = 1;//anz_alt != anz_y  --> 1!=2
                    while(anz_alt != anz_y())
                    {
                        anz_alt = anz_y();

                        for(uint i=1; i<=potlora.zeilenanzahl() ;i++)
                        {
                            pvor.set_y(y() - rasterabst );
                            pnach.set_y(y() + (rasterabst * anz_y())  );

                            bohrung b2(potlora.zeile(i));

                            if(pvor.z_QString() == b2.z_qstring()  &&  pvor.y_QString() == b2.y_qstring())
                            {
                                set_y(y()-rasterabst);//erste Bohrung neu setzen
                                set_anz_y(anz_y() + 1);//anz der Bohrungen erhöhen
                                potlora.zeile_loeschen(i);
                                break;
                            }else if(pnach.z_QString() == b2.z_qstring()  &&  pnach.y_QString() == b2.y_qstring())
                            {
                                set_anz_y(anz_y() + 1);//anz der Bohrungen erhöhen
                                potlora.zeile_loeschen(i);
                                break;
                            }
                        }
                    }


                }

                //----------------------------------------------------------------------
                //Daten zurück speichern / Einzelbohrungen durch Raster ersetzen:
                set_raster_y(rasterabst);
                if(Anz_y >= mindanz)
                {
                    //erste Bohrung des Rasters in bearb finden und durch Bohrraster ersetzen (Damit Reihenfolge der Bearbeitungen stimmt):
                    for(uint i=0; i<bearb->count();i++)
                    {
                        zeile.set_text(bearb->at(i), TRENNZ_BEARB_PARAM);
                        if(zeile.at(0) == BEARBART_BOHR)
                        {
                            bohrung b(zeile.text());
                            if(b.z_qstring() == z_qstring()  &&\
                               b.y_qstring() == y_qstring()  &&\
                               b.dm_qstring() == dm_qstring()  &&\
                               b.tiefe_qstring() == tiefe_qstring() &&\
                               b.bezug() == bezug())
                            {
                                bearb->edit(i, text());
                            }
                        }
                    }
                    //Restliche Bohrungen des Rasters finden und löschen
                    for(uint i = 1; i<Anz_y ;i++)
                    {
                        for(uint ii=0; ii<bearb->count() ;ii++)
                        {
                            zeile.set_text(bearb->at(ii), TRENNZ_BEARB_PARAM);
                            if(zeile.at(0) == BEARBART_BOHR)
                            {
                                bohrung beinzeln(zeile.text());
                                bohrung bausraster(text_erste_bohrung());
                                bausraster.set_y(y()+i*rasterabst);
                                if(beinzeln.x_qstring() == bausraster.x_qstring() &&\
                                   beinzeln.y_qstring() == bausraster.y_qstring() &&\
                                   beinzeln.dm_qstring() == bausraster.dm_qstring() &&\
                                   beinzeln.tiefe_qstring() == bausraster.tiefe_qstring() &&\
                                   beinzeln.bezug() == bausraster.bezug()            )
                                {
                                    bearb->entf(ii);
                                    break;
                                }
                            }
                        }
                    }
                    return true;
                }else
                {
                    return false;
                }
            }
        }
    }else if(rasterrichtung == RASTERRICHTUNG_0_BIS_D)
    {
        return false;//Dieser Filter wird vorerst noch nicht gebraucht, desshalb nur return
    }else
    {
        return false;
    }


    return false;//wird nie erreicht
}















