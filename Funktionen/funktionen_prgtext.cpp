#include "Funktionen/funktionen_prgtext.h"

QString bezug(QString b)
{
    QString msg;
    if(b == WST_BEZUG_OBSEI)
    {
        msg += "ob";
    }else if(b == WST_BEZUG_UNSEI)
    {
        msg += "un";
    }else if(b == WST_BEZUG_LI)
    {
        msg += "li";
    }else if(b == WST_BEZUG_RE)
    {
        msg += "re";
    }else if(b == WST_BEZUG_VO)
    {
        msg += "vo";
    }else if(b == WST_BEZUG_HI)
    {
        msg += "hi";
    }
    return msg;
}

QString rta_zu_prgeile(QString text)
{
    QString msg = "RTA von ";
    rechtecktasche rt(text);
    msg += bezug(rt.bezug());
    msg += "\tL: ";
    msg += rt.laenge_qstring();
    msg += "\tB: ";
    msg += rt.breite_qstring();
    msg += "\tTi: ";
    msg += rt.tiefe_qstring();
    msg += "\tX: ";
    msg += rt.x_qstring();
    msg += "\tY: ";
    msg += rt.y_qstring();
    msg += "\tZ: ";
    msg += rt.z_qstring();
    msg += "\tZSM: ";
    msg += rt.zustellmass_qstring();
    msg += "\tWi: ";
    msg += rt.drewi_qstring();
    msg += "\tRAD: ";
    msg += rt.rad_qstring();
    msg += "\tausr: ";
    msg += rt.ausraeumen_qstring();
    msg += "\tAFB: ";
    msg += rt.afb();
    msg += "\tWKZ: ";
    msg += rt.wkznum();
    return msg;
}
