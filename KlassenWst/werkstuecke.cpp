#include "werkstuecke.h"


werkstuecke::werkstuecke()
{

}

//---------------------------------------------------------------allgemeine Funktionen:
bool werkstuecke::ist_bekannt(QString Werkstueckname)
{
    for(uint i=1; i<=namen.zeilenanzahl() ;i++)
    {
        if(Werkstueckname == namen.zeile(i))
        {
            return true;
        }
    }
    return false;
}
bool werkstuecke::neu(QString Werkstueckname, QString Quellformat)
{
    if(ist_bekannt(Werkstueckname))
    {
        return true;//FEHLER, der Teil gibt es bereits!!!
    }else
    {
        namen.zeile_anhaengen(Werkstueckname);
        quellformate.zeile_anhaengen(Quellformat);
        werkstueck w;
        wste.append(w);
    }
    return false;
}
void werkstuecke::clear()
{
    namen.clear();
    quellformate.clear();
    wste.clear();
}
uint werkstuecke::get_index(QString Werkstueckname)
{
    for(uint i=1; i<=namen.zeilenanzahl() ;i++)
    {
        if(namen.zeile(i)==Werkstueckname)
        {
            return i;
        }
    }
    return 0; //Wenn der Name nicht gefunden wurde
}
QString werkstuecke::wert_nach_istgleich(QString text)
{
    if(text.contains("="))
    {
        if(text.contains("\n"))
        {
            return text_mitte(text, "=", "\n");
        }else
        {
            return text_rechts(text, "=");
        }
    }else
    {
        return "";
    }
}
werkstueck werkstuecke::get_wst(uint index)
{
    if(index > 0 && index <= namen.zeilenanzahl())
    {
        return wste.at(index-1);
    }else
    {
        werkstueck w;   //leeres Wst
        return w;
    }
}
QString werkstuecke::get_name(uint index)
{
    if(index > 0 && index <= namen.zeilenanzahl())
    {
        return namen.zeile(index);
    }else
    {
        return "";
    }
}
void werkstuecke::stdnamen(text_zeilenweise namen_alt, text_zeilenweise namen_neu)
{
    for(uint i = 1; i<=namen.zeilenanzahl() ;i++)
    {
        QString tmp = namen.zeile(i);
        for(uint ii=1; ii<=namen_alt.zeilenanzahl();ii++)
        {
            if(tmp.contains(namen_alt.zeile(ii)))
            {
                tmp.replace(namen_alt.zeile(ii), namen_neu.zeile(ii));
                namen.zeile_ersaetzen(i, tmp);
                break;
            }
        }
    }
}

