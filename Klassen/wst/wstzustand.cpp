#include "wstzustand.h"

wstzustand::wstzustand()
{
    Schwellenwert_ay = 230;
    Zugabe_gehrungen = 0;
}
void wstzustand::clear()
{
    //...
    //...
    //...
    //...
    //...
    //...
}

void wstzustand::set_dicke(double d)
{
    if(d>0 && d<200)
    {
        Dicke = d;
    }
}
void wstzustand::set_kante_vo(QString artiklenummer)
{
    Kante_vo = artiklenummer;
}
void wstzustand::set_kante_hi(QString artiklenummer)
{
    Kante_hi = artiklenummer;
}
void wstzustand::set_kante_li(QString artiklenummer)
{
    Kante_li = artiklenummer;
}
void wstzustand::set_kante_re(QString artiklenummer)
{
    Kante_re = artiklenummer;
}
void wstzustand::set_zugabe_gehrungen(double zugabe)
{
    if(zugabe != Zugabe_gehrungen)
    {
        Zugabe_gehrungen = zugabe;
        clear();
    }
}

void wstzustand::erzeugen(QString format, werkzeugmagazin wkzmag, text_zeilenweise bearbeitung, QString drehung, \
                          double l, double b)
{
    Format.append(format);
    Wkzmag.append(wkzmag);
    Bearbeitung_bekommen.append(bearbeitung);
    Drehung_bekommen.append(drehung);
    Laenge_bekommen.append(l);
    Breite_bekommen.append(b);
    finde_drehwinkel_auto(Format.count()-1);
}

