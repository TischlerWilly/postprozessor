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

QString rta_zu_prgzei(QString text)
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
QString bohr_zu_prgzei(QString text)
{
    QString msg = "Bohr von ";
    bohrung bo(text);
    msg += bezug(bo.bezug());
    msg += "\tØ: ";
    msg += bo.dm_qstring();
    msg += "\tTi: ";
    msg += bo.tiefe_qstring();
    msg += "\tX: ";
    msg += bo.x_qstring();
    msg += "\tY: ";
    msg += bo.y_qstring();
    msg += "\tZ: ";
    msg += bo.z_qstring();
    msg += "\tZSM: ";
    msg += bo.zustellmass_qstring();
    msg += "\tAFB: ";
    msg += bo.afb();
    msg += "\tWKZ: ";
    msg += bo.wkznum();
    return msg;
}
QString bohrRaster_zu_prgzei(QString text)
{
    QString msg = "BoRa von ";
    bohrraster bo(text);
    msg += bezug(bo.bezug());
    msg += "\tØ: ";
    msg += bo.dm_qstring();
    msg += "\tTi: ";
    msg += bo.tiefe_qstring();
    msg += "\tX: ";
    msg += bo.x_qstring();
    msg += "\tY: ";
    msg += bo.y_qstring();
    msg += "\tZ: ";
    msg += bo.z_qstring();
    msg += "\tZSM: ";
    msg += bo.zustellmass_qstring();
    msg += "\tAFB: ";
    msg += bo.afb();
    msg += "\tWKZ: ";
    msg += bo.wkznum();
    msg += "\tAnz X: ";
    msg += bo.anz_x_qstring();
    msg += "\tAbst X: ";
    msg += bo.raster_x_qstring();
    msg += "\tAnz Y: ";
    msg += bo.anz_y_qstring();
    msg += "\tAbst Y: ";
    msg += bo.raster_y_qstring();
    msg += "\tAnz Z: ";
    msg += bo.anz_z_qstring();
    msg += "\tAbst Z: ";
    msg += bo.raster_z_qstring();
    return msg;
}
QString nut_zu_prgzei(QString text)
{
    QString msg = "Nut von ";
    nut nu(text);
    msg += bezug(nu.bezug());
    msg += "\tTi: ";
    msg += nu.tiefe_qstring();
    msg += "\tB: ";
    msg += nu.breite_qstring();
    msg += "\tXS: ";
    msg += nu.xs_qstring();
    msg += "\tYS: ";
    msg += nu.ys_qstring();
    msg += "\tZS: ";
    msg += nu.zs_qstring();
    msg += "\tXE: ";
    msg += nu.xe_qstring();
    msg += "\tYE: ";
    msg += nu.ye_qstring();
    msg += "\tZE: ";
    msg += nu.ze_qstring();
    msg += "\tAFB: ";
    msg += nu.afb();
    return msg;
}
QString fauf_zu_prgzei(QString text)
{
    QString msg = "Fräser von ";
    fraeseraufruf fa(text);
    msg += bezug(fa.bezug());
    msg += "\tX: ";
    msg += fa.x_qstring();
    msg += "\tY: ";
    msg += fa.y_qstring();
    msg += "\tZ: ";
    msg += fa.z_qstring();
    msg += "\tTi: ";
    msg += fa.tiefe_qstring();
    msg += "\tAFB: ";
    msg += fa.afb();
    msg += "\tKor: ";
    msg += fa.radkor();
    msg += "\tWKZ: ";
    msg += fa.wkznum();
    return msg;
}
QString fgerade_zu_prgzei(QString text)
{
    QString msg = "Gerade von ";
    fraesergerade fg(text);
    msg += bezug(fg.bezug());
    msg += "\tXS: ";
    msg += fg.xs_qstring();
    msg += "\tYS: ";
    msg += fg.ys_qstring();
    msg += "\tZS: ";
    msg += fg.zs_qstring();
    msg += "\tXE: ";
    msg += fg.xe_qstring();
    msg += "\tYE: ";
    msg += fg.ye_qstring();
    msg += "\tZE: ";
    msg += fg.ze_qstring();
    msg += "\tAFB: ";
    msg += fg.afb();
    return msg;
}
QString fbogen_zu_prgzei(QString text)
{
    QString msg = "Bogen von ";
    fraeserbogen fb(text);
    msg += bezug(fb.bezug());
    msg += "\tXS: ";
    msg += fb.xs_qstring();
    msg += "\tYS: ";
    msg += fb.ys_qstring();
    msg += "\tZS: ";
    msg += fb.zs_qstring();
    msg += "\tXE: ";
    msg += fb.xe_qstring();
    msg += "\tYE: ";
    msg += fb.ye_qstring();
    msg += "\tZE: ";
    msg += fb.ze_qstring();
    msg += "\tRAD: ";
    msg += fb.rad_qstring();
    msg += "\tUZS: ";
    msg += fb.uzs_qstring();
    msg += "\tAFB: ";
    msg += fb.afb();
    return msg;
}
QString gehr_zu_prgzei(QString text)
{
    QString msg = "Gehrung ";
    gehrung ge(text);
    msg += "\tSpitze :";
    if(ge.bezug() == WST_BEZUG_OBSEI)
    {
        msg += "unten";
    }else
    {
        msg += "oben";
    }
    msg += "\tWinkel: ";
    msg += ge.winkel_qstring();
    msg += "\tRitztiefe: ";
    msg += ge.riti_qstring();
    msg += "\tSchnittiefe: ";
    msg += ge.sti_qstring();
    msg += "\tXS: ";
    msg += ge.stapu().x_QString();
    msg += "\tYS: ";
    msg += ge.stapu().y_QString();
    msg += "\tXE: ";
    msg += ge.endpu().x_QString();
    msg += "\tYE: ";
    msg += ge.endpu().y_QString();
    msg += "\tY: ";
    msg += "\tAFB: ";
    msg += ge.afb();
    msg += "\tWKZ: ";
    msg += ge.wkznum();
    return msg;
}





