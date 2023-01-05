#include "text_zw.h"

text_zw::text_zw()
{
    clear();
}
text_zw::text_zw(QString text, char trennzeichen)
{
    set_text(text, trennzeichen);
}

//---------------------------------------------set_xy:
void text_zw::set_text(QString text, char trennzeichen)
{
    clear();
    Trennzeichen = trennzeichen;
    Daten = to_vector(text, trennzeichen);
}

//---------------------------------------------get_xy:
QString text_zw::zeile(uint zeilennummer)
{
    QString ret;
    if(zeilennummer < Daten.size())
    {
        ret = Daten.at(zeilennummer);
    }else
    {
        ret = "Fehler! Zeilennummer zu hoch.";
    }
    return ret;
}
QString text_zw::zeilen(uint zeilennummer_beginn, uint zeilenmenge)
{
    QString ret;
    uint zeilennummer_ende = zeilennummer_beginn + zeilenmenge - 1 ;
    if(zeilennummer_ende < Daten.size())
    {
        for(uint i=zeilennummer_beginn; i<=zeilennummer_ende ;i++)
        {
            ret += Daten.at(i);
            if(i < zeilennummer_ende)
            {
                ret += Trennzeichen;
            }
        }
    }else
    {
        ret = "Fehler! Zeilennummer + Menge > Wertebereich";
    }
    return ret;
}
QString text_zw::text()
{
    QString ret;
    for(uint i=0; i<Daten.size() ;i++)
    {
        ret += Daten.at(i);
        if(i+1 < Daten.size())
        {
            ret += Trennzeichen;
        }
    }
    return ret;
}
char text_zw::trennz()
{
    return Trennzeichen;
}
uint text_zw::count()
{
    return Daten.size();
}
//---------------------------------------------Manipulationen:
void text_zw::clear()
{
    Daten.clear();
    Trennzeichen = '\n';
}
//---------------------------------------------
void text_zw::add_before(QString text)
{
    if(Daten.empty())
    {
        Daten = to_vector(text, Trennzeichen);
    }else
    {
        std::vector<QString> v;
        v = to_vector(text, Trennzeichen);
        Daten.insert(Daten.begin(), v.begin(), v.end());
    }
}
void text_zw::add_after(QString text)
{
    if(Daten.empty())
    {
        Daten = to_vector(text, Trennzeichen);
    }else
    {
        std::vector<QString> v;
        v = to_vector(text, Trennzeichen);
        Daten.insert(Daten.end(), v.begin(), v.end());
    }
}

//--------------------------------------------------------------------------------------
//private:
std::vector<QString> text_zw::to_vector(QString text, char trennzeichen)
{
    std::vector<QString> v;
    if(text.contains(trennzeichen))
    {
        QString zeile;
        int letztes_trennzeichen = 0;
        for(int i=0; i<text.count() ;i++)
        {
            if(text.at(i) == trennzeichen)
            {
                v.push_back(zeile);
                zeile.clear();
                letztes_trennzeichen = i;
            }else
            {
                zeile += text.at(i);
            }
        }
        int anz_rest = text.count() - letztes_trennzeichen - 1;
        if(anz_rest > 0)
        {
            v.push_back(text.right(anz_rest));
        }
    }else
    {
        v.push_back(text);
    }
    return v;
}
