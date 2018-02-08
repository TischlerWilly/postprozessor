#include "werkstueck.h"

werkstueck::werkstueck()
{
    laenge  = 0;
    breite  = 0;
    dicke   = 0;
}
werkstueck::werkstueck(QString neuer_name)
{
    name    = neuer_name;
    laenge  = 0;
    breite  = 0;
    dicke   = 0;
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
                }else//Es ist auch kein passender Fräser da, die CNC-Bearbeitung kann nicht erfolgen
                {
                    msg += "  !! Kein Werkzeug fuer Bohrung oder Kreistasche gefunden!\n";
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
            }
        }else if(art == BEARBART_NUT)
        {
            nut nu(zeile.get_text());
            QString bezug = nu.get_bezug();
            QString tnummer = wkzmag.get_wkznummer(WKZ_TYP_SAEGE, 0, nu.get_tiefe(), dicke, bezug);
            if(nu.get_xs() != nu.get_xe())
            {
                msg += "  !! Nutrichutng auf der der Maschine nicht moeglich!\n";
            }else if(nu.get_xs() < 10)
            {
                msg += "  !! Nut zu dicht am Rand/zu dicht an Spannzange!\n";
                msg += "     X-Mass Nutmitte muss mind 10mm sein\n";
                msg += "     X ist ca ";
                msg += nu.get_xe_qstring();
                msg += "mm\n";
            }
            double nutblattbreite = wkzmag.get_saegeblattbreite(tnummer).toDouble();
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
    if(tmp_b < 60)
    {
        msg += "  !! Werkstueck-Breite < 60mm\n";
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
                if(fa.get_tiefe() > wkzmag.get_nutzlaenge(tnummer).toDouble())
                {
                    msg += "  !! Nutzlaenge < Fraestiefe    bei Fraeseraufruf!\n";
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

    if(drehwinkel == "0")
    {
        double tmp_l = laenge;
        double tmp_b = breite;
        text_zeilenweise tmp_bearb = bearbeitungen;
        msg = get_fmc_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b, zust_fkon);
        QString warnungen = warnungen_fmc(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
        info = warnungen;
    }else if(drehwinkel == "90")
    {
        double tmp_l = laenge;
        double tmp_b = breite;
        text_zeilenweise tmp_bearb = bearbeitungen;
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        msg = get_fmc_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b, zust_fkon);
        QString warnungen = warnungen_fmc(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
        info = warnungen;
    }else if(drehwinkel == "180")
    {
        double tmp_l = laenge;
        double tmp_b = breite;
        text_zeilenweise tmp_bearb = bearbeitungen;
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        msg = get_fmc_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b, zust_fkon);
        QString warnungen = warnungen_fmc(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
        info = warnungen;
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
        info = warnungen;
    }else
    {
        double tmp_l = laenge;
        double tmp_b = breite;
        text_zeilenweise tmp_bearb;

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
        //Teile bevorzugen, bei bei denen gilt: L > B:
        if(l_0 > b_0)
        {
            bewertung_0 += 2;
        }
        if(l_90 > b_90)
        {
            bewertung_90 += 2;
        }
        if(l_180 > b_180)
        {
            bewertung_180 += 2;
        }
        if(l_270 > b_270)
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
            double tmp_l = laenge;
            double tmp_b = breite;
            text_zeilenweise tmp_bearb = bearbeitungen;
            msg = get_fmc_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b, zust_fkon);
            QString warnungen = warnungen_fmc(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
            info = warnungen;
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
            info = warnungen;
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
            info = warnungen;
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
            info = warnungen;
        }else
        {
            //wir nehmen 0:
            double tmp_l = laenge;
            double tmp_b = breite;
            text_zeilenweise tmp_bearb = bearbeitungen;
            msg = get_fmc_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b, zust_fkon);
            QString warnungen = warnungen_fmc(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
            info = warnungen;
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
        info = warnungen;
    }else if(drehwinkel == "90")
    {
        double tmp_l = breite;
        double tmp_b = laenge;
        text_zeilenweise tmp_bearb;
        tmp_bearb = bearb_optimieren_ganx(bearbeitungen);
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        msg = get_ganx_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b);
        QString warnungen = warnungen_ganx(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
        info = warnungen;
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
        info = warnungen;
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
        info = warnungen;
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
            info = warnungen;
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
            info = warnungen;
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
            info = warnungen;
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
            info = warnungen;
        }else
        {
            //wir nehmen 0:
            double tmp_l = breite;
            double tmp_b = laenge;
            text_zeilenweise tmp_bearb;
            tmp_bearb = bearb_optimieren_ganx(bearbeitungen);
            msg = get_ganx_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b);
            QString warnungen = warnungen_ganx(tmp_bearb, tmp_l, tmp_b, wkzmagazin);
            info = warnungen;
        }
    }
    return msg;
}
QString werkstueck::get_eigenses_format(QString drehwinkel)
{
    QString msg;
    bearb_sortieren();

    if(drehwinkel == "0")
    {
        double tmp_l = laenge;
        double tmp_b = breite;
        text_zeilenweise tmp_bearb = bearbeitungen;
        msg = get_eigen_dateitext(tmp_bearb, tmp_l, tmp_b);
    }else if(drehwinkel == "90")
    {
        double tmp_l = laenge;
        double tmp_b = breite;
        text_zeilenweise tmp_bearb = bearbeitungen;
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        msg = get_eigen_dateitext(tmp_bearb, tmp_l, tmp_b);
    }else if(drehwinkel == "180")
    {
        double tmp_l = laenge;
        double tmp_b = breite;
        text_zeilenweise tmp_bearb = bearbeitungen;
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        msg = get_eigen_dateitext(tmp_bearb, tmp_l, tmp_b);
    }else if(drehwinkel == "270")
    {
        double tmp_l = laenge;
        double tmp_b = breite;
        text_zeilenweise tmp_bearb = bearbeitungen;
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        msg = get_eigen_dateitext(tmp_bearb, tmp_l, tmp_b);
    }else
    {
        //drehung 0:
        double tmp_l = laenge;
        double tmp_b = breite;
        text_zeilenweise tmp_bearb = bearbeitungen;
        msg = get_eigen_dateitext(tmp_bearb, tmp_l, tmp_b);
    }
    return msg;
}

