#include "werkzeugmagazin.h"

werkzeugmagazin::werkzeugmagazin()
{

}
werkzeugmagazin::werkzeugmagazin(text_zeilenweise neues_magazin)
{
    magazin = neues_magazin;
}

QString werkzeugmagazin::get_wkznummer(QString wkz_typ, \
                                       double dm, \
                                       double bearbeitungstiefe, \
                                       double werkstueckdicke, \
                                       QString bezugskante)
{
    QString returntext = "";
    text_zeilenweise zeile;
    zeile.set_trennzeichen('\t');
    double wkz_dm_tmp = 0;

    for(uint i = 2; i<=magazin.zeilenanzahl() ;i++)
    {
        zeile.set_text(magazin.zeile(i));
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
            returntext = zeile.zeile(2);
        }else if(  (zeile.zeile(1) == wkz_typ)  &&  (wkz_typ == WKZ_TYP_FRAESER)  )
        {
            double wkz_dm = zeile.zeile(3).toDouble();
            if(  (wkz_dm <= dm-4)  &&  (wkz_dm > wkz_dm_tmp)  )
            {
                if(zeile.zeile(4).toDouble() > bearbeitungstiefe)
                {
                    wkz_dm_tmp = wkz_dm;
                    returntext = zeile.zeile(2);
                }
            }
        }
    }
    //Suchen, ob es einen passenden durchgangsbohrer gibt, wo wir keinen Nicht-Durchgangsbohrer haben:
    if(returntext.isEmpty())
    {
        wkz_dm_tmp = 0;
        for(uint i = 2; i<=magazin.zeilenanzahl() ;i++)
        {
            zeile.set_text(magazin.zeile(i));
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
                                returntext = zeile.zeile(2);
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
        for(uint i = 2; i<=magazin.zeilenanzahl() ;i++)
        {
            zeile.set_text(magazin.zeile(i));
            if(  (zeile.zeile(1) == wkz_typ)  &&  (wkz_typ == WKZ_TYP_FRAESER)  )
            {
                double wkz_dm = zeile.zeile(3).toDouble();
                if(  (wkz_dm <= dm-1)  &&  (wkz_dm > wkz_dm_tmp)  )
                {
                    if(zeile.zeile(4).toDouble() > bearbeitungstiefe)
                    {
                        wkz_dm_tmp = wkz_dm;
                        returntext = zeile.zeile(2);
                    }
                }
            }
        }
    }

    return returntext;
}
QString werkzeugmagazin::get_wkznummer_von_alias(QString alias)
{
    QString returntext = "";
    text_zeilenweise zeile;
    zeile.set_trennzeichen('\t');

    for(uint i = 2; i<magazin.zeilenanzahl() ;i++)//i<.. und nicht i<=... weil letzte Zeile nur \n enthällt
    {
        zeile.set_text(magazin.zeile(i));

        if(zeile.zeile(11) == alias)
        {
            if(zeile.zeile(1) == WKZ_TYP_FRAESER)
            {
                returntext = zeile.zeile(2);
                break;
            }
        }
    }
    return returntext;
}

QString werkzeugmagazin::get_dm(QString wkz_nr)
{
    QString returntext = "";
    text_zeilenweise zeile;
    zeile.set_trennzeichen('\t');

    for(uint i = 2; i<=magazin.zeilenanzahl() ;i++)
    {
        zeile.set_text(magazin.zeile(i));

        if(zeile.zeile(2) == wkz_nr)
        {
            returntext = zeile.zeile(3);
        }

    }
    returntext.replace(",",".");
    return returntext;
}
QString werkzeugmagazin::get_vorschub(QString wkz_nr)
{
    QString returntext = "";
    text_zeilenweise zeile;
    zeile.set_trennzeichen('\t');

    for(uint i = 2; i<=magazin.zeilenanzahl() ;i++)
    {
        zeile.set_text(magazin.zeile(i));

        if(zeile.zeile(2) == wkz_nr)
        {
            returntext = zeile.zeile(5);
        }

    }
    returntext.replace(",",".");
    return returntext;
}
QString werkzeugmagazin::get_zustellmass(QString wkz_nr)
{
    QString returntext = "";
    text_zeilenweise zeile;
    zeile.set_trennzeichen('\t');

    for(uint i = 2; i<=magazin.zeilenanzahl() ;i++)
    {
        zeile.set_text(magazin.zeile(i));

        if(zeile.zeile(2) == wkz_nr)
        {
            returntext = zeile.zeile(6);
        }

    }
    returntext.replace(",",".");
    return returntext;
}
QString werkzeugmagazin::get_zustellmass_min(QString wkz_nr)
{
    QString returntext = "";
    text_zeilenweise zeile;
    zeile.set_trennzeichen('\t');

    for(uint i = 2; i<=magazin.zeilenanzahl() ;i++)
    {
        zeile.set_text(magazin.zeile(i));

        if(zeile.zeile(2) == wkz_nr)
        {
            returntext = zeile.zeile(12);
        }

    }
    returntext.replace(",",".");
    return returntext;
}
QString werkzeugmagazin::get_tabellenkopf()
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

    tmp += " ";
    tmp += "\n";
    tmp += " ";

    return tmp;
}
QString werkzeugmagazin::get_saegeblattbreite(QString wkz_nr)
{
    QString returntext = "";
    text_zeilenweise zeile;
    zeile.set_trennzeichen('\t');

    for(uint i = 2; i<=magazin.zeilenanzahl() ;i++)
    {
        zeile.set_text(magazin.zeile(i));

        if(zeile.zeile(2) == wkz_nr)
        {
            returntext = zeile.zeile(9);
        }

    }
    returntext.replace(",",".");
    return returntext;
}
QString werkzeugmagazin::get_nutzlaenge(QString wkz_nr)
{
    QString returntext = "";
    text_zeilenweise zeile;
    zeile.set_trennzeichen('\t');

    for(uint i = 2; i<=magazin.zeilenanzahl() ;i++)
    {
        zeile.set_text(magazin.zeile(i));

        if(zeile.zeile(2) == wkz_nr)
        {
            returntext = zeile.zeile(4);
        }

    }
    returntext.replace(",",".");
    return returntext;
}
QString werkzeugmagazin::get_spiegelwkz(QString wkz_nr)
{
    QString returntext = "";
    text_zeilenweise zeile;
    zeile.set_trennzeichen('\t');

    for(uint i = 2; i<=magazin.zeilenanzahl() ;i++)
    {
        zeile.set_text(magazin.zeile(i));

        if(zeile.zeile(2) == wkz_nr)
        {
            returntext = zeile.zeile(13);
        }

    }
    return returntext;
}

text_zeilenweise werkzeugmagazin::get_alle_bodm(QString hori_oder_vert)
{
    text_zeilenweise tz;


    for(uint i=2; i<=magazin.zeilenanzahl() ;i++)//Zeile 1 ist Tabellenkopf
    {
        text_zeilenweise werkzeug;
        werkzeug.set_text(magazin.zeile(i));

        text_zeilenweise parameter;
        parameter.set_trennzeichen('\t');
        parameter.set_text(werkzeug.get_text());

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
