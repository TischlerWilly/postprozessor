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
}
void einstellung_dxf::set_text(QString t)
{
    text_zeilenweise tz;
    tz.set_text(t);
    for(uint i=1;i<=tz.zeilenanzahl();i++)
    {
        text_zeilenweise spalten;
        spalten.set_trennzeichen('\t');
        spalten.set_text(tz.zeile(i));
        if(spalten.zeile(1) == "Parametertrenner:")
        {
            set_paramtren(spalten.zeile(2));
        }
        if(spalten.zeile(1) == "Dezimaltrenner:")
        {
            set_dezitren(spalten.zeile(2));
        }
        if(spalten.zeile(1) == "Kennung Oberseite:")
        {
            set_kenObsei(spalten.zeile(2));
        }
        if(spalten.zeile(1) == "Kennung Unterseite:")
        {
            set_kenUnsei(spalten.zeile(2));
        }
        if(spalten.zeile(1) == "Drehtyp Unterseite:")
        {
            set_dretypUnsei(spalten.zeile(2));
        }
        if(spalten.zeile(1) == "Kennung Werkzeugnummer:")
        {
            set_kenWKZnr(spalten.zeile(2));
        }
        if(spalten.zeile(1) == "Kennung Radiuskorrektur li:")
        {
            set_kenRadKorLi(spalten.zeile(2));
        }
        if(spalten.zeile(1) == "Kennung Radiuskorrektur mi:")
        {
            set_kenRadKorMi(spalten.zeile(2));
        }
        if(spalten.zeile(1) == "Kennung Radiuskorrektur re:")
        {
            set_kenRadKorRe(spalten.zeile(2));
        }
    }
}

//-------------------------------------------set:
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

    return text;
}
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
       e1.kenRadKorRe() == e2.kenRadKorRe()  )
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
       e1.kenRadKorRe() == e2.kenRadKorRe()  )
    {
        return false;
    }else
    {
        return true;
    }
}

