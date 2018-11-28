#include "werkstueck.h"

werkstueck::werkstueck()
{
    laenge  = 0;
    breite  = 0;
    dicke   = 0;
    schwellenwert_ay = 230;
}
werkstueck::werkstueck(QString neuer_name)
{
    name    = neuer_name;
    laenge  = 0;
    breite  = 0;
    dicke   = 0;
    schwellenwert_ay = 230;
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
        bearbeitungen.zeilen_anhaengen(text);
    }
}

QString werkstueck::warnungen_ganx(text_zeilenweise bearbeit,double tmp_l, double tmp_b, text_zeilenweise wkzmagazin)
{
    QString msg = "";
    double wst_x = tmp_l;
    double wst_y = tmp_b;

    //Wst-Maße prüfen:
    double tmp_d = dicke;
    if(wst_y > 4000)
    {
        msg += "  !! Werkstueck-Y-Mass > 4000mm\n";
        msg += "     Y-Mass = " + double_to_qstring(wst_y) + "\n";
    }
    if(wst_y < 250)
    {
        msg += "  !! Werkstueck-Y-Mass < 250mm\n";
        msg += "     Y-Mass = " + double_to_qstring(wst_y) + "\n";
    }
    if(wst_x > 1000)
    {
        msg += "  !! Werkstueck-X-Mass > 1000mm\n";
        msg += "     X-Mass = " + double_to_qstring(wst_x) + "\n";
    }
    if(wst_x < 50)
    {
        msg += "  !! Werkstueck-X-Mass < 50mm\n";
        msg += "     X-Mass = " + double_to_qstring(wst_x) + "\n";
    }
    if(tmp_d > 50)
    {
        msg += "  !! Werkstueck-Dicke > 50mm\n";
        msg += "     Dicke = " + double_to_qstring(tmp_d) + "\n";
    }
    if(tmp_d < 6)
    {
        msg += "  !! Werkstueck-Dicke < 6mm\n";
        msg += "     Dicke = " + double_to_qstring(tmp_d) + "\n";
    }

    werkzeugmagazin wkzmag(wkzmagazin);

    for(uint i=1; i<=bearbeit.zeilenanzahl() ;i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(bearbeit.zeile(i));

        QString art = zeile.zeile(1);
        if(art == BEARBART_BOHR)
        {
            bohrung bo(zeile.get_text());
            QString bezug = bo.get_bezug();

            //Warnung für HBEs:
            if(bezug == WST_BEZUG_VO || bezug == WST_BEZUG_HI)
            {
                double x = bo.get_x();
                if( x<18 )
                {
                    msg += "  !! HBE zu dicht am Rand!\n";
                    msg += "     X-Mass muss >= 18mm sein\n";
                    msg += "     X-Mass ist ";
                    msg += double_to_qstring(x);
                    msg += "mm\n";
                }
            }

            //Warnung für Kreistaschen di zu dicht am Rand sind:
            QString tnummer = wkzmag.get_wkznummer(WKZ_TYP_BOHRER, bo.get_dm(), bo.get_tiefe(), dicke, bezug);
            if(tnummer.isEmpty())//Bohren nicht möglich weil kein passendes Werkzeug
            {
                tnummer = wkzmag.get_wkznummer_von_alias(bo.get_wkznum());//Ist direkt ei WKZ definiert?
                if(tnummer.isEmpty())
                {
                    tnummer = wkzmag.get_wkznummer(WKZ_TYP_FRAESER, bo.get_dm(), bo.get_tiefe(), dicke, bezug);
                }
                if(!tnummer.isEmpty())//Kreistasche kann gefräst werden
                {
                    double xmin = bo.get_x() - bo.get_dm()/2;
                    if(xmin < 40)
                    {
                        msg += "  !! Kreistasche zu dicht am Rand!\n";
                        msg += "     X-Abstand muss mind 40mm sein\n";
                        msg += "     X-Abstand ist ";
                        msg += double_to_qstring(xmin);
                        msg += "mm\n";
                    }

                    //Nutzlänge Fräser und Tati prüfen:
                    if(bo.get_tiefe() > wkzmag.get_nutzlaenge(tnummer).toDouble())
                    {
                        msg += "  !! Nutzlaenge < Fraestiefe    bei Kreistasche!\n";
                    }
                    //Mindest-Zustellmaß des Fräsers Prüfen:
                    if(bo.get_tiefe() < wkzmag.get_zustellmass_min(tnummer).toDouble())
                    {
                        msg += "  !! Mindest-Zustellmass < Fraestiefe    bei Kreistasche!\n";
                    }
                }else//Es ist auch kein passender Fräser da, die CNC-Bearbeitung kann nicht erfolgen
                {
                    msg += "  !! Kein Werkzeug fuer Bohrung oder Kreistasche gefunden!\n";
                }
            }else
            {

                if(wkzmag.get_dm(tnummer) == "35")
                {
                    //Warnung für 35er Bohrer geben der in Kante Bohrt (Bohrerbruch durch Unwucht)
                    //rein mechanisch ist das mind X-Maß beim 35er Bohrer 11,5mm == 35/2-6 == 17,5-6
                    if(bo.get_x() < 17.5            ||\
                       bo.get_x() > (tmp_l-17.5)    ||\
                       bo.get_y() < 17.5            ||\
                       bo.get_y() > (tmp_b-17.5)    )
                    {
                        msg += "  !! 35er Bohrung zu dicht am Rand fuer verwendeten Bohrer!\n";
                    }
                }else if(wkzmag.get_dm(tnummer) == "8")
                {
                    if(bo.get_x() < 0)
                    {
                        msg += "  !! X-Maß 8er Bohrung zu gering! Mind 0mm erforderlich.\n";
                    }
                }else if(wkzmag.get_dm(tnummer) == "10")
                {
                    if(bo.get_x() < 0)
                    {
                        msg += "  !! X-Maß 10er Bohrung zu gering! Mind 0mm erforderlich.\n";
                    }
                }else
                {
                    double wkzdm = wkzmag.get_dm(tnummer).toDouble();
                    if(bo.get_x() < 1+wkzdm/2)
                    {
                        msg += "  !! X-Maß ";
                        msg += double_to_qstring(wkzdm);
                        msg += "er Bohrung zu gering! Mind ";
                        msg += double_to_qstring(1+wkzdm/2);
                        msg += "mm erforderlich.\n";
                    }
                }

            }

        }else if(art == BEARBART_RTA)
        {
            rechtecktasche rt(zeile.get_text());
            //Prüfen ob Tasche zu dicht am WST-Rand ist:
            double xmin = rt.get_x();
            if(rt.get_drewi() == 0 || rt.get_drewi() == 180)
            {
                xmin = xmin - rt.get_laenge()/2;
            }if(rt.get_drewi() == 90 || rt.get_drewi() == 270)
            {
                xmin = xmin - rt.get_breite()/2;
            }else
            {
                xmin = xmin - sqrt(rt.get_laenge() * rt.get_breite())/2; //Näherungsweise
            }

            if(xmin < 40)
            {
                msg += "  !! Rechtecktasche zu dicht am Rand!\n";
                msg += "     X-Abstand muss mind 40mm sein\n";
                msg += "     X-Abstand ist ca ";
                msg += double_to_qstring(xmin);
                msg += "mm\n";
            }

            //-----------------------------------------------

            //Prüfen ob Nutzlänge ausreichend für Tati ist:
            QString tnummer = wkzmag.get_wkznummer_von_alias(rt.get_wkznum());//Ist direkt ei WKZ definiert?
            if(tnummer.isEmpty())
            {
                QString bezug = rt.get_bezug();
                double minmass = 0;
                if(rt.get_laenge() < rt.get_breite())
                {
                    minmass = rt.get_laenge();
                }else
                {
                    minmass = get_breite();
                }
                tnummer = wkzmag.get_wkznummer(WKZ_TYP_FRAESER, minmass, rt.get_tiefe(), dicke, bezug);
            }
            if(!tnummer.isEmpty())
            {
                //Nutzlänge Fräser und Tati prüfen
                if(rt.get_tiefe() > wkzmag.get_nutzlaenge(tnummer).toDouble())
                {
                    msg += "  !! Nutzlaenge < Fraestiefe    bei Rechtecktasche!\n";
                }
                //Mindest-Zustellmaß des Fräsers Prüfen:
                if(rt.get_tiefe() < wkzmag.get_zustellmass_min(tnummer).toDouble())
                {
                    msg += "  !! Mindest-Zustellmass < Fraestiefe    bei Rechtecktasche!\n";
                }
            }
        }else if(art == BEARBART_NUT)
        {
            nut nu(zeile.get_text());
            QString bezug = nu.get_bezug();
            QString tnummer = wkzmag.get_wkznummer(WKZ_TYP_SAEGE, 0, nu.get_tiefe(), dicke, bezug);
            double nutblattbreite = wkzmag.get_saegeblattbreite(tnummer).toDouble();
            if(nu.get_xs() != nu.get_xe())
            {
                msg += "  !! Nutrichutng auf der der Maschine nicht moeglich!\n";
            }else if(nu.get_xs()-nu.get_breite() < 57.5)
            {
                msg += "  !! Nut zu dicht am Rand/zu dicht an Spannzange!\n";
                msg += "     Randabstand in X muss mind 57,5mm sein\n";
                msg += "     Randabstand X ist ca ";
                msg += double_to_qstring(nu.get_xs()-nu.get_breite());
                msg += "mm\n";
            }
            if(nu.get_breite() < nutblattbreite)
            {
                msg += "  !! Nutbreite ist kleiner als Blattbreite!\n";
            }
        }
    }

    return msg;
}
QString werkstueck::warnungen_fmc(text_zeilenweise bearbeit,double tmp_l, double tmp_b, text_zeilenweise wkzmagazin)
{
    QString msg = "";

    //Wst-Maße prüfen:
    double tmp_d = dicke;
    if(tmp_l > 3000)
    {
        msg += "  !! Werkstueck-Laenge > 3000mm\n";
    }
    if(tmp_l < 120)
    {
        msg += "  !! Werkstueck-Laenge < 120mm\n";
    }
    if(tmp_b > 1100)
    {
        msg += "  !! Werkstueck-Breite > 1100mm\n";
    }
    if(tmp_b < 50)
    {
        msg += "  !! Werkstueck-Breite < 50mm\n";
    }
    if(tmp_d > 100)
    {
        msg += "  !! Werkstueck ist sehr dick\n";
    }
    if(tmp_d < 5)
    {
        msg += "  !! Werkstueck ist sehr duenn\n";
    }

    werkzeugmagazin wkzmag(wkzmagazin);

    for(uint i=1; i<=bearbeit.zeilenanzahl() ;i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(bearbeit.zeile(i));

        QString art = zeile.zeile(1);
        if(art == BEARBART_BOHR)
        {
            bohrung bo(zeile.get_text());
            QString bezug = bo.get_bezug();

            QString tnummer = wkzmag.get_wkznummer(WKZ_TYP_BOHRER, bo.get_dm(), bo.get_tiefe(), dicke, bezug);
            if(tnummer.isEmpty())//Bohren nicht möglich weil kein passendes Werkzeug
            {
                tnummer = wkzmag.get_wkznummer_von_alias(bo.get_wkznum());//Ist direkt ei WKZ definiert?
                if(tnummer.isEmpty())
                {
                    tnummer = wkzmag.get_wkznummer(WKZ_TYP_FRAESER, bo.get_dm(), bo.get_tiefe(), dicke, bezug);
                }
                if(!tnummer.isEmpty())//Kreistasche kann gefräst werden
                {
                    //Nutzlänge Fräser und Tati prüfen:
                    if(bo.get_tiefe() > wkzmag.get_nutzlaenge(tnummer).toDouble())
                    {
                        msg += "  !! Nutzlaenge < Fraestiefe    bei Kreistasche!\n";
                    }
                    //Mindest-Zustellmaß des Fräsers Prüfen:
                    if(bo.get_tiefe() < wkzmag.get_zustellmass_min(tnummer).toDouble())
                    {
                        msg += "  !! Mindest-Zustellmass < Fraestiefe    bei Kreistasche!\n";
                    }

                }else//Es ist auch kein passender Frser da, die CNC-Bearbeitung kann nicht erfolgen
                {
                    msg += "  !! Kein Werkzeug fuer Bohrung oder Kreistasche gefunden!\n";
                }
            }

        }else if(art == BEARBART_RTA)
        {
            rechtecktasche rt(zeile.get_text());

            //Prüfen ob Nutzlänge ausreichend für Tati ist:
            QString tnummer = wkzmag.get_wkznummer_von_alias(rt.get_wkznum());//Ist direkt ei WKZ definiert?
            if(tnummer.isEmpty())
            {
                QString bezug = rt.get_bezug();
                double minmass = 0;
                if(rt.get_laenge() < rt.get_breite())
                {
                    minmass = rt.get_laenge();
                }else
                {
                    minmass = get_breite();
                }
                tnummer = wkzmag.get_wkznummer(WKZ_TYP_FRAESER, minmass, rt.get_tiefe(), dicke, bezug);
            }
            if(!tnummer.isEmpty())
            {
                //Nutzlänge Fräser und Tati prüfen
                if(rt.get_tiefe() > wkzmag.get_nutzlaenge(tnummer).toDouble())
                {
                    msg += "  !! Nutzlaenge < Fraestiefe    bei Rechtecktasche!\n";
                }
                //Mindest-Zustellmaß des Fräsers Prüfen:
                if(rt.get_tiefe() < wkzmag.get_zustellmass_min(tnummer).toDouble())
                {
                    msg += "  !! Mindest-Zustellmass < Fraestiefe    bei Rechtecktasche!\n";
                }
            }
        }else if(art == BEARBART_NUT)
        {
            nut nu(zeile.get_text());
            QString bezug = nu.get_bezug();
            QString tnummer = wkzmag.get_wkznummer(WKZ_TYP_SAEGE, 0, nu.get_tiefe(), dicke, bezug);
            double nutblattbreite = wkzmag.get_saegeblattbreite(tnummer).toDouble();
            if(nu.get_breite() < nutblattbreite)
            {
                msg += "  !! Nutbreite ist kleiner als Blattbreite!\n";
            }
        }else if(art == BEARBART_FRAESERAUFRUF)
        {
            fraueseraufruf fa(zeile.get_text());
            QString tnummer = wkzmag.get_wkznummer_von_alias(fa.get_wkznum());
            if(tnummer.isEmpty())
            {
                msg += "  !! Keine Werkzeugnummer vergeben bei Fraeseraufruf!\n";
            }else
            {
                //Nutzlänge Fräser und Tati prüfen
                if(fa.get_tiefe() > wkzmag.get_nutzlaenge(tnummer).toDouble())
                {
                    msg += "  !! Nutzlaenge < Fraestiefe    bei Fraeseraufruf!\n";
                }
                //Mindest-Zustellmaß des Fräsers Prüfen:
                if(fa.get_tiefe() < wkzmag.get_zustellmass_min(tnummer).toDouble())
                {
                    msg += "  !! Mindest-Zustellmass < Fraestiefe    bei Fraeseraufruf!\n";
                }
            }

        }
    }

    return msg;
}
QString werkstueck::fehler_kein_WKZ(QString exportformat, text_zeilenweise bearbeitung)
{
    QString fehlermeldung;

    fehlermeldung += "Fehler bei ";
    fehlermeldung += exportformat;
    fehlermeldung += "-Export!\n";

    fehlermeldung += "Teilname: ";
    fehlermeldung += name;
    fehlermeldung += "\n";

    fehlermeldung += "Kein Werkzeug fuer ";

    fehlermeldung += get_bearb_menschlich_lesbar(bearbeitung);

    return fehlermeldung;
}
QString werkstueck::get_bearb_menschlich_lesbar(text_zeilenweise bearbeitung)
{
    QString daten;
    if(bearbeitung.zeile(1) == BEARBART_BOHR)
    {
        daten += "Bohrung oder Kreistasche:\n";
        daten += "Bezugsflaeche: ";
        daten += bearbeitung.zeile(2);
        daten += "\n";
        daten += "Durchmesser: ";
        daten += bearbeitung.zeile(3);
        daten += "\n";
        daten += "Tiefe: ";
        daten += bearbeitung.zeile(4);
        daten += "\n";
        daten += "Pos X: ";
        daten += bearbeitung.zeile(5);
        daten += "\n";
        daten += "Pos Y: ";
        daten += bearbeitung.zeile(6);
        daten += "\n";
        daten += "Pos Z: ";
        daten += bearbeitung.zeile(7);
        daten += "\n";
        daten += "AFB: ";
        daten += bearbeitung.zeile(8);
        daten += "\n";
        daten += "Zustellmass: ";
        daten += bearbeitung.zeile(9);
        daten += "\n";
        daten += "Werkzeug: ";
        daten += bearbeitung.zeile(10);
        daten += "\n";
    }else if(bearbeitung.zeile(1) == BEARBART_RTA)
    {
        daten += "Rechtecktasche:\n";
        daten += "Bezugsflaeche: ";
        daten += bearbeitung.zeile(2);
        daten += "\n";
        daten += "Taschenleange: ";
        daten += bearbeitung.zeile(3);
        daten += "\n";
        daten += "Taschenbreite: ";
        daten += bearbeitung.zeile(4);
        daten += "\n";
        daten += "Taschentiefe: ";
        daten += bearbeitung.zeile(5);
        daten += "\n";
        daten += "Pos X: ";
        daten += bearbeitung.zeile(6);
        daten += "\n";
        daten += "Pos Y: ";
        daten += bearbeitung.zeile(7);
        daten += "\n";
        daten += "Pos Z: ";
        daten += bearbeitung.zeile(8);
        daten += "\n";
        daten += "Drehwinkel im UZS: ";
        daten += bearbeitung.zeile(9);
        daten += "\n";
        daten += "Eckenradius: ";
        daten += bearbeitung.zeile(10);
        daten += "\n";
        daten += "Ausraeumen: ";
        daten += bearbeitung.zeile(11);
        daten += "\n";
        daten += "AFB: ";
        daten += bearbeitung.zeile(12);
        daten += "\n";
        daten += "Zustellmass: ";
        daten += bearbeitung.zeile(13);
        daten += "\n";
        daten += "Werkzeug: ";
        daten += bearbeitung.zeile(14);
        daten += "\n";
    }else if(bearbeitung.zeile(1) == BEARBART_NUT)
    {
        daten += "Nut:\n";
        daten += "Bezugsflaeche: ";
        daten += bearbeitung.zeile(2);
        daten += "\n";
        daten += "Startpunkt in X: ";
        daten += bearbeitung.zeile(3);
        daten += "\n";
        daten += "Startpunkt in Y: ";
        daten += bearbeitung.zeile(4);
        daten += "\n";
        daten += "Endpunkt in X: ";
        daten += bearbeitung.zeile(5);
        daten += "\n";
        daten += "Endpunkt in Y: ";
        daten += bearbeitung.zeile(6);
        daten += "\n";
        daten += "Nuttiefe: ";
        daten += bearbeitung.zeile(7);
        daten += "\n";
        daten += "Nutbreite: ";
        daten += bearbeitung.zeile(8);
        daten += "\n";
        daten += "AFB: ";
        daten += bearbeitung.zeile(9);
        daten += "\n";
    }else if(bearbeitung.zeile(1) == BEARBART_FRAESERAUFRUF)
    {
        daten += "Aufruf Fraeser:\n";
        daten += "Bezugsflaeche: ";
        daten += bearbeitung.zeile(2);
        daten += "\n";
        daten += "Startpunkt in X: ";
        daten += bearbeitung.zeile(3);
        daten += "\n";
        daten += "Startpunkt in Y: ";
        daten += bearbeitung.zeile(4);
        daten += "\n";
        daten += "Startpunkt in Z: ";
        daten += bearbeitung.zeile(5);
        daten += "\n";
        daten += "Tiefe: ";
        daten += bearbeitung.zeile(6);
        daten += "\n";
        daten += "Bahnkorrektur: ";
        daten += bearbeitung.zeile(7);
        daten += "\n";
        daten += "Werkzeug: ";
        daten += bearbeitung.zeile(8);
        daten += "\n";
        daten += "AFB: ";
        daten += bearbeitung.zeile(9);
        daten += "\n";
    }else if(bearbeitung.zeile(1) == BEARBART_FRAESERGERADE)
    {
        daten += "gerade Fraesbahn:\n";
        daten += "Bezugsflaeche: ";
        daten += bearbeitung.zeile(2);
        daten += "\n";
        daten += "Startpunkt in X: ";
        daten += bearbeitung.zeile(3);
        daten += "\n";
        daten += "Startpunkt in Y: ";
        daten += bearbeitung.zeile(4);
        daten += "\n";
        daten += "Startpunkt Tiefe: ";
        daten += bearbeitung.zeile(5);
        daten += "\n";
        daten += "Endpunkt in X: ";
        daten += bearbeitung.zeile(6);
        daten += "\n";
        daten += "Endpunkt in Y: ";
        daten += bearbeitung.zeile(7);
        daten += "\n";
        daten += "Endpunkt Tiefe: ";
        daten += bearbeitung.zeile(8);
        daten += "\n";
        daten += "AFB: ";
        daten += bearbeitung.zeile(9);
        daten += "\n";
    }else if(bearbeitung.zeile(1) == BEARBART_FRAESERBOGEN)
    {
        daten += "gebogene Fraesbahn:\n";
        daten += "Bezugsflaeche: ";
        daten += bearbeitung.zeile(2);
        daten += "\n";
        daten += "Startpunkt in X: ";
        daten += bearbeitung.zeile(3);
        daten += "\n";
        daten += "Startpunkt in Y: ";
        daten += bearbeitung.zeile(4);
        daten += "\n";
        daten += "Startpunkt Tiefe: ";
        daten += bearbeitung.zeile(5);
        daten += "\n";
        daten += "Endpunkt in X: ";
        daten += bearbeitung.zeile(6);
        daten += "\n";
        daten += "Endpunkt in Y: ";
        daten += bearbeitung.zeile(7);
        daten += "\n";
        daten += "Endpunkt Tiefe: ";
        daten += bearbeitung.zeile(8);
        daten += "\n";
        daten += "Radius: ";
        daten += bearbeitung.zeile(9);
        daten += "\n";
        daten += "Bogenrichtung: ";
        if(bearbeitung.zeile(8) == "1")
        {
            daten += "Uhrzeigersinn";
        }else
        {
            daten += "Gegen-Uhrzeigersinn";
        }
        daten += "\n";
        daten += "AFB: ";
        daten += bearbeitung.zeile(11);
        daten += "\n";
    }
    return daten;
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
text_zeilenweise werkstueck::bearb_drehen_90(text_zeilenweise bearb, double& tmp_l, double& tmp_b)
{
    //diese Funktion dreht die Bearbeitungen um 90° im Uhrzeigersin

    for(uint i=1; i<=bearb.zeilenanzahl() ;i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(bearb.zeile(i));
        QString zeile_neu;

        if(zeile.zeile(1) == BEARBART_BOHR)
        {
            bohrung bo(zeile.get_text());
            double x = bo.get_x();
            double y = bo.get_y();
            QString bezug = bo.get_bezug();
            if(bezug == WST_BEZUG_OBSEI || bezug == WST_BEZUG_UNSEI)
            {
                bo.set_x(y);
                bo.set_y(tmp_l - x);
            }else if(bezug == WST_BEZUG_VO)
            {
                bo.set_bezug(WST_BEZUG_LI);
                bo.set_x(y);
                bo.set_y(tmp_l - x);
            }else if(bezug == WST_BEZUG_HI)
            {
                bo.set_bezug(WST_BEZUG_RE);
                bo.set_x(y);
                bo.set_y(tmp_l - x);
            }else if(bezug == WST_BEZUG_LI)
            {
                bo.set_bezug(WST_BEZUG_HI);
                bo.set_x(y);
                bo.set_y(tmp_l - x);
            }else if(bezug == WST_BEZUG_RE)
            {
                bo.set_bezug(WST_BEZUG_VO);
                bo.set_x(y);
                bo.set_y(tmp_l - x);
            }
            zeile_neu = bo.get_text();
        }else if(zeile.zeile(1) == BEARBART_BOHRRASTER)
        {
            bohrraster bora(zeile.get_text());
            double x = bora.get_x();
            double y = bora.get_y();
            QString bezug = bora.get_bezug();
            if(bezug == WST_BEZUG_OBSEI || bezug == WST_BEZUG_UNSEI)
            {
                bora.set_x(y);
                bora.set_y(tmp_l - x);
                uint anz_x = bora.get_anz_x();
                uint anz_y = bora.get_anz_y();
                bora.set_anz_x(anz_y);
                bora.set_anz_y(anz_x);
                double raster_x = bora.get_raster_x();
                double raster_y = bora.get_raster_y();
                bora.set_raster_x(raster_y);
                bora.set_raster_y(raster_x);
            }
        }else if(zeile.zeile(1) == BEARBART_RTA)
        {
            rechtecktasche rt(zeile.get_text());
            double x = rt.get_x();
            double y = rt.get_y();
            double tal = rt.get_laenge();
            double tab = rt.get_breite();
            QString bezug = rt.get_bezug();
            if(bezug == WST_BEZUG_OBSEI || bezug == WST_BEZUG_UNSEI)
            {
                rt.set_x(y);
                rt.set_y(tmp_l - x);
                rt.set_laenge(tab);
                rt.set_breite(tal);
            }else if(bezug == WST_BEZUG_VO)
            {
                rt.set_bezug(WST_BEZUG_LI);
                rt.set_x(y);
                rt.set_y(tmp_l - x);
            }else if(bezug == WST_BEZUG_HI)
            {
                rt.set_bezug(WST_BEZUG_RE);
                rt.set_x(y);
                rt.set_y(tmp_l - x);
            }else if(bezug == WST_BEZUG_LI)
            {
                rt.set_bezug(WST_BEZUG_HI);
                rt.set_x(y);
                rt.set_y(tmp_l - x);
            }else if(bezug == WST_BEZUG_RE)
            {
                rt.set_bezug(WST_BEZUG_VO);
                rt.set_x(y);
                rt.set_y(tmp_l - x);
            }
            zeile_neu = rt.get_text();
        }else if(zeile.zeile(1) == BEARBART_NUT)
        {
            nut nu(zeile.get_text());
            double xs = nu.get_xs();
            double ys = nu.get_ys();
            double xe = nu.get_xe();
            double ye = nu.get_ye();

            nu.set_xs(ys);
            nu.set_ys(tmp_l - xs);
            nu.set_xe(ye);
            nu.set_ye(tmp_l - xe);

            zeile_neu = nu.get_text();
        }else if(zeile.zeile(1) == BEARBART_FRAESERAUFRUF)
        {
            fraueseraufruf tmp(zeile.get_text());
            double x = tmp.get_x();
            double y = tmp.get_y();

            tmp.set_x(y);
            tmp.set_y(tmp_l - x);
            zeile_neu = tmp.get_text();
        }else if(zeile.zeile(1) == BEARBART_FRAESERGERADE)
        {
            fraesergerade tmp(zeile.get_text());
            double xs = tmp.get_xs();
            double xe = tmp.get_xe();
            double ys = tmp.get_ys();
            double ye = tmp.get_ye();

            tmp.set_xs(ys);
            tmp.set_xe(ye);
            tmp.set_ys(tmp_l - xs);
            tmp.set_ye(tmp_l - xe);
            zeile_neu = tmp.get_text();
        }else if(zeile.zeile(1) == BEARBART_FRAESERBOGEN)
        {
            fraeserbogen tmp(zeile.get_text());
            double xs = tmp.get_xs();
            double xe = tmp.get_xe();
            double ys = tmp.get_ys();
            double ye = tmp.get_ye();

            tmp.set_xs(ys);
            tmp.set_xe(ye);
            tmp.set_ys(tmp_l - xs);
            tmp.set_ye(tmp_l - xe);
            zeile_neu = tmp.get_text();
        }

        bearb.zeile_ersaetzen(i, zeile_neu);
    }
    //Länge und Breite tauschen:
    double tmp;
    tmp = tmp_l;
    tmp_l = tmp_b;
    tmp_b = tmp;


    return bearb;
}
text_zeilenweise werkstueck::bearb_optimieren_ganx(text_zeilenweise bearb)
{
    //X-Werte werden Y-Werte und umgehrt
    //Bearbeitungen wechseln von der Ober- auf die Unterseite und umgehrt

    for(uint i=1; i<=bearb.zeilenanzahl() ;i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(bearb.zeile(i));
        QString zeile_neu;

        if(zeile.zeile(1) == BEARBART_BOHR)
        {
            bohrung bo(zeile.get_text());
            double x = bo.get_x();
            double y = bo.get_y();
            double z = bo.get_z();
            QString bezug = bo.get_bezug();
            if(bezug == WST_BEZUG_OBSEI)
            {
                bo.set_bezug(WST_BEZUG_UNSEI);
                bo.set_x(y);
                bo.set_y(x);
            }else if(bezug == WST_BEZUG_UNSEI)
            {
                bo.set_bezug(WST_BEZUG_OBSEI);
                bo.set_x(y);
                bo.set_y(x);
            }else if(bezug == WST_BEZUG_VO)
            {
                bo.set_bezug(WST_BEZUG_LI);
                bo.set_x(y);
                bo.set_y(x);
                bo.set_z(dicke-z);
            }else if(bezug == WST_BEZUG_HI)
            {
                bo.set_bezug(WST_BEZUG_RE);
                bo.set_x(y);
                bo.set_y(x);
                bo.set_z(dicke-z);
            }else if(bezug == WST_BEZUG_LI)
            {
                bo.set_bezug(WST_BEZUG_VO);
                bo.set_x(y);
                bo.set_y(x);
                bo.set_z(dicke-z);
            }else if(bezug == WST_BEZUG_RE)
            {
                bo.set_bezug(WST_BEZUG_HI);
                bo.set_x(y);
                bo.set_y(x);
                bo.set_z(dicke-z);
            }
            zeile_neu = bo.get_text();
        }else if(zeile.zeile(1) == BEARBART_BOHR)
        {
            bohrraster bora(zeile.get_text());
            double x = bora.get_x();
            double y = bora.get_y();
            //double z = bora.get_z();
            QString bezug = bora.get_bezug();
            if(bezug == WST_BEZUG_OBSEI)
            {
                bora.set_bezug(WST_BEZUG_UNSEI);
                bora.set_x(y);
                bora.set_y(x);
                uint anz_x = bora.get_anz_x();
                uint anz_y = bora.get_anz_y();
                bora.set_anz_x(anz_y);
                bora.set_anz_y(anz_x);
                double raster_x = bora.get_raster_x();
                double raster_y = bora.get_raster_y();
                bora.set_raster_x(raster_y);
                bora.set_raster_y(raster_x);
            }else if(bezug == WST_BEZUG_UNSEI)
            {
                bora.set_bezug(WST_BEZUG_OBSEI);
                bora.set_x(y);
                bora.set_y(x);
                uint anz_x = bora.get_anz_x();
                uint anz_y = bora.get_anz_y();
                bora.set_anz_x(anz_y);
                bora.set_anz_y(anz_x);
                double raster_x = bora.get_raster_x();
                double raster_y = bora.get_raster_y();
                bora.set_raster_x(raster_y);
                bora.set_raster_y(raster_x);
            }
            zeile_neu = bora.get_text();
        }else if(zeile.zeile(1) == BEARBART_RTA)
        {
            rechtecktasche rt(zeile.get_text());
            double x = rt.get_x();
            double y = rt.get_y();
            double z = rt.get_z();
            double tal = rt.get_laenge();
            double tab = rt.get_breite();
            QString bezug = rt.get_bezug();
            if(bezug == WST_BEZUG_OBSEI)
            {
                rt.set_bezug(WST_BEZUG_UNSEI);
                rt.set_x(y);
                rt.set_y(x);
                rt.set_laenge(tab);
                rt.set_breite(tal);
            }else if(bezug == WST_BEZUG_UNSEI)
            {
                rt.set_bezug(WST_BEZUG_OBSEI);
                rt.set_x(y);
                rt.set_y(x);
                rt.set_laenge(tab);
                rt.set_breite(tal);
            }else if(bezug == WST_BEZUG_VO)
            {
                rt.set_bezug(WST_BEZUG_LI);
                rt.set_x(y);
                rt.set_y(x);
                rt.set_z(dicke-z);
            }else if(bezug == WST_BEZUG_HI)
            {
                rt.set_bezug(WST_BEZUG_RE);
                rt.set_x(y);
                rt.set_y(x);
                rt.set_z(dicke-z);
            }else if(bezug == WST_BEZUG_LI)
            {
                rt.set_bezug(WST_BEZUG_VO);
                rt.set_x(y);
                rt.set_y(x);
                rt.set_z(dicke-z);
            }else if(bezug == WST_BEZUG_RE)
            {
                rt.set_bezug(WST_BEZUG_HI);
                rt.set_x(y);
                rt.set_y(x);
                rt.set_z(dicke-z);
            }
            zeile_neu = rt.get_text();
        }else if(zeile.zeile(1) == BEARBART_NUT)
        {
            nut nu(zeile.get_text());
            double xs = nu.get_xs();
            double ys = nu.get_ys();
            double xe = nu.get_xe();
            double ye = nu.get_ye();
            QString bezug = nu.get_bezug();
            if(bezug == WST_BEZUG_OBSEI)
            {
                nu.set_bezug(WST_BEZUG_UNSEI);
                nu.set_xs(ys);
                nu.set_ys(xs);
                nu.set_xe(ye);
                nu.set_ye(xe);
            }else if(bezug == WST_BEZUG_UNSEI)
            {
                nu.set_bezug(WST_BEZUG_OBSEI);
                nu.set_xs(ys);
                nu.set_ys(xs);
                nu.set_xe(ye);
                nu.set_ye(xe);
            }
            zeile_neu = nu.get_text();
        }
        bearb.zeile_ersaetzen(i, zeile_neu);
    }
    return bearb;
}

QString werkstueck::suche_cad_fehler()
{
    QString msg;

    if(name.contains("Tuer") || \
       name.contains("Tur")      )
    {
        uint anz_asd = 0; //Anzahl Aufschlagdämpfer

        for(uint i=1; i<=bearbeitungen.zeilenanzahl() ;i++)
        {
            if(bearbeitungen.zeile(i).contains(BEARBART_BOHR))
            {
                bohrung bo(bearbeitungen.zeile(i));
                if(bo.get_dm() == 6 && bo.get_tiefe() < get_dicke())
                {
                    anz_asd++;
                }
            }
        }
        if(anz_asd < 2)
        {
            msg += get_name();
            msg += ": ";
            msg += double_to_qstring(anz_asd);
            msg += " Aufschlagdaempfer";
            msg += "\n";
        }
    }
    if(name.contains("SchubFront") || \
       name.contains("Schubfront")      )
    {
        uint anz_asd = 0; //Anzahl Aufschlagdämpfer

        for(uint i=1; i<=bearbeitungen.zeilenanzahl() ;i++)
        {
            if(bearbeitungen.zeile(i).contains(BEARBART_BOHR))
            {
                bohrung bo(bearbeitungen.zeile(i));
                if(bo.get_dm() == 6 && bo.get_tiefe() < get_dicke())
                {
                    anz_asd++;
                }
            }
        }
        if(anz_asd < 4)
        {
            msg += get_name();
            msg += ": ";
            msg += double_to_qstring(anz_asd);
            msg += " Aufschlagdaempfer";
            msg += "\n";
        }
    }


    return msg;
}

//-------------------------------------------------------------------------Export:
QString werkstueck::get_fmc(text_zeilenweise wkzmagazin, QString& info , QString drehwinkel, \
                            QString zust_fkon)
{
    QString msg;
    bearb_sortieren();
    fraesergeraden_zusammenfassen();

    if(drehwinkel == "0")
    {
        double tmp_l = laenge;
        double tmp_b = breite;
        text_zeilenweise tmp_bearb = bearbeitungen;
        msg = get_fmc_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b, zust_fkon);
        QString warnungen = warnungen_fmc(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
        info  = "\n";
        info += warnungen;
    }else if(drehwinkel == "90")
    {
        double tmp_l = laenge;
        double tmp_b = breite;
        text_zeilenweise tmp_bearb = bearbeitungen;
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        msg = get_fmc_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b, zust_fkon);
        QString warnungen = warnungen_fmc(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
        info  = "\n";
        info += warnungen;
    }else if(drehwinkel == "180")
    {
        double tmp_l = laenge;
        double tmp_b = breite;
        text_zeilenweise tmp_bearb = bearbeitungen;
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        msg = get_fmc_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b, zust_fkon);
        QString warnungen = warnungen_fmc(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
        info  = "\n";
        info += warnungen;
    }else if(drehwinkel == "270")
    {
        double tmp_l = laenge;
        double tmp_b = breite;
        text_zeilenweise tmp_bearb = bearbeitungen;
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        msg = get_fmc_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b, zust_fkon);
        QString warnungen = warnungen_fmc(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
        info  = "\n";
        info += warnungen;
    }else
    {
        double tmp_l = laenge;
        double tmp_b = breite;
        text_zeilenweise tmp_bearb = bearbeitungen;

        //Die beste Drehrichtung herausfinden:
        uint bewertung_0    = 1;
        uint bewertung_90   = 1;
        uint bewertung_180  = 1;
        uint bewertung_270  = 1;
        //Stufe 1:
        //heraus bekommen, für welche Lage es Warnungen gibt:
        QString warnung;
        text_zeilenweise bearb_kopie = tmp_bearb;
        double l_kopie = tmp_l;
        double b_kopie = tmp_b;
        //------------------------0:
        warnung = warnungen_fmc(bearb_kopie, l_kopie, b_kopie, wkzmagazin);
        if(warnung.isEmpty())
        {
            bewertung_0 = 100;
        }else
        {
            bewertung_0 = 0;
        }
        text_zeilenweise bearb_0 = bearb_kopie;
        double l_0 = l_kopie;
        double b_0 = b_kopie;
        //------------------------90:
        bearb_kopie = bearb_drehen_90(bearb_kopie, l_kopie, b_kopie);
        warnung = warnungen_fmc(bearb_kopie, l_kopie, b_kopie, wkzmagazin);
        if(warnung.isEmpty())
        {
            bewertung_90 = 100;
        }else
        {
            bewertung_90 = 0;
        }
        text_zeilenweise bearb_90 = bearb_kopie;
        double l_90 = l_kopie;
        double b_90 = b_kopie;
        //------------------------180:
        bearb_kopie = bearb_drehen_90(bearb_kopie, l_kopie, b_kopie);
        warnung = warnungen_fmc(bearb_kopie, l_kopie, b_kopie, wkzmagazin);
        if(warnung.isEmpty())
        {
            bewertung_180 = 100;
        }else
        {
            bewertung_180 = 0;
        }
        text_zeilenweise bearb_180 = bearb_kopie;
        double l_180 = l_kopie;
        double b_180 = b_kopie;
        //------------------------270:
        bearb_kopie = bearb_drehen_90(bearb_kopie, l_kopie, b_kopie);
        warnung = warnungen_fmc(bearb_kopie, l_kopie, b_kopie, wkzmagazin);
        if(warnung.isEmpty())
        {
            bewertung_270 = 100;
        }else
        {
            bewertung_270 = 0;
        }
        text_zeilenweise bearb_270 = bearb_kopie;
        double l_270 = l_kopie;
        double b_270 = b_kopie;

        //Stufe 2:
        //heraus bekommen wo vorne ist:
        for(uint i=1; i<=bearb_0.zeilenanzahl() ;i++)
        {
            text_zeilenweise zeile;
            zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
            zeile.set_text(bearb_0.zeile(i));
            if(zeile.zeile(1) == BEARBART_BOHR)
            {
                bohrung bo(zeile.get_text());
                if(bo.get_dm() == 8 || \
                   bo.get_dm() == 8.2)
                {                   
                    if(bo.get_y() == 20)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                    {
                        bewertung_0 += 2;
                    }
                    if(bo.get_x() == 20)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                    {
                        bewertung_0 += 2;
                    }
                }
            }
        }
        for(uint i=1; i<=bearb_90.zeilenanzahl() ;i++)
        {
            text_zeilenweise zeile;
            zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
            zeile.set_text(bearb_90.zeile(i));
            if(zeile.zeile(1) == BEARBART_BOHR)
            {
                bohrung bo(zeile.get_text());
                if(bo.get_dm() == 8 || \
                   bo.get_dm() == 8.2)
                {
                    if(bo.get_x() == 20)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                    {
                        bewertung_90 += 2;
                    }
                    if(bo.get_y() == 20)//Gilt für HBE, Löcher mit diesem Abst. in der Fläche sind nicht zu erwarten
                    {
                        bewertung_90 += 2;
                    }
                }
            }
        }
        for(uint i=1; i<=bearb_180.zeilenanzahl() ;i++)
        {
            text_zeilenweise zeile;
            zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
            zeile.set_text(bearb_180.zeile(i));
            if(zeile.zeile(1) == BEARBART_BOHR)
            {
               bohrung bo(zeile.get_text());
                if(bo.get_dm() == 8 || \
                   bo.get_dm() == 8.2)
                {
                    if(bo.get_x() == 20)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                    {
                        bewertung_180 += 2;
                    }
                    if(bo.get_y() == 20)//Gilt für HBE, Löcher mit diesem Abst. in der Fläche sind nicht zu erwarten
                    {
                        bewertung_180 += 2;
                    }
                }
            }
        }
        for(uint i=1; i<=bearb_270.zeilenanzahl() ;i++)
        {
            text_zeilenweise zeile;
            zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
            zeile.set_text(bearb_270.zeile(i));
            if(zeile.zeile(1) == BEARBART_BOHR)
            {
                bohrung bo(zeile.get_text());
                if(bo.get_dm() == 8 || \
                   bo.get_dm() == 8.2)
                {
                    if(bo.get_x() == 20)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                    {
                        bewertung_270 += 2;
                    }
                    if(bo.get_y() == 20)//Gilt für HBE, Löcher mit diesem Abst. in der Fläche sind nicht zu erwarten
                    {
                        bewertung_270 += 2;
                    }
                }
            }
        }

        //Stufe 3:
        //Teile bevorzugen, bei bei denen gilt: L > B:
        if(l_0 > b_0)
        {
            bewertung_0 += 10;
        }
        if(l_90 > b_90)
        {
            bewertung_90 += 10;
        }
        if(l_180 > b_180)
        {
            bewertung_180 += 10;
        }
        if(l_270 > b_270)
        {
            bewertung_270 += 10;
        }

        //Stufe 4:
        //Bei schmalen Teilen bevorzugen, wenn HBE nicht aus richtung des Anschlages kommt:
        if(b_0 <= schwellenwert_ay)
        {
            bool bonus = true;
            for(uint i=1; i<=bearb_0.zeilenanzahl() ;i++)
            {
                text_zeilenweise zeile;
                zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
                zeile.set_text(bearb_0.zeile(i));
                if(zeile.zeile(1) == BEARBART_BOHR)
                {
                    bohrung bo(zeile.get_text());
                    if(bo.get_bezug() == WST_BEZUG_VO)
                    {
                        bonus = false;
                    }
                }
            }
            if(bonus == true)
            {
                bewertung_0 += 1;
            }else
            {
                bewertung_0 -= 2;
            }
        }
        if(b_90 <= schwellenwert_ay)
        {
            bool bonus = true;
            for(uint i=1; i<=bearb_90.zeilenanzahl() ;i++)
            {
                text_zeilenweise zeile;
                zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
                zeile.set_text(bearb_90.zeile(i));
                if(zeile.zeile(1) == BEARBART_BOHR)
                {
                    bohrung bo(zeile.get_text());
                    if(bo.get_bezug() == WST_BEZUG_VO)
                    {
                        bonus = false;
                    }
                }
            }
            if(bonus == true)
            {
                bewertung_90 += 1;
            }else
            {
                bewertung_90 -= 2;
            }
        }
        if(b_180 <= schwellenwert_ay)
        {
            bool bonus = true;
            for(uint i=1; i<=bearb_180.zeilenanzahl() ;i++)
            {
                text_zeilenweise zeile;
                zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
                zeile.set_text(bearb_180.zeile(i));
                if(zeile.zeile(1) == BEARBART_BOHR)
                {
                    bohrung bo(zeile.get_text());
                    if(bo.get_bezug() == WST_BEZUG_VO)
                    {
                        bonus = false;
                    }
                }
            }
            if(bonus == true)
            {
                bewertung_180 += 1;
            }else
            {
                bewertung_180 -= 2;
            }
        }
        if(b_270 <= schwellenwert_ay)
        {
            bool bonus = true;
            for(uint i=1; i<=bearb_270.zeilenanzahl() ;i++)
            {
                text_zeilenweise zeile;
                zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
                zeile.set_text(bearb_270.zeile(i));
                if(zeile.zeile(1) == BEARBART_BOHR)
                {
                    bohrung bo(zeile.get_text());
                    if(bo.get_bezug() == WST_BEZUG_VO)
                    {
                        bonus = false;
                    }
                }
            }
            if(bonus == true)
            {
                bewertung_270 += 1;
            }else
            {
                bewertung_270 -= 2;
            }
        }


        //Bewertungen auswerten:
        if(bewertung_0 >= 100 && \
           bewertung_0 >= bewertung_90 && \
           bewertung_0 >= bewertung_180 && \
           bewertung_0 >= bewertung_270 )
        {
            //0 ist super:
            double tmp_l = laenge;
            double tmp_b = breite;
            text_zeilenweise tmp_bearb = bearbeitungen;
            msg = get_fmc_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b, zust_fkon);
            QString warnungen = warnungen_fmc(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
            info  = "  -> Drehung keine\n";
            info += warnungen;
        }else if(bewertung_90 >= 100 && \
                 bewertung_90 >= bewertung_0 && \
                 bewertung_90 >= bewertung_180 && \
                 bewertung_90 >= bewertung_270 )
        {
            //90 ist super:
            double tmp_l = laenge;
            double tmp_b = breite;
            text_zeilenweise tmp_bearb = bearbeitungen;
            tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
            msg = get_fmc_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b, zust_fkon);
            QString warnungen = warnungen_fmc(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
            info  = "  -> Drehung 90 Grad\n";
            info += warnungen;
        }else if(bewertung_180 >= 100 && \
                 bewertung_180 >= bewertung_0 && \
                 bewertung_180 >= bewertung_90 && \
                 bewertung_180 >= bewertung_270 )
        {
            //180 ist super:
            double tmp_l = laenge;
            double tmp_b = breite;
            text_zeilenweise tmp_bearb = bearbeitungen;
            tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
            tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
            msg = get_fmc_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b, zust_fkon);
            QString warnungen = warnungen_fmc(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
            info  = "  -> Drehung 180 Grad\n";
            info += warnungen;
        }else if(bewertung_270 >= 100 && \
                 bewertung_270 >= bewertung_0 && \
                 bewertung_270 >= bewertung_90 && \
                 bewertung_270 >= bewertung_180 )
        {
            //270 ist super:
            double tmp_l = laenge;
            double tmp_b = breite;
            text_zeilenweise tmp_bearb = bearbeitungen;
            tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
            tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
            tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
            msg = get_fmc_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b, zust_fkon);
            QString warnungen = warnungen_fmc(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
            info = "  -> Drehung 270 Grad\n";
            info += warnungen;
        }else
        {
            //wir nehmen 0:
            double tmp_l = laenge;
            double tmp_b = breite;
            text_zeilenweise tmp_bearb = bearbeitungen;
            msg = get_fmc_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b, zust_fkon);
            QString warnungen = warnungen_fmc(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
            info  = "  -> Drehung keine\n";
            info += warnungen;
        }
    }
    return msg;
}
QString werkstueck::get_ganx(text_zeilenweise wkzmagazin, QString& info , QString drehwinkel)
{
    QString msg;
    bearb_sortieren();

    if(drehwinkel == "0")
    {
        double tmp_l = breite;
        double tmp_b = laenge;
        text_zeilenweise tmp_bearb;
        tmp_bearb = bearb_optimieren_ganx(bearbeitungen);
        msg = get_ganx_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b);
        QString warnungen = warnungen_ganx(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
        info  = "\n";
        info += warnungen;
    }else if(drehwinkel == "90")
    {
        double tmp_l = breite;
        double tmp_b = laenge;
        text_zeilenweise tmp_bearb;
        tmp_bearb = bearb_optimieren_ganx(bearbeitungen);
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        msg = get_ganx_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b);
        QString warnungen = warnungen_ganx(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
        info  = "\n";
        info += warnungen;
    }else if(drehwinkel == "180")
    {
        double tmp_l = breite;
        double tmp_b = laenge;
        text_zeilenweise tmp_bearb;
        tmp_bearb = bearb_optimieren_ganx(bearbeitungen);
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        msg = get_ganx_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b);
        QString warnungen = warnungen_ganx(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
        info  = "\n";
        info += warnungen;
    }else if(drehwinkel == "270")
    {
        double tmp_l = breite;
        double tmp_b = laenge;
        text_zeilenweise tmp_bearb;
        tmp_bearb = bearb_optimieren_ganx(bearbeitungen);
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        msg = get_ganx_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b);
        QString warnungen = warnungen_ganx(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
        info  = "\n";
        info += warnungen;
    }else
    {
        double tmp_l = breite;
        double tmp_b = laenge;
        text_zeilenweise tmp_bearb;
        tmp_bearb = bearb_optimieren_ganx(bearbeitungen);

        //Die beste Drehrichtung herausfinden:
        uint bewertung_0    = 1;
        uint bewertung_90   = 1;
        uint bewertung_180  = 1;
        uint bewertung_270  = 1;
        //Stufe 1:
        //heraus bekommen, für welche Lage es Warnungen gibt:
        QString warnung;
        text_zeilenweise bearb_kopie = tmp_bearb;
        double l_kopie = tmp_l;
        double b_kopie = tmp_b;
        //------------------------0:
        warnung = warnungen_ganx(bearb_kopie, l_kopie, b_kopie, wkzmagazin);
        if(warnung.isEmpty())
        {
            bewertung_0 = 100;
        }else
        {
            bewertung_0 = 0;
        }
        text_zeilenweise bearb_0 = bearb_kopie;
        double l_0 = l_kopie;
        double b_0 = b_kopie;
        //------------------------90:
        bearb_kopie = bearb_drehen_90(bearb_kopie, l_kopie, b_kopie);
        warnung = warnungen_ganx(bearb_kopie, l_kopie, b_kopie, wkzmagazin);
        if(warnung.isEmpty())
        {
            bewertung_90 = 100;
        }else
        {
            bewertung_90 = 0;
        }
        text_zeilenweise bearb_90 = bearb_kopie;
        double l_90 = l_kopie;
        double b_90 = b_kopie;
        //------------------------180:
        bearb_kopie = bearb_drehen_90(bearb_kopie, l_kopie, b_kopie);
        warnung = warnungen_ganx(bearb_kopie, l_kopie, b_kopie, wkzmagazin);
        if(warnung.isEmpty())
        {
            bewertung_180 = 100;
        }else
        {
            bewertung_180 = 0;
        }
        text_zeilenweise bearb_180 = bearb_kopie;
        double l_180 = l_kopie;
        double b_180 = b_kopie;
        //------------------------270:
        bearb_kopie = bearb_drehen_90(bearb_kopie, l_kopie, b_kopie);
        warnung = warnungen_ganx(bearb_kopie, l_kopie, b_kopie, wkzmagazin);
        if(warnung.isEmpty())
        {
            bewertung_270 = 100;
        }else
        {
            bewertung_270 = 0;
        }
        text_zeilenweise bearb_270 = bearb_kopie;
        double l_270 = l_kopie;
        double b_270 = b_kopie;

        //Stufe 2:
        //heraus bekommen wo vorne ist:
        for(uint i=1; i<=bearb_0.zeilenanzahl() ;i++)
        {
            text_zeilenweise zeile;
            zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
            zeile.set_text(bearb_0.zeile(i));
            if(zeile.zeile(1) == BEARBART_BOHR)
            {
                bohrung bo(zeile.get_text());
                if(bo.get_dm() == 8 || \
                   bo.get_dm() == 8.2)
                {
                    if(bo.get_x() == 20)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                    {
                        bewertung_0 += 2;
                    }
                    if(bo.get_y() == b_0-20)//Gilt für HBE, Löcher mit diesem Abst. in der Fläche sind nicht zu erwarten
                    {
                        bewertung_0 += 2;
                    }
                }
            }
        }
        for(uint i=1; i<=bearb_90.zeilenanzahl() ;i++)
        {
            text_zeilenweise zeile;
            zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
            zeile.set_text(bearb_90.zeile(i));
            if(zeile.zeile(1) == BEARBART_BOHR)
            {
                bohrung bo(zeile.get_text());
                if(bo.get_dm() == 8 || \
                   bo.get_dm() == 8.2)
                {
                    if(bo.get_x() == 20)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                    {
                        bewertung_90 += 2;
                    }
                    if(bo.get_y() == b_90-20)//Gilt für HBE, Löcher mit diesem Abst. in der Fläche sind nicht zu erwarten
                    {
                        bewertung_90 += 2;
                    }
                }
            }
        }
        for(uint i=1; i<=bearb_180.zeilenanzahl() ;i++)
        {
            text_zeilenweise zeile;
            zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
            zeile.set_text(bearb_180.zeile(i));
            if(zeile.zeile(1) == BEARBART_BOHR)
            {
                bohrung bo(zeile.get_text());
                if(bo.get_dm() == 8 || \
                   bo.get_dm() == 8.2)
                {
                    if(bo.get_x() == 20)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                    {
                        bewertung_180 += 2;
                    }
                    if(bo.get_y() == b_180-20)//Gilt für HBE, Löcher mit diesem Abst. in der Fläche sind nicht zu erwarten
                    {
                        bewertung_180 += 2;
                    }
                }
            }
        }
        for(uint i=1; i<=bearb_270.zeilenanzahl() ;i++)
        {
            text_zeilenweise zeile;
            zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
            zeile.set_text(bearb_270.zeile(i));
            if(zeile.zeile(1) == BEARBART_BOHR)
            {
                bohrung bo(zeile.get_text());
                if(bo.get_dm() == 8 || \
                   bo.get_dm() == 8.2)
                {
                    if(bo.get_x() == 20)//Gilt für alle Bohrungen ob HBE oder nicht ist hier egal
                    {
                        bewertung_270 += 2;
                    }
                    if(bo.get_y() == b_270-20)//Gilt für HBE, Löcher mit diesem Abst. in der Fläche sind nicht zu erwarten
                    {
                        bewertung_270 += 2;
                    }
                }
            }
        }

        //Stufe 3:
        //Teile bevorzugen, bei bei denen gilt: B > L:
        if(b_0 > l_0)
        {
            bewertung_0 += 2;
        }
        if(b_90 > l_90)
        {
            bewertung_90 += 2;
        }
        if(b_180 > l_180)
        {
            bewertung_180 += 2;
        }
        if(b_270 > l_270)
        {
            bewertung_270 += 2;
        }

        //Bewertungen auswerten:
        if(bewertung_0 >= 100 && \
           bewertung_0 >= bewertung_90 && \
           bewertung_0 >= bewertung_180 && \
           bewertung_0 >= bewertung_270 )
        {
            //0 ist super:
            double tmp_l = breite;
            double tmp_b = laenge;
            text_zeilenweise tmp_bearb;
            tmp_bearb = bearb_optimieren_ganx(bearbeitungen);
            msg = get_ganx_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b);
            QString warnungen = warnungen_ganx(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
            info  = "  -> Drehung keine\n";
            info += warnungen;
        }else if(bewertung_90 >= 100 && \
                 bewertung_90 >= bewertung_0 && \
                 bewertung_90 >= bewertung_180 && \
                 bewertung_90 >= bewertung_270 )
        {
            //90 ist super:
            double tmp_l = breite;
            double tmp_b = laenge;
            text_zeilenweise tmp_bearb;
            tmp_bearb = bearb_optimieren_ganx(bearbeitungen);
            tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
            msg = get_ganx_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b);
            QString warnungen = warnungen_ganx(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
            info  = "  -> Drehung 90 Grad\n";
            info += warnungen;
        }else if(bewertung_180 >= 100 && \
                 bewertung_180 >= bewertung_0 && \
                 bewertung_180 >= bewertung_90 && \
                 bewertung_180 >= bewertung_270 )
        {
            //180 ist super:
            double tmp_l = breite;
            double tmp_b = laenge;
            text_zeilenweise tmp_bearb;
            tmp_bearb = bearb_optimieren_ganx(bearbeitungen);
            tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
            tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
            msg = get_ganx_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b);
            QString warnungen = warnungen_ganx(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
            info  = "  -> Drehung 180 Grad\n";
            info += warnungen;
        }else if(bewertung_270 >= 100 && \
                 bewertung_270 >= bewertung_0 && \
                 bewertung_270 >= bewertung_90 && \
                 bewertung_270 >= bewertung_180 )
        {
            //270 ist super:
            double tmp_l = breite;
            double tmp_b = laenge;
            text_zeilenweise tmp_bearb;
            tmp_bearb = bearb_optimieren_ganx(bearbeitungen);
            tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
            tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
            tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
            msg = get_ganx_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b);
            QString warnungen = warnungen_ganx(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
            info  = "  -> Drehung 270 Grad\n";
            info += warnungen;
        }else
        {
            //wir nehmen 0:
            double tmp_l = breite;
            double tmp_b = laenge;
            text_zeilenweise tmp_bearb;
            tmp_bearb = bearb_optimieren_ganx(bearbeitungen);
            msg = get_ganx_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b);
            QString warnungen = warnungen_ganx(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
            info  = "  -> Drehung keine\n";
            info += warnungen;
        }
    }
    return msg;
}
QString werkstueck::get_eigenses_format(QString drehwinkel, QString ausgabeformat, text_zeilenweise wkzmagazin)
{
    QString msg;
    bearb_sortieren();

    if(drehwinkel == "0")
    {
        double tmp_l = laenge;
        double tmp_b = breite;
        text_zeilenweise tmp_bearb = bearbeitungen;
        if(ausgabeformat == GANX)
        {
            tmp_l = breite;
            tmp_b = laenge;
            tmp_bearb = bearb_optimieren_ganx(bearbeitungen); //nur zu Testzwecken
        }
        msg = get_eigen_dateitext(tmp_bearb, tmp_l, tmp_b, ausgabeformat, wkzmagazin);
    }else if(drehwinkel == "90")
    {
        double tmp_l = laenge;
        double tmp_b = breite;
        text_zeilenweise tmp_bearb = bearbeitungen;
        if(ausgabeformat == GANX)
        {
            tmp_l = breite;
            tmp_b = laenge;
            tmp_bearb = bearb_optimieren_ganx(bearbeitungen); //nur zu Testzwecken
        }
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);        
        msg = get_eigen_dateitext(tmp_bearb, tmp_l, tmp_b, ausgabeformat, wkzmagazin);
    }else if(drehwinkel == "180")
    {
        double tmp_l = laenge;
        double tmp_b = breite;
        text_zeilenweise tmp_bearb = bearbeitungen;
        if(ausgabeformat == GANX)
        {
            tmp_l = breite;
            tmp_b = laenge;
            tmp_bearb = bearb_optimieren_ganx(bearbeitungen); //nur zu Testzwecken
        }
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        msg = get_eigen_dateitext(tmp_bearb, tmp_l, tmp_b, ausgabeformat, wkzmagazin);
    }else if(drehwinkel == "270")
    {
        double tmp_l = laenge;
        double tmp_b = breite;
        text_zeilenweise tmp_bearb = bearbeitungen;
        if(ausgabeformat == GANX)
        {
            tmp_l = breite;
            tmp_b = laenge;
            tmp_bearb = bearb_optimieren_ganx(bearbeitungen); //nur zu Testzwecken
        }
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        msg = get_eigen_dateitext(tmp_bearb, tmp_l, tmp_b, ausgabeformat, wkzmagazin);
    }else
    {
        //drehung 0:
        double tmp_l = laenge;
        double tmp_b = breite;
        text_zeilenweise tmp_bearb = bearbeitungen;
        if(ausgabeformat == GANX)
        {
            tmp_l = breite;
            tmp_b = laenge;
            tmp_bearb = bearb_optimieren_ganx(bearbeitungen); //nur zu Testzwecken
        }
        msg = get_eigen_dateitext(tmp_bearb, tmp_l, tmp_b, ausgabeformat, wkzmagazin);
    }
    return msg;
}

