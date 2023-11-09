#include "werkstueck.h"

werkstueck::werkstueck()
{
    Laenge  = 0;
    Breite  = 0;
    Dicke   = 0;
    Gut_ist_oben = true;
}
werkstueck::werkstueck(QString neuer_name)
{
    Name    = neuer_name;
    Laenge  = 0;
    Breite  = 0;
    Dicke   = 0;
    Gut_ist_oben = true;
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

    for(uint i=0; i<Bearb.count() ;i++)
    {
        if(Bearb.at(i) == text)
        {
            text_zw zeile;//Folgezeile
            zeile.set_text(text, TRENNZ_BEARB_PARAM);
            if(zeile.at(0) == BEARBART_BOHR)//Nur doppelte Bohrungen unterdrücken, Doppelte Fräsbahnen können gewollt sein!
            {
                bereits_vorhanden = true;
                break;
            }
        }
    }

    if(bereits_vorhanden == false)
    {
        Bearb.add_hi(text);
    }
    gute_seite_ermitteln();
}
void werkstueck::set_bearb(text_zw b)
{
    Bearb = b;
    gute_seite_ermitteln();
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
void werkstueck::set_zustand(QString format, wkz_magazin* wkzmag, QString drehung, \
                             bool formartierungen_aufbrechen, QString zust_fkon, \
                             bool gut_ist_oben)
{
    Zustand.set_bearb(Bearb);
    Zustand.set_laenge(laenge());
    Zustand.set_breite(breite());
    Zustand.set_dicke(dicke());
    Zustand.set_kante_vo(Kante_vo);
    Zustand.set_kante_hi(Kante_hi);
    Zustand.set_kante_li(Kante_li);
    Zustand.set_kante_re(Kante_re);
    Zustand.set_zugabe_gehrungen(Zugabe_gehrungen);
    Zustand.set_formartierungen_aufbrechen(formartierungen_aufbrechen);
    Zustand.set_name(name());
    Zustand.set_zust_fkon(zust_fkon);
    Zustand.set_gute_seite(gut_ist_oben);
    Zustand.anfordern(format, *wkzmag, drehung);
}
void werkstueck::set_einstellung_ganx(einstellung_ganx e)
{
    Zustand.set_einst_ganx(e);
}
void werkstueck::set_use_ax(bool benutzen)
{
    Zustand.set_use_ax(benutzen);
}
void werkstueck::set_use_ay(bool benutzen)
{
    Zustand.set_use_ay(benutzen);
}
//--------------------------------------------------get_xy:

QString werkstueck::cad_fehler(bool kurz)
{
    QString msg;
    if(Name.contains("Tuer") || \
       Name.contains("Tur")      )
    {
        uint anz_asd = 0; //Anzahl Aufschlagdämpfer

        for(uint i=0; i<Bearb.count() ;i++)
        {
            if(Bearb.at(i).contains(BEARBART_BOHR))
            {
                bohrung bo(Bearb.at(i));
                if(bo.dm() == 6 && bo.tiefe() < dicke())
                {
                    anz_asd++;
                }
            }
        }
        if(anz_asd < 2)
        {
            if(kurz)
            {
                if(!msg.isEmpty())
                {
                    msg += " / ";
                }
                msg += double_to_qstring(anz_asd);
                msg += " Aufschlagdämpfer";
            }else
            {
                msg += name();
                msg += ": ";
                msg += double_to_qstring(anz_asd);
                msg += " Aufschlagdämpfer";
                msg += "\n";
            }
        }
    }
    if(Name.contains("SchubFront") || \
       Name.contains("Schubfront")      )
    {
        uint anz_asd = 0; //Anzahl Aufschlagdämpfer

        for(uint i=0; i<Bearb.count() ;i++)
        {
            if(Bearb.at(i).contains(BEARBART_BOHR))
            {
                bohrung bo(Bearb.at(i));
                if(bo.dm() == 6 && bo.tiefe() < dicke())
                {
                    anz_asd++;
                }
            }
        }
        if(anz_asd < 4)
        {
            if(kurz)
            {
                if(!msg.isEmpty())
                {
                    msg += " / ";
                }
                msg += double_to_qstring(anz_asd);
                msg += " Aufschlagdämpfer";
            }else
            {
                msg += name();
                msg += ": ";
                msg += double_to_qstring(anz_asd);
                msg += " Aufschlagdämpfer";
                msg += "\n";
            }
        }
    }
    return msg;
}
double werkstueck::max_x(QString format)
{
    if(drehung()=="0" | drehung()=="180")
    {
        if(format == "ganx")
        {
            return breite()+25;
        }else
        {
            return laenge()+25;
        }
    }else
    {
        if(format == "ganx")
        {
            return laenge()+25;
        }else
        {
            return breite()+25;
        }
    }
    //Drehung "AUTO" kann hier nicht korrekt verarbeitet werden, muss aber auch nicht
}
double werkstueck::max_x()
{
    return zustand().l()+25;
}
double werkstueck::max_x_einzelwst()
{
    return laenge()+25;
}
double werkstueck::min_x(QString format)
{
    return 0-25;
}
double werkstueck::min_x()
{
    return 0-25;
}
double werkstueck::max_y(QString format)
{
    if(drehung()=="0" | drehung()=="180")
    {
        if(format == "ganx")
        {
            return laenge()+25+ay();
        }else
        {
            return breite()+25+ay();
        }
    }else
    {
        if(format == "ganx")
        {
            return breite()+25+ay();
        }else
        {
            return laenge()+25+ay();
        }
    }
    //Drehung "AUTO" kann hier nicht korrekt verarbeitet werden, muss aber auch nicht
}
double werkstueck::max_y()
{
    return zustand().b()+25+ay();
}
double werkstueck::max_y_einzelwst()
{
    return breite()+25+ay();
}
double werkstueck::min_y(QString format)
{
    return 0-25;
}
double werkstueck::min_y()
{
    return 0-25;
}
geo_text werkstueck::geo(wkz_magazin wkzm)
{
    double versatz_x = 0;
    double versatz_y = 0;
    QString kante_v = kante_vo();
    QString kante_h = kante_hi();
    QString kante_l = kante_li();
    QString kante_r = kante_re();
    //-------------------------------------------
    return geo_ermitteln(Bearb, Laenge, Breite, Dicke, \
                         kante_v, kante_h, kante_l, kante_r,\
                         versatz_x, versatz_y, wkzm);
}
geo_text werkstueck::geofkon(wkz_magazin wkzm)
{
    double versatz_x = 0;
    double versatz_y = 0;
    //-------------------------------------------
    return geofkon_ermitteln(Bearb, versatz_x, versatz_y, wkzm);
}

//--------------------------------------------------Manipulationen:
void werkstueck::gute_seite_ermitteln()
{
    bool retwert = true;
    if(Name.contains("Seite"))
    {
        bool hat_5er_durchgangsbohrungen = false;
        text_zw zeile;
        for(uint i=0; i<Bearb.count() ;i++)
        {
            zeile.set_text(Bearb.at(i),TRENNZ_BEARB_PARAM);
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
            retwert = true;
        }else
        {
            retwert = false;
        }
    }else if(Name.contains("MS"))
    {
        retwert = true;
    }else if(Name.contains("OB"))
    {
        retwert = true;
    }else if(Name.contains("UB"))
    {
        int anz_obsei = 0;
        int anz_unsei = 0;
        text_zw zeile;
        for(uint i=0; i<Bearb.count() ;i++)
        {
            zeile.set_text(Bearb.at(i),TRENNZ_BEARB_PARAM);
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
            retwert = false;
        }else
        {
            retwert = true;
        }
    }else if(Name.contains("KB"))
    {
        retwert = false;
    }else if(Name.contains("EB"))
    {
        retwert = false;
    }else if(Name.contains("RW"))
    {
        retwert = false;//Wert wird ggf. weiter unten überschrieben
        bool hat_5er_durchgangsbohrungen = false;
        bool hat_8er_flaechenbohrungen_obsei = false;
        text_zw zeile;
        for(uint i=0; i<Bearb.count() ;i++)
        {
            zeile.set_text(Bearb.at(i),TRENNZ_BEARB_PARAM);
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
                retwert = true;
            }
        }
    }else if(Name.contains("Tuer"))
    {
        retwert = false;
    }else if(Name.contains("Front") || Name.contains("front"))
    {
        retwert = false;
    }else if(Name.contains("Blende") || Name.contains("blende"))
    {
        retwert = false;
    }else if(Name.contains("Doppel") || Name.contains("doppel"))
    {
        retwert = false;
    }else if(Name.contains("Paneel") || Name.contains("paneel"))
    {
        retwert = false;
    }else if(Name.contains("SF"))
    {
        retwert = false;
    }else if(Name.contains("SB"))
    {
        retwert = false;
    }
    Gut_ist_oben = retwert;    
}








