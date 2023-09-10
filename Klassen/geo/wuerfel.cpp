#include "wuerfel.h"

wuerfel::wuerfel()
{
    set_bezugspunkt(MITTE);
    set_einfuegepunkt(0,0,0);
    set_laenge(0);
    set_breite(0);
    set_rad(0);
    set_drewi(0);
    set_hoehe(0);
}
wuerfel::wuerfel(QString geotext)
{
    set_text(geotext);
}

void wuerfel::set_text(QString geotext)
{
    text_zw tz;
    tz.set_text(geotext,TRZ_PA_);
    set_bezugspunkt(tz.at(1).toInt());
    punkt3d p;
    p.set_x(tz.at(2).toDouble());
    p.set_y(tz.at(3).toDouble());
    p.set_z(tz.at(4).toDouble());
    set_einfuegepunkt(p);
    set_laenge(tz.at(5).toDouble());
    set_breite(tz.at(6).toDouble());
    set_rad(tz.at(7).toDouble());
    set_drewi(tz.at(8).toDouble());
    set_hoehe(tz.at(9).toDouble());
    set_farbe(tz.at(10));
    set_farbe_fuellung(tz.at(11));
    set_linienbreite(tz.at(12).toInt());
    set_stil(tz.at(13));
}
