#include "einstellung_ganx.h"

einstellung_ganx::einstellung_ganx()
{
    Bezugsmass_in_use = true;
    Bezugskantenmass = 40;
}

void einstellung_ganx::set_text(QString t)
{
    text_zeilenweise tz;
    tz.set_text(t);
    for(uint i=1;i<=tz.zeilenanzahl();i++)
    {
        text_zeilenweise spalten;
        spalten.set_trennzeichen('\t');
        spalten.set_text(tz.zeile(i));
        if(spalten.zeile(1) == "Bezugsmass_in_use:")
        {
            use_bezugsmass(spalten.zeile(2));
        }
        if(spalten.zeile(1) == "Bezugskantenmass:")
        {
            set_bezugskantenmass(spalten.zeile(2).toDouble());
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