QString werkstueck::get_ganx_dateitext(text_zeilenweise wkzmagazin, text_zeilenweise bearb, \
                                       double tmp_l, double tmp_b)
{
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
    uint id = 1;
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
                //-------------------------------
                if(bezug == WST_BEZUG_OBSEI)
                {
                    //x = Breite
                    //y = Länge
                    //z = Tiefe

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
                    msg += bo.get_tiefe_qstring();
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
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</OldID>";
                    msg += "\n";
                    //----------------------
                    msg += "    <KleiGeTei>";    //Tiefe???
                    msg += double_to_qstring(z);
                    msg += "</KleiGeTei>";
                    msg += "\n";
                    //----------------------
                    msg += "  </PrgrFileWork>";
                    msg += "\n";

                    id++;

                }else if(bezug == WST_BEZUG_UNSEI)
                {
                    //x = Breite
                    //y = Länge
                    //z = Tiefe

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
                    msg += bo.get_tiefe_qstring();
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
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</OldID>";
                    msg += "\n";
                    //----------------------
                    msg += "    <KleiGeTei>";    //Tiefe???
                    msg += double_to_qstring(z);
                    msg += "</KleiGeTei>";
                    msg += "\n";
                    //----------------------
                    msg += "  </PrgrFileWork>";
                    msg += "\n";

                    id++;

                }else if(bezug == WST_BEZUG_LI)
                {
                    //x = Tiefe
                    //y = Y-Pos
                    //z = Z-Pos
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
                    msg += bo.get_tiefe_qstring();
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
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</OldID>";
                    msg += "\n";
                    //----------------------
                    msg += "    <KleiGeTei>";    //Tiefe???
                    msg += double_to_qstring(x);
                    msg += "</KleiGeTei>";
                    msg += "\n";
                    //----------------------
                    msg += "  </PrgrFileWork>";
                    msg += "\n";

                    id++;

                }else if(bezug == WST_BEZUG_RE)
                {
                    //x = Tiefe
                    //y = Y-Pos
                    //z = Z-Pos
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
                    msg += bo.get_tiefe_qstring();
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
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</OldID>";
                    msg += "\n";
                    //----------------------
                    msg += "    <KleiGeTei>";    //Tiefe???
                    msg += double_to_qstring(x);
                    msg += "</KleiGeTei>";
                    msg += "\n";
                    //----------------------
                    msg += "  </PrgrFileWork>";
                    msg += "\n";

                    id++;

                }else if(bezug == WST_BEZUG_VO)
                {
                    //x = X-Pos
                    //y = Tiefe
                    //z = Z-Pos
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
                    msg += bo.get_tiefe_qstring();
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
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</OldID>";
                    msg += "\n";
                    //----------------------
                    msg += "    <KleiGeTei>";    //Tiefe???
                    msg += double_to_qstring(y);
                    msg += "</KleiGeTei>";
                    msg += "\n";
                    //----------------------
                    msg += "  </PrgrFileWork>";
                    msg += "\n";

                    id++;

                }else if(bezug == WST_BEZUG_HI)
                {
                    //x = X-Pos
                    //y = Tiefe
                    //z = Z-Pos
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
                    msg += bo.get_tiefe_qstring();
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
                    msg += int_to_qstring(id);               //ID-Nummer
                    msg += "</OldID>";
                    msg += "\n";
                    //----------------------
                    msg += "    <KleiGeTei>";    //Tiefe???
                    msg += double_to_qstring(y);
                    msg += "</KleiGeTei>";
                    msg += "\n";
                    //----------------------
                    msg += "  </PrgrFileWork>";
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
                    QString ref = GANX_REF_UNTEN_LINKS;
                    //y < 40 -> TL
                    //Länge - y < 40 ->BL
                    if(laenge_y - y < bezugsmass)
                    {
                        ref = GANX_REF_OBEN_LINKS;
                        y = laenge_y - y;
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
                    msg += int_to_qstring(id);               //ID-Nummer
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

                }else
                {
                    QString msg = fehler_kein_WKZ("ganx", zeile);
                    QMessageBox mb;
                    mb.setText(msg);
                    mb.exec();
                    return msg;
                }
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
            double y = nu.get_ys();
            double z = nu.get_tiefe(); //Tiefe
            double l = 0;
            //Nutlänge berechnen:
            if(nu.get_ys() < nu.get_ye())
            {
                l = nu.get_ye() - nu.get_ys();
            }else
            {
                l = nu.get_ys() - nu.get_ye();
            }
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
                msg += GANX_REF_UNTEN_LINKS;
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
                msg += int_to_qstring(id);               //ID-Nummer
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
                        x = x + versatz*2;
                    }else
                    {
                        x = x + (  (anz_nuten-2)*nutblattbreite  );
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
                    msg += GANX_REF_UNTEN_LINKS;
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
                    msg += int_to_qstring(id);               //ID-Nummer
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
            QString ref = GANX_REF_UNTEN_LINKS;
            //y < 40 -> TL
            //Länge - y < 40 ->BL
            if(laenge_y - y < bezugsmass)
            {
                ref = GANX_REF_OBEN_LINKS;
                y = laenge_y - y;
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
            msg += double_to_qstring(by);    //TAB
            msg += ";";
            msg += double_to_qstring(lx);    //TAL
            msg += ";";
            msg += double_to_qstring(eckenradius); //Eckenradius Tasche
            msg += ";";
            msg += ti;                       //TaTi
            msg += ";";
            //Variante der Rechtecktasche (1 = ausgeräumt):
            if(ausraeumen == true)
            {
                msg += "1";
            }else
            {
                msg += "0";
            }
            msg += ";";
            msg += "GL";                     //Gleichlauf (GL = Gleichlauf / GG = Gegenlauf)
            msg += ";";
            msg += double_to_qstring(wkz_vorschub);
            msg += ";";
            msg += int_to_qstring(zustellungen);
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
            msg += int_to_qstring(id);               //ID-Nummer
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

        }
    }

    //-------------------------Bearbeitungen <PrgrFile>:
    id = 1;
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
            double y = nu.get_ys();
            double z = nu.get_tiefe(); //Tiefe
            double l = 0;
            //Nutlänge berechnen:
            if(nu.get_ys() < nu.get_ye())
            {
                l = nu.get_ye() - nu.get_ys();
            }else
            {
                l = nu.get_ys() - nu.get_ye();
            }
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
                msg += GANX_REF_UNTEN_LINKS;
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
                        x = x + versatz*2;
                    }else
                    {
                        x = x + (  (anz_nuten-2)*nutblattbreite  );
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
                    msg += GANX_REF_UNTEN_LINKS;
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
            msg += double_to_qstring(by);    //TAB
            msg += ";";
            msg += double_to_qstring(lx);    //TAL
            msg += ";";
            msg += double_to_qstring(eckenradius); //Eckenradius Tasche
            msg += ";";
            msg += ti;                       //TaTi
            msg += ";";
            //Variante der Rechtecktasche (1 = ausgeräumt):
            if(ausraeumen == true)
            {
                msg += "1";
            }else
            {
                msg += "0";
            }
            msg += ";";
            msg += "GL";                     //Gleichlauf (GL = Gleichlauf / GG = Gegenlauf)
            msg += ";";
            msg += double_to_qstring(wkz_vorschub);
            msg += ";";
            msg += int_to_qstring(zustellungen);
            msg += "</Mill>";
            msg += "\n";
            //----------------------
            msg += "    <ImageKey>RE</ImageKey>";
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

        }
    }

    //-------------------------Programmende:
    msg += "</Programm>";


    return msg;
}
QString werkstueck::get_fmc_dateitext(text_zeilenweise wkzmagazin, text_zeilenweise bearb, \
                                      double tmp_l, double tmp_b, QString zust_fkon)
{
    QString msg;   
    text_zeilenweise zeile;
    zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
     werkzeugmagazin wkzmag(wkzmagazin);
     double schwellenwert_ay = 230;
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
    msg += "KOM1=";                 //Kommentar 1
    msg += "(NULL)";
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
                    msg += FMC_NUT;
                    msg += "\n";
                    msg += "SWKZID=";               //WKZ-Nummer
                    msg += tnummer;
                    msg += "\n";
                    msg += "SPX=";
                    msg += nu.get_xs_qstring();
                    msg += "\n";
                    msg += "SPY=";
                    msg += nu.get_ys_qstring();
                    msg += "\n";
                    msg += "EPX=";
                    msg += nu.get_xe_qstring();
                    msg += "\n";
                    msg += "EPY=";
                    msg += nu.get_ye_qstring();
                    msg += "\n";
                    msg += "TI=";
                    msg += nu.get_tiefe_qstring();
                    msg += "\n";
                    msg += "NB=";
                    msg += nu.get_breite_qstring();
                    msg += "\n";
                    msg += "TYPA=1\n";              //Auslauf
                    msg += "TRKOR=0\n";             //KOrrektur/Bezugskante
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
                //double radius_wkz = wkzmag.get_dm(tnummer).toDouble()/2;
                //if(radius < radius_wkz)
                //{
                    //radius = radius_wkz;
                //}
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
                        msg += "TYPAN=1\n";     //Anfahrtyp
                        msg += "TYPAB=1\n";     //Abfahrtyp
                        msg += "TYPEIN=1\n";    //Eintauchtp
                        msg += "LGEAN=2*WKZR\n";    //Anfahrwert
                        msg += "LGEAB=2*WKZR\n";    //Abfahrwert
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
                }
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
                        msg += FMC_NUT;
                        msg += "\n";
                        msg += "SWKZID=";               //WKZ-Nummer
                        msg += tnummer;
                        msg += "\n";
                        msg += "SPX=";
                        msg += nu.get_xs_qstring();
                        msg += "\n";
                        msg += "SPY=";
                        msg += nu.get_ys_qstring();
                        msg += "\n";
                        msg += "EPX=";
                        msg += nu.get_xe_qstring();
                        msg += "\n";
                        msg += "EPY=";
                        msg += nu.get_ye_qstring();
                        msg += "\n";
                        msg += "TI=";
                        msg += nu.get_tiefe_qstring();
                        msg += "\n";
                        msg += "NB=";
                        msg += nu.get_breite_qstring();
                        msg += "\n";
                        msg += "TYPA=1\n";              //Auslauf
                        msg += "TRKOR=0\n";             //KOrrektur/Bezugskante
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
                    //double radius_wkz = wkzmag.get_dm(tnummer).toDouble()/2;
                    //if(radius < radius_wkz)
                    //{
                        //radius = radius_wkz;
                    //}
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
                            msg += "TYPAN=1\n";     //Anfahrtyp
                            msg += "TYPAB=1\n";     //Abfahrtyp
                            msg += "TYPEIN=1\n";    //Eintauchtp
                            msg += "LGEAN=2*WKZR\n";    //Anfahrwert
                            msg += "LGEAB=2*WKZR\n";    //Abfahrwert
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
QString werkstueck::get_eigen_dateitext(text_zeilenweise bearb, double tmp_l, double tmp_b)
{
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

//-------------------------------------------------------------------------Werkzeug:


