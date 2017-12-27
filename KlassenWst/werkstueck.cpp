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
                    msg += "\n";
                }
            }
        }else if(art == BEARBART_RTA)
        {
            //...
        }else if(art == BEARBART_NUT)
        {

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
            QString bezug = rt.get_bezug();
            if(bezug == WST_BEZUG_OBSEI || bezug == WST_BEZUG_UNSEI)
            {
                rt.set_x(y);
                rt.set_y(tmp_l - x);
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
        }else if(zeile.zeile(1) == BEARBART_RTA)
        {
            rechtecktasche rt(zeile.get_text());
            double x = rt.get_x();
            double y = rt.get_y();
            double z = rt.get_z();
            QString bezug = rt.get_bezug();
            if(bezug == WST_BEZUG_OBSEI)
            {
                rt.set_bezug(WST_BEZUG_UNSEI);
                rt.set_x(y);
                rt.set_y(x);
            }else if(bezug == WST_BEZUG_UNSEI)
            {
                rt.set_bezug(WST_BEZUG_OBSEI);
                rt.set_x(y);
                rt.set_y(x);
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
        }
        bearb.zeile_ersaetzen(i, zeile.get_text());
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
        QString warnungen = warnungen_ganx(tmp_bearb, tmp_l, tmp_b);
        info = warnungen;
    }else if(drehwinkel == "90")
    {
        double tmp_l = laenge;
        double tmp_b = breite;
        text_zeilenweise tmp_bearb = bearbeitungen;
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        msg = get_fmc_dateitext(werkzeugmagazin, tmp_bearb, tmp_l, tmp_b);
        QString warnungen = warnungen_ganx(tmp_bearb, tmp_l, tmp_b);
        info = warnungen;
    }else if(drehwinkel == "180")
    {
        double tmp_l = laenge;
        double tmp_b = breite;
        text_zeilenweise tmp_bearb = bearbeitungen;
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        tmp_bearb = bearb_drehen_90(tmp_bearb, tmp_l, tmp_b);
        msg = get_fmc_dateitext(werkzeugmagazin, tmp_bearb, tmp_l, tmp_b);
        QString warnungen = warnungen_ganx(tmp_bearb, tmp_l, tmp_b);
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
        QString warnungen = warnungen_ganx(tmp_bearb, tmp_l, tmp_b);
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

