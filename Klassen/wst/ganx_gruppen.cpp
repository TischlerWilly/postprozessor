#include "ganx_gruppen.h"

ganx_Gruppen::ganx_Gruppen()
{
    setup();
}

void ganx_Gruppen::setup()
{
    clear();
    Gruppenzeile.set_trenz('\t');
}
void ganx_Gruppen::clear()
{
    Gruppen.clear();
    Gruppenzeile.clear();
}
void ganx_Gruppen::neue_gruppe(QString bezugsflaeche)
{
    Gruppenzeile.clear();
    Gruppenzeile.add_hi(bezugsflaeche);
    //ggf weitere Parameter anhängen
    Gruppen.add_hi(Gruppenzeile.text());
}

QString ganx_Gruppen::gruppen()
{
    QString msg;

    for(uint i=0; i<Gruppen.count() ;i++)
    {
        Gruppenzeile.set_text(Gruppen.at(i));

        msg += "  <CycleGroups>";
        msg += "\n";
        //-------------------------------
        msg += "    <ID>";
        if(i==0)
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
        msg += Gruppenzeile.at(0);       //Bezugsfläche
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
    msg += double_to_qstring(Gruppen.count()-1);
    //-------------------------------

    return msg;
}