QString werkstueck::get_ganx_dateitext(text_zeilenweise wkzmagazin, text_zeilenweise bearb, \
                                       double tmp_l, double tmp_b)
{
    bearb = rasterbohrungen_finden_ganx(bearb, wkzmagazin, tmp_l, tmp_b);
    QString msg;
    text_zeilenweise zeile;
    zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
    double bezugsmass = 40;    //Referenzmaß zum Erkennen der Bezugskante
    werkzeugmagazin wkzmag(wkzmagazin);

    //-------------------------1.Vorspann:
    {
    msg  = "<?xml version=\"1.0\" standalone=\"yes\"?>";
    msg += "\n";
    msg += "<Programm xmlns=\"http://tempuri.org/Programm.xsd\">";
    msg += "\n";
    }
    //-------------------------Programmkopf:
    {
    msg += "  <PrgrSet>";
    msg += "\n";
    msg += "    <PrgrName>";
    msg += name;
    msg += "</PrgrName>";
    msg += "\n";
    msg += "    <Description>";
    msg += "";                       //Kommentar
    msg += "</Description>";
    msg += "\n";
    msg += "    <wsX>";
    msg += double_to_qstring(tmp_l);
    msg += "</wsX>";
    msg += "\n";
    msg += "    <wsY>";
    msg += double_to_qstring(tmp_b);
    msg += "</wsY>";
    msg += "\n";
    msg += "    <wsZ>";
    msg += get_dicke_qstring();
    msg += "</wsZ>";
    msg += "\n";
    msg += "    <DoMF>";
    msg += "False";          //Maxifix
    msg += "</DoMF>";
    msg += "\n";
    msg += "    <MFPos>";
    msg += "0";              //Position Maxitix
    msg += "</MFPos>";
    msg += "\n";
    msg += "    <MFTool>";
    msg += "TO";             //Werkzeug für Maxifix
    msg += "</MFTool>";
    msg += "\n";
    msg += "  </PrgrSet>";
    msg += "\n";
    }
    //-------------------------2. Vorspann:
    {
    msg += "  <Root>";
    msg += "\n";
    msg += "    <Version>1.1.0.26</Version>";
    msg += "\n";
    msg += "    <CreationDate>2017-06-02T09:26:14.9442359+02:00</CreationDate>";
    msg += "\n";
    msg += "    <CreationApp>ASCII Import - 1.1.0.26</CreationApp>";
    msg += "\n";
    msg += "    <ModificationApp />";
    msg += "\n";
    msg += "  </Root>";
    msg += "\n";
    }
    //-------------------------Bearbeitungen <PrgrFileWork>:
    //Dies ist der Teil, den die Maschinen-Steuerung liest
    //Hier darf nur mit absoluten Zahlen gearbeitet werden
    //Die Ausgabe von Formeln wird von der Maschinen-steuerung nicht unterstützt
    uint id = 1; //id für die Maschiene
    uint ideditor = 1;//id die im Editor angezeigt wird
    ganx_Gruppen gruppen_PrgrFileWork;

    for(uint i=1 ; i<=bearb.zeilenanzahl() ; i++)
    {
        zeile.set_text(bearb.zeile(i));
        if(zeile.zeile(1) == BEARBART_BOHR)
        {
            bohrung bo(zeile.get_text());

            QString afb_text = bo.get_afb();
            afb_text.replace("L", get_laenge_qstring());
            afb_text.replace("B", get_breite_qstring());
            afb_text.replace("D", get_dicke_qstring());
            afb_text.replace(",", ".");
            afb_text = ausdruck_auswerten(afb_text);
            if(afb_text.toDouble() == 0)
            {
                continue;
            }

            double x = bo.get_x();
            double y = bo.get_y();
            double z = bo.get_z();
            double dm = bo.get_dm();
            double laenge_y = tmp_b;
            QString bezug = bo.get_bezug();

            //Y-Maß bezieht sich hier immer auf den Nullpunkt der Wst oben links
            //die Maße intern beziehen sich immer auf Nullpunkt unten links
            //das heißt, die Y-Maße müssen an dieser Stelle gegengerechnet werden:
            y = tmp_b - y;

            QString tnummer = wkzmag.get_wkznummer(WKZ_TYP_BOHRER, dm, bo.get_tiefe(), dicke, bezug);
            if(!tnummer.isEmpty())
            {
                //Werkzeug wurde gefunden, Bohrung kann gebohrt werden:

                //Anzahl der Zustellungen berechnen:
                double zustmass = bo.get_zustellmass();
                if(zustmass <= 0)
                {
                    zustmass = wkzmag.get_zustellmass(tnummer).toDouble();
                }
                int zustellungen = aufrunden(bo.get_tiefe() / zustmass);
                if(zustellungen <= 0)
                {
                    zustellungen = 1;
                }
                zustmass = bo.get_tiefe()/zustellungen;
                //-------------------------------

                if(bezug == WST_BEZUG_OBSEI)
                {
                    //x = Breite
                    //y = Länge
                    //z = Tiefe
                    double aktti; //aktuelle Tiefe
                    aktti = zustmass;
                    while(aktti <= bo.get_tiefe())
                    {
                        msg += "  <PrgrFileWork>";
                        msg += "\n";
                        msg += "    <CntID>";
                        msg += int_to_qstring(id);               //ID-Nummer
                        msg += "</CntID>";
                        msg += "\n";
                        msg += "    <Plane>Top</Plane>";
                        msg += "\n";
                        //----------------------Bezugskante festlegen:
                        msg += "    <Ref>";
                        //y < 40 -> TL
                        //Länge - y < 40 ->BL
                        QString ref;
                        if(laenge_y - y < bezugsmass)
                        {
                            ref += GANX_REF_OBEN_LINKS;
                        }else
                        {
                            ref += GANX_REF_UNTEN_LINKS;
                        }
                        msg += ref;
                        msg += "</Ref>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Typ>B</Typ>";
                        msg += "\n";
                        //----------------------
                        msg += "    <X>";
                        msg += double_to_qstring(x);
                        msg += "</X>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Y>";
                        msg += double_to_qstring(y);
                        msg += "</Y>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Z>";
                        msg += double_to_qstring(0);
                        msg += "</Z>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Diameter>";
                        msg += wkzmag.get_dm(tnummer);
                        msg += "</Diameter>";
                        msg += "\n";
                        //----------------------
                        msg += "   <Depth>";
                        msg += double_to_qstring(aktti);
                        msg += "</Depth>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Tool>";
                        msg += tnummer;
                        msg += "</Tool>";
                        msg += "\n";
                        //----------------------
                        msg += "    <OldID>";
                        msg += GANX_WST_BEZUG_OBSEI;
                        msg += "\\";
                        msg += ref;
                        msg += "\\";
                        msg += "B-";
                        msg += int_to_qstring(ideditor);               //ID-Nummer
                        msg += "</OldID>";
                        msg += "\n";
                        //----------------------
                        msg += "    <KleiGeTei>";    //Zustelltiefe
                        msg += double_to_qstring(zustmass);
                        msg += "</KleiGeTei>";
                        msg += "\n";
                        //----------------------
                        msg += "  </PrgrFileWork>";
                        msg += "\n";

                        id++;
                        aktti = aktti + zustmass;
                    }
                    ideditor++;


                }else if(bezug == WST_BEZUG_UNSEI)
                {
                    //x = Breite
                    //y = Länge
                    //z = Tiefe
                    double aktti; //aktuelle Tiefe
                    aktti = zustmass;
                    while(aktti <= bo.get_tiefe())
                    {
                        msg += "  <PrgrFileWork>";
                        msg += "\n";
                        msg += "    <CntID>";
                        msg += int_to_qstring(id);               //ID-Nummer
                        msg += "</CntID>";
                        msg += "\n";
                        msg += "    <Plane>Bottom</Plane>";
                        msg += "\n";
                        //----------------------Bezugskante festlegen:
                        msg += "    <Ref>";
                        //y < 40 -> TL
                        //Länge - y < 40 ->BL
                        QString ref;
                        if(laenge_y - y < bezugsmass)
                        {
                            ref = GANX_REF_OBEN_LINKS;
                        }else
                        {
                            ref = GANX_REF_UNTEN_LINKS;
                        }
                        msg += ref;
                        msg += "</Ref>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Typ>B</Typ>";
                        msg += "\n";
                        //----------------------
                        msg += "    <X>";
                        msg += double_to_qstring(x);
                        msg += "</X>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Y>";
                        msg += double_to_qstring(y);
                        msg += "</Y>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Z>";
                        msg += double_to_qstring(0);
                        msg += "</Z>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Diameter>";
                        msg += wkzmag.get_dm(tnummer);
                        msg += "</Diameter>";
                        msg += "\n";
                        //----------------------
                        msg += "   <Depth>";
                        msg += double_to_qstring(aktti);
                        msg += "</Depth>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Tool>";
                        msg += tnummer;
                        msg += "</Tool>";
                        msg += "\n";
                        //----------------------
                        msg += "    <OldID>";
                        msg += GANX_WST_BEZUG_UNSEI;
                        msg += "\\";
                        msg += ref;
                        msg += "\\";
                        msg += "B-";
                        msg += int_to_qstring(ideditor);               //ID-Nummer
                        msg += "</OldID>";
                        msg += "\n";
                        //----------------------
                        msg += "    <KleiGeTei>";    //Zustelltiefe
                        msg += double_to_qstring(zustmass);
                        msg += "</KleiGeTei>";
                        msg += "\n";
                        //----------------------
                        msg += "  </PrgrFileWork>";
                        msg += "\n";

                        id++;
                        aktti = aktti + zustmass;
                    }
                    ideditor++;

                }else if(bezug == WST_BEZUG_LI)
                {
                    //x = Tiefe
                    //y = Y-Pos
                    //z = Z-Pos
                    double aktti; //aktuelle Tiefe
                    aktti = zustmass;
                    while(aktti <= bo.get_tiefe())
                    {
                        msg += "  <PrgrFileWork>";
                        msg += "\n";
                        msg += "    <CntID>";
                        msg += int_to_qstring(id);               //ID-Nummer
                        msg += "</CntID>";
                        msg += "\n";
                        msg += "    <Plane>Left</Plane>";
                        msg += "\n";
                        //----------------------Bezugskante festlegen:
                        msg += "    <Ref>";
                        QString ref = GANX_REF_UNTEN_LINKS;
                        msg += ref;
                        msg += "</Ref>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Typ>B</Typ>";
                        msg += "\n";
                        //----------------------
                        msg += "    <X>";
                        msg += double_to_qstring(0);
                        msg += "</X>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Y>";
                        msg += double_to_qstring(y);
                        msg += "</Y>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Z>";
                        msg += double_to_qstring(z);
                        msg += "</Z>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Diameter>";
                        msg += wkzmag.get_dm(tnummer);
                        msg += "</Diameter>";
                        msg += "\n";
                        //----------------------
                        msg += "   <Depth>";
                        msg += double_to_qstring(aktti);
                        msg += "</Depth>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Tool>";
                        msg += tnummer;
                        msg += "</Tool>";
                        msg += "\n";
                        //----------------------
                        msg += "    <OldID>";
                        msg += GANX_WST_BEZUG_LI;
                        msg += "\\";
                        msg += ref;
                        msg += "\\";
                        msg += "B-";
                        msg += int_to_qstring(ideditor);               //ID-Nummer
                        msg += "</OldID>";
                        msg += "\n";
                        //----------------------
                        msg += "    <KleiGeTei>";    //Zustelltiefe
                        msg += double_to_qstring(zustmass);
                        msg += "</KleiGeTei>";
                        msg += "\n";
                        //----------------------
                        msg += "  </PrgrFileWork>";
                        msg += "\n";

                        id++;
                        aktti = aktti + zustmass;
                    }
                    ideditor++;

                }else if(bezug == WST_BEZUG_RE)
                {
                    //x = Tiefe
                    //y = Y-Pos
                    //z = Z-Pos
                    double aktti; //aktuelle Tiefe
                    aktti = zustmass;
                    while(aktti <= bo.get_tiefe())
                    {
                        msg += "  <PrgrFileWork>";
                        msg += "\n";
                        msg += "    <CntID>";
                        msg += int_to_qstring(id);               //ID-Nummer
                        msg += "</CntID>";
                        msg += "\n";
                        msg += "    <Plane>Right</Plane>";
                        msg += "\n";
                        //----------------------Bezugskante festlegen:
                        msg += "    <Ref>";
                        QString ref = GANX_REF_UNTEN_RECHTS;
                        msg += ref;
                        msg += "</Ref>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Typ>B</Typ>";
                        msg += "\n";
                        //----------------------
                        msg += "    <X>";
                        msg += double_to_qstring(0);
                        msg += "</X>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Y>";
                        msg += double_to_qstring(y);
                        msg += "</Y>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Z>";
                        msg += double_to_qstring(z);
                        msg += "</Z>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Diameter>";
                        msg += wkzmag.get_dm(tnummer);
                        msg += "</Diameter>";
                        msg += "\n";
                        //----------------------
                        msg += "   <Depth>";
                        msg += double_to_qstring(aktti);
                        msg += "</Depth>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Tool>";
                        msg += tnummer;
                        msg += "</Tool>";
                        msg += "\n";
                        //----------------------
                        msg += "    <OldID>";
                        msg += GANX_WST_BEZUG_RE;
                        msg += "\\";
                        msg += ref;
                        msg += "\\";
                        msg += "B-";
                        msg += int_to_qstring(ideditor);               //ID-Nummer
                        msg += "</OldID>";
                        msg += "\n";
                        //----------------------
                        msg += "    <KleiGeTei>";    //Zustelltiefe
                        msg += double_to_qstring(zustmass);
                        msg += "</KleiGeTei>";
                        msg += "\n";
                        //----------------------
                        msg += "  </PrgrFileWork>";
                        msg += "\n";

                        id++;
                        aktti = aktti + zustmass;
                    }
                    ideditor++;

                }else if(bezug == WST_BEZUG_VO)
                {
                    //x = X-Pos
                    //y = Tiefe
                    //z = Z-Pos
                    double aktti; //aktuelle Tiefe
                    aktti = zustmass;
                    while(aktti <= bo.get_tiefe())
                    {
                        msg += "  <PrgrFileWork>";
                        msg += "\n";
                        msg += "    <CntID>";
                        msg += int_to_qstring(id);               //ID-Nummer
                        msg += "</CntID>";
                        msg += "\n";
                        msg += "    <Plane>Front</Plane>";
                        msg += "\n";
                        //----------------------Bezugskante festlegen:
                        msg += "    <Ref>";
                        QString ref = GANX_REF_UNTEN_LINKS;
                        msg += ref;
                        msg += "</Ref>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Typ>B</Typ>";
                        msg += "\n";
                        //----------------------
                        msg += "    <X>";
                        msg += double_to_qstring(x);
                        msg += "</X>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Y>";
                        msg += double_to_qstring(0);
                        msg += "</Y>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Z>";
                        msg += double_to_qstring(z);
                        msg += "</Z>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Diameter>";
                        msg += wkzmag.get_dm(tnummer);
                        msg += "</Diameter>";
                        msg += "\n";
                        //----------------------
                        msg += "   <Depth>";
                        msg += double_to_qstring(aktti);
                        msg += "</Depth>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Tool>";
                        msg += tnummer;
                        msg += "</Tool>";
                        msg += "\n";
                        //----------------------
                        msg += "    <OldID>";
                        msg += GANX_WST_BEZUG_VO;
                        msg += "\\";
                        msg += ref;
                        msg += "\\";
                        msg += "B-";
                        msg += int_to_qstring(ideditor);               //ID-Nummer
                        msg += "</OldID>";
                        msg += "\n";
                        //----------------------
                        msg += "    <KleiGeTei>";    //Zustelltiefe
                        msg += double_to_qstring(zustmass);
                        msg += "</KleiGeTei>";
                        msg += "\n";
                        //----------------------
                        msg += "  </PrgrFileWork>";
                        msg += "\n";

                        id++;
                        aktti = aktti + zustmass;
                    }
                    ideditor++;

                }else if(bezug == WST_BEZUG_HI)
                {
                    //x = X-Pos
                    //y = Tiefe
                    //z = Z-Pos
                    double aktti; //aktuelle Tiefe
                    aktti = zustmass;
                    while(aktti <= bo.get_tiefe())
                    {
                        msg += "  <PrgrFileWork>";
                        msg += "\n";
                        msg += "    <CntID>";
                        msg += int_to_qstring(id);               //ID-Nummer
                        msg += "</CntID>";
                        msg += "\n";
                        msg += "    <Plane>Rear</Plane>";
                        msg += "\n";
                        //----------------------Bezugskante festlegen:
                        msg += "    <Ref>";
                        QString ref = GANX_REF_OBEN_LINKS;
                        msg += ref;
                        msg += "</Ref>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Typ>B</Typ>";
                        msg += "\n";
                        //----------------------
                        msg += "    <X>";
                        msg += double_to_qstring(x);
                        msg += "</X>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Y>";
                        msg += double_to_qstring(0);
                        msg += "</Y>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Z>";
                        msg += double_to_qstring(z);
                        msg += "</Z>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Diameter>";
                        msg += wkzmag.get_dm(tnummer);
                        msg += "</Diameter>";
                        msg += "\n";
                        //----------------------
                        msg += "   <Depth>";
                        msg += double_to_qstring(aktti);
                        msg += "</Depth>";
                        msg += "\n";
                        //----------------------
                        msg += "    <Tool>";
                        msg += tnummer;
                        msg += "</Tool>";
                        msg += "\n";
                        //----------------------
                        msg += "    <OldID>";
                        msg += GANX_WST_BEZUG_HI;
                        msg += "\\";
                        msg += ref;
                        msg += "\\";
                        msg += "B-";
                        msg += int_to_qstring(ideditor);               //ID-Nummer
                        msg += "</OldID>";
                        msg += "\n";
                        //----------------------
                        msg += "    <KleiGeTei>";    //Zustelltiefe
                        msg += double_to_qstring(zustmass);
                        msg += "</KleiGeTei>";
                        msg += "\n";
                        //----------------------
                        msg += "  </PrgrFileWork>";
                        msg += "\n";

                        id++;
                        aktti = aktti + zustmass;
                    }
                    ideditor++;

                }

            }else
            {
                //Kein Werkzeug wurde gefunden.
                //Kann Bohrung als Kreistasche gefräst werden?:
                tnummer = wkzmag.get_wkznummer_von_alias(bo.get_wkznum());//Ist direkt ei WKZ definiert?
                if(tnummer.isEmpty())
                {
                    tnummer = wkzmag.get_wkznummer(WKZ_TYP_FRAESER, dm, bo.get_tiefe(), dicke, bezug);
                }

                if(!tnummer.isEmpty())
                {
                    //Werkzeug wurde gefunden, Kreistasche kann gefräst werden:

                    QString ti = bo.get_tiefe_qstring();
                    /*
                     * Formeln sind nicht zulässig:
                    if(ti.toDouble() > get_dicke())
                    {
                        QString tmp = "{LZ}+";
                        double dif = ti.toDouble() - get_dicke();
                        tmp += double_to_qstring(dif);
                        ti = tmp;
                    }
                    */
                    //Anzahl der Zustellungen berechnen:
                    double zustmass = bo.get_zustellmass();
                    if(zustmass <= 0)
                    {
                        zustmass = wkzmag.get_zustellmass(tnummer).toDouble();
                    }
                    int zustellungen = aufrunden(bo.get_tiefe() / zustmass);

                    if(zustellungen <= 0)
                    {
                        zustellungen = 1;
                    }


                    msg += "  <PrgrFileWork>";
                    msg += "\n";
                    //----------------------
                    msg += "    <CntID>";
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</CntID>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Plane>";
                    if(bo.get_bezug() == WST_BEZUG_OBSEI)
                    {
                        msg += GANX_WST_BEZUG_OBSEI;
                    }else
                    {
                        msg += GANX_WST_BEZUG_UNSEI;
                    }
                    msg += "</Plane>";
                    msg += "\n";
                    //----------------------Bezugskante festlegen:
                    QString ref;
                    if(laenge_y - y < bezugsmass)
                    {
                        ref = GANX_REF_OBEN_LINKS;
                    }else
                    {
                        ref = GANX_REF_UNTEN_LINKS;
                    }
                    msg += "    <Ref>";
                    msg += ref;
                    msg += "</Ref>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Typ>M</Typ>";
                    msg += "\n";
                    //----------------------
                    msg += "    <X>";
                    msg += double_to_qstring(x);
                    msg += "</X>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Y>";
                    msg += double_to_qstring(y);
                    msg += "</Y>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Z>";
                    msg += double_to_qstring(0);
                    msg += "</Z>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Tool>";
                    msg += tnummer;
                    msg += "</Tool>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Mill>";
                    msg += "2";                      //Kreistasche
                    msg += ";";
                    msg += double_to_qstring(dm);
                    msg += ";";
                    msg += ti;                       //TaTi
                    msg += ";";
                    msg += "2";                      //Variante der Kreistasche (2 = ausgeräumt)
                    msg += ";";
                    msg += "GL";                     //Gleichlauf (GL = Gleichlauf / GG = Gegenlauf)
                    msg += ";";
                    msg += wkzmag.get_vorschub(tnummer);
                    msg += ";";
                    msg += int_to_qstring(zustellungen);
                    msg += "</Mill>";
                    msg += "\n";
                    //----------------------
                    msg += "    <ImageKey>KR</ImageKey>";
                    msg += "\n";
                    //----------------------
                    msg += "    <OldID>";
                    if(bo.get_bezug() == WST_BEZUG_OBSEI)
                    {
                        msg += GANX_WST_BEZUG_OBSEI;
                    }else
                    {
                        msg += GANX_WST_BEZUG_UNSEI;
                    }
                    msg += "\\";
                    msg += GANX_REF_OBEN_LINKS;
                    msg += "\\";
                    msg += "M-";
                    msg += int_to_qstring(ideditor);               //ID-Nummer
                    msg += "</OldID>";
                    msg += "\n";
                    //----------------------
                    msg += "    <KleiGeTei>";
                    msg += "0";
                    msg += "</KleiGeTei>";
                    msg += "\n";
                    //----------------------
                    msg += "  </PrgrFileWork>";
                    msg += "\n";

                    id++;
                    ideditor++;

                }else
                {
                    QString msg = fehler_kein_WKZ("ganx", zeile);
                    QMessageBox mb;
                    mb.setText(msg);
                    mb.exec();
                    return msg;
                }
            }
        }else if(zeile.zeile(1) == BEARBART_BOHRRASTER)
        {
            bohrraster bora(zeile.get_text());
            double x = bora.get_x();
            double y = bora.get_y();
            //double z = bora.get_z();
            double dm = bora.get_dm();
            double laenge_y = tmp_b;
            QString bezug = bora.get_bezug();

            //Y-Maß bezieht sich hier immer auf den Nullpunkt der Wst oben links
            //die Maße intern beziehen sich immer auf Nullpunkt unten links
            //das heißt, die Y-Maße müssen an dieser Stelle gegengerechnet werden:
            y = tmp_b - y;

            QString tnummer = wkzmag.get_wkznummer(WKZ_TYP_BOHRER, dm, bora.get_tiefe(), dicke, bezug);
            if(!tnummer.isEmpty())
            {
                //Anzahl der Zustellungen berechnen:
                double zustmass = bora.get_zustellmass();
                if(zustmass <= 0)
                {
                    zustmass = wkzmag.get_zustellmass(tnummer).toDouble();
                }
                int zustellungen = aufrunden(bora.get_tiefe() / zustmass);
                if(zustellungen <= 0)
                {
                    zustellungen = 1;
                }
                zustmass = bora.get_tiefe()/zustellungen;
                //-------------------------------

                if(bezug == WST_BEZUG_OBSEI  ||  bezug == WST_BEZUG_UNSEI)
                {
                    for(uint i=1; i<=bora.get_anz_y() ;i++)
                    {
                        y = tmp_b - (  bora.get_y()+(bora.get_raster_y()*(i-1))  );

                        for(uint ii=1; ii<=bora.get_anz_x() ;ii++)
                        {
                            x = bora.get_x()+(bora.get_raster_x()*(ii-1));
                            //x = Breite
                            //y = Länge
                            //z = Tiefe
                            double aktti; //aktuelle Tiefe
                            aktti = zustmass;
                            while(aktti <= bora.get_tiefe())
                            {
                                msg += "  <PrgrFileWork>";
                                msg += "\n";
                                //----------------------
                                msg += "    <CntID>";
                                msg += int_to_qstring(id);               //ID-Nummer
                                msg += "</CntID>";
                                msg += "\n";
                                //----------------------
                                msg += "    <Plane>";
                                if(bezug == WST_BEZUG_OBSEI)
                                {
                                    msg += GANX_WST_BEZUG_OBSEI;
                                }else
                                {
                                    msg += GANX_WST_BEZUG_UNSEI;
                                }
                                msg += "</Plane>";
                                msg += "\n";
                                //----------------------
                                msg += "    <Ref>";
                                QString ref;
                                if(  laenge_y - y < bezugsmass  &&  bora.get_anz_y()==1  )
                                {
                                    ref += GANX_REF_OBEN_LINKS;
                                }else
                                {
                                    ref += GANX_REF_UNTEN_LINKS;
                                }
                                msg += ref;
                                msg += "</Ref>";
                                msg += "\n";
                                //----------------------
                                msg += "    <Typ>B</Typ>";
                                msg += "\n";
                                //----------------------
                                msg += "    <X>";
                                msg += double_to_qstring(x);
                                msg += "</X>";
                                msg += "\n";
                                //----------------------
                                msg += "    <Y>";
                                msg += double_to_qstring(y);
                                msg += "</Y>";
                                msg += "\n";
                                //----------------------
                                msg += "    <Z>";
                                msg += double_to_qstring(0);
                                msg += "</Z>";
                                msg += "\n";
                                //----------------------
                                msg += "    <Diameter>";
                                msg += wkzmag.get_dm(tnummer);
                                msg +="</Diameter>";
                                msg += "\n";
                                //----------------------
                                msg += "    <Depth>";
                                msg += double_to_qstring(aktti);
                                msg += "</Depth>";
                                msg += "\n";
                                //----------------------
                                msg += "    <DblB>false</DblB>";
                                msg += "\n";
                                //----------------------
                                msg += "    <DblL>false</DblL>";
                                msg += "\n";
                                //----------------------
                                msg += "    <DblE>false</DblE>";
                                msg += "\n";
                                //----------------------
                                msg += "    <Tool>";
                                msg += tnummer;
                                msg += "</Tool>";
                                msg += "\n";
                                //----------------------
                                msg += "    <ImageKey>BR</ImageKey>";
                                msg += "\n";
                                //----------------------
                                msg += "    <OldID>";
                                if(bezug == WST_BEZUG_OBSEI)
                                {
                                    msg += GANX_WST_BEZUG_OBSEI;
                                }else
                                {
                                    msg += GANX_WST_BEZUG_UNSEI;
                                }
                                msg += "\\";
                                msg += ref;
                                msg += "\\";
                                msg += "BR-";
                                msg += int_to_qstring(ideditor);               //ID-Nummer
                                msg += "</OldID>";
                                msg += "\n";
                                //----------------------
                                msg += "    <KleiGeTei>";    //Zustelltiefe
                                msg += double_to_qstring(zustmass);
                                msg += "</KleiGeTei>";
                                msg += "\n";
                                //----------------------
                                msg += "    <Clause />";
                                msg += "\n";
                                //----------------------
                                msg += "    <iClauseState>0</iClauseState>";
                                msg += "\n";
                                //----------------------
                                msg += "  </PrgrFileWork>";
                                msg += "\n";
                                //----------------------

                                id++;
                                aktti = aktti + zustmass;
                            }
                        }
                    }
                    ideditor++;
                }
            }else
            {
                //Sollte nicht vorkommen können, da bohrraster anhand des vorhandenen Werkzeuges ermittelt werden
            }
        }else if(zeile.zeile(1)==BEARBART_NUT)
        {

            nut nu(zeile.get_text());
            if(nu.get_xs() != nu.get_xe())
            {
                //Warnung ausgeben und Nut unterdrücken:
                QString msg = "";
                msg += "Achtung bei ganx-Export!\n";
                msg += "Teilname: ";
                msg += name;
                msg += "\n";
                msg += "Nut ist nicht parallel zur X-Achse:\n";
                msg += get_bearb_menschlich_lesbar(zeile);
                msg += "\n";
                msg += "Bearbeitung wird unterdrueckt.";

                QMessageBox mb;
                mb.setText(msg);
                mb.exec();
                continue;
            }
            double x = nu.get_xs();
            double y;
            double z = nu.get_tiefe(); //Tiefe
            double l = 0;
            //Nutlänge berechnen:
            if(nu.get_ys() < nu.get_ye())
            {
                l = nu.get_ye() - nu.get_ys();
                y = nu.get_ys();
            }else
            {
                l = nu.get_ys() - nu.get_ye();
                y = nu.get_ye();
            }
            y = tmp_b - y;
            y = y-l;
            QString tnummer = wkzmag.get_wkznummer(WKZ_TYP_SAEGE);
            if(tnummer.isEmpty())
            {
                QString msg = fehler_kein_WKZ("ganx", zeile);
                QMessageBox mb;
                mb.setText(msg);
                mb.exec();
                return msg;
            }
            double wkz_dm = wkzmag.get_dm(tnummer).toDouble();

            QString nutvariante_qstring = "Var2";
            //"Var1" = Nuttiefe wird beim Startmaß und Endmaß erreicht
            //"Var2" = Nut beginnt beim Startmaß und endet am Endmaß

            QString nutrichtung = "Y";
            //Mögliche Werte:
            //"X" = Nut von links nach rechts = entlang der Y-Achse
            //"Y" = Nut von vorne nach hinten = entlang der X-Achse

            double nutblattbreite = wkzmag.get_saegeblattbreite(tnummer).toDouble();

            if(nu.get_breite() < nutblattbreite)
            {
                //Warnung ausgeben und Nut unterdrücken:
                QString msg = "";
                msg += "Achtung bei ganx-Export!\n";
                msg += "Teilname: ";
                msg += name;
                msg += "\n";
                msg += "Saegeblatt zu breit fuer ";
                msg += get_bearb_menschlich_lesbar(zeile);
                msg += "\n";
                msg += "Bearbeitung wird unterdrueckt.";

                QMessageBox mb;
                mb.setText(msg);
                mb.exec();
                continue;
            }else if(nu.get_breite() == nutblattbreite)
            {
                msg += "  <PrgrFileWork>";
                msg += "\n";
                //----------------------
                msg += "    <CntID>";
                msg += int_to_qstring(id);               //ID-Nummer
                msg += "</CntID>";
                msg += "\n";
                //----------------------
                msg += "    <Plane>";
                if(nu.get_bezug() == WST_BEZUG_OBSEI)
                {
                    msg += GANX_WST_BEZUG_OBSEI;
                }else
                {
                    msg += GANX_WST_BEZUG_UNSEI;
                }
                msg += "</Plane>";
                msg += "\n";
                //----------------------
                msg += "    <Ref>";
                msg += GANX_REF_OBEN_LINKS;
                msg += "</Ref>";
                msg += "\n";
                //----------------------
                msg += "    <Typ>S</Typ>";
                msg += "\n";
                //----------------------
                msg += "    <X>";
                msg += double_to_qstring(x);
                msg += "</X>";
                msg += "\n";
                //----------------------
                msg += "    <Y>";
                msg += double_to_qstring(y);
                msg += "</Y>";
                msg += "\n";
                //----------------------
                msg += "    <Z>";
                msg += double_to_qstring(0);
                msg += "</Z>";
                msg += "\n";
                //----------------------
                msg += "    <Diameter>";
                msg += double_to_qstring(wkz_dm);
                msg += "</Diameter>";
                msg += "\n";
                //----------------------
                msg += "    <Depth>";
                msg += double_to_qstring(z);
                msg += "</Depth>";
                msg += "\n";
                //----------------------
                msg += "    <Tool>";
                msg += tnummer;
                msg += "</Tool>";
                msg += "\n";
                //----------------------
                msg += "    <SVar>";
                msg += nutvariante_qstring;
                msg += "</SVar>";
                msg += "\n";
                //----------------------
                msg += "    <SParallel>";
                msg += nutrichtung;
                msg += "</SParallel>";
                msg += "\n";
                //----------------------
                msg += "    <SGrooveLength>";
                msg += double_to_qstring(l);
                msg += "</SGrooveLength>";
                msg += "\n";
                //----------------------
                msg += "    <OldID>";
                if(nu.get_bezug() == WST_BEZUG_OBSEI)
                {
                    msg += GANX_WST_BEZUG_OBSEI;
                }else
                {
                    msg += GANX_WST_BEZUG_UNSEI;
                }
                msg += "\\";
                msg += GANX_REF_OBEN_LINKS;
                msg += "\\";
                msg += "S-";
                msg += int_to_qstring(ideditor);               //ID-Nummer
                msg += "</OldID>";
                msg += "\n";
                //----------------------
                msg += "    <KleiGeTei>";
                msg += "0";
                msg += "</KleiGeTei>";
                msg += "\n";
                //----------------------
                msg += "  </PrgrFileWork>";
                msg += "\n";

                id++;
                ideditor++;

            }else if(nu.get_breite() > nutblattbreite)
            {
                //Wir müssen mehrere Nuten fahren Nuten
                uint anz_nuten = aufrunden(nu.get_breite() / nutblattbreite);
                double x = nu.get_xs();

                for(uint ii=1; ii<=anz_nuten ;ii++)
                {
                    //Beispiel:
                    //Nutbreite = 8,5
                    //blattbreite = 5
                    //Anzahl Nuten = 2
                    //x-Versatz  Nut:
                    //8,5/2 - 5/2 = 1,75
                    //Versatz = +-1,75

                    double versatz = nu.get_breite()/2 - nutblattbreite/2 ;

                    if(ii == 1)
                    {
                        x = x - versatz;

                    }else if(ii==anz_nuten)
                    {
                        x = nu.get_xs();
                        x = x + versatz;
                    }else
                    {
                        double schleifenversatz;
                        schleifenversatz = nutblattbreite - ((nutblattbreite*anz_nuten)-nu.get_breite()) /(anz_nuten-1);
                        x = nu.get_xs() - versatz + (ii-1)*schleifenversatz;
                    }

                    msg += "  <PrgrFileWork>";
                    msg += "\n";
                    //----------------------
                    msg += "    <CntID>";
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</CntID>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Plane>";
                    if(nu.get_bezug() == WST_BEZUG_OBSEI)
                    {
                        msg += GANX_WST_BEZUG_OBSEI;
                    }else
                    {
                        msg += GANX_WST_BEZUG_UNSEI;
                    }
                    msg += "</Plane>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Ref>";
                    msg += GANX_REF_OBEN_LINKS;
                    msg += "</Ref>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Typ>S</Typ>";
                    msg += "\n";
                    //----------------------
                    msg += "    <X>";
                    msg += double_to_qstring(x);
                    msg += "</X>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Y>";
                    msg += double_to_qstring(y);
                    msg += "</Y>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Z>";
                    msg += double_to_qstring(0);
                    msg += "</Z>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Diameter>";
                    msg += double_to_qstring(wkz_dm);
                    msg += "</Diameter>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Depth>";
                    msg += double_to_qstring(z);
                    msg += "</Depth>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Tool>";
                    msg += tnummer;
                    msg += "</Tool>";
                    msg += "\n";
                    //----------------------
                    msg += "    <SVar>";
                    msg += nutvariante_qstring;
                    msg += "</SVar>";
                    msg += "\n";
                    //----------------------
                    msg += "    <SParallel>";
                    msg += nutrichtung;
                    msg += "</SParallel>";
                    msg += "\n";
                    //----------------------
                    msg += "    <SGrooveLength>";
                    msg += double_to_qstring(l);
                    msg += "</SGrooveLength>";
                    msg += "\n";
                    //----------------------
                    msg += "    <OldID>";
                    if(nu.get_bezug() == WST_BEZUG_OBSEI)
                    {
                        msg += GANX_WST_BEZUG_OBSEI;
                    }else
                    {
                        msg += GANX_WST_BEZUG_UNSEI;
                    }
                    msg += "\\";
                    msg += GANX_REF_OBEN_LINKS;
                    msg += "\\";
                    msg += "S-";
                    msg += int_to_qstring(ideditor);               //ID-Nummer
                    msg += "</OldID>";
                    msg += "\n";
                    //----------------------
                    msg += "    <KleiGeTei>";
                    msg += "0";
                    msg += "</KleiGeTei>";
                    msg += "\n";
                    //----------------------
                    msg += "  </PrgrFileWork>";
                    msg += "\n";

                    id++;
                    ideditor++;

                }
            }


        }else if(zeile.zeile(1)==BEARBART_RTA)
        {
            rechtecktasche rt(zeile.get_text());
            double x = rt.get_x();
            double y = rt.get_y();

            bool ausraeumen = true;
            if(rt.get_tiefe() >= dicke  || \
               rt.get_tiefe() <  0 )
            {
                ausraeumen = true;
            }else
            {
                if(rt.get_ausraeumen() == false)
                {
                    ausraeumen = false;
                }else
                {
                    ausraeumen = true;
                }
            }

            //Y-Maß bezieht sich hier immer auf den Nullpunkt der Wst oben links
            //die Maße intern beziehen sich immer auf Nullpunkt unten links
            //das heißt, die Y-Maße müssen an dieser Stelle gegengerechnet werden:
            y = tmp_b - y;

            //double z = rt.get_z();
            QString ti = rt.get_tiefe_qstring();
            /*
             * Formeln sind nicht zulässig:
            if(ti.toDouble() > get_dicke())
            {
                QString tmp = "{LZ}+";
                double dif = ti.toDouble() - get_dicke();
                tmp += double_to_qstring(dif);
                ti = tmp;
            }
            */
            double lx = 0;
            double by = 0;
            if(rt.get_drewi() == 0 || rt.get_drewi() == 180)
            {
                lx = rt.get_laenge();
                by = rt.get_breite();
            }else if(rt.get_drewi() == 90 || rt.get_drewi() == 270)
            {
                lx = rt.get_breite();
                by = rt.get_laenge();
            }else
            {
                //Warnung ausgeben und RTA unterdrücken:
                QString msg = "";
                msg += "Achtung bei Export ganx!\n";
                msg += "Teilname: ";
                msg += name;
                msg += "\n";
                msg += "Drehwinkel der Rechtecktasche wird nicht unterstuetzt:\n";
                msg += zeile.get_text();
                msg += "\n";
                msg += "Bearbeitung wird unterdrueckt.";

                QMessageBox mb;
                mb.setText(msg);
                mb.exec();
                continue;
            }
            double laenge_y = tmp_b;
            double minmass = lx;
            if(by < minmass)
            {
                minmass = by;
            }

            QString tnummer = wkzmag.get_wkznummer_von_alias(rt.get_wkznum());//Ist direkt ei WKZ definiert?
            if(tnummer.isEmpty())
            {
                 tnummer = wkzmag.get_wkznummer(WKZ_TYP_FRAESER, minmass, rt.get_tiefe(), dicke, rt.get_bezug());
            }

            if(tnummer.isEmpty())
            {
                QString msg = fehler_kein_WKZ("ganx", zeile);
                QMessageBox mb;
                mb.setText(msg);
                mb.exec();
                return msg;
            }
            double wkz_dm = wkzmag.get_dm(tnummer).toDouble();
            double eckenradius = rt.get_rad();
            if(eckenradius < wkz_dm/2)
            {
                eckenradius = wkz_dm/2;
            }
            double wkz_vorschub = wkzmag.get_vorschub(tnummer).toDouble();
            //Anzahl der Zustellungen berechnen:
            double zustmass = rt.get_zustellmass();
            if(zustmass <= 0)
            {
                zustmass = wkzmag.get_zustellmass(tnummer).toDouble();
            }
            int zustellungen = aufrunden(rt.get_tiefe() / zustmass);

            if(zustellungen <= 0)
            {
                zustellungen = 1;
            }

            if(zustellungen > 1)
            {
                if(rt.get_bezug() == WST_BEZUG_OBSEI)
                {
                    gruppen_PrgrFileWork.neue_gruppe(GANX_WST_BEZUG_OBSEI);
                }else
                {
                    gruppen_PrgrFileWork.neue_gruppe(GANX_WST_BEZUG_UNSEI);
                }
                if(wkz_dm > by-2  ||  wkz_dm > lx-2)//by==TAB  lx==TAL
                {
                    QString msg = fehler_kein_WKZ("ganx", zeile);
                    msg += "\n";
                    msg += "Anzahl der Zustellungen: ";
                    msg += double_to_qstring(zustellungen);
                    QMessageBox mb;
                    mb.setText(msg);
                    mb.exec();
                    return msg;
                }
            }

            for(uint ii=1 ; ii<=zustellungen ;ii++)
            {
                //----------------------------------------------
                msg += "  <PrgrFileWork>";
                msg += "\n";
                //----------------------
                msg += "    <CntID>";
                msg += int_to_qstring(id);               //ID-Nummer
                msg += "</CntID>";
                msg += "\n";
                //----------------------
                msg += "    <Plane>";
                if(rt.get_bezug() == WST_BEZUG_OBSEI)
                {
                    msg += GANX_WST_BEZUG_OBSEI;
                }else
                {
                    msg += GANX_WST_BEZUG_UNSEI;
                }
                msg += "</Plane>";
                msg += "\n";
                //----------------------Bezugskante festlegen:
                QString ref;
                if(laenge_y - y < bezugsmass)
                {
                    ref = GANX_REF_OBEN_LINKS;
                }else
                {
                    ref = GANX_REF_UNTEN_LINKS;
                }
                msg += "    <Ref>";
                msg += ref;
                msg += "</Ref>";
                msg += "\n";
                //----------------------
                msg += "    <Typ>M</Typ>";
                msg += "\n";
                //----------------------
                msg += "    <X>";
                msg += double_to_qstring(x);
                msg += "</X>";
                msg += "\n";
                //----------------------
                msg += "    <Y>";
                msg += double_to_qstring(y);
                msg += "</Y>";
                msg += "\n";
                //----------------------
                msg += "    <Z>";
                msg += double_to_qstring(0);
                msg += "</Z>";
                msg += "\n";
                //----------------------
                msg += "    <Tool>";
                msg += tnummer;
                msg += "</Tool>";
                msg += "\n";
                //----------------------
                msg += "    <Mill>";
                msg += "3";                      //Rechtecktasche
                msg += ";";
                //msg += double_to_qstring(by);    //TAB
                if(zustellungen > 1  &&  ii != zustellungen)
                {
                    msg += double_to_qstring(by-2);    //TAB
                }else
                {
                    msg += double_to_qstring(by);    //TAB
                }
                msg += ";";
                //msg += double_to_qstring(lx);    //TAL
                if(zustellungen > 1  &&  ii != zustellungen)
                {
                    msg += double_to_qstring(lx-2);    //TAL
                }else
                {
                    msg += double_to_qstring(lx);    //TAL
                }
                msg += ";";
                msg += double_to_qstring(eckenradius); //Eckenradius Tasche
                msg += ";";
                //msg += ti;                       //TaTi
                msg += double_to_qstring(ti.toDouble()/zustellungen*ii);    //TaTi
                msg += ";";
                //Variante der Rechtecktasche:
                //  1 = ausgeräumt
                //  2 = nicht ausgeräumt von der Mitte angefahren
                //  3 = nicht ausgeräumt entlang der Taschenkante angefahren
                if(ausraeumen == true)
                {
                    msg += "1";
                }else
                {
                    msg += "3";
                }
                msg += ";";
                msg += "GL";                     //Gleichlauf (GL = Gleichlauf / GG = Gegenlauf)
                msg += ";";
                msg += double_to_qstring(wkz_vorschub);
                msg += ";";
                //msg += int_to_qstring(zustellungen);
                msg += "1";                     //ohne Zustellungen
                msg += "</Mill>";
                msg += "\n";
                //----------------------
                msg += "    <ImageKey>RE</ImageKey>";
                msg += "\n";
                //----------------------
                msg += "    <OldID>";
                if(rt.get_bezug() == WST_BEZUG_OBSEI)
                {
                    msg += GANX_WST_BEZUG_OBSEI;
                }else
                {
                    msg += GANX_WST_BEZUG_UNSEI;
                }
                msg += "\\";
                msg += GANX_REF_OBEN_LINKS;
                msg += "\\";
                msg += "M-";
                msg += int_to_qstring(ideditor);               //ID-Nummer
                msg += "</OldID>";
                msg += "\n";
                //----------------------
                msg += "    <KleiGeTei>";
                msg += "0";
                msg += "</KleiGeTei>";
                msg += "\n";
                //----------------------
                if(zustellungen > 1)
                {
                    //----------------------
                    msg += "    <GroupName>";
                    msg += gruppen_PrgrFileWork.get_letzten_gruppennamen();
                    msg += "</GroupName>";
                    msg += "\n";
                    //----------------------
                    msg += "    <SortID>";
                    msg += double_to_qstring(ii);
                    msg += "</SortID>";
                    msg += "\n";
                    //----------------------
                }
                //----------------------
                msg += "    <Clause />";
                msg += "\n";
                //----------------------
                msg += "    <iClauseState>0</iClauseState>";
                msg += "\n";
                //----------------------
                msg += "  </PrgrFileWork>";
                msg += "\n";

                id++;
                ideditor++;
            }
        }
    }

    //-------------------------Bearbeitungen <PrgrFile>:
    //Dies ist der Teil, den die Gannomat-Editor liest
    //Hier darf nur mit der Syntax entsprechenden Formeln gearbeitet werden
    id = 1;//id die im Editor angezeigt wird
    ganx_Gruppen gruppen_PrgrFile;

    for(uint i=1 ; i<=bearb.zeilenanzahl() ; i++)
    {
        zeile.set_text(bearb.zeile(i));
        if(zeile.zeile(1) == BEARBART_BOHR)
        {
            bohrung bo(zeile.get_text());

            QString afb_text = bo.get_afb();
            afb_text.replace("L", get_laenge_qstring());
            afb_text.replace("B", get_breite_qstring());
            afb_text.replace("D", get_dicke_qstring());
            afb_text.replace(",", ".");
            afb_text = ausdruck_auswerten(afb_text);
            if(afb_text.toDouble() == 0)
            {
                continue;
            }

            double x = bo.get_x();
            double y = bo.get_y();
            double z = bo.get_z();

            double dm = bo.get_dm();
            double laenge_y = tmp_b;
            QString bezug = bo.get_bezug();

            QString tnummer = wkzmag.get_wkznummer(WKZ_TYP_BOHRER, dm, bo.get_tiefe(), dicke, bezug);
            if(!tnummer.isEmpty())
            {
                //Werkzeug wurde gefunden, Bohrung kann gebohrt werden:

                //Anzahl der Zustellungen berechnen:
                double zustmass = bo.get_zustellmass();
                if(zustmass <= 0)
                {
                    zustmass = wkzmag.get_zustellmass(tnummer).toDouble();
                }
                int zustellungen = aufrunden(bo.get_tiefe() / zustmass);
                if(zustellungen <= 0)
                {
                    zustellungen = 1;
                }
                //-------------------------------

                if(bezug == WST_BEZUG_OBSEI)
                {
                    //x = Breite
                    //y = Länge
                    //z = Tiefe
                    msg += "  <PrgrFile>";
                    msg += "\n";
                    //----------------------
                    msg += "    <CntID>";
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</CntID>";
                    msg += "\n";
                    //----------------------
                    //y < 40 -> TL
                    //Länge - y < 40 ->BL
                    QString ref;
                    if(laenge_y - y < bezugsmass)
                    {
                        ref += GANX_REF_OBEN_LINKS;
                        y = laenge_y - y;
                    }else
                    {
                        ref += GANX_REF_UNTEN_LINKS;
                    }
                    //msg += ref;
                    //----------------------
                    msg += "    <ID>";
                    msg += GANX_WST_BEZUG_OBSEI;
                    msg += "\\";
                    msg += ref;
                    msg += "\\";
                    msg += "B-";
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</ID>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefVal1>";
                    msg += double_to_qstring(y).replace(".",",");
                    msg += "</RefVal1>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefVal2>";
                    msg += double_to_qstring(x).replace(".",",");
                    msg += "</RefVal2>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefLVL>";
                    msg += double_to_qstring(0).replace(".",",");
                    msg += "</RefLVL>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Diameter>";
                    msg += wkzmag.get_dm(tnummer).replace(".",",");
                    msg += "</Diameter>";
                    msg += "\n";
                    //----------------------
                    msg += "   <Depth>";
                    msg += bo.get_tiefe_qstring().replace(".",",");
                    msg += "</Depth>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DoDbl>false</DoDbl>";
                    msg += "\n";
                    //----------------------
                    msg += "    <UsedDbl>ERR</UsedDbl>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblB>true</DblB>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblL>false</DblL>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblE>false</DblE>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DoMF>false</DoMF>";
                    msg += "\n";
                    //----------------------
                    msg += "    <MFLage>B</MFLage>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Tool>";
                    msg += tnummer;
                    msg += "</Tool>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Cyclic>";
                    msg += int_to_qstring(zustellungen);
                    msg += "</Cyclic>";
                    msg += "\n";
                    //----------------------
                    msg += "    <ImageKey>B</ImageKey>>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Step>1</Step>";
                    msg += "\n";
                    //----------------------
                    msg += "  </PrgrFile>";
                    msg += "\n";

                    id++;

                }else if(bezug == WST_BEZUG_UNSEI)
                {
                    //x = Breite
                    //y = Länge
                    //z = Tiefe
                    msg += "  <PrgrFile>";
                    msg += "\n";
                    msg += "    <CntID>";
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</CntID>";
                    msg += "\n";
                    //----------------------
                    QString ref;
                    if(laenge_y - y < bezugsmass)
                    {
                        ref = GANX_REF_OBEN_LINKS;
                        y = laenge_y - y;
                    }else
                    {
                        ref = GANX_REF_UNTEN_LINKS;
                    }
                    //----------------------
                    msg += "    <ID>";
                    msg += GANX_WST_BEZUG_UNSEI;
                    msg += "\\";
                    msg += ref;
                    msg += "\\";
                    msg += "B-";
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</ID>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefVal1>";
                    msg += double_to_qstring(y).replace(".",",");
                    msg += "</RefVal1>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefVal2>";
                    msg += double_to_qstring(x).replace(".",",");
                    msg += "</RefVal2>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefLVL>";
                    msg += double_to_qstring(0).replace(".",",");
                    msg += "</RefLVL>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Diameter>";
                    msg += wkzmag.get_dm(tnummer).replace(".",",");
                    msg += "</Diameter>";
                    msg += "\n";
                    //----------------------
                    msg += "   <Depth>";
                    msg += bo.get_tiefe_qstring().replace(".",",");
                    msg += "</Depth>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DoDbl>false</DoDbl>";
                    msg += "\n";
                    //----------------------
                    msg += "    <UsedDbl>ERR</UsedDbl>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblB>true</DblB>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblL>false</DblL>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblE>false</DblE>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DoMF>false</DoMF>";
                    msg += "\n";
                    //----------------------
                    msg += "    <MFLage>B</MFLage>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Tool>";
                    msg += tnummer;
                    msg += "</Tool>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Cyclic>";
                    msg += int_to_qstring(zustellungen);
                    msg += "</Cyclic>";
                    msg += "\n";
                    //----------------------
                    msg += "    <ImageKey>B</ImageKey>>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Step>1</Step>";
                    msg += "\n";
                    //----------------------
                    msg += "  </PrgrFile>";
                    msg += "\n";

                    id++;

                }else if(bezug == WST_BEZUG_LI)
                {
                    //x = Tiefe
                    //y = Y-Pos
                    //z = Z-Pos
                    msg += "  <PrgrFile>";
                    msg += "\n";
                    msg += "    <CntID>";
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</CntID>";
                    msg += "\n";
                    //----------------------
                    QString ref;
                    if(laenge_y - y < bezugsmass)
                    {
                        ref += GANX_REF_OBEN_LINKS;
                        y = laenge_y - y;
                    }else
                    {
                        ref += GANX_REF_UNTEN_LINKS;
                    }
                    //----------------------
                    msg += "    <ID>";
                    msg += GANX_WST_BEZUG_LI;
                    msg += "\\";
                    msg += ref;
                    msg += "\\";
                    msg += "B-";
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</ID>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefVal1>";
                    msg += double_to_qstring(y).replace(".",",");
                    msg += "</RefVal1>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefVal2>";
                    msg += double_to_qstring(z).replace(".",",");
                    msg += "</RefVal2>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefLVL>";
                    msg += double_to_qstring(0).replace(".",",");
                    msg += "</RefLVL>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Diameter>";
                    msg += wkzmag.get_dm(tnummer).replace(".",",");
                    msg += "</Diameter>";
                    msg += "\n";
                    //----------------------
                    msg += "   <Depth>";
                    msg += bo.get_tiefe_qstring().replace(".",",");
                    msg += "</Depth>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DoDbl>false</DoDbl>";
                    msg += "\n";
                    //----------------------
                    msg += "    <UsedDbl>ERR</UsedDbl>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblB>true</DblB>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblL>false</DblL>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblE>false</DblE>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DoMF>false</DoMF>";
                    msg += "\n";
                    //----------------------
                    msg += "    <MFLage>B</MFLage>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Tool>";
                    msg += tnummer;
                    msg += "</Tool>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Cyclic>";
                    msg += int_to_qstring(zustellungen);
                    msg += "</Cyclic>";
                    msg += "\n";
                    //----------------------
                    msg += "    <ImageKey>B</ImageKey>>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Step>1</Step>";
                    msg += "\n";
                    //----------------------
                    msg += "  </PrgrFile>";
                    msg += "\n";

                    id++;

                }else if(bezug == WST_BEZUG_RE)
                {
                    //x = Tiefe
                    //y = Y-Pos
                    //z = Z-Pos
                    msg += "  <PrgrFile>";
                    msg += "\n";
                    msg += "    <CntID>";
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</CntID>";
                    msg += "\n";
                    //----------------------
                    QString ref;
                    if(laenge_y - y < bezugsmass)
                    {
                        ref += GANX_REF_OBEN_RECHTS;
                        y = laenge_y - y;
                    }else
                    {
                        ref += GANX_REF_UNTEN_RECHTS;
                    }
                    //----------------------
                    msg += "    <ID>";
                    msg += GANX_WST_BEZUG_RE;
                    msg += "\\";
                    msg += ref;
                    msg += "\\";
                    msg += "B-";
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</ID>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefVal1>";
                    msg += double_to_qstring(y).replace(".",",");
                    msg += "</RefVal1>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefVal2>";
                    msg += double_to_qstring(z).replace(".",",");
                    msg += "</RefVal2>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefLVL>";
                    msg += double_to_qstring(0).replace(".",",");
                    msg += "</RefLVL>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Diameter>";
                    msg += wkzmag.get_dm(tnummer).replace(".",",");
                    msg += "</Diameter>";
                    msg += "\n";
                    //----------------------
                    msg += "   <Depth>";
                    msg += bo.get_tiefe_qstring().replace(".",",");
                    msg += "</Depth>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DoDbl>false</DoDbl>";
                    msg += "\n";
                    //----------------------
                    msg += "    <UsedDbl>ERR</UsedDbl>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblB>true</DblB>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblL>false</DblL>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblE>false</DblE>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DoMF>false</DoMF>";
                    msg += "\n";
                    //----------------------
                    msg += "    <MFLage>B</MFLage>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Tool>";
                    msg += tnummer;
                    msg += "</Tool>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Cyclic>";
                    msg += int_to_qstring(zustellungen);
                    msg += "</Cyclic>";
                    msg += "\n";
                    //----------------------
                    msg += "    <ImageKey>B</ImageKey>>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Step>1</Step>";
                    msg += "\n";
                    //----------------------
                    msg += "  </PrgrFile>";
                    msg += "\n";

                    id++;

                }else if(bezug == WST_BEZUG_VO)
                {
                    //x = x-Pos
                    //y = Tiefe
                    //z = Z-Pos
                    msg += "  <PrgrFile>";
                    msg += "\n";
                    msg += "    <CntID>";
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</CntID>";
                    msg += "\n";
                    //----------------------
                    QString ref = GANX_REF_UNTEN_LINKS;
                    //----------------------
                    msg += "    <ID>";
                    msg += GANX_WST_BEZUG_VO;
                    msg += "\\";
                    msg += ref;
                    msg += "\\";
                    msg += "B-";
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</ID>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefVal1>";
                    msg += double_to_qstring(z).replace(".",",");
                    msg += "</RefVal1>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefVal2>";
                    msg += double_to_qstring(x).replace(".",",");
                    msg += "</RefVal2>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefLVL>";
                    msg += double_to_qstring(0).replace(".",",");
                    msg += "</RefLVL>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Diameter>";
                    msg += wkzmag.get_dm(tnummer).replace(".",",");
                    msg += "</Diameter>";
                    msg += "\n";
                    //----------------------
                    msg += "   <Depth>";
                    msg += bo.get_tiefe_qstring().replace(".",",");
                    msg += "</Depth>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DoDbl>false</DoDbl>";
                    msg += "\n";
                    //----------------------
                    msg += "    <UsedDbl>ERR</UsedDbl>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblB>true</DblB>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblL>false</DblL>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblE>false</DblE>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DoMF>false</DoMF>";
                    msg += "\n";
                    //----------------------
                    msg += "    <MFLage>B</MFLage>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Tool>";
                    msg += tnummer;
                    msg += "</Tool>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Cyclic>";
                    msg += int_to_qstring(zustellungen);
                    msg += "</Cyclic>";
                    msg += "\n";
                    //----------------------
                    msg += "    <ImageKey>B</ImageKey>>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Step>1</Step>";
                    msg += "\n";
                    //----------------------
                    msg += "  </PrgrFile>";
                    msg += "\n";

                    id++;

                }else if(bezug == WST_BEZUG_HI)
                {
                    //x = x-Pos
                    //y = Tiefe
                    //z = Z-Pos
                    msg += "  <PrgrFile>";
                    msg += "\n";
                    msg += "    <CntID>";
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</CntID>";
                    msg += "\n";
                    //----------------------
                    QString ref = GANX_REF_OBEN_LINKS;
                    //----------------------
                    msg += "    <ID>";
                    msg += GANX_WST_BEZUG_HI;
                    msg += "\\";
                    msg += ref;
                    msg += "\\";
                    msg += "B-";
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</ID>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefVal1>";
                    msg += double_to_qstring(z).replace(".",",");
                    msg += "</RefVal1>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefVal2>";
                    msg += double_to_qstring(x).replace(".",",");
                    msg += "</RefVal2>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefLVL>";
                    msg += double_to_qstring(0).replace(".",",");
                    msg += "</RefLVL>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Diameter>";
                    msg += wkzmag.get_dm(tnummer).replace(".",",");
                    msg += "</Diameter>";
                    msg += "\n";
                    //----------------------
                    msg += "   <Depth>";
                    msg += bo.get_tiefe_qstring().replace(".",",");
                    msg += "</Depth>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DoDbl>false</DoDbl>";
                    msg += "\n";
                    //----------------------
                    msg += "    <UsedDbl>ERR</UsedDbl>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblB>true</DblB>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblL>false</DblL>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblE>false</DblE>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DoMF>false</DoMF>";
                    msg += "\n";
                    //----------------------
                    msg += "    <MFLage>B</MFLage>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Tool>";
                    msg += tnummer;
                    msg += "</Tool>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Cyclic>";
                    msg += int_to_qstring(zustellungen);
                    msg += "</Cyclic>";
                    msg += "\n";
                    //----------------------
                    msg += "    <ImageKey>B</ImageKey>>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Step>1</Step>";
                    msg += "\n";
                    //----------------------
                    msg += "  </PrgrFile>";
                    msg += "\n";

                    id++;

                }
            }else
            {
                //Kein Werkzeug wurde gefunden.
                //Kann Bohrung als Kreistasche gefräst werden?:
                tnummer = wkzmag.get_wkznummer_von_alias(bo.get_wkznum());//Ist direkt ei WKZ definiert?
                if(tnummer.isEmpty())
                {
                    tnummer = wkzmag.get_wkznummer(WKZ_TYP_FRAESER, dm, bo.get_tiefe(), dicke, bezug);
                }

                if(!tnummer.isEmpty())
                {
                    //Werkzeug wurde gefunden, Kreistasche kann gefräst werden:

                    QString ti = bo.get_tiefe_qstring();
                    if(ti.toDouble() > get_dicke())
                    {
                        QString tmp = "{LZ}+";
                        double dif = ti.toDouble() - get_dicke();
                        tmp += double_to_qstring(dif);
                        ti = tmp;
                    }

                    //Anzahl der Zustellungen berechnen:
                    double zustmass = bo.get_zustellmass();
                    if(zustmass <= 0)
                    {
                        zustmass = wkzmag.get_zustellmass(tnummer).toDouble();
                    }
                    int zustellungen = aufrunden(bo.get_tiefe() / zustmass);

                    if(zustellungen <= 0)
                    {
                        zustellungen = 1;
                    }
                    //---------------------------------------
                    QString wkz_nr = tnummer;
                    double wkz_vorschub = wkzmag.get_vorschub(tnummer).toDouble();

                    msg += "  <PrgrFile>";
                    msg += "\n";
                    //----------------------
                    msg += "    <CntID>";
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</CntID>";
                    msg += "\n";
                    //----------------------
                    QString ref = GANX_REF_UNTEN_LINKS;
                    //y < 40 -> TL
                    //Länge - y < 40 ->BL
                    if(laenge_y - y < bezugsmass)
                    {
                        ref = GANX_REF_OBEN_LINKS;
                        y = laenge_y - y;
                    }
                    //----------------------
                    msg += "    <ID>";
                    if(bo.get_bezug() == WST_BEZUG_OBSEI)
                    {
                        msg += GANX_WST_BEZUG_OBSEI;
                    }else
                    {
                        msg += GANX_WST_BEZUG_UNSEI;
                    }
                    msg += "\\";
                    msg += ref;
                    msg += "\\";
                    msg += "M-";
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</ID>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefVal1>";
                    msg += double_to_qstring(y).replace(".",",");
                    msg += "</RefVal1>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefVal2>";
                    msg += double_to_qstring(x).replace(".",",");
                    msg += "</RefVal2>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Diameter>";
                    msg += "0";
                    msg += "</Diameter>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Depth>";
                    msg += double_to_qstring(z).replace(".",",");
                    msg += "</Depth>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DoDbl>false</DoDbl>";
                    msg += "\n";
                    //----------------------
                    msg += "    <UsedDbl>ERR</UsedDbl>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblB>false</DblB>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblL>false</DblL>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblE>false</DblE>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DoMF>false</DoMF>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Tool>";
                    msg += wkz_nr;
                    msg += "</Tool>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Cyclic>0</Cyclic>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Mill>";
                    msg += "2";                      //Kreistasche
                    msg += ";";
                    msg += double_to_qstring(dm);
                    msg += ";";
                    msg += ti;                       //TaTi
                    msg += ";";
                    msg += "2";                      //Variante der Kreistasche (2 = ausgeräumt)
                    msg += ";";
                    msg += "GL";                     //Gleichlauf (GL = Gleichlauf / GG = Gegenlauf)
                    msg += ";";
                    msg += double_to_qstring(wkz_vorschub);
                    msg += ";";
                    msg += int_to_qstring(zustellungen);
                    msg += "</Mill>";
                    msg += "\n";
                    //----------------------
                    msg += "    <ImageKey>KR</ImageKey>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Step>1</Step>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Clause>0</Clause>";
                    msg += "\n";
                    //----------------------
                    msg += "  </PrgrFile>";
                    msg += "\n";

                    id++;

                }else
                {
                    //Diese Stelle des Codes wird theoretisch niemals erreicht,
                    //da die Funktion bereits in er ersten For-Schleife abbricht.

                    QString msg = fehler_kein_WKZ("ganx", zeile);
                    QMessageBox mb;
                    mb.setText(msg);
                    mb.exec();
                    return msg;
                }
            }
        }else if(zeile.zeile(1) == BEARBART_BOHRRASTER)
        {
            bohrraster bora(zeile.get_text());

            double x = bora.get_x();
            double y = bora.get_y();
            //double z = bora.get_z();

            double dm = bora.get_dm();
            double laenge_y = tmp_b;
            QString bezug = bora.get_bezug();

            QString tnummer = wkzmag.get_wkznummer(WKZ_TYP_BOHRER, dm, bora.get_tiefe(), dicke, bezug);

            if(!tnummer.isEmpty())
            {
                //Werkzeug wurde gefunden, Bohrraster kann gebohrt werden:

                //Anzahl der Zustellungen berechnen:
                double zustmass = bora.get_zustellmass();
                if(zustmass <= 0)
                {
                    zustmass = wkzmag.get_zustellmass(tnummer).toDouble();
                }
                int zustellungen = aufrunden(bora.get_tiefe() / zustmass);
                if(zustellungen <= 0)
                {
                    zustellungen = 1;
                }
                //-------------------------------

                if(bezug == WST_BEZUG_OBSEI  ||  bezug == WST_BEZUG_UNSEI)
                {
                    //x = Breite
                    //y = Länge
                    //z = Tiefe
                    msg += "  <PrgrFile>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DELMARK>OK</DELMARK>";
                    msg += "\n";
                    //----------------------
                    msg += "    <CntID>";
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</CntID>";
                    msg += "\n";
                    //----------------------
                    //y < 40 -> TL
                    //Länge - y < 40 ->BL
                    QString ref;
                    if(  laenge_y - y < bezugsmass  &&  bora.get_anz_y()==1  )
                    {
                        ref += GANX_REF_OBEN_LINKS;
                        y = laenge_y - y;
                    }else
                    {
                        ref += GANX_REF_UNTEN_LINKS;
                    }
                    //msg += ref;
                    //----------------------
                    msg += "    <ID>";
                    if(bezug == WST_BEZUG_OBSEI)
                    {
                        msg += GANX_WST_BEZUG_OBSEI;
                    }else
                    {
                        msg += GANX_WST_BEZUG_UNSEI;
                    }
                    msg += "\\";
                    msg += ref;
                    msg += "\\";
                    msg += "BR-";
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</ID>";
                    msg += "\n";
                    //----------------------
                    //----------------------
                    msg += "    <RefVal1>";
                    msg += double_to_qstring(y).replace(".",",");
                    msg += "</RefVal1>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefVal2>";
                    msg += double_to_qstring(x).replace(".",",");
                    msg += "</RefVal2>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefLVL>";
                    msg += double_to_qstring(0).replace(".",",");
                    msg += "</RefLVL>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Diameter>";
                    msg += wkzmag.get_dm(tnummer).replace(".",",");
                    msg += "</Diameter>";
                    msg += "\n";
                    //----------------------
                    msg += "   <Depth>";
                    msg += bora.get_tiefe_qstring().replace(".",",");
                    msg += "</Depth>";
                    msg += "\n";
                    //---------------------
                    msg += "    <DoDbl>false</DoDbl>";
                    msg += "\n";
                    //---------------------
                    msg += "    <UsedDbl>ERR</UsedDbl>";
                    msg += "\n";
                    //---------------------
                    msg += "    <DblB>true</DblB>";
                    msg += "\n";
                    //---------------------
                    msg += "    <DblL>false</DblL>";
                    msg += "\n";
                    //---------------------
                    msg += "    <DblE>false</DblE>";
                    msg += "\n";
                    //---------------------
                    msg += "    <DoMF>false</DoMF>";
                    msg += "\n";
                    //---------------------
                    msg += "    <Cols>";
                    msg += bora.get_anz_x_qstring();
                    msg += "</Cols>";
                    msg += "\n";
                    //---------------------
                    msg += "    <ColsDistance>";
                    msg += bora.get_raster_x_qstring();
                    msg += "</ColsDistance>";
                    msg += "\n";
                    //---------------------
                    msg += "    <Rows>";
                    msg += bora.get_anz_y_qstring();
                    msg += "</Rows>";
                    msg += "\n";
                    //---------------------
                    msg += "    <RowsDistance>";
                    msg += bora.get_raster_y_qstring();
                    msg += "</RowsDistance>";
                    msg += "\n";
                    //---------------------
                    msg += "    <Tool>";
                    msg += tnummer;
                    msg += "</Tool>";
                    msg += "\n";
                    //----------------------
                    msg += "    <SVar>VAR1</SVar>";
                    msg += "\n";
                    //---------------------
                    msg += "    <Cyclic>";
                    msg += int_to_qstring(zustellungen);
                    msg += "</Cyclic>";
                    msg += "\n";
                    //----------------------
                    msg += "    <ImageKey>BR</ImageKey>>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Step>1</Step>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Clause />";
                    msg += "\n";
                    //----------------------
                    msg += "    <iClauseState>0</iClauseState>";
                    msg += "\n";
                    //----------------------
                    msg += "    <IsActivated>true</IsActivated>";
                    msg += "\n";
                    //----------------------
                    msg += "    <iColor>4294309340</iColor>";
                    msg += "\n";
                    //----------------------
                    msg += "  </PrgrFile>";
                    msg += "\n";

                    id++;

                }
            }else
            {
                //Sollte nicht vorkommen können, da bohrraster anhand des vorhandenen Werkzeuges ermittelt werden
            }
        }else if(zeile.zeile(1) == BEARBART_NUT)
        {

            nut nu(zeile.get_text());
            if(nu.get_xs() != nu.get_xe())
            {
                /*
                //Warnung ausgeben und Nut unterdrücken:
                QString msg = "";
                msg += "Achtung bei Export ganx!\n";
                msg += "Teilname: ";
                msg += name;
                msg += "\n";
                msg += "Nut ist nicht parallel zur X-Achse:\n";
                msg += zeile.get_text();
                msg += "\n";
                msg += "Bearbeitung wird unterdrueckt.";

                QMessageBox mb;
                mb.setText(msg);
                mb.exec();
                */
                continue;
            }
            double x = nu.get_xs();
            double y;
            double z = nu.get_tiefe(); //Tiefe
            double l = 0;
            //Nutlänge berechnen:
            if(nu.get_ys() < nu.get_ye())
            {
                l = nu.get_ye() - nu.get_ys();
                y = nu.get_ys();
            }else
            {
                l = nu.get_ys() - nu.get_ye();
                y = nu.get_ye();
            }
            y = tmp_b - y;
            y = y-l;
            QString tnummer = wkzmag.get_wkznummer(WKZ_TYP_SAEGE);
            if(tnummer.isEmpty())
            {
                //Diese Stelle des Codes wird theoretisch niemals erreicht,
                //da die Funktion bereits in er ersten For-Schleife abbricht.

                QString msg = fehler_kein_WKZ("ganx", zeile);
                QMessageBox mb;
                mb.setText(msg);
                mb.exec();
                return msg;
            }
            //double wkz_dm = wkzmag.get_dm(tnummer).toDouble();

            QString nutvariante_qstring = "Var2";
            //"Var1" = Nuttiefe wird beim Startmaß und Endmaß erreicht
            //"Var2" = Nut beginnt beim Startmaß und endet am Endmaß

            QString nutrichtung = "Y";
            //Mögliche Werte:
            //"X" = Nut von links nach rechts = entlang der Y-Achse
            //"Y" = Nut von vorne nach hinten = entlang der X-Achse

            double nutblattbreite = wkzmag.get_saegeblattbreite(tnummer).toDouble();

            if(nu.get_breite() < nutblattbreite)
            {
                /*
                //Warnung ausgeben und Nut unterdrücken:
                QString msg = "";
                msg += "Achtung bei Export ganx!\n";
                msg += "Teilname: ";
                msg += name;
                msg += "\n";
                msg += "Saegeblatt zu breit fuer Nut:\n";
                msg += zeile.get_text();
                msg += "\n";
                msg += "Bearbeitung wird unterdrueckt.";

                QMessageBox mb;
                mb.setText(msg);
                mb.exec();
                */
                continue;
            }else if(nu.get_breite() == nutblattbreite)
            {
                msg += "  <PrgrFile>";
                msg += "\n";
                //----------------------
                msg += "    <CntID>";
                msg += int_to_qstring(id);               //ID-Nummer
                msg += "</CntID>";
                msg += "\n";
                //----------------------
                msg += "    <ID>";
                if(nu.get_bezug() == WST_BEZUG_OBSEI)
                {
                    msg += GANX_WST_BEZUG_OBSEI;
                }else
                {
                    msg += GANX_WST_BEZUG_UNSEI;
                }
                msg += "\\";
                msg += GANX_REF_OBEN_LINKS;
                msg += "\\";
                msg += "S-";
                msg += int_to_qstring(id);               //ID-Nummer
                msg += "</ID>";
                msg += "\n";
                //----------------------
                msg += "    <RefVal1>";
                msg += double_to_qstring(y).replace(".",",");
                msg += "</RefVal1>";
                msg += "\n";
                //----------------------
                msg += "    <RefVal2>";
                msg += double_to_qstring(x).replace(".",",");
                msg += "</RefVal2>";
                msg += "\n";
                //----------------------
                msg += "    <Diameter>";
                msg += "0";
                msg += "</Diameter>";
                msg += "\n";
                //----------------------
                msg += "    <Depth>";
                msg += double_to_qstring(z).replace(".",",");
                msg += "</Depth>";
                msg += "\n";
                //----------------------
                msg += "    <DoDbl>false</DoDbl>";
                msg += "\n";
                //----------------------
                msg += "    <DblB>false</DblB>";
                msg += "\n";
                //----------------------
                msg += "    <DblL>false</DblL>";
                msg += "\n";
                //----------------------
                msg += "    <DblE>false</DblE>";
                msg += "\n";
                //----------------------
                msg += "    <DoMF>false</DoMF>";
                msg += "\n";
                //----------------------
                msg += "    <Tool>";
                msg += tnummer;
                msg += "</Tool>";
                msg += "\n";
                //----------------------
                msg += "    <SVar>";
                msg += nutvariante_qstring;
                msg += "</SVar>";
                msg += "\n";
                //----------------------
                msg += "    <SParallel>";
                msg += nutrichtung;
                msg += "</SParallel>";
                msg += "\n";
                //----------------------
                msg += "    <SGrooveLength>";
                msg += double_to_qstring(l);
                msg += "</SGrooveLength>";
                msg += "\n";
                //----------------------
                msg += "    <Cyclic>0</Cyclic>";//Zustellung?? Testen!!!
                msg += "\n";
                //----------------------
                msg += "    <ImageKey>S</ImageKey>";
                msg += "\n";
                //----------------------
                msg += "    <Step>1</Step>";
                msg += "\n";
                //----------------------
                msg += "  </PrgrFile>";
                msg += "\n";
                //----------------------

                id++;

            }else if(nu.get_breite() > nutblattbreite)
            {
                //Wir müssen mehrere Nuten fahren Nuten
                uint anz_nuten = aufrunden(nu.get_breite() / nutblattbreite);
                double x = nu.get_xs();

                for(uint ii=1; ii<=anz_nuten ;ii++)
                {
                    double versatz = nu.get_breite()/2 - nutblattbreite/2 ;

                    if(ii == 1)
                    {
                        x = x - versatz;

                    }else if(ii==anz_nuten)
                    {
                        x = nu.get_xs();
                        x = x + versatz;
                    }else
                    {
                        double schleifenversatz;
                        schleifenversatz = nutblattbreite - ((nutblattbreite*anz_nuten)-nu.get_breite()) /(anz_nuten-1);
                        x = nu.get_xs() - versatz + (ii-1)*schleifenversatz;
                    }

                    msg += "  <PrgrFile>";
                    msg += "\n";
                    //----------------------
                    msg += "    <CntID>";
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</CntID>";
                    msg += "\n";
                    //----------------------
                    msg += "    <ID>";
                    if(nu.get_bezug() == WST_BEZUG_OBSEI)
                    {
                        msg += GANX_WST_BEZUG_OBSEI;
                    }else
                    {
                        msg += GANX_WST_BEZUG_UNSEI;
                    }
                    msg += "\\";
                    msg += GANX_REF_OBEN_LINKS;
                    msg += "\\";
                    msg += "S-";
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</ID>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefVal1>";
                    msg += double_to_qstring(y).replace(".",",");
                    msg += "</RefVal1>";
                    msg += "\n";
                    //----------------------
                    msg += "    <RefVal2>";
                    msg += double_to_qstring(x).replace(".",",");
                    msg += "</RefVal2>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Diameter>";
                    msg += "0";
                    msg += "</Diameter>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Depth>";
                    msg += double_to_qstring(z).replace(".",",");
                    msg += "</Depth>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DoDbl>false</DoDbl>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblB>false</DblB>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblL>false</DblL>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DblE>false</DblE>";
                    msg += "\n";
                    //----------------------
                    msg += "    <DoMF>false</DoMF>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Tool>";
                    msg += tnummer;
                    msg += "</Tool>";
                    msg += "\n";
                    //----------------------
                    msg += "    <SVar>";
                    msg += nutvariante_qstring;
                    msg += "</SVar>";
                    msg += "\n";
                    //----------------------
                    msg += "    <SParallel>";
                    msg += nutrichtung;
                    msg += "</SParallel>";
                    msg += "\n";
                    //----------------------
                    msg += "    <SGrooveLength>";
                    msg += double_to_qstring(l);
                    msg += "</SGrooveLength>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Cyclic>0</Cyclic>";//Zustellung?? Testen!!!
                    msg += "\n";
                    //----------------------
                    msg += "    <ImageKey>S</ImageKey>";
                    msg += "\n";
                    //----------------------
                    msg += "    <Step>1</Step>";
                    msg += "\n";
                    //----------------------
                    msg += "  </PrgrFile>";
                    msg += "\n";
                    //----------------------

                    id++;

                }
            }



        }else if(zeile.zeile(1) == BEARBART_RTA)
        {
            rechtecktasche rt(zeile.get_text());
            double x = rt.get_x();
            double y = rt.get_y();
            double z = rt.get_z();
            bool ausraeumen = true;
            if(rt.get_tiefe() >= dicke  || \
               rt.get_tiefe() <  0 )
            {
                ausraeumen = true;
            }else
            {
                if(rt.get_ausraeumen() == false)
                {
                    ausraeumen = false;
                }else
                {
                    ausraeumen = true;
                }
            }
            QString ti = rt.get_tiefe_qstring();
            if(ti.toDouble() > get_dicke())
            {
                QString tmp = "{LZ}+";
                double dif = ti.toDouble() - get_dicke();
                tmp += double_to_qstring(dif);
                ti = tmp;
            }
            double lx = 0;
            double by = 0;
            if(rt.get_drewi() == 0 || rt.get_drewi() == 180)
            {
                lx = rt.get_laenge();
                by = rt.get_breite();
            }else if(rt.get_drewi() == 90 || rt.get_drewi() == 270)
            {
                lx = rt.get_breite();
                by = rt.get_laenge();
            }else
            {
                /*Diese Warnung wird bereits durch die vorherige For-Schleife ausgegeben:
                 *
                //Warnung ausgeben und RTA unterdrücken:
                QString msg = "";
                msg += "Achtung bei Export ganx!\n";
                msg += "Teilname: ";
                msg += name;
                msg += "\n";
                msg += "Drehwinkel der Rechtecktasche wird nicht unterstuetzt:\n";
                msg += zeile.get_text();
                msg += "\n";
                msg += "Bearbeitung wird unterdrueckt.";

                QMessageBox mb;
                mb.setText(msg);
                mb.exec();
                */
                continue;
            }
            double laenge_y = tmp_b;
            double minmass = lx;
            if(by < minmass)
            {
                minmass = by;
            }

            QString tnummer = wkzmag.get_wkznummer_von_alias(rt.get_wkznum());//Ist direkt ei WKZ definiert?
            if(tnummer.isEmpty())
            {
                 tnummer = wkzmag.get_wkznummer(WKZ_TYP_FRAESER, minmass, rt.get_tiefe(), dicke, rt.get_bezug());
            }

            if(tnummer.isEmpty())
            {
                //Diese Stelle des Codes wird theoretisch niemals erreicht,
                //da die Funktion bereits in er ersten For-Schleife abbricht.

                QString msg = fehler_kein_WKZ("ganx", zeile);
                QMessageBox mb;
                mb.setText(msg);
                mb.exec();
                return msg;
            }
            double wkz_dm = wkzmag.get_dm(tnummer).toDouble();
            double eckenradius = rt.get_rad();
            if(eckenradius < wkz_dm/2)
            {
                eckenradius = wkz_dm/2;
            }
            double wkz_vorschub = wkzmag.get_vorschub(tnummer).toDouble();
            //Anzahl der Zustellungen berechnen:
            double zustmass = rt.get_zustellmass();
            if(zustmass <= 0)
            {
                zustmass = wkzmag.get_zustellmass(tnummer).toDouble();
            }
            int zustellungen = aufrunden(rt.get_tiefe() / zustmass);
            if(zustellungen <= 0)
            {
                zustellungen = 1;
            }

            if(zustellungen > 1)
            {
                if(rt.get_bezug() == WST_BEZUG_OBSEI)
                {
                    gruppen_PrgrFile.neue_gruppe(GANX_WST_BEZUG_OBSEI);
                }else
                {
                    gruppen_PrgrFile.neue_gruppe(GANX_WST_BEZUG_UNSEI);
                }
                if(wkz_dm > by-2  ||  wkz_dm > lx-2)//by==TAB  lx==TAL
                {
                    //Diese Stelle des Codes wird theoretisch niemals erreicht,
                    //da die Funktion bereits in er ersten For-Schleife abbricht.

                    QString msg = fehler_kein_WKZ("ganx", zeile);
                    msg += "\n";
                    msg += "Anzahl der Zustellungen: ";
                    msg += double_to_qstring(zustellungen);
                    QMessageBox mb;
                    mb.setText(msg);
                    mb.exec();
                    return msg;
                }
            }

            for(uint ii=1 ; ii<=zustellungen ;ii++)
            {
                //----------------------------------------------

                msg += "  <PrgrFile>";
                msg += "\n";
                //----------------------
                msg += "    <CntID>";
                msg += int_to_qstring(id);               //ID-Nummer
                msg += "</CntID>";
                msg += "\n";
                //----------------------
                QString ref = GANX_REF_UNTEN_LINKS;
                //y < 40 -> TL
                //Länge - y < 40 ->BL
                if(laenge_y - y < bezugsmass)
                {
                    ref = GANX_REF_OBEN_LINKS;
                    y = laenge_y - y;
                }
                //----------------------
                msg += "    <ID>";
                if(rt.get_bezug() == WST_BEZUG_OBSEI)
                {
                    msg += GANX_WST_BEZUG_OBSEI;
                }else
                {
                    msg += GANX_WST_BEZUG_UNSEI;
                }
                msg += "\\";
                msg += ref;
                msg += "\\";
                msg += "M-";
                msg += int_to_qstring(id);               //ID-Nummer
                msg += "</ID>";
                msg += "\n";
                //----------------------
                msg += "    <RefVal1>";
                msg += double_to_qstring(y).replace(".",",");
                msg += "</RefVal1>";
                msg += "\n";
                //----------------------
                msg += "    <RefVal2>";
                msg += double_to_qstring(x).replace(".",",");
                msg += "</RefVal2>";
                msg += "\n";
                //----------------------
                //----------------------
                msg += "    <Diameter>";
                msg += "0";
                msg += "</Diameter>";
                msg += "\n";
                //----------------------
                msg += "    <Depth>";
                msg += double_to_qstring(z).replace(".",",");
                msg += "</Depth>";
                msg += "\n";
                //----------------------
                msg += "    <DoDbl>false</DoDbl>";
                msg += "\n";
                //----------------------
                msg += "    <UsedDbl>ERR</UsedDbl>";
                msg += "\n";
                //----------------------
                msg += "    <DblB>false</DblB>";
                msg += "\n";
                //----------------------
                msg += "    <DblL>false</DblL>";
                msg += "\n";
                //----------------------
                msg += "    <DblE>false</DblE>";
                msg += "\n";
                //----------------------
                msg += "    <DoMF>false</DoMF>";
                msg += "\n";
                //----------------------
                msg += "    <Tool>";
                msg += tnummer;
                msg += "</Tool>";
                msg += "\n";
                //----------------------
                msg += "    <Cyclic>0</Cyclic>";
                msg += "\n";
                //----------------------
                msg += "    <Mill>";
                msg += "3";                      //Rechtecktasche
                msg += ";";
                //msg += double_to_qstring(by);    //TAB
                if(zustellungen > 1  &&  ii != zustellungen)
                {
                    msg += double_to_qstring(by-2);    //TAB
                }else
                {
                    msg += double_to_qstring(by);    //TAB
                }
                msg += ";";
                //msg += double_to_qstring(lx);    //TAL
                if(zustellungen > 1  &&  ii != zustellungen)
                {
                    msg += double_to_qstring(lx-2);    //TAL
                }else
                {
                    msg += double_to_qstring(lx);    //TAL
                }
                msg += ";";
                msg += double_to_qstring(eckenradius); //Eckenradius Tasche
                msg += ";";
                //msg += ti;                       //TaTi
                QString tiakt = rt.get_tiefe_qstring();//Weil ti sonst evtl. {LZ}+2 seinkönnte
                if((tiakt.toDouble()/zustellungen*ii) > get_dicke())
                {
                    QString tmp = "{LZ}+";
                    double dif = tiakt.toDouble() - get_dicke();
                    tmp += double_to_qstring(dif);
                    tiakt = tmp;
                }else
                {
                    tiakt = double_to_qstring(tiakt.toDouble()/zustellungen*ii);
                }
                msg += tiakt;    //TaTi
                msg += ";";
                //Variante der Rechtecktasche:
                //  1 = ausgeräumt
                //  2 = nicht ausgeräumt von der Mitte angefahren
                //  3 = nicht ausgeräumt entlang der Taschenkante angefahren
                if(ausraeumen == true)
                {
                    msg += "1";
                }else
                {
                    msg += "3";
                }
                msg += ";";
                msg += "GL";                     //Gleichlauf (GL = Gleichlauf / GG = Gegenlauf)
                msg += ";";
                msg += double_to_qstring(wkz_vorschub);
                msg += ";";
                //msg += int_to_qstring(zustellungen);
                msg += "1";                     //ohne Zustellungen
                msg += "</Mill>";
                msg += "\n";
                //----------------------
                msg += "    <ImageKey>RE</ImageKey>";
                msg += "\n";
                //----------------------
                msg += "    <Step>1</Step>";
                msg += "\n";
                //----------------------
                if(zustellungen > 1)
                {
                    //----------------------
                    msg += "    <GroupName>";
                    msg += gruppen_PrgrFile.get_letzten_gruppennamen();
                    msg += "</GroupName>";
                    msg += "\n";
                    //----------------------
                    msg += "    <SortID>";
                    msg += double_to_qstring(ii);
                    msg += "</SortID>";
                    msg += "\n";
                    //----------------------
                }
                //----------------------
                msg += "    <Clause>0</Clause>";
                msg += "\n";
                //----------------------
                msg += "    <iClauseState>0</iClauseState>";
                msg += "\n";
                //----------------------
                msg += "  </PrgrFile>";
                msg += "\n";

                id++;
            }
        }
    }

    //-------------------------Bearbeitungsgruppen:
    if(gruppen_PrgrFile.get_gruppen()  ==  gruppen_PrgrFileWork.get_gruppen())
    {
        msg += gruppen_PrgrFile.get_gruppen();
    }else
    {
        //Diese Stelle sollte niermals erreicht werden

        QString msg = "Programminterner Fehler bei der Erstellung von Bearbeitungsgruppen!";
        QMessageBox mb;
        mb.setText(msg);
        mb.exec();
        return msg;
    }

    //-------------------------Programmende:
    msg += "</Programm>";


    return msg;
}
QString werkstueck::get_fmc_dateitext(text_zeilenweise wkzmagazin, text_zeilenweise bearb, \
                                      double tmp_l, double tmp_b, QString zust_fkon)
{
    text_zeilenweise bearb_kopie = bearb;
    bearb = rasterbohrungen_finden_fmc(bearb, wkzmagazin, tmp_l, tmp_b);
    QString msg;   
    text_zeilenweise zeile;
    zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
     werkzeugmagazin wkzmag(wkzmagazin);

     bool ay = false;
     if(tmp_b < schwellenwert_ay)
     {
         ay = true;
     }

     int min_kta_dm_ausraeumen_false = 200; //Durchmesser ab dem Kreistaschen nicht ausgeräumt werden

    //---------------------------------------Programmkopf:
    msg = FMC_PRGKOPF;
    msg += "\n";
    msg += "ABSTS=";                //Sicherheitsabstand
    msg += "20";
    msg += "\n";
    msg += "AFB=1\n";
    msg += "AXV=";                  //X-Versatz
    msg += "0";
    msg += "\n";
    msg += "AYV=";                  //Y-Veratz
    if(ay == true)
    {
        msg += "210";
    }else
    {
        msg += "0";
    }
    msg += "\n";
    msg += "BEZB=";                 //Bezeichnung
    msg += "Programmkopf";
    msg += "\n";
    msg += "FTL=";                  //Länge
    msg += double_to_qstring(tmp_l);
    msg += "\n";
    msg += "FTB=";                  //Breite
    msg += double_to_qstring(tmp_b);
    msg += "\n";
    msg += "FTD=";                  //Dicke
    msg += get_dicke_qstring();
    msg += "\n";
    msg += "HOLKA=-1\n";            //Hole Kante Nr
    msg += "KOM1=";                //Kommentar 1
    msg += fmc_kommentar_gute_seite(bearb_kopie);
    //msg += "(NULL)";
    msg += "\n";
    msg += "KOM2=";                 //Kommentar 2
    msg += "(NULL)";
    msg += "\n";
    msg += "LOESEN=";               //Automatisch lösen
    msg += "1";
    msg += "\n";
    msg += "MPB=";                  //Mehrplatzbelegungsart
    msg += "0";
    msg += "\n";
    msg += "RTB=B+(2*AY)\n";        //Rohteillänge
    msg += "RTL=L+(2*AX)\n";        //Rohteilbreite
    msg += "SPGLWKS=";              //Spiegeln
    msg += "0";
    msg += "\n";
    msg += "WKDS=";                 //Fünf Seiten
    msg += "0";
    msg += "\n";
    msg += "ZSCHABLO=";             //Schablonenhöhe
    msg += "0";
    msg += "\n";
    msg += "\n";
    //---------------------------------------ggf. Y-Versatz kennlich machen:
    if(ay == true)
    {
        msg += kommentar_fmc("--------------------");
        msg += kommentar_fmc("ay 210");
        msg += kommentar_fmc("--------------------");

        bool kreuzkopf_von_vorne = false;
        for(uint i=1; i<=bearb.zeilenanzahl() ;i++)
        {
            text_zeilenweise zeile;
            zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
            zeile.set_text(bearb.zeile(i));

            QString art = zeile.zeile(1);
            if(art == BEARBART_BOHR)
            {
                bohrung bo(zeile.get_text());

                if(bo.get_bezug() == WST_BEZUG_VO)
                {
                    kreuzkopf_von_vorne = true;
                }
            }
        }
        if(kreuzkopf_von_vorne == true)
        {
            msg += kommentar_fmc("----------------------------------------");
            msg += kommentar_fmc("Achtung!");
            msg += kommentar_fmc("Kreuzkopf in Kollision mit");
            msg += kommentar_fmc("Versatzbrett ay 210");
            msg += kommentar_fmc("----------------------------------------");
        }
    }
    //---------------------------------------Bearbeitungen Oberseite und Hirnseiten:
    for(uint i=1 ; i<=bearb.zeilenanzahl() ; i++)
    {
        zeile.set_text(bearb.zeile(i));
        if(zeile.zeile(1) == BEARBART_BOHR)
        {
            bohrung bo(zeile.get_text());
            QString bezug = bo.get_bezug();
            QString tnummer = wkzmag.get_wkznummer(WKZ_TYP_BOHRER, bo.get_dm(), bo.get_tiefe(), dicke, bezug);
            if(!tnummer.isEmpty())
            {
                //Werkzeug wurde gefunden, Bohrung kann gebohrt werden:
                QString bohrgruppe = "1";
                if(bezug == WST_BEZUG_OBSEI)
                {
                    double tiefe;
                    if(bo.get_tiefe() <= get_dicke())
                    {
                        tiefe = bo.get_tiefe();
                    }else
                    {
                        tiefe = get_dicke() - bo.get_tiefe();
                    }
                    msg += FMC_BOHR_DM;
                    msg += "\n";
                    msg += FMC_BOHR_DM_X;
                    msg += "=";
                    msg += double_to_qstring(bo.get_x());
                    msg += "\n";
                    msg += FMC_BOHR_DM_Y;
                    msg += "=";
                    msg += double_to_qstring(bo.get_y());
                    msg += "\n";
                    msg += FMC_BOHR_DM_TIEFE;
                    msg += "=";
                    msg += double_to_qstring(tiefe);
                    msg += "\n";
                    msg += FMC_BOHR_DM_DM;
                    msg += "=";
                    msg += bo.get_dm_qstring();
                    msg += "\n";
                    msg += "GRP=";                  //Bohrgruppe
                    msg += bohrgruppe;
                    msg += "\n";

                    //Anbohrtiefe gem. Voreinstellung IMAWOP
                    //Anbohrvorschub gem. Voreinstellung IMAWOP
                    //Restbohrmaß gem. Voreinstellung IMAWOP
                    //Bohrvorschub gem. Voreinstellung IMAWOP

                    msg += "ZSM=";                  //Zustellmaß
                    msg += wkzmag.get_zustellmass(tnummer);
                    msg += "\n";

                    //Drehzahl gem. Voreinstellung IMAWOP

                    msg += "MRICHT=0\n";
                    msg += "TASTEIN=-1\n";
                    msg += "BEZB=";
                    msg += "Bohrung DM";
                    msg += bo.get_dm_qstring();
                    msg += " T";
                    msg += double_to_qstring(tiefe);
                    msg += "\n";
                    msg += FMC_BOHR_DM_AFB;
                    msg += "=";
                    msg += bo.get_afb();
                    msg += "\n";
                    msg += "\n";
                }else if(bezug == WST_BEZUG_LI)
                {
                    msg += FMC_HBEXP;
                    msg += "\n";
                    msg += "Y1=";
                    msg += bo.get_y_qstring();
                    msg += "\n";
                    msg += "Y2=(NULL)\n";
                    msg += "Y3=(NULL)\n";
                    msg += "Y4=(NULL)\n";
                    msg += "Y5=(NULL)\n";
                    msg += "Y6=(NULL)\n";
                    msg += "TI=";
                    msg += bo.get_tiefe_qstring();
                    msg += "\n";
                    msg += "Z=";
                    msg += bo.get_z_qstring();
                    msg += "\n";
                    msg += "DM=";
                    msg += bo.get_dm_qstring();
                    msg += "\n";
                    msg += "KETTE=0\n";
                    msg += "GRP=1\n";           //Bohrgruppe
                    msg += "X2=-1\n";
                    msg += "X1=0\n";

                    //Anbohrtiefe gem. Voreinstellung IMAWOP
                    //Anbohrvorschub gem. Voreinstellung IMAWOP
                    //Bohrvorschub gem. Voreinstellung IMAWOP
                    //Drehzahl gem. Voreinstellung IMAWOP

                    msg += "BEZB=";
                    msg += "HBE X+ DM";
                    msg += bo.get_dm_qstring();
                    msg += " T";
                    msg += bo.get_tiefe_qstring();
                    msg += "\n";
                    msg += "AFB=";
                    msg += bo.get_afb();
                    msg += "\n";
                    msg += "\n";
                }else if(bezug == WST_BEZUG_RE)
                {
                    msg += FMC_HBEXM;
                    msg += "\n";
                    msg += "Y1=";
                    msg += bo.get_y_qstring();
                    msg += "\n";
                    msg += "Y2=(NULL)\n";
                    msg += "Y3=(NULL)\n";
                    msg += "Y4=(NULL)\n";
                    msg += "Y5=(NULL)\n";
                    msg += "Y6=(NULL)\n";
                    msg += "TI=";
                    msg += bo.get_tiefe_qstring();
                    msg += "\n";
                    msg += "Z=";
                    msg += bo.get_z_qstring();
                    msg += "\n";
                    msg += "DM=";
                    msg += bo.get_dm_qstring();
                    msg += "\n";
                    msg += "KETTE=0\n";
                    msg += "GRP=1\n";           //Bohrgruppe
                    msg += "X2=-1\n";
                    msg += "X1=L\n";

                    //Anbohrtiefe gem. Voreinstellung IMAWOP
                    //Anbohrvorschub gem. Voreinstellung IMAWOP
                    //Bohrvorschub gem. Voreinstellung IMAWOP
                    //Drehzahl gem. Voreinstellung IMAWOP

                    msg += "BEZB=";
                    msg += "HBE X- DM";
                    msg += bo.get_dm_qstring();
                    msg += " T";
                    msg += bo.get_tiefe_qstring();
                    msg += "\n";
                    msg += "AFB=";
                    msg += bo.get_afb();
                    msg += "\n";
                    msg += "\n";
                }else if(bezug == WST_BEZUG_VO)
                {
                    msg += FMC_HBEYP;
                    msg += "\n";
                    msg += "X1=";
                    msg += bo.get_x_qstring();
                    msg += "\n";
                    msg += "X2=(NULL)\n";
                    msg += "X3=(NULL)\n";
                    msg += "X4=(NULL)\n";
                    msg += "X5=(NULL)\n";
                    msg += "X6=(NULL)\n";
                    msg += "TI=";
                    msg += bo.get_tiefe_qstring();
                    msg += "\n";
                    msg += "Z=";
                    msg += bo.get_z_qstring();
                    msg += "\n";
                    msg += "DM=";
                    msg += bo.get_dm_qstring();
                    msg += "\n";
                    msg += "KETTE=0\n";
                    msg += "GRP=1\n";           //Bohrgruppe
                    msg += "Y2=-1\n";
                    msg += "Y1=0\n";

                    //Anbohrtiefe gem. Voreinstellung IMAWOP
                    //Anbohrvorschub gem. Voreinstellung IMAWOP
                    //Bohrvorschub gem. Voreinstellung IMAWOP
                    //Drehzahl gem. Voreinstellung IMAWOP

                    msg += "BEZB=";
                    msg += "HBE Y+ DM";
                    msg += bo.get_dm_qstring();
                    msg += " T";
                    msg += bo.get_tiefe_qstring();
                    msg += "\n";
                    msg += "AFB=";
                    msg += bo.get_afb();
                    msg += "\n";
                    msg += "\n";
                }else if(bezug == WST_BEZUG_HI)
                {
                    msg += FMC_HBEYM;
                    msg += "\n";
                    msg += "X1=";
                    msg += bo.get_x_qstring();
                    msg += "\n";
                    msg += "X2=(NULL)\n";
                    msg += "X3=(NULL)\n";
                    msg += "X4=(NULL)\n";
                    msg += "X5=(NULL)\n";
                    msg += "X6=(NULL)\n";
                    msg += "TI=";
                    msg += bo.get_tiefe_qstring();
                    msg += "\n";
                    msg += "Z=";
                    msg += bo.get_z_qstring();
                    msg += "\n";
                    msg += "DM=";
                    msg += bo.get_dm_qstring();
                    msg += "\n";
                    msg += "KETTE=0\n";
                    msg += "GRP=1\n";           //Bohrgruppe
                    msg += "Y2=-1\n";
                    msg += "Y1=B\n";

                    //Anbohrtiefe gem. Voreinstellung IMAWOP
                    //Anbohrvorschub gem. Voreinstellung IMAWOP
                    //Bohrvorschub gem. Voreinstellung IMAWOP
                    //Drehzahl gem. Voreinstellung IMAWOP

                    msg += "BEZB=";
                    msg += "HBE Y- DM";
                    msg += bo.get_dm_qstring();
                    msg += " T";
                    msg += bo.get_tiefe_qstring();
                    msg += "\n";
                    msg += "AFB=";
                    msg += bo.get_afb();
                    msg += "\n";
                    msg += "\n";
                }
            }else
            {
                //Kein Werkzeug wurde gefunden.
                //Kann Bohrung als Kreistasche gefräst werden?:

                tnummer = wkzmag.get_wkznummer_von_alias(bo.get_wkznum());//Ist direkt ei WKZ definiert?
                if(tnummer.isEmpty())
                {
                    tnummer = wkzmag.get_wkznummer(WKZ_TYP_FRAESER, bo.get_dm(), bo.get_tiefe(), dicke, bezug);
                }
                if(!tnummer.isEmpty())
                {
                    double zustellmas = bo.get_zustellmass();
                    if(zustellmas <= 0)
                    {
                        zustellmas = wkzmag.get_zustellmass(tnummer).toDouble();
                    }

                    double tiefe = 0;
                    QString tiefe_qstring;
                    if(bo.get_tiefe() > get_dicke())
                    {
                        tiefe = get_dicke() - bo.get_tiefe();
                        tiefe_qstring = double_to_qstring(tiefe);
                    }else if(get_dicke()-bo.get_tiefe() <= 2)
                    {
                        tiefe_qstring  = "D-";
                        tiefe_qstring += double_to_qstring(get_dicke()-bo.get_tiefe());
                    }else
                    {
                        tiefe = bo.get_tiefe();
                        tiefe_qstring = double_to_qstring(tiefe);
                    }

                    bool ausraeumen = true;
                    if(bo.get_dm() > 2*wkzmag.get_dm(tnummer).toDouble()+20)
                    {
                        if(bo.get_tiefe() < 0  ||  bo.get_tiefe() > get_dicke())
                        {
                            ausraeumen = false;
                        }
                    }
                    if(bo.get_dm() > min_kta_dm_ausraeumen_false)
                    {
                        ausraeumen = false;
                    }

                    if(bo.get_bezug() == WST_BEZUG_OBSEI)
                    {
                        msg += FMC_KTA;
                        msg += "\n";
                        msg += "WKZID=";           //WKZ-Nummer
                        msg += tnummer;
                        msg += "\n";
                        msg += "MPX=";
                        msg += bo.get_x_qstring();
                        msg += "\n";
                        msg += "MPY=";
                        msg += bo.get_y_qstring();
                        msg += "\n";
                        msg += "DM=";
                        msg += bo.get_dm_qstring();
                        msg += "\n";
                        msg += "TI=";
                        msg += tiefe_qstring;
                        msg += "\n";
                        msg += "LGEZU=";            //Zustellmaß
                        msg += double_to_qstring(zustellmas);
                        msg += "\n";
                        msg += "GEGENL=1\n";        //Gegenlauf
                        msg += "RAEUMEN=";          //Ausräumen
                        if(ausraeumen == true)
                        {
                            msg += "1";
                        }else
                        {
                            msg += "0";
                        }
                        msg += "\n";

                        //Eintauchvorschub gem. Voreinstellung IMAWOP
                        //Vorschub gem. Voreinstellung IMAWOP
                        //Drehzahl gem. Voreinstellung IMAWOP

                        msg += "BEZB=";
                        msg += "Kreistasche DM";
                        msg += bo.get_dm_qstring();
                        msg += " T";
                        msg += tiefe_qstring;
                        msg += "\n";
                        msg += "AFB=";
                        msg += bo.get_afb();
                        msg += "\n";
                        msg += "WKZAKTUELL=1\n";
                        msg += "\n";
                    }

                }else
                {
                    //Mit Fehlermeldung abbrechen:
                    QString msg = fehler_kein_WKZ("fmc", zeile);
                    QMessageBox mb;
                    mb.setText(msg);
                    mb.exec();
                    return msg;
                }
            }
        }else if(zeile.zeile(1) == BEARBART_BOHRRASTER)
        {
            bohrraster bora(zeile.get_text());
            QString bezug = bora.get_bezug();
            QString tnummer = wkzmag.get_wkznummer(WKZ_TYP_BOHRER, bora.get_dm(), bora.get_tiefe(), dicke, bezug);
            if(!tnummer.isEmpty())
            {
                //Werkzeug wurde gefunden, Bohrung kann gebohrt werden:
                QString bohrgruppe = "1";
                if(bezug == WST_BEZUG_OBSEI)
                {
                    double tiefe;
                    if(bora.get_tiefe() <= get_dicke())
                    {
                        tiefe = bora.get_tiefe();
                    }else
                    {
                        tiefe = get_dicke() - bora.get_tiefe();
                    }

                    //Lochreihen ausgeben
                    if(bora.get_anz_y() == 1)
                    {
                        //Lochreihen oder Bohrbild in X?:
                        if(bora.get_raster_x() == 32  &&  bora.get_dm() == 5)
                        {
                            //Lochreihe:
                            msg += FMC_LORAE;
                            msg += "\n";
                            //---------------------------------
                            msg += FMC_LORAE_AFB;       //Aufruf Lochreihendialog
                            msg += bora.get_afb();
                            msg += "\n";
                            //---------------------------------
                            msg += FMC_LORAE_BEZ;       //Bezeichnung
                            msg += "=";
                            msg += "Lochreihe DM";
                            msg += bora.get_dm_qstring();
                            msg += " T";
                            msg += double_to_qstring(tiefe);
                            msg += "\n";
                            //---------------------------------
                            msg += FMC_LORAE_DM;        //Durchmesser
                            msg += "=";
                            msg += bora.get_dm_qstring();
                            msg += "\n";
                            //---------------------------------
                            msg += FMC_LORAE_XS;        //Startpunkt in X
                            msg += "=";
                            msg += bora.get_x_qstring();
                            msg += "\n";
                            //---------------------------------
                            msg += FMC_LORAE_XE;        //Endpunkt in X
                            msg += "=";
                            msg += double_to_qstring(bora.get_x() + (bora.get_anz_x()*(bora.get_raster_x()-1))  );
                            msg += "+0.5";              //Sonst ist es zu genau und es wird ggf 1 Bohrung zu wenig gebohrt
                            msg += "\n";
                            //---------------------------------
                            msg += "EPY";
                            msg += "=";
                            msg += "Y1";                //gerade verlaufende Lochreihe von 0 bis L
                            msg += "\n";
                            //---------------------------------
                            msg += FMC_LORAE_Y1;
                            msg += "=";
                            msg += bora.get_y_qstring();
                            msg += "\n";
                            //---------------------------------
                            msg += FMC_LORAE_Y2;
                            msg += "=";
                            msg += "(NULL)";
                            msg += "\n";
                            //---------------------------------
                            msg += "F";                 //Vorschub
                            msg += "=";
                            msg += "AUTO";
                            msg += "\n";
                            //---------------------------------
                            msg += "FAN";                 //Anfahr-Vorschub
                            msg += "=";
                            msg += "AUTO";
                            msg += "\n";
                            //---------------------------------
                            msg += "GRP";               //Bohrgruppe
                            msg += "=";
                            msg += bohrgruppe;
                            msg += "\n";
                            //---------------------------------
                            msg += "LGEAB";             //Restbohrmaß
                            msg += "=";
                            msg += "4";
                            msg += "\n";
                            //---------------------------------
                            msg += "LGEAN";             //Anbohrtiefe
                            msg += "=";
                            msg += "4";
                            msg += "\n";
                            //---------------------------------
                            msg += "MITTE";             //Vermitteln  0|1|2
                            msg += "=";
                            msg += "0";
                            msg += "\n";
                            //---------------------------------
                            msg += "MRICHT";            //Messen Seite
                            msg += "=";
                            msg += "0";
                            msg += "\n";
                            //---------------------------------
                            msg += "N";                 //Drehzahl
                            msg += "=";
                            msg += "AUTO";
                            msg += "\n";
                            //---------------------------------
                            msg += FMC_LORAE_RASTER;
                            msg += "=";
                            msg += bora.get_raster_x_qstring();
                            msg += "\n";
                            //---------------------------------
                            msg += "TASTEIN";
                            msg += "=";
                            msg += "-1";
                            msg += "\n";
                            //---------------------------------
                            msg += FMC_LORAE_TI;
                            msg += "=";
                            msg += double_to_qstring(tiefe);
                            msg += "\n";
                            //---------------------------------
                            msg += "ZSM";           //Zustellmaß
                            msg += "=";
                            msg += bora.get_zustellmass_qstring();
                            msg += "\n";
                            //---------------------------------
                            msg += "\n";
                        }else
                        {
                            //Bohrbild in X:
                            //max 6 Bohrungen pro Dialog!
                            for(uint i=0 ; i<bora.get_anz_x() ; i=i+6)
                            {
                                msg += FMC_BOBIX;
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIX_AFB;
                                msg += "=";
                                msg += bora.get_afb();
                                msg += "\n";
                                //------------------------------
                                msg += "BEZB";
                                msg += "=";
                                msg += "Bohren in X  DM";
                                msg += bora.get_dm_qstring();
                                msg += " T";
                                msg += double_to_qstring(tiefe);
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIX_DM;
                                msg += "=";
                                msg += bora.get_dm_qstring();
                                msg += "\n";
                                //------------------------------
                                msg += "F";                     //Vorschub
                                msg += "=";
                                msg += "AUTO";
                                msg += "\n";
                                //------------------------------
                                msg += "FAN";                   //Anfahrvorschub
                                msg += "=";
                                msg += "AUTO";
                                msg += "\n";
                                //------------------------------
                                msg += "GRP";                   //Bohrgruppe
                                msg += "=";
                                msg += bohrgruppe;
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIX_KM;            //Kettenmaß
                                msg += "=";
                                msg += "1";
                                msg += "\n";
                                //------------------------------
                                msg += "LGEAB";                 //Restbohrmaß
                                msg += "=";
                                msg += "4";
                                msg += "\n";
                                //------------------------------
                                msg += "LGEAN";                 //Anbohrtiefe
                                msg += "=";
                                msg += "4";
                                msg += "\n";
                                //------------------------------
                                msg += "MRICHT";                //Messen Seite
                                msg += "=";
                                msg += "0";
                                msg += "\n";
                                //------------------------------
                                msg += "N";                     //Drehzahl
                                msg += "=";
                                msg += "AUTO";
                                msg += "\n";
                                //------------------------------
                                msg += "TASTEIN";               //Taste Satz ein
                                msg += "=";
                                msg += "-1";
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIX_TI;            //Tiefe
                                msg += "=";
                                msg += double_to_qstring(tiefe);
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIX_X1;
                                msg += "=";
                                msg += double_to_qstring(  bora.get_x() + (i*bora.get_raster_x())  );
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIX_X2;
                                msg += "=";
                                if(bora.get_anz_x() >= i+2)
                                {
                                    msg += bora.get_raster_x_qstring();
                                }else
                                {
                                    msg += "(NULL)";
                                }
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIX_X3;
                                msg += "=";
                                if(bora.get_anz_x() >= i+3)
                                {
                                    msg += bora.get_raster_x_qstring();
                                }else
                                {
                                    msg += "(NULL)";
                                }
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIX_X4;
                                msg += "=";
                                if(bora.get_anz_x() >= i+4)
                                {
                                    msg += bora.get_raster_x_qstring();
                                }else
                                {
                                    msg += "(NULL)";
                                }
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIX_X5;
                                msg += "=";
                                if(bora.get_anz_x() >= i+5)
                                {
                                    msg += bora.get_raster_x_qstring();
                                }else
                                {
                                    msg += "(NULL)";
                                }
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIX_X6;
                                msg += "=";
                                if(bora.get_anz_x() >= i+6)
                                {
                                    msg += bora.get_raster_x_qstring();
                                }else
                                {
                                    msg += "(NULL)";
                                }
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIX_Y1;
                                msg += "=";
                                msg += bora.get_y_qstring();
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIX_Y2;
                                msg += "=";
                                msg += "-1";
                                msg += "\n";
                                //------------------------------
                                msg += "ZSM";           //Zustellmaß
                                msg += "=";
                                msg += bora.get_zustellmass_qstring();
                                msg += "\n";
                                //------------------------------
                                msg += "\n";
                            }
                        }
                    }else if(bora.get_anz_x() == 1)
                    {
                        //Bohrbild in Y:
                        //max 6 Bohrungen pro Dialog!
                        for(uint i=0 ; i<bora.get_anz_y() ; i=i+6)
                        {
                            msg += FMC_BOBIY;
                            msg += "\n";
                            //------------------------------
                            msg += FMC_BOBIX_AFB;
                            msg += "=";
                            msg += bora.get_afb();
                            msg += "\n";
                            //------------------------------
                            msg += "BEZB";
                            msg += "=";
                            msg += "Bohren in Y  DM";
                            msg += bora.get_dm_qstring();
                            msg += " T";
                            msg += double_to_qstring(tiefe);
                            msg += "\n";
                            //------------------------------
                            msg += FMC_BOBIX_DM;
                            msg += "=";
                            msg += bora.get_dm_qstring();
                            msg += "\n";
                            //------------------------------
                            msg += "F";                     //Vorschub
                            msg += "=";
                            msg += "AUTO";
                            msg += "\n";
                            //------------------------------
                            msg += "FAN";                   //Anfahrvorschub
                            msg += "=";
                            msg += "AUTO";
                            msg += "\n";
                            //------------------------------
                            msg += "GRP";                   //Bohrgruppe
                            msg += "=";
                            msg += bohrgruppe;
                            msg += "\n";
                            //------------------------------
                            msg += FMC_BOBIY_KM;            //Kettenmaß
                            msg += "=";
                            msg += "1";
                            msg += "\n";
                            //------------------------------
                            msg += "LGEAB";                 //Restbohrmaß
                            msg += "=";
                            msg += "4";
                            msg += "\n";
                            //------------------------------
                            msg += "LGEAN";                 //Anbohrtiefe
                            msg += "=";
                            msg += "4";
                            msg += "\n";
                            //------------------------------
                            msg += "MRICHT";                //Messen Seite
                            msg += "=";
                            msg += "0";
                            msg += "\n";
                            //------------------------------
                            msg += "N";                     //Drehzahl
                            msg += "=";
                            msg += "AUTO";
                            msg += "\n";
                            //------------------------------
                            msg += "TASTEIN";               //Taste Satz ein
                            msg += "=";
                            msg += "-1";
                            msg += "\n";
                            //------------------------------
                            msg += FMC_BOBIY_TI;            //Tiefe
                            msg += "=";
                            msg += double_to_qstring(tiefe);
                            msg += "\n";
                            //------------------------------
                            msg += FMC_BOBIY_Y1;
                            msg += "=";
                            msg += double_to_qstring(  bora.get_y() + (i*bora.get_raster_y())  );
                            msg += "\n";
                            //------------------------------
                            msg += FMC_BOBIY_Y2;
                            msg += "=";
                            if(bora.get_anz_y() >= i+2)
                            {
                                msg += bora.get_raster_y_qstring();
                            }else
                            {
                                msg += "(NULL)";
                            }
                            msg += "\n";
                            //------------------------------
                            msg += FMC_BOBIY_Y3;
                            msg += "=";
                            if(bora.get_anz_y() >= i+3)
                            {
                                msg += bora.get_raster_y_qstring();
                            }else
                            {
                                msg += "(NULL)";
                            }
                            msg += "\n";
                            //------------------------------
                            msg += FMC_BOBIY_Y4;
                            msg += "=";
                            if(bora.get_anz_y() >= i+4)
                            {
                                msg += bora.get_raster_y_qstring();
                            }else
                            {
                                msg += "(NULL)";
                            }
                            msg += "\n";
                            //------------------------------
                            msg += FMC_BOBIY_Y5;
                            msg += "=";
                            if(bora.get_anz_y() >= i+5)
                            {
                                msg += bora.get_raster_y_qstring();
                            }else
                            {
                                msg += "(NULL)";
                            }
                            msg += "\n";
                            //------------------------------
                            msg += FMC_BOBIY_Y6;
                            msg += "=";
                            if(bora.get_anz_y() >= i+6)
                            {
                                msg += bora.get_raster_y_qstring();
                            }else
                            {
                                msg += "(NULL)";
                            }
                            msg += "\n";
                            //------------------------------
                            msg += FMC_BOBIY_X1;
                            msg += "=";
                            msg += bora.get_x_qstring();
                            msg += "\n";
                            //------------------------------
                            msg += FMC_BOBIY_X2;
                            msg += "=";
                            msg += "-1";
                            msg += "\n";
                            //------------------------------
                            msg += "ZSM";           //Zustellmaß
                            msg += "=";
                            msg += bora.get_zustellmass_qstring();
                            msg += "\n";
                            //------------------------------
                            msg += "\n";
                        }
                    }else
                    {
                        //Bislang noch keine Lochrasttererkennung in X und Y gleichzeitig vorhanden
                        //desshalb Ausgabe an dieser Stellen nicht nötig
                    }
                }else if(bezug == WST_BEZUG_LI)
                {
                    //HBE Xplus:
                    for(uint i=0 ; i<bora.get_anz_y() ; i=i+6)
                    {
                        msg += FMC_HBEXP;
                        msg += "\n";
                        //------------------------------
                        msg += "Y1=";
                        msg += double_to_qstring(  bora.get_y() + (i*bora.get_raster_y())  );
                        msg += "\n";
                        //------------------------------
                        msg += "Y2=";
                        if(bora.get_anz_y() >= i+2)
                        {
                            msg += bora.get_raster_y_qstring();
                        }else
                        {
                            msg += "(NULL)";
                        }
                        msg += "\n";
                        //------------------------------
                        msg += "Y3=";
                        if(bora.get_anz_y() >= i+3)
                        {
                            msg += bora.get_raster_y_qstring();
                        }else
                        {
                            msg += "(NULL)";
                        }
                        msg += "\n";
                        //------------------------------
                        msg += "Y4=";
                        if(bora.get_anz_y() >= i+4)
                        {
                            msg += bora.get_raster_y_qstring();
                        }else
                        {
                            msg += "(NULL)";
                        }
                        msg += "\n";
                        //------------------------------
                        msg += "Y5=";
                        if(bora.get_anz_y() >= i+5)
                        {
                            msg += bora.get_raster_y_qstring();
                        }else
                        {
                            msg += "(NULL)";
                        }
                        msg += "\n";
                        //------------------------------
                        msg += "Y6=";
                        if(bora.get_anz_y() >= i+6)
                        {
                            msg += bora.get_raster_y_qstring();
                        }else
                        {
                            msg += "(NULL)";
                        }
                        msg += "\n";
                        //------------------------------
                        msg += "TI=";
                        msg += bora.get_tiefe_qstring();
                        msg += "\n";
                        msg += "Z=";
                        msg += bora.get_z_qstring();
                        msg += "\n";
                        msg += "DM=";
                        msg += bora.get_dm_qstring();
                        msg += "\n";
                        msg += "KETTE=1\n";
                        msg += "GRP=1\n";           //Bohrgruppe
                        msg += "X2=-1\n";
                        msg += "X1=0\n";

                        //Anbohrtiefe gem. Voreinstellung IMAWOP
                        //Anbohrvorschub gem. Voreinstellung IMAWOP
                        //Bohrvorschub gem. Voreinstellung IMAWOP
                        //Drehzahl gem. Voreinstellung IMAWOP

                        msg += "BEZB=";
                        msg += "HBE X+ DM";
                        msg += bora.get_dm_qstring();
                        msg += " T";
                        msg += bora.get_tiefe_qstring();
                        msg += "\n";
                        msg += "AFB=";
                        msg += bora.get_afb();
                        msg += "\n";
                        msg += "\n";
                    }
                }else if(bezug == WST_BEZUG_RE)
                {
                    //HBE Xminus:
                    for(uint i=0 ; i<bora.get_anz_y() ; i=i+6)
                    {
                        msg += FMC_HBEXM;
                        msg += "\n";
                        //------------------------------
                        msg += "Y1=";
                        msg += double_to_qstring(  bora.get_y() + (i*bora.get_raster_y())  );
                        msg += "\n";
                        //------------------------------
                        msg += "Y2=";
                        if(bora.get_anz_y() >= i+2)
                        {
                            msg += bora.get_raster_y_qstring();
                        }else
                        {
                            msg += "(NULL)";
                        }
                        msg += "\n";
                        //------------------------------
                        msg += "Y3=";
                        if(bora.get_anz_y() >= i+3)
                        {
                            msg += bora.get_raster_y_qstring();
                        }else
                        {
                            msg += "(NULL)";
                        }
                        msg += "\n";
                        //------------------------------
                        msg += "Y4=";
                        if(bora.get_anz_y() >= i+4)
                        {
                            msg += bora.get_raster_y_qstring();
                        }else
                        {
                            msg += "(NULL)";
                        }
                        msg += "\n";
                        //------------------------------
                        msg += "Y5=";
                        if(bora.get_anz_y() >= i+5)
                        {
                            msg += bora.get_raster_y_qstring();
                        }else
                        {
                            msg += "(NULL)";
                        }
                        msg += "\n";
                        //------------------------------
                        msg += "Y6=";
                        if(bora.get_anz_y() >= i+6)
                        {
                            msg += bora.get_raster_y_qstring();
                        }else
                        {
                            msg += "(NULL)";
                        }
                        msg += "\n";
                        //------------------------------
                        msg += "TI=";
                        msg += bora.get_tiefe_qstring();
                        msg += "\n";
                        msg += "Z=";
                        msg += bora.get_z_qstring();
                        msg += "\n";
                        msg += "DM=";
                        msg += bora.get_dm_qstring();
                        msg += "\n";
                        msg += "KETTE=1\n";
                        msg += "GRP=1\n";           //Bohrgruppe
                        msg += "X2=-1\n";
                        msg += "X1=L\n";

                        //Anbohrtiefe gem. Voreinstellung IMAWOP
                        //Anbohrvorschub gem. Voreinstellung IMAWOP
                        //Bohrvorschub gem. Voreinstellung IMAWOP
                        //Drehzahl gem. Voreinstellung IMAWOP

                        msg += "BEZB=";
                        msg += "HBE X- DM";
                        msg += bora.get_dm_qstring();
                        msg += " T";
                        msg += bora.get_tiefe_qstring();
                        msg += "\n";
                        msg += "AFB=";
                        msg += bora.get_afb();
                        msg += "\n";
                        msg += "\n";
                    }
                }else if(bezug == WST_BEZUG_VO)
                {
                    //HBE Yplus:
                    for(uint i=0 ; i<bora.get_anz_x() ; i=i+6)
                    {
                        msg += FMC_HBEYP;
                        msg += "\n";
                        msg += "X1=";
                        msg += double_to_qstring(  bora.get_x() + (i*bora.get_raster_x())  );
                        msg += "\n";
                        //------------------------------
                        msg += "X2=";
                        if(bora.get_anz_x() >= i+2)
                        {
                            msg += bora.get_raster_x_qstring();
                        }else
                        {
                            msg += "(NULL)";
                        }
                        msg += "\n";
                        //------------------------------
                        msg += "X3=";
                        if(bora.get_anz_x() >= i+3)
                        {
                            msg += bora.get_raster_x_qstring();
                        }else
                        {
                            msg += "(NULL)";
                        }
                        msg += "\n";
                        //------------------------------
                        msg += "X4=";
                        if(bora.get_anz_x() >= i+4)
                        {
                            msg += bora.get_raster_x_qstring();
                        }else
                        {
                            msg += "(NULL)";
                        }
                        msg += "\n";
                        //------------------------------
                        msg += "X5=";
                        if(bora.get_anz_x() >= i+5)
                        {
                            msg += bora.get_raster_x_qstring();
                        }else
                        {
                            msg += "(NULL)";
                        }
                        msg += "\n";
                        //------------------------------
                        msg += "X6=";
                        if(bora.get_anz_x() >= i+6)
                        {
                            msg += bora.get_raster_x_qstring();
                        }else
                        {
                            msg += "(NULL)";
                        }
                        msg += "\n";
                        //------------------------------
                        msg += "TI=";
                        msg += bora.get_tiefe_qstring();
                        msg += "\n";
                        msg += "Z=";
                        msg += bora.get_z_qstring();
                        msg += "\n";
                        msg += "DM=";
                        msg += bora.get_dm_qstring();
                        msg += "\n";
                        msg += "KETTE=1\n";
                        msg += "GRP=1\n";           //Bohrgruppe
                        msg += "Y2=-1\n";
                        msg += "Y1=0\n";

                        //Anbohrtiefe gem. Voreinstellung IMAWOP
                        //Anbohrvorschub gem. Voreinstellung IMAWOP
                        //Bohrvorschub gem. Voreinstellung IMAWOP
                        //Drehzahl gem. Voreinstellung IMAWOP

                        msg += "BEZB=";
                        msg += "HBE Y+ DM";
                        msg += bora.get_dm_qstring();
                        msg += " T";
                        msg += bora.get_tiefe_qstring();
                        msg += "\n";
                        msg += "AFB=";
                        msg += bora.get_afb();
                        msg += "\n";
                        msg += "\n";
                    }
                }else if(bezug == WST_BEZUG_HI)
                {
                    //HBE Yminus:
                    for(uint i=0 ; i<bora.get_anz_x() ; i=i+6)
                    {
                        msg += FMC_HBEYM;
                        msg += "\n";
                        msg += "X1=";
                        msg += double_to_qstring(  bora.get_x() + (i*bora.get_raster_x())  );
                        msg += "\n";
                        //------------------------------
                        msg += "X2=";
                        if(bora.get_anz_x() >= i+2)
                        {
                            msg += bora.get_raster_x_qstring();
                        }else
                        {
                            msg += "(NULL)";
                        }
                        msg += "\n";
                        //------------------------------
                        msg += "X3=";
                        if(bora.get_anz_x() >= i+3)
                        {
                            msg += bora.get_raster_x_qstring();
                        }else
                        {
                            msg += "(NULL)";
                        }
                        msg += "\n";
                        //------------------------------
                        msg += "X4=";
                        if(bora.get_anz_x() >= i+4)
                        {
                            msg += bora.get_raster_x_qstring();
                        }else
                        {
                            msg += "(NULL)";
                        }
                        msg += "\n";
                        //------------------------------
                        msg += "X5=";
                        if(bora.get_anz_x() >= i+5)
                        {
                            msg += bora.get_raster_x_qstring();
                        }else
                        {
                            msg += "(NULL)";
                        }
                        msg += "\n";
                        //------------------------------
                        msg += "X6=";
                        if(bora.get_anz_x() >= i+6)
                        {
                            msg += bora.get_raster_x_qstring();
                        }else
                        {
                            msg += "(NULL)";
                        }
                        msg += "\n";
                        //------------------------------
                        msg += "TI=";
                        msg += bora.get_tiefe_qstring();
                        msg += "\n";
                        msg += "Z=";
                        msg += bora.get_z_qstring();
                        msg += "\n";
                        msg += "DM=";
                        msg += bora.get_dm_qstring();
                        msg += "\n";
                        msg += "KETTE=1\n";
                        msg += "GRP=1\n";           //Bohrgruppe
                        msg += "Y2=-1\n";
                        msg += "Y1=B\n";

                        //Anbohrtiefe gem. Voreinstellung IMAWOP
                        //Anbohrvorschub gem. Voreinstellung IMAWOP
                        //Bohrvorschub gem. Voreinstellung IMAWOP
                        //Drehzahl gem. Voreinstellung IMAWOP

                        msg += "BEZB=";
                        msg += "HBE Y- DM";
                        msg += bora.get_dm_qstring();
                        msg += " T";
                        msg += bora.get_tiefe_qstring();
                        msg += "\n";
                        msg += "AFB=";
                        msg += bora.get_afb();
                        msg += "\n";
                        msg += "\n";
                    }
                }
            }else
            {
                //Sollte nicht vorkommen können, da bohrraster anhand des vorhandenen Werkzeuges ermittelt werden
            }
        }else if(zeile.zeile(1) == BEARBART_NUT)
        {
            nut nu(zeile.get_text());
            QString bezug = nu.get_bezug();
            QString tnummer = wkzmag.get_wkznummer(WKZ_TYP_SAEGE, 0, nu.get_tiefe(), dicke, bezug);
            if(!tnummer.isEmpty())
            {
                double nutblattbreite = wkzmag.get_saegeblattbreite(tnummer).toDouble();
                if(nu.get_breite() < nutblattbreite)
                {
                    //Warnung ausgeben und Nut unterdrücken:
                    QString msg = "";
                    msg += "Achtung bei fmc-Export!\n";
                    msg += "Teilname: ";
                    msg += name;
                    msg += "\n";
                    msg += "Saegeblatt zu breit fuer ";
                    msg += get_bearb_menschlich_lesbar(zeile);
                    msg += "\n";
                    msg += "Bitte FMC-Programm pruefen und schmaleres Nutblatt zuweisen.";

                    QMessageBox mb;
                    mb.setText(msg);
                    mb.exec();
                }
                if(bezug == WST_BEZUG_OBSEI)
                {
                    //Bezugskante der Nut finden:
                    QString bezugskante = "0"; //Maß gibt Mittellinie der nut an
                    QString posys = nu.get_ys_qstring();
                    QString posye = nu.get_ye_qstring();
                    if(posys == posye)
                    {
                        if(nu.get_ys() < (tmp_b-nu.get_ys()))
                        {
                            posys = double_to_qstring(  nu.get_ys() - nu.get_breite()/2  );
                            posye = "SY";
                            bezugskante = "2"; //Maß gibt linke Flanke der nut an
                        }else
                        {
                            if(nu.get_breite() == 8.5 && nu.get_tiefe() == 6.5)
                            {
                                posys = "B-";
                                posys += double_to_qstring(  (tmp_b - nu.get_ys()) + nu.get_breite()/2  );
                                posye = "SY";
                                bezugskante = "2"; //Maß gibt linke Flanke der nut an
                            }else
                            {
                                posys = "B-";
                                posys += double_to_qstring(  (tmp_b - nu.get_ys()) - nu.get_breite()/2  );
                                posye = "SY";
                                bezugskante = "1"; //Maß gibt rechte Flanke der nut an
                            }
                        }
                    }

                    msg += FMC_NUT;
                    msg += "\n";
                    msg += "WKZID=";                //WKZ-Nummer
                    msg += tnummer;
                    msg += "\n";
                    msg += "SWKZID=";               //Spiegel-WKZ-Nummer
                    msg += tnummer;
                    msg += "\n";
                    msg += "WERKZEUGNAME=";         //WKZ-Nummer
                    msg += tnummer;
                    msg += "\n";
                    msg += "WKZAKTUELL=1";
                    msg += "\n";
                    msg += "SPX=";
                    //Nuten auf unserer BIMA310 müssen immer von L zu 0 verlaufen
                    //Da Agregat versetzt wenn es gedreht wird
                    if(nu.get_ys() == nu.get_ye())
                    {
                        if(nu.get_xs() > nu.get_xe())
                        {
                            msg += nu.get_xs_qstring();
                        }else
                        {
                            msg += nu.get_xe_qstring();
                        }
                    }else
                    {
                        msg += nu.get_xs_qstring();
                    }
                    msg += "\n";


                    msg += "SPY=";
                    msg += posys;
                    msg += "\n";
                    msg += "EPX=";
                    if(nu.get_ys() == nu.get_ye())
                    {
                        if(nu.get_xs() < nu.get_xe())
                        {
                            msg += nu.get_xs_qstring();
                        }else
                        {
                            msg += nu.get_xe_qstring();
                        }
                    }else
                    {
                         msg += nu.get_xe_qstring();
                    }
                    msg += "\n";
                    msg += "EPY=";
                    msg += posye;
                    msg += "\n";
                    msg += "TI=";
                    msg += nu.get_tiefe_qstring();
                    msg += "\n";
                    msg += "NB=";
                    msg += nu.get_breite_qstring();
                    msg += "\n";
                    msg += "TYPA=1\n";              //Auslauf                    
                    msg += "TRKOR=";                //Korrektur/Bezugskante
                    msg += bezugskante;
                    msg += "\n";
                    msg += "GEGENL=0\n";            //Genenlauf
                    msg += "TWKL=0\n";              //Neigungswinkel
                    msg += "TYPN=1\n";              //Neigungstyp
                    msg += "ABSTN=10\n";            //Abstand auf Neigung
                    msg += "Z=D/2\n";               //POs in Z

                    //Eintauchvorschub gem. Voreinstellung IMAWOP
                    //Vorschub gem. Voreinstellung IMAWOP
                    //Drehzahl gem. Voreinstellung IMAWOP

                    msg += "BEZB=";
                    msg += "Nut B";
                    msg += nu.get_breite_qstring();
                    msg += " T";
                    msg += nu.get_tiefe_qstring();
                    msg += "\n";
                    msg += FMC_BOHR_DM_AFB;
                    msg += "=";
                    msg += nu.get_afb();
                    msg += "\n";
                    msg += "\n";
                }
            }else
            {
                //Mit Fehlermeldung abbrechen:
                QString msg = fehler_kein_WKZ("fmc", zeile);
                QMessageBox mb;
                mb.setText(msg);
                mb.exec();
                return msg;
            }
        }else if(zeile.zeile(1) == BEARBART_RTA)
        {
            rechtecktasche rt(zeile.get_text());
            QString tnummer = wkzmag.get_wkznummer_von_alias(rt.get_wkznum());//Ist direkt ei WKZ definiert?
            if(tnummer.isEmpty())
            {
                QString bezug = rt.get_bezug();
                double minmass = 0;
                if(rt.get_laenge() < rt.get_breite())
                {
                    minmass = rt.get_laenge();
                }else
                {
                    minmass = get_breite();
                }
                tnummer = wkzmag.get_wkznummer(WKZ_TYP_FRAESER, minmass, rt.get_tiefe(), dicke, bezug);
            }
            if(!tnummer.isEmpty())
            {
                double zustellmas = rt.get_zustellmass();
                if(zustellmas <= 0)
                {
                    zustellmas = wkzmag.get_zustellmass(tnummer).toDouble();
                }

                double tiefe = 0;
                QString tiefe_qstring;
                if(rt.get_tiefe() > get_dicke())
                {
                    tiefe = get_dicke() - rt.get_tiefe();
                    tiefe_qstring = double_to_qstring(tiefe);
                }else if(get_dicke()-rt.get_tiefe() <= 2)
                {
                    tiefe_qstring  = "D-";
                    tiefe_qstring += double_to_qstring(get_dicke()-rt.get_tiefe());
                }else
                {
                    tiefe = rt.get_tiefe();
                    tiefe_qstring = double_to_qstring(tiefe);
                }

                double radius = rt.get_rad();

                if(rt.get_bezug() == WST_BEZUG_OBSEI)
                {
                    msg += FMC_RTA;
                    msg += "\n";
                    msg += "WKZID=";            //Werkzeugnummer
                    msg += tnummer;
                    msg += "\n";
                    msg += "MPX=";
                    msg += rt.get_x_qstring();
                    msg += "\n";
                    msg += "MPY=";
                    msg += rt.get_y_qstring();
                    msg += "\n";
                    msg += "LGET1=";
                    msg += rt.get_laenge_qstring();
                    msg += "\n";
                    msg += "LGET2=";
                    msg += rt.get_breite_qstring();
                    msg += "\n";
                    msg += "TI=";                   //Tiefe
                    msg += tiefe_qstring;
                    msg += "\n";
                    msg += "R=";
                    msg += double_to_qstring(radius);
                    msg += "\n";
                    msg += "LGEZU=";                //Zustellmaß
                    msg += double_to_qstring(zustellmas);
                    msg += "\n";
                    msg += "GEGENL=";               //Gegenslauf
                    msg += "1";
                    msg += "\n";
                    msg += "WKL=";
                    msg += rt.get_drewi_qstring();
                    msg += "\n";
                    msg += "RAEUMEN=";              //Ausräumen
                    msg += rt.get_ausraeumen_qstring();
                    msg += "\n";
                    msg += "WKZAKTUELL=1\n";

                    //Eintauchvorschub gem. Voreinstellung IMAWOP
                    //Vorschub gem. Voreinstellung IMAWOP
                    //Drehzahl gem. Voreinstellung IMAWOP

                    msg += "BEZB=";
                    msg += "Rechtecktasche L";
                    msg += rt.get_laenge_qstring();
                    msg += " B";
                    msg += rt.get_breite_qstring();
                    msg += "\n";
                    msg += "AFB=";
                    msg += rt.get_afb();
                    msg += "\n";
                    msg += "\n";
                }

            }else
            {
                //Mit Fehlermeldung abbrechen:
                QString msg = fehler_kein_WKZ("fmc", zeile);
                QMessageBox mb;
                mb.setText(msg);
                mb.exec();
                return msg;
            }
        }else if(zeile.zeile(1) == BEARBART_FRAESERAUFRUF)
        {
            fraueseraufruf fa(zeile.get_text());
            QString tnummer = wkzmag.get_wkznummer_von_alias(fa.get_wkznum());
            if(!tnummer.isEmpty())
            {
                double gesamttiefe = fa.get_tiefe();
                double zustellmass = wkzmag.get_zustellmass(tnummer).toDouble();
                double zustelltiefe;
                if(zust_fkon == "wkz")
                {
                    if(zustellmass < gesamttiefe)
                    {
                        zustelltiefe = zustellmass;
                    }else
                    {
                        zustelltiefe = gesamttiefe;
                    }
                }else // == "orgi"
                {
                    zustelltiefe = gesamttiefe;
                }

                QString radkor = fa.get_radkor();
                if(radkor == FRKOR_L)
                {
                    radkor = "1";
                }else if(radkor == FRKOR_M)
                {
                    radkor = "0";
                }else if(radkor == FRKOR_R)
                {
                    radkor = "2";
                }

                if(fa.get_bezug() == WST_BEZUG_OBSEI)
                {
                    msg += kommentar_fmc("--------------------");

                    double backup_i = i;
                    while(1)//abbruch durch breake
                    {
                        i = backup_i;
                        double pos_z = get_dicke()-zustelltiefe;
                        //--------------------------------------------
                        msg += FMC_FKON;
                        msg += "\n";
                        msg += "WKZID=";            //Werkzeugnummer
                        msg += tnummer;
                        msg += "\n";
                        msg += FMC_FKON_X;
                        msg += "=";
                        msg += fa.get_x_qstring();
                        msg += "\n";
                        msg += FMC_FKON_Y;
                        msg += "=";
                        msg += fa.get_y_qstring();
                        msg += "\n";
                        msg += FMC_FKON_Z;
                        msg += "=";
                        msg += double_to_qstring(pos_z);
                        msg += "\n";
                        msg += "EBG=0\n";       //Eckenrunden global
                        msg += "KD=0\n";        //Kantendicke
                        msg += FMC_FKON_KOR;    //Fräsbaohnkorrektur
                        msg += "=";
                        msg += radkor;
                        msg += "\n";

                        //Prüfen ob Eintauchpunkt des Fräsers auf oder neben dem WST liegt:
                        punkt3d pfa;//Punkt Fräseraufruf
                        pfa.set_x(fa.get_x());
                        pfa.set_y(fa.get_y());
                        text_zeilenweise folzei;//Folgezeile
                        folzei.set_trennzeichen(TRENNZ_BEARB_PARAM);
                        folzei.set_text(bearb.zeile(i+1));
                        punkt3d pein;//Eintauchpunkt
                        int anweg = 50;

                        if(folzei.zeile(1) == BEARBART_FRAESERGERADE)
                        {
                            fraesergerade fg(folzei.get_text());
                            strecke s;
                            s.set_start(pfa);
                            punkt3d ep = fg.get_ep();
                            ep.set_z(0);
                            s.set_ende(ep);
                            strecke_bezugspunkt sb;
                            sb = strecke_bezugspunkt_ende;
                            s.set_laenge_2d(s.laenge2dim()+anweg, sb);
                            pein = s.startp();
                        }else if(folzei.zeile(1) == BEARBART_FRAESERBOGEN)
                        {
                            fraeserbogen fb(folzei.get_text());
                            bogen b;
                            b.set_startpunkt(pfa);
                            b.set_endpunkt(fb.get_ep());
                            strecke s;
                            s.set_start(pfa);
                            punkt3d pmibo;
                            pmibo.set_x(b.mitte().x());
                            pmibo.set_y(b.mitte().y());
                            s.set_ende(pmibo);
                            s.drenen_um_startpunkt_2d(90, b.im_uzs());
                            strecke_bezugspunkt sb;
                            sb = strecke_bezugspunkt_start;
                            s.set_laenge_2d(anweg, sb);
                            pein = s.endp();
                        }

                        bool aufwst = punkt_auf_wst(pein.x(), pein.y(), get_laenge(), get_breite(), 1);
                        if(aufwst == true)
                        {
                            msg += "TYPAN=1\n";     //Anfahrtyp
                            msg += "TYPAB=1\n";     //Abfahrtyp
                            msg += "TYPEIN=1\n";    //Eintauchtp
                            if(pos_z > 0)
                            {
                                //Anfahranweisung für nicht durchgefräste Innen-Bahnen:
                                msg += "LGEAN=2*WKZR\n";    //Anfahrwert
                                msg += "LGEAB=2*WKZR\n";    //Abfahrwert
                            }else
                            {
                                //Anfahranweisung für durchgefräste Innen-Bahnen:
                                msg += "LGEAN=50\n";    //Anfahrwert
                                msg += "LGEAB=50\n";    //Abfahrwert
                            }
                        }else
                        {
                            //Anfahranweisung für außen-Bahnen (z.B. Formatierungen):
                            msg += "TYPAN=0\n";     //Anfahrtyp
                            msg += "TYPAB=0\n";     //Abfahrtyp
                            msg += "TYPEIN=-1\n";   //Eintauchtp
                            msg += "LGEAN=2*WKZR+";    //Anfahrwert
                            msg += double_to_qstring(anweg);
                            msg += "\n";
                            msg += "LGEAB=2*WKZR+";    //Abfahrwert
                            msg += double_to_qstring(anweg);
                            msg += "\n";
                        }
                        msg += "FAN=AUTO\n";    //Anfahrvorschub
                        msg += "F=AUTO\n";      //Vorschub
                        //msg += "N=AUTO\n";      //Drehzahl
                        msg += "EVS=0.05\n";    //Ecken-Verschleifen
                        msg += "AFB=";
                        msg += fa.get_afb();
                        msg += "\n";
                        msg += "WKZAKTUELL=1\n";
                        msg += "\n";
                        //--------------------------------------------
                        //Fräsbahnen:
                        while(i+1<=bearb.zeilenanzahl())
                        {
                            zeile.set_text(bearb.zeile(i+1));

                            if(zeile.zeile(1) == BEARBART_FRAESERGERADE)
                            {
                                i++;
                                zeile.set_text(bearb.zeile(i));
                                //Gerade fräsen:
                                fraesergerade fg(zeile.get_text());
                                QString tiefe_fg = 0;
                                if(fg.get_ze() == fa.get_tiefe())
                                {
                                    tiefe_fg = "Z"; //Tiefe beibehalten
                                                    //Führt zu falschen Ergebissen, wenn manuell geschriebene
                                                    //fmc-Programme eingelesen wurden, bei denen
                                                    //die FKONs zwischen dem Fräseraufruf und dieser Gerade
                                                    //nicht den selben Z-Wert haben!!!
                                                    //Dieser Fall wird nicht erwartet....
                                }else
                                {
                                    tiefe_fg = double_to_qstring(  get_dicke()-fg.get_ze()  );
                                }

                                msg += FMC_FKONG;
                                msg += "\n";
                                msg += FMC_FKONG_XE;
                                msg += "=";
                                msg += fg.get_xe_qstring();
                                msg += "\n";
                                msg += FMC_FKONG_YE;
                                msg += "=";
                                msg += fg.get_ye_qstring();
                                msg += "\n";
                                msg += FMC_FKONG_ZE;
                                msg += "=";
                                msg += tiefe_fg;
                                msg += "\n";
                                msg += "\n";
                            }else if(zeile.zeile(1) == BEARBART_FRAESERBOGEN)
                            {
                                i++;
                                zeile.set_text(bearb.zeile(i));
                                //Bogen fräsen:
                                fraeserbogen fb(zeile.get_text());
                                QString tiefe_fb = 0;
                                if(fb.get_ze() == fa.get_tiefe())
                                {
                                    tiefe_fb = "Z"; //Tiefe beibehalten
                                                    //Führt zu falschen Ergebissen, wenn manuell geschriebene
                                                    //fmc-Programme eingelesen wurden, bei denen
                                                    //die FKONs zwischen dem Fräseraufruf und dieser Gerade
                                                    //nicht den selben Z-Wert haben!!!
                                                    //Dieser Fall wird nicht erwartet....
                                }else
                                {
                                    tiefe_fb = double_to_qstring(  get_dicke()-fb.get_ze()  );
                                }
                                QString dlg_name;
                                if(fb.get_uzs() == true)
                                {
                                    dlg_name = FMC_FKONBOGUZS;
                                }else
                                {
                                    dlg_name = FMC_FKONBOGGUZS;
                                }

                                msg += dlg_name;
                                msg += "\n";
                                msg += FMC_FKONBOG_RAD;
                                msg += "=";
                                msg += fb.get_rad_qstring();
                                msg += "\n";
                                msg += FMC_FKONBOG_XE;
                                msg += "=";
                                msg += fb.get_xe_qstring();
                                msg += "\n";
                                msg += FMC_FKONBOG_YE;
                                msg += "=";
                                msg += fb.get_ye_qstring();
                                msg += "\n";
                                msg += FMC_FKONBOG_ZE;
                                msg += "=";
                                msg += tiefe_fb;
                                msg += "\n";
                                msg += "\n";
                            }else
                            {
                                break;
                            }
                        }
                        //--------------------------------------------
                        //Abfahren Fräser:
                        msg += "[KO'AB_N2]";
                        msg += "\n";
                        msg += "AFB=1";
                        msg += "\n";
                        msg += "AGGD=AGGDREHBAR";
                        msg += "\n";
                        msg += "AGGFWKL=AGGFWKL";
                        msg += "\n";
                        msg += "AGGO=AGGOFFSET";
                        msg += "\n";
                        msg += "\n";
                        //--------------------------------------------
                        if(zustelltiefe == gesamttiefe)
                        {
                            break; //letzter Schleifendurchlauf
                        }
                        if(zustelltiefe != gesamttiefe)
                        {
                            msg += kommentar_fmc("---");
                        }
                        if(zustelltiefe+zustellmass  <  gesamttiefe)
                        {
                            zustelltiefe = zustelltiefe + zustellmass;
                        }else
                        {
                            zustelltiefe = gesamttiefe;
                        }
                    }
                    msg += kommentar_fmc("--------------------");
                }

            }else
            {
                //Mit Fehlermeldung abbrechen:
                QString msg = fehler_kein_WKZ("fmc", zeile);
                QMessageBox mb;
                mb.setText(msg);
                mb.exec();
                return msg;
            }
        }
    }
    //---------------------------------------Bearbeitungen Unterseite:
    bool unterseite_hat_bearb = false;
    for(uint i=1 ; i<=bearb.zeilenanzahl() ; i++)
    {
        zeile.set_text(bearb.zeile(i));
        if(zeile.zeile(2) == WST_BEZUG_UNSEI)
        {
            unterseite_hat_bearb = true;
            break;
        }
    }
    if(unterseite_hat_bearb == true)
    {
        msg += kommentar_fmc("--------------------");
        msg += kommentar_fmc("-----------------------------------------");
        msg += FMC_HALT;
        msg += "\n";
        msg += "APX=L+700\n";
        msg += "APY=0\n";
        msg += "BEZB=Halt\n";
        msg += "AFB=1\n";
        msg += "\n";
        msg += kommentar_fmc("drehen um b/2");
        msg += kommentar_fmc("-----------------------------------------");
        msg += kommentar_fmc("--------------------");

        for(uint i=1 ; i<=bearb.zeilenanzahl() ; i++)
        {
            zeile.set_text(bearb.zeile(i));
            if(zeile.zeile(1) == BEARBART_BOHR)
            {
                bohrung bo(zeile.get_text());
                QString bezug = bo.get_bezug();
                QString tnummer = wkzmag.get_wkznummer(WKZ_TYP_BOHRER, bo.get_dm(), bo.get_tiefe(), dicke, bezug);

                //Beareitung auf die Oberseite drehen:
                bo.set_y(  tmp_b - bo.get_y()  );

                if(!tnummer.isEmpty())
                {
                    //Werkzeug wurde gefunden, Bohrung kann gebohrt werden:
                    QString bohrgruppe = "2";
                    if(bezug == WST_BEZUG_UNSEI)
                    {
                        double tiefe;
                        if(bo.get_tiefe() <= get_dicke())
                        {
                            tiefe = bo.get_tiefe();
                        }else
                        {
                            tiefe = get_dicke() - bo.get_tiefe();
                        }
                        msg += FMC_BOHR_DM;
                        msg += "\n";
                        msg += FMC_BOHR_DM_X;
                        msg += "=";
                        msg += double_to_qstring(bo.get_x());
                        msg += "\n";
                        msg += FMC_BOHR_DM_Y;
                        msg += "=";
                        msg += double_to_qstring(bo.get_y());
                        msg += "\n";
                        msg += FMC_BOHR_DM_TIEFE;
                        msg += "=";
                        msg += double_to_qstring(tiefe);
                        msg += "\n";
                        msg += FMC_BOHR_DM_DM;
                        msg += "=";
                        msg += bo.get_dm_qstring();
                        msg += "\n";
                        msg += "GRP=";                  //Bohrgruppe
                        msg += bohrgruppe;
                        msg += "\n";

                        //Anbohrtiefe gem. Voreinstellung IMAWOP
                        //Anbohrvorschub gem. Voreinstellung IMAWOP
                        //Restbohrmaß gem. Voreinstellung IMAWOP
                        //Bohrvorschub gem. Voreinstellung IMAWOP

                        msg += "ZSM=";                  //Zustellmaß
                        msg += wkzmag.get_zustellmass(tnummer);
                        msg += "\n";

                        //Drehzahl gem. Voreinstellung IMAWOP

                        msg += "MRICHT=0\n";
                        msg += "TASTEIN=-1\n";
                        msg += "BEZB=";
                        msg += "Bohrung DM";
                        msg += bo.get_dm_qstring();
                        msg += " T";
                        msg += double_to_qstring(tiefe);
                        msg += "\n";
                        msg += FMC_BOHR_DM_AFB;
                        msg += "=";
                        msg += bo.get_afb();
                        msg += "\n";
                        msg += "\n";
                    }
                }else
                {
                    //Kein Werkzeug wurde gefunden.
                    //Kann Bohrung als Kreistasche gefräst werden?:
                    tnummer = wkzmag.get_wkznummer_von_alias(bo.get_wkznum());//Ist direkt ei WKZ definiert?
                    if(tnummer.isEmpty())
                    {
                        tnummer = wkzmag.get_wkznummer(WKZ_TYP_FRAESER, bo.get_dm(), bo.get_tiefe(), dicke, bezug);
                    }
                    if(!tnummer.isEmpty())
                    {
                        double zustellmas = bo.get_zustellmass();
                        if(zustellmas <= 0)
                        {
                            zustellmas = wkzmag.get_zustellmass(tnummer).toDouble();
                        }

                        double tiefe = 0;
                        QString tiefe_qstring;
                        if(bo.get_tiefe() > get_dicke())
                        {
                            tiefe = get_dicke() - bo.get_tiefe();
                            tiefe_qstring = double_to_qstring(tiefe);
                        }else if(get_dicke()-bo.get_tiefe() <= 2)
                        {
                            tiefe_qstring  = "D-";
                            tiefe_qstring += double_to_qstring(get_dicke()-bo.get_tiefe());
                        }else
                        {
                            tiefe = bo.get_tiefe();
                            tiefe_qstring = double_to_qstring(tiefe);
                        }

                        bool ausraeumen = true;
                        if(bo.get_dm() > 2*wkzmag.get_dm(tnummer).toDouble()+20)
                        {
                            if(bo.get_tiefe() < 0  ||  bo.get_tiefe() > get_dicke())
                            {
                                ausraeumen = false;
                            }
                        }
                        if(bo.get_dm() > min_kta_dm_ausraeumen_false)
                        {
                            ausraeumen = false;
                        }

                        if(bo.get_bezug() == WST_BEZUG_UNSEI)
                        {
                            msg += FMC_KTA;
                            msg += "\n";
                            msg += "WKZID=";           //WKZ-Nummer
                            msg += tnummer;
                            msg += "\n";
                            msg += "MPX=";
                            msg += bo.get_x_qstring();
                            msg += "\n";
                            msg += "MPY=";
                            msg += bo.get_y_qstring();
                            msg += "\n";
                            msg += "DM=";
                            msg += bo.get_dm_qstring();
                            msg += "\n";
                            msg += "TI=";
                            msg += tiefe_qstring;
                            msg += "\n";
                            msg += "LGEZU=";            //Zustellmaß
                            msg += double_to_qstring(zustellmas);
                            msg += "\n";
                            msg += "GEGENL=1\n";        //Gegenlauf
                            msg += "RAEUMEN=";          //Ausräumen
                            if(ausraeumen == true)
                            {
                                msg += "1";
                            }else
                            {
                                msg += "0";
                            }
                            msg += "\n";

                            //Eintauchvorschub gem. Voreinstellung IMAWOP
                            //Vorschub gem. Voreinstellung IMAWOP
                            //Drehzahl gem. Voreinstellung IMAWOP

                            msg += "BEZB=";
                            msg += "Kreistasche DM";
                            msg += bo.get_dm_qstring();
                            msg += " T";
                            msg += tiefe_qstring;
                            msg += "\n";
                            msg += "AFB=";
                            msg += bo.get_afb();
                            msg += "\n";
                            msg += "WKZAKTUELL=1\n";
                            msg += "\n";
                        }

                    }else
                    {
                        //Mit Fehlermeldung abbrechen:
                        QString msg = "";
                        msg += "Fehler bei Export ganx!\n";
                        msg += "Teilname: ";
                        msg += name;
                        msg += "\n";
                        msg += "Kein Werkzeug fuer:\n";
                        msg += zeile.get_text();

                        QMessageBox mb;
                        mb.setText(msg);
                        mb.exec();
                        return msg;
                    }
                }
            }else if(zeile.zeile(1) == BEARBART_BOHRRASTER)
            {
                bohrraster bora(zeile.get_text());
                QString bezug = bora.get_bezug();
                QString tnummer = wkzmag.get_wkznummer(WKZ_TYP_BOHRER, bora.get_dm(), bora.get_tiefe(), dicke, bezug);

                //Beareitung auf die Oberseite drehen:
                bora.set_y(  tmp_b - bora.get_y()  );
                bora.set_raster_y( -1 * bora.get_raster_y() );

                if(!tnummer.isEmpty())
                {
                    //Werkzeug wurde gefunden, Bohrung kann gebohrt werden:
                    QString bohrgruppe = "2";
                    if(bezug == WST_BEZUG_UNSEI)
                    {
                        double tiefe;
                        if(bora.get_tiefe() <= get_dicke())
                        {
                            tiefe = bora.get_tiefe();
                        }else
                        {
                            tiefe = get_dicke() - bora.get_tiefe();
                        }

                        //Lochreihen ausgeben
                        if(bora.get_anz_y() == 1)
                        {
                            //Lochreihen oder Bohrbild in X?:
                            if(bora.get_raster_x() == 32  &&  bora.get_dm() == 5)
                            {
                                //Lochreihe:
                                msg += FMC_LORAE;
                                msg += "\n";
                                //---------------------------------
                                msg += FMC_LORAE_AFB;       //Aufruf Lochreihendialog
                                msg += bora.get_afb();
                                msg += "\n";
                                //---------------------------------
                                msg += FMC_LORAE_BEZ;       //Bezeichnung
                                msg += "=";
                                msg += "Lochreihe DM";
                                msg += bora.get_dm_qstring();
                                msg += " T";
                                msg += double_to_qstring(tiefe);
                                msg += "\n";
                                //---------------------------------
                                msg += FMC_LORAE_DM;        //Durchmesser
                                msg += "=";
                                msg += bora.get_dm_qstring();
                                msg += "\n";
                                //---------------------------------
                                msg += FMC_LORAE_XS;        //Startpunkt in X
                                msg += "=";
                                msg += bora.get_x_qstring();
                                msg += "\n";
                                //---------------------------------
                                msg += FMC_LORAE_XE;        //Endpunkt in X
                                msg += "=";
                                msg += double_to_qstring(bora.get_x() + (bora.get_anz_x()*(bora.get_raster_x()-1))  );
                                msg += "+0.5";              //Sonst ist es zu genau und es wird ggf 1 Bohrung zu wenig gebohrt
                                msg += "\n";
                                //---------------------------------
                                msg += "EPY";
                                msg += "=";
                                msg += "Y1";                //gerade verlaufende Lochreihe von 0 bis L
                                msg += "\n";
                                //---------------------------------
                                msg += FMC_LORAE_Y1;
                                msg += "=";
                                msg += bora.get_y_qstring();
                                msg += "\n";
                                //---------------------------------
                                msg += FMC_LORAE_Y2;
                                msg += "=";
                                msg += "(NULL)";
                                msg += "\n";
                                //---------------------------------
                                msg += "F";                 //Vorschub
                                msg += "=";
                                msg += "AUTO";
                                msg += "\n";
                                //---------------------------------
                                msg += "FAN";                 //Anfahr-Vorschub
                                msg += "=";
                                msg += "AUTO";
                                msg += "\n";
                                //---------------------------------
                                msg += "GRP";               //Bohrgruppe
                                msg += "=";
                                msg += bohrgruppe;
                                msg += "\n";
                                //---------------------------------
                                msg += "LGEAB";             //Restbohrmaß
                                msg += "=";
                                msg += "4";
                                msg += "\n";
                                //---------------------------------
                                msg += "LGEAN";             //Anbohrtiefe
                                msg += "=";
                                msg += "4";
                                msg += "\n";
                                //---------------------------------
                                msg += "MITTE";             //Vermitteln  0|1|2
                                msg += "=";
                                msg += "0";
                                msg += "\n";
                                //---------------------------------
                                msg += "MRICHT";            //Messen Seite
                                msg += "=";
                                msg += "0";
                                msg += "\n";
                                //---------------------------------
                                msg += "N";                 //Drehzahl
                                msg += "=";
                                msg += "AUTO";
                                msg += "\n";
                                //---------------------------------
                                msg += FMC_LORAE_RASTER;
                                msg += "=";
                                msg += bora.get_raster_x_qstring();
                                msg += "\n";
                                //---------------------------------
                                msg += "TASTEIN";
                                msg += "=";
                                msg += "-1";
                                msg += "\n";
                                //---------------------------------
                                msg += FMC_LORAE_TI;
                                msg += "=";
                                msg += double_to_qstring(tiefe);
                                msg += "\n";
                                //---------------------------------
                                msg += "ZSM";           //Zustellmaß
                                msg += "=";
                                msg += bora.get_zustellmass_qstring();
                                msg += "\n";
                                //---------------------------------
                                msg += "\n";
                            }else
                            {
                                //Bohrbild in X:
                                //max 6 Bohrungen pro Dialog!
                                for(uint i=0 ; i<bora.get_anz_x() ; i=i+6)
                                {
                                    msg += FMC_BOBIX;
                                    msg += "\n";
                                    //------------------------------
                                    msg += FMC_BOBIX_AFB;
                                    msg += "=";
                                    msg += bora.get_afb();
                                    msg += "\n";
                                    //------------------------------
                                    msg += "BEZB";
                                    msg += "=";
                                    msg += "Bohren in X  DM";
                                    msg += bora.get_dm_qstring();
                                    msg += " T";
                                    msg += double_to_qstring(tiefe);
                                    msg += "\n";
                                    //------------------------------
                                    msg += FMC_BOBIX_DM;
                                    msg += "=";
                                    msg += bora.get_dm_qstring();
                                    msg += "\n";
                                    //------------------------------
                                    msg += "F";                     //Vorschub
                                    msg += "=";
                                    msg += "AUTO";
                                    msg += "\n";
                                    //------------------------------
                                    msg += "FAN";                   //Anfahrvorschub
                                    msg += "=";
                                    msg += "AUTO";
                                    msg += "\n";
                                    //------------------------------
                                    msg += "GRP";                   //Bohrgruppe
                                    msg += "=";
                                    msg += bohrgruppe;
                                    msg += "\n";
                                    //------------------------------
                                    msg += FMC_BOBIX_KM;            //Kettenmaß
                                    msg += "=";
                                    msg += "1";
                                    msg += "\n";
                                    //------------------------------
                                    msg += "LGEAB";                 //Restbohrmaß
                                    msg += "=";
                                    msg += "4";
                                    msg += "\n";
                                    //------------------------------
                                    msg += "LGEAN";                 //Anbohrtiefe
                                    msg += "=";
                                    msg += "4";
                                    msg += "\n";
                                    //------------------------------
                                    msg += "MRICHT";                //Messen Seite
                                    msg += "=";
                                    msg += "0";
                                    msg += "\n";
                                    //------------------------------
                                    msg += "N";                     //Drehzahl
                                    msg += "=";
                                    msg += "AUTO";
                                    msg += "\n";
                                    //------------------------------
                                    msg += "TASTEIN";               //Taste Satz ein
                                    msg += "=";
                                    msg += "-1";
                                    msg += "\n";
                                    //------------------------------
                                    msg += FMC_BOBIX_TI;            //Tiefe
                                    msg += "=";
                                    msg += double_to_qstring(tiefe);
                                    msg += "\n";
                                    //------------------------------
                                    msg += FMC_BOBIX_X1;
                                    msg += "=";
                                    msg += double_to_qstring(  bora.get_x() + (i*bora.get_raster_x())  );
                                    msg += "\n";
                                    //------------------------------
                                    msg += FMC_BOBIX_X2;
                                    msg += "=";
                                    if(bora.get_anz_x() >= i+2)
                                    {
                                        msg += bora.get_raster_x_qstring();
                                    }else
                                    {
                                        msg += "(NULL)";
                                    }
                                    msg += "\n";
                                    //------------------------------
                                    msg += FMC_BOBIX_X3;
                                    msg += "=";
                                    if(bora.get_anz_x() >= i+3)
                                    {
                                        msg += bora.get_raster_x_qstring();
                                    }else
                                    {
                                        msg += "(NULL)";
                                    }
                                    msg += "\n";
                                    //------------------------------
                                    msg += FMC_BOBIX_X4;
                                    msg += "=";
                                    if(bora.get_anz_x() >= i+4)
                                    {
                                        msg += bora.get_raster_x_qstring();
                                    }else
                                    {
                                        msg += "(NULL)";
                                    }
                                    msg += "\n";
                                    //------------------------------
                                    msg += FMC_BOBIX_X5;
                                    msg += "=";
                                    if(bora.get_anz_x() >= i+5)
                                    {
                                        msg += bora.get_raster_x_qstring();
                                    }else
                                    {
                                        msg += "(NULL)";
                                    }
                                    msg += "\n";
                                    //------------------------------
                                    msg += FMC_BOBIX_X6;
                                    msg += "=";
                                    if(bora.get_anz_x() >= i+6)
                                    {
                                        msg += bora.get_raster_x_qstring();
                                    }else
                                    {
                                        msg += "(NULL)";
                                    }
                                    msg += "\n";
                                    //------------------------------
                                    msg += FMC_BOBIX_Y1;
                                    msg += "=";
                                    msg += bora.get_y_qstring();
                                    msg += "\n";
                                    //------------------------------
                                    msg += FMC_BOBIX_Y2;
                                    msg += "=";
                                    msg += "-1";
                                    msg += "\n";
                                    //------------------------------
                                    msg += "ZSM";           //Zustellmaß
                                    msg += "=";
                                    msg += bora.get_zustellmass_qstring();
                                    msg += "\n";
                                    //------------------------------
                                    msg += "\n";
                                }
                            }
                        }else if(bora.get_anz_x() == 1)
                        {
                            //Bohrbild in Y:
                            //max 6 Bohrungen pro Dialog!
                            for(uint i=0 ; i<bora.get_anz_y() ; i=i+6)
                            {
                                msg += FMC_BOBIY;
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIX_AFB;
                                msg += "=";
                                msg += bora.get_afb();
                                msg += "\n";
                                //------------------------------
                                msg += "BEZB";
                                msg += "=";
                                msg += "Bohren in Y  DM";
                                msg += bora.get_dm_qstring();
                                msg += " T";
                                msg += double_to_qstring(tiefe);
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIX_DM;
                                msg += "=";
                                msg += bora.get_dm_qstring();
                                msg += "\n";
                                //------------------------------
                                msg += "F";                     //Vorschub
                                msg += "=";
                                msg += "AUTO";
                                msg += "\n";
                                //------------------------------
                                msg += "FAN";                   //Anfahrvorschub
                                msg += "=";
                                msg += "AUTO";
                                msg += "\n";
                                //------------------------------
                                msg += "GRP";                   //Bohrgruppe
                                msg += "=";
                                msg += bohrgruppe;
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIY_KM;            //Kettenmaß
                                msg += "=";
                                msg += "1";
                                msg += "\n";
                                //------------------------------
                                msg += "LGEAB";                 //Restbohrmaß
                                msg += "=";
                                msg += "4";
                                msg += "\n";
                                //------------------------------
                                msg += "LGEAN";                 //Anbohrtiefe
                                msg += "=";
                                msg += "4";
                                msg += "\n";
                                //------------------------------
                                msg += "MRICHT";                //Messen Seite
                                msg += "=";
                                msg += "0";
                                msg += "\n";
                                //------------------------------
                                msg += "N";                     //Drehzahl
                                msg += "=";
                                msg += "AUTO";
                                msg += "\n";
                                //------------------------------
                                msg += "TASTEIN";               //Taste Satz ein
                                msg += "=";
                                msg += "-1";
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIY_TI;            //Tiefe
                                msg += "=";
                                msg += double_to_qstring(tiefe);
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIY_Y1;
                                msg += "=";
                                msg += double_to_qstring(  bora.get_y() + (i*bora.get_raster_y())  );
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIY_Y2;
                                msg += "=";
                                if(bora.get_anz_y() >= i+2)
                                {
                                    msg += bora.get_raster_y_qstring();
                                }else
                                {
                                    msg += "(NULL)";
                                }
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIY_Y3;
                                msg += "=";
                                if(bora.get_anz_y() >= i+3)
                                {
                                    msg += bora.get_raster_y_qstring();
                                }else
                                {
                                    msg += "(NULL)";
                                }
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIY_Y4;
                                msg += "=";
                                if(bora.get_anz_y() >= i+4)
                                {
                                    msg += bora.get_raster_y_qstring();
                                }else
                                {
                                    msg += "(NULL)";
                                }
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIY_Y5;
                                msg += "=";
                                if(bora.get_anz_y() >= i+5)
                                {
                                    msg += bora.get_raster_y_qstring();
                                }else
                                {
                                    msg += "(NULL)";
                                }
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIY_Y6;
                                msg += "=";
                                if(bora.get_anz_y() >= i+6)
                                {
                                    msg += bora.get_raster_y_qstring();
                                }else
                                {
                                    msg += "(NULL)";
                                }
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIY_X1;
                                msg += "=";
                                msg += bora.get_x_qstring();
                                msg += "\n";
                                //------------------------------
                                msg += FMC_BOBIY_X2;
                                msg += "=";
                                msg += "-1";
                                msg += "\n";
                                //------------------------------
                                msg += "ZSM";           //Zustellmaß
                                msg += "=";
                                msg += bora.get_zustellmass_qstring();
                                msg += "\n";
                                //------------------------------
                                msg += "\n";
                            }
                        }else
                        {
                            //Bislang noch keine Lochrasttererkennung in X und Y gleichzeitig vorhanden
                            //desshalb Ausgabe an dieser Stellen nicht nötig
                        }
                    }
                }else
                {
                    //Sollte nicht vorkommen können, da bohrraster anhand des vorhandenen Werkzeuges ermittelt werden
                }
            }else if(zeile.zeile(1) == BEARBART_NUT)
            {
                nut nu(zeile.get_text());
                QString bezug = nu.get_bezug();
                if(bezug == WST_BEZUG_UNSEI)
                {
                    bezug = WST_BEZUG_OBSEI;
                    nu.set_bezug(WST_BEZUG_OBSEI);
                    nu.set_ys(  tmp_b - nu.get_ys()  );
                    nu.set_ye(  tmp_b - nu.get_ye()  );

                    QString tnummer = wkzmag.get_wkznummer(WKZ_TYP_SAEGE, 0, nu.get_tiefe(), dicke, bezug);
                    if(!tnummer.isEmpty())
                    {
                        double nutblattbreite = wkzmag.get_saegeblattbreite(tnummer).toDouble();
                        if(nu.get_breite() < nutblattbreite)
                        {
                            //Warnung ausgeben und Nut unterdrücken:
                            QString msg = "";
                            msg += "Achtung bei fmc-Export!\n";
                            msg += "Teilname: ";
                            msg += name;
                            msg += "\n";
                            msg += "Saegeblatt zu breit fuer ";
                            msg += get_bearb_menschlich_lesbar(zeile);
                            msg += "\n";
                            msg += "Bitte FMC-Programm pruefen und schmaleres Nutblatt zuweisen.";

                            QMessageBox mb;
                            mb.setText(msg);
                            mb.exec();
                        }

                        //Bezugskante der Nut finden:
                        QString bezugskante = "0"; //Maß gibt Mittellinie der nut an
                        QString posys = nu.get_ys_qstring();
                        QString posye = nu.get_ye_qstring();
                        if(posys == posye)
                        {
                            if(nu.get_ys() < (tmp_b-nu.get_ys()))
                            {
                                posys = double_to_qstring(  nu.get_ys() - nu.get_breite()/2  );
                                posye = "SY";
                                bezugskante = "2"; //Maß gibt linke Flanke der nut an
                            }else
                            {
                                if(nu.get_breite() == 8.5 && nu.get_tiefe() == 6.5)
                                {
                                    posys = "B-";
                                    posys += double_to_qstring(  (tmp_b - nu.get_ys()) + nu.get_breite()/2  );
                                    posye = "SY";
                                    bezugskante = "2"; //Maß gibt linke Flanke der nut an
                                }else
                                {
                                    posys = "B-";
                                    posys += double_to_qstring(  (tmp_b - nu.get_ys()) - nu.get_breite()/2  );
                                    posye = "SY";
                                    bezugskante = "1"; //Maß gibt rechte Flanke der nut an
                                }
                            }
                        }

                        msg += FMC_NUT;
                        msg += "\n";
                        msg += "WKZID=";                //WKZ-Nummer
                        msg += tnummer;
                        msg += "\n";
                        msg += "SWKZID=";               //Spiegel-WKZ-Nummer
                        msg += tnummer;
                        msg += "\n";
                        msg += "WERKZEUGNAME=";         //WKZ-Nummer
                        msg += tnummer;
                        msg += "\n";
                        msg += "WKZAKTUELL=1";
                        msg += "\n";
                        msg += "SPX=";
                        //Nuten auf unserer BIMA310 müssen immer von L zu 0 verlaufen
                        //Da Agregat versetzt wenn es gedreht wird
                        if(nu.get_ys() == nu.get_ye())
                        {
                            if(nu.get_xs() > nu.get_xe())
                            {
                                msg += nu.get_xs_qstring();
                            }else
                            {
                                msg += nu.get_xe_qstring();
                            }
                        }else
                        {
                            msg += nu.get_xs_qstring();
                        }
                        msg += "\n";
                        msg += "SPY=";
                        msg += posys;
                        msg += "\n";
                        msg += "EPX=";
                        if(nu.get_ys() == nu.get_ye())
                        {
                            if(nu.get_xs() < nu.get_xe())
                            {
                                msg += nu.get_xs_qstring();
                            }else
                            {
                                msg += nu.get_xe_qstring();
                            }
                        }else
                        {
                             msg += nu.get_xe_qstring();
                        }
                        msg += "\n";
                        msg += "EPY=";
                        msg += posye;
                        msg += "\n";
                        msg += "TI=";
                        msg += nu.get_tiefe_qstring();
                        msg += "\n";
                        msg += "NB=";
                        msg += nu.get_breite_qstring();
                        msg += "\n";
                        msg += "TYPA=1\n";              //Auslauf
                        msg += "TRKOR=";                //Korrektur/Bezugskante
                        msg += bezugskante;
                        msg += "\n";
                        msg += "GEGENL=0\n";            //Genenlauf
                        msg += "TWKL=0\n";              //Neigungswinkel
                        msg += "TYPN=1\n";              //Neigungstyp
                        msg += "ABSTN=10\n";            //Abstand auf Neigung
                        msg += "Z=D/2\n";               //Pos in Z

                        //Eintauchvorschub gem. Voreinstellung IMAWOP
                        //Vorschub gem. Voreinstellung IMAWOP
                        //Drehzahl gem. Voreinstellung IMAWOP

                        msg += "BEZB=";
                        msg += "Nut B";
                        msg += nu.get_breite_qstring();
                        msg += " T";
                        msg += nu.get_tiefe_qstring();
                        msg += "\n";
                        msg += FMC_BOHR_DM_AFB;
                        msg += "=";
                        msg += nu.get_afb();
                        msg += "\n";
                        msg += "\n";
                    }else
                    {
                        //Mit Fehlermeldung abbrechen:
                        QString msg = fehler_kein_WKZ("fmc", zeile);
                        QMessageBox mb;
                        mb.setText(msg);
                        mb.exec();
                        return msg;
                    }
                }                
            }else if(zeile.zeile(1) == BEARBART_RTA)
            {
                rechtecktasche rt(zeile.get_text());
                QString tnummer = wkzmag.get_wkznummer_von_alias(rt.get_wkznum());//Ist direkt ei WKZ definiert?
                if(tnummer.isEmpty())
                {
                    QString bezug = rt.get_bezug();
                    double minmass = 0;
                    if(rt.get_laenge() < rt.get_breite())
                    {
                        minmass = rt.get_laenge();
                    }else
                    {
                        minmass = get_breite();
                    }
                    tnummer = wkzmag.get_wkznummer(WKZ_TYP_FRAESER, minmass, rt.get_tiefe(), dicke, bezug);
                }
                //Beareitung auf die Oberseite drehen:
                rt.set_y(  tmp_b - rt.get_y()  );
                rt.set_drewi(  180 - rt.get_drewi()  );

                if(!tnummer.isEmpty())
                {
                    double zustellmas = rt.get_zustellmass();
                    if(zustellmas <= 0)
                    {
                        zustellmas = wkzmag.get_zustellmass(tnummer).toDouble();
                    }

                    double tiefe = 0;
                    QString tiefe_qstring;
                    if(rt.get_tiefe() > get_dicke())
                    {
                        tiefe = get_dicke() - rt.get_tiefe();
                        tiefe_qstring = double_to_qstring(tiefe);
                    }else if(get_dicke()-rt.get_tiefe() <= 2)
                    {
                        tiefe_qstring  = "D-";
                        tiefe_qstring += double_to_qstring(get_dicke()-rt.get_tiefe());
                    }else
                    {
                        tiefe = rt.get_tiefe();
                        tiefe_qstring = double_to_qstring(tiefe);
                    }

                    double radius = rt.get_rad();

                    if(rt.get_bezug() == WST_BEZUG_UNSEI)
                    {
                        msg += FMC_RTA;
                        msg += "\n";
                        msg += "WKZID=";            //Werkzeugnummer
                        msg += tnummer;
                        msg += "\n";
                        msg += "MPX=";
                        msg += rt.get_x_qstring();
                        msg += "\n";
                        msg += "MPY=";
                        msg += rt.get_y_qstring();
                        msg += "\n";
                        msg += "LGET1=";
                        msg += rt.get_laenge_qstring();
                        msg += "\n";
                        msg += "LGET2=";
                        msg += rt.get_breite_qstring();
                        msg += "\n";
                        msg += "TI=";                   //Tiefe
                        msg += tiefe_qstring;
                        msg += "\n";
                        msg += "R=";
                        msg += double_to_qstring(radius);
                        msg += "\n";
                        msg += "LGEZU=";                //Zustellmaß
                        msg += double_to_qstring(zustellmas);
                        msg += "\n";
                        msg += "GEGENL=";               //Gegenslauf
                        msg += "1";
                        msg += "\n";
                        msg += "WKL=";
                        msg += rt.get_drewi_qstring();
                        msg += "\n";
                        msg += "RAEUMEN=";              //Ausräumen
                        msg += rt.get_ausraeumen_qstring();
                        msg += "\n";
                        msg += "WKZAKTUELL=1\n";

                        //Eintauchvorschub gem. Voreinstellung IMAWOP
                        //Vorschub gem. Voreinstellung IMAWOP
                        //Drehzahl gem. Voreinstellung IMAWOP

                        msg += "BEZB=";
                        msg += "Rechtecktasche L";
                        msg += rt.get_laenge_qstring();
                        msg += " B";
                        msg += rt.get_breite_qstring();
                        msg += "\n";
                        msg += "AFB=";
                        msg += rt.get_afb();
                        msg += "\n";
                        msg += "\n";
                    }

                }else
                {
                    //Mit Fehlermeldung abbrechen:
                    QString msg = fehler_kein_WKZ("fmc", zeile);
                    QMessageBox mb;
                    mb.setText(msg);
                    mb.exec();
                    return msg;
                }
            }else if(zeile.zeile(1) == BEARBART_FRAESERAUFRUF)
            {
                fraueseraufruf fa(zeile.get_text());
                QString tnummer = wkzmag.get_wkznummer_von_alias(fa.get_wkznum());
                if(!tnummer.isEmpty())
                {
                    //Beareitung auf die Oberseite drehen:
                    fa.set_y(  tmp_b - fa.get_y()  );

                    double gesamttiefe = fa.get_tiefe();
                    double zustellmass = wkzmag.get_zustellmass(tnummer).toDouble();
                    double zustelltiefe;
                    if(zust_fkon == "wkz")
                    {
                        if(zustellmass < gesamttiefe)
                        {
                            zustelltiefe = zustellmass;
                        }else
                        {
                            zustelltiefe = gesamttiefe;
                        }
                    }else // == "orgi"
                    {
                        zustelltiefe = gesamttiefe;
                    }

                    QString radkor = fa.get_radkor();
                    if(radkor == FRKOR_L)
                    {
                        radkor = "1";
                    }else if(radkor == FRKOR_M)
                    {
                        radkor = "0";
                    }else if(radkor == FRKOR_R)
                    {
                        radkor = "2";
                    }

                    if(fa.get_bezug() == WST_BEZUG_UNSEI)
                    {
                        msg += kommentar_fmc("--------------------");

                        double backup_i = i;
                        while(1)//abbruch durch breake
                        {
                            i = backup_i;
                            double pos_z = get_dicke()-zustelltiefe;
                            //--------------------------------------------
                            msg += FMC_FKON;
                            msg += "\n";
                            msg += "WKZID=";            //Werkzeugnummer
                            msg += tnummer;
                            msg += "\n";
                            msg += FMC_FKON_X;
                            msg += "=";
                            msg += fa.get_x_qstring();
                            msg += "\n";
                            msg += FMC_FKON_Y;
                            msg += "=";
                            msg += fa.get_y_qstring();
                            msg += "\n";
                            msg += FMC_FKON_Z;
                            msg += "=";
                            msg += double_to_qstring(pos_z);
                            msg += "\n";
                            msg += "EBG=0\n";       //Eckenrunden global
                            msg += "KD=0\n";        //Kantendicke
                            msg += FMC_FKON_KOR;    //Fräsbaohnkorrektur
                            msg += "=";
                            msg += radkor;
                            msg += "\n";

                            //Prüfen ob Eintauchpunkt des Fräsers auf oder neben dem WST liegt:
                            punkt3d pfa;//Punkt Fräseraufruf
                            pfa.set_x(fa.get_x());
                            pfa.set_y(fa.get_y());
                            text_zeilenweise folzei;//Folgezeile
                            folzei.set_trennzeichen(TRENNZ_BEARB_PARAM);
                            folzei.set_text(bearb.zeile(i+1));
                            punkt3d pein;//Eintauchpunkt
                            int anweg = 50;

                            if(folzei.zeile(1) == BEARBART_FRAESERGERADE)
                            {
                                fraesergerade fg(folzei.get_text());
                                //Beareitung auf die Oberseite drehen:
                                fg.set_ys(  tmp_b - fg.get_ys()  );
                                fg.set_ye(  tmp_b - fg.get_ye()  );
                                //-------
                                strecke s;
                                s.set_start(pfa);
                                punkt3d ep = fg.get_ep();
                                ep.set_z(0);
                                s.set_ende(ep);
                                strecke_bezugspunkt sb;
                                sb = strecke_bezugspunkt_ende;
                                s.set_laenge_2d(s.laenge2dim()+anweg, sb);
                                pein = s.startp();
                            }else if(folzei.zeile(1) == BEARBART_FRAESERBOGEN)
                            {
                                fraeserbogen fb(folzei.get_text());
                                //Beareitung auf die Oberseite drehen:
                                fb.set_ys(  tmp_b - fb.get_ys()  );
                                fb.set_ye(  tmp_b - fb.get_ye()  );
                                //---------
                                bogen b;
                                b.set_startpunkt(pfa);
                                b.set_endpunkt(fb.get_ep());
                                strecke s;
                                s.set_start(pfa);
                                punkt3d pmibo;
                                pmibo.set_x(b.mitte().x());
                                pmibo.set_y(b.mitte().y());
                                s.set_ende(pmibo);
                                s.drenen_um_startpunkt_2d(90, b.im_uzs());
                                strecke_bezugspunkt sb;
                                sb = strecke_bezugspunkt_start;
                                s.set_laenge_2d(anweg, sb);
                                pein = s.endp();
                            }

                            bool aufwst = punkt_auf_wst(pein.x(), pein.y(), get_laenge(), get_breite(), 1);
                            if(aufwst == true)
                            {
                                msg += "TYPAN=1\n";     //Anfahrtyp
                                msg += "TYPAB=1\n";     //Abfahrtyp
                                msg += "TYPEIN=1\n";    //Eintauchtp
                                if(pos_z > 0)
                                {
                                    //Anfahranweisung für nicht durchgefräste Innen-Bahnen:
                                    msg += "LGEAN=2*WKZR\n";    //Anfahrwert
                                    msg += "LGEAB=2*WKZR\n";    //Abfahrwert
                                }else
                                {
                                    //Anfahranweisung für durchgefräste Innen-Bahnen:
                                    msg += "LGEAN=50\n";    //Anfahrwert
                                    msg += "LGEAB=50\n";    //Abfahrwert
                                }
                            }else
                            {
                                //Anfahranweisung für außen-Bahnen (z.B. Formatierungen):
                                msg += "TYPAN=0\n";     //Anfahrtyp
                                msg += "TYPAB=0\n";     //Abfahrtyp
                                msg += "TYPEIN=-1\n";   //Eintauchtp
                                msg += "LGEAN=2*WKZR+";    //Anfahrwert
                                msg += double_to_qstring(anweg);
                                msg += "\n";
                                msg += "LGEAB=2*WKZR+";    //Abfahrwert
                                msg += double_to_qstring(anweg);
                                msg += "\n";
                            }
                            msg += "FAN=AUTO\n";    //Anfahrvorschub
                            msg += "F=AUTO\n";      //Vorschub
                            //msg += "N=AUTO\n";      //Drehzahl
                            msg += "EVS=0.05\n";    //Ecken-Verschleifen
                            msg += "AFB=";
                            msg += fa.get_afb();
                            msg += "\n";
                            msg += "WKZAKTUELL=1\n";
                            msg += "\n";
                            //--------------------------------------------
                            //Fräsbahnen:
                            while(i+1<=bearb.zeilenanzahl())
                            {
                                zeile.set_text(bearb.zeile(i+1));

                                if(zeile.zeile(1) == BEARBART_FRAESERGERADE)
                                {
                                    i++;
                                    zeile.set_text(bearb.zeile(i));
                                    //Gerade fräsen:
                                    fraesergerade fg(zeile.get_text());
                                    QString tiefe_fg = 0;
                                    if(fg.get_ze() == fa.get_tiefe())
                                    {
                                        tiefe_fg = "Z"; //Tiefe beibehalten
                                                        //Führt zu falschen Ergebissen, wenn manuell geschriebene
                                                        //fmc-Programme eingelesen wurden, bei denen
                                                        //die FKONs zwischen dem Fräseraufruf und dieser Gerade
                                                        //nicht den selben Z-Wert haben!!!
                                                        //Dieser Fall wird nicht erwartet....
                                    }else
                                    {
                                        tiefe_fg = double_to_qstring(  get_dicke()-fg.get_ze()  );
                                    }

                                    //Beareitung auf die Oberseite drehen:
                                    fg.set_ys(  tmp_b - fg.get_ys()  );
                                    fg.set_ye(  tmp_b - fg.get_ye()  );

                                    msg += FMC_FKONG;
                                    msg += "\n";
                                    msg += FMC_FKONG_XE;
                                    msg += "=";
                                    msg += fg.get_xe_qstring();
                                    msg += "\n";
                                    msg += FMC_FKONG_YE;
                                    msg += "=";
                                    msg += fg.get_ye_qstring();
                                    msg += "\n";
                                    msg += FMC_FKONG_ZE;
                                    msg += "=";
                                    msg += tiefe_fg;
                                    msg += "\n";
                                    msg += "\n";
                                }else if(zeile.zeile(1) == BEARBART_FRAESERBOGEN)
                                {
                                    i++;
                                    zeile.set_text(bearb.zeile(i));
                                    //Bogen fräsen:
                                    fraeserbogen fb(zeile.get_text());
                                    QString tiefe_fb = 0;
                                    if(fb.get_ze() == fa.get_tiefe())
                                    {
                                        tiefe_fb = "Z"; //Tiefe beibehalten
                                                        //Führt zu falschen Ergebissen, wenn manuell geschriebene
                                                        //fmc-Programme eingelesen wurden, bei denen
                                                        //die FKONs zwischen dem Fräseraufruf und dieser Gerade
                                                        //nicht den selben Z-Wert haben!!!
                                                        //Dieser Fall wird nicht erwartet....
                                    }else
                                    {
                                        tiefe_fb = double_to_qstring(  get_dicke()-fb.get_ze()  );
                                    }
                                    QString dlg_name;
                                    if(fb.get_uzs() == true)
                                    {
                                        dlg_name = FMC_FKONBOGUZS;
                                    }else
                                    {
                                        dlg_name = FMC_FKONBOGGUZS;
                                    }

                                    //Beareitung auf die Oberseite drehen:
                                    fb.set_ys(  tmp_b - fb.get_ys()  );
                                    fb.set_ye(  tmp_b - fb.get_ye()  );

                                    msg += dlg_name;
                                    msg += "\n";
                                    msg += FMC_FKONBOG_RAD;
                                    msg += "=";
                                    msg += fb.get_rad_qstring();
                                    msg += "\n";
                                    msg += FMC_FKONBOG_XE;
                                    msg += "=";
                                    msg += fb.get_xe_qstring();
                                    msg += "\n";
                                    msg += FMC_FKONBOG_YE;
                                    msg += "=";
                                    msg += fb.get_ye_qstring();
                                    msg += "\n";
                                    msg += FMC_FKONBOG_ZE;
                                    msg += "=";
                                    msg += tiefe_fb;
                                    msg += "\n";
                                    msg += "\n";
                                }else
                                {
                                    break;
                                }
                            }
                            //--------------------------------------------
                            //Abfahren Fräser:
                            msg += "[KO'AB_N2]";
                            msg += "\n";
                            msg += "AFB=1";
                            msg += "\n";
                            msg += "AGGD=AGGDREHBAR";
                            msg += "\n";
                            msg += "AGGFWKL=AGGFWKL";
                            msg += "\n";
                            msg += "AGGO=AGGOFFSET";
                            msg += "\n";
                            msg += "\n";
                            //--------------------------------------------
                            if(zustelltiefe == gesamttiefe)
                            {
                                break; //letzter Schleifendurchlauf
                            }
                            if(zustelltiefe != gesamttiefe)
                            {
                                msg += kommentar_fmc("---");
                            }
                            if(zustelltiefe+zustellmass  <  gesamttiefe)
                            {
                                zustelltiefe = zustelltiefe + zustellmass;
                            }else
                            {
                                zustelltiefe = gesamttiefe;
                            }
                        }
                        msg += kommentar_fmc("--------------------");
                    }

                }else
                {
                    //Mit Fehlermeldung abbrechen:
                    QString msg = fehler_kein_WKZ("fmc", zeile);
                    QMessageBox mb;
                    mb.setText(msg);
                    mb.exec();
                    return msg;
                }
            }
        }
    }

    //---------------------------------------Programmende:
    msg += FMC_ENDE;
    msg += "\n";
    msg += "AFB=1\n";
    msg += "PP=2\n";                //Parkposition
    msg += "BEZB=Programm-Ende";

    return msg;
}
QString werkstueck::get_eigen_dateitext(text_zeilenweise bearb, double tmp_l, double tmp_b, \
                                        QString ausgabeformat, text_zeilenweise wkzmagazin)
{
    if(ausgabeformat == FMC)
    {
        bearb = rasterbohrungen_finden_fmc(bearb, wkzmagazin, tmp_l, tmp_b);
    }else if(ausgabeformat == GANX)
    {
        bearb = rasterbohrungen_finden_ganx(bearb, wkzmagazin, tmp_l, tmp_b);
    }
    QString msg = "";
    bearb_sortieren();

    //Programmkopf:
    msg += get_name();
    msg += "\n";
    msg += "L: ";
    msg += double_to_qstring(tmp_l);
    msg += "\n";
    msg += "B: ";
    msg += double_to_qstring(tmp_b);
    msg += "\n";
    msg += "D: ";
    msg += get_dicke_qstring();
    msg += "\n";
    msg += "---------------";
    msg += "\n";

    msg += bearb.get_text();

    return msg;
}

