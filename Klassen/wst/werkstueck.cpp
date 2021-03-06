#include "werkstueck.h"

werkstueck::werkstueck()
{
    Laenge  = 0;
    Breite  = 0;
    Dicke   = 0;
}
werkstueck::werkstueck(QString neuer_name)
{
    Name    = neuer_name;
    Laenge  = 0;
    Breite  = 0;
    Dicke   = 0;
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
void werkstueck::set_zustand(QString format, text_zeilenweise wkzmag, QString drehung, \
                             bool formartierungen_aufbrechen, QString zust_fkon)
{
    Zustand.set_bearb(Bearbeitungen);
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
    Zustand.anfordern(format, wkzmag, drehung);
}
void werkstueck::set_einstellung_ganx(einstellung_ganx e)
{
    Zustand.set_einst_ganx(e);
}
//--------------------------------------------------get_xy:

QString werkstueck::cad_fehler(bool kurz)
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
double werkstueck::min_x(QString format)
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
double werkstueck::min_y(QString format)
{
    return 0-25;
}

