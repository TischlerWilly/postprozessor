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
                tnummer = wkzmag.get_wkznummer(WKZ_TYP_FRAESER, bo.get_dm(), bo.get_tiefe(), dicke, bezug);
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
                }else//Es ist auch kein passender Frser da, die CNC-Bearbeitung kann nicht erfolgen
                {
                    msg += "  !! Kein Werkzeug fuer Bohrung oder Kreistasche gefunden!\n";
                }
            }

        }else if(art == BEARBART_RTA)
        {
            rechtecktasche rt(zeile.get_text());
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

        }else if(art == BEARBART_NUT)
        {
            nut nu(zeile.get_text());
            if(nu.get_xs() != nu.get_xe())
            {
                msg += "  !! Nutrichutng auf der der Maschine nicht moeglich!\n";
            }
        }
    }

    return msg;
}
QString werkstueck::warnungen_fmc(text_zeilenweise bearbeit,double tmp_l, double tmp_b)
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

    for(uint i=1; i<=bearbeit.zeilenanzahl() ;i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(bearbeit.zeile(i));

        QString art = zeile.zeile(1);
        if(art == BEARBART_BOHR)
        {
            //...
        }else if(art == BEARBART_RTA)
        {
            //...
        }else if(art == BEARBART_NUT)
        {
            //...
        }
    }

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

//-------------------------------------------------------------------------Export:
QString werkstueck::get_fmc(text_zeilenweise wkzmagazin, QString& info , QString drehwinkel)
{
    QString msg;
    bearb_sortieren();

    if(drehwinkel == "0")
    {
        double tmp_l = laenge;
        double tmp_b = breite;
        text_zeilenweise tmp_bearb = bearbeitungen;
        msg = get_fmc_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b);
        QString warnungen = warnungen_fmc(tmp_bearb, tmp_l, tmp_b);
        info = warnungen;
    }else if(drehwinkel == "90")
    {
        double tmp_l = laenge;
        double tmp_b = breite;
        text_zeilenweise tmp_bearb = bearbeitungen;
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        msg = get_fmc_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b);
        QString warnungen = warnungen_fmc(tmp_bearb, tmp_l, tmp_b);
        info = warnungen;
    }else if(drehwinkel == "180")
    {
        double tmp_l = laenge;
        double tmp_b = breite;
        text_zeilenweise tmp_bearb = bearbeitungen;
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        msg = get_fmc_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b);
        QString warnungen = warnungen_fmc(tmp_bearb, tmp_l, tmp_b);
        info = warnungen;
    }else if(drehwinkel == "270")
    {
        double tmp_l = laenge;
        double tmp_b = breite;
        text_zeilenweise tmp_bearb = bearbeitungen;
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        msg = get_fmc_dateitext(wkzmagazin, tmp_bearb, tmp_l, tmp_b);
        QString warnungen = warnungen_fmc(tmp_bearb, tmp_l, tmp_b);
        info = warnungen;
    }else
    {
        info = "Die Option AUTOMATISCH wird derzeit noch nicht unterstuetzt\n";
        msg = "";
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
        info = "Die Option AUTOMATISCH wird derzeit noch nicht unterstuetzt\n";
        msg = "";

        //double tmp_l = breite;
        //double tmp_b = laenge;
        //text_zeilenweise tmp_bearb;
        //tmp_bearb = bearb_optimieren_ganx(bearbeitungen);
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
        msg = "";
    }
    return msg;
}

QString werkstueck::get_ganx_dateitext(text_zeilenweise wkzmagazin, text_zeilenweise bearb, double tmp_l, double tmp_b)
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
                        y = laenge_y - y;
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
                        y = laenge_y - y;
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
                tnummer = wkzmag.get_wkznummer(WKZ_TYP_FRAESER, dm, bo.get_tiefe(), dicke, bezug);

                if(!tnummer.isEmpty())
                {
                    //Werkzeug wurde gefunden, Kreistasche kann gefräst werden:

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
                    msg += double_to_qstring(z);     //TaTi
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
        }else if(zeile.zeile(1)==BEARBART_NUT)
        {

            nut nu(zeile.get_text());
            if(nu.get_xs() != nu.get_xe())
            {
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
            double z = rt.get_z();
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
            QString tnummer = wkzmag.get_wkznummer(WKZ_TYP_FRAESER, minmass, rt.get_tiefe(), dicke, rt.get_bezug());
            if(tnummer.isEmpty())
            {
                //Mit Fehlermeldung abbrechen:
                QString msg = "";
                msg += "Fehler bei Export ganx!\n";
                msg += "Teilname: ";
                msg += name;
                msg += "\n";
                msg += "Kein Werkzeug fuer Rechtecktasche:\n";
                msg += zeile.get_text();

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
            msg += double_to_qstring(z);     //TaTi
            msg += ";";
            msg += "1";                      //Variante der Rechtecktasche (1 = ausgeräumt)
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
                tnummer = wkzmag.get_wkznummer(WKZ_TYP_FRAESER, dm, bo.get_tiefe(), dicke, bezug);

                if(!tnummer.isEmpty())
                {
                    //Werkzeug wurde gefunden, Kreistasche kann gefräst werden:

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
                    msg += double_to_qstring(z);     //TaTi
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
            QString tnummer = wkzmag.get_wkznummer(WKZ_TYP_FRAESER, minmass, rt.get_tiefe(), dicke, rt.get_bezug());
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
            msg += double_to_qstring(z);     //TaTi
            msg += ";";
            msg += "1";                      //Variante der Rechtecktasche (1 = ausgeräumt)
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
QString werkstueck::get_fmc_dateitext(text_zeilenweise wkzmagazin, text_zeilenweise bearb, double tmp_l, double tmp_b)
{
    QString msg;
    werkzeugmagazin wkzmag(wkzmagazin);

    //Programmkopf:
    msg = FMC_PRGKOPF;
    msg += "\n";


    //Programmende:

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

//-------------------------------------------------------------------------Werkzeug:


