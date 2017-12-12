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
    for(uint i=1; i<=tz.zeilenanzahl() ;i++)
    {
        QString zeile = tz.zeile(i);
        if(zeile.contains(FMC_PRGKOPF))
        {
            for(uint ii=i; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(zeile == "\n")//Ende des Programmpopfes
                {
                    i=ii;
                    break;
                }else
                {
                    if(zeile.contains(FMC_PRGKOPF_LAENGE))
                    {
                        werkstueck w = wste.at(i-1);
                        w.set_laenge(wert_nach_istgleich(zeile));
                        wste.replace(i-1, w);
                    }else if(zeile.contains(FMC_PRGKOPF_BREITE))
                    {
                        werkstueck w = wste.at(i-1);
                        w.set_breite(wert_nach_istgleich(zeile));
                        wste.replace(i-1, w);
                    }else if(zeile.contains(FMC_PRGKOPF_DICKE))
                    {
                        werkstueck w = wste.at(i-1);
                        w.set_dicke(wert_nach_istgleich(zeile));
                        wste.replace(i-1, w);
                    }
                }
            }
        }
    }

    return 0;
}






