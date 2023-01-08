#include "wkz_bohrer.h"

wkz_bohrer::wkz_bohrer()
{    
    IstAktiv        = true;
    DMimport        = 0;
    DMexport        = 0;
    Nutzlaenge      = 0;
    Zustellmass     = 0;
    IstDuBo         = false;    
    IstHori         = false;
    IstVerti        = false;
}
wkz_bohrer::wkz_bohrer(text_zw wkz)
{
    Wkznr       = wkz.at(1);
    if(wkz.at(2) == "1")
    {
        IstAktiv = true;
    }else
    {
        IstAktiv = false;
    }
    DMimport    = wkz.at(3).toDouble();
    DMexport    = wkz.at(4).toDouble();
    Nutzlaenge  = wkz.at(5).toDouble();
    Zustellmass = wkz.at(6).toDouble();
    if(wkz.at(7) == "1")
    {
        IstDuBo = true;
    }else
    {
        IstDuBo = false;
    }
    if(wkz.at(8) == "1")
    {
        IstHori = true;
    }else
    {
        IstHori = false;
    }
    if(wkz.at(9) == "1")
    {
        IstVerti = true;
    }else
    {
        IstVerti = false;
    }

}
//----------------------------------set:
void wkz_bohrer::set_wkznr(QString nr)
{
    Wkznr = nr;
}
void wkz_bohrer::set_istaktiv(bool ja)
{
    IstAktiv = ja;
}
void wkz_bohrer::set_dmimport(double dm)
{
    if(dm >= 0)
    {
        DMimport = dm;
    }
}
void wkz_bohrer::set_dmexport(double dm)
{
    if(dm >= 0)
    {
        DMexport = dm;
    }
}
void wkz_bohrer::set_nutzl(double n)
{
    if(n >= 0)
    {
        Nutzlaenge = n;
    }
}
void wkz_bohrer::set_zustma(double zm)
{
    if(zm >= 0)
    {
        Zustellmass = zm;
    }
}
void wkz_bohrer::set_istdubo(bool ja)
{
    IstDuBo = ja;
}
void wkz_bohrer::set_isthori(bool ja)
{
    IstHori = ja;
}
void wkz_bohrer::set_istverti(bool ja)
{
    IstVerti = ja;
}
//----------------------------------get:
text_zw wkz_bohrer::daten()
{
    text_zw wkz;
    wkz.set_trenz(WKZ_TRENNZ);
    wkz.add_hi(WKZ_TYP_BOHRER);                 //0: WKZ-Typ
    wkz.add_hi(Wkznr);                          //1: Werkzeugnummer
    if(IstAktiv == true)                        //2: Ist Aktiv
    {
        wkz.add_hi("1");
    }else
    {
        wkz.add_hi("0");
    }
    wkz.add_hi(double_to_qstring(DMimport));    //3: DM für den Import in den pp
    wkz.add_hi(double_to_qstring(DMexport));    //4: DM für den Export aus dem pp
    wkz.add_hi(double_to_qstring(Nutzlaenge));  //5: Nutzlänge
    wkz.add_hi(double_to_qstring(Zustellmass)); //6: Zustellmaß
    if(IstDuBo == true)                         //7: Ist Durchgangsbohrer
    {
        wkz.add_hi("1");
    }else
    {
        wkz.add_hi("0");
    }
    if(IstHori == true)                         //8: Ist Horizontalbohrer / kann horizontal bohren
    {
        wkz.add_hi("1");
    }else
    {
        wkz.add_hi("0");
    }
    if(IstVerti == true)                        //9: Ist Vertikalbohrer / kann vertikal bohren
    {
        wkz.add_hi("1");
    }else
    {
        wkz.add_hi("0");
    }
    return wkz;
}
QString wkz_bohrer::wkznr()
{
    return Wkznr;
}
bool wkz_bohrer::istaktiv()
{
    return IstAktiv;
}
double wkz_bohrer::dmimport()
{
    return DMimport;
}
double wkz_bohrer::dmexport()
{
    return DMexport;
}
double wkz_bohrer::nutzl()
{
    return Nutzlaenge;
}
double wkz_bohrer::zustma()
{
    return Zustellmass;
}
bool wkz_bohrer::istdubo()
{
    return IstDuBo;
}
bool wkz_bohrer::isthori()
{
    return IstHori;
}
bool wkz_bohrer::istverti()
{
    return IstVerti;
}




