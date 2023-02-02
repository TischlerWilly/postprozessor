#include "einstellung_dxf.h"

einstellung_dxf::einstellung_dxf()
{
    Paramtren               = "_";
    Dezitren                = "_";
    KennungOberseite        = "_1";
    KennungUnterseite       = "_2";
    DrehtypUnterseite       = "B";
    KennungWKZnr            = "T";
    KennungRadKorLi         = "L";
    KennungRadKorMi         = "N";
    KennungRadKorRe         = "R";
    BezugTiFkon             = "Unterseite Bauteil";
}
void einstellung_dxf::set_text(QString t)
{
    text_zw tz;
    tz.set_text(t,'\n');
    for(uint i=0;i<tz.count();i++)
    {
        text_zw spalten;
        spalten.set_text(tz.at(i),'\t');
        if(spalten.at(0) == "Parametertrenner:")
        {
            set_paramtren(spalten.at(1));
        }
        if(spalten.at(0) == "Dezimaltrenner:")
        {
            set_dezitren(spalten.at(1));
        }
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
        if(spalten.at(0) == "Kennung Werkzeugnummer:")
        {
            set_kenWKZnr(spalten.at(1));
        }
        if(spalten.at(0) == "Kennung Radiuskorrektur li:")
        {
            set_kenRadKorLi(spalten.at(1));
        }
        if(spalten.at(0) == "Kennung Radiuskorrektur mi:")
        {
            set_kenRadKorMi(spalten.at(1));
        }
        if(spalten.at(0) == "Kennung Radiuskorrektur re:")
        {
            set_kenRadKorRe(spalten.at(1));
        }
        if(spalten.at(0) == "Tiefenangabe Fraeskontur:")
        {
            set_bezugTiFkon(spalten.at(1));
        }
    }
}
QString einstellung_dxf::text()
{
    QString text;

    text += "Parametertrenner:";
    text += "\t";
    text += paramtren();
    text += "\n";

    text += "Dezimaltrenner:";
    text += "\t";
    text += dezitren();
    text += "\n";

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

    text += "Kennung Werkzeugnummer:";
    text += "\t";
    text += kenWKZnr();
    text += "\n";

    text += "Kennung Radiuskorrektur li:";
    text += "\t";
    text += kenRadKorLi();
    text += "\n";

    text += "Kennung Radiuskorrektur mi:";
    text += "\t";
    text += kenRadKorMi();
    text += "\n";

    text += "Kennung Radiuskorrektur re:";
    text += "\t";
    text += kenRadKorRe();
    text += "\n";

    text += "Tiefenangabe Fraeskontur:";
    text += "\t";
    text += bezugTiFkon();
    text += "\n";

    return text;
}
//-------------------------------------------set:
void einstellung_dxf::set_paramtren(QString parametertrennzeichen)
{
    Paramtren = parametertrennzeichen;
}
void einstellung_dxf::set_dezitren(QString dezimaltrenner)
{
    Dezitren = dezimaltrenner;
}
void einstellung_dxf::set_kenObsei(QString kennung_oberseite)
{
    KennungOberseite = kennung_oberseite;
}
void einstellung_dxf::set_kenUnsei(QString kennung_unterseite)
{
    KennungUnterseite = kennung_unterseite;
}
void einstellung_dxf::set_dretypUnsei(QString drehtyp)
{
    DrehtypUnterseite = drehtyp;
}
void einstellung_dxf::set_kenWKZnr(QString kennung)
{
    KennungWKZnr = kennung;
}
void einstellung_dxf::set_kenRadKorLi(QString kennung)
{
    KennungRadKorLi = kennung;
}
void einstellung_dxf::set_kenRadKorMi(QString kennung)
{
    KennungRadKorMi = kennung;
}
void einstellung_dxf::set_kenRadKorRe(QString kennung)
{
    KennungRadKorRe = kennung;
}
void einstellung_dxf::set_bezugTiFkon(QString bezug)
{
    BezugTiFkon = bezug;
}

//-------------------------------------------get:
QString einstellung_dxf::paramtren()
{
    return Paramtren;
}
QString einstellung_dxf::dezitren()
{
    return Dezitren;
}
QString einstellung_dxf::kenObsei()
{
    return KennungOberseite;
}
QString einstellung_dxf::kenUnsei()
{
    return KennungUnterseite;
}
QString einstellung_dxf::drehtypUnsei()
{
    return DrehtypUnterseite;
}
bool einstellung_dxf::drehtyp_L()
{
    if(drehtypUnsei() == "L")
    {
        return true;
    }else
    {
        return false;
    }
}
bool einstellung_dxf::drehtyp_B()
{
    if(drehtypUnsei() == "B")
    {
        return true;
    }else
    {
        return false;
    }
}
QString einstellung_dxf::kenWKZnr()
{
    return KennungWKZnr;
}
QString einstellung_dxf::kenRadKorLi()
{
    return KennungRadKorLi;
}
QString einstellung_dxf::kenRadKorMi()
{
    return KennungRadKorMi;
}
QString einstellung_dxf::kenRadKorRe()
{
    return KennungRadKorRe;
}
QString einstellung_dxf::bezugTiFkon()
{
    return BezugTiFkon;
}
bool einstellung_dxf::bezugTiFkonObSei()
{
    if(bezugTiFkon() == "Oberseite Bauteil")
    {
        return true;
    }else
    {
        return false;
    }
}
bool einstellung_dxf::bezugTiFkonUnSei()
{
    if(bezugTiFkon() == "Unterseite Bauteil")
    {
        return true;
    }else
    {
        return false;
    }
}

//-------------------Funktionen nicht innerhalb der Klasse:
bool operator ==(einstellung_dxf e1, einstellung_dxf e2)
{
    if(e1.paramtren() == e2.paramtren()  && \
       e1.dezitren() == e2.dezitren()    && \
       e1.kenObsei() == e2.kenObsei()    && \
       e1.kenUnsei() == e2.kenUnsei()    && \
       e1.drehtypUnsei() == e2.drehtypUnsei()&& \
       e1.kenWKZnr() == e2.kenWKZnr()&& \
       e1.kenRadKorLi() == e2.kenRadKorLi()&& \
       e1.kenRadKorMi() == e2.kenRadKorMi()&& \
       e1.kenRadKorRe() == e2.kenRadKorRe()&&\
       e1.bezugTiFkon() == e2.bezugTiFkon()  )
    {
        return true;
    }else
    {
        return false;
    }
}
bool operator !=(einstellung_dxf e1, einstellung_dxf e2)
{
    if(e1.paramtren() == e2.paramtren()  && \
       e1.dezitren() == e2.dezitren()    && \
       e1.kenObsei() == e2.kenObsei()    && \
       e1.kenUnsei() == e2.kenUnsei()    && \
       e1.drehtypUnsei() == e2.drehtypUnsei()&& \
       e1.kenWKZnr() == e2.kenWKZnr()&& \
       e1.kenRadKorLi() == e2.kenRadKorLi()&& \
       e1.kenRadKorMi() == e2.kenRadKorMi()&& \
       e1.kenRadKorRe() == e2.kenRadKorRe()&&\
       e1.bezugTiFkon() == e2.bezugTiFkon()  )
    {
        return false;
    }else
    {
        return true;
    }
}

