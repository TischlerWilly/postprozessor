#include "bogenac.h"

bogenac::bogenac()
{

}

//---------------------------------set:
void bogenac::set_text(QString geotext)
{
    text_zw tz;
    tz.set_text(geotext,TRZ_PA_);
    punkt3d p;
    p.set_x(tz.at(1).toDouble());
    p.set_y(tz.at(2).toDouble());
    p.set_z(tz.at(3).toDouble());
    set_mipu(p);
    set_rad(tz.at(4).toDouble());
    set_swi(tz.at(5).toDouble());
    set_ewi(tz.at(6).toDouble());
    set_farbe(tz.at(7));
    set_linienbreite(tz.at(8).toInt());
    set_stil(tz.at(9));
}
void bogenac::set_mipu(punkt3d p)
{
    Mipu = p;
}
void bogenac::set_rad(double rad)
{
    if(rad >= 0)
    {
        Rad = rad;
    }else
    {
        Rad = rad * -1;
    }

}
void bogenac::set_swi(double w)
{
    if(w < 0)
    {
        w = w+360;
    }
    Swi = w;
}
void bogenac::set_ewi(double w)
{
    if(w < 0)
    {
        w = w+360;
    }
    Ewi = w;
}

//---------------------------------get:
QString bogenac::text()
{
    QString msg = BOGENAC;
    msg += TRZ_PA;
    msg += Mipu.x_QString();
    msg += TRZ_PA;
    msg += Mipu.y_QString();
    msg += TRZ_PA;
    msg += Mipu.z_QString();
    msg += TRZ_PA;
    msg += rad_QString();
    msg += TRZ_PA;
    msg += swi_QString();
    msg += TRZ_PA;
    msg += ewi_QString();
    msg += farbe();
    msg += TRZ_PA;
    msg += linienbreite_qstring();
    msg += TRZ_PA;
    msg += stil();

    return msg;
}
punkt3d bogenac::mipu()
{
    return Mipu;
}
double bogenac::rad()
{
    return Rad;
}
QString bogenac::rad_QString()
{
    return double_to_qstring(rad());
}
double bogenac::swi()
{
    return Swi;
}
QString bogenac::swi_QString()
{
    return double_to_qstring(swi());
}
double bogenac::ewi()
{
    return Ewi;
}
QString bogenac::ewi_QString()
{
    return double_to_qstring(ewi());
}
punkt3d bogenac::spu()
{
    punkt3d p = mipu();
    p.verschieben_um(rad(),0);
    return drehen(mipu(), p, swi(), false);
}
punkt3d bogenac::epu()
{
    punkt3d p = mipu();
    p.verschieben_um(rad(),0);
    return drehen(mipu(), p, ewi(), false);
}
bool bogenac::im_uzs()
{
    if(swi() < ewi())
    {
        return false;
    }else
    {
        return true;
    }
}

//---------------------------------Manipulationen:
void bogenac::richtung_unkehren()
{
    double s = swi();
    double e = ewi();
    set_swi(e);
    set_ewi(s);
}






