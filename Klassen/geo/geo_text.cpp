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
                       double versatz_x, double versatz_y, wkz_magazin wkzm)
{
    double abst_darstel_hirnansicht = 20;
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
    //WST-Hirnseite vorne:
    punkt3d nullpunkt_vo(0,-abst_darstel_hirnansicht,0);
    nullpunkt_vo.set_linienbreite(10);
    gt.add_punkt(nullpunkt_vo);
    rechteck3d rec_vo;
    rec_vo.set_bezugspunkt(OBEN_LINKS);
    rec_vo.set_einfuegepunkt(nullpunkt_vo.x(),nullpunkt_vo.y(),0);
    rec_vo.set_laenge(wst_l);
    rec_vo.set_breite(wst_d);
    rec_vo.set_farbe_fuellung(FARBE_GRAU);
    gt.add_rechteck(rec_vo);
    //------------------------------
    //WST-Hirnseite hinten:
    punkt3d nullpunkt_hi(0,wst_b+versatz_y+abst_darstel_hirnansicht,0);
    nullpunkt_hi.set_linienbreite(10);
    gt.add_punkt(nullpunkt_hi);
    rechteck3d rec_hi;
    rec_hi.set_bezugspunkt(UNTEN_LINKS);
    rec_hi.set_einfuegepunkt(nullpunkt_hi.x(),nullpunkt_hi.y(),0);
    rec_hi.set_laenge(wst_l);
    rec_hi.set_breite(wst_d);
    rec_hi.set_farbe_fuellung(FARBE_GRAU);
    gt.add_rechteck(rec_hi);
    //------------------------------
    //WST-Hirnseite links:
    punkt3d nullpunkt_li(-abst_darstel_hirnansicht,versatz_y,0);
    nullpunkt_li.set_linienbreite(10);
    gt.add_punkt(nullpunkt_li);
    rechteck3d rec_li;
    rec_li.set_bezugspunkt(UNTEN_RECHTS);
    rec_li.set_einfuegepunkt(nullpunkt_li.x(),nullpunkt_li.y(),0);
    rec_li.set_laenge(wst_d);
    rec_li.set_breite(wst_b);
    rec_li.set_farbe_fuellung(FARBE_GRAU);
    gt.add_rechteck(rec_li);
    //------------------------------
    //WST-Hirnseite rechts:
    punkt3d nullpunkt_re(wst_l+versatz_x+abst_darstel_hirnansicht,versatz_y,0);
    nullpunkt_re.set_linienbreite(10);
    gt.add_punkt(nullpunkt_re);
    rechteck3d rec_re;
    rec_re.set_bezugspunkt(UNTEN_LINKS);
    rec_re.set_einfuegepunkt(nullpunkt_re.x(),nullpunkt_re.y(),0);
    rec_re.set_laenge(wst_d);
    rec_re.set_breite(wst_b);
    rec_re.set_farbe_fuellung(FARBE_GRAU);
    gt.add_rechteck(rec_re);
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
                kreis k;
                k.set_farbe_fuellung(FARBE_BRAUN);
                k.set_radius(bo.dm()/2);
                k.set_mittelpunkt(nullpunkt_li.x()-bo.z(),nullpunkt_li.y()+bo.y(), 0);
                gt.add_kreis(k);
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
                kreis k;
                k.set_farbe_fuellung(FARBE_BRAUN);
                k.set_radius(bo.dm()/2);
                k.set_mittelpunkt(nullpunkt_re.x()+bo.z(),nullpunkt_re.y()+bo.y(), 0);
                gt.add_kreis(k);
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
                kreis k;
                k.set_farbe_fuellung(FARBE_BRAUN);
                k.set_radius(bo.dm()/2);
                k.set_mittelpunkt(nullpunkt_vo.x()+bo.x(),nullpunkt_vo.y()-bo.z(), 0);
                gt.add_kreis(k);
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
                kreis k;
                k.set_farbe_fuellung(FARBE_BRAUN);
                k.set_radius(bo.dm()/2);
                k.set_mittelpunkt(nullpunkt_hi.x()+bo.x(),nullpunkt_hi.y()+bo.z(), 0);
                gt.add_kreis(k);
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
                kreis k;
                k.set_farbe_fuellung(FARBE_BRAUN);
                k.set_radius(bo.dm()/2);
                k.set_mittelpunkt(nullpunkt_li.x()-bo.z(),nullpunkt_li.y()+bo.y(), 0);
                for(uint i=0; i<bo.anz_y() ;i++)
                {
                    rechteck3d tmp_r = r;
                    tmp_r.verschieben_um(0, i*bo.raster_y());
                    gt.add_rechteck(tmp_r);
                    kreis tmp_k = k;
                    tmp_k.verschieben_um(0, i*bo.raster_y());
                    gt.add_kreis(tmp_k);
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
                kreis k;
                k.set_farbe_fuellung(FARBE_BRAUN);
                k.set_radius(bo.dm()/2);
                k.set_mittelpunkt(nullpunkt_re.x()+bo.z(),nullpunkt_re.y()+bo.y(), 0);
                for(uint i=0; i<bo.anz_y() ;i++)
                {
                    rechteck3d tmp_r = r;
                    tmp_r.verschieben_um(0, i*bo.raster_y());
                    gt.add_rechteck(tmp_r);
                    kreis tmp_k = k;
                    tmp_k.verschieben_um(0, i*bo.raster_y());
                    gt.add_kreis(tmp_k);
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
                kreis k;
                k.set_farbe_fuellung(FARBE_BRAUN);
                k.set_radius(bo.dm()/2);
                k.set_mittelpunkt(nullpunkt_vo.x()+bo.x(),nullpunkt_vo.y()-bo.z(), 0);
                for(uint i=0; i<bo.anz_x() ;i++)
                {
                    rechteck3d tmp_r = r;
                    tmp_r.verschieben_um(i*bo.raster_x(), 0);
                    gt.add_rechteck(tmp_r);
                    kreis tmp_k = k;
                    tmp_k.verschieben_um(i*bo.raster_x(), 0);
                    gt.add_kreis(tmp_k);
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
                kreis k;
                k.set_farbe_fuellung(FARBE_BRAUN);
                k.set_radius(bo.dm()/2);
                k.set_mittelpunkt(nullpunkt_hi.x()+bo.x(),nullpunkt_hi.y()+bo.z(), 0);
                for(uint i=0; i<bo.anz_x() ;i++)
                {
                    rechteck3d tmp_r = r;
                    tmp_r.verschieben_um(i*bo.raster_x(), 0);
                    gt.add_rechteck(tmp_r);
                    kreis tmp_k = k;
                    tmp_k.verschieben_um(i*bo.raster_x(), 0);
                    gt.add_kreis(tmp_k);
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
            double wkzdm = wkzm.dm(rt.wkznum()).toDouble();
            double eckenrad;
            if(wkzdm > rt.rad())
            {
                eckenrad = wkzdm/2;
            }else
            {
                eckenrad = rt.rad();
            }

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
                r.set_rad(eckenrad);
                gt.add_rechteck(r);
                if(rt.ausraeumen() == false)
                {
                    r.set_laenge(r.l()-wkzdm);
                    r.set_breite(r.b()-wkzdm);
                    r.set_rad(eckenrad-wkzdm/2);
                    r.set_farbe_fuellung(FARBE_GRAU);
                    gt.add_rechteck(r);
                }
            }else
            {
                rechteck3d r_kantenansicht;
                if(rt.bezug() == WST_BEZUG_LI)
                {
                    r.set_bezugspunkt(LINKS);
                    r.set_laenge(rt.tiefe());
                    r.set_breite(rt.laenge());
                    r_kantenansicht.set_laenge(rt.breite());
                    r_kantenansicht.set_breite(rt.laenge());
                    r_kantenansicht.set_mipu(nullpunkt_li.x()-rt.z(),nullpunkt_li.y()+rt.y(), 0);
                }else if(rt.bezug() == WST_BEZUG_RE)
                {
                    r.set_bezugspunkt(RECHTS);
                    r.set_laenge(rt.tiefe());
                    r.set_breite(rt.laenge());
                    r_kantenansicht.set_laenge(rt.breite());
                    r_kantenansicht.set_breite(rt.laenge());
                    r_kantenansicht.set_mipu(nullpunkt_re.x()+rt.z(),nullpunkt_re.y()+rt.y(), 0);
                }else if(rt.bezug() == WST_BEZUG_VO)
                {
                    r.set_bezugspunkt(UNTEN);
                    r.set_laenge(rt.laenge());
                    r.set_breite(rt.tiefe());
                    r_kantenansicht.set_laenge(rt.laenge());
                    r_kantenansicht.set_breite(rt.breite());
                    r_kantenansicht.set_mipu(nullpunkt_vo.x()+rt.x(),nullpunkt_vo.y()-rt.z(), 0);
                }else if(rt.bezug() == WST_BEZUG_HI)
                {
                    r.set_bezugspunkt(OBEN);
                    r.set_laenge(rt.laenge());
                    r.set_breite(rt.tiefe());
                    r_kantenansicht.set_laenge(rt.laenge());
                    r_kantenansicht.set_breite(rt.breite());
                    r_kantenansicht.set_mipu(nullpunkt_hi.x()+rt.x(),nullpunkt_hi.y()+rt.z(), 0);
                }
                r.set_farbe_fuellung(FARBE_GRUEN);
                r.set_einfuegepunkt(rt.x(), rt.y(), rt.z());
                r.verschieben_um(versatz_x, versatz_y);
                //r.set_rad(rt.rad()); //hier darf nicht der rad gesetzt werden weil Draufsicht
                gt.add_rechteck(r);
                r_kantenansicht.set_rad(eckenrad);
                r_kantenansicht.set_farbe_fuellung(r.farbe_fuellung());
                r_kantenansicht.set_farbe(r.farbe());
                gt.add_rechteck(r_kantenansicht);
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
        }else if(zeile.at(0) == BEARBART_GEHRUNG)
        {
            gehrung ge(zeile.text());
            strecke s;
            s.set_stapu(ge.stapu());
            s.set_endpu(ge.endpu());
            s.verschieben_um(versatz_x, versatz_y);
            s.set_stil(STIL_GEPUNKTET);
            gt.add_strecke(s);
        }
        gt.zeilenvorschub();
    }

    return gt;
}
geo_text geofkon_ermitteln(text_zw bearb, double versatz_x, double versatz_y, wkz_magazin wkzm)
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
    fraeseraufruf letzter_fa;
    for(uint i=0; i<bearb.count() ;i++)
    {
        text_zw zeile;
        zeile.set_text(bearb.at(i),TRENNZ_BEARB_PARAM);
        if(zeile.at(0) == BEARBART_FRAESERAUFRUF)
        {
            fraeseraufruf fa(zeile.text());
            letzter_fa = fa;//wird gebraucht für die Berechnung der Abfahrwege
            radkor = fa.radkor();
            gt.add_leerzeile();
            QString wkznr = fa.wkznum();
            fraeserdm = wkzm.dm(wkznr).toDouble();
            if(i+1 < bearb.count())
            {
                double anweg;
                if(fa.anfahrweg_qstring() == FAUFRUF_ANABWEG_AUTO)
                {
                    anweg = fraeserdm;
                }else
                {
                    anweg = fa.anfahrweg();
                }
                text_zw folzei;//Folgezeile
                folzei.set_text(bearb.at(i+1),TRENNZ_BEARB_PARAM);
                punkt3d pfa;//Punkt Fräseraufruf
                pfa.set_x(fa.x());
                pfa.set_y(fa.y());
                punkt3d pein;//Eintauchpunkt
                if(folzei.at(0) == BEARBART_FRAESERGERADE)
                {
                    fraesergerade fg(folzei.text());
                    if(fa.anfahrtyp() == FAUFRUF_ANABTYP_GARADE)
                    {
                        strecke s = fg.strecke_();
                        strecke_bezugspunkt sb;
                        sb = strecke_bezugspunkt_ende;
                        s.set_laenge_2d(s.laenge2d()+anweg, sb);
                        sb = strecke_bezugspunkt_start;
                        s.set_laenge_2d(anweg, sb);
                        if(fa.bezug() == WST_BEZUG_OBSEI)
                        {
                            s.set_farbe(FARBE_BLAU);
                        }else
                        {
                            s.set_farbe(farbe_unterseite);
                            s.set_stil(STIL_GESTRICHELT);
                        }
                        s.verschieben_um(versatz_x, versatz_y);
                        gt.add_strecke(s);
                    }else if(fa.anfahrtyp() == FAUFRUF_ANABTYP_BOGEN)
                    {
                        bogen b;
                        //Hilfs-Strecke:
                        strecke s = fg.strecke_();
                        strecke_bezugspunkt sb;
                        sb = strecke_bezugspunkt_ende;
                        s.set_laenge_2d(s.laenge2d()+anweg, sb);
                        sb = strecke_bezugspunkt_start;
                        s.set_laenge_2d(anweg, sb);
                        //---
                        if(fa.bezug() == WST_BEZUG_OBSEI)
                        {
                            b.set_farbe(FARBE_BLAU);
                            if(fa.radkor() == FRKOR_L)
                            {
                                s.drenen_um_endpu_2d(90, true);
                                s.drenen_um_stapu_2d(90, true);
                                b.set_startpunkt(s.endpu());
                                b.set_endpunkt(fa.pos());
                                b.set_radius(anweg, false);
                            }else if(fa.radkor() == FRKOR_R)
                            {
                                s.drenen_um_endpu_2d(90, false);
                                s.drenen_um_stapu_2d(90, false);
                                b.set_startpunkt(s.endpu());
                                b.set_endpunkt(fa.pos());
                                b.set_radius(anweg, true);
                            }
                        }else
                        {
                            b.set_farbe(farbe_unterseite);
                            b.set_stil(STIL_GESTRICHELT);
                            if(fa.radkor() == FRKOR_L)
                            {
                                s.drenen_um_endpu_2d(90, false);
                                s.drenen_um_stapu_2d(90, false);
                                b.set_startpunkt(s.endpu());
                                b.set_endpunkt(fa.pos());
                                b.set_radius(anweg, true);
                            }else if(fa.radkor() == FRKOR_R)
                            {
                                s.drenen_um_endpu_2d(90, true);
                                s.drenen_um_stapu_2d(90, true);
                                b.set_startpunkt(s.endpu());
                                b.set_endpunkt(fa.pos());
                                b.set_radius(anweg, false);
                            }
                        }
                        b.verschieben_um(versatz_x, versatz_y);
                        gt.add_bogen(b);
                    }
                }else if(folzei.at(0) == BEARBART_FRAESERBOGEN)
                {
                    fraeserbogen fb(folzei.text());
                    if(fa.anfahrtyp() == FAUFRUF_ANABTYP_GARADE)
                    {
                        strecke s;
                        s.set_stapu(fb.bog().mitte());
                        s.set_endpu(fb.bog().start());
                        strecke_bezugspunkt sb;
                        sb = strecke_bezugspunkt_ende;
                        s.set_laenge_2d(anweg, sb);
                        if(fa.bezug() == WST_BEZUG_OBSEI)
                        {
                            s.set_farbe(FARBE_BLAU);
                            s.drenen_um_endpu_2d(90, fb.bog().im_uzs());
                        }else
                        {
                            s.set_farbe(farbe_unterseite);
                            s.set_stil(STIL_GESTRICHELT);
                            s.drenen_um_endpu_2d(180, true);
                        }
                        s.verschieben_um(versatz_x, versatz_y);
                        gt.add_strecke(s);
                    }else if(fa.anfahrtyp() == FAUFRUF_ANABTYP_BOGEN)
                    {
                        bogen b;                       
                        if(fa.bezug() == WST_BEZUG_OBSEI)
                        {
                            strecke s;
                            s.set_stapu(fb.bog().mitte());
                            s.set_endpu(fb.stapu());
                            strecke_bezugspunkt sb;
                            sb = strecke_bezugspunkt_ende;
                            s.set_laenge_2d(anweg, sb);
                            b.set_farbe(FARBE_BLAU);
                            s.drenen_um_endpu_2d(90, fb.bog().im_uzs());
                            if(fa.radkor() == FRKOR_L)
                            {
                                if(fb.bog().im_uzs())
                                {
                                    s.drenen_um_endpu_2d(90, true);
                                    s.drenen_um_stapu_2d(90, true);
                                    b.set_startpunkt(s.endpu());
                                    b.set_endpunkt(fa.pos());
                                    b.set_radius(anweg, false);
                                }else
                                {
                                    s.drenen_um_stapu_2d(90, fb.uzs());
                                    b.set_startpunkt(s.endpu());
                                    b.set_endpunkt(fa.pos());
                                    b.set_radius(anweg, false);
                                }
                            }else if(fa.radkor() == FRKOR_R)
                            {
                                if(fb.bog().im_uzs())
                                {
                                    s.drenen_um_endpu_2d(90, false);
                                    s.drenen_um_stapu_2d(90, false);
                                    b.set_startpunkt(s.endpu());
                                    b.set_endpunkt(fa.pos());
                                    b.set_radius(anweg, true);
                                }else
                                {
                                    s.drenen_um_stapu_2d(90, true);
                                    b.set_startpunkt(s.endpu());
                                    b.set_endpunkt(fa.pos());
                                    b.set_radius(anweg, true);
                                }
                            }
                        }else
                        {
                            strecke s;
                            s.set_stapu(fb.bog().mitte());
                            s.set_endpu(fb.endpu());
                            strecke_bezugspunkt sb;
                            sb = strecke_bezugspunkt_ende;
                            s.set_laenge_2d(anweg, sb);
                            strecke sehne;
                            sehne.set_stapu(fb.stapu());
                            sehne.set_endpu(fb.endpu());
                            punkt3d strecke_sp = drehen(sehne.mipu(), s.stapu(), (double)180, true);
                            punkt3d strecke_ep = drehen(sehne.mipu(), s.endpu(), (double)180, true);
                            s.set_stapu(strecke_sp);
                            s.set_endpu(strecke_ep);
                            b.set_farbe(farbe_unterseite);
                            b.set_stil(STIL_GESTRICHELT);
                            if(fa.radkor() == FRKOR_L)
                            {
                                if(fb.bog().im_uzs())
                                {
                                    s.drenen_um_endpu_2d(180, true);
                                    s.drenen_um_stapu_2d(90, false);
                                    b.set_startpunkt(s.endpu());
                                    b.set_endpunkt(fa.pos());
                                    b.set_radius(anweg, true);
                                }else
                                {
                                    s.drenen_um_stapu_2d(90, false);
                                    b.set_startpunkt(s.endpu());
                                    b.set_endpunkt(fa.pos());
                                    b.set_radius(anweg, true);
                                }
                            }else if(fa.radkor() == FRKOR_R)
                            {
                                if(fb.bog().im_uzs())
                                {
                                    s.drenen_um_stapu_2d(90, true);
                                    b.set_startpunkt(s.endpu());
                                    b.set_endpunkt(fa.pos());
                                    b.set_radius(anweg, false);
                                }else
                                {
                                    s.drenen_um_endpu_2d(180, false);
                                    s.drenen_um_stapu_2d(90, true);
                                    b.set_startpunkt(s.endpu());
                                    b.set_endpunkt(fa.pos());
                                    b.set_radius(anweg, false);
                                }
                            }
                        }
                        b.verschieben_um(versatz_x, versatz_y);
                        gt.add_bogen(b);
                    }
                }
            }
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
            //Abfahrweg:
            double abweg;
            if(letzter_fa.abfahrweg_qstring() == FAUFRUF_ANABWEG_AUTO)
            {
                abweg = fraeserdm;
            }else
            {
                abweg = letzter_fa.abfahrweg();
            }
            bool ist_konturende = false;
            if(i+1 == bearb.count())
            {
                ist_konturende = true;
            }
            if(i+1 < bearb.count())
            {
                text_zw folzei;//Folgezeile
                folzei.set_text(bearb.at(i+1),TRENNZ_BEARB_PARAM);
                if(folzei.at(0) != BEARBART_FRAESERGERADE  &&  folzei.at(0) != BEARBART_FRAESERBOGEN)
                {
                    ist_konturende = true;
                }
            }
            if(ist_konturende == true)
            {
                if(letzter_fa.abfahrtyp() == FAUFRUF_ANABTYP_GARADE)
                {
                    strecke s = fg.strecke_();
                    strecke_bezugspunkt sb;
                    sb = strecke_bezugspunkt_start;
                    s.set_laenge_2d(s.laenge2d()+abweg, sb);
                    sb = strecke_bezugspunkt_ende;
                    s.set_laenge_2d(abweg, sb);
                    if(letzter_fa.bezug() == WST_BEZUG_OBSEI)
                    {
                        s.set_farbe(FARBE_BLAU);
                    }else
                    {
                        s.set_farbe(farbe_unterseite);
                        s.set_stil(STIL_GESTRICHELT);
                    }
                    s.verschieben_um(versatz_x, versatz_y);
                    gt.add_strecke(s);
                }else if(letzter_fa.abfahrtyp() == FAUFRUF_ANABTYP_BOGEN)
                {
                    bogen b;
                    //Hilfs-Strecke:
                    strecke s = fg.strecke_();
                    strecke_bezugspunkt sb;
                    sb = strecke_bezugspunkt_start;
                    s.set_laenge_2d(s.laenge2d()+abweg, sb);
                    sb = strecke_bezugspunkt_ende;
                    s.set_laenge_2d(abweg, sb);
                    //---
                    if(letzter_fa.bezug() == WST_BEZUG_OBSEI)
                    {
                        b.set_farbe(FARBE_BLAU);
                        if(letzter_fa.radkor() == FRKOR_L)
                        {
                            s.drenen_um_endpu_2d(90, true);
                            s.drenen_um_stapu_2d(90, true);
                            b.set_startpunkt(fg.ep());
                            b.set_endpunkt(s.stapu());
                            b.set_radius(abweg, false);
                        }else if(letzter_fa.radkor() == FRKOR_R)
                        {
                            s.drenen_um_endpu_2d(90, false);
                            s.drenen_um_stapu_2d(90, false);
                            b.set_startpunkt(fg.ep());
                            b.set_endpunkt(s.stapu());
                            b.set_radius(abweg, true);
                        }
                    }else
                    {
                        b.set_farbe(farbe_unterseite);
                        b.set_stil(STIL_GESTRICHELT);
                        if(letzter_fa.radkor() == FRKOR_L)
                        {
                            s.drenen_um_endpu_2d(90, false);
                            s.drenen_um_stapu_2d(90, false);
                            b.set_startpunkt(fg.ep());
                            b.set_endpunkt(s.stapu());
                            b.set_radius(abweg, true);
                        }else if(letzter_fa.radkor() == FRKOR_R)
                        {
                            s.drenen_um_endpu_2d(90, true);
                            s.drenen_um_stapu_2d(90, true);
                            b.set_startpunkt(fg.ep());
                            b.set_endpunkt(s.stapu());
                            b.set_radius(abweg, false);
                        }
                    }
                    b.verschieben_um(versatz_x, versatz_y);
                    gt.add_bogen(b);
                }
            }
        }else if(zeile.at(0) == BEARBART_FRAESERBOGEN)
        {
            fraeserbogen fb(zeile.text());
            bogen b = fb.bog();
            b.verschieben_um(versatz_x, versatz_y);
            kreis k;
            k.set_radius(fraeserdm/2);
            if(fb.bezug() == WST_BEZUG_OBSEI)
            {
                k.set_farbe(FARBE_BLAU);
            }else
            {
                b.set_radius(b.rad(), !b.im_uzs());
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
                if(fb.bezug() == WST_BEZUG_OBSEI)
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
                }else if(fb.bezug() == WST_BEZUG_UNSEI)
                {
                    if(radkor == FRKOR_R)
                    {
                        if(b.im_uzs())
                        {
                            s.set_laenge_2d(b.rad()+fraeserdm/2, strecke_bezugspunkt_start);
                        }else
                        {
                            s.set_laenge_2d(b.rad()-fraeserdm/2, strecke_bezugspunkt_start);
                        }
                    }else //if(radkor == FRKOR_L)
                    {
                        if(b.im_uzs())
                        {
                            s.set_laenge_2d(b.rad()-fraeserdm/2, strecke_bezugspunkt_start);
                        }else
                        {
                            s.set_laenge_2d(b.rad()+fraeserdm/2, strecke_bezugspunkt_start);
                        }
                    }
                }

                k.set_mittelpunkt(s.endpu());
            }
            gt.add_kreis(k);
            //Abfahrweg:
            double abweg;
            if(letzter_fa.abfahrweg_qstring() == FAUFRUF_ANABWEG_AUTO)
            {
                abweg = fraeserdm;
            }else
            {
                abweg = letzter_fa.abfahrweg();
            }
            bool ist_konturende = false;
            if(i+1 == bearb.count())
            {
                ist_konturende = true;
            }
            if(i+1 < bearb.count())
            {
                text_zw folzei;//Folgezeile
                folzei.set_text(bearb.at(i+1),TRENNZ_BEARB_PARAM);
                if(folzei.at(0) != BEARBART_FRAESERGERADE  &&  folzei.at(0) != BEARBART_FRAESERBOGEN)
                {
                    ist_konturende = true;
                }
            }
            if(ist_konturende == true)
            {
                if(letzter_fa.abfahrtyp() == FAUFRUF_ANABTYP_GARADE)
                {
                    strecke s;
                    s.set_stapu(fb.bog().ende());
                    s.set_endpu(fb.bog().mitte());
                    strecke_bezugspunkt sb;
                    sb = strecke_bezugspunkt_start;
                    s.set_laenge_2d(abweg, sb);
                    if(letzter_fa.bezug() == WST_BEZUG_OBSEI)
                    {
                        s.set_farbe(FARBE_BLAU);
                        s.drenen_um_stapu_2d(90, !fb.bog().im_uzs());
                    }else
                    {
                        s.set_farbe(farbe_unterseite);
                        s.set_stil(STIL_GESTRICHELT);
                        s.drenen_um_stapu_2d(180, true);
                    }
                    s.verschieben_um(versatz_x, versatz_y);
                    gt.add_strecke(s);
                }else if(letzter_fa.anfahrtyp() == FAUFRUF_ANABTYP_BOGEN)
                {
                    bogen b;                    
                    if(letzter_fa.bezug() == WST_BEZUG_OBSEI)
                    {
                        s.set_stapu(fb.bog().ende());
                        s.set_endpu(fb.bog().mitte());
                        strecke_bezugspunkt sb;
                        sb = strecke_bezugspunkt_start;
                        s.set_laenge_2d(abweg, sb);
                        b.set_farbe(FARBE_BLAU);
                        s.drenen_um_stapu_2d(90, !fb.bog().im_uzs());
                        s.drenen_um_endpu_2d(90, !fb.bog().im_uzs());
                        if(letzter_fa.radkor() == FRKOR_L)
                        {
                            if(fb.bog().im_uzs())
                            {
                                s.drenen_um_endpu_2d(180, false);
                            }
                            b.set_startpunkt(fb.endpu());
                            b.set_endpunkt(s.stapu());
                            b.set_radius(abweg, false);
                        }else if(letzter_fa.radkor() == FRKOR_R)
                        {
                            if(!fb.bog().im_uzs())
                            {
                                s.drenen_um_endpu_2d(180, false);
                            }
                            b.set_startpunkt(fb.endpu());
                            b.set_endpunkt(s.stapu());
                            b.set_radius(abweg, true);
                        }
                    }else
                    {
                        s.set_stapu(fb.bog().start());
                        s.set_endpu(fb.bog().mitte());
                        strecke sehne;
                        sehne.set_stapu(fb.stapu());
                        sehne.set_endpu(fb.endpu());
                        punkt3d strecke_sp = drehen(sehne.mipu(), s.stapu(), (double)180, true);
                        punkt3d strecke_ep = drehen(sehne.mipu(), s.endpu(), (double)180, true);
                        s.set_stapu(strecke_sp);
                        s.set_endpu(strecke_ep);
                        strecke_bezugspunkt sb;
                        sb = strecke_bezugspunkt_start;
                        s.set_laenge_2d(abweg, sb);
                        b.set_farbe(farbe_unterseite);
                        b.set_stil(STIL_GESTRICHELT);
                        if(letzter_fa.radkor() == FRKOR_L)
                        {
                            if(fb.uzs())
                            {
                                s.drenen_um_stapu_2d(90, fb.bog().im_uzs());
                                s.drenen_um_endpu_2d(90, !fb.bog().im_uzs());
                                b.set_startpunkt(fb.endpu());
                                b.set_endpunkt(s.stapu());
                                b.set_radius(abweg, fb.bog().im_uzs());
                            }else
                            {
                                s.drenen_um_endpu_2d(90, !fb.bog().im_uzs());
                                b.set_startpunkt(fb.endpu());
                                b.set_endpunkt(s.stapu());
                                b.set_radius(abweg, !fb.bog().im_uzs());
                            }
                        }else if(letzter_fa.radkor() == FRKOR_R)
                        {
                            if(fb.uzs())
                            {
                                s.drenen_um_endpu_2d(90, !fb.bog().im_uzs());
                                b.set_startpunkt(fb.endpu());
                                b.set_endpunkt(s.stapu());
                                b.set_radius(abweg, !fb.bog().im_uzs());
                            }else
                            {
                                s.drenen_um_stapu_2d(90, fb.bog().im_uzs());
                                s.drenen_um_endpu_2d(90, !fb.bog().im_uzs());
                                b.set_startpunkt(fb.endpu());
                                b.set_endpunkt(s.stapu());
                                b.set_radius(abweg, fb.bog().im_uzs());
                            }
                        }
                    }
                    b.verschieben_um(versatz_x, versatz_y);
                    gt.add_bogen(b);
                }
            }
        }else
        {
            gt.add_leerzeile();
        }
        gt.zeilenvorschub();
    }
    return gt;
}