QString werkstueck::kommentar_fmc(QString kom)
{
    QString text;
    text = FMC_KOMMENTAR;
    text += "\n";
    text += FMC_KOMMENTAR_TEXT;
    text += kom;
    text += "\n";
    text += "\n";
    return text;
}

QString werkstueck::fmc_kommentar_gute_seite(text_zeilenweise bearb)
{
    QString retmsg;
    if(name.contains("Seite"))
    {
        bool hat_5er_durchgangsbohrungen = false;
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        for(uint i=1; i<=bearbeitungen.zeilenanzahl() ;i++)
        {
            zeile.set_text(bearb.zeile(i));
            if(zeile.zeile(1) == BEARBART_BOHR)
            {
                bohrung bo(zeile.get_text());
                if(bo.get_dm() == 5)
                {
                    if(bo.get_tiefe() > dicke  ||  bo.get_tiefe() < 0)
                    {
                        hat_5er_durchgangsbohrungen = true;
                    }
                }
            }
        }
        if(hat_5er_durchgangsbohrungen == true)
        {
            retmsg = "gut oben";
        }else
        {
            retmsg = "gut unten";
        }
    }else if(name.contains("MS"))
    {
        retmsg = "gut oben";
    }else if(name.contains("OB"))
    {
        retmsg = "gut oben";
    }else if(name.contains("UB"))
    {
        int anz_obsei = 0;
        int anz_unsei = 0;
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        for(uint i=1; i<=bearbeitungen.zeilenanzahl() ;i++)
        {
            zeile.set_text(bearb.zeile(i));
            if(zeile.zeile(1) == BEARBART_BOHR)
            {
                bohrung bo(zeile.get_text());
                if(bo.get_dm() == 15)
                {
                    if(bo.get_bezug() == WST_BEZUG_OBSEI)
                    {
                        anz_obsei++;
                    }else if(bo.get_bezug() == WST_BEZUG_UNSEI)
                    {
                        anz_unsei++;
                    }
                }
            }
        }
        if(anz_obsei > anz_unsei)
        {
            retmsg = "gut unten";
        }else
        {
            retmsg = "gut oben";
        }
    }else if(name.contains("KB"))
    {
        retmsg = "gut unten";
    }else if(name.contains("EB"))
    {
        retmsg = "gut unten";
    }else if(name.contains("RW"))
    {
        retmsg = "gut unten";
    }else if(name.contains("Tuer"))
    {
        retmsg = "gut unten";
    }else if(name.contains("Front") || name.contains("front"))
    {
        retmsg = "gut unten";
    }else if(name.contains("Blende") || name.contains("blende"))
    {
        retmsg = "gut unten";
    }else if(name.contains("Doppel") || name.contains("doppel"))
    {
        retmsg = "gut unten";
    }else if(name.contains("Paneel") || name.contains("paneel"))
    {
        retmsg = "gut unten";
    }else if(name.contains("SF"))
    {
        retmsg = "gut unten";
    }else if(name.contains("SB"))
    {
        retmsg = "gut unten";
    }else
    {
        retmsg = "(NULL)";
    }

    return retmsg;
}