//---------------------------------------------------------------Import-Funktionen:
bool werkstuecke::import_fmc_oberseite(QString Werkstueckname, QString importtext)
{
    uint index = get_index(Werkstueckname);
    if(index == 0)
    {
        neu(Werkstueckname, FMC);
        index = get_index(Werkstueckname);
    }
    text_zeilenweise tz;
    tz.set_text(importtext);

    werkstueck w = wste.at(index-1);

    for(uint i=1; i<=tz.zeilenanzahl() ;i++)
    {
        QString zeile = tz.zeile(i);
        if(zeile.contains(FMC_PRGKOPF))
        {
            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii;
                    break;
                }else
                {
                    if(zeile.contains(FMC_PRGKOPF_LAENGE))
                    { 
                        w.set_laenge(wert_nach_istgleich(zeile));
                    }else if(zeile.contains(FMC_PRGKOPF_BREITE))
                    {
                        w.set_breite(wert_nach_istgleich(zeile));
                    }else if(zeile.contains(FMC_PRGKOPF_DICKE))
                    {
                        w.set_dicke(wert_nach_istgleich(zeile));
                    }                    
                }
            }
        }else if(zeile.contains(FMC_BOHR_DM))
        {
            bohrung bo;
            bo.set_bezug(WST_BEZUG_OBSEI);

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii;
                    w.neue_bearbeitung(bo.get_text());
                    break;
                }else
                {                    
                    if(zeile.contains(FMC_BOHR_DM_AFB))
                    {
                        bo.set_afb(wert_nach_istgleich(zeile));
                    }else if(zeile.contains(FMC_BOHR_DM_DM))
                    {
                        bo.set_dm(wert_nach_istgleich(zeile));
                    }else if(zeile.contains(FMC_BOHR_DM_TIEFE))
                    {
                        bo.set_tiefe(wert_nach_istgleich(zeile));
                    }else if(zeile.contains(FMC_BOHR_DM_X))
                    {
                        bo.set_x(wert_nach_istgleich(zeile));
                    }else if(zeile.contains(FMC_BOHR_DM_Y))
                    {
                        bo.set_y(wert_nach_istgleich(zeile));
                    }
                }
            }
        }else if(zeile.contains(FMC_HBEXP))
        {
            bohrung bo;
            bo.set_bezug(WST_BEZUG_LI);
            double bohrtiefe = 0;
            double x1 = 0;
            double x2 = -1;
            bool kettenmass = false;
            double y1 = 0;
            double y2 = 0;
            double y3 = 0;
            double y4 = 0;
            double y5 = 0;
            double y6 = 0;

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii;
                    bo.set_tiefe(x1 + bohrtiefe);
                    if(y1)
                    {
                        bo.set_y(y1);
                        w.neue_bearbeitung(bo.get_text());
                    }
                    if(y2)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y2);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(y3)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y3);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2+y3);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(y4)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y4);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(y5)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y5);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4+y5);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(y6)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y6);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4+y5+y6);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }

                    if(x2 > 0)
                    {
                        bo.set_bezug(WST_BEZUG_RE);
                        bo.set_tiefe(w.get_laenge() - x2 + bohrtiefe);

                        if(y1)
                        {
                            bo.set_y(y1);
                            w.neue_bearbeitung(bo.get_text());
                        }
                        if(y2)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y2);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(y3)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y3);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2+y3);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(y4)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y4);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(y5)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y5);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4+y5);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(y6)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y6);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4+y5+y6);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                    }
                    break;
                }else
                {
                    if(zeile.contains(FMC_HBEXP_AFB))
                    {
                        bo.set_afb(wert_nach_istgleich(zeile));
                    }else if(zeile.contains(FMC_HBEXP_DM))
                    {
                        bo.set_dm(wert_nach_istgleich(zeile));
                    }else if(zeile.contains(FMC_HBEXP_TI))
                    {
                        bohrtiefe = ausdruck_auswerten(wert_nach_istgleich(zeile)).toDouble();
                    }else if(zeile.contains(FMC_HBEXP_Z))
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        if(tmp.contains("D"))
                        {
                            tmp.replace("D", w.get_dicke_qstring());
                        }
                        double z = ausdruck_auswerten(tmp).toDouble();
                        bo.set_z(z);
                    }else if(zeile.contains(FMC_HBEXP_X1))
                    {
                        x1 = ausdruck_auswerten(wert_nach_istgleich(zeile)).toDouble();
                    }else if(zeile.contains(FMC_HBEXP_X2))
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        if(tmp.contains("L"))
                        {
                            tmp.replace("L", w.get_laenge_qstring());
                        }
                        x2 = ausdruck_auswerten(tmp).toDouble();
                    }else if(zeile.contains(FMC_HBEXP_KM))
                    {
                        kettenmass = ausdruck_auswerten(wert_nach_istgleich(zeile)).toDouble();
                    }else if(zeile.contains(FMC_HBEXP_Y1))
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            y1 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(zeile.contains(FMC_HBEXP_Y2))
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            y2 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(zeile.contains(FMC_HBEXP_Y3))
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            y3 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(zeile.contains(FMC_HBEXP_Y4))
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            y4 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(zeile.contains(FMC_HBEXP_Y5))
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            y5 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(zeile.contains(FMC_HBEXP_Y6))
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            y6 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }
                }
            }
        }else if(zeile.contains(FMC_HBEXM))
        {
            bohrung bo;
            bo.set_bezug(WST_BEZUG_RE);
            double bohrtiefe = 0;
            double x1 = 0;
            double x2 = -1;
            bool kettenmass = false;
            double y1 = 0;
            double y2 = 0;
            double y3 = 0;
            double y4 = 0;
            double y5 = 0;
            double y6 = 0;

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii;
                    bo.set_tiefe(w.get_laenge() - x1 + bohrtiefe);
                    if(y1)
                    {
                        bo.set_y(y1);
                        w.neue_bearbeitung(bo.get_text());
                    }
                    if(y2)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y2);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(y3)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y3);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2+y3);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(y4)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y4);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(y5)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y5);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4+y5);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(y6)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y6);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4+y5+y6);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }

                    if(x2 >= 0)
                    {
                        bo.set_bezug(WST_BEZUG_LI);
                        bo.set_tiefe(x2 + bohrtiefe);

                        if(y1)
                        {
                            bo.set_y(y1);
                            w.neue_bearbeitung(bo.get_text());
                        }
                        if(y2)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y2);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(y3)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y3);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2+y3);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(y4)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y4);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(y5)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y5);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4+y5);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(y6)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y6);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4+y5+y6);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                    }
                    break;
                }else
                {
                    if(zeile.contains(FMC_HBEXP_AFB))
                    {
                        bo.set_afb(wert_nach_istgleich(zeile));
                    }else if(zeile.contains(FMC_HBEXP_DM))
                    {
                        bo.set_dm(wert_nach_istgleich(zeile));
                    }else if(zeile.contains(FMC_HBEXP_TI))
                    {
                        bohrtiefe = ausdruck_auswerten(wert_nach_istgleich(zeile)).toDouble();
                    }else if(zeile.contains(FMC_HBEXP_Z))
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        if(tmp.contains("D"))
                        {
                            tmp.replace("D", w.get_dicke_qstring());
                        }
                        double z = ausdruck_auswerten(tmp).toDouble();
                        bo.set_z(z);
                    }else if(zeile.contains(FMC_HBEXP_X2))
                    {
                        x2 = ausdruck_auswerten(wert_nach_istgleich(zeile)).toDouble();
                    }else if(zeile.contains(FMC_HBEXP_X1))
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        if(tmp.contains("L"))
                        {
                            tmp.replace("L", w.get_laenge_qstring());
                        }
                        x1 = ausdruck_auswerten(tmp).toDouble();
                    }else if(zeile.contains(FMC_HBEXP_KM))
                    {
                        kettenmass = ausdruck_auswerten(wert_nach_istgleich(zeile)).toDouble();
                    }else if(zeile.contains(FMC_HBEXP_Y1))
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            y1 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(zeile.contains(FMC_HBEXP_Y2))
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            y2 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(zeile.contains(FMC_HBEXP_Y3))
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            y3 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(zeile.contains(FMC_HBEXP_Y4))
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            y4 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(zeile.contains(FMC_HBEXP_Y5))
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            y5 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(zeile.contains(FMC_HBEXP_Y6))
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            y6 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }
                }
            }
        }
    }

    wste.replace(index-1, w);

    return 0;
}

