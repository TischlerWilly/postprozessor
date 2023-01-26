#include "zylinder.h"

zylinder::zylinder()
{
    set_mittelpunkt(0,0,0);
    set_radius(0);
    set_hoehe(0);
}
zylinder::zylinder(QString geotext)
{
    text_zw tz;
    tz.set_text(geotext,TRZ_PA_);
    punkt3d p;
    p.set_x(tz.at(1).toDouble());
    p.set_y(tz.at(2).toDouble());
    p.set_z(tz.at(3).toDouble());
    set_mittelpunkt(p);
    set_radius(tz.at(4).toDouble());
    set_hoehe(tz.at(5).toDouble());
    set_farbe(tz.at(6));
    set_farbe_fuellung(tz.at(7));
    set_linienbreite(tz.at(8).toInt());
    set_stil(tz.at(9));
}
