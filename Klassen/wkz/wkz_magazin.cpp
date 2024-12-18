#include "wkz_magazin.h"

wkz_magazin::wkz_magazin()
{

}
wkz_magazin::wkz_magazin(text_zw neues_magazin)
{
    set_text(neues_magazin);
}
//----------------------------------set:
void wkz_magazin::set_text(QString werkzeuge)
{
    Magazin.set_text(werkzeuge,'\n');
}
void wkz_magazin::set_text(text_zw werkzeuge)
{
    Magazin = werkzeuge;
}
void wkz_magazin::add_fraeser(QString f)
{
    bool bekannt = false;
    for(uint i=0; i<Magazin.count();i++)
    {
        if(Magazin.at(i) == f)
        {
            bekannt = true;
            break;
        }
    }
    if(bekannt == false)
    {
        Magazin.add_hi(f);
    }
}
//----------------------------------get:
text_zw *wkz_magazin::magazin_ptr()
{
    return &Magazin;
}
text_zw wkz_magazin::magazin()
{
    return Magazin;
}
QString wkz_magazin::text()
{
    return Magazin.text();
}
QString wkz_magazin::wkznummer(QString wkz_typ, \
                               double dm, \
                               double bearbeitungstiefe, \
                               double werkstueckdicke, \
                               QString bezugskante)
{
    //1. Suchdurchlauf:
    double wkz_dm_tmp = 0;
    for(uint i=0; i<Magazin.count();i++)
    {
        text_zw zeile;
        zeile.set_text(Magazin.at(i), WKZ_TRENNZ);
        if(istaktiv(zeile))
        {
            if(typ(zeile) == wkz_typ  &&  (wkz_typ == WKZ_TYP_BOHRER))
            {
                wkz_bohrer borer(zeile);
                if(borer.dmimport() == dm)
                {
                    if(bezugskante == WST_BEZUG_OBSEI || \
                       bezugskante == WST_BEZUG_UNSEI)
                    {
                        if(borer.nutzl() > bearbeitungstiefe)
                        {
                            if(bearbeitungstiefe >= werkstueckdicke || ((bearbeitungstiefe == 2)&&(dm == 5)))//Tiefe 2mm == Ankörnungen
                            {                                
                                if(borer.istdubo() == true)
                                {
                                    if(borer.istverti())
                                    {
                                        return borer.wkznr();
                                    }
                                }
                            }else
                            {
                                if(borer.istverti())
                                {
                                    if(borer.istdubo() == false)
                                    {
                                        return borer.wkznr();
                                    }
                                }
                            }
                        }
                    }else
                    {
                        if(borer.nutzl() > bearbeitungstiefe)
                        {
                            if(borer.isthori())
                            {
                                return borer.wkznr();
                            }
                        }
                    }
                }
            }else if(  typ(zeile) == wkz_typ  &&  (wkz_typ == WKZ_TYP_SAEGE)  )
            {
                wkz_saege saege(zeile);
                if(bezugskante == WST_BEZUG_OBSEI || \
                   bezugskante == WST_BEZUG_UNSEI)
                {
                    if(saege.istverti())
                    {
                        return saege.wkznr();
                    }
                }else
                {
                    if(saege.isthori())
                    {
                        return saege.wkznr();
                    }
                }
            }else if(  typ(zeile) == wkz_typ  &&  (wkz_typ == WKZ_TYP_FRAESER)  )
            {
                wkz_fraeser fraeser(zeile);
                double wkz_dm = fraeser.dm();
                if(  (wkz_dm <= dm-4)  &&  (wkz_dm > wkz_dm_tmp)  )
                {
                    if(fraeser.nutzl() > bearbeitungstiefe)
                    {
                        if(fraeser.nurdirektzuw() == false) //ist nicht nur direkt zuweisbar
                        {
                            wkz_dm_tmp = wkz_dm;
                            return fraeser.wkznr();
                        }
                    }
                }
            }
        }
    }
    //2. Suchdurchlauf:
    //Suchen, ob es einen passenden durchgangsbohrer gibt, wo wir keinen Nicht-Durchgangsbohrer haben:
    wkz_dm_tmp = 0;
    for(uint i=0; i<Magazin.count();i++)
    {
        text_zw zeile;
        zeile.set_text(Magazin.at(i), WKZ_TRENNZ);
        if(istaktiv(zeile))
        {
            if(typ(zeile) == wkz_typ  &&  (wkz_typ == WKZ_TYP_BOHRER))
            {
                wkz_bohrer borer(zeile);
                if(borer.dmimport() == dm)
                {
                    if(bezugskante == WST_BEZUG_OBSEI || \
                       bezugskante == WST_BEZUG_UNSEI)
                    {
                        if(borer.nutzl() > bearbeitungstiefe)
                        {
                            if(borer.istverti())
                            {
                                if(borer.istdubo())
                                {
                                    return borer.wkznr();
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    //3. Suchdurchlauf:
    wkz_dm_tmp = 0;
    for(uint i=0; i<Magazin.count();i++)
    {
        text_zw zeile;
        zeile.set_text(Magazin.at(i), WKZ_TRENNZ);
        if(istaktiv(zeile))
        {
            if(  typ(zeile) == wkz_typ  &&  (wkz_typ == WKZ_TYP_FRAESER)  )
            {
                wkz_fraeser fraeser(zeile);
                double wkz_dm = fraeser.dm();
                if(  (wkz_dm <= dm-1)  &&  (wkz_dm > wkz_dm_tmp)  )
                {
                    if(fraeser.nutzl() > bearbeitungstiefe)
                    {
                        if(fraeser.nurdirektzuw() == false) //ist nicht nur direkt zuweisbar
                        {
                            wkz_dm_tmp = wkz_dm;
                            return fraeser.wkznr();
                        }
                    }
                }
            }
        }
    }
    //Hier kommen wir nur an wenn kein passendes Werkzeug gefunden wurde:
    return "";
}
QString wkz_magazin::wkznummer_von_alias(QString alias, QString lage)
{
    alias.replace("void", "");
    if(alias.isEmpty())
    {
        return "";
    }
    for(uint i=0; i<Magazin.count();i++)
    {
        text_zw zeile;
        zeile.set_text(Magazin.at(i), WKZ_TRENNZ);
        if(istaktiv(zeile))
        {
            if(  typ(zeile) == WKZ_TYP_FRAESER  )
            {
                wkz_fraeser fraeser(zeile);
                if(fraeser.alias() == alias)
                {
                    if(lage == WKZ_VERT && fraeser.istverti())
                    {
                        return fraeser.wkznr();
                    }else if(lage == WKZ_HORI && fraeser.isthori())
                    {
                        return fraeser.wkznr();
                    }
                }
            }
        }
    }
    //Hier kommen wir nur an wenn kein passendes Werkzeug gefunden wurde:
    return "";
}
QString wkz_magazin::dm(QString wkz_nr)
{
    for(uint i=0; i<Magazin.count();i++)
    {
        text_zw zeile;
        zeile.set_text(Magazin.at(i), WKZ_TRENNZ);        
        if(typ(zeile) == WKZ_TYP_FRAESER)
        {
            wkz_fraeser fraeser(zeile);
            if(wkznr(zeile) == wkz_nr  ||  fraeser.alias() == wkz_nr)
            {
                return double_to_qstring(fraeser.dm());
            }
        }else if(typ(zeile) == WKZ_TYP_BOHRER)
        {
            if(wkznr(zeile) == wkz_nr)
            {
                wkz_bohrer bohrer(zeile);
                return double_to_qstring(bohrer.dmexport());
            }
        }else if(typ(zeile) == WKZ_TYP_SAEGE)
        {
            if(wkznr(zeile) == wkz_nr)
            {
                wkz_saege saege(zeile);
                return double_to_qstring(saege.dm());
            }
        }
    }
    //Hier kommen wir nur an wenn kein passendes Werkzeug gefunden wurde:
    return "0";
}
bool wkz_magazin::ist_dubo(QString wkz_nr)
{
    for(uint i=0; i<Magazin.count();i++)
    {
        text_zw zeile;
        zeile.set_text(Magazin.at(i), WKZ_TRENNZ);
        if(wkznr(zeile) == wkz_nr)
        {
            if(typ(zeile) == WKZ_TYP_BOHRER)
            {
                wkz_bohrer bohrer(zeile);
                return bohrer.istdubo();
            }
        }
    }
    //Hier kommen wir nur an wenn kein passendes Werkzeug gefunden wurde:
    return false;
}
QString wkz_magazin::vorschub(QString wkz_nr)
{
    for(uint i=0; i<Magazin.count();i++)
    {
        text_zw zeile;
        zeile.set_text(Magazin.at(i), WKZ_TRENNZ);
        if(wkznr(zeile) == wkz_nr)
        {
            if(typ(zeile) == WKZ_TYP_FRAESER)
            {
                wkz_fraeser fraeser(zeile);
                return double_to_qstring(fraeser.vorschub());
            }else if(typ(zeile) == WKZ_TYP_BOHRER)
            {
                //wkz_bohrer bohrer(zeile);
                //return double_to_qstring(...);
                return "0";
            }else if(typ(zeile) == WKZ_TYP_SAEGE)
            {
                //wkz_saege saege(zeile);
                //return double_to_qstring(...);
                return "0";
            }
        }
    }
    //Hier kommen wir nur an wenn kein passendes Werkzeug gefunden wurde:
    return "0";
}
QString wkz_magazin::zustmasvert(QString wkz_nr)
{
    for(uint i=0; i<Magazin.count();i++)
    {
        text_zw zeile;
        zeile.set_text(Magazin.at(i), WKZ_TRENNZ);
        if(wkznr(zeile) == wkz_nr)
        {
            if(typ(zeile) == WKZ_TYP_FRAESER)
            {
                wkz_fraeser fraeser(zeile);
                return double_to_qstring(fraeser.zustmavert());
            }else if(typ(zeile) == WKZ_TYP_BOHRER)
            {
                wkz_bohrer bohrer(zeile);
                return double_to_qstring(bohrer.zustmavert());
            }else if(typ(zeile) == WKZ_TYP_SAEGE)
            {
                wkz_saege saege(zeile);
                return double_to_qstring(saege.zustma());
            }
        }
    }
    //Hier kommen wir nur an wenn kein passendes Werkzeug gefunden wurde:
    return "0";
}
QString wkz_magazin::zustmashori(QString wkz_nr)
{
    for(uint i=0; i<Magazin.count();i++)
    {
        text_zw zeile;
        zeile.set_text(Magazin.at(i), WKZ_TRENNZ);
        if(wkznr(zeile) == wkz_nr)
        {
            if(typ(zeile) == WKZ_TYP_FRAESER)
            {
                wkz_fraeser fraeser(zeile);
                return double_to_qstring(fraeser.zustmahori());
            }else if(typ(zeile) == WKZ_TYP_BOHRER)
            {
                wkz_bohrer bohrer(zeile);
                return double_to_qstring(bohrer.zustmahori());
            }else if(typ(zeile) == WKZ_TYP_SAEGE)
            {
                wkz_saege saege(zeile);
                return double_to_qstring(saege.zustma());
            }
        }
    }
    //Hier kommen wir nur an wenn kein passendes Werkzeug gefunden wurde:
    return "0";
}
QString wkz_magazin::zustellmass_min(QString wkz_nr)
{
    for(uint i=0; i<Magazin.count();i++)
    {
        text_zw zeile;
        zeile.set_text(Magazin.at(i), WKZ_TRENNZ);
        if(wkznr(zeile) == wkz_nr)
        {
            if(typ(zeile) == WKZ_TYP_FRAESER)
            {
                wkz_fraeser fraeser(zeile);
                return double_to_qstring(fraeser.minzust());
            }else if(typ(zeile) == WKZ_TYP_BOHRER)
            {
                //wkz_bohrer bohrer(zeile);
                //return double_to_qstring(...);
                return "0";
            }else if(typ(zeile) == WKZ_TYP_SAEGE)
            {
                //wkz_saege saege(zeile);
                //return double_to_qstring(...);
                return "0";
            }
        }
    }
    //Hier kommen wir nur an wenn kein passendes Werkzeug gefunden wurde:
    return "0";
}
QString wkz_magazin::saegeblattbreite(QString wkz_nr)
{
    for(uint i=0; i<Magazin.count();i++)
    {
        text_zw zeile;
        zeile.set_text(Magazin.at(i), WKZ_TRENNZ);
        if(wkznr(zeile) == wkz_nr)
        {
            if(typ(zeile) == WKZ_TYP_SAEGE)
            {
                wkz_saege saege(zeile);
                return double_to_qstring(saege.sbreite());
            }
        }
    }
    //Hier kommen wir nur an wenn kein passendes Werkzeug gefunden wurde:
    return "0";
}
QString wkz_magazin::nutzlaenge(QString wkz_nr)
{
    for(uint i=0; i<Magazin.count();i++)
    {
        text_zw zeile;
        zeile.set_text(Magazin.at(i), WKZ_TRENNZ);
        if(wkznr(zeile) == wkz_nr)
        {
            if(typ(zeile) == WKZ_TYP_FRAESER)
            {
                wkz_fraeser fraeser(zeile);
                return double_to_qstring(fraeser.nutzl());
            }else if(typ(zeile) == WKZ_TYP_BOHRER)
            {
                wkz_bohrer bohrer(zeile);
                return double_to_qstring(bohrer.nutzl());
            }else if(typ(zeile) == WKZ_TYP_SAEGE)
            {
                //wkz_saege saege(zeile);
                //return double_to_qstring(...);
                return "0";
            }
        }
    }
    //Hier kommen wir nur an wenn kein passendes Werkzeug gefunden wurde:
    return "0";
}
text_zw wkz_magazin::alle_bodm_hori()
{
    text_zw tz;
    tz.set_trenz(WKZ_TRENNZ);
    for(uint i=0; i<Magazin.count();i++)
    {
        text_zw zeile;
        zeile.set_text(Magazin.at(i), WKZ_TRENNZ);
        if(istaktiv(zeile))
        {
            if(typ(zeile) == WKZ_TYP_BOHRER)
            {
                wkz_bohrer bohrer(zeile);
                if(bohrer.isthori())
                {
                    tz.add_hi(double_to_qstring(bohrer.dmimport()));
                }
            }
        }
    }
    return tz;
}
text_zw wkz_magazin::alle_bodm_verti()
{
    text_zw tz;
    tz.set_trenz(WKZ_TRENNZ);
    for(uint i=0; i<Magazin.count();i++)
    {
        text_zw zeile;
        zeile.set_text(Magazin.at(i), WKZ_TRENNZ);
        if(istaktiv(zeile))
        {
            if(typ(zeile) == WKZ_TYP_BOHRER)
            {
                wkz_bohrer bohrer(zeile);
                if(bohrer.istverti())
                {
                    tz.add_hi(double_to_qstring(bohrer.dmimport()));
                }
            }
        }
    }
    return tz;
}
text_zw wkz_magazin::alle_fraeser()
{
    text_zw mag;
    for(uint i=0; i<Magazin.count();i++)
    {
        text_zw zeile;
        zeile.set_text(Magazin.at(i), WKZ_TRENNZ);
        if(typ(zeile) == WKZ_TYP_FRAESER)
        {
            mag.add_hi(zeile.text());
        }
    }
    return mag;
}
QString wkz_magazin::spiegelwkz(QString wkz_nr)
{
    for(uint i=0; i<Magazin.count();i++)
    {
        text_zw zeile;
        zeile.set_text(Magazin.at(i), WKZ_TRENNZ);
        if(wkznr(zeile) == wkz_nr)
        {
            if(typ(zeile) == WKZ_TYP_FRAESER)
            {
                wkz_fraeser fraeser(zeile);
                return fraeser.spiegelwkz();
            }
        }
    }
    //Hier kommen wir nur an wenn kein passendes Werkzeug gefunden wurde:
    return "";
}
//----------------------------------manipulation:
void wkz_magazin::item_down(uint index)
{
    if(index+1 < Magazin.count())
    {
        QString tmp = Magazin.at(index);
        Magazin.entf(index);
        Magazin.add_mi(index, tmp);
    }
}
void wkz_magazin::item_up(uint index)
{
    if(index < Magazin.count() && index > 0)
    {
        QString tmp = Magazin.at(index);
        Magazin.entf(index);
        if(index == 1)
        {
            Magazin.add_vo(tmp);
        }else
        {
            Magazin.add_mi(index-2, tmp);
        }
    }
}
void wkz_magazin::entf(uint index)
{
    Magazin.entf(index);
}
//----------------------------------private get:
QString wkz_magazin::typ(text_zw wkz)
{
    //0: WKZ-Typ
    return wkz.at(0);
}
bool wkz_magazin::istaktiv(text_zw wkz)
{
    //2: Ist Aktiv
    if(wkz.at(2) == "1")
    {
        return true;
    }else
    {
        return false;
    }
}
QString wkz_magazin::wkznr(text_zw wkz)
{
    //1: Werkzeugnummer
    return wkz.at(1);
}
//----------------------------------

//-------------------Funktionen nicht innerhalb der Klasse:
bool operator ==(wkz_magazin w1, wkz_magazin w2)
{
    if(w1.magazin() == w2.magazin())
    {
        return true;
    }else
    {
        return false;
    }
}
bool operator !=(wkz_magazin w1, wkz_magazin w2)
{
    if(w1.magazin() != w2.magazin())
    {
        return true;
    }else
    {
        return false;
    }
}