bool werkstueck::punkt_auf_wst(double x, double y, double l, double b, double tolleranz)
{
    bool returnwert = true;
    if(x <= 0+tolleranz ||\
       x >= l-tolleranz ||\
       y <= 0+tolleranz ||\
       y >= b-tolleranz)
    {
        returnwert = false;
    }
    return returnwert;
}

void werkstueck::fraesergeraden_zusammenfassen()
{
    for(uint i=1 ; i<bearbeitungen.zeilenanzahl() ; i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(bearbeitungen.zeile(i));
        text_zeilenweise folgezeile;
        folgezeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        folgezeile.set_text(bearbeitungen.zeile(i+1));

        if(zeile.zeile(1) == BEARBART_FRAESERGERADE &&\
           folgezeile.zeile(1) == BEARBART_FRAESERGERADE)
        {
            strecke s1, s2;
            fraesergerade fg1(zeile.get_text());
            fraesergerade fg2(folgezeile.get_text());
            s1=fg1.get_strecke();
            s2=fg2.get_strecke();
            strecke_bezugspunkt sb = strecke_bezugspunkt_start;
            s1.set_laenge_2d(s1.laenge2dim()+s2.laenge2dim(), sb );
            fg1.set_endpunkt(s1.endp());
            //Vergleich der Strings statt der double da sonst ungleiche Nachkommastellen alles zu genau machen:
            if(fg1.get_xe_qstring() == fg2.get_xe_qstring() &&\
               fg1.get_ye_qstring() == fg2.get_ye_qstring() &&\
               fg1.get_ze_qstring() == fg2.get_ze_qstring()    )
            {
                bearbeitungen.zeile_ersaetzen(i, fg1.get_text());
                bearbeitungen.zeile_loeschen(i+1);
                i--;
            }
        }

    }
}

