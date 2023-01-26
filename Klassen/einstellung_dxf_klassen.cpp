#include "einstellung_dxf_klassen.h"

einstellung_dxf_klassen::einstellung_dxf_klassen()
{
    Wst             = "Werkstk";
    BohrVert        = "V_Bohr";
    BohrHori        = "H_Bohr";
    NutVert         = "V_Saeg";
    FraesVert       = "V_Fraes";
    Kta             = "F_Tasche";
    Rta             = "F_Tasche";
}

//--------------------------set_xy():
void einstellung_dxf_klassen::set_text(QString t)
{
    text_zw tz;
    tz.set_text(t,'\t');
    for(uint i=0;i<tz.count();i++)
    {
        text_zw spalten;
        spalten.set_text(tz.at(i),'\t');
        if(spalten.at(0) == "Wertkstueckklasse:")
        {
            set_wst(spalten.at(1));
        }
        if(spalten.at(0) == "Bohrung vertikal:")
        {
            set_bohr_vert(spalten.at(1));
        }
        if(spalten.at(0) == "Bohrung horizontal:")
        {
            set_bohr_hori(spalten.at(1));
        }
        if(spalten.at(0) == "Nut vertikal:")
        {
            set_nut_vert(spalten.at(1));
        }
        if(spalten.at(0) == "Kreistasche:")
        {
            set_kta(spalten.at(1));
        }
        if(spalten.at(0) == "Rechtecktasche:")
        {
            set_rta(spalten.at(1));
        }
        if(spalten.at(0) == "Fraeser vertikal:")
        {
            set_fraes_vert(spalten.at(1));
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

    text += "Bohrung horizontal:";
    text += "\t";
    text += bohr_hori();
    text += "\n";

    text += "Nut vertikal:";
    text += "\t";
    text += nut_vert();
    text += "\n";

    text += "Kreistasche:";
    text += "\t";
    text += kta();
    text += "\n";

    text += "Rechtecktasche:";
    text += "\t";
    text += rta();
    text += "\n";

    text += "Fraeser vertikal:";
    text += "\t";
    text += fraes_vert();
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
void einstellung_dxf_klassen::set_bohr_hori(QString klasse)
{
    BohrHori = klasse;
}
void einstellung_dxf_klassen::set_nut_vert(QString klasse)
{
    NutVert = klasse;
}
void einstellung_dxf_klassen::set_kta(QString klasse)
{
    Kta = klasse;
}
void einstellung_dxf_klassen::set_rta(QString klasse)
{
    Rta = klasse;
}
void einstellung_dxf_klassen::set_fraes_vert(QString klasse)
{
    FraesVert = klasse;
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
QString einstellung_dxf_klassen::bohr_hori()
{
    return BohrHori;
}
QString einstellung_dxf_klassen::nut_vert()
{
    return NutVert;
}
QString einstellung_dxf_klassen::kta()
{
    return Kta;
}
QString einstellung_dxf_klassen::rta()
{
    return Rta;
}
QString einstellung_dxf_klassen::fraes_vert()
{
    return FraesVert;
}

//-------------------Funktionen nicht innerhalb der Klasse:
bool operator ==(einstellung_dxf_klassen e1, einstellung_dxf_klassen e2)
{
    if(e1.wst() == e2.wst() &&\
       e1.bohr_vert() == e2.bohr_vert()&&\
       e1.bohr_hori() == e2.bohr_hori()&&\
       e1.nut_vert() == e2.nut_vert()&&\
       e1.kta() == e2.kta()&&\
       e1.rta() == e2.rta()&&\
       e1.fraes_vert() == e2.fraes_vert())
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
       e1.bohr_vert() == e2.bohr_vert()&&\
       e1.bohr_hori() == e2.bohr_hori()&&\
       e1.nut_vert() == e2.nut_vert()&&\
       e1.kta() == e2.kta()&&\
       e1.rta() == e2.rta()&&\
       e1.fraes_vert() == e2.fraes_vert())
    {
        return false;
    }else
    {
        return true;
    }
}
