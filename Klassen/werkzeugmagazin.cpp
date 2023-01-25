#include "werkzeugmagazin.h"

werkzeugmagazin::werkzeugmagazin()
{

}
werkzeugmagazin::werkzeugmagazin(text_zeilenweise neues_magazin)
{
    Magazin = neues_magazin;
}

QString werkzeugmagazin::wkznummer(QString wkz_typ, \
                                       double dm, \
                                       double bearbeitungstiefe, \
                                       double werkstueckdicke, \
                                       QString bezugskante)
{
    QString returntext = "";
    text_zeilenweise zeile;
    zeile.set_trennzeichen('\t');
    double wkz_dm_tmp = 0;

    for(uint i = 2; i<=Magazin.zeilenanzahl() ;i++)
    {
        zeile.set_text(Magazin.zeile(i));
        if(zeile.zeile(15) == "1")//WKZ ist aktiv
        {
            if(  (zeile.zeile(1) == wkz_typ)  &&  (wkz_typ == WKZ_TYP_BOHRER)  )
            {
                if(zeile.zeile(7).toDouble() == dm)//Durchmesser aus Import == gesuchter DM?
                {
                    if(bezugskante == WST_BEZUG_OBSEI || \
                       bezugskante == WST_BEZUG_UNSEI)
                    {
                        if(zeile.zeile(4).toDouble() > bearbeitungstiefe)//Nutzlänge > Bohrtiefe?
                        {
                            if(bearbeitungstiefe >= werkstueckdicke || ((bearbeitungstiefe == 2)&&(dm == 5)))//Tiefe 2mm == Ankörnungen
                            {
                                if(zeile.zeile(8) == "1")//ist Durchgangsbohrer?
                                {
                                    if(zeile.zeile(10) == WKZ_PARAMETER_LAGE_VERT)//ist ein vertikaler Bohrer
                                    {
                                        returntext = zeile.zeile(2);
                                    }
                                }
                            }else
                            {
                                if(zeile.zeile(10) == WKZ_PARAMETER_LAGE_VERT)//ist ein vertikaler Bohrer
                                {
                                    //nur Nicht-Durchgangsbohrer zulassen:
                                    if(zeile.zeile(8) == "0")//ist Durchgangsbohrer?
                                    {
                                        returntext = zeile.zeile(2);
                                    }
                                }
                            }
                        }
                    }else
                    {
                        if(zeile.zeile(4).toDouble() > bearbeitungstiefe)//Nutzlänge > Bohrtiefe?
                        {
                            if(zeile.zeile(10) == WKZ_PARAMETER_LAGE_HORI)//ist ein horizontaler Bohrer
                            {
                                returntext = zeile.zeile(2);
                            }
                        }
                    }
                }
            }else if(  (zeile.zeile(1) == wkz_typ)  &&  (wkz_typ == WKZ_TYP_SAEGE)  )
            {
                if(bezugskante == WST_BEZUG_OBSEI || \
                   bezugskante == WST_BEZUG_UNSEI)
                {
                    if(zeile.zeile(17) == "1")//vertikale Säge
                    {
                        returntext = zeile.zeile(2);
                    }
                }else
                {
                    if(zeile.zeile(16) == "1")//horizontale Säge
                    {
                        returntext = zeile.zeile(2);
                    }
                }

            }else if(  (zeile.zeile(1) == wkz_typ)  &&  (wkz_typ == WKZ_TYP_FRAESER)  )
            {
                double wkz_dm = zeile.zeile(3).toDouble();
                if(  (wkz_dm <= dm-4)  &&  (wkz_dm > wkz_dm_tmp)  )
                {
                    if(zeile.zeile(4).toDouble() > bearbeitungstiefe)
                    {
                        if(zeile.zeile(14) != "ja") //ist nicht nur direkt zuweisbar
                        {
                            wkz_dm_tmp = wkz_dm;
                            returntext = zeile.zeile(2);
                        }
                    }
                }
            }
        }
    }
    //Suchen, ob es einen passenden durchgangsbohrer gibt, wo wir keinen Nicht-Durchgangsbohrer haben:
    if(returntext.isEmpty())
    {
        wkz_dm_tmp = 0;
        for(uint i = 2; i<=Magazin.zeilenanzahl() ;i++)
        {
            zeile.set_text(Magazin.zeile(i));
            if(zeile.zeile(15) == "1")//WKZ ist aktiv
            {
                if(  (zeile.zeile(1) == wkz_typ)  &&  (wkz_typ == WKZ_TYP_BOHRER)  )
                {
                    if(zeile.zeile(7).toDouble() == dm)//Durchmesser aus Import == gesuchter DM?
                    {
                        if(bezugskante == WST_BEZUG_OBSEI || \
                           bezugskante == WST_BEZUG_UNSEI)
                        {
                            if(zeile.zeile(4).toDouble() > bearbeitungstiefe)//Nutzlänge > Bohrtiefe?
                            {
                                if(zeile.zeile(10) == WKZ_PARAMETER_LAGE_VERT)//ist ein vertikaler Bohrer
                                {
                                    if(zeile.zeile(8) == "1")//ist Durchgangsbohrer?
                                    {
                                        returntext = zeile.zeile(2);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if(returntext.isEmpty())
    {
        wkz_dm_tmp = 0;
        for(uint i = 2; i<=Magazin.zeilenanzahl() ;i++)
        {
            zeile.set_text(Magazin.zeile(i));
            if(zeile.zeile(15) == "1")//WKZ ist aktiv
            {
                if(  (zeile.zeile(1) == wkz_typ)  &&  (wkz_typ == WKZ_TYP_FRAESER)  )
                {
                    double wkz_dm = zeile.zeile(3).toDouble();
                    if(  (wkz_dm <= dm-1)  &&  (wkz_dm > wkz_dm_tmp)  )
                    {
                        if(zeile.zeile(4).toDouble() > bearbeitungstiefe)
                        {
                            if(zeile.zeile(14) != "ja") //ist nicht nur direkt zuweisbar
                            {
                                wkz_dm_tmp = wkz_dm;
                                returntext = zeile.zeile(2);
                            }
                        }
                    }
                }
            }
        }
    }

    return returntext;
}
QString werkzeugmagazin::wkznummer_von_alias(QString alias)
{
    QString returntext = "";
    text_zeilenweise zeile;
    zeile.set_trennzeichen('\t');

    for(uint i = 2; i<Magazin.zeilenanzahl() ;i++)//i<.. und nicht i<=... weil letzte Zeile nur \n enthällt
    {
        zeile.set_text(Magazin.zeile(i));
        if(zeile.zeile(15) == "1")//WKZ ist aktiv
        {
            if(  (zeile.zeile(11) == alias) &&  !zeile.zeile(11).isEmpty()  )
            {
                if(zeile.zeile(1) == WKZ_TYP_FRAESER)
                {
                    returntext = zeile.zeile(2);
                    break;
                }
            }
        }
    }
    return returntext;
}

QString werkzeugmagazin::dm(QString wkz_nr)
{
    QString returntext = "";
    text_zeilenweise zeile;
    zeile.set_trennzeichen('\t');

    for(uint i = 2; i<=Magazin.zeilenanzahl() ;i++)
    {
        zeile.set_text(Magazin.zeile(i));

        if(zeile.zeile(2) == wkz_nr)
        {
            returntext = zeile.zeile(3);
        }

    }
    returntext.replace(",",".");
    return returntext;
}

bool werkzeugmagazin::ist_dubo(QString wkz_nr)//Ist Durchgangsbohrer
{
    bool retbool = false;
    text_zeilenweise zeile;
    zeile.set_trennzeichen('\t');

    for(uint i = 2; i<=Magazin.zeilenanzahl() ;i++)
    {
        zeile.set_text(Magazin.zeile(i));

        if(zeile.zeile(2) == wkz_nr)
        {
            if(zeile.zeile(1) == "B")//WKZ-Typ Borer
            {
                if(zeile.zeile(8) == "1")//WKZ-Typ Borer
                {
                    retbool = true;
                }
            }
        }

    }
    return retbool;
}

QString werkzeugmagazin::vorschub(QString wkz_nr)
{
    QString returntext = "";
    text_zeilenweise zeile;
    zeile.set_trennzeichen('\t');

    for(uint i = 2; i<=Magazin.zeilenanzahl() ;i++)
    {
        zeile.set_text(Magazin.zeile(i));

        if(zeile.zeile(2) == wkz_nr)
        {
            returntext = zeile.zeile(5);
        }

    }
    returntext.replace(",",".");
    return returntext;
}
QString werkzeugmagazin::zustellmass(QString wkz_nr)
{
    QString returntext = "";
    text_zeilenweise zeile;
    zeile.set_trennzeichen('\t');

    for(uint i = 2; i<=Magazin.zeilenanzahl() ;i++)
    {
        zeile.set_text(Magazin.zeile(i));

        if(zeile.zeile(2) == wkz_nr)
        {
            returntext = zeile.zeile(6);
        }

    }
    returntext.replace(",",".");
    return returntext;
}
QString werkzeugmagazin::zustellmass_min(QString wkz_nr)
{
    QString returntext = "";
    text_zeilenweise zeile;
    zeile.set_trennzeichen('\t');

    for(uint i = 2; i<=Magazin.zeilenanzahl() ;i++)
    {
        zeile.set_text(Magazin.zeile(i));

        if(zeile.zeile(2) == wkz_nr)
        {
            returntext = zeile.zeile(12);
        }

    }
    returntext.replace(",",".");
    return returntext;
}
QString werkzeugmagazin::tabellenkopf()
{
    QString tmp;

    tmp += "Typ";
    tmp += "\t";
    tmp += "Nr";
    tmp += "\t";
    tmp += "DM";
    tmp += "\t";
    tmp += "Nutzl";
    tmp += "\t";
    tmp += "Vorschub";
    tmp += "\t";
    tmp += "Zustellm";
    tmp += "\t";
    tmp += "DM_CAD";
    tmp += "\t";
    tmp += "DoBor";
    tmp += "\t";
    tmp += "Saegebr";
    tmp += "\t";
    tmp += "Lage";
    tmp += "\t";
    tmp += "Alias";
    tmp += "\t";
    tmp += "MindZust";
    tmp += "\t";
    tmp += "SpiegelWKZ";
    tmp += "\t";
    tmp += "nur direkt zuweisbar";
    tmp += "\t";

    tmp += " ";
    tmp += "\n";
    tmp += " ";

    return tmp;
}
QString werkzeugmagazin::saegeblattbreite(QString wkz_nr)
{
    QString returntext = "";
    text_zeilenweise zeile;
    zeile.set_trennzeichen('\t');

    for(uint i = 2; i<=Magazin.zeilenanzahl() ;i++)
    {
        zeile.set_text(Magazin.zeile(i));

        if(zeile.zeile(2) == wkz_nr)
        {
            returntext = zeile.zeile(9);
        }

    }
    returntext.replace(",",".");
    return returntext;
}
QString werkzeugmagazin::nutzlaenge(QString wkz_nr)
{
    QString returntext = "";
    text_zeilenweise zeile;
    zeile.set_trennzeichen('\t');

    for(uint i = 2; i<=Magazin.zeilenanzahl() ;i++)
    {
        zeile.set_text(Magazin.zeile(i));

        if(zeile.zeile(2) == wkz_nr)
        {
            returntext = zeile.zeile(4);
        }

    }
    returntext.replace(",",".");
    return returntext;
}
QString werkzeugmagazin::spiegelwkz(QString wkz_nr)
{
    QString returntext = "";
    text_zeilenweise zeile;
    zeile.set_trennzeichen('\t');

    for(uint i = 2; i<=Magazin.zeilenanzahl() ;i++)
    {
        zeile.set_text(Magazin.zeile(i));

        if(zeile.zeile(2) == wkz_nr)
        {
            returntext = zeile.zeile(13);
        }

    }
    return returntext;
}

text_zeilenweise werkzeugmagazin::alle_bodm(QString hori_oder_vert)
{
    text_zeilenweise tz;


    for(uint i=2; i<=Magazin.zeilenanzahl() ;i++)//Zeile 1 ist Tabellenkopf
    {
        text_zeilenweise werkzeug;
        werkzeug.set_text(Magazin.zeile(i));

        text_zeilenweise parameter;
        parameter.set_trennzeichen('\t');
        parameter.set_text(werkzeug.text());

        if(parameter.zeile(1) == WKZ_TYP_BOHRER)
        {
            if(parameter.zeile(10) == hori_oder_vert)
            {
                tz.zeile_anhaengen(parameter.zeile(7));//dm aus Import
            }
        }
    }
    return tz;
}




//-------------------Funktionen nicht innerhalb der Klasse:
bool operator ==(werkzeugmagazin w1, werkzeugmagazin w2)
{
    if(w1.magazin().text() == w2.magazin().text())
    {
        return true;
    }else
    {
        return false;
    }
}
bool operator !=(werkzeugmagazin w1, werkzeugmagazin w2)
{
    if(w1.magazin().text() == w2.magazin().text())
    {
        return false;
    }else
    {
        return true;
    }
}