text_zeilenweise werkstueck::rasterbohrungen_finden_ganx(text_zeilenweise bearb, text_zeilenweise wkzmagazin,\
                                                         double tmp_l, double tmp_b)
{
    bohrraster bora;

    text_zeilenweise wkzbodm; //Speichert die verschiedenen vorhandenen Bohrdurchmesser
    werkzeugmagazin magazin(wkzmagazin);
    int min_rasterbohrungen_anz = 2;

    text_zeilenweise boti;
    for(uint i=1; i<= bearb.zeilenanzahl() ;i++)
    {
        text_zeilenweise param;
        param.set_trennzeichen(TRENNZ_BEARB_PARAM);
        param.set_text(bearb.zeile(i));
        if(param.zeile(1) == BEARBART_BOHR)
        {
            bohrung b(param.get_text());
            QString tiefe_neu = b.get_tiefe_qstring();
            bool schon_da = false;
            for(uint i=1; i<=boti.zeilenanzahl();i++)
            {
                if(tiefe_neu == boti.zeile(i))
                {
                    schon_da = true;
                }
            }
            if(schon_da == false)
            {
                boti.zeile_anhaengen(tiefe_neu);
            }
        }
    }

    //Alle vertikalen Lochraster finden die zu Bohrern im Werkzeugmagazin passen:
    wkzbodm = magazin.get_alle_bodm(WKZ_PARAMETER_LAGE_VERT);

    for(uint i=1; i<=wkzbodm.zeilenanzahl() ;i++)
    {
        double dm = wkzbodm.zeile(i).toDouble();

        for(uint i=1; i<=boti.zeilenanzahl() ; i++)
        {
            double tiefe = boti.zeile(i).toDouble();
            bool raster_gefunden;

            //-------------------------------------------------------------------------------
            //Oberseite  0_bis_L:
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_OBSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_L,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        get_dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        32);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_OBSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_L,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        get_dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        64);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_OBSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_L,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        get_dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        96);
            }
            //-------------------------------------------------------------------------------
            //Oberseite  0_bis_B:
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_OBSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_B,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        get_dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        32);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_OBSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_B,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        get_dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        64);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_OBSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_B,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        get_dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        96);
            }
            //-------------------------------------------------------------------------------
            //Unterseite  0_bis_L:
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_UNSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_L,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        get_dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        32);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_UNSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_L,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        get_dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        64);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_UNSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_L,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        get_dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        96);
            }
            //-------------------------------------------------------------------------------
            //Unterseite  0_bis_B:
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_UNSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_B,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        get_dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        32);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_UNSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_B,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        get_dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        64);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_UNSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_B,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        get_dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        96);
            }
        }


    }

    return bearb;
}

