#include "kreis.h"

kreis::kreis()
{
    set_mittelpunkt(0,0,0);
    set_radius(0);
}

kreis::kreis(QString geotext)
{
    set_text(geotext);
}

void kreis::set_text(QString geotext)
{
    text_zw tz;
    tz.set_text(geotext,TRZ_PA_);
    punkt3d p;
    p.set_x(tz.at(1).toDouble());
    p.set_y(tz.at(2).toDouble());
    p.set_z(tz.at(3).toDouble());
    set_mittelpunkt(p);
    set_radius(tz.at(4).toDouble());
    set_farbe(tz.at(5));
    set_farbe_fuellung(tz.at(6));
    set_linienbreite(tz.at(7).toInt());
    set_stil(tz.at(8));
}

void kreis::verschieben_um(double xversatz, double yversatz)
{
    Mittelp.verschieben_um(xversatz, yversatz);
}

QString kreis::text()
{
    QString msg = KREIS;
    msg += TRZ_PA;
    msg += Mittelp.x_QString();
    msg += TRZ_PA;
    msg += Mittelp.y_QString();
    msg += TRZ_PA;
    msg += Mittelp.z_QString();
    msg += TRZ_PA;
    msg += radius_QString();
    msg += TRZ_PA;
    msg += farbe();
    msg += TRZ_PA;
    msg += farbe_fuellung();
    msg += TRZ_PA;
    msg += linienbreite_qstring();
    msg += TRZ_PA;
    msg += stil();

    return msg;
}
