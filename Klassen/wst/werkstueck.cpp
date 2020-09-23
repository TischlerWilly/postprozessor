#include "werkstueck.h"

werkstueck::werkstueck()
{
    Laenge  = 0;
    Breite  = 0;
    Dicke   = 0;
    Schwellenwert_ay = 230;
}
werkstueck::werkstueck(QString neuer_name)
{
    Name    = neuer_name;
    Laenge  = 0;
    Breite  = 0;
    Dicke   = 0;
    Schwellenwert_ay = 230;
}
//#######################################################################
//Public:
//#######################################################################
//--------------------------------------------------set_xy:
void werkstueck::set_laenge(double l)
{
    if(l>0 && l<5000)
    {
        Laenge = l;
    }
}
void werkstueck::set_laenge(QString l)
{
    set_laenge(l.toDouble());
}
void werkstueck::set_breite(double b)
{
    if(b>0 && b<5000)
    {
        Breite = b;
    }
}
void werkstueck::set_breite(QString b)
{
    set_breite(b.toDouble());
}
void werkstueck::set_dicke(double d)
{
    if(d>0 && d<200)
    {
        Dicke = d;
    }
}
void werkstueck::set_dicke(QString d)
{
    set_dicke(d.toDouble());
}
void werkstueck::neue_bearbeitung(QString text)
{
    bool bereits_vorhanden = false;

    for(uint i=0; i<=Bearbeitungen.zeilenanzahl() ;i++)
    {
        if(Bearbeitungen.zeile(i) == text)
        {
            text_zeilenweise zeile;//Folgezeile
            zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
            zeile.set_text(text);
            if(zeile.zeile(1) == BEARBART_BOHR)//Nur doppelte Bohrungen unterdrücken, Doppelte Fräsbahnen können gewollt sein!
            {
                bereits_vorhanden = true;
                break;
            }
        }
    }

    if(bereits_vorhanden == false)
    {
        Bearbeitungen.zeilen_anhaengen(text);
    }
}
void werkstueck::set_kante_vo(QString artiklenummer)
{
    Kante_vo = artiklenummer;
}
void werkstueck::set_kante_hi(QString artiklenummer)
{
    Kante_hi = artiklenummer;
}
void werkstueck::set_kante_li(QString artiklenummer)
{
    Kante_li = artiklenummer;
}
void werkstueck::set_kante_re(QString artiklenummer)
{
    Kante_re = artiklenummer;
}
void werkstueck::set_zugabe_gehrungen(double wert)
{
    Zugabe_gehrungen = wert;
}

//--------------------------------------------------get_xy:
QString werkstueck::kante_vo(QString drewi)
{
    if(drewi == "90")
    {
        return Kante_re;
    }else if(drewi == "180")
    {
        return Kante_hi;
    }else if(drewi == "270")
    {
        return Kante_li;
    }else
    {
        return Kante_vo;
    }
}
QString werkstueck::kante_hi(QString drewi)
{
    if(drewi == "90")
    {
        return Kante_li;
    }else if(drewi == "180")
    {
        return Kante_vo;
    }else if(drewi == "270")
    {
        return Kante_re;
    }else
    {
        return Kante_hi;
    }
}
QString werkstueck::kante_li(QString drewi)
{
    if(drewi == "90")
    {
        return Kante_vo;
    }else if(drewi == "180")
    {
        return Kante_re;
    }else if(drewi == "270")
    {
        return Kante_hi;
    }else
    {
        return Kante_li;
    }
}
QString werkstueck::kante_re(QString drewi)
{
    if(drewi == "90")
    {
        return Kante_hi;
    }else if(drewi == "180")
    {
        return Kante_li;
    }else if(drewi == "270")
    {
        return Kante_vo;
    }else
    {
        return Kante_re;
    }
}
QString werkstueck::kante_vo_ganx(QString drewi)
{
    if(drewi == "90")
    {
        return Kante_hi;
    }else if(drewi == "180")
    {
        return Kante_li;
    }else if(drewi == "270")
    {
        return Kante_vo;
    }else
    {
        return Kante_re;
    }
}
QString werkstueck::kante_hi_ganx(QString drewi)
{
    if(drewi == "90")
    {
        return Kante_vo;
    }else if(drewi == "180")
    {
        return Kante_re;
    }else if(drewi == "270")
    {
        return Kante_hi;
    }else
    {
        return Kante_li;
    }
}
QString werkstueck::kante_li_ganx(QString drewi)
{
    if(drewi == "90")
    {
        return Kante_re;
    }else if(drewi == "180")
    {
        return Kante_hi;
    }else if(drewi == "270")
    {
        return Kante_li;
    }else
    {
        return Kante_vo;
    }
}
QString werkstueck::kante_re_ganx(QString drewi)
{
    if(drewi == "90")
    {
        return Kante_li;
    }else if(drewi == "180")
    {
        return Kante_vo;
    }else if(drewi == "270")
    {
        return Kante_re;
    }else
    {
        return Kante_hi;
    }
}
QString werkstueck::cad_fehler()
{
    QString msg;

    if(Name.contains("Tuer") || \
       Name.contains("Tur")      )
    {
        uint anz_asd = 0; //Anzahl Aufschlagdämpfer

        for(uint i=1; i<=Bearbeitungen.zeilenanzahl() ;i++)
        {
            if(Bearbeitungen.zeile(i).contains(BEARBART_BOHR))
            {
                bohrung bo(Bearbeitungen.zeile(i));
                if(bo.dm() == 6 && bo.tiefe() < dicke())
                {
                    anz_asd++;
                }
            }
        }
        if(anz_asd < 2)
        {
            msg += name();
            msg += ": ";
            msg += double_to_qstring(anz_asd);
            msg += " Aufschlagdaempfer";
            msg += "\n";
        }
    }
    if(Name.contains("SchubFront") || \
       Name.contains("Schubfront")      )
    {
        uint anz_asd = 0; //Anzahl Aufschlagdämpfer

        for(uint i=1; i<=Bearbeitungen.zeilenanzahl() ;i++)
        {
            if(Bearbeitungen.zeile(i).contains(BEARBART_BOHR))
            {
                bohrung bo(Bearbeitungen.zeile(i));
                if(bo.dm() == 6 && bo.tiefe() < dicke())
                {
                    anz_asd++;
                }
            }
        }
        if(anz_asd < 4)
        {
            msg += name();
            msg += ": ";
            msg += double_to_qstring(anz_asd);
            msg += " Aufschlagdaempfer";
            msg += "\n";
        }
    }


    return msg;
}
QString werkstueck::fmc(text_zeilenweise wkzmagazin, QString& info , QString drehwinkel, QString zust_fkon,\
                            bool formartierungen_aufbrechen, bool fkon_kantenschonend)
{
//#define ISDEBUG

#ifdef ISDEBUG
    bool isdebugmodus_0     = false;
    bool isdebugmodus_90    = false;
    bool isdebugmodus_180   = false;
    bool isdebugmodus_270   = false;

    if(drehwinkel == "0")
    {
        isdebugmodus_0 = true;
    }else if(drehwinkel == "90")
    {
        isdebugmodus_90 = true;
    }else if(drehwinkel == "180")
    {
        isdebugmodus_180 = true;
    }else if(drehwinkel == "270")
    {
        isdebugmodus_270 = true;
    }
#endif //ISDEBUG

    QString msg;
    bearb_sortieren();
    fraesergeraden_zusammenfassen();
    hbemiduebeltiefe();

    double tmp_l = Laenge;
    double tmp_b = Breite;
    text_zeilenweise tmp_bearb = Bearbeitungen;
    tmp_bearb = gehr_3achs(tmp_bearb, tmp_l, tmp_b, "fmc");

    //Die beste Drehrichtung herausfinden:
    int bewertung_0    = 1;
    int bewertung_90   = 1;
    int bewertung_180  = 1;
    int bewertung_270  = 1;
    //Stufe 1:
    //heraus bekommen, für welche Lage es Warnungen gibt:
    QString warnung;
    text_zeilenweise bearb_kopie = tmp_bearb;
    double l_kopie = tmp_l;
    double b_kopie = tmp_b;
    //------------------------0:
    warnung = warnungen_fmc(bearb_kopie, l_kopie, b_kopie, wkzmagazin);
    if(warnung.isEmpty())
    {
        bewertung_0 = 100;
    }else
    {
        bewertung_0 = 0;
    }
    text_zeilenweise bearb_0 = bearb_kopie;
    double l_0 = l_kopie;
    double b_0 = b_kopie;
    //------------------------90:
    bearb_kopie = bearb_drehen_90(bearb_kopie, l_kopie, b_kopie);
    warnung = warnungen_fmc(bearb_kopie, l_kopie, b_kopie, wkzmagazin);
    if(warnung.isEmpty())
    {
        bewertung_90 = 100;
    }else
    {
        bewertung_90 = 0;
    }
    text_zeilenweise bearb_90 = bearb_kopie;
    double l_90 = l_kopie;
    double b_90 = b_kopie;
    //------------------------180:
    bearb_kopie = bearb_drehen_90(bearb_kopie, l_kopie, b_kopie);
    warnung = warnungen_fmc(bearb_kopie, l_kopie, b_kopie, wkzmagazin);
    if(warnung.isEmpty())
    {
        bewertung_180 = 100;
    }else
    {
        bewertung_180 = 0;
    }
    text_zeilenweise bearb_180 = bearb_kopie;
    double l_180 = l_kopie;
    double b_180 = b_kopie;
    //------------------------270:
    bearb_kopie = bearb_drehen_90(bearb_kopie, l_kopie, b_kopie);
    warnung = warnungen_fmc(bearb_kopie, l_kopie, b_kopie, wkzmagazin);
    if(warnung.isEmpty())
    {
        bewertung_270 = 100;
    }else
    {
        bewertung_270 = 0;
    }
    text_zeilenweise bearb_270 = bearb_kopie;
    double l_270 = l_kopie;
    double b_270 = b_kopie;

    //Stufe 2:
    //heraus bekommen wo vorne ist anhand von Bearbeitungen:
    for(uint i=1; i<=bearb_0.zeilenanzahl() ;i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(bearb_0.zeile(i));
        if(zeile.zeile(1) == BEARBART_BOHR)
        {
            bohrung bo(zeile.text());
            if(bo.dm() == 8 || \
               bo.dm() == 8.2)
            {
                if(bo.x() == 20)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                {
                    bewertung_0 += 2;
#ifdef ISDEBUG
                    if(isdebugmodus_0 == true)
                    {
                        QMessageBox mb;
                        mb.setText("Punkte fuer Bohrun DM8 X=20");
                        mb.exec();
                    }
#endif
                }
                if(bo.y() == 20)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                {
                    bewertung_0 += 2;
#ifdef ISDEBUG
                    if(isdebugmodus_0 == true)
                    {
                        QMessageBox mb;
                        mb.setText("Punkte fuer Bohrun DM8 Y=20");
                        mb.exec();
                    }
#endif
                }
            }else if(bo.dm() == 35.3)//Töpfe/Topfbänder am Anschlag anlegen
            {
                if(bo.x() < 30)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                {
                    bewertung_0 += 5;
#ifdef ISDEBUG
                    if(isdebugmodus_0 == true)
                    {
                        QMessageBox mb;
                        mb.setText("Punkte fuer Bohrun DM35.3 X<30");
                        mb.exec();
                    }
#endif
                }
                if(bo.y() < 30)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                {
                    bewertung_0 += 5;
#ifdef ISDEBUG
                    if(isdebugmodus_0 == true)
                    {
                        QMessageBox mb;
                        mb.setText("Punkte fuer Bohrun DM35.3 Y<30");
                        mb.exec();
                    }
#endif
                }

            }
        }
    }
    for(uint i=1; i<=bearb_90.zeilenanzahl() ;i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(bearb_90.zeile(i));
        if(zeile.zeile(1) == BEARBART_BOHR)
        {
            bohrung bo(zeile.text());
            if(bo.dm() == 8 || \
               bo.dm() == 8.2)
            {
                if(bo.x() == 20)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                {
                    bewertung_90 += 2;
#ifdef ISDEBUG
                    if(isdebugmodus_90 == true)
                    {
                        QMessageBox mb;
                        mb.setText("Punkte fuer Bohrun DM8 X=20");
                        mb.exec();
                    }
#endif
                }
                if(bo.y() == 20)//Gilt für HBE, Löcher mit diesem Abst. in der Fläche sind nicht zu erwarten
                {
                    bewertung_90 += 2;
#ifdef ISDEBUG
                    if(isdebugmodus_90 == true)
                    {
                        QMessageBox mb;
                        mb.setText("Punkte fuer Bohrun DM8 Y=20");
                        mb.exec();
                    }
#endif
                }
            }else if(bo.dm() == 35.3)//Töpfe/Topfbänder am Anschlag anlegen
            {
                if(bo.x() < 30)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                {
                    bewertung_90 += 5;
#ifdef ISDEBUG
                    if(isdebugmodus_90 == true)
                    {
                        QMessageBox mb;
                        mb.setText("Punkte fuer Bohrun DM35.3 X<30");
                        mb.exec();
                    }
#endif
                }
                if(bo.y() < 30)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                {
                    bewertung_90 += 5;
#ifdef ISDEBUG
                    if(isdebugmodus_90 == true)
                    {
                        QMessageBox mb;
                        mb.setText("Punkte fuer Bohrun DM35.3 Y<30");
                        mb.exec();
                    }
#endif
                }
            }
        }
    }
    for(uint i=1; i<=bearb_180.zeilenanzahl() ;i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(bearb_180.zeile(i));
        if(zeile.zeile(1) == BEARBART_BOHR)
        {
           bohrung bo(zeile.text());
            if(bo.dm() == 8 || \
               bo.dm() == 8.2)
            {
                if(bo.x() == 20)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                {
                    bewertung_180 += 2;
#ifdef ISDEBUG
                    if(isdebugmodus_180 == true)
                    {
                        QMessageBox mb;
                        mb.setText("Punkte fuer Bohrun DM8 X=20");
                        mb.exec();
                    }
#endif
                }
                if(bo.y() == 20)//Gilt für HBE, Löcher mit diesem Abst. in der Fläche sind nicht zu erwarten
                {
                    bewertung_180 += 2;
#ifdef ISDEBUG
                    if(isdebugmodus_180 == true)
                    {
                        QMessageBox mb;
                        mb.setText("Punkte fuer Bohrun DM8 Y=20");
                        mb.exec();
                    }
#endif
                }
            }else if(bo.dm() == 35.3)//Töpfe/Topfbänder am Anschlag anlegen
            {
                if(bo.x() < 30)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                {
                    bewertung_180 += 5;
#ifdef ISDEBUG
                    if(isdebugmodus_180 == true)
                    {
                        QMessageBox mb;
                        mb.setText("Punkte fuer Bohrun DM35.3 X<30");
                        mb.exec();
                    }
#endif
                }
                if(bo.y() < 30)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                {
                    bewertung_180 += 5;
#ifdef ISDEBUG
                    if(isdebugmodus_180 == true)
                    {
                        QMessageBox mb;
                        mb.setText("Punkte fuer Bohrun DM35.3 Y<30");
                        mb.exec();
                    }
#endif
                }

            }
        }
    }
    for(uint i=1; i<=bearb_270.zeilenanzahl() ;i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(bearb_270.zeile(i));
        if(zeile.zeile(1) == BEARBART_BOHR)
        {
            bohrung bo(zeile.text());
            if(bo.dm() == 8 || \
               bo.dm() == 8.2)
            {
                if(bo.x() == 20)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                {
                    bewertung_270 += 2;
#ifdef ISDEBUG
                    if(isdebugmodus_270 == true)
                    {
                        QMessageBox mb;
                        mb.setText("Punkte fuer Bohrun DM8 X=20");
                        mb.exec();
                    }
#endif
                }
                if(bo.y() == 20)//Gilt für HBE, Löcher mit diesem Abst. in der Fläche sind nicht zu erwarten
                {
                    bewertung_270 += 2;
#ifdef ISDEBUG
                    if(isdebugmodus_270 == true)
                    {
                        QMessageBox mb;
                        mb.setText("Punkte fuer Bohrun DM8 Y=20");
                        mb.exec();
                    }
#endif
                }
            }else if(bo.dm() == 35.3)//Töpfe/Topfbänder am Anschlag anlegen
            {
                if(bo.x() < 30)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                {
                    bewertung_270 += 5;
#ifdef ISDEBUG
                    if(isdebugmodus_270 == true)
                    {
                        QMessageBox mb;
                        mb.setText("Punkte fuer Bohrun DM35.3 X<30");
                        mb.exec();
                    }
#endif
                }
                if(bo.y() < 30)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                {
                    bewertung_270 += 5;
#ifdef ISDEBUG
                    if(isdebugmodus_270 == true)
                    {
                        QMessageBox mb;
                        mb.setText("Punkte fuer Bohrun DM35.3 Y<30");
                        mb.exec();
                    }
#endif
                }
            }
        }
    }

    //Stufe 3:
    //heraus bekommen wo vorne ist anhand von Kanteninfo:
    if(!kante_vo("0").isEmpty() || !kante_li("0").isEmpty())
    {
        if(!kante_vo("0").isEmpty())
        {
            bewertung_0 += 15;
        }
        if(!kante_li("0").isEmpty())
        {
            bewertung_0 += 10;
        }
#ifdef ISDEBUG
        if(isdebugmodus_0 == true)
        {
            QMessageBox mb;
            mb.setText("Punkte fuer Kante an X oder Y");
            mb.exec();
        }
#endif
    }
    if(!kante_vo("90").isEmpty() || !kante_li("90").isEmpty())
    {
        if(!kante_vo("90").isEmpty())
        {
            bewertung_90 += 15;
        }
        if(!kante_li("90").isEmpty())
        {
            bewertung_90 += 10;
        }
#ifdef ISDEBUG
        if(isdebugmodus_90 == true)
        {
            QMessageBox mb;
            mb.setText("Punkte fuer Kante an X oder Y");
            mb.exec();
        }
#endif
    }
    if(!kante_vo("180").isEmpty() || !kante_li("180").isEmpty())
    {
        if(!kante_vo("180").isEmpty())
        {
            bewertung_180 += 15;
        }
        if(!kante_li("180").isEmpty())
        {
            bewertung_180 += 10;
        }
#ifdef ISDEBUG
        if(isdebugmodus_180 == true)
        {
            QMessageBox mb;
            mb.setText("Punkte fuer Kante an X oder Y");
            mb.exec();
        }
#endif
    }
    if(!kante_vo("270").isEmpty() || !kante_li("270").isEmpty())
    {
        if(!kante_vo("270").isEmpty())
        {
            bewertung_270 += 15;
        }
        if(!kante_li("270").isEmpty())
        {
            bewertung_270 += 10;
        }
#ifdef ISDEBUG
        if(isdebugmodus_270 == true)
        {
            QMessageBox mb;
            mb.setText("Punkte fuer Kante an X oder Y");
            mb.exec();
        }
#endif
    }

    //Stufe 4:
    //Teile bevorzugen, bei bei denen gilt: L > B:
    if(l_0 > b_0)
    {
        bewertung_0 += 20;
#ifdef ISDEBUG
        if(isdebugmodus_0 == true)
        {
            QMessageBox mb;
            mb.setText("Punkte fuer Kante L > B");
            mb.exec();
        }
#endif
    }
    if(l_90 > b_90)
    {
        bewertung_90 += 20;
#ifdef ISDEBUG
        if(isdebugmodus_90 == true)
        {
            QMessageBox mb;
            mb.setText("Punkte fuer Kante L > B");
            mb.exec();
        }
#endif
    }
    if(l_180 > b_180)
    {
        bewertung_180 += 20;
#ifdef ISDEBUG
        if(isdebugmodus_180 == true)
        {
            QMessageBox mb;
            mb.setText("Punkte fuer Kante L > B");
            mb.exec();
        }
#endif
    }
    if(l_270 > b_270)
    {
       bewertung_270 += 20;
#ifdef ISDEBUG
       if(isdebugmodus_270 == true)
       {
           QMessageBox mb;
           mb.setText("Punkte fuer Kante L > B");
           mb.exec();
       }
#endif
    }

    //Stufe 5:
    //Bei schmalen Teilen bevorzugen, wenn HBE nicht aus richtung des Anschlages kommt:
    if(b_0 <= Schwellenwert_ay)
    {
        bool bonus = true;
        for(uint i=1; i<=bearb_0.zeilenanzahl() ;i++)
        {
            text_zeilenweise zeile;
            zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
            zeile.set_text(bearb_0.zeile(i));
            if(zeile.zeile(1) == BEARBART_BOHR)
            {
                bohrung bo(zeile.text());
                if(bo.bezug() == WST_BEZUG_VO)
                {
                    bonus = false;
                }
            }
        }
        if(bonus == true)
        {
            bewertung_0 += 20;
#ifdef ISDEBUG
            if(isdebugmodus_0 == true)
            {
                QMessageBox mb;
                mb.setText("Punkte fuer HBE nicht am Anschlag bei Schmalteil");
                mb.exec();
            }
#endif
        }else
        {
            bewertung_0 -= 10;
#ifdef ISDEBUG
            if(isdebugmodus_0 == true)
            {
                QMessageBox mb;
                mb.setText("Punkteabzug fuer HBE nicht am Anschlag bei Schmalteil");
                mb.exec();
            }
#endif
        }
    }
    if(b_90 <= Schwellenwert_ay)
    {
        bool bonus = true;
        for(uint i=1; i<=bearb_90.zeilenanzahl() ;i++)
        {
            text_zeilenweise zeile;
            zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
            zeile.set_text(bearb_90.zeile(i));
            if(zeile.zeile(1) == BEARBART_BOHR)
            {
                bohrung bo(zeile.text());
                if(bo.bezug() == WST_BEZUG_VO)
                {
                    bonus = false;
                }
            }
        }
        if(bonus == true)
        {
            bewertung_90 += 20;
#ifdef ISDEBUG
            if(isdebugmodus_90 == true)
            {
                QMessageBox mb;
                mb.setText("Punkte fuer HBE nicht am Anschlag bei Schmalteil");
                mb.exec();
            }
#endif
        }else
        {
            bewertung_90 -= 10;
#ifdef ISDEBUG
            if(isdebugmodus_90 == true)
            {
                QMessageBox mb;
                mb.setText("Punkteabzug fuer HBE nicht am Anschlag bei Schmalteil");
                mb.exec();
            }
#endif
        }
    }
    if(b_180 <= Schwellenwert_ay)
    {
        bool bonus = true;
        for(uint i=1; i<=bearb_180.zeilenanzahl() ;i++)
        {
            text_zeilenweise zeile;
            zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
            zeile.set_text(bearb_180.zeile(i));
            if(zeile.zeile(1) == BEARBART_BOHR)
            {
                bohrung bo(zeile.text());
                if(bo.bezug() == WST_BEZUG_VO)
                {
                    bonus = false;
                }
            }
        }
        if(bonus == true)
        {
            bewertung_180 += 20;
#ifdef ISDEBUG
            if(isdebugmodus_180 == true)
            {
                QMessageBox mb;
                mb.setText("Punkte fuer HBE nicht am Anschlag bei Schmalteil");
                mb.exec();
            }
#endif
        }else
        {
            bewertung_180 -= 10;
#ifdef ISDEBUG
            if(isdebugmodus_180 == true)
            {
                QMessageBox mb;
                mb.setText("Punkteabzug fuer HBE nicht am Anschlag bei Schmalteil");
                mb.exec();
            }
#endif
        }
    }
    if(b_270 <= Schwellenwert_ay)
    {
        bool bonus = true;
        for(uint i=1; i<=bearb_270.zeilenanzahl() ;i++)
        {
            text_zeilenweise zeile;
            zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
            zeile.set_text(bearb_270.zeile(i));
            if(zeile.zeile(1) == BEARBART_BOHR)
            {
                bohrung bo(zeile.text());
                if(bo.bezug() == WST_BEZUG_VO)
                {
                    bonus = false;
                }
            }
        }
        if(bonus == true)
        {
            bewertung_270 += 20;
#ifdef ISDEBUG
            if(isdebugmodus_270 == true)
            {
                QMessageBox mb;
                mb.setText("Punkte fuer HBE nicht am Anschlag bei Schmalteil");
                mb.exec();
            }
#endif
        }else
        {
            bewertung_270 -= 10;
#ifdef ISDEBUG
            if(isdebugmodus_270 == true)
            {
                QMessageBox mb;
                mb.setText("Punkteabzug fuer HBE nicht am Anschlag bei Schmalteil");
                mb.exec();
            }
#endif
        }
    }

    //Stufe 6:
    //Flächenbohrungen mit geringem Kantenabstand beforzugen
    for(uint i=1; i<=bearb_0.zeilenanzahl() ;i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(bearb_0.zeile(i));
        if(zeile.zeile(1) == BEARBART_BOHR)
        {
            bohrung bo(zeile.text());
            if(bo.x() < 20 || bo.y() < 20)
            {
                bewertung_0 += 1;
            }
        }
    }
    for(uint i=1; i<=bearb_90.zeilenanzahl() ;i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(bearb_90.zeile(i));
        if(zeile.zeile(1) == BEARBART_BOHR)
        {
            bohrung bo(zeile.text());
            if(bo.x() < 20 || bo.y() < 20)
            {
                bewertung_90 += 1;
            }
        }
    }
    for(uint i=1; i<=bearb_180.zeilenanzahl() ;i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(bearb_180.zeile(i));
        if(zeile.zeile(1) == BEARBART_BOHR)
        {
            bohrung bo(zeile.text());
            if(bo.x() < 20 || bo.y() < 20)
            {
                bewertung_180 += 1;
            }
        }
    }
    for(uint i=1; i<=bearb_270.zeilenanzahl() ;i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(bearb_270.zeile(i));
        if(zeile.zeile(1) == BEARBART_BOHR)
        {
            bohrung bo(zeile.text());
            if(bo.x() < 20 || bo.y() < 20)
            {
                bewertung_270 += 1;
            }
        }
    }

    //Stufe 7:
    //RW-Nuten nicht am Anschlag bevorzugen
    for(uint i=1; i<=bearb_0.zeilenanzahl() ;i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(bearb_0.zeile(i));
        if(zeile.zeile(1) == BEARBART_NUT)
        {
            nut n(zeile.text());
            if(n.breite() == 8.5 && n.tiefe() == 6.5)
            {
                if(n.ys() == n.ye())
                {
                    if(n.ys() == b_0 - 20 + 4.25)
                    {
                        bewertung_0 += 10;
                    }
                }
            }
        }
    }
    for(uint i=1; i<=bearb_90.zeilenanzahl() ;i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(bearb_90.zeile(i));
        if(zeile.zeile(1) == BEARBART_NUT)
        {
            nut n(zeile.text());
            if(n.breite() == 8.5 && n.tiefe() == 6.5)
            {
                if(n.ys() == n.ye())
                {
                    if(n.ys() == b_0 - 20 + 4.25)
                    {
                        bewertung_90 += 10;
                    }
                }
            }
        }
    }
    for(uint i=1; i<=bearb_180.zeilenanzahl() ;i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(bearb_180.zeile(i));
        if(zeile.zeile(1) == BEARBART_NUT)
        {
            nut n(zeile.text());
            if(n.breite() == 8.5 && n.tiefe() == 6.5)
            {
                if(n.ys() == n.ye())
                {
                    if(n.ys() == b_0 - 20 + 4.25)
                    {
                        bewertung_180 += 10;
                    }
                }
            }
        }
    }
    for(uint i=1; i<=bearb_270.zeilenanzahl() ;i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(bearb_270.zeile(i));
        if(zeile.zeile(1) == BEARBART_NUT)
        {
            nut n(zeile.text());
            if(n.breite() == 8.5 && n.tiefe() == 6.5)
            {
                if(n.ys() == n.ye())
                {
                    if(n.ys() == b_0 - 20 + 4.25)
                    {
                        bewertung_270 += 10;
                    }
                }
            }
        }
    }

    if(drehwinkel == "0")
    {
        double tmp_l = Laenge;
        double tmp_b = Breite;
        text_zeilenweise tmp_bearb = Bearbeitungen;
        tmp_bearb = gehr_3achs(tmp_bearb, tmp_l, tmp_b, "fmc");
        msg = fmc_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b, zust_fkon, "0", \
                                formartierungen_aufbrechen, fkon_kantenschonend);
        QString warnungen = warnungen_fmc(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
        info += " (";
        info += double_to_qstring(bewertung_0);
        info += " Punkte)";
        info += "\n";
        info += warnungen;
    }else if(drehwinkel == "90")
    {
        double tmp_l = Laenge;
        double tmp_b = Breite;
        text_zeilenweise tmp_bearb = Bearbeitungen;
        tmp_bearb = gehr_3achs(tmp_bearb, tmp_l, tmp_b, "fmc");
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        msg = fmc_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b, zust_fkon, "90", \
                                formartierungen_aufbrechen, fkon_kantenschonend);
        QString warnungen = warnungen_fmc(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
        info += " (";
        info += double_to_qstring(bewertung_90);
        info += " Punkte)";
        info += "\n";
        info += warnungen;
    }else if(drehwinkel == "180")
    {
        double tmp_l = Laenge;
        double tmp_b = Breite;
        text_zeilenweise tmp_bearb = Bearbeitungen;
        tmp_bearb = gehr_3achs(tmp_bearb, tmp_l, tmp_b, "fmc");
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        msg = fmc_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b, zust_fkon, "180", \
                                formartierungen_aufbrechen, fkon_kantenschonend);
        QString warnungen = warnungen_fmc(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
        info += " (";
        info += double_to_qstring(bewertung_180);
        info += " Punkte)";
        info += "\n";
        info += warnungen;
    }else if(drehwinkel == "270")
    {
        double tmp_l = Laenge;
        double tmp_b = Breite;
        text_zeilenweise tmp_bearb = Bearbeitungen;
        tmp_bearb = gehr_3achs(tmp_bearb, tmp_l, tmp_b, "fmc");
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        msg = fmc_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b, zust_fkon, "270", \
                                formartierungen_aufbrechen, fkon_kantenschonend);
        QString warnungen = warnungen_fmc(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
        info += " (";
        info += double_to_qstring(bewertung_270);
        info += " Punkte)";
        info += "\n";
        info += warnungen;
    }else
    {
        //Bewertungen auswerten:
        if(bewertung_0 >= 100 && \
           bewertung_0 >= bewertung_90 && \
           bewertung_0 >= bewertung_180 && \
           bewertung_0 >= bewertung_270 )
        {
            //0 ist super:
            double tmp_l = Laenge;
            double tmp_b = Breite;
            text_zeilenweise tmp_bearb = Bearbeitungen;
            tmp_bearb = gehr_3achs(tmp_bearb, tmp_l, tmp_b, "fmc");
            msg = fmc_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b, zust_fkon, "0", \
                                    formartierungen_aufbrechen, fkon_kantenschonend);
            QString warnungen = warnungen_fmc(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
            info  = "  -> Drehung keine";
            info += " (";
            info += double_to_qstring(bewertung_0);
            info += " Punkte)";
            info += "\n";
            info += warnungen;
        }else if(bewertung_90 >= 100 && \
                 bewertung_90 >= bewertung_0 && \
                 bewertung_90 >= bewertung_180 && \
                 bewertung_90 >= bewertung_270 )
        {
            //90 ist super:
            double tmp_l = Laenge;
            double tmp_b = Breite;
            text_zeilenweise tmp_bearb = Bearbeitungen;
            tmp_bearb = gehr_3achs(tmp_bearb, tmp_l, tmp_b, "fmc");
            tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
            msg = fmc_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b, zust_fkon, "90", \
                                    formartierungen_aufbrechen, fkon_kantenschonend);
            QString warnungen = warnungen_fmc(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
            info  = "  -> Drehung 90 Grad";
            info += " (";
            info += double_to_qstring(bewertung_90);
            info += " Punkte)";
            info += "\n";
            info += warnungen;
        }else if(bewertung_180 >= 100 && \
                 bewertung_180 >= bewertung_0 && \
                 bewertung_180 >= bewertung_90 && \
                 bewertung_180 >= bewertung_270 )
        {
            //180 ist super:
            double tmp_l = Laenge;
            double tmp_b = Breite;
            text_zeilenweise tmp_bearb = Bearbeitungen;
            tmp_bearb = gehr_3achs(tmp_bearb, tmp_l, tmp_b, "fmc");
            tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
            tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
            msg = fmc_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b, zust_fkon, "180", \
                                    formartierungen_aufbrechen, fkon_kantenschonend);
            QString warnungen = warnungen_fmc(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
            info  = "  -> Drehung 180 Grad";
            info += " (";
            info += double_to_qstring(bewertung_180);
            info += " Punkte)";
            info += "\n";
            info += warnungen;
        }else if(bewertung_270 >= 100 && \
                 bewertung_270 >= bewertung_0 && \
                 bewertung_270 >= bewertung_90 && \
                 bewertung_270 >= bewertung_180 )
        {
            //270 ist super:
            double tmp_l = Laenge;
            double tmp_b = Breite;
            text_zeilenweise tmp_bearb = Bearbeitungen;
            tmp_bearb = gehr_3achs(tmp_bearb, tmp_l, tmp_b, "fmc");
            tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
            tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
            tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
            msg = fmc_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b, zust_fkon, "270", \
                                    formartierungen_aufbrechen, fkon_kantenschonend);
            QString warnungen = warnungen_fmc(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
            info = "  -> Drehung 270 Grad";
            info += " (";
            info += double_to_qstring(bewertung_270);
            info += " Punkte)";
            info += "\n";
            info += warnungen;
        }else
        {
            //wir nehmen 0:
            double tmp_l = Laenge;
            double tmp_b = Breite;
            text_zeilenweise tmp_bearb = Bearbeitungen;
            tmp_bearb = gehr_3achs(tmp_bearb, tmp_l, tmp_b, "fmc");
            msg = fmc_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b, zust_fkon, "0", \
                                    formartierungen_aufbrechen, fkon_kantenschonend);
            QString warnungen = warnungen_fmc(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
            info  = "  -> Drehung keine";
            info += " (";
            info += double_to_qstring(bewertung_0);
            info += " Punkte)";
            info += "\n";
            info += warnungen;
        }
    }
    return msg;
}
QString werkstueck::ganx(text_zeilenweise wkzmagazin, QString& info , QString drehwinkel)
{
    QString msg;
    bearb_sortieren();
    hbemiduebeltiefe();

    double tmp_l = Breite;
    double tmp_b = Laenge;
    text_zeilenweise tmp_bearb;
    tmp_bearb = bearb_optimieren_ganx(Bearbeitungen);
    tmp_bearb = gehr_3achs(tmp_bearb, tmp_l, tmp_b, "ganx");

    //Die beste Drehrichtung herausfinden:
    int bewertung_0    = 1;
    int bewertung_90   = 1;
    int bewertung_180  = 1;
    int bewertung_270  = 1;
    //Stufe 1:
    //heraus bekommen, für welche Lage es Warnungen gibt:
    QString warnung;
    text_zeilenweise bearb_kopie = tmp_bearb;
    double l_kopie = tmp_l;
    double b_kopie = tmp_b;
    //------------------------0:
    warnung = warnungen_ganx(bearb_kopie, l_kopie, b_kopie, wkzmagazin);
    if(warnung.isEmpty())
    {
        bewertung_0 = 100;
    }else
    {
        bewertung_0 = 0;
    }
    text_zeilenweise bearb_0 = bearb_kopie;
    double l_0 = l_kopie;
    double b_0 = b_kopie;
    //------------------------90:
    bearb_kopie = bearb_drehen_90(bearb_kopie, l_kopie, b_kopie);
    warnung = warnungen_ganx(bearb_kopie, l_kopie, b_kopie, wkzmagazin);
    if(warnung.isEmpty())
    {
        bewertung_90 = 100;
    }else
    {
        bewertung_90 = 0;
    }
    text_zeilenweise bearb_90 = bearb_kopie;
    double l_90 = l_kopie;
    double b_90 = b_kopie;
    //------------------------180:
    bearb_kopie = bearb_drehen_90(bearb_kopie, l_kopie, b_kopie);
    warnung = warnungen_ganx(bearb_kopie, l_kopie, b_kopie, wkzmagazin);
    if(warnung.isEmpty())
    {
        bewertung_180 = 100;
    }else
    {
        bewertung_180 = 0;
    }
    text_zeilenweise bearb_180 = bearb_kopie;
    double l_180 = l_kopie;
    double b_180 = b_kopie;
    //------------------------270:
    bearb_kopie = bearb_drehen_90(bearb_kopie, l_kopie, b_kopie);
    warnung = warnungen_ganx(bearb_kopie, l_kopie, b_kopie, wkzmagazin);
    if(warnung.isEmpty())
    {
        bewertung_270 = 100;
    }else
    {
        bewertung_270 = 0;
    }
    text_zeilenweise bearb_270 = bearb_kopie;
    double l_270 = l_kopie;
    double b_270 = b_kopie;

    //Stufe 2:
    //heraus bekommen wo vorne ist anhand von Bearbeitungen:
    for(uint i=1; i<=bearb_0.zeilenanzahl() ;i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(bearb_0.zeile(i));
        if(zeile.zeile(1) == BEARBART_BOHR)
        {
            bohrung bo(zeile.text());
            if(bo.dm() == 8 || \
               bo.dm() == 8.2)
            {
                if(bo.x() == 20)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                {
                    bewertung_0 += 2;
                }
                if(bo.y() == b_0-20)//Gilt für HBE, Löcher mit diesem Abst. in der Fläche sind nicht zu erwarten
                {
                    bewertung_0 += 2;
                }
            }else if(bo.dm() == 35.3)//Töpfe/Topfbänder am Anschlag anlegen
            {
                if(bo.y() < 30)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                {
                    bewertung_0 += 5;
                }
                if(bo.x() < 30)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                {
                    bewertung_0 += 5;
                }
            }
        }
    }
    for(uint i=1; i<=bearb_90.zeilenanzahl() ;i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(bearb_90.zeile(i));
        if(zeile.zeile(1) == BEARBART_BOHR)
        {
            bohrung bo(zeile.text());
            if(bo.dm() == 8 || \
               bo.dm() == 8.2)
            {
                if(bo.x() == 20)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                {
                    bewertung_90 += 2;
                }
                if(bo.y() == b_90-20)//Gilt für HBE, Löcher mit diesem Abst. in der Fläche sind nicht zu erwarten
                {
                    bewertung_90 += 2;
                }
            }else if(bo.dm() == 35.3)//Töpfe/Topfbänder am Anschlag anlegen
            {
                if(bo.y() < 30)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                {
                    bewertung_90 += 5;
                }
                if(bo.x() < 30)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                {
                    bewertung_90 += 5;
                }
            }
        }
    }
    for(uint i=1; i<=bearb_180.zeilenanzahl() ;i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(bearb_180.zeile(i));
        if(zeile.zeile(1) == BEARBART_BOHR)
        {
            bohrung bo(zeile.text());
            if(bo.dm() == 8 || \
               bo.dm() == 8.2)
            {
                if(bo.x() == 20)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                {
                    bewertung_180 += 2;
                }
                if(bo.y() == b_180-20)//Gilt für HBE, Löcher mit diesem Abst. in der Fläche sind nicht zu erwarten
                {
                    bewertung_180 += 2;
                }
            }else if(bo.dm() == 35.3)//Töpfe/Topfbänder am Anschlag anlegen
            {
                if(bo.y() < 30)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                {
                    bewertung_180 += 5;
                }
                if(bo.x() < 30)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                {
                    bewertung_180 += 5;
                }
            }
        }
    }
    for(uint i=1; i<=bearb_270.zeilenanzahl() ;i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(bearb_270.zeile(i));
        if(zeile.zeile(1) == BEARBART_BOHR)
        {
            bohrung bo(zeile.text());
            if(bo.dm() == 8 || \
               bo.dm() == 8.2)
            {
                if(bo.x() == 20)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                {
                    bewertung_270 += 2;
                }
                if(bo.y() == b_270-20)//Gilt für HBE, Löcher mit diesem Abst. in der Fläche sind nicht zu erwarten
                {
                    bewertung_270 += 2;
                }
            }else if(bo.dm() == 35.3)//Töpfe/Topfbänder am Anschlag anlegen
            {
                if(bo.y() < 30)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                {
                    bewertung_270 += 5;
                }
                if(bo.x() < 30)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                {
                    bewertung_270 += 5;
                }
            }
        }
    }

    //Stufe 3:
    //heraus bekommen wo vorne ist anhand von Kanteninfo:
    if(!kante_hi_ganx("0").isEmpty())
    {
        bewertung_0 += 10;
    }
    if(!kante_li_ganx("0").isEmpty())
    {
        bewertung_0 += 15;
    }

    if(!kante_hi_ganx("90").isEmpty())
    {
        bewertung_90 += 10;
    }
    if(!kante_li_ganx("90").isEmpty())
    {
        bewertung_90 += 15;
    }

    if(!kante_hi_ganx("180").isEmpty())
    {
        bewertung_180 += 10;
    }
    if(!kante_li_ganx("180").isEmpty())
    {
        bewertung_180 += 15;
    }

    if(!kante_hi_ganx("270").isEmpty())
    {
        bewertung_270 += 10;
    }
    if(!kante_li_ganx("270").isEmpty())
    {
        bewertung_270 += 15;
    }

    //Stufe 4:
    //Teile bevorzugen, bei bei denen gilt: B > L:
    if(b_0 > l_0)
    {
        bewertung_0 += 20;
    }
    if(b_90 > l_90)
    {
        bewertung_90 += 20;
    }
    if(b_180 > l_180)
    {
        bewertung_180 += 20;
    }
    if(b_270 > l_270)
    {
        bewertung_270 += 20;
    }

    //Stufe 5:
    //Bei schmalen Teilen bevorzugen, wenn HBE nicht aus richtung des Anschlages kommt:
    if(b_0 <= Schwellenwert_ay)
    {
        bool bonus = true;
        for(uint i=1; i<=bearb_0.zeilenanzahl() ;i++)
        {
            text_zeilenweise zeile;
            zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
            zeile.set_text(bearb_0.zeile(i));
            if(zeile.zeile(1) == BEARBART_BOHR)
            {
                bohrung bo(zeile.text());
                if(bo.bezug() == WST_BEZUG_VO)
                {
                    bonus = false;
                }
            }
        }
        if(bonus == true)
        {
            bewertung_0 += 20;
        }else
        {
            bewertung_0 -= 10;
        }
    }
    if(b_90 <= Schwellenwert_ay)
    {
        bool bonus = true;
        for(uint i=1; i<=bearb_90.zeilenanzahl() ;i++)
        {
            text_zeilenweise zeile;
            zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
            zeile.set_text(bearb_90.zeile(i));
            if(zeile.zeile(1) == BEARBART_BOHR)
            {
                bohrung bo(zeile.text());
                if(bo.bezug() == WST_BEZUG_VO)
                {
                    bonus = false;
                }
            }
        }
        if(bonus == true)
        {
            bewertung_90 += 20;
        }else
        {
            bewertung_90 -= 10;
        }
    }
    if(b_180 <= Schwellenwert_ay)
    {
        bool bonus = true;
        for(uint i=1; i<=bearb_180.zeilenanzahl() ;i++)
        {
            text_zeilenweise zeile;
            zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
            zeile.set_text(bearb_180.zeile(i));
            if(zeile.zeile(1) == BEARBART_BOHR)
            {
                bohrung bo(zeile.text());
                if(bo.bezug() == WST_BEZUG_VO)
                {
                    bonus = false;
                }
            }
        }
        if(bonus == true)
        {
            bewertung_180 += 20;
        }else
        {
            bewertung_180 -= 10;
        }
    }
    if(b_270 <= Schwellenwert_ay)
    {
        bool bonus = true;
        for(uint i=1; i<=bearb_270.zeilenanzahl() ;i++)
        {
            text_zeilenweise zeile;
            zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
            zeile.set_text(bearb_270.zeile(i));
            if(zeile.zeile(1) == BEARBART_BOHR)
            {
                bohrung bo(zeile.text());
                if(bo.bezug() == WST_BEZUG_VO)
                {
                    bonus = false;
                }
            }
        }
        if(bonus == true)
        {
            bewertung_270 += 20;
        }else
        {
            bewertung_270 -= 10;
        }
    }

    //Stufe 6:
    //Flächenbohrungen mit geringem Kantenabstand beforzugen
    for(uint i=1; i<=bearb_0.zeilenanzahl() ;i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(bearb_0.zeile(i));
        if(zeile.zeile(1) == BEARBART_BOHR)
        {
            bohrung bo(zeile.text());
            if(bo.x() < 20 || bo.y() < 20)
            {
                bewertung_0 += 1;
            }
        }
    }
    for(uint i=1; i<=bearb_90.zeilenanzahl() ;i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(bearb_90.zeile(i));
        if(zeile.zeile(1) == BEARBART_BOHR)
        {
            bohrung bo(zeile.text());
            if(bo.x() < 20 || bo.y() < 20)
            {
                bewertung_90 += 1;
            }
        }
    }
    for(uint i=1; i<=bearb_180.zeilenanzahl() ;i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(bearb_180.zeile(i));
        if(zeile.zeile(1) == BEARBART_BOHR)
        {
            bohrung bo(zeile.text());
            if(bo.x() < 20 || bo.y() < 20)
            {
                bewertung_180 += 1;
            }
        }
    }
    for(uint i=1; i<=bearb_270.zeilenanzahl() ;i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(bearb_270.zeile(i));
        if(zeile.zeile(1) == BEARBART_BOHR)
        {
            bohrung bo(zeile.text());
            if(bo.x() < 20 || bo.y() < 20)
            {
                bewertung_270 += 1;
            }
        }
    }

    //Stufe 7:
    //RW-Nuten nicht am Anschlag bevorzugen
    //ist bei GANX nicht nötig weil physisch mit der Maschine nicht möglich

    if(drehwinkel == "0")
    {
        double tmp_l = Breite;
        double tmp_b = Laenge;
        text_zeilenweise tmp_bearb;
        tmp_bearb = bearb_optimieren_ganx(Bearbeitungen);
        tmp_bearb = gehr_3achs(tmp_bearb, tmp_l, tmp_b, "ganx");                             //<--------------------
        msg = ganx_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b);
        QString warnungen = warnungen_ganx(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
        info += " (";
        info += double_to_qstring(bewertung_0);
        info += " Punkte)";
        info += "\n";
        info += warnungen;
    }else if(drehwinkel == "90")
    {
        double tmp_l = Breite;
        double tmp_b = Laenge;
        text_zeilenweise tmp_bearb;
        tmp_bearb = bearb_optimieren_ganx(Bearbeitungen);
        tmp_bearb = gehr_3achs(tmp_bearb, tmp_l, tmp_b, "ganx");
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        msg = ganx_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b);
        QString warnungen = warnungen_ganx(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
        info += " (";
        info += double_to_qstring(bewertung_90);
        info += " Punkte)";
        info += "\n";
        info += warnungen;
    }else if(drehwinkel == "180")
    {
        double tmp_l = Breite;
        double tmp_b = Laenge;
        text_zeilenweise tmp_bearb;
        tmp_bearb = bearb_optimieren_ganx(Bearbeitungen);
        tmp_bearb = gehr_3achs(tmp_bearb, tmp_l, tmp_b, "ganx");
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        msg = ganx_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b);
        QString warnungen = warnungen_ganx(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
        info += " (";
        info += double_to_qstring(bewertung_180);
        info += " Punkte)";
        info += "\n";
        info += warnungen;
    }else if(drehwinkel == "270")
    {
        double tmp_l = Breite;
        double tmp_b = Laenge;
        text_zeilenweise tmp_bearb;
        tmp_bearb = bearb_optimieren_ganx(Bearbeitungen);
        tmp_bearb = gehr_3achs(tmp_bearb, tmp_l, tmp_b, "ganx");
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        msg = ganx_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b);
        QString warnungen = warnungen_ganx(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
        info += " (";
        info += double_to_qstring(bewertung_270);
        info += " Punkte)";
        info += "\n";
        info += warnungen;
    }else
    {
        //Bewertungen auswerten:
        if(bewertung_0 >= 100 && \
           bewertung_0 >= bewertung_90 && \
           bewertung_0 >= bewertung_180 && \
           bewertung_0 >= bewertung_270 )
        {
            //0 ist super:
            double tmp_l = Breite;
            double tmp_b = Laenge;
            text_zeilenweise tmp_bearb;
            tmp_bearb = bearb_optimieren_ganx(Bearbeitungen);
            tmp_bearb = gehr_3achs(tmp_bearb, tmp_l, tmp_b, "ganx");
            msg = ganx_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b);
            QString warnungen = warnungen_ganx(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
            info  = "  -> Drehung keine";
            info += " (";
            info += double_to_qstring(bewertung_0);
            info += " Punkte)";
            info += "\n";
            info += warnungen;
        }else if(bewertung_90 >= 100 && \
                 bewertung_90 >= bewertung_0 && \
                 bewertung_90 >= bewertung_180 && \
                 bewertung_90 >= bewertung_270 )
        {
            //90 ist super:
            double tmp_l = Breite;
            double tmp_b = Laenge;
            text_zeilenweise tmp_bearb;
            tmp_bearb = bearb_optimieren_ganx(Bearbeitungen);
            tmp_bearb = gehr_3achs(tmp_bearb, tmp_l, tmp_b, "ganx");
            tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
            msg = ganx_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b);
            QString warnungen = warnungen_ganx(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
            info  = "  -> Drehung 90 Grad";
            info += " (";
            info += double_to_qstring(bewertung_90);
            info += " Punkte)";
            info += "\n";
            info += warnungen;
        }else if(bewertung_180 >= 100 && \
                 bewertung_180 >= bewertung_0 && \
                 bewertung_180 >= bewertung_90 && \
                 bewertung_180 >= bewertung_270 )
        {
            //180 ist super:
            double tmp_l = Breite;
            double tmp_b = Laenge;
            text_zeilenweise tmp_bearb;
            tmp_bearb = bearb_optimieren_ganx(Bearbeitungen);
            tmp_bearb = gehr_3achs(tmp_bearb, tmp_l, tmp_b, "ganx");
            tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
            tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
            msg = ganx_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b);
            QString warnungen = warnungen_ganx(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
            info  = "  -> Drehung 180 Grad";
            info += " (";
            info += double_to_qstring(bewertung_180);
            info += " Punkte)";
            info += "\n";
            info += warnungen;
        }else if(bewertung_270 >= 100 && \
                 bewertung_270 >= bewertung_0 && \
                 bewertung_270 >= bewertung_90 && \
                 bewertung_270 >= bewertung_180 )
        {
            //270 ist super:
            double tmp_l = Breite;
            double tmp_b = Laenge;
            text_zeilenweise tmp_bearb;
            tmp_bearb = bearb_optimieren_ganx(Bearbeitungen);
            tmp_bearb = gehr_3achs(tmp_bearb, tmp_l, tmp_b, "ganx");
            tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
            tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
            tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
            msg = ganx_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b);
            QString warnungen = warnungen_ganx(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
            info  = "  -> Drehung 270 Grad";
            info += " (";
            info += double_to_qstring(bewertung_270);
            info += " Punkte)";
            info += "\n";
            info += warnungen;
        }else
        {
            //wir nehmen 0:
            double tmp_l = Breite;
            double tmp_b = Laenge;
            text_zeilenweise tmp_bearb;
            tmp_bearb = bearb_optimieren_ganx(Bearbeitungen);
            tmp_bearb = gehr_3achs(tmp_bearb, tmp_l, tmp_b, "ganx");
            msg = ganx_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b);
            QString warnungen = warnungen_ganx(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
            info  = "  -> Drehung keine";
            info += " (";
            info += double_to_qstring(bewertung_0);
            info += " Punkte)";
            info += "\n";
            info += warnungen;
        }
    }
    return msg;
}
QString werkstueck::ggf(text_zeilenweise wkzmagazin, QString& info , QString drehwinkel)
{
    QString msg;
    if(drehwinkel == "0")
    {
        double tmp_l = Laenge;
        double tmp_b = Breite;
        text_zeilenweise tmp_bearb = Bearbeitungen;
        msg = ggf_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b);
        QString warnungen = warnungen_ggf(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
        info += " ";
        info += warnungen;
    }else if(drehwinkel == "90")
    {
        double tmp_l = Laenge;
        double tmp_b = Breite;
        text_zeilenweise tmp_bearb = Bearbeitungen;
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        msg = ggf_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b);
        QString warnungen = warnungen_ggf(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
        info += " ";
        info += warnungen;
    }else if(drehwinkel == "180")
    {
        double tmp_l = Laenge;
        double tmp_b = Breite;
        text_zeilenweise tmp_bearb = Bearbeitungen;
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        msg = ggf_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b);
        QString warnungen = warnungen_ggf(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
        info += " ";
        info += warnungen;
    }else if(drehwinkel == "270")
    {
        double tmp_l = Laenge;
        double tmp_b = Breite;
        text_zeilenweise tmp_bearb = Bearbeitungen;
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        msg = ggf_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b);
        QString warnungen = warnungen_ggf(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
        info += " ";
        info += warnungen;
    }else
    {
        double tmp_l = Laenge;
        double tmp_b = Breite;
        text_zeilenweise tmp_bearb = Bearbeitungen;
        msg = ggf_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b);
        QString warnungen = warnungen_ggf(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
        info += " ";
        info += warnungen;
    }
    return msg;
}
QString werkstueck::eigenses_format(QString drehwinkel, QString ausgabeformat, text_zeilenweise wkzmagazin,\
                                        bool formartierungen_aufbrechen, bool fkon_kantenschonend)
{
    QString msg;
    bearb_sortieren();
    hbemiduebeltiefe();

    if(drehwinkel == "0")
    {
        double tmp_l = Laenge;
        double tmp_b = Breite;
        text_zeilenweise tmp_bearb = Bearbeitungen;        
        tmp_bearb = gehr_3achs(tmp_bearb, tmp_l, tmp_b, "eigen");
        if(ausgabeformat == GANX)
        {
            tmp_l = Breite;
            tmp_b = Laenge;
            tmp_bearb = bearb_optimieren_ganx(Bearbeitungen); //nur zu Testzwecken
        }
        msg = eigen_dateitext(tmp_bearb, tmp_l, tmp_b, ausgabeformat, wkzmagazin, \
                                  formartierungen_aufbrechen, fkon_kantenschonend);
    }else if(drehwinkel == "90")
    {
        double tmp_l = Laenge;
        double tmp_b = Breite;
        text_zeilenweise tmp_bearb = Bearbeitungen;
        tmp_bearb = gehr_3achs(tmp_bearb, tmp_l, tmp_b, "eigen");
        if(ausgabeformat == GANX)
        {
            tmp_l = Breite;
            tmp_b = Laenge;
            tmp_bearb = bearb_optimieren_ganx(Bearbeitungen); //nur zu Testzwecken
        }
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        msg = eigen_dateitext(tmp_bearb, tmp_l, tmp_b, ausgabeformat, wkzmagazin, \
                                  formartierungen_aufbrechen, fkon_kantenschonend);
    }else if(drehwinkel == "180")
    {
        double tmp_l = Laenge;
        double tmp_b = Breite;
        text_zeilenweise tmp_bearb = Bearbeitungen;
        tmp_bearb = gehr_3achs(tmp_bearb, tmp_l, tmp_b, "eigen");
        if(ausgabeformat == GANX)
        {
            tmp_l = Breite;
            tmp_b = Laenge;
            tmp_bearb = bearb_optimieren_ganx(Bearbeitungen); //nur zu Testzwecken
        }
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        msg = eigen_dateitext(tmp_bearb, tmp_l, tmp_b, ausgabeformat, wkzmagazin, \
                                  formartierungen_aufbrechen, fkon_kantenschonend);
    }else if(drehwinkel == "270")
    {
        double tmp_l = Laenge;
        double tmp_b = Breite;
        text_zeilenweise tmp_bearb = Bearbeitungen;
        tmp_bearb = gehr_3achs(tmp_bearb, tmp_l, tmp_b, "eigen");
        if(ausgabeformat == GANX)
        {
            tmp_l = Breite;
            tmp_b = Laenge;
            tmp_bearb = bearb_optimieren_ganx(Bearbeitungen); //nur zu Testzwecken
        }
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        msg = eigen_dateitext(tmp_bearb, tmp_l, tmp_b, ausgabeformat, wkzmagazin, \
                                  formartierungen_aufbrechen, fkon_kantenschonend);
    }else
    {
        //drehung 0:
        double tmp_l = Laenge;
        double tmp_b = Breite;
        text_zeilenweise tmp_bearb = Bearbeitungen;
        tmp_bearb = gehr_3achs(tmp_bearb, tmp_l, tmp_b, "eigen");
        if(ausgabeformat == GANX)
        {
            tmp_l = Breite;
            tmp_b = Laenge;
            tmp_bearb = bearb_optimieren_ganx(Bearbeitungen); //nur zu Testzwecken
        }
        msg = eigen_dateitext(tmp_bearb, tmp_l, tmp_b, ausgabeformat, wkzmagazin, \
                                  formartierungen_aufbrechen, fkon_kantenschonend);
    }
    return msg;
}

//--------------------------------------------------Manipulationen:

//--------------------------------------------------
//#######################################################################
//Private:
//#######################################################################
//--------------------------------------------------set_xy:

//--------------------------------------------------get_xy:
QString werkstueck::warnungen_ganx(text_zeilenweise bearbeit,double tmp_l, double tmp_b, text_zeilenweise wkzmagazin)
{
    bearbeit = dubosplitten(bearbeit, wkzmagazin, dicke());
    QString msg = "";
    double wst_x = tmp_l;
    double wst_y = tmp_b;

    //Wst-Maße prüfen:
    double tmp_d = Dicke;
    if(wst_y > 4000)
    {
        msg += "  !! Werkstueck-Y-Mass > 4000mm\n";
        msg += "     Y-Mass = " + double_to_qstring(wst_y) + "\n";
    }
    if(wst_y < 250)
    {
        msg += "  !! Werkstueck-Y-Mass < 250mm\n";
        msg += "     Y-Mass = " + double_to_qstring(wst_y) + "\n";
    }
    if(wst_x > 1000)
    {
        msg += "  !! Werkstueck-X-Mass > 1000mm\n";
        msg += "     X-Mass = " + double_to_qstring(wst_x) + "\n";
    }
    if(wst_x < 50)
    {
        msg += "  !! Werkstueck-X-Mass < 50mm\n";
        msg += "     X-Mass = " + double_to_qstring(wst_x) + "\n";
    }
    if(tmp_d > 60)
    {
        msg += "  !! Werkstueck-Dicke > 60mm\n";
        msg += "     Dicke = " + double_to_qstring(tmp_d) + "\n";
    }
    if(tmp_d < 6)
    {
        msg += "  !! Werkstueck-Dicke < 6mm\n";
        msg += "     Dicke = " + double_to_qstring(tmp_d) + "\n";
    }

    werkzeugmagazin wkzmag(wkzmagazin);

    for(uint i=1; i<=bearbeit.zeilenanzahl() ;i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(bearbeit.zeile(i));

        QString art = zeile.zeile(1);
        if(art == BEARBART_BOHR)
        {
            bohrung bo(zeile.text());
            QString bezug = bo.bezug();

            //Warnung für HBEs:
            if(bezug == WST_BEZUG_VO || bezug == WST_BEZUG_HI)
            {
                double x = bo.x();
                if( x<18 )
                {
                    msg += "  !! HBE zu dicht am Rand!\n";
                    msg += "     X-Mass muss >= 18mm sein\n";
                    msg += "     X-Mass ist ";
                    msg += double_to_qstring(x);
                    msg += "mm\n";
                }
            }

            //Warnung für Kreistaschen di zu dicht am Rand sind:
            QString tnummer = wkzmag.wkznummer(WKZ_TYP_BOHRER, bo.dm(), bo.tiefe(), Dicke, bezug);
            if(tnummer.isEmpty())//Bohren nicht möglich weil kein passendes Werkzeug
            {
                tnummer = wkzmag.wkznummer_von_alias(bo.wkznum());//Ist direkt ei WKZ definiert?
                if(tnummer.isEmpty())
                {
                    tnummer = wkzmag.wkznummer(WKZ_TYP_FRAESER, bo.dm(), bo.tiefe(), Dicke, bezug);
                }
                if(!tnummer.isEmpty())//Kreistasche kann gefräst werden
                {
                    double xmin = bo.x() - bo.dm()/2;
                    if(xmin < 40)
                    {
                        msg += "  !! Kreistasche zu dicht am Rand!\n";
                        msg += "     X-Abstand muss mind 40mm sein\n";
                        msg += "     X-Abstand ist ";
                        msg += double_to_qstring(xmin);
                        msg += "mm\n";
                    }

                    //Nutzlänge Fräser und Tati prüfen:
                    if(bo.tiefe() > wkzmag.nutzlaenge(tnummer).toDouble())
                    {
                        msg += "  !! Nutzlaenge < Fraestiefe    bei Kreistasche!\n";
                    }
                    //Mindest-Zustellmaß des Fräsers Prüfen:
                    if(bo.tiefe() < wkzmag.zustellmass_min(tnummer).toDouble())
                    {
                        msg += "  !! Fraestiefe < Mindest-Zustellmass   bei Kreistasche!\n";
                    }
                }else//Es ist auch kein passender Fräser da, die CNC-Bearbeitung kann nicht erfolgen
                {
                    msg += "  !! Kein Werkzeug fuer Bohrung oder Kreistasche gefunden!\n";
                    msg += "    ->";
                    msg += bearbeit.zeile(i).replace("\t", " | ");
                    msg += "\n";
                }
            }else
            {

                if(wkzmag.dm(tnummer) == "35")
                {
                    //Warnung für 35er Bohrer geben der in Kante Bohrt (Bohrerbruch durch Unwucht)
                    //rein mechanisch ist das mind X-Maß beim 35er Bohrer 11,5mm == 35/2-6 == 17,5-6
                    if(bo.x() < 17.5            ||\
                       bo.x() > (tmp_l-17.5)    ||\
                       bo.y() < 17.5            ||\
                       bo.y() > (tmp_b-17.5)    )
                    {
                        msg += "  !! 35er Bohrung zu dicht am Rand fuer verwendeten Bohrer!\n";
                    }
                }else if(wkzmag.dm(tnummer) == "8")
                {
                    if(bo.x() < 0)
                    {
                        msg += "  !! X-Maß 8er Bohrung zu gering! Mind 0mm erforderlich.\n";
                    }
                }else if(wkzmag.dm(tnummer) == "10")
                {
                    if(bo.x() < 0)
                    {
                        msg += "  !! X-Maß 10er Bohrung zu gering! Mind 0mm erforderlich.\n";
                    }
                }else
                {
                    double wkzdm = wkzmag.dm(tnummer).toDouble();
                    if(bo.x() < 1+wkzdm/2)
                    {
                        msg += "  !! X-Maß ";
                        msg += double_to_qstring(wkzdm);
                        msg += "er Bohrung zu gering! Mind ";
                        msg += double_to_qstring(1+wkzdm/2);
                        msg += "mm erforderlich.\n";
                    }
                }

            }

        }else if(art == BEARBART_RTA)
        {
            rechtecktasche rt(zeile.text());
            //Prüfen ob Tasche zu dicht am WST-Rand ist:
            double xmin = rt.x();
            if(rt.drewi() == 0 || rt.drewi() == 180)
            {
                xmin = xmin - rt.laenge()/2;
            }if(rt.drewi() == 90 || rt.drewi() == 270)
            {
                xmin = xmin - rt.breite()/2;
            }else
            {
                xmin = xmin - sqrt(rt.laenge() * rt.breite())/2; //Näherungsweise
            }

            if(xmin < 40)
            {
                msg += "  !! Rechtecktasche zu dicht am Rand!\n";
                msg += "     X-Abstand muss mind 40mm sein\n";
                msg += "     X-Abstand ist ca ";
                msg += double_to_qstring(xmin);
                msg += "mm\n";
            }

            //-----------------------------------------------

            //Prüfen ob Nutzlänge ausreichend für Tati ist:
            QString tnummer = wkzmag.wkznummer_von_alias(rt.wkznum());//Ist direkt ei WKZ definiert?
            if(tnummer.isEmpty())
            {
                QString bezug = rt.bezug();
                double minmass = 0;
                if(rt.laenge() < rt.breite())
                {
                    minmass = rt.laenge();
                }else
                {
                    minmass = breite();
                }
                tnummer = wkzmag.wkznummer(WKZ_TYP_FRAESER, minmass, rt.tiefe(), Dicke, bezug);
            }
            if(!tnummer.isEmpty())
            {
                //Nutzlänge Fräser und Tati prüfen
                if(rt.tiefe() > wkzmag.nutzlaenge(tnummer).toDouble())
                {
                    msg += "  !! Nutzlaenge < Fraestiefe    bei Rechtecktasche!\n";
                }
                //Mindest-Zustellmaß des Fräsers Prüfen:
                if(rt.tiefe() < wkzmag.zustellmass_min(tnummer).toDouble())
                {
                    msg += "  !! Fraestiefe < Mindest-Zustellmass    bei Rechtecktasche!\n";
                }
            }
        }else if(art == BEARBART_NUT)
        {
            nut nu(zeile.text());
            QString bezug = nu.bezug();
            QString tnummer = wkzmag.wkznummer(WKZ_TYP_SAEGE, 0, nu.tiefe(), Dicke, bezug);
            double nutblattbreite = wkzmag.saegeblattbreite(tnummer).toDouble();
            if(nu.xs() != nu.xe())
            {
                msg += "  !! Nutrichutng auf der der Maschine nicht moeglich!\n";
            }else if(nu.xs()-nu.breite() < 57.5)
            {
                msg += "  !! Nut zu dicht am Rand/zu dicht an Spannzange!\n";
                msg += "     Randabstand in X muss mind 57,5mm sein\n";
                msg += "     Randabstand X ist ca ";
                msg += double_to_qstring(nu.xs()-nu.breite());
                msg += "mm\n";
            }
            if(nu.breite() < nutblattbreite)
            {
                msg += "  !! Nutbreite ist kleiner als Blattbreite!\n";
            }
        }
    }

    return msg;
}
QString werkstueck::warnungen_fmc(text_zeilenweise bearbeit,double tmp_l, double tmp_b, text_zeilenweise wkzmagazin)
{
    bearbeit = dubosplitten(bearbeit, wkzmagazin, dicke());
    QString msg = "";

    //Wst-Maße prüfen:
    double tmp_d = Dicke;
    if(tmp_l > 3000)
    {
        msg += "  !! Werkstueck-Laenge > 3000mm\n";
    }
    if(tmp_l < 120)
    {
        msg += "  !! Werkstueck-Laenge < 120mm\n";
    }
    if(tmp_b > 1100)
    {
        msg += "  !! Werkstueck-Breite > 1100mm\n";
    }
    if(tmp_b < 50)
    {
        msg += "  !! Werkstueck-Breite < 50mm\n";
    }
    if(tmp_d > 100)
    {
        msg += "  !! Werkstueck ist sehr dick\n";
    }
    if(tmp_d < 5)
    {
        msg += "  !! Werkstueck ist sehr duenn\n";
    }

    werkzeugmagazin wkzmag(wkzmagazin);

    for(uint i=1; i<=bearbeit.zeilenanzahl() ;i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(bearbeit.zeile(i));

        QString art = zeile.zeile(1);
        if(art == BEARBART_BOHR)
        {
            bohrung bo(zeile.text());
            QString bezug = bo.bezug();

            QString tnummer = wkzmag.wkznummer(WKZ_TYP_BOHRER, bo.dm(), bo.tiefe(), Dicke, bezug);
            if(tnummer.isEmpty())//Bohren nicht möglich weil kein passendes Werkzeug
            {
                tnummer = wkzmag.wkznummer_von_alias(bo.wkznum());//Ist direkt ei WKZ definiert?
                if(tnummer.isEmpty())
                {
                    tnummer = wkzmag.wkznummer(WKZ_TYP_FRAESER, bo.dm(), bo.tiefe(), Dicke, bezug);
                }
                if(!tnummer.isEmpty())//Kreistasche kann gefräst werden
                {
                    //Nutzlänge Fräser und Tati prüfen:
                    if(bo.tiefe() > wkzmag.nutzlaenge(tnummer).toDouble())
                    {
                        msg += "  !! Nutzlaenge < Fraestiefe    bei Kreistasche!\n";
                    }
                    //Mindest-Zustellmaß des Fräsers Prüfen:
                    if(bo.tiefe() < wkzmag.zustellmass_min(tnummer).toDouble())
                    {
                        msg += "  !! Fraestiefe < Mindest-Zustellmass    bei Kreistasche!\n";
                    }

                }else//Es ist auch kein passender Frser da, die CNC-Bearbeitung kann nicht erfolgen
                {
                    msg += "  !! Kein Werkzeug fuer Bohrung oder Kreistasche gefunden!\n";
                    msg += "    ->";
                    msg += bearbeit.zeile(i).replace("\t", " | ");
                    msg += "\n";
                }
            }

        }else if(art == BEARBART_RTA)
        {
            rechtecktasche rt(zeile.text());

            //Prüfen ob Nutzlänge ausreichend für Tati ist:
            QString tnummer = wkzmag.wkznummer_von_alias(rt.wkznum());//Ist direkt ei WKZ definiert?
            if(tnummer.isEmpty())
            {
                QString bezug = rt.bezug();
                double minmass = 0;
                if(rt.laenge() < rt.breite())
                {
                    minmass = rt.laenge();
                }else
                {
                    minmass = breite();
                }
                tnummer = wkzmag.wkznummer(WKZ_TYP_FRAESER, minmass, rt.tiefe(), Dicke, bezug);
            }
            if(!tnummer.isEmpty())
            {
                //Nutzlänge Fräser und Tati prüfen
                if(rt.tiefe() > wkzmag.nutzlaenge(tnummer).toDouble())
                {
                    msg += "  !! Nutzlaenge < Fraestiefe    bei Rechtecktasche!\n";
                }
                //Mindest-Zustellmaß des Fräsers Prüfen:
                if(rt.tiefe() < wkzmag.zustellmass_min(tnummer).toDouble())
                {
                    msg += "  !! Fraestiefe < Mindest-Zustellmass    bei Rechtecktasche!\n";
                }
            }
        }else if(art == BEARBART_NUT)
        {
            nut nu(zeile.text());
            QString bezug = nu.bezug();
            QString tnummer = wkzmag.wkznummer(WKZ_TYP_SAEGE, 0, nu.tiefe(), Dicke, bezug);
            double nutblattbreite = wkzmag.saegeblattbreite(tnummer).toDouble();
            if(nu.breite() < nutblattbreite)
            {
                msg += "  !! Nutbreite ist kleiner als Blattbreite!\n";
            }
        }else if(art == BEARBART_FRAESERAUFRUF)
        {
            fraueseraufruf fa(zeile.text());
            QString tnummer = wkzmag.wkznummer_von_alias(fa.wkznum());
            if(tnummer.isEmpty())
            {
                msg += "  !! Keine Werkzeugnummer vergeben bei Fraeseraufruf!\n";
            }else
            {
                //Nutzlänge Fräser und Tati prüfen
                if(fa.tiefe() > wkzmag.nutzlaenge(tnummer).toDouble())
                {
                    msg += "  !! Nutzlaenge < Fraestiefe    bei Fraeseraufruf!\n";
                }
                //Mindest-Zustellmaß des Fräsers Prüfen:
                if(fa.tiefe() < wkzmag.zustellmass_min(tnummer).toDouble())
                {
                    msg += "  !! Fraestiefe < Mindest-Zustellmass    bei Fraeseraufruf!\n";
                }
            }

        }
    }

    return msg;
}
QString werkstueck::warnungen_ggf(text_zeilenweise bearbeit, double tmp_l, double tmp_b, text_zeilenweise wkzmagazin)
{
    QString msg = "";
    //Bislang erfolgt keine Prüfung und es werden keine Warnungen gegeben...
    //...
    //...
    //...
    //...
    //...
    //...
    //...
    //...
    //...
    return msg;
}
QString werkstueck::fehler_kein_WKZ(QString exportformat, text_zeilenweise bearbeitung)
{
    QString fehlermeldung;

    fehlermeldung += "Fehler bei ";
    fehlermeldung += exportformat;
    fehlermeldung += "-Export!\n";

    fehlermeldung += "Teilname: ";
    fehlermeldung += Name;
    fehlermeldung += "\n";

    fehlermeldung += "Kein Werkzeug fuer ";

    fehlermeldung += bearb_menschlich_lesbar(bearbeitung);

    return fehlermeldung;
}
QString werkstueck::bearb_menschlich_lesbar(text_zeilenweise bearbeitung)
{
    QString daten;
    if(bearbeitung.zeile(1) == BEARBART_BOHR)
    {
        daten += "Bohrung oder Kreistasche:\n";
        daten += "Bezugsflaeche: ";
        daten += bearbeitung.zeile(2);
        daten += "\n";
        daten += "Durchmesser: ";
        daten += bearbeitung.zeile(3);
        daten += "\n";
        daten += "Tiefe: ";
        daten += bearbeitung.zeile(4);
        daten += "\n";
        daten += "Pos X: ";
        daten += bearbeitung.zeile(5);
        daten += "\n";
        daten += "Pos Y: ";
        daten += bearbeitung.zeile(6);
        daten += "\n";
        daten += "Pos Z: ";
        daten += bearbeitung.zeile(7);
        daten += "\n";
        daten += "AFB: ";
        daten += bearbeitung.zeile(8);
        daten += "\n";
        daten += "Zustellmass: ";
        daten += bearbeitung.zeile(9);
        daten += "\n";
        daten += "Werkzeug: ";
        daten += bearbeitung.zeile(10);
        daten += "\n";
    }else if(bearbeitung.zeile(1) == BEARBART_RTA)
    {
        daten += "Rechtecktasche:\n";
        daten += "Bezugsflaeche: ";
        daten += bearbeitung.zeile(2);
        daten += "\n";
        daten += "Taschenleange: ";
        daten += bearbeitung.zeile(3);
        daten += "\n";
        daten += "Taschenbreite: ";
        daten += bearbeitung.zeile(4);
        daten += "\n";
        daten += "Taschentiefe: ";
        daten += bearbeitung.zeile(5);
        daten += "\n";
        daten += "Pos X: ";
        daten += bearbeitung.zeile(6);
        daten += "\n";
        daten += "Pos Y: ";
        daten += bearbeitung.zeile(7);
        daten += "\n";
        daten += "Pos Z: ";
        daten += bearbeitung.zeile(8);
        daten += "\n";
        daten += "Drehwinkel im UZS: ";
        daten += bearbeitung.zeile(9);
        daten += "\n";
        daten += "Eckenradius: ";
        daten += bearbeitung.zeile(10);
        daten += "\n";
        daten += "Ausraeumen: ";
        daten += bearbeitung.zeile(11);
        daten += "\n";
        daten += "AFB: ";
        daten += bearbeitung.zeile(12);
        daten += "\n";
        daten += "Zustellmass: ";
        daten += bearbeitung.zeile(13);
        daten += "\n";
        daten += "Werkzeug: ";
        daten += bearbeitung.zeile(14);
        daten += "\n";
    }else if(bearbeitung.zeile(1) == BEARBART_NUT)
    {
        daten += "Nut:\n";
        daten += "Bezugsflaeche: ";
        daten += bearbeitung.zeile(2);
        daten += "\n";
        daten += "Startpunkt in X: ";
        daten += bearbeitung.zeile(3);
        daten += "\n";
        daten += "Startpunkt in Y: ";
        daten += bearbeitung.zeile(4);
        daten += "\n";
        daten += "Endpunkt in X: ";
        daten += bearbeitung.zeile(5);
        daten += "\n";
        daten += "Endpunkt in Y: ";
        daten += bearbeitung.zeile(6);
        daten += "\n";
        daten += "Nuttiefe: ";
        daten += bearbeitung.zeile(7);
        daten += "\n";
        daten += "Nutbreite: ";
        daten += bearbeitung.zeile(8);
        daten += "\n";
        daten += "AFB: ";
        daten += bearbeitung.zeile(9);
        daten += "\n";
    }else if(bearbeitung.zeile(1) == BEARBART_FRAESERAUFRUF)
    {
        daten += "Aufruf Fraeser:\n";
        daten += "Bezugsflaeche: ";
        daten += bearbeitung.zeile(2);
        daten += "\n";
        daten += "Startpunkt in X: ";
        daten += bearbeitung.zeile(3);
        daten += "\n";
        daten += "Startpunkt in Y: ";
        daten += bearbeitung.zeile(4);
        daten += "\n";
        daten += "Startpunkt in Z: ";
        daten += bearbeitung.zeile(5);
        daten += "\n";
        daten += "Tiefe: ";
        daten += bearbeitung.zeile(6);
        daten += "\n";
        daten += "Bahnkorrektur: ";
        daten += bearbeitung.zeile(7);
        daten += "\n";
        daten += "Werkzeug: ";
        daten += bearbeitung.zeile(8);
        daten += "\n";
        daten += "AFB: ";
        daten += bearbeitung.zeile(9);
        daten += "\n";
    }else if(bearbeitung.zeile(1) == BEARBART_FRAESERGERADE)
    {
        daten += "gerade Fraesbahn:\n";
        daten += "Bezugsflaeche: ";
        daten += bearbeitung.zeile(2);
        daten += "\n";
        daten += "Startpunkt in X: ";
        daten += bearbeitung.zeile(3);
        daten += "\n";
        daten += "Startpunkt in Y: ";
        daten += bearbeitung.zeile(4);
        daten += "\n";
        daten += "Startpunkt Tiefe: ";
        daten += bearbeitung.zeile(5);
        daten += "\n";
        daten += "Endpunkt in X: ";
        daten += bearbeitung.zeile(6);
        daten += "\n";
        daten += "Endpunkt in Y: ";
        daten += bearbeitung.zeile(7);
        daten += "\n";
        daten += "Endpunkt Tiefe: ";
        daten += bearbeitung.zeile(8);
        daten += "\n";
        daten += "AFB: ";
        daten += bearbeitung.zeile(9);
        daten += "\n";
    }else if(bearbeitung.zeile(1) == BEARBART_FRAESERBOGEN)
    {
        daten += "gebogene Fraesbahn:\n";
        daten += "Bezugsflaeche: ";
        daten += bearbeitung.zeile(2);
        daten += "\n";
        daten += "Startpunkt in X: ";
        daten += bearbeitung.zeile(3);
        daten += "\n";
        daten += "Startpunkt in Y: ";
        daten += bearbeitung.zeile(4);
        daten += "\n";
        daten += "Startpunkt Tiefe: ";
        daten += bearbeitung.zeile(5);
        daten += "\n";
        daten += "Endpunkt in X: ";
        daten += bearbeitung.zeile(6);
        daten += "\n";
        daten += "Endpunkt in Y: ";
        daten += bearbeitung.zeile(7);
        daten += "\n";
        daten += "Endpunkt Tiefe: ";
        daten += bearbeitung.zeile(8);
        daten += "\n";
        daten += "Radius: ";
        daten += bearbeitung.zeile(9);
        daten += "\n";
        daten += "Bogenrichtung: ";
        if(bearbeitung.zeile(8) == "1")
        {
            daten += "Uhrzeigersinn";
        }else
        {
            daten += "Gegen-Uhrzeigersinn";
        }
        daten += "\n";
        daten += "AFB: ";
        daten += bearbeitung.zeile(11);
        daten += "\n";
    }
    return daten;
}
QString werkstueck::fmc_dateitext(text_zeilenweise wkzmagazin, text_zeilenweise bearb, \
                                      double tmp_l, double tmp_b, QString zust_fkon,\
                                      QString drewi, bool formartierungen_aufbrechen,\
                                      bool fkon_kantenschonend)
{
    text_zeilenweise bearb_kopie = bearb;
    if(formartierungen_aufbrechen == true)
    {
        bearb = formartierung_zu_einzelfkon(bearb, tmp_l, tmp_b);
    }
    if(fkon_kantenschonend == true)
    {
        bearb = fkon_kantengut(bearb, wkzmagazin, tmp_l, tmp_b);
    }
    bearb = kurze_an_ab_geraden(bearb, wkzmagazin);//Kringelfahrten vermeiden
    bearb = dubosplitten(bearb, wkzmagazin, dicke());
    bearb = rasterbohrungen_finden_fmc(bearb, wkzmagazin, tmp_l, tmp_b);
    QString msg;
    text_zeilenweise zeile;
    zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
     werkzeugmagazin wkzmag(wkzmagazin);
     QString kavo = kante_vo(drewi);//Kante vorne == Kante an X
     QString kali = kante_li(drewi);//Kante links == Kante an Y
     QString kahi = kante_hi(drewi);//Kante hinten == Kante nicht an X
     QString kare = kante_re(drewi);//Kante rechts == Kante nicht an Y

     bool ay = false;
     if(tmp_b < Schwellenwert_ay)
     {
         ay = true;
     }

     int min_kta_dm_ausraeumen_false = 200; //Durchmesser ab dem Kreistaschen nicht ausgeräumt werden

    //---------------------------------------Programmkopf:
    msg = FMC_PRGKOPF;
    msg += "\n";
    msg += "ABSTS=";                //Sicherheitsabstand
    msg += "20";
    msg += "\n";
    msg += "AFB=1\n";
    msg += "AXV=";                  //X-Versatz
    msg += "0";
    msg += "\n";
    msg += "AYV=";                  //Y-Veratz
    if(ay == true)
    {
        msg += "210";
    }else
    {
        msg += "0";
    }
    msg += "\n";
    msg += "BEZB=";                 //Bezeichnung
    msg += "Programmkopf";
    msg += "\n";
    msg += "FTL=";                  //Länge
    msg += double_to_qstring(tmp_l);
    msg += "\n";
    msg += "FTB=";                  //Breite
    msg += double_to_qstring(tmp_b);
    msg += "\n";
    msg += "FTD=";                  //Dicke
    msg += dicke_qstring();
    msg += "\n";
    msg += "HOLKA=-1\n";            //Hole Kante Nr
    msg += "KOM1=";                //Kommentar 1
    msg += fmc_kommentar_gute_seite(bearb_kopie);
    //msg += "(NULL)";
    msg += "\n";
    msg += "KOM2=";                 //Kommentar 2
    if(!kavo.isEmpty()  &&  !kali.isEmpty())
    {
        msg += "an X+Y mit Kante";
    }else if(!kavo.isEmpty()  &&  kali.isEmpty())
    {
        msg += "an X mit / an Y ohne Kante";
    }else if(kavo.isEmpty()  &&  !kali.isEmpty())
    {
        msg += "an X ohne / an Y mit Kante";
    }else
    {
        if(kavo.isEmpty() && kahi.isEmpty() && kali.isEmpty() && kare.isEmpty())
        {
            msg += "(NULL)";
        }else
        {
            msg += "an X+Y ohne Kante";
        }
    }
    msg += "\n";
    msg += "LOESEN=";               //Automatisch lösen
    msg += "1";
    msg += "\n";
    msg += "MPB=";                  //Mehrplatzbelegungsart
    msg += "0";
    msg += "\n";
    msg += "RTB=B+(2*AY)\n";        //Rohteillänge
    msg += "RTL=L+(2*AX)\n";        //Rohteilbreite
    msg += "SPGLWKS=";              //Spiegeln
    msg += "0";
    msg += "\n";
    msg += "WKDS=";                 //Fünf Seiten
    msg += "0";
    msg += "\n";
    msg += "ZSCHABLO=";             //Schablonenhöhe
    msg += "0";
    msg += "\n";
    msg += "\n";
    //---------------------------------------ggf. Y-Versatz kennlich machen:
    if(ay == true)
    {
        msg += kommentar_fmc("--------------------");
        msg += kommentar_fmc("ay 210");
        msg += kommentar_fmc("--------------------");

        bool kreuzkopf_von_vorne = false;
        for(uint i=1; i<=bearb.zeilenanzahl() ;i++)
        {
            text_zeilenweise zeile;
            zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
            zeile.set_text(bearb.zeile(i));

            QString art = zeile.zeile(1);
            if(art == BEARBART_BOHR)
            {
                bohrung bo(zeile.text());

                if(bo.bezug() == WST_BEZUG_VO)
                {
                    kreuzkopf_von_vorne = true;
                }
            }
        }
        if(kreuzkopf_von_vorne == true)
        {
            msg += kommentar_fmc("----------------------------------------");
            msg += kommentar_fmc("Achtung!");
            msg += kommentar_fmc("Kreuzkopf in Kollision mit");
            msg += kommentar_fmc("Versatzbrett ay 210");
            msg += kommentar_fmc("----------------------------------------");
        }
    }
    //---------------------------------------Bearbeitungen Oberseite und Hirnseiten:
    for(uint i=1 ; i<=bearb.zeilenanzahl() ; i++)
    {
        zeile.set_text(bearb.zeile(i));
        if(zeile.zeile(1) == BEARBART_BOHR)
        {
            bohrung bo(zeile.text());
            QString bezug = bo.bezug();
            QString tnummer = wkzmag.wkznummer(WKZ_TYP_BOHRER, bo.dm(), bo.tiefe(), Dicke, bezug);
            if(!tnummer.isEmpty())
            {
                //Werkzeug wurde gefunden, Bohrung kann gebohrt werden:
                QString bohrgruppe = "1";
                if(bezug == WST_BEZUG_OBSEI)
                {
                    double tiefe;
                    if(bo.tiefe() <= dicke())
                    {
                        tiefe = bo.tiefe();
                    }else
                    {
                        tiefe = dicke() - bo.tiefe();
                    }
                    msg += FMC_BOHR_DM;
                    msg += "\n";
                    msg += FMC_BOHR_DM_X;
                    msg += "=";
                    msg += double_to_qstring(bo.x());
                    msg += "\n";
                    msg += FMC_BOHR_DM_Y;
                    msg += "=";
                    msg += double_to_qstring(bo.y());
                    msg += "\n";
                    msg += FMC_BOHR_DM_TIEFE;
                    msg += "=";
                    msg += double_to_qstring(tiefe);
                    msg += "\n";
                    msg += FMC_BOHR_DM_DM;
                    msg += "=";
                    msg += bo.dm_qstring();
                    msg += "\n";
                    msg += "GRP=";                  //Bohrgruppe
                    msg += bohrgruppe;
                    msg += "\n";

                    //Anbohrtiefe gem. Voreinstellung IMAWOP
                    //Anbohrvorschub gem. Voreinstellung IMAWOP
                    //Restbohrmaß gem. Voreinstellung IMAWOP
                    //Bohrvorschub gem. Voreinstellung IMAWOP

                    msg += "ZSM=";                  //Zustellmaß
                    msg += wkzmag.zustellmass(tnummer);
                    msg += "\n";

                    //Drehzahl gem. Voreinstellung IMAWOP

                    msg += "MRICHT=0\n";
                    msg += "TASTEIN=-1\n";
                    msg += "BEZB=";
                    msg += "Bohrung DM";
                    msg += bo.dm_qstring();
                    msg += " T";
                    msg += double_to_qstring(tiefe);
                    msg += "\n";
                    msg += FMC_BOHR_DM_AFB;
                    msg += "=";
                    msg += bo.afb();
                    msg += "\n";
                    msg += "\n";
                }else if(bezug == WST_BEZUG_LI)
                {
                    msg += FMC_HBEXP;
                    msg += "\n";
                    msg += "Y1=";
                    msg += bo.y_qstring();
                    msg += "\n";
                    msg += "Y2=(NULL)\n";
                    msg += "Y3=(NULL)\n";
                    msg += "Y4=(NULL)\n";
                    msg += "Y5=(NULL)\n";
                    msg += "Y6=(NULL)\n";
                    msg += "TI=";
                    msg += bo.tiefe_qstring();
                    msg += "\n";
                    msg += "Z=";
                    msg += bo.z_qstring();
                    msg += "\n";
                    msg += "DM=";
                    msg += bo.dm_qstring();
                    msg += "\n";
                    msg += "KETTE=0\n";
                    msg += "GRP=1\n";           //Bohrgruppe
                    msg += "X2=-1\n";
                    msg += "X1=0\n";

                    //Anbohrtiefe gem. Voreinstellung IMAWOP
                    //Anbohrvorschub gem. Voreinstellung IMAWOP
                    //Bohrvorschub gem. Voreinstellung IMAWOP
                    //Drehzahl gem. Voreinstellung IMAWOP

                    msg += "BEZB=";
                    msg += "HBE X+ DM";
                    msg += bo.dm_qstring();
                    msg += " T";
                    msg += bo.tiefe_qstring();
                    msg += "\n";
                    msg += "AFB=";
                    msg += bo.afb();
                    msg += "\n";
                    msg += "\n";
                }else if(bezug == WST_BEZUG_RE)
                {
                    msg += FMC_HBEXM;
                    msg += "\n";
                    msg += "Y1=";
                    msg += bo.y_qstring();
                    msg += "\n";
                    msg += "Y2=(NULL)\n";
                    msg += "Y3=(NULL)\n";
                    msg += "Y4=(NULL)\n";
                    msg += "Y5=(NULL)\n";
                    msg += "Y6=(NULL)\n";
                    msg += "TI=";
                    msg += bo.tiefe_qstring();
                    msg += "\n";
                    msg += "Z=";
                    msg += bo.z_qstring();
                    msg += "\n";
                    msg += "DM=";
                    msg += bo.dm_qstring();
                    msg += "\n";
                    msg += "KETTE=0\n";
                    msg += "GRP=1\n";           //Bohrgruppe
                    msg += "X2=-1\n";
                    msg += "X1=L\n";

                    //Anbohrtiefe gem. Voreinstellung IMAWOP
                    //Anbohrvorschub gem. Voreinstellung IMAWOP
                    //Bohrvorschub gem. Voreinstellung IMAWOP
                    //Drehzahl gem. Voreinstellung IMAWOP

                    msg += "BEZB=";
                    msg += "HBE X- DM";
                    msg += bo.dm_qstring();
                    msg += " T";
                    msg += bo.tiefe_qstring();
                    msg += "\n";
                    msg += "AFB=";
                    msg += bo.afb();
                    msg += "\n";
                    msg += "\n";
                }else if(bezug == WST_BEZUG_VO)
                {
                    msg += FMC_HBEYP;
                    msg += "\n";
                    msg += "X1=";
                    msg += bo.x_qstring();
                    msg += "\n";
                    msg += "X2=(NULL)\n";
                    msg += "X3=(NULL)\n";
                    msg += "X4=(NULL)\n";
                    msg += "X5=(NULL)\n";
                    msg += "X6=(NULL)\n";
                    msg += "TI=";
                    msg += bo.tiefe_qstring();
                    msg += "\n";
                    msg += "Z=";
                    msg += bo.z_qstring();
                    msg += "\n";
                    msg += "DM=";
                    msg += bo.dm_qstring();
                    msg += "\n";
                    msg += "KETTE=0\n";
                    msg += "GRP=1\n";           //Bohrgruppe
                    msg += "Y2=-1\n";
                    msg += "Y1=0\n";

                    //Anbohrtiefe gem. Voreinstellung IMAWOP
                    //Anbohrvorschub gem. Voreinstellung IMAWOP
                    //Bohrvorschub gem. Voreinstellung IMAWOP
                    //Drehzahl gem. Voreinstellung IMAWOP

                    msg += "BEZB=";
                    msg += "HBE Y+ DM";
                    msg += bo.dm_qstring();
                    msg += " T";
                    msg += bo.tiefe_qstring();
                    msg += "\n";
                    msg += "AFB=";
                    msg += bo.afb();
                    msg += "\n";
                    msg += "\n";
                }else if(bezug == WST_BEZUG_HI)
                {
                    msg += FMC_HBEYM;
                    msg += "\n";
                    msg += "X1=";
                    msg += bo.x_qstring();
                    msg += "\n";
                    msg += "X2=(NULL)\n";
                    msg += "X3=(NULL)\n";
                    msg += "X4=(NULL)\n";
                    msg += "X5=(NULL)\n";
                    msg += "X6=(NULL)\n";
                    msg += "TI=";
                    msg += bo.tiefe_qstring();
                    msg += "\n";
                    msg += "Z=";
                    msg += bo.z_qstring();
                    msg += "\n";
                    msg += "DM=";
                    msg += bo.dm_qstring();
                    msg += "\n";
                    msg += "KETTE=0\n";
                    msg += "GRP=1\n";           //Bohrgruppe
                    msg += "Y2=-1\n";
                    msg += "Y1=B\n";

                    //Anbohrtiefe gem. Voreinstellung IMAWOP
                    //Anbohrvorschub gem. Voreinstellung IMAWOP
                    //Bohrvorschub gem. Voreinstellung IMAWOP
                    //Drehzahl gem. Voreinstellung IMAWOP

                    msg += "BEZB=";
                    msg += "HBE Y- DM";
                    msg += bo.dm_qstring();
                    msg += " T";
                    msg += bo.tiefe_qstring();
                    msg += "\n";
                    msg += "AFB=";
                    msg += bo.afb();
                    msg += "\n";
                    msg += "\n";
                }
            }else
            {
                //Kein Werkzeug wurde gefunden.
                //Kann Bohrung als Kreistasche gefräst werden?:
                tnummer = wkzmag.wkznummer_von_alias(bo.wkznum());//Ist direkt ei WKZ definiert?
                if(tnummer.isEmpty())
                {
                    tnummer = wkzmag.wkznummer(WKZ_TYP_FRAESER, bo.dm(), bo.tiefe(), Dicke, bezug);
                }
                if(!tnummer.isEmpty())
                {
                    double zustellmas = bo.zustellmass();
                    if(zustellmas <= 0)
                    {
                        zustellmas = wkzmag.zustellmass(tnummer).toDouble();
                    }

                    double tiefe = 0;
                    QString tiefe_qstring;
                    if(bo.tiefe() > dicke())
                    {
                        tiefe = dicke() - bo.tiefe();
                        tiefe_qstring = double_to_qstring(tiefe);
                    }else if(dicke()-bo.tiefe() <= 2)
                    {
                        tiefe_qstring  = "D-";
                        tiefe_qstring += double_to_qstring(dicke()-bo.tiefe());
                    }else
                    {
                        tiefe = bo.tiefe();
                        tiefe_qstring = double_to_qstring(tiefe);
                    }

                    bool ausraeumen = true;
                    if(bo.dm() > 2*wkzmag.dm(tnummer).toDouble()+20)
                    {
                        if(bo.tiefe() < 0  ||  bo.tiefe() > dicke())
                        {
                            ausraeumen = false;
                        }
                    }
                    if(bo.dm() > min_kta_dm_ausraeumen_false)
                    {
                        ausraeumen = false;
                    }

                    if(bo.bezug() == WST_BEZUG_OBSEI)
                    {
                        msg += FMC_KTA;
                        msg += "\n";
                        msg += "WKZID=";           //WKZ-Nummer
                        msg += tnummer;
                        msg += "\n";
                        msg += "MPX=";
                        msg += bo.x_qstring();
                        msg += "\n";
                        msg += "MPY=";
                        msg += bo.y_qstring();
                        msg += "\n";
                        msg += "DM=";
                        msg += bo.dm_qstring();
                        msg += "\n";
                        msg += "TI=";
                        msg += tiefe_qstring;
                        msg += "\n";
                        msg += "LGEZU=";            //Zustellmaß
                        msg += double_to_qstring(zustellmas);
                        msg += "\n";
                        msg += "GEGENL=1\n";        //Gegenlauf
                        msg += "RAEUMEN=";          //Ausräumen
                        if(ausraeumen == true)
                        {
                            msg += "1";
                        }else
                        {
                            msg += "0";
                        }
                        msg += "\n";

                        //Eintauchvorschub gem. Voreinstellung IMAWOP
                        //Vorschub gem. Voreinstellung IMAWOP
                        //Drehzahl gem. Voreinstellung IMAWOP

                        msg += "BEZB=";
                        msg += "Kreistasche DM";
                        msg += bo.dm_qstring();
                        msg += " T";
                        msg += tiefe_qstring;
                        msg += "\n";
                        msg += "AFB=";
                        msg += bo.afb();
                        msg += "\n";
                        msg += "WKZAKTUELL=1\n";
                        msg += "\n";
                    }

                }else
                {
                    //Mit Fehlermeldung abbrechen:
                    QString msg = fehler_kein_WKZ("fmc", zeile);
                    QMessageBox mb;
                    mb.setText(msg);
                    mb.exec();
                    return msg;
                }
            }
        }else if(zeile.zeile(1) == BEARBART_BOHRRASTER)
        {
            bohrraster bora(zeile.text());
            QString bezug = bora.bezug();
            QString tnummer = wkzmag.wkznummer(WKZ_TYP_BOHRER, bora.dm(), bora.tiefe(), Dicke, bezug);
            if(!tnummer.isEmpty())
            {
                //Werkzeug wurde gefunden, Bohrung kann gebohrt werden:
                QString bohrgruppe = "1";
                if(bezug == WST_BEZUG_OBSEI)
                {
                    double tiefe;
                    if(bora.tiefe() <= dicke())
                    {
                        tiefe = bora.tiefe();
                    }else
                    {
                        tiefe = dicke() - bora.tiefe();
                    }

                    //Lochreihen ausgeben
                    if(bora.anz_y() == 1)
                    {
                        //Lochreihen oder Bohrbild in X?:
                        if(bora.raster_x() == 32  &&  bora.dm() == 5)
                        {
                            //Lochreihe:
                            msg += FMC_LORAE;
                            msg += "\n";
                            //---------------------------------
                            msg += FMC_LORAE_AFB;       //Aufruf Lochreihendialog
                            msg += bora.afb();
                            msg += "\n";
                            //---------------------------------
                            msg += FMC_LORAE_BEZ;       //Bezeichnung
                            msg += "=";
                            msg += "Lochreihe DM";
                            msg += bora.dm_qstring();
                            msg += " T";
                            msg += double_to_qstring(tiefe);
                            msg += "\n";
                            //---------------------------------
                            msg += FMC_LORAE_DM;        //Durchmesser
                            msg += "=";
                            msg += bora.dm_qstring();
                            msg += "\n";
                            //---------------------------------
                            msg += FMC_LORAE_XS;        //Startpunkt in X
                            msg += "=";
                            msg += bora.x_qstring();
                            msg += "\n";
                            //---------------------------------
                            msg += FMC_LORAE_XE;        //Endpunkt in X
                            msg += "=";
                            msg += double_to_qstring(bora.x() + (bora.anz_x()*(bora.raster_x()-1))  );
                            msg += "+0.5";              //Sonst ist es zu genau und es wird ggf 1 Bohrung zu wenig gebohrt
                            msg += "\n";
                            //---------------------------------
                            msg += "EPY";
                            msg += "=";
                            msg += "Y1";                //gerade verlaufende Lochreihe von 0 bis L
                            msg += "\n";
                            //---------------------------------
                            msg += FMC_LORAE_Y1;
                            msg += "=";
                            msg += bora.y_qstring();
                            msg += "\n";
                            //---------------------------------
                            msg += FMC_LORAE_Y2;
                            msg += "=";
                            msg += "(NULL)";
                            msg += "\n";
                            //---------------------------------
                            msg += "F";                 //Vorschub
                            msg += "=";
                            msg += "AUTO";
                            msg += "\n";
                            //---------------------------------
                            msg += "FAN";                 //Anfahr-Vorschub
                            msg += "=";
                            msg += "AUTO";
                            msg += "\n";
                            //---------------------------------
                            msg += "GRP";               //Bohrgruppe
                            msg += "=";
                            msg += bohrgruppe;
                            msg += "\n";
                            //---------------------------------
                            msg += "LGEAB";             //Restbohrmaß
                            msg += "=";
                            msg += "4";
                            msg += "\n";
                            //---------------------------------
                            msg += "LGEAN";             //Anbohrtiefe
                            msg += "=";
                            msg += "4";
                            msg += "\n";
                            //---------------------------------
                            msg += "MITTE";             //Vermitteln  0|1|2
                            msg += "=";
                            msg += "0";
                            msg += "\n";
                            //---------------------------------
                            msg += "MRICHT";            //Messen Seite
                            msg += "=";
                            msg += "0";
                            msg += "\n";
                            //---------------------------------
                            msg += "N";                 //Drehzahl
                            msg += "=";
                            msg += "AUTO";
                            msg += "\n";
                            //---------------------------------
                            msg += FMC_LORAE_RASTER;
                            msg += "=";
                            msg += bora.raster_x_qstring();
                            msg += "\n";
                            //---------------------------------
                            msg += "TASTEIN";
                            msg += "=";
                            msg += "-1";
                            msg += "\n";
                            //---------------------------------
                            msg += FMC_LORAE_TI;
                            msg += "=";
                            msg += double_to_qstring(tiefe);
                            msg += "\n";
                            //---------------------------------
                            msg += "ZSM";           //Zustellmaß
                            msg += "=";
                            //msg += bora.zustellmass_qstring();
                            msg += wkzmag.zustellmass(tnummer);
                            msg += "\n";
                            //---------------------------------
                            msg += "\n";
                        }else
                        {
                            //Bohrbild in X:
                            //max 6 Bohrungen pro Dialog!
                            for(uint i=0 ; i<bora.anz_x() ; i=i+6)
                            {
                                msg += FMC_BOBIX;
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIX_AFB;
                                msg += "=";
                                msg += bora.afb();
                                msg += "\n";
                                //------------------------------
                                msg += "BEZB";
                                msg += "=";
                                msg += "Bohren in X  DM";
                                msg += bora.dm_qstring();
                                msg += " T";
                                msg += double_to_qstring(tiefe);
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIX_DM;
                                msg += "=";
                                msg += bora.dm_qstring();
                                msg += "\n";
                                //------------------------------
                                msg += "F";                     //Vorschub
                                msg += "=";
                                msg += "AUTO";
                                msg += "\n";
                                //------------------------------
                                msg += "FAN";                   //Anfahrvorschub
                                msg += "=";
                                msg += "AUTO";
                                msg += "\n";
                                //------------------------------
                                msg += "GRP";                   //Bohrgruppe
                                msg += "=";
                                msg += bohrgruppe;
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIX_KM;            //Kettenmaß
                                msg += "=";
                                msg += "1";
                                msg += "\n";
                                //------------------------------
                                msg += "LGEAB";                 //Restbohrmaß
                                msg += "=";
                                msg += "4";
                                msg += "\n";
                                //------------------------------
                                msg += "LGEAN";                 //Anbohrtiefe
                                msg += "=";
                                msg += "4";
                                msg += "\n";
                                //------------------------------
                                msg += "MRICHT";                //Messen Seite
                                msg += "=";
                                msg += "0";
                                msg += "\n";
                                //------------------------------
                                msg += "N";                     //Drehzahl
                                msg += "=";
                                msg += "AUTO";
                                msg += "\n";
                                //------------------------------
                                msg += "TASTEIN";               //Taste Satz ein
                                msg += "=";
                                msg += "-1";
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIX_TI;            //Tiefe
                                msg += "=";
                                msg += double_to_qstring(tiefe);
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIX_X1;
                                msg += "=";
                                msg += double_to_qstring(  bora.x() + (i*bora.raster_x())  );
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIX_X2;
                                msg += "=";
                                if(bora.anz_x() >= i+2)
                                {
                                    msg += bora.raster_x_qstring();
                                }else
                                {
                                    msg += "(NULL)";
                                }
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIX_X3;
                                msg += "=";
                                if(bora.anz_x() >= i+3)
                                {
                                    msg += bora.raster_x_qstring();
                                }else
                                {
                                    msg += "(NULL)";
                                }
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIX_X4;
                                msg += "=";
                                if(bora.anz_x() >= i+4)
                                {
                                    msg += bora.raster_x_qstring();
                                }else
                                {
                                    msg += "(NULL)";
                                }
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIX_X5;
                                msg += "=";
                                if(bora.anz_x() >= i+5)
                                {
                                    msg += bora.raster_x_qstring();
                                }else
                                {
                                    msg += "(NULL)";
                                }
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIX_X6;
                                msg += "=";
                                if(bora.anz_x() >= i+6)
                                {
                                    msg += bora.raster_x_qstring();
                                }else
                                {
                                    msg += "(NULL)";
                                }
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIX_Y1;
                                msg += "=";
                                msg += bora.y_qstring();
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIX_Y2;
                                msg += "=";
                                msg += "-1";
                                msg += "\n";
                                //------------------------------
                                msg += "ZSM";           //Zustellmaß
                                msg += "=";
                                //msg += bora.zustellmass_qstring();
                                msg += wkzmag.zustellmass(tnummer);
                                msg += "\n";
                                //------------------------------
                                msg += "\n";
                            }
                        }
                    }else if(bora.anz_x() == 1)
                    {
                        //Bohrbild in Y:
                        //max 6 Bohrungen pro Dialog!
                        for(uint i=0 ; i<bora.anz_y() ; i=i+6)
                        {
                            msg += FMC_BOBIY;
                            msg += "\n";
                            //------------------------------
                            msg += FMC_BOBIX_AFB;
                            msg += "=";
                            msg += bora.afb();
                            msg += "\n";
                            //------------------------------
                            msg += "BEZB";
                            msg += "=";
                            msg += "Bohren in Y  DM";
                            msg += bora.dm_qstring();
                            msg += " T";
                            msg += double_to_qstring(tiefe);
                            msg += "\n";
                            //------------------------------
                            msg += FMC_BOBIX_DM;
                            msg += "=";
                            msg += bora.dm_qstring();
                            msg += "\n";
                            //------------------------------
                            msg += "F";                     //Vorschub
                            msg += "=";
                            msg += "AUTO";
                            msg += "\n";
                            //------------------------------
                            msg += "FAN";                   //Anfahrvorschub
                            msg += "=";
                            msg += "AUTO";
                            msg += "\n";
                            //------------------------------
                            msg += "GRP";                   //Bohrgruppe
                            msg += "=";
                            msg += bohrgruppe;
                            msg += "\n";
                            //------------------------------
                            msg += FMC_BOBIY_KM;            //Kettenmaß
                            msg += "=";
                            msg += "1";
                            msg += "\n";
                            //------------------------------
                            msg += "LGEAB";                 //Restbohrmaß
                            msg += "=";
                            msg += "4";
                            msg += "\n";
                            //------------------------------
                            msg += "LGEAN";                 //Anbohrtiefe
                            msg += "=";
                            msg += "4";
                            msg += "\n";
                            //------------------------------
                            msg += "MRICHT";                //Messen Seite
                            msg += "=";
                            msg += "0";
                            msg += "\n";
                            //------------------------------
                            msg += "N";                     //Drehzahl
                            msg += "=";
                            msg += "AUTO";
                            msg += "\n";
                            //------------------------------
                            msg += "TASTEIN";               //Taste Satz ein
                            msg += "=";
                            msg += "-1";
                            msg += "\n";
                            //------------------------------
                            msg += FMC_BOBIY_TI;            //Tiefe
                            msg += "=";
                            msg += double_to_qstring(tiefe);
                            msg += "\n";
                            //------------------------------
                            msg += FMC_BOBIY_Y1;
                            msg += "=";
                            msg += double_to_qstring(  bora.y() + (i*bora.raster_y())  );
                            msg += "\n";
                            //------------------------------
                            msg += FMC_BOBIY_Y2;
                            msg += "=";
                            if(bora.anz_y() >= i+2)
                            {
                                msg += bora.raster_y_qstring();
                            }else
                            {
                                msg += "(NULL)";
                            }
                            msg += "\n";
                            //------------------------------
                            msg += FMC_BOBIY_Y3;
                            msg += "=";
                            if(bora.anz_y() >= i+3)
                            {
                                msg += bora.raster_y_qstring();
                            }else
                            {
                                msg += "(NULL)";
                            }
                            msg += "\n";
                            //------------------------------
                            msg += FMC_BOBIY_Y4;
                            msg += "=";
                            if(bora.anz_y() >= i+4)
                            {
                                msg += bora.raster_y_qstring();
                            }else
                            {
                                msg += "(NULL)";
                            }
                            msg += "\n";
                            //------------------------------
                            msg += FMC_BOBIY_Y5;
                            msg += "=";
                            if(bora.anz_y() >= i+5)
                            {
                                msg += bora.raster_y_qstring();
                            }else
                            {
                                msg += "(NULL)";
                            }
                            msg += "\n";
                            //------------------------------
                            msg += FMC_BOBIY_Y6;
                            msg += "=";
                            if(bora.anz_y() >= i+6)
                            {
                                msg += bora.raster_y_qstring();
                            }else
                            {
                                msg += "(NULL)";
                            }
                            msg += "\n";
                            //------------------------------
                            msg += FMC_BOBIY_X1;
                            msg += "=";
                            msg += bora.x_qstring();
                            msg += "\n";
                            //------------------------------
                            msg += FMC_BOBIY_X2;
                            msg += "=";
                            msg += "-1";
                            msg += "\n";
                            //------------------------------
                            msg += "ZSM";           //Zustellmaß
                            msg += "=";
                            //msg += bora.zustellmass_qstring();
                            msg += wkzmag.zustellmass(tnummer);
                            msg += "\n";
                            //------------------------------
                            msg += "\n";
                        }
                    }else
                    {
                        //Bislang noch keine Lochrasttererkennung in X und Y gleichzeitig vorhanden
                        //desshalb Ausgabe an dieser Stellen nicht nötig
                    }
                }else if(bezug == WST_BEZUG_LI)
                {
                    //HBE Xplus:
                    for(uint i=0 ; i<bora.anz_y() ; i=i+6)
                    {
                        msg += FMC_HBEXP;
                        msg += "\n";
                        //------------------------------
                        msg += "Y1=";
                        msg += double_to_qstring(  bora.y() + (i*bora.raster_y())  );
                        msg += "\n";
                        //------------------------------
                        msg += "Y2=";
                        if(bora.anz_y() >= i+2)
                        {
                            msg += bora.raster_y_qstring();
                        }else
                        {
                            msg += "(NULL)";
                        }
                        msg += "\n";
                        //------------------------------
                        msg += "Y3=";
                        if(bora.anz_y() >= i+3)
                        {
                            msg += bora.raster_y_qstring();
                        }else
                        {
                            msg += "(NULL)";
                        }
                        msg += "\n";
                        //------------------------------
                        msg += "Y4=";
                        if(bora.anz_y() >= i+4)
                        {
                            msg += bora.raster_y_qstring();
                        }else
                        {
                            msg += "(NULL)";
                        }
                        msg += "\n";
                        //------------------------------
                        msg += "Y5=";
                        if(bora.anz_y() >= i+5)
                        {
                            msg += bora.raster_y_qstring();
                        }else
                        {
                            msg += "(NULL)";
                        }
                        msg += "\n";
                        //------------------------------
                        msg += "Y6=";
                        if(bora.anz_y() >= i+6)
                        {
                            msg += bora.raster_y_qstring();
                        }else
                        {
                            msg += "(NULL)";
                        }
                        msg += "\n";
                        //------------------------------
                        msg += "TI=";
                        msg += bora.tiefe_qstring();
                        msg += "\n";
                        msg += "Z=";
                        msg += bora.z_qstring();
                        msg += "\n";
                        msg += "DM=";
                        msg += bora.dm_qstring();
                        msg += "\n";
                        msg += "KETTE=1\n";
                        msg += "GRP=1\n";           //Bohrgruppe
                        msg += "X2=-1\n";
                        msg += "X1=0\n";

                        //Anbohrtiefe gem. Voreinstellung IMAWOP
                        //Anbohrvorschub gem. Voreinstellung IMAWOP
                        //Bohrvorschub gem. Voreinstellung IMAWOP
                        //Drehzahl gem. Voreinstellung IMAWOP

                        msg += "BEZB=";
                        msg += "HBE X+ DM";
                        msg += bora.dm_qstring();
                        msg += " T";
                        msg += bora.tiefe_qstring();
                        msg += "\n";
                        msg += "AFB=";
                        msg += bora.afb();
                        msg += "\n";
                        msg += "\n";
                    }
                }else if(bezug == WST_BEZUG_RE)
                {
                    //HBE Xminus:
                    for(uint i=0 ; i<bora.anz_y() ; i=i+6)
                    {
                        msg += FMC_HBEXM;
                        msg += "\n";
                        //------------------------------
                        msg += "Y1=";
                        msg += double_to_qstring(  bora.y() + (i*bora.raster_y())  );
                        msg += "\n";
                        //------------------------------
                        msg += "Y2=";
                        if(bora.anz_y() >= i+2)
                        {
                            msg += bora.raster_y_qstring();
                        }else
                        {
                            msg += "(NULL)";
                        }
                        msg += "\n";
                        //------------------------------
                        msg += "Y3=";
                        if(bora.anz_y() >= i+3)
                        {
                            msg += bora.raster_y_qstring();
                        }else
                        {
                            msg += "(NULL)";
                        }
                        msg += "\n";
                        //------------------------------
                        msg += "Y4=";
                        if(bora.anz_y() >= i+4)
                        {
                            msg += bora.raster_y_qstring();
                        }else
                        {
                            msg += "(NULL)";
                        }
                        msg += "\n";
                        //------------------------------
                        msg += "Y5=";
                        if(bora.anz_y() >= i+5)
                        {
                            msg += bora.raster_y_qstring();
                        }else
                        {
                            msg += "(NULL)";
                        }
                        msg += "\n";
                        //------------------------------
                        msg += "Y6=";
                        if(bora.anz_y() >= i+6)
                        {
                            msg += bora.raster_y_qstring();
                        }else
                        {
                            msg += "(NULL)";
                        }
                        msg += "\n";
                        //------------------------------
                        msg += "TI=";
                        msg += bora.tiefe_qstring();
                        msg += "\n";
                        msg += "Z=";
                        msg += bora.z_qstring();
                        msg += "\n";
                        msg += "DM=";
                        msg += bora.dm_qstring();
                        msg += "\n";
                        msg += "KETTE=1\n";
                        msg += "GRP=1\n";           //Bohrgruppe
                        msg += "X2=-1\n";
                        msg += "X1=L\n";

                        //Anbohrtiefe gem. Voreinstellung IMAWOP
                        //Anbohrvorschub gem. Voreinstellung IMAWOP
                        //Bohrvorschub gem. Voreinstellung IMAWOP
                        //Drehzahl gem. Voreinstellung IMAWOP

                        msg += "BEZB=";
                        msg += "HBE X- DM";
                        msg += bora.dm_qstring();
                        msg += " T";
                        msg += bora.tiefe_qstring();
                        msg += "\n";
                        msg += "AFB=";
                        msg += bora.afb();
                        msg += "\n";
                        msg += "\n";
                    }
                }else if(bezug == WST_BEZUG_VO)
                {
                    //HBE Yplus:
                    for(uint i=0 ; i<bora.anz_x() ; i=i+6)
                    {
                        msg += FMC_HBEYP;
                        msg += "\n";
                        msg += "X1=";
                        msg += double_to_qstring(  bora.x() + (i*bora.raster_x())  );
                        msg += "\n";
                        //------------------------------
                        msg += "X2=";
                        if(bora.anz_x() >= i+2)
                        {
                            msg += bora.raster_x_qstring();
                        }else
                        {
                            msg += "(NULL)";
                        }
                        msg += "\n";
                        //------------------------------
                        msg += "X3=";
                        if(bora.anz_x() >= i+3)
                        {
                            msg += bora.raster_x_qstring();
                        }else
                        {
                            msg += "(NULL)";
                        }
                        msg += "\n";
                        //------------------------------
                        msg += "X4=";
                        if(bora.anz_x() >= i+4)
                        {
                            msg += bora.raster_x_qstring();
                        }else
                        {
                            msg += "(NULL)";
                        }
                        msg += "\n";
                        //------------------------------
                        msg += "X5=";
                        if(bora.anz_x() >= i+5)
                        {
                            msg += bora.raster_x_qstring();
                        }else
                        {
                            msg += "(NULL)";
                        }
                        msg += "\n";
                        //------------------------------
                        msg += "X6=";
                        if(bora.anz_x() >= i+6)
                        {
                            msg += bora.raster_x_qstring();
                        }else
                        {
                            msg += "(NULL)";
                        }
                        msg += "\n";
                        //------------------------------
                        msg += "TI=";
                        msg += bora.tiefe_qstring();
                        msg += "\n";
                        msg += "Z=";
                        msg += bora.z_qstring();
                        msg += "\n";
                        msg += "DM=";
                        msg += bora.dm_qstring();
                        msg += "\n";
                        msg += "KETTE=1\n";
                        msg += "GRP=1\n";           //Bohrgruppe
                        msg += "Y2=-1\n";
                        msg += "Y1=0\n";

                        //Anbohrtiefe gem. Voreinstellung IMAWOP
                        //Anbohrvorschub gem. Voreinstellung IMAWOP
                        //Bohrvorschub gem. Voreinstellung IMAWOP
                        //Drehzahl gem. Voreinstellung IMAWOP

                        msg += "BEZB=";
                        msg += "HBE Y+ DM";
                        msg += bora.dm_qstring();
                        msg += " T";
                        msg += bora.tiefe_qstring();
                        msg += "\n";
                        msg += "AFB=";
                        msg += bora.afb();
                        msg += "\n";
                        msg += "\n";
                    }
                }else if(bezug == WST_BEZUG_HI)
                {
                    //HBE Yminus:
                    for(uint i=0 ; i<bora.anz_x() ; i=i+6)
                    {
                        msg += FMC_HBEYM;
                        msg += "\n";
                        msg += "X1=";
                        msg += double_to_qstring(  bora.x() + (i*bora.raster_x())  );
                        msg += "\n";
                        //------------------------------
                        msg += "X2=";
                        if(bora.anz_x() >= i+2)
                        {
                            msg += bora.raster_x_qstring();
                        }else
                        {
                            msg += "(NULL)";
                        }
                        msg += "\n";
                        //------------------------------
                        msg += "X3=";
                        if(bora.anz_x() >= i+3)
                        {
                            msg += bora.raster_x_qstring();
                        }else
                        {
                            msg += "(NULL)";
                        }
                        msg += "\n";
                        //------------------------------
                        msg += "X4=";
                        if(bora.anz_x() >= i+4)
                        {
                            msg += bora.raster_x_qstring();
                        }else
                        {
                            msg += "(NULL)";
                        }
                        msg += "\n";
                        //------------------------------
                        msg += "X5=";
                        if(bora.anz_x() >= i+5)
                        {
                            msg += bora.raster_x_qstring();
                        }else
                        {
                            msg += "(NULL)";
                        }
                        msg += "\n";
                        //------------------------------
                        msg += "X6=";
                        if(bora.anz_x() >= i+6)
                        {
                            msg += bora.raster_x_qstring();
                        }else
                        {
                            msg += "(NULL)";
                        }
                        msg += "\n";
                        //------------------------------
                        msg += "TI=";
                        msg += bora.tiefe_qstring();
                        msg += "\n";
                        msg += "Z=";
                        msg += bora.z_qstring();
                        msg += "\n";
                        msg += "DM=";
                        msg += bora.dm_qstring();
                        msg += "\n";
                        msg += "KETTE=1\n";
                        msg += "GRP=1\n";           //Bohrgruppe
                        msg += "Y2=-1\n";
                        msg += "Y1=B\n";

                        //Anbohrtiefe gem. Voreinstellung IMAWOP
                        //Anbohrvorschub gem. Voreinstellung IMAWOP
                        //Bohrvorschub gem. Voreinstellung IMAWOP
                        //Drehzahl gem. Voreinstellung IMAWOP

                        msg += "BEZB=";
                        msg += "HBE Y- DM";
                        msg += bora.dm_qstring();
                        msg += " T";
                        msg += bora.tiefe_qstring();
                        msg += "\n";
                        msg += "AFB=";
                        msg += bora.afb();
                        msg += "\n";
                        msg += "\n";
                    }
                }
            }else
            {
                //Sollte nicht vorkommen können, da bohrraster anhand des vorhandenen Werkzeuges ermittelt werden
            }
        }else if(zeile.zeile(1) == BEARBART_NUT)
        {
            nut nu(zeile.text());
            QString bezug = nu.bezug();
            QString tnummer = wkzmag.wkznummer(WKZ_TYP_SAEGE, 0, nu.tiefe(), Dicke, bezug);
            if(!tnummer.isEmpty())
            {
                double nutblattbreite = wkzmag.saegeblattbreite(tnummer).toDouble();
                if(nu.breite() < nutblattbreite)
                {
                    //Warnung ausgeben und Nut unterdrücken:
                    QString msg = "";
                    msg += "Achtung bei fmc-Export!\n";
                    msg += "Teilname: ";
                    msg += Name;
                    msg += "\n";
                    msg += "Saegeblatt zu breit fuer ";
                    msg += bearb_menschlich_lesbar(zeile);
                    msg += "\n";
                    msg += "Bitte FMC-Programm pruefen und schmaleres Nutblatt zuweisen.";

                    QMessageBox mb;
                    mb.setText(msg);
                    mb.exec();
                }
                if(bezug == WST_BEZUG_OBSEI)
                {
                    //Bezugskante der Nut finden:
                    QString bezugskante = "0"; //Maß gibt Mittellinie der nut an
                    QString posys = nu.ys_qstring();
                    QString posye = nu.ye_qstring();
                    if(posys == posye)
                    {
                        if(nu.ys() < (tmp_b-nu.ys()))
                        {
                            posys = double_to_qstring(  nu.ys() - nu.breite()/2  );
                            posye = "SY";
                            bezugskante = "2"; //Maß gibt linke Flanke der nut an
                        }else
                        {
                            if(nu.breite() == 8.5 && nu.tiefe() == 6.5)
                            {
                                posys = "B-";
                                posys += double_to_qstring(  (tmp_b - nu.ys()) + nu.breite()/2  );
                                posye = "SY";
                                bezugskante = "2"; //Maß gibt linke Flanke der nut an
                            }else
                            {
                                posys = "B-";
                                posys += double_to_qstring(  (tmp_b - nu.ys()) - nu.breite()/2  );
                                posye = "SY";
                                bezugskante = "1"; //Maß gibt rechte Flanke der nut an
                            }
                        }
                    }

                    msg += FMC_NUT;
                    msg += "\n";
                    msg += "WKZID=";                //WKZ-Nummer
                    msg += tnummer;
                    msg += "\n";
                    msg += "SWKZID=";               //Spiegel-WKZ-Nummer
                    msg += tnummer;
                    msg += "\n";
                    msg += "WERKZEUGNAME=";         //WKZ-Nummer
                    msg += tnummer;
                    msg += "\n";
                    msg += "WKZAKTUELL=1";
                    msg += "\n";
                    msg += "SPX=";
                    //Nuten auf unserer BIMA310 müssen immer von L zu 0 verlaufen
                    //Da Agregat versetzt wenn es gedreht wird
                    if(nu.ys() == nu.ye())
                    {
                        if(nu.xs() > nu.xe())
                        {
                            msg += nu.xs_qstring();
                        }else
                        {
                            msg += nu.xe_qstring();
                        }
                    }else
                    {
                        msg += nu.xs_qstring();
                    }
                    msg += "\n";


                    msg += "SPY=";
                    msg += posys;
                    msg += "\n";
                    msg += "EPX=";
                    if(nu.ys() == nu.ye())
                    {
                        if(nu.xs() < nu.xe())
                        {
                            msg += nu.xs_qstring();
                        }else
                        {
                            msg += nu.xe_qstring();
                        }
                    }else
                    {
                         msg += nu.xe_qstring();
                    }
                    msg += "\n";
                    msg += "EPY=";
                    msg += posye;
                    msg += "\n";
                    msg += "TI=";
                    msg += nu.tiefe_qstring();
                    msg += "\n";
                    msg += "NB=";
                    msg += nu.breite_qstring();
                    msg += "\n";
                    msg += "TYPA=1\n";              //Auslauf
                    msg += "TRKOR=";                //Korrektur/Bezugskante
                    msg += bezugskante;
                    msg += "\n";
                    msg += "GEGENL=0\n";            //Genenlauf
                    msg += "TWKL=0\n";              //Neigungswinkel
                    msg += "TYPN=1\n";              //Neigungstyp
                    msg += "ABSTN=10\n";            //Abstand auf Neigung
                    msg += "Z=D/2\n";               //POs in Z

                    //Eintauchvorschub gem. Voreinstellung IMAWOP
                    //Vorschub gem. Voreinstellung IMAWOP
                    //Drehzahl gem. Voreinstellung IMAWOP

                    msg += "BEZB=";
                    msg += "Nut B";
                    msg += nu.breite_qstring();
                    msg += " T";
                    msg += nu.tiefe_qstring();
                    msg += "\n";
                    msg += FMC_BOHR_DM_AFB;
                    msg += "=";
                    msg += nu.afb();
                    msg += "\n";
                    msg += "\n";
                }
            }else
            {
                //Mit Fehlermeldung abbrechen:
                QString msg = fehler_kein_WKZ("fmc", zeile);
                QMessageBox mb;
                mb.setText(msg);
                mb.exec();
                return msg;
            }
        }else if(zeile.zeile(1) == BEARBART_RTA)
        {
            rechtecktasche rt(zeile.text());
            QString tnummer = wkzmag.wkznummer_von_alias(rt.wkznum());//Ist direkt ei WKZ definiert?
            if(tnummer.isEmpty())
            {
                QString bezug = rt.bezug();
                double minmass = 0;
                if(rt.laenge() < rt.breite())
                {
                    minmass = rt.laenge();
                }else
                {
                    minmass = breite();
                }
                tnummer = wkzmag.wkznummer(WKZ_TYP_FRAESER, minmass, rt.tiefe(), Dicke, bezug);
            }
            if(!tnummer.isEmpty())
            {
                double zustellmas = rt.zustellmass();
                if(zustellmas <= 0)
                {
                    zustellmas = wkzmag.zustellmass(tnummer).toDouble();
                }

                double tiefe = 0;
                QString tiefe_qstring;
                if(rt.tiefe() > dicke())
                {
                    tiefe = dicke() - rt.tiefe();
                    tiefe_qstring = double_to_qstring(tiefe);
                }else if(dicke()-rt.tiefe() <= 2)
                {
                    if(dicke() == rt.tiefe())
                    {
                        tiefe_qstring  = "-2";
                    }else
                    {
                        tiefe_qstring  = "D-";
                        tiefe_qstring += double_to_qstring(dicke()-rt.tiefe());
                    }
                }else
                {
                    tiefe = rt.tiefe();
                    tiefe_qstring = double_to_qstring(tiefe);
                }

                double radius = rt.rad();

                if(rt.bezug() == WST_BEZUG_OBSEI)
                {
                    msg += FMC_RTA;
                    msg += "\n";
                    msg += "WKZID=";            //Werkzeugnummer
                    msg += tnummer;
                    msg += "\n";
                    msg += "MPX=";
                    msg += rt.x_qstring();
                    msg += "\n";
                    msg += "MPY=";
                    msg += rt.y_qstring();
                    msg += "\n";
                    msg += "LGET1=";
                    msg += rt.laenge_qstring();
                    msg += "\n";
                    msg += "LGET2=";
                    msg += rt.breite_qstring();
                    msg += "\n";
                    msg += "TI=";                   //Tiefe
                    msg += tiefe_qstring;
                    msg += "\n";
                    msg += "R=";
                    msg += double_to_qstring(radius);
                    msg += "\n";
                    msg += "LGEZU=";                //Zustellmaß
                    msg += double_to_qstring(zustellmas);
                    msg += "\n";
                    msg += "GEGENL=";               //Gegenslauf
                    msg += "1";
                    msg += "\n";
                    msg += "WKL=";
                    msg += rt.drewi_qstring();
                    msg += "\n";
                    msg += "RAEUMEN=";              //Ausräumen
                    msg += rt.ausraeumen_qstring();
                    msg += "\n";
                    msg += "WKZAKTUELL=1\n";

                    //Eintauchvorschub gem. Voreinstellung IMAWOP
                    //Vorschub gem. Voreinstellung IMAWOP
                    //Drehzahl gem. Voreinstellung IMAWOP

                    msg += "BEZB=";
                    msg += "Rechtecktasche L";
                    msg += rt.laenge_qstring();
                    msg += " B";
                    msg += rt.breite_qstring();
                    msg += "\n";
                    msg += "AFB=";
                    msg += rt.afb();
                    msg += "\n";
                    msg += "\n";
                }

            }else
            {
                //Mit Fehlermeldung abbrechen:
                QString msg = fehler_kein_WKZ("fmc", zeile);
                QMessageBox mb;
                mb.setText(msg);
                mb.exec();
                return msg;
            }
        }else if(zeile.zeile(1) == BEARBART_FRAESERAUFRUF)
        {
            fraueseraufruf fa(zeile.text());
            QString tnummer = wkzmag.wkznummer_von_alias(fa.wkznum());
            if(!tnummer.isEmpty())
            {
                double gesamttiefe = fa.tiefe();
                double zustellmass = wkzmag.zustellmass(tnummer).toDouble();
                double zustelltiefe;
                if(zust_fkon == "wkz")
                {
                    if(zustellmass < gesamttiefe)
                    {
                        zustelltiefe = zustellmass;
                    }else
                    {
                        zustelltiefe = gesamttiefe;
                    }
                }else // == "orgi"
                {
                    zustelltiefe = gesamttiefe;
                }

                QString radkor = fa.radkor();
                if(radkor == FRKOR_L)
                {
                    radkor = "1";
                }else if(radkor == FRKOR_M)
                {
                    radkor = "0";
                }else if(radkor == FRKOR_R)
                {
                    radkor = "2";
                }

                if(fa.bezug() == WST_BEZUG_OBSEI)
                {
                    msg += kommentar_fmc("--------------------");

                    double backup_i = i;
                    while(1)//abbruch durch breake
                    {
                        i = backup_i;
                        double pos_z = dicke()-zustelltiefe;
                        //--------------------------------------------
                        msg += FMC_FKON;
                        msg += "\n";
                        msg += "WKZID=";            //Werkzeugnummer
                        msg += tnummer;
                        msg += "\n";
                        msg += FMC_FKON_X;
                        msg += "=";
                        msg += fa.x_qstring();
                        msg += "\n";
                        msg += FMC_FKON_Y;
                        msg += "=";
                        msg += fa.y_qstring();
                        msg += "\n";
                        msg += FMC_FKON_Z;
                        msg += "=";
                        msg += double_to_qstring(pos_z);
                        msg += "\n";
                        msg += "EBG=0\n";       //Eckenrunden global
                        msg += "KD=";           //Kantendicke
                        if(zustelltiefe == gesamttiefe)
                        {
                            msg += "0";     //Originalkontur fahren bei letztem Fräsgang in der Tiefe
                        }else
                        {
                            msg += "-0,5";  //Vorfräsung leicht versetzen
                        }
                        msg += "\n";
                        msg += FMC_FKON_KOR;    //Fräsbaohnkorrektur
                        msg += "=";
                        msg += radkor;
                        msg += "\n";

                        //Prüfen ob Eintauchpunkt des Fräsers auf oder neben dem WST liegt:
                        punkt3d pfa;//Punkt Fräseraufruf
                        pfa.set_x(fa.x());
                        pfa.set_y(fa.y());
                        text_zeilenweise folzei;//Folgezeile
                        folzei.set_trennzeichen(TRENNZ_BEARB_PARAM);
                        folzei.set_text(bearb.zeile(i+1));
                        punkt3d pein;//Eintauchpunkt
                        int anweg = 50;

                        if(folzei.zeile(1) == BEARBART_FRAESERGERADE)
                        {
                            fraesergerade fg(folzei.text());
                            strecke s;
                            s.set_start(pfa);
                            punkt3d ep = fg.ep();
                            ep.set_z(0);
                            s.set_ende(ep);
                            strecke_bezugspunkt sb;
                            sb = strecke_bezugspunkt_ende;
                            s.set_laenge_2d(s.laenge2d()+anweg, sb);
                            pein = s.stapu();
                            msg += "anfahrpunkt X = ";
                            msg += s.stapu().x_QString();
                            msg += " / Y = ";
                            msg += s.stapu().y_QString();
                            msg += "\n";
                        }else if(folzei.zeile(1) == BEARBART_FRAESERBOGEN)
                        {
                            fraeserbogen fb(folzei.text());
                            bogen b;
                            b.set_startpunkt(pfa);
                            b.set_endpunkt(fb.ep());
                            strecke s;
                            s.set_start(pfa);
                            punkt3d pmibo;
                            pmibo.set_x(b.mitte().x());
                            pmibo.set_y(b.mitte().y());
                            s.set_ende(pmibo);
                            s.drenen_um_startpunkt_2d(90, b.im_uzs());
                            strecke_bezugspunkt sb;
                            sb = strecke_bezugspunkt_start;
                            s.set_laenge_2d(anweg, sb);
                            pein = s.endpu();
                        }

                        bool aufwst = punkt_auf_wst(pein.x(), pein.y(), tmp_l, tmp_b, 1);
                        if(aufwst == true)
                        {
                            msg += "TYPAN=1\n";     //Anfahrtyp
                            msg += "TYPAB=1\n";     //Abfahrtyp
                            msg += "TYPEIN=1\n";    //Eintauchtp
                            if(pos_z > 0)
                            {
                                //Anfahranweisung für nicht durchgefräste Innen-Bahnen:
                                msg += "LGEAN=2*WKZR\n";    //Anfahrwert
                                msg += "LGEAB=2*WKZR\n";    //Abfahrwert
                            }else
                            {
                                //Anfahranweisung für durchgefräste Innen-Bahnen:
                                msg += "LGEAN=50\n";    //Anfahrwert
                                msg += "LGEAB=50\n";    //Abfahrwert
                            }
                        }else
                        {
                            //Anfahranweisung für außen-Bahnen (z.B. Formatierungen):
                            msg += "TYPAN=0\n";     //Anfahrtyp
                            msg += "TYPAB=0\n";     //Abfahrtyp
                            msg += "TYPEIN=-1\n";   //Eintauchtp
                            msg += "LGEAN=2*WKZR+";    //Anfahrwert
                            msg += double_to_qstring(anweg);
                            msg += "\n";
                            msg += "LGEAB=2*WKZR+";    //Abfahrwert
                            msg += double_to_qstring(anweg);
                            msg += "\n";
                        }
                        msg += "FAN=AUTO\n";    //Anfahrvorschub
                        msg += "F=AUTO\n";      //Vorschub
                        //msg += "N=AUTO\n";      //Drehzahl
                        msg += "EVS=0.05\n";    //Ecken-Verschleifen
                        msg += "AFB=";
                        msg += fa.afb();
                        msg += "\n";
                        msg += "WKZAKTUELL=1\n";
                        msg += "\n";
                        //--------------------------------------------
                        //Fräsbahnen:
                        while(i+1<=bearb.zeilenanzahl())
                        {
                            zeile.set_text(bearb.zeile(i+1));

                            if(zeile.zeile(1) == BEARBART_FRAESERGERADE)
                            {
                                i++;
                                zeile.set_text(bearb.zeile(i));
                                //Gerade fräsen:
                                fraesergerade fg(zeile.text());
                                QString tiefe_fg = "0";
                                if(fg.ze() == fa.tiefe())
                                {
                                    tiefe_fg = "Z"; //Tiefe beibehalten
                                                    //Führt zu falschen Ergebissen, wenn manuell geschriebene
                                                    //fmc-Programme eingelesen wurden, bei denen
                                                    //die FKONs zwischen dem Fräseraufruf und dieser Gerade
                                                    //nicht den selben Z-Wert haben!!!
                                                    //Dieser Fall wird nicht erwartet....
                                }else
                                {
                                    tiefe_fg = double_to_qstring(  dicke()-fg.ze()  );
                                }

                                msg += FMC_FKONG;
                                msg += "\n";
                                msg += FMC_FKONG_XE;
                                msg += "=";
                                msg += fg.xe_qstring();
                                msg += "\n";
                                msg += FMC_FKONG_YE;
                                msg += "=";
                                msg += fg.ye_qstring();
                                msg += "\n";
                                msg += FMC_FKONG_ZE;
                                msg += "=";
                                msg += tiefe_fg;
                                msg += "\n";
                                msg += "\n";
                            }else if(zeile.zeile(1) == BEARBART_FRAESERBOGEN)
                            {
                                i++;
                                zeile.set_text(bearb.zeile(i));
                                //Bogen fräsen:
                                fraeserbogen fb(zeile.text());
                                QString tiefe_fb = "0";
                                if(fb.ze() == fa.tiefe())
                                {
                                    tiefe_fb = "Z"; //Tiefe beibehalten
                                                    //Führt zu falschen Ergebissen, wenn manuell geschriebene
                                                    //fmc-Programme eingelesen wurden, bei denen
                                                    //die FKONs zwischen dem Fräseraufruf und dieser Gerade
                                                    //nicht den selben Z-Wert haben!!!
                                                    //Dieser Fall wird nicht erwartet....
                                }else
                                {
                                    tiefe_fb = double_to_qstring(  dicke()-fb.ze()  );
                                }
                                QString dlg_name;
                                if(fb.uzs() == true)
                                {
                                    dlg_name = FMC_FKONBOGUZS;
                                }else
                                {
                                    dlg_name = FMC_FKONBOGGUZS;
                                }

                                msg += dlg_name;
                                msg += "\n";
                                msg += FMC_FKONBOG_RAD;
                                msg += "=";
                                msg += fb.rad_qstring();
                                msg += "\n";
                                msg += FMC_FKONBOG_XE;
                                msg += "=";
                                msg += fb.xe_qstring();
                                msg += "\n";
                                msg += FMC_FKONBOG_YE;
                                msg += "=";
                                msg += fb.ye_qstring();
                                msg += "\n";
                                msg += FMC_FKONBOG_ZE;
                                msg += "=";
                                msg += tiefe_fb;
                                msg += "\n";
                                msg += "\n";
                            }else
                            {
                                break;
                            }
                        }
                        //--------------------------------------------
                        //Abfahren Fräser:
                        msg += "[KO'AB_N2]";
                        msg += "\n";
                        msg += "AFB=1";
                        msg += "\n";
                        msg += "AGGD=AGGDREHBAR";
                        msg += "\n";
                        msg += "AGGFWKL=AGGFWKL";
                        msg += "\n";
                        msg += "AGGO=AGGOFFSET";
                        msg += "\n";
                        msg += "\n";
                        //--------------------------------------------
                        if(zustelltiefe == gesamttiefe)
                        {
                            break; //letzter Schleifendurchlauf
                        }
                        if(zustelltiefe != gesamttiefe)
                        {
                            msg += kommentar_fmc("---");
                        }
                        if(zustelltiefe+zustellmass  <  gesamttiefe)
                        {
                            zustelltiefe = zustelltiefe + zustellmass;
                        }else
                        {
                            zustelltiefe = gesamttiefe;
                        }
                    }
                    msg += kommentar_fmc("--------------------");
                }

            }else
            {
                //Mit Fehlermeldung abbrechen:
                QString msg = fehler_kein_WKZ("fmc", zeile);
                QMessageBox mb;
                mb.setText(msg);
                mb.exec();
                return msg;
            }
        }
    }
    //---------------------------------------Bearbeitungen Unterseite:
    bool unterseite_hat_bearb = false;
    for(uint i=1 ; i<=bearb.zeilenanzahl() ; i++)
    {
        zeile.set_text(bearb.zeile(i));
        if(zeile.zeile(2) == WST_BEZUG_UNSEI)
        {
            unterseite_hat_bearb = true;
            break;
        }
    }
    if(unterseite_hat_bearb == true)
    {
        msg += kommentar_fmc("--------------------");
        msg += kommentar_fmc("-----------------------------------------");
        msg += FMC_HALT;
        msg += "\n";
        msg += "APX=L+700\n";
        msg += "APY=0\n";
        msg += "BEZB=Halt\n";
        msg += "AFB=1\n";
        msg += "\n";
        msg += kommentar_fmc("drehen um b/2");
        msg += kommentar_fmc("-----------------------------------------");
        msg += kommentar_fmc("--------------------");

        for(uint i=1 ; i<=bearb.zeilenanzahl() ; i++)
        {
            zeile.set_text(bearb.zeile(i));
            if(zeile.zeile(1) == BEARBART_BOHR)
            {
                bohrung bo(zeile.text());
                QString bezug = bo.bezug();
                QString tnummer = wkzmag.wkznummer(WKZ_TYP_BOHRER, bo.dm(), bo.tiefe(), Dicke, bezug);

                //Beareitung auf die Oberseite drehen:
                bo.set_y(  tmp_b - bo.y()  );

                if(!tnummer.isEmpty())
                {
                    //Werkzeug wurde gefunden, Bohrung kann gebohrt werden:
                    QString bohrgruppe = "2";
                    if(bezug == WST_BEZUG_UNSEI)
                    {
                        double tiefe;
                        if(bo.tiefe() <= dicke())
                        {
                            tiefe = bo.tiefe();
                        }else
                        {
                            tiefe = dicke() - bo.tiefe();
                        }
                        msg += FMC_BOHR_DM;
                        msg += "\n";
                        msg += FMC_BOHR_DM_X;
                        msg += "=";
                        msg += double_to_qstring(bo.x());
                        msg += "\n";
                        msg += FMC_BOHR_DM_Y;
                        msg += "=";
                        msg += double_to_qstring(bo.y());
                        msg += "\n";
                        msg += FMC_BOHR_DM_TIEFE;
                        msg += "=";
                        msg += double_to_qstring(tiefe);
                        msg += "\n";
                        msg += FMC_BOHR_DM_DM;
                        msg += "=";
                        msg += bo.dm_qstring();
                        msg += "\n";
                        msg += "GRP=";                  //Bohrgruppe
                        msg += bohrgruppe;
                        msg += "\n";

                        //Anbohrtiefe gem. Voreinstellung IMAWOP
                        //Anbohrvorschub gem. Voreinstellung IMAWOP
                        //Restbohrmaß gem. Voreinstellung IMAWOP
                        //Bohrvorschub gem. Voreinstellung IMAWOP

                        msg += "ZSM=";                  //Zustellmaß
                        msg += wkzmag.zustellmass(tnummer);
                        msg += "\n";

                        //Drehzahl gem. Voreinstellung IMAWOP

                        msg += "MRICHT=0\n";
                        msg += "TASTEIN=-1\n";
                        msg += "BEZB=";
                        msg += "Bohrung DM";
                        msg += bo.dm_qstring();
                        msg += " T";
                        msg += double_to_qstring(tiefe);
                        msg += "\n";
                        msg += FMC_BOHR_DM_AFB;
                        msg += "=";
                        msg += bo.afb();
                        msg += "\n";
                        msg += "\n";
                    }
                }else
                {
                    //Kein Werkzeug wurde gefunden.
                    //Kann Bohrung als Kreistasche gefräst werden?:
                    tnummer = wkzmag.wkznummer_von_alias(bo.wkznum());//Ist direkt ei WKZ definiert?
                    if(tnummer.isEmpty())
                    {
                        tnummer = wkzmag.wkznummer(WKZ_TYP_FRAESER, bo.dm(), bo.tiefe(), Dicke, bezug);
                    }
                    if(!tnummer.isEmpty())
                    {
                        double zustellmas = bo.zustellmass();
                        if(zustellmas <= 0)
                        {
                            zustellmas = wkzmag.zustellmass(tnummer).toDouble();
                        }

                        double tiefe = 0;
                        QString tiefe_qstring;
                        if(bo.tiefe() > dicke())
                        {
                            tiefe = dicke() - bo.tiefe();
                            tiefe_qstring = double_to_qstring(tiefe);
                        }else if(dicke()-bo.tiefe() <= 2)
                        {
                            tiefe_qstring  = "D-";
                            tiefe_qstring += double_to_qstring(dicke()-bo.tiefe());
                        }else
                        {
                            tiefe = bo.tiefe();
                            tiefe_qstring = double_to_qstring(tiefe);
                        }

                        bool ausraeumen = true;
                        if(bo.dm() > 2*wkzmag.dm(tnummer).toDouble()+20)
                        {
                            if(bo.tiefe() < 0  ||  bo.tiefe() > dicke())
                            {
                                ausraeumen = false;
                            }
                        }
                        if(bo.dm() > min_kta_dm_ausraeumen_false)
                        {
                            ausraeumen = false;
                        }

                        if(bo.bezug() == WST_BEZUG_UNSEI)
                        {
                            msg += FMC_KTA;
                            msg += "\n";
                            msg += "WKZID=";           //WKZ-Nummer
                            msg += tnummer;
                            msg += "\n";
                            msg += "MPX=";
                            msg += bo.x_qstring();
                            msg += "\n";
                            msg += "MPY=";
                            msg += bo.y_qstring();
                            msg += "\n";
                            msg += "DM=";
                            msg += bo.dm_qstring();
                            msg += "\n";
                            msg += "TI=";
                            msg += tiefe_qstring;
                            msg += "\n";
                            msg += "LGEZU=";            //Zustellmaß
                            msg += double_to_qstring(zustellmas);
                            msg += "\n";
                            msg += "GEGENL=1\n";        //Gegenlauf
                            msg += "RAEUMEN=";          //Ausräumen
                            if(ausraeumen == true)
                            {
                                msg += "1";
                            }else
                            {
                                msg += "0";
                            }
                            msg += "\n";

                            //Eintauchvorschub gem. Voreinstellung IMAWOP
                            //Vorschub gem. Voreinstellung IMAWOP
                            //Drehzahl gem. Voreinstellung IMAWOP

                            msg += "BEZB=";
                            msg += "Kreistasche DM";
                            msg += bo.dm_qstring();
                            msg += " T";
                            msg += tiefe_qstring;
                            msg += "\n";
                            msg += "AFB=";
                            msg += bo.afb();
                            msg += "\n";
                            msg += "WKZAKTUELL=1\n";
                            msg += "\n";
                        }

                    }else
                    {
                        //Mit Fehlermeldung abbrechen:
                        QString msg = "";
                        msg += "Fehler bei Export ganx!\n";
                        msg += "Teilname: ";
                        msg += Name;
                        msg += "\n";
                        msg += "Kein Werkzeug fuer:\n";
                        msg += zeile.text();

                        QMessageBox mb;
                        mb.setText(msg);
                        mb.exec();
                        return msg;
                    }
                }
            }else if(zeile.zeile(1) == BEARBART_BOHRRASTER)
            {
                bohrraster bora(zeile.text());
                QString bezug = bora.bezug();
                QString tnummer = wkzmag.wkznummer(WKZ_TYP_BOHRER, bora.dm(), bora.tiefe(), Dicke, bezug);

                //Beareitung auf die Oberseite drehen:
                bora.set_y(  tmp_b - bora.y()  );
                bora.set_raster_y( -1 * bora.raster_y() );

                if(!tnummer.isEmpty())
                {
                    //Werkzeug wurde gefunden, Bohrung kann gebohrt werden:
                    QString bohrgruppe = "2";
                    if(bezug == WST_BEZUG_UNSEI)
                    {
                        double tiefe;
                        if(bora.tiefe() <= dicke())
                        {
                            tiefe = bora.tiefe();
                        }else
                        {
                            tiefe = dicke() - bora.tiefe();
                        }

                        //Lochreihen ausgeben
                        if(bora.anz_y() == 1)
                        {
                            //Lochreihen oder Bohrbild in X?:
                            if(bora.raster_x() == 32  &&  bora.dm() == 5)
                            {
                                //Lochreihe:
                                msg += FMC_LORAE;
                                msg += "\n";
                                //---------------------------------
                                msg += FMC_LORAE_AFB;       //Aufruf Lochreihendialog
                                msg += bora.afb();
                                msg += "\n";
                                //---------------------------------
                                msg += FMC_LORAE_BEZ;       //Bezeichnung
                                msg += "=";
                                msg += "Lochreihe DM";
                                msg += bora.dm_qstring();
                                msg += " T";
                                msg += double_to_qstring(tiefe);
                                msg += "\n";
                                //---------------------------------
                                msg += FMC_LORAE_DM;        //Durchmesser
                                msg += "=";
                                msg += bora.dm_qstring();
                                msg += "\n";
                                //---------------------------------
                                msg += FMC_LORAE_XS;        //Startpunkt in X
                                msg += "=";
                                msg += bora.x_qstring();
                                msg += "\n";
                                //---------------------------------
                                msg += FMC_LORAE_XE;        //Endpunkt in X
                                msg += "=";
                                msg += double_to_qstring(bora.x() + (bora.anz_x()*(bora.raster_x()-1))  );
                                msg += "+0.5";              //Sonst ist es zu genau und es wird ggf 1 Bohrung zu wenig gebohrt
                                msg += "\n";
                                //---------------------------------
                                msg += "EPY";
                                msg += "=";
                                msg += "Y1";                //gerade verlaufende Lochreihe von 0 bis L
                                msg += "\n";
                                //---------------------------------
                                msg += FMC_LORAE_Y1;
                                msg += "=";
                                msg += bora.y_qstring();
                                msg += "\n";
                                //---------------------------------
                                msg += FMC_LORAE_Y2;
                                msg += "=";
                                msg += "(NULL)";
                                msg += "\n";
                                //---------------------------------
                                msg += "F";                 //Vorschub
                                msg += "=";
                                msg += "AUTO";
                                msg += "\n";
                                //---------------------------------
                                msg += "FAN";                 //Anfahr-Vorschub
                                msg += "=";
                                msg += "AUTO";
                                msg += "\n";
                                //---------------------------------
                                msg += "GRP";               //Bohrgruppe
                                msg += "=";
                                msg += bohrgruppe;
                                msg += "\n";
                                //---------------------------------
                                msg += "LGEAB";             //Restbohrmaß
                                msg += "=";
                                msg += "4";
                                msg += "\n";
                                //---------------------------------
                                msg += "LGEAN";             //Anbohrtiefe
                                msg += "=";
                                msg += "4";
                                msg += "\n";
                                //---------------------------------
                                msg += "MITTE";             //Vermitteln  0|1|2
                                msg += "=";
                                msg += "0";
                                msg += "\n";
                                //---------------------------------
                                msg += "MRICHT";            //Messen Seite
                                msg += "=";
                                msg += "0";
                                msg += "\n";
                                //---------------------------------
                                msg += "N";                 //Drehzahl
                                msg += "=";
                                msg += "AUTO";
                                msg += "\n";
                                //---------------------------------
                                msg += FMC_LORAE_RASTER;
                                msg += "=";
                                msg += bora.raster_x_qstring();
                                msg += "\n";
                                //---------------------------------
                                msg += "TASTEIN";
                                msg += "=";
                                msg += "-1";
                                msg += "\n";
                                //---------------------------------
                                msg += FMC_LORAE_TI;
                                msg += "=";
                                msg += double_to_qstring(tiefe);
                                msg += "\n";
                                //---------------------------------
                                msg += "ZSM";           //Zustellmaß
                                msg += "=";
                                //msg += bora.zustellmass_qstring();
                                msg += wkzmag.zustellmass(tnummer);
                                msg += "\n";
                                //---------------------------------
                                msg += "\n";
                            }else
                            {
                                //Bohrbild in X:
                                //max 6 Bohrungen pro Dialog!
                                for(uint i=0 ; i<bora.anz_x() ; i=i+6)
                                {
                                    msg += FMC_BOBIX;
                                    msg += "\n";
                                    //------------------------------
                                    msg += FMC_BOBIX_AFB;
                                    msg += "=";
                                    msg += bora.afb();
                                    msg += "\n";
                                    //------------------------------
                                    msg += "BEZB";
                                    msg += "=";
                                    msg += "Bohren in X  DM";
                                    msg += bora.dm_qstring();
                                    msg += " T";
                                    msg += double_to_qstring(tiefe);
                                    msg += "\n";
                                    //------------------------------
                                    msg += FMC_BOBIX_DM;
                                    msg += "=";
                                    msg += bora.dm_qstring();
                                    msg += "\n";
                                    //------------------------------
                                    msg += "F";                     //Vorschub
                                    msg += "=";
                                    msg += "AUTO";
                                    msg += "\n";
                                    //------------------------------
                                    msg += "FAN";                   //Anfahrvorschub
                                    msg += "=";
                                    msg += "AUTO";
                                    msg += "\n";
                                    //------------------------------
                                    msg += "GRP";                   //Bohrgruppe
                                    msg += "=";
                                    msg += bohrgruppe;
                                    msg += "\n";
                                    //------------------------------
                                    msg += FMC_BOBIX_KM;            //Kettenmaß
                                    msg += "=";
                                    msg += "1";
                                    msg += "\n";
                                    //------------------------------
                                    msg += "LGEAB";                 //Restbohrmaß
                                    msg += "=";
                                    msg += "4";
                                    msg += "\n";
                                    //------------------------------
                                    msg += "LGEAN";                 //Anbohrtiefe
                                    msg += "=";
                                    msg += "4";
                                    msg += "\n";
                                    //------------------------------
                                    msg += "MRICHT";                //Messen Seite
                                    msg += "=";
                                    msg += "0";
                                    msg += "\n";
                                    //------------------------------
                                    msg += "N";                     //Drehzahl
                                    msg += "=";
                                    msg += "AUTO";
                                    msg += "\n";
                                    //------------------------------
                                    msg += "TASTEIN";               //Taste Satz ein
                                    msg += "=";
                                    msg += "-1";
                                    msg += "\n";
                                    //------------------------------
                                    msg += FMC_BOBIX_TI;            //Tiefe
                                    msg += "=";
                                    msg += double_to_qstring(tiefe);
                                    msg += "\n";
                                    //------------------------------
                                    msg += FMC_BOBIX_X1;
                                    msg += "=";
                                    msg += double_to_qstring(  bora.x() + (i*bora.raster_x())  );
                                    msg += "\n";
                                    //------------------------------
                                    msg += FMC_BOBIX_X2;
                                    msg += "=";
                                    if(bora.anz_x() >= i+2)
                                    {
                                        msg += bora.raster_x_qstring();
                                    }else
                                    {
                                        msg += "(NULL)";
                                    }
                                    msg += "\n";
                                    //------------------------------
                                    msg += FMC_BOBIX_X3;
                                    msg += "=";
                                    if(bora.anz_x() >= i+3)
                                    {
                                        msg += bora.raster_x_qstring();
                                    }else
                                    {
                                        msg += "(NULL)";
                                    }
                                    msg += "\n";
                                    //------------------------------
                                    msg += FMC_BOBIX_X4;
                                    msg += "=";
                                    if(bora.anz_x() >= i+4)
                                    {
                                        msg += bora.raster_x_qstring();
                                    }else
                                    {
                                        msg += "(NULL)";
                                    }
                                    msg += "\n";
                                    //------------------------------
                                    msg += FMC_BOBIX_X5;
                                    msg += "=";
                                    if(bora.anz_x() >= i+5)
                                    {
                                        msg += bora.raster_x_qstring();
                                    }else
                                    {
                                        msg += "(NULL)";
                                    }
                                    msg += "\n";
                                    //------------------------------
                                    msg += FMC_BOBIX_X6;
                                    msg += "=";
                                    if(bora.anz_x() >= i+6)
                                    {
                                        msg += bora.raster_x_qstring();
                                    }else
                                    {
                                        msg += "(NULL)";
                                    }
                                    msg += "\n";
                                    //------------------------------
                                    msg += FMC_BOBIX_Y1;
                                    msg += "=";
                                    msg += bora.y_qstring();
                                    msg += "\n";
                                    //------------------------------
                                    msg += FMC_BOBIX_Y2;
                                    msg += "=";
                                    msg += "-1";
                                    msg += "\n";
                                    //------------------------------
                                    msg += "ZSM";           //Zustellmaß
                                    msg += "=";
                                    //msg += bora.zustellmass_qstring();
                                    msg += wkzmag.zustellmass(tnummer);
                                    msg += "\n";
                                    //------------------------------
                                    msg += "\n";
                                }
                            }
                        }else if(bora.anz_x() == 1)
                        {
                            //Bohrbild in Y:
                            //max 6 Bohrungen pro Dialog!
                            for(uint i=0 ; i<bora.anz_y() ; i=i+6)
                            {
                                msg += FMC_BOBIY;
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIX_AFB;
                                msg += "=";
                                msg += bora.afb();
                                msg += "\n";
                                //------------------------------
                                msg += "BEZB";
                                msg += "=";
                                msg += "Bohren in Y  DM";
                                msg += bora.dm_qstring();
                                msg += " T";
                                msg += double_to_qstring(tiefe);
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIX_DM;
                                msg += "=";
                                msg += bora.dm_qstring();
                                msg += "\n";
                                //------------------------------
                                msg += "F";                     //Vorschub
                                msg += "=";
                                msg += "AUTO";
                                msg += "\n";
                                //------------------------------
                                msg += "FAN";                   //Anfahrvorschub
                                msg += "=";
                                msg += "AUTO";
                                msg += "\n";
                                //------------------------------
                                msg += "GRP";                   //Bohrgruppe
                                msg += "=";
                                msg += bohrgruppe;
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIY_KM;            //Kettenmaß
                                msg += "=";
                                msg += "1";
                                msg += "\n";
                                //------------------------------
                                msg += "LGEAB";                 //Restbohrmaß
                                msg += "=";
                                msg += "4";
                                msg += "\n";
                                //------------------------------
                                msg += "LGEAN";                 //Anbohrtiefe
                                msg += "=";
                                msg += "4";
                                msg += "\n";
                                //------------------------------
                                msg += "MRICHT";                //Messen Seite
                                msg += "=";
                                msg += "0";
                                msg += "\n";
                                //------------------------------
                                msg += "N";                     //Drehzahl
                                msg += "=";
                                msg += "AUTO";
                                msg += "\n";
                                //------------------------------
                                msg += "TASTEIN";               //Taste Satz ein
                                msg += "=";
                                msg += "-1";
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIY_TI;            //Tiefe
                                msg += "=";
                                msg += double_to_qstring(tiefe);
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIY_Y1;
                                msg += "=";
                                msg += double_to_qstring(  bora.y() + (i*bora.raster_y())  );
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIY_Y2;
                                msg += "=";
                                if(bora.anz_y() >= i+2)
                                {
                                    msg += bora.raster_y_qstring();
                                }else
                                {
                                    msg += "(NULL)";
                                }
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIY_Y3;
                                msg += "=";
                                if(bora.anz_y() >= i+3)
                                {
                                    msg += bora.raster_y_qstring();
                                }else
                                {
                                    msg += "(NULL)";
                                }
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIY_Y4;
                                msg += "=";
                                if(bora.anz_y() >= i+4)
                                {
                                    msg += bora.raster_y_qstring();
                                }else
                                {
                                    msg += "(NULL)";
                                }
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIY_Y5;
                                msg += "=";
                                if(bora.anz_y() >= i+5)
                                {
                                    msg += bora.raster_y_qstring();
                                }else
                                {
                                    msg += "(NULL)";
                                }
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIY_Y6;
                                msg += "=";
                                if(bora.anz_y() >= i+6)
                                {
                                    msg += bora.raster_y_qstring();
                                }else
                                {
                                    msg += "(NULL)";
                                }
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIY_X1;
                                msg += "=";
                                msg += bora.x_qstring();
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIY_X2;
                                msg += "=";
                                msg += "-1";
                                msg += "\n";
                                //------------------------------
                                msg += "ZSM";           //Zustellmaß
                                msg += "=";
                                //msg += bora.zustellmass_qstring();
                                msg += wkzmag.zustellmass(tnummer);
                                msg += "\n";
                                //------------------------------
                                msg += "\n";
                            }
                        }else
                        {
                            //Bislang noch keine Lochrasttererkennung in X und Y gleichzeitig vorhanden
                            //desshalb Ausgabe an dieser Stellen nicht nötig
                        }
                    }
                }else
                {
                    //Sollte nicht vorkommen können, da bohrraster anhand des vorhandenen Werkzeuges ermittelt werden
                }
            }else if(zeile.zeile(1) == BEARBART_NUT)
            {
                nut nu(zeile.text());
                QString bezug = nu.bezug();
                if(bezug == WST_BEZUG_UNSEI)
                {
                    bezug = WST_BEZUG_OBSEI;
                    nu.set_bezug(WST_BEZUG_OBSEI);
                    nu.set_ys(  tmp_b - nu.ys()  );
                    nu.set_ye(  tmp_b - nu.ye()  );

                    QString tnummer = wkzmag.wkznummer(WKZ_TYP_SAEGE, 0, nu.tiefe(), Dicke, bezug);
                    if(!tnummer.isEmpty())
                    {
                        double nutblattbreite = wkzmag.saegeblattbreite(tnummer).toDouble();
                        if(nu.breite() < nutblattbreite)
                        {
                            //Warnung ausgeben und Nut unterdrücken:
                            QString msg = "";
                            msg += "Achtung bei fmc-Export!\n";
                            msg += "Teilname: ";
                            msg += Name;
                            msg += "\n";
                            msg += "Saegeblatt zu breit fuer ";
                            msg += bearb_menschlich_lesbar(zeile);
                            msg += "\n";
                            msg += "Bitte FMC-Programm pruefen und schmaleres Nutblatt zuweisen.";

                            QMessageBox mb;
                            mb.setText(msg);
                            mb.exec();
                        }

                        //Bezugskante der Nut finden:
                        QString bezugskante = "0"; //Maß gibt Mittellinie der nut an
                        QString posys = nu.ys_qstring();
                        QString posye = nu.ye_qstring();
                        if(posys == posye)
                        {
                            if(nu.ys() < (tmp_b-nu.ys()))
                            {
                                posys = double_to_qstring(  nu.ys() - nu.breite()/2  );
                                posye = "SY";
                                bezugskante = "2"; //Maß gibt linke Flanke der nut an
                            }else
                            {
                                if(nu.breite() == 8.5 && nu.tiefe() == 6.5)
                                {
                                    posys = "B-";
                                    posys += double_to_qstring(  (tmp_b - nu.ys()) + nu.breite()/2  );
                                    posye = "SY";
                                    bezugskante = "2"; //Maß gibt linke Flanke der nut an
                                }else
                                {
                                    posys = "B-";
                                    posys += double_to_qstring(  (tmp_b - nu.ys()) - nu.breite()/2  );
                                    posye = "SY";
                                    bezugskante = "1"; //Maß gibt rechte Flanke der nut an
                                }
                            }
                        }

                        msg += FMC_NUT;
                        msg += "\n";
                        msg += "WKZID=";                //WKZ-Nummer
                        msg += tnummer;
                        msg += "\n";
                        msg += "SWKZID=";               //Spiegel-WKZ-Nummer
                        msg += tnummer;
                        msg += "\n";
                        msg += "WERKZEUGNAME=";         //WKZ-Nummer
                        msg += tnummer;
                        msg += "\n";
                        msg += "WKZAKTUELL=1";
                        msg += "\n";
                        msg += "SPX=";
                        //Nuten auf unserer BIMA310 müssen immer von L zu 0 verlaufen
                        //Da Agregat versetzt wenn es gedreht wird
                        if(nu.ys() == nu.ye())
                        {
                            if(nu.xs() > nu.xe())
                            {
                                msg += nu.xs_qstring();
                            }else
                            {
                                msg += nu.xe_qstring();
                            }
                        }else
                        {
                            msg += nu.xs_qstring();
                        }
                        msg += "\n";
                        msg += "SPY=";
                        msg += posys;
                        msg += "\n";
                        msg += "EPX=";
                        if(nu.ys() == nu.ye())
                        {
                            if(nu.xs() < nu.xe())
                            {
                                msg += nu.xs_qstring();
                            }else
                            {
                                msg += nu.xe_qstring();
                            }
                        }else
                        {
                             msg += nu.xe_qstring();
                        }
                        msg += "\n";
                        msg += "EPY=";
                        msg += posye;
                        msg += "\n";
                        msg += "TI=";
                        msg += nu.tiefe_qstring();
                        msg += "\n";
                        msg += "NB=";
                        msg += nu.breite_qstring();
                        msg += "\n";
                        msg += "TYPA=1\n";              //Auslauf
                        msg += "TRKOR=";                //Korrektur/Bezugskante
                        msg += bezugskante;
                        msg += "\n";
                        msg += "GEGENL=0\n";            //Genenlauf
                        msg += "TWKL=0\n";              //Neigungswinkel
                        msg += "TYPN=1\n";              //Neigungstyp
                        msg += "ABSTN=10\n";            //Abstand auf Neigung
                        msg += "Z=D/2\n";               //Pos in Z

                        //Eintauchvorschub gem. Voreinstellung IMAWOP
                        //Vorschub gem. Voreinstellung IMAWOP
                        //Drehzahl gem. Voreinstellung IMAWOP

                        msg += "BEZB=";
                        msg += "Nut B";
                        msg += nu.breite_qstring();
                        msg += " T";
                        msg += nu.tiefe_qstring();
                        msg += "\n";
                        msg += FMC_BOHR_DM_AFB;
                        msg += "=";
                        msg += nu.afb();
                        msg += "\n";
                        msg += "\n";
                    }else
                    {
                        //Mit Fehlermeldung abbrechen:
                        QString msg = fehler_kein_WKZ("fmc", zeile);
                        QMessageBox mb;
                        mb.setText(msg);
                        mb.exec();
                        return msg;
                    }
                }
            }else if(zeile.zeile(1) == BEARBART_RTA)
            {
                rechtecktasche rt(zeile.text());
                QString tnummer = wkzmag.wkznummer_von_alias(rt.wkznum());//Ist direkt ei WKZ definiert?
                if(tnummer.isEmpty())
                {
                    QString bezug = rt.bezug();
                    double minmass = 0;
                    if(rt.laenge() < rt.breite())
                    {
                        minmass = rt.laenge();
                    }else
                    {
                        minmass = breite();
                    }
                    tnummer = wkzmag.wkznummer(WKZ_TYP_FRAESER, minmass, rt.tiefe(), Dicke, bezug);
                }
                //Beareitung auf die Oberseite drehen:
                rt.set_y(  tmp_b - rt.y()  );
                rt.set_drewi(  180 - rt.drewi()  );

                if(!tnummer.isEmpty())
                {
                    double zustellmas = rt.zustellmass();
                    if(zustellmas <= 0)
                    {
                        zustellmas = wkzmag.zustellmass(tnummer).toDouble();
                    }

                    double tiefe = 0;
                    QString tiefe_qstring;
                    if(rt.tiefe() > dicke())
                    {
                        tiefe = dicke() - rt.tiefe();
                        tiefe_qstring = double_to_qstring(tiefe);
                    }else if(dicke()-rt.tiefe() <= 2)
                    {
                        if(dicke() == rt.tiefe())
                        {
                            tiefe_qstring  = "-2";
                        }else
                        {
                            tiefe_qstring  = "D-";
                            tiefe_qstring += double_to_qstring(dicke()-rt.tiefe());
                        }
                    }else
                    {
                        tiefe = rt.tiefe();
                        tiefe_qstring = double_to_qstring(tiefe);
                    }

                    double radius = rt.rad();

                    if(rt.bezug() == WST_BEZUG_UNSEI)
                    {
                        msg += FMC_RTA;
                        msg += "\n";
                        msg += "WKZID=";            //Werkzeugnummer
                        msg += tnummer;
                        msg += "\n";
                        msg += "MPX=";
                        msg += rt.x_qstring();
                        msg += "\n";
                        msg += "MPY=";
                        msg += rt.y_qstring();
                        msg += "\n";
                        msg += "LGET1=";
                        msg += rt.laenge_qstring();
                        msg += "\n";
                        msg += "LGET2=";
                        msg += rt.breite_qstring();
                        msg += "\n";
                        msg += "TI=";                   //Tiefe
                        msg += tiefe_qstring;
                        msg += "\n";
                        msg += "R=";
                        msg += double_to_qstring(radius);
                        msg += "\n";
                        msg += "LGEZU=";                //Zustellmaß
                        msg += double_to_qstring(zustellmas);
                        msg += "\n";
                        msg += "GEGENL=";               //Gegenslauf
                        msg += "1";
                        msg += "\n";
                        msg += "WKL=";
                        msg += rt.drewi_qstring();
                        msg += "\n";
                        msg += "RAEUMEN=";              //Ausräumen
                        msg += rt.ausraeumen_qstring();
                        msg += "\n";
                        msg += "WKZAKTUELL=1\n";

                        //Eintauchvorschub gem. Voreinstellung IMAWOP
                        //Vorschub gem. Voreinstellung IMAWOP
                        //Drehzahl gem. Voreinstellung IMAWOP

                        msg += "BEZB=";
                        msg += "Rechtecktasche L";
                        msg += rt.laenge_qstring();
                        msg += " B";
                        msg += rt.breite_qstring();
                        msg += "\n";
                        msg += "AFB=";
                        msg += rt.afb();
                        msg += "\n";
                        msg += "\n";
                    }

                }else
                {
                    //Mit Fehlermeldung abbrechen:
                    QString msg = fehler_kein_WKZ("fmc", zeile);
                    QMessageBox mb;
                    mb.setText(msg);
                    mb.exec();
                    return msg;
                }
            }else if(zeile.zeile(1) == BEARBART_FRAESERAUFRUF)
            {
                fraueseraufruf fa(zeile.text());
                QString tnummer = wkzmag.wkznummer_von_alias(fa.wkznum());
                if(!tnummer.isEmpty())
                {
                    //Beareitung auf die Oberseite drehen:
                    fa.set_y(  tmp_b - fa.y()  );

                    double gesamttiefe = fa.tiefe();
                    double zustellmass = wkzmag.zustellmass(tnummer).toDouble();
                    double zustelltiefe;
                    if(zust_fkon == "wkz")
                    {
                        if(zustellmass < gesamttiefe)
                        {
                            zustelltiefe = zustellmass;
                        }else
                        {
                            zustelltiefe = gesamttiefe;
                        }
                    }else // == "orgi"
                    {
                        zustelltiefe = gesamttiefe;
                    }

                    QString radkor = fa.radkor();
                    if(radkor == FRKOR_L)
                    {
                        radkor = "1";
                    }else if(radkor == FRKOR_M)
                    {
                        radkor = "0";
                    }else if(radkor == FRKOR_R)
                    {
                        radkor = "2";
                    }

                    if(fa.bezug() == WST_BEZUG_UNSEI)
                    {
                        msg += kommentar_fmc("--------------------");

                        double backup_i = i;
                        while(1)//abbruch durch breake
                        {
                            i = backup_i;
                            double pos_z = dicke()-zustelltiefe;
                            //--------------------------------------------
                            msg += FMC_FKON;
                            msg += "\n";
                            msg += "WKZID=";            //Werkzeugnummer
                            msg += tnummer;
                            msg += "\n";
                            msg += FMC_FKON_X;
                            msg += "=";
                            msg += fa.x_qstring();
                            msg += "\n";
                            msg += FMC_FKON_Y;
                            msg += "=";
                            msg += fa.y_qstring();
                            msg += "\n";
                            msg += FMC_FKON_Z;
                            msg += "=";
                            msg += double_to_qstring(pos_z);
                            msg += "\n";
                            msg += "EBG=0\n";       //Eckenrunden global
                            msg += "KD=";           //Kantendicke
                            if(zustelltiefe == gesamttiefe)
                            {
                                msg += "0";     //Originalkontur fahren bei letztem Fräsgang in der Tiefe
                            }else
                            {
                                msg += "-0,5";  //Vorfräsung leicht versetzen
                            }
                            msg += "\n";
                            msg += FMC_FKON_KOR;    //Fräsbaohnkorrektur
                            msg += "=";
                            msg += radkor;
                            msg += "\n";

                            //Prüfen ob Eintauchpunkt des Fräsers auf oder neben dem WST liegt:
                            punkt3d pfa;//Punkt Fräseraufruf
                            pfa.set_x(fa.x());
                            pfa.set_y(fa.y());
                            text_zeilenweise folzei;//Folgezeile
                            folzei.set_trennzeichen(TRENNZ_BEARB_PARAM);
                            folzei.set_text(bearb.zeile(i+1));
                            punkt3d pein;//Eintauchpunkt
                            int anweg = 50;

                            if(folzei.zeile(1) == BEARBART_FRAESERGERADE)
                            {
                                fraesergerade fg(folzei.text());
                                //Beareitung auf die Oberseite drehen:
                                fg.set_ys(  tmp_b - fg.ys()  );
                                fg.set_ye(  tmp_b - fg.ye()  );
                                //-------
                                strecke s;
                                s.set_start(pfa);
                                punkt3d ep = fg.ep();
                                ep.set_z(0);
                                s.set_ende(ep);
                                strecke_bezugspunkt sb;
                                sb = strecke_bezugspunkt_ende;
                                s.set_laenge_2d(s.laenge2d()+anweg, sb);
                                pein = s.stapu();
                            }else if(folzei.zeile(1) == BEARBART_FRAESERBOGEN)
                            {
                                fraeserbogen fb(folzei.text());
                                //Beareitung auf die Oberseite drehen:
                                fb.set_ys(  tmp_b - fb.ys()  );
                                fb.set_ye(  tmp_b - fb.ye()  );
                                //---------
                                bogen b;
                                b.set_startpunkt(pfa);
                                b.set_endpunkt(fb.ep());
                                strecke s;
                                s.set_start(pfa);
                                punkt3d pmibo;
                                pmibo.set_x(b.mitte().x());
                                pmibo.set_y(b.mitte().y());
                                s.set_ende(pmibo);
                                s.drenen_um_startpunkt_2d(90, b.im_uzs());
                                strecke_bezugspunkt sb;
                                sb = strecke_bezugspunkt_start;
                                s.set_laenge_2d(anweg, sb);
                                pein = s.endpu();
                            }

                            bool aufwst = punkt_auf_wst(pein.x(), pein.y(), tmp_l, tmp_b, 1);
                            if(aufwst == true)
                            {
                                msg += "TYPAN=1\n";     //Anfahrtyp
                                msg += "TYPAB=1\n";     //Abfahrtyp
                                msg += "TYPEIN=1\n";    //Eintauchtp
                                if(pos_z > 0)
                                {
                                    //Anfahranweisung für nicht durchgefräste Innen-Bahnen:
                                    msg += "LGEAN=2*WKZR\n";    //Anfahrwert
                                    msg += "LGEAB=2*WKZR\n";    //Abfahrwert
                                }else
                                {
                                    //Anfahranweisung für durchgefräste Innen-Bahnen:
                                    msg += "LGEAN=50\n";    //Anfahrwert
                                    msg += "LGEAB=50\n";    //Abfahrwert
                                }
                            }else
                            {
                                //Anfahranweisung für außen-Bahnen (z.B. Formatierungen):
                                msg += "TYPAN=0\n";     //Anfahrtyp
                                msg += "TYPAB=0\n";     //Abfahrtyp
                                msg += "TYPEIN=-1\n";   //Eintauchtp
                                msg += "LGEAN=2*WKZR+";    //Anfahrwert
                                msg += double_to_qstring(anweg);
                                msg += "\n";
                                msg += "LGEAB=2*WKZR+";    //Abfahrwert
                                msg += double_to_qstring(anweg);
                                msg += "\n";
                            }
                            msg += "FAN=AUTO\n";    //Anfahrvorschub
                            msg += "F=AUTO\n";      //Vorschub
                            //msg += "N=AUTO\n";      //Drehzahl
                            msg += "EVS=0.05\n";    //Ecken-Verschleifen
                            msg += "AFB=";
                            msg += fa.afb();
                            msg += "\n";
                            msg += "WKZAKTUELL=1\n";
                            msg += "\n";
                            //--------------------------------------------
                            //Fräsbahnen:
                            while(i+1<=bearb.zeilenanzahl())
                            {
                                zeile.set_text(bearb.zeile(i+1));

                                if(zeile.zeile(1) == BEARBART_FRAESERGERADE)
                                {
                                    i++;
                                    zeile.set_text(bearb.zeile(i));
                                    //Gerade fräsen:
                                    fraesergerade fg(zeile.text());
                                    QString tiefe_fg = 0;
                                    if(fg.ze() == fa.tiefe())
                                    {
                                        tiefe_fg = "Z"; //Tiefe beibehalten
                                                        //Führt zu falschen Ergebissen, wenn manuell geschriebene
                                                        //fmc-Programme eingelesen wurden, bei denen
                                                        //die FKONs zwischen dem Fräseraufruf und dieser Gerade
                                                        //nicht den selben Z-Wert haben!!!
                                                        //Dieser Fall wird nicht erwartet....
                                    }else
                                    {
                                        tiefe_fg = double_to_qstring(  dicke()-fg.ze()  );
                                    }

                                    //Beareitung auf die Oberseite drehen:
                                    fg.set_ys(  tmp_b - fg.ys()  );
                                    fg.set_ye(  tmp_b - fg.ye()  );

                                    msg += FMC_FKONG;
                                    msg += "\n";
                                    msg += FMC_FKONG_XE;
                                    msg += "=";
                                    msg += fg.xe_qstring();
                                    msg += "\n";
                                    msg += FMC_FKONG_YE;
                                    msg += "=";
                                    msg += fg.ye_qstring();
                                    msg += "\n";
                                    msg += FMC_FKONG_ZE;
                                    msg += "=";
                                    msg += tiefe_fg;
                                    msg += "\n";
                                    msg += "\n";
                                }else if(zeile.zeile(1) == BEARBART_FRAESERBOGEN)
                                {
                                    i++;
                                    zeile.set_text(bearb.zeile(i));
                                    //Bogen fräsen:
                                    fraeserbogen fb(zeile.text());
                                    QString tiefe_fb = 0;
                                    if(fb.ze() == fa.tiefe())
                                    {
                                        tiefe_fb = "Z"; //Tiefe beibehalten
                                                        //Führt zu falschen Ergebissen, wenn manuell geschriebene
                                                        //fmc-Programme eingelesen wurden, bei denen
                                                        //die FKONs zwischen dem Fräseraufruf und dieser Gerade
                                                        //nicht den selben Z-Wert haben!!!
                                                        //Dieser Fall wird nicht erwartet....
                                    }else
                                    {
                                        tiefe_fb = double_to_qstring(  dicke()-fb.ze()  );
                                    }
                                    QString dlg_name;
                                    if(fb.uzs() == true)
                                    {
                                        dlg_name = FMC_FKONBOGUZS;
                                    }else
                                    {
                                        dlg_name = FMC_FKONBOGGUZS;
                                    }

                                    //Beareitung auf die Oberseite drehen:
                                    fb.set_ys(  tmp_b - fb.ys()  );
                                    fb.set_ye(  tmp_b - fb.ye()  );

                                    msg += dlg_name;
                                    msg += "\n";
                                    msg += FMC_FKONBOG_RAD;
                                    msg += "=";
                                    msg += fb.rad_qstring();
                                    msg += "\n";
                                    msg += FMC_FKONBOG_XE;
                                    msg += "=";
                                    msg += fb.xe_qstring();
                                    msg += "\n";
                                    msg += FMC_FKONBOG_YE;
                                    msg += "=";
                                    msg += fb.ye_qstring();
                                    msg += "\n";
                                    msg += FMC_FKONBOG_ZE;
                                    msg += "=";
                                    msg += tiefe_fb;
                                    msg += "\n";
                                    msg += "\n";
                                }else
                                {
                                    break;
                                }
                            }
                            //--------------------------------------------
                            //Abfahren Fräser:
                            msg += "[KO'AB_N2]";
                            msg += "\n";
                            msg += "AFB=1";
                            msg += "\n";
                            msg += "AGGD=AGGDREHBAR";
                            msg += "\n";
                            msg += "AGGFWKL=AGGFWKL";
                            msg += "\n";
                            msg += "AGGO=AGGOFFSET";
                            msg += "\n";
                            msg += "\n";
                            //--------------------------------------------
                            if(zustelltiefe == gesamttiefe)
                            {
                                break; //letzter Schleifendurchlauf
                            }
                            if(zustelltiefe != gesamttiefe)
                            {
                                msg += kommentar_fmc("---");
                            }
                            if(zustelltiefe+zustellmass  <  gesamttiefe)
                            {
                                zustelltiefe = zustelltiefe + zustellmass;
                            }else
                            {
                                zustelltiefe = gesamttiefe;
                            }
                        }
                        msg += kommentar_fmc("--------------------");
                    }

                }else
                {
                    //Mit Fehlermeldung abbrechen:
                    QString msg = fehler_kein_WKZ("fmc", zeile);
                    QMessageBox mb;
                    mb.setText(msg);
                    mb.exec();
                    return msg;
                }
            }
        }
    }

    //---------------------------------------Programmende:
    msg += FMC_ENDE;
    msg += "\n";
    msg += "AFB=1\n";
    msg += "PP=2\n";                //Parkposition
    msg += "BEZB=Programm-Ende";

    return msg;
}
QString werkstueck::ganx_dateitext(text_zeilenweise wkzmagazin, text_zeilenweise bearb, \
                                       double tmp_l, double tmp_b)
{
    bearb = dubosplitten(bearb, wkzmagazin, dicke());
    bearb = rasterbohrungen_finden_ganx(bearb, wkzmagazin, tmp_l, tmp_b);
    QString msg;
    text_zeilenweise zeile;
    zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
    double bezugsmass = 40;    //Referenzmaß zum Erkennen der Bezugskante
    werkzeugmagazin wkzmag(wkzmagazin);

    //-------------------------1.Vorspann:
    {
    msg  = "<?xml version=\"1.0\" standalone=\"yes\"?>";
    msg += "\n";
    msg += "<Programm xmlns=\"http://tempuri.org/Programm.xsd\">";
    msg += "\n";
    }
    //-------------------------Programmkopf:
    {
    msg += "  <PrgrSet>";
    msg += "\n";
    msg += "    <PrgrName>";
    msg += Name;
    msg += "</PrgrName>";
    msg += "\n";
    msg += "    <Description>";
    msg += "";                       //Kommentar
    msg += "</Description>";
    msg += "\n";
    msg += "    <wsX>";
    msg += double_to_qstring(tmp_l);
    msg += "</wsX>";
    msg += "\n";
    msg += "    <wsY>";
    msg += double_to_qstring(tmp_b);
    msg += "</wsY>";
    msg += "\n";
    msg += "    <wsZ>";
    msg += dicke_qstring();
    msg += "</wsZ>";
    msg += "\n";
    msg += "    <DoMF>";
    msg += "False";          //Maxifix
    msg += "</DoMF>";
    msg += "\n";
    msg += "    <MFPos>";
    msg += "0";              //Position Maxitix
    msg += "</MFPos>";
    msg += "\n";
    msg += "    <MFTool>";
    msg += "TO";             //Werkzeug für Maxifix
    msg += "</MFTool>";
    msg += "\n";
    msg += "  </PrgrSet>";
    msg += "\n";
    }
    //-------------------------2. Vorspann:
    {
    msg += "  <Root>";
    msg += "\n";
    msg += "    <Version>1.1.0.26</Version>";
    msg += "\n";
    msg += "    <CreationDate>2017-06-02T09:26:14.9442359+02:00</CreationDate>";
    msg += "\n";
    msg += "    <CreationApp>ASCII Import - 1.1.0.26</CreationApp>";
    msg += "\n";
    msg += "    <ModificationApp />";
    msg += "\n";
    msg += "  </Root>";
    msg += "\n";
    }
    //-------------------------Bearbeitungen <PrgrFileWork>:
    //Dies ist der Teil, den die Maschinen-Steuerung liest
    //Hier darf nur mit absoluten Zahlen gearbeitet werden
    //Die Ausgabe von Formeln wird von der Maschinen-steuerung nicht unterstützt
    uint id = 1; //id für die Maschiene
    uint ideditor = 1;//id die im Editor angezeigt wird
    ganx_Gruppen gruppen_PrgrFileWork;

    for(uint i=1 ; i<=bearb.zeilenanzahl() ; i++)
    {
        zeile.set_text(bearb.zeile(i));
        if(zeile.zeile(1) == BEARBART_BOHR)
        {
            bohrung bo(zeile.text());

            QString afb_text = bo.afb();
            afb_text.replace("L", laenge_qstring());
            afb_text.replace("B", breite_qstring());
            afb_text.replace("D", dicke_qstring());
            afb_text.replace(",", ".");
            afb_text = ausdruck_auswerten(afb_text);
            if(afb_text.toDouble() == 0)
            {
                continue;
            }

            double x = bo.x();
            double y = bo.y();
            double z = bo.z();
            double dm = bo.dm();
            double laenge_y = tmp_b;
            QString bezug = bo.bezug();

            //Y-Maß bezieht sich hier immer auf den Nullpunkt der Wst oben links
            //die Maße intern beziehen sich immer auf Nullpunkt unten links
            //das heißt, die Y-Maße müssen an dieser Stelle gegengerechnet werden:
            y = tmp_b - y;

            QString tnummer = wkzmag.wkznummer(WKZ_TYP_BOHRER, dm, bo.tiefe(), Dicke, bezug);
            if(!tnummer.isEmpty())
            {
                //Werkzeug wurde gefunden, Bohrung kann gebohrt werden:

                //Anzahl der Zustellungen berechnen:
                double zustmass = bo.zustellmass();
                if(zustmass <= 0)
                {
                    zustmass = wkzmag.zustellmass(tnummer).toDouble();
                }
                int zustellungen = aufrunden(bo.tiefe() / zustmass);
                if(zustellungen <= 0)
                {
                    zustellungen = 1;
                }
                zustmass = bo.tiefe()/zustellungen;
                //-------------------------------

                if(bezug == WST_BEZUG_OBSEI)
                {
                    //x = Breite
                    //y = Länge
                    //z = Tiefe
                    double aktti; //aktuelle Tiefe
                    aktti = zustmass;
                    while(aktti <= bo.tiefe())
                    {
                        msg += "  <PrgrFileWork>";
                        msg += "\n";
                        msg += "    <CntID>";
                        msg += int_to_qstring(id);               //ID-Nummer
                        msg += "</CntID>";
                        msg += "\n";
                        msg += "    <Plane>Top</Plane>";
                        msg += "\n";
                        //----------------------Bezugskante festlegen:
                        msg += "    <Ref>";
                        //y < 40 -> TL
                        //Länge - y < 40 ->BL
                        QString ref;
                        if(laenge_y - y < bezugsmass)
                        {
                            ref += GANX_REF_OBEN_LINKS;
                        }else
                        {
                            ref += GANX_REF_UNTEN_LINKS;
                        }
                        msg += ref;
                        msg += "</Ref>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Typ>B</Typ>";
                        msg += "\n";
                        //----------------------
                        msg += "    <X>";
                        msg += double_to_qstring(x);
                        msg += "</X>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Y>";
                        msg += double_to_qstring(y);
                        msg += "</Y>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Z>";
                        msg += double_to_qstring(0);
                        msg += "</Z>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Diameter>";
                        msg += wkzmag.dm(tnummer);
                        msg += "</Diameter>";
                        msg += "\n";
                        //----------------------
                        msg += "   <Depth>";
                        msg += double_to_qstring(aktti);
                        msg += "</Depth>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Tool>";
                        msg += tnummer;
                        msg += "</Tool>";
                        msg += "\n";
                        //----------------------
                        msg += "    <OldID>";
                        msg += GANX_WST_BEZUG_OBSEI;
                        msg += "\\";
                        msg += ref;
                        msg += "\\";
                        msg += "B-";
                        msg += int_to_qstring(ideditor);               //ID-Nummer
                        msg += "</OldID>";
                        msg += "\n";
                        //----------------------
                        msg += "    <KleiGeTei>";    //Zustelltiefe
                        msg += double_to_qstring(zustmass);
                        msg += "</KleiGeTei>";
                        msg += "\n";
                        //----------------------
                        msg += "  </PrgrFileWork>";
                        msg += "\n";

                        id++;
                        aktti = aktti + zustmass;
                    }
                    ideditor++;


                }else if(bezug == WST_BEZUG_UNSEI)
                {
                    //x = Breite
                    //y = Länge
                    //z = Tiefe
                    double aktti; //aktuelle Tiefe
                    aktti = zustmass;
                    while(aktti <= bo.tiefe())
                    {
                        msg += "  <PrgrFileWork>";
                        msg += "\n";
                        msg += "    <CntID>";
                        msg += int_to_qstring(id);               //ID-Nummer
                        msg += "</CntID>";
                        msg += "\n";
                        msg += "    <Plane>Bottom</Plane>";
                        msg += "\n";
                        //----------------------Bezugskante festlegen:
                        msg += "    <Ref>";
                        //y < 40 -> TL
                        //Länge - y < 40 ->BL
                        QString ref;
                        if(laenge_y - y < bezugsmass)
                        {
                            ref = GANX_REF_OBEN_LINKS;
                        }else
                        {
                            ref = GANX_REF_UNTEN_LINKS;
                        }
                        msg += ref;
                        msg += "</Ref>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Typ>B</Typ>";
                        msg += "\n";
                        //----------------------
                        msg += "    <X>";
                        msg += double_to_qstring(x);
                        msg += "</X>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Y>";
                        msg += double_to_qstring(y);
                        msg += "</Y>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Z>";
                        msg += double_to_qstring(0);
                        msg += "</Z>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Diameter>";
                        msg += wkzmag.dm(tnummer);
                        msg += "</Diameter>";
                        msg += "\n";
                        //----------------------
                        msg += "   <Depth>";
                        msg += double_to_qstring(aktti);
                        msg += "</Depth>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Tool>";
                        msg += tnummer;
                        msg += "</Tool>";
                        msg += "\n";
                        //----------------------
                        msg += "    <OldID>";
                        msg += GANX_WST_BEZUG_UNSEI;
                        msg += "\\";
                        msg += ref;
                        msg += "\\";
                        msg += "B-";
                        msg += int_to_qstring(ideditor);               //ID-Nummer
                        msg += "</OldID>";
                        msg += "\n";
                        //----------------------
                        msg += "    <KleiGeTei>";    //Zustelltiefe
                        msg += double_to_qstring(zustmass);
                        msg += "</KleiGeTei>";
                        msg += "\n";
                        //----------------------
                        msg += "  </PrgrFileWork>";
                        msg += "\n";

                        id++;
                        aktti = aktti + zustmass;
                    }
                    ideditor++;

                }else if(bezug == WST_BEZUG_LI)
                {
                    //x = Tiefe
                    //y = Y-Pos
                    //z = Z-Pos
                    double aktti; //aktuelle Tiefe
                    aktti = zustmass;
                    while(aktti <= bo.tiefe())
                    {
                        msg += "  <PrgrFileWork>";
                        msg += "\n";
                        msg += "    <CntID>";
                        msg += int_to_qstring(id);               //ID-Nummer
                        msg += "</CntID>";
                        msg += "\n";
                        msg += "    <Plane>Left</Plane>";
                        msg += "\n";
                        //----------------------Bezugskante festlegen:
                        msg += "    <Ref>";
                        QString ref = GANX_REF_UNTEN_LINKS;
                        msg += ref;
                        msg += "</Ref>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Typ>B</Typ>";
                        msg += "\n";
                        //----------------------
                        msg += "    <X>";
                        msg += double_to_qstring(0);
                        msg += "</X>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Y>";
                        msg += double_to_qstring(y);
                        msg += "</Y>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Z>";
                        msg += double_to_qstring(z);
                        msg += "</Z>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Diameter>";
                        msg += wkzmag.dm(tnummer);
                        msg += "</Diameter>";
                        msg += "\n";
                        //----------------------
                        msg += "   <Depth>";
                        msg += double_to_qstring(aktti);
                        msg += "</Depth>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Tool>";
                        msg += tnummer;
                        msg += "</Tool>";
                        msg += "\n";
                        //----------------------
                        msg += "    <OldID>";
                        msg += GANX_WST_BEZUG_LI;
                        msg += "\\";
                        msg += ref;
                        msg += "\\";
                        msg += "B-";
                        msg += int_to_qstring(ideditor);               //ID-Nummer
                        msg += "</OldID>";
                        msg += "\n";
                        //----------------------
                        msg += "    <KleiGeTei>";    //Zustelltiefe
                        msg += double_to_qstring(zustmass);
                        msg += "</KleiGeTei>";
                        msg += "\n";
                        //----------------------
                        msg += "  </PrgrFileWork>";
                        msg += "\n";

                        id++;
                        aktti = aktti + zustmass;
                    }
                    ideditor++;

                }else if(bezug == WST_BEZUG_RE)
                {
                    //x = Tiefe
                    //y = Y-Pos
                    //z = Z-Pos
                    double aktti; //aktuelle Tiefe
                    aktti = zustmass;
                    while(aktti <= bo.tiefe())
                    {
                        msg += "  <PrgrFileWork>";
                        msg += "\n";
                        msg += "    <CntID>";
                        msg += int_to_qstring(id);               //ID-Nummer
                        msg += "</CntID>";
                        msg += "\n";
                        msg += "    <Plane>Right</Plane>";
                        msg += "\n";
                        //----------------------Bezugskante festlegen:
                        msg += "    <Ref>";
                        QString ref = GANX_REF_UNTEN_RECHTS;
                        msg += ref;
                        msg += "</Ref>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Typ>B</Typ>";
                        msg += "\n";
                        //----------------------
                        msg += "    <X>";
                        msg += double_to_qstring(0);
                        msg += "</X>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Y>";
                        msg += double_to_qstring(y);
                        msg += "</Y>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Z>";
                        msg += double_to_qstring(z);
                        msg += "</Z>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Diameter>";
                        msg += wkzmag.dm(tnummer);
                        msg += "</Diameter>";
                        msg += "\n";
                        //----------------------
                        msg += "   <Depth>";
                        msg += double_to_qstring(aktti);
                        msg += "</Depth>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Tool>";
                        msg += tnummer;
                        msg += "</Tool>";
                        msg += "\n";
                        //----------------------
                        msg += "    <OldID>";
                        msg += GANX_WST_BEZUG_RE;
                        msg += "\\";
                        msg += ref;
                        msg += "\\";
                        msg += "B-";
                        msg += int_to_qstring(ideditor);               //ID-Nummer
                        msg += "</OldID>";
                        msg += "\n";
                        //----------------------
                        msg += "    <KleiGeTei>";    //Zustelltiefe
                        msg += double_to_qstring(zustmass);
                        msg += "</KleiGeTei>";
                        msg += "\n";
                        //----------------------
                        msg += "  </PrgrFileWork>";
                        msg += "\n";

                        id++;
                        aktti = aktti + zustmass;
                    }
                    ideditor++;

                }else if(bezug == WST_BEZUG_VO)
                {
                    //x = X-Pos
                    //y = Tiefe
                    //z = Z-Pos
                    double aktti; //aktuelle Tiefe
                    aktti = zustmass;
                    while(aktti <= bo.tiefe())
                    {
                        msg += "  <PrgrFileWork>";
                        msg += "\n";
                        msg += "    <CntID>";
                        msg += int_to_qstring(id);               //ID-Nummer
                        msg += "</CntID>";
                        msg += "\n";
                        msg += "    <Plane>Front</Plane>";
                        msg += "\n";
                        //----------------------Bezugskante festlegen:
                        msg += "    <Ref>";
                        QString ref = GANX_REF_UNTEN_LINKS;
                        msg += ref;
                        msg += "</Ref>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Typ>B</Typ>";
                        msg += "\n";
                        //----------------------
                        msg += "    <X>";
                        msg += double_to_qstring(x);
                        msg += "</X>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Y>";
                        msg += double_to_qstring(0);
                        msg += "</Y>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Z>";
                        msg += double_to_qstring(z);
                        msg += "</Z>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Diameter>";
                        msg += wkzmag.dm(tnummer);
                        msg += "</Diameter>";
                        msg += "\n";
                        //----------------------
                        msg += "   <Depth>";
                        msg += double_to_qstring(aktti);
                        msg += "</Depth>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Tool>";
                        msg += tnummer;
                        msg += "</Tool>";
                        msg += "\n";
                        //----------------------
                        msg += "    <OldID>";
                        msg += GANX_WST_BEZUG_VO;
                        msg += "\\";
                        msg += ref;
                        msg += "\\";
                        msg += "B-";
                        msg += int_to_qstring(ideditor);               //ID-Nummer
                        msg += "</OldID>";
                        msg += "\n";
                        //----------------------
                        msg += "    <KleiGeTei>";    //Zustelltiefe
                        msg += double_to_qstring(zustmass);
                        msg += "</KleiGeTei>";
                        msg += "\n";
                        //----------------------
                        msg += "  </PrgrFileWork>";
                        msg += "\n";

                        id++;
                        aktti = aktti + zustmass;
                    }
                    ideditor++;

                }else if(bezug == WST_BEZUG_HI)
                {
                    //x = X-Pos
                    //y = Tiefe
                    //z = Z-Pos
                    double aktti; //aktuelle Tiefe
                    aktti = zustmass;
                    while(aktti <= bo.tiefe())
                    {
                        msg += "  <PrgrFileWork>";
                        msg += "\n";
                        msg += "    <CntID>";
                        msg += int_to_qstring(id);               //ID-Nummer
                        msg += "</CntID>";
                        msg += "\n";
                        msg += "    <Plane>Rear</Plane>";
                        msg += "\n";
                        //----------------------Bezugskante festlegen:
                        msg += "    <Ref>";
                        QString ref = GANX_REF_OBEN_LINKS;
                        msg += ref;
                        msg += "</Ref>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Typ>B</Typ>";
                        msg += "\n";
                        //----------------------
                        msg += "    <X>";
                        msg += double_to_qstring(x);
                        msg += "</X>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Y>";
                        msg += double_to_qstring(0);
                        msg += "</Y>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Z>";
                        msg += double_to_qstring(z);
                        msg += "</Z>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Diameter>";
                        msg += wkzmag.dm(tnummer);
                        msg += "</Diameter>";
                        msg += "\n";
                        //----------------------
                        msg += "   <Depth>";
                        msg += double_to_qstring(aktti);
                        msg += "</Depth>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Tool>";
                        msg += tnummer;
                        msg += "</Tool>";
                        msg += "\n";
                        //----------------------
                        msg += "    <OldID>";
                        msg += GANX_WST_BEZUG_HI;
                        msg += "\\";
                        msg += ref;
                        msg += "\\";
                        msg += "B-";
                        msg += int_to_qstring(ideditor);               //ID-Nummer
                        msg += "</OldID>";
                        msg += "\n";
                        //----------------------
                        msg += "    <KleiGeTei>";    //Zustelltiefe
                        msg += double_to_qstring(zustmass);
                        msg += "</KleiGeTei>";
                        msg += "\n";
                        //----------------------
                        msg += "  </PrgrFileWork>";
                        msg += "\n";

                        id++;
                        aktti = aktti + zustmass;
                    }
                    ideditor++;

                }

            }else
            {
                //Kein Werkzeug wurde gefunden.
                //Kann Bohrung als Kreistasche gefräst werden?:
                tnummer = wkzmag.wkznummer_von_alias(bo.wkznum());//Ist direkt ei WKZ definiert?
                if(tnummer.isEmpty())
                {
                    tnummer = wkzmag.wkznummer(WKZ_TYP_FRAESER, dm, bo.tiefe(), Dicke, bezug);
                }

                if(!tnummer.isEmpty())
                {
                    //Werkzeug wurde gefunden, Kreistasche kann gefräst werden:

                    QString ti = bo.tiefe_qstring();
                    /*
                     * Formeln sind nicht zulässig:
                    if(ti.toDouble() > dicke())
                    {
                        QString tmp = "{LZ}+";
                        double dif = ti.toDouble() - dicke();
                        tmp += double_to_qstring(dif);
                        ti = tmp;
                    }
                    */
                    //Anzahl der Zustellungen berechnen:
                    double zustmass = bo.zustellmass();
                    if(zustmass <= 0)
                    {
                        zustmass = wkzmag.zustellmass(tnummer).toDouble();
                    }
                    int zustellungen = aufrunden(bo.tiefe() / zustmass);

                    if(zustellungen <= 0)
                    {
                        zustellungen = 1;
                    }


                    msg += "  <PrgrFileWork>";
                    msg += "\n";
                    //----------------------
                    msg += "    <CntID>";
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</CntID>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Plane>";
                    if(bo.bezug() == WST_BEZUG_OBSEI)
                    {
                        msg += GANX_WST_BEZUG_OBSEI;
                    }else
                    {
                        msg += GANX_WST_BEZUG_UNSEI;
                    }
                    msg += "</Plane>";
                    msg += "\n";
                    //----------------------Bezugskante festlegen:
                    QString ref;
                    if(laenge_y - y < bezugsmass)
                    {
                        ref = GANX_REF_OBEN_LINKS;
                    }else
                    {
                        ref = GANX_REF_UNTEN_LINKS;
                    }
                    msg += "    <Ref>";
                    msg += ref;
                    msg += "</Ref>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Typ>M</Typ>";
                    msg += "\n";
                    //----------------------
                    msg += "    <X>";
                    msg += double_to_qstring(x);
                    msg += "</X>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Y>";
                    msg += double_to_qstring(y);
                    msg += "</Y>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Z>";
                    msg += double_to_qstring(0);
                    msg += "</Z>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Tool>";
                    msg += tnummer;
                    msg += "</Tool>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Mill>";
                    msg += "2";                      //Kreistasche
                    msg += ";";
                    msg += double_to_qstring(dm);
                    msg += ";";
                    msg += ti;                       //TaTi
                    msg += ";";
                    msg += "2";                      //Variante der Kreistasche (2 = ausgeräumt)
                    msg += ";";
                    msg += "GL";                     //Gleichlauf (GL = Gleichlauf / GG = Gegenlauf)
                    msg += ";";
                    msg += wkzmag.vorschub(tnummer);
                    msg += ";";
                    msg += int_to_qstring(zustellungen);
                    msg += "</Mill>";
                    msg += "\n";
                    //----------------------
                    msg += "    <ImageKey>KR</ImageKey>";
                    msg += "\n";
                    //----------------------
                    msg += "    <OldID>";
                    if(bo.bezug() == WST_BEZUG_OBSEI)
                    {
                        msg += GANX_WST_BEZUG_OBSEI;
                    }else
                    {
                        msg += GANX_WST_BEZUG_UNSEI;
                    }
                    msg += "\\";
                    msg += GANX_REF_OBEN_LINKS;
                    msg += "\\";
                    msg += "M-";
                    msg += int_to_qstring(ideditor);               //ID-Nummer
                    msg += "</OldID>";
                    msg += "\n";
                    //----------------------
                    msg += "    <KleiGeTei>";
                    msg += "0";
                    msg += "</KleiGeTei>";
                    msg += "\n";
                    //----------------------
                    msg += "  </PrgrFileWork>";
                    msg += "\n";

                    id++;
                    ideditor++;

                }else
                {
                    QString msg = fehler_kein_WKZ("ganx", zeile);
                    QMessageBox mb;
                    mb.setText(msg);
                    mb.exec();
                    return msg;
                }
            }
        }else if(zeile.zeile(1) == BEARBART_BOHRRASTER)
        {
            bohrraster bora(zeile.text());
            double x = bora.x();
            double y = bora.y();
            //double z = bora.z();
            double dm = bora.dm();
            double laenge_y = tmp_b;
            QString bezug = bora.bezug();

            //Y-Maß bezieht sich hier immer auf den Nullpunkt der Wst oben links
            //die Maße intern beziehen sich immer auf Nullpunkt unten links
            //das heißt, die Y-Maße müssen an dieser Stelle gegengerechnet werden:
            y = tmp_b - y;

            QString tnummer = wkzmag.wkznummer(WKZ_TYP_BOHRER, dm, bora.tiefe(), Dicke, bezug);
            if(!tnummer.isEmpty())
            {
                //Anzahl der Zustellungen berechnen:
                double zustmass = bora.zustellmass();
                if(zustmass <= 0)
                {
                    zustmass = wkzmag.zustellmass(tnummer).toDouble();
                }
                int zustellungen = aufrunden(bora.tiefe() / zustmass);
                if(zustellungen <= 0)
                {
                    zustellungen = 1;
                }
                zustmass = bora.tiefe()/zustellungen;
                //-------------------------------

                if(bezug == WST_BEZUG_OBSEI  ||  bezug == WST_BEZUG_UNSEI)
                {
                    for(uint i=1; i<=bora.anz_y() ;i++)
                    {
                        y = tmp_b - (  bora.y()+(bora.raster_y()*(i-1))  );

                        for(uint ii=1; ii<=bora.anz_x() ;ii++)
                        {
                            x = bora.x()+(bora.raster_x()*(ii-1));
                            //x = Breite
                            //y = Länge
                            //z = Tiefe
                            double aktti; //aktuelle Tiefe
                            aktti = zustmass;
                            while(aktti <= bora.tiefe())
                            {
                                msg += "  <PrgrFileWork>";
                                msg += "\n";
                                //----------------------
                                msg += "    <CntID>";
                                msg += int_to_qstring(id);               //ID-Nummer
                                msg += "</CntID>";
                                msg += "\n";
                                //----------------------
                                msg += "    <Plane>";
                                if(bezug == WST_BEZUG_OBSEI)
                                {
                                    msg += GANX_WST_BEZUG_OBSEI;
                                }else
                                {
                                    msg += GANX_WST_BEZUG_UNSEI;
                                }
                                msg += "</Plane>";
                                msg += "\n";
                                //----------------------
                                msg += "    <Ref>";
                                QString ref;
                                if(  laenge_y - y < bezugsmass  &&  bora.anz_y()==1  )
                                {
                                    ref += GANX_REF_OBEN_LINKS;
                                }else
                                {
                                    ref += GANX_REF_UNTEN_LINKS;
                                }
                                msg += ref;
                                msg += "</Ref>";
                                msg += "\n";
                                //----------------------
                                msg += "    <Typ>B</Typ>";
                                msg += "\n";
                                //----------------------
                                msg += "    <X>";
                                msg += double_to_qstring(x);
                                msg += "</X>";
                                msg += "\n";
                                //----------------------
                                msg += "    <Y>";
                                msg += double_to_qstring(y);
                                msg += "</Y>";
                                msg += "\n";
                                //----------------------
                                msg += "    <Z>";
                                msg += double_to_qstring(0);
                                msg += "</Z>";
                                msg += "\n";
                                //----------------------
                                msg += "    <Diameter>";
                                msg += wkzmag.dm(tnummer);
                                msg +="</Diameter>";
                                msg += "\n";
                                //----------------------
                                msg += "    <Depth>";
                                msg += double_to_qstring(aktti);
                                msg += "</Depth>";
                                msg += "\n";
                                //----------------------
                                msg += "    <DblB>false</DblB>";
                                msg += "\n";
                                //----------------------
                                msg += "    <DblL>false</DblL>";
                                msg += "\n";
                                //----------------------
                                msg += "    <DblE>false</DblE>";
                                msg += "\n";
                                //----------------------
                                msg += "    <Tool>";
                                msg += tnummer;
                                msg += "</Tool>";
                                msg += "\n";
                                //----------------------
                                msg += "    <ImageKey>BR</ImageKey>";
                                msg += "\n";
                                //----------------------
                                msg += "    <OldID>";
                                if(bezug == WST_BEZUG_OBSEI)
                                {
                                    msg += GANX_WST_BEZUG_OBSEI;
                                }else
                                {
                                    msg += GANX_WST_BEZUG_UNSEI;
                                }
                                msg += "\\";
                                msg += ref;
                                msg += "\\";
                                msg += "BR-";
                                msg += int_to_qstring(ideditor);               //ID-Nummer
                                msg += "</OldID>";
                                msg += "\n";
                                //----------------------
                                msg += "    <KleiGeTei>";    //Zustelltiefe
                                msg += double_to_qstring(zustmass);
                                msg += "</KleiGeTei>";
                                msg += "\n";
                                //----------------------
                                msg += "    <Clause />";
                                msg += "\n";
                                //----------------------
                                msg += "    <iClauseState>0</iClauseState>";
                                msg += "\n";
                                //----------------------
                                msg += "  </PrgrFileWork>";
                                msg += "\n";
                                //----------------------

                                id++;
                                aktti = aktti + zustmass;
                            }
                        }
                    }
                    ideditor++;
                }
            }else
            {
                //Sollte nicht vorkommen können, da bohrraster anhand des vorhandenen Werkzeuges ermittelt werden
            }
        }else if(zeile.zeile(1)==BEARBART_NUT)
        {

            nut nu(zeile.text());
            if(nu.xs() != nu.xe())
            {
                //Warnung ausgeben und Nut unterdrücken:
                QString msg = "";
                msg += "Achtung bei ganx-Export!\n";
                msg += "Teilname: ";
                msg += Name;
                msg += "\n";
                msg += "Nut ist nicht parallel zur X-Achse:\n";
                msg += bearb_menschlich_lesbar(zeile);
                msg += "\n";
                msg += "Bearbeitung wird unterdrueckt.";

                QMessageBox mb;
                mb.setText(msg);
                mb.exec();
                continue;
            }
            double x = nu.xs();
            double y;
            double z = nu.tiefe(); //Tiefe
            double l = 0;
            //Nutlänge berechnen:
            if(nu.ys() < nu.ye())
            {
                l = nu.ye() - nu.ys();
                y = nu.ys();
            }else
            {
                l = nu.ys() - nu.ye();
                y = nu.ye();
            }
            y = tmp_b - y;
            y = y-l;
            QString tnummer = wkzmag.wkznummer(WKZ_TYP_SAEGE);
            if(tnummer.isEmpty())
            {
                QString msg = fehler_kein_WKZ("ganx", zeile);
                QMessageBox mb;
                mb.setText(msg);
                mb.exec();
                return msg;
            }
            double wkz_dm = wkzmag.dm(tnummer).toDouble();

            QString nutvariante_qstring = "Var2";
            //"Var1" = Nuttiefe wird beim Startmaß und Endmaß erreicht
            //"Var2" = Nut beginnt beim Startmaß und endet am Endmaß

            QString nutrichtung = "Y";
            //Mögliche Werte:
            //"X" = Nut von links nach rechts = entlang der Y-Achse
            //"Y" = Nut von vorne nach hinten = entlang der X-Achse

            double nutblattbreite = wkzmag.saegeblattbreite(tnummer).toDouble();

            if(nu.breite() < nutblattbreite)
            {
                //Warnung ausgeben und Nut unterdrücken:
                QString msg = "";
                msg += "Achtung bei ganx-Export!\n";
                msg += "Teilname: ";
                msg += Name;
                msg += "\n";
                msg += "Saegeblatt zu breit fuer ";
                msg += bearb_menschlich_lesbar(zeile);
                msg += "\n";
                msg += "Bearbeitung wird unterdrueckt.";

                QMessageBox mb;
                mb.setText(msg);
                mb.exec();
                continue;
            }else if(nu.breite() == nutblattbreite)
            {
                msg += "  <PrgrFileWork>";
                msg += "\n";
                //----------------------
                msg += "    <CntID>";
                msg += int_to_qstring(id);               //ID-Nummer
                msg += "</CntID>";
                msg += "\n";
                //----------------------
                msg += "    <Plane>";
                if(nu.bezug() == WST_BEZUG_OBSEI)
                {
                    msg += GANX_WST_BEZUG_OBSEI;
                }else
                {
                    msg += GANX_WST_BEZUG_UNSEI;
                }
                msg += "</Plane>";
                msg += "\n";
                //----------------------
                msg += "    <Ref>";
                msg += GANX_REF_OBEN_LINKS;
                msg += "</Ref>";
                msg += "\n";
                //----------------------
                msg += "    <Typ>S</Typ>";
                msg += "\n";
                //----------------------
                msg += "    <X>";
                msg += double_to_qstring(x);
                msg += "</X>";
                msg += "\n";
                //----------------------
                msg += "    <Y>";
                msg += double_to_qstring(y);
                msg += "</Y>";
                msg += "\n";
                //----------------------
                msg += "    <Z>";
                msg += double_to_qstring(0);
                msg += "</Z>";
                msg += "\n";
                //----------------------
                msg += "    <Diameter>";
                msg += double_to_qstring(wkz_dm);
                msg += "</Diameter>";
                msg += "\n";
                //----------------------
                msg += "    <Depth>";
                msg += double_to_qstring(z);
                msg += "</Depth>";
                msg += "\n";
                //----------------------
                msg += "    <Tool>";
                msg += tnummer;
                msg += "</Tool>";
                msg += "\n";
                //----------------------
                msg += "    <SVar>";
                msg += nutvariante_qstring;
                msg += "</SVar>";
                msg += "\n";
                //----------------------
                msg += "    <SParallel>";
                msg += nutrichtung;
                msg += "</SParallel>";
                msg += "\n";
                //----------------------
                msg += "    <SGrooveLength>";
                msg += double_to_qstring(l);
                msg += "</SGrooveLength>";
                msg += "\n";
                //----------------------
                msg += "    <OldID>";
                if(nu.bezug() == WST_BEZUG_OBSEI)
                {
                    msg += GANX_WST_BEZUG_OBSEI;
                }else
                {
                    msg += GANX_WST_BEZUG_UNSEI;
                }
                msg += "\\";
                msg += GANX_REF_OBEN_LINKS;
                msg += "\\";
                msg += "S-";
                msg += int_to_qstring(ideditor);               //ID-Nummer
                msg += "</OldID>";
                msg += "\n";
                //----------------------
                msg += "    <KleiGeTei>";
                msg += "0";
                msg += "</KleiGeTei>";
                msg += "\n";
                //----------------------
                msg += "  </PrgrFileWork>";
                msg += "\n";

                id++;
                ideditor++;

            }else if(nu.breite() > nutblattbreite)
            {
                //Wir müssen mehrere Nuten fahren Nuten
                uint anz_nuten = aufrunden(nu.breite() / nutblattbreite);
                double x = nu.xs();

                for(uint ii=1; ii<=anz_nuten ;ii++)
                {
                    //Beispiel:
                    //Nutbreite = 8,5
                    //blattbreite = 5
                    //Anzahl Nuten = 2
                    //x-Versatz  Nut:
                    //8,5/2 - 5/2 = 1,75
                    //Versatz = +-1,75

                    double versatz = nu.breite()/2 - nutblattbreite/2 ;

                    if(ii == 1)
                    {
                        x = x - versatz;

                    }else if(ii==anz_nuten)
                    {
                        x = nu.xs();
                        x = x + versatz;
                    }else
                    {
                        double schleifenversatz;
                        schleifenversatz = nutblattbreite - ((nutblattbreite*anz_nuten)-nu.breite()) /(anz_nuten-1);
                        x = nu.xs() - versatz + (ii-1)*schleifenversatz;
                    }

                    msg += "  <PrgrFileWork>";
                    msg += "\n";
                    //----------------------
                    msg += "    <CntID>";
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</CntID>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Plane>";
                    if(nu.bezug() == WST_BEZUG_OBSEI)
                    {
                        msg += GANX_WST_BEZUG_OBSEI;
                    }else
                    {
                        msg += GANX_WST_BEZUG_UNSEI;
                    }
                    msg += "</Plane>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Ref>";
                    msg += GANX_REF_OBEN_LINKS;
                    msg += "</Ref>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Typ>S</Typ>";
                    msg += "\n";
                    //----------------------
                    msg += "    <X>";
                    msg += double_to_qstring(x);
                    msg += "</X>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Y>";
                    msg += double_to_qstring(y);
                    msg += "</Y>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Z>";
                    msg += double_to_qstring(0);
                    msg += "</Z>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Diameter>";
                    msg += double_to_qstring(wkz_dm);
                    msg += "</Diameter>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Depth>";
                    msg += double_to_qstring(z);
                    msg += "</Depth>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Tool>";
                    msg += tnummer;
                    msg += "</Tool>";
                    msg += "\n";
                    //----------------------
                    msg += "    <SVar>";
                    msg += nutvariante_qstring;
                    msg += "</SVar>";
                    msg += "\n";
                    //----------------------
                    msg += "    <SParallel>";
                    msg += nutrichtung;
                    msg += "</SParallel>";
                    msg += "\n";
                    //----------------------
                    msg += "    <SGrooveLength>";
                    msg += double_to_qstring(l);
                    msg += "</SGrooveLength>";
                    msg += "\n";
                    //----------------------
                    msg += "    <OldID>";
                    if(nu.bezug() == WST_BEZUG_OBSEI)
                    {
                        msg += GANX_WST_BEZUG_OBSEI;
                    }else
                    {
                        msg += GANX_WST_BEZUG_UNSEI;
                    }
                    msg += "\\";
                    msg += GANX_REF_OBEN_LINKS;
                    msg += "\\";
                    msg += "S-";
                    msg += int_to_qstring(ideditor);               //ID-Nummer
                    msg += "</OldID>";
                    msg += "\n";
                    //----------------------
                    msg += "    <KleiGeTei>";
                    msg += "0";
                    msg += "</KleiGeTei>";
                    msg += "\n";
                    //----------------------
                    msg += "  </PrgrFileWork>";
                    msg += "\n";

                    id++;
                    ideditor++;

                }
            }


        }else if(zeile.zeile(1)==BEARBART_RTA)
        {
            rechtecktasche rt(zeile.text());
            double x = rt.x();
            double y = rt.y();

            bool ausraeumen = true;
            if(rt.tiefe() == dicke())
            {
                rt.set_tiefe(dicke()+2);
            }
            if(rt.tiefe() >= Dicke  || \
               rt.tiefe() <  0 )
            {
                ausraeumen = true;
            }else
            {
                if(rt.ausraeumen() == false)
                {
                    ausraeumen = false;
                }else
                {
                    ausraeumen = true;
                }
            }

            //Y-Maß bezieht sich hier immer auf den Nullpunkt der Wst oben links
            //die Maße intern beziehen sich immer auf Nullpunkt unten links
            //das heißt, die Y-Maße müssen an dieser Stelle gegengerechnet werden:
            y = tmp_b - y;

            //double z = rt.z();
            QString ti = rt.tiefe_qstring();
            /*
             * Formeln sind nicht zulässig:
            if(ti.toDouble() > dicke())
            {
                QString tmp = "{LZ}+";
                double dif = ti.toDouble() - dicke();
                tmp += double_to_qstring(dif);
                ti = tmp;
            }
            */
            double lx = 0;
            double by = 0;
            if(rt.drewi() == 0 || rt.drewi() == 180)
            {
                lx = rt.laenge();
                by = rt.breite();
            }else if(rt.drewi() == 90 || rt.drewi() == 270)
            {
                lx = rt.breite();
                by = rt.laenge();
            }else
            {
                //Warnung ausgeben und RTA unterdrücken:
                QString msg = "";
                msg += "Achtung bei Export ganx!\n";
                msg += "Teilname: ";
                msg += Name;
                msg += "\n";
                msg += "Drehwinkel der Rechtecktasche wird nicht unterstuetzt:\n";
                msg += zeile.text();
                msg += "\n";
                msg += "Bearbeitung wird unterdrueckt.";

                QMessageBox mb;
                mb.setText(msg);
                mb.exec();
                continue;
            }
            double laenge_y = tmp_b;
            double minmass = lx;
            if(by < minmass)
            {
                minmass = by;
            }

            QString tnummer = wkzmag.wkznummer_von_alias(rt.wkznum());//Ist direkt ei WKZ definiert?
            if(tnummer.isEmpty())
            {
                 tnummer = wkzmag.wkznummer(WKZ_TYP_FRAESER, minmass, rt.tiefe(), Dicke, rt.bezug());
            }

            if(tnummer.isEmpty())
            {
                QString msg = fehler_kein_WKZ("ganx", zeile);
                QMessageBox mb;
                mb.setText(msg);
                mb.exec();
                return msg;
            }
            double wkz_dm = wkzmag.dm(tnummer).toDouble();
            double eckenradius = rt.rad();
            if(eckenradius < wkz_dm/2)
            {
                eckenradius = wkz_dm/2;
            }
            double wkz_vorschub = wkzmag.vorschub(tnummer).toDouble();
            //Anzahl der Zustellungen berechnen:
            double zustmass = rt.zustellmass();
            if(zustmass <= 0)
            {
                zustmass = wkzmag.zustellmass(tnummer).toDouble();
            }
            int zustellungen = aufrunden(rt.tiefe() / zustmass);

            if(zustellungen <= 0)
            {
                zustellungen = 1;
            }

            if(zustellungen > 1)
            {
                if(rt.bezug() == WST_BEZUG_OBSEI)
                {
                    gruppen_PrgrFileWork.neue_gruppe(GANX_WST_BEZUG_OBSEI);
                }else
                {
                    gruppen_PrgrFileWork.neue_gruppe(GANX_WST_BEZUG_UNSEI);
                }
                if(wkz_dm > by-2  ||  wkz_dm > lx-2)//by==TAB  lx==TAL
                {
                    QString msg = fehler_kein_WKZ("ganx", zeile);
                    msg += "\n";
                    msg += "Anzahl der Zustellungen: ";
                    msg += double_to_qstring(zustellungen);
                    QMessageBox mb;
                    mb.setText(msg);
                    mb.exec();
                    return msg;
                }
            }

            for(uint ii=1 ; ii<=zustellungen ;ii++)
            {
                //----------------------------------------------
                msg += "  <PrgrFileWork>";
                msg += "\n";
                //----------------------
                msg += "    <CntID>";
                msg += int_to_qstring(id);               //ID-Nummer
                msg += "</CntID>";
                msg += "\n";
                //----------------------
                msg += "    <Plane>";
                if(rt.bezug() == WST_BEZUG_OBSEI)
                {
                    msg += GANX_WST_BEZUG_OBSEI;
                }else
                {
                    msg += GANX_WST_BEZUG_UNSEI;
                }
                msg += "</Plane>";
                msg += "\n";
                //----------------------Bezugskante festlegen:
                QString ref;
                if(laenge_y - y < bezugsmass)
                {
                    ref = GANX_REF_OBEN_LINKS;
                }else
                {
                    ref = GANX_REF_UNTEN_LINKS;
                }
                msg += "    <Ref>";
                msg += ref;
                msg += "</Ref>";
                msg += "\n";
                //----------------------
                msg += "    <Typ>M</Typ>";
                msg += "\n";
                //----------------------
                msg += "    <X>";
                msg += double_to_qstring(x);
                msg += "</X>";
                msg += "\n";
                //----------------------
                msg += "    <Y>";
                msg += double_to_qstring(y);
                msg += "</Y>";
                msg += "\n";
                //----------------------
                msg += "    <Z>";
                msg += double_to_qstring(0);
                msg += "</Z>";
                msg += "\n";
                //----------------------
                msg += "    <Tool>";
                msg += tnummer;
                msg += "</Tool>";
                msg += "\n";
                //----------------------
                msg += "    <Mill>";
                msg += "3";                      //Rechtecktasche
                msg += ";";
                //msg += double_to_qstring(by);    //TAB
                if(zustellungen > 1  &&  ii != zustellungen)
                {
                    msg += double_to_qstring(by-2);    //TAB
                }else
                {
                    msg += double_to_qstring(by);    //TAB
                }
                msg += ";";
                //msg += double_to_qstring(lx);    //TAL
                if(zustellungen > 1  &&  ii != zustellungen)
                {
                    msg += double_to_qstring(lx-2);    //TAL
                }else
                {
                    msg += double_to_qstring(lx);    //TAL
                }
                msg += ";";
                msg += double_to_qstring(eckenradius); //Eckenradius Tasche
                msg += ";";
                //msg += ti;                       //TaTi
                msg += double_to_qstring(ti.toDouble()/zustellungen*ii);    //TaTi
                msg += ";";
                //Variante der Rechtecktasche:
                //  1 = ausgeräumt
                //  2 = nicht ausgeräumt von der Mitte angefahren
                //  3 = nicht ausgeräumt entlang der Taschenkante angefahren
                if(ausraeumen == true)
                {
                    msg += "1";
                }else
                {
                    msg += "3";
                }
                msg += ";";
                msg += "GL";                     //Gleichlauf (GL = Gleichlauf / GG = Gegenlauf)
                msg += ";";
                msg += double_to_qstring(wkz_vorschub);
                msg += ";";
                //msg += int_to_qstring(zustellungen);
                msg += "1";                     //ohne Zustellungen
                msg += "</Mill>";
                msg += "\n";
                //----------------------
                msg += "    <ImageKey>RE</ImageKey>";
                msg += "\n";
                //----------------------
                msg += "    <OldID>";
                if(rt.bezug() == WST_BEZUG_OBSEI)
                {
                    msg += GANX_WST_BEZUG_OBSEI;
                }else
                {
                    msg += GANX_WST_BEZUG_UNSEI;
                }
                msg += "\\";
                msg += GANX_REF_OBEN_LINKS;
                msg += "\\";
                msg += "M-";
                msg += int_to_qstring(ideditor);               //ID-Nummer
                msg += "</OldID>";
                msg += "\n";
                //----------------------
                msg += "    <KleiGeTei>";
                msg += "0";
                msg += "</KleiGeTei>";
                msg += "\n";
                //----------------------
                if(zustellungen > 1)
                {
                    //----------------------
                    msg += "    <GroupName>";
                    msg += gruppen_PrgrFileWork.letzten_gruppennamen();
                    msg += "</GroupName>";
                    msg += "\n";
                    //----------------------
                    msg += "    <SortID>";
                    msg += double_to_qstring(ii);
                    msg += "</SortID>";
                    msg += "\n";
                    //----------------------
                }
                //----------------------
                msg += "    <Clause />";
                msg += "\n";
                //----------------------
                msg += "    <iClauseState>0</iClauseState>";
                msg += "\n";
                //----------------------
                msg += "  </PrgrFileWork>";
                msg += "\n";

                id++;
                ideditor++;
            }
        }
    }

    //-------------------------Bearbeitungen <PrgrFile>:
    //Dies ist der Teil, den die Gannomat-Editor liest
    //Hier darf nur mit der Syntax entsprechenden Formeln gearbeitet werden
    id = 1;//id die im Editor angezeigt wird
    ganx_Gruppen gruppen_PrgrFile;

    for(uint i=1 ; i<=bearb.zeilenanzahl() ; i++)
    {
        zeile.set_text(bearb.zeile(i));
        if(zeile.zeile(1) == BEARBART_BOHR)
        {
            bohrung bo(zeile.text());

            QString afb_text = bo.afb();
            afb_text.replace("L", laenge_qstring());
            afb_text.replace("B", breite_qstring());
            afb_text.replace("D", dicke_qstring());
            afb_text.replace(",", ".");
            afb_text = ausdruck_auswerten(afb_text);
            if(afb_text.toDouble() == 0)
            {
                continue;
            }

            double x = bo.x();
            double y = bo.y();
            double z = bo.z();

            double dm = bo.dm();
            double laenge_y = tmp_b;
            QString bezug = bo.bezug();

            QString tnummer = wkzmag.wkznummer(WKZ_TYP_BOHRER, dm, bo.tiefe(), Dicke, bezug);
            if(!tnummer.isEmpty())
            {
                //Werkzeug wurde gefunden, Bohrung kann gebohrt werden:

                //Anzahl der Zustellungen berechnen:
                double zustmass = bo.zustellmass();
                if(zustmass <= 0)
                {
                    zustmass = wkzmag.zustellmass(tnummer).toDouble();
                }
                int zustellungen = aufrunden(bo.tiefe() / zustmass);
                if(zustellungen <= 0)
                {
                    zustellungen = 1;
                }
                //-------------------------------

                if(bezug == WST_BEZUG_OBSEI)
                {
                    //x = Breite
                    //y = Länge
                    //z = Tiefe
                    msg += "  <PrgrFile>";
                    msg += "\n";
                    //----------------------
                    msg += "    <CntID>";
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</CntID>";
                    msg += "\n";
                    //----------------------
                    //y < 40 -> TL
                    //Länge - y < 40 ->BL
                    QString ref;
                    if(laenge_y - y < bezugsmass)
                    {
                        ref += GANX_REF_OBEN_LINKS;
                        y = laenge_y - y;
                    }else
                    {
                        ref += GANX_REF_UNTEN_LINKS;
                    }
                    //msg += ref;
                    //----------------------
                    msg += "    <ID>";
                    msg += GANX_WST_BEZUG_OBSEI;
                    msg += "\\";
                    msg += ref;
                    msg += "\\";
                    msg += "B-";
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</ID>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefVal1>";
                    msg += double_to_qstring(y).replace(".",",");
                    msg += "</RefVal1>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefVal2>";
                    msg += double_to_qstring(x).replace(".",",");
                    msg += "</RefVal2>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefLVL>";
                    msg += double_to_qstring(0).replace(".",",");
                    msg += "</RefLVL>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Diameter>";
                    msg += wkzmag.dm(tnummer).replace(".",",");
                    msg += "</Diameter>";
                    msg += "\n";
                    //----------------------
                    msg += "   <Depth>";
                    msg += bo.tiefe_qstring().replace(".",",");
                    msg += "</Depth>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DoDbl>false</DoDbl>";
                    msg += "\n";
                    //----------------------
                    msg += "    <UsedDbl>ERR</UsedDbl>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblB>true</DblB>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblL>false</DblL>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblE>false</DblE>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DoMF>false</DoMF>";
                    msg += "\n";
                    //----------------------
                    msg += "    <MFLage>B</MFLage>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Tool>";
                    msg += tnummer;
                    msg += "</Tool>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Cyclic>";
                    msg += int_to_qstring(zustellungen);
                    msg += "</Cyclic>";
                    msg += "\n";
                    //----------------------
                    msg += "    <ImageKey>B</ImageKey>>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Step>1</Step>";
                    msg += "\n";
                    //----------------------
                    msg += "  </PrgrFile>";
                    msg += "\n";

                    id++;

                }else if(bezug == WST_BEZUG_UNSEI)
                {
                    //x = Breite
                    //y = Länge
                    //z = Tiefe
                    msg += "  <PrgrFile>";
                    msg += "\n";
                    msg += "    <CntID>";
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</CntID>";
                    msg += "\n";
                    //----------------------
                    QString ref;
                    if(laenge_y - y < bezugsmass)
                    {
                        ref = GANX_REF_OBEN_LINKS;
                        y = laenge_y - y;
                    }else
                    {
                        ref = GANX_REF_UNTEN_LINKS;
                    }
                    //----------------------
                    msg += "    <ID>";
                    msg += GANX_WST_BEZUG_UNSEI;
                    msg += "\\";
                    msg += ref;
                    msg += "\\";
                    msg += "B-";
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</ID>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefVal1>";
                    msg += double_to_qstring(y).replace(".",",");
                    msg += "</RefVal1>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefVal2>";
                    msg += double_to_qstring(x).replace(".",",");
                    msg += "</RefVal2>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefLVL>";
                    msg += double_to_qstring(0).replace(".",",");
                    msg += "</RefLVL>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Diameter>";
                    msg += wkzmag.dm(tnummer).replace(".",",");
                    msg += "</Diameter>";
                    msg += "\n";
                    //----------------------
                    msg += "   <Depth>";
                    msg += bo.tiefe_qstring().replace(".",",");
                    msg += "</Depth>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DoDbl>false</DoDbl>";
                    msg += "\n";
                    //----------------------
                    msg += "    <UsedDbl>ERR</UsedDbl>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblB>true</DblB>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblL>false</DblL>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblE>false</DblE>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DoMF>false</DoMF>";
                    msg += "\n";
                    //----------------------
                    msg += "    <MFLage>B</MFLage>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Tool>";
                    msg += tnummer;
                    msg += "</Tool>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Cyclic>";
                    msg += int_to_qstring(zustellungen);
                    msg += "</Cyclic>";
                    msg += "\n";
                    //----------------------
                    msg += "    <ImageKey>B</ImageKey>>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Step>1</Step>";
                    msg += "\n";
                    //----------------------
                    msg += "  </PrgrFile>";
                    msg += "\n";

                    id++;

                }else if(bezug == WST_BEZUG_LI)
                {
                    //x = Tiefe
                    //y = Y-Pos
                    //z = Z-Pos
                    msg += "  <PrgrFile>";
                    msg += "\n";
                    msg += "    <CntID>";
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</CntID>";
                    msg += "\n";
                    //----------------------
                    QString ref;
                    if(laenge_y - y < bezugsmass)
                    {
                        ref += GANX_REF_OBEN_LINKS;
                        y = laenge_y - y;
                    }else
                    {
                        ref += GANX_REF_UNTEN_LINKS;
                    }
                    //----------------------
                    msg += "    <ID>";
                    msg += GANX_WST_BEZUG_LI;
                    msg += "\\";
                    msg += ref;
                    msg += "\\";
                    msg += "B-";
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</ID>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefVal1>";
                    msg += double_to_qstring(y).replace(".",",");
                    msg += "</RefVal1>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefVal2>";
                    msg += double_to_qstring(z).replace(".",",");
                    msg += "</RefVal2>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefLVL>";
                    msg += double_to_qstring(0).replace(".",",");
                    msg += "</RefLVL>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Diameter>";
                    msg += wkzmag.dm(tnummer).replace(".",",");
                    msg += "</Diameter>";
                    msg += "\n";
                    //----------------------
                    msg += "   <Depth>";
                    msg += bo.tiefe_qstring().replace(".",",");
                    msg += "</Depth>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DoDbl>false</DoDbl>";
                    msg += "\n";
                    //----------------------
                    msg += "    <UsedDbl>ERR</UsedDbl>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblB>true</DblB>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblL>false</DblL>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblE>false</DblE>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DoMF>false</DoMF>";
                    msg += "\n";
                    //----------------------
                    msg += "    <MFLage>B</MFLage>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Tool>";
                    msg += tnummer;
                    msg += "</Tool>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Cyclic>";
                    msg += int_to_qstring(zustellungen);
                    msg += "</Cyclic>";
                    msg += "\n";
                    //----------------------
                    msg += "    <ImageKey>B</ImageKey>>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Step>1</Step>";
                    msg += "\n";
                    //----------------------
                    msg += "  </PrgrFile>";
                    msg += "\n";

                    id++;

                }else if(bezug == WST_BEZUG_RE)
                {
                    //x = Tiefe
                    //y = Y-Pos
                    //z = Z-Pos
                    msg += "  <PrgrFile>";
                    msg += "\n";
                    msg += "    <CntID>";
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</CntID>";
                    msg += "\n";
                    //----------------------
                    QString ref;
                    if(laenge_y - y < bezugsmass)
                    {
                        ref += GANX_REF_OBEN_RECHTS;
                        y = laenge_y - y;
                    }else
                    {
                        ref += GANX_REF_UNTEN_RECHTS;
                    }
                    //----------------------
                    msg += "    <ID>";
                    msg += GANX_WST_BEZUG_RE;
                    msg += "\\";
                    msg += ref;
                    msg += "\\";
                    msg += "B-";
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</ID>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefVal1>";
                    msg += double_to_qstring(y).replace(".",",");
                    msg += "</RefVal1>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefVal2>";
                    msg += double_to_qstring(z).replace(".",",");
                    msg += "</RefVal2>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefLVL>";
                    msg += double_to_qstring(0).replace(".",",");
                    msg += "</RefLVL>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Diameter>";
                    msg += wkzmag.dm(tnummer).replace(".",",");
                    msg += "</Diameter>";
                    msg += "\n";
                    //----------------------
                    msg += "   <Depth>";
                    msg += bo.tiefe_qstring().replace(".",",");
                    msg += "</Depth>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DoDbl>false</DoDbl>";
                    msg += "\n";
                    //----------------------
                    msg += "    <UsedDbl>ERR</UsedDbl>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblB>true</DblB>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblL>false</DblL>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblE>false</DblE>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DoMF>false</DoMF>";
                    msg += "\n";
                    //----------------------
                    msg += "    <MFLage>B</MFLage>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Tool>";
                    msg += tnummer;
                    msg += "</Tool>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Cyclic>";
                    msg += int_to_qstring(zustellungen);
                    msg += "</Cyclic>";
                    msg += "\n";
                    //----------------------
                    msg += "    <ImageKey>B</ImageKey>>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Step>1</Step>";
                    msg += "\n";
                    //----------------------
                    msg += "  </PrgrFile>";
                    msg += "\n";

                    id++;

                }else if(bezug == WST_BEZUG_VO)
                {
                    //x = x-Pos
                    //y = Tiefe
                    //z = Z-Pos
                    msg += "  <PrgrFile>";
                    msg += "\n";
                    msg += "    <CntID>";
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</CntID>";
                    msg += "\n";
                    //----------------------
                    QString ref = GANX_REF_UNTEN_LINKS;
                    //----------------------
                    msg += "    <ID>";
                    msg += GANX_WST_BEZUG_VO;
                    msg += "\\";
                    msg += ref;
                    msg += "\\";
                    msg += "B-";
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</ID>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefVal1>";
                    msg += double_to_qstring(z).replace(".",",");
                    msg += "</RefVal1>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefVal2>";
                    msg += double_to_qstring(x).replace(".",",");
                    msg += "</RefVal2>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefLVL>";
                    msg += double_to_qstring(0).replace(".",",");
                    msg += "</RefLVL>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Diameter>";
                    msg += wkzmag.dm(tnummer).replace(".",",");
                    msg += "</Diameter>";
                    msg += "\n";
                    //----------------------
                    msg += "   <Depth>";
                    msg += bo.tiefe_qstring().replace(".",",");
                    msg += "</Depth>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DoDbl>false</DoDbl>";
                    msg += "\n";
                    //----------------------
                    msg += "    <UsedDbl>ERR</UsedDbl>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblB>true</DblB>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblL>false</DblL>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblE>false</DblE>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DoMF>false</DoMF>";
                    msg += "\n";
                    //----------------------
                    msg += "    <MFLage>B</MFLage>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Tool>";
                    msg += tnummer;
                    msg += "</Tool>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Cyclic>";
                    msg += int_to_qstring(zustellungen);
                    msg += "</Cyclic>";
                    msg += "\n";
                    //----------------------
                    msg += "    <ImageKey>B</ImageKey>>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Step>1</Step>";
                    msg += "\n";
                    //----------------------
                    msg += "  </PrgrFile>";
                    msg += "\n";

                    id++;

                }else if(bezug == WST_BEZUG_HI)
                {
                    //x = x-Pos
                    //y = Tiefe
                    //z = Z-Pos
                    msg += "  <PrgrFile>";
                    msg += "\n";
                    msg += "    <CntID>";
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</CntID>";
                    msg += "\n";
                    //----------------------
                    QString ref = GANX_REF_OBEN_LINKS;
                    //----------------------
                    msg += "    <ID>";
                    msg += GANX_WST_BEZUG_HI;
                    msg += "\\";
                    msg += ref;
                    msg += "\\";
                    msg += "B-";
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</ID>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefVal1>";
                    msg += double_to_qstring(z).replace(".",",");
                    msg += "</RefVal1>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefVal2>";
                    msg += double_to_qstring(x).replace(".",",");
                    msg += "</RefVal2>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefLVL>";
                    msg += double_to_qstring(0).replace(".",",");
                    msg += "</RefLVL>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Diameter>";
                    msg += wkzmag.dm(tnummer).replace(".",",");
                    msg += "</Diameter>";
                    msg += "\n";
                    //----------------------
                    msg += "   <Depth>";
                    msg += bo.tiefe_qstring().replace(".",",");
                    msg += "</Depth>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DoDbl>false</DoDbl>";
                    msg += "\n";
                    //----------------------
                    msg += "    <UsedDbl>ERR</UsedDbl>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblB>true</DblB>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblL>false</DblL>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblE>false</DblE>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DoMF>false</DoMF>";
                    msg += "\n";
                    //----------------------
                    msg += "    <MFLage>B</MFLage>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Tool>";
                    msg += tnummer;
                    msg += "</Tool>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Cyclic>";
                    msg += int_to_qstring(zustellungen);
                    msg += "</Cyclic>";
                    msg += "\n";
                    //----------------------
                    msg += "    <ImageKey>B</ImageKey>>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Step>1</Step>";
                    msg += "\n";
                    //----------------------
                    msg += "  </PrgrFile>";
                    msg += "\n";

                    id++;

                }
            }else
            {
                //Kein Werkzeug wurde gefunden.
                //Kann Bohrung als Kreistasche gefräst werden?:
                tnummer = wkzmag.wkznummer_von_alias(bo.wkznum());//Ist direkt ei WKZ definiert?
                if(tnummer.isEmpty())
                {
                    tnummer = wkzmag.wkznummer(WKZ_TYP_FRAESER, dm, bo.tiefe(), Dicke, bezug);
                }

                if(!tnummer.isEmpty())
                {
                    //Werkzeug wurde gefunden, Kreistasche kann gefräst werden:

                    QString ti = bo.tiefe_qstring();
                    if(ti.toDouble() > dicke())
                    {
                        QString tmp = "{LZ}+";
                        double dif = ti.toDouble() - dicke();
                        tmp += double_to_qstring(dif);
                        ti = tmp;
                    }

                    //Anzahl der Zustellungen berechnen:
                    double zustmass = bo.zustellmass();
                    if(zustmass <= 0)
                    {
                        zustmass = wkzmag.zustellmass(tnummer).toDouble();
                    }
                    int zustellungen = aufrunden(bo.tiefe() / zustmass);

                    if(zustellungen <= 0)
                    {
                        zustellungen = 1;
                    }
                    //---------------------------------------
                    QString wkz_nr = tnummer;
                    double wkz_vorschub = wkzmag.vorschub(tnummer).toDouble();

                    msg += "  <PrgrFile>";
                    msg += "\n";
                    //----------------------
                    msg += "    <CntID>";
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</CntID>";
                    msg += "\n";
                    //----------------------
                    QString ref = GANX_REF_UNTEN_LINKS;
                    //y < 40 -> TL
                    //Länge - y < 40 ->BL
                    if(laenge_y - y < bezugsmass)
                    {
                        ref = GANX_REF_OBEN_LINKS;
                        y = laenge_y - y;
                    }
                    //----------------------
                    msg += "    <ID>";
                    if(bo.bezug() == WST_BEZUG_OBSEI)
                    {
                        msg += GANX_WST_BEZUG_OBSEI;
                    }else
                    {
                        msg += GANX_WST_BEZUG_UNSEI;
                    }
                    msg += "\\";
                    msg += ref;
                    msg += "\\";
                    msg += "M-";
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</ID>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefVal1>";
                    msg += double_to_qstring(y).replace(".",",");
                    msg += "</RefVal1>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefVal2>";
                    msg += double_to_qstring(x).replace(".",",");
                    msg += "</RefVal2>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Diameter>";
                    msg += "0";
                    msg += "</Diameter>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Depth>";
                    msg += double_to_qstring(z).replace(".",",");
                    msg += "</Depth>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DoDbl>false</DoDbl>";
                    msg += "\n";
                    //----------------------
                    msg += "    <UsedDbl>ERR</UsedDbl>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblB>false</DblB>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblL>false</DblL>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblE>false</DblE>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DoMF>false</DoMF>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Tool>";
                    msg += wkz_nr;
                    msg += "</Tool>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Cyclic>0</Cyclic>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Mill>";
                    msg += "2";                      //Kreistasche
                    msg += ";";
                    msg += double_to_qstring(dm);
                    msg += ";";
                    msg += ti;                       //TaTi
                    msg += ";";
                    msg += "2";                      //Variante der Kreistasche (2 = ausgeräumt)
                    msg += ";";
                    msg += "GL";                     //Gleichlauf (GL = Gleichlauf / GG = Gegenlauf)
                    msg += ";";
                    msg += double_to_qstring(wkz_vorschub);
                    msg += ";";
                    msg += int_to_qstring(zustellungen);
                    msg += "</Mill>";
                    msg += "\n";
                    //----------------------
                    msg += "    <ImageKey>KR</ImageKey>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Step>1</Step>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Clause>0</Clause>";
                    msg += "\n";
                    //----------------------
                    msg += "  </PrgrFile>";
                    msg += "\n";

                    id++;

                }else
                {
                    //Diese Stelle des Codes wird theoretisch niemals erreicht,
                    //da die Funktion bereits in er ersten For-Schleife abbricht.

                    QString msg = fehler_kein_WKZ("ganx", zeile);
                    QMessageBox mb;
                    mb.setText(msg);
                    mb.exec();
                    return msg;
                }
            }
        }else if(zeile.zeile(1) == BEARBART_BOHRRASTER)
        {
            bohrraster bora(zeile.text());

            double x = bora.x();
            double y = bora.y();
            //double z = bora.z();

            double dm = bora.dm();
            double laenge_y = tmp_b;
            QString bezug = bora.bezug();

            QString tnummer = wkzmag.wkznummer(WKZ_TYP_BOHRER, dm, bora.tiefe(), Dicke, bezug);

            if(!tnummer.isEmpty())
            {
                //Werkzeug wurde gefunden, Bohrraster kann gebohrt werden:

                //Anzahl der Zustellungen berechnen:
                double zustmass = bora.zustellmass();
                if(zustmass <= 0)
                {
                    zustmass = wkzmag.zustellmass(tnummer).toDouble();
                }
                int zustellungen = aufrunden(bora.tiefe() / zustmass);
                if(zustellungen <= 0)
                {
                    zustellungen = 1;
                }
                //-------------------------------

                if(bezug == WST_BEZUG_OBSEI  ||  bezug == WST_BEZUG_UNSEI)
                {
                    //x = Breite
                    //y = Länge
                    //z = Tiefe
                    msg += "  <PrgrFile>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DELMARK>OK</DELMARK>";
                    msg += "\n";
                    //----------------------
                    msg += "    <CntID>";
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</CntID>";
                    msg += "\n";
                    //----------------------
                    //y < 40 -> TL
                    //Länge - y < 40 ->BL
                    QString ref;
                    if(bora.anz_y()==1  )
                    {
                        if(laenge_y - y < bezugsmass)
                        {
                            ref += GANX_REF_OBEN_LINKS;
                            y = laenge_y - y;
                        }else
                        {
                            ref += GANX_REF_UNTEN_LINKS;
                        }
                    }else //bora.anz_y()>1
                    {
                        ref += GANX_REF_OBEN_LINKS;
                        y = laenge_y - (y + (  (bora.anz_y()-1)*bora.raster_y()  ));
                    }
                    //msg += ref;
                    //----------------------
                    msg += "    <ID>";
                    if(bezug == WST_BEZUG_OBSEI)
                    {
                        msg += GANX_WST_BEZUG_OBSEI;
                    }else
                    {
                        msg += GANX_WST_BEZUG_UNSEI;
                    }
                    msg += "\\";
                    msg += ref;
                    msg += "\\";
                    msg += "BR-";
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</ID>";
                    msg += "\n";
                    //----------------------
                    //----------------------
                    msg += "    <RefVal1>";
                    msg += double_to_qstring(y).replace(".",",");
                    msg += "</RefVal1>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefVal2>";
                    msg += double_to_qstring(x).replace(".",",");
                    msg += "</RefVal2>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefLVL>";
                    msg += double_to_qstring(0).replace(".",",");
                    msg += "</RefLVL>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Diameter>";
                    msg += wkzmag.dm(tnummer).replace(".",",");
                    msg += "</Diameter>";
                    msg += "\n";
                    //----------------------
                    msg += "   <Depth>";
                    msg += bora.tiefe_qstring().replace(".",",");
                    msg += "</Depth>";
                    msg += "\n";
                    //---------------------
                    msg += "    <DoDbl>false</DoDbl>";
                    msg += "\n";
                    //---------------------
                    msg += "    <UsedDbl>ERR</UsedDbl>";
                    msg += "\n";
                    //---------------------
                    msg += "    <DblB>true</DblB>";
                    msg += "\n";
                    //---------------------
                    msg += "    <DblL>false</DblL>";
                    msg += "\n";
                    //---------------------
                    msg += "    <DblE>false</DblE>";
                    msg += "\n";
                    //---------------------
                    msg += "    <DoMF>false</DoMF>";
                    msg += "\n";
                    //---------------------
                    msg += "    <Cols>";
                    msg += bora.anz_x_qstring();
                    msg += "</Cols>";
                    msg += "\n";
                    //---------------------
                    msg += "    <ColsDistance>";
                    msg += bora.raster_x_qstring();
                    msg += "</ColsDistance>";
                    msg += "\n";
                    //---------------------
                    msg += "    <Rows>";
                    msg += bora.anz_y_qstring();
                    msg += "</Rows>";
                    msg += "\n";
                    //---------------------
                    msg += "    <RowsDistance>";
                    msg += bora.raster_y_qstring();
                    msg += "</RowsDistance>";
                    msg += "\n";
                    //---------------------
                    msg += "    <Tool>";
                    msg += tnummer;
                    msg += "</Tool>";
                    msg += "\n";
                    //----------------------
                    msg += "    <SVar>VAR1</SVar>";
                    msg += "\n";
                    //---------------------
                    msg += "    <Cyclic>";
                    msg += int_to_qstring(zustellungen);
                    msg += "</Cyclic>";
                    msg += "\n";
                    //----------------------
                    msg += "    <ImageKey>BR</ImageKey>>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Step>1</Step>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Clause />";
                    msg += "\n";
                    //----------------------
                    msg += "    <iClauseState>0</iClauseState>";
                    msg += "\n";
                    //----------------------
                    msg += "    <IsActivated>true</IsActivated>";
                    msg += "\n";
                    //----------------------
                    msg += "    <iColor>4294309340</iColor>";
                    msg += "\n";
                    //----------------------
                    msg += "  </PrgrFile>";
                    msg += "\n";

                    id++;

                }
            }else
            {
                //Sollte nicht vorkommen können, da bohrraster anhand des vorhandenen Werkzeuges ermittelt werden
            }
        }else if(zeile.zeile(1) == BEARBART_NUT)
        {

            nut nu(zeile.text());
            if(nu.xs() != nu.xe())
            {
                /*
                //Warnung ausgeben und Nut unterdrücken:
                QString msg = "";
                msg += "Achtung bei Export ganx!\n";
                msg += "Teilname: ";
                msg += Name;
                msg += "\n";
                msg += "Nut ist nicht parallel zur X-Achse:\n";
                msg += zeile.text();
                msg += "\n";
                msg += "Bearbeitung wird unterdrueckt.";

                QMessageBox mb;
                mb.setText(msg);
                mb.exec();
                */
                continue;
            }
            double x = nu.xs();
            double y;
            double z = nu.tiefe(); //Tiefe
            double l = 0;
            //Nutlänge berechnen:
            if(nu.ys() < nu.ye())
            {
                l = nu.ye() - nu.ys();
                y = nu.ys();
            }else
            {
                l = nu.ys() - nu.ye();
                y = nu.ye();
            }
            y = tmp_b - y;
            y = y-l;
            QString tnummer = wkzmag.wkznummer(WKZ_TYP_SAEGE);
            if(tnummer.isEmpty())
            {
                //Diese Stelle des Codes wird theoretisch niemals erreicht,
                //da die Funktion bereits in er ersten For-Schleife abbricht.

                QString msg = fehler_kein_WKZ("ganx", zeile);
                QMessageBox mb;
                mb.setText(msg);
                mb.exec();
                return msg;
            }
            //double wkz_dm = wkzmag.dm(tnummer).toDouble();

            QString nutvariante_qstring = "Var2";
            //"Var1" = Nuttiefe wird beim Startmaß und Endmaß erreicht
            //"Var2" = Nut beginnt beim Startmaß und endet am Endmaß

            QString nutrichtung = "Y";
            //Mögliche Werte:
            //"X" = Nut von links nach rechts = entlang der Y-Achse
            //"Y" = Nut von vorne nach hinten = entlang der X-Achse

            double nutblattbreite = wkzmag.saegeblattbreite(tnummer).toDouble();

            if(nu.breite() < nutblattbreite)
            {
                /*
                //Warnung ausgeben und Nut unterdrücken:
                QString msg = "";
                msg += "Achtung bei Export ganx!\n";
                msg += "Teilname: ";
                msg += Name;
                msg += "\n";
                msg += "Saegeblatt zu breit fuer Nut:\n";
                msg += zeile.text();
                msg += "\n";
                msg += "Bearbeitung wird unterdrueckt.";

                QMessageBox mb;
                mb.setText(msg);
                mb.exec();
                */
                continue;
            }else if(nu.breite() == nutblattbreite)
            {
                msg += "  <PrgrFile>";
                msg += "\n";
                //----------------------
                msg += "    <CntID>";
                msg += int_to_qstring(id);               //ID-Nummer
                msg += "</CntID>";
                msg += "\n";
                //----------------------
                msg += "    <ID>";
                if(nu.bezug() == WST_BEZUG_OBSEI)
                {
                    msg += GANX_WST_BEZUG_OBSEI;
                }else
                {
                    msg += GANX_WST_BEZUG_UNSEI;
                }
                msg += "\\";
                msg += GANX_REF_OBEN_LINKS;
                msg += "\\";
                msg += "S-";
                msg += int_to_qstring(id);               //ID-Nummer
                msg += "</ID>";
                msg += "\n";
                //----------------------
                msg += "    <RefVal1>";
                msg += double_to_qstring(y).replace(".",",");
                msg += "</RefVal1>";
                msg += "\n";
                //----------------------
                msg += "    <RefVal2>";
                msg += double_to_qstring(x).replace(".",",");
                msg += "</RefVal2>";
                msg += "\n";
                //----------------------
                msg += "    <Diameter>";
                msg += "0";
                msg += "</Diameter>";
                msg += "\n";
                //----------------------
                msg += "    <Depth>";
                msg += double_to_qstring(z).replace(".",",");
                msg += "</Depth>";
                msg += "\n";
                //----------------------
                msg += "    <DoDbl>false</DoDbl>";
                msg += "\n";
                //----------------------
                msg += "    <DblB>false</DblB>";
                msg += "\n";
                //----------------------
                msg += "    <DblL>false</DblL>";
                msg += "\n";
                //----------------------
                msg += "    <DblE>false</DblE>";
                msg += "\n";
                //----------------------
                msg += "    <DoMF>false</DoMF>";
                msg += "\n";
                //----------------------
                msg += "    <Tool>";
                msg += tnummer;
                msg += "</Tool>";
                msg += "\n";
                //----------------------
                msg += "    <SVar>";
                msg += nutvariante_qstring;
                msg += "</SVar>";
                msg += "\n";
                //----------------------
                msg += "    <SParallel>";
                msg += nutrichtung;
                msg += "</SParallel>";
                msg += "\n";
                //----------------------
                msg += "    <SGrooveLength>";
                msg += double_to_qstring(l);
                msg += "</SGrooveLength>";
                msg += "\n";
                //----------------------
                msg += "    <Cyclic>0</Cyclic>";//Zustellung?? Testen!!!
                msg += "\n";
                //----------------------
                msg += "    <ImageKey>S</ImageKey>";
                msg += "\n";
                //----------------------
                msg += "    <Step>1</Step>";
                msg += "\n";
                //----------------------
                msg += "  </PrgrFile>";
                msg += "\n";
                //----------------------

                id++;

            }else if(nu.breite() > nutblattbreite)
            {
                //Wir müssen mehrere Nuten fahren Nuten
                uint anz_nuten = aufrunden(nu.breite() / nutblattbreite);
                double x = nu.xs();

                for(uint ii=1; ii<=anz_nuten ;ii++)
                {
                    double versatz = nu.breite()/2 - nutblattbreite/2 ;

                    if(ii == 1)
                    {
                        x = x - versatz;

                    }else if(ii==anz_nuten)
                    {
                        x = nu.xs();
                        x = x + versatz;
                    }else
                    {
                        double schleifenversatz;
                        schleifenversatz = nutblattbreite - ((nutblattbreite*anz_nuten)-nu.breite()) /(anz_nuten-1);
                        x = nu.xs() - versatz + (ii-1)*schleifenversatz;
                    }

                    msg += "  <PrgrFile>";
                    msg += "\n";
                    //----------------------
                    msg += "    <CntID>";
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</CntID>";
                    msg += "\n";
                    //----------------------
                    msg += "    <ID>";
                    if(nu.bezug() == WST_BEZUG_OBSEI)
                    {
                        msg += GANX_WST_BEZUG_OBSEI;
                    }else
                    {
                        msg += GANX_WST_BEZUG_UNSEI;
                    }
                    msg += "\\";
                    msg += GANX_REF_OBEN_LINKS;
                    msg += "\\";
                    msg += "S-";
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</ID>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefVal1>";
                    msg += double_to_qstring(y).replace(".",",");
                    msg += "</RefVal1>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefVal2>";
                    msg += double_to_qstring(x).replace(".",",");
                    msg += "</RefVal2>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Diameter>";
                    msg += "0";
                    msg += "</Diameter>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Depth>";
                    msg += double_to_qstring(z).replace(".",",");
                    msg += "</Depth>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DoDbl>false</DoDbl>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblB>false</DblB>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblL>false</DblL>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblE>false</DblE>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DoMF>false</DoMF>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Tool>";
                    msg += tnummer;
                    msg += "</Tool>";
                    msg += "\n";
                    //----------------------
                    msg += "    <SVar>";
                    msg += nutvariante_qstring;
                    msg += "</SVar>";
                    msg += "\n";
                    //----------------------
                    msg += "    <SParallel>";
                    msg += nutrichtung;
                    msg += "</SParallel>";
                    msg += "\n";
                    //----------------------
                    msg += "    <SGrooveLength>";
                    msg += double_to_qstring(l);
                    msg += "</SGrooveLength>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Cyclic>0</Cyclic>";//Zustellung?? Testen!!!
                    msg += "\n";
                    //----------------------
                    msg += "    <ImageKey>S</ImageKey>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Step>1</Step>";
                    msg += "\n";
                    //----------------------
                    msg += "  </PrgrFile>";
                    msg += "\n";
                    //----------------------

                    id++;

                }
            }



        }else if(zeile.zeile(1) == BEARBART_RTA)
        {
            rechtecktasche rt(zeile.text());
            double x = rt.x();
            double y = rt.y();
            double z = rt.z();
            bool ausraeumen = true;
            if(rt.tiefe() == dicke())
            {
                rt.set_tiefe(dicke()+2);
            }
            if(rt.tiefe() >= Dicke  || \
               rt.tiefe() <  0 )
            {
                ausraeumen = true;
            }else
            {
                if(rt.ausraeumen() == false)
                {
                    ausraeumen = false;
                }else
                {
                    ausraeumen = true;
                }
            }
            QString ti = rt.tiefe_qstring();
            if(ti.toDouble() > dicke())
            {
                QString tmp = "{LZ}+";
                double dif = ti.toDouble() - dicke();
                tmp += double_to_qstring(dif);
                ti = tmp;
            }
            double lx = 0;
            double by = 0;
            if(rt.drewi() == 0 || rt.drewi() == 180)
            {
                lx = rt.laenge();
                by = rt.breite();
            }else if(rt.drewi() == 90 || rt.drewi() == 270)
            {
                lx = rt.breite();
                by = rt.laenge();
            }else
            {
                /*Diese Warnung wird bereits durch die vorherige For-Schleife ausgegeben:
                 *
                //Warnung ausgeben und RTA unterdrücken:
                QString msg = "";
                msg += "Achtung bei Export ganx!\n";
                msg += "Teilname: ";
                msg += Name;
                msg += "\n";
                msg += "Drehwinkel der Rechtecktasche wird nicht unterstuetzt:\n";
                msg += zeile.text();
                msg += "\n";
                msg += "Bearbeitung wird unterdrueckt.";

                QMessageBox mb;
                mb.setText(msg);
                mb.exec();
                */
                continue;
            }
            double laenge_y = tmp_b;
            double minmass = lx;
            if(by < minmass)
            {
                minmass = by;
            }

            QString tnummer = wkzmag.wkznummer_von_alias(rt.wkznum());//Ist direkt ei WKZ definiert?
            if(tnummer.isEmpty())
            {
                 tnummer = wkzmag.wkznummer(WKZ_TYP_FRAESER, minmass, rt.tiefe(), Dicke, rt.bezug());
            }

            if(tnummer.isEmpty())
            {
                //Diese Stelle des Codes wird theoretisch niemals erreicht,
                //da die Funktion bereits in er ersten For-Schleife abbricht.

                QString msg = fehler_kein_WKZ("ganx", zeile);
                QMessageBox mb;
                mb.setText(msg);
                mb.exec();
                return msg;
            }
            double wkz_dm = wkzmag.dm(tnummer).toDouble();
            double eckenradius = rt.rad();
            if(eckenradius < wkz_dm/2)
            {
                eckenradius = wkz_dm/2;
            }
            double wkz_vorschub = wkzmag.vorschub(tnummer).toDouble();
            //Anzahl der Zustellungen berechnen:
            double zustmass = rt.zustellmass();
            if(zustmass <= 0)
            {
                zustmass = wkzmag.zustellmass(tnummer).toDouble();
            }
            int zustellungen = aufrunden(rt.tiefe() / zustmass);
            if(zustellungen <= 0)
            {
                zustellungen = 1;
            }

            if(zustellungen > 1)
            {
                if(rt.bezug() == WST_BEZUG_OBSEI)
                {
                    gruppen_PrgrFile.neue_gruppe(GANX_WST_BEZUG_OBSEI);
                }else
                {
                    gruppen_PrgrFile.neue_gruppe(GANX_WST_BEZUG_UNSEI);
                }
                if(wkz_dm > by-2  ||  wkz_dm > lx-2)//by==TAB  lx==TAL
                {
                    //Diese Stelle des Codes wird theoretisch niemals erreicht,
                    //da die Funktion bereits in er ersten For-Schleife abbricht.

                    QString msg = fehler_kein_WKZ("ganx", zeile);
                    msg += "\n";
                    msg += "Anzahl der Zustellungen: ";
                    msg += double_to_qstring(zustellungen);
                    QMessageBox mb;
                    mb.setText(msg);
                    mb.exec();
                    return msg;
                }
            }

            for(uint ii=1 ; ii<=zustellungen ;ii++)
            {
                //----------------------------------------------

                msg += "  <PrgrFile>";
                msg += "\n";
                //----------------------
                msg += "    <CntID>";
                msg += int_to_qstring(id);               //ID-Nummer
                msg += "</CntID>";
                msg += "\n";
                //----------------------
                QString ref = GANX_REF_UNTEN_LINKS;
                //y < 40 -> TL
                //Länge - y < 40 ->BL
                if(laenge_y - y < bezugsmass)
                {
                    ref = GANX_REF_OBEN_LINKS;
                    y = laenge_y - y;
                }
                //----------------------
                msg += "    <ID>";
                if(rt.bezug() == WST_BEZUG_OBSEI)
                {
                    msg += GANX_WST_BEZUG_OBSEI;
                }else
                {
                    msg += GANX_WST_BEZUG_UNSEI;
                }
                msg += "\\";
                msg += ref;
                msg += "\\";
                msg += "M-";
                msg += int_to_qstring(id);               //ID-Nummer
                msg += "</ID>";
                msg += "\n";
                //----------------------
                msg += "    <RefVal1>";
                msg += double_to_qstring(y).replace(".",",");
                msg += "</RefVal1>";
                msg += "\n";
                //----------------------
                msg += "    <RefVal2>";
                msg += double_to_qstring(x).replace(".",",");
                msg += "</RefVal2>";
                msg += "\n";
                //----------------------
                //----------------------
                msg += "    <Diameter>";
                msg += "0";
                msg += "</Diameter>";
                msg += "\n";
                //----------------------
                msg += "    <Depth>";
                msg += double_to_qstring(z).replace(".",",");
                msg += "</Depth>";
                msg += "\n";
                //----------------------
                msg += "    <DoDbl>false</DoDbl>";
                msg += "\n";
                //----------------------
                msg += "    <UsedDbl>ERR</UsedDbl>";
                msg += "\n";
                //----------------------
                msg += "    <DblB>false</DblB>";
                msg += "\n";
                //----------------------
                msg += "    <DblL>false</DblL>";
                msg += "\n";
                //----------------------
                msg += "    <DblE>false</DblE>";
                msg += "\n";
                //----------------------
                msg += "    <DoMF>false</DoMF>";
                msg += "\n";
                //----------------------
                msg += "    <Tool>";
                msg += tnummer;
                msg += "</Tool>";
                msg += "\n";
                //----------------------
                msg += "    <Cyclic>0</Cyclic>";
                msg += "\n";
                //----------------------
                msg += "    <Mill>";
                msg += "3";                      //Rechtecktasche
                msg += ";";
                //msg += double_to_qstring(by);    //TAB
                if(zustellungen > 1  &&  ii != zustellungen)
                {
                    msg += double_to_qstring(by-2);    //TAB
                }else
                {
                    msg += double_to_qstring(by);    //TAB
                }
                msg += ";";
                //msg += double_to_qstring(lx);    //TAL
                if(zustellungen > 1  &&  ii != zustellungen)
                {
                    msg += double_to_qstring(lx-2);    //TAL
                }else
                {
                    msg += double_to_qstring(lx);    //TAL
                }
                msg += ";";
                msg += double_to_qstring(eckenradius); //Eckenradius Tasche
                msg += ";";
                //msg += ti;                       //TaTi
                QString tiakt = rt.tiefe_qstring();//Weil ti sonst evtl. {LZ}+2 seinkönnte
                if((tiakt.toDouble()/zustellungen*ii) > dicke())
                {
                    QString tmp = "{LZ}+";
                    double dif = tiakt.toDouble() - dicke();
                    tmp += double_to_qstring(dif);
                    tiakt = tmp;
                }else
                {
                    tiakt = double_to_qstring(tiakt.toDouble()/zustellungen*ii);
                }
                msg += tiakt;    //TaTi
                msg += ";";
                //Variante der Rechtecktasche:
                //  1 = ausgeräumt
                //  2 = nicht ausgeräumt von der Mitte angefahren
                //  3 = nicht ausgeräumt entlang der Taschenkante angefahren
                if(ausraeumen == true)
                {
                    msg += "1";
                }else
                {
                    msg += "3";
                }
                msg += ";";
                msg += "GL";                     //Gleichlauf (GL = Gleichlauf / GG = Gegenlauf)
                msg += ";";
                msg += double_to_qstring(wkz_vorschub);
                msg += ";";
                //msg += int_to_qstring(zustellungen);
                msg += "1";                     //ohne Zustellungen
                msg += "</Mill>";
                msg += "\n";
                //----------------------
                msg += "    <ImageKey>RE</ImageKey>";
                msg += "\n";
                //----------------------
                msg += "    <Step>1</Step>";
                msg += "\n";
                //----------------------
                if(zustellungen > 1)
                {
                    //----------------------
                    msg += "    <GroupName>";
                    msg += gruppen_PrgrFile.letzten_gruppennamen();
                    msg += "</GroupName>";
                    msg += "\n";
                    //----------------------
                    msg += "    <SortID>";
                    msg += double_to_qstring(ii);
                    msg += "</SortID>";
                    msg += "\n";
                    //----------------------
                }
                //----------------------
                msg += "    <Clause>0</Clause>";
                msg += "\n";
                //----------------------
                msg += "    <iClauseState>0</iClauseState>";
                msg += "\n";
                //----------------------
                msg += "  </PrgrFile>";
                msg += "\n";

                id++;
            }
        }
    }

    //-------------------------Bearbeitungsgruppen:
    if(gruppen_PrgrFile.gruppen()  ==  gruppen_PrgrFileWork.gruppen())
    {
        msg += gruppen_PrgrFile.gruppen();
    }else
    {
        //Diese Stelle sollte niermals erreicht werden

        QString msg = "Programminterner Fehler bei der Erstellung von Bearbeitungsgruppen!";
        QMessageBox mb;
        mb.setText(msg);
        mb.exec();
        return msg;
    }

    //-------------------------Programmende:
    msg += "</Programm>";


    return msg;
}
QString werkstueck::ggf_dateitext(text_zeilenweise wkzmagazin, text_zeilenweise bearb, double tmp_l, double tmp_b)
{
    QString msg;
    text_zeilenweise zeile;
    zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
     werkzeugmagazin wkzmag(wkzmagazin);
     int min_kta_dm_ausraeumen_false = 200; //Durchmesser ab dem Kreistaschen nicht ausgeräumt werden

     //---------------------------------------Programmversion:
     msg = "GCodeGenerator Version 2";
     msg += "\n";
     //---------------------------------------Programmkopf:
     msg += ">PRGKOPF:";
     msg += "[L]";
     msg += double_to_qstring(tmp_l);
     msg += ";";
     msg += "[B]";
     msg += double_to_qstring(tmp_b);
     msg += ";";
     msg += "[D]";
     msg += dicke_qstring();
     msg += ";";
     msg += "[KOM]";
     msg += "";
     msg += ";";
     msg += "[SIA]";
     msg += "20";
     msg += ";";
     msg += "[BEZ]";
     msg += "Programmkopf";
     msg += ";";
     msg += "[AFB]";
     msg += "1";
     msg += ";";
     msg += "[AX]";
     msg += "0";
     msg += ";";
     msg += "[AY]";
     msg += "0";
     msg += ";";
     msg += "[SH]";
     msg += "0";
     msg += ";";
     msg += ";#ENDE#";
     msg += "\n";
     //---------------------------------------Bearbeitungen Oberseite:
     for(uint i=1 ; i<=bearb.zeilenanzahl() ; i++)
     {
        zeile.set_text(bearb.zeile(i));
        if(zeile.zeile(1) == BEARBART_BOHR)
        {
            bohrung bo(zeile.text());
            QString bezug = bo.bezug();
            QString tnummer = wkzmag.wkznummer(WKZ_TYP_BOHRER, bo.dm(), bo.tiefe(), Dicke, bezug);
            if(!tnummer.isEmpty())
            {
                //Werkzeug wurde gefunden, Bohrung kann gebohrt werden:
                if(bezug == WST_BEZUG_OBSEI)
                {
                    double tiefe;
                    if(bo.tiefe() <= dicke())
                    {
                        tiefe = bo.tiefe();
                    }else
                    {
                        tiefe = dicke() - bo.tiefe();
                    }
                    msg += ">BOHREN";//Achtung der GCodeGenerator speichert derzeit nicht als ">BOHREN:" !!!
                    msg += "[wNAME]";
                    msg += tnummer;
                    msg += ";";
                    msg += "[wD]";
                    msg += "Durchmesser";
                    msg += ";";
                    msg += "[DM]";
                    msg += bo.dm_qstring();
                    msg += ";";
                    msg += "[X]";
                    msg += bo.x_qstring();
                    msg += ";";
                    msg += "[Y]";
                    msg += bo.y_qstring();
                    msg += ";";
                    msg += "[BT]";
                    msg += double_to_qstring(tiefe);
                    msg += ";";
                    msg += "[ANBT]";
                    msg += "AUTO";
                    msg += ";";
                    msg += "[REBT]";
                    msg += "AUTO";
                    msg += ";";
                    msg += "[ZUST]";
                    msg += "AUTO";
                    msg += ";";
                    msg += "[FAN]";
                    msg += "AUTO";
                    msg += ";";
                    msg += "[F]";
                    msg += "AUTO";
                    msg += ";";
                    msg += "[N]";
                    msg += "AUTO";
                    msg += ";";
                    msg += "[KOM]";
                    msg += "";
                    msg += ";";
                    msg += "[BEZ]";
                    msg += "Bohrung";
                    msg += ";";
                    msg += "[AFB]";
                    msg += "1";
                    msg += ";";
                    msg += ";#ENDE#";
                    msg += "\n";
                }
            }else
            {
                //Kein Werkzeug wurde gefunden.
                //Kann Bohrung als Kreistasche gefräst werden?:

                tnummer = wkzmag.wkznummer_von_alias(bo.wkznum());//Ist direkt ei WKZ definiert?
                if(tnummer.isEmpty())
                {
                    tnummer = wkzmag.wkznummer(WKZ_TYP_FRAESER, bo.dm(), bo.tiefe(), Dicke, bezug);
                }
                if(!tnummer.isEmpty())
                {
                    double zustellmas = bo.zustellmass();
                    if(zustellmas <= 0)
                    {
                        zustellmas = wkzmag.zustellmass(tnummer).toDouble();
                    }

                    double tiefe = 0;
                    QString tiefe_qstring;
                    if(bo.tiefe() > dicke())
                    {
                        tiefe = dicke() - bo.tiefe();
                        tiefe_qstring = double_to_qstring(tiefe);
                    }else if(dicke()-bo.tiefe() <= 2)
                    {
                        tiefe_qstring  = "D-";
                        tiefe_qstring += double_to_qstring(dicke()-bo.tiefe());
                    }else
                    {
                        tiefe = bo.tiefe();
                        tiefe_qstring = double_to_qstring(tiefe);
                    }

                    bool ausraeumen = true;
                    if(bo.dm() > 2*wkzmag.dm(tnummer).toDouble()+20)
                    {
                        if(bo.tiefe() < 0  ||  bo.tiefe() > dicke())
                        {
                            ausraeumen = false;
                        }
                    }
                    if(bo.dm() > min_kta_dm_ausraeumen_false)
                    {
                        ausraeumen = false;
                    }

                    if(bo.bezug() == WST_BEZUG_OBSEI)
                    {
                        msg += ">KTASCHE:";
                        msg += "[wNAME]";
                        msg += tnummer;
                        msg += ";";
                        msg += "[wD]";
                        msg += wkzmag.dm(tnummer);
                        msg += ";";
                        msg += "[X]";
                        msg += bo.x_qstring();
                        msg += ";";
                        msg += "[Y]";
                        msg += bo.y_qstring();
                        msg += ";";
                        msg += "[DM]";
                        msg += bo.dm_qstring();
                        msg += ";";
                        msg += "[TT]";
                        msg += tiefe_qstring;
                        msg += ";";
                        msg += "[ZUST]";
                        msg += "AUTO";
                        msg += ";";
                        msg += "[AUSR]";
                        if(ausraeumen == true)
                        {
                            msg += "1";
                        }else
                        {
                            msg += "0";
                        }
                        msg += ";";
                        msg += "[GEGL]";
                        msg += "1";
                        msg += ";";
                        msg += "[FAN]";
                        msg += "AUTO";
                        msg += ";";
                        msg += "[F]";
                        msg += "AUTO";
                        msg += ";";
                        msg += "[N]";
                        msg += "AUTO";
                        msg += ";";
                        msg += "[KOM]";
                        msg += "";
                        msg += ";";
                        msg += "[BEZ]";
                        msg += "Kreistasche";
                        msg += ";";
                        msg += "[AFB]";
                        msg += "1";
                        msg += ";";
                        msg += "#ENDE#";
                        msg += "\n";
                    }
                }else
                {
                    //Fehler melden:
                    QString msg = fehler_kein_WKZ("ggf", zeile);
                    QMessageBox mb;
                    mb.setText(msg);
                    mb.exec();
                    //return msg;
                }
            }
        }else if(zeile.zeile(1) == BEARBART_RTA)
        {
            rechtecktasche rt(zeile.text());
            QString tnummer = wkzmag.wkznummer_von_alias(rt.wkznum());//Ist direkt ei WKZ definiert?
            if(tnummer.isEmpty())
            {
                QString bezug = rt.bezug();
                double minmass = 0;
                if(rt.laenge() < rt.breite())
                {
                    minmass = rt.laenge();
                }else
                {
                    minmass = breite();
                }
                tnummer = wkzmag.wkznummer(WKZ_TYP_FRAESER, minmass, rt.tiefe(), Dicke, bezug);
            }
            if(!tnummer.isEmpty())
            {
                double zustellmas = rt.zustellmass();
                if(zustellmas <= 0)
                {
                    zustellmas = wkzmag.zustellmass(tnummer).toDouble();
                }

                double tiefe = 0;
                QString tiefe_qstring;
                if(rt.tiefe() > dicke())
                {
                    tiefe = dicke() - rt.tiefe();
                    tiefe_qstring = double_to_qstring(tiefe);
                }else if(dicke()-rt.tiefe() <= 2)
                {
                    if(dicke() == rt.tiefe())
                    {
                        tiefe_qstring  = "-2";
                    }else
                    {
                        tiefe_qstring  = "D-";
                        tiefe_qstring += double_to_qstring(dicke()-rt.tiefe());
                    }
                }else
                {
                    tiefe = rt.tiefe();
                    tiefe_qstring = double_to_qstring(tiefe);
                }

                double radius = rt.rad();

                if(rt.bezug() == WST_BEZUG_OBSEI)
                {
                    msg += ">RTASCHE:";
                    msg += "[wNAME]";
                    msg += tnummer;
                    msg += ";";
                    msg += "[wD]";
                    msg += wkzmag.dm(tnummer);
                    msg += ";";
                    msg += "[X]";
                    msg += rt.x_qstring();
                    msg += ";";
                    msg += "[Y]";
                    msg += rt.y_qstring();
                    msg += ";";
                    msg += "[TL]";
                    msg += rt.laenge_qstring();
                    msg += ";";
                    msg += "[TB]";
                    msg += rt.breite_qstring();
                    msg += ";";
                    msg += "[TT]";
                    msg += tiefe_qstring;
                    msg += ";";
                    msg += "[RAD]";
                    msg += double_to_qstring(radius);
                    msg += ";";
                    msg += "[ZUST]";
                    msg += "AUTO";
                    msg += ";";
                    msg += "[GEGL]";
                    msg += "1";
                    msg += ";";
                    msg += "[W]";
                    msg += rt.drewi_qstring();
                    msg += ";";
                    msg += "[AUSR]";
                    msg += rt.ausraeumen_qstring();;
                    msg += ";";
                    msg += "[FAN]";
                    msg += "AUTO";
                    msg += ";";
                    msg += "[F]";
                    msg += "AUTO";
                    msg += ";";
                    msg += "[N]";
                    msg += "AUTO";
                    msg += ";";
                    msg += "[KOM]";
                    msg += "";
                    msg += ";";
                    msg += "[BEZ]";
                    msg += "Kreistasche";
                    msg += ";";
                    msg += "[AFB]";
                    msg += "1";
                    msg += ";";
                    msg += "[BEZPUNKT]";
                    msg += "5";//Mitte
                    msg += ";";
                    msg += "#ENDE#";
                    msg += "\n";
                }
            }else
            {
                //Mit Fehlermeldung abbrechen:
                QString msg = fehler_kein_WKZ("ggf", zeile);
                QMessageBox mb;
                mb.setText(msg);
                mb.exec();
                //return msg;
            }
        }else if(zeile.zeile(1) == BEARBART_FRAESERAUFRUF)
        {
            fraueseraufruf fa(zeile.text());
            QString tnummer = wkzmag.wkznummer_von_alias(fa.wkznum());
            if(!tnummer.isEmpty())
            {
                QString radkor = fa.radkor();
                QString anabtyp = "kein";
                if(radkor == FRKOR_L)
                {
                    radkor = "links";
                    anabtyp = "Bogen gegen den Uhrzeigersinn";
                }else if(radkor == FRKOR_M)
                {
                    radkor = "keine";
                    anabtyp = "kein";
                }else if(radkor == FRKOR_R)
                {
                    radkor = "rechts";
                    anabtyp = "Bogen im Uhrzeigersinn";
                }

                if(fa.bezug() == WST_BEZUG_OBSEI)
                {
                    msg += kommentar_ggf("--------------------");

                    msg += ">FAUFR:";
                    msg += "[wNAME]";
                    msg += tnummer;
                    msg += ";";
                    msg += "[BKO]";
                    msg += radkor;
                    msg += ";";
                    msg += "[X]";
                    msg += fa.x_qstring();
                    msg += ";";
                    msg += "[Y]";
                    msg += fa.y_qstring();
                    msg += ";";
                    msg += "[Z]";
                    msg += fa.tiefe_qstring();
                    msg += ";";
                    msg += "[ERG]";
                    msg += "0";
                    msg += ";";
                    msg += "[KD]";
                    msg += "0";
                    msg += ";";
                    msg += "[FAN]AUTO;[F]AUTO;[N]AUTO;";
                    msg += "[ANT]";
                    msg += anabtyp;
                    msg += ";";
                    msg += "[ABT]";
                    msg += anabtyp;
                    msg += ";";
                    msg += "[KOM]";
                    msg += "";
                    msg += ";";
                    msg += "[BEZ]";
                    msg += "Aufruf Fraeser";
                    msg += ";";
                    msg += "[AFB]1;";
                    msg += "[wD]";
                    msg += wkzmag.dm(tnummer);
                    msg += ";";
                    msg += "[ZUST]AUTO;#ENDE#";
                    msg += "\n";

                    //Fräsbahnen:
                    while(i+1<=bearb.zeilenanzahl())
                    {
                        zeile.set_text(bearb.zeile(i+1));

                        if(zeile.zeile(1) == BEARBART_FRAESERGERADE)
                        {
                            i++;
                            zeile.set_text(bearb.zeile(i));
                            //Gerade fräsen:
                            fraesergerade fg(zeile.text());
                            QString tiefe_fg = "0";
                            if(fg.ze() == fa.tiefe())
                            {
                                tiefe_fg = "Z"; //Tiefe beibehalten
                                                //Führt zu falschen Ergebissen, wenn manuell geschriebene
                                                //fmc-Programme eingelesen wurden, bei denen
                                                //die FKONs zwischen dem Fräseraufruf und dieser Gerade
                                                //nicht den selben Z-Wert haben!!!
                                                //Dieser Fall wird nicht erwartet....
                            }else
                            {
                                tiefe_fg = double_to_qstring(  dicke()-fg.ze()  );
                            }

                            msg += ">FGERADE:";
                            msg += "[X]";
                            msg += fg.xe_qstring();
                            msg += ";";
                            msg += "[Y]";
                            msg += fg.ye_qstring();
                            msg += ";";
                            msg += "[Z]";
                            msg += tiefe_fg;
                            msg += ";";
                            msg += "[RAD]ERG;";
                            msg += "[BEZ]";
                            msg += "--- gerade Fraesbahn";
                            msg += ";";
                            msg += "[AFB]";
                            msg += "1";
                            msg += ";";
                            msg += "#ENDE#";
                            msg += "\n";
                        }else if(zeile.zeile(1) == BEARBART_FRAESERBOGEN)
                        {
                            i++;
                            zeile.set_text(bearb.zeile(i));
                            //Bogen fräsen:
                            fraeserbogen fb(zeile.text());
                            QString tiefe_fb = "0";
                            if(fb.ze() == fa.tiefe())
                            {
                                tiefe_fb = "Z"; //Tiefe beibehalten
                                                //Führt zu falschen Ergebissen, wenn manuell geschriebene
                                                //fmc-Programme eingelesen wurden, bei denen
                                                //die FKONs zwischen dem Fräseraufruf und dieser Gerade
                                                //nicht den selben Z-Wert haben!!!
                                                //Dieser Fall wird nicht erwartet....
                            }else
                            {
                                tiefe_fb = double_to_qstring(  dicke()-fb.ze()  );
                            }
                            msg += ">FBOGEN:";
                            msg += "[X]";
                            msg += fb.xe_qstring();
                            msg += ";";
                            msg += "[Y]";
                            msg += fb.ye_qstring();
                            msg += ";";
                            msg += "[Z]";
                            msg += tiefe_fb;
                            msg += ";";
                            msg += "[RAD]";
                            msg += fb.rad_qstring();
                            msg += ";";
                            msg += "[BRICH]";
                            if(fb.uzs() == true)
                            {
                                msg += "uzs";
                            }else
                            {
                                msg += "guzs";
                            }
                            msg += ";";
                            msg += "[BEZ]";
                            msg += "--- gebogene Fraesbahn";
                            msg += ";";
                            msg += "[AFB]1;#ENDE#";
                            msg += "\n";
                        }else
                        {
                            break;
                        }
                    }

                    //--------------------------------------------
                    //Abfahren Fräser:
                    msg += ">FABFA:[BEZ]Abfahren Fraeser;[AFB]1;#ENDE#";
                    msg += "\n";

                    msg += kommentar_ggf("--------------------");
                }

            }else
            {
                //Mit Fehlermeldung abbrechen:
                QString msg = fehler_kein_WKZ("ggf", zeile);
                QMessageBox mb;
                mb.setText(msg);
                mb.exec();
                //return msg;
            }
        }
     }
     //---------------------------------------Bearbeitungen Unterseite:
     bool unterseite_hat_bearb = false;
     for(uint i=1 ; i<=bearb.zeilenanzahl() ; i++)
     {
         zeile.set_text(bearb.zeile(i));
         if(zeile.zeile(2) == WST_BEZUG_UNSEI)
         {
             unterseite_hat_bearb = true;
             break;
         }
     }
     if(unterseite_hat_bearb == true)
     {
         for(uint i=1 ; i<=bearb.zeilenanzahl() ; i++)
         {
             //...
         }
     }
     //---------------------------------------Programmende:
     msg += ">PRGENDE:";
     msg += "[MODUS]";
     msg += "benutzerdefiniert";
     msg += ";";
     msg += "[X]";
     msg += "400";
     msg += ";";
     msg += "[Y]";
     msg += "400";
     msg += ";";
     msg += "[Z]";
     msg += "100";
     msg += ";";
     msg += "[BEZ]";
     msg += "Programmende";
     msg += ";";
     msg += "[AFB]";
     msg += "1";
     msg += ";";
     msg += "#ENDE#";
     msg += "\n";
     //---------------------------------------letzte Zeile:
     msg += ">ENDE";


     return msg;
}
QString werkstueck::eigen_dateitext(text_zeilenweise bearb, double tmp_l, double tmp_b, \
                                        QString ausgabeformat, text_zeilenweise wkzmagazin,\
                                        bool formartierungen_aufbrechen, \
                                        bool fkon_kantenschonend)
{
    if(ausgabeformat == FMC)
    {
        bearb = dubosplitten(bearb, wkzmagazin, dicke());
        bearb = rasterbohrungen_finden_fmc(bearb, wkzmagazin, tmp_l, tmp_b);
    }else if(ausgabeformat == GANX)
    {
        bearb = rasterbohrungen_finden_ganx(bearb, wkzmagazin, tmp_l, tmp_b);
        bearb = dubosplitten(bearb, wkzmagazin, dicke());
    }
    QString msg = "";
    bearb_sortieren();
    if(formartierungen_aufbrechen == true)
    {
        bearb = formartierung_zu_einzelfkon(bearb, tmp_l, tmp_b);
    }
    if(fkon_kantenschonend == true)
    {
        bearb = fkon_kantengut(bearb, wkzmagazin, tmp_l, tmp_b);
    }

    //Programmkopf:
    msg += name();
    msg += "\n";
    msg += "L: ";
    msg += double_to_qstring(tmp_l);
    msg += "\n";
    msg += "B: ";
    msg += double_to_qstring(tmp_b);
    msg += "\n";
    msg += "D: ";
    msg += dicke_qstring();
    msg += "\n";
    msg += "---------------";
    msg += "\n";
    //Kanteninfo:
    msg += "Kante vorne: \t\"";
    msg += Kante_vo;
    msg += "\"\n";
    msg += "Kante hinten: \t\"";
    msg += Kante_hi;
    msg += "\"\n";
    msg += "Kante links: \t\"";
    msg += Kante_li;
    msg += "\"\n";
    msg += "Kante rechts: \t\"";
    msg += Kante_re;
    msg += "\"\n";
    msg += "---------------";
    msg += "\n";

    msg += bearb.text();

    return msg;
}
QString werkstueck::kommentar_fmc(QString kom)
{
    QString text;
    text = FMC_KOMMENTAR;
    text += "\n";
    text += FMC_KOMMENTAR_TEXT;
    text += "=";
    text += kom;
    text += "\n";
    text += "\n";
    return text;
}
QString werkstueck::kommentar_ggf(QString kom)
{
    QString text;
    text = ">KOMMENTAR:[KOM]";
    text += kom;
    text += ";[AFB]1;#ENDE#";
    text += "\n";
    return text;
}
QString werkstueck::fmc_kommentar_gute_seite(text_zeilenweise bearb)
{
    QString retmsg;
    if(Name.contains("Seite"))
    {
        bool hat_5er_durchgangsbohrungen = false;
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        for(uint i=1; i<=Bearbeitungen.zeilenanzahl() ;i++)
        {
            zeile.set_text(bearb.zeile(i));
            if(zeile.zeile(1) == BEARBART_BOHR)
            {
                bohrung bo(zeile.text());
                if(bo.dm() == 5)
                {
                    if(bo.tiefe() > Dicke  ||  bo.tiefe() < 0)
                    {
                        hat_5er_durchgangsbohrungen = true;
                    }
                }
            }
        }
        if(hat_5er_durchgangsbohrungen == true)
        {
            retmsg = "gut oben";
        }else
        {
            retmsg = "gut unten";
        }
    }else if(Name.contains("MS"))
    {
        retmsg = "gut oben";
    }else if(Name.contains("OB"))
    {
        retmsg = "gut oben";
    }else if(Name.contains("UB"))
    {
        int anz_obsei = 0;
        int anz_unsei = 0;
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        for(uint i=1; i<=Bearbeitungen.zeilenanzahl() ;i++)
        {
            zeile.set_text(bearb.zeile(i));
            if(zeile.zeile(1) == BEARBART_BOHR)
            {
                bohrung bo(zeile.text());
                if(bo.dm() == 15)
                {
                    if(bo.bezug() == WST_BEZUG_OBSEI)
                    {
                        anz_obsei++;
                    }else if(bo.bezug() == WST_BEZUG_UNSEI)
                    {
                        anz_unsei++;
                    }
                }
            }
        }
        if(anz_obsei > anz_unsei)
        {
            retmsg = "gut unten";
        }else
        {
            retmsg = "gut oben";
        }
    }else if(Name.contains("KB"))
    {
        retmsg = "gut unten";
    }else if(Name.contains("EB"))
    {
        retmsg = "gut unten";
    }else if(Name.contains("RW"))
    {
        retmsg = "gut unten";//Wert wird ggf. weiter unten überschrieben
        bool hat_5er_durchgangsbohrungen = false;
        bool hat_8er_flaechenbohrungen_obsei = false;
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        for(uint i=1; i<=Bearbeitungen.zeilenanzahl() ;i++)
        {
            zeile.set_text(bearb.zeile(i));
            if(zeile.zeile(1) == BEARBART_BOHR)
            {
                bohrung bo(zeile.text());
                if(bo.dm() == 5)
                {
                    if(bo.tiefe() > Dicke  ||  bo.tiefe() < 0)
                    {
                        hat_5er_durchgangsbohrungen = true;
                    }
                }else if(bo.dm() == 8)
                {
                    if(bo.tiefe() < Dicke &&  bo.bezug() == WST_BEZUG_OBSEI)
                    {
                        hat_8er_flaechenbohrungen_obsei = true;
                    }
                }
            }
        }
        if(hat_8er_flaechenbohrungen_obsei)
        {
            if(hat_5er_durchgangsbohrungen)
            {
                retmsg = "gut oben";
            }
        }
    }else if(Name.contains("Tuer"))
    {
        retmsg = "gut unten";
    }else if(Name.contains("Front") || Name.contains("front"))
    {
        retmsg = "gut unten";
    }else if(Name.contains("Blende") || Name.contains("blende"))
    {
        retmsg = "gut unten";
    }else if(Name.contains("Doppel") || Name.contains("doppel"))
    {
        retmsg = "gut unten";
    }else if(Name.contains("Paneel") || Name.contains("paneel"))
    {
        retmsg = "gut unten";
    }else if(Name.contains("SF"))
    {
        retmsg = "gut unten";
    }else if(Name.contains("SB"))
    {
        retmsg = "gut unten";
    }else
    {
        retmsg = "(NULL)";
    }

    return retmsg;
}
bool werkstueck::punkt_auf_wst(double x, double y, double l, double b, double tolleranz)
{
    bool returnwert = true;
    if(x <= 0+tolleranz ||\
       x >= l-tolleranz ||\
       y <= 0+tolleranz ||\
       y >= b-tolleranz)
    {
        returnwert = false;
    }
    return returnwert;
}

//--------------------------------------------------Manipulationen:
void werkstueck::bearb_sortieren()
{
    text_zeilenweise tz_bohr_vert;
    text_zeilenweise tz_bohr_hori;
    text_zeilenweise tz_rta;            //Rechtecktaschen

    //in for-Schleife bearb aufsplitten:
    //....

    //Reihenfolge der Bearbeitungen festlegen:
    //Bearbeitungen.clear();
    //Bearbeitungen.zeilen_anhaengen(tz_bohr_vert);
}
text_zeilenweise werkstueck::bearb_drehen_90(text_zeilenweise bearb, double& tmp_l, double& tmp_b)
{
    //diese Funktion dreht die Bearbeitungen um 90° im Uhrzeigersin

    for(uint i=1; i<=bearb.zeilenanzahl() ;i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(bearb.zeile(i));
        QString zeile_neu;

        if(zeile.zeile(1) == BEARBART_BOHR)
        {
            bohrung bo(zeile.text());
            double x = bo.x();
            double y = bo.y();
            QString bezug = bo.bezug();
            if(bezug == WST_BEZUG_OBSEI || bezug == WST_BEZUG_UNSEI)
            {
                bo.set_x(y);
                bo.set_y(tmp_l - x);
            }else if(bezug == WST_BEZUG_VO)
            {
                bo.set_bezug(WST_BEZUG_LI);
                bo.set_x(y);
                bo.set_y(tmp_l - x);
            }else if(bezug == WST_BEZUG_HI)
            {
                bo.set_bezug(WST_BEZUG_RE);
                bo.set_x(y);
                bo.set_y(tmp_l - x);
            }else if(bezug == WST_BEZUG_LI)
            {
                bo.set_bezug(WST_BEZUG_HI);
                bo.set_x(y);
                bo.set_y(tmp_l - x);
            }else if(bezug == WST_BEZUG_RE)
            {
                bo.set_bezug(WST_BEZUG_VO);
                bo.set_x(y);
                bo.set_y(tmp_l - x);
            }
            zeile_neu = bo.text();
        }else if(zeile.zeile(1) == BEARBART_BOHRRASTER)
        {
            bohrraster bora(zeile.text());
            double x = bora.x();
            double y = bora.y();
            QString bezug = bora.bezug();
            if(bezug == WST_BEZUG_OBSEI || bezug == WST_BEZUG_UNSEI)
            {
                bora.set_x(y);
                bora.set_y(tmp_l - x);
                uint anz_x = bora.anz_x();
                uint anz_y = bora.anz_y();
                bora.set_anz_x(anz_y);
                bora.set_anz_y(anz_x);
                double raster_x = bora.raster_x();
                double raster_y = bora.raster_y();
                bora.set_raster_x(raster_y);
                bora.set_raster_y(raster_x);
            }
            zeile_neu = bora.text();
        }else if(zeile.zeile(1) == BEARBART_RTA)
        {
            rechtecktasche rt(zeile.text());
            double x = rt.x();
            double y = rt.y();
            double tal = rt.laenge();
            double tab = rt.breite();
            QString bezug = rt.bezug();
            if(bezug == WST_BEZUG_OBSEI || bezug == WST_BEZUG_UNSEI)
            {
                rt.set_x(y);
                rt.set_y(tmp_l - x);
                rt.set_laenge(tab);
                rt.set_breite(tal);
            }else if(bezug == WST_BEZUG_VO)
            {
                rt.set_bezug(WST_BEZUG_LI);
                rt.set_x(y);
                rt.set_y(tmp_l - x);
            }else if(bezug == WST_BEZUG_HI)
            {
                rt.set_bezug(WST_BEZUG_RE);
                rt.set_x(y);
                rt.set_y(tmp_l - x);
            }else if(bezug == WST_BEZUG_LI)
            {
                rt.set_bezug(WST_BEZUG_HI);
                rt.set_x(y);
                rt.set_y(tmp_l - x);
            }else if(bezug == WST_BEZUG_RE)
            {
                rt.set_bezug(WST_BEZUG_VO);
                rt.set_x(y);
                rt.set_y(tmp_l - x);
            }
            zeile_neu = rt.text();
        }else if(zeile.zeile(1) == BEARBART_NUT)
        {
            nut nu(zeile.text());
            double xs = nu.xs();
            double ys = nu.ys();
            double xe = nu.xe();
            double ye = nu.ye();

            nu.set_xs(ys);
            nu.set_ys(tmp_l - xs);
            nu.set_xe(ye);
            nu.set_ye(tmp_l - xe);

            zeile_neu = nu.text();
        }else if(zeile.zeile(1) == BEARBART_FRAESERAUFRUF)
        {
            fraueseraufruf tmp(zeile.text());
            double x = tmp.x();
            double y = tmp.y();

            tmp.set_x(y);
            tmp.set_y(tmp_l - x);
            zeile_neu = tmp.text();
        }else if(zeile.zeile(1) == BEARBART_FRAESERGERADE)
        {
            fraesergerade tmp(zeile.text());
            double xs = tmp.xs();
            double xe = tmp.xe();
            double ys = tmp.ys();
            double ye = tmp.ye();

            tmp.set_xs(ys);
            tmp.set_xe(ye);
            tmp.set_ys(tmp_l - xs);
            tmp.set_ye(tmp_l - xe);
            zeile_neu = tmp.text();
        }else if(zeile.zeile(1) == BEARBART_FRAESERBOGEN)
        {
            fraeserbogen tmp(zeile.text());
            double xs = tmp.xs();
            double xe = tmp.xe();
            double ys = tmp.ys();
            double ye = tmp.ye();

            tmp.set_xs(ys);
            tmp.set_xe(ye);
            tmp.set_ys(tmp_l - xs);
            tmp.set_ye(tmp_l - xe);
            zeile_neu = tmp.text();
        }

        bearb.zeile_ersaetzen(i, zeile_neu);
    }
    //Länge und Breite tauschen:
    double tmp;
    tmp = tmp_l;
    tmp_l = tmp_b;
    tmp_b = tmp;


    return bearb;
}
text_zeilenweise werkstueck::bearb_optimieren_ganx(text_zeilenweise bearb)
{
    //X-Werte werden Y-Werte und umgehrt
    //Bearbeitungen wechseln von der Ober- auf die Unterseite und umgehrt

    for(uint i=1; i<=bearb.zeilenanzahl() ;i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(bearb.zeile(i));
        QString zeile_neu;

        if(zeile.zeile(1) == BEARBART_BOHR)
        {
            bohrung bo(zeile.text());
            double x = bo.x();
            double y = bo.y();
            double z = bo.z();
            QString bezug = bo.bezug();
            if(bezug == WST_BEZUG_OBSEI)
            {
                bo.set_bezug(WST_BEZUG_UNSEI);
                bo.set_x(y);
                bo.set_y(x);
            }else if(bezug == WST_BEZUG_UNSEI)
            {
                bo.set_bezug(WST_BEZUG_OBSEI);
                bo.set_x(y);
                bo.set_y(x);
            }else if(bezug == WST_BEZUG_VO)
            {
                bo.set_bezug(WST_BEZUG_LI);
                bo.set_x(y);
                bo.set_y(x);
                bo.set_z(Dicke-z);
            }else if(bezug == WST_BEZUG_HI)
            {
                bo.set_bezug(WST_BEZUG_RE);
                bo.set_x(y);
                bo.set_y(x);
                bo.set_z(Dicke-z);
            }else if(bezug == WST_BEZUG_LI)
            {
                bo.set_bezug(WST_BEZUG_VO);
                bo.set_x(y);
                bo.set_y(x);
                bo.set_z(Dicke-z);
            }else if(bezug == WST_BEZUG_RE)
            {
                bo.set_bezug(WST_BEZUG_HI);
                bo.set_x(y);
                bo.set_y(x);
                bo.set_z(Dicke-z);
            }
            zeile_neu = bo.text();
        }else if(zeile.zeile(1) == BEARBART_BOHR)
        {
            bohrraster bora(zeile.text());
            double x = bora.x();
            double y = bora.y();
            //double z = bora.z();
            QString bezug = bora.bezug();
            if(bezug == WST_BEZUG_OBSEI)
            {
                bora.set_bezug(WST_BEZUG_UNSEI);
                bora.set_x(y);
                bora.set_y(x);
                uint anz_x = bora.anz_x();
                uint anz_y = bora.anz_y();
                bora.set_anz_x(anz_y);
                bora.set_anz_y(anz_x);
                double raster_x = bora.raster_x();
                double raster_y = bora.raster_y();
                bora.set_raster_x(raster_y);
                bora.set_raster_y(raster_x);
            }else if(bezug == WST_BEZUG_UNSEI)
            {
                bora.set_bezug(WST_BEZUG_OBSEI);
                bora.set_x(y);
                bora.set_y(x);
                uint anz_x = bora.anz_x();
                uint anz_y = bora.anz_y();
                bora.set_anz_x(anz_y);
                bora.set_anz_y(anz_x);
                double raster_x = bora.raster_x();
                double raster_y = bora.raster_y();
                bora.set_raster_x(raster_y);
                bora.set_raster_y(raster_x);
            }
            zeile_neu = bora.text();
        }else if(zeile.zeile(1) == BEARBART_RTA)
        {
            rechtecktasche rt(zeile.text());
            double x = rt.x();
            double y = rt.y();
            double z = rt.z();
            double tal = rt.laenge();
            double tab = rt.breite();
            QString bezug = rt.bezug();
            if(bezug == WST_BEZUG_OBSEI)
            {
                rt.set_bezug(WST_BEZUG_UNSEI);
                rt.set_x(y);
                rt.set_y(x);
                rt.set_laenge(tab);
                rt.set_breite(tal);
            }else if(bezug == WST_BEZUG_UNSEI)
            {
                rt.set_bezug(WST_BEZUG_OBSEI);
                rt.set_x(y);
                rt.set_y(x);
                rt.set_laenge(tab);
                rt.set_breite(tal);
            }else if(bezug == WST_BEZUG_VO)
            {
                rt.set_bezug(WST_BEZUG_LI);
                rt.set_x(y);
                rt.set_y(x);
                rt.set_z(Dicke-z);
            }else if(bezug == WST_BEZUG_HI)
            {
                rt.set_bezug(WST_BEZUG_RE);
                rt.set_x(y);
                rt.set_y(x);
                rt.set_z(Dicke-z);
            }else if(bezug == WST_BEZUG_LI)
            {
                rt.set_bezug(WST_BEZUG_VO);
                rt.set_x(y);
                rt.set_y(x);
                rt.set_z(Dicke-z);
            }else if(bezug == WST_BEZUG_RE)
            {
                rt.set_bezug(WST_BEZUG_HI);
                rt.set_x(y);
                rt.set_y(x);
                rt.set_z(Dicke-z);
            }
            zeile_neu = rt.text();
        }else if(zeile.zeile(1) == BEARBART_NUT)
        {
            nut nu(zeile.text());
            double xs = nu.xs();
            double ys = nu.ys();
            double xe = nu.xe();
            double ye = nu.ye();
            QString bezug = nu.bezug();
            if(bezug == WST_BEZUG_OBSEI)
            {
                nu.set_bezug(WST_BEZUG_UNSEI);
                nu.set_xs(ys);
                nu.set_ys(xs);
                nu.set_xe(ye);
                nu.set_ye(xe);
            }else if(bezug == WST_BEZUG_UNSEI)
            {
                nu.set_bezug(WST_BEZUG_OBSEI);
                nu.set_xs(ys);
                nu.set_ys(xs);
                nu.set_xe(ye);
                nu.set_ye(xe);
            }
            zeile_neu = nu.text();
        }else if(zeile.zeile(1) == BEARBART_GEHRUNG)
        {
            gehrung ge(zeile.text());   //nut nu(zeile.text());
            double xs = ge.pfad().stapu().x(); //nu.xs();
            double ys = ge.pfad().stapu().y(); //nu.ys();
            double xe = ge.pfad().endpu().x(); //nu.xe();
            double ye = ge.pfad().endpu().y(); //nu.ye();
            QString bezug = ge.bezug();
            if(bezug == WST_BEZUG_OBSEI)
            {
                ge.set_bezug(WST_BEZUG_UNSEI);
            }else //if(bezug == WST_BEZUG_UNSEI)
            {
                ge.set_bezug(WST_BEZUG_OBSEI);
            }
            punkt3d sp, ep;
            sp.set_x(ys);
            sp.set_y(xs);
            ep.set_x(ye);
            ep.set_y(xe);
            strecke s;
            s.set_start(sp);
            s.set_ende(ep);
            ge.set_pfad(s);
            zeile_neu = ge.text();
        }
        bearb.zeile_ersaetzen(i, zeile_neu);
    }
    return bearb;
}
text_zeilenweise werkstueck::rasterbohrungen_finden_ganx(text_zeilenweise bearb, text_zeilenweise wkzmagazin,\
                                                         double tmp_l, double tmp_b)
{
    bohrraster bora;

    text_zeilenweise wkzbodm; //Speichert die verschiedenen vorhandenen Bohrdurchmesser
    werkzeugmagazin magazin(wkzmagazin);
    int min_rasterbohrungen_anz = 2;

    text_zeilenweise boti;
    for(uint i=1; i<= bearb.zeilenanzahl() ;i++)
    {
        text_zeilenweise param;
        param.set_trennzeichen(TRENNZ_BEARB_PARAM);
        param.set_text(bearb.zeile(i));
        if(param.zeile(1) == BEARBART_BOHR)
        {
            bohrung b(param.text());
            QString tiefe_neu = b.tiefe_qstring();
            bool schon_da = false;
            for(uint i=1; i<=boti.zeilenanzahl();i++)
            {
                if(tiefe_neu == boti.zeile(i))
                {
                    schon_da = true;
                }
            }
            if(schon_da == false)
            {
                boti.zeile_anhaengen(tiefe_neu);
            }
        }
    }

    //Alle vertikalen Lochraster finden die zu Bohrern im Werkzeugmagazin passen:
    wkzbodm = magazin.alle_bodm(WKZ_PARAMETER_LAGE_VERT);

    for(uint i=1; i<=wkzbodm.zeilenanzahl() ;i++)
    {
        double dm = wkzbodm.zeile(i).toDouble();

        for(uint i=1; i<=boti.zeilenanzahl() ; i++)
        {
            double tiefe = boti.zeile(i).toDouble();
            bool raster_gefunden;

            //-------------------------------------------------------------------------------
            //Oberseite  0_bis_L:
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_OBSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_L,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        32);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_OBSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_L,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        64);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_OBSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_L,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        96);
            }
            //-------------------------------------------------------------------------------
            //Oberseite  0_bis_B:
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_OBSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_B,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        32);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_OBSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_B,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        64);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_OBSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_B,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        96);
            }
            //-------------------------------------------------------------------------------
            //Unterseite  0_bis_L:
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_UNSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_L,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        32);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_UNSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_L,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        64);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_UNSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_L,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        96);
            }
            //-------------------------------------------------------------------------------
            //Unterseite  0_bis_B:
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_UNSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_B,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        32);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_UNSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_B,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        64);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_UNSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_B,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        96);
            }
        }


    }

    return bearb;
}
text_zeilenweise werkstueck::rasterbohrungen_finden_fmc(text_zeilenweise bearb, text_zeilenweise wkzmagazin,\
                                                        double tmp_l, double tmp_b)
{
    bohrraster bora;

    text_zeilenweise wkzbodm; //Speichert die verschiedenen vorhandenen Bohrdurchmesser
    werkzeugmagazin magazin(wkzmagazin);
    int min_rasterbohrungen_anz = 3;

    text_zeilenweise boti;
    for(uint i=1; i<= bearb.zeilenanzahl() ;i++)
    {
        text_zeilenweise param;
        param.set_trennzeichen(TRENNZ_BEARB_PARAM);
        param.set_text(bearb.zeile(i));
        if(param.zeile(1) == BEARBART_BOHR)
        {
            bohrung b(param.text());
            QString tiefe_neu = b.tiefe_qstring();
            bool schon_da = false;
            for(uint i=1; i<=boti.zeilenanzahl();i++)
            {
                if(tiefe_neu == boti.zeile(i))
                {
                    schon_da = true;
                }
            }
            if(schon_da == false)
            {
                boti.zeile_anhaengen(tiefe_neu);
            }
        }
    }

    //Alle vertikalen Lochraster finden die zu Bohrern im Werkzeugmagazin passen:
    wkzbodm = magazin.alle_bodm(WKZ_PARAMETER_LAGE_VERT);

    for(uint i=1; i<=wkzbodm.zeilenanzahl() ;i++)
    {
        double dm = wkzbodm.zeile(i).toDouble();

        for(uint i=1; i<=boti.zeilenanzahl() ; i++)
        {
            double tiefe = boti.zeile(i).toDouble();
            bool raster_gefunden;

            //-------------------------------------------------------------------------------
            //Oberseite  0_bis_L:
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_OBSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_L,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        32);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_OBSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_L,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        64);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_OBSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_L,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        96);
            }
            //-------------------------------------------------------------------------------
            //Oberseite  0_bis_B:
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_OBSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_B,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        32);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_OBSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_B,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        64);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_OBSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_B,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        96);
            }
            //-------------------------------------------------------------------------------
            //Unterseite  0_bis_L:
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_UNSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_L,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        32);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_UNSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_L,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        64);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_UNSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_L,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        96);
            }
            //-------------------------------------------------------------------------------
            //Unterseite  0_bis_B:
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_UNSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_B,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        32);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_UNSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_B,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        64);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_UNSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_B,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        96);
            }
        }
    }

    //HBEs im Raser finden die zu Bohrern im Werkzeugmagazin passen:
    wkzbodm = magazin.alle_bodm(WKZ_PARAMETER_LAGE_HORI);

    for(uint i=1; i<=wkzbodm.zeilenanzahl() ;i++)
    {
        double dm = wkzbodm.zeile(i).toDouble();

        for(uint i=1; i<=boti.zeilenanzahl() ; i++)
        {
            double tiefe = boti.zeile(i).toDouble();
            bool raster_gefunden;

            //-------------------------------------------------------------------------------
            //vorne 0_bis_L:
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_VO, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_L,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        32);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_VO, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_L,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        64);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_VO, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_L,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        96);
            }
            //-------------------------------------------------------------------------------
            //hinten 0_bis_L:
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_HI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_L,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        32);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_HI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_L,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        64);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_HI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_L,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        96);
            }
            //-------------------------------------------------------------------------------
            //links 0_bis_B:
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_LI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_B,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        32);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_LI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_B,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        64);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_LI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_B,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        96);
            }
            //-------------------------------------------------------------------------------
            //rechts 0_bis_B:
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_RE, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_B,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        32);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_RE, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_B,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        64);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_RE, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_B,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        96);
            }
        }
    }

    return bearb;
}
text_zeilenweise werkstueck::formartierung_zu_einzelfkon(text_zeilenweise bearb, \
                                                         double tmp_l, double tmp_b)
{
    //Diese Funktion soll die vom VW ausgegebenen Poligonförmigen Formartierungen entdecken.
    //Diese werden generiert, wenn die Grundfläche eines 3D-Bauteils kein Rechteck ist
    //Die Bestandteile der Fräskontur, die deckungsgleich auf der Kante liegen werden nicht benötigt
    //Und werden durch diese Funktion heraus genommen

    //Prüfen ob wst eine umlaufende Formartierung enthällt:
    for(uint i=1; i<= bearb.zeilenanzahl() ;i++)
    {
        text_zeilenweise param;
        param.set_trennzeichen(TRENNZ_BEARB_PARAM);
        param.set_text(bearb.zeile(i));
        if(param.zeile(1) == BEARBART_FRAESERAUFRUF)
        {
            uint zeibeg = i;
            uint zeiend = i;
            fraueseraufruf fa(param.text());
            double xbeg = fa.x();
            double ybeg = fa.y();
            double zbeg = fa.tiefe();
            double xend = xbeg;
            double yend = ybeg;
            double zend = zbeg;
            double xmin = xbeg;
            double xmax = xbeg;
            double ymin = ybeg;
            double ymax = ybeg;
            if(i<= bearb.zeilenanzahl())
            {
                i++;
                for(; i<= bearb.zeilenanzahl() ;i++)
                {
                    param.set_text(bearb.zeile(i));
                    if(param.zeile(1) == BEARBART_FRAESERGERADE)
                    {
                        fraesergerade fg(param.text());
                        xend = fg.xe();
                        yend = fg.ye();
                        zend = fg.ze();
                        zeiend = i;
                        if(xend > xmax)
                        {
                            xmax = xend;
                        }
                        if(xend < xmin)
                        {
                            xmin = xend;
                        }
                        if(yend > ymax)
                        {
                            ymax = yend;
                        }
                        if(yend < ymin)
                        {
                            ymin = yend;
                        }
                    }else if(param.zeile(1) == BEARBART_FRAESERBOGEN)
                    {
                        fraeserbogen fb(param.text());
                        xend = fb.xe();
                        yend = fb.ye();
                        zend = fb.ze();
                        zeiend = i;
                        if(xend > xmax)
                        {
                            xmax = xend;
                        }
                        if(xend < xmin)
                        {
                            xmin = xend;
                        }
                        if(yend > ymax)
                        {
                            ymax = yend;
                        }
                        if(yend < ymin)
                        {
                            ymin = yend;
                        }
                    }else
                    {
                        break;
                    }
                }
            }
            if(zeibeg != zeiend)
            {
                //Prüfen ob Start- und Endpunkt gleich sind:
                if(xbeg == xend && ybeg == yend && zbeg == zend)//evtl. ist hier cagleich nötig!!
                {
                    //Prüfen ob fkon Formartierung ist:
                    if(xmin <= 0        &&\
                       xmax >= tmp_l    &&\
                       ymin <= 0        &&\
                       ymax >= tmp_b)
                    {
                        //Die Teile aus der Bearbeitung löschen die Deckungsgleich auf der WST-Kante liegen
                        text_zeilenweise bearb_neu;
                        bearb_neu.set_text(fa.text());

                        for(uint ii=zeibeg+1; ii<=zeiend ;ii++)
                        {
                            text_zeilenweise param;
                            param.set_trennzeichen(TRENNZ_BEARB_PARAM);
                            param.set_text(bearb.zeile(ii));
                            if(param.zeile(1) == BEARBART_FRAESERGERADE)
                            {
                                fraesergerade fg(param.text());
                                bool loeschen = false;
                                if((fg.xs() == fg.xe()) && (fg.ys() != fg.ye()))
                                {
                                    //Gerade ist senkrecht
                                    if((fg.xs() == 0) || (fg.xs()== tmp_l))
                                    {
                                        //Gerade liegt auf der WST-Kante
                                        loeschen = true;
                                    }
                                }else if((fg.xs() != fg.xe()) && (fg.ys() == fg.ye()))
                                {
                                    //Gerade ist wagerecht
                                    if((fg.ys() == 0) || (fg.ys()== tmp_b))
                                    {
                                        //Gerade liegt auf der WST-Kante
                                        loeschen = true;
                                    }
                                }
                                if(loeschen == true)
                                {
                                    QString vorzeile = bearb_neu.zeile(bearb_neu.zeilenanzahl());
                                    text_zeilenweise vorparam;
                                    vorparam.set_trennzeichen(TRENNZ_BEARB_PARAM);
                                    vorparam.set_text(vorzeile);
                                    if(vorparam.zeile(1) == BEARBART_FRAESERAUFRUF)
                                    {
                                        fraueseraufruf tmpfa(vorparam.text());
                                        tmpfa.set_x(fg.xe());
                                        tmpfa.set_y(fg.ye());
                                        bearb_neu.zeile_ersaetzen(bearb_neu.zeilenanzahl(), tmpfa.text());
                                    }else
                                    {
                                        fa.set_x(fg.xe());
                                        fa.set_y(fg.ye());
                                        bearb_neu.zeile_anhaengen(fa.text());
                                    }
                                }else
                                {
                                    bearb_neu.zeile_anhaengen(bearb.zeile(ii));
                                }
                            }else
                            {
                                bearb_neu.zeile_anhaengen(bearb.zeile(ii));
                            }
                        }
                        //prüfen ob letzte Zeile von bearb_neu fa ist und ggf löschen:
                        text_zeilenweise endparam;
                        endparam.set_trennzeichen(TRENNZ_BEARB_PARAM);
                        endparam.set_text(bearb_neu.zeile(bearb_neu.zeilenanzahl()));
                        if(endparam.zeile(1) == BEARBART_FRAESERAUFRUF)
                        {
                            bearb_neu.zeile_loeschen(bearb_neu.zeilenanzahl());
                        }

                        //bearb.zeile(zeibeg bis zeiend) gegen bearb_neu austauschen:
                        if(zeiend < bearb.zeilenanzahl())
                        {
                            bearb.zeilen_loeschen(zeibeg, zeiend-zeibeg+1);
                            bearb.zeilen_einfuegen(zeibeg-1, bearb_neu.text());
                            i = zeibeg-1+bearb_neu.zeilenanzahl();
                        }else
                        {
                            bearb.zeilen_loeschen(zeibeg, zeiend-zeibeg+1);
                            bearb.zeilen_anhaengen(bearb_neu.text());
                            i = bearb.zeilenanzahl();
                        }

                    }
                }
            }
        }
    }
    return bearb;
}
text_zeilenweise werkstueck::kurze_an_ab_geraden(text_zeilenweise bearb, text_zeilenweise wkzmagazin)
{
    //Geraden die Kürzer sind als der Fräser-Durchmesser und ungünstig liegen kann
    //die CNC-Maschine nicht korrekt verarbeiten
    //in Folge fährt die CNC einen ungewollten Kringel
    //Dies soll durch diese Funktion verringert werden
    werkzeugmagazin wkzmag(wkzmagazin);
    double wkzdm;
    double afb = false; //Bei Fräserradiuskorrektur 0 soll die Funktion keine Änderungen vornehmen

    for(uint i=1; i<= bearb.zeilenanzahl() ;i++)
    {
        text_zeilenweise param;
        param.set_trennzeichen(TRENNZ_BEARB_PARAM);
        param.set_text(bearb.zeile(i));
        if(param.zeile(1) == BEARBART_FRAESERAUFRUF)//zu Kurze Geraden am Anfang finden
        {
            fraueseraufruf fa(param.text());
            if(  fa.radkor() == FRKOR_L  ||  fa.radkor() == FRKOR_R  )
            {
                afb = true;
            }else
            {
                afb = false;
                continue; //For-Schleife in die nächste Runde
            }
            QString tnummer = wkzmag.wkznummer_von_alias(fa.wkznum());
            if(!tnummer.isEmpty())
            {
                wkzdm = wkzmag.dm(tnummer).toDouble();
            }else
            {
                wkzdm = 2;//Defaultwert
            }

            if(i+1 <= bearb.zeilenanzahl())
            {
                text_zeilenweise param2; //Folgezeile
                param2.set_trennzeichen(TRENNZ_BEARB_PARAM);
                param2.set_text(bearb.zeile(i+1));
                if(param2.zeile(1) == BEARBART_FRAESERGERADE)
                {
                    fraesergerade fg(param2.text());
                    punkt3d sp,ep;
                    sp.set_x(param2.zeile(3));
                    sp.set_y(param2.zeile(4));
                    ep.set_x(param2.zeile(6));
                    ep.set_y(param2.zeile(7));
                    strecke s;
                    s.set_start(sp);
                    s.set_ende(ep);

                    if(wkzdm >= s.laenge2d())
                    {
                        s.set_laenge_2d(wkzdm+1, strecke_bezugspunkt_ende);
                        fa.set_x(s.stapu().x());
                        fa.set_y(s.stapu().y());
                        fg.set_xs(s.stapu().x());
                        fg.set_ys(s.stapu().y());
                        bearb.zeile_ersaetzen(i, fa.text());
                        bearb.zeile_ersaetzen(i+1, fg.text());
                        i++;
                    }
                }
            }
        }else if(param.zeile(1) == BEARBART_FRAESERGERADE  &&  afb == true)//zu Kurze Geraden am Ende finden
        {
            bool ist_schlussgerade = false;
            if(i+1 <= bearb.zeilenanzahl())
            {
                text_zeilenweise param2; //Folgezeile
                param2.set_trennzeichen(TRENNZ_BEARB_PARAM);
                param2.set_text(bearb.zeile(i+1));
                if(  param2.zeile(1) != BEARBART_FRAESERGERADE  &&  param2.zeile(1) != BEARBART_FRAESERBOGEN  )
                {
                    ist_schlussgerade = true;
                }
            }else
            {
                ist_schlussgerade = true;
            }
            if(ist_schlussgerade == true)
            {
                fraesergerade fg(param.text());
                punkt3d sp,ep;
                sp.set_x(param.zeile(3));
                sp.set_y(param.zeile(4));
                ep.set_x(param.zeile(6));
                ep.set_y(param.zeile(7));
                strecke s;
                s.set_start(sp);
                s.set_ende(ep);
                if(wkzdm >= s.laenge2d())
                {
                    s.set_laenge_2d(wkzdm+1, strecke_bezugspunkt_start);
                    fg.set_xe(s.endpu().x());
                    fg.set_ye(s.endpu().y());
                    bearb.zeile_ersaetzen(i, fg.text());
                }
            }
        }
    }
    return bearb;
}
text_zeilenweise werkstueck::dubosplitten(text_zeilenweise bearb, text_zeilenweise wkzmagazin, double wstdicke)
{
    //Diese Funktion soll Durchgangs-Bohrungen finden
    //Gibt es für eine Durchgangsbohrung keinen Duchgangsborer so soll das Loch von beiden Plattenseiten gebohrt werden
    //Gibt es einen Durchgangsbohrer, dieser ist jedoch zu kurz so soll das Loch von beiden Plattenseiten gebohrt werden
    //Diese Funktion sollte vor der Funktion zum finden von Bohrrastern aufgerufen werden
    //da Bohrraster hier nicht berücksichtigt werden
    werkzeugmagazin wkzmag(wkzmagazin);
    text_zeilenweise bearb_neu;

    for(uint i=1; i<= bearb.zeilenanzahl() ;i++)
    {
        bool editiert = false;
        text_zeilenweise param;
        param.set_trennzeichen(TRENNZ_BEARB_PARAM);
        param.set_text(bearb.zeile(i));
        if(param.zeile(1) == BEARBART_BOHR)
        {
            QString bezflaeche = param.zeile(2);
            if(bezflaeche == WST_BEZUG_OBSEI  ||  bezflaeche == WST_BEZUG_UNSEI  )
            {
                bohrung bo(param.text());
                if(bo.tiefe() >= wstdicke)
                {
                    QString tnummer = wkzmag.wkznummer(WKZ_TYP_BOHRER, bo.dm(), bo.tiefe(), Dicke, bo.bezug());
                    if(tnummer.isEmpty())
                    {
                        bohrung boA = bo;
                        boA.set_tiefe(bo.tiefe()/2 + 2);
                        tnummer = wkzmag.wkznummer(WKZ_TYP_BOHRER, bo.dm(), boA.tiefe(), Dicke, bo.bezug());
                        if(!tnummer.isEmpty())
                        {
                            bohrung boB = boA;
                            if(boB.bezug() == WST_BEZUG_OBSEI)
                            {
                                boB.set_bezug(WST_BEZUG_UNSEI);
                            }else
                            {
                                boB.set_bezug(WST_BEZUG_OBSEI);
                            }
                            bearb_neu.zeile_anhaengen(boA.text());
                            bearb_neu.zeile_anhaengen(boB.text());
                            editiert = true;
                        }
                    }
                }
            }
        }
        if(editiert == false)
        {
            bearb_neu.zeile_anhaengen(bearb.zeile(i));
        }
    }
    return bearb_neu;
}
text_zeilenweise werkstueck::fkon_kantengut(text_zeilenweise bearb, text_zeilenweise wkzmagazin, double tmp_l, double tmp_b)
{
    //Diese Funktion soll Fräsungen entdecken die zum Abscheren der ABS-Kante führen
    //Also Fräsungen von Werkstückmitte in Richtung Kante
    //Wird eine solche Fräsung gefunden, so soll diese intweder in der Lufrichtung umgekehrt werden
    //Oder in 2 Einzelfräskonturen zerteilt werden
    //Dies ist jeweis nur dann möglich, wenn es einen Spiegelfräser gibt damit aus Gegenlauf nicht
    //Gleichlauf wird

    return bearb;
}
void werkstueck::hbemiduebeltiefe()
{
    //Diese Funktion stellt die Lochtiefe für die Dübel 8x30 bei den
    //HBEs einheitlich auf 18mm ein, damit es nicht zu Problemen in
    //der Fertigung kommt wenn die Löcher CNC-gebohrt werden und mit dem
    //Dübelautomaten die Dübel eingetrieben werden

    const double min = 16;//Maximale Dübellochtiefe
    const double max = 18;//Minimale Dübellochtiefe
    for(uint i=1 ; i<=Bearbeitungen.zeilenanzahl() ; i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(Bearbeitungen.zeile(i));
        if(zeile.zeile(1) == BEARBART_BOHR)
        {
            bohrung bo(zeile.text());
            QString bezug = bo.bezug();
            if(bezug == WST_BEZUG_LI || bezug == WST_BEZUG_RE || \
               bezug == WST_BEZUG_VO || bezug == WST_BEZUG_HI)
            {
                //Bohrung ist HBE
                if(bo.dm() == 8.2)
                {
                    double boti = bo.tiefe();
                    if(max >= boti && boti >= min)
                    {
                        bo.set_tiefe(max);
                        Bearbeitungen.zeile_ersaetzen(i, bo.text());
                    }
                }
            }
        }else if(zeile.zeile(1) == BEARBART_BOHRRASTER)
        {
            bohrraster bo(zeile.text());
            QString bezug = bo.bezug();
            if(bezug == WST_BEZUG_LI || bezug == WST_BEZUG_RE || \
               bezug == WST_BEZUG_VO || bezug == WST_BEZUG_HI)
            {
                //Bohrung ist HBE
                if(bo.dm() == 8.2)
                {
                    double boti = bo.tiefe();
                    if(max >= boti && boti >= min)
                    {
                        bo.set_tiefe(max);
                        Bearbeitungen.zeile_ersaetzen(i, bo.text());
                    }
                }
            }
        }
    }
}
void werkstueck::fraesergeraden_zusammenfassen()
{
    for(uint i=1 ; i<Bearbeitungen.zeilenanzahl() ; i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(Bearbeitungen.zeile(i));
        text_zeilenweise folgezeile;
        folgezeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        folgezeile.set_text(Bearbeitungen.zeile(i+1));

        if(zeile.zeile(1) == BEARBART_FRAESERGERADE &&\
           folgezeile.zeile(1) == BEARBART_FRAESERGERADE)
        {
            strecke s1, s2;
            fraesergerade fg1(zeile.text());
            fraesergerade fg2(folgezeile.text());
            s1=fg1.strecke_();
            s2=fg2.strecke_();
            strecke_bezugspunkt sb = strecke_bezugspunkt_start;
            s1.set_laenge_2d(s1.laenge2d()+s2.laenge2d(), sb );
            fg1.set_endpunkt(s1.endpu());
            //Vergleich der Strings statt der double da sonst ungleiche Nachkommastellen alles zu genau machen:
            if(fg1.xe_qstring() == fg2.xe_qstring() &&\
               fg1.ye_qstring() == fg2.ye_qstring() &&\
               fg1.ze_qstring() == fg2.ze_qstring()    )
            {
                Bearbeitungen.zeile_ersaetzen(i, fg1.text());
                Bearbeitungen.zeile_loeschen(i+1);
                i--;
            }
        }

    }
}
text_zeilenweise werkstueck::gehr_3achs(text_zeilenweise bearb, double &tmp_l, double &tmp_b, QString ausgabeformat)
{
    //Diese Funktion löscht die Gehrungen aus den Bearbeitungen heraus
    //Diese können mit einer 3-Achs-Maschine nicht ohne Spezial-WKS hergestellt werden.
    //und im Spezielle nicht mit beliebigem Winkel
    //ausgabeformate: fmc, ganx, eigen

    //Schritt 1:
    //Heraus bekommen ob Gehrungen vorhanden sind und wo sie liegen
    //Gehrungen löschen
    bool li = false;
    bool re = false;
    bool ob = false;
    bool un = false;

    for(uint i=1; i<=bearb.zeilenanzahl() ;i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(bearb.zeile(i));
        //QString zeile_neu;
        if(zeile.zeile(1) == BEARBART_GEHRUNG)
        {
            gehrung ge(zeile.text());
            double spx = ge.stapu().x();
            double spy = ge.stapu().y();
            double epx = ge.endpu().x();
            double epy = ge.endpu().y();
            if(spx == epx)//senkrecht
            {
                if(spx == 0)
                {
                    li = true;
                }else if(spx == tmp_l)
                {
                    re = true;
                }
            }else if(spy == epy)//waagerecht
            {
                if(spy == 0)
                {
                    un = true;
                }else if(spy == tmp_b)
                {
                    ob = true;
                }
            }
            bearb.zeile_loeschen(i);
            i--;
        }
    }

    //Schritt 2:
    //WST vergrößern
    //andere Bearbeitungen gem vergrößerung verschieben
    double zugabe = Zugabe_gehrungen;
    if(li == true) //X-Werte verschieben
    {
        tmp_l += zugabe;
        for(uint i=1; i<=bearb.zeilenanzahl() ;i++)
        {
            text_zeilenweise zeile;
            zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
            zeile.set_text(bearb.zeile(i));
            QString zeile_neu;
            if(zeile.zeile(1) == BEARBART_BOHR)
            {
                bohrung bo(zeile.text());
                bo.set_x(bo.x() + zugabe);
                zeile_neu = bo.text();
            }else if(zeile.zeile(1) == BEARBART_BOHRRASTER)
            {
                bohrraster bora(zeile.text());
                bora.set_x((bora.x() + zugabe));
                zeile_neu = bora.text();
            }else if(zeile.zeile(1) == BEARBART_RTA)
            {
                rechtecktasche rt(zeile.text());
                rt.set_x(rt.x() + zugabe);
                zeile_neu = rt.text();
            }else if(zeile.zeile(1) == BEARBART_NUT)
            {
                nut nu(zeile.text());
                nu.set_xs(nu.xs() + zugabe);
                nu.set_xe(nu.xe() + zugabe);
                zeile_neu = nu.text();
            }else if(zeile.zeile(1) == BEARBART_FRAESERAUFRUF)
            {
                fraueseraufruf tmp(zeile.text());
                tmp.set_x(tmp.x() + zugabe);
                zeile_neu = tmp.text();
            }else if(zeile.zeile(1) == BEARBART_FRAESERGERADE)
            {
                fraesergerade tmp(zeile.text());
                tmp.set_xs(tmp.xs() + zugabe);
                tmp.set_xe(tmp.xe() + zugabe);
                zeile_neu = tmp.text();
            }else if(zeile.zeile(1) == BEARBART_FRAESERBOGEN)
            {
                fraeserbogen tmp(zeile.text());
                tmp.set_xs(tmp.xs() + zugabe);
                tmp.set_xe(tmp.xe() + zugabe);
                zeile_neu = tmp.text();
            }

            bearb.zeile_ersaetzen(i, zeile_neu);
        }
    }
    if(re == true)
    {
        tmp_l += zugabe;
    }
    if(un == true) //Y-Werte verschieben
    {
        tmp_b += zugabe;
        for(uint i=1; i<=bearb.zeilenanzahl() ;i++)
        {
            text_zeilenweise zeile;
            zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
            zeile.set_text(bearb.zeile(i));
            QString zeile_neu;
            if(zeile.zeile(1) == BEARBART_BOHR)
            {
                bohrung bo(zeile.text());
                bo.set_y(bo.y() + zugabe);
                zeile_neu = bo.text();
            }else if(zeile.zeile(1) == BEARBART_BOHRRASTER)
            {
                bohrraster bora(zeile.text());
                bora.set_y((bora.y() + zugabe));
                zeile_neu = bora.text();
            }else if(zeile.zeile(1) == BEARBART_RTA)
            {
                rechtecktasche rt(zeile.text());
                rt.set_y(rt.y() + zugabe);
                zeile_neu = rt.text();
            }else if(zeile.zeile(1) == BEARBART_NUT)
            {
                nut nu(zeile.text());
                nu.set_ys(nu.ys() + zugabe);
                nu.set_ye(nu.ye() + zugabe);
                zeile_neu = nu.text();
            }else if(zeile.zeile(1) == BEARBART_FRAESERAUFRUF)
            {
                fraueseraufruf tmp(zeile.text());
                tmp.set_y(tmp.y() + zugabe);
                zeile_neu = tmp.text();
            }else if(zeile.zeile(1) == BEARBART_FRAESERGERADE)
            {
                fraesergerade tmp(zeile.text());
                tmp.set_ys(tmp.ys() + zugabe);
                tmp.set_ye(tmp.ye() + zugabe);
                zeile_neu = tmp.text();
            }else if(zeile.zeile(1) == BEARBART_FRAESERBOGEN)
            {
                fraeserbogen tmp(zeile.text());
                tmp.set_ys(tmp.ys() + zugabe);
                tmp.set_ye(tmp.ye() + zugabe);
                zeile_neu = tmp.text();
            }

            bearb.zeile_ersaetzen(i, zeile_neu);
        }
    }
    if(ob == true)
    {
        tmp_b += zugabe;
    }

    //Schritt 3:
    //Prüfen ob WST jetzt nur noch auf der Unterseite Bearbeitungen hat    
    bool unsei = false;
    bool obsei = false;
    for(uint i=1; i<=bearb.zeilenanzahl() ;i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(bearb.zeile(i));
        if(zeile.zeile(2) == WST_BEZUG_OBSEI)
        {
            obsei = true;
        }else if(zeile.zeile(2) == WST_BEZUG_UNSEI)
        {
            unsei = true;
        }
        if(obsei == true && unsei == true)
        {
            break; //for
        }
    }
    if(  (ausgabeformat == "fmc")  ||  (ausgabeformat == "eigen")  )
    {
        if(obsei == false && unsei == true)
        {
            bearb = drehen_um_b_halbe(bearb, tmp_l, tmp_b);
        }
    }else if(ausgabeformat == "ganx")
    {
        if(obsei == true && unsei == false)
        {
            bearb = drehen_um_b_halbe(bearb, tmp_l, tmp_b);
        }
    }

    return bearb;
}
text_zeilenweise werkstueck::drehen_um_b_halbe(text_zeilenweise bearb, double &tmp_l, double &tmp_b)
{
    for(uint i=1; i<=bearb.zeilenanzahl() ;i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(bearb.zeile(i));
        QString zeile_neu;
        if(zeile.zeile(1) == BEARBART_BOHR)
        {
            bohrung bo(zeile.text());
            QString bezug = bo.bezug();
            if(bezug == WST_BEZUG_OBSEI)
            {
                bo.set_y(tmp_b - bo.y());
                bo.set_bezug(WST_BEZUG_UNSEI);
            }else if(bezug == WST_BEZUG_UNSEI)
            {
                bo.set_y(tmp_b - bo.y());
                bo.set_bezug(WST_BEZUG_OBSEI);
            }else if(bezug == WST_BEZUG_LI)
            {
                bo.set_y(tmp_b - bo.y());
            }else if(bezug == WST_BEZUG_RE)
            {
                bo.set_y(tmp_b - bo.y());
            }else if(bezug == WST_BEZUG_VO)
            {
                bo.set_y(tmp_b - bo.y());
                bo.set_bezug(WST_BEZUG_HI);
            }else if(bezug == WST_BEZUG_HI)
            {
                bo.set_y(tmp_b - bo.y());
                bo.set_bezug(WST_BEZUG_VO);
            }
            zeile_neu = bo.text();
        }else if(zeile.zeile(1) == BEARBART_BOHRRASTER)
        {
            bohrraster bora(zeile.text());
            QString bezug = bora.bezug();
            if(bezug == WST_BEZUG_OBSEI)
            {
                bora.set_y(tmp_b - bora.y());
                bora.set_raster_y(-1 * bora.raster_y());
                bora.set_bezug(WST_BEZUG_UNSEI);
            }else if(bezug == WST_BEZUG_UNSEI)
            {
                bora.set_y(tmp_b - bora.y());
                bora.set_raster_y(-1 * bora.raster_y());
                bora.set_bezug(WST_BEZUG_OBSEI);
            }else if(bezug == WST_BEZUG_LI)
            {
                bora.set_raster_y(-1 * bora.raster_y());
                bora.set_y(tmp_b - bora.y());
            }else if(bezug == WST_BEZUG_RE)
            {
                bora.set_raster_y(-1 * bora.raster_y());
                bora.set_y(tmp_b - bora.y());
            }else if(bezug == WST_BEZUG_VO)
            {
                bora.set_y(tmp_b - bora.y());
                bora.set_bezug(WST_BEZUG_HI);
            }else if(bezug == WST_BEZUG_HI)
            {
                bora.set_y(tmp_b - bora.y());
                bora.set_bezug(WST_BEZUG_VO);
            }
            zeile_neu = bora.text();
        }else if(zeile.zeile(1) == BEARBART_RTA)
        {
            rechtecktasche rt(zeile.text());
            rt.set_y(tmp_b - rt.y());
            QString bezug = rt.bezug();
            if(bezug == WST_BEZUG_OBSEI)
            {
                rt.set_bezug(WST_BEZUG_UNSEI);
            }else
            {
                rt.set_bezug(WST_BEZUG_OBSEI);
            }
            zeile_neu = rt.text();
        }else if(zeile.zeile(1) == BEARBART_NUT)
        {
            nut nu(zeile.text());
            nu.set_ys(tmp_b - nu.ys());
            nu.set_ye(tmp_b - nu.ye());
            QString bezug = nu.bezug();
            if(bezug == WST_BEZUG_OBSEI)
            {
                nu.set_bezug(WST_BEZUG_UNSEI);
            }else
            {
                nu.set_bezug(WST_BEZUG_OBSEI);
            }
            zeile_neu = nu.text();
        }else if(zeile.zeile(1) == BEARBART_FRAESERAUFRUF)
        {
            fraueseraufruf tmp(zeile.text());
            tmp.set_y(tmp_b - tmp.y());
            QString bezug = tmp.bezug();
            if(bezug == WST_BEZUG_OBSEI)
            {
                tmp.set_bezug(WST_BEZUG_UNSEI);
            }else
            {
                tmp.set_bezug(WST_BEZUG_OBSEI);
            }
            zeile_neu = tmp.text();
        }else if(zeile.zeile(1) == BEARBART_FRAESERGERADE)
        {
            fraesergerade tmp(zeile.text());
            tmp.set_ys(tmp_b - tmp.ys());
            tmp.set_ye(tmp_b - tmp.ye());
            QString bezug = tmp.bezug();
            if(bezug == WST_BEZUG_OBSEI)
            {
                tmp.set_bezug(WST_BEZUG_UNSEI);
            }else
            {
                tmp.set_bezug(WST_BEZUG_OBSEI);
            }
            zeile_neu = tmp.text();
        }else if(zeile.zeile(1) == BEARBART_FRAESERBOGEN)
        {
            fraeserbogen tmp(zeile.text());
            tmp.set_ys(tmp_b - tmp.ys());
            tmp.set_ye(tmp_b - tmp.ye());
            QString bezug = tmp.bezug();
            if(bezug == WST_BEZUG_OBSEI)
            {
                tmp.set_bezug(WST_BEZUG_UNSEI);
            }else
            {
                tmp.set_bezug(WST_BEZUG_OBSEI);
            }
            zeile_neu = tmp.text();
        }

        bearb.zeile_ersaetzen(i, zeile_neu);
    }
    return bearb;
}
//--------------------------------------------------