text_zeilenweise werkstueck::rasterbohrungen_finden_fmc(text_zeilenweise bearb, text_zeilenweise wkzmagazin,\
                                                        double tmp_l, double tmp_b)
{
    bohrraster bora;

    text_zeilenweise wkzbodm; //Speichert die verschiedenen vorhandenen Bohrdurchmesser
    werkzeugmagazin magazin(wkzmagazin);
    int min_rasterbohrungen_anz = 3;

    text_zeilenweise boti;
    for(uint i=1; i<= bearb.zeilenanzahl() ;i++)
    {
        text_zeilenweise param;
        param.set_trennzeichen(TRENNZ_BEARB_PARAM);
        param.set_text(bearb.zeile(i));
        if(param.zeile(1) == BEARBART_BOHR)
        {
            bohrung b(param.get_text());
            QString tiefe_neu = b.get_tiefe_qstring();
            bool schon_da = false;
            for(uint i=1; i<=boti.zeilenanzahl();i++)
            {
                if(tiefe_neu == boti.zeile(i))
                {
                    schon_da = true;
                }
            }
            if(schon_da == false)
            {
                boti.zeile_anhaengen(tiefe_neu);
            }
        }
    }

    //Alle vertikalen Lochraster finden die zu Bohrern im Werkzeugmagazin passen:
    wkzbodm = magazin.get_alle_bodm(WKZ_PARAMETER_LAGE_VERT);

    for(uint i=1; i<=wkzbodm.zeilenanzahl() ;i++)
    {
        double dm = wkzbodm.zeile(i).toDouble();

        for(uint i=1; i<=boti.zeilenanzahl() ; i++)
        {
            double tiefe = boti.zeile(i).toDouble();
            bool raster_gefunden;

            //-------------------------------------------------------------------------------
            //Oberseite  0_bis_L:
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_OBSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_L,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        get_dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        32);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_OBSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_L,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        get_dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        64);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_OBSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_L,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        get_dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        96);
            }
            //-------------------------------------------------------------------------------
            //Oberseite  0_bis_B:
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_OBSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_B,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        get_dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        32);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_OBSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_B,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        get_dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        64);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_OBSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_B,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        get_dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        96);
            }
            //-------------------------------------------------------------------------------
            //Unterseite  0_bis_L:
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_UNSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_L,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        get_dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        32);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_UNSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_L,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        get_dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        64);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_UNSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_L,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        get_dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        96);
            }
            //-------------------------------------------------------------------------------
            //Unterseite  0_bis_B:
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_UNSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_B,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        get_dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        32);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_UNSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_B,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        get_dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        64);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_UNSEI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_B,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        get_dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        96);
            }
        }
    }

    //HBEs im Raser finden die zu Bohrern im Werkzeugmagazin passen:
    wkzbodm = magazin.get_alle_bodm(WKZ_PARAMETER_LAGE_HORI);

    for(uint i=1; i<=wkzbodm.zeilenanzahl() ;i++)
    {
        double dm = wkzbodm.zeile(i).toDouble();

        for(uint i=1; i<=boti.zeilenanzahl() ; i++)
        {
            double tiefe = boti.zeile(i).toDouble();
            bool raster_gefunden;

            //-------------------------------------------------------------------------------
            //vorne 0_bis_L:
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_VO, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_L,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        get_dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        32);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_VO, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_L,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        get_dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        64);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_VO, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_L,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        get_dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        96);
            }
            //-------------------------------------------------------------------------------
            //hinten 0_bis_L:
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_HI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_L,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        get_dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        32);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_HI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_L,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        get_dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        64);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_HI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_L,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        get_dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        96);
            }
            //-------------------------------------------------------------------------------
            //links 0_bis_B:
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_LI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_B,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        get_dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        32);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_LI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_B,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        get_dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        64);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_LI, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_B,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        get_dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        96);
            }
            //-------------------------------------------------------------------------------
            //rechts 0_bis_B:
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_RE, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_B,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        get_dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        32);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_RE, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_B,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        get_dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        64);
            }
            raster_gefunden = true;
            while(raster_gefunden == true)
            {
                raster_gefunden = bora.finde_bohrraster(&bearb,\
                                                        WST_BEZUG_RE, \
                                                        dm,\
                                                        tiefe,\
                                                        RASTERRICHTUNG_0_BIS_B,\
                                                        tmp_l,\
                                                        tmp_b,\
                                                        get_dicke(),\
                                                        min_rasterbohrungen_anz,\
                                                        96);
            }
        }
    }

    return bearb;
}

//-------------------------------------------------------------------------Werkzeug:


