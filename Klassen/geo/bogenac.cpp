#include "bogenac.h"

bogenac::bogenac()
{

}

//---------------------------------set:
void bogenac::set_text(QString geotext)
{
    text_zeilenweise tz;
    tz.set_trennzeichen(TRZ_PA_);
    tz.set_text(geotext);
    punkt3d p;
    p.set_x(tz.zeile(2).toDouble());
    p.set_y(tz.zeile(3).toDouble());
    p.set_z(tz.zeile(4).toDouble());
    set_mipu(p);
    set_rad(tz.zeile(5).toDouble());
    set_swi(tz.zeile(6).toDouble());
    set_ewi(tz.zeile(7).toDouble());
    set_farbe(tz.zeile(8));
    set_linienbreite(tz.zeile(9).toInt());
    set_stil(tz.zeile(10));
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






