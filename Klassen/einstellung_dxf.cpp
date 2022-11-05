#include "einstellung_dxf.h"

einstellung_dxf::einstellung_dxf()
{
    Paramtren = "_";
    Dezitren = "_";
    KennungOberseite = "1";
    KennungUnterseite = "2";
    DrehtypUnterseite = "B";
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

//-------------------Funktionen nicht innerhalb der Klasse:
bool operator ==(einstellung_dxf e1, einstellung_dxf e2)
{
    if(e1.paramtren() == e2.paramtren()  && \
       e1.dezitren() == e2.dezitren()    && \
       e1.kenObsei() == e2.kenObsei()    && \
       e1.kenUnsei() == e2.kenUnsei()    && \
       e1.drehtypUnsei() == e2.drehtypUnsei()  )
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
       e1.drehtypUnsei() == e2.drehtypUnsei()  )
    {
        return false;
    }else
    {
        return true;
    }
}

