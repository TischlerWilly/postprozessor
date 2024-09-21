#include "einstellung_fmc.h"

einstellung_fmc::einstellung_fmc()
{
    KennungOberseite        = "_H";
    KennungUnterseite       = "_N";
    DrehtypUnterseite       = "L";
}
void einstellung_fmc::set_text(QString t)
{
    text_zw tz;
    tz.set_text(t,'\n');
    for(uint i=0;i<tz.count();i++)
    {
        text_zw spalten;
        spalten.set_text(tz.at(i),'\t');
        if(spalten.at(0) == "Kennung Oberseite:")
        {
            set_kenObsei(spalten.at(1));
        }
        if(spalten.at(0) == "Kennung Unterseite:")
        {
            set_kenUnsei(spalten.at(1));
        }
        if(spalten.at(0) == "Drehtyp Unterseite:")
        {
            set_dretypUnsei(spalten.at(1));
        }
    }
}
QString einstellung_fmc::text()
{
    QString text;

    text += "Kennung Oberseite:";
    text += "\t";
    text += kenObsei();
    text += "\n";

    text += "Kennung Unterseite:";
    text += "\t";
    text += kenUnsei();
    text += "\n";

    text += "Drehtyp Unterseite:";
    text += "\t";
    text += drehtypUnsei();
    text += "\n";

    return text;
}
//--------------------------------------------set:
void einstellung_fmc::set_kenObsei(QString kennung_oberseite)
{
    KennungOberseite = kennung_oberseite;
}
void einstellung_fmc::set_kenUnsei(QString kennung_unterseite)
{
    KennungUnterseite = kennung_unterseite;
}
void einstellung_fmc::set_dretypUnsei(QString drehtyp)
{
    DrehtypUnterseite = drehtyp;
}

//--------------------------------------------get:QString text();
QString einstellung_fmc::kenObsei()
{
    return KennungOberseite;
}
QString einstellung_fmc::kenUnsei()
{
    return KennungUnterseite;
}
QString einstellung_fmc::drehtypUnsei()
{
    return DrehtypUnterseite;
}
bool einstellung_fmc::drehtyp_L()
{
    if(drehtypUnsei() == "L")
    {
        return true;
    }else
    {
        return false;
    }
}
bool einstellung_fmc::drehtyp_B()
{
    if(drehtypUnsei() == "B")
    {
        return true;
    }else
    {
        return false;
    }
}


//-------------------Funktionen nicht innerhalb der Klasse:
bool operator ==(einstellung_fmc e1, einstellung_fmc e2)
{
    if(e1.text() == e2.text())
    {
        return true;
    }else
    {
        return false;
    }
}
bool operator !=(einstellung_fmc e1, einstellung_fmc e2)
{
    if(e1.text() == e2.text())
    {
        return false;
    }else
    {
        return true;
    }
}

