#include "wkz_fraeser.h"

wkz_fraeser::wkz_fraeser()
{
    IstAktiv            = true;
    DM                  = 0;
    Nutzlaenge          = 0;
    Zustellmass         = 0;
    MinZust             = 0;
    Vorschub            = 0;
    NurDirektZuweisen   = true;
    IstHori             = false;
    IstVerti            = false;
}
wkz_fraeser::wkz_fraeser(text_zw wkz)
{
    Wkznr       = wkz.at(1);
    if(wkz.at(2) == "1")
    {
        IstAktiv = true;
    }else
    {
        IstAktiv = false;
    }
    DM          = wkz.at(3).toDouble();
    Nutzlaenge  = wkz.at(4).toDouble();
    Zustellmass = wkz.at(5).toDouble();
    MinZust     = wkz.at(6).toDouble();
    Vorschub    = wkz.at(7).toDouble();
    Alias       = wkz.at(8);
    Spiegelwkz  = wkz.at(9);
    if(wkz.at(10) == "1")
    {
        NurDirektZuweisen = true;
    }else
    {
        NurDirektZuweisen = false;
    }
    if(wkz.at(11) == "1")
    {
        IstHori = true;
    }else
    {
        IstHori = false;
    }
    if(wkz.at(12) == "1")
    {
        IstVerti = true;
    }else
    {
        IstVerti = false;
    }

}
//----------------------------------set:
void wkz_fraeser::set_wkznr(QString nr)
{
    Wkznr = nr;
}
void wkz_fraeser::set_istaktiv(bool ja)
{
    IstAktiv = ja;
}
void wkz_fraeser::set_dm(double dm)
{
    if(dm >= 0)
    {
        DM = dm;
    }
}
void wkz_fraeser::set_nutzl(double n)
{
    if(n >= 0)
    {
        Nutzlaenge = n;
    }
}
void wkz_fraeser::set_zustma(double zm)
{
    if(zm >= 0)
    {
        Zustellmass = zm;
    }
}
void wkz_fraeser::set_minzust(double mindestzustellung)
{
    if(mindestzustellung >= 0)
    {
        MinZust = mindestzustellung;
    }
}
void wkz_fraeser::set_vorschub(double vorschub)
{
    if(vorschub >= 0)
    {
        Vorschub = vorschub;
    }
}
void wkz_fraeser::set_alias(QString alias)
{
    Alias = alias;
}
void wkz_fraeser::set_spiegelwkz(QString wkz)
{
    Spiegelwkz = wkz;
}
void wkz_fraeser::set_nurdirektzuw(bool ja)
{
    NurDirektZuweisen = ja;
}
void wkz_fraeser::set_isthori(bool ja)
{
    IstHori = ja;
}
void wkz_fraeser::set_istverti(bool ja)
{
    IstVerti = ja;
}
//----------------------------------get:
text_zw wkz_fraeser::daten()
{
    text_zw wkz;
    wkz.set_trenz('\t');
    wkz.add_hi("M");                            //0: WKZ-Typ
    wkz.add_hi(Wkznr);                          //1: Werkzeugnummer
    if(IstAktiv == true)                        //2: Ist Aktiv
    {
        wkz.add_hi("1");
    }else
    {
        wkz.add_hi("0");
    }
    wkz.add_hi(double_to_qstring(DM));          //3: Durchmesser
    wkz.add_hi(double_to_qstring(Nutzlaenge));  //4: Nutzlänge
    wkz.add_hi(double_to_qstring(Zustellmass)); //5: Zustellmaß
    wkz.add_hi(double_to_qstring(MinZust));     //6: Mindest-Zustelltiefe
    wkz.add_hi(double_to_qstring(Vorschub));    //7: Vorschub
    wkz.add_hi(Alias);                          //8: Alias-Name
    wkz.add_hi(Spiegelwkz);                     //9: Siegelwerkzeug
    if(NurDirektZuweisen == true)               //10: Ist nur direkt Zuweisbar
    {
        wkz.add_hi("1");
    }else
    {
        wkz.add_hi("0");
    }
    if(IstHori == true)                         //11: Ist horizontaler Fräser / kann horizontal fräsen
    {
        wkz.add_hi("1");
    }else
    {
        wkz.add_hi("0");
    }
    if(IstVerti == true)                        //12: Ist vertikaler Fräser / kann vertikal fräsen
    {
        wkz.add_hi("1");
    }else
    {
        wkz.add_hi("0");
    }
    return wkz;
}
QString wkz_fraeser::wkznr()
{
    return Wkznr;
}
bool wkz_fraeser::istaktiv()
{
    return IstAktiv;
}
double wkz_fraeser::dm()
{
    return DM;
}
double wkz_fraeser::nutzl()
{
    return Nutzlaenge;
}
double wkz_fraeser::zustma()
{
    return Zustellmass;
}
double wkz_fraeser::vorschub()
{
    return Vorschub;
}
QString wkz_fraeser::alias()
{
    return Alias;
}
QString wkz_fraeser::spiegelwkz()
{
    return Spiegelwkz;
}
bool wkz_fraeser::nurdirektzuw()
{
    return NurDirektZuweisen;
}
bool wkz_fraeser::isthori()
{
    return IstHori;
}
bool wkz_fraeser::istverti()
{
    return IstVerti;
}

