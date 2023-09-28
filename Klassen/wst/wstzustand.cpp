#include "wstzustand.h"

wstzustand::wstzustand()
{
    clear();
    Laenge_bekommen = 0;
    Breite_bekommen = 0;
    Zugabe_gehrungen = 20;
    Schwellenwert_ay = 230;
    Formartierungen_aufbrechen = false;
    Dicke = 0;
}
void wstzustand::clear()
{    
    Akt_zust = -1;
    Format.clear();
    Wkzm.clear();
    Drehung_bekommen.clear();
    Drehung.clear();
    Bewertung.clear();
    Warnungen.clear();
    Bearb.clear();
    Laenge.clear();
    Breite.clear();
    Exporttext.clear();
    Fehler_kein_wkz.clear();
    Export_moeglich.clear();
    Geotext.clear();
    GeoFkon.clear();
    Versatz_y.clear();
    Zust_use_ax.clear();
    Zust_use_ay.clear();
    Use_ax = true;
    Use_ay = true;
}

//----------------------------------
//Public:
//----------------------------------set_xy:
void wstzustand::set_bearb(text_zw bearb)
{
    if(bearb.text() != Bearb_bekommen.text())
    {
        if(!Format.isEmpty())
        {
            clear();
        }
        Bearb_bekommen = bearb;
    }
}
void wstzustand::set_laenge(double l)
{
    if(l != Laenge_bekommen)
    {
        if(!Format.isEmpty())
        {
            clear();
        }
        Laenge_bekommen = l;
    }
}
void wstzustand::set_breite(double b)
{
    if(b != Breite_bekommen)
    {
        if(!Format.isEmpty())
        {
            clear();
        }
        Breite_bekommen = b;
    }
}
void wstzustand::set_dicke(double d)
{
    if(d>0 && d<200)
    {
        if(d != Dicke)
        {
            if(!Format.isEmpty())
            {
                clear();
            }
            Dicke = d;
        }
    }
}
void wstzustand::set_kante_vo(QString artiklenummer)
{
    if(artiklenummer != Kante_vo)
    {
        if(!Format.isEmpty())
        {
            clear();
        }
        Kante_vo = artiklenummer;
    }
}
void wstzustand::set_kante_hi(QString artiklenummer)
{
    if(artiklenummer != Kante_hi)
    {
        if(!Format.isEmpty())
        {
            clear();
        }
        Kante_hi = artiklenummer;
    }
}
void wstzustand::set_kante_li(QString artiklenummer)
{
    if(artiklenummer != Kante_li)
    {
        if(!Format.isEmpty())
        {
            clear();
        }
        Kante_li = artiklenummer;
    }
}
void wstzustand::set_kante_re(QString artiklenummer)
{
    if(artiklenummer != Kante_re)
    {
        if(!Format.isEmpty())
        {
            clear();
        }
        Kante_re = artiklenummer;
    }

}
void wstzustand::set_zugabe_gehrungen(double zugabe)
{
    if(zugabe != Zugabe_gehrungen)
    {
        if(!Format.isEmpty())
        {
            clear();
        }
        Zugabe_gehrungen = zugabe;
    }
}
void wstzustand::set_formartierungen_aufbrechen(bool jn)
{
    if(jn != Formartierungen_aufbrechen)
    {
        if(!Format.isEmpty())
        {
            clear();
        }
        Formartierungen_aufbrechen = jn;
    }

}
void wstzustand::set_name(QString neuer_name)
{
    if(neuer_name != Name)
    {
        if(!Format.isEmpty())
        {
            clear();
        }
        Name = neuer_name;
    }
}
void wstzustand::set_zust_fkon(QString zust)
{
    if(zust != Zust_fkon)
    {
        if(!Format.isEmpty())
        {
            clear();
        }
        Zust_fkon = zust;
        //"wkz" == gemäß Werkzeugmagazin
        //"orgi" == gemäß Importdatei
    }
}
void wstzustand::set_einst_ganx(einstellung_ganx e)
{
    if(e != Eganx)
    {
        if(!Format.isEmpty())
        {
            clear();
        }
        Eganx = e;
    }
}
void wstzustand::set_use_ax(bool benutzen)
{
    Use_ax = benutzen;
}
void wstzustand::set_use_ay(bool benutzen)
{
    Use_ay = benutzen;
}

QString wstzustand::kante_vo()
{
    if(Akt_zust != -1 && Akt_zust<Exporttext.count())
    {
        QString f = Format.at(Akt_zust);
        QString wi = Drehung.at(Akt_zust);
        if (f == "ganx")
        {
            return kante_vo_ganx(wi);
        }else
        {
            return kante_vo(wi);
        }
    }else
    {
        return "";
    }
}
QString wstzustand::kante_hi()
{
    if(Akt_zust != -1 && Akt_zust<Exporttext.count())
    {
        QString f = Format.at(Akt_zust);
        QString wi = Drehung.at(Akt_zust);
        if (f == "ganx")
        {
            return kante_hi_ganx(wi);
        }else
        {
            return kante_hi(wi);
        }
    }else
    {
        return "";
    }
}
QString wstzustand::kante_li()
{
    if(Akt_zust != -1 && Akt_zust<Exporttext.count())
    {
        QString f = Format.at(Akt_zust);
        QString wi = Drehung.at(Akt_zust);
        if (f == "ganx")
        {
            return kante_li_ganx(wi);
        }else
        {
            return kante_li(wi);
        }
    }else
    {
        return "";
    }
}
QString wstzustand::kante_re()
{
    if(Akt_zust != -1 && Akt_zust<Exporttext.count())
    {
        QString f = Format.at(Akt_zust);
        QString wi = Drehung.at(Akt_zust);
        if (f == "ganx")
        {
            return kante_re_ganx(wi);
        }else
        {
            return kante_re(wi);
        }
    }else
    {
        return "";
    }
}

