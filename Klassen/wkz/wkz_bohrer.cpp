#include "wkz_bohrer.h"

wkz_bohrer::wkz_bohrer()
{    
    DMimport        = 0;
    DMexport        = 0;
    Nutzlaenge      = 0;
    Zustellmass     = 0;
    IstDuBo         = false;
    IstAktiv        = true;
}
wkz_bohrer::wkz_bohrer(text_zw wkz)
{
    Wkznr       = wkz.at(1);
    DMimport    = wkz.at(2).toDouble();
    DMexport    = wkz.at(3).toDouble();
    Nutzlaenge  = wkz.at(4).toDouble();
    Zustellmass = wkz.at(5).toDouble();
    if(wkz.at(6) == "1")
    {
        IstDuBo = true;
    }else
    {
        IstDuBo = false;
    }
    Lage        = wkz.at(7);
    if(wkz.at(8) == "1")
    {
        IstAktiv = true;
    }else
    {
        IstAktiv = false;
    }
}

//----------------------------------get:
text_zw wkz_bohrer::daten()
{
    text_zw wkz;
    wkz.set_trenz('\t');
    wkz.add_hi("B");                            //0: WKZ-Typ
    wkz.add_hi(Wkznr);                          //1: Werkzeugnummer
    wkz.add_hi(double_to_qstring(DMimport));    //2: DM für den Import in den pp
    wkz.add_hi(double_to_qstring(DMexport));    //3: DM für den Export aus dem pp
    wkz.add_hi(double_to_qstring(Nutzlaenge));  //4: Nutzlänge
    wkz.add_hi(double_to_qstring(Zustellmass)); //5: Zustellmaß
    if(IstDuBo == true)                         //6: Ist Durchgangsbohrer
    {
        wkz.add_hi("1");
    }else
    {
        wkz.add_hi("0");
    }
    wkz.add_hi(Lage);                           //7: Lage
    if(IstAktiv == true)                        //8: Ist Aktiv
    {
        wkz.add_hi("1");
    }else
    {
        wkz.add_hi("0");
    }
    return wkz;
}
