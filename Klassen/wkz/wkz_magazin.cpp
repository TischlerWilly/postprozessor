#include "wkz_magazin.h"

wkz_magazin::wkz_magazin()
{

}
wkz_magazin::wkz_magazin(text_zw neues_magazin)
{
    Magazin = neues_magazin;
}
//----------------------------------get:
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
        QString zeile = Magazin.at(i);
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
        QString zeile = Magazin.at(i);
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
        QString zeile = Magazin.at(i);
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
QString wkz_magazin::wkznummer_von_alias(QString alias)
{
    for(uint i=0; i<Magazin.count();i++)
    {
        QString zeile = Magazin.at(i);
        if(istaktiv(zeile))
        {
            if(  typ(zeile) == WKZ_TYP_FRAESER  )
            {
                wkz_fraeser fraeser(zeile);
                if(  fraeser.alias() == alias &&  !alias.isEmpty()  )
                {
                    return fraeser.wkznr();
                }
            }
        }
    }
    //Hier kommen wir nur an wenn kein passendes Werkzeug gefunden wurde:
    return "";
}

//----------------------------------private get:
QString wkz_magazin::typ(QString wkz)
{
    //0: WKZ-Typ
    text_zw wkz_tz(wkz, WKZ_TRENNZ);
    return wkz_tz.at(0);
}
bool wkz_magazin::istaktiv(QString wkz)
{
    //2: Ist Aktiv
    text_zw wkz_tz(wkz, WKZ_TRENNZ);
    if(wkz_tz.at(1) == "2")
    {
        return true;
    }else
    {
        return false;
    }
}
