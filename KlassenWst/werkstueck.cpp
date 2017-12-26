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
    bool bereits_vorhanden = false;

    for(uint i=0; i<=bearbeitungen.zeilenanzahl() ;i++)
    {
        if(bearbeitungen.zeile(i) == text)
        {
            bereits_vorhanden = true;
            break;
        }
    }

    if(bereits_vorhanden == false)
    {
        bearbeitungen.zeilen_anhaengen(text);
    }
}

QString werkstueck::fehler_ganx(text_zeilenweise bearbeit, QString drehwinkel)
{
    QString msg = "";

    //Wst-Maße prüfen:
    if(drehwinkel == "0" || drehwinkel == "180")
    {
        double tmp_l = laenge;
        double tmp_b = breite;
        double tmp_d = dicke;
        if(tmp_l > 1)
        {
            msg += "  !! Werkstueck-Laenge zu gross\n";
        }
        if(tmp_b > 1)
        {
            msg += "  !! Werkstueck-Breite zu gross\n";
        }
        if(tmp_d > 1)
        {
            msg += "  !! Werkstueck-Dicke zu gross\n";
        }
    }else if(drehwinkel == "90" || drehwinkel == "270")
    {

    }

    return msg;
}
QString werkstueck::warnungen_ganx(text_zeilenweise bearbeit, QString drehwinkel)
{
    QString msg = "";

    return msg;
}
QString werkstueck::fehler_fmc(text_zeilenweise bearbeit, QString drehwinkel)
{
    QString msg = "";

    return msg;
}
QString werkstueck::warnungen_fmc(text_zeilenweise bearbeit, QString drehwinkel)
{
    QString msg = "";

    return msg;
}

void werkstueck::bearb_sortieren()
{
    text_zeilenweise tz_bohr_vert;
    text_zeilenweise tz_bohr_hori;
    text_zeilenweise tz_rta;            //Rechtecktaschen

    //in for-Schleife bearb aufsplitten:
    //....

    //Reihenfolge der Bearbeitungen festlegen:
    //bearbeitungen.clear();
    //bearbeitungen.zeilen_anhaengen(tz_bohr_vert);
}
text_zeilenweise werkstueck::bearb_drehen_90(text_zeilenweise bearb)
{
    //diese Funktion dreht die Bearbeitungen um 90° im Uhrzeigersinn
    text_zeilenweise tz;


    return tz;
}

//-------------------------------------------------------------------------Export:
QString werkstueck::get_fmc(text_zeilenweise werkzeugmagazin, QString& info , QString drehwinkel)
{
    QString msg;

    if(drehwinkel == "0")
    {
        QString warnungen = warnungen_fmc(bearbeitungen, drehwinkel);
        QString fehler = fehler_fmc(bearbeitungen, drehwinkel);
        info = warnungen + fehler;

        //Programmkopf:
        msg = FMC_PRGKOPF;
        msg += "\n";


        //Programmende:

    }else
    {
        msg = "Derzeit wird nur Drehwinkel 0 = unterstuetzt.";
    }
    return msg;
}
QString werkstueck::get_ganx(text_zeilenweise werkzeugmagazin, QString& info , QString drehwinkel)
{
    QString msg;

    if(drehwinkel == "0")
    {
        QString warnungen = warnungen_ganx(bearbeitungen, drehwinkel);
        QString fehler = fehler_ganx(bearbeitungen, drehwinkel);
        info = warnungen + fehler;

        double tmp_l = breite;
        double tmp_b = laenge;
        text_zeilenweise tmp_bearb = bearb_drehen_90(bearbeitungen);

    }else
    {
        msg = "Derzeit wird nur Drehwinkel 0 = unterstuetzt.";
    }
    return msg;
}
QString werkstueck::get_eigenses_format()
{
    QString msg;

    //Programmkopf:
    msg = "L: ";
    msg += get_laenge_qstring();
    msg += "\n";
    msg += "B: ";
    msg += get_breite_qstring();
    msg += "\n";
    msg += "D: ";
    msg += get_dicke_qstring();
    msg += "\n";
    msg += "---------------";
    msg += "\n";

    msg += bearbeitungen.get_text();

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

