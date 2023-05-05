#include "geo_text.h"

geo_text::geo_text()
{
    clear();
}

void geo_text::clear()
{
    Daten.clear();
    AktIndex = 0;
    Zeivor = false;
}
void geo_text::zeilenvorschub()
{
    Zeivor = true;
}
//--------------------------------------set:
void geo_text::add(text_zw geometrie, uint index)
{
    text_zw geometrieen;
    geometrieen.set_trenz(TRZ_EL_);
    if(Zeivor == true)
    {
        //Zeile hinten anhängen:
        geometrieen.add_hi(geometrie.text());
        Daten.push_back(geometrieen);
        AktIndex++;
        Zeivor = false;
    }else
    {
        if(index + 1 > Daten.size())
        {
            //Zeile hinten anhängen:
            geometrieen.add_hi(geometrie.text());
            Daten.push_back(geometrieen);
        }else
        {
            //Zeile verlängern
            geometrieen = Daten.at(index);
            geometrieen.add_hi(geometrie.text());
            Daten.at(index) = geometrieen;
        }
    }
}
void geo_text::add_leerzeile()
{
    text_zw geo;
    geo.set_text("leerzeile", TRZ_PA_);
    add(geo, akt_index());
}
void geo_text::add_punkt(punkt3d p)
{
    add_punkt(p, AktIndex);
}
void geo_text::add_punkt(punkt3d p, uint index)
{
    text_zw geo;
    geo.set_trenz(TRZ_PA_);
    geo.add_hi(PUNKT);
    geo.add_hi(p.x_QString());
    geo.add_hi(p.y_QString());
    geo.add_hi(p.z_QString());
    geo.add_hi(p.farbe());
    geo.add_hi(p.linienbreite_qstring());
    add(geo, index);
}
void geo_text::add_strecke(strecke s)
{
    add_strecke(s, AktIndex);
}
void geo_text::add_strecke(strecke s, uint index)
{
    text_zw geo;
    geo.set_trenz(TRZ_PA_);
    geo.add_hi(STRECKE);
    geo.add_hi(s.stapu().x_QString());
    geo.add_hi(s.stapu().y_QString());
    geo.add_hi(s.stapu().z_QString());
    geo.add_hi(s.endpu().x_QString());
    geo.add_hi(s.endpu().y_QString());
    geo.add_hi(s.endpu().z_QString());
    geo.add_hi(s.farbe());
    geo.add_hi(s.linienbreite_qstring());
    geo.add_hi(s.stil());
    add(geo, index);
}
void geo_text::add_bogen(bogen b)
{
    add_bogen(b, AktIndex);
}
void geo_text::add_bogen(bogen b, uint index)
{
    text_zw geo;
    geo.set_trenz(TRZ_PA_);
    geo.add_hi(BOGEN);
    geo.add_hi(b.start().x_QString());
    geo.add_hi(b.start().y_QString());
    geo.add_hi(b.start().z_QString());
    geo.add_hi(b.ende().x_QString());
    geo.add_hi(b.ende().y_QString());
    geo.add_hi(b.ende().z_QString());
    geo.add_hi(b.rad_qString());
    geo.add_hi(b.im_uzs_QString());
    geo.add_hi(b.mitte().x_QString());
    geo.add_hi(b.mitte().y_QString());
    geo.add_hi(b.farbe());
    geo.add_hi(b.linienbreite_qstring());
    geo.add_hi(b.stil());
    add(geo, index);
}
void geo_text::add_kreis(kreis k)
{
    add_kreis(k, AktIndex);
}
void geo_text::add_kreis(kreis k, uint index)
{
    text_zw geo;
    geo.set_trenz(TRZ_PA_);
    geo.add_hi(KREIS);
    geo.add_hi(k.mitte3d().x_QString());
    geo.add_hi(k.mitte3d().y_QString());
    geo.add_hi(k.mitte3d().z_QString());
    geo.add_hi(k.radius_QString());
    geo.add_hi(k.farbe());
    geo.add_hi(k.farbe_fuellung());
    geo.add_hi(k.linienbreite_qstring());
    geo.add_hi(k.stil());
    add(geo, index);
}
void geo_text::add_zylinder(zylinder z)
{
    add_zylinder(z, AktIndex);
}
void geo_text::add_zylinder(zylinder z, uint index)
{
    text_zw geo;
    geo.set_trenz(TRZ_PA_);
    geo.add_hi(ZYLINDER);
    geo.add_hi(z.mitte3d().x_QString());
    geo.add_hi(z.mitte3d().y_QString());
    geo.add_hi(z.mitte3d().z_QString());
    geo.add_hi(z.radius_QString());
    geo.add_hi(z.hoehe_qstring());
    geo.add_hi(z.farbe());
    geo.add_hi(z.farbe_fuellung());
    geo.add_hi(z.linienbreite_qstring());
    geo.add_hi(z.stil());
    add(geo, index);
}
void geo_text::add_rechteck(rechteck3d rec)
{
    add_rechteck(rec, AktIndex);
}
void geo_text::add_rechteck(rechteck3d rec, uint index)
{
    text_zw geo;
    geo.set_trenz(TRZ_PA_);
    geo.add_hi(RECHTECK3D);
    geo.add_hi(rec.bezpunkt_num_qstring());
    geo.add_hi(rec.einfpunkt().x_QString());
    geo.add_hi(rec.einfpunkt().y_QString());
    geo.add_hi(rec.einfpunkt().z_QString());
    geo.add_hi(rec.l_qstring());
    geo.add_hi(rec.b_qstring());
    geo.add_hi(rec.rad_qstring());
    geo.add_hi(rec.drewi_qstring());
    geo.add_hi(rec.farbe());
    geo.add_hi(rec.farbe_fuellung());
    geo.add_hi(rec.linienbreite_qstring());
    geo.add_hi(rec.stil());
    add(geo, index);
}
void geo_text::add_wuerfel(wuerfel w)
{
    add_wuerfel(w, AktIndex);
}
void geo_text::add_wuerfel(wuerfel w, uint index)
{
    text_zw geo;
    geo.set_trenz(TRZ_PA_);
    geo.add_hi(WUERFEL);
    geo.add_hi(w.bezpunkt_num_qstring());
    geo.add_hi(w.einfpunkt().x_QString());
    geo.add_hi(w.einfpunkt().y_QString());
    geo.add_hi(w.einfpunkt().z_QString());
    geo.add_hi(w.l_qstring());
    geo.add_hi(w.b_qstring());
    geo.add_hi(w.rad_qstring());
    geo.add_hi(w.drewi_qstring());
    geo.add_hi(w.hoehe_qstring());
    geo.add_hi(w.farbe());
    geo.add_hi(w.farbe_fuellung());
    geo.add_hi(w.linienbreite_qstring());
    geo.add_hi(w.stil());
    add(geo, index);
}
//--------------------------------------get:
uint geo_text::akt_index()
{
    return AktIndex;
}
uint geo_text::count()
{
    return Daten.size();
}
text_zw geo_text::at()
{
    return at(AktIndex);
}
text_zw geo_text::at(uint index)
{
    text_zw ret;
    if(index < Daten.size())
    {
        ret = Daten.at(index);
    }else
    {
        ret.set_text("Fehler in Funktion geo_text::at(...)! Zeilennummer zu hoch.",'\n');
    }
    return ret;
}
//--------------------------------------
//Funktionen außerhalb der Klasse:
geo_text geo_ermitteln(text_zw bearb, double wst_l, double wst_b, double wst_d, \
                       QString kante_v, QString kante_h, QString kante_l, QString kante_r, \
                       double versatz_x, double versatz_y)
{
    //-------------------------------------------
    geo_text gt;
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
    rec.set_laenge(wst_l);
    rec.set_breite(wst_b);
    rec.set_farbe_fuellung(FARBE_GRAU);
    gt.add_rechteck(rec);
    //------------------------------
    //Kanten darstellen:
    strecke skante;
    skante.set_linienbreite(5);
    if(!kante_v.isEmpty())
    {
        punkt3d sp(0,0,0);
        punkt3d ep(wst_l,0,0);
        skante.set_stapu(sp);
        skante.set_endpu(ep);
        skante.verschieben_um(versatz_x, versatz_y);
        gt.add_strecke(skante);
    }
    if(!kante_h.isEmpty())
    {
        punkt3d sp(0,wst_b,0);
        punkt3d ep(wst_l,wst_b,0);
        skante.set_stapu(sp);
        skante.set_endpu(ep);
        skante.verschieben_um(versatz_x, versatz_y);
        gt.add_strecke(skante);
    }
    if(!kante_l.isEmpty())
    {
        punkt3d sp(0,0,0);
        punkt3d ep(0,wst_b,0);
        skante.set_stapu(sp);
        skante.set_endpu(ep);
        skante.verschieben_um(versatz_x, versatz_y);
        gt.add_strecke(skante);
    }
    if(!kante_r.isEmpty())
    {
        punkt3d sp(wst_l,0,0);
        punkt3d ep(wst_l,wst_b,0);
        skante.set_stapu(sp);
        skante.set_endpu(ep);
        skante.verschieben_um(versatz_x, versatz_y);
        gt.add_strecke(skante);
    }
    //------------------------------
    gt.zeilenvorschub();
    //------------------------------
    //Bearbeitungen darstellen:
    QString farbe_unterseite = FARBE_ROSE;
    for(uint i=0; i<bearb.count() ;i++)
    {
        text_zw zeile;
        zeile.set_text(bearb.at(i),TRENNZ_BEARB_PARAM);
        if(zeile.at(0) == BEARBART_BOHR)
        {
            bohrung bo(zeile.text());
            if(bo.bezug() == WST_BEZUG_OBSEI)
            {
                kreis k;
                k.set_farbe(FARBE_SCHWARZ);
                k.set_radius(bo.dm()/2);
                k.set_mittelpunkt(bo.mipu());
                k.verschieben_um(versatz_x, versatz_y);
                if(bo.tiefe() > wst_d)
                {
                    k.set_farbe_fuellung(FARBE_WEISS);
                }else
                {
                    k.set_farbe_fuellung(FARBE_HELLBLAU);
                }
                gt.add_kreis(k);
                strecke s;
                s.set_farbe(k.farbe());
                s.set_stapu(bo.x() - bo.dm()/2 - 2, bo.y(), bo.z());
                s.set_endpu(bo.x() + bo.dm()/2 + 2, bo.y(), bo.z());
                s.verschieben_um(versatz_x, versatz_y);
                gt.add_strecke(s);
                s.drenen_um_mipu_2d(90, true);
                gt.add_strecke(s);
            }else if(bo.bezug() == WST_BEZUG_UNSEI)
            {
                kreis k;
                k.set_farbe(farbe_unterseite);
                k.set_radius(bo.dm()/2);
                k.set_mittelpunkt(bo.mipu());
                if(bo.tiefe() > wst_d)
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
                s.set_stapu(bo.x() - bo.dm()/2 - 2, bo.y(), bo.z());
                s.set_endpu(bo.x() + bo.dm()/2 + 2, bo.y(), bo.z());
                s.drenen_um_mipu_2d(45, true);
                s.verschieben_um(versatz_x, versatz_y);
                gt.add_strecke(s);
                s.drenen_um_mipu_2d(90, true);
                gt.add_strecke(s);
            }else if(bo.bezug() == WST_BEZUG_LI)
            {
                rechteck3d r;
                r.set_farbe_fuellung(FARBE_BRAUN);
                r.set_laenge(bo.tiefe());
                r.set_breite(bo.dm());
                r.set_bezugspunkt(LINKS);
                r.set_einfuegepunkt(bo.x(), bo.y(), 0);
                r.verschieben_um(versatz_x, versatz_y);
                gt.add_rechteck(r);
            }else if(bo.bezug() == WST_BEZUG_RE)
            {
                rechteck3d r;
                r.set_farbe_fuellung(FARBE_BRAUN);
                r.set_laenge(bo.tiefe());
                r.set_breite(bo.dm());
                r.set_bezugspunkt(RECHTS);
                r.set_einfuegepunkt(bo.x(), bo.y(), 0);
                r.verschieben_um(versatz_x, versatz_y);
                gt.add_rechteck(r);
            }else if(bo.bezug() == WST_BEZUG_VO)
            {
                rechteck3d r;
                r.set_farbe_fuellung(FARBE_BRAUN);
                r.set_laenge(bo.dm());
                r.set_breite(bo.tiefe());
                r.set_bezugspunkt(UNTEN);
                r.set_einfuegepunkt(bo.x(), bo.y(), 0);
                r.verschieben_um(versatz_x, versatz_y);
                gt.add_rechteck(r);
            }else if(bo.bezug() == WST_BEZUG_HI)
            {
                rechteck3d r;
                r.set_farbe_fuellung(FARBE_BRAUN);
                r.set_laenge(bo.dm());
                r.set_breite(bo.tiefe());
                r.set_bezugspunkt(OBEN);
                r.set_einfuegepunkt(bo.x(), bo.y(), 0);
                r.verschieben_um(versatz_x, versatz_y);
                gt.add_rechteck(r);
            }
        }else if(zeile.at(0) == BEARBART_BOHRRASTER)
        {
            bohrraster bo(zeile.text());
            if(bo.bezug() == WST_BEZUG_OBSEI)
            {
                kreis k;
                k.set_farbe(FARBE_SCHWARZ);
                k.set_radius(bo.dm()/2);
                k.set_mittelpunkt(bo.mipu());
                k.verschieben_um(versatz_x, versatz_y);
                if(bo.tiefe() > wst_d)
                {
                    k.set_farbe_fuellung(FARBE_WEISS);
                }else
                {
                    k.set_farbe_fuellung(FARBE_HELLBLAU);
                }
                strecke s1;
                s1.set_farbe(k.farbe());
                s1.set_stapu(bo.x() - bo.dm()/2 - 2, bo.y(), bo.z());
                s1.set_endpu(bo.x() + bo.dm()/2 + 2, bo.y(), bo.z());
                s1.verschieben_um(versatz_x, versatz_y);
                strecke s2 = s1;
                s2.drenen_um_mipu_2d(90, true);
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
                if(bo.tiefe() > wst_d)
                {
                    k.set_farbe_fuellung(FARBE_WEISS);
                }else
                {
                    k.set_farbe_fuellung(FARBE_HELLBLAU);
                }
                strecke s1;
                s1.set_farbe(k.farbe());
                s1.set_stapu(bo.x() - bo.dm()/2 - 2, bo.y(), bo.z());
                s1.set_endpu(bo.x() + bo.dm()/2 + 2, bo.y(), bo.z());
                s1.drenen_um_mipu_2d(45, true);
                s1.verschieben_um(versatz_x, versatz_y);
                strecke s2 = s1;
                s2.drenen_um_mipu_2d(90, true);
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
                r.set_einfuegepunkt(wst_l, bo.y(), 0);
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
                r.set_einfuegepunkt(bo.x(), wst_b, 0);
                r.verschieben_um(versatz_x, versatz_y);
                for(uint i=0; i<bo.anz_x() ;i++)
                {
                    rechteck3d tmp_r = r;
                    tmp_r.verschieben_um(i*bo.raster_x(), 0);
                    gt.add_rechteck(tmp_r);
                }
            }
        }else if(zeile.at(0) == BEARBART_NUT)
        {
            nut nu(zeile.text());
            strecke s;
            s.set_stapu(nu.xs(), nu.ys(), 0);
            s.set_endpu(nu.xe(), nu.ye(), 0);
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
                r.set_einfuegepunkt(s.mipu());
                r.set_drewi(s.wink());
                r.verschieben_um(versatz_x, versatz_y);
                gt.add_rechteck(r);
            }else
            {
                if(nu.bezug() == WST_BEZUG_LI)
                {
                    r.set_laenge(nu.tiefe());
                    r.set_breite(s.laenge2d());
                    r.set_drewi(0);
                }else if(nu.bezug() == WST_BEZUG_RE)
                {
                    r.set_laenge(nu.tiefe());
                    r.set_breite(s.laenge2d());
                    r.set_drewi(0);
                }else if(nu.bezug() == WST_BEZUG_VO)
                {
                    r.set_laenge(s.laenge2d());
                    r.set_breite(nu.tiefe());
                    r.set_drewi(0);
                }else if(nu.bezug() == WST_BEZUG_HI)
                {
                    r.set_laenge(s.laenge2d());
                    r.set_breite(nu.tiefe());
                    r.set_drewi(0);
                }
                r.set_farbe_fuellung(FARBE_GELB);
                punkt3d mipu = s.mipu();
                r.set_bezugspunkt(MITTE);
                strecke s_mipu;
                s_mipu.set_stapu(mipu);
                s_mipu.set_endpu(s.endpu());
                s_mipu.set_laenge_2d(nu.tiefe()/2, strecke_bezugspunkt_start);
                s_mipu.drenen_um_stapu_2d(90, false);
                mipu = s_mipu.endpu();
                r.set_einfuegepunkt(mipu);
                r.verschieben_um(versatz_x, versatz_y);
                //Start anzeigen:
                strecke stmp = s;
                stmp.drenen_um_stapu_2d(90, true);
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
        }else if(zeile.at(0) == BEARBART_RTA)
        {
            rechtecktasche rt(zeile.text());
            rechteck3d r;
            if(  (rt.bezug() == WST_BEZUG_OBSEI) ||  (rt.bezug() == WST_BEZUG_UNSEI)  )
            {
                r.set_bezugspunkt(MITTE);
                if(rt.tiefe() >= wst_d)
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
                    r.set_laenge(rt.tiefe());
                    r.set_breite(rt.laenge());
                }else if(rt.bezug() == WST_BEZUG_RE)
                {
                    r.set_bezugspunkt(RECHTS);
                    r.set_laenge(rt.tiefe());
                    r.set_breite(rt.laenge());
                }else if(rt.bezug() == WST_BEZUG_VO)
                {
                    r.set_bezugspunkt(UNTEN);
                    r.set_laenge(rt.laenge());
                    r.set_breite(rt.tiefe());
                }else if(rt.bezug() == WST_BEZUG_HI)
                {
                    r.set_bezugspunkt(OBEN);
                    r.set_laenge(rt.laenge());
                    r.set_breite(rt.tiefe());
                }
                r.set_farbe_fuellung(FARBE_GRUEN);
                r.set_einfuegepunkt(rt.x(), rt.y(), rt.z());
                r.verschieben_um(versatz_x, versatz_y);
                //r.set_rad(rt.rad()); //hier darf nicht der rad gesetzt werden weil Draufsicht
                gt.add_rechteck(r);
            }

        }else if(zeile.at(0) == BEARBART_FRAESERAUFRUF)
        {
            fraeseraufruf fa(zeile.text());
            punkt3d p(fa.x(), fa.y(), fa.z());
            p.set_linienbreite(10);
            p.verschieben_um(versatz_x, versatz_y);
            if(fa.bezug() == WST_BEZUG_OBSEI)
            {
                p.set_farbe(FARBE_BLAU);
            }else
            {
                p.set_farbe(farbe_unterseite);
            }
            gt.add_punkt(p);
        }else if(zeile.at(0) == BEARBART_FRAESERGERADE)
        {
            fraesergerade fg(zeile.text());
            strecke s;
            s = fg.strecke_();
            s.verschieben_um(versatz_x, versatz_y);
            if(fg.bezug() == WST_BEZUG_OBSEI)
            {
                s.set_farbe(FARBE_BLAU);
            }else
            {
                s.set_farbe(farbe_unterseite);
                s.set_stil(STIL_GESTRICHELT);
            }
            gt.add_strecke(s);
        }else if(zeile.at(0) == BEARBART_FRAESERBOGEN)
        {
            fraeserbogen fb(zeile.text());
            bogen b;
            b.set_startpunkt(fb.stapu());
            b.set_endpunkt(fb.endpu());
            if(fb.bezug() == WST_BEZUG_OBSEI)
            {
                b.set_radius(fb.rad(), fb.uzs());
                b.set_farbe(FARBE_BLAU);
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
geo_text geofkon_ermitteln(text_zw bearb, double versatz_x, double versatz_y)
{
    //-------------------------------------------
    geo_text gt;
    gt.add_leerzeile();//Werkstück
    gt.zeilenvorschub();
    //------------------------------
    //fkon darstellen:
    QString radkor;
    double fraeserdm = 10;
    QString farbe_unterseite = FARBE_ROSE;
    for(uint i=0; i<bearb.count() ;i++)
    {
        text_zw zeile;
        zeile.set_text(bearb.at(i),TRENNZ_BEARB_PARAM);
        if(zeile.at(0) == BEARBART_FRAESERAUFRUF)
        {
            fraeseraufruf fa(zeile.text());
            radkor = fa.radkor();
            gt.add_leerzeile();
        }else if(zeile.at(0) == BEARBART_FRAESERGERADE)
        {
            fraesergerade fg(zeile.text());
            strecke s;
            s = fg.strecke_();
            s.verschieben_um(versatz_x, versatz_y);
            kreis k;
            if(fg.bezug() == WST_BEZUG_OBSEI)
            {
                k.set_farbe(FARBE_BLAU);
            }else
            {
                k.set_farbe(farbe_unterseite);
                k.set_stil(STIL_GESTRICHELT);
            }
            k.set_radius(fraeserdm/2);
            if(radkor == FRKOR_M)
            {
                k.set_mittelpunkt(s.mipu());
            }else
            {
                strecke stmp = s;
                stmp.drenen_um_mipu_2d(90, true);
                stmp.set_laenge_2d(fraeserdm, strecke_bezugspunkt_mitte);
                if(radkor == FRKOR_L)
                {
                    if(fg.bezug() == WST_BEZUG_OBSEI)
                    {
                        k.set_mittelpunkt(stmp.stapu());
                    }else
                    {
                        k.set_mittelpunkt(stmp.endpu());
                    }
                }else //if(radkor == FRKOR_R)
                {
                    if(fg.bezug() == WST_BEZUG_OBSEI)
                    {
                        k.set_mittelpunkt(stmp.endpu());
                    }else
                    {
                        k.set_mittelpunkt(stmp.stapu());
                    }
                }
            }
            gt.add_kreis(k);
        }else if(zeile.at(0) == BEARBART_FRAESERBOGEN)
        {
            fraeserbogen fb(zeile.text());
            bogen b;
            b.set_startpunkt(fb.stapu());
            b.set_endpunkt(fb.endpu());
            b.verschieben_um(versatz_x, versatz_y);
            kreis k;
            k.set_radius(fraeserdm/2);
            if(fb.bezug() == WST_BEZUG_OBSEI)
            {
                b.set_radius(fb.rad(), fb.uzs());
                k.set_farbe(FARBE_BLAU);
            }else
            {
                b.set_radius(fb.rad(), !fb.uzs());
                k.set_farbe(farbe_unterseite);
                k.set_stil(STIL_GESTRICHELT);
            }
            strecke sehne;
            sehne.set_stapu(b.start());
            sehne.set_endpu(b.ende());
            strecke s;
            s.set_stapu(b.mitte());
            s.set_endpu(sehne.mipu2d());
            if(radkor == FRKOR_M)
            {
                s.set_laenge_2d(b.rad(), strecke_bezugspunkt_start);
                k.set_mittelpunkt(s.endpu());
            }else
            {
                if(radkor == FRKOR_L)
                {
                    if(b.im_uzs())
                    {
                        s.set_laenge_2d(b.rad()+fraeserdm/2, strecke_bezugspunkt_start);
                    }else
                    {
                        s.set_laenge_2d(b.rad()-fraeserdm/2, strecke_bezugspunkt_start);
                    }
                }else //if(radkor == FRKOR_R)
                {
                    if(b.im_uzs())
                    {
                        s.set_laenge_2d(b.rad()-fraeserdm/2, strecke_bezugspunkt_start);
                    }else
                    {
                        s.set_laenge_2d(b.rad()+fraeserdm/2, strecke_bezugspunkt_start);
                    }
                }
                k.set_mittelpunkt(s.endpu());
            }
            gt.add_kreis(k);
        }else
        {
            gt.add_leerzeile();
        }
        gt.zeilenvorschub();
    }
    return gt;
}