//----------------------------------Manipulationen:
void wstzustand::anfordern(QString format, wkz_magazin wkzmag, QString drehung)
{
    //Prüfen ob Zustand bereits existiert:
    bool existiert = false;
    for(int i = 0; i<Format.count();i++)
    {
        if(format == Format.at(i) && wkzmag == Wkzm.at(i) && drehung == Drehung.at(i) && \
            Use_ax == Zust_use_ax.at(i) && Use_ay == Zust_use_ay.at(i))
        {
            existiert = true;
            Akt_zust = i;
            break;
        }
    }
    if(!existiert)
    {
        erzeugen(format, wkzmag, drehung);
        Akt_zust = Format.count()-1;
    }
}
//----------------------------------
//Private:
//----------------------------------
void wstzustand::erzeugen(QString format, wkz_magazin wkzmag, QString drehung)
{
    Format.append(format);
    //  ->Format
    Wkzm.append(wkzmag);
    //  ->Wkzmag
    Drehung_bekommen.append(drehung);
    //  ->Drehung_bekommen
    Zust_use_ax.append(Use_ax);
    Zust_use_ay.append(Use_ay);
    finde_drehwinkel_auto_(Format.count()-1);
    //  ->Drehung
    //  ->Bewertung
    //  ->Warnungen
    //  ->Bearbeitung
    //  ->Laenge
    //  ->Breite
    if(format == "fmc")
    {
        fmc_dateitext(Format.count()-1);
        //  ->Exporttext
        //  ->Fehler_kein_wkz
        //  ->Export_moeglich
        geo(Format.count()-1);
        //  ->Geotext
        //  ->Versatz_y
    }else if(format == "ganx")
    {
        ganx_dateitext(Format.count()-1);
        //  ->Exporttext
        //  ->Fehler_kein_wkz
        //  ->Export_moeglich
        geo(Format.count()-1);
        //  ->Geotext
        //  ->Versatz_y
    }else if(format == "ggf")
    {
        ggf_dateitext(Format.count()-1);
        //  ->Exporttext
        //  ->Fehler_kein_wkz
        //  ->Export_moeglich
        geo(Format.count()-1);
        //  ->Geotext
        //  ->Versatz_y
    }else if(format == "eigen")
    {
        eigen_dateitext(Format.count()-1);
        //  ->Exporttext
        //  ->Fehler_kein_wkz
        //  ->Export_moeglich
        geo(Format.count()-1);
        //  ->Geotext
        //  ->Versatz_y
    }else if(format == "cix")
    {
        cix_dateitext(Format.count()-1);
        //  ->Exporttext
        //  ->Fehler_kein_wkz
        //  ->Export_moeglich
        geo(Format.count()-1);
        //  ->Geotext
        //  ->Versatz_y
    }
}
void wstzustand::finde_drehwinkel_auto_(int index)
{
    //vor dem Aufruf dieser Funktion müssen folgende Parameter zwingend erzeugt sein:
    //Format
    //Wkzmag
    //Drehung_bekommen
    //Bearbeitung_bekommen
    //Laenge_bekommen
    //Breite_bekommen

    //Diese Funktion berechnet den besten Drehwinkel für der wst
    //(indirekte) Rückgabewerte sind:
    QString             ret_drehung;//isEmpty
    int                 ret_bewertung = 0;
    QString             ret_warnungen;//isEmpty
    text_zw             ret_bearb;//isEmpty
    double              ret_laenge = 0;
    double              ret_breite = 0;

    QString drehwinkel = Drehung_bekommen.at(index);
    QString format = Format.at(index);
    text_zw bearb = Bearb_bekommen;
    wkz_magazin wkzmag = Wkzm.at(index);

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
        double tmp_l = Laenge_bekommen;
        double tmp_b = Breite_bekommen;
        gehr_3achs(bearb, tmp_l, tmp_b, format, "0");
        //Die beste Drehrichtung herausfinden:
        int bewertung_0    = 1;
        int bewertung_90   = 1;
        int bewertung_180  = 1;
        int bewertung_270  = 1;
        //Stufe 1:
        //heraus bekommen, für welche Lage es Warnungen gibt:
        text_zw bearb_kopie = bearb;
        text_zw bearb_0;
        text_zw bearb_90;
        text_zw bearb_180;
        text_zw bearb_270;
        double l_0 = tmp_l;
        double l_90 = tmp_l;
        double l_180 = tmp_l;
        double l_270 = tmp_l;
        double b_0 = tmp_b;
        double b_90 = tmp_b;
        double b_180 = tmp_b;
        double b_270 = tmp_b;
        QString warnung_0;
        QString warnung_90;
        QString warnung_180;
        QString warnung_270;

        if(drehwinkel == "0" || drehwinkel == "AUTO")
        {
            warnung_0 = warnungen_fmc(bearb_kopie, wkzmag, l_0, b_0);
            if(warnung_0.isEmpty())
            {
                bewertung_0 = 100;
            }else
            {
                bewertung_0 = 0;
            }
            bearb_0 = bearb_kopie;
        }
        if(drehwinkel == "90" || drehwinkel == "AUTO")
        {
            bearb_drehen_90(bearb_kopie, l_90, b_90);
            warnung_90 = warnungen_fmc(bearb_kopie, wkzmag, l_90, b_90);
            if(warnung_90.isEmpty())
            {
                bewertung_90 = 100;
            }else
            {
                bewertung_90 = 0;
            }
            bearb_90 = bearb_kopie;
        }
        if(drehwinkel == "180" || drehwinkel == "AUTO")
        {
            if(drehwinkel == "180")
            {
                bearb_drehen_90(bearb_kopie, l_180, b_180);
                bearb_drehen_90(bearb_kopie, l_180, b_180);
            }else //AUTO
            {
                l_180 = l_90;//Drehung mitnehmen
                b_180 = b_90;//Drehung mitnehmen
                bearb_drehen_90(bearb_kopie, l_180, b_180);
            }
            warnung_180 = warnungen_fmc(bearb_kopie, wkzmag, l_180, b_180);
            if(warnung_180.isEmpty())
            {
                bewertung_180 = 100;
            }else
            {
                bewertung_180 = 0;
            }
            bearb_180 = bearb_kopie;
        }
        if(drehwinkel == "270" || drehwinkel == "AUTO")
        {
            if(drehwinkel == "270")
            {
                bearb_drehen_90(bearb_kopie, l_270, b_270);
                bearb_drehen_90(bearb_kopie, l_270, b_270);
                bearb_drehen_90(bearb_kopie, l_270, b_270);
            }else //AUTO
            {
                l_270 = l_180;//Drehung mitnehmen
                b_270 = b_180;//Drehung mitnehmen
                bearb_drehen_90(bearb_kopie, l_270, b_270);
            }
            warnung_270 = warnungen_fmc(bearb_kopie, wkzmag, l_270, b_270);
            if(warnung_270.isEmpty())
            {
                bewertung_270 = 100;
            }else
            {
                bewertung_270 = 0;
            }
            bearb_270 = bearb_kopie;
        }

        //Stufe 2:
        //heraus bekommen wo vorne ist anhand von Bearbeitungen:
        if(drehwinkel == "0" || drehwinkel == "AUTO")
        {
            for(uint i=0; i<bearb_0.count() ;i++)
            {
                text_zw zeile;
                zeile.set_text(bearb_0.at(i), TRENNZ_BEARB_PARAM);
                if(zeile.at(0) == BEARBART_BOHR)
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
                    }else if(bo.dm() == 35.6)//Töpfe/Topfbänder am Anschlag anlegen
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
            for(uint i=0; i<bearb_90.count() ;i++)
            {
                text_zw zeile;
                zeile.set_text(bearb_90.at(i),TRENNZ_BEARB_PARAM);
                if(zeile.at(0) == BEARBART_BOHR)
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
                    }else if(bo.dm() == 35.6)//Töpfe/Topfbänder am Anschlag anlegen
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
            for(uint i=0; i<bearb_180.count() ;i++)
            {
                text_zw zeile;
                zeile.set_text(bearb_180.at(i),TRENNZ_BEARB_PARAM);
                if(zeile.at(0) == BEARBART_BOHR)
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
                    }else if(bo.dm() == 35.6)//Töpfe/Topfbänder am Anschlag anlegen
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
            for(uint i=0; i<bearb_270.count() ;i++)
            {
                text_zw zeile;
                zeile.set_text(bearb_270.at(i),TRENNZ_BEARB_PARAM);
                if(zeile.at(0) == BEARBART_BOHR)
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
                    }else if(bo.dm() == 35.6)//Töpfe/Topfbänder am Anschlag anlegen
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
                for(uint i=0; i<bearb_0.count() ;i++)
                {
                    text_zw zeile;
                    zeile.set_text(bearb_0.at(i),TRENNZ_BEARB_PARAM);
                    if(zeile.at(0) == BEARBART_BOHR)
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
                for(uint i=0; i<bearb_90.count() ;i++)
                {
                    text_zw zeile;
                    zeile.set_text(bearb_90.at(i), TRENNZ_BEARB_PARAM);
                    if(zeile.at(0) == BEARBART_BOHR)
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
                for(uint i=0; i<bearb_180.count() ;i++)
                {
                    text_zw zeile;
                    zeile.set_text(bearb_180.at(i),TRENNZ_BEARB_PARAM);
                    if(zeile.at(0) == BEARBART_BOHR)
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
                for(uint i=0; i<bearb_270.count() ;i++)
                {
                    text_zw zeile;
                    zeile.set_text(bearb_270.at(i), TRENNZ_BEARB_PARAM);
                    if(zeile.at(0) == BEARBART_BOHR)
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
            for(uint i=0; i<bearb_0.count() ;i++)
            {
                text_zw zeile;
                zeile.set_text(bearb_0.at(i), TRENNZ_BEARB_PARAM);
                if(zeile.at(0) == BEARBART_BOHR)
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
            for(uint i=0; i<bearb_90.count() ;i++)
            {
                text_zw zeile;
                zeile.set_text(bearb_90.at(i),TRENNZ_BEARB_PARAM);
                if(zeile.at(0) == BEARBART_BOHR)
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
            for(uint i=0; i<bearb_180.count() ;i++)
            {
                text_zw zeile;
                zeile.set_text(bearb_180.at(i),TRENNZ_BEARB_PARAM);
                if(zeile.at(0) == BEARBART_BOHR)
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
            for(uint i=0; i<bearb_270.count() ;i++)
            {
                text_zw zeile;
                zeile.set_text(bearb_270.at(i),TRENNZ_BEARB_PARAM);
                if(zeile.at(0) == BEARBART_BOHR)
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
            for(uint i=0; i<bearb_0.count() ;i++)
            {
                text_zw zeile;
                zeile.set_text(bearb_0.at(i),TRENNZ_BEARB_PARAM);
                if(zeile.at(0) == BEARBART_NUT)
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
            for(uint i=0; i<bearb_90.count() ;i++)
            {
                text_zw zeile;
                zeile.set_text(bearb_90.at(i),TRENNZ_BEARB_PARAM);
                if(zeile.at(0) == BEARBART_NUT)
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
            for(uint i=0; i<bearb_180.count() ;i++)
            {
                text_zw zeile;
                zeile.set_text(bearb_180.at(i),TRENNZ_BEARB_PARAM);
                if(zeile.at(0) == BEARBART_NUT)
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
            for(uint i=0; i<bearb_270.count() ;i++)
            {
                text_zw zeile;
                zeile.set_text(bearb_270.at(i),TRENNZ_BEARB_PARAM);
                if(zeile.at(0) == BEARBART_NUT)
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
            bewertung_0 = 9999;
            bewertung_90 = 0;
            bewertung_180 = 0;
            bewertung_270 = 0;
        }else if(drehwinkel == "90")
        {
            bewertung_90 = 9999;
            bewertung_0 = 0;
            bewertung_180 = 0;
            bewertung_270 = 0;
        }else if(drehwinkel == "180")
        {
            bewertung_180 = 9999;
            bewertung_0 = 0;
            bewertung_90 = 0;
            bewertung_270 = 0;
        }else if(drehwinkel == "270")
        {
            bewertung_270 = 9999;
            bewertung_0 = 0;
            bewertung_90 = 0;
            bewertung_180 = 0;
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
        rasterbohrungen_finden_fmc(ret_bearb, wkzmag, ret_laenge, ret_breite);
        if(Formartierungen_aufbrechen == true)
        {
            formartierung_zu_einzelfkon(ret_bearb, ret_laenge, ret_breite);
        }
        kurze_an_ab_geraden(ret_bearb, wkzmag);
    }else if(format == "ganx")
    {
        const int ranking_abst_zwanzig = 5;
        hbemiduebeltiefe(bearb);
        double tmp_l = Breite_bekommen;
        double tmp_b = Laenge_bekommen;
        bearb_optimieren_ganx(bearb);
        gehr_3achs(bearb, tmp_l, tmp_b, "ganx", "0");
        //Die beste Drehrichtung herausfinden:
        int bewertung_0    = 1;
        int bewertung_90   = 1;
        int bewertung_180  = 1;
        int bewertung_270  = 1;
        //Stufe 1:
        //heraus bekommen, für welche Lage es Warnungen gibt:
        text_zw bearb_kopie = bearb;
        text_zw bearb_0;
        text_zw bearb_90;
        text_zw bearb_180;
        text_zw bearb_270;
        double l_0 = tmp_l;
        double l_90 = tmp_l;
        double l_180 = tmp_l;
        double l_270 = tmp_l;
        double b_0 = tmp_b;
        double b_90 = tmp_b;
        double b_180 = tmp_b;
        double b_270 = tmp_b;
        QString warnung_0;
        QString warnung_90;
        QString warnung_180;
        QString warnung_270;

        if(drehwinkel == "0" || drehwinkel == "AUTO")
        {
            warnung_0 = warnungen_ganx(bearb_kopie, wkzmag, l_0, b_0);
            if(warnung_0.isEmpty())
            {
                bewertung_0 = 100;
            }else
            {
                bewertung_0 = 0;
            }
            bearb_0 = bearb_kopie;
        }
        if(drehwinkel == "90" || drehwinkel == "AUTO")
        {
            bearb_drehen_90(bearb_kopie, l_90, b_90);
            warnung_90 = warnungen_ganx(bearb_kopie, wkzmag, l_90, b_90);
            if(warnung_90.isEmpty())
            {
                bewertung_90 = 100;
            }else
            {
                bewertung_90 = 0;
            }
            bearb_90 = bearb_kopie;
        }
        if(drehwinkel == "180" || drehwinkel == "AUTO")
        {
            if(drehwinkel == "180")
            {
                bearb_drehen_90(bearb_kopie, l_180, b_180);
                bearb_drehen_90(bearb_kopie, l_180, b_180);
            }else //AUTO
            {
                l_180 = l_90;//Drehung mitnehmen
                b_180 = b_90;//Drehung mitnehmen
                bearb_drehen_90(bearb_kopie, l_180, b_180);
            }
            warnung_180 = warnungen_ganx(bearb_kopie, wkzmag, l_180, b_180);
            if(warnung_180.isEmpty())
            {
                bewertung_180 = 100;
            }else
            {
                bewertung_180 = 0;
            }
            bearb_180 = bearb_kopie;
        }
        if(drehwinkel == "270" || drehwinkel == "AUTO")
        {
            if(drehwinkel == "270")
            {
                bearb_drehen_90(bearb_kopie, l_270, b_270);
                bearb_drehen_90(bearb_kopie, l_270, b_270);
                bearb_drehen_90(bearb_kopie, l_270, b_270);
            }else //AUTO
            {
                l_270 = l_180;//Drehung mitnehmen
                b_270 = b_180;//Drehung mitnehmen
                bearb_drehen_90(bearb_kopie, l_270, b_270);
            }
            warnung_270 = warnungen_ganx(bearb_kopie, wkzmag, l_270, b_270);
            if(warnung_270.isEmpty())
            {
                bewertung_270 = 100;
            }else
            {
                bewertung_270 = 0;
            }
            bearb_270 = bearb_kopie;
        }

        //Stufe 2:
        //heraus bekommen wo vorne ist anhand von Bearbeitungen:
        if(drehwinkel == "0" || drehwinkel == "AUTO")
        {
            for(uint i=0; i<bearb_0.count() ;i++)
            {
                text_zw zeile;
                zeile.set_text(bearb_0.at(i),TRENNZ_BEARB_PARAM);
                if(zeile.at(0) == BEARBART_BOHR)
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
        }
        if(drehwinkel == "90" || drehwinkel == "AUTO")
        {
            for(uint i=0; i<bearb_90.count() ;i++)
            {
                text_zw zeile;
                zeile.set_text(bearb_90.at(i),TRENNZ_BEARB_PARAM);
                if(zeile.at(0) == BEARBART_BOHR)
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
        }
        if(drehwinkel == "180" || drehwinkel == "AUTO")
        {
            for(uint i=0; i<bearb_180.count() ;i++)
            {
                text_zw zeile;
                zeile.set_text(bearb_180.at(i),TRENNZ_BEARB_PARAM);
                if(zeile.at(0) == BEARBART_BOHR)
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
        }
        if(drehwinkel == "270" || drehwinkel == "AUTO")
        {
            for(uint i=0; i<bearb_270.count() ;i++)
            {
                text_zw zeile;
                zeile.set_text(bearb_270.at(i),TRENNZ_BEARB_PARAM);
                if(zeile.at(0) == BEARBART_BOHR)
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
            for(uint i=0; i<bearb_0.count() ;i++)
            {
                text_zw zeile;
                zeile.set_text(bearb_0.at(i),TRENNZ_BEARB_PARAM);
                if(zeile.at(0) == BEARBART_BOHR)
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
            for(uint i=0; i<bearb_90.count() ;i++)
            {
                text_zw zeile;
                zeile.set_text(bearb_90.at(i),TRENNZ_BEARB_PARAM);
                if(zeile.at(0) == BEARBART_BOHR)
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
            for(uint i=0; i<bearb_180.count() ;i++)
            {
                text_zw zeile;
                zeile.set_text(bearb_180.at(i),TRENNZ_BEARB_PARAM);
                if(zeile.at(0) == BEARBART_BOHR)
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
            for(uint i=0; i<bearb_270.count() ;i++)
            {
                text_zw zeile;
                zeile.set_text(bearb_270.at(i),TRENNZ_BEARB_PARAM);
                if(zeile.at(0) == BEARBART_BOHR)
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
        if(drehwinkel == "0" || drehwinkel == "AUTO")
        {
            for(uint i=0; i<bearb_0.count() ;i++)
            {
                text_zw zeile;
                zeile.set_text(bearb_0.at(i),TRENNZ_BEARB_PARAM);
                if(zeile.at(0) == BEARBART_BOHR)
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
            for(uint i=0; i<bearb_90.count() ;i++)
            {
                text_zw zeile;
                zeile.set_text(bearb_90.at(i),TRENNZ_BEARB_PARAM);
                if(zeile.at(0) == BEARBART_BOHR)
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
            for(uint i=0; i<bearb_180.count() ;i++)
            {
                text_zw zeile;
                zeile.set_text(bearb_180.at(i),TRENNZ_BEARB_PARAM);
                if(zeile.at(0) == BEARBART_BOHR)
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
            for(uint i=0; i<bearb_270.count() ;i++)
            {
                text_zw zeile;
                zeile.set_text(bearb_270.at(i),TRENNZ_BEARB_PARAM);
                if(zeile.at(1) == BEARBART_BOHR)
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
        //ist bei GANX nicht nötig weil physisch mit der Maschine nicht möglich

        //Bewertungen auswerten:
        if(drehwinkel == "0")
        {
            bewertung_0 = 9999;
            bewertung_90 = 0;
            bewertung_180 = 0;
            bewertung_270 = 0;
        }else if(drehwinkel == "90")
        {
            bewertung_90 = 9999;
            bewertung_0 = 0;
            bewertung_180 = 0;
            bewertung_270 = 0;
        }else if(drehwinkel == "180")
        {
            bewertung_180 = 9999;
            bewertung_0 = 0;
            bewertung_90 = 0;
            bewertung_270 = 0;
        }else if(drehwinkel == "270")
        {
            bewertung_270 = 9999;
            bewertung_0 = 0;
            bewertung_90 = 0;
            bewertung_180 = 0;
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
        rasterbohrungen_finden_ganx(ret_bearb, wkzmag, ret_laenge, ret_breite);
    }else if(format == "ggf" || format == "eigen")
    {
        fraesergeraden_zusammenfassen(bearb);
        hbemiduebeltiefe(bearb);
        double tmp_l = Laenge_bekommen;
        double tmp_b = Breite_bekommen;
        gehr_3achs(bearb, tmp_l, tmp_b, format, "0");
        if(drehwinkel == "0" || drehwinkel == "AUTO")
        {
            //tue nichts
        }else if(drehwinkel == "90")
        {
            bearb_drehen_90(bearb, tmp_l, tmp_b);
        }else if(drehwinkel == "180")
        {
            bearb_drehen_90(bearb, tmp_l, tmp_b);
            bearb_drehen_90(bearb, tmp_l, tmp_b);
        }else //if(drehwinkel == "270")
        {
            bearb_drehen_90(bearb, tmp_l, tmp_b);
            bearb_drehen_90(bearb, tmp_l, tmp_b);
            bearb_drehen_90(bearb, tmp_l, tmp_b);
        }
        if(Formartierungen_aufbrechen == true)
        {
            formartierung_zu_einzelfkon(ret_bearb, ret_laenge, ret_breite);
        }
        kurze_an_ab_geraden(ret_bearb, wkzmag);
        ret_drehung     = "0";
        ret_bewertung   =  0 ;
        ret_warnungen.clear();
        ret_bearb = bearb;
        ret_laenge = tmp_l;
        ret_breite = tmp_b;        
    }else if(format == "cix")
    {
        fraesergeraden_zusammenfassen(bearb);
        hbemiduebeltiefe(bearb);
        double tmp_l = Laenge_bekommen;
        double tmp_b = Breite_bekommen;
        gehr_3achs(bearb, tmp_l, tmp_b, format, "0");
        //Die beste Drehrichtung herausfinden:
        int bewertung_0    = 1;
        int bewertung_90   = 1;
        int bewertung_180  = 1;
        int bewertung_270  = 1;
        //Stufe 1:
        //heraus bekommen, für welche Lage es Warnungen gibt:
        text_zw bearb_kopie = bearb;
        text_zw bearb_0;
        text_zw bearb_90;
        text_zw bearb_180;
        text_zw bearb_270;
        double l_0 = tmp_l;
        double l_90 = tmp_l;
        double l_180 = tmp_l;
        double l_270 = tmp_l;
        double b_0 = tmp_b;
        double b_90 = tmp_b;
        double b_180 = tmp_b;
        double b_270 = tmp_b;
        QString warnung_0;
        QString warnung_90;
        QString warnung_180;
        QString warnung_270;
        if(drehwinkel == "0" || drehwinkel == "AUTO")
        {
            warnung_0 = warnungen_cix(bearb_kopie, wkzmag, l_0, b_0);
            if(warnung_0.isEmpty())
            {
                bewertung_0 = 100;
            }else
            {
                bewertung_0 = 0;
            }
            bearb_0 = bearb_kopie;
        }
        if(drehwinkel == "90" || drehwinkel == "AUTO")
        {
            bearb_drehen_90(bearb_kopie, l_90, b_90);
            warnung_90 = warnungen_cix(bearb_kopie, wkzmag, l_90, b_90);
            if(warnung_90.isEmpty())
            {
                bewertung_90 = 100;
            }else
            {
                bewertung_90 = 0;
            }
            bearb_90 = bearb_kopie;
        }
        if(drehwinkel == "180" || drehwinkel == "AUTO")
        {
            if(drehwinkel == "180")
            {
                bearb_drehen_90(bearb_kopie, l_180, b_180);
                bearb_drehen_90(bearb_kopie, l_180, b_180);
            }else //AUTO
            {
                l_180 = l_90;//Drehung mitnehmen
                b_180 = b_90;//Drehung mitnehmen
                bearb_drehen_90(bearb_kopie, l_180, b_180);
            }
            warnung_180 = warnungen_cix(bearb_kopie, wkzmag, l_180, b_180);
            if(warnung_180.isEmpty())
            {
                bewertung_180 = 100;
            }else
            {
                bewertung_180 = 0;
            }
            bearb_180 = bearb_kopie;
        }
        if(drehwinkel == "270" || drehwinkel == "AUTO")
        {
            if(drehwinkel == "270")
            {
                bearb_drehen_90(bearb_kopie, l_270, b_270);
                bearb_drehen_90(bearb_kopie, l_270, b_270);
                bearb_drehen_90(bearb_kopie, l_270, b_270);
            }else //AUTO
            {
                l_270 = l_180;//Drehung mitnehmen
                b_270 = b_180;//Drehung mitnehmen
                bearb_drehen_90(bearb_kopie, l_270, b_270);
            }
            warnung_270 = warnungen_cix(bearb_kopie, wkzmag, l_270, b_270);
            if(warnung_270.isEmpty())
            {
                bewertung_270 = 100;
            }else
            {
                bewertung_270 = 0;
            }
            bearb_270 = bearb_kopie;
        }
        //Stufe 2:
        //heraus bekommen wo vorne ist anhand von Bearbeitungen:
        //...

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

        //Stufe 6:
        //Flächenbohrungen mit geringem Kantenabstand bevorzugen
        if(drehwinkel == "0" || drehwinkel == "AUTO")
        {
            for(uint i=0; i<bearb_0.count() ;i++)
            {
                text_zw zeile;
                zeile.set_text(bearb_0.at(i), TRENNZ_BEARB_PARAM);
                if(zeile.at(0) == BEARBART_BOHR)
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
            for(uint i=0; i<bearb_90.count() ;i++)
            {
                text_zw zeile;
                zeile.set_text(bearb_90.at(i),TRENNZ_BEARB_PARAM);
                if(zeile.at(0) == BEARBART_BOHR)
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
            for(uint i=0; i<bearb_180.count() ;i++)
            {
                text_zw zeile;
                zeile.set_text(bearb_180.at(i),TRENNZ_BEARB_PARAM);
                if(zeile.at(0) == BEARBART_BOHR)
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
            for(uint i=0; i<bearb_270.count() ;i++)
            {
                text_zw zeile;
                zeile.set_text(bearb_270.at(i),TRENNZ_BEARB_PARAM);
                if(zeile.at(0) == BEARBART_BOHR)
                {
                    bohrung bo(zeile.text());
                    if(bo.x() < 20 || bo.y() < 20)
                    {
                        bewertung_270 += 1;
                    }
                }
            }
        }

        //Bewertungen auswerten:
        if(drehwinkel == "0")
        {
            bewertung_0 = 9999;
            bewertung_90 = 0;
            bewertung_180 = 0;
            bewertung_270 = 0;
        }else if(drehwinkel == "90")
        {
            bewertung_90 = 9999;
            bewertung_0 = 0;
            bewertung_180 = 0;
            bewertung_270 = 0;
        }else if(drehwinkel == "180")
        {
            bewertung_180 = 9999;
            bewertung_0 = 0;
            bewertung_90 = 0;
            bewertung_270 = 0;
        }else if(drehwinkel == "270")
        {
            bewertung_270 = 9999;
            bewertung_0 = 0;
            bewertung_90 = 0;
            bewertung_180 = 0;
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
        rasterbohrungen_finden_fmc(ret_bearb, wkzmag, ret_laenge, ret_breite);
        if(Formartierungen_aufbrechen == true)
        {
            formartierung_zu_einzelfkon(ret_bearb, ret_laenge, ret_breite);
        }
        kurze_an_ab_geraden(ret_bearb, wkzmag);
    }

    Drehung.append(ret_drehung);
    Bewertung.append(ret_bewertung);
    Warnungen.append(ret_warnungen);
    Bearb.append(ret_bearb);
    Laenge.append(ret_laenge);
    Breite.append(ret_breite);
}
void wstzustand::fraesergeraden_zusammenfassen(text_zw& bearbeitung)
{
    for(uint i=0 ; i+1<bearbeitung.count() ; i++)
    {
        text_zw zeile;
        zeile.set_text(bearbeitung.at(i), TRENNZ_BEARB_PARAM);
        text_zw folgezeile;
        folgezeile.set_text(bearbeitung.at(i+1), TRENNZ_BEARB_PARAM);

        if(zeile.at(0) == BEARBART_FRAESERGERADE &&\
           folgezeile.at(0) == BEARBART_FRAESERGERADE)
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
                bearbeitung.edit(i, fg1.text());
                bearbeitung.entf(i+1);
                i--;
            }
        }

    }
}
void wstzustand::hbemiduebeltiefe(text_zw& bearbeitung)
{
    //Diese Funktion stellt die Lochtiefe für die Dübel 8x30 bei den
    //HBEs einheitlich auf 18mm ein, damit es nicht zu Problemen in
    //der Fertigung kommt wenn die Löcher CNC-gebohrt werden und mit dem
    //Dübelautomaten die Dübel eingetrieben werden

    const double min = 16;//Maximale Dübellochtiefe
    const double max = 18;//Minimale Dübellochtiefe
    for(uint i=0 ; i<bearbeitung.count() ; i++)
    {
        text_zw zeile;
        zeile.set_text(bearbeitung.at(i), TRENNZ_BEARB_PARAM);
        if(zeile.at(0) == BEARBART_BOHR)
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
                        bearbeitung.edit(i, bo.text());
                    }
                }
            }
        }else if(zeile.at(0) == BEARBART_BOHRRASTER)
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
                        bearbeitung.edit(i, bo.text());
                    }
                }
            }
        }
    }
}
void wstzustand::gehr_3achs(text_zw& bearb, double &tmp_l, double &tmp_b, QString ausgabeformat, QString drehwi)
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

    for(uint i=0; i<bearb.count() ;i++)
    {
        text_zw zeile;
        zeile.set_text(bearb.at(i), TRENNZ_BEARB_PARAM);
        //QString zeile_neu;
        if(zeile.at(0) == BEARBART_GEHRUNG)
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
            bearb.entf(i);
            i--;
        }
    }

    //Wo eine Kante ist wo eine Gehrung ist keine Maßzugabe geben:
    if(li == true)
    {
        QString kante;
        if (ausgabeformat == "ganx")
        {
            kante = kante_li_ganx(drehwi);
        }else
        {
            kante = kante_li(drehwi);
        }
        if(!kante.isEmpty())
        {
            li = false;
        }
    }
    if(re == true)
    {
        QString kante;
        if (ausgabeformat == "ganx")
        {
            kante = kante_re_ganx(drehwi);
        }else
        {
            kante = kante_re(drehwi);
        }
        if(!kante.isEmpty())
        {
            re = false;
        }
    }
    if(ob == true)
    {
        QString kante;
        if (ausgabeformat == "ganx")
        {
            kante = kante_hi_ganx(drehwi);
        }else
        {
            kante = kante_hi(drehwi);
        }
        if(!kante.isEmpty())
        {
            ob = false;
        }
    }
    if(un == true)
    {
        QString kante;
        if (ausgabeformat == "ganx")
        {
            kante = kante_vo_ganx(drehwi);
        }else
        {
            kante = kante_vo(drehwi);
        }
        if(!kante.isEmpty())
        {
            un = false;
        }
    }

    //Schritt 2:
    //WST vergrößern
    //andere Bearbeitungen gem vergrößerung verschieben
    double zugabe = Zugabe_gehrungen;
    if(li == true) //X-Werte verschieben
    {
        tmp_l += zugabe;
        for(uint i=0; i<bearb.count() ;i++)
        {
            text_zw zeile;
            zeile.set_text(bearb.at(i), TRENNZ_BEARB_PARAM);
            QString zeile_neu;
            if(zeile.at(0) == BEARBART_BOHR)
            {
                bohrung bo(zeile.text());
                bo.set_x(bo.x() + zugabe);
                zeile_neu = bo.text();
            }else if(zeile.at(0) == BEARBART_BOHRRASTER)
            {
                bohrraster bora(zeile.text());
                bora.set_x((bora.x() + zugabe));
                zeile_neu = bora.text();
            }else if(zeile.at(0) == BEARBART_RTA)
            {
                rechtecktasche rt(zeile.text());
                rt.set_x(rt.x() + zugabe);
                zeile_neu = rt.text();
            }else if(zeile.at(0) == BEARBART_NUT)
            {
                nut nu(zeile.text());
                nu.set_xs(nu.xs() + zugabe);
                nu.set_xe(nu.xe() + zugabe);
                zeile_neu = nu.text();
            }else if(zeile.at(0) == BEARBART_FRAESERAUFRUF)
            {
                fraeseraufruf tmp(zeile.text());
                tmp.set_x(tmp.x() + zugabe);
                zeile_neu = tmp.text();
            }else if(zeile.at(0) == BEARBART_FRAESERGERADE)
            {
                fraesergerade tmp(zeile.text());
                tmp.set_xs(tmp.xs() + zugabe);
                tmp.set_xe(tmp.xe() + zugabe);
                zeile_neu = tmp.text();
            }else if(zeile.at(0) == BEARBART_FRAESERBOGEN)
            {
                fraeserbogen tmp(zeile.text());
                tmp.set_xs(tmp.xs() + zugabe);
                tmp.set_xe(tmp.xe() + zugabe);
                zeile_neu = tmp.text();
            }

            bearb.edit(i, zeile_neu);
        }
    }
    if(re == true)
    {
        tmp_l += zugabe;
    }
    if(un == true) //Y-Werte verschieben
    {
        tmp_b += zugabe;
        for(uint i=0; i<bearb.count() ;i++)
        {
            text_zw zeile;
            zeile.set_text(bearb.at(i), TRENNZ_BEARB_PARAM);
            QString zeile_neu;
            if(zeile.at(0) == BEARBART_BOHR)
            {
                bohrung bo(zeile.text());
                bo.set_y(bo.y() + zugabe);
                zeile_neu = bo.text();
            }else if(zeile.at(0) == BEARBART_BOHRRASTER)
            {
                bohrraster bora(zeile.text());
                bora.set_y((bora.y() + zugabe));
                zeile_neu = bora.text();
            }else if(zeile.at(0) == BEARBART_RTA)
            {
                rechtecktasche rt(zeile.text());
                rt.set_y(rt.y() + zugabe);
                zeile_neu = rt.text();
            }else if(zeile.at(0) == BEARBART_NUT)
            {
                nut nu(zeile.text());
                nu.set_ys(nu.ys() + zugabe);
                nu.set_ye(nu.ye() + zugabe);
                zeile_neu = nu.text();
            }else if(zeile.at(0) == BEARBART_FRAESERAUFRUF)
            {
                fraeseraufruf tmp(zeile.text());
                tmp.set_y(tmp.y() + zugabe);
                zeile_neu = tmp.text();
            }else if(zeile.at(0) == BEARBART_FRAESERGERADE)
            {
                fraesergerade tmp(zeile.text());
                tmp.set_ys(tmp.ys() + zugabe);
                tmp.set_ye(tmp.ye() + zugabe);
                zeile_neu = tmp.text();
            }else if(zeile.at(0) == BEARBART_FRAESERBOGEN)
            {
                fraeserbogen tmp(zeile.text());
                tmp.set_ys(tmp.ys() + zugabe);
                tmp.set_ye(tmp.ye() + zugabe);
                zeile_neu = tmp.text();
            }

            bearb.edit(i, zeile_neu);
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
    for(uint i=0; i<bearb.count() ;i++)
    {
        text_zw zeile;
        zeile.set_text(bearb.at(i), TRENNZ_BEARB_PARAM);
        if(zeile.at(1) == WST_BEZUG_OBSEI)
        {
            obsei = true;
        }else if(zeile.at(1) == WST_BEZUG_UNSEI)
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
void wstzustand::drehen_um_b_halbe(text_zw& bearb, double &tmp_b)
{
    for(uint i=0; i<bearb.count() ;i++)
    {
        text_zw zeile;
        zeile.set_text(bearb.at(i), TRENNZ_BEARB_PARAM);
        QString zeile_neu;
        if(zeile.at(0) == BEARBART_BOHR)
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
        }else if(zeile.at(0) == BEARBART_BOHRRASTER)
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
        }else if(zeile.at(0) == BEARBART_RTA)
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
        }else if(zeile.at(0) == BEARBART_NUT)
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
        }else if(zeile.at(0) == BEARBART_FRAESERAUFRUF)
        {
            fraeseraufruf tmp(zeile.text());
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
        }else if(zeile.at(0) == BEARBART_FRAESERGERADE)
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
        }else if(zeile.at(0) == BEARBART_FRAESERBOGEN)
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

        bearb.edit(i, zeile_neu);
    }
}
void wstzustand::bearb_drehen_90(text_zw& bearb, double& tmp_l, double& tmp_b)
{
    //diese Funktion dreht die Bearbeitungen um 90° im Uhrzeigersin

    for(uint i=0; i<bearb.count() ;i++)
    {
        text_zw zeile;
        zeile.set_text(bearb.at(i), TRENNZ_BEARB_PARAM);
        QString zeile_neu;

        if(zeile.at(0) == BEARBART_BOHR)
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
        }else if(zeile.at(0) == BEARBART_BOHRRASTER)
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
        }else if(zeile.at(0) == BEARBART_RTA)
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
        }else if(zeile.at(0) == BEARBART_NUT)
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
        }else if(zeile.at(0) == BEARBART_FRAESERAUFRUF)
        {
            fraeseraufruf tmp(zeile.text());
            double x = tmp.x();
            double y = tmp.y();

            tmp.set_x(y);
            tmp.set_y(tmp_l - x);
            zeile_neu = tmp.text();
        }else if(zeile.at(0) == BEARBART_FRAESERGERADE)
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
        }else if(zeile.at(0) == BEARBART_FRAESERBOGEN)
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

        bearb.edit(i, zeile_neu);
    }
    //Länge und Breite tauschen:
    double tmp;
    tmp = tmp_l;
    tmp_l = tmp_b;
    tmp_b = tmp;
}
void wstzustand::bearb_optimieren_ganx(text_zw& bearb)
{
    //X-Werte werden Y-Werte und umgehrt
    //Bearbeitungen wechseln von der Ober- auf die Unterseite und umgehrt

    for(uint i=0; i<=bearb.count() ;i++)
    {
        text_zw zeile;
        zeile.set_text(bearb.at(i), TRENNZ_BEARB_PARAM);
        QString zeile_neu;

        if(zeile.at(0) == BEARBART_BOHR)
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
        }else if(zeile.at(0) == BEARBART_BOHRRASTER)
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
        }else if(zeile.at(0) == BEARBART_RTA)
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
        }else if(zeile.at(0) == BEARBART_NUT)
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
        }else if(zeile.at(0) == BEARBART_GEHRUNG)
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
            s.set_stapu(sp);
            s.set_endpu(ep);
            ge.set_pfad(s);
            zeile_neu = ge.text();
        }
        bearb.edit(i, zeile_neu);
    }
}
void wstzustand::dubosplitten(text_zw& bearb, wkz_magazin& wkzmag)
{
    //Diese Funktion soll Durchgangs-Bohrungen finden
    //Gibt es für eine Durchgangsbohrung keinen Duchgangsborer so soll das Loch von beiden Plattenseiten gebohrt werden
    //Gibt es einen Durchgangsbohrer, dieser ist jedoch zu kurz so soll das Loch von beiden Plattenseiten gebohrt werden
    //Diese Funktion sollte vor der Funktion zum finden von Bohrrastern aufgerufen werden
    //da Bohrraster hier nicht berücksichtigt werden
    text_zw bearb_neu;

    for(uint i=0; i< bearb.count() ;i++)
    {
        bool editiert = false;
        text_zw param;
        param.set_text(bearb.at(i), TRENNZ_BEARB_PARAM);
        if(param.at(0) == BEARBART_BOHR)
        {
            QString bezflaeche = param.at(1);
            if(bezflaeche == WST_BEZUG_OBSEI  ||  bezflaeche == WST_BEZUG_UNSEI  )
            {
                bohrung bo(param.text());
                if(bo.tiefe() >= Dicke)
                {
                    QString tnummer = wkzmag.wkznummer(WKZ_TYP_BOHRER, bo.dm(), bo.tiefe(), Dicke, bo.bezug());
                    if(tnummer.isEmpty())
                    {
                        bohrung boA = bo;
                        double boti = Dicke/2 + 2;
                        boA.set_tiefe(boti);
                        tnummer = wkzmag.wkznummer(WKZ_TYP_BOHRER, bo.dm(), boti, Dicke, bo.bezug());
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
                            bearb_neu.add_hi(boA.text());
                            bearb_neu.add_hi(boB.text());
                            editiert = true;
                        }
                    }
                }
            }
        }
        if(editiert == false)
        {
            bearb_neu.add_hi(bearb.at(i));
        }
    }
    bearb = bearb_neu;
}
QString wstzustand::warnungen_fmc(text_zw bearb, wkz_magazin wkzmag, double tmp_l, double tmp_b)
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

    for(uint i=0; i<bearb.count() ;i++)
    {
        text_zw zeile;
        zeile.set_text(bearb.at(i), TRENNZ_BEARB_PARAM);

        QString art = zeile.at(0);
        if(art == BEARBART_BOHR || art == BEARBART_BOHRRASTER)
        {
            //BOHRUNG ist eine Teilmenge von BOHRRASTER
            bohrung bo(zeile.text());//die nicht benötigten Parameter werden beim einlesen ignoriert
            QString bezug = bo.bezug();

            QString tnummer = wkzmag.wkznummer(WKZ_TYP_BOHRER, bo.dm(), bo.tiefe(), Dicke, bezug);
            if(tnummer.isEmpty())//Bohren nicht möglich weil kein passendes Werkzeug
            {
                //Ist direkt ei WKZ definiert?
                if(bo.bezug() == WST_BEZUG_OBSEI || bo.bezug() == WST_BEZUG_UNSEI)
                {
                    tnummer = wkzmag.wkznummer_von_alias(bo.wkznum(), WKZ_VERT);
                }else
                {
                    tnummer = wkzmag.wkznummer_von_alias(bo.wkznum(), WKZ_HORI);
                }
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
                    msg += bearb.at(i).replace("\t", " | ");
                    msg += "\n";
                }
            }

        }else if(art == BEARBART_RTA)
        {
            rechtecktasche rt(zeile.text());

            //Prüfen ob Nutzlänge ausreichend für Tati ist:
            //Ist direkt ei WKZ definiert?
            QString tnummer;
            if(rt.bezug() == WST_BEZUG_OBSEI || rt.bezug() == GANX_WST_BEZUG_UNSEI)
            {
                tnummer = wkzmag.wkznummer_von_alias(rt.wkznum(), WKZ_VERT);
            }else
            {
                tnummer = wkzmag.wkznummer_von_alias(rt.wkznum(), WKZ_HORI);
            }
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
            fraeseraufruf fa(zeile.text());
            QString tnummer = wkzmag.wkznummer_von_alias(fa.wkznum(), WKZ_VERT);
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
QString wstzustand::warnungen_ganx(text_zw bearb, wkz_magazin wkzmag, double tmp_l, double tmp_b)
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

    for(uint i=0; i<bearb.count() ;i++)
    {
        text_zw zeile;
        zeile.set_text(bearb.at(i), TRENNZ_BEARB_PARAM);

        QString art = zeile.at(0);
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
                //Ist direkt ei WKZ definiert?
                if(bo.bezug() == WST_BEZUG_OBSEI || bo.bezug() == WST_BEZUG_UNSEI)
                {
                    tnummer = wkzmag.wkznummer_von_alias(bo.wkznum(), WKZ_VERT);
                }else
                {
                    tnummer = wkzmag.wkznummer_von_alias(bo.wkznum(), WKZ_HORI);
                }
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
                    msg += bearb.at(i).replace("\t", " | ");
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
            //Ist direkt ei WKZ definiert?
            QString tnummer;
            if(rt.bezug() == WST_BEZUG_OBSEI || rt.bezug() == WST_BEZUG_UNSEI)
            {
                tnummer = wkzmag.wkznummer_von_alias(rt.wkznum(), WKZ_VERT);
            }else
            {
                tnummer = wkzmag.wkznummer_von_alias(rt.wkznum(), WKZ_HORI);
            }
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
QString wstzustand::warnungen_cix(text_zw bearb, wkz_magazin wkzmag, double tmp_l, double tmp_b)
{
    dubosplitten(bearb, wkzmag);
    QString msg = "";

    //...

    return msg;
}
void wstzustand::rasterbohrungen_finden_fmc(text_zw& bearb, wkz_magazin wkzmag,double tmp_l, double tmp_b)
{
    bohrraster bora;

    text_zw wkzbodm; //Speichert die verschiedenen vorhandenen Bohrdurchmesser
    int min_rasterbohrungen_anz = 3;

    text_zw boti;
    for(uint i=0; i< bearb.count() ;i++)
    {
        text_zw param;
        param.set_text(bearb.at(i), TRENNZ_BEARB_PARAM);
        if(param.at(0) == BEARBART_BOHR)
        {
            bohrung b(param.text());
            QString tiefe_neu = b.tiefe_qstring();
            bool schon_da = false;
            for(uint i=0; i<boti.count();i++)
            {
                if(tiefe_neu == boti.at(i))
                {
                    schon_da = true;
                }
            }
            if(schon_da == false)
            {
                boti.add_hi(tiefe_neu);
            }
        }
    }

    //Alle vertikalen Lochraster finden die zu Bohrern im Werkzeugmagazin passen:
    wkzbodm = wkzmag.alle_bodm_verti();

    for(uint i=0; i<wkzbodm.count() ;i++)
    {
        double dm = wkzbodm.at(i).toDouble();

        for(uint i=0; i<boti.count() ; i++)
        {
            double tiefe = boti.at(i).toDouble();
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
                                                        Dicke,\
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
                                                        Dicke,\
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
                                                        Dicke,\
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
                                                        Dicke,\
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
                                                        Dicke,\
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
                                                        Dicke,\
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
                                                        Dicke,\
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
                                                        Dicke,\
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
                                                        Dicke,\
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
                                                        Dicke,\
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
                                                        Dicke,\
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
                                                        Dicke,\
                                                        min_rasterbohrungen_anz,\
                                                        96);
            }
        }
    }

    //HBEs im Raser finden die zu Bohrern im Werkzeugmagazin passen:
    wkzbodm = wkzmag.alle_bodm_hori();

    for(uint i=0; i<wkzbodm.count() ;i++)
    {
        double dm = wkzbodm.at(i).toDouble();

        for(uint i=0; i<boti.count() ; i++)
        {
            double tiefe = boti.at(i).toDouble();
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
                                                        Dicke,\
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
                                                        Dicke,\
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
                                                        Dicke,\
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
                                                        Dicke,\
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
                                                        Dicke,\
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
                                                        Dicke,\
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
                                                        Dicke,\
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
                                                        Dicke,\
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
                                                        Dicke,\
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
                                                        Dicke,\
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
                                                        Dicke,\
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
                                                        Dicke,\
                                                        min_rasterbohrungen_anz,\
                                                        96);
            }
        }
    }

}
void wstzustand::rasterbohrungen_finden_ganx(text_zw& bearb, wkz_magazin wkzmag,double tmp_l, double tmp_b)
{
    bohrraster bora;

    text_zw wkzbodm; //Speichert die verschiedenen vorhandenen Bohrdurchmesser
    int min_rasterbohrungen_anz = 2;

    text_zw boti;
    for(uint i=0; i< bearb.count() ;i++)
    {
        text_zw param;
        param.set_text(bearb.at(i), TRENNZ_BEARB_PARAM);
        if(param.at(0) == BEARBART_BOHR)
        {
            bohrung b(param.text());
            QString tiefe_neu = b.tiefe_qstring();
            bool schon_da = false;
            for(uint i=0; i<boti.count();i++)
            {
                if(tiefe_neu == boti.at(i))
                {
                    schon_da = true;
                }
            }
            if(schon_da == false)
            {
                boti.add_hi(tiefe_neu);
            }
        }
    }

    //Alle vertikalen Lochraster finden die zu Bohrern im Werkzeugmagazin passen:
    wkzbodm = wkzmag.alle_bodm_verti();

    for(uint i=0; i<wkzbodm.count() ;i++)
    {
        double dm = wkzbodm.at(i).toDouble();

        for(uint i=0; i<boti.count() ; i++)
        {
            double tiefe = boti.at(i).toDouble();
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
}
void wstzustand::formartierung_zu_einzelfkon(text_zw& bearb,double tmp_l, double tmp_b)
{
    //Diese Funktion soll die vom VW ausgegebenen Poligonförmigen Formartierungen entdecken.
    //Diese werden generiert, wenn die Grundfläche eines 3D-Bauteils kein Rechteck ist
    //Die Bestandteile der Fräskontur, die deckungsgleich auf der Kante liegen werden nicht benötigt
    //Und werden durch diese Funktion heraus genommen

    //Prüfen ob wst eine umlaufende Formartierung enthällt:
    for(uint i=0; i< bearb.count() ;i++)
    {
        text_zw param;
        param.set_text(bearb.at(i), TRENNZ_BEARB_PARAM);
        if(param.at(0) == BEARBART_FRAESERAUFRUF)
        {
            uint zeibeg = i;
            uint zeiend = i;
            fraeseraufruf fa(param.text());
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
            if(i< bearb.count())
            {
                i++;
                for(; i< bearb.count() ;i++)
                {
                    param.set_text(bearb.at(i), TRENNZ_BEARB_PARAM);
                    if(param.at(0) == BEARBART_FRAESERGERADE)
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
                    }else if(param.at(0) == BEARBART_FRAESERBOGEN)
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
                        text_zw bearb_neu;
                        bearb_neu.set_text(fa.text(), '\n');

                        for(uint ii=zeibeg+1; ii<=zeiend ;ii++)
                        {
                            text_zw param;
                            param.set_text(bearb.at(ii), TRENNZ_BEARB_PARAM);                            

                            if(param.at(0) == BEARBART_FRAESERGERADE)
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
                                    QString vorzeile = bearb_neu.at(bearb_neu.count()-1);
                                    text_zw vorparam;
                                    vorparam.set_text(vorzeile, TRENNZ_BEARB_PARAM);
                                    if(vorparam.at(0) == BEARBART_FRAESERAUFRUF)
                                    {
                                        fraeseraufruf tmpfa(vorparam.text());
                                        tmpfa.set_x(fg.xe());
                                        tmpfa.set_y(fg.ye());
                                        bearb_neu.edit(bearb_neu.count()-1, tmpfa.text());
                                    }else
                                    {
                                        fa.set_x(fg.xe());
                                        fa.set_y(fg.ye());
                                        bearb_neu.add_hi(fa.text());
                                    }
                                }else
                                {
                                    bearb_neu.add_hi(bearb.at(ii));
                                }
                            }else
                            {
                                bearb_neu.add_hi(bearb.at(ii));
                            }
                        }
                        //prüfen ob letzte Zeile von bearb_neu fa ist und ggf löschen:
                        text_zw endparam;
                        endparam.set_text(bearb_neu.at(bearb_neu.count()-1), TRENNZ_BEARB_PARAM);
                        if(endparam.at(0) == BEARBART_FRAESERAUFRUF)
                        {
                            bearb_neu.entf(bearb_neu.count()-1);
                        }
                        //bearb.zeile(zeibeg bis zeiend) gegen bearb_neu austauschen:
                        if(zeiend+1 < bearb.count())
                        {
                            bearb.entf(zeibeg, zeiend-zeibeg+1);
                            bearb.add_mi(zeibeg, bearb_neu.text());
                            i = zeibeg+bearb_neu.count()-1;
                        }else
                        {
                            bearb.entf(zeibeg, zeiend-zeibeg+1);
                            bearb.add_hi(bearb_neu.text());
                            i = bearb.count()-1;
                        }
                    }
                }
            }
        }
    }
}
void wstzustand::kurze_an_ab_geraden(text_zw& bearb, wkz_magazin wkzmag)
{
    //Geraden die Kürzer sind als der Fräser-Durchmesser und ungünstig liegen kann
    //die CNC-Maschine nicht korrekt verarbeiten
    //in Folge fährt die CNC einen ungewollten Kringel
    //Dies soll durch diese Funktion verringert werden
    double wkzdm = 2;//Defaultwert
    double afb = false; //Bei Fräserradiuskorrektur 0 soll die Funktion keine Änderungen vornehmen

    for(uint i=0; i< bearb.count() ;i++)
    {
        text_zw param;
        param.set_text(bearb.at(i),TRENNZ_BEARB_PARAM);
        if(param.at(0) == BEARBART_FRAESERAUFRUF)//zu Kurze Geraden am Anfang finden
        {
            fraeseraufruf fa(param.text());
            if(  fa.radkor() == FRKOR_L  ||  fa.radkor() == FRKOR_R  )
            {
                afb = true;
            }else
            {
                afb = false;
                continue; //For-Schleife in die nächste Runde
            }
            QString tnummer = wkzmag.wkznummer_von_alias(fa.wkznum(), WKZ_VERT);
            if(!tnummer.isEmpty())
            {
                wkzdm = wkzmag.dm(tnummer).toDouble();                
            }else
            {
                wkzdm = 2;//Defaultwert
            }
            if(i+1 < bearb.count())
            {
                text_zw param2; //Folgezeile
                param2.set_text(bearb.at(i+1),TRENNZ_BEARB_PARAM);
                if(param2.at(0) == BEARBART_FRAESERGERADE)
                {
                    fraesergerade fg(param2.text());
                    strecke s;
                    s.set_stapu(fg.sp());
                    s.set_endpu(fg.ep());
                    if(wkzdm >= s.laenge2d())
                    {
                        s.set_laenge_2d(wkzdm+1, strecke_bezugspunkt_ende);
                        fa.set_x(s.stapu().x());
                        fa.set_y(s.stapu().y());
                        fg.set_xs(s.stapu().x());
                        fg.set_ys(s.stapu().y());
                        bearb.edit(i, fa.text());
                        bearb.edit(i+1, fg.text());
                        i++;
                    }
                }                
            }            
        }else if(param.at(0) == BEARBART_FRAESERGERADE  &&  afb == true)//zu Kurze Geraden am Ende finden
        {
            bool ist_schlussgerade = false;
            if(i+1 < bearb.count())
            {
                text_zw param2; //Folgezeile
                param2.set_text(bearb.at(i+1),TRENNZ_BEARB_PARAM);
                if(  param2.at(0) != BEARBART_FRAESERGERADE  &&  param2.at(0) != BEARBART_FRAESERBOGEN  )
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
                strecke s;
                s.set_stapu(fg.sp());
                s.set_endpu(fg.ep());
                if(wkzdm >= s.laenge2d())
                {
                    s.set_laenge_2d(wkzdm+1, strecke_bezugspunkt_start);
                    fg.set_xe(s.endpu().x());
                    fg.set_ye(s.endpu().y());
                    bearb.edit(i, fg.text());
                }
                return;
            }
        }
    }
}
QString wstzustand::kommentar_fmc(QString kom)
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
QString wstzustand::variable_fmc(QString bez, QString wert)
{
    QString text;
    text = FMC_VAR;
    text += "\n";
    text += FMC_VAR_NAME;
    text += "=";
    text += bez;
    text += "\n";
    text += FMC_VAR_WERT;
    text += "=";
    text += wert;
    text += "\n";
    text += FMC_VAR_BEZ;
    text += "=";
    text += "Variable ";
    text += bez;
    text += "\n";
    text += FMC_VAR_AFB;
    text += "=";
    text += "1";
    text += "\n";
    text += "\n";
    return text;
}
QString wstzustand::kommentar_ggf(QString kom)
{
    QString text;
    text = ">KOMMENTAR:[KOM]";
    text += kom;
    text += ";[AFB]1;#ENDE#";
    text += "\n";
    return text;
}
QString wstzustand::fmc_kommentar_gute_seite(text_zw& bearb)
{
    QString retmsg;
    if(Name.contains("Seite"))
    {
        bool hat_5er_durchgangsbohrungen = false;
        text_zw zeile;
        for(uint i=0; i<bearb.count() ;i++)
        {
            zeile.set_text(bearb.at(i),TRENNZ_BEARB_PARAM);
            if(zeile.at(0) == BEARBART_BOHR)
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
        text_zw zeile;
        for(uint i=0; i<bearb.count() ;i++)
        {
            zeile.set_text(bearb.at(i),TRENNZ_BEARB_PARAM);
            if(zeile.at(0) == BEARBART_BOHR)
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
        text_zw zeile;
        for(uint i=0; i<bearb.count() ;i++)
        {
            zeile.set_text(bearb.at(i),TRENNZ_BEARB_PARAM);
            if(zeile.at(0) == BEARBART_BOHR)
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
bool wstzustand::punkt_auf_wst(double x, double y, double l, double b, double tolleranz)
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
QString wstzustand::fehler_kein_WKZ(QString exportformat, text_zw bearbzeile)
{
    QString fehlermeldung;

    fehlermeldung += "Fehler bei ";
    fehlermeldung += exportformat;
    fehlermeldung += "-Export!\n";

    fehlermeldung += "Teilname: ";
    fehlermeldung += Name;
    fehlermeldung += "\n";

    fehlermeldung += "Kein Werkzeug fuer ";

    fehlermeldung += bearb_menschlich_lesbar(bearbzeile);

    return fehlermeldung;
}
QString wstzustand::bearb_menschlich_lesbar(text_zw bearbzeile)
{
    //Hier fehlen noch Bohrraster und Gehrung
    QString daten;
    if(bearbzeile.at(0) == BEARBART_BOHR)
    {
        daten += "Bohrung oder Kreistasche:\n";
        daten += "Bezugsflaeche: ";
        daten += bearbzeile.at(1);
        daten += "\n";
        daten += "Durchmesser: ";
        daten += bearbzeile.at(2);
        daten += "\n";
        daten += "Tiefe: ";
        daten += bearbzeile.at(3);
        daten += "\n";
        daten += "Pos X: ";
        daten += bearbzeile.at(4);
        daten += "\n";
        daten += "Pos Y: ";
        daten += bearbzeile.at(5);
        daten += "\n";
        daten += "Pos Z: ";
        daten += bearbzeile.at(6);
        daten += "\n";
        daten += "AFB: ";
        daten += bearbzeile.at(7);
        daten += "\n";
        daten += "Zustellmass: ";
        daten += bearbzeile.at(8);
        daten += "\n";
        daten += "Werkzeug: ";
        daten += bearbzeile.at(9);
        daten += "\n";
    }else if(bearbzeile.at(0) == BEARBART_RTA)
    {
        daten += "Rechtecktasche:\n";
        daten += "Bezugsflaeche: ";
        daten += bearbzeile.at(1);
        daten += "\n";
        daten += "Taschenleange: ";
        daten += bearbzeile.at(2);
        daten += "\n";
        daten += "Taschenbreite: ";
        daten += bearbzeile.at(3);
        daten += "\n";
        daten += "Taschentiefe: ";
        daten += bearbzeile.at(4);
        daten += "\n";
        daten += "Pos X: ";
        daten += bearbzeile.at(5);
        daten += "\n";
        daten += "Pos Y: ";
        daten += bearbzeile.at(6);
        daten += "\n";
        daten += "Pos Z: ";
        daten += bearbzeile.at(7);
        daten += "\n";
        daten += "Drehwinkel im UZS: ";
        daten += bearbzeile.at(8);
        daten += "\n";
        daten += "Eckenradius: ";
        daten += bearbzeile.at(9);
        daten += "\n";
        daten += "Ausraeumen: ";
        daten += bearbzeile.at(10);
        daten += "\n";
        daten += "AFB: ";
        daten += bearbzeile.at(11);
        daten += "\n";
        daten += "Zustellmass: ";
        daten += bearbzeile.at(12);
        daten += "\n";
        daten += "Werkzeug: ";
        daten += bearbzeile.at(13);
        daten += "\n";
    }else if(bearbzeile.at(0) == BEARBART_NUT)
    {
        daten += "Nut:\n";
        daten += "Bezugsflaeche: ";
        daten += bearbzeile.at(1);
        daten += "\n";
        daten += "Startpunkt in X: ";
        daten += bearbzeile.at(2);
        daten += "\n";
        daten += "Startpunkt in Y: ";
        daten += bearbzeile.at(3);
        daten += "\n";
        daten += "Endpunkt in X: ";
        daten += bearbzeile.at(4);
        daten += "\n";
        daten += "Endpunkt in Y: ";
        daten += bearbzeile.at(5);
        daten += "\n";
        daten += "Nuttiefe: ";
        daten += bearbzeile.at(6);
        daten += "\n";
        daten += "Nutbreite: ";
        daten += bearbzeile.at(7);
        daten += "\n";
        daten += "AFB: ";
        daten += bearbzeile.at(8);
        daten += "\n";
    }else if(bearbzeile.at(0) == BEARBART_FRAESERAUFRUF)
    {
        daten += "Aufruf Fraeser:\n";
        daten += "Bezugsflaeche: ";
        daten += bearbzeile.at(1);
        daten += "\n";
        daten += "Startpunkt in X: ";
        daten += bearbzeile.at(2);
        daten += "\n";
        daten += "Startpunkt in Y: ";
        daten += bearbzeile.at(3);
        daten += "\n";
        daten += "Startpunkt in Z: ";
        daten += bearbzeile.at(4);
        daten += "\n";
        daten += "Tiefe: ";
        daten += bearbzeile.at(5);
        daten += "\n";
        daten += "Bahnkorrektur: ";
        daten += bearbzeile.at(6);
        daten += "\n";
        daten += "Werkzeug: ";
        daten += bearbzeile.at(7);
        daten += "\n";
        daten += "AFB: ";
        daten += bearbzeile.at(8);
        daten += "\n";
    }else if(bearbzeile.at(0) == BEARBART_FRAESERGERADE)
    {
        daten += "gerade Fraesbahn:\n";
        daten += "Bezugsflaeche: ";
        daten += bearbzeile.at(1);
        daten += "\n";
        daten += "Startpunkt in X: ";
        daten += bearbzeile.at(2);
        daten += "\n";
        daten += "Startpunkt in Y: ";
        daten += bearbzeile.at(3);
        daten += "\n";
        daten += "Startpunkt Tiefe: ";
        daten += bearbzeile.at(4);
        daten += "\n";
        daten += "Endpunkt in X: ";
        daten += bearbzeile.at(5);
        daten += "\n";
        daten += "Endpunkt in Y: ";
        daten += bearbzeile.at(6);
        daten += "\n";
        daten += "Endpunkt Tiefe: ";
        daten += bearbzeile.at(7);
        daten += "\n";
        daten += "AFB: ";
        daten += bearbzeile.at(8);
        daten += "\n";
    }else if(bearbzeile.at(0) == BEARBART_FRAESERBOGEN)
    {
        daten += "gebogene Fraesbahn:\n";
        daten += "Bezugsflaeche: ";
        daten += bearbzeile.at(1);
        daten += "\n";
        daten += "Startpunkt in X: ";
        daten += bearbzeile.at(2);
        daten += "\n";
        daten += "Startpunkt in Y: ";
        daten += bearbzeile.at(3);
        daten += "\n";
        daten += "Startpunkt Tiefe: ";
        daten += bearbzeile.at(4);
        daten += "\n";
        daten += "Endpunkt in X: ";
        daten += bearbzeile.at(5);
        daten += "\n";
        daten += "Endpunkt in Y: ";
        daten += bearbzeile.at(6);
        daten += "\n";
        daten += "Endpunkt Tiefe: ";
        daten += bearbzeile.at(7);
        daten += "\n";
        daten += "Radius: ";
        daten += bearbzeile.at(8);
        daten += "\n";
        daten += "Bogenrichtung: ";
        if(bearbzeile.at(9) == "1")
        {
            daten += "Uhrzeigersinn";
        }else
        {
            daten += "Gegen-Uhrzeigersinn";
        }
        daten += "\n";
        daten += "AFB: ";
        daten += bearbzeile.at(12);
        daten += "\n";
    }
    return daten;
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
        return Kante_re;
    }else if(drewi == "270")
    {
        return Kante_vo;
    }else
    {
        return Kante_li;
    }
}
QString wstzustand::kante_hi_ganx(QString drewi)
{
    if(drewi == "90")
    {
        return Kante_vo;
    }else if(drewi == "180")
    {
        return Kante_li;
    }else if(drewi == "270")
    {
        return Kante_hi;
    }else
    {
        return Kante_re;
    }
}
QString wstzustand::kante_li_ganx(QString drewi)
{
    if(drewi == "90")
    {
        return Kante_li;
    }else if(drewi == "180")
    {
        return Kante_hi;
    }else if(drewi == "270")
    {
        return Kante_re;
    }else
    {
        return Kante_vo;
    }
}
QString wstzustand::kante_re_ganx(QString drewi)
{
    if(drewi == "90")
    {
        return Kante_re;
    }else if(drewi == "180")
    {
        return Kante_vo;
    }else if(drewi == "270")
    {
        return Kante_li;
    }else
    {
        return Kante_hi;
    }
}
void wstzustand::fmc_dateitext(int index)
{
    const double hbe_max_abst_obsei = 25;
    text_zw bearb = Bearb.at(index);
    QString drewi = Drehung.at(index);
    double tmp_l = Laenge.at(index);
    double tmp_b = Breite.at(index);
    wkz_magazin wkzmag = Wkzm.at(index);
    dubosplitten(bearb, wkzmag);

    text_zw bearb_kopie = bearb;

    QString msg;
    text_zw zeile;
    //Trennzeichen: TRENNZ_BEARB_PARAM
    QString kavo = kante_vo(drewi);//Kante vorne == Kante an X
    QString kali = kante_li(drewi);//Kante links == Kante an Y
    QString kahi = kante_hi(drewi);//Kante hinten == Kante nicht an X
    QString kare = kante_re(drewi);//Kante rechts == Kante nicht an Y

    bool ay = false;
    if(tmp_b < Schwellenwert_ay)
     {
        if(use_ay() == true)
        {
            ay = true;
        }
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
    msg += double_to_qstring(Dicke);
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
        for(uint i=0; i<bearb.count() ;i++)
        {
            text_zw zeile;
            zeile.set_text(bearb.at(i),TRENNZ_BEARB_PARAM);

            QString art = zeile.at(0);
            if(art == BEARBART_BOHR)
            {
                bohrung bo(zeile.text());

                if(bo.bezug() == WST_BEZUG_VO)
                {
                    kreuzkopf_von_vorne = true;
                }
            }else if(art == BEARBART_BOHRRASTER)
            {
                bohrraster bora(zeile.text());

                if(bora.bezug() == WST_BEZUG_VO)
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
    //Prüfen ob es Horizontale Nuten gibt:
    bool hat_horizontale_nut = false;
    for(uint i=0 ; i<bearb.count() ; i++)
    {
        zeile.set_text(bearb.at(i),TRENNZ_BEARB_PARAM);
        if(zeile.at(0) == BEARBART_NUT)
        {
            nut nu(zeile.text());
            if(nu.bezug() == WST_BEZUG_LI  ||  nu.bezug() == WST_BEZUG_RE  ||  \
               nu.bezug() == WST_BEZUG_VO  ||  nu.bezug() == WST_BEZUG_HI  )
            {
                hat_horizontale_nut = true;
                break;
            }
        }
    }
    if(hat_horizontale_nut == true)
    {
        msg += kommentar_fmc("----------------------------");
        msg += variable_fmc("BLATTDICKE", "3.70");
        msg += variable_fmc("BLATTDM", "120");
        msg += kommentar_fmc("BLATTDICKE muss WKZNL");
        msg += kommentar_fmc("aus Maschienendaten sein !!!");
        msg += kommentar_fmc("----------------------------");
    }
    //---    
    text_zw hbe_nach_drehen;
    for(uint i=0 ; i<bearb.count() ; i++)
    {
        zeile.set_text(bearb.at(i),TRENNZ_BEARB_PARAM);
        if(zeile.at(0) == BEARBART_BOHR)
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
                        if(wkzmag.ist_dubo(tnummer))
                        {
                            tiefe = -1 * bo.dm(); //Tiefe Durchgangsbohrung entspricht DM Bohrer
                        }else
                        {
                            tiefe = dicke() - bo.tiefe();
                        }
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
                    //msg += bo.dm_qstring();
                    msg += wkzmag.dm(tnummer);
                    msg += "\n";
                    msg += "GRP=";                  //Bohrgruppe
                    msg += bohrgruppe;
                    msg += "\n";

                    //Anbohrtiefe gem. Voreinstellung IMAWOP
                    //Anbohrvorschub gem. Voreinstellung IMAWOP
                    //Restbohrmaß gem. Voreinstellung IMAWOP
                    //Bohrvorschub gem. Voreinstellung IMAWOP

                    msg += "ZSM=";                  //Zustellmaß
                    msg += wkzmag.zustmasvert(tnummer);
                    msg += "\n";

                    //Drehzahl gem. Voreinstellung IMAWOP

                    msg += "MRICHT=0\n";
                    msg += "TASTEIN=-1\n";
                    msg += "BEZB=";
                    msg += "Bohrung DM";
                    //msg += bo.dm_qstring();
                    msg += wkzmag.dm(tnummer);
                    msg += " T";
                    msg += double_to_qstring(tiefe);
                    msg += "\n";
                    msg += FMC_BOHR_DM_AFB;
                    msg += "=";
                    msg += bo.afb();
                    msg += "\n";
                    msg += "\n";
                }else if(bezug != WST_BEZUG_UNSEI)
                {
                    double abst_obsei = dicke() - bo.z();
                    if(abst_obsei > hbe_max_abst_obsei)
                    {
                        hbe_nach_drehen.add_hi(bo.text());
                    }else
                    {
                        if(bezug == WST_BEZUG_LI)
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
                            //msg += bo.dm_qstring();
                            msg += wkzmag.dm(tnummer);
                            msg += "\n";
                            msg += "KETTE=0\n";
                            msg += "GRP=";           //Bohrgruppe
                            msg += bohrgruppe;
                            msg += "\n";
                            msg += "X2=-1\n";
                            msg += "X1=0\n";

                            //Anbohrtiefe gem. Voreinstellung IMAWOP
                            //Anbohrvorschub gem. Voreinstellung IMAWOP
                            //Bohrvorschub gem. Voreinstellung IMAWOP
                            //Drehzahl gem. Voreinstellung IMAWOP

                            msg += "BEZB=";
                            msg += "HBE X+ DM";
                            //msg += bo.dm_qstring();
                            msg += wkzmag.dm(tnummer);
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
                            //msg += bo.dm_qstring();
                            msg += wkzmag.dm(tnummer);
                            msg += "\n";
                            msg += "KETTE=0\n";
                            msg += "GRP=";           //Bohrgruppe
                            msg += bohrgruppe;
                            msg += "\n";
                            msg += "X2=-1\n";
                            msg += "X1=L\n";

                            //Anbohrtiefe gem. Voreinstellung IMAWOP
                            //Anbohrvorschub gem. Voreinstellung IMAWOP
                            //Bohrvorschub gem. Voreinstellung IMAWOP
                            //Drehzahl gem. Voreinstellung IMAWOP

                            msg += "BEZB=";
                            msg += "HBE X- DM";
                            //msg += bo.dm_qstring();
                            msg += wkzmag.dm(tnummer);
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
                            //msg += bo.dm_qstring();
                            msg += wkzmag.dm(tnummer);
                            msg += "\n";
                            msg += "KETTE=0\n";
                            msg += "GRP=";           //Bohrgruppe
                            msg += bohrgruppe;
                            msg += "\n";
                            msg += "Y2=-1\n";
                            msg += "Y1=0\n";

                            //Anbohrtiefe gem. Voreinstellung IMAWOP
                            //Anbohrvorschub gem. Voreinstellung IMAWOP
                            //Bohrvorschub gem. Voreinstellung IMAWOP
                            //Drehzahl gem. Voreinstellung IMAWOP

                            msg += "BEZB=";
                            msg += "HBE Y+ DM";
                            //msg += bo.dm_qstring();
                            msg += wkzmag.dm(tnummer);
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
                            //msg += bo.dm_qstring();
                            msg += wkzmag.dm(tnummer);
                            msg += "\n";
                            msg += "KETTE=0\n";
                            msg += "GRP=";           //Bohrgruppe
                            msg += bohrgruppe;
                            msg += "\n";
                            msg += "Y2=-1\n";
                            msg += "Y1=B\n";

                            //Anbohrtiefe gem. Voreinstellung IMAWOP
                            //Anbohrvorschub gem. Voreinstellung IMAWOP
                            //Bohrvorschub gem. Voreinstellung IMAWOP
                            //Drehzahl gem. Voreinstellung IMAWOP

                            msg += "BEZB=";
                            msg += "HBE Y- DM";
                            //msg += bo.dm_qstring();
                            msg += wkzmag.dm(tnummer);
                            msg += " T";
                            msg += bo.tiefe_qstring();
                            msg += "\n";
                            msg += "AFB=";
                            msg += bo.afb();
                            msg += "\n";
                            msg += "\n";
                        }
                    }
                }
            }else
            {
                //Kein Werkzeug wurde gefunden.
                //Kann Bohrung als Kreistasche gefräst werden?:
                //Ist direkt ein WKZ definiert?
                if(bo.bezug() == WST_BEZUG_OBSEI  ||  bo.bezug() == WST_BEZUG_UNSEI)
                {
                    tnummer = wkzmag.wkznummer_von_alias(bo.wkznum(), WKZ_VERT);
                }else
                {
                    tnummer = wkzmag.wkznummer_von_alias(bo.wkznum(), WKZ_HORI);
                }
                if(tnummer.isEmpty())
                {
                    tnummer = wkzmag.wkznummer(WKZ_TYP_FRAESER, bo.dm(), bo.tiefe(), Dicke, bezug);
                }                
                if(!tnummer.isEmpty())
                {
                    double zustellmas = bo.zustellmass();
                    if(zustellmas <= 0)
                    {
                        zustellmas = wkzmag.zustmasvert(tnummer).toDouble();
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
                    Fehler_kein_wkz.append(msg);
                    Exporttext.append(msg);
                    Export_moeglich.append(false);
                    return;
                }
            }
        }else if(zeile.at(0) == BEARBART_BOHRRASTER)
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
                        if(wkzmag.ist_dubo(tnummer))
                        {
                            tiefe = -1 * bora.dm(); //Tiefe Durchgangsbohrung entspricht DM Bohrer
                        }else
                        {
                            tiefe = dicke() - bora.tiefe();
                        }
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
                            //msg += bora.dm_qstring();
                            msg += wkzmag.dm(tnummer);
                            msg += " T";
                            msg += double_to_qstring(tiefe);
                            msg += "\n";
                            //---------------------------------
                            msg += FMC_LORAE_DM;        //Durchmesser
                            msg += "=";
                            //msg += bora.dm_qstring();
                            msg += wkzmag.dm(tnummer);
                            msg += "\n";
                            //---------------------------------
                            msg += FMC_LORAE_XS;        //Startpunkt in X
                            msg += "=";
                            msg += bora.x_qstring();
                            msg += "\n";
                            //---------------------------------
                            msg += FMC_LORAE_XE;        //Endpunkt in X
                            msg += "=";
                            msg += double_to_qstring(bora.x() + ((bora.anz_x()-1)*bora.raster_x())  );
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
                            msg += wkzmag.zustmasvert(tnummer);
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
                                //msg += bora.dm_qstring();
                                msg += wkzmag.dm(tnummer);
                                msg += " T";
                                msg += double_to_qstring(tiefe);
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIX_DM;
                                msg += "=";
                                //msg += bora.dm_qstring();
                                msg += wkzmag.dm(tnummer);
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
                                msg += wkzmag.zustmasvert(tnummer);
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
                            //msg += bora.dm_qstring();
                            msg += wkzmag.dm(tnummer);
                            msg += " T";
                            msg += double_to_qstring(tiefe);
                            msg += "\n";
                            //------------------------------
                            msg += FMC_BOBIX_DM;
                            msg += "=";
                            //msg += bora.dm_qstring();
                            msg += wkzmag.dm(tnummer);
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
                            msg += wkzmag.zustmasvert(tnummer);
                            msg += "\n";
                            //------------------------------
                            msg += "\n";
                        }
                    }else
                    {
                        //Bislang noch keine Lochrasttererkennung in X und Y gleichzeitig vorhanden
                        //desshalb Ausgabe an dieser Stellen nicht nötig
                    }
                }else if(bezug != WST_BEZUG_UNSEI)
                {
                    double abst_obsei = dicke() - bora.z();
                    if(abst_obsei > hbe_max_abst_obsei)
                    {
                        hbe_nach_drehen.add_hi(bora.text());
                    }else
                    {
                        if(bezug == WST_BEZUG_LI)
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
                                //msg += bora.dm_qstring();
                                msg += wkzmag.dm(tnummer);
                                msg += "\n";
                                msg += "KETTE=1\n";
                                msg += "GRP=";           //Bohrgruppe
                                msg += bohrgruppe;
                                msg += "\n";
                                msg += "X2=-1\n";
                                msg += "X1=0\n";

                                //Anbohrtiefe gem. Voreinstellung IMAWOP
                                //Anbohrvorschub gem. Voreinstellung IMAWOP
                                //Bohrvorschub gem. Voreinstellung IMAWOP
                                //Drehzahl gem. Voreinstellung IMAWOP

                                msg += "BEZB=";
                                msg += "HBE X+ DM";
                                //msg += bora.dm_qstring();
                                msg += wkzmag.dm(tnummer);
                                msg += " T";
                                msg += bora.tiefe_qstring();
                                msg += "\n";
                                msg += "AFB=";
                                msg += bora.afb();
                                msg += "\n";
                                msg += "\n";
                            }
                        }
                        else if(bezug == WST_BEZUG_RE)
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
                                //msg += bora.dm_qstring();
                                msg += wkzmag.dm(tnummer);
                                msg += "\n";
                                msg += "KETTE=1\n";
                                msg += "GRP=";           //Bohrgruppe
                                msg += bohrgruppe;
                                msg += "\n";
                                msg += "X2=-1\n";
                                msg += "X1=L\n";

                                //Anbohrtiefe gem. Voreinstellung IMAWOP
                                //Anbohrvorschub gem. Voreinstellung IMAWOP
                                //Bohrvorschub gem. Voreinstellung IMAWOP
                                //Drehzahl gem. Voreinstellung IMAWOP

                                msg += "BEZB=";
                                msg += "HBE X- DM";
                                //msg += bora.dm_qstring();
                                msg += wkzmag.dm(tnummer);
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
                                //msg += bora.dm_qstring();
                                msg += wkzmag.dm(tnummer);
                                msg += "\n";
                                msg += "KETTE=1\n";
                                msg += "GRP=";           //Bohrgruppe
                                msg += bohrgruppe;
                                msg += "\n";
                                msg += "Y2=-1\n";
                                msg += "Y1=0\n";

                                //Anbohrtiefe gem. Voreinstellung IMAWOP
                                //Anbohrvorschub gem. Voreinstellung IMAWOP
                                //Bohrvorschub gem. Voreinstellung IMAWOP
                                //Drehzahl gem. Voreinstellung IMAWOP

                                msg += "BEZB=";
                                msg += "HBE Y+ DM";
                                //msg += bora.dm_qstring();
                                msg += wkzmag.dm(tnummer);
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
                                //msg += bora.dm_qstring();
                                msg += wkzmag.dm(tnummer);
                                msg += "\n";
                                msg += "KETTE=1\n";
                                msg += "GRP=";           //Bohrgruppe
                                msg += bohrgruppe;
                                msg += "\n";
                                msg += "Y2=-1\n";
                                msg += "Y1=B\n";

                                //Anbohrtiefe gem. Voreinstellung IMAWOP
                                //Anbohrvorschub gem. Voreinstellung IMAWOP
                                //Bohrvorschub gem. Voreinstellung IMAWOP
                                //Drehzahl gem. Voreinstellung IMAWOP

                                msg += "BEZB=";
                                msg += "HBE Y- DM";
                                //msg += bora.dm_qstring();
                                msg += wkzmag.dm(tnummer);
                                msg += " T";
                                msg += bora.tiefe_qstring();
                                msg += "\n";
                                msg += "AFB=";
                                msg += bora.afb();
                                msg += "\n";
                                msg += "\n";
                            }
                        }
                    }
                }
            }else
            {
                //Sollte nicht vorkommen können, da bohrraster anhand des vorhandenen Werkzeuges ermittelt werden
            }
        }else if(zeile.at(0) == BEARBART_NUT)
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
            }else
            {
                //Mit Fehlermeldung abbrechen:
                QString msg = fehler_kein_WKZ("fmc", zeile);
                Fehler_kein_wkz.append(msg);
                Exporttext.append(msg);
                Export_moeglich.append(false);
                return;
            }
            if(nu.bezug() == WST_BEZUG_OBSEI)
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
                msg += FMC_NUT_AFB;
                msg += "=";
                msg += nu.afb();
                msg += "\n";
                msg += "\n";
            }else if(nu.bezug() != WST_BEZUG_UNSEI)
            {
                QString xs = nu.xs_qstring();
                if(xs.toDouble() == tmp_l)
                {
                    xs = "L";
                }
                QString xe = nu.xe_qstring();
                if(xe.toDouble() == tmp_l)
                {
                    xe = "L";
                }
                QString ys = nu.ys_qstring();
                if(ys.toDouble() == tmp_b)
                {
                    ys = "B";
                }
                QString ye = nu.ye_qstring();
                if(ye.toDouble() == tmp_b)
                {
                    ye = "B";
                }

                msg += kommentar_fmc("----------------------------");
                //10er-Variable
                msg += FMC_VAR10;
                msg += "\n";
                msg += FMC_VAR10_BEZ;
                msg += "=";
                msg += "Variablen hori-Nut";
                msg += "\n";
                msg += FMC_VAR10_AFB;
                msg += "=";
                msg += "1";
                msg += "\n";
                msg += FMC_VAR10_NAME1;
                msg += "=";
                msg += "POS_Z_MITE_NUT";
                msg += "\n";
                msg += FMC_VAR10_NAME2;
                msg += "=";
                msg += "NUTBREITE";
                msg += "\n";
                msg += FMC_VAR10_NAME3;
                msg += "=";
                msg += "NUTTIEFE";
                msg += "\n";
                msg += FMC_VAR10_NAME4;
                msg += "=";
                msg += "";
                msg += "\n";
                msg += FMC_VAR10_NAME5;
                msg += "=";
                msg += "";
                msg += "\n";
                msg += FMC_VAR10_NAME6;
                msg += "=";
                msg += "START_X";
                msg += "\n";
                msg += FMC_VAR10_NAME7;
                msg += "=";
                msg += "START_Y";
                msg += "\n";
                msg += FMC_VAR10_NAME8;
                msg += "=";
                msg += "END_X";
                msg += "\n";
                msg += FMC_VAR10_NAME9;
                msg += "=";
                msg += "END_Y";
                msg += "\n";
                msg += FMC_VAR10_NAME10;
                msg += "=";
                msg += "AN_AB_WERT";
                msg += "\n";

                msg += FMC_VAR10_WERT1; //POS_Z_MITE_NUT
                msg += "=";
                msg += nu.zs_qstring();
                msg += "\n";
                msg += FMC_VAR10_WERT2; //NUTBREITE
                msg += "=";
                msg += nu.breite_qstring();
                msg += "\n";
                msg += FMC_VAR10_WERT3; //NUTTIEFE
                msg += "=";
                msg += nu.tiefe_qstring();
                msg += "\n";
                msg += FMC_VAR10_WERT4;
                msg += "=";
                msg += "";
                msg += "\n";
                msg += FMC_VAR10_WERT5;
                msg += "=";
                msg += "";
                msg += "\n";
                msg += FMC_VAR10_WERT6; //START_X
                msg += "=";
                msg += xs;
                msg += "\n";
                msg += FMC_VAR10_WERT7; //START_Y
                msg += "=";
                msg += ys;
                msg += "\n";
                msg += FMC_VAR10_WERT8; //END_X
                msg += "=";
                msg += xe;
                msg += "\n";
                msg += FMC_VAR10_WERT9; //END_Y
                msg += "=";
                msg += ye;
                msg += "\n";
                msg += FMC_VAR10_WERT10; //AN_AB_WERT
                msg += "=";
                msg += "130";
                msg += "\n";

                msg += "\n";
                //---
                msg += kommentar_fmc("---");
                msg += kommentar_fmc("bis Nutbreiten max 7mm :");
                //---Aufruf Fraeser:
                msg += FMC_FKON;
                msg += "\n";
                msg += FMC_FKON_WKZ;
                msg += "=";
                msg += tnummer;
                msg += "\n";
                msg += FMC_FKON_X;
                msg += "=";
                msg += "START_X";
                msg += "\n";
                msg += FMC_FKON_Y;
                msg += "=";
                msg += "START_Y";
                msg += "\n";
                msg += FMC_FKON_Z;
                msg += "=";
                msg += "-(NUTBREITE/2)+POS_Z_MITE_NUT";
                msg += "\n";
                msg += FMC_FKON_RAD;
                msg += "=";
                msg += "0";
                msg += "\n";
                msg += FMC_FKON_KADI;
                msg += "=";
                msg += "NUTTIEFE";
                msg += "\n";
                msg += FMC_FKON_KOR;
                msg += "=";
                msg += "2";
                msg += "\n";
                msg += FMC_FKON_BEZ;
                msg += "=";
                msg += "Aufruf Fraeser (unten)";
                msg += "\n";
                msg += FMC_FKON_AFB;
                msg += "=";
                msg += "1";
                msg += "\n";
                msg += FMC_FKON_ANTYP;
                msg += "=";
                msg += "1";
                msg += "\n";
                msg += FMC_FKON_ABTYP;
                msg += "=";
                msg += "1";
                msg += "\n";
                msg += FMC_FKON_EINTYP;
                msg += "=";
                msg += "0";
                msg += "\n";
                msg += FMC_FKON_ANWEG;
                msg += "=";
                msg += "AN_AB_WERT";
                msg += "\n";
                msg += FMC_FKON_ABWEG;
                msg += "=";
                msg += "AN_AB_WERT";
                msg += "\n";
                msg += FMC_FKON_ANVO;
                msg += "=";
                msg += "3500";
                msg += "\n";
                msg += FMC_FKON_VO;
                msg += "=";
                msg += "6000";
                msg += "\n";
                msg += FMC_FKON_DREHZ;
                msg += "=";
                msg += "AUTO";
                msg += "\n";
                msg += FMC_FKON_ECKVERSCHL;
                msg += "=";
                msg += "0.05";
                msg += "\n";
                msg += FMC_FKON_WKZAKT;
                msg += "=";
                msg += "1";
                msg += "\n";
                msg += "\n";
                //---Gerade Fräsen:
                msg += FMC_FKONG;
                msg += "\n";
                msg += FMC_FKONG_XE;
                msg += "=";
                msg += "END_X";
                msg += "\n";
                msg += FMC_FKONG_YE;
                msg += "=";
                msg += "END_Y";
                msg += "\n";
                msg += FMC_FKONG_ZE;
                msg += "=";
                msg += "Z";
                msg += "\n";
                msg += FMC_FKONG_AFB;
                msg += "=";
                msg += "1";
                msg += "\n";
                msg += "EB=EBG\n";
                msg += "F=V\n";
                msg += "AGGD=AGGDREHBAR\n";
                msg += "AGGO=AGGOFFSET\n";
                msg += "AGGFWKL=AGGWKL\n";
                msg += "BEZB=Gerade\n";
                msg += "\n";
                //---Abfahren:
                msg += "[KOABFA40]\n";
                msg += "AGGD=AGGDREHBAR\n";
                msg += "AGGO=AGGOFFSET\n";
                msg += "AGGFWKL=AGGFWKL\n";
                msg += "BEZB=Abfahren\n";
                msg += "AFB=1\n";
                msg += "\n";
                //---
                //---Aufruf Fraeser:
                msg += FMC_FKON;
                msg += "\n";
                msg += FMC_FKON_WKZ;
                msg += "=";
                msg += tnummer;
                msg += "\n";
                msg += FMC_FKON_X;
                msg += "=";
                msg += "START_X";
                msg += "\n";
                msg += FMC_FKON_Y;
                msg += "=";
                msg += "START_Y";
                msg += "\n";
                msg += FMC_FKON_Z;
                msg += "=";
                msg += "NUTBREITE/2-BLATTDICKE+POS_Z_MITE_NUT";
                msg += "\n";
                msg += FMC_FKON_RAD;
                msg += "=";
                msg += "0";
                msg += "\n";
                msg += FMC_FKON_KADI;
                msg += "=";
                msg += "NUTTIEFE";
                msg += "\n";
                msg += FMC_FKON_KOR;
                msg += "=";
                msg += "2";
                msg += "\n";
                msg += FMC_FKON_BEZ;
                msg += "=";
                msg += "Aufruf Fraeser (oben)";
                msg += "\n";
                msg += FMC_FKON_AFB;
                msg += "=";
                msg += "1";
                msg += "\n";
                msg += FMC_FKON_ANTYP;
                msg += "=";
                msg += "1";
                msg += "\n";
                msg += FMC_FKON_ABTYP;
                msg += "=";
                msg += "1";
                msg += "\n";
                msg += FMC_FKON_EINTYP;
                msg += "=";
                msg += "0";
                msg += "\n";
                msg += FMC_FKON_ANWEG;
                msg += "=";
                msg += "AN_AB_WERT";
                msg += "\n";
                msg += FMC_FKON_ABWEG;
                msg += "=";
                msg += "AN_AB_WERT";
                msg += "\n";
                msg += FMC_FKON_ANVO;
                msg += "=";
                msg += "3500";
                msg += "\n";
                msg += FMC_FKON_VO;
                msg += "=";
                msg += "6000";
                msg += "\n";
                msg += FMC_FKON_DREHZ;
                msg += "=";
                msg += "AUTO";
                msg += "\n";
                msg += FMC_FKON_ECKVERSCHL;
                msg += "=";
                msg += "0.05";
                msg += "\n";
                msg += FMC_FKON_WKZAKT;
                msg += "=";
                msg += "1";
                msg += "\n";
                msg += "\n";
                //---Gerade Fräsen:
                msg += FMC_FKONG;
                msg += "\n";
                msg += FMC_FKONG_XE;
                msg += "=";
                msg += "END_X";
                msg += "\n";
                msg += FMC_FKONG_YE;
                msg += "=";
                msg += "END_Y";
                msg += "\n";
                msg += FMC_FKONG_ZE;
                msg += "=";
                msg += "Z";
                msg += "\n";
                msg += FMC_FKONG_AFB;
                msg += "=";
                msg += "1";
                msg += "\n";
                msg += "EB=EBG\n";
                msg += "F=V\n";
                msg += "AGGD=AGGDREHBAR\n";
                msg += "AGGO=AGGOFFSET\n";
                msg += "AGGFWKL=AGGWKL\n";
                msg += "BEZB=Gerade\n";
                msg += "\n";
                //---Abfahren:
                msg += "[KOABFA40]\n";
                msg += "AGGD=AGGDREHBAR\n";
                msg += "AGGO=AGGOFFSET\n";
                msg += "AGGFWKL=AGGFWKL\n";
                msg += "BEZB=Abfahren\n";
                msg += "AFB=1\n";
                msg += "\n";
                //---
                msg += kommentar_fmc("---");//--------------------------------------------------------
                msg += kommentar_fmc("bis Nutbreiten max 13mm :");
                msg += variable_fmc("AFB_AUSRAEUMEN", "(NUTBREITE>BLATTDICKE*2)?1:0");
                //---Aufruf Fraeser:
                msg += FMC_FKON;
                msg += "\n";
                msg += FMC_FKON_WKZ;
                msg += "=";
                msg += tnummer;
                msg += "\n";
                msg += FMC_FKON_X;
                msg += "=";
                msg += "START_X";
                msg += "\n";
                msg += FMC_FKON_Y;
                msg += "=";
                msg += "START_Y";
                msg += "\n";
                msg += FMC_FKON_Z;
                msg += "=";
                msg += "-(NUTBREITE/2)+POS_Z_MITE_NUT+(BLATTDICKE-0.5)";
                msg += "\n";
                msg += FMC_FKON_RAD;
                msg += "=";
                msg += "0";
                msg += "\n";
                msg += FMC_FKON_KADI;
                msg += "=";
                msg += "NUTTIEFE";
                msg += "\n";
                msg += FMC_FKON_KOR;
                msg += "=";
                msg += "2";
                msg += "\n";
                msg += FMC_FKON_BEZ;
                msg += "=";
                msg += "Aufruf Fraeser (unten2)";
                msg += "\n";
                msg += FMC_FKON_AFB;
                msg += "=";
                msg += "AFB_AUSRAEUMEN";
                msg += "\n";
                msg += FMC_FKON_ANTYP;
                msg += "=";
                msg += "1";
                msg += "\n";
                msg += FMC_FKON_ABTYP;
                msg += "=";
                msg += "1";
                msg += "\n";
                msg += FMC_FKON_EINTYP;
                msg += "=";
                msg += "0";
                msg += "\n";
                msg += FMC_FKON_ANWEG;
                msg += "=";
                msg += "AN_AB_WERT";
                msg += "\n";
                msg += FMC_FKON_ABWEG;
                msg += "=";
                msg += "AN_AB_WERT";
                msg += "\n";
                msg += FMC_FKON_ANVO;
                msg += "=";
                msg += "3500";
                msg += "\n";
                msg += FMC_FKON_VO;
                msg += "=";
                msg += "6000";
                msg += "\n";
                msg += FMC_FKON_DREHZ;
                msg += "=";
                msg += "AUTO";
                msg += "\n";
                msg += FMC_FKON_ECKVERSCHL;
                msg += "=";
                msg += "0.05";
                msg += "\n";
                msg += FMC_FKON_WKZAKT;
                msg += "=";
                msg += "1";
                msg += "\n";
                msg += "\n";
                //---Gerade Fräsen:
                msg += FMC_FKONG;
                msg += "\n";
                msg += FMC_FKONG_XE;
                msg += "=";
                msg += "END_X";
                msg += "\n";
                msg += FMC_FKONG_YE;
                msg += "=";
                msg += "END_Y";
                msg += "\n";
                msg += FMC_FKONG_ZE;
                msg += "=";
                msg += "Z";
                msg += "\n";
                msg += FMC_FKONG_AFB;
                msg += "=";
                msg += "AFB_AUSRAEUMEN";
                msg += "\n";
                msg += "EB=EBG\n";
                msg += "F=V\n";
                msg += "AGGD=AGGDREHBAR\n";
                msg += "AGGO=AGGOFFSET\n";
                msg += "AGGFWKL=AGGWKL\n";
                msg += "BEZB=Gerade\n";
                msg += "\n";
                //---Abfahren:
                msg += "[KOABFA40]\n";
                msg += "AGGD=AGGDREHBAR\n";
                msg += "AGGO=AGGOFFSET\n";
                msg += "AGGFWKL=AGGFWKL\n";
                msg += "BEZB=Abfahren\n";
                msg += "AFB=AFB_AUSRAEUMEN\n";
                msg += "\n";
                //---
                //---Aufruf Fraeser:
                msg += FMC_FKON;
                msg += "\n";
                msg += FMC_FKON_WKZ;
                msg += "=";
                msg += tnummer;
                msg += "\n";
                msg += FMC_FKON_X;
                msg += "=";
                msg += "START_X";
                msg += "\n";
                msg += FMC_FKON_Y;
                msg += "=";
                msg += "START_Y";
                msg += "\n";
                msg += FMC_FKON_Z;
                msg += "=";
                msg += "NUTBREITE/2-BLATTDICKE+POS_Z_MITE_NUT-(BLATTDICKE-0.5)";
                msg += "\n";
                msg += FMC_FKON_RAD;
                msg += "=";
                msg += "0";
                msg += "\n";
                msg += FMC_FKON_KADI;
                msg += "=";
                msg += "NUTTIEFE";
                msg += "\n";
                msg += FMC_FKON_KOR;
                msg += "=";
                msg += "2";
                msg += "\n";
                msg += FMC_FKON_BEZ;
                msg += "=";
                msg += "Aufruf Fraeser (oben2)";
                msg += "\n";
                msg += FMC_FKON_AFB;
                msg += "=";
                msg += "AFB_AUSRAEUMEN";
                msg += "\n";
                msg += FMC_FKON_ANTYP;
                msg += "=";
                msg += "1";
                msg += "\n";
                msg += FMC_FKON_ABTYP;
                msg += "=";
                msg += "1";
                msg += "\n";
                msg += FMC_FKON_EINTYP;
                msg += "=";
                msg += "0";
                msg += "\n";
                msg += FMC_FKON_ANWEG;
                msg += "=";
                msg += "AN_AB_WERT";
                msg += "\n";
                msg += FMC_FKON_ABWEG;
                msg += "=";
                msg += "AN_AB_WERT";
                msg += "\n";
                msg += FMC_FKON_ANVO;
                msg += "=";
                msg += "3500";
                msg += "\n";
                msg += FMC_FKON_VO;
                msg += "=";
                msg += "6000";
                msg += "\n";
                msg += FMC_FKON_DREHZ;
                msg += "=";
                msg += "AUTO";
                msg += "\n";
                msg += FMC_FKON_ECKVERSCHL;
                msg += "=";
                msg += "0.05";
                msg += "\n";
                msg += FMC_FKON_WKZAKT;
                msg += "=";
                msg += "1";
                msg += "\n";
                msg += "\n";
                //---Gerade Fräsen:
                msg += FMC_FKONG;
                msg += "\n";
                msg += FMC_FKONG_XE;
                msg += "=";
                msg += "END_X";
                msg += "\n";
                msg += FMC_FKONG_YE;
                msg += "=";
                msg += "END_Y";
                msg += "\n";
                msg += FMC_FKONG_ZE;
                msg += "=";
                msg += "Z";
                msg += "\n";
                msg += FMC_FKONG_AFB;
                msg += "=";
                msg += "AFB_AUSRAEUMEN";
                msg += "\n";
                msg += "EB=EBG\n";
                msg += "F=V\n";
                msg += "AGGD=AGGDREHBAR\n";
                msg += "AGGO=AGGOFFSET\n";
                msg += "AGGFWKL=AGGWKL\n";
                msg += "BEZB=Gerade\n";
                msg += "\n";
                //---Abfahren:
                msg += "[KOABFA40]\n";
                msg += "AGGD=AGGDREHBAR\n";
                msg += "AGGO=AGGOFFSET\n";
                msg += "AGGFWKL=AGGFWKL\n";
                msg += "BEZB=Abfahren\n";
                msg += "AFB=AFB_AUSRAEUMEN\n";
                msg += "\n";
                //---
                msg += kommentar_fmc("----------------------------");
            }
        }else if(zeile.at(0) == BEARBART_RTA)
        {
            rechtecktasche rt(zeile.text());

            QString tnummer;
            //Ist direkt ei WKZ definiert?
            if(rt.bezug() == WST_BEZUG_OBSEI  ||  rt.bezug() == WST_BEZUG_UNSEI)
            {
                tnummer = wkzmag.wkznummer_von_alias(rt.wkznum(), WKZ_VERT);
            }else
            {
                tnummer = wkzmag.wkznummer_von_alias(rt.wkznum(), WKZ_HORI);
            }
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
                double radius = rt.rad();
                if(rt.bezug() == WST_BEZUG_OBSEI)
                {
                    double zustellmas = rt.zustellmass();
                    if(zustellmas <= 0)
                    {
                        zustellmas = wkzmag.zustmasvert(tnummer).toDouble();
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
                }else if(rt.bezug() != WST_BEZUG_UNSEI)
                {
                    double zustellmas = rt.zustellmass();
                    if(zustellmas <= 0)
                    {
                        zustellmas = wkzmag.zustmashori(tnummer).toDouble();
                    }
                    msg += FMC_STULP;
                    msg += "\n";
                    msg += FMC_STULP_WKZ;
                    msg += "=";
                    msg += tnummer;
                    msg += "\n";
                    msg += FMC_STULP_WKZAKT;
                    msg += "=";
                    msg += "1";
                    msg += "\n";
                    msg += FMC_STULP_X;
                    msg += "=";
                    msg += rt.x_qstring();
                    msg += "\n";
                    msg += FMC_STULP_Y;
                    msg += "=";
                    msg += rt.y_qstring();
                    msg += "\n";
                    msg += FMC_STULP_Z;
                    msg += "=";
                    msg += rt.z_qstring();
                    msg += "\n";
                    msg += FMC_STULP_L;
                    msg += "=";
                    msg += rt.laenge_qstring();
                    msg += "\n";
                    msg += FMC_STULP_B;
                    msg += "=";
                    msg += rt.breite_qstring();
                    msg += "\n";
                    msg += FMC_STULP_TI;
                    msg += "=";
                    msg += rt.tiefe_qstring();
                    msg += "\n";
                    msg += FMC_STULP_RAD;
                    msg += "=";
                    msg += double_to_qstring(radius);
                    msg += "\n";
                    msg += FMC_STULP_VERSATZ;
                    msg += "=";
                    msg += "0";
                    msg += "\n";
                    msg += FMC_STULP_ZUST;
                    msg += "=";
                    msg += double_to_qstring(zustellmas);
                    msg += "\n";
                    msg += FMC_STULP_GEGENL;
                    msg += "=";
                    msg += "1";
                    msg += "\n";
                    msg += FMC_STULP_SEITE;
                    msg += "=";
                    if(rt.bezug() == WST_BEZUG_LI)
                    {
                        msg += "4";
                    }else if(rt.bezug() == WST_BEZUG_RE)
                    {
                        msg += "2";
                    }else if(rt.bezug() == WST_BEZUG_VO)
                    {
                        msg += "1";
                    }else if(rt.bezug() == WST_BEZUG_HI)
                    {
                        msg += "3";
                    }
                    msg += "\n";

                    //Eintauchvorschub gem. Voreinstellung IMAWOP
                    //Vorschub gem. Voreinstellung IMAWOP
                    //Drehzahl gem. Voreinstellung IMAWOP

                    msg += FMC_STULP_BEZ;
                    msg += "=";
                    msg += "Stulp L";
                    msg += rt.laenge_qstring();
                    msg += " B";
                    msg += rt.breite_qstring();
                    msg += " Ti";
                    msg += rt.tiefe_qstring();
                    msg += "\n";
                    msg += FMC_STULP_AFB;
                    msg += "=";
                    msg += rt.afb();
                    msg += "\n";
                    msg += "\n";
                }

            }else
            {
                //Mit Fehlermeldung abbrechen:
                QString msg = fehler_kein_WKZ("fmc", zeile);
                Fehler_kein_wkz.append(msg);
                Exporttext.append(msg);
                Export_moeglich.append(false);
                return;
            }
        }else if(zeile.at(0) == BEARBART_FRAESERAUFRUF)
        {
            fraeseraufruf fa(zeile.text());
            QString tnummer = wkzmag.wkznummer_von_alias(fa.wkznum(), WKZ_VERT);
            if(!tnummer.isEmpty())
            {
                double gesamttiefe = fa.tiefe();
                double zustellmass = wkzmag.zustmasvert(tnummer).toDouble();
                double wkzdm = wkzmag.dm(tnummer).toDouble();
                double zustelltiefe;
                if(Zust_fkon == "wkz")
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

                    //Prüfen ob Eintauchpunkt des Fräsers auf oder neben dem WST liegt:
                    punkt3d pfa;//Punkt Fräseraufruf
                    pfa.set_x(fa.x());
                    pfa.set_y(fa.y());
                    text_zw folzei;//Folgezeile
                    folzei.set_text(bearb.at(i+1),TRENNZ_BEARB_PARAM);
                    punkt3d pein;//Eintauchpunkt
                    double anweg = 50;
                    QString anweg_;
                    if(fa.anfahrweg_qstring() == FAUFRUF_ANABWEG_AUTO)
                    {
                        anweg = wkzmag.dm(tnummer).toDouble();
                        anweg_ = "2*WKZR";
                    }else
                    {
                        anweg = fa.anfahrweg();
                        anweg_ = fa.anfahrweg_qstring();
                    }
                    double abweg = 50;
                    QString abweg_;
                    if(fa.abfahrweg_qstring() == FAUFRUF_ANABWEG_AUTO)
                    {
                        abweg = wkzmag.dm(tnummer).toDouble();
                        abweg_ = "2*WKZR";
                    }else
                    {
                        abweg = fa.abfahrweg();
                        abweg_ = fa.abfahrweg_qstring();
                    }
                    if(folzei.at(0) == BEARBART_FRAESERGERADE)
                    {
                        fraesergerade fg(folzei.text());
                        strecke s;
                        s.set_stapu(pfa);
                        punkt3d ep = fg.ep();
                        ep.set_z(0);
                        s.set_endpu(ep);
                        strecke_bezugspunkt sb;
                        sb = strecke_bezugspunkt_ende;
                        s.set_laenge_2d(s.laenge2d()+anweg, sb);
                        pein = s.stapu();
                    }else if(folzei.at(0) == BEARBART_FRAESERBOGEN)
                    {
                        fraeserbogen fb(folzei.text());
                        bogen b;
                        b.set_startpunkt(pfa);
                        b.set_endpunkt(fb.ep());
                        b.set_radius(fb.rad(), fb.uzs());
                        strecke s;
                        s.set_stapu(pfa);
                        punkt3d pmibo;
                        pmibo.set_x(b.mitte().x());
                        pmibo.set_y(b.mitte().y());
                        s.set_endpu(pmibo);
                        s.drenen_um_stapu_2d(90, b.im_uzs());
                        strecke_bezugspunkt sb;
                        sb = strecke_bezugspunkt_start;
                        s.set_laenge_2d(anweg, sb);
                        pein = s.endpu();
                    }
                    bool aufwst = punkt_auf_wst(pein.x(), pein.y(), tmp_l, tmp_b, 1);
                    QString fkoneintyp;
                    if(aufwst == true)
                    {
                        fkoneintyp = "1";
                    }else
                    {
                        fkoneintyp = "-1";
                    }
                    msg += variable_fmc("FKONEINTYP", fkoneintyp);

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

                        if(aufwst == true)
                        {
                            msg += FMC_FKON_EINTYP;   //Eintauchtp
                            msg += "=FKONEINTYP";//Variable siehe oben
                            msg += "\n";
                            //msg += "=1\n";
                        }else //Anfahrweg beginnt nicht auf WST
                        {                            
                            msg += FMC_FKON_EINTYP;   //Eintauchtp
                            msg += "=FKONEINTYP";//Variable siehe oben
                            msg += "\n";
                            //msg += "=-1\n";                            
                        }
                        if(fa.anfahrtyp() == FAUFRUF_ANABTYP_NDEF)
                        {
                            msg += FMC_FKON_ANTYP;    //Anfahrtyp
                            msg += "=0\n";
                        }else if(fa.anfahrtyp() == FAUFRUF_ANABTYP_GARADE)
                        {
                            msg += FMC_FKON_ANTYP;    //Anfahrtyp
                            msg += "=0\n";
                        }else //if(fa.anfahrtyp() == FAUFRUF_ANABTYP_BOGEN)
                        {
                            msg += FMC_FKON_ANTYP;    //Anfahrtyp
                            msg += "=1\n";
                        }
                        if(fa.abfahrtyp() == FAUFRUF_ANABTYP_NDEF)
                        {
                            msg += FMC_FKON_ABTYP;    //Anfahrtyp
                            msg += "=0\n";
                        }else if(fa.abfahrtyp() == FAUFRUF_ANABTYP_GARADE)
                        {
                            msg += FMC_FKON_ABTYP;    //Anfahrtyp
                            msg += "=0\n";
                        }else //if(fa.abfahrtyp() == FAUFRUF_ANABTYP_BOGEN)
                        {
                            msg += FMC_FKON_ABTYP;    //Anfahrtyp
                            msg += "=1\n";
                        }
                        msg += FMC_FKON_ANWEG;    //Anfahrwert
                        msg += "=";
                        msg += anweg_;
                        msg += "\n";
                        msg += FMC_FKON_ABWEG;    //Abfahrwert
                        msg += "=";
                        msg += abweg_;
                        msg += "\n";

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
                        while(i+1<bearb.count())
                        {
                            zeile.set_text(bearb.at(i+1),TRENNZ_BEARB_PARAM);

                            if(zeile.at(0) == BEARBART_FRAESERGERADE)
                            {
                                i++;
                                zeile.set_text(bearb.at(i),TRENNZ_BEARB_PARAM);
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
                            }else if(zeile.at(0) == BEARBART_FRAESERBOGEN)
                            {
                                i++;
                                zeile.set_text(bearb.at(i),TRENNZ_BEARB_PARAM);
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
                Fehler_kein_wkz.append(msg);
                Exporttext.append(msg);
                Export_moeglich.append(false);
                return;
            }
        }
    }
    //---------------------------------------Bearbeitungen Unterseite:
    bool unterseite_hat_bearb = false;
    for(uint i=0 ; i<bearb.count() ; i++)
    {
        zeile.set_text(bearb.at(i),TRENNZ_BEARB_PARAM);
        if(zeile.at(1) == WST_BEZUG_UNSEI)
        {
            unterseite_hat_bearb = true;
            break;
        }
    }
    if(hbe_nach_drehen.count() > 0)
    {
        unterseite_hat_bearb = true;
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

        for(uint i=0 ; i<bearb.count() ; i++)
        {
            zeile.set_text(bearb.at(i),TRENNZ_BEARB_PARAM);
            if(zeile.at(0) == BEARBART_BOHR)
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
                            if(wkzmag.ist_dubo(tnummer))
                            {
                                tiefe = -1 * bo.dm(); //Tiefe Durchgangsbohrung entspricht DM Bohrer
                            }else
                            {
                                tiefe = dicke() - bo.tiefe();
                            }
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
                        //msg += bo.dm_qstring();
                        msg += wkzmag.dm(tnummer);
                        msg += "\n";
                        msg += "GRP=";                  //Bohrgruppe
                        msg += bohrgruppe;
                        msg += "\n";

                        //Anbohrtiefe gem. Voreinstellung IMAWOP
                        //Anbohrvorschub gem. Voreinstellung IMAWOP
                        //Restbohrmaß gem. Voreinstellung IMAWOP
                        //Bohrvorschub gem. Voreinstellung IMAWOP

                        msg += "ZSM=";                  //Zustellmaß
                        msg += wkzmag.zustmasvert(tnummer);
                        msg += "\n";

                        //Drehzahl gem. Voreinstellung IMAWOP

                        msg += "MRICHT=0\n";
                        msg += "TASTEIN=-1\n";
                        msg += "BEZB=";
                        msg += "Bohrung DM";
                        //msg += bo.dm_qstring();
                        msg += wkzmag.dm(tnummer);
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
                    //Ist direkt ei WKZ definiert?
                    if(bo.bezug() == WST_BEZUG_OBSEI  ||  bo.bezug() == WST_BEZUG_UNSEI)
                    {
                        tnummer = wkzmag.wkznummer_von_alias(bo.wkznum(), WKZ_VERT);
                    }else
                    {
                        tnummer = wkzmag.wkznummer_von_alias(bo.wkznum(), WKZ_HORI);
                    }
                    if(tnummer.isEmpty())
                    {
                        tnummer = wkzmag.wkznummer(WKZ_TYP_FRAESER, bo.dm(), bo.tiefe(), Dicke, bezug);
                    }
                    if(!tnummer.isEmpty())
                    {
                        double zustellmas = bo.zustellmass();
                        if(zustellmas <= 0)
                        {
                            zustellmas = wkzmag.zustmasvert(tnummer).toDouble();
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
                        QString msg = fehler_kein_WKZ("fmc", zeile);
                        Fehler_kein_wkz.append(msg);
                        Exporttext.append(msg);
                        Export_moeglich.append(false);
                        return;
                    }
                }
            }else if(zeile.at(0) == BEARBART_BOHRRASTER)
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
                            if(wkzmag.ist_dubo(tnummer))
                            {
                                tiefe = -1 * bora.dm(); //Tiefe Durchgangsbohrung entspricht DM Bohrer
                            }else
                            {
                                tiefe = dicke() - bora.tiefe();
                            }
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
                                //msg += bora.dm_qstring();
                                msg += wkzmag.dm(tnummer);
                                msg += " T";
                                msg += double_to_qstring(tiefe);
                                msg += "\n";
                                //---------------------------------
                                msg += FMC_LORAE_DM;        //Durchmesser
                                msg += "=";
                                //msg += bora.dm_qstring();
                                msg += wkzmag.dm(tnummer);
                                msg += "\n";
                                //---------------------------------
                                msg += FMC_LORAE_XS;        //Startpunkt in X
                                msg += "=";
                                msg += bora.x_qstring();
                                msg += "\n";
                                //---------------------------------
                                msg += FMC_LORAE_XE;        //Endpunkt in X
                                msg += "=";
                                msg += double_to_qstring(bora.x() + ((bora.anz_x()-1)*bora.raster_x())  );
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
                                msg += wkzmag.zustmasvert(tnummer);
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
                                    //msg += bora.dm_qstring();
                                    msg += wkzmag.dm(tnummer);
                                    msg += " T";
                                    msg += double_to_qstring(tiefe);
                                    msg += "\n";
                                    //------------------------------
                                    msg += FMC_BOBIX_DM;
                                    msg += "=";
                                    //msg += bora.dm_qstring();
                                    msg += wkzmag.dm(tnummer);
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
                                    msg += wkzmag.zustmasvert(tnummer);
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
                                //msg += bora.dm_qstring();
                                msg += wkzmag.dm(tnummer);
                                msg += " T";
                                msg += double_to_qstring(tiefe);
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIX_DM;
                                msg += "=";
                                //msg += bora.dm_qstring();
                                msg += wkzmag.dm(tnummer);
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
                                msg += wkzmag.zustmasvert(tnummer);
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
            }else if(zeile.at(0) == BEARBART_NUT)
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
                        Fehler_kein_wkz.append(msg);
                        Exporttext.append(msg);
                        Export_moeglich.append(false);
                        return;
                    }
                }
            }else if(zeile.at(0) == BEARBART_RTA)
            {
                rechtecktasche rt(zeile.text());
                QString tnummer;
                //Ist direkt ei WKZ definiert?
                if(rt.bezug() == WST_BEZUG_OBSEI  ||  rt.bezug() == WST_BEZUG_UNSEI)
                {
                    tnummer = wkzmag.wkznummer_von_alias(rt.wkznum(), WKZ_VERT);
                }else
                {
                    tnummer = wkzmag.wkznummer_von_alias(rt.wkznum(), WKZ_HORI);
                }
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
                //Beareitung auf die Oberseite drehen:
                rt.set_y(  tmp_b - rt.y()  );
                rt.set_drewi(  180 - rt.drewi()  );

                if(!tnummer.isEmpty())
                {
                    double zustellmas = rt.zustellmass();
                    if(zustellmas <= 0)
                    {
                        zustellmas = wkzmag.zustmasvert(tnummer).toDouble();
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
                    Fehler_kein_wkz.append(msg);
                    Exporttext.append(msg);
                    Export_moeglich.append(false);
                    return;
                }
            }else if(zeile.at(0) == BEARBART_FRAESERAUFRUF)
            {
                fraeseraufruf fa(zeile.text());
                QString tnummer = wkzmag.wkznummer_von_alias(fa.wkznum(), WKZ_VERT);
                if(!tnummer.isEmpty())
                {
                    //Beareitung auf die Oberseite drehen:
                    fa.set_y(  tmp_b - fa.y()  );

                    double gesamttiefe = fa.tiefe();
                    double zustellmass = wkzmag.zustmasvert(tnummer).toDouble();
                    double wkzdm = wkzmag.dm(tnummer).toDouble();
                    double zustelltiefe;
                    if(Zust_fkon == "wkz")
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

                        //Prüfen ob Eintauchpunkt des Fräsers auf oder neben dem WST liegt:
                        punkt3d pfa;//Punkt Fräseraufruf
                        pfa.set_x(fa.x());
                        pfa.set_y(fa.y());
                        text_zw folzei;//Folgezeile
                        folzei.set_text(bearb.at(i+1),TRENNZ_BEARB_PARAM);
                        punkt3d pein;//Eintauchpunkt
                        double anweg = 50;
                        QString anweg_;
                        if(fa.anfahrweg_qstring() == FAUFRUF_ANABWEG_AUTO)
                        {
                            anweg = wkzmag.dm(tnummer).toDouble();
                            anweg_ = "2*WKZR";
                        }else
                        {
                            anweg = fa.anfahrweg();
                            anweg_ = fa.anfahrweg_qstring();
                        }
                        double abweg = 50;
                        QString abweg_;
                        if(fa.abfahrweg_qstring() == FAUFRUF_ANABWEG_AUTO)
                        {
                            abweg = wkzmag.dm(tnummer).toDouble();
                            abweg_ = "2*WKZR";
                        }else
                        {
                            abweg = fa.abfahrweg();
                            abweg_ = fa.abfahrweg_qstring();
                        }

                        if(folzei.at(0) == BEARBART_FRAESERGERADE)
                        {
                            fraesergerade fg(folzei.text());
                            //Beareitung auf die Oberseite drehen:
                            fg.set_ys(  tmp_b - fg.ys()  );
                            fg.set_ye(  tmp_b - fg.ye()  );
                            //-------
                            strecke s;
                            s.set_stapu(pfa);
                            punkt3d ep = fg.ep();
                            ep.set_z(0);
                            s.set_endpu(ep);
                            strecke_bezugspunkt sb;
                            sb = strecke_bezugspunkt_ende;
                            s.set_laenge_2d(s.laenge2d()+anweg, sb);
                            pein = s.stapu();
                        }else if(folzei.at(0) == BEARBART_FRAESERBOGEN)
                        {
                            fraeserbogen fb(folzei.text());
                            //Beareitung auf die Oberseite drehen:
                            fb.set_ys(  tmp_b - fb.ys()  );
                            fb.set_ye(  tmp_b - fb.ye()  );
                            //---------
                            bogen b;
                            b.set_startpunkt(pfa);
                            b.set_endpunkt(fb.ep());
                            b.set_radius(fb.rad(), fb.uzs());
                            strecke s;
                            s.set_stapu(pfa);
                            punkt3d pmibo;
                            pmibo.set_x(b.mitte().x());
                            pmibo.set_y(b.mitte().y());
                            s.set_endpu(pmibo);
                            s.drenen_um_stapu_2d(90, b.im_uzs());
                            strecke_bezugspunkt sb;
                            sb = strecke_bezugspunkt_start;
                            s.set_laenge_2d(anweg, sb);
                            pein = s.endpu();
                        }
                        bool aufwst = punkt_auf_wst(pein.x(), pein.y(), tmp_l, tmp_b, 1);
                        QString fkoneintyp;
                        if(aufwst == true)
                        {
                            fkoneintyp = "1";
                        }else
                        {
                            fkoneintyp = "-1";
                        }
                        msg += variable_fmc("FKONEINTYP", fkoneintyp);

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

                            if(aufwst == true)
                            {
                                msg += FMC_FKON_EINTYP;   //Eintauchtp
                                msg += "=FKONEINTYP";//Variable siehe oben
                                msg += "\n";
                                //msg += "=1\n";
                            }else //Anfahrweg beginnt nicht auf WST
                            {
                                msg += FMC_FKON_EINTYP;   //Eintauchtp
                                msg += "=FKONEINTYP";//Variable siehe oben
                                msg += "\n";
                                //msg += "=-1\n";
                            }
                            if(fa.anfahrtyp() == FAUFRUF_ANABTYP_NDEF)
                            {
                                msg += FMC_FKON_ANTYP;    //Anfahrtyp
                                msg += "=0\n";
                            }else if(fa.anfahrtyp() == FAUFRUF_ANABTYP_GARADE)
                            {
                                msg += FMC_FKON_ANTYP;    //Anfahrtyp
                                msg += "=0\n";
                            }else //if(fa.anfahrtyp() == FAUFRUF_ANABTYP_BOGEN)
                            {
                                msg += FMC_FKON_ANTYP;    //Anfahrtyp
                                msg += "=1\n";
                            }
                            if(fa.abfahrtyp() == FAUFRUF_ANABTYP_NDEF)
                            {
                                msg += FMC_FKON_ABTYP;    //Anfahrtyp
                                msg += "=0\n";
                            }else if(fa.abfahrtyp() == FAUFRUF_ANABTYP_GARADE)
                            {
                                msg += FMC_FKON_ABTYP;    //Anfahrtyp
                                msg += "=0\n";
                            }else //if(fa.abfahrtyp() == FAUFRUF_ANABTYP_BOGEN)
                            {
                                msg += FMC_FKON_ABTYP;    //Anfahrtyp
                                msg += "=1\n";
                            }
                            msg += FMC_FKON_ANWEG;    //Anfahrwert
                            msg += "=";
                            msg += anweg_;
                            msg += "\n";
                            msg += FMC_FKON_ABWEG;    //Abfahrwert
                            msg += "=";
                            msg += abweg_;
                            msg += "\n";

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
                            while(i+1<bearb.count())
                            {
                                zeile.set_text(bearb.at(i+1),TRENNZ_BEARB_PARAM);

                                if(zeile.at(0) == BEARBART_FRAESERGERADE)
                                {
                                    i++;
                                    zeile.set_text(bearb.at(i),TRENNZ_BEARB_PARAM);
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
                                }else if(zeile.at(0) == BEARBART_FRAESERBOGEN)
                                {
                                    i++;
                                    zeile.set_text(bearb.at(i),TRENNZ_BEARB_PARAM);
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
                    Fehler_kein_wkz.append(msg);
                    Exporttext.append(msg);
                    Export_moeglich.append(false);
                    return;
                }
            }
        }
        for(uint i=0 ; i<hbe_nach_drehen.count() ; i++)
        {
            zeile.set_text(hbe_nach_drehen.at(i),TRENNZ_BEARB_PARAM);
            if(zeile.at(0) == BEARBART_BOHR)
            {
                bohrung bo(hbe_nach_drehen.at(i));
                if(bo.z() < hbe_max_abst_obsei)
                {
                    QString bezug = bo.bezug();
                    //Bohrung um b/2 drehen:
                    bo.set_z(dicke()-bo.z());
                    if(bezug == WST_BEZUG_LI)
                    {
                        bo.set_y(tmp_b-bo.y());
                    }else if(bezug == WST_BEZUG_RE)
                    {
                        bo.set_y(tmp_b-bo.y());
                    }else if(bezug == WST_BEZUG_VO)
                    {
                        bo.set_bezug(WST_BEZUG_HI);
                    }else if(bezug == WST_BEZUG_HI)
                    {
                        bo.set_bezug(WST_BEZUG_VO);
                    }
                    //Bohrung in fmc-Datei schreibe:
                    bezug = bo.bezug();
                    QString tnummer = wkzmag.wkznummer(WKZ_TYP_BOHRER, bo.dm(), bo.tiefe(), Dicke, bezug);
                    if(!tnummer.isEmpty())
                    {
                        //Werkzeug wurde gefunden, Bohrung kann gebohrt werden:
                        QString bohrgruppe = "2";
                        if(bezug == WST_BEZUG_LI)
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
                            //msg += bo.dm_qstring();
                            msg += wkzmag.dm(tnummer);
                            msg += "\n";
                            msg += "KETTE=0\n";
                            msg += "GRP=";           //Bohrgruppe
                            msg += bohrgruppe;
                            msg += "\n";
                            msg += "X2=-1\n";
                            msg += "X1=0\n";

                            //Anbohrtiefe gem. Voreinstellung IMAWOP
                            //Anbohrvorschub gem. Voreinstellung IMAWOP
                            //Bohrvorschub gem. Voreinstellung IMAWOP
                            //Drehzahl gem. Voreinstellung IMAWOP

                            msg += "BEZB=";
                            msg += "HBE X+ DM";
                            //msg += bo.dm_qstring();
                            msg += wkzmag.dm(tnummer);
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
                            //msg += bo.dm_qstring();
                            msg += wkzmag.dm(tnummer);
                            msg += "\n";
                            msg += "KETTE=0\n";
                            msg += "GRP=";           //Bohrgruppe
                            msg += bohrgruppe;
                            msg += "\n";
                            msg += "X2=-1\n";
                            msg += "X1=L\n";

                            //Anbohrtiefe gem. Voreinstellung IMAWOP
                            //Anbohrvorschub gem. Voreinstellung IMAWOP
                            //Bohrvorschub gem. Voreinstellung IMAWOP
                            //Drehzahl gem. Voreinstellung IMAWOP

                            msg += "BEZB=";
                            msg += "HBE X- DM";
                            //msg += bo.dm_qstring();
                            msg += wkzmag.dm(tnummer);
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
                            //msg += bo.dm_qstring();
                            msg += wkzmag.dm(tnummer);
                            msg += "\n";
                            msg += "KETTE=0\n";
                            msg += "GRP=";           //Bohrgruppe
                            msg += bohrgruppe;
                            msg += "\n";
                            msg += "Y2=-1\n";
                            msg += "Y1=0\n";

                            //Anbohrtiefe gem. Voreinstellung IMAWOP
                            //Anbohrvorschub gem. Voreinstellung IMAWOP
                            //Bohrvorschub gem. Voreinstellung IMAWOP
                            //Drehzahl gem. Voreinstellung IMAWOP

                            msg += "BEZB=";
                            msg += "HBE Y+ DM";
                            //msg += bo.dm_qstring();
                            msg += wkzmag.dm(tnummer);
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
                            //msg += bo.dm_qstring();
                            msg += wkzmag.dm(tnummer);
                            msg += "\n";
                            msg += "KETTE=0\n";
                            msg += "GRP=";           //Bohrgruppe
                            msg += bohrgruppe;
                            msg += "\n";
                            msg += "Y2=-1\n";
                            msg += "Y1=B\n";

                            //Anbohrtiefe gem. Voreinstellung IMAWOP
                            //Anbohrvorschub gem. Voreinstellung IMAWOP
                            //Bohrvorschub gem. Voreinstellung IMAWOP
                            //Drehzahl gem. Voreinstellung IMAWOP

                            msg += "BEZB=";
                            msg += "HBE Y- DM";
                            //msg += bo.dm_qstring();
                            msg += wkzmag.dm(tnummer);
                            msg += " T";
                            msg += bo.tiefe_qstring();
                            msg += "\n";
                            msg += "AFB=";
                            msg += bo.afb();
                            msg += "\n";
                            msg += "\n";
                        }
                    }else //kann theoretisch nie erreicht werden, da hbe_nach_drehen erst gefüllt wird
                    {     //nachdem ein wkz gefunden wurde
                          //zur Sicherheit aber trotzdem hier noch einmal:
                        //Mit Fehlermeldung abbrechen:
                        QString msg = fehler_kein_WKZ("fmc", zeile);
                        Fehler_kein_wkz.append(msg);
                        Exporttext.append(msg);
                        Export_moeglich.append(false);
                        return;
                    }
                }else
                {
                    msg += kommentar_fmc("--------------------");
                    msg += kommentar_fmc("HBE-Export nicht möglich");
                    msg += kommentar_fmc("Z-Pos im Kollisionsbereich");
                    msg += kommentar_fmc(bo.text());
                    msg += kommentar_fmc("--------------------");
                }
            }else if(zeile.at(0) == BEARBART_BOHRRASTER)
            {
                bohrraster bora(hbe_nach_drehen.at(i));
                if(bora.z() < hbe_max_abst_obsei)
                {
                    QString bezug = bora.bezug();
                    //Bohrungen um b/2 drehen:
                    bora.set_z(dicke()-bora.z());
                    if(bezug == WST_BEZUG_LI)
                    {
                        bora.set_y(tmp_b-bora.y());
                        bora.set_raster_y(bora.raster_y() * -1);
                    }else if(bezug == WST_BEZUG_RE)
                    {
                        bora.set_y(tmp_b-bora.y());
                        bora.set_raster_y(bora.raster_y() * -1);
                    }else if(bezug == WST_BEZUG_VO)
                    {
                        bora.set_bezug(WST_BEZUG_HI);
                    }else if(bezug == WST_BEZUG_HI)
                    {
                        bora.set_bezug(WST_BEZUG_VO);
                    }
                    //Bohrung in fmc-Datei schreibe:
                    bezug = bora.bezug();
                    QString tnummer = wkzmag.wkznummer(WKZ_TYP_BOHRER, bora.dm(), bora.tiefe(), Dicke, bezug);
                    if(!tnummer.isEmpty())
                    {
                        //Werkzeug wurde gefunden, Bohrung kann gebohrt werden:
                        QString bohrgruppe = "2";
                        if(bezug == WST_BEZUG_LI)
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
                                //msg += bora.dm_qstring();
                                msg += wkzmag.dm(tnummer);
                                msg += "\n";
                                msg += "KETTE=1\n";
                                msg += "GRP=";           //Bohrgruppe
                                msg += bohrgruppe;
                                msg += "\n";
                                msg += "X2=-1\n";
                                msg += "X1=0\n";

                                //Anbohrtiefe gem. Voreinstellung IMAWOP
                                //Anbohrvorschub gem. Voreinstellung IMAWOP
                                //Bohrvorschub gem. Voreinstellung IMAWOP
                                //Drehzahl gem. Voreinstellung IMAWOP

                                msg += "BEZB=";
                                msg += "HBE X+ DM";
                                //msg += bora.dm_qstring();
                                msg += wkzmag.dm(tnummer);
                                msg += " T";
                                msg += bora.tiefe_qstring();
                                msg += "\n";
                                msg += "AFB=";
                                msg += bora.afb();
                                msg += "\n";
                                msg += "\n";
                            }
                        }
                        else if(bezug == WST_BEZUG_RE)
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
                                //msg += bora.dm_qstring();
                                msg += wkzmag.dm(tnummer);
                                msg += "\n";
                                msg += "KETTE=1\n";
                                msg += "GRP=";           //Bohrgruppe
                                msg += bohrgruppe;
                                msg += "\n";
                                msg += "X2=-1\n";
                                msg += "X1=L\n";

                                //Anbohrtiefe gem. Voreinstellung IMAWOP
                                //Anbohrvorschub gem. Voreinstellung IMAWOP
                                //Bohrvorschub gem. Voreinstellung IMAWOP
                                //Drehzahl gem. Voreinstellung IMAWOP

                                msg += "BEZB=";
                                msg += "HBE X- DM";
                                //msg += bora.dm_qstring();
                                msg += wkzmag.dm(tnummer);
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
                                //msg += bora.dm_qstring();
                                msg += wkzmag.dm(tnummer);
                                msg += "\n";
                                msg += "KETTE=1\n";
                                msg += "GRP=";           //Bohrgruppe
                                msg += bohrgruppe;
                                msg += "\n";
                                msg += "Y2=-1\n";
                                msg += "Y1=0\n";

                                //Anbohrtiefe gem. Voreinstellung IMAWOP
                                //Anbohrvorschub gem. Voreinstellung IMAWOP
                                //Bohrvorschub gem. Voreinstellung IMAWOP
                                //Drehzahl gem. Voreinstellung IMAWOP

                                msg += "BEZB=";
                                msg += "HBE Y+ DM";
                                //msg += bora.dm_qstring();
                                msg += wkzmag.dm(tnummer);
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
                                //msg += bora.dm_qstring();
                                msg += wkzmag.dm(tnummer);
                                msg += "\n";
                                msg += "KETTE=1\n";
                                msg += "GRP=";           //Bohrgruppe
                                msg += bohrgruppe;
                                msg += "\n";
                                msg += "Y2=-1\n";
                                msg += "Y1=B\n";

                                //Anbohrtiefe gem. Voreinstellung IMAWOP
                                //Anbohrvorschub gem. Voreinstellung IMAWOP
                                //Bohrvorschub gem. Voreinstellung IMAWOP
                                //Drehzahl gem. Voreinstellung IMAWOP

                                msg += "BEZB=";
                                msg += "HBE Y- DM";
                                //msg += bora.dm_qstring();
                                msg += wkzmag.dm(tnummer);
                                msg += " T";
                                msg += bora.tiefe_qstring();
                                msg += "\n";
                                msg += "AFB=";
                                msg += bora.afb();
                                msg += "\n";
                                msg += "\n";
                            }
                        }
                    }
                }else
                {
                    msg += kommentar_fmc("--------------------");
                    msg += kommentar_fmc("HBE-Export nicht möglich");
                    msg += kommentar_fmc("Z-Pos im Kollisionsbereich");
                    msg += kommentar_fmc(bora.text());
                    msg += kommentar_fmc("--------------------");
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

    Fehler_kein_wkz.append("");
    Exporttext.append(msg);
    Export_moeglich.append(true);
}
void wstzustand::eigen_dateitext(int index)
{
    text_zw bearb = Bearb.at(index);
    QString drewi = Drehung.at(index);
    double tmp_l = Laenge.at(index);
    double tmp_b = Breite.at(index);
    wkz_magazin wkzmag = Wkzm.at(index);
    dubosplitten(bearb, wkzmag);

    QString msg;

    //Programmkopf:
    msg += Name;
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
    msg += kante_vo(drewi);
    msg += "\"\n";
    msg += "Kante hinten: \t\"";
    msg += kante_hi(drewi);
    msg += "\"\n";
    msg += "Kante links: \t\"";
    msg += kante_li(drewi);
    msg += "\"\n";
    msg += "Kante rechts: \t\"";
    msg += kante_re(drewi);
    msg += "\"\n";
    msg += "---------------";
    msg += "\n";

    msg += bearb.text();

    Fehler_kein_wkz.append("");
    Exporttext.append(msg);
    Export_moeglich.append(true);
}

