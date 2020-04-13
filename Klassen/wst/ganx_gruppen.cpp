#include "ganx_gruppen.h"

ganx_Gruppen::ganx_Gruppen()
{
    setup();
}

void ganx_Gruppen::setup()
{
    clear();
    Gruppenzeile.set_trennzeichen('\t');
}

void ganx_Gruppen::clear()
{
    Gruppen.clear();
    Gruppenzeile.clear();
}

void ganx_Gruppen::neue_gruppe(QString bezugsflaeche)
{
    Gruppenzeile.clear();
    Gruppenzeile.zeile_anhaengen(bezugsflaeche);
    //ggf weitere Parameter anhängen
    Gruppen.zeile_anhaengen(Gruppenzeile.text());
}

QString ganx_Gruppen::gruppen()
{
    QString msg;

    for(uint i=1; i<=Gruppen.zeilenanzahl() ;i++)
    {
        Gruppenzeile.set_text(Gruppen.zeile(i));

        msg += "  <CycleGroups>";
        msg += "\n";
        //-------------------------------
        msg += "    <ID>";
        if(i==1)
        {
            msg += "0";
        }else
        {
            msg += double_to_qstring(i);
        }
        msg += "</ID>";
        msg += "\n";
        //-------------------------------
        msg += "    <GroupName>";
        msg += "Gruppe";
        msg += double_to_qstring(i);
        msg += "</GroupName>";
        msg += "\n";
        //-------------------------------
        msg += "    <Plane>";
        msg += Gruppenzeile.zeile(1);       //Bezugsfläche
        msg += "</Plane>";
        msg += "\n";
        //-------------------------------
        msg += "    <Ref />";
        msg += "\n";
        //-------------------------------
        msg += "    <Info>0</Info>";
        msg += "\n";
        //-------------------------------
        msg += "    <Type>1</Type>";
        msg += "\n";
        //-------------------------------
        msg += "  </CycleGroups>";
        msg += "\n";
        //-------------------------------
    }

    return msg;
}

QString ganx_Gruppen::letzten_gruppennamen()
{
    QString msg;

    //-------------------------------
    msg += "Gruppe";
    msg += double_to_qstring(Gruppen.zeilenanzahl());
    //-------------------------------

    return msg;
}
