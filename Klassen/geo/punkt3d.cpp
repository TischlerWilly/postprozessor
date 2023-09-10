#include "punkt3d.h"

punkt3d::punkt3d()
{
    set_x(0);
    set_y(0);
    set_z(0);
}
punkt3d::punkt3d(QString geotext)
{
    set_text(geotext);
}

void punkt3d::set_text(QString geotext)
{
    text_zw tz;
    tz.set_text(geotext,TRZ_PA_);
    set_x(tz.at(1).toDouble());
    set_y(tz.at(2).toDouble());
    set_z(tz.at(3).toDouble());
    set_farbe(tz.at(4));
    set_linienbreite(tz.at(5).toInt());
}

void punkt3d::verschieben_um(double xversatz, double yversatz)
{
    X_param += xversatz;
    Y_param += yversatz;
}

//-------------------Funktionen nicht innerhalb der Klasse:
punkt3d operator +(punkt3d p1, punkt3d p2)
{
    punkt3d p3;
    p3.set_x(p1.x() + p2.x());
    p3.set_y(p1.y() + p2.y());
    p3.set_z(p1.z() + p2.z());
    return p3;
}

punkt3d operator -(punkt3d p1, punkt3d p2)
{
    punkt3d p3;
    p3.set_x(p1.x() - p2.x());
    p3.set_y(p1.y() - p2.y());
    p3.set_z(p1.z() - p2.z());
    return p3;
}

punkt3d operator *(punkt3d p1, double fakror)
{
    punkt3d p2;
    p2.set_x(p1.x() * fakror);
    p2.set_y(p1.y() * fakror);
    p2.set_z(p1.z() * fakror);
    return p2;
}

punkt3d operator *(double fakror, punkt3d p1)
{
    punkt3d p2;
    p2.set_x(p1.x() * fakror);
    p2.set_y(p1.y() * fakror);
    p2.set_z(p1.z() * fakror);
    return p2;
}

punkt3d operator /(punkt3d p1, double divisor)
{
    punkt3d p2;
    p2.set_x(p1.x() / divisor);
    p2.set_y(p1.y() / divisor);
    p2.set_z(p1.z() / divisor);
    return p2;
}

bool operator ==(punkt3d p1, punkt3d p2)
{
    bool returnbool = true;
    if(p1.x() != p2.x())
    {
        returnbool = false;
    }
    if(p1.y() != p2.y())
    {
        returnbool = false;
    }
    if(p1.z() != p2.z())
    {
        returnbool = false;
    }
    return returnbool;
}

bool operator !=(punkt3d p1, punkt3d p2)
{
    bool returnbool = true;
    if(p1.x() != p2.x())
    {
        returnbool = false;
    }
    if(p1.y() != p2.y())
    {
        returnbool = false;
    }
    if(p1.z() != p2.z())
    {
        returnbool = false;
    }
    if(returnbool == true)
    {
        return false;
    }else
    {
        return true;
    }
}