void wstzustand::cix_dateitext(int index)
{
    text_zw bearb = Bearb.at(index);
    QString drewi = Drehung.at(index);
    double tmp_l = Laenge.at(index);
    double tmp_b = Breite.at(index);
    wkz_magazin wkzmag = Wkzm.at(index);
    dubosplitten(bearb, wkzmag);

    QString msg;
    cix_index id;
    cix_index_geo id_g;
    int min_kta_dm_ausraeumen_false = 200; //Durchmesser ab dem Kreistaschen nicht ausgeräumt werden

    //Version:
    msg += "BEGIN ID CID3";
    msg += "\n\t";
    msg += "REL= 5.0";
    msg += "\n";
    msg += "END ID";
    msg += "\n";
    msg += "\n";

    //Programmkopf:
    msg += "BEGIN MAINDATA";
    msg += "\n\t";
    msg += CIX_WST_L;
    msg += " = ";
    msg += double_to_qstring(tmp_l);
    msg += "\n\t";
    msg += CIX_WST_B;
    msg += " = ";
    msg += double_to_qstring(tmp_b);
    msg += "\n\t";
    msg += CIX_WST_D;
    msg += " = ";
    msg += dicke_qstring();
    msg += "\n\t";
    msg += CIX_WST_NULLPUNKTLISTE;
    msg += " = ";
    msg += "\"1\""; //nur 1 Nullpunkt
    msg += "\n\t";
    msg += CIX_WST_SPIEGELBAR;
    msg += " = ";
    msg += "0";
    msg += "\n\t";
    msg += CIX_WST_WKZ_OPTI;
    msg += " = ";
    msg += "0";     //aktiviert
    msg += "\n\t";
    msg += CIX_WST_WKZ_BESTUECKUNG;
    msg += " = ";
    msg += "\"\"";
    msg += "\n\t";
    msg += CIX_WST_BENUTZERDATEN;
    msg += " =";
    msg += "$B$KBsExportToNcRoverNET.XncExtraPanelData$V\"\"";
    msg += "\n\t";
    msg += CIX_WST_MASSEINHEIT;
    msg += " = ";
    msg += "1.000000";  //mm
    msg += "\n\t";
    msg += CIX_WST_BEARB_REFKANTENABST_X;
    msg += " = ";
    msg += "0";
    msg += "\n\t";
    msg += CIX_WST_BEARB_REFKANTENABST_Y;
    msg += " = ";
    msg += "0";
    msg += "\n\t";
    msg += CIX_WST_SCHABLONENHOEHE;
    msg += " = ";
    msg += "0";
    msg += "\n\t";
    msg += CIX_WST_FREIGABE_AX_AY;
    msg += " = ";
    msg += "0";
    msg += "\n\t";
    msg += CIX_WST_EINZIGER_NULLPUNKT;
    msg += " = ";
    msg += "0";
    msg += "\n\t";
    msg += CIX_WST_MATERIAL;
    msg += " = ";
    msg += "\"Spanplatte\"";
    msg += "\n\t";
    msg += "PUTLST = ";             //???
    msg += "\"\"";
    msg += "\n\t";
    msg += CIX_WST_BEARB_ENTGEGENGESETZT,
    msg += " = ";
    msg += "0";
    msg += "\n\t";
    msg += CIX_WST_SPANNER_UNNICLAMP;
    msg += " = ";
    msg += "0";
    msg += "\n\t";
    msg += CIX_WST_KOLLISIONSKONTROLLE_TISCH;
    msg += " = ";
    msg += "0";
    msg += "\n\t";
    msg += CIX_WST_AUFSPANNZONE;
    msg += " = ";
    msg += "0";
    msg += "\n\t";
    msg += CIX_WST_WKZ_DM_QUELLE;
    msg += " = ";
    msg += "0";
    msg += "\n\t";
    msg += "CALCEDTH = ";           //???
    msg += "0";
    msg += "\n\t";
    msg += CIX_WST_ETTIKETTENDRUCKER;
    msg += " = ";
    msg += "0";//nein
    msg += "\n\t";
    msg += CIX_WST_AUSWURFSPERRE;
    msg += " = ";
    msg += "0";
    msg += "\n\t";
    msg += "LOADEDGEOPT = ";        //???
    msg += "0";
    msg += "\n\t";
    msg += "ITLTYPE = ";            //???
    msg += "0";
    msg += "\n\t";
    msg += CIX_WST_SAUGER_OPTIMIEREN;
    msg += " = ";
    msg += "1";
    msg += "\n\t";
    msg += "FLIPEND = ";            //???
    msg += "0";
    msg += "\n";
    msg += "END MAINDATA";
    msg += "\n";
    msg += "\n";

    //Bearbeitungen:

    for(uint i=0 ; i<bearb.count() ; i++)
    {
        text_zw zeile;
        zeile.set_text(bearb.at(i),TRENNZ_BEARB_PARAM);
        if(zeile.at(0) == BEARBART_BOHR)
        {
            bohrung bo(zeile.text());
            QString bezug = bo.bezug();
            QString tnummer = wkzmag.wkznummer(WKZ_TYP_BOHRER, bo.dm(), bo.tiefe(), Dicke, bezug);
            QString bohrerdm = wkzmag.dm(tnummer);
            if(!tnummer.isEmpty())
            {
                //Werkzeug wurde gefunden, Bohrung kann gebohrt werden:
                msg += cix_bohrung(bo, id.index_QString(), bohrerdm);
            }else
            {
                //Kein Werkzeug wurde gefunden.
                //Kann Bohrung als Kreistasche gefräst werden?:
                //Ist direkt ein WKZ definiert?
                if(bo.bezug() == WST_BEZUG_OBSEI  ||  bo.bezug() == WST_BEZUG_UNSEI)
                {
                    tnummer = wkzmag.wkznummer_von_alias(bo.wkznum(), WKZ_VERT);
                }else
                {
                    tnummer = wkzmag.wkznummer_von_alias(bo.wkznum(), WKZ_HORI);
                }
                if(tnummer.isEmpty())
                {
                    tnummer = wkzmag.wkznummer(WKZ_TYP_FRAESER, bo.dm(), bo.tiefe(), Dicke, bezug);
                }
                if(!tnummer.isEmpty())
                {
                    double zustellmas = bo.zustellmass();
                    if(zustellmas <= 0)
                    {
                        zustellmas = wkzmag.zustmasvert(tnummer).toDouble();
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
                    //Kreistasche fräsen:
                    QString geo_id = "Kreis ";
                    geo_id += id_g.index_QString();
                    msg += cix_kreis(bo, geo_id);
                    msg += cix_ende_poly(id.index_QString());
                    if(ausraeumen == true)
                    {
                        msg += cix_tasche(bo, tnummer, geo_id, bo.dm());
                    }else
                    {
                        msg += cix_fkon(bo, geo_id, tnummer);
                        msg += cix_ende_poly(id.index_QString());
                    }
                }else
                {
                    //Mit Fehlermeldung abbrechen:
                    QString msg = fehler_kein_WKZ("fmc", zeile);
                    Fehler_kein_wkz.append(msg);
                    Exporttext.append(msg);
                    Export_moeglich.append(false);
                    return;
                }
            }
        }else if(zeile.at(0) == BEARBART_NUT)
        {
            nut nu(zeile.text());
            QString bezug = nu.bezug();
            QString tnummer = wkzmag.wkznummer(WKZ_TYP_SAEGE, 0, nu.tiefe(), Dicke, bezug);
            if(!tnummer.isEmpty())
            {
                msg += cix_nut(nu, id.index_QString(), tnummer);
            }else
            {
                //Mit Fehlermeldung abbrechen:
                QString msg = fehler_kein_WKZ("cix", zeile);
                Fehler_kein_wkz.append(msg);
                Exporttext.append(msg);
                Export_moeglich.append(false);
                return;
            }
        }else if(zeile.at(0) == BEARBART_FRAESERAUFRUF)
        {
            fraeseraufruf fa(zeile.text());
            //Geometrie einfügen:
            QString geo_id = "Konturzug ";
            geo_id += id_g.index_QString();

            msg += cix_beginn_poly(fa, geo_id);
            i++;
            for(uint ii=i ; ii<bearb.count() ; ii++)
            {
                zeile.set_text(bearb.at(ii),TRENNZ_BEARB_PARAM);
                if(zeile.at(0) == BEARBART_FRAESERGERADE)
                {
                    fraesergerade fg(zeile.text());
                    msg += cix_linie_ep(fg, id.index_QString());
                }else if(zeile.at(0) == BEARBART_FRAESERBOGEN)
                {
                    fraeserbogen fb(zeile.text());
                    msg += cix_bogen_ep_mipu(fb, id.index_QString());
                }else
                {                    
                    break;
                }
            }
            msg += cix_ende_poly(id.index_QString());
            //Fräsbearbeitung einfügen:
            msg += cix_fkon(fa, geo_id);
            msg += cix_ende_poly(id.index_QString());
        }else if(zeile.at(0) == BEARBART_RTA)
        {
            rechtecktasche rt(zeile.text());

            QString tnummer;
            //Ist direkt ei WKZ definiert?
            if(rt.bezug() == WST_BEZUG_OBSEI  ||  rt.bezug() == WST_BEZUG_UNSEI)
            {
                tnummer = wkzmag.wkznummer_von_alias(rt.wkznum(), WKZ_VERT);
            }else
            {
                tnummer = wkzmag.wkznummer_von_alias(rt.wkznum(), WKZ_HORI);
            }
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
                double zustellmas = rt.zustellmass();
                if(zustellmas <= 0)
                {
                    zustellmas = wkzmag.zustmasvert(tnummer).toDouble();
                }
                //Geometrie einfügen:
                QString geo_id = "Rechteck ";
                geo_id += id_g.index_QString();
                msg += cix_rechteck(rt, geo_id);
                //Fräsbearbeitung einfügen:
                if(rt.ausraeumen() == true)
                {
                    msg += cix_tasche(rt, tnummer, geo_id);
                }else
                {
                    msg += cix_fkon(rt, geo_id, tnummer);
                    msg += cix_ende_poly(id.index_QString());
                }
            }else
            {
                //Mit Fehlermeldung abbrechen:
                QString msg = fehler_kein_WKZ("cix", zeile);
                Fehler_kein_wkz.append(msg);
                Exporttext.append(msg);
                Export_moeglich.append(false);
                return;
            }
        }
    }

    Fehler_kein_wkz.append("");
    Exporttext.append(msg);
    Export_moeglich.append(true);
}
QString wstzustand::cix_makroparam(QString name, QString wert, bool als_text)
{
    QString ret;
    ret  = "\t";
    ret += "PARAM,NAME=";
    ret += name;
    ret += ",VALUE=";
    if(als_text)
    {
        ret += "\"";
    }
    ret += wert;
    if(als_text)
    {
        ret += "\"";
    }
    ret += "\n";
    return ret;
}
QString wstzustand::cix_bohrung(bohrung bo, QString id, QString bohrerdm)
{
    QString ret;
    ret  = "BEGIN MACRO";
    ret += "\n";
    ret += "\t";    
    if(bo.bezug() == WST_BEZUG_OBSEI)
    {
        ret += "NAME=BV";
        ret += "\n";
        ret += cix_makroparam(CIX_BO_LAYER,"BV",true);
        ret += cix_makroparam(CIX_SEITE,CIX_SEITE_OBSEI,false);
        ret += cix_makroparam(CIX_BEZUG,CIX_BEZUG_UL,true);
        ret += cix_makroparam(CIX_BO_X,bo.x_qstring(),false);
        ret += cix_makroparam(CIX_BO_Y,bo.y_qstring(),false);
    }else if(bo.bezug() == WST_BEZUG_UNSEI)
    {
        ret += "NAME=BV";
        ret += "\n";
        ret += cix_makroparam(CIX_BO_LAYER,"BV",true);
        ret += cix_makroparam(CIX_SEITE,CIX_SEITE_UNSEI,false);
        ret += cix_makroparam(CIX_BEZUG,CIX_BEZUG_OR,true);
        ret += cix_makroparam(CIX_BO_X,bo.x_qstring(),false);
        ret += cix_makroparam(CIX_BO_Y,bo.y_qstring(),false);
    }else if(bo.bezug() == WST_BEZUG_LI)
    {
        ret += "NAME=BH";
        ret += "\n";
        ret += cix_makroparam(CIX_SEITE,CIX_SEITE_LI,false);
        ret += cix_makroparam(CIX_BEZUG,CIX_BEZUG_OR,true);
        ret += cix_makroparam(CIX_BO_X,bo.y_qstring(),false);
        ret += cix_makroparam(CIX_BO_Y,bo.z_qstring(),false);
    }else if(bo.bezug() == WST_BEZUG_RE)
    {
        ret += "NAME=BH";
        ret += "\n";
        ret += cix_makroparam(CIX_BO_LAYER,"BH",true);
        ret += cix_makroparam(CIX_SEITE,CIX_SEITE_RE,false);
        ret += cix_makroparam(CIX_BEZUG,CIX_BEZUG_UL,true);
        ret += cix_makroparam(CIX_BO_X,bo.y_qstring(),false);
        ret += cix_makroparam(CIX_BO_Y,bo.z_qstring(),false);
    }else if(bo.bezug() == WST_BEZUG_VO)
    {
        ret += "NAME=BH";
        ret += "\n";
        ret += cix_makroparam(CIX_BO_LAYER,"BH",true);
        ret += cix_makroparam(CIX_SEITE,CIX_SEITE_VO,false);
        ret += cix_makroparam(CIX_BEZUG,CIX_BEZUG_UL,true);
        ret += cix_makroparam(CIX_BO_X,bo.x_qstring(),false);
        ret += cix_makroparam(CIX_BO_Y,bo.z_qstring(),false);
    }else if(bo.bezug() == WST_BEZUG_HI)
    {
        ret += "NAME=BH";
        ret += "\n";
        ret += cix_makroparam(CIX_BO_LAYER,"BH",true);
        ret += cix_makroparam(CIX_SEITE,CIX_SEITE_HI,false);
        ret += cix_makroparam(CIX_BEZUG,CIX_BEZUG_OR,true);
        ret += cix_makroparam(CIX_BO_X,bo.x_qstring(),false);
        ret += cix_makroparam(CIX_BO_Y,bo.z_qstring(),false);
    }

    ret += cix_makroparam(CIX_BO_Z,"0",false);
    ret += cix_makroparam(CIX_BO_BOTI,bo.tiefe_qstring(),false);
    ret += cix_makroparam(CIX_BO_DM,bohrerdm,false);//Export-DM des Bohrers, nicht DM der Bohrung!!
    ret += cix_makroparam(CIX_BEARB_DURCHGEHEND,"NO",false);
    ret += cix_makroparam(CIX_WDH_TYP,CIX_WDH_TYP_KEIN,false);
    ret += cix_makroparam(CIX_WDH_ABST_X,"32",false);
    ret += cix_makroparam(CIX_WDH_ABST_Y,"32",false);
    ret += cix_makroparam(CIX_WDH_RAD,"32",false);
    ret += cix_makroparam(CIX_WDH_STARTWINKEL,"0",false);
    ret += cix_makroparam(CIX_WDH_WINKEL,"45",false);
    ret += cix_makroparam(CIX_WDH_ANZAHL,"0",false);
    ret += cix_makroparam(CIX_BEARB_OPTIMIEREN,"YES",false);
    ret += cix_makroparam(CIX_WKZ_NEIGUNG,"0",false);
    ret += cix_makroparam(CIX_WKZ_DREHWI,"0",false);
    ret += cix_makroparam(CIX_WKZ_DREHTYP,CIX_WKZ_DREHTYP_KEIN,false);
    ret += cix_makroparam(CIX_WDH_DREHZENTRUM_X,"0",false);
    ret += cix_makroparam(CIX_WDH_DREHZENTRUM_Y,"0",false);
    ret += cix_makroparam(CIX_WDH_GERADENWINKEL,"0",false);
    ret += cix_makroparam(CIX_WDH_ABST,"0",false);
    ret += cix_makroparam(CIX_BEZUG_SIABST,CIX_BEZUG_SIABST_BEARBGRUND,false);
    ret += cix_makroparam(CIX_BEARB_ID,id,true);
    ret += cix_makroparam(CIX_WKZ,"",true);
    ret += cix_makroparam(CIX_WKZART,CIX_WKZART_BO_STD,false);
    ret += cix_makroparam(CIX_WKZGRUPPE, CIX_WKZGRUPPE_BOHRER,false);
    ret += cix_makroparam(CIX_DREHZAHL,"0",false);
    ret += cix_makroparam(CIX_SPEED_ANAB,"0",false);
    ret += cix_makroparam(CIX_SPEED,"0",false);
    ret += cix_makroparam(CIX_WKZSPINDEL, CIX_WKZSPINDEL_AUTO,true);
    ret += cix_makroparam(CIX_BO_REBOMA,"0",false);
    ret += cix_makroparam(CIX_DREHZ_LETZTE_ZUST,"0",false);
    ret += cix_makroparam(CIX_ABBLASEN,"NO",false);
    ret += cix_makroparam(CIX_HAUBENPOS,CIX_HAUBENPOS_AUTO,false);
    ret += cix_makroparam(CIX_KENNCODE_ARBEITSZENTRUM_MASCHINE, "",true);
    ret += cix_makroparam(CIX_KENNCODE_AGGREGAT, "",true);
    ret += cix_makroparam(CIX_BO_PRESSVORRICHTUNG_AKTV,"NO",false);

    ret += cix_makroparam("ISO","",true);               //ISO-Anweisung / Werkstückabtastung
    ret += cix_makroparam("AP","NO",false);             //hängt mit einer Dialogeinstellung für HBEs zusammen
                            // 0 = NO; linear
                            // 1 = YES; kreisförmig
    ret += cix_makroparam("ER","YES",false);            //gibt die erste Bohrung ER als Anfangsbohrung der Wiederholung frei
    ret += cix_makroparam("MD","NO",false);             //aktiviert die Erstellung der Bohrung auf halber Werkstückstärke
                            // 0 = “NO”
                            // 1 = “YES”
    ret += cix_makroparam("COW","NO",false);            //nur für die Maschine “Skipper”
    ret += cix_makroparam("A21","0",false);             //Winkel Aggr21
    ret += cix_makroparam("VTR","0",false);             //Anzahl der Durchgänge, die sich auf die Tiefe der programmierten Bearbeitung auswirken
    ret += cix_makroparam("S21","-1",false);            //Winkel Aggr21
    ret += cix_makroparam("MAC","",true);               //? evtl Maschinenzuweisung bei mehreren Maschinen
    ret += cix_makroparam("AZS","0",false);             //Sicherheitswert entlang der Z-Achse, der dann zum Tragen kommt, wenn schräge
                            //Bearbeitungen z.B. mit Hilfe der Tilting Achse durchgeführt werden. Lässt man
                            //den Wert auf 0, verwendet das System die im Feld Sicherheit in der Karte Bearbeitungen des
                            //Setups  angegebene Angabe.
    ret += cix_makroparam("EA21","NO",false);           //aktiviert die Verwendung der Parameter A21 und S21
                            // 0 = “NO”
                            // 1 = “YES”

    ret += "END MACRO";
    ret += "\n";
    ret += "\n";
    return ret;
}
QString wstzustand::cix_nut(nut nu, QString id, QString wkz)
{
    QString ret;
    ret  = "BEGIN MACRO";
    ret += "\n";
    ret += "\t";
    if(nu.bezug() == WST_BEZUG_OBSEI)
    {
        ret += "NAME=CUT_G";
        ret += "\n";
        ret += cix_makroparam(CIX_NUT_LAYER,"CUT_G",true);
        ret += cix_makroparam(CIX_SEITE,CIX_SEITE_OBSEI,false);
        ret += cix_makroparam(CIX_BEZUG,CIX_BEZUG_UL,true);
        ret += cix_makroparam(CIX_NUT_XS, nu.xs_qstring(), false);
        ret += cix_makroparam(CIX_NUT_YS, nu.ys_qstring(), false);
        ret += cix_makroparam(CIX_NUT_ZS, "0", false);
        ret += cix_makroparam(CIX_NUT_XE, nu.xe_qstring(), false);
        ret += cix_makroparam(CIX_NUT_YE, nu.ye_qstring(), false);
        ret += cix_makroparam(CIX_NUT_ZE, "0", false);
        ret += cix_makroparam(CIX_NUT_AUSLAUF, "YES", false);
        ret += cix_makroparam(CIX_NUT_VERLAENGERN_START, "0", false);
        ret += cix_makroparam(CIX_NUT_VERLAENGERN_ENDE, "0", false);
    }else if(nu.bezug() == WST_BEZUG_UNSEI)
    {
        ret += "NAME=CUT_G";
        ret += "\n";
        ret += cix_makroparam(CIX_NUT_LAYER,"CUT_G",true);
        ret += cix_makroparam(CIX_SEITE,CIX_SEITE_UNSEI,false);
        ret += cix_makroparam(CIX_BEZUG,CIX_BEZUG_OR,true);
        ret += cix_makroparam(CIX_NUT_XS, nu.xs_qstring(), false);
        ret += cix_makroparam(CIX_NUT_YS, nu.ys_qstring(), false);
        ret += cix_makroparam(CIX_NUT_ZS, "0", false);
        ret += cix_makroparam(CIX_NUT_XE, nu.xe_qstring(), false);
        ret += cix_makroparam(CIX_NUT_YE, nu.ye_qstring(), false);
        ret += cix_makroparam(CIX_NUT_ZE, "0", false);
        ret += cix_makroparam(CIX_NUT_AUSLAUF, "YES", false);
        ret += cix_makroparam(CIX_NUT_VERLAENGERN_START, "0", false);
        ret += cix_makroparam(CIX_NUT_VERLAENGERN_ENDE, "0", false);
    }else if(nu.bezug() == WST_BEZUG_LI)
    {
        ret += "NAME=CUT_G";
        ret += "\n";
        ret += cix_makroparam(CIX_NUT_LAYER,"CUT_G",true);
        ret += cix_makroparam(CIX_SEITE,CIX_SEITE_LI,false);
        ret += cix_makroparam(CIX_BEZUG,CIX_BEZUG_OR,true);
        ret += cix_makroparam(CIX_NUT_XS, nu.ys_qstring(), false);
        ret += cix_makroparam(CIX_NUT_YS, nu.zs_qstring(), false);
        ret += cix_makroparam(CIX_NUT_ZS, "0", false);
        ret += cix_makroparam(CIX_NUT_XE, nu.ye_qstring(), false);
        ret += cix_makroparam(CIX_NUT_YE, nu.ze_qstring(), false);
        ret += cix_makroparam(CIX_NUT_ZE, "0", false);
        ret += cix_makroparam(CIX_NUT_AUSLAUF, "NO", false);
        ret += cix_makroparam(CIX_NUT_VERLAENGERN_START, "0", false);
        ret += cix_makroparam(CIX_NUT_VERLAENGERN_ENDE, "0", false);
    }else if(nu.bezug() == WST_BEZUG_RE)
    {
        ret += "NAME=CUT_G";
        ret += "\n";
        ret += cix_makroparam(CIX_NUT_LAYER,"CUT_G",true);
        ret += cix_makroparam(CIX_SEITE,CIX_SEITE_RE,false);
        ret += cix_makroparam(CIX_BEZUG,CIX_BEZUG_UL,true);
        ret += cix_makroparam(CIX_NUT_XS, nu.ys_qstring(), false);
        ret += cix_makroparam(CIX_NUT_YS, nu.zs_qstring(), false);
        ret += cix_makroparam(CIX_NUT_ZS, "0", false);
        ret += cix_makroparam(CIX_NUT_XE, nu.ye_qstring(), false);
        ret += cix_makroparam(CIX_NUT_YE, nu.ze_qstring(), false);
        ret += cix_makroparam(CIX_NUT_ZE, "0", false);
        ret += cix_makroparam(CIX_NUT_AUSLAUF, "NO", false);
        ret += cix_makroparam(CIX_NUT_VERLAENGERN_START, "0", false);
        ret += cix_makroparam(CIX_NUT_VERLAENGERN_ENDE, "0", false);
    }else if(nu.bezug() == WST_BEZUG_VO)
    {
        ret += "NAME=CUT_G";
        ret += "\n";
        ret += cix_makroparam(CIX_NUT_LAYER,"CUT_G",true);
        ret += cix_makroparam(CIX_SEITE,CIX_SEITE_VO,false);
        ret += cix_makroparam(CIX_BEZUG,CIX_BEZUG_UL,true);
        ret += cix_makroparam(CIX_NUT_XS, nu.xs_qstring(), false);
        ret += cix_makroparam(CIX_NUT_YS, nu.zs_qstring(), false);
        ret += cix_makroparam(CIX_NUT_ZS, "0", false);
        ret += cix_makroparam(CIX_NUT_XE, nu.xe_qstring(), false);
        ret += cix_makroparam(CIX_NUT_YE, nu.ze_qstring(), false);
        ret += cix_makroparam(CIX_NUT_ZE, "0", false);
        ret += cix_makroparam(CIX_NUT_AUSLAUF, "NO", false);
        ret += cix_makroparam(CIX_NUT_VERLAENGERN_START, "0", false);
        ret += cix_makroparam(CIX_NUT_VERLAENGERN_ENDE, "0", false);
    }else if(nu.bezug() == WST_BEZUG_HI)
    {
        ret += "NAME=CUT_G";
        ret += "\n";
        ret += cix_makroparam(CIX_NUT_LAYER,"CUT_G",true);
        ret += cix_makroparam(CIX_SEITE,CIX_SEITE_HI,false);
        ret += cix_makroparam(CIX_BEZUG,CIX_BEZUG_OR,true);
        ret += cix_makroparam(CIX_NUT_XS, nu.xs_qstring(), false);
        ret += cix_makroparam(CIX_NUT_YS, nu.zs_qstring(), false);
        ret += cix_makroparam(CIX_NUT_ZS, "0", false);
        ret += cix_makroparam(CIX_NUT_XE, nu.xe_qstring(), false);
        ret += cix_makroparam(CIX_NUT_YE, nu.ze_qstring(), false);
        ret += cix_makroparam(CIX_NUT_ZE, "0", false);
        ret += cix_makroparam(CIX_NUT_AUSLAUF, "NO", false);
        ret += cix_makroparam(CIX_NUT_VERLAENGERN_START, "0", false);
        ret += cix_makroparam(CIX_NUT_VERLAENGERN_ENDE, "0", false);
    }
    ret += cix_makroparam(CIX_BEARB_ID,id,true);
    ret += cix_makroparam(CIX_NUT_TYP, CIX_NUT_TYP_SP_EP, false);
    ret += cix_makroparam(CIX_NUT_TI, nu.tiefe_qstring(), false);
    ret += cix_makroparam(CIX_NUT_BREITE, nu.breite_qstring(), false);
    ret += cix_makroparam(CIX_NUT_BREITENZUGABE, "0", false);
    ret += cix_makroparam(CIX_NUT_ISO, "", true);
    ret += cix_makroparam(CIX_BEARB_OPTIMIEREN, "YES", false);
    ret += cix_makroparam(CIX_WDH_TYP, CIX_WDH_TYP_KEIN, false);
    ret += cix_makroparam(CIX_WDH_ABST_X, "0", false);
    ret += cix_makroparam(CIX_WDH_ABST_Y, "0", false);
    ret += cix_makroparam(CIX_WDH_RAD, "0", false);
    ret += cix_makroparam(CIX_WDH_STARTWINKEL, "0", false);
    ret += cix_makroparam(CIX_WDH_WINKEL, "0", false);
    ret += cix_makroparam(CIX_WDH_RADIAL, "NO", false);
    ret += cix_makroparam(CIX_WDH_ANZAHL, "0", false);
    ret += cix_makroparam(CIX_WKZ_DREHTYP, CIX_WKZ_DREHTYP_KEIN, false);
    ret += cix_makroparam(CIX_BEARB_DURCHGEHEND,"NO",false);
    ret += cix_makroparam(CIX_NUT_REVERS, "NO", false);
    ret += cix_makroparam(CIX_WDH_DREHZENTRUM_X, "0", false);
    ret += cix_makroparam(CIX_WDH_DREHZENTRUM_Y, "0", false);
    ret += cix_makroparam(CIX_WDH_GERADENWINKEL, "0", false);
    ret += cix_makroparam(CIX_WDH_ABST, "0", false);
    ret += cix_makroparam(CIX_BEZUG_SIABST,CIX_BEZUG_SIABST_BEARBGRUND,false);
    ret += cix_makroparam(CIX_NUT_ANZ_TIZUST,"0", false);
    ret += cix_makroparam(CIX_NUT_TIEFENMASSBEZUG_ANGEPASST, "NO", false);
    ret += cix_makroparam(CIX_WKZ, wkz, true);
    ret += cix_makroparam(CIX_WKZART, CIX_WKZART_SAEGE_STD, false);
    ret += cix_makroparam(CIX_WKZGRUPPE, CIX_WKZGRUPPE_SAEGER, false);
    ret += cix_makroparam(CIX_DREHZAHL, "0", false);
    ret += cix_makroparam(CIX_SPEED_ANAB, "0", false);
    ret += cix_makroparam(CIX_SPEED, "0" ,false);
    ret += cix_makroparam(CIX_WKZSPINDEL, CIX_WKZSPINDEL_AUTO,true);
    ret += cix_makroparam(CIX_ABBLASEN, "NO", false);
    ret += cix_makroparam(CIX_HAUBENPOS, CIX_HAUBENPOS_AUTO, false);
    ret += cix_makroparam(CIX_NUT_BIDIREKTIONAL, "YES", false);
    ret += cix_makroparam(CIX_NUT_SCHNITTUMKEHR_VERHINDERN, "YES", false);
    ret += cix_makroparam(CIX_NUT_SCHNITTRICHTUNG_UMKEHREN, "NO", false);
    ret += cix_makroparam(CIX_RADKOR, CIX_RADKOR_KEIN, false);
    ret += cix_makroparam(CIX_DREHZ_LETZTE_ZUST, "0", false);
    ret += cix_makroparam(CIX_KENNCODE_ARBEITSZENTRUM_MASCHINE, "",true);
    ret += cix_makroparam(CIX_KENNCODE_AGGREGAT, "",true);
    ret += cix_makroparam(CIX_RESTBEARBTIEFE, "0", false);

    ret += cix_makroparam("ER","YES",false);   //gibt die erste Bohrung ER als Anfangsbohrung der Wiederholung frei
    ret += cix_makroparam("COW", "NO", false); //nur für die Maschine “Skipper”
    ret += cix_makroparam("TH", "0", false);   //???
    ret += cix_makroparam("ETB", "NO", false); //???
    ret += cix_makroparam("KDT", "NO", false); //???
    ret += cix_makroparam("IMS", "0", false);  //???

    ret += "END MACRO";
    ret += "\n";
    ret += "\n";
    return ret;
}
QString wstzustand::cix_beginn_poly(fraeseraufruf fa, QString geo_id)
{
    QString ret;
    ret  = "BEGIN MACRO";
    ret += "\n";
    ret += "\t";
    ret += "NAME=GEO";
    ret += "\n";
    ret += cix_makroparam(CIX_BEARB_ID, geo_id, true);
    ret += cix_makroparam(CIX_NUT_LAYER,"GEO",true);
    if(fa.bezug() == WST_BEZUG_OBSEI)
    {
        ret += cix_makroparam(CIX_SEITE,CIX_SEITE_OBSEI,false);
        ret += cix_makroparam(CIX_BEZUG,CIX_BEZUG_UL,true);
        if(fa.radkor() == FRKOR_L)
        {
            ret += cix_makroparam(CIX_RADKOR, CIX_RADKOR_LI, false);
        }else if(fa.radkor() == FRKOR_R)
        {
            ret += cix_makroparam(CIX_RADKOR, CIX_RADKOR_RE, false);
        }else //FRKOR_M
        {
            ret += cix_makroparam(CIX_RADKOR, CIX_RADKOR_KEIN, false);
        }
    }
    else if(fa.bezug() == WST_BEZUG_UNSEI)
    {
        ret += cix_makroparam(CIX_SEITE,CIX_SEITE_UNSEI,false);
        ret += cix_makroparam(CIX_BEZUG,CIX_BEZUG_OR,true);
        if(fa.radkor() == FRKOR_L)
        {
            ret += cix_makroparam(CIX_RADKOR, CIX_RADKOR_RE, false);//RE weil Unterseite
        }else if(fa.radkor() == FRKOR_R)
        {
            ret += cix_makroparam(CIX_RADKOR, CIX_RADKOR_LI, false);//LI weil Unterseite
        }else //FRKOR_M
        {
            ret += cix_makroparam(CIX_RADKOR, CIX_RADKOR_KEIN, false);
        }
    }
    ret += cix_makroparam(CIX_FKON_TI, fa.tiefe_qstring(), false);
    ret += cix_makroparam(CIX_WDH_TYP,CIX_WDH_TYP_KEIN,false);
    ret += cix_makroparam(CIX_WDH_DREHZENTRUM_X,"0",false);
    ret += cix_makroparam(CIX_WDH_DREHZENTRUM_Y,"0",false);
    ret += cix_makroparam(CIX_WDH_ABST_X, "0", false);
    ret += cix_makroparam(CIX_WDH_ABST_Y, "0", false);
    ret += cix_makroparam(CIX_WDH_RAD, "0", false);
    ret += cix_makroparam(CIX_WDH_STARTWINKEL, "0", false);
    ret += cix_makroparam(CIX_WDH_WINKEL, "0", false);
    ret += cix_makroparam(CIX_WDH_RADIAL, "NO", false);
    ret += cix_makroparam(CIX_WDH_ANZAHL, "0", false);
    ret += cix_makroparam(CIX_WDH_GERADENWINKEL, "0", false);
    ret += cix_makroparam(CIX_WDH_ABST, "0", false);
    ret += cix_makroparam(CIX_FKON_REVERS, "NO", false);    
    ret += cix_makroparam("ER","YES",false);   //gibt die erste Bohrung ER als Anfangsbohrung der Wiederholung frei
    ret += cix_makroparam("COW","NO",false);            //nur für die Maschine “Skipper”
    ret += "END MACRO";
    ret += "\n";
    ret += "\n";
    //------------------------Startpunkt:
    ret += "BEGIN MACRO";
    ret += "\n";
    ret += "\t";
    ret += "NAME=START_POINT";
    ret += "\n";
    if(fa.bezug() == WST_BEZUG_OBSEI  ||  fa.bezug() == WST_BEZUG_UNSEI)
    {
        ret += cix_makroparam(CIX_X, fa.x_qstring(), false);
        ret += cix_makroparam(CIX_Y, fa.y_qstring(), false);
        ret += cix_makroparam(CIX_Z, "0", false);
    }
    ret += "END MACRO";
    ret += "\n";
    ret += "\n";
    return ret;
}
QString wstzustand::cix_linie_ep(fraesergerade fg, QString id)
{
    QString ret;
    ret  = "BEGIN MACRO";
    ret += "\n";
    ret += "\t";
    ret += "NAME=LINE_EP";
    ret += "\n";
    ret += cix_makroparam(CIX_BEARB_ID,id,true);
    if(fg.bezug() == WST_BEZUG_OBSEI  ||  fg.bezug() == WST_BEZUG_UNSEI)
    {
        ret += cix_makroparam(CIX_XE, fg.xe_qstring(),false);
        ret += cix_makroparam(CIX_YE, fg.ye_qstring(),false);
        ret += cix_makroparam(CIX_ZS, "0",false);
        ret += cix_makroparam(CIX_ZE, "0",false);
    }
    ret += cix_makroparam(CIX_LINIE_SCHARFE_KANNTE, CIX_LINIE_SCHARFE_KANNTE_AUS, false);
    ret += cix_makroparam(CIX_LINIE_VORSCHUB, "0", false);
    ret += cix_makroparam(CIX_LINIE_DREHZAHL, "0", false);
    ret += cix_makroparam("SOL", "0", false);//Lösung; an der Linie anwendbare Lösungen,
        //je nach den zuvor eingegebenen Daten. Eine der verfügbaren Optionen wählen
    ret += "END MACRO";
    ret += "\n";
    ret += "\n";
    return ret;
}
QString wstzustand::cix_bogen_ep_mipu(fraeserbogen fb, QString id)
{
    QString ret;
    ret  = "BEGIN MACRO";
    ret += "\n";
    ret += "\t";
    ret += "NAME=ARC_EPCE";
    ret += "\n";
    ret += cix_makroparam(CIX_BEARB_ID,id,true);
    if(fb.bezug() == WST_BEZUG_OBSEI)
    {
        ret += cix_makroparam(CIX_XE, fb.xe_qstring(),false);
        ret += cix_makroparam(CIX_YE, fb.ye_qstring(),false);
        ret += cix_makroparam(CIX_ZE, "0",false);
        bogen b = fb.bog();
        ret += cix_makroparam(CIX_MIPU_X, b.mitte().x_QString(),false);
        ret += cix_makroparam(CIX_MIPU_Y, b.mitte().y_QString(),false);
        if(fb.uzs() == true)
        {
            ret += cix_makroparam(CIX_BOGEN_RICHTUNG, CIX_BOGEN_RICHTUNG_UZS, false);
        }else
        {
            ret += cix_makroparam(CIX_BOGEN_RICHTUNG, CIX_BOGEN_RICHTUNG_GUZS, false);
        }
    }else if(fb.bezug() == WST_BEZUG_UNSEI)
    {
        ret += cix_makroparam(CIX_XE, fb.xe_qstring(),false);
        ret += cix_makroparam(CIX_YE, fb.ye_qstring(),false);
        ret += cix_makroparam(CIX_ZE, "0",false);
        bogen b = fb.bog();
        b.set_radius(b.rad(), !b.im_uzs());
        ret += cix_makroparam(CIX_MIPU_X, b.mitte().x_QString(),false);
        ret += cix_makroparam(CIX_MIPU_Y, b.mitte().y_QString(),false);
        if(fb.uzs() == true)
        {
            ret += cix_makroparam(CIX_BOGEN_RICHTUNG, CIX_BOGEN_RICHTUNG_UZS, false);
        }else
        {
            ret += cix_makroparam(CIX_BOGEN_RICHTUNG, CIX_BOGEN_RICHTUNG_GUZS, false);
        }
    }

    ret += "END MACRO";
    ret += "\n";
    ret += "\n";
    return ret;
}
QString wstzustand::cix_ende_poly(QString id)
{
    QString ret;
    ret  = "BEGIN MACRO";
    ret += "\n";
    ret += "\t";
    ret += "NAME=ENDPATH";
    ret += "\n";
    ret += cix_makroparam(CIX_BEARB_ID, id, true);
    ret += "END MACRO";
    ret += "\n";
    ret += "\n";
    return ret;
}
QString wstzustand::cix_fkon(fraeseraufruf fa, QString geo_id)
{
    QString erw = "_1";
    QString ret;
    ret  = "BEGIN MACRO";
    ret += "\n";
    ret += "\t";
    ret += "NAME=ROUTG";
    ret += "\n";
    ret += cix_makroparam(CIX_BEARB_ID, geo_id+erw, true);
    ret += cix_makroparam(CIX_FKON_GEO_ID, geo_id, true);
    ret += cix_makroparam(CIX_SPEED, "0", false);
    ret += cix_makroparam(CIX_WKZ, fa.wkznum(), true);
    if(fa.radkor() == FRKOR_L)
    {
        ret += cix_makroparam(CIX_RADKOR, CIX_RADKOR_LI, false);
    }else if(fa.radkor() == FRKOR_R)
    {
        ret += cix_makroparam(CIX_RADKOR, CIX_RADKOR_RE, false);
    }else //FRKOR_M
    {
        ret += cix_makroparam(CIX_RADKOR, CIX_RADKOR_KEIN, false);
    }
    ret += cix_makroparam(CIX_FKON_TI, fa.tiefe_qstring(), false);
    ret += cix_makroparam(CIX_FKON_ANZ_TIZUST, "1", false);
    ret += cix_makroparam(CIX_FKON_BREITENZUGABE, "0", false);
    ret += cix_makroparam(CIX_FKON_EINTYP, CIX_FKON_EINTYP_KEIN, false);
    ret += cix_makroparam(CIX_FKON_AUSTYP, CIX_FKON_EINTYP_KEIN, false);
    ret += cix_makroparam(CIX_FKON_EINWI, "45", false);
    ret += cix_makroparam(CIX_FKON_AUSWI, "45", false);
    ret += cix_makroparam(CIX_FKON_VERLAENGERN_START, "30", false);
    ret += cix_makroparam(CIX_FKON_VERLAENGERN_ENDE, "30", false);
    ret += cix_makroparam(CIX_FKON_EINKOR, "NO", false);
    ret += cix_makroparam(CIX_FKON_AUSKOR, "NO", false);
    ret += cix_makroparam(CIX_FKON_GIN, "0", false);
    ret += cix_makroparam(CIX_FKON_GOU, "0", false);
    ret += cix_makroparam(CIX_FKON_TBI, "NO", false);
    ret += cix_makroparam(CIX_FKON_TBO, "NO", false);
    ret += cix_makroparam("TLI", "0", false);//hat was mit TBI zu tun
    ret += cix_makroparam("TLO", "0", false);//hat was mit TBI zu tun
    ret += cix_makroparam("TQI", "0", false);//hat was mit TBI zu tun
    ret += cix_makroparam("TQO", "0", false);//hat was mit TBI zu tun
    ret += cix_makroparam(CIX_FKON_EINAUSRADPROZENT, "0", false);
    ret += cix_makroparam(CIX_HAUBENPOS, CIX_HAUBENPOS_AUTO, false);
    ret += cix_makroparam(CIX_ABWEISER, "NO", false);
    ret += "END MACRO";
    ret += "\n";
    ret += "\n";
    return ret;
}
QString wstzustand::cix_fkon(bohrung bo, QString geo_id, QString wkz)
{
    fraeseraufruf fa;
    fa.set_wkznum(wkz);
    fa.set_radkor(FRKOR_R);
    fa.set_tiefe(bo.tiefe());
    fa.set_bezug(bo.bezug());
    return cix_fkon(fa, geo_id);
}
QString wstzustand::cix_fkon(rechtecktasche rt, QString geo_id, QString wkz)
{
    fraeseraufruf fa;
    fa.set_wkznum(wkz);
    fa.set_radkor(FRKOR_R);
    fa.set_tiefe(rt.tiefe());
    fa.set_bezug(rt.bezug());
    return cix_fkon(fa, geo_id);
}
QString wstzustand::cix_kreis(bohrung bo, QString geo_id)
{
    QString ret;
    ret  = "BEGIN MACRO";
    ret += "\n";
    ret += "\t";
    ret += "NAME=GEO";
    ret += "\n";
    ret += cix_makroparam(CIX_BEARB_ID, geo_id, true);
    ret += cix_makroparam(CIX_NUT_LAYER,"GEO",true);
    if(bo.bezug() == WST_BEZUG_OBSEI)
    {
        ret += cix_makroparam(CIX_SEITE,CIX_SEITE_OBSEI,false);
        ret += cix_makroparam(CIX_BEZUG,CIX_BEZUG_UL,true);
    }else if(bo.bezug() == WST_BEZUG_UNSEI)
    {
        ret += cix_makroparam(CIX_SEITE,CIX_SEITE_UNSEI,false);
        ret += cix_makroparam(CIX_BEZUG,CIX_BEZUG_OR,true);
    }else if(bo.bezug() == WST_BEZUG_LI)
    {
        ret += cix_makroparam(CIX_SEITE,CIX_SEITE_LI,false);
        ret += cix_makroparam(CIX_BEZUG,CIX_BEZUG_OR,true);
    }else if(bo.bezug() == WST_BEZUG_RE)
    {
        ret += cix_makroparam(CIX_SEITE,CIX_SEITE_RE,false);
        ret += cix_makroparam(CIX_BEZUG,CIX_BEZUG_UL,true);
    }else if(bo.bezug() == WST_BEZUG_VO)
    {
        ret += cix_makroparam(CIX_SEITE,CIX_SEITE_VO,false);
        ret += cix_makroparam(CIX_BEZUG,CIX_BEZUG_UL,true);
    }else if(bo.bezug() == WST_BEZUG_HI)
    {
        ret += cix_makroparam(CIX_SEITE,CIX_SEITE_HI,false);
        ret += cix_makroparam(CIX_BEZUG,CIX_BEZUG_OR,true);
    }
    ret += cix_makroparam(CIX_KREIS_REVERS, "0", false);
    ret += cix_makroparam(CIX_RADKOR, CIX_RADKOR_INTERN, false);
    ret += cix_makroparam("DP", "0", false);
    ret += cix_makroparam(CIX_WDH_TYP,CIX_WDH_TYP_KEIN,false);
    ret += cix_makroparam(CIX_WDH_ANZAHL, "0", false);
    ret += cix_makroparam(CIX_WDH_ABST_X, "0", false);
    ret += cix_makroparam(CIX_WDH_ABST_Y, "0", false);
    ret += cix_makroparam("COW","NO",false);            //nur für die Maschine “Skipper”
    ret += "END MACRO";
    ret += "\n";
    ret += "\n";

    ret += "BEGIN MACRO";
    ret += "\n";
    ret += "\t";
    ret += "NAME=CIRCLE_CR";
    ret += "\n";
    ret += cix_makroparam(CIX_NUT_LAYER,"GEO",true);
    if(bo.bezug() == WST_BEZUG_OBSEI)
    {
        ret += cix_makroparam(CIX_MIPU_X,bo.x_qstring(),false);
        ret += cix_makroparam(CIX_MIPU_Y,bo.y_qstring(),false);
    }else if(bo.bezug() == WST_BEZUG_UNSEI)
    {
        ret += cix_makroparam(CIX_MIPU_X,bo.x_qstring(),false);
        ret += cix_makroparam(CIX_MIPU_Y,bo.y_qstring(),false);
    }else if(bo.bezug() == WST_BEZUG_LI)
    {
        ret += cix_makroparam(CIX_MIPU_X,bo.y_qstring(),false);
        ret += cix_makroparam(CIX_MIPU_Y,bo.z_qstring(),false);
    }else if(bo.bezug() == WST_BEZUG_RE)
    {
        ret += cix_makroparam(CIX_MIPU_X,bo.y_qstring(),false);
        ret += cix_makroparam(CIX_MIPU_Y,bo.z_qstring(),false);
    }else if(bo.bezug() == WST_BEZUG_VO)
    {
        ret += cix_makroparam(CIX_MIPU_X,bo.x_qstring(),false);
        ret += cix_makroparam(CIX_MIPU_Y,bo.z_qstring(),false);
    }else if(bo.bezug() == WST_BEZUG_HI)
    {
        ret += cix_makroparam(CIX_MIPU_X,bo.x_qstring(),false);
        ret += cix_makroparam(CIX_MIPU_Y,bo.z_qstring(),false);
    }
    ret += cix_makroparam(CIX_KREIS_RAD, double_to_qstring(bo.dm()/2), false);
    ret += cix_makroparam(CIX_KREIS_STARTWI, "90", false);
    ret += cix_makroparam(CIX_RICHTUNG, CIX_RICHTUNG_UZS, false);
    ret += cix_makroparam(CIX_KREIS_VORSCHUB, "0", false);
    ret += cix_makroparam(CIX_KREIS_DREHZAHL, "0", false);
    ret += "END MACRO";
    ret += "\n";
    ret += "\n";
    return ret;
}
QString wstzustand::cix_tasche(fraeseraufruf fa, QString geo_id, double dm)
{
    QString erw = "_1";
    QString ret;
    ret  = "BEGIN MACRO";
    ret += "\n";
    ret += "\t";
    ret += "NAME=POCK";
    ret += "\n";
    ret += cix_makroparam(CIX_BEARB_ID, geo_id+erw, true);
    ret += cix_makroparam(CIX_FKON_GEO_ID, geo_id, true);
    ret += cix_makroparam(CIX_TASCHE_LAYER, "POCK", true);
    ret += cix_makroparam(CIX_TASCHE_TYP, CIX_TASCHE_TYP_IzuA, false);
    ret += cix_makroparam(CIX_TASCHE_DM, double_to_qstring(dm),false);
    ret += cix_makroparam(CIX_SPEED, "0", false);
    ret += cix_makroparam(CIX_WKZ, fa.wkznum(), true);
    ret += cix_makroparam(CIX_FKON_TI, fa.tiefe_qstring(), false);
    ret += cix_makroparam(CIX_FKON_BREITENZUGABE, "0", false);
    ret += cix_makroparam(CIX_FKON_EINTYP, CIX_FKON_EINTYP_BOG, false);
    ret += cix_makroparam(CIX_FKON_AUSTYP, CIX_FKON_EINTYP_BOG, false);
    ret += cix_makroparam(CIX_FKON_EINWI, "45", false);
    ret += cix_makroparam(CIX_FKON_AUSWI, "45", false);
    ret += cix_makroparam(CIX_FKON_VERLAENGERN_START, "14.5", false);
    ret += cix_makroparam(CIX_FKON_VERLAENGERN_ENDE, "14.5", false);
    ret += cix_makroparam(CIX_FKON_EINKOR, "NO", false);
    ret += cix_makroparam(CIX_FKON_AUSKOR, "NO", false);
    ret += cix_makroparam(CIX_FKON_EINAUSRADPROZENT, "0", false);
    ret += cix_makroparam(CIX_HAUBENPOS, CIX_HAUBENPOS_AUTO, false);
    ret += cix_makroparam(CIX_TASCHE_INSELLISTE, "", true);
    ret += cix_makroparam(CIX_TASCHE_ISO, "", true);
    ret += cix_makroparam(CIX_BEARB_OPTIMIEREN, "YES", false);
    ret += cix_makroparam(CIX_WDH_STARTWINKEL, "0", false);
    ret += cix_makroparam(CIX_TASCHE_KOMPENSATION, "YES", false);
    ret += cix_makroparam(CIX_TASCHE_INSELNAKTIV, "NO", false);
    ret += cix_makroparam(CIX_TASCHE_REVERS, "NO", false);
    ret += cix_makroparam(CIX_TASCHE_REVERS_NB, "NO", false);
    ret += cix_makroparam(CIX_TASCHE_Z, "0", false);
    ret += cix_makroparam(CIX_BEZUG_SIABST, CIX_BEZUG_SIABST_BEARBGRUND, false);
    ret += cix_makroparam(CIX_DREHZ_LETZTE_ZUST, "100", false);
    ret += cix_makroparam(CIX_DREHZAHL, "0", false);
    ret += cix_makroparam(CIX_SPEED_ANAB, "100", false);
    ret += cix_makroparam(CIX_WKZART, CIX_WKZART_FR_KERZE, false);
    ret += cix_makroparam(CIX_WKZGRUPPE, CIX_WKZGRUPPE_FRAESER, false);
    ret += cix_makroparam(CIX_TASCHEVERLAGERUNG, CIX_TASCHEVERLAGERUNG_AUTO, false);
    ret += cix_makroparam(CIX_WKZSPINDEL, CIX_WKZSPINDEL_AUTO, true);
    ret += cix_makroparam(CIX_KENNCODE_ARBEITSZENTRUM_MASCHINE, "", true);
    ret += cix_makroparam(CIX_KENNCODE_AGGREGAT, "", true);
    ret += cix_makroparam("COW","NO",false);            //nur für die Maschine “Skipper”
    ret += cix_makroparam("EA21","NO",false);           //aktiviert die Verwendung der Parameter A21 und S21
    ret += cix_makroparam(CIX_WKZ_NEIGUNG,"0",false);
    ret += cix_makroparam(CIX_WKZ_DREHWI,"0",false);
    ret += cix_makroparam(CIX_WKZ_DREHTYP,CIX_WKZ_DREHTYP_KEIN,false);
    ret += cix_makroparam(CIX_ABBLASEN, "NO", false);

    ret += cix_makroparam(CIX_TASCHE_UEBERLAPPUNG, "2", false); //??
    ret += cix_makroparam(CIX_TASCHE_UEBERLAPPUNG_, "0", false);//?
    ret += cix_makroparam("N", "-1", false); //???
    ret += cix_makroparam("A21","0",false);             //Winkel Aggr21
    ret += cix_makroparam("S21","-1",false);            //Winkel Aggr21

    ret += "END MACRO";
    ret += "\n";
    ret += "\n";
    return ret;
}
QString wstzustand::cix_tasche(bohrung bo, QString wkz, QString geo_id, double dm)
{
    fraeseraufruf fa;
    fa.set_wkznum(wkz);
    fa.set_radkor(FRKOR_R);
    fa.set_tiefe(bo.tiefe());
    fa.set_bezug(bo.bezug());
    return cix_tasche(fa, geo_id, dm);
}
QString wstzustand::cix_tasche(rechtecktasche rt, QString wkz, QString geo_id)
{
    fraeseraufruf fa;
    fa.set_wkznum(wkz);
    fa.set_radkor(FRKOR_R);
    fa.set_tiefe(rt.tiefe());
    fa.set_bezug(rt.bezug());
    return cix_tasche(fa, geo_id, 0);
}
QString wstzustand::cix_rechteck(rechtecktasche rt, QString geo_id)
{
    QString ret;
    ret  = "BEGIN MACRO";
    ret += "\n";
    ret += "\t";
    ret += "NAME=GEO";
    ret += "\n";
    ret += cix_makroparam(CIX_BEARB_ID, geo_id, true);
    ret += cix_makroparam(CIX_NUT_LAYER,"GEO",true);
    if(rt.bezug() == WST_BEZUG_OBSEI)
    {
        ret += cix_makroparam(CIX_SEITE,CIX_SEITE_OBSEI,false);
        ret += cix_makroparam(CIX_BEZUG,CIX_BEZUG_UL,true);
    }else if(rt.bezug() == WST_BEZUG_UNSEI)
    {
        ret += cix_makroparam(CIX_SEITE,CIX_SEITE_UNSEI,false);
        ret += cix_makroparam(CIX_BEZUG,CIX_BEZUG_OR,true);
    }else if(rt.bezug() == WST_BEZUG_LI)
    {
        ret += cix_makroparam(CIX_SEITE,CIX_SEITE_LI,false);
        ret += cix_makroparam(CIX_BEZUG,CIX_BEZUG_OR,true);
    }else if(rt.bezug() == WST_BEZUG_RE)
    {
        ret += cix_makroparam(CIX_SEITE,CIX_SEITE_RE,false);
        ret += cix_makroparam(CIX_BEZUG,CIX_BEZUG_UL,true);
    }else if(rt.bezug() == WST_BEZUG_VO)
    {
        ret += cix_makroparam(CIX_SEITE,CIX_SEITE_VO,false);
        ret += cix_makroparam(CIX_BEZUG,CIX_BEZUG_UL,true);
    }else if(rt.bezug() == WST_BEZUG_HI)
    {
        ret += cix_makroparam(CIX_SEITE,CIX_SEITE_HI,false);
        ret += cix_makroparam(CIX_BEZUG,CIX_BEZUG_OR,true);
    }
    ret += "END MACRO";
    ret += "\n";
    ret += "\n";

    ret += "BEGIN MACRO";
    ret += "\n";
    ret += "\t";
    ret += "NAME=RECTANGLE";
    ret += "\n";
    ret += cix_makroparam(CIX_BEARB_ID, geo_id, true);
    ret += cix_makroparam(CIX_NUT_LAYER,"GEO",true);
    if(rt.bezug() == WST_BEZUG_OBSEI)
    {
        ret += cix_makroparam(CIX_MIPU_X,rt.x_qstring(),false);
        ret += cix_makroparam(CIX_MIPU_Y,rt.y_qstring(),false);
    }else if(rt.bezug() == WST_BEZUG_UNSEI)
    {
        ret += cix_makroparam(CIX_MIPU_X,rt.x_qstring(),false);
        ret += cix_makroparam(CIX_MIPU_Y,rt.y_qstring(),false);
    }else if(rt.bezug() == WST_BEZUG_LI)
    {
        ret += cix_makroparam(CIX_MIPU_X,rt.y_qstring(),false);
        ret += cix_makroparam(CIX_MIPU_Y,rt.z_qstring(),false);
    }else if(rt.bezug() == WST_BEZUG_RE)
    {
        ret += cix_makroparam(CIX_MIPU_X,rt.y_qstring(),false);
        ret += cix_makroparam(CIX_MIPU_Y,rt.z_qstring(),false);
    }else if(rt.bezug() == WST_BEZUG_VO)
    {
        ret += cix_makroparam(CIX_MIPU_X,rt.x_qstring(),false);
        ret += cix_makroparam(CIX_MIPU_Y,rt.z_qstring(),false);
    }else if(rt.bezug() == WST_BEZUG_HI)
    {
        ret += cix_makroparam(CIX_MIPU_X,rt.x_qstring(),false);
        ret += cix_makroparam(CIX_MIPU_Y,rt.z_qstring(),false);
    }
    ret += cix_makroparam(CIX_RECHTECK_L, rt.laenge_qstring(), false);
    ret += cix_makroparam(CIX_RECHTECK_B, rt.breite_qstring(), false);
    ret += cix_makroparam(CIX_RICHTUNG, CIX_RICHTUNG_UZS, false);
    ret += cix_makroparam(CIX_KREIS_VORSCHUB, "0", false);
    ret += cix_makroparam(CIX_KREIS_DREHZAHL, "0", false);
    if(rt.rad() == 0)
    {
        ret += cix_makroparam(CIX_RECHTECK_ECKENTYP, CIX_RECHTECK_ECKENTYP_ECKIG, false);
    }else
    {
        ret += cix_makroparam(CIX_RECHTECK_ECKENTYP, CIX_RECHTECK_ECKENTYP_RUND, false);
    }
    ret += cix_makroparam(CIX_RECHTECK_ECKENRAD, rt.rad_qstring(), false);
    ret += cix_makroparam(CIX_RECHTECK_STARTSEITE, "1", true);
    ret += cix_makroparam(CIX_RECHTECK_STARTABST, CIX_HAELFTE, false);
    ret += cix_makroparam(CIX_RECHTECK_DREWI, rt.drewi_qstring(), false);
    ret += cix_makroparam(CIX_RECHTECK_BUZUGSPUNKT, CIX_RECHTECK_BUZUGSPUNKT_MITTE, false);
    ret += cix_makroparam(CIX_RECHTECK_BEZUGSECKE, "1", false);
    ret += cix_makroparam(CIX_ZS, "0", false);
    ret += cix_makroparam(CIX_ZE, "0", false);
    ret += cix_makroparam(CIX_LINIE_SCHARFE_KANNTE, CIX_LINIE_SCHARFE_KANNTE_AUS, false);
    ret += "END MACRO";
    ret += "\n";
    ret += "\n";

    ret += "BEGIN MACRO";
    ret += "\n";
    ret += "\t";
    ret += "NAME=ENDPATH";
    ret += "\n";
    ret += "END MACRO";
    ret += "\n";
    ret += "\n";

    return ret;
}