void wstzustand::finde_drehwinkel_auto(int index)
{
    //vor dem Aufruf dieser Funktion müssen folgende Parameter zwingend erzeugt sein:
    //Format
    //Wkzmag
    //Drehung_bekommen
    //Bearbeitung_bekommen
    //Laenge_bekommen
    //Laenge_bekommen

    //Diese Funktion berechnet den besten Drehwinkel für der wst
    //(indirekte) Rückgabewerte sind:
    QString             ret_drehung;//isEmpty
    int                 ret_bewertung = 0;
    QString             ret_warnungen;//isEmpty
    text_zeilenweise    ret_bearb;//isEmpty
    double              ret_laenge = 0;
    double              ret_breite = 0;

    QString drehwinkel = Drehung_bekommen.at(index);
    QString format = Format.at(index);
    text_zeilenweise bearb = Bearbeitung_bekommen.at(index);
    werkzeugmagazin wkzmag = Wkzmag.at(index);

    if(drehwinkel=="0" || drehwinkel=="90" || drehwinkel=="180" || drehwinkel=="270")
    {
        ret_drehung = drehwinkel;
    }

    if(format == "fmc")
    {
        const int ranking_abst_zwanzig = 5;
        const int ranking_rw_nut = 30;
        fraesergeraden_zusammenfassen(bearb);
        hbemiduebeltiefe(bearb);
        double tmp_l = Laenge_bekommen.at(index);
        double tmp_b = Breite_bekommen.at(index);
        text_zeilenweise tmp_bearb = bearb;
        gehr_3achs(tmp_bearb, tmp_l, tmp_b, format);
        //Die beste Drehrichtung herausfinden:
        int bewertung_0    = 1;
        int bewertung_90   = 1;
        int bewertung_180  = 1;
        int bewertung_270  = 1;
        //Stufe 1:
        //heraus bekommen, für welche Lage es Warnungen gibt:
        text_zeilenweise bearb_kopie = tmp_bearb;
        double l_kopie = tmp_l;
        double b_kopie = tmp_b;
        //------------------------0:
        text_zeilenweise bearb_0;
        double l_0 = 0;
        double b_0 = 0;
        QString warnung_0;
        if(drehwinkel == "0" || drehwinkel == "AUTO")
        {
            warnung_0 = warnungen_fmc(bearb_kopie, wkzmag, l_kopie, b_kopie);
            if(warnung_0.isEmpty())
            {
                bewertung_0 = 100;
            }else
            {
                bewertung_0 = 0;
            }
            bearb_0 = bearb_kopie;
            l_0 = l_kopie;
            b_0 = b_kopie;
        }
        //------------------------90:
        text_zeilenweise bearb_90;
        double l_90 = 0;
        double b_90 = 0;
        QString warnung_90;
        if(drehwinkel == "90" || drehwinkel == "AUTO")
        {
            bearb_drehen_90(bearb_kopie, l_kopie, b_kopie);
            warnung_90 = warnungen_fmc(bearb_kopie, wkzmag, l_kopie, b_kopie);
            if(warnung_90.isEmpty())
            {
                bewertung_90 = 100;
            }else
            {
                bewertung_90 = 0;
            }
            bearb_90 = bearb_kopie;
            l_90 = l_kopie;
            b_90 = b_kopie;
        }
        //------------------------180:
        text_zeilenweise bearb_180;
        double l_180 = 0;
        double b_180 = 0;
        QString warnung_180;
        if(drehwinkel == "180" || drehwinkel == "AUTO")
        {
            if(drehwinkel == "180")
            {
                bearb_drehen_90(bearb_kopie, l_kopie, b_kopie);
                bearb_drehen_90(bearb_kopie, l_kopie, b_kopie);
            }else //AUTO
            {
                bearb_drehen_90(bearb_kopie, l_kopie, b_kopie);
            }
            warnung_180 = warnungen_fmc(bearb_kopie, wkzmag, l_kopie, b_kopie);
            if(warnung_180.isEmpty())
            {
                bewertung_180 = 100;
            }else
            {
                bewertung_180 = 0;
            }
            bearb_180 = bearb_kopie;
            l_180 = l_kopie;
            b_180 = b_kopie;
        }
        //------------------------270:
        text_zeilenweise bearb_270;
        double l_270 = 0;
        double b_270 = 0;
        QString warnung_270;
        if(drehwinkel == "0" || drehwinkel == "AUTO")
        {
            if(drehwinkel == "270")
            {
                bearb_drehen_90(bearb_kopie, l_kopie, b_kopie);
                bearb_drehen_90(bearb_kopie, l_kopie, b_kopie);
                bearb_drehen_90(bearb_kopie, l_kopie, b_kopie);
            }else //AUTO
            {
                bearb_drehen_90(bearb_kopie, l_kopie, b_kopie);
            }
            warnung_270 = warnungen_fmc(bearb_kopie, wkzmag, l_kopie, b_kopie);
            if(warnung_270.isEmpty())
            {
                bewertung_270 = 100;
            }else
            {
                bewertung_270 = 0;
            }
            bearb_270 = bearb_kopie;
            l_270 = l_kopie;
            b_270 = b_kopie;
        }

        //Stufe 2:
        //heraus bekommen wo vorne ist anhand von Bearbeitungen:
        if(drehwinkel == "0" || drehwinkel == "AUTO")
        {
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
                            bewertung_0 += ranking_abst_zwanzig;
                        }
                        if(bo.y() == 20)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                        {
                            bewertung_0 += ranking_abst_zwanzig;
                        }
                    }else if(bo.dm() == 35.3)//Töpfe/Topfbänder am Anschlag anlegen
                    {
                        if(bo.x() < 30)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                        {
                            bewertung_0 += 5;
                        }
                        if(bo.y() < 30)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                        {
                            bewertung_0 += 5;
                        }

                    }
                }
            }
        }
        if(drehwinkel == "90" || drehwinkel == "AUTO")
        {
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
                            bewertung_90 += ranking_abst_zwanzig;
                        }
                        if(bo.y() == 20)//Gilt für HBE, Löcher mit diesem Abst. in der Fläche sind nicht zu erwarten
                        {
                            bewertung_90 += ranking_abst_zwanzig;
                        }
                    }else if(bo.dm() == 35.3)//Töpfe/Topfbänder am Anschlag anlegen
                    {
                        if(bo.x() < 30)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                        {
                            bewertung_90 += 5;
                        }
                        if(bo.y() < 30)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                        {
                            bewertung_90 += 5;
                        }
                    }
                }
            }
        }
        if(drehwinkel == "180" || drehwinkel == "AUTO")
        {
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
                            bewertung_180 += ranking_abst_zwanzig;
                        }
                        if(bo.y() == 20)//Gilt für HBE, Löcher mit diesem Abst. in der Fläche sind nicht zu erwarten
                        {
                            bewertung_180 += ranking_abst_zwanzig;
                        }
                    }else if(bo.dm() == 35.3)//Töpfe/Topfbänder am Anschlag anlegen
                    {
                        if(bo.x() < 30)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                        {
                            bewertung_180 += 5;
                        }
                        if(bo.y() < 30)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                        {
                            bewertung_180 += 5;
                        }

                    }
                }
            }
        }
        if(drehwinkel == "270" || drehwinkel == "AUTO")
        {
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
                            bewertung_270 += ranking_abst_zwanzig;
                        }
                        if(bo.y() == 20)//Gilt für HBE, Löcher mit diesem Abst. in der Fläche sind nicht zu erwarten
                        {
                            bewertung_270 += ranking_abst_zwanzig;
                        }
                    }else if(bo.dm() == 35.3)//Töpfe/Topfbänder am Anschlag anlegen
                    {
                        if(bo.x() < 30)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                        {
                            bewertung_270 += 5;
                        }
                        if(bo.y() < 30)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                        {
                            bewertung_270 += 5;
                        }
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
        }

        //Stufe 4:
        //Teile bevorzugen, bei bei denen gilt: L > B:
        if(l_0 > b_0)
        {
            bewertung_0 += 20;
        }
        if(l_90 > b_90)
        {
            bewertung_90 += 20;
        }
        if(l_180 > b_180)
        {
            bewertung_180 += 20;
        }
        if(l_270 > b_270)
        {
           bewertung_270 += 20;
        }

        //Stufe 5:
        //Bei schmalen Teilen bevorzugen, wenn HBE nicht aus richtung des Anschlages kommt:
        if(drehwinkel == "0" || drehwinkel == "AUTO")
        {
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
        }
        if(drehwinkel == "90" || drehwinkel == "AUTO")
        {
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
        }
        if(drehwinkel == "180" || drehwinkel == "AUTO")
        {
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
        }
        if(drehwinkel == "270" || drehwinkel == "AUTO")
        {
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
        }

        //Stufe 6:
        //Flächenbohrungen mit geringem Kantenabstand bevorzugen
        if(drehwinkel == "0" || drehwinkel == "AUTO")
        {
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
        }
        if(drehwinkel == "90" || drehwinkel == "AUTO")
        {
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

        }
        if(drehwinkel == "180" || drehwinkel == "AUTO")
        {
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

        }
        if(drehwinkel == "270" || drehwinkel == "AUTO")
        {
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
        }

        //Stufe 7:
        //RW-Nuten nicht am Anschlag bevorzugen
        if(drehwinkel == "0" || drehwinkel == "AUTO")
        {
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
                                bewertung_0 += ranking_rw_nut;
                            }
                        }
                    }
                }
            }
        }
        if(drehwinkel == "90" || drehwinkel == "AUTO")
        {
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
                                bewertung_90 += ranking_rw_nut;
                            }
                        }
                    }
                }
            }
        }
        if(drehwinkel == "180" || drehwinkel == "AUTO")
        {
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
                                bewertung_180 += ranking_rw_nut;
                            }
                        }
                    }
                }
            }
        }
        if(drehwinkel == "270" || drehwinkel == "AUTO")
        {
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
                                bewertung_270 += ranking_rw_nut;
                            }
                        }
                    }
                }
            }
        }

        //Bewertungen auswerten:
        if(drehwinkel == "0")
        {
            bewertung_0 = 999999;
        }else if(drehwinkel == "90")
        {
            bewertung_90 = 999999;
        }else if(drehwinkel == "180")
        {
            bewertung_180 = 999999;
        }else if(drehwinkel == "270")
        {
            bewertung_270 = 999999;
        }
        if(bewertung_0 >= 100 && \
           bewertung_0 >= bewertung_90 && \
           bewertung_0 >= bewertung_180 && \
           bewertung_0 >= bewertung_270 )
        {
            ret_bewertung = bewertung_0;
            ret_drehung = "0";
            ret_warnungen = warnung_0;
            ret_bearb = bearb_0;
            ret_laenge = l_0;
            ret_breite = b_0;
        }else if(bewertung_90 >= 100 && \
                 bewertung_90 >= bewertung_0 && \
                 bewertung_90 >= bewertung_180 && \
                 bewertung_90 >= bewertung_270 )
        {
            ret_bewertung = bewertung_90;
            ret_drehung = "90";
            ret_warnungen = warnung_90;
            ret_bearb = bearb_90;
            ret_laenge = l_90;
            ret_breite = b_90;
        }else if(bewertung_180 >= 100 && \
                 bewertung_180 >= bewertung_0 && \
                 bewertung_180 >= bewertung_90 && \
                 bewertung_180 >= bewertung_270 )
        {
            ret_bewertung = bewertung_180;
            ret_drehung = "180";
            ret_warnungen = warnung_180;
            ret_bearb = bearb_180;
            ret_laenge = l_180;
            ret_breite = b_180;
        }else if(bewertung_270 >= 100 && \
                 bewertung_270 >= bewertung_0 && \
                 bewertung_270 >= bewertung_90 && \
                 bewertung_270 >= bewertung_180 )
        {
            ret_bewertung = bewertung_270;
            ret_drehung = "270";
            ret_warnungen = warnung_270;
            ret_bearb = bearb_270;
            ret_laenge = l_270;
            ret_breite = b_270;
        }else
        {
            //wir nehmen 0:
            ret_bewertung = bewertung_0;
            ret_drehung = "0";
            ret_warnungen = warnung_0;
            ret_bearb = bearb_0;
            ret_laenge = l_0;
            ret_breite = b_0;
        }

    }else if(format == "ganx")
    {
        const int ranking_abst_zwanzig = 5;
        hbemiduebeltiefe(bearb);
        double tmp_l = Breite_bekommen.at(index);
        double tmp_b = Laenge_bekommen.at(index);
        bearb_optimieren_ganx(bearb);
        gehr_3achs(bearb, tmp_l, tmp_b, "ganx");
        //Die beste Drehrichtung herausfinden:
        int bewertung_0    = 1;
        int bewertung_90   = 1;
        int bewertung_180  = 1;
        int bewertung_270  = 1;
        //Stufe 1:
        //heraus bekommen, für welche Lage es Warnungen gibt:
        QString warnung;
        text_zeilenweise bearb_kopie = bearb;
        double l_kopie = tmp_l;
        double b_kopie = tmp_b;
        //------------------------0:
        warnung = warnungen_ganx(bearb_kopie, wkzmag, l_kopie, b_kopie);
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
        bearb_drehen_90(bearb_kopie, l_kopie, b_kopie);
        warnung = warnungen_ganx(bearb_kopie, wkzmag, l_kopie, b_kopie);
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
        bearb_drehen_90(bearb_kopie, l_kopie, b_kopie);
        warnung = warnungen_ganx(bearb_kopie, wkzmag, l_kopie, b_kopie);
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
        bearb_drehen_90(bearb_kopie, l_kopie, b_kopie);
        warnung = warnungen_ganx(bearb_kopie, wkzmag, l_kopie, b_kopie);
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
                        bewertung_0 += ranking_abst_zwanzig;
                    }
                    if(bo.y() == b_0-20)//Gilt für HBE, Löcher mit diesem Abst. in der Fläche sind nicht zu erwarten
                    {
                        bewertung_0 += ranking_abst_zwanzig;
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
                        bewertung_90 += ranking_abst_zwanzig;
                    }
                    if(bo.y() == b_90-20)//Gilt für HBE, Löcher mit diesem Abst. in der Fläche sind nicht zu erwarten
                    {
                        bewertung_90 += ranking_abst_zwanzig;
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
                        bewertung_180 += ranking_abst_zwanzig;
                    }
                    if(bo.y() == b_180-20)//Gilt für HBE, Löcher mit diesem Abst. in der Fläche sind nicht zu erwarten
                    {
                        bewertung_180 += ranking_abst_zwanzig;
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
                        bewertung_270 += ranking_abst_zwanzig;
                    }
                    if(bo.y() == b_270-20)//Gilt für HBE, Löcher mit diesem Abst. in der Fläche sind nicht zu erwarten
                    {
                        bewertung_270 += ranking_abst_zwanzig;
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

        //Bewertungen auswerten:
        if(bewertung_0 >= 100 && \
           bewertung_0 >= bewertung_90 && \
           bewertung_0 >= bewertung_180 && \
           bewertung_0 >= bewertung_270 )
        {
            ret_bewertung = bewertung_0;
            ret_drehung = "0";
        }else if(bewertung_90 >= 100 && \
                 bewertung_90 >= bewertung_0 && \
                 bewertung_90 >= bewertung_180 && \
                 bewertung_90 >= bewertung_270 )
        {
            ret_bewertung = bewertung_90;
            ret_drehung = "90";
        }else if(bewertung_180 >= 100 && \
                 bewertung_180 >= bewertung_0 && \
                 bewertung_180 >= bewertung_90 && \
                 bewertung_180 >= bewertung_270 )
        {
            ret_bewertung = bewertung_180;
            ret_drehung = "180";
        }else if(bewertung_270 >= 100 && \
                 bewertung_270 >= bewertung_0 && \
                 bewertung_270 >= bewertung_90 && \
                 bewertung_270 >= bewertung_180 )
        {
            ret_bewertung = bewertung_270;
            ret_drehung = "270";
        }else
        {
            //wir nehmen 0:
            ret_bewertung = bewertung_0;
            ret_drehung = "0";
        }
    }else if(format == "ggf" || format == "eigen")
    {
        ret_drehung     = "0";
        ret_bewertung   =  0 ;
    }

    Drehung.append(ret_drehung);
    Bewertung.append(ret_bewertung);
    Warnungen.append(ret_warnungen);
    Bearbeitung.append(ret_bearb);
    Laenge.append(ret_laenge);
    Breite.append(ret_breite);
}

