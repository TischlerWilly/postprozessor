#include "werkstueck.h"

werkstueck::werkstueck()
{
    laenge=0;
    breite=0;
    dicke=0;
}

void werkstueck::set_laenge(double l)
{
    if(l>0 && l<5000)
    {
        laenge = l;
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
        breite = b;
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
        dicke = d;
    }
}
void werkstueck::set_dicke(QString d)
{
    set_dicke(d.toDouble());
}
void werkstueck::neue_bearbeitung(QString text)
{
    bearbeitungen.zeilen_anhaengen(text);
}

//-------------------------------------------------------------------------Export:
QString werkstueck::get_fmc(text_zeilenweise werkzeugmagazin, QString drehwinkel)
{
    QString msg;

    //Programmkopf:
    msg = FMC_PRGKOPF;
    msg += "\n";


    //Programmende:


    return msg;
}
QString werkstueck::get_ganx(text_zeilenweise werkzeugmagazin, QString drehwinkel)
{
    QString msg;

    msg = "jo";

    return msg;
}

//-------------------------------------------------------------------------Werkzeug:
QString werkstueck::get_wkz_nummer(text_zeilenweise wkz_magazin, QString wkz_typ, double dm, double bearbeitungstiefe)
{
    QString returntext = "";
    text_zeilenweise zeile;
    zeile.set_trennzeichen('\t');
    double wkz_dm_tmp = 0;

    for(uint i = 2; i<=wkz_magazin.zeilenanzahl() ;i++)
    {
        zeile.set_text(wkz_magazin.zeile(i));
        if(  (zeile.zeile(1) == wkz_typ)  &&  (wkz_typ == WKZ_TYP_BOHRER)  )
        {
            if(zeile.zeile(3).toDouble() == dm)
            {
                if(zeile.zeile(4).toDouble() > bearbeitungstiefe)
                {
                    returntext = zeile.zeile(2);
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
        for(uint i = 2; i<=wkz_magazin.zeilenanzahl() ;i++)
        {
            zeile.set_text(wkz_magazin.zeile(i));
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
QString werkstueck::get_wkz_dm(text_zeilenweise wkz_magazin, QString wkz_nr)
{
    QString returntext = "";
    text_zeilenweise zeile;
    zeile.set_trennzeichen('\t');

    for(uint i = 2; i<=wkz_magazin.zeilenanzahl() ;i++)
    {
        zeile.set_text(wkz_magazin.zeile(i));

        if(zeile.zeile(2) == wkz_nr)
        {
            returntext = zeile.zeile(3);
        }

    }
    return returntext;
}
QString werkstueck::get_wkz_vorschub(text_zeilenweise wkz_magazin, QString wkz_nr)
{
    QString returntext = "";
    text_zeilenweise zeile;
    zeile.set_trennzeichen('\t');

    for(uint i = 2; i<=wkz_magazin.zeilenanzahl() ;i++)
    {
        zeile.set_text(wkz_magazin.zeile(i));

        if(zeile.zeile(2) == wkz_nr)
        {
            returntext = zeile.zeile(5);
        }

    }
    return returntext;
}