bool werkstuecke::import_fmc_unterseite(QString Werkstueckname, QString importtext)
{
    uint index = get_index(Werkstueckname);
    if(index == 0)
    {
        return 1;   //Die Bearbeitung soll nur auf die Unterseite importiert werden,
                    //wenn bereits die Bearbeitung auf der Oberseite importiert wurde
    }
    text_zeilenweise tz;
    tz.set_text(importtext);

    werkstueck w = wste.at(index-1);

    for(uint i=1; i<=tz.zeilenanzahl() ;i++)
    {
        QString zeile = tz.zeile(i);

        if(zeile.contains(FMC_BOHR_DM))
        {
            bohrung bo;
            bo.set_bezug(WST_BEZUG_UNSEI);

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii;
                    w.neue_bearbeitung(bo.get_text());
                    break;
                }else
                {
                    if(zeile.contains(FMC_BOHR_DM_AFB))
                    {
                        bo.set_afb(wert_nach_istgleich(zeile));
                    }else if(zeile.contains(FMC_BOHR_DM_DM))
                    {
                        bo.set_dm(wert_nach_istgleich(zeile));
                    }else if(zeile.contains(FMC_BOHR_DM_TIEFE))
                    {
                        bo.set_tiefe(wert_nach_istgleich(zeile));
                    }else if(zeile.contains(FMC_BOHR_DM_X))
                    {
                        double x = ausdruck_auswerten(wert_nach_istgleich(zeile)).toDouble();
                        x = w.get_laenge()-x;
                        bo.set_x(x);
                    }else if(zeile.contains(FMC_BOHR_DM_Y))
                    {
                        bo.set_y(wert_nach_istgleich(zeile));
                    }
                }
            }
        }else if(zeile.contains(FMC_HBEXP))
        {
            bohrung bo;
            bo.set_bezug(WST_BEZUG_RE); //Bearbeitung von Unterseite auf Oberseite bringen (drehen um l/2)
            double bohrtiefe = 0;
            double x1 = 0;
            double x2 = -1;
            bool kettenmass = false;
            double y1 = 0;
            double y2 = 0;
            double y3 = 0;
            double y4 = 0;
            double y5 = 0;
            double y6 = 0;

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii;
                    bo.set_tiefe(x1 + bohrtiefe);
                    if(y1)
                    {
                        bo.set_y(y1);
                        w.neue_bearbeitung(bo.get_text());
                    }
                    if(y2)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y2);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(y3)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y3);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2+y3);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(y4)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y4);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(y5)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y5);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4+y5);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(y6)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y6);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4+y5+y6);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }

                    if(x2 > 0)
                    {
                        bo.set_bezug(WST_BEZUG_LI);//Bearbeitung von Unterseite auf Oberseite bringen (drehen um l/2)
                        bo.set_tiefe(w.get_laenge() - x2 + bohrtiefe);

                        if(y1)
                        {
                            bo.set_y(y1);
                            w.neue_bearbeitung(bo.get_text());
                        }
                        if(y2)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y2);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(y3)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y3);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2+y3);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(y4)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y4);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(y5)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y5);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4+y5);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(y6)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y6);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4+y5+y6);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                    }
                    break;
                }else
                {
                    if(zeile.contains(FMC_HBEXP_AFB))
                    {
                        bo.set_afb(wert_nach_istgleich(zeile));
                    }else if(zeile.contains(FMC_HBEXP_DM))
                    {
                        bo.set_dm(wert_nach_istgleich(zeile));
                    }else if(zeile.contains(FMC_HBEXP_TI))
                    {
                        bohrtiefe = ausdruck_auswerten(wert_nach_istgleich(zeile)).toDouble();
                    }else if(zeile.contains(FMC_HBEXP_Z))
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        if(tmp.contains("D"))
                        {
                            tmp.replace("D", w.get_dicke_qstring());
                        }
                        double z = w.get_dicke() - ausdruck_auswerten(tmp).toDouble();//Umrechen auf Oberseite
                        bo.set_z(z);
                    }else if(zeile.contains(FMC_HBEXP_X1))
                    {
                        x1 = ausdruck_auswerten(wert_nach_istgleich(zeile)).toDouble();
                    }else if(zeile.contains(FMC_HBEXP_X2))
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        if(tmp.contains("L"))
                        {
                            tmp.replace("L", w.get_laenge_qstring());
                        }
                        x2 = ausdruck_auswerten(tmp).toDouble();
                    }else if(zeile.contains(FMC_HBEXP_KM))
                    {
                        kettenmass = ausdruck_auswerten(wert_nach_istgleich(zeile)).toDouble();
                    }else if(zeile.contains(FMC_HBEXP_Y1))
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            y1 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(zeile.contains(FMC_HBEXP_Y2))
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            y2 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(zeile.contains(FMC_HBEXP_Y3))
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            y3 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(zeile.contains(FMC_HBEXP_Y4))
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            y4 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(zeile.contains(FMC_HBEXP_Y5))
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            y5 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(zeile.contains(FMC_HBEXP_Y6))
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            y6 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }
                }
            }
        }else if(zeile.contains(FMC_HBEXM))
        {
            bohrung bo;
            bo.set_bezug(WST_BEZUG_LI);//Bearbeitung von Unterseite auf Oberseite bringen (drehen um l/2)
            double bohrtiefe = 0;
            double x1 = 0;
            double x2 = -1;
            bool kettenmass = false;
            double y1 = 0;
            double y2 = 0;
            double y3 = 0;
            double y4 = 0;
            double y5 = 0;
            double y6 = 0;

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii;
                    bo.set_tiefe(w.get_laenge() - x1 + bohrtiefe);
                    if(y1)
                    {
                        bo.set_y(y1);
                        w.neue_bearbeitung(bo.get_text());
                    }
                    if(y2)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y2);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(y3)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y3);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2+y3);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(y4)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y4);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(y5)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y5);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4+y5);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(y6)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y6);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4+y5+y6);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }

                    if(x2 >= 0)
                    {
                        bo.set_bezug(WST_BEZUG_RE);//Bearbeitung von Unterseite auf Oberseite bringen (drehen um l/2)
                        bo.set_tiefe(x2 + bohrtiefe);

                        if(y1)
                        {
                            bo.set_y(y1);
                            w.neue_bearbeitung(bo.get_text());
                        }
                        if(y2)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y2);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(y3)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y3);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2+y3);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(y4)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y4);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(y5)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y5);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4+y5);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(y6)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y6);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4+y5+y6);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                    }
                    break;
                }else
                {
                    if(zeile.contains(FMC_HBEXP_AFB))
                    {
                        bo.set_afb(wert_nach_istgleich(zeile));
                    }else if(zeile.contains(FMC_HBEXP_DM))
                    {
                        bo.set_dm(wert_nach_istgleich(zeile));
                    }else if(zeile.contains(FMC_HBEXP_TI))
                    {
                        bohrtiefe = ausdruck_auswerten(wert_nach_istgleich(zeile)).toDouble();
                    }else if(zeile.contains(FMC_HBEXP_Z))
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        if(tmp.contains("D"))
                        {
                            tmp.replace("D", w.get_dicke_qstring());
                        }
                        double z = w.get_dicke() - ausdruck_auswerten(tmp).toDouble();//Umrechen auf Oberseite
                        bo.set_z(z);
                    }else if(zeile.contains(FMC_HBEXP_X2))
                    {
                        x2 = ausdruck_auswerten(wert_nach_istgleich(zeile)).toDouble();
                    }else if(zeile.contains(FMC_HBEXP_X1))
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        if(tmp.contains("L"))
                        {
                            tmp.replace("L", w.get_laenge_qstring());
                        }
                        x1 = ausdruck_auswerten(tmp).toDouble();
                    }else if(zeile.contains(FMC_HBEXP_KM))
                    {
                        kettenmass = ausdruck_auswerten(wert_nach_istgleich(zeile)).toDouble();
                    }else if(zeile.contains(FMC_HBEXP_Y1))
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            y1 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(zeile.contains(FMC_HBEXP_Y2))
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            y2 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(zeile.contains(FMC_HBEXP_Y3))
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            y3 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(zeile.contains(FMC_HBEXP_Y4))
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            y4 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(zeile.contains(FMC_HBEXP_Y5))
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            y5 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(zeile.contains(FMC_HBEXP_Y6))
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            y6 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }
                }
            }
        }

    }

    wste.replace(index-1, w);

    return 0;
}




