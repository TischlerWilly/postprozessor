#include "ganx_gruppen.h"

ganx_Gruppen::ganx_Gruppen()
{
    setup();
}

void ganx_Gruppen::setup()
{
    clear();
    gruppenzeile.set_trennzeichen('\t');
}

void ganx_Gruppen::clear()
{
    gruppen.clear();
    gruppenzeile.clear();
}

void ganx_Gruppen::neue_gruppe(QString bezugsflaeche)
{
    gruppenzeile.clear();
    gruppenzeile.zeile_anhaengen(bezugsflaeche);
    //ggf weitere Parameter anhängen
    gruppen.zeile_anhaengen(gruppenzeile.text());
}

QString ganx_Gruppen::get_gruppen()
{
    QString msg;

    for(uint i=1; i<=gruppen.zeilenanzahl() ;i++)
    {
        gruppenzeile.set_text(gruppen.zeile(i));

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
        msg += gruppenzeile.zeile(1);       //Bezugsfläche
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

QString ganx_Gruppen::get_letzten_gruppennamen()
{
    QString msg;

    //-------------------------------
    msg += "Gruppe";
    msg += double_to_qstring(gruppen.zeilenanzahl());
    //-------------------------------

    return msg;
}
