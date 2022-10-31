#include "einstellung_dxf_klassen.h"

einstellung_dxf_klassen::einstellung_dxf_klassen()
{

}

void einstellung_dxf_klassen::set_text(QString t)
{
    text_zeilenweise tz;
    tz.set_text(t);
    for(uint i=1;i<=tz.zeilenanzahl();i++)
    {
        text_zeilenweise spalten;
        spalten.set_trennzeichen('\t');
        spalten.set_text(tz.zeile(i));
        if(spalten.zeile(1) == "Wertkstueckklasse:")
        {
            set_wst(spalten.zeile(2));
        }
    }
}

QString einstellung_dxf_klassen::text()
{
    QString text;

    text += "Wertkstueckklasse:";
    text += "\t";
    text += wst();
    text += "\n";

    //text += "Wertkstueckklasse:";
    //text += "\t";
    //text += wst();
    //text += "\n";

    return text;
}

void einstellung_dxf_klassen::set_wst(QString wstklasse)
{
    Wst = wstklasse;
}

QString einstellung_dxf_klassen::wst()
{
    return Wst;
}

//-------------------Funktionen nicht innerhalb der Klasse:
bool operator ==(einstellung_dxf_klassen e1, einstellung_dxf_klassen e2)
{
    if(e1.wst() == e2.wst())
    {
        return true;
    }else
    {
        return false;
    }
}
bool operator !=(einstellung_dxf_klassen e1, einstellung_dxf_klassen e2)
{
    if(e1.wst() == e2.wst())
    {
        return false;
    }else
    {
        return true;
    }
}