void wstzustand::fraesergeraden_zusammenfassen(text_zeilenweise& bearbeitung)
{
    for(uint i=1 ; i<bearbeitung.zeilenanzahl() ; i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(bearbeitung.zeile(i));
        text_zeilenweise folgezeile;
        folgezeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        folgezeile.set_text(bearbeitung.zeile(i+1));

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
                bearbeitung.zeile_ersaetzen(i, fg1.text());
                bearbeitung.zeile_loeschen(i+1);
                i--;
            }
        }

    }
}

void wstzustand::hbemiduebeltiefe(text_zeilenweise& bearbeitung)
{
    //Diese Funktion stellt die Lochtiefe für die Dübel 8x30 bei den
    //HBEs einheitlich auf 18mm ein, damit es nicht zu Problemen in
    //der Fertigung kommt wenn die Löcher CNC-gebohrt werden und mit dem
    //Dübelautomaten die Dübel eingetrieben werden

    const double min = 16;//Maximale Dübellochtiefe
    const double max = 18;//Minimale Dübellochtiefe
    for(uint i=1 ; i<=bearbeitung.zeilenanzahl() ; i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(bearbeitung.zeile(i));
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
                        bearbeitung.zeile_ersaetzen(i, bo.text());
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
                        bearbeitung.zeile_ersaetzen(i, bo.text());
                    }
                }
            }
        }
    }
}

