#include "werkstueck.h"

werkstueck::werkstueck()
{
    Laenge  = 0;
    Breite  = 0;
    Dicke   = 0;
}
werkstueck::werkstueck(QString neuer_name)
{
    Name    = neuer_name;
    Laenge  = 0;
    Breite  = 0;
    Dicke   = 0;
}
//#######################################################################
//Public:
//#######################################################################
//--------------------------------------------------set_xy:
void werkstueck::set_laenge(double l)
{
    if(l>0 && l<5000)
    {
        Laenge = l;
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
        Breite = b;
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
        Dicke = d;
    }
}
void werkstueck::set_dicke(QString d)
{
    set_dicke(d.toDouble());
}
void werkstueck::neue_bearbeitung(QString text)
{
    bool bereits_vorhanden = false;

    for(uint i=0; i<=Bearbeitungen.zeilenanzahl() ;i++)
    {
        if(Bearbeitungen.zeile(i) == text)
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
        Bearbeitungen.zeilen_anhaengen(text);
    }
}
void werkstueck::set_bearb(text_zeilenweise b)
{
    Bearbeitungen = b;
}
void werkstueck::set_kante_vo(QString artiklenummer)
{
    Kante_vo = artiklenummer;
}
void werkstueck::set_kante_hi(QString artiklenummer)
{
    Kante_hi = artiklenummer;
}
void werkstueck::set_kante_li(QString artiklenummer)
{
    Kante_li = artiklenummer;
}
void werkstueck::set_kante_re(QString artiklenummer)
{
    Kante_re = artiklenummer;
}
void werkstueck::set_zugabe_gehrungen(double wert)
{
    Zugabe_gehrungen = wert;
}
void werkstueck::set_zustand(QString format, text_zeilenweise wkzmag, QString drehung, \
                             bool formartierungen_aufbrechen, QString zust_fkon)
{
    Zustand.set_bearb(Bearbeitungen);
    Zustand.set_laenge(laenge());
    Zustand.set_breite(breite());
    Zustand.set_dicke(dicke());
    Zustand.set_kante_vo(Kante_vo);
    Zustand.set_kante_hi(Kante_hi);
    Zustand.set_kante_li(Kante_li);
    Zustand.set_kante_re(Kante_re);
    Zustand.set_zugabe_gehrungen(Zugabe_gehrungen);
    Zustand.set_formartierungen_aufbrechen(formartierungen_aufbrechen);
    Zustand.set_name(name());
    Zustand.set_zust_fkon(zust_fkon);
    Zustand.anfordern(format, wkzmag, drehung);
}
void werkstueck::set_einstellung_ganx(einstellung_ganx e)
{
    Zustand.set_einst_ganx(e);
}
//--------------------------------------------------get_xy:

QString werkstueck::cad_fehler(bool kurz)
{
    QString msg;

    if(Name.contains("Tuer") || \
       Name.contains("Tur")      )
    {
        uint anz_asd = 0; //Anzahl Aufschlagdämpfer

        for(uint i=1; i<=Bearbeitungen.zeilenanzahl() ;i++)
        {
            if(Bearbeitungen.zeile(i).contains(BEARBART_BOHR))
            {
                bohrung bo(Bearbeitungen.zeile(i));
                if(bo.dm() == 6 && bo.tiefe() < dicke())
                {
                    anz_asd++;
                }
            }
        }
        if(anz_asd < 2)
        {
            if(kurz)
            {
                if(!msg.isEmpty())
                {
                    msg += " / ";
                }
                msg += double_to_qstring(anz_asd);
                msg += " Aufschlagdämpfer";
            }else
            {
                msg += name();
                msg += ": ";
                msg += double_to_qstring(anz_asd);
                msg += " Aufschlagdämpfer";
                msg += "\n";
            }
        }
    }
    if(Name.contains("SchubFront") || \
       Name.contains("Schubfront")      )
    {
        uint anz_asd = 0; //Anzahl Aufschlagdämpfer

        for(uint i=1; i<=Bearbeitungen.zeilenanzahl() ;i++)
        {
            if(Bearbeitungen.zeile(i).contains(BEARBART_BOHR))
            {
                bohrung bo(Bearbeitungen.zeile(i));
                if(bo.dm() == 6 && bo.tiefe() < dicke())
                {
                    anz_asd++;
                }
            }
        }
        if(anz_asd < 4)
        {
            if(kurz)
            {
                if(!msg.isEmpty())
                {
                    msg += " / ";
                }
                msg += double_to_qstring(anz_asd);
                msg += " Aufschlagdämpfer";
            }else
            {
                msg += name();
                msg += ": ";
                msg += double_to_qstring(anz_asd);
                msg += " Aufschlagdämpfer";
                msg += "\n";
            }
        }
    }


    return msg;
}
double werkstueck::max_x(QString format)
{
    if(drehung()=="0" | drehung()=="180")
    {
        if(format == "ganx")
        {
            return breite()+25;
        }else
        {
            return laenge()+25;
        }
    }else
    {
        if(format == "ganx")
        {
            return laenge()+25;
        }else
        {
            return breite()+25;
        }
    }
    //Drehung "AUTO" kann hier nicht korrekt verarbeitet werden, muss aber auch nicht
}
double werkstueck::max_x()
{
    return zustand().l()+25;
}
double werkstueck::min_x(QString format)
{
    return 0-25;
}
double werkstueck::min_x()
{
    return 0-25;
}
double werkstueck::max_y(QString format)
{
    if(drehung()=="0" | drehung()=="180")
    {
        if(format == "ganx")
        {
            return laenge()+25+ay();
        }else
        {
            return breite()+25+ay();
        }
    }else
    {
        if(format == "ganx")
        {
            return breite()+25+ay();
        }else
        {
            return laenge()+25+ay();
        }
    }
    //Drehung "AUTO" kann hier nicht korrekt verarbeitet werden, muss aber auch nicht
}
double werkstueck::max_y()
{
    return zustand().b()+25+ay();
}
double werkstueck::min_y(QString format)
{
    return 0-25;
}
double werkstueck::min_y()
{
    return 0-25;
}
geometrietext werkstueck::geo()
{
    double versatz_x = 0;
    double versatz_y = 0;
    QString kante_v = kante_vo();
    QString kante_h = kante_hi();
    QString kante_l = kante_li();
    QString kante_r = kante_re();
    //-------------------------------------------
    geometrietext gt;
    //------------------------------
    //Nullpunkt darstellen:
    punkt3d nullpunkt(0,0,0);
    nullpunkt.set_linienbreite(15);
    gt.add_punkt(nullpunkt);
    //------------------------------
    //wst darstellen:
    rechteck3d rec;
    rec.set_bezugspunkt(UNTEN_LINKS);
    rec.set_einfuegepunkt(versatz_x,versatz_y,0);
    rec.set_laenge(laenge());
    rec.set_breite(breite());
    rec.set_farbe_fuellung(FARBE_GRAU);
    gt.add_rechteck(rec);
    //------------------------------
    //Kanten darstellen:
    strecke skante;
    skante.set_linienbreite(5);
    if(!kante_v.isEmpty())
    {
        punkt3d sp(0,0,0);
        punkt3d ep(laenge(),0,0);
        skante.set_start(sp);
        skante.set_ende(ep);
        skante.verschieben_um(versatz_x, versatz_y);
        gt.add_strecke(skante);
    }
    if(!kante_h.isEmpty())
    {
        punkt3d sp(0,breite(),0);
        punkt3d ep(laenge(),breite(),0);
        skante.set_start(sp);
        skante.set_ende(ep);
        skante.verschieben_um(versatz_x, versatz_y);
        gt.add_strecke(skante);
    }
    if(!kante_l.isEmpty())
    {
        punkt3d sp(0,0,0);
        punkt3d ep(0,breite(),0);
        skante.set_start(sp);
        skante.set_ende(ep);
        skante.verschieben_um(versatz_x, versatz_y);
        gt.add_strecke(skante);
    }
    if(!kante_r.isEmpty())
    {
        punkt3d sp(laenge(),0,0);
        punkt3d ep(laenge(),breite(),0);
        skante.set_start(sp);
        skante.set_ende(ep);
        skante.verschieben_um(versatz_x, versatz_y);
        gt.add_strecke(skante);
    }
    //------------------------------
    gt.zeilenvorschub();
    //------------------------------
    //Bearbeitungen darstellen:
    QString farbe_unterseite = FARBE_ROSE;
    for(uint i=1; i<=Bearbeitungen.zeilenanzahl() ;i++)
    {
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(Bearbeitungen.zeile(i));
        if(zeile.zeile(1) == BEARBART_BOHR)
        {
            bohrung bo(zeile.text());
            if(bo.bezug() == WST_BEZUG_OBSEI)
            {
                kreis k;
                k.set_farbe(FARBE_SCHWARZ);
                k.set_radius(bo.dm()/2);
                k.set_mittelpunkt(bo.mipu());
                k.verschieben_um(versatz_x, versatz_y);
                if(bo.tiefe() > dicke())
                {
                    k.set_farbe_fuellung(FARBE_WEISS);
                }else
                {
                    k.set_farbe_fuellung(FARBE_HELLBLAU);
                }
                gt.add_kreis(k);
                strecke s;
                s.set_farbe(k.farbe());
                s.set_start(bo.x() - bo.dm()/2 - 2, bo.y(), bo.z());
                s.set_ende( bo.x() + bo.dm()/2 + 2, bo.y(), bo.z());
                s.verschieben_um(versatz_x, versatz_y);
                gt.add_strecke(s);
                s.drenen_um_mittelpunkt_2d(90, true);
                gt.add_strecke(s);
            }else if(bo.bezug() == WST_BEZUG_UNSEI)
            {
                kreis k;
                k.set_farbe(farbe_unterseite);
                k.set_radius(bo.dm()/2);
                k.set_mittelpunkt(bo.mipu());
                if(bo.tiefe() > dicke())
                {
                    k.set_farbe_fuellung(FARBE_WEISS);
                }else
                {
                    k.set_farbe_fuellung(FARBE_HELLBLAU);
                }
                k.verschieben_um(versatz_x, versatz_y);
                gt.add_kreis(k);
                strecke s;
                s.set_farbe(k.farbe());
                s.set_start(bo.x() - bo.dm()/2 - 2, bo.y(), bo.z());
                s.set_ende( bo.x() + bo.dm()/2 + 2, bo.y(), bo.z());
                s.drenen_um_mittelpunkt_2d(45, true);
                s.verschieben_um(versatz_x, versatz_y);
                gt.add_strecke(s);
                s.drenen_um_mittelpunkt_2d(90, true);
                gt.add_strecke(s);
            }else if(bo.bezug() == WST_BEZUG_LI)
            {
                rechteck3d r;
                r.set_farbe_fuellung(FARBE_BRAUN);
                r.set_laenge(bo.tiefe());
                r.set_breite(bo.dm());
                r.set_bezugspunkt(LINKS);
                r.set_einfuegepunkt(0, bo.y(), 0);
                r.verschieben_um(versatz_x, versatz_y);
                gt.add_rechteck(r);
            }else if(bo.bezug() == WST_BEZUG_RE)
            {
                rechteck3d r;
                r.set_farbe_fuellung(FARBE_BRAUN);
                r.set_laenge(bo.tiefe());
                r.set_breite(bo.dm());
                r.set_bezugspunkt(RECHTS);
                r.set_einfuegepunkt(laenge(), bo.y(), 0);
                r.verschieben_um(versatz_x, versatz_y);
                gt.add_rechteck(r);
            }else if(bo.bezug() == WST_BEZUG_VO)
            {
                rechteck3d r;
                r.set_farbe_fuellung(FARBE_BRAUN);
                r.set_laenge(bo.dm());
                r.set_breite(bo.tiefe());
                r.set_bezugspunkt(UNTEN);
                r.set_einfuegepunkt(bo.x(), 0, 0);
                r.verschieben_um(versatz_x, versatz_y);
                gt.add_rechteck(r);
            }else if(bo.bezug() == WST_BEZUG_HI)
            {
                rechteck3d r;
                r.set_farbe_fuellung(FARBE_BRAUN);
                r.set_laenge(bo.dm());
                r.set_breite(bo.tiefe());
                r.set_bezugspunkt(OBEN);
                r.set_einfuegepunkt(bo.x(), breite(), 0);
                r.verschieben_um(versatz_x, versatz_y);
                gt.add_rechteck(r);
            }
        }else if(zeile.zeile(1) == BEARBART_BOHRRASTER)
        {
            bohrraster bo(zeile.text());
            if(bo.bezug() == WST_BEZUG_OBSEI)
            {
                kreis k;
                k.set_farbe(FARBE_SCHWARZ);
                k.set_radius(bo.dm()/2);
                k.set_mittelpunkt(bo.mipu());
                k.verschieben_um(versatz_x, versatz_y);
                if(bo.tiefe() > dicke())
                {
                    k.set_farbe_fuellung(FARBE_WEISS);
                }else
                {
                    k.set_farbe_fuellung(FARBE_HELLBLAU);
                }
                strecke s1;
                s1.set_farbe(k.farbe());
                s1.set_start(bo.x() - bo.dm()/2 - 2, bo.y(), bo.z());
                s1.set_ende( bo.x() + bo.dm()/2 + 2, bo.y(), bo.z());
                s1.verschieben_um(versatz_x, versatz_y);
                strecke s2 = s1;
                s2.drenen_um_mittelpunkt_2d(90, true);
                for(uint i=0; i<bo.anz_x() ;i++)
                {
                    kreis tmp_k = k;
                    tmp_k.verschieben_um(i*bo.raster_x(), 0);
                    strecke tmp_s1 = s1;
                    tmp_s1.verschieben_um(i*bo.raster_x(), 0);
                    strecke tmp_s2 = s2;
                    tmp_s2.verschieben_um(i*bo.raster_x(), 0);
                    for(uint ii=0; ii<bo.anz_y() ;ii++)
                    {
                        kreis tmp_kk = tmp_k;
                        strecke tmp_s11 = tmp_s1;
                        strecke tmp_s22 = tmp_s2;
                        tmp_kk.verschieben_um(0, ii*bo.raster_y());
                        tmp_s11.verschieben_um(0, ii*bo.raster_y());
                        tmp_s22.verschieben_um(0, ii*bo.raster_y());
                        gt.add_kreis(tmp_kk);
                        gt.add_strecke(tmp_s11);
                        gt.add_strecke(tmp_s22);
                    }
                }
            }else if(bo.bezug() == WST_BEZUG_UNSEI)
            {
                kreis k;
                k.set_farbe(farbe_unterseite);
                k.set_radius(bo.dm()/2);
                k.set_mittelpunkt(bo.mipu());
                k.verschieben_um(versatz_x, versatz_y);
                if(bo.tiefe() > dicke())
                {
                    k.set_farbe_fuellung(FARBE_WEISS);
                }else
                {
                    k.set_farbe_fuellung(FARBE_HELLBLAU);
                }
                strecke s1;
                s1.set_farbe(k.farbe());
                s1.set_start(bo.x() - bo.dm()/2 - 2, bo.y(), bo.z());
                s1.set_ende( bo.x() + bo.dm()/2 + 2, bo.y(), bo.z());
                s1.drenen_um_mittelpunkt_2d(45, true);
                s1.verschieben_um(versatz_x, versatz_y);
                strecke s2 = s1;
                s2.drenen_um_mittelpunkt_2d(90, true);
                for(uint i=0; i<bo.anz_x() ;i++)
                {
                    kreis tmp_k = k;
                    tmp_k.verschieben_um(i*bo.raster_x(), 0);
                    strecke tmp_s1 = s1;
                    tmp_s1.verschieben_um(i*bo.raster_x(), 0);
                    strecke tmp_s2 = s2;
                    tmp_s2.verschieben_um(i*bo.raster_x(), 0);
                    for(uint ii=0; ii<bo.anz_y() ;ii++)
                    {
                        kreis tmp_kk = tmp_k;
                        strecke tmp_s11 = tmp_s1;
                        strecke tmp_s22 = tmp_s2;
                        tmp_kk.verschieben_um(0, ii*bo.raster_y());
                        tmp_s11.verschieben_um(0, ii*bo.raster_y());
                        tmp_s22.verschieben_um(0, ii*bo.raster_y());
                        gt.add_kreis(tmp_kk);
                        gt.add_strecke(tmp_s11);
                        gt.add_strecke(tmp_s22);
                    }
                }
            }else if(bo.bezug() == WST_BEZUG_LI)
            {
                rechteck3d r;
                r.set_farbe_fuellung(FARBE_BRAUN);
                r.set_laenge(bo.tiefe());
                r.set_breite(bo.dm());
                r.set_bezugspunkt(LINKS);
                r.set_einfuegepunkt(0, bo.y(), 0);
                r.verschieben_um(versatz_x, versatz_y);
                for(uint i=0; i<bo.anz_y() ;i++)
                {
                    rechteck3d tmp_r = r;
                    tmp_r.verschieben_um(0, i*bo.raster_y());
                    gt.add_rechteck(tmp_r);
                }
            }else if(bo.bezug() == WST_BEZUG_RE)
            {
                rechteck3d r;
                r.set_farbe_fuellung(FARBE_BRAUN);
                r.set_laenge(bo.tiefe());
                r.set_breite(bo.dm());
                r.set_bezugspunkt(RECHTS);
                r.set_einfuegepunkt(laenge(), bo.y(), 0);
                r.verschieben_um(versatz_x, versatz_y);
                for(uint i=0; i<bo.anz_y() ;i++)
                {
                    rechteck3d tmp_r = r;
                    tmp_r.verschieben_um(0, i*bo.raster_y());
                    gt.add_rechteck(tmp_r);
                }
            }else if(bo.bezug() == WST_BEZUG_VO)
            {
                rechteck3d r;
                r.set_farbe_fuellung(FARBE_BRAUN);
                r.set_laenge(bo.dm());
                r.set_breite(bo.tiefe());
                r.set_bezugspunkt(UNTEN);
                r.set_einfuegepunkt(bo.x(), 0, 0);
                r.verschieben_um(versatz_x, versatz_y);
                for(uint i=0; i<bo.anz_x() ;i++)
                {
                    rechteck3d tmp_r = r;
                    tmp_r.verschieben_um(i*bo.raster_x(), 0);
                    gt.add_rechteck(tmp_r);
                }
            }else if(bo.bezug() == WST_BEZUG_HI)
            {
                rechteck3d r;
                r.set_farbe_fuellung(FARBE_BRAUN);
                r.set_laenge(bo.dm());
                r.set_breite(bo.tiefe());
                r.set_bezugspunkt(OBEN);
                r.set_einfuegepunkt(bo.x(), breite(), 0);
                r.verschieben_um(versatz_x, versatz_y);
                for(uint i=0; i<bo.anz_x() ;i++)
                {
                    rechteck3d tmp_r = r;
                    tmp_r.verschieben_um(i*bo.raster_x(), 0);
                    gt.add_rechteck(tmp_r);
                }
            }
        }else if(zeile.zeile(1) == BEARBART_NUT)
        {
            nut nu(zeile.text());
            strecke s;
            s.set_start(nu.xs(), nu.ys(), 0);
            s.set_ende(nu.xe(), nu.ye(), 0);
            rechteck3d r;
            if(  (nu.bezug() == WST_BEZUG_OBSEI) ||  (nu.bezug() == WST_BEZUG_UNSEI)  )
            {
                if(nu.bezug() == WST_BEZUG_OBSEI)
                {
                    r.set_farbe_fuellung(FARBE_BLAU);
                }else
                {
                    r.set_farbe_fuellung(farbe_unterseite);
                    r.set_stil(STIL_GESTRICHELT);
                }
                r.set_laenge(s.laenge2d());
                r.set_breite(nu.breite());
                r.set_bezugspunkt(MITTE);
                r.set_einfuegepunkt(s.mitpu3d());
                r.set_drewi(s.wink());
                r.verschieben_um(versatz_x, versatz_y);
                gt.add_rechteck(r);
            }else
            {
                if(nu.bezug() == WST_BEZUG_LI)
                {
                    r.set_bezugspunkt(LINKS);
                    r.set_laenge(nu.tiefe());
                    r.set_breite(s.laenge2d());                    
                }else if(nu.bezug() == WST_BEZUG_RE)
                {
                    r.set_bezugspunkt(RECHTS);
                    r.set_laenge(nu.tiefe());
                    r.set_breite(s.laenge2d());
                }else if(nu.bezug() == WST_BEZUG_VO)
                {
                    r.set_bezugspunkt(UNTEN);
                    r.set_laenge(s.laenge2d());
                    r.set_breite(nu.tiefe());
                }else if(nu.bezug() == WST_BEZUG_HI)
                {
                    r.set_bezugspunkt(OBEN);
                    r.set_laenge(s.laenge2d());
                    r.set_breite(nu.tiefe());
                }
                r.set_farbe_fuellung(FARBE_GELB);
                r.set_einfuegepunkt(s.mitpu3d());
                r.verschieben_um(versatz_x, versatz_y);
                //Start anzeigen:
                strecke stmp = s;
                stmp.drenen_um_startpunkt_2d(90, true);
                stmp.set_laenge_2d(stmp.laenge2d()+nu.tiefe(), strecke_bezugspunkt_ende);
                stmp.set_laenge_2d(30, strecke_bezugspunkt_start);
                kreis k;
                k.set_mittelpunkt(stmp.endpu());
                k.set_radius(30);
                k.set_farbe(FARBE_GELB);
                gt.add_kreis(k);
                //---
                gt.add_rechteck(r);
            }
        }else if(zeile.zeile(1) == BEARBART_RTA)
        {
            rechtecktasche rt(zeile.text());
            rechteck3d r;
            if(  (rt.bezug() == WST_BEZUG_OBSEI) ||  (rt.bezug() == WST_BEZUG_UNSEI)  )
            {                
                r.set_bezugspunkt(MITTE);
                if(rt.tiefe() >= dicke())
                {
                    r.set_farbe_fuellung(FARBE_WEISS);
                }else
                {
                    if(rt.bezug() == WST_BEZUG_OBSEI)
                    {
                        r.set_farbe_fuellung(FARBE_DUNKELGRAU);
                    }else
                    {
                        r.set_farbe_fuellung(farbe_unterseite);
                        r.set_stil(STIL_GESTRICHELT);
                    }
                }
                r.set_laenge(rt.laenge());
                r.set_breite(rt.breite());
                r.set_mipu(rt.x(), rt.y(), rt.z());
                r.set_drewi(rt.drewi());
                r.verschieben_um(versatz_x, versatz_y);
                r.set_rad(rt.rad());
                gt.add_rechteck(r);
                if(rt.ausraeumen() == false)
                {
                    r.set_laenge(r.l()/8*5);
                    r.set_breite(r.b()/8*5);
                    r.set_farbe_fuellung(FARBE_WEISS);
                    gt.add_rechteck(r);
                }
            }else
            {                
                if(rt.bezug() == WST_BEZUG_LI)
                {
                    r.set_bezugspunkt(LINKS);
                    r.set_laenge(rt.breite());
                    r.set_breite(rt.laenge());
                }else if(rt.bezug() == WST_BEZUG_RE)
                {
                    r.set_bezugspunkt(RECHTS);
                    r.set_laenge(rt.breite());
                    r.set_breite(rt.laenge());
                }else if(rt.bezug() == WST_BEZUG_VO)
                {
                    r.set_bezugspunkt(UNTEN);
                    r.set_laenge(rt.laenge());
                    r.set_breite(rt.breite());
                }else if(rt.bezug() == WST_BEZUG_HI)
                {
                    r.set_bezugspunkt(OBEN);
                    r.set_laenge(rt.laenge());
                    r.set_breite(rt.breite());
                }
                r.set_farbe_fuellung(FARBE_GRUEN);
                r.set_einfuegepunkt(rt.x(), rt.y(), rt.z());
                r.verschieben_um(versatz_x, versatz_y);
                r.set_rad(rt.rad());
                gt.add_rechteck(r);
            }

        }else if(zeile.zeile(1) == BEARBART_FRAESERAUFRUF)
        {
            fraueseraufruf fa(zeile.text());
            punkt3d p(fa.x(), fa.y(), fa.z());
            p.set_linienbreite(10);
            p.verschieben_um(versatz_x, versatz_y);
            if(fa.bezug() == WST_BEZUG_OBSEI)
            {
                p.set_farbe(FARBE_DUNKELGRAU);
            }else
            {
                p.set_farbe(farbe_unterseite);
            }
            gt.add_punkt(p);
        }else if(zeile.zeile(1) == BEARBART_FRAESERGERADE)
        {
            fraesergerade fg(zeile.text());
            strecke s;
            s = fg.strecke_();
            s.verschieben_um(versatz_x, versatz_y);
            if(fg.bezug() == WST_BEZUG_OBSEI)
            {
                s.set_farbe(FARBE_DUNKELGRAU);
            }else
            {
                s.set_farbe(farbe_unterseite);
                s.set_stil(STIL_GESTRICHELT);
            }
            gt.add_strecke(s);
        }else if(zeile.zeile(1) == BEARBART_FRAESERBOGEN)
        {
            fraeserbogen fb(zeile.text());
            bogen b;
            b.set_startpunkt(fb.stapu());
            b.set_endpunkt(fb.endpu());
            if(fb.bezug() == WST_BEZUG_OBSEI)
            {
                b.set_radius(fb.rad(), fb.uzs());
                b.set_farbe(FARBE_DUNKELGRAU);
            }else
            {
                b.set_radius(fb.rad(), !fb.uzs());
                b.set_farbe(farbe_unterseite);
                b.set_stil(STIL_GESTRICHELT);
            }
            b.verschieben_um(versatz_x, versatz_y);
            gt.add_bogen(b);
        }
        gt.zeilenvorschub();
    }
    return gt;
}