void wstzustand::ganx_dateitext(int index)
{
    //Physischer-Maschinen-Nullpunkt ist oben links
    //Maschinen-Nullunkt in der Software ist unten links
    //Programm-Nullpunkt in bearb ist unten links
    text_zw bearb = Bearb.at(index);
    QString drewi = Drehung.at(index);
    double tmp_l = Laenge.at(index);
    double tmp_b = Breite.at(index);
    wkz_magazin wkzmag = Wkzm.at(index);
    dubosplitten(bearb, wkzmag);    

    text_zw bearb_kopie = bearb;

    QString msg;
    text_zw zeile;
    //Trennzeichen: TRENNZ_BEARB_PARAM
    QString kavo = kante_vo_ganx(drewi);//Kante vorne == Kante an X
    QString kali = kante_li_ganx(drewi);//Kante links == Kante an Y
    QString kahi = kante_hi_ganx(drewi);//Kante hinten == Kante nicht an X
    QString kare = kante_re_ganx(drewi);//Kante rechts == Kante nicht an Y

    double bezugsmass;    //Referenzmaß zum Erkennen der Bezugskante
    bezugsmass = Eganx.bezugsmass();
    bool bezmass_in_use = Eganx.bezugsmass_in_use();


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

    for(uint i=0 ; i<bearb.count() ; i++)
    {
        zeile.set_text(bearb.at(i),TRENNZ_BEARB_PARAM);
        if(zeile.at(0) == BEARBART_BOHR)
        {
            bohrung bo(zeile.text());

            QString afb_text = bo.afb();
            afb_text.replace("L", double_to_qstring(tmp_l));
            afb_text.replace("B", double_to_qstring(tmp_b));
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
                double boti = bo.tiefe();
                if(  (bezug == WST_BEZUG_OBSEI)  ||  (bezug == WST_BEZUG_UNSEI)  )
                {
                    if(boti > Dicke && wkzmag.ist_dubo(tnummer))
                    {
                        boti = Dicke + bo.dm();//Tiefe Durchgangsbohrung entspricht DM Bohrer
                    }
                }

                //Anzahl der Zustellungen berechnen:
                double zustmass = bo.zustellmass();
                if(zustmass <= 0)
                {
                    if(bo.bezug() == WST_BEZUG_OBSEI  || bo.bezug() == GANX_WST_BEZUG_UNSEI)
                    {
                        zustmass = wkzmag.zustmasvert(tnummer).toDouble();
                    }else
                    {
                        zustmass = wkzmag.zustmashori(tnummer).toDouble();
                    }
                }
                int zustellungen = aufrunden(boti / zustmass);
                if(zustellungen <= 0)
                {
                    zustellungen = 1;
                }
                zustmass = boti/zustellungen;
                //-------------------------------

                if(bezug == WST_BEZUG_OBSEI)
                {
                    //x = Breite
                    //y = Länge
                    //z = Tiefe
                    double aktti; //aktuelle Tiefe
                    aktti = zustmass;
                    while(aktti <= boti)
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
                        y = laenge_y - y; //Y-Maß auf physischen Maschinen-Nullpnkt umdenken (oben links)
                        if(bezmass_in_use && laenge_y - y < bezugsmass)
                        {
                            ref += GANX_REF_UNTEN_LINKS;
                            y = laenge_y - y; //Y-Maß auf Maschinen-Nullpnkt in der Software umdenken (unten links)
                        }else
                        {
                            ref += GANX_REF_OBEN_LINKS;
                            y = laenge_y - y; //Y-Maß auf Maschinen-Nullpnkt in der Software umdenken (unten links)
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
                    while(aktti <= boti)
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
                        y = laenge_y - y; //Y-Maß auf physischen Maschinen-Nullpnkt umdenken (oben links)
                        if(bezmass_in_use && laenge_y - y < bezugsmass)
                        {
                            ref = GANX_REF_UNTEN_LINKS;
                            y = laenge_y - y; //Y-Maß auf Maschinen-Nullpnkt in der Software umdenken (unten links)
                        }else
                        {
                            ref = GANX_REF_OBEN_LINKS;
                            y = laenge_y - y; //Y-Maß auf Maschinen-Nullpnkt in der Software umdenken (unten links)
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
                    while(aktti <= boti)
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
                    while(aktti <= boti)
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
                    while(aktti <= boti)
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
                    while(aktti <= boti)
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
                //Ist direkt ei WKZ definiert?
                if(bo.bezug() == WST_BEZUG_OBSEI  ||  bo.bezug() == WST_BEZUG_UNSEI)
                {
                    tnummer = wkzmag.wkznummer_von_alias(bo.wkznum(), WKZ_VERT);
                }else
                {
                    tnummer = wkzmag.wkznummer_von_alias(bo.wkznum(), WKZ_HORI);
                }
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
                        zustmass = wkzmag.zustmasvert(tnummer).toDouble();
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
                    y = laenge_y - y; //Y-Maß auf physischen Maschinen-Nullpnkt umdenken (oben links)
                    if(bezmass_in_use && laenge_y - y < bezugsmass)
                    {
                        ref = GANX_REF_UNTEN_LINKS;
                        y = laenge_y - y; //Y-Maß auf Maschinen-Nullpnkt in der Software umdenken (unten links)
                    }else
                    {
                        ref = GANX_REF_OBEN_LINKS;
                        y = laenge_y - y; //Y-Maß auf Maschinen-Nullpnkt in der Software umdenken (unten links)
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
                    //Mit Fehlermeldung abbrechen:
                    QString msg = fehler_kein_WKZ("ganx", zeile);
                    Fehler_kein_wkz.append(msg);
                    Exporttext.append(msg);
                    Export_moeglich.append(false);
                    return;
                }
            }
        }else if(zeile.at(0) == BEARBART_BOHRRASTER)
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
                    zustmass = wkzmag.zustmasvert(tnummer).toDouble();
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
                                y = laenge_y - y; //Y-Maß auf physischen Maschinen-Nullpnkt umdenken (oben links)
                                if(bezmass_in_use && laenge_y - y < bezugsmass  &&  bora.anz_y()==1  )
                                {
                                    ref += GANX_REF_UNTEN_LINKS;
                                    y = laenge_y - y; //Y-Maß auf Maschinen-Nullpnkt in der Software umdenken (unten links)
                                }else
                                {
                                    ref += GANX_REF_OBEN_LINKS;
                                    y = laenge_y - y; //Y-Maß auf Maschinen-Nullpnkt in der Software umdenken (unten links)
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
        }else if(zeile.at(0)==BEARBART_NUT)
        {
            nut nu(zeile.text());
            if(nu.bezug() == WST_BEZUG_OBSEI  ||  nu.bezug() == WST_BEZUG_UNSEI)
            {
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
                    //Mit Fehlermeldung abbrechen:
                    QString msg = fehler_kein_WKZ("ganx", zeile);
                    Fehler_kein_wkz.append(msg);
                    Exporttext.append(msg);
                    Export_moeglich.append(false);
                    return;
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

            }
        }else if(zeile.at(0)==BEARBART_RTA)
        {
            rechtecktasche rt(zeile.text());
            if(  (rt.bezug() == WST_BEZUG_OBSEI) ||  (rt.bezug() == WST_BEZUG_UNSEI)  )
            {
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

                QString tnummer;
                //Ist direkt ei WKZ definiert?
                if(rt.bezug() == WST_BEZUG_OBSEI  ||  rt.bezug() == WST_BEZUG_UNSEI)
                {
                    tnummer = wkzmag.wkznummer_von_alias(rt.wkznum(), WKZ_VERT);
                }else
                {
                    tnummer = wkzmag.wkznummer_von_alias(rt.wkznum(), WKZ_HORI);
                }
                if(tnummer.isEmpty())
                {
                     tnummer = wkzmag.wkznummer(WKZ_TYP_FRAESER, minmass, rt.tiefe(), Dicke, rt.bezug());
                }

                if(tnummer.isEmpty())
                {
                    //Mit Fehlermeldung abbrechen:
                    QString msg = fehler_kein_WKZ("ganx", zeile);
                    Fehler_kein_wkz.append(msg);
                    Exporttext.append(msg);
                    Export_moeglich.append(false);
                    return;
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
                    zustmass = wkzmag.zustmasvert(tnummer).toDouble();
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
                        //Mit Fehlermeldung abbrechen:
                        QString msg = fehler_kein_WKZ("ganx", zeile);
                        msg += "\n";
                        msg += "Anzahl der Zustellungen: ";
                        msg += double_to_qstring(zustellungen);
                        Fehler_kein_wkz.append(msg);
                        Exporttext.append(msg);
                        Export_moeglich.append(false);
                        return;
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
                    y = laenge_y - y; //Y-Maß auf physischen Maschinen-Nullpnkt umdenken (oben links)
                    if(bezmass_in_use && laenge_y - y < bezugsmass)
                    {
                        ref = GANX_REF_UNTEN_LINKS;
                        y = laenge_y - y; //Y-Maß auf Maschinen-Nullpnkt in der Software umdenken (unten links)
                    }else
                    {
                        ref = GANX_REF_OBEN_LINKS;
                        y = laenge_y - y; //Y-Maß auf Maschinen-Nullpnkt in der Software umdenken (unten links)
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
    }

    //-------------------------Bearbeitungen <PrgrFile>:
    //Dies ist der Teil, den die Gannomat-Editor liest
    //Hier darf nur mit der Syntax entsprechenden Formeln gearbeitet werden
    id = 1;//id die im Editor angezeigt wird
    ganx_Gruppen gruppen_PrgrFile;

    for(uint i=0 ; i<bearb.count() ; i++)
    {
        zeile.set_text(bearb.at(i),TRENNZ_BEARB_PARAM);
        if(zeile.at(0) == BEARBART_BOHR)
        {
            bohrung bo(zeile.text());

            QString afb_text = bo.afb();
            afb_text.replace("L", double_to_qstring(tmp_l));
            afb_text.replace("B", double_to_qstring(tmp_b));
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
                double boti = bo.tiefe();
                if(  (bezug == WST_BEZUG_OBSEI)  ||  (bezug == WST_BEZUG_UNSEI)  )
                {
                    if(boti > Dicke && wkzmag.ist_dubo(tnummer))
                    {
                        boti = Dicke + bo.dm();//Tiefe Durchgangsbohrung entspricht DM Bohrer
                    }
                }

                //Anzahl der Zustellungen berechnen:
                double zustmass = bo.zustellmass();
                if(zustmass <= 0)
                {
                    if(bo.bezug() == WST_BEZUG_OBSEI  ||  bo.bezug() == WST_BEZUG_UNSEI)
                    {
                        zustmass = wkzmag.zustmasvert(tnummer).toDouble();
                    }else
                    {
                        zustmass = wkzmag.zustmashori(tnummer).toDouble();
                    }
                }
                int zustellungen = aufrunden(boti / zustmass);
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
                    y = laenge_y - y; //Y-Maß auf physischen Maschinen-Nullpnkt umdenken (oben links)
                    if(bezmass_in_use && laenge_y - y < bezugsmass)
                    {
                        ref += GANX_REF_UNTEN_LINKS;
                        y = laenge_y - y;
                    }else
                    {
                        ref += GANX_REF_OBEN_LINKS;
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
                    msg += double_to_qstring(boti).replace(".",",");
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
                    y = laenge_y - y; //Y-Maß auf physischen Maschinen-Nullpnkt umdenken (oben links)
                    if(bezmass_in_use && laenge_y - y < bezugsmass)
                    {
                        ref = GANX_REF_UNTEN_LINKS;
                        y = laenge_y - y;
                    }else
                    {
                        ref = GANX_REF_OBEN_LINKS;
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
                    msg += double_to_qstring(boti).replace(".",",");
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
                    y = laenge_y - y; //Y-Maß auf physischen Maschinen-Nullpnkt umdenken (oben links)
                    if(bezmass_in_use && laenge_y - y < bezugsmass)
                    {
                        ref += GANX_REF_UNTEN_LINKS;
                        y = laenge_y - y;
                    }else
                    {
                        ref += GANX_REF_OBEN_LINKS;
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
                    msg += double_to_qstring(boti).replace(".",",");
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
                    y = laenge_y - y; //Y-Maß auf physischen Maschinen-Nullpnkt umdenken (oben links)
                    if(bezmass_in_use && laenge_y - y < bezugsmass)
                    {
                        ref += GANX_REF_UNTEN_RECHTS;
                        y = laenge_y - y;
                    }else
                    {
                        ref += GANX_REF_OBEN_RECHTS;
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
                    msg += double_to_qstring(boti).replace(".",",");
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
                    msg += double_to_qstring(boti).replace(".",",");
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
                    msg += double_to_qstring(boti).replace(".",",");
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
                //Ist direkt ei WKZ definiert?
                if(bo.bezug() == WST_BEZUG_OBSEI  ||  bo.bezug() == WST_BEZUG_UNSEI)
                {
                    tnummer = wkzmag.wkznummer_von_alias(bo.wkznum(), WKZ_VERT);
                }else
                {
                    tnummer = wkzmag.wkznummer_von_alias(bo.wkznum(), WKZ_HORI);
                }
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
                        if(bo.bezug() == WST_BEZUG_OBSEI  || bo.bezug() == GANX_WST_BEZUG_UNSEI)
                        {
                            zustmass = wkzmag.zustmasvert(tnummer).toDouble();
                        }else
                        {
                            zustmass = wkzmag.zustmashori(tnummer).toDouble();
                        }
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
                    QString ref;
                    //y < 40 -> TL
                    //Länge - y < 40 ->BL
                    y = laenge_y - y; //Y-Maß auf physischen Maschinen-Nullpnkt umdenken (oben links)
                    if(bezmass_in_use && laenge_y - y < bezugsmass)
                    {
                        ref = GANX_REF_UNTEN_LINKS;
                        y = laenge_y - y;
                    }else
                    {
                        ref = GANX_REF_OBEN_LINKS;
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
                    //da die Funktion bereits in der ersten For-Schleife abbricht.

                    //Mit Fehlermeldung abbrechen:
                    QString msg = fehler_kein_WKZ("ganx", zeile);
                    Fehler_kein_wkz.append(msg);
                    Exporttext.append(msg);
                    Export_moeglich.append(false);
                    return;
                }
            }
        }else if(zeile.at(0) == BEARBART_BOHRRASTER)
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
                    zustmass = wkzmag.zustmasvert(tnummer).toDouble();
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
                        y = laenge_y - y; //Y-Maß auf physischen Maschinen-Nullpnkt umdenken (oben links)
                        if(bezmass_in_use && laenge_y - y < bezugsmass)
                        {
                            ref += GANX_REF_UNTEN_LINKS;
                            y = laenge_y - y;
                        }else
                        {
                            ref += GANX_REF_OBEN_LINKS;
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
        }else if(zeile.at(0) == BEARBART_NUT)
        {

            nut nu(zeile.text());
            if(nu.bezug() == WST_BEZUG_OBSEI  ||  nu.bezug() == WST_BEZUG_UNSEI)
            {
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

                    //Mit Fehlermeldung abbrechen:
                    QString msg = fehler_kein_WKZ("ganx", zeile);
                    Fehler_kein_wkz.append(msg);
                    Exporttext.append(msg);
                    Export_moeglich.append(false);
                    return;
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
            }
        }else if(zeile.at(0) == BEARBART_RTA)
        {
            rechtecktasche rt(zeile.text());
            if(  (rt.bezug() == WST_BEZUG_OBSEI) ||  (rt.bezug() == WST_BEZUG_UNSEI)  )
            {
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

                QString tnummer;
                //Ist direkt ei WKZ definiert?
                if(rt.bezug() == WST_BEZUG_OBSEI  ||  rt.bezug() == WST_BEZUG_UNSEI)
                {
                    tnummer = wkzmag.wkznummer_von_alias(rt.wkznum(), WKZ_VERT);
                }else
                {
                    tnummer = wkzmag.wkznummer_von_alias(rt.wkznum(), WKZ_HORI);
                }
                if(tnummer.isEmpty())
                {
                     tnummer = wkzmag.wkznummer(WKZ_TYP_FRAESER, minmass, rt.tiefe(), Dicke, rt.bezug());
                }

                if(tnummer.isEmpty())
                {
                    //Diese Stelle des Codes wird theoretisch niemals erreicht,
                    //da die Funktion bereits in er ersten For-Schleife abbricht.

                    //Mit Fehlermeldung abbrechen:
                    QString msg = fehler_kein_WKZ("ganx", zeile);
                    Fehler_kein_wkz.append(msg);
                    Exporttext.append(msg);
                    Export_moeglich.append(false);
                    return;
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
                    zustmass = wkzmag.zustmasvert(tnummer).toDouble();
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

                        //Mit Fehlermeldung abbrechen:
                        QString msg = fehler_kein_WKZ("ganx", zeile);
                        msg += "\n";
                        msg += "Anzahl der Zustellungen: ";
                        msg += double_to_qstring(zustellungen);
                        Fehler_kein_wkz.append(msg);
                        Exporttext.append(msg);
                        Export_moeglich.append(false);
                        return;
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
                    QString ref;
                    //y < 40 -> TL
                    //Länge - y < 40 ->BL
                    y = laenge_y - y; //Y-Maß auf physischen Maschinen-Nullpnkt umdenken (oben links)
                    if(bezmass_in_use && laenge_y - y < bezugsmass)
                    {
                        ref = GANX_REF_UNTEN_LINKS;
                        y = laenge_y - y;
                    }else
                    {
                        ref = GANX_REF_OBEN_LINKS;
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
    }

    //-------------------------Bearbeitungsgruppen:
    if(gruppen_PrgrFile.gruppen()  ==  gruppen_PrgrFileWork.gruppen())
    {
        msg += gruppen_PrgrFile.gruppen();
    }else
    {
        //Diese Stelle sollte niermals erreicht werden

        QString msg = "Programminterner Fehler bei der Erstellung von Bearbeitungsgruppen!";
        Fehler_kein_wkz.append(msg);
        Exporttext.append(msg);
        Export_moeglich.append(false);
        return;
    }

    //-------------------------Programmende:
    msg += "</Programm>";

    Fehler_kein_wkz.append("");
    Exporttext.append(msg);
    Export_moeglich.append(true);
}
void wstzustand::ggf_dateitext(int index)
{
    text_zw bearb = Bearb.at(index);
    QString drewi = Drehung.at(index);
    double tmp_l = Laenge.at(index);
    double tmp_b = Breite.at(index);
    wkz_magazin wkzmag = Wkzm.at(index);
    dubosplitten(bearb, wkzmag);

    text_zw bearb_kopie = bearb;

    QString msg;
    text_zw zeile;
    QString kavo = kante_vo(drewi);//Kante vorne == Kante an X
    QString kali = kante_li(drewi);//Kante links == Kante an Y
    QString kahi = kante_hi(drewi);//Kante hinten == Kante nicht an X
    QString kare = kante_re(drewi);//Kante rechts == Kante nicht an Y

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
    for(uint i=0 ; i<bearb.count() ; i++)
    {
       zeile.set_text(bearb.at(i), TRENNZ_BEARB_PARAM);
       if(zeile.at(0) == BEARBART_BOHR)
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
                   //msg += bo.dm_qstring();
                   msg += wkzmag.dm(tnummer);
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
               //Ist direkt ei WKZ definiert?
               if(bo.bezug() == WST_BEZUG_OBSEI  ||  bo.bezug() == WST_BEZUG_UNSEI)
               {
                   tnummer = wkzmag.wkznummer_von_alias(bo.wkznum(), WKZ_VERT);
               }else
               {
                   tnummer = wkzmag.wkznummer_von_alias(bo.wkznum(), WKZ_HORI);
               }
               if(tnummer.isEmpty())
               {
                   tnummer = wkzmag.wkznummer(WKZ_TYP_FRAESER, bo.dm(), bo.tiefe(), Dicke, bezug);
               }
               if(!tnummer.isEmpty())
               {
                   double zustellmas = bo.zustellmass();
                   if(zustellmas <= 0)
                   {
                       zustellmas = wkzmag.zustmasvert(tnummer).toDouble();
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
                       //msg += bo.dm_qstring();
                       msg += wkzmag.dm(tnummer);
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
                   //Mit Fehlermeldung abbrechen:
                   QString msg = fehler_kein_WKZ("ggf", zeile);
                   Fehler_kein_wkz.append(msg);
                   Exporttext.append(msg);
                   Export_moeglich.append(false);
                   return;
               }
           }
       }else if(zeile.at(0) == BEARBART_RTA)
       {
           rechtecktasche rt(zeile.text());
           QString tnummer = wkzmag.wkznummer_von_alias(rt.wkznum(), WKZ_VERT);//Ist direkt ei WKZ definiert?
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
               double zustellmas = rt.zustellmass();
               if(zustellmas <= 0)
               {
                   zustellmas = wkzmag.zustmasvert(tnummer).toDouble();
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
               Fehler_kein_wkz.append(msg);
               Exporttext.append(msg);
               Export_moeglich.append(false);
               return;
           }
       }else if(zeile.at(0) == BEARBART_FRAESERAUFRUF)
       {
           fraeseraufruf fa(zeile.text());
           QString tnummer = wkzmag.wkznummer_von_alias(fa.wkznum(), WKZ_VERT);
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
                   while(i+1<bearb.count())
                   {
                       zeile.set_text(bearb.at(i+1), TRENNZ_BEARB_PARAM);

                       if(zeile.at(0) == BEARBART_FRAESERGERADE)
                       {
                           i++;
                           zeile.set_text(bearb.at(i),TRENNZ_BEARB_PARAM);
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
                       }else if(zeile.at(0) == BEARBART_FRAESERBOGEN)
                       {
                           i++;
                           zeile.set_text(bearb.at(i),TRENNZ_BEARB_PARAM);
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
               Fehler_kein_wkz.append(msg);
               Exporttext.append(msg);
               Export_moeglich.append(false);
               return;
           }
       }
    }
    //---------------------------------------Bearbeitungen Unterseite:
    bool unterseite_hat_bearb = false;
    for(uint i=0 ; i<bearb.count() ; i++)
    {
        zeile.set_text(bearb.at(i), TRENNZ_BEARB_PARAM);
        if(zeile.at(1) == WST_BEZUG_UNSEI)
        {
            unterseite_hat_bearb = true;
            break;
        }
    }
    if(unterseite_hat_bearb == true)
    {
        for(uint i=0 ; i<bearb.count() ; i++)
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

    Fehler_kein_wkz.append("");
    Exporttext.append(msg);
    Export_moeglich.append(true);
}
void wstzustand::geo(int index)
{
    QString format = Format.at(index);
    QString drehwinkel = Drehung.at(index);
    double l = Laenge.at(index);
    double b = Breite.at(index);
    double d = Dicke;
    text_zw tmp_bearb = Bearb.at(index);
    double versatz_x = 0;
    double versatz_y = 0;
    QString kante_v;
    QString kante_h;
    QString kante_l;
    QString kante_r;
    //-------------------------------------------
    if(format == "fmc")
    {
        if(b < Schwellenwert_ay)
        {
            versatz_y = 210;
        }
        kante_v = kante_vo(drehwinkel);
        kante_h = kante_hi(drehwinkel);
        kante_l = kante_li(drehwinkel);
        kante_r = kante_re(drehwinkel);
    }else if(format == "ganx")
    {
        kante_v = kante_vo_ganx(drehwinkel);
        kante_h = kante_hi_ganx(drehwinkel);
        kante_l = kante_li_ganx(drehwinkel);
        kante_r = kante_re_ganx(drehwinkel);
    }else if(format == "ggf" || format == "eigen")
    {
        kante_v = kante_vo(drehwinkel);
        kante_h = kante_hi(drehwinkel);
        kante_l = kante_li(drehwinkel);
        kante_r = kante_re(drehwinkel);
    }else if(format == "cix")
    {
        kante_v = kante_vo(drehwinkel);
        kante_h = kante_hi(drehwinkel);
        kante_l = kante_li(drehwinkel);
        kante_r = kante_re(drehwinkel);
    }
    //-------------------------------------------
    if(use_ax() == false)
    {
        versatz_x = 0;
    }
    if(use_ay() == false)
    {
        versatz_y = 0;
    }
    Versatz_y.append(versatz_y);
    Geotext.append(geo_ermitteln(tmp_bearb, l, b, d, \
                                 kante_v, kante_h, kante_l, kante_r,\
                                 versatz_x, versatz_y, Wkzm.at(index)));
    GeoFkon.append(geofkon_ermitteln(tmp_bearb, versatz_x, versatz_y, Wkzm.at(index)));
}





