#include "werkstuecke.h"


werkstuecke::werkstuecke()
{

}

//---------------------------------------------------------------allgemeine Funktionen:
bool werkstuecke::ist_bekannt(QString Werkstueckname)
{
    for(uint i=1; i<=namen.zeilenanzahl() ;i++)
    {
        if(Werkstueckname == namen.zeile(i))
        {
            return true;
        }
    }
    return false;
}
bool werkstuecke::neu(QString Werkstueckname, QString Quellformat)
{
    if(ist_bekannt(Werkstueckname))
    {
        return true;//FEHLER, der Teil gibt es bereits!!!
    }else
    {
        namen.zeile_anhaengen(Werkstueckname);
        quellformate.zeile_anhaengen(Quellformat);
        werkstueck w;
        wste.append(w);
    }
    return false;
}
void werkstuecke::clear()
{
    namen.clear();
    quellformate.clear();
    wste.clear();
}
uint werkstuecke::get_index(QString Werkstueckname)
{
    for(uint i=1; i<=namen.zeilenanzahl() ;i++)
    {
        if(namen.zeile(i)==Werkstueckname)
        {
            return i;
        }
    }
    return 0; //Wenn der Name nicht gefunden wurde
}
QString werkstuecke::wert_nach_istgleich(QString text)
{
    if(text.contains("="))
    {
        if(text.contains("\n"))
        {
            return text_mitte(text, "=", "\n");
        }else
        {
            return text_rechts(text, "=");
        }
    }else
    {
        return "";
    }
}
werkstueck werkstuecke::get_wst(uint index)
{
    if(index > 0 && index <= namen.zeilenanzahl())
    {
        return wste.at(index-1);
    }else
    {
        werkstueck w;   //leeres Wst
        return w;
    }
}
QString werkstuecke::get_name(uint index)
{
    if(index > 0 && index <= namen.zeilenanzahl())
    {
        return namen.zeile(index);
    }else
    {
        return "";
    }
}

//---------------------------------------------------------------Import-Funktionen:
bool werkstuecke::import_fmc_oberseite(QString Werkstueckname, QString importtext)
{
    uint index = get_index(Werkstueckname);
    if(index == 0)
    {
        neu(Werkstueckname, FMC);
        index = get_index(Werkstueckname);
    }
    text_zeilenweise tz;
    tz.set_text(importtext);

    werkstueck w = wste.at(index-1);

    for(uint i=1; i<=tz.zeilenanzahl() ;i++)
    {
        QString zeile = tz.zeile(i);
        if(zeile.contains(FMC_PRGKOPF))
        {
            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii;
                    break;
                }else
                {
                    if(zeile.contains(FMC_PRGKOPF_LAENGE))
                    { 
                        w.set_laenge(wert_nach_istgleich(zeile));
                    }else if(zeile.contains(FMC_PRGKOPF_BREITE))
                    {
                        w.set_breite(wert_nach_istgleich(zeile));
                    }else if(zeile.contains(FMC_PRGKOPF_DICKE))
                    {
                        w.set_dicke(wert_nach_istgleich(zeile));
                    }                    
                }
            }
        }else if(zeile.contains(FMC_BOHR_DM))
        {
            bohrung bo;
            bo.set_bezug(WST_BEZUG_OBSEI);

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii;
                    w.neue_bearbeitung(bo.get_text());
                    break;
                }else
                {                    
                    if(zeile.contains(FMC_BOHR_DM_AFB))
                    {
                        bo.set_afb(wert_nach_istgleich(zeile));
                    }else if(zeile.contains(FMC_BOHR_DM_DM))
                    {
                        bo.set_dm(wert_nach_istgleich(zeile));
                    }else if(zeile.contains(FMC_BOHR_DM_TIEFE))
                    {
                        bo.set_tiefe(wert_nach_istgleich(zeile));
                    }else if(zeile.contains(FMC_BOHR_DM_X))
                    {
                        bo.set_x(wert_nach_istgleich(zeile));
                    }else if(zeile.contains(FMC_BOHR_DM_Y))
                    {
                        bo.set_y(wert_nach_istgleich(zeile));
                    }
                }
            }
        }
    }

    wste.replace(index-1, w);

    return 0;
}

bool werkstuecke::import_fmc_unterseite(QString Werkstueckname, QString importtext)
{
    uint index = get_index(Werkstueckname);
    if(index == 0)
    {
        return 1;   //Die Bearbeitung soll nur auf die Unterseite importiert werden,
                    //wenn bereits die Bearbeitung auf der Oberseite importiert wurde
    }
    text_zeilenweise tz;
    tz.set_text(importtext);

    werkstueck w = wste.at(index-1);

    for(uint i=1; i<=tz.zeilenanzahl() ;i++)
    {
        QString zeile = tz.zeile(i);

        if(zeile.contains(FMC_BOHR_DM))
        {
            bohrung bo;
            bo.set_bezug(WST_BEZUG_UNSEI);

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii;
                    w.neue_bearbeitung(bo.get_text());
                    break;
                }else
                {
                    if(zeile.contains(FMC_BOHR_DM_AFB))
                    {
                        bo.set_afb(wert_nach_istgleich(zeile));
                    }else if(zeile.contains(FMC_BOHR_DM_DM))
                    {
                        bo.set_dm(wert_nach_istgleich(zeile));
                    }else if(zeile.contains(FMC_BOHR_DM_TIEFE))
                    {
                        bo.set_tiefe(wert_nach_istgleich(zeile));
                    }else if(zeile.contains(FMC_BOHR_DM_X))
                    {
                        double x = ausdruck_auswerten(wert_nach_istgleich(zeile)).toDouble();
                        x = w.get_laenge()-x;
                        bo.set_x(x);
                    }else if(zeile.contains(FMC_BOHR_DM_Y))
                    {
                        bo.set_y(wert_nach_istgleich(zeile));
                    }
                }
            }
        }
    }

    wste.replace(index-1, w);

    return 0;
}




