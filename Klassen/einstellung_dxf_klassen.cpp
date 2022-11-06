#include "einstellung_dxf_klassen.h"

einstellung_dxf_klassen::einstellung_dxf_klassen()
{
    Wst             = "Werkstk";
    BohrVert        = "V_Bohr";
}

//--------------------------set_xy():
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
        if(spalten.zeile(1) == "Bohrung vertikal:")
        {
            set_bohr_vert(spalten.zeile(2));
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

    text += "Bohrung vertikal:";
    text += "\t";
    text += bohr_vert();
    text += "\n";

    return text;
}

void einstellung_dxf_klassen::set_wst(QString wstklasse)
{
    Wst = wstklasse;
}
void einstellung_dxf_klassen::set_bohr_vert(QString klasse)
{
    BohrVert = klasse;
}

//--------------------------get_xy():
QString einstellung_dxf_klassen::wst()
{
    return Wst;
}
QString einstellung_dxf_klassen::bohr_vert()
{
    return BohrVert;
}

//-------------------Funktionen nicht innerhalb der Klasse:
bool operator ==(einstellung_dxf_klassen e1, einstellung_dxf_klassen e2)
{
    if(e1.wst() == e2.wst() &&\
       e1.bohr_vert() == e2.bohr_vert())
    {
        return true;
    }else
    {
        return false;
    }
}
bool operator !=(einstellung_dxf_klassen e1, einstellung_dxf_klassen e2)
{
    if(e1.wst() == e2.wst() &&\
       e1.bohr_vert() == e2.bohr_vert())
    {
        return false;
    }else
    {
        return true;
    }
}
