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
                        if(bearbeitungstiefe >= werkstueckdicke)
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
                                returntext = zeile.zeile(2);
                            }
                            //ist im WKZ-Magazin ein Durchgangsbohrer und ein Nicht-Durchgangsbohrer
                            //mit dem selben DM, so muss Nicht-Durchgangsbohrer vor dem Durchgangsbohrer stehen
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
