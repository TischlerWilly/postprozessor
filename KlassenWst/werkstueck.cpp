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

QString werkstueck::warnungen_ganx(text_zeilenweise bearbeit,double tmp_l, double tmp_b)
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

    for(uint i=1; i<=bearbeit.zeilenanzahl() ;i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(bearbeit.zeile(i));

        QString art = zeile.zeile(1);
        if(art == BEARBART_BOHR)
        {
            QString bezug = zeile.zeile(2);

            if(bezug == WST_BEZUG_VO || bezug == WST_BEZUG_HI)
            {
                double x = zeile.zeile(5).toDouble();
                if( x<18 )
                {
                    msg += "  !! HBE zu dicht am Rand!\n";
                    msg += "     X-Mass muss >= 18mm sein\n";
                    msg += "     X-Mass ist ";
                    msg += double_to_qstring(x);
                    msg += "mm\n";
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
QString werkstueck::get_fmc(text_zeilenweise werkzeugmagazin, QString& info , QString drehwinkel)
{
    QString msg;
    bearb_sortieren();

    if(drehwinkel == "0")
    {
        double tmp_l = laenge;
        double tmp_b = breite;
        text_zeilenweise tmp_bearb = bearbeitungen;
        msg = get_fmc_dateitext(werkzeugmagazin, tmp_bearb, tmp_l, tmp_b);
        QString warnungen = warnungen_fmc(tmp_bearb, tmp_l, tmp_b);
        info = warnungen;
    }else if(drehwinkel == "90")
    {
        double tmp_l = laenge;
        double tmp_b = breite;
        text_zeilenweise tmp_bearb = bearbeitungen;
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        msg = get_fmc_dateitext(werkzeugmagazin, tmp_bearb, tmp_l, tmp_b);
        QString warnungen = warnungen_fmc(tmp_bearb, tmp_l, tmp_b);
        info = warnungen;
    }else if(drehwinkel == "180")
    {
        double tmp_l = laenge;
        double tmp_b = breite;
        text_zeilenweise tmp_bearb = bearbeitungen;
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        msg = get_fmc_dateitext(werkzeugmagazin, tmp_bearb, tmp_l, tmp_b);
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
        msg = get_fmc_dateitext(werkzeugmagazin, tmp_bearb, tmp_l, tmp_b);
        QString warnungen = warnungen_fmc(tmp_bearb, tmp_l, tmp_b);
        info = warnungen;
    }else
    {
        info = "Die Option AUTOMATISCH wird derzeit noch nicht unterstuetzt\n";
        msg = "";
    }
    return msg;
}
QString werkstueck::get_ganx(text_zeilenweise werkzeugmagazin, QString& info , QString drehwinkel)
{
    QString msg;
    bearb_sortieren();

    if(drehwinkel == "0")
    {
        double tmp_l = breite;
        double tmp_b = laenge;
        text_zeilenweise tmp_bearb;
        tmp_bearb = bearb_optimieren_ganx(bearbeitungen);
        msg = get_ganx_dateitext(werkzeugmagazin, tmp_bearb, tmp_l, tmp_b);
        QString warnungen = warnungen_ganx(tmp_bearb, tmp_l, tmp_b);
        info = warnungen;
    }else if(drehwinkel == "90")
    {
        double tmp_l = breite;
        double tmp_b = laenge;
        text_zeilenweise tmp_bearb;
        tmp_bearb = bearb_optimieren_ganx(bearbeitungen);
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        msg = get_ganx_dateitext(werkzeugmagazin, tmp_bearb, tmp_l, tmp_b);
        QString warnungen = warnungen_ganx(tmp_bearb, tmp_l, tmp_b);
        info = warnungen;
    }else if(drehwinkel == "180")
    {
        double tmp_l = breite;
        double tmp_b = laenge;
        text_zeilenweise tmp_bearb;
        tmp_bearb = bearb_optimieren_ganx(bearbeitungen);
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        msg = get_ganx_dateitext(werkzeugmagazin, tmp_bearb, tmp_l, tmp_b);
        QString warnungen = warnungen_ganx(tmp_bearb, tmp_l, tmp_b);
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
        msg = get_ganx_dateitext(werkzeugmagazin, tmp_bearb, tmp_l, tmp_b);
        QString warnungen = warnungen_ganx(tmp_bearb, tmp_l, tmp_b);
        info = warnungen;
    }else
    {
        info = "Die Option AUTOMATISCH wird derzeit noch nicht unterstuetzt\n";
        msg = "";
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

QString werkstueck::get_ganx_dateitext(text_zeilenweise werkzeugmagazin, text_zeilenweise bearb, double tmp_l, double tmp_b)
{
    QString msg;
    text_zeilenweise zeile;
    zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
    double bezugsmass = 40;    //Referenzmaß zum Erkennen der Bezugskante

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
    msg += "ppf";
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
    for(uint i=1 ; i<=baerb.zeilenanzahl() ; i++)
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

            if(bezug == WST_BEZUG_OBSEI)
            {
                //x = Breite
                //y = Länge
                //z = Tiefe
                msg += "  <PrgrFileWork>";
                msg += "\n";
                msg += "    <CntID>";
                msg += int_to_qstring(i);               //ID-Nummer, wir nehemn einfach die Zeilennummer
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
                    ref += GANX_REF_UNTEN_LINKS;
                }else
                {
                    ref += GANX_REF_OBEN_LINKS;
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
                msg += double_to_qstring(dm);
                msg += "</Diameter>";
                msg += "\n";
                //----------------------
                msg += "   <Depth>";
                msg += double_to_qstring(z);
                msg += "</Depth>";
                msg += "\n";
                //----------------------Werkzeugnummer:
                msg += "    <Tool>";

                QString tnummer = get_wkz_nummer(WKZ_TYP_BOHRER, dm, z);
                if(tnummer.isEmpty())
                {
                    QString msg = "Fehler!\nKein Bohrer im Werkzeugmagazin für:\n" + zeile.get_text();
                    QMessageBox mb;
                    mb.setText(msg);
                    mb.exec();
                    return msg;
                }
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
                msg += int_to_qstring(i);               //ID-Nummer, wir nehemn einfach die Zeilennummer
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

            }else if(bezug == WST_BEZUG_UNSEI)
            {
                //x = Breite
                //y = Länge
                //z = Tiefe
                msg += "  <PrgrFileWork>";
                msg += "\n";
                msg += "    <CntID>";
                msg += int_to_qstring(i);               //ID-Nummer, wir nehemn einfach die Zeilennummer
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
                    ref = GANX_REF_UNTEN_LINKS;
                }else
                {
                    ref = GANX_REF_OBEN_LINKS;
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
                msg += double_to_qstring(dm);
                msg += "</Diameter>";
                msg += "\n";
                //----------------------
                msg += "   <Depth>";
                msg += double_to_qstring(z);
                msg += "</Depth>";
                msg += "\n";
                //----------------------Werkzeugnummer:
                msg += "    <Tool>";

                QString tnummer = get_wkz_nummer(WKZ_TYP_BOHRER, dm, z);
                if(tnummer.isEmpty())
                {
                    QString msg = "Fehler!\nKein Bohrer im Werkzeugmagazin für:\n" + zeile.get_text();
                    QMessageBox mb;
                    mb.setText(msg);
                    mb.exec();
                    return msg;
                }
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
                msg += int_to_qstring(i);               //ID-Nummer, wir nehemn einfach die Zeilennummer
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

            }else if(bezug == WST_BEZUG_LI)
            {
                //x = Tiefe
                //y = Y-Pos
                //z = Z-Pos
                msg += "  <PrgrFileWork>";
                msg += "\n";
                msg += "    <CntID>";
                msg += int_to_qstring(i);               //ID-Nummer, wir nehemen einfach die Zeilennummer
                msg += "</CntID>";
                msg += "\n";
                msg += "    <Plane>Left</Plane>";
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
                msg += double_to_qstring(dm);
                msg += "</Diameter>";
                msg += "\n";
                //----------------------
                msg += "   <Depth>";
                msg += double_to_qstring(x);
                msg += "</Depth>";
                msg += "\n";
                //----------------------Werkzeugnummer:
                msg += "    <Tool>";

                QString tnummer = get_wkz_nummer(WKZ_TYP_BOHRER, dm, x);
                if(tnummer.isEmpty())
                {
                    QString msg = "Fehler!\nKein Bohrer im Werkzeugmagazin für:\n" + zeile.get_text();
                    QMessageBox mb;
                    mb.setText(msg);
                    mb.exec();
                    return msg;
                }
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
                msg += int_to_qstring(i);               //ID-Nummer, wir nehemn einfach die Zeilennummer
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

            }else if(bezug == WST_BEZUG_RE)
            {
                //x = Tiefe
                //y = Y-Pos
                //z = Z-Pos
                msg += "  <PrgrFileWork>";
                msg += "\n";
                msg += "    <CntID>";
                msg += int_to_qstring(i);               //ID-Nummer, wir nehemen einfach die Zeilennummer
                msg += "</CntID>";
                msg += "\n";
                msg += "    <Plane>Right</Plane>";
                msg += "\n";
                //----------------------Bezugskante festlegen:
                msg += "    <Ref>";
                QString ref = GANX_REF_OBEN_RECHTS;
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
                msg += double_to_qstring(dm);
                msg += "</Diameter>";
                msg += "\n";
                //----------------------
                msg += "   <Depth>";
                msg += double_to_qstring(x);
                msg += "</Depth>";
                msg += "\n";
                //----------------------Werkzeugnummer:
                msg += "    <Tool>";

                QString tnummer = get_wkz_nummer(WKZ_TYP_BOHRER, dm, x);
                if(tnummer.isEmpty())
                {
                    QString msg = "Fehler!\nKein Bohrer im Werkzeugmagazin für:\n" + zeile.get_text();
                    QMessageBox mb;
                    mb.setText(msg);
                    mb.exec();
                    return msg;
                }
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
                msg += int_to_qstring(i);               //ID-Nummer, wir nehemn einfach die Zeilennummer
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

            }else if(bezug == WST_BEZUG_VO)
            {
                //x = X-Pos
                //y = Tiefe
                //z = Z-Pos
                msg += "  <PrgrFileWork>";
                msg += "\n";
                msg += "    <CntID>";
                msg += int_to_qstring(i);               //ID-Nummer, wir nehemen einfach die Zeilennummer
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
                msg += double_to_qstring(dm);
                msg += "</Diameter>";
                msg += "\n";
                //----------------------
                msg += "   <Depth>";
                msg += double_to_qstring(y);
                msg += "</Depth>";
                msg += "\n";
                //----------------------Werkzeugnummer:
                msg += "    <Tool>";

                QString tnummer = get_wkz_nummer(WKZ_TYP_BOHRER, dm, y);
                if(tnummer.isEmpty())
                {
                    QString msg = "Fehler!\nKein Bohrer im Werkzeugmagazin für:\n" + zeile.get_text();
                    QMessageBox mb;
                    mb.setText(msg);
                    mb.exec();
                    return msg;
                }
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
                msg += int_to_qstring(i);               //ID-Nummer, wir nehemn einfach die Zeilennummer
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
            }else if(bezug == WST_BEZUG_HI)
            {
                //x = X-Pos
                //y = Tiefe
                //z = Z-Pos
                msg += "  <PrgrFileWork>";
                msg += "\n";
                msg += "    <CntID>";
                msg += int_to_qstring(i);               //ID-Nummer, wir nehemen einfach die Zeilennummer
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
                msg += double_to_qstring(dm);
                msg += "</Diameter>";
                msg += "\n";
                //----------------------
                msg += "   <Depth>";
                msg += double_to_qstring(y);
                msg += "</Depth>";
                msg += "\n";
                //----------------------Werkzeugnummer:
                msg += "    <Tool>";

                QString tnummer = get_wkz_nummer(WKZ_TYP_BOHRER, dm, y);
                if(tnummer.isEmpty())
                {
                    QString msg = "Fehler!\nKein Bohrer im Werkzeugmagazin für:\n" + zeile.get_text();
                    QMessageBox mb;
                    mb.setText(msg);
                    mb.exec();
                    return msg;
                }
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
                msg += int_to_qstring(i);               //ID-Nummer, wir nehemn einfach die Zeilennummer
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
            }
        }else if(zeile.zeile(1)==BEARBEITUNG_NUT)
        {
            double x = zeile.zeile(4).toDouble();
            double y = zeile.zeile(5).toDouble();
            double z = zeile.zeile(6).toDouble();
            double l = zeile.zeile(7).toDouble();
            QString wkztyp = WKZ_TYP_SAEGE;
            QString wkz_nr = get_wkz_nummer(wkztyp);
            if(wkz_nr.isEmpty())
            {
                QString msg = "Fehler!\nKeine Saege im Werkzeugmagazin für:\n" + zeile.get_text();
                QMessageBox mb;
                mb.setText(msg);
                mb.exec();
                return msg;
            }
            double wkz_dm = get_wkz_dm(wkz_nr).toDouble();
            double nutvariante = zeile.zeile(9).toDouble();
            QString nutvariante_qstring = "";
            if(nutvariante == 1)
            {
                nutvariante_qstring = "Var2";
            }else if(nutvariante == 2)
            {
                nutvariante_qstring = "Var1";
            }else
            {
                QString msg = "Fehler!\nKeine keine Nut-Variante angegeben:\n" + zeile.get_text();
                QMessageBox mb;
                mb.setText(msg);
                mb.exec();
                return msg;
            }
            QString nutrichtung;
            if (zeile.zeile(8).toDouble() == 1)
            {
                nutrichtung = "X";
            }else
            {
                nutrichtung = "Y";
            }

                msg += "  <PrgrFileWork>";
                msg += "\n";
                //----------------------
                msg += "    <CntID>";
                msg += int_to_qstring(i);               //ID-Nummer, wir nehemen einfach die Zeilennummer in der ASCII-Datei
                msg += "</CntID>";
                msg += "\n";
                //----------------------
                msg += "    <Plane>";
                if(zeile.zeile(2)==BEZUG_FLAECHE_OBEN_ASCII)
                {
                    msg += "Top";
                }else
                {
                    msg += "Bottom";
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
                msg += wkz_nr;
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
                if(zeile.zeile(2)==BEZUG_FLAECHE_OBEN_ASCII)
                {
                    msg += "Top";
                }else
                {
                    msg += "Bottom";
                }
                msg += "\\";
                msg += GANX_REF_OBEN_LINKS;
                msg += "\\";
                msg += "S-";
                msg += int_to_qstring(i);               //ID-Nummer, wir nehemen einfach die Zeilennummer in der ASCII-Datei
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

        }else if(zeile.zeile(1)==BEARBEITUNG_FRAES)//Alle arten von Fräsarbeiten
        {
            if(zeile.zeile(3).toDouble() == 101)//Rechtecktaschen
            {
                double x = zeile.zeile(4).toDouble();
                double y = zeile.zeile(5).toDouble();
                double z = zeile.zeile(6).toDouble();
                double lx = zeile.zeile(7).toDouble();
                double by = zeile.zeile(8).toDouble();
                double minmass = lx;
                if(by < minmass)
                {
                    minmass = by;
                }
                QString wkztyp = WKZ_TYP_FRAESER;
                QString wkz_nr = get_wkz_nummer(wkztyp, minmass, z);
                if(wkz_nr.isEmpty())
                {
                    QString msg = "Fehler!\nKein Fraeser im Werkzeugmagazin für:\n" + zeile.get_text();
                    QMessageBox mb;
                    mb.setText(msg);
                    mb.exec();
                    return msg;
                }
                double wkz_dm = get_wkz_dm(wkz_nr).toDouble();
                double eckenradius = zeile.zeile(9).toDouble();
                if(eckenradius < wkz_dm/2)
                {
                    eckenradius = wkz_dm/2;
                }
                double wkz_vorschub = get_wkz_vorschub(wkz_nr).toDouble();
                int zustellungen = zeile.zeile(10).toInt();
                if(zustellungen <= 0)
                {
                    zustellungen = 1;
                }

                msg += "  <PrgrFileWork>";
                msg += "\n";
                //----------------------
                msg += "    <CntID>";
                msg += int_to_qstring(i);               //ID-Nummer, wir nehemen einfach die Zeilennummer in der ASCII-Datei
                msg += "</CntID>";
                msg += "\n";
                //----------------------
                msg += "    <Plane>";
                if(zeile.zeile(2)==BEZUG_FLAECHE_OBEN_ASCII)
                {
                    msg += "Top";
                }else
                {
                    msg += "Bottom";
                }
                msg += "</Plane>";
                msg += "\n";
                //----------------------Bezugskante festlegen:
                QString bezug = GANX_REF_OBEN_LINKS;
                //y < 40 -> TL
                //Länge - y < 40 ->BL
                if(laenge_y - y < bezugsmass)
                {
                    bezug = GANX_REF_UNTEN_LINKS;
                }
                msg += "    <Ref>";
                msg += bezug;
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
                msg += wkz_nr;
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
                if(zeile.zeile(2)==BEZUG_FLAECHE_OBEN_ASCII)
                {
                    msg += "Top";
                }else
                {
                    msg += "Bottom";
                }
                msg += "\\";
                msg += GANX_REF_OBEN_LINKS;
                msg += "\\";
                msg += "M-";
                msg += int_to_qstring(i);               //ID-Nummer, wir nehemen einfach die Zeilennummer in der ASCII-Datei
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



            }else if(zeile.zeile(3).toDouble() == 102)//Kreistaschen
            {
                double x = zeile.zeile(4).toDouble();
                double y = zeile.zeile(5).toDouble();
                double z = zeile.zeile(6).toDouble();
                double dm = zeile.zeile(7).toDouble();
                QString wkztyp = WKZ_TYP_FRAESER;
                QString wkz_nr = get_wkz_nummer(wkztyp, dm, z);
                if(wkz_nr.isEmpty())
                {
                    QString msg = "Fehler!\nKein Fraeser im Werkzeugmagazin für:\n" + zeile.get_text();
                    QMessageBox mb;
                    mb.setText(msg);
                    mb.exec();
                    return msg;
                }
                //double wkz_dm = get_wkz_dm(wkz_nr).toDouble();
                double wkz_vorschub = get_wkz_vorschub(wkz_nr).toDouble();
                int zustellungen = zeile.zeile(8).toInt();
                if(zustellungen <= 0)
                {
                    zustellungen = 1;
                }


                msg += "  <PrgrFileWork>";
                msg += "\n";
                //----------------------
                msg += "    <CntID>";
                msg += int_to_qstring(i);               //ID-Nummer, wir nehemen einfach die Zeilennummer in der ASCII-Datei
                msg += "</CntID>";
                msg += "\n";
                //----------------------
                msg += "    <Plane>";
                if(zeile.zeile(2)==BEZUG_FLAECHE_OBEN_ASCII)
                {
                    msg += "Top";
                }else
                {
                    msg += "Bottom";
                }
                msg += "</Plane>";
                msg += "\n";
                //----------------------Bezugskante festlegen:
                QString bezug = GANX_REF_OBEN_LINKS;
                //y < 40 -> TL
                //Länge - y < 40 ->BL
                if(laenge_y - y < bezugsmass)
                {
                    bezug = GANX_REF_UNTEN_LINKS;
                }
                msg += "    <Ref>";
                msg += bezug;
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
                msg += wkz_nr;
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
                msg += double_to_qstring(wkz_vorschub);
                msg += ";";
                msg += int_to_qstring(zustellungen);
                msg += "</Mill>";
                msg += "\n";
                //----------------------
                msg += "    <ImageKey>KR</ImageKey>";
                msg += "\n";
                //----------------------
                msg += "    <OldID>";
                if(zeile.zeile(2)==BEZUG_FLAECHE_OBEN_ASCII)
                {
                    msg += "Top";
                }else
                {
                    msg += "Bottom";
                }
                msg += "\\";
                msg += GANX_REF_OBEN_LINKS;
                msg += "\\";
                msg += "M-";
                msg += int_to_qstring(i);               //ID-Nummer, wir nehemen einfach die Zeilennummer in der ASCII-Datei
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
            }
        }
    }

    //-------------------------Bearbeitungen <PrgrFile>:
    for(uint i=4 ; i<=tz.zeilenanzahl() ; i++)
    {
        zeile.set_text(tz.zeile(i));
        if(zeile.zeile(1) == BEARBART_BOHR)
        {
            double x = zeile.zeile(4).toDouble();
            double y = zeile.zeile(5).toDouble();
            double z = zeile.zeile(6).toDouble();
            double dm = zeile.zeile(7).toDouble();
            double laenge_y = tmp_b;
            QString bezug = bo.get_bezug();

            //int ref = zeile.zeile(3).toInt();       //Referenzkante 1 = TL / 4 = BL

            if(bezug == WST_BEZUG_OBSEI)
            {
                //x = Breite
                //y = Länge
                //z = Tiefe
                msg += "  <PrgrFile>";
                msg += "\n";
                //----------------------
                msg += "    <CntID>";
                msg += int_to_qstring(i);               //ID-Nummer, wir nehemn einfach die Zeilennummer
                msg += "</CntID>";
                msg += "\n";
                //----------------------
                //y < 40 -> TL
                //Länge - y < 40 ->BL
                QString ref;
                if(laenge_y - y < bezugsmass)
                {
                    ref += GANX_REF_UNTEN_LINKS;
                }else
                {
                    ref += GANX_REF_OBEN_LINKS;
                }
                msg += ref;
                //----------------------
                msg += "    <ID>";
                msg += GANX_WST_BEZUG_OBSEI;
                msg += "\\";
                msg += ref;
                msg += "\\";
                msg += "B-";
                msg += int_to_qstring(i);               //ID-Nummer, wir nehemn einfach die Zeilennummer
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
                msg += double_to_qstring(dm).replace(".",",");
                msg += "</Diameter>";
                msg += "\n";
                //----------------------
                msg += "   <Depth>";
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
                //----------------------Werkzeugnummer:
                msg += "    <Tool>";

                QString tnummer = get_wkz_nummer(WKZ_TYP_BOHRER, dm, z);
                if(tnummer.isEmpty())
                {
                    QString msg = "Fehler!\nKein Bohrer im Werkzeugmagazin für:\n" + zeile.get_text();
                    QMessageBox mb;
                    mb.setText(msg);
                    mb.exec();
                    return msg;
                }
                msg += tnummer;
                msg += "</Tool>";
                msg += "\n";
                //----------------------
                msg += "    <Cyclic>1</Cyclic>";
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

            }else if(bezug == WST_BEZUG_UNSEI)
            {
                //x = Breite
                //y = Länge
                //z = Tiefe
                msg += "  <PrgrFile>";
                msg += "\n";
                msg += "    <CntID>";
                msg += int_to_qstring(i);               //ID-Nummer, wir nehemn einfach die Zeilennummer
                msg += "</CntID>";
                msg += "\n";
                //----------------------
                QString ref;
                if(laenge_y - y < bezugsmass)
                {
                    ref = GANX_REF_UNTEN_LINKS;
                }else
                {
                    ref = GANX_REF_OBEN_LINKS;
                }
                msg += ref;
                //----------------------
                msg += "    <ID>";
                msg += GANX_WST_BEZUG_UNSEI;
                msg += "\\";
                msg += ref;
                msg += "\\";
                msg += "B-";
                msg += int_to_qstring(i);               //ID-Nummer, wir nehemn einfach die Zeilennummer
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
                msg += double_to_qstring(dm).replace(".",",");
                msg += "</Diameter>";
                msg += "\n";
                //----------------------
                msg += "   <Depth>";
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
                //----------------------Werkzeugnummer:
                msg += "    <Tool>";

                QString tnummer = get_wkz_nummer(WKZ_TYP_BOHRER, dm, z);
                if(tnummer.isEmpty())
                {
                    QString msg = "Fehler!\nKein Bohrer im Werkzeugmagazin für:\n" + zeile.get_text();
                    QMessageBox mb;
                    mb.setText(msg);
                    mb.exec();
                    return msg;
                }
                msg += tnummer;
                msg += "</Tool>";
                msg += "\n";
                //----------------------
                msg += "    <Cyclic>1</Cyclic>";
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

            }else if(bezug == WST_BEZUG_LI)
            {
                //x = Tiefe
                //y = Y-Pos
                //z = Z-Pos
                msg += "  <PrgrFile>";
                msg += "\n";
                msg += "    <CntID>";
                msg += int_to_qstring(i);               //ID-Nummer, wir nehemn einfach die Zeilennummer
                msg += "</CntID>";
                msg += "\n";
                //----------------------
                QString bezug = GANX_REF_OBEN_LINKS;
                if(ref == 4)//BL
                {
                    y = laenge_y - y; //Maß hat jetzt Bezug TL
                }
                //----------------------
                msg += "    <ID>";
                msg += GANX_WST_BEZUG_LI;
                msg += "\\";
                msg += bezug;
                msg += "\\";
                msg += "B-";
                msg += int_to_qstring(i);               //ID-Nummer, wir nehemn einfach die Zeilennummer
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
                msg += double_to_qstring(dm).replace(".",",");
                msg += "</Diameter>";
                msg += "\n";
                //----------------------
                msg += "   <Depth>";
                msg += double_to_qstring(x).replace(".",",");
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
                //----------------------Werkzeugnummer:
                msg += "    <Tool>";

                QString tnummer = get_wkz_nummer(WKZ_TYP_BOHRER, dm, x);
                if(tnummer.isEmpty())
                {
                    QString msg = "Fehler!\nKein Bohrer im Werkzeugmagazin für:\n" + zeile.get_text();
                    QMessageBox mb;
                    mb.setText(msg);
                    mb.exec();
                    return msg;
                }
                msg += tnummer;
                msg += "</Tool>";
                msg += "\n";
                //----------------------
                msg += "    <Cyclic>1</Cyclic>";
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

            }else if(bezug == WST_BEZUG_RE
            {
                //x = Tiefe
                //y = Y-Pos
                //z = Z-Pos
                msg += "  <PrgrFile>";
                msg += "\n";
                msg += "    <CntID>";
                msg += int_to_qstring(i);               //ID-Nummer, wir nehemn einfach die Zeilennummer in der ASCII-Datei
                msg += "</CntID>";
                msg += "\n";
                //----------------------
                QString bezug = GANX_REF_OBEN_RECHTS;
                if(ref == 4)//BL
                {
                    y = laenge_y - y; //Maß hat jetzt Bezug TL
                }
                //----------------------
                msg += "    <ID>";
                msg += "Right";
                msg += "\\";
                msg += bezug;
                msg += "\\";
                msg += "B-";
                msg += int_to_qstring(i);               //ID-Nummer, wir nehemn einfach die Zeilennummer in der ASCII-Datei
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
                msg += double_to_qstring(dm).replace(".",",");
                msg += "</Diameter>";
                msg += "\n";
                //----------------------
                msg += "   <Depth>";
                msg += double_to_qstring(x).replace(".",",");
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
                //----------------------Werkzeugnummer:
                msg += "    <Tool>";

                QString tnummer = get_wkz_nummer(WKZ_TYP_BOHRER, dm, x);
                if(tnummer.isEmpty())
                {
                    QString msg = "Fehler!\nKein Bohrer im Werkzeugmagazin für:\n" + zeile.get_text();
                    QMessageBox mb;
                    mb.setText(msg);
                    mb.exec();
                    return msg;
                }
                msg += tnummer;
                msg += "</Tool>";
                msg += "\n";
                //----------------------
                msg += "    <Cyclic>1</Cyclic>";
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

            }else if(bezug == WST_BEZUG_VO)
            {
                //x = x-Pos
                //y = Tiefe
                //z = Z-Pos
                msg += "  <PrgrFile>";
                msg += "\n";
                msg += "    <CntID>";
                msg += int_to_qstring(i);               //ID-Nummer, wir nehemn einfach die Zeilennummer in der ASCII-Datei
                msg += "</CntID>";
                msg += "\n";
                //----------------------
                QString bezug = GANX_REF_UNTEN_LINKS;
                //----------------------
                msg += "    <ID>";
                msg += "Front";
                msg += "\\";
                msg += bezug;
                msg += "\\";
                msg += "B-";
                msg += int_to_qstring(i);               //ID-Nummer, wir nehemn einfach die Zeilennummer in der ASCII-Datei
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
                msg += double_to_qstring(dm).replace(".",",");
                msg += "</Diameter>";
                msg += "\n";
                //----------------------
                msg += "   <Depth>";
                msg += double_to_qstring(y).replace(".",",");
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
                //----------------------Werkzeugnummer:
                msg += "    <Tool>";

                QString tnummer = get_wkz_nummer(WKZ_TYP_BOHRER, dm, y);
                if(tnummer.isEmpty())
                {
                    QString msg = "Fehler!\nKein Bohrer im Werkzeugmagazin für:\n" + zeile.get_text();
                    QMessageBox mb;
                    mb.setText(msg);
                    mb.exec();
                    return msg;
                }
                msg += tnummer;
                msg += "</Tool>";
                msg += "\n";
                //----------------------
                msg += "    <Cyclic>1</Cyclic>";
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
            }else if(bezug == WST_BEZUG_HI)
            {
                //x = x-Pos
                //y = Tiefe
                //z = Z-Pos
                msg += "  <PrgrFile>";
                msg += "\n";
                msg += "    <CntID>";
                msg += int_to_qstring(i);               //ID-Nummer, wir nehemn einfach die Zeilennummer in der ASCII-Datei
                msg += "</CntID>";
                msg += "\n";
                //----------------------
                QString bezug = GANX_REF_OBEN_LINKS;
                //----------------------
                msg += "    <ID>";
                msg += "Rear";
                msg += "\\";
                msg += bezug;
                msg += "\\";
                msg += "B-";
                msg += int_to_qstring(i);               //ID-Nummer, wir nehemn einfach die Zeilennummer in der ASCII-Datei
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
                msg += double_to_qstring(dm).replace(".",",");
                msg += "</Diameter>";
                msg += "\n";
                //----------------------
                msg += "   <Depth>";
                msg += double_to_qstring(y).replace(".",",");
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
                //----------------------Werkzeugnummer:
                msg += "    <Tool>";

                QString tnummer = get_wkz_nummer(WKZ_TYP_BOHRER, dm, y);
                if(tnummer.isEmpty())
                {
                    QString msg = "Fehler!\nKein Bohrer im Werkzeugmagazin für:\n" + zeile.get_text();
                    QMessageBox mb;
                    mb.setText(msg);
                    mb.exec();
                    return msg;
                }
                msg += tnummer;
                msg += "</Tool>";
                msg += "\n";
                //----------------------
                msg += "    <Cyclic>1</Cyclic>";
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
            }
        }else if(zeile.zeile(1)==BEARBEITUNG_NUT)
        {
            double x = zeile.zeile(4).toDouble();
            double y = zeile.zeile(5).toDouble();
            double z = zeile.zeile(6).toDouble();
            double l = zeile.zeile(7).toDouble();
            QString wkztyp = WKZ_TYP_SAEGE;
            QString wkz_nr = get_wkz_nummer(wkztyp);
            //double wkz_dm = get_wkz_dm(wkz_nr).toDouble();
            double nutvariante = zeile.zeile(9).toDouble();
            QString nutvariante_qstring = "";
            if(nutvariante == 1)
            {
                nutvariante_qstring = "Var2";
            }else if(nutvariante == 2)
            {
                nutvariante_qstring = "Var1";
            }else
            {
                QString msg = "Fehler!\nKeine keine Nut-Variante angegeben:\n" + zeile.get_text();
                QMessageBox mb;
                mb.setText(msg);
                mb.exec();
                return msg;
            }
            QString nutrichtung;
            if (zeile.zeile(8).toDouble() == 1)
            {
                nutrichtung = "X";
            }else
            {
                nutrichtung = "Y";
            }

            msg += "  <PrgrFile>";
            msg += "\n";
            //----------------------
            msg += "    <CntID>";
            msg += int_to_qstring(i);               //ID-Nummer, wir nehemen einfach die Zeilennummer in der ASCII-Datei
            msg += "</CntID>";
            msg += "\n";
            //----------------------
            msg += "    <ID>";
            if(zeile.zeile(2)==BEZUG_FLAECHE_OBEN_ASCII)
            {
                msg += "Top";
            }else
            {
                msg += "Bottom";
            }
            msg += "\\";
            msg += GANX_REF_OBEN_LINKS;
            msg += "\\";
            msg += "S-";
            msg += int_to_qstring(i);               //ID-Nummer, wir nehemen einfach die Zeilennummer in der ASCII-Datei
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
            msg += wkz_nr;
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
            msg += "    <Cyclic>0</Cyclic>";
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

        }else if(zeile.zeile(1)==BEARBEITUNG_FRAES)//Alle arten von Fräsarbeiten
        {
            if(zeile.zeile(3).toDouble() == 101)//Rechtecktaschen
            {
                double x = zeile.zeile(4).toDouble();
                double y = zeile.zeile(5).toDouble();
                double z = zeile.zeile(6).toDouble();
                double lx = zeile.zeile(7).toDouble();
                double by = zeile.zeile(8).toDouble();
                double minmass = lx;
                if(by < minmass)
                {
                    minmass = by;
                }
                QString wkztyp = WKZ_TYP_FRAESER;
                QString wkz_nr = get_wkz_nummer(wkztyp, minmass, z);
                double wkz_dm = get_wkz_dm(wkz_nr).toDouble();
                double eckenradius = zeile.zeile(9).toDouble();
                if(eckenradius < wkz_dm/2)
                {
                    eckenradius = wkz_dm/2;
                }
                double wkz_vorschub = get_wkz_vorschub(wkz_nr).toDouble();
                int zustellungen = zeile.zeile(10).toInt();
                if(zustellungen <= 0)
                {
                    zustellungen = 1;
                }

                msg += "  <PrgrFile>";
                msg += "\n";
                //----------------------
                msg += "    <CntID>";
                msg += int_to_qstring(i);               //ID-Nummer, wir nehemen einfach die Zeilennummer in der ASCII-Datei
                msg += "</CntID>";
                msg += "\n";
                //----------------------
                QString bezug = GANX_REF_OBEN_LINKS;
                //y < 40 -> TL
                //Länge - y < 40 ->BL
                if(laenge_y - y < bezugsmass)
                {
                    bezug = GANX_REF_UNTEN_LINKS;
                    y = laenge_y - y;
                }
                //----------------------
                msg += "    <ID>";
                if(zeile.zeile(2)==BEZUG_FLAECHE_OBEN_ASCII)
                {
                    msg += "Top";
                }else
                {
                    msg += "Bottom";
                }
                msg += "\\";
                msg += bezug;
                msg += "\\";
                msg += "M-";
                msg += int_to_qstring(i);               //ID-Nummer, wir nehemn einfach die Zeilennummer in der ASCII-Datei
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
                msg += wkz_nr;
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
            }else if(zeile.zeile(3).toDouble() == 102)//Kreistaschen
            {
                double x = zeile.zeile(4).toDouble();
                double y = zeile.zeile(5).toDouble();
                double z = zeile.zeile(6).toDouble();
                double dm = zeile.zeile(7).toDouble();
                QString wkztyp = WKZ_TYP_FRAESER;
                QString wkz_nr = get_wkz_nummer(wkztyp, dm, z);
                //double wkz_dm = get_wkz_dm(wkz_nr).toDouble();
                double wkz_vorschub = get_wkz_vorschub(wkz_nr).toDouble();
                int zustellungen = zeile.zeile(8).toInt();
                if(zustellungen <= 0)
                {
                    zustellungen = 1;
                }

                msg += "  <PrgrFile>";
                msg += "\n";
                //----------------------
                msg += "    <CntID>";
                msg += int_to_qstring(i);               //ID-Nummer, wir nehemen einfach die Zeilennummer in der ASCII-Datei
                msg += "</CntID>";
                msg += "\n";
                //----------------------
                QString bezug = GANX_REF_OBEN_LINKS;
                //y < 40 -> TL
                //Länge - y < 40 ->BL
                if(laenge_y - y < bezugsmass)
                {
                    bezug = GANX_REF_UNTEN_LINKS;
                    y = laenge_y - y;
                }
                //----------------------
                msg += "    <ID>";
                if(zeile.zeile(2)==BEZUG_FLAECHE_OBEN_ASCII)
                {
                    msg += "Top";
                }else
                {
                    msg += "Bottom";
                }
                msg += "\\";
                msg += bezug;
                msg += "\\";
                msg += "M-";
                msg += int_to_qstring(i);               //ID-Nummer, wir nehemn einfach die Zeilennummer in der ASCII-Datei
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
            }
        }
    }

    //-------------------------Programmende:
    msg += "</Programm>";


    return msg;
}
QString werkstueck::get_fmc_dateitext(text_zeilenweise werkzeugmagazin, text_zeilenweise bearb, double tmp_l, double tmp_b)
{
    QString msg;

    //Programmkopf:
    msg = FMC_PRGKOPF;
    msg += "\n";


    //Programmende:

    return msg;
}
QString werkstueck::get_eigen_dateitext(text_zeilenweise bearb, double tmp_l, double tmp_b)
{
    QString msg;
    bearb_sortieren();

    //Programmkopf:
    msg = "L: ";
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

