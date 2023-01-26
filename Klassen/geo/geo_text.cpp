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






