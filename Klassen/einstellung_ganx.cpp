#include "einstellung_ganx.h"

einstellung_ganx::einstellung_ganx()
{
    Bezugsmass_in_use = true;
    Bezugskantenmass = 40;
}

void einstellung_ganx::set_text(QString t)
{
    text_zw tz;
    tz.set_text(t,'\n');
    for(uint i=0;i<tz.count();i++)
    {
        text_zw spalten;
        spalten.set_text(tz.at(i),'\t');
        if(spalten.at(0) == "Bezugsmass_in_use:")
        {
            use_bezugsmass(spalten.at(1));
        }
        if(spalten.at(0) == "Bezugskantenmass:")
        {
            set_bezugskantenmass(spalten.at(1).toDouble());
        }
    }
}

QString einstellung_ganx::text()
{
    QString text;

    text += "Bezugsmass_in_use:";
    text += "\t";
    if(Bezugsmass_in_use == true)
    {
        text += "ja";
    }else
    {
        text += "nein";
    }
    text += "\n";

    text += "Bezugskantenmass:";
    text += "\t";
    text += double_to_qstring(Bezugskantenmass);
    text += "\n";

    return text;
}

void einstellung_ganx::set_bezugskantenmass(double b)
{
    if(b >= 0)
    {
        Bezugskantenmass = b;
    }else
    {
        QString msg;
        msg = "Fehler im Dialog Einstellungen ganx!\n";
        msg += "Bezugskantenmaß konnte nicht gesetzt werden.\n";
        msg += "Bitte einen Wert > oder = 0 wählen.";
        QMessageBox mb;
        mb.setText(msg);
        mb.exec();
    }
}

void einstellung_ganx::use_bezugsmass(bool in_use)
{
    Bezugsmass_in_use = in_use;
}
void einstellung_ganx::use_bezugsmass(QString in_use)
{
    if(in_use == "ja")
    {
        use_bezugsmass(true);
    }else
    {
        use_bezugsmass(false);
    }
}

double einstellung_ganx::bezugsmass()
{
    return Bezugskantenmass;
}

bool einstellung_ganx::bezugsmass_in_use()
{
    return Bezugsmass_in_use;
}

//-------------------Funktionen nicht innerhalb der Klasse:
bool operator ==(einstellung_ganx e1, einstellung_ganx e2)
{
    if(e1.bezugsmass() == e2.bezugsmass() && \
       e1.bezugsmass_in_use() == e2.bezugsmass_in_use())
    {
        return true;
    }else
    {
        return false;
    }
}
bool operator !=(einstellung_ganx e1, einstellung_ganx e2)
{
    if(e1.bezugsmass() == e2.bezugsmass() && \
            e1.bezugsmass_in_use() == e2.bezugsmass_in_use())
    {
        return false;
    }else
    {
        return true;
    }
}
