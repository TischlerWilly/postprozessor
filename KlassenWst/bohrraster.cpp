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
    raster_x = 0;
    raster_y = 0;
    raster_z = 0;
    werkzeugnummer = "";
}
void bohrraster::clear()
{
    setup();
}

void bohrraster::set_startbohrung(bohrung b)
{
    clear();
    set_dm(b.get_dm());
    set_tiefe(b.get_tiefe());
    set_bezug(b.get_bezug());
    set_afb(b.get_afb());
    set_zustellmass(b.get_zustellmass());
    set_x(b.get_x());
    set_y(b.get_y());
    set_z(b.get_z());
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

bool bohrraster::finde_bohrraster(text_zeilenweise *bearb, \
                                  QString bezug, double dm, \
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
        if(potlora.zeilenanzahl() >= 2)
        {
            if(bezug == WST_BEZUG_OBSEI || bezug == WST_BEZUG_UNSEI)
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
                    pvor.set_x(b.get_x() - rasterabst);
                    pvor.set_y(b.get_y());
                    pvor.set_z(b.get_z());
                    pnach.set_x(b.get_x() + rasterabst);
                    pnach.set_y(b.get_y());
                    pnach.set_z(b.get_z());

                    for(uint ii=1; ii<=potlora.zeilenanzahl() ;ii++)
                    {
                        if(i==ii)
                        {
                            continue;
                        }
                        bohrung b2(potlora.zeile(ii));

                        if(pvor.x_QString() == b2.get_x_qstring()  &&  pvor.y_QString() == b2.get_y_qstring())
                        {
                            set_startbohrung(b2);
                            set_anz_x(get_anz_x() + 1);//anz der Bohrungen erhöhen
                            potlora.zeile_loeschen(ii);
                            break;
                        }else if(pnach.x_QString() == b2.get_x_qstring()  &&  pnach.y_QString() == b2.get_y_qstring())
                        {
                            set_startbohrung(b);
                            set_anz_x(get_anz_x() + 1);//anz der Bohrungen erhöhen
                            potlora.zeile_loeschen(ii);
                            break;
                        }
                    }
                    if(anz_x > 1)
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
                if(anz_x == 2)//wenn 2 paarige Bohrungen gefunden wurden
                {
                    uint anz_alt = 1;//anz_alt != anz_x  --> 1!=2
                    while(anz_alt != get_anz_x())
                    {
                        anz_alt = get_anz_x();

                        for(uint i=1; i<=potlora.zeilenanzahl() ;i++)
                        {
                            pvor.set_x(get_x() - rasterabst );
                            pnach.set_x(get_x() + (rasterabst * get_anz_x())  );

                            bohrung b2(potlora.zeile(i));

                            if(pvor.x_QString() == b2.get_x_qstring()  &&  pvor.y_QString() == b2.get_y_qstring())
                            {
                                set_x(get_x()-rasterabst);//erste Bohrung neu setzen
                                set_anz_x(get_anz_x() + 1);//anz der Bohrungen erhöhen
                                potlora.zeile_loeschen(i);
                                break;
                            }else if(pnach.x_QString() == b2.get_x_qstring()  &&  pnach.y_QString() == b2.get_y_qstring())
                            {
                                set_anz_x(get_anz_x() + 1);//anz der Bohrungen erhöhen
                                potlora.zeile_loeschen(i);
                                break;
                            }
                        }
                    }
                }

                //----------------------------------------------------------------------
                //Daten zurück speichern / Einzelbohrungen durch Raster ersetzen:
                set_raster_x(rasterabst);
                if(anz_x >= mindanz)
                {
                    //erste Bohrung des Rasters in bearb finden und durch Bohrraster ersetzen (Damit Reihenfolge der Bearbeitungen stimmt):
                    for(uint i=1; i<=bearb->zeilenanzahl();i++)
                    {
                        zeile.set_text(bearb->zeile(i));
                        if(zeile.zeile(1) == BEARBART_BOHR)
                        {
                            bohrung b(zeile.get_text());
                            if(b.get_x_qstring() == get_x_qstring()  &&\
                               b.get_y_qstring() == get_y_qstring()  &&\
                               b.get_dm_qstring() == get_dm_qstring()  &&\
                               b.get_tiefe_qstring() == get_tiefe_qstring() &&\
                               b.get_bezug() == get_bezug())
                            {
                                bearb->zeile_ersaetzen(i, get_text());
                            }
                        }
                    }
                    //Restliche Bohrungen des Rasters finden und löschen
                    for(uint i = 1; i<anz_x ;i++)
                    {
                        for(uint ii=1; ii<=bearb->zeilenanzahl() ;ii++)
                        {
                            zeile.set_text(bearb->zeile(ii));
                            if(zeile.zeile(1) == BEARBART_BOHR)
                            {
                                bohrung beinzeln(zeile.get_text());
                                bohrung bausraster(zeile.get_text());
                                bausraster.set_bezug(bezug);
                                bausraster.set_x(get_x()+i*rasterabst);
                                if(beinzeln.get_text() == bausraster.get_text())
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
            }else if(bezug == WST_BEZUG_VO || bezug == WST_BEZUG_HI)
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
                    pvor.set_x(b.get_x() - rasterabst);
                    pvor.set_y(b.get_y());
                    pvor.set_z(b.get_z());
                    pnach.set_x(b.get_x() + rasterabst);
                    pnach.set_y(b.get_y());
                    pnach.set_z(b.get_z());

                    for(uint ii=1; ii<=potlora.zeilenanzahl() ;ii++)
                    {
                        if(i==ii)
                        {
                            continue;
                        }
                        bohrung b2(potlora.zeile(ii));

                        if(pvor.x_QString() == b2.get_x_qstring()  &&  pvor.z_QString() == b2.get_z_qstring())
                        {
                            set_startbohrung(b2);
                            set_anz_x(get_anz_x() + 1);//anz der Bohrungen erhöhen
                            potlora.zeile_loeschen(ii);
                            break;
                        }else if(pnach.x_QString() == b2.get_x_qstring()  &&  pnach.z_QString() == b2.get_z_qstring())
                        {
                            set_startbohrung(b);
                            set_anz_x(get_anz_x() + 1);//anz der Bohrungen erhöhen
                            potlora.zeile_loeschen(ii);
                            break;
                        }
                    }
                    if(anz_x > 1)
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
                if(anz_x == 2)//wenn 2 paarige Bohrungen gefunden wurden
                {
                    uint anz_alt = 1;//anz_alt != anz_x  --> 1!=2
                    while(anz_alt != get_anz_x())
                    {
                        anz_alt = get_anz_x();

                        for(uint i=1; i<=potlora.zeilenanzahl() ;i++)
                        {
                            pvor.set_x(get_x() - rasterabst );
                            pnach.set_x(get_x() + (rasterabst * get_anz_x())  );

                            bohrung b2(potlora.zeile(i));

                            if(pvor.x_QString() == b2.get_x_qstring()  &&  pvor.z_QString() == b2.get_z_qstring())
                            {
                                set_x(get_x()-rasterabst);//erste Bohrung neu setzen
                                set_anz_x(get_anz_x() + 1);//anz der Bohrungen erhöhen
                                potlora.zeile_loeschen(i);
                                break;
                            }else if(pnach.x_QString() == b2.get_x_qstring()  &&  pnach.z_QString() == b2.get_z_qstring())
                            {
                                set_anz_x(get_anz_x() + 1);//anz der Bohrungen erhöhen
                                potlora.zeile_loeschen(i);
                                break;
                            }
                        }
                    }
                }

                //----------------------------------------------------------------------
                //Daten zurück speichern / Einzelbohrungen durch Raster ersetzen:
                set_raster_x(rasterabst);
                if(anz_x >= mindanz)
                {
                    //erste Bohrung des Rasters in bearb finden und durch Bohrraster ersetzen (Damit Reihenfolge der Bearbeitungen stimmt):
                    for(uint i=1; i<=bearb->zeilenanzahl();i++)
                    {
                        zeile.set_text(bearb->zeile(i));
                        if(zeile.zeile(1) == BEARBART_BOHR)
                        {
                            bohrung b(zeile.get_text());
                            if(b.get_x_qstring() == get_x_qstring()  &&\
                               b.get_z_qstring() == get_z_qstring()  &&\
                               b.get_dm_qstring() == get_dm_qstring()  &&\
                               b.get_tiefe_qstring() == get_tiefe_qstring() &&\
                               b.get_bezug() == get_bezug())
                            {
                                bearb->zeile_ersaetzen(i, get_text());
                            }
                        }
                    }
                    //Restliche Bohrungen des Rasters finden und löschen
                    for(uint i = 1; i<anz_x ;i++)
                    {
                        for(uint ii=1; ii<=bearb->zeilenanzahl() ;ii++)
                        {
                            zeile.set_text(bearb->zeile(ii));
                            if(zeile.zeile(1) == BEARBART_BOHR)
                            {
                                bohrung beinzeln(zeile.get_text());
                                bohrung bausraster(zeile.get_text());
                                bausraster.set_bezug(bezug);
                                bausraster.set_x(get_x()+i*rasterabst);
                                if(beinzeln.get_text() == bausraster.get_text())
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
            if(bezug == WST_BEZUG_OBSEI || bezug == WST_BEZUG_UNSEI)
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
                    pvor.set_x(b.get_x());
                    pvor.set_y(b.get_y() - rasterabst);
                    pvor.set_z(b.get_z());
                    pnach.set_x(b.get_x());
                    pnach.set_y(b.get_y() + rasterabst);
                    pnach.set_z(b.get_z());

                    for(uint ii=1; ii<=potlora.zeilenanzahl() ;ii++)
                    {
                        if(i==ii)
                        {
                            continue;
                        }
                        bohrung b2(potlora.zeile(ii));

                        if(pvor.x_QString() == b2.get_x_qstring()  &&  pvor.y_QString() == b2.get_y_qstring())
                        {
                            set_startbohrung(b2);
                            set_anz_y(get_anz_y() + 1);//anz der Bohrungen erhöhen
                            potlora.zeile_loeschen(ii);
                            break;
                        }else if(pnach.x_QString() == b2.get_x_qstring()  &&  pnach.y_QString() == b2.get_y_qstring())
                        {
                            set_startbohrung(b);
                            set_anz_y(get_anz_y() + 1);//anz der Bohrungen erhöhen
                            potlora.zeile_loeschen(ii);
                            break;
                        }
                    }
                    if(anz_y > 1)
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
                if(anz_y == 2)//wenn 2 paarige Bohrungen gefunden wurden
                {
                    uint anz_alt = 1;//anz_alt != anz_y  --> 1!=2
                    while(anz_alt != get_anz_y())
                    {
                        anz_alt = get_anz_y();

                        for(uint i=1; i<=potlora.zeilenanzahl() ;i++)
                        {
                            pvor.set_y(get_y() - rasterabst );
                            pnach.set_y(get_y() + (rasterabst * get_anz_y())  );

                            bohrung b2(potlora.zeile(i));

                            if(pvor.x_QString() == b2.get_x_qstring()  &&  pvor.y_QString() == b2.get_y_qstring())
                            {
                                set_y(get_y()-rasterabst);//erste Bohrung neu setzen
                                set_anz_y(get_anz_y() + 1);//anz der Bohrungen erhöhen
                                potlora.zeile_loeschen(i);
                                break;
                            }else if(pnach.x_QString() == b2.get_x_qstring()  &&  pnach.y_QString() == b2.get_y_qstring())
                            {
                                set_anz_y(get_anz_y() + 1);//anz der Bohrungen erhöhen
                                potlora.zeile_loeschen(i);
                                break;
                            }
                        }
                    }


                }

                //----------------------------------------------------------------------
                //Daten zurück speichern / Einzelbohrungen durch Raster ersetzen:
                set_raster_y(rasterabst);
                if(anz_y >= mindanz)
                {
                    //erste Bohrung des Rasters in bearb finden und durch Bohrraster ersetzen (Damit Reihenfolge der Bearbeitungen stimmt):
                    for(uint i=1; i<=bearb->zeilenanzahl();i++)
                    {
                        zeile.set_text(bearb->zeile(i));
                        if(zeile.zeile(1) == BEARBART_BOHR)
                        {
                            bohrung b(zeile.get_text());
                            if(b.get_x_qstring() == get_x_qstring()  &&\
                               b.get_y_qstring() == get_y_qstring()  &&\
                               b.get_dm_qstring() == get_dm_qstring()  &&\
                               b.get_tiefe_qstring() == get_tiefe_qstring() &&\
                               b.get_bezug() == get_bezug())
                            {
                                bearb->zeile_ersaetzen(i, get_text());
                            }
                        }
                    }
                    //Restliche Bohrungen des Rasters finden und löschen
                    for(uint i = 1; i<anz_y ;i++)
                    {
                        for(uint ii=1; ii<=bearb->zeilenanzahl() ;ii++)
                        {
                            zeile.set_text(bearb->zeile(ii));
                            if(zeile.zeile(1) == BEARBART_BOHR)
                            {
                                bohrung beinzeln(zeile.get_text());
                                bohrung bausraster(zeile.get_text());
                                bausraster.set_bezug(bezug);
                                bausraster.set_y(get_y()+i*rasterabst);
                                if(beinzeln.get_text() == bausraster.get_text())
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
            }else if(bezug == WST_BEZUG_LI || bezug == WST_BEZUG_RE)
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
                    pvor.set_x(b.get_x());
                    pvor.set_y(b.get_y() - rasterabst);
                    pvor.set_z(b.get_z());
                    pnach.set_x(b.get_x());
                    pnach.set_y(b.get_y() + rasterabst);
                    pnach.set_z(b.get_z());

                    for(uint ii=1; ii<=potlora.zeilenanzahl() ;ii++)
                    {
                        if(i==ii)
                        {
                            continue;
                        }
                        bohrung b2(potlora.zeile(ii));

                        if(pvor.z_QString() == b2.get_z_qstring()  &&  pvor.y_QString() == b2.get_y_qstring())
                        {
                            set_startbohrung(b2);
                            set_anz_y(get_anz_y() + 1);//anz der Bohrungen erhöhen
                            potlora.zeile_loeschen(ii);
                            break;
                        }else if(pnach.z_QString() == b2.get_z_qstring()  &&  pnach.y_QString() == b2.get_y_qstring())
                        {
                            set_startbohrung(b);
                            set_anz_y(get_anz_y() + 1);//anz der Bohrungen erhöhen
                            potlora.zeile_loeschen(ii);
                            break;
                        }
                    }
                    if(anz_y > 1)
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
                if(anz_y == 2)//wenn 2 paarige Bohrungen gefunden wurden
                {
                    uint anz_alt = 1;//anz_alt != anz_y  --> 1!=2
                    while(anz_alt != get_anz_y())
                    {
                        anz_alt = get_anz_y();

                        for(uint i=1; i<=potlora.zeilenanzahl() ;i++)
                        {
                            pvor.set_y(get_y() - rasterabst );
                            pnach.set_y(get_y() + (rasterabst * get_anz_y())  );

                            bohrung b2(potlora.zeile(i));

                            if(pvor.z_QString() == b2.get_z_qstring()  &&  pvor.y_QString() == b2.get_y_qstring())
                            {
                                set_y(get_y()-rasterabst);//erste Bohrung neu setzen
                                set_anz_y(get_anz_y() + 1);//anz der Bohrungen erhöhen
                                potlora.zeile_loeschen(i);
                                break;
                            }else if(pnach.z_QString() == b2.get_z_qstring()  &&  pnach.y_QString() == b2.get_y_qstring())
                            {
                                set_anz_y(get_anz_y() + 1);//anz der Bohrungen erhöhen
                                potlora.zeile_loeschen(i);
                                break;
                            }
                        }
                    }


                }

                //----------------------------------------------------------------------
                //Daten zurück speichern / Einzelbohrungen durch Raster ersetzen:
                set_raster_y(rasterabst);
                if(anz_y >= mindanz)
                {
                    //erste Bohrung des Rasters in bearb finden und durch Bohrraster ersetzen (Damit Reihenfolge der Bearbeitungen stimmt):
                    for(uint i=1; i<=bearb->zeilenanzahl();i++)
                    {
                        zeile.set_text(bearb->zeile(i));
                        if(zeile.zeile(1) == BEARBART_BOHR)
                        {
                            bohrung b(zeile.get_text());
                            if(b.get_z_qstring() == get_z_qstring()  &&\
                               b.get_y_qstring() == get_y_qstring()  &&\
                               b.get_dm_qstring() == get_dm_qstring()  &&\
                               b.get_tiefe_qstring() == get_tiefe_qstring() &&\
                               b.get_bezug() == get_bezug())
                            {
                                bearb->zeile_ersaetzen(i, get_text());
                            }
                        }
                    }
                    //Restliche Bohrungen des Rasters finden und löschen
                    for(uint i = 1; i<anz_y ;i++)
                    {
                        for(uint ii=1; ii<=bearb->zeilenanzahl() ;ii++)
                        {
                            zeile.set_text(bearb->zeile(ii));
                            if(zeile.zeile(1) == BEARBART_BOHR)
                            {
                                bohrung beinzeln(zeile.get_text());
                                bohrung bausraster(zeile.get_text());
                                bausraster.set_bezug(bezug);
                                bausraster.set_y(get_y()+i*rasterabst);
                                if(beinzeln.get_text() == bausraster.get_text())
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