void wstzustand::gehr_3achs(text_zeilenweise& bearb, double &tmp_l, double &tmp_b, QString ausgabeformat)
{
    //Diese Funktion löscht die Gehrungen aus den Bearbeitungen heraus
    //Diese können mit einer 3-Achs-Maschine nicht ohne Spezial-WKZ hergestellt werden.
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
            drehen_um_b_halbe(bearb, tmp_b);
        }
    }else if(ausgabeformat == "ganx")
    {
        if(obsei == true && unsei == false)
        {
            drehen_um_b_halbe(bearb, tmp_b);
        }
    }
}

void wstzustand::drehen_um_b_halbe(text_zeilenweise& bearb, double &tmp_b)
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
}

void wstzustand::bearb_drehen_90(text_zeilenweise& bearb, double& tmp_l, double& tmp_b)
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
}

void wstzustand::bearb_optimieren_ganx(text_zeilenweise& bearb)
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
}

void wstzustand::dubosplitten(text_zeilenweise& bearb, werkzeugmagazin wkzmag)
{
    //Diese Funktion soll Durchgangs-Bohrungen finden
    //Gibt es für eine Durchgangsbohrung keinen Duchgangsborer so soll das Loch von beiden Plattenseiten gebohrt werden
    //Gibt es einen Durchgangsbohrer, dieser ist jedoch zu kurz so soll das Loch von beiden Plattenseiten gebohrt werden
    //Diese Funktion sollte vor der Funktion zum finden von Bohrrastern aufgerufen werden
    //da Bohrraster hier nicht berücksichtigt werden
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
                if(bo.tiefe() >= Dicke)
                {
                    QString tnummer = wkzmag.wkznummer(WKZ_TYP_BOHRER, bo.dm(), bo.tiefe(), Dicke, bo.bezug());
                    if(tnummer.isEmpty())
                    {
                        bohrung boA = bo;
                        double boti = bo.tiefe();
                        boti = boti -4; // jetzt boti == wst-Dicke
                        boA.set_tiefe(boti/2 + 2);
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
    bearb = bearb_neu;
}


QString wstzustand::warnungen_fmc(text_zeilenweise bearb, werkzeugmagazin wkzmag, \
                                  double tmp_l, double tmp_b)
{
    dubosplitten(bearb, wkzmag);
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

    for(uint i=1; i<=bearb.zeilenanzahl() ;i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(bearb.zeile(i));

        QString art = zeile.zeile(1);
        if(art == BEARBART_BOHR || art == BEARBART_BOHRRASTER)
        {
            //BOHRUNG ist eine Teilmenge von BOHRRASTER
            bohrung bo(zeile.text());//die nicht benötigten Parameter werden beim einlesen ignoriert
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

                }else//Es ist auch kein passender Fräser da, die CNC-Bearbeitung kann nicht erfolgen
                {
                    msg += "  !! Kein Werkzeug fuer Bohrung oder Kreistasche gefunden!\n";
                    msg += "    ->";
                    msg += bearb.zeile(i).replace("\t", " | ");
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
                    minmass = rt.breite();
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
QString wstzustand::warnungen_ganx(text_zeilenweise bearb, werkzeugmagazin wkzmag, \
                                  double tmp_l, double tmp_b)
{
    dubosplitten(bearb, wkzmag);
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

    for(uint i=1; i<=bearb.zeilenanzahl() ;i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(bearb.zeile(i));

        QString art = zeile.zeile(1);
        if(art == BEARBART_BOHR || art == BEARBART_BOHRRASTER)
        {
            //BOHRUNG ist eine Teilmenge von BOHRRASTER
            bohrung bo(zeile.text());//die nicht benötigten Parameter werden beim einlesen ignoriert
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
                    msg += bearb.zeile(i).replace("\t", " | ");
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
                    minmass = rt.breite();
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

QString wstzustand::kante_vo(QString drewi)
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
QString wstzustand::kante_hi(QString drewi)
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
QString wstzustand::kante_li(QString drewi)
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
QString wstzustand::kante_re(QString drewi)
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
QString wstzustand::kante_vo_ganx(QString drewi)
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
QString wstzustand::kante_hi_ganx(QString drewi)
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
QString wstzustand::kante_li_ganx(QString drewi)
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
QString wstzustand::kante_re_ganx(QString drewi)
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








