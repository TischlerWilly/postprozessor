#include "wkz_saege.h"

wkz_saege::wkz_saege()
{
    IstAktiv        = true;
    DM              = 0;
    Zustellmass     = 0;
    Schnittbreite   = 0;
    IstHori         = false;
    IstVerti        = false;
}
wkz_saege::wkz_saege(text_zw wkz)
{
    Wkznr           = wkz.at(1);
    if(wkz.at(2) == "1")
    {
        IstAktiv = true;
    }else
    {
        IstAktiv = false;
    }
    DM = wkz.at(3).toDouble();
    Zustellmass     = wkz.at(4).toDouble();
    Schnittbreite   = wkz.at(5).toDouble();
    if(wkz.at(6) == "1")
    {
        IstHori = true;
    }else
    {
        IstHori = false;
    }
    if(wkz.at(7) == "1")
    {
        IstVerti = true;
    }else
    {
        IstVerti = false;
    }
}
//----------------------------------set:
void wkz_saege::set_wkznr(QString nr)
{
    Wkznr = nr;
}
void wkz_saege::set_istaktiv(bool ja)
{
    IstAktiv = ja;
}
void wkz_saege::set_dm(double dm)
{
    if(dm >= 0)
    {
        DM = dm;
    }
}
void wkz_saege::set_zustma(double zm)
{
    if(zm >= 0)
    {
        Zustellmass = zm;
    }
}
void wkz_saege::set_sbreite(double schnittbreite)
{
    if(schnittbreite >= 0)
    {
        Schnittbreite = schnittbreite;
    }
}
void wkz_saege::set_isthori(bool ja)
{
    IstHori = ja;
}
void wkz_saege::set_istverti(bool ja)
{
    IstVerti = ja;
}
//----------------------------------get:
text_zw wkz_saege::daten()
{
    text_zw wkz;
    wkz.set_trenz(WKZ_TRENNZ);
    wkz.add_hi(WKZ_TYP_SAEGE);                      //0: WKZ-Typ
    wkz.add_hi(Wkznr);                              //1: Werkzeugnummer
    if(IstAktiv == true)                            //2: Ist Aktiv
    {
        wkz.add_hi("1");
    }else
    {
        wkz.add_hi("0");
    }
    wkz.add_hi(double_to_qstring(DM));              //3: Durchmesser
    wkz.add_hi(double_to_qstring(Zustellmass));     //4: Zustellmaß
    wkz.add_hi(double_to_qstring(Schnittbreite));   //5:Schnittbreite
    if(IstHori == true)                             //6: Ist horizontale Säge / kann horizontal sägen
    {
        wkz.add_hi("1");
    }else
    {
        wkz.add_hi("0");
    }
    if(IstVerti == true)                            //7: Ist vertikale Säge / kann vertikal sägen
    {
        wkz.add_hi("1");
    }else
    {
        wkz.add_hi("0");
    }
    return wkz;
}
QString wkz_saege::wkznr()
{
    return Wkznr;
}
bool wkz_saege::istaktiv()
{
    return IstAktiv;
}
double wkz_saege::dm()
{
    return DM;
}
double wkz_saege::zustma()
{
    return Zustellmass;
}
double wkz_saege::sbreite()
{
    return Schnittbreite;
}
bool wkz_saege::isthori()
{
    return IstHori;
}
bool wkz_saege::istverti()
{
    return IstVerti;
}





