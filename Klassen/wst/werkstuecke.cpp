#include "werkstuecke.h"


werkstuecke::werkstuecke()
{
    Min_fkon_gerade_laenge = 1;
    Kurze_geraden_import = false;
}
//#######################################################################
//Public:
//#######################################################################
//--------------------------------------------------set_xy:
bool werkstuecke::neu(QString Werkstueckname, QString Quellformat)
{
    if(ist_bekannt(Werkstueckname))
    {
        return true;//FEHLER, der Teil gibt es bereits!!!
    }else
    {
        Namen.add_hi(Werkstueckname);
        Quellformate.add_hi(Quellformat);
        werkstueck w(Werkstueckname);
        w.set_zugabe_gehrungen(Zugabe_gehrungen);
        Wste.append(w);
    }
    return false;
}
bool werkstuecke::import_fmc(QString Werkstueckname, QString importtext, bool istOberseite)
{

    int Index = index(Werkstueckname);
    if(Index == -1)
    {
        neu(Werkstueckname, FMC);
        Index = index(Werkstueckname);
    }
    werkstueck w = Wste.at(Index);
    text_zw tz;
    tz.set_text(importtext,'\n');
    //globale Variablen:
    bool schalter_halt = false;
    bool drehtyp_L = Einstellung_fmc.drehtyp_L();//muss lokale Variable sein für Import FMC mit Halt
    bool drehtyp_B = Einstellung_fmc.drehtyp_B();//muss lokale Variable sein für Import FMC mit Halt
    //---
    punkt3d p3dfkon;//Speichert XYZ-Werte, ggf. nach dem drehen auf die Unterseite
    double orginal_x = 0;//speichert X-Wert vor dem Drehen auf die Unterseite
    double orginal_y = 0;//speichert Y-Wert vor dem Drehen auf die Unterseite
    double tifkon = 0;//speichert die Frästiefe
    for(uint i=0; i<tz.count() ;i++)
    {
        QString zeile = tz.at(i);
        if(zeile.contains(FMC_PRGKOPF))
        {
            for(uint ii=i+1; ii<tz.count() ;ii++)
            {
                zeile = tz.at(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_PRGKOPF_LAENGE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        w.set_laenge(tmp);
                    }else if(schluessel == FMC_PRGKOPF_BREITE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        w.set_breite(tmp);
                    }else if(schluessel == FMC_PRGKOPF_DICKE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        w.set_dicke(tmp);
                    }
                }
            }
        }else if(zeile.contains(FMC_HALT))
        {
            schalter_halt = true;
            //Drehtyp wird über Auswertung vom Kommentar ermitteln
            //Erst dann wird der Halt wirksam
        }else if(zeile.contains(FMC_KOMMENTAR))
        {
            i++;
            zeile = tz.at(i);
            QString schluessel = text_links(zeile, "=");
            if(schluessel == FMC_KOMMENTAR_TEXT)
            {
                QString vo = VW_KANTE_VO;
                vo = vo.toUpper();
                QString hi = VW_KANTE_HI;
                hi = hi.toUpper();
                QString li = VW_KANTE_LI;
                li = li.toUpper();
                QString re = VW_KANTE_RE;
                re = re.toUpper();
                QString kom = text_rechts(zeile, "=");
                if(kom.contains(vo))
                {
                    w.set_kante_vo(text_rechts(kom, vo));
                }else if(kom.contains(hi))
                {
                    w.set_kante_hi(text_rechts(kom, hi));
                }else if(kom.contains(li))
                {
                    w.set_kante_li(text_rechts(kom, li));
                }else if(kom.contains(re))
                {
                    w.set_kante_re(text_rechts(kom, re));
                }
                if(schalter_halt == true)
                {
                    schalter_halt = false;
                    istOberseite = !istOberseite;
                    if(kom.contains("l/2") || kom.contains("L/2"))
                    {
                        drehtyp_L = true;
                        drehtyp_B = false;
                    }else if(kom.contains("b/2") || kom.contains("B/2"))
                    {
                        drehtyp_L = false;
                        drehtyp_B = true;
                    }
                }
            }
        }else if(zeile.contains(FMC_BOHR_DM))
        {
            bohrung bo;
            double x = 0;
            double y = 0;
            for(uint ii=i+1; ii<tz.count() ;ii++)
            {
                zeile = tz.at(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    if(istOberseite)
                    {
                        bo.set_bezug(WST_BEZUG_OBSEI);
                        bo.set_x(x);
                        bo.set_y(y);
                        bo.set_z(w.dicke());
                    }else
                    {
                        bo.set_bezug(WST_BEZUG_UNSEI);
                        if(drehtyp_L)
                        {
                            bo.set_x(w.laenge()-x);
                            bo.set_y(y);
                        }else //if(drehtyp_B)
                        {
                            bo.set_x(x);
                            bo.set_y(w.breite()-y);
                        }
                        bo.set_z(0);
                    }
                    w.neue_bearbeitung(bo.text());
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_BOHR_DM_AFB)
                    {
                        bo.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_BOHR_DM_DM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bo.set_dm(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_BOHR_DM_TIEFE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        double tiefe = ausdruck_auswerten(tmp).toDouble();
                        if(tiefe < 0)
                        {
                            tiefe = w.dicke() - tiefe;
                        }
                        bo.set_tiefe(tiefe);
                    }else if(schluessel == FMC_BOHR_DM_X)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        x = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_BOHR_DM_Y)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        y = ausdruck_auswerten(tmp).toDouble();
                    }
                }
            }
        }else if(zeile.contains(FMC_HBEXP))
        {
            bohrung bo;
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
            double z = 0;
            for(uint ii=i+1; ii<tz.count() ;ii++)
            {
                zeile = tz.at(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    //istOberseite und Kettenmaß ausweten:
                    if(istOberseite)
                    {
                        bo.set_bezug(WST_BEZUG_LI);
                        if(kettenmass == true)
                        {
                            double alt_y1 = y1;
                            double alt_y2 = y2;
                            double alt_y3 = y3;
                            double alt_y4 = y4;
                            double alt_y5 = y5;
                            double alt_y6 = y6;
                            if(y2)
                            {
                                y2 = alt_y1 + alt_y2;
                            }
                            if(y3)
                            {
                                y3 = alt_y1 + alt_y2 + alt_y3;
                            }
                            if(y4)
                            {
                                y4 = alt_y1 + alt_y2 + alt_y3 + alt_y4;
                            }
                            if(y5)
                            {
                                y5 = alt_y1 + alt_y2 + alt_y3 + alt_y4 + alt_y5;
                            }
                            if(y6)
                            {
                                y6 = alt_y1 + alt_y2 + alt_y3 + alt_y4 + alt_y5 + alt_y6;
                            }
                        }
                    }else
                    {
                        z = w.dicke() - z;
                        if(drehtyp_L)
                        {
                            bo.set_bezug(WST_BEZUG_RE);
                            x1 = w.laenge() - x1;
                            if(x2 > 0)
                            {
                                x2 = w.laenge() - x2;
                            }
                            if(kettenmass == true)
                            {
                                double alt_y1 = y1;
                                double alt_y2 = y2;
                                double alt_y3 = y3;
                                double alt_y4 = y4;
                                double alt_y5 = y5;
                                double alt_y6 = y6;
                                if(y2)
                                {
                                    y2 = alt_y1 + alt_y2;
                                }
                                if(y3)
                                {
                                    y3 = alt_y1 + alt_y2 + alt_y3;
                                }
                                if(y4)
                                {
                                    y4 = alt_y1 + alt_y2 + alt_y3 + alt_y4;
                                }
                                if(y5)
                                {
                                    y5 = alt_y1 + alt_y2 + alt_y3 + alt_y4 + alt_y5;
                                }
                                if(y6)
                                {
                                    y6 = alt_y1 + alt_y2 + alt_y3 + alt_y4 + alt_y5 + alt_y6;
                                }
                            }
                        }else //if(drehtyp_B)
                        {
                            bo.set_bezug(WST_BEZUG_LI);
                            if(kettenmass == true)
                            {
                                double alt_y1 = y1;
                                double alt_y2 = y2;
                                double alt_y3 = y3;
                                double alt_y4 = y4;
                                double alt_y5 = y5;
                                double alt_y6 = y6;
                                if(y1)
                                {
                                    y1 = w.breite() - alt_y1;
                                }
                                if(y2)
                                {
                                    y2 = w.breite() - (alt_y1 + alt_y2);
                                }
                                if(y3)
                                {
                                    y3 = w.breite() - (alt_y1 + alt_y2 + alt_y3);
                                }
                                if(y4)
                                {
                                    y4 = w.breite() - (alt_y1 + alt_y2 + alt_y3 + alt_y4);
                                }
                                if(y5)
                                {
                                    y5 = w.breite() - (alt_y1 + alt_y2 + alt_y3 + alt_y4 + alt_y5);
                                }
                                if(y6)
                                {
                                    y6 = w.breite() - (alt_y1 + alt_y2 + alt_y3 + alt_y4 + alt_y5 + alt_y6);
                                }
                            }else
                            {
                                if(y1)
                                {
                                    y1 = w.breite() - y1;
                                }
                                if(y2)
                                {
                                    y2 = w.breite() - y2;
                                }
                                if(y3)
                                {
                                    y3 = w.breite() - y3;
                                }
                                if(y4)
                                {
                                    y4 = w.breite() - y4;
                                }
                                if(y5)
                                {
                                    y5 = w.breite() - y5;
                                }
                                if(y6)
                                {
                                    y6 = w.breite() - y6;
                                }
                            }
                        }
                    }
                    //---
                    bo.set_tiefe(bohrtiefe);
                    bo.set_z(z);
                    bo.set_x(x1);
                    if(y1)
                    {
                        bo.set_y(y1);
                        w.neue_bearbeitung(bo.text());
                    }
                    if(y2)
                    {
                        bo.set_y(y2);
                        w.neue_bearbeitung(bo.text());
                    }
                    if(y3)
                    {
                        bo.set_y(y3);
                        w.neue_bearbeitung(bo.text());
                    }
                    if(y4)
                    {
                        bo.set_y(y4);
                        w.neue_bearbeitung(bo.text());
                    }
                    if(y5)
                    {
                        bo.set_y(y5);
                        w.neue_bearbeitung(bo.text());
                    }
                    if(y6)
                    {
                        bo.set_y(y6);
                        w.neue_bearbeitung(bo.text());
                    }

                    if(x2 > 0)
                    {
                        if(bo.bezug() == WST_BEZUG_LI)
                        {
                            bo.set_bezug(WST_BEZUG_RE);
                        }else
                        {
                            bo.set_bezug(WST_BEZUG_LI);
                        }
                        bo.set_x(x2);
                        if(y1)
                        {
                            bo.set_y(y1);
                            w.neue_bearbeitung(bo.text());
                        }
                        if(y2)
                        {
                            bo.set_y(y2);
                            w.neue_bearbeitung(bo.text());
                        }
                        if(y3)
                        {
                            bo.set_y(y3);
                            w.neue_bearbeitung(bo.text());
                        }
                        if(y4)
                        {
                            bo.set_y(y4);
                            w.neue_bearbeitung(bo.text());
                        }
                        if(y5)
                        {
                            bo.set_y(y5);
                            w.neue_bearbeitung(bo.text());
                        }
                        if(y6)
                        {
                            bo.set_y(y6);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_HBEXP_AFB)
                    {
                        bo.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_HBEXP_DM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bo.set_dm(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_HBEXP_TI)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bohrtiefe = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEXP_Z)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        z = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEXP_X1)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        x1 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEXP_X2)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        x2 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEXP_KM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        kettenmass = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEXP_Y1)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y1 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEXP_Y2)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y2 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEXP_Y3)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y3 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEXP_Y4)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y4 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEXP_Y5)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y5 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEXP_Y6)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y6 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }
                }
            }
        }else if(zeile.contains(FMC_HBEXM))
        {
            bohrung bo;
            double bohrtiefe = 0;
            double x1 = w.laenge();
            double x2 = -1;
            bool kettenmass = false;
            double y1 = 0;
            double y2 = 0;
            double y3 = 0;
            double y4 = 0;
            double y5 = 0;
            double y6 = 0;
            double z = 0;
            for(uint ii=i+1; ii<tz.count() ;ii++)
            {
                zeile = tz.at(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    //istOberseite und Kettenmaß ausweten:
                    if(istOberseite)
                    {
                        bo.set_bezug(WST_BEZUG_RE);
                        if(kettenmass == true)
                        {
                            double alt_y1 = y1;
                            double alt_y2 = y2;
                            double alt_y3 = y3;
                            double alt_y4 = y4;
                            double alt_y5 = y5;
                            double alt_y6 = y6;
                            if(y2)
                            {
                                y2 = alt_y1 + alt_y2;
                            }
                            if(y3)
                            {
                                y3 = alt_y1 + alt_y2 + alt_y3;
                            }
                            if(y4)
                            {
                                y4 = alt_y1 + alt_y2 + alt_y3 + alt_y4;
                            }
                            if(y5)
                            {
                                y5 = alt_y1 + alt_y2 + alt_y3 + alt_y4 + alt_y5;
                            }
                            if(y6)
                            {
                                y6 = alt_y1 + alt_y2 + alt_y3 + alt_y4 + alt_y5 + alt_y6;
                            }
                        }
                    }else
                    {
                        z = w.dicke() - z;
                        if(drehtyp_L)
                        {
                            bo.set_bezug(WST_BEZUG_LI);
                            x1 = w.laenge() - x1;
                            if(x2 > 0)
                            {
                                x2 = w.laenge() - x2;
                            }
                            if(kettenmass == true)
                            {
                                double alt_y1 = y1;
                                double alt_y2 = y2;
                                double alt_y3 = y3;
                                double alt_y4 = y4;
                                double alt_y5 = y5;
                                double alt_y6 = y6;
                                if(y2)
                                {
                                    y2 = alt_y1 + alt_y2;
                                }
                                if(y3)
                                {
                                    y3 = alt_y1 + alt_y2 + alt_y3;
                                }
                                if(y4)
                                {
                                    y4 = alt_y1 + alt_y2 + alt_y3 + alt_y4;
                                }
                                if(y5)
                                {
                                    y5 = alt_y1 + alt_y2 + alt_y3 + alt_y4 + alt_y5;
                                }
                                if(y6)
                                {
                                    y6 = alt_y1 + alt_y2 + alt_y3 + alt_y4 + alt_y5 + alt_y6;
                                }
                            }
                        }else //if(drehtyp_B)
                        {
                            bo.set_bezug(WST_BEZUG_RE);
                            if(kettenmass == true)
                            {
                                double alt_y1 = y1;
                                double alt_y2 = y2;
                                double alt_y3 = y3;
                                double alt_y4 = y4;
                                double alt_y5 = y5;
                                double alt_y6 = y6;
                                if(y1)
                                {
                                    y1 = w.breite() - alt_y1;
                                }
                                if(y2)
                                {
                                    y2 = w.breite() - (alt_y1 + alt_y2);
                                }
                                if(y3)
                                {
                                    y3 = w.breite() - (alt_y1 + alt_y2 + alt_y3);
                                }
                                if(y4)
                                {
                                    y4 = w.breite() - (alt_y1 + alt_y2 + alt_y3 + alt_y4);
                                }
                                if(y5)
                                {
                                    y5 = w.breite() - (alt_y1 + alt_y2 + alt_y3 + alt_y4 + alt_y5);
                                }
                                if(y6)
                                {
                                    y6 = w.breite() - (alt_y1 + alt_y2 + alt_y3 + alt_y4 + alt_y5 + alt_y6);
                                }
                            }else
                            {
                                if(y1)
                                {
                                    y1 = w.breite() - y1;
                                }
                                if(y2)
                                {
                                    y2 = w.breite() - y2;
                                }
                                if(y3)
                                {
                                    y3 = w.breite() - y3;
                                }
                                if(y4)
                                {
                                    y4 = w.breite() - y4;
                                }
                                if(y5)
                                {
                                    y5 = w.breite() - y5;
                                }
                                if(y6)
                                {
                                    y6 = w.breite() - y6;
                                }
                            }
                        }
                    }
                    //---
                    bo.set_tiefe(bohrtiefe);
                    bo.set_z(z);
                    bo.set_x(x1);
                    if(y1)
                    {
                        bo.set_y(y1);
                        w.neue_bearbeitung(bo.text());
                    }
                    if(y2)
                    {
                        bo.set_y(y2);
                        w.neue_bearbeitung(bo.text());
                    }
                    if(y3)
                    {
                        bo.set_y(y3);
                        w.neue_bearbeitung(bo.text());
                    }
                    if(y4)
                    {
                        bo.set_y(y4);
                        w.neue_bearbeitung(bo.text());
                    }
                    if(y5)
                    {
                        bo.set_y(y5);
                        w.neue_bearbeitung(bo.text());
                    }
                    if(y6)
                    {
                        bo.set_y(y6);
                        w.neue_bearbeitung(bo.text());
                    }

                    if(x2 > 0)
                    {
                        if(bo.bezug() == WST_BEZUG_LI)
                        {
                            bo.set_bezug(WST_BEZUG_RE);
                        }else
                        {
                            bo.set_bezug(WST_BEZUG_LI);
                        }
                        bo.set_x(x2);
                        if(y1)
                        {
                            bo.set_y(y1);
                            w.neue_bearbeitung(bo.text());
                        }
                        if(y2)
                        {
                            bo.set_y(y2);
                            w.neue_bearbeitung(bo.text());
                        }
                        if(y3)
                        {
                            bo.set_y(y3);
                            w.neue_bearbeitung(bo.text());
                        }
                        if(y4)
                        {
                            bo.set_y(y4);
                            w.neue_bearbeitung(bo.text());
                        }
                        if(y5)
                        {
                            bo.set_y(y5);
                            w.neue_bearbeitung(bo.text());
                        }
                        if(y6)
                        {
                            bo.set_y(y6);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_HBEXP_AFB)
                    {
                        bo.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_HBEXP_DM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bo.set_dm(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_HBEXP_TI)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bohrtiefe = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEXP_Z)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        z = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEXP_X1)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        x1 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEXP_X2)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        x2 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEXP_KM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        kettenmass = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEXP_Y1)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y1 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEXP_Y2)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y2 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEXP_Y3)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y3 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEXP_Y4)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y4 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEXP_Y5)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y5 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEXP_Y6)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y6 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }
                }
            }
        }else if(zeile.contains(FMC_HBEYP))
        {
            bohrung bo;
            double bohrtiefe = 0;
            double y1 = 0;
            double y2 = -1;
            bool kettenmass = false;
            double x1 = 0;
            double x2 = 0;
            double x3 = 0;
            double x4 = 0;
            double x5 = 0;
            double x6 = 0;
            double z = 0;
            for(uint ii=i+1; ii<tz.count() ;ii++)
            {
                zeile = tz.at(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    //istOberseite und Kettenmaß ausweten:
                    if(istOberseite)
                    {
                        bo.set_bezug(WST_BEZUG_VO);
                        if(kettenmass == true)
                        {
                            double alt_x1 = x1;
                            double alt_x2 = x2;
                            double alt_x3 = x3;
                            double alt_x4 = x4;
                            double alt_x5 = x5;
                            double alt_x6 = x6;
                            if(x2)
                            {
                                x2 = alt_x1 + alt_x2;
                            }
                            if(x3)
                            {
                                x3 = alt_x1 + alt_x2 + alt_x3;
                            }
                            if(x4)
                            {
                                x4 = alt_x1 + alt_x2 + alt_x3 + alt_x4;
                            }
                            if(x5)
                            {
                                x5 = alt_x1 + alt_x2 + alt_x3 + alt_x4 + alt_x5;
                            }
                            if(x6)
                            {
                                x6 = alt_x1 + alt_x2 + alt_x3 + alt_x4 + alt_x5 + alt_x6;
                            }
                        }
                    }else
                    {
                        z = w.dicke() - z;
                        if(drehtyp_L)
                        {
                            bo.set_bezug(WST_BEZUG_VO);
                            if(kettenmass == true)
                            {
                                double alt_x1 = x1;
                                double alt_x2 = x2;
                                double alt_x3 = x3;
                                double alt_x4 = x4;
                                double alt_x5 = x5;
                                double alt_x6 = x6;
                                if(x1)
                                {
                                    x1 = w.laenge() - alt_x1;
                                }
                                if(x2)
                                {
                                    x2 = w.laenge() - (alt_x1 + alt_x2);
                                }
                                if(x3)
                                {
                                    x3 = w.laenge() - (alt_x1 + alt_x2 + alt_x3);
                                }
                                if(x4)
                                {
                                    x4 = w.laenge() - (alt_x1 + alt_x2 + alt_x3 + alt_x4);
                                }
                                if(x5)
                                {
                                    x5 = w.laenge() - (alt_x1 + alt_x2 + alt_x3 + alt_x4 + alt_x5);
                                }
                                if(x6)
                                {
                                    x6 = w.laenge() - (alt_x1 + alt_x2 + alt_x3 + alt_x4 + alt_x5 + alt_x6);
                                }
                            }else
                            {
                                if(x1)
                                {
                                    x1 = w.laenge() - x1;
                                }
                                if(x2)
                                {
                                    x2 = w.laenge() - x2;
                                }
                                if(x3)
                                {
                                    x3 = w.laenge() - x3;
                                }
                                if(x4)
                                {
                                    x4 = w.laenge() - x4;
                                }
                                if(x5)
                                {
                                    x5 = w.laenge() - x5;
                                }
                                if(x6)
                                {
                                    x6 = w.laenge() - x6;
                                }
                            }

                        }else //if(drehtyp_B)
                        {
                            bo.set_bezug(WST_BEZUG_HI);
                            y1 = w.breite() - y1;
                            if(y2 > 0)
                            {
                                y2 = w.breite() - y2;
                            }
                            if(kettenmass == true)
                            {
                                double alt_x1 = x1;
                                double alt_x2 = x2;
                                double alt_x3 = x3;
                                double alt_x4 = x4;
                                double alt_x5 = x5;
                                double alt_x6 = x6;
                                if(x2)
                                {
                                    x2 = alt_x1 + alt_x2;
                                }
                                if(x3)
                                {
                                    x3 = alt_x1 + alt_x2 + alt_x3;
                                }
                                if(x4)
                                {
                                    x4 = alt_x1 + alt_x2 + alt_x3 + alt_x4;
                                }
                                if(x5)
                                {
                                    x5 = alt_x1 + alt_x2 + alt_x3 + alt_x4 + alt_x5;
                                }
                                if(x6)
                                {
                                    x6 = alt_x1 + alt_x2 + alt_x3 + alt_x4 + alt_x5 + alt_x6;
                                }
                            }
                        }
                    }
                    //---
                    bo.set_tiefe(bohrtiefe);
                    bo.set_z(z);
                    bo.set_y(y1);
                    if(x1)
                    {
                        bo.set_x(x1);
                        w.neue_bearbeitung(bo.text());
                    }
                    if(x2)
                    {
                        bo.set_x(x2);
                        w.neue_bearbeitung(bo.text());
                    }
                    if(x3)
                    {
                        bo.set_x(x3);
                        w.neue_bearbeitung(bo.text());
                    }
                    if(x4)
                    {
                        bo.set_x(x4);
                        w.neue_bearbeitung(bo.text());
                    }
                    if(x5)
                    {
                        bo.set_x(x5);
                        w.neue_bearbeitung(bo.text());
                    }
                    if(x6)
                    {
                        bo.set_x(x6);
                        w.neue_bearbeitung(bo.text());
                    }

                    if(y2 > 0)
                    {
                        if(bo.bezug() == WST_BEZUG_VO)
                        {
                            bo.set_bezug(WST_BEZUG_HI);
                        }else
                        {
                            bo.set_bezug(WST_BEZUG_VO);
                        }
                        bo.set_y(y2);
                        if(x1)
                        {
                            bo.set_x(x1);
                            w.neue_bearbeitung(bo.text());
                        }
                        if(x2)
                        {
                            bo.set_x(x2);
                            w.neue_bearbeitung(bo.text());
                        }
                        if(x3)
                        {
                            bo.set_x(x3);
                            w.neue_bearbeitung(bo.text());
                        }
                        if(x4)
                        {
                            bo.set_x(x4);
                            w.neue_bearbeitung(bo.text());
                        }
                        if(x5)
                        {
                            bo.set_x(x5);
                            w.neue_bearbeitung(bo.text());
                        }
                        if(x6)
                        {
                            bo.set_x(x6);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_HBEYP_AFB)
                    {
                        bo.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_HBEYP_DM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bo.set_dm(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_HBEYP_TI)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bohrtiefe = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEYP_Z)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        z = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEXP_Y1)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        y1 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEXP_Y2)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        y2 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEYP_KM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        kettenmass = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEYP_X1)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x1 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEYP_X2)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x2 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEYP_X3)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x3 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEYP_X4)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x4 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEYP_X5)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x5 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEYP_X6)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x6 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }
                }
            }
        }else if(zeile.contains(FMC_HBEYM))
        {
            bohrung bo;
            double bohrtiefe = 0;
            double y1 = 0;
            double y2 = -1;
            bool kettenmass = false;
            double x1 = 0;
            double x2 = 0;
            double x3 = 0;
            double x4 = 0;
            double x5 = 0;
            double x6 = 0;
            double z = 0;
            for(uint ii=i+1; ii<tz.count() ;ii++)
            {
                zeile = tz.at(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    //istOberseite und Kettenmaß ausweten:
                    if(istOberseite)
                    {
                        bo.set_bezug(WST_BEZUG_HI);
                        if(kettenmass == true)
                        {
                            double alt_x1 = x1;
                            double alt_x2 = x2;
                            double alt_x3 = x3;
                            double alt_x4 = x4;
                            double alt_x5 = x5;
                            double alt_x6 = x6;
                            if(x2)
                            {
                                x2 = alt_x1 + alt_x2;
                            }
                            if(x3)
                            {
                                x3 = alt_x1 + alt_x2 + alt_x3;
                            }
                            if(x4)
                            {
                                x4 = alt_x1 + alt_x2 + alt_x3 + alt_x4;
                            }
                            if(x5)
                            {
                                x5 = alt_x1 + alt_x2 + alt_x3 + alt_x4 + alt_x5;
                            }
                            if(x6)
                            {
                                x6 = alt_x1 + alt_x2 + alt_x3 + alt_x4 + alt_x5 + alt_x6;
                            }
                        }
                    }else
                    {
                        z = w.dicke() - z;
                        if(drehtyp_L)
                        {
                            bo.set_bezug(WST_BEZUG_HI);
                            if(kettenmass == true)
                            {
                                double alt_x1 = x1;
                                double alt_x2 = x2;
                                double alt_x3 = x3;
                                double alt_x4 = x4;
                                double alt_x5 = x5;
                                double alt_x6 = x6;
                                if(x1)
                                {
                                    x1 = w.laenge() - alt_x1;
                                }
                                if(x2)
                                {
                                    x2 = w.laenge() - (alt_x1 + alt_x2);
                                }
                                if(x3)
                                {
                                    x3 = w.laenge() - (alt_x1 + alt_x2 + alt_x3);
                                }
                                if(x4)
                                {
                                    x4 = w.laenge() - (alt_x1 + alt_x2 + alt_x3 + alt_x4);
                                }
                                if(x5)
                                {
                                    x5 = w.laenge() - (alt_x1 + alt_x2 + alt_x3 + alt_x4 + alt_x5);
                                }
                                if(x6)
                                {
                                    x6 = w.laenge() - (alt_x1 + alt_x2 + alt_x3 + alt_x4 + alt_x5 + alt_x6);
                                }
                            }else
                            {
                                if(x1)
                                {
                                    x1 = w.laenge() - x1;
                                }
                                if(x2)
                                {
                                    x2 = w.laenge() - x2;
                                }
                                if(x3)
                                {
                                    x3 = w.laenge() - x3;
                                }
                                if(x4)
                                {
                                    x4 = w.laenge() - x4;
                                }
                                if(x5)
                                {
                                    x5 = w.laenge() - x5;
                                }
                                if(x6)
                                {
                                    x6 = w.laenge() - x6;
                                }
                            }

                        }else //if(drehtyp_B)
                        {
                            bo.set_bezug(WST_BEZUG_VO);
                            y1 = w.breite() - y1;
                            if(y2 > 0)
                            {
                                y2 = w.breite() - y2;
                            }
                            if(kettenmass == true)
                            {
                                double alt_x1 = x1;
                                double alt_x2 = x2;
                                double alt_x3 = x3;
                                double alt_x4 = x4;
                                double alt_x5 = x5;
                                double alt_x6 = x6;
                                if(x2)
                                {
                                    x2 = alt_x1 + alt_x2;
                                }
                                if(x3)
                                {
                                    x3 = alt_x1 + alt_x2 + alt_x3;
                                }
                                if(x4)
                                {
                                    x4 = alt_x1 + alt_x2 + alt_x3 + alt_x4;
                                }
                                if(x5)
                                {
                                    x5 = alt_x1 + alt_x2 + alt_x3 + alt_x4 + alt_x5;
                                }
                                if(x6)
                                {
                                    x6 = alt_x1 + alt_x2 + alt_x3 + alt_x4 + alt_x5 + alt_x6;
                                }
                            }
                        }
                    }
                    //---
                    bo.set_tiefe(bohrtiefe);
                    bo.set_z(z);
                    bo.set_y(y1);
                    if(x1)
                    {
                        bo.set_x(x1);
                        w.neue_bearbeitung(bo.text());
                    }
                    if(x2)
                    {
                        bo.set_x(x2);
                        w.neue_bearbeitung(bo.text());
                    }
                    if(x3)
                    {
                        bo.set_x(x3);
                        w.neue_bearbeitung(bo.text());
                    }
                    if(x4)
                    {
                        bo.set_x(x4);
                        w.neue_bearbeitung(bo.text());
                    }
                    if(x5)
                    {
                        bo.set_x(x5);
                        w.neue_bearbeitung(bo.text());
                    }
                    if(x6)
                    {
                        bo.set_x(x6);
                        w.neue_bearbeitung(bo.text());
                    }

                    if(y2 > 0)
                    {
                        if(bo.bezug() == WST_BEZUG_VO)
                        {
                            bo.set_bezug(WST_BEZUG_HI);
                        }else
                        {
                            bo.set_bezug(WST_BEZUG_VO);
                        }
                        bo.set_y(y2);
                        if(x1)
                        {
                            bo.set_x(x1);
                            w.neue_bearbeitung(bo.text());
                        }
                        if(x2)
                        {
                            bo.set_x(x2);
                            w.neue_bearbeitung(bo.text());
                        }
                        if(x3)
                        {
                            bo.set_x(x3);
                            w.neue_bearbeitung(bo.text());
                        }
                        if(x4)
                        {
                            bo.set_x(x4);
                            w.neue_bearbeitung(bo.text());
                        }
                        if(x5)
                        {
                            bo.set_x(x5);
                            w.neue_bearbeitung(bo.text());
                        }
                        if(x6)
                        {
                            bo.set_x(x6);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_HBEYP_AFB)
                    {
                        bo.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_HBEYP_DM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bo.set_dm(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_HBEYP_TI)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bohrtiefe = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEYP_Z)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        z = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEXP_Y1)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        y1 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEXP_Y2)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        y2 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEYP_KM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        kettenmass = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEYP_X1)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x1 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEYP_X2)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x2 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEYP_X3)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x3 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEYP_X4)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x4 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEYP_X5)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x5 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEYP_X6)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x6 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }
                }
            }
        }else if(zeile.contains(FMC_BOBIY))
        {
            bohrung bo;
            double x1 = 0;
            double x2 = -1;
            bool kettenmass = false;
            double y1 = 0;
            double y2 = 0;
            double y3 = 0;
            double y4 = 0;
            double y5 = 0;
            double y6 = 0;
            for(uint ii=i+1; ii<tz.count() ;ii++)
            {
                zeile = tz.at(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    //istOberseite und Kettenmaß ausweten:
                    if(istOberseite)
                    {
                        bo.set_bezug(WST_BEZUG_OBSEI);
                        bo.set_z(w.dicke());
                        if(kettenmass == true)
                        {
                            double alt_y1 = y1;
                            double alt_y2 = y2;
                            double alt_y3 = y3;
                            double alt_y4 = y4;
                            double alt_y5 = y5;
                            double alt_y6 = y6;
                            if(y2)
                            {
                                y2 = alt_y1 + alt_y2;
                            }
                            if(y3)
                            {
                                y3 = alt_y1 + alt_y2 + alt_y3;
                            }
                            if(y4)
                            {
                                y4 = alt_y1 + alt_y2 + alt_y3 + alt_y4;
                            }
                            if(y5)
                            {
                                y5 = alt_y1 + alt_y2 + alt_y3 + alt_y4 + alt_y5;
                            }
                            if(y6)
                            {
                                y6 = alt_y1 + alt_y2 + alt_y3 + alt_y4 + alt_y5 + alt_y6;
                            }
                        }
                    }else
                    {
                        bo.set_bezug(WST_BEZUG_UNSEI);
                        bo.set_z(0);
                        if(drehtyp_L)
                        {
                            x1 = w.laenge() - x1;
                            if(x2 > 0)
                            {
                                x2 = w.laenge() - x2;
                            }
                            if(kettenmass == true)
                            {
                                double alt_y1 = y1;
                                double alt_y2 = y2;
                                double alt_y3 = y3;
                                double alt_y4 = y4;
                                double alt_y5 = y5;
                                double alt_y6 = y6;
                                if(y2)
                                {
                                    y2 = alt_y1 + alt_y2;
                                }
                                if(y3)
                                {
                                    y3 = alt_y1 + alt_y2 + alt_y3;
                                }
                                if(y4)
                                {
                                    y4 = alt_y1 + alt_y2 + alt_y3 + alt_y4;
                                }
                                if(y5)
                                {
                                    y5 = alt_y1 + alt_y2 + alt_y3 + alt_y4 + alt_y5;
                                }
                                if(y6)
                                {
                                    y6 = alt_y1 + alt_y2 + alt_y3 + alt_y4 + alt_y5 + alt_y6;
                                }
                            }
                        }else //if(drehtyp_B)
                        {
                            if(kettenmass == true)
                            {
                                double alt_y1 = y1;
                                double alt_y2 = y2;
                                double alt_y3 = y3;
                                double alt_y4 = y4;
                                double alt_y5 = y5;
                                double alt_y6 = y6;
                                if(y1)
                                {
                                    y1 = w.breite() - alt_y1;
                                }
                                if(y2)
                                {
                                    y2 = w.breite() - (alt_y1 + alt_y2);
                                }
                                if(y3)
                                {
                                    y3 = w.breite() - (alt_y1 + alt_y2 + alt_y3);
                                }
                                if(y4)
                                {
                                    y4 = w.breite() - (alt_y1 + alt_y2 + alt_y3 + alt_y4);
                                }
                                if(y5)
                                {
                                    y5 = w.breite() - (alt_y1 + alt_y2 + alt_y3 + alt_y4 + alt_y5);
                                }
                                if(y6)
                                {
                                    y6 = w.breite() - (alt_y1 + alt_y2 + alt_y3 + alt_y4 + alt_y5 + alt_y6);
                                }
                            }else
                            {
                                if(y1)
                                {
                                    y1 = w.breite() - y1;
                                }
                                if(y2)
                                {
                                    y2 = w.breite() - y2;
                                }
                                if(y3)
                                {
                                    y3 = w.breite() - y3;
                                }
                                if(y4)
                                {
                                    y4 = w.breite() - y4;
                                }
                                if(y5)
                                {
                                    y5 = w.breite() - y5;
                                }
                                if(y6)
                                {
                                    y6 = w.breite() - y6;
                                }
                            }
                        }
                    }
                    //---
                    bo.set_x(x1);
                    if(y1)
                    {
                        bo.set_y(y1);
                        w.neue_bearbeitung(bo.text());
                    }
                    if(y2)
                    {
                        bo.set_y(y2);
                        w.neue_bearbeitung(bo.text());
                    }
                    if(y3)
                    {
                        bo.set_y(y3);
                        w.neue_bearbeitung(bo.text());
                    }
                    if(y4)
                    {
                        bo.set_y(y4);
                        w.neue_bearbeitung(bo.text());
                    }
                    if(y5)
                    {
                        bo.set_y(y5);
                        w.neue_bearbeitung(bo.text());
                    }
                    if(y6)
                    {
                        bo.set_y(y6);
                        w.neue_bearbeitung(bo.text());
                    }

                    if(x2 > 0)
                    {
                        bo.set_x(x2);
                        if(y1)
                        {
                            bo.set_y(y1);
                            w.neue_bearbeitung(bo.text());
                        }
                        if(y2)
                        {
                            bo.set_y(y2);
                            w.neue_bearbeitung(bo.text());
                        }
                        if(y3)
                        {
                            bo.set_y(y3);
                            w.neue_bearbeitung(bo.text());
                        }
                        if(y4)
                        {
                            bo.set_y(y4);
                            w.neue_bearbeitung(bo.text());
                        }
                        if(y5)
                        {
                            bo.set_y(y5);
                            w.neue_bearbeitung(bo.text());
                        }
                        if(y6)
                        {
                            bo.set_y(y6);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_BOBIY_AFB)
                    {
                        bo.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_BOBIY_DM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bo.set_dm(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_BOBIY_TI)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        bo.set_tiefe(tmp);
                    }else if(schluessel == FMC_BOBIY_X1)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        x1 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_BOBIY_X2)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        if(tmp.contains("X1"))
                        {
                            tmp.replace("X1",double_to_qstring(x1));
                        }
                        tmp = var_einsetzen(w, tmp);
                        x2 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_BOBIY_KM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        kettenmass = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_BOBIY_Y1)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y1 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_BOBIY_Y2)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y2 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_BOBIY_Y3)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y3 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_BOBIY_Y4)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y4 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_BOBIY_Y5)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y5 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_BOBIY_Y6)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y6 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }
                }
            }
        }else if(zeile.contains(FMC_BOBIX))
        {
            bohrung bo;
            double y1 = 0;
            double y2 = -1;
            bool kettenmass = false;
            double x1 = 0;
            double x2 = 0;
            double x3 = 0;
            double x4 = 0;
            double x5 = 0;
            double x6 = 0;
            for(uint ii=i+1; ii<tz.count() ;ii++)
            {
                zeile = tz.at(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    zeile = tz.at(ii);
                    if(!zeile.contains("=")) //Ende des Abschnittes
                    {
                        i=ii-1;
                        //istOberseite und Kettenmaß ausweten:
                        if(istOberseite)
                        {
                            bo.set_bezug(WST_BEZUG_OBSEI);
                            bo.set_z(w.dicke());
                            if(kettenmass == true)
                            {
                                double alt_x1 = x1;
                                double alt_x2 = x2;
                                double alt_x3 = x3;
                                double alt_x4 = x4;
                                double alt_x5 = x5;
                                double alt_x6 = x6;
                                if(x2)
                                {
                                    x2 = alt_x1 + alt_x2;
                                }
                                if(x3)
                                {
                                    x3 = alt_x1 + alt_x2 + alt_x3;
                                }
                                if(x4)
                                {
                                    x4 = alt_x1 + alt_x2 + alt_x3 + alt_x4;
                                }
                                if(x5)
                                {
                                    x5 = alt_x1 + alt_x2 + alt_x3 + alt_x4 + alt_x5;
                                }
                                if(x6)
                                {
                                    x6 = alt_x1 + alt_x2 + alt_x3 + alt_x4 + alt_x5 + alt_x6;
                                }
                            }
                        }else
                        {
                            bo.set_bezug(WST_BEZUG_UNSEI);
                            bo.set_z(0);
                            if(drehtyp_L)
                            {
                                if(kettenmass == true)
                                {
                                    double alt_x1 = x1;
                                    double alt_x2 = x2;
                                    double alt_x3 = x3;
                                    double alt_x4 = x4;
                                    double alt_x5 = x5;
                                    double alt_x6 = x6;
                                    if(x1)
                                    {
                                        x1 = w.laenge() - alt_x1;
                                    }
                                    if(x2)
                                    {
                                        x2 = w.laenge() - (alt_x1 + alt_x2);
                                    }
                                    if(x3)
                                    {
                                        x3 = w.laenge() - (alt_x1 + alt_x2 + alt_x3);
                                    }
                                    if(x4)
                                    {
                                        x4 = w.laenge() - (alt_x1 + alt_x2 + alt_x3 + alt_x4);
                                    }
                                    if(x5)
                                    {
                                        x5 = w.laenge() - (alt_x1 + alt_x2 + alt_x3 + alt_x4 + alt_x5);
                                    }
                                    if(x6)
                                    {
                                        x6 = w.laenge() - (alt_x1 + alt_x2 + alt_x3 + alt_x4 + alt_x5 + alt_x6);
                                    }
                                }else
                                {
                                    if(x1)
                                    {
                                        x1 = w.laenge() - x1;
                                    }
                                    if(x2)
                                    {
                                        x2 = w.laenge() - x2;
                                    }
                                    if(x3)
                                    {
                                        x3 = w.laenge() - x3;
                                    }
                                    if(x4)
                                    {
                                        x4 = w.laenge() - x4;
                                    }
                                    if(x5)
                                    {
                                        x5 = w.laenge() - x5;
                                    }
                                    if(x6)
                                    {
                                        x6 = w.laenge() - x6;
                                    }
                                }

                            }else //if(drehtyp_B)
                            {
                                y1 = w.breite() - y1;
                                if(y2 > 0)
                                {
                                    y2 = w.breite() - y2;
                                }
                                if(kettenmass == true)
                                {
                                    double alt_x1 = x1;
                                    double alt_x2 = x2;
                                    double alt_x3 = x3;
                                    double alt_x4 = x4;
                                    double alt_x5 = x5;
                                    double alt_x6 = x6;
                                    if(x2)
                                    {
                                        x2 = alt_x1 + alt_x2;
                                    }
                                    if(x3)
                                    {
                                        x3 = alt_x1 + alt_x2 + alt_x3;
                                    }
                                    if(x4)
                                    {
                                        x4 = alt_x1 + alt_x2 + alt_x3 + alt_x4;
                                    }
                                    if(x5)
                                    {
                                        x5 = alt_x1 + alt_x2 + alt_x3 + alt_x4 + alt_x5;
                                    }
                                    if(x6)
                                    {
                                        x6 = alt_x1 + alt_x2 + alt_x3 + alt_x4 + alt_x5 + alt_x6;
                                    }
                                }
                            }
                        }
                        //---
                        bo.set_y(y1);
                        if(x1)
                        {
                            bo.set_x(x1);
                            w.neue_bearbeitung(bo.text());
                        }
                        if(x2)
                        {
                            bo.set_x(x2);
                            w.neue_bearbeitung(bo.text());
                        }
                        if(x3)
                        {
                            bo.set_x(x3);
                            w.neue_bearbeitung(bo.text());
                        }
                        if(x4)
                        {
                            bo.set_x(x4);
                            w.neue_bearbeitung(bo.text());
                        }
                        if(x5)
                        {
                            bo.set_x(x5);
                            w.neue_bearbeitung(bo.text());
                        }
                        if(x6)
                        {
                            bo.set_x(x6);
                            w.neue_bearbeitung(bo.text());
                        }

                        if(y2 > 0)
                        {
                            bo.set_x(x2);
                            if(x1)
                            {
                                bo.set_x(x1);
                                w.neue_bearbeitung(bo.text());
                            }
                            if(x2)
                            {
                                bo.set_x(x2);
                                w.neue_bearbeitung(bo.text());
                            }
                            if(x3)
                            {
                                bo.set_x(x3);
                                w.neue_bearbeitung(bo.text());
                            }
                            if(x4)
                            {
                                bo.set_x(x4);
                                w.neue_bearbeitung(bo.text());
                            }
                            if(x5)
                            {
                                bo.set_x(x5);
                                w.neue_bearbeitung(bo.text());
                            }
                            if(x6)
                            {
                                bo.set_x(x6);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        break;
                    }
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_BOBIX_AFB)
                    {
                        bo.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_BOBIX_DM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bo.set_dm(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_BOBIX_TI)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        bo.set_tiefe(tmp);
                    }else if(schluessel == FMC_BOBIX_Y1)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        y1 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_BOBIX_Y2)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        if(tmp.contains("Y1"))
                        {
                            tmp.replace("Y1",double_to_qstring(x1));
                        }
                        tmp = var_einsetzen(w, tmp);
                        y2 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_BOBIX_KM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        kettenmass = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_BOBIX_X1)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x1 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_BOBIX_X2)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x2 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_BOBIX_X3)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x3 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_BOBIX_X4)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x4 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_BOBIX_X5)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x5 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_BOBIX_X6)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x6 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }
                }
            }
        }else if(zeile.contains(FMC_KTA))
        {
            bohrung bo;
            double x = 0;
            double y = 0;
            for(uint ii=i+1; ii<tz.count() ;ii++)
            {
                zeile = tz.at(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    if(istOberseite)
                    {
                        bo.set_bezug(WST_BEZUG_OBSEI);
                        bo.set_x(x);
                        bo.set_y(y);
                        bo.set_z(w.dicke());
                    }else
                    {
                        bo.set_bezug(WST_BEZUG_UNSEI);
                        if(drehtyp_L)
                        {
                            bo.set_x(w.laenge()-x);
                            bo.set_y(y);
                        }else //if(drehtyp_B)
                        {
                            bo.set_x(x);
                            bo.set_y(w.breite()-y);
                        }
                        bo.set_z(0);
                    }
                    w.neue_bearbeitung(bo.text());
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_KTA_AFB)
                    {
                        bo.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_KTA_DM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        bo.set_dm(tmp);
                    }else if(schluessel == FMC_KTA_TI)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        double tiefe = ausdruck_auswerten(tmp).toDouble();
                        if(tiefe < 0)
                        {
                            tiefe = w.dicke() - tiefe;
                        }
                        bo.set_tiefe(tiefe);
                    }else if(schluessel == FMC_KTA_X)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        x = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_KTA_Y)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        y = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_KTA_ZUST)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        bo.set_zustellmass(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_KTA_WKZ)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        bo.set_wkznum(tmp);
                    }
                }
            }
        }else if(zeile.contains(FMC_RTA))
        {
            rechtecktasche rt;
            double x = 0;
            double y = 0;
            double wi = 0;
            for(uint ii=i+1; ii<tz.count() ;ii++)
            {
                zeile = tz.at(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    if(istOberseite)
                    {
                        rt.set_bezug(WST_BEZUG_OBSEI);
                        rt.set_x(x);
                        rt.set_y(y);
                        rt.set_z(w.dicke());
                    }else
                    {
                        rt.set_bezug(WST_BEZUG_UNSEI);
                        if(drehtyp_L)
                        {
                            rt.set_x(w.laenge()-x);
                            rt.set_y(y);
                        }else //if(drehtyp_B)
                        {
                            rt.set_x(x);
                            rt.set_y(w.breite()-y);                            
                        }
                        if(wi > 180)
                        {
                            wi = wi -180;
                        }
                        wi = 180 - wi;
                        rt.set_z(0);
                    }
                    rt.set_drewi(wi);
                    w.neue_bearbeitung(rt.text());
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_RTA_AFB)
                    {
                        rt.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_RTA_L)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        rt.set_laenge(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_RTA_B)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        rt.set_breite(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_RTA_TI)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        double tiefe = ausdruck_auswerten(tmp).toDouble();
                        if(tiefe < 0)
                        {
                            tiefe = w.dicke() - tiefe;
                        }
                        rt.set_tiefe(tiefe);
                    }else if(schluessel == FMC_RTA_X)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        x = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_RTA_Y)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        y = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_RTA_ZUST)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        rt.set_zustellmass(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_RTA_WI)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        wi = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_RTA_RAD)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        rt.set_rad(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_RTA_RAEUM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        rt.set_ausraeumen(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_RTA_WKZ)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        rt.set_wkznum(tmp);
                    }
                }
            }
        }else if(zeile.contains(FMC_NUT))
        {
            nut n;
            punkt3d stapu, endpu;
            for(uint ii=i+1; ii<tz.count() ;ii++)
            {
                zeile = tz.at(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    if(istOberseite)
                    {
                        n.set_bezug(WST_BEZUG_OBSEI);
                        stapu.set_z(w.dicke());
                        endpu.set_z(w.dicke());
                        n.set_stapu(stapu);
                        n.set_endpu(endpu);
                    }else
                    {
                        n.set_bezug(WST_BEZUG_UNSEI);
                        stapu.set_z(0);
                        endpu.set_z(0);
                        if(drehtyp_L)
                        {
                            stapu.set_x(w.laenge()-stapu.x());
                            endpu.set_x(w.laenge()-endpu.x());
                        }else //if(drehtyp_B)
                        {
                            stapu.set_y(w.breite()-stapu.y());
                            endpu.set_y(w.breite()-endpu.y());
                        }
                        n.set_stapu(stapu);
                        n.set_endpu(endpu);
                    }
                    w.neue_bearbeitung(n.text());
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_NUT_AFB)
                    {
                        n.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_NUT_TI)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        n.set_tiefe(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_NUT_BR)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        n.set_breite(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_NUT_XS)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        stapu.set_x(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_NUT_YS)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        stapu.set_y(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_NUT_XE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        endpu.set_x(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_NUT_YE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        endpu.set_y(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_NUT_KOR)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        QString kor = ausdruck_auswerten(tmp);
                        if(kor.toInt() != 0)//Korrektur nach links
                        {
                            strecke s;
                            s.set_stapu(stapu);
                            s.set_endpu(endpu);
                            strecke stmp = s;
                            stmp.set_laenge_2d(n.breite()/2, strecke_bezugspunkt_start);
                            if(kor.toInt() == 1)//Korrektur nach links
                            {
                                stmp.drenen_um_endpu_2d(90, true);
                            }else //if(kor.toInt() == 2)//Korrektur nach rechts
                            {
                                stmp.drenen_um_endpu_2d(90, false);
                            }
                            s.verschieben_um(stmp.stapu().x()-s.stapu().x(), stmp.stapu().y()-s.stapu().y());
                            stapu.x();
                            stapu.y();
                            endpu.x();
                            endpu.y();
                        }
                    }
                }
            }
        }else if(zeile.contains(FMC_LORAE))
        {
            bohrung bo;
            double xs = 0;
            double xe = 0;
            double y1 = 0;
            double y2 = 0;
            double raster = 32;
            for(uint ii=i+1; ii<tz.count() ;ii++)
            {
                zeile = tz.at(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii;
                    if(istOberseite)
                    {
                        bo.set_bezug(WST_BEZUG_OBSEI);
                        bo.set_z(w.dicke());
                    }else
                    {
                        bo.set_bezug(WST_BEZUG_UNSEI);
                        if(drehtyp_L)
                        {
                            xs = w.laenge()-xs;
                            xe = w.laenge()-xe;
                        }else //if(drehtyp_B)
                        {
                            if(y1 != 0)
                            {
                                y1 = w.breite()-y1;
                            }
                            if(y2 != 0)
                            {
                                y2 = w.breite()-y2;
                            }
                        }
                        bo.set_z(0);
                    }
                    if(xe < xs)
                    {
                        double tmp;
                        tmp = xe;
                        xe = xs;
                        xs = tmp;
                    }
                    if(y1 != 0)
                    {
                        bo.set_y(y1);
                        double tmp_x = xs;
                        while(tmp_x <= xe)
                        {
                            bo.set_x(tmp_x);
                            w.neue_bearbeitung(bo.text());
                            tmp_x = tmp_x + raster;
                        }
                    }
                    if(y2 != 0)
                    {
                        bo.set_y(y2);
                        double tmp_x = xs;
                        while(tmp_x <= xe)
                        {
                            bo.set_x(tmp_x);
                            w.neue_bearbeitung(bo.text());
                            tmp_x = tmp_x + raster;
                        }
                    }
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_LORAE_AFB)
                    {
                        bo.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_LORAE_DM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bo.set_dm(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_LORAE_DM_)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bo.set_dm(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_LORAE_TI)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        double tiefe = ausdruck_auswerten(tmp).toDouble();
                        if(tiefe < 0)
                        {
                            tiefe = w.dicke() - tiefe;
                        }
                        bo.set_tiefe(tiefe);
                    }else if(schluessel == FMC_LORAE_XS)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        xs = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_LORAE_XE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp.replace("SX", double_to_qstring(xs));
                        xe = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_LORAE_Y1)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        y1 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_LORAE_Y2)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp.replace("Y1", double_to_qstring(y1));
                        y2 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_LORAE_RASTER)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        raster = ausdruck_auswerten(tmp).toDouble();
                    }
                }
            }
        }else if(zeile.contains(FMC_LORAM))
        {
            bohrung bo;
            double xs = 0;
            double xm = 0;
            double y1 = 0;
            double y2 = 0;
            double raster = 32;
            for(uint ii=i+1; ii<tz.count() ;ii++)
            {
                zeile = tz.at(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    double diff = xm - xs;
                    double xe = xm + diff;
                    if(istOberseite)
                    {
                        bo.set_bezug(WST_BEZUG_OBSEI);
                        bo.set_z(w.dicke());
                    }else
                    {
                        bo.set_bezug(WST_BEZUG_UNSEI);
                        if(drehtyp_L)
                        {
                            xs = w.laenge()-xs;
                            xe = w.laenge()-xe;
                        }else //if(drehtyp_B)
                        {
                            if(y1 != 0)
                            {
                                y1 = w.breite()-y1;
                            }
                            if(y2 != 0)
                            {
                                y2 = w.breite()-y2;
                            }
                        }
                        bo.set_z(0);
                    }
                    if(xe < xs)
                    {
                        double tmp;
                        tmp = xe;
                        xe = xs;
                        xs = tmp;
                    }
                    if(y1 != 0)
                    {
                        bo.set_y(y1);
                        double tmp_x = xs;
                        while(tmp_x <= xe)
                        {
                            bo.set_x(tmp_x);
                            w.neue_bearbeitung(bo.text());
                            tmp_x = tmp_x + raster;
                        }
                    }
                    if(y2 != 0)
                    {
                        bo.set_y(y2);
                        double tmp_x = xs;
                        while(tmp_x <= xe)
                        {
                            bo.set_x(tmp_x);
                            w.neue_bearbeitung(bo.text());
                            tmp_x = tmp_x + raster;
                        }
                    }

                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_LORAM_AFB)
                    {
                        bo.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_LORAM_DM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bo.set_dm(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_LORAM_DM_)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bo.set_dm(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_LORAM_TI   || \
                             schluessel == FMC_LORAM_TI_     )
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        double tiefe = ausdruck_auswerten(tmp).toDouble();
                        if(tiefe < 0)
                        {
                            tiefe = w.dicke() - tiefe;
                        }
                        bo.set_tiefe(tiefe);
                    }else if(schluessel == FMC_LORAM_XS)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        xs = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_LORAM_XM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        xm = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_LORAM_Y1)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        y1 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_LORAM_Y2)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp.replace("Y1", double_to_qstring(y1));
                        y2 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_LORAM_RASTER  || \
                             schluessel == FMC_LORAM_RASTER_)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        raster = ausdruck_auswerten(tmp).toDouble();
                    }
                }
            }
        }else if(zeile.contains(FMC_FKON))
        {
            fraeseraufruf fa;
            double x = 0;
            double y = 0;
            for(uint ii=i+1; ii<tz.count() ;ii++)
            {
                zeile = tz.at(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    orginal_x = x;
                    orginal_y = y;
                    if(istOberseite)
                    {
                        fa.set_bezug(WST_BEZUG_OBSEI);
                        fa.set_x(x);
                        fa.set_y(y);
                        fa.set_z(w.dicke());
                    }else
                    {
                        fa.set_bezug(WST_BEZUG_UNSEI);
                        if(drehtyp_L)
                        {
                            fa.set_x(w.laenge()-x);
                            fa.set_y(y);
                        }else //if(drehtyp_B)
                        {
                            fa.set_x(x);
                            fa.set_y(w.breite()-y);
                        }
                        fa.set_z(0);
                    }
                    w.neue_bearbeitung(fa.text());
                    p3dfkon = fa.pos();
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_FKON_AFB)
                    {
                        fa.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_FKON_X)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        x = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_FKON_Y)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        y = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_FKON_Z)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        tifkon = w.dicke() - tmp.toDouble();
                        fa.set_tiefe(tifkon);//Tiefe, nicht Z-Wert!!
                                            //Z-Wert ist für horizontale Fräseraufrufe gedacht
                    }else if(schluessel == FMC_FKON_KOR)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        if(tmp == "1")
                        {
                            fa.set_radkor(FRKOR_L);
                        }else if(tmp == "0")
                        {
                            fa.set_radkor(FRKOR_M);
                        }else if(tmp == "2")
                        {
                            fa.set_radkor(FRKOR_R);
                        }

                    }else if(schluessel == FMC_FKON_WKZ)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        fa.set_wkznum(tmp);
                    }
                }
            }
        }else if(zeile.contains(FMC_FKONG))
        {
            fraesergerade fg;
            double x = 0;
            double y = 0;
            double zs = tifkon;//Der Z-Wert gibt die Tiefe an
            double ze = 0;//Der Z-Wert gibt die Tiefe an
            for(uint ii=i+1; ii<tz.count() ;ii++)
            {
                zeile = tz.at(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    orginal_x = x;
                    orginal_y = y;
                    punkt3d endpu;
                    if(istOberseite)
                    {
                        fg.set_bezug(WST_BEZUG_OBSEI);
                        endpu.set_x(x);
                        endpu.set_y(y);
                    }else
                    {
                        fg.set_bezug(WST_BEZUG_UNSEI);
                        if(drehtyp_L)
                        {
                            endpu.set_x(w.laenge()-x);
                            endpu.set_y(y);
                        }else //if(drehtyp_B)
                        {
                            endpu.set_x(x);
                            endpu.set_y(w.breite()-y);
                        }
                    }
                    fg.set_startpunkt(p3dfkon);
                    fg.set_endpunkt(endpu);
                    fg.set_zs(zs);//Der Z-Wert gibt die Tiefe an
                    fg.set_ze(ze);//Der Z-Wert gibt die Tiefe an
                    tifkon = ze;
                    p3dfkon = endpu;
                    if(Kurze_geraden_import == true)
                    {
                        w.neue_bearbeitung(fg.text());
                    }else if(fg.laenge_2d() > Min_fkon_gerade_laenge || \
                             fg.zs() != fg.ze())
                    {
                        w.neue_bearbeitung(fg.text());
                    }
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_FKONG_AFB)
                    {
                        fg.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_FKONG_XE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp.replace("X", double_to_qstring(orginal_x));
                        x = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_FKONG_YE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp.replace("Y", double_to_qstring(orginal_y));
                        y = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_FKONG_ZE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        if(tmp == "Z")
                        {
                            ze = zs;
                        }else
                        {
                            tmp = var_einsetzen(w, tmp);
                            tmp = ausdruck_auswerten(tmp);
                            ze = w.dicke() - tmp.toDouble();
                        }
                    }
                }
            }
        }else if(zeile.contains(FMC_FKONBOGUZS)   || \
                 zeile.contains(FMC_FKONBOGGUZS)     )
        {
            fraeserbogen fb;
            double x = 0;
            double y = 0;
            double zs = tifkon;//Der Z-Wert gibt die Tiefe an
            double ze = 0;//Der Z-Wert gibt die Tiefe an
            if(zeile.contains(FMC_FKONBOGUZS))
            {
                fb.set_uzs(true);
            }else
            {
                fb.set_uzs(false);
            }
            for(uint ii=i+1; ii<tz.count() ;ii++)
            {
                zeile = tz.at(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    orginal_x = x;
                    orginal_y = y;
                    punkt3d endpu;
                    if(istOberseite)
                    {
                        fb.set_bezug(WST_BEZUG_OBSEI);
                        endpu.set_x(x);
                        endpu.set_y(y);
                    }else
                    {
                        fb.set_bezug(WST_BEZUG_UNSEI);
                        if(drehtyp_L)
                        {
                            endpu.set_x(w.laenge()-x);
                            endpu.set_y(y);
                        }else //if(drehtyp_B)
                        {
                            endpu.set_x(x);
                            endpu.set_y(w.breite()-y);
                        }
                    }
                    fb.set_startpunkt(p3dfkon);
                    fb.set_endpunkt(endpu);
                    fb.set_zs(zs);//Der Z-Wert gibt die Tiefe an
                    fb.set_ze(ze);//Der Z-Wert gibt die Tiefe an
                    tifkon = ze;
                    p3dfkon = endpu;
                    w.neue_bearbeitung(fb.text());
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_FKONBOG_AFB)
                    {
                        fb.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_FKONBOG_XE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp.replace("X", double_to_qstring(orginal_x));
                        x = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_FKONBOG_YE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp.replace("Y", double_to_qstring(orginal_y));
                        y = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_FKONBOG_ZE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        if(tmp == "Z")
                        {
                            ze = zs;
                        }else
                        {
                            tmp = var_einsetzen(w, tmp);
                            tmp = ausdruck_auswerten(tmp);
                            ze = w.dicke() - tmp.toDouble();
                        }
                    }else if(schluessel == FMC_FKONBOG_RAD)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        double rad = tmp.toDouble();
                        if(rad < 0)
                        {
                            rad = rad * -1;
                        }
                        fb.set_rad(rad);
                    }
                }
            }
        }else if(zeile.contains(FMC_FALZ))
        {
            fraeseraufruf fa;
            fraesergerade fg;
            double spx = 0;
            double spy = 0;
            double epx = 0;
            double epy = 0;
            for(uint ii=i+1; ii<tz.count() ;ii++)
            {
                zeile = tz.at(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    if(istOberseite)
                    {
                        fa.set_bezug(WST_BEZUG_OBSEI);
                        fg.set_bezug(WST_BEZUG_OBSEI);
                        fa.set_z(w.dicke());
                    }else
                    {
                        fa.set_bezug(WST_BEZUG_UNSEI);
                        fg.set_bezug(WST_BEZUG_UNSEI);
                        fa.set_z(0);
                        if(drehtyp_L)
                        {
                            spx = w.laenge()-spx;
                            epx = w.laenge()-epx;
                        }else //if(drehtyp_B)
                        {
                            spy = w.breite()-spy;
                            epy = w.breite()-epy;
                        }
                    }
                    fa.set_x(spx);
                    fa.set_y(spy);
                    fg.set_xs(spx);
                    fg.set_ys(spy);
                    fg.set_xe(epx);
                    fg.set_ye(epy);
                    w.neue_bearbeitung(fa.text());
                    w.neue_bearbeitung(fg.text());
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_FALZ_AFB)
                    {
                        fa.set_afb(wert_nach_istgleich(zeile));
                        fg.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_FALZ_XS)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        spx = tmp.toDouble();
                    }else if(schluessel == FMC_FALZ_YS)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        spy = tmp.toDouble();
                    }else if(schluessel == FMC_FALZ_XE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        epx = tmp.toDouble();
                    }else if(schluessel == FMC_FALZ_YE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        epy = tmp.toDouble();
                    }else if(schluessel == FMC_FALZ_Z)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        double tiefe = w.dicke() - tmp.toDouble();
                        fa.set_tiefe(tiefe);//Tiefe, nicht Z-Wert!!
                                            //Z-Wert ist für horizontale Fräseraufrufe gedacht
                        fg.set_zs(tiefe);
                        fg.set_ze(tiefe);
                    }else if(schluessel == FMC_FALZ_KOR)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        if(tmp == "1")
                        {
                            fa.set_radkor(FRKOR_L);
                        }else if(tmp == "0")
                        {
                            fa.set_radkor(FRKOR_M);
                        }else if(tmp == "2")
                        {
                            fa.set_radkor(FRKOR_R);
                        }

                    }else if(schluessel == FMC_FKON_WKZ)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        fa.set_wkznum(tmp);
                    }
                }
            }
        }else if(zeile.contains(FMC_TOPF))
        {
            bohrung botopf;
            bohrung boduebel;
            double topfabst = 0;
            double abst1 = 0;
            double abst2 = 0;
            double abst3 = 0;
            double abst4 = 0;
            double abst5 = 0;
            double massA = 0;
            double massB = 0;
            bool kettenmass = false;
            double seite = 0;
            for(uint ii=i+1; ii<tz.count() ;ii++)
            {
                zeile = tz.at(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    if(istOberseite)
                    {
                        botopf.set_bezug(WST_BEZUG_OBSEI);
                        boduebel.set_bezug(WST_BEZUG_OBSEI);
                        botopf.set_z(w.dicke());
                        boduebel.set_z(w.dicke());
                    }else
                    {
                        botopf.set_bezug(WST_BEZUG_UNSEI);
                        boduebel.set_bezug(WST_BEZUG_UNSEI);
                        if(drehtyp_L)
                        {
                            if(seite == 1 || seite == 3)//vorne||hinten
                            {
                                if(kettenmass == false)
                                {
                                    if(abst1 != 0)
                                    {
                                        abst1 = w.laenge()-abst1;
                                    }
                                    if(abst2 != 0)
                                    {
                                        abst2 = w.laenge()-abst2;
                                    }
                                    if(abst3 != 0)
                                    {
                                        abst3 = w.laenge()-abst3;
                                    }
                                    if(abst4 != 0)
                                    {
                                        abst4 = w.laenge()-abst4;
                                    }
                                    if(abst5 != 0)
                                    {
                                        abst5 = w.laenge()-abst5;
                                    }
                                }else
                                {
                                    if(abst1 != 0)
                                    {
                                        abst1 = w.laenge()-abst1;
                                    }
                                    if(abst2 != 0)
                                    {
                                        abst2 = abst2 * -1;
                                    }
                                    if(abst3 != 0)
                                    {
                                        abst3 = abst3 * -1;
                                    }
                                    if(abst4 != 0)
                                    {
                                        abst4 = abst4 * -1;
                                    }
                                    if(abst5 != 0)
                                    {
                                        abst5 = abst5 * -1;
                                    }
                                }
                            }else //rechts||links
                            {
                                if(seite == 2)
                                {
                                    seite = 4;
                                }else
                                {
                                    seite = 2;
                                }
                            }
                        }else //if(drehtyp_B)
                        {
                            if(seite == 1 || seite == 3)//vorne||hinten
                            {
                                if(seite == 1)
                                {
                                    seite = 3;
                                }else
                                {
                                    seite = 1;
                                }
                            }else //rechts||links
                            {
                                if(kettenmass == false)
                                {
                                    if(abst1 != 0)
                                    {
                                        abst1 = w.breite()-abst1;
                                    }
                                    if(abst2 != 0)
                                    {
                                        abst2 = w.breite()-abst2;
                                    }
                                    if(abst3 != 0)
                                    {
                                        abst3 = w.breite()-abst3;
                                    }
                                    if(abst4 != 0)
                                    {
                                        abst4 = w.breite()-abst4;
                                    }
                                    if(abst5 != 0)
                                    {
                                        abst5 = w.breite()-abst5;
                                    }
                                }else
                                {
                                    if(abst1 != 0)
                                    {
                                        abst1 = w.breite()-abst1;
                                    }
                                    if(abst2 != 0)
                                    {
                                        abst2 = abst2 * -1;
                                    }
                                    if(abst3 != 0)
                                    {
                                        abst3 = abst3 * -1;
                                    }
                                    if(abst4 != 0)
                                    {
                                        abst4 = abst4 * -1;
                                    }
                                    if(abst5 != 0)
                                    {
                                        abst5 = abst5 * -1;
                                    }
                                }
                            }
                        }
                        botopf.set_z(0);
                        boduebel.set_z(0);
                    }
                    if(seite == 1)//vorne
                    {
                        if(abst1 != 0)
                        {
                            double abst_tmp = abst1;

                            botopf.set_x(abst_tmp);
                            botopf.set_y(topfabst);
                            w.neue_bearbeitung(botopf.text());

                            boduebel.set_y(topfabst+massB);
                            boduebel.set_x(abst_tmp - massA/2);
                            w.neue_bearbeitung(boduebel.text());
                            boduebel.set_x(abst_tmp + massA/2);
                            w.neue_bearbeitung(boduebel.text());
                        }
                        if(abst2 != 0)
                        {
                            double abst_tmp;
                            if(kettenmass == true)
                            {
                                abst_tmp = abst1+abst2;
                            }else
                            {
                                abst_tmp = abst2;
                            }

                            botopf.set_x(abst_tmp);
                            botopf.set_y(topfabst);
                            w.neue_bearbeitung(botopf.text());

                            boduebel.set_y(topfabst+massB);
                            boduebel.set_x(abst_tmp - massA/2);
                            w.neue_bearbeitung(boduebel.text());
                            boduebel.set_x(abst_tmp + massA/2);
                            w.neue_bearbeitung(boduebel.text());
                        }
                        if(abst3 != 0)
                        {
                            double abst_tmp;
                            if(kettenmass == true)
                            {
                                abst_tmp = abst1+abst2+abst3;
                            }else
                            {
                                abst_tmp = abst3;
                            }

                            botopf.set_x(abst_tmp);
                            botopf.set_y(topfabst);
                            w.neue_bearbeitung(botopf.text());

                            boduebel.set_y(topfabst+massB);
                            boduebel.set_x(abst_tmp - massA/2);
                            w.neue_bearbeitung(boduebel.text());
                            boduebel.set_x(abst_tmp + massA/2);
                            w.neue_bearbeitung(boduebel.text());
                        }
                        if(abst4 != 0)
                        {
                            double abst_tmp;
                            if(kettenmass == true)
                            {
                                abst_tmp = abst1+abst2+abst3+abst4;
                            }else
                            {
                                abst_tmp = abst4;
                            }

                            botopf.set_x(abst_tmp);
                            botopf.set_y(topfabst);
                            w.neue_bearbeitung(botopf.text());

                            boduebel.set_y(topfabst+massB);
                            boduebel.set_x(abst_tmp - massA/2);
                            w.neue_bearbeitung(boduebel.text());
                            boduebel.set_x(abst_tmp + massA/2);
                            w.neue_bearbeitung(boduebel.text());
                        }
                        if(abst5 != 0)
                        {
                            double abst_tmp;
                            if(kettenmass == true)
                            {
                                abst_tmp = abst1+abst2+abst3+abst4+abst5;
                            }else
                            {
                                abst_tmp = abst5;
                            }

                            botopf.set_x(abst_tmp);
                            botopf.set_y(topfabst);
                            w.neue_bearbeitung(botopf.text());

                            boduebel.set_y(topfabst+massB);
                            boduebel.set_x(abst_tmp - massA/2);
                            w.neue_bearbeitung(boduebel.text());
                            boduebel.set_x(abst_tmp + massA/2);
                            w.neue_bearbeitung(boduebel.text());
                        }
                    }else if(seite == 2)//rechts
                    {
                        if(abst1 != 0)
                        {
                            double abst_tmp = abst1;
                            botopf.set_x(w.laenge()-topfabst);
                            botopf.set_y(abst_tmp);
                            w.neue_bearbeitung(botopf.text());
                            boduebel.set_y(abst_tmp - massA/2);
                            boduebel.set_x(w.laenge()-topfabst-massB);
                            w.neue_bearbeitung(boduebel.text());
                            boduebel.set_y(abst_tmp + massA/2);
                            w.neue_bearbeitung(boduebel.text());
                        }
                        if(abst2 != 0)
                        {
                            double abst_tmp;
                            if(kettenmass == true)
                            {
                                abst_tmp = abst1+abst2;
                            }else
                            {
                                abst_tmp = abst2;
                            }
                            botopf.set_x(w.laenge()-topfabst);
                            botopf.set_y(abst_tmp);
                            w.neue_bearbeitung(botopf.text());
                            boduebel.set_y(abst_tmp - massA/2);
                            boduebel.set_x(w.laenge()-topfabst-massB);
                            w.neue_bearbeitung(boduebel.text());
                            boduebel.set_y(abst_tmp + massA/2);
                            w.neue_bearbeitung(boduebel.text());
                        }
                        if(abst3 != 0)
                        {
                            double abst_tmp;
                            if(kettenmass == true)
                            {
                                abst_tmp = abst1+abst2+abst3;
                            }else
                            {
                                abst_tmp = abst3;
                            }
                            botopf.set_x(w.laenge()-topfabst);
                            botopf.set_y(abst_tmp);
                            w.neue_bearbeitung(botopf.text());
                            boduebel.set_y(abst_tmp - massA/2);
                            boduebel.set_x(w.laenge()-topfabst-massB);
                            w.neue_bearbeitung(boduebel.text());
                            boduebel.set_y(abst_tmp + massA/2);
                            w.neue_bearbeitung(boduebel.text());
                        }
                        if(abst4 != 0)
                        {
                            double abst_tmp;
                            if(kettenmass == true)
                            {
                                abst_tmp = abst1+abst2+abst3+abst4;
                            }else
                            {
                                abst_tmp = abst4;
                            }
                            botopf.set_x(w.laenge()-topfabst);
                            botopf.set_y(abst_tmp);
                            w.neue_bearbeitung(botopf.text());
                            boduebel.set_y(abst_tmp - massA/2);
                            boduebel.set_x(w.laenge()-topfabst-massB);
                            w.neue_bearbeitung(boduebel.text());
                            boduebel.set_y(abst_tmp + massA/2);
                            w.neue_bearbeitung(boduebel.text());
                        }
                        if(abst5 != 0)
                        {
                            double abst_tmp;
                            if(kettenmass == true)
                            {
                                abst_tmp = abst1+abst2+abst3+abst4+abst5;
                            }else
                            {
                                abst_tmp = abst5;
                            }
                            botopf.set_x(w.laenge()-topfabst);
                            botopf.set_y(abst_tmp);
                            w.neue_bearbeitung(botopf.text());
                            boduebel.set_y(abst_tmp - massA/2);
                            boduebel.set_x(w.laenge()-topfabst-massB);
                            w.neue_bearbeitung(boduebel.text());
                            boduebel.set_y(abst_tmp + massA/2);
                            w.neue_bearbeitung(boduebel.text());
                        }
                    }else if(seite == 3)//hinten
                    {
                        if(abst1 != 0)
                        {
                            double abst_tmp = abst1;

                            botopf.set_x(abst_tmp);
                            botopf.set_y(w.breite() - topfabst);
                            w.neue_bearbeitung(botopf.text());

                            boduebel.set_y(w.breite() - topfabst - massB);
                            boduebel.set_x(abst_tmp - massA/2);
                            w.neue_bearbeitung(boduebel.text());
                            boduebel.set_x(abst_tmp + massA/2);
                            w.neue_bearbeitung(boduebel.text());
                        }
                        if(abst2 != 0)
                        {
                            double abst_tmp;
                            if(kettenmass == true)
                            {
                                abst_tmp = abst1+abst2;
                            }else
                            {
                                abst_tmp = abst2;
                            }

                            botopf.set_x(abst_tmp);
                            botopf.set_y(w.breite() - topfabst);
                            w.neue_bearbeitung(botopf.text());

                            boduebel.set_y(w.breite() - topfabst - massB);
                            boduebel.set_x(abst_tmp - massA/2);
                            w.neue_bearbeitung(boduebel.text());
                            boduebel.set_x(abst_tmp + massA/2);
                            w.neue_bearbeitung(boduebel.text());
                        }
                        if(abst3 != 0)
                        {
                            double abst_tmp;
                            if(kettenmass == true)
                            {
                                abst_tmp = abst1+abst2+abst3;
                            }else
                            {
                                abst_tmp = abst3;
                            }

                            botopf.set_x(abst_tmp);
                            botopf.set_y(w.breite() - topfabst);
                            w.neue_bearbeitung(botopf.text());

                            boduebel.set_y(w.breite() - topfabst - massB);
                            boduebel.set_x(abst_tmp - massA/2);
                            w.neue_bearbeitung(boduebel.text());
                            boduebel.set_x(abst_tmp + massA/2);
                            w.neue_bearbeitung(boduebel.text());
                        }
                        if(abst4 != 0)
                        {
                            double abst_tmp;
                            if(kettenmass == true)
                            {
                                abst_tmp = abst1+abst2+abst3+abst4;
                            }else
                            {
                                abst_tmp = abst4;
                            }

                            botopf.set_x(abst_tmp);
                            botopf.set_y(w.breite() - topfabst);
                            w.neue_bearbeitung(botopf.text());

                            boduebel.set_y(w.breite() - topfabst - massB);
                            boduebel.set_x(abst_tmp - massA/2);
                            w.neue_bearbeitung(boduebel.text());
                            boduebel.set_x(abst_tmp + massA/2);
                            w.neue_bearbeitung(boduebel.text());
                        }
                        if(abst5 != 0)
                        {
                            double abst_tmp;
                            if(kettenmass == true)
                            {
                                abst_tmp = abst1+abst2+abst3+abst4+abst5;
                            }else
                            {
                                abst_tmp = abst5;
                            }

                            botopf.set_x(abst_tmp);
                            botopf.set_y(w.breite() - topfabst);
                            w.neue_bearbeitung(botopf.text());

                            boduebel.set_y(w.breite() - topfabst - massB);
                            boduebel.set_x(abst_tmp - massA/2);
                            w.neue_bearbeitung(boduebel.text());
                            boduebel.set_x(abst_tmp + massA/2);
                            w.neue_bearbeitung(boduebel.text());
                        }
                    }else if(seite == 4)//links
                    {
                        if(abst1 != 0)
                        {
                            double abst_tmp = abst1;
                            botopf.set_x(topfabst);
                            botopf.set_y(abst_tmp);
                            w.neue_bearbeitung(botopf.text());
                            boduebel.set_y(abst_tmp - massA/2);
                            boduebel.set_x(topfabst+massB);
                            w.neue_bearbeitung(boduebel.text());
                            boduebel.set_y(abst_tmp + massA/2);
                            w.neue_bearbeitung(boduebel.text());
                        }
                        if(abst2 != 0)
                        {
                            double abst_tmp;
                            if(kettenmass == true)
                            {
                                abst_tmp = abst1+abst2;
                            }else
                            {
                                abst_tmp = abst2;
                            }
                            botopf.set_x(topfabst);
                            botopf.set_y(abst_tmp);
                            w.neue_bearbeitung(botopf.text());
                            boduebel.set_y(abst_tmp - massA/2);
                            boduebel.set_x(topfabst+massB);
                            w.neue_bearbeitung(boduebel.text());
                            boduebel.set_y(abst_tmp + massA/2);
                            w.neue_bearbeitung(boduebel.text());
                        }
                        if(abst3 != 0)
                        {
                            double abst_tmp;
                            if(kettenmass == true)
                            {
                                abst_tmp = abst1+abst2+abst3;
                            }else
                            {
                                abst_tmp = abst3;
                            }
                            botopf.set_x(topfabst);
                            botopf.set_y(abst_tmp);
                            w.neue_bearbeitung(botopf.text());
                            boduebel.set_y(abst_tmp - massA/2);
                            boduebel.set_x(topfabst+massB);
                            w.neue_bearbeitung(boduebel.text());
                            boduebel.set_y(abst_tmp + massA/2);
                            w.neue_bearbeitung(boduebel.text());
                        }
                        if(abst4 != 0)
                        {
                            double abst_tmp;
                            if(kettenmass == true)
                            {
                                abst_tmp = abst1+abst2+abst3+abst4;
                            }else
                            {
                                abst_tmp = abst4;
                            }
                            botopf.set_x(topfabst);
                            botopf.set_y(abst_tmp);
                            w.neue_bearbeitung(botopf.text());
                            boduebel.set_y(abst_tmp - massA/2);
                            boduebel.set_x(topfabst+massB);
                            w.neue_bearbeitung(boduebel.text());
                            boduebel.set_y(abst_tmp + massA/2);
                            w.neue_bearbeitung(boduebel.text());
                        }
                        if(abst5 != 0)
                        {
                            double abst_tmp;
                            if(kettenmass == true)
                            {
                                abst_tmp = abst1+abst2+abst3+abst4+abst5;
                            }else
                            {
                                abst_tmp = abst5;
                            }
                            botopf.set_x(topfabst);
                            botopf.set_y(abst_tmp);
                            w.neue_bearbeitung(botopf.text());
                            boduebel.set_y(abst_tmp - massA/2);
                            boduebel.set_x(topfabst+massB);
                            w.neue_bearbeitung(boduebel.text());
                            boduebel.set_y(abst_tmp + massA/2);
                            w.neue_bearbeitung(boduebel.text());
                        }
                    }
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_TOPF_AFB)
                    {
                        botopf.set_afb(wert_nach_istgleich(zeile));
                        boduebel.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_TOPF_TODM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        botopf.set_dm(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_TOPF_DDM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        boduebel.set_dm(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_TOPF_TOTI)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        botopf.set_tiefe(tmp);
                    }else if(schluessel == FMC_TOPF_DTI)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        boduebel.set_tiefe(tmp);
                    }else if(schluessel == FMC_TOPF_KM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        kettenmass = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_TOPF_ABST)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        topfabst = tmp.toDouble();
                    }else if(schluessel == FMC_TOPF_MA)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        massA = tmp.toDouble();
                    }else if(schluessel == FMC_TOPF_MB)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        massB = tmp.toDouble();
                    }else if(schluessel == FMC_TOPF_A1)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            tmp = ausdruck_auswerten(tmp);
                            abst1 = tmp.toDouble();
                        }
                    }else if(schluessel == FMC_TOPF_A2)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            tmp.replace("A1",double_to_qstring(abst1));
                            tmp = ausdruck_auswerten(tmp);
                            abst2 = tmp.toDouble();
                        }
                    }else if(schluessel == FMC_TOPF_A3)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            tmp.replace("A1",double_to_qstring(abst1));
                            tmp.replace("A2",double_to_qstring(abst2));
                            tmp = ausdruck_auswerten(tmp);
                            abst3 = tmp.toDouble();
                        }
                    }else if(schluessel == FMC_TOPF_A4)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            tmp.replace("A1",double_to_qstring(abst1));
                            tmp.replace("A2",double_to_qstring(abst2));
                            tmp.replace("A3",double_to_qstring(abst3));
                            tmp = ausdruck_auswerten(tmp);
                            abst4 = tmp.toDouble();
                        }
                    }else if(schluessel == FMC_TOPF_A5)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            tmp.replace("A1",double_to_qstring(abst1));
                            tmp.replace("A2",double_to_qstring(abst2));
                            tmp.replace("A3",double_to_qstring(abst3));
                            tmp.replace("A4",double_to_qstring(abst4));
                            tmp = ausdruck_auswerten(tmp);
                            abst5 = tmp.toDouble();
                        }
                    }else if(schluessel == FMC_TOPF_TOWKZ)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        botopf.set_wkznum(tmp);
                    }else if(schluessel == FMC_TOPF_SEITE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        seite = tmp.toDouble();
                    }
                }
            }
        }else if(zeile.contains(FMC_GEHR))
        {
            gehrung ge;
            double spx = 0;
            double spy = 0;
            double epx = 0;
            double epy = 0;
            QString bezug;
            for(uint ii=i+1; ii<tz.count() ;ii++)
            {
                zeile = tz.at(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    if(!istOberseite)
                    {
                        if(bezug == WST_BEZUG_OBSEI)
                        {
                            bezug = WST_BEZUG_UNSEI;
                        }else
                        {
                            bezug = WST_BEZUG_OBSEI;
                        }
                        if(drehtyp_L)
                        {
                            spx = w.laenge()-spx;
                            epx = w.laenge()-epx;
                        }else //if(drehtyp_B)
                        {
                            spy = w.breite()-spy;
                            epy = w.breite()-epy;
                        }
                    }
                    punkt3d sp, ep;
                    sp.set_x(spx);
                    sp.set_y(spy);
                    ep.set_x(epx);
                    ep.set_y(epy);
                    ge.set_bezug(bezug);
                    ge.set_stapu(sp);
                    ge.set_endpu(ep);
                    w.neue_bearbeitung(ge.text());
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_GEHR_AFB)
                    {
                        ge.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_GEHR_SPX)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        spx = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_GEHR_SPY)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        spy = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_GEHR_EPX)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        epx = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_GEHR_EPY)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        epy = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_GEHR_TIRITZEN)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        ge.set_riti(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_GEHR_TISCHNITT)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        ge.set_sti(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_GEHR_KOR)
                    {
                        //...
                    }else if(schluessel == FMC_GEHR_GEGENLAUF)
                    {
                        //...
                    }else if(schluessel == FMC_GEHR_KADI)
                    {
                        //...
                    }else if(schluessel == FMC_GEHR_WI)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        ge.set_winkel(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_GEHR_BEZUG)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp).toDouble();
                        if(tmp == 1)//Spitze auf der Unterseite
                        {
                            bezug = WST_BEZUG_OBSEI;
                        }else//Spitze auf der Oberseite
                        {
                            bezug = WST_BEZUG_UNSEI;
                        }
                    }else if(schluessel == FMC_GEHR_WKZNR)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        ge.set_wkznum(tmp);
                    }
                }
            }
        }else if(zeile.contains(FMC_STULP))
        {
            rechtecktasche rt;
            double x = 0;
            double y = 0;
            double z = 0;
            for(uint ii=i+1; ii<tz.count() ;ii++)
            {
                zeile = tz.at(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    if(!istOberseite)
                    {
                        if(drehtyp_L)
                        {
                            x = w.laenge()-x;
                        }else //if(drehtyp_B)
                        {
                            y = w.breite()-y;
                        }
                        z = w.dicke()-z;
                    }
                    //Bezugsfläche ermitteln:
                    if(cagleich(x, 0, 0.1))
                    {
                        rt.set_bezug(WST_BEZUG_LI);
                    }else if(cagleich(x, w.laenge(), 0.1))
                    {
                        rt.set_bezug(WST_BEZUG_RE);
                    }else if(cagleich(y, 0, 0.1))
                    {
                        rt.set_bezug(WST_BEZUG_VO);
                    }else if(cagleich(y, w.breite(), 0.1))
                    {
                        rt.set_bezug(WST_BEZUG_HI);
                    }
                    rt.set_x(x);
                    rt.set_y(y);
                    rt.set_z(z);
                    w.neue_bearbeitung(rt.text());
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_STULP_AFB)
                    {
                        rt.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_STULP_L)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        rt.set_laenge(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_STULP_B)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        rt.set_breite(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_STULP_TI)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        double tiefe = ausdruck_auswerten(tmp).toDouble();
                        rt.set_tiefe(tiefe);
                    }else if(schluessel == FMC_STULP_X)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        x = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_STULP_Y)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        y = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_STULP_Z)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        z = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_STULP_ZUST)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        rt.set_zustellmass(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_STULP_RAD)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        rt.set_rad(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_STULP_WKZ)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        rt.set_wkznum(tmp);
                    }
                }
            }
        }
    }
    Wste.replace(Index, w);
    return 0;
}

QString werkstuecke::dxf_wert(QString namen, QString werte, QString gesucht)
{
    text_zw tz_name;
    text_zw tz_wert;
    tz_name.set_text(namen,'\n');
    tz_wert.set_text(werte,'\n');
    QString ret;
    for(uint i=0; i<tz_name.count() ;i++)
    {
        if(tz_name.at(i) == gesucht)
        {
            ret = tz_wert.at(i);
            break;
        }
    }
    return ret;
}
strecke werkstuecke::dxf_strecke(QString namen, QString werte, QString dxf_version)
{
    strecke s;
    if(dxf_version == "AC1009")
    {
        punkt3d p;
        p.set_x(dxf_wert(namen, werte, DXF_AC1009_STRECKE_SX));
        p.set_y(dxf_wert(namen, werte, DXF_AC1009_STRECKE_SY));
        s.set_stapu(p);
        p.set_x(dxf_wert(namen, werte, DXF_AC1009_STRECKE_EX));
        p.set_y(dxf_wert(namen, werte, DXF_AC1009_STRECKE_EY));
        s.set_endpu(p);
    }
    return s;
}
kreis werkstuecke::dxf_kreis(QString namen, QString werte, QString dxf_version)
{
    kreis k;
    if(dxf_version == "AC1009")
    {
        k.set_radius(dxf_wert(namen, werte, DXF_AC1009_KREIS_RAD));
        punkt3d p;
        p.set_x(dxf_wert(namen, werte, DXF_AC1009_KREIS_X));
        p.set_y(dxf_wert(namen, werte, DXF_AC1009_KREIS_Y));
        p.set_z(dxf_wert(namen, werte, DXF_AC1009_KREIS_Z));
        k.set_mittelpunkt(p);
    }
    return k;
}
bogen werkstuecke::dxf_bogen(QString namen, QString werte, QString dxf_version)
{
    bogen b;
    if(dxf_version == "AC1009")
    {
        punkt3d mipu;
        mipu.set_x(dxf_wert(namen, werte, DXF_AC1009_BOGEN_MIPUX));
        mipu.set_y(dxf_wert(namen, werte, DXF_AC1009_BOGEN_MIPUY));
        mipu.set_z(dxf_wert(namen, werte, DXF_AC1009_BOGEN_MIPUZ));
        double rad = dxf_wert(namen, werte, DXF_AC1009_BOGEN_RAD).toDouble();
        double swi = dxf_wert(namen, werte, DXF_AC1009_BOGEN_SWI).toDouble();
        double ewi = dxf_wert(namen, werte, DXF_AC1009_BOGEN_EWI).toDouble();
        bogen tmp(mipu, rad, swi, ewi);
        b = tmp;
    }
    return b;
}
bogenac werkstuecke::dxf_bogenac(QString namen, QString werte, QString dxf_version)
{
    bogenac b;
    if(dxf_version == "AC1009")
    {
        punkt3d mipu;
        mipu.set_x(dxf_wert(namen, werte, DXF_AC1009_BOGEN_MIPUX));
        mipu.set_y(dxf_wert(namen, werte, DXF_AC1009_BOGEN_MIPUY));
        mipu.set_z(dxf_wert(namen, werte, DXF_AC1009_BOGEN_MIPUZ));
        double rad = dxf_wert(namen, werte, DXF_AC1009_BOGEN_RAD).toDouble();
        double swi = dxf_wert(namen, werte, DXF_AC1009_BOGEN_SWI).toDouble();
        double ewi = dxf_wert(namen, werte, DXF_AC1009_BOGEN_EWI).toDouble();
        b.set_mipu(mipu);
        b.set_rad(rad);
        b.set_swi(swi);
        b.set_ewi(ewi);
    }
    return b;
}
bool werkstuecke::import_dxf(QString Werkstueckname, QString importtext, bool istOberseite)
{
    int Index = index(Werkstueckname);
    if(Index == -1)
    {
        neu(Werkstueckname, DXF);
        Index = index(Werkstueckname);
    }
    text_zw tz, tz_name, tz_wert;
    tz.set_text(importtext,'\n');
    werkstueck w = Wste.at(Index);

    //tz_name und tz_wert mit Daten füllen:
    bool schalter = true;
    for(uint i=0; i<tz.count() ;i++)
    {
        if(schalter == true)
        {
            tz_name.add_hi(tz.at(i));
        }else
        {
            tz_wert.add_hi(tz.at(i));
        }
        schalter = !schalter;
    }

    //DXF-Version prüfen:
    QString dxf_version;
    for(uint i=0; i<tz.count() ;i++)
    {
        QString zeile = tz.at(i);
        if(zeile.contains(DXF_VERSION))
        {
            dxf_version = tz.at(i+2);
            break;//for
        }
    }
    //------------------------------
    if(dxf_version == "AC1009")
    {
        //Start und Ende finden:
        uint i_start = 0;
        uint i_ende  = 0;
        //------------------------------Geometriebereich ermitteln (Start und Ende):
        for(uint i=0; i<tz_name.count() ;i++)
        {
            if(tz_name.at(i).toInt() == 2)// A name Attribute tag, Block name, and so on. Also used to identify a DXF section or table name
            {
                if(tz_wert.at(i) == "ENTITIES")
                {
                    i_start = i;
                }
            }
            if(i_start > 0 && tz_name.at(i).toInt() == 0)
            {
                if(tz_wert.at(i) == DXF_AC1009_EOF)
                {
                    i_ende = i;
                    break;//for i
                }
            }
        }
        //------------------------------Unterblöcke ermitteln:
        text_zw block;
        //Ersten Block finden:
        for(uint i=i_start; i<=i_ende ;i++)
        {
            if(tz_name.at(i) == DXF_AC1009_NULL)
            {
                QString start = int_to_qstring(i_start);
                QString ende = int_to_qstring(i);
                QString tren = "|";
                block.set_text(start+tren+ende,'\n');
                break;
            }
        }
        //restliche Blöcke finden:
        for(uint i=i_start; i<=i_ende ;i++)
        {
            if(tz_name.at(i) == DXF_AC1009_NULL)
            {
                QString tren = "|";
                QString start = text_rechts(block.at(block.count()-1),tren);
                QString ende = int_to_qstring(i);
                block.add_hi(start+tren+ende);
            }
        }
        block.entf(block.count()-1);
        block.entf(0);
        block.entf(0);
        //------------------------------Werkstück-Größe bestimmen:
        for(uint i=0;i<block.count();i++)
        {
            uint sta = text_links(block.at(i),"|").toUInt();
            uint end = text_rechts(block.at(i),"|").toUInt();
            uint anz = end-sta;
            QString klasse;
            klasse = dxf_wert(tz_name.at(sta,anz), tz_wert.at(sta,anz),\
                              DXF_AC1009_KLASSE);
            if(klasse.contains(Einstellung_dxf_klassen.wst()))
            {
                if(w.dicke()<=0)
                {
                    QString dicke;
                    dicke = text_rechts(klasse, Einstellung_dxf_klassen.wst());
                    dicke = text_rechts(dicke, Einstellung_dxf.paramtren());
                    dicke.replace(Einstellung_dxf.dezitren(),".");
                    w.set_dicke(dicke);
                }
                QString x = dxf_wert(tz_name.at(sta,anz), tz_wert.at(sta,anz),\
                                     DXF_AC1009_WST_X);
                if(x.toDouble() > w.laenge())
                {
                    w.set_laenge(x);
                }
                QString y = dxf_wert(tz_name.at(sta,anz), tz_wert.at(sta,anz),\
                                     DXF_AC1009_WST_Y);
                if(y.toDouble() > w.breite())
                {
                    w.set_breite(y);
                }
            }
        }
        //------------------------------Bohrungen vertikal:
        for(uint i=0;i<block.count();i++)
        {
            uint sta = text_links(block.at(i),"|").toUInt();
            uint end = text_rechts(block.at(i),"|").toUInt();
            uint anz = end-sta;
            QString klasse;
            klasse = dxf_wert(tz_name.at(sta,anz), tz_wert.at(sta,anz),\
                              DXF_AC1009_KLASSE);
            if(klasse.contains(Einstellung_dxf_klassen.bohr_vert()))
            {
                QString typ = dxf_wert(tz_name.at(sta,anz), tz_wert.at(sta,anz),\
                                       DXF_AC1009_NULL);
                if(typ == DXF_AC1009_KREIS)
                {
                    kreis k = dxf_kreis(tz_name.at(sta,anz), tz_wert.at(sta,anz), "AC1009");
                    bohrung bo;
                    bo.set_afb("1");
                    QString ti;
                    ti = text_rechts(klasse, Einstellung_dxf_klassen.bohr_vert());
                    ti = text_rechts(ti, Einstellung_dxf.paramtren());
                    ti.replace(Einstellung_dxf.dezitren(),".");
                    double ti_double = ti.toDouble();
                    if(ti_double == w.dicke())
                    {
                        ti_double = ti_double + 4;
                    }
                    if(ti_double < 0)
                    {
                        ti_double = w.dicke() - ti_double;
                    }
                    bo.set_tiefe(ti_double);
                    double dm = k.radius()*2;
                    dm = runden(dm, 1);
                    bo.set_dm(dm);
                    if(istOberseite)
                    {
                        bo.set_bezug(WST_BEZUG_OBSEI);
                        bo.set_x(k.mitte3d().x());
                        bo.set_y(k.mitte3d().y());
                    }else
                    {
                        bo.set_bezug(WST_BEZUG_UNSEI);
                        if(Einstellung_dxf.drehtyp_L())
                        {
                            bo.set_x(w.laenge()-k.mitte3d().x());
                            bo.set_y(k.mitte3d().y());
                        }else //if(Einstellung_dxf.drehtyp_B())
                        {
                            bo.set_x(k.mitte3d().x());
                            bo.set_y(w.breite()-k.mitte3d().y());
                        }
                    }
                    w.neue_bearbeitung(bo.text());
                }
            }
        }
        //------------------------------Bohrungen horizontal:
        geo_text geo;
        for(uint i=0;i<block.count();i++)
        {
            uint sta = text_links(block.at(i),"|").toUInt();
            uint end = text_rechts(block.at(i),"|").toUInt();
            uint anz = end-sta;
            QString klasse;
            klasse = dxf_wert(tz_name.at(sta,anz), tz_wert.at(sta,anz),\
                              DXF_AC1009_KLASSE);
            if(klasse.contains(Einstellung_dxf_klassen.bohr_hori()))
            {
                QString typ = dxf_wert(tz_name.at(sta,anz), tz_wert.at(sta,anz),\
                                       DXF_AC1009_NULL);
                //Bohrung wird durch 2 Strecken definiert:
                if(typ == DXF_AC1009_STRECKE)
                {
                    strecke s = dxf_strecke(tz_name.at(sta,anz), tz_wert.at(sta,anz), "AC1009");
                    if(geo.count() == 0)
                    {
                        geo.add_strecke(s);
                    }else
                    {
                        strecke s2 = geo.at(0).text();
                        geo.clear();
                        bohrung bo;
                        bo.set_afb("1");
                        QString z;
                        z = text_rechts(klasse, Einstellung_dxf_klassen.bohr_hori());
                        z = text_rechts(z, Einstellung_dxf.paramtren());
                        z.replace(Einstellung_dxf.dezitren(),".");
                        bo.set_z(z);
                        if(s.wink()==0 || s.wink()==180)//waagerecht
                        {
                            if(s.stapu().x()==0 || s.endpu().x()==0)//HBE von links
                            {
                                if(s.stapu().x() > s.endpu().x())
                                {
                                    s.drenen_um_mipu_2d(180,true);
                                }
                                if(s2.stapu().x() > s2.endpu().x())
                                {
                                    s.drenen_um_mipu_2d(180,true);
                                }
                                bo.set_bezug(WST_BEZUG_LI);
                            }else//HBE von rechts
                            {
                                if(s.stapu().x() < s.endpu().x())
                                {
                                    s.drenen_um_mipu_2d(180,true);
                                }
                                if(s2.stapu().x() < s2.endpu().x())
                                {
                                    s.drenen_um_mipu_2d(180,true);
                                }
                                bo.set_bezug(WST_BEZUG_RE);
                            }
                        }else //senkrecht
                        {
                            if(s.stapu().y()==0 || s.endpu().y()==0)//HBE von vorne (Süden)
                            {
                                if(s.stapu().y() > s.endpu().y())
                                {
                                    s.drenen_um_mipu_2d(180,true);
                                }
                                if(s2.stapu().y() > s2.endpu().y())
                                {
                                    s2.drenen_um_mipu_2d(180,true);
                                }
                                bo.set_bezug(WST_BEZUG_VO);
                            }else//HBE von hinten (Norden)
                            {
                                if(s.stapu().y() < s.endpu().y())
                                {
                                    s.drenen_um_mipu_2d(180,true);
                                }
                                if(s2.stapu().y() < s2.endpu().y())
                                {
                                    s2.drenen_um_mipu_2d(180,true);
                                }
                                bo.set_bezug(WST_BEZUG_HI);
                            }                            
                        }
                        strecke grundlinie;
                        grundlinie.set_stapu(s.stapu());
                        grundlinie.set_endpu(s2.stapu());
                        double dm = grundlinie.laenge2d();
                        dm = runden(dm, 1);
                        bo.set_dm(dm);
                        bo.set_tiefe(s.laenge2d());
                        if(istOberseite)
                        {
                            bo.set_x(grundlinie.mipu().x());
                            bo.set_y(grundlinie.mipu().y());
                        }else
                        {
                            if(Einstellung_dxf.drehtyp_L())
                            {
                                bo.set_x(w.laenge()-grundlinie.mipu().x());
                                bo.set_y(grundlinie.mipu().y());
                            }else //if(Einstellung_dxf.drehtyp_B())
                            {
                                bo.set_x(grundlinie.mipu().x());
                                bo.set_y(w.breite()-grundlinie.mipu().y());
                            }
                        }
                        w.neue_bearbeitung(bo.text());
                    }
                }
            }
        }
        geo.clear();
        //------------------------------Nut vertikal:
        for(uint i=0;i<block.count();i++)
        {
            uint sta = text_links(block.at(i),"|").toUInt();
            uint end = text_rechts(block.at(i),"|").toUInt();
            uint anz = end-sta;
            QString klasse;
            klasse = dxf_wert(tz_name.at(sta,anz), tz_wert.at(sta,anz),\
                              DXF_AC1009_KLASSE);
            if(klasse.contains(Einstellung_dxf_klassen.nut_vert()))
            {
                QString typ = dxf_wert(tz_name.at(sta,anz), tz_wert.at(sta,anz),\
                                       DXF_AC1009_NULL);
                //Nut wird durch 2 oder 4 Strecken definiert:
                if(typ == DXF_AC1009_STRECKE)
                {
                    strecke s = dxf_strecke(tz_name.at(sta,anz), tz_wert.at(sta,anz), "AC1009");
                    //Trennzeichen = ';'
                    geo.add_strecke(s);
                    if(geo.count() == 2)
                    {
                        strecke s2 = geo.at(0).text();
                        if(s.laenge2d() == s2.laenge2d())//Nut ist durch 2 Linien Definiert
                        {
                            geo.clear();
                            nut nu;
                            nu.set_afb("1");
                            QString ti;
                            ti = text_rechts(klasse, Einstellung_dxf_klassen.nut_vert());
                            ti = text_rechts(ti, Einstellung_dxf.paramtren());
                            ti.replace(Einstellung_dxf.dezitren(),".");
                            nu.set_tiefe(ti);
                            strecke grundlinie_start;
                            grundlinie_start.set_stapu(s.stapu());
                            grundlinie_start.set_endpu(s2.stapu());
                            strecke grundlinie_ende;
                            grundlinie_ende.set_stapu(s.endpu());
                            grundlinie_ende.set_endpu(s2.endpu());
                            nu.set_breite(grundlinie_start.laenge2d());
                            if(istOberseite)
                            {
                                nu.set_bezug(WST_BEZUG_OBSEI);
                                nu.set_xs(grundlinie_start.mipu().x());
                                nu.set_ys(grundlinie_start.mipu().y());
                                nu.set_xe(grundlinie_ende.mipu().x());
                                nu.set_ye(grundlinie_ende.mipu().y());
                            }else
                            {
                                nu.set_bezug(WST_BEZUG_UNSEI);
                                if(Einstellung_dxf.drehtyp_L())
                                {
                                    nu.set_xs(w.laenge()-grundlinie_start.mipu().x());
                                    nu.set_ys(grundlinie_start.mipu().y());
                                    nu.set_xe(w.laenge()-grundlinie_ende.mipu().x());
                                    nu.set_ye(grundlinie_ende.mipu().y());
                                }else //if(Einstellung_dxf.drehtyp_B())
                                {
                                    nu.set_xs(grundlinie_start.mipu().x());
                                    nu.set_ys(w.breite()-grundlinie_start.mipu().y());
                                    nu.set_xe(grundlinie_ende.mipu().x());
                                    nu.set_ye(w.breite()-grundlinie_ende.mipu().y());
                                }
                            }
                            w.neue_bearbeitung(nu.text());
                            geo.clear();//Wichtig das es auch an dieser Stelle steht
                        }
                    }else if(geo.count() == 4)
                    {
                        strecke s1 = geo.at(0).text();//von UL nach UR
                        strecke s2 = geo.at(1).text();//von UR nach OR
                        strecke s3 = geo.at(2).text();//von OR nach OL
                        strecke s4 = s;//von OL nach UL
                        nut nu;
                        nu.set_afb("1");
                        QString ti;
                        ti = text_rechts(klasse, Einstellung_dxf_klassen.nut_vert());
                        ti = text_rechts(ti, Einstellung_dxf.paramtren());
                        ti.replace(Einstellung_dxf.dezitren(),".");
                        nu.set_tiefe(ti);
                        nu.set_breite(s2.laenge2d());
                        strecke tmp;
                        tmp.set_stapu(s2.mipu());
                        tmp.set_endpu(s4.mipu());
                        if(istOberseite)
                        {
                            nu.set_bezug(WST_BEZUG_OBSEI);
                            nu.set_xs(tmp.stapu().x());
                            nu.set_ys(tmp.stapu().y());
                            nu.set_xe(tmp.endpu().x());
                            nu.set_ye(tmp.endpu().y());
                        }else
                        {
                            nu.set_bezug(WST_BEZUG_UNSEI);
                            if(Einstellung_dxf.drehtyp_L())
                            {
                                nu.set_xs(w.laenge()-tmp.stapu().x());
                                nu.set_ys(tmp.stapu().y());
                                nu.set_xe(w.laenge()-tmp.endpu().x());
                                nu.set_ye(tmp.endpu().y());
                            }else //if(Einstellung_dxf.drehtyp_B())
                            {
                                nu.set_xs(tmp.stapu().x());
                                nu.set_ys(w.breite()-tmp.stapu().y());
                                nu.set_xe(tmp.endpu().x());
                                nu.set_ye(w.breite()-tmp.endpu().y());
                            }
                        }
                        w.neue_bearbeitung(nu.text());
                    }
                }
            }
        }
        geo.clear();
        //------------------------------Kreistasche:
        for(uint i=0;i<block.count();i++)
        {
            uint sta = text_links(block.at(i),"|").toUInt();
            uint end = text_rechts(block.at(i),"|").toUInt();
            uint anz = end-sta;
            QString klasse;
            klasse = dxf_wert(tz_name.at(sta,anz), tz_wert.at(sta,anz),\
                              DXF_AC1009_KLASSE);
            if(klasse.contains(Einstellung_dxf_klassen.kta()))
            {
                QString typ = dxf_wert(tz_name.at(sta,anz), tz_wert.at(sta,anz),\
                                       DXF_AC1009_NULL);
                if(typ == DXF_AC1009_KREIS)
                {
                    kreis k = dxf_kreis(tz_name.at(sta,anz), tz_wert.at(sta,anz), "AC1009");
                    bohrung bo;
                    bo.set_afb("1");
                    QString ti;
                    ti = text_rechts(klasse, Einstellung_dxf_klassen.kta());
                    ti = text_rechts(ti, Einstellung_dxf.paramtren());
                    if(ti.contains(Einstellung_dxf.kenWKZnr()))
                    {
                        QString wkznr = text_rechts(ti, Einstellung_dxf.kenWKZnr());
                        bo.set_wkznum(wkznr);
                        ti = text_links(ti, Einstellung_dxf.kenWKZnr());
                    }
                    ti.replace(Einstellung_dxf.dezitren(),".");
                    double ti_double = ti.toDouble();
                    if(ti_double == w.dicke())
                    {
                        ti_double = ti_double + 2;
                    }
                    if(ti_double < 0)
                    {
                        ti_double = w.dicke() - ti_double;
                    }
                    bo.set_tiefe(ti_double);
                    double dm = k.radius()*2;
                    dm = runden(dm, 1);
                    bo.set_dm(dm);
                    if(istOberseite)
                    {
                        bo.set_bezug(WST_BEZUG_OBSEI);
                        bo.set_x(k.mitte3d().x());
                        bo.set_y(k.mitte3d().y());
                    }else
                    {
                        bo.set_bezug(WST_BEZUG_UNSEI);
                        if(Einstellung_dxf.drehtyp_L())
                        {
                            bo.set_x(w.laenge()-k.mitte3d().x());
                            bo.set_y(k.mitte3d().y());
                        }else //if(Einstellung_dxf.drehtyp_B())
                        {
                            bo.set_x(k.mitte3d().x());
                            bo.set_y(w.breite()-k.mitte3d().y());
                        }
                    }
                    w.neue_bearbeitung(bo.text());
                }
            }
        }
        geo.clear();
        //------------------------------Rechtecktasche:
        for(uint i=0;i<block.count();i++)
        {
            uint sta = text_links(block.at(i),"|").toUInt();
            uint end = text_rechts(block.at(i),"|").toUInt();
            uint anz = end-sta;
            QString klasse;
            klasse = dxf_wert(tz_name.at(sta,anz), tz_wert.at(sta,anz),\
                              DXF_AC1009_KLASSE);
            if(klasse.contains(Einstellung_dxf_klassen.rta()))
            {
                QString typ = dxf_wert(tz_name.at(sta,anz), tz_wert.at(sta,anz),\
                                       DXF_AC1009_NULL);
                if(typ == DXF_AC1009_STRECKE)
                {
                    strecke s = dxf_strecke(tz_name.at(sta,anz), tz_wert.at(sta,anz), "AC1009");
                    geo.add_strecke(s);
                }else if(typ == DXF_AC1009_BOGEN)
                {
                    bogen b = dxf_bogen(tz_name.at(sta,anz), tz_wert.at(sta,anz), "AC1009");
                    geo.add_bogen(b);
                }
                //------------------------------
                text_zw geozw;
                //------------------------------
                if(geozw.count() == 4)//RTA wird durch 4 Strecken definiert?
                {
                    strecke s1 = geozw.at(0);//von OL nach OR
                    strecke s2 = geozw.at(1);//von OR nach UR
                    strecke s3 = geozw.at(2);//von UR nach UL
                    strecke s4 = geozw.at(3);//von UL nach OL
                    bool gesund = true;
                    if(!cagleich(s1.laenge2d(), s3.laenge2d(),0.1))
                    {
                        gesund = false;
                    }
                    if(!cagleich(s2.laenge2d(), s4.laenge2d(),0.1))
                    {
                        gesund = false;
                    }
                    strecke dg1;//Diagonale 1
                    dg1.set_stapu(s1.stapu());
                    dg1.set_endpu(s3.stapu());
                    strecke dg2;//Diagonale 2
                    dg2.set_stapu(s1.endpu());
                    dg2.set_endpu(s3.endpu());
                    //Wenn die Diagonalen gleich lang sind ist das 4Eck rechtwinkelig:
                    if(!cagleich(dg1.laenge2d(), dg2.laenge2d(),0.1))
                    {
                        gesund = false;
                    }
                    //Wenn die Endpunkte aufeinander liegen:
                    if(!cagleich(s1.endpu(), s2.stapu(),0.1))//OR
                    {
                        gesund = false;
                    }
                    if(!cagleich(s2.endpu(), s3.stapu(),0.1))//UR
                    {
                        gesund = false;
                    }
                    if(!cagleich(s3.endpu(), s4.stapu(),0.1))//UL
                    {
                        gesund = false;
                    }
                    if(!cagleich(s4.endpu(), s1.stapu(),0.1))//OL
                    {
                        gesund = false;
                    }
                    if(gesund == true)
                    {
                        rechtecktasche rt;
                        rt.set_afb("1");
                        QString ti;
                        ti = text_rechts(klasse, Einstellung_dxf_klassen.rta());
                        ti = text_rechts(ti, Einstellung_dxf.paramtren());
                        if(ti.contains(Einstellung_dxf.kenWKZnr()))
                        {
                            QString wkznr = text_rechts(ti, Einstellung_dxf.kenWKZnr());
                            rt.set_wkznum(wkznr);
                            ti = text_links(ti, Einstellung_dxf.kenWKZnr());
                        }
                        ti.replace(Einstellung_dxf.dezitren(),".");
                        double ti_double = ti.toDouble();
                        if(ti_double == w.dicke())
                        {
                            ti_double = ti_double + 2;
                        }
                        if(ti_double < 0)
                        {
                            ti_double = w.dicke() - ti_double;
                        }
                        rt.set_tiefe(ti_double);
                        rt.set_laenge(s1.laenge2d());
                        rt.set_breite(s2.laenge2d());
                        strecke tmp;
                        tmp.set_stapu(s2.mipu());
                        tmp.set_endpu(s4.mipu());
                        if(istOberseite)
                        {
                            rt.set_bezug(WST_BEZUG_OBSEI);
                            rt.set_x(tmp.mipu().x());
                            rt.set_y(tmp.mipu().y());
                            rt.set_drewi(s1.wink());
                        }else
                        {
                            rt.set_bezug(WST_BEZUG_UNSEI);
                            if(Einstellung_dxf.drehtyp_L())
                            {
                                rt.set_x(w.laenge()-tmp.mipu().x());
                                rt.set_y(tmp.mipu().y());
                            }else //if(Einstellung_dxf.drehtyp_B())
                            {
                                rt.set_x(tmp.mipu().x());
                                rt.set_y(w.breite()-tmp.mipu().y());
                            }
                            //Der Winkel hau einen Werk zwischen 0 und 360°
                            //1° entspricht 181° usw.
                            //das heißt, der Winkel kann bei Bedarf gekürzt werden:
                            double winkel = s1.wink();
                            if(winkel > 180)
                            {
                                winkel = winkel -180;
                            }
                            //Auf die Unterseite drehen, weil Drehen um L/2
                            //Bei drehen um B/2 verhällt sich der winkel genauso:
                            winkel = 180 - winkel;
                            rt.set_drewi(winkel);
                        }
                        w.neue_bearbeitung(rt.text());
                        geo.clear();
                    }
                }else if(geozw.count() == 8)//RTA wird durch 4 Strecken und 4 Bögen definiert?
                {
                    strecke s_ob = geozw.at(0);//von OR nach OL
                    strecke s_li = geozw.at(2);//von OL nach UL
                    strecke s_un = geozw.at(4);//von UL nach UR
                    strecke s_re = geozw.at(6);//von UR nach OR
                    bogen b_OL = geozw.at(1);
                    bogen b_UL = geozw.at(3);
                    bogen b_UR = geozw.at(5);
                    bogen b_OR = geozw.at(7);
                    bool gesund = true;
                    if(!cagleich(s_ob.laenge2d(), s_un.laenge2d(),0.1))
                    {
                        gesund = false;
                    }
                    if(!cagleich(s_li.laenge2d(), s_re.laenge2d(),0.1))
                    {
                        gesund = false;
                    }
                    if(!cagleich(b_OL.rad(), b_UL.rad(),0.1))
                    {
                        gesund = false;
                    }
                    if(!cagleich(b_OL.rad(), b_UR.rad(),0.1))
                    {
                        gesund = false;
                    }
                    if(!cagleich(b_OL.rad(), b_OR.rad(),0.1))
                    {
                        gesund = false;
                    }
                    strecke dg1;//Diagonale 1
                    dg1.set_stapu(s_ob.stapu());
                    dg1.set_endpu(s_un.stapu());
                    strecke dg2;//Diagonale 2
                    dg2.set_stapu(s_ob.endpu());
                    dg2.set_endpu(s_un.endpu());
                    strecke dg3;//Diagonale 3
                    dg3.set_stapu(s_li.stapu());
                    dg3.set_endpu(s_re.stapu());
                    strecke dg4;//Diagonale 4
                    dg4.set_stapu(s_li.endpu());
                    dg4.set_endpu(s_re.endpu());
                    //Wenn die Diagonalen gleich lang sind ist das 4Eck rechtwinkelig:
                    if(!cagleich(dg1.laenge2d(), dg2.laenge2d(),0.1))
                    {
                        gesund = false;
                    }
                    if(!cagleich(dg3.laenge2d(), dg4.laenge2d(),0.1))
                    {
                        gesund = false;
                    }
                    if(gesund == true)
                    {
                        rechtecktasche rt;
                        rt.set_afb("1");
                        QString ti;
                        ti = text_rechts(klasse, Einstellung_dxf_klassen.rta());
                        ti = text_rechts(ti, Einstellung_dxf.paramtren());
                        if(ti.contains(Einstellung_dxf.kenWKZnr()))
                        {
                            QString wkznr = text_rechts(ti, Einstellung_dxf.kenWKZnr());
                            rt.set_wkznum(wkznr);
                            ti = text_links(ti, Einstellung_dxf.kenWKZnr());
                        }
                        ti.replace(Einstellung_dxf.dezitren(),".");
                        double ti_double = ti.toDouble();
                        if(ti_double == w.dicke())
                        {
                            ti_double = ti_double + 2;
                        }
                        if(ti_double < 0)
                        {
                            ti_double = w.dicke() - ti_double;
                        }
                        rt.set_tiefe(ti_double);
                        strecke s_laenge;
                        s_laenge.set_stapu(s_li.stapu());
                        s_laenge.set_endpu(s_re.endpu());
                        rt.set_laenge(s_laenge.laenge2d());
                        strecke s_breite;
                        s_breite.set_stapu(s_ob.stapu());
                        s_breite.set_endpu(s_un.endpu());
                        rt.set_breite(s_breite.laenge2d());
                        strecke tmp;
                        tmp.set_stapu(s_ob.mipu());
                        tmp.set_endpu(s_un.mipu());
                        if(istOberseite)
                        {
                            rt.set_bezug(WST_BEZUG_OBSEI);
                            rt.set_x(tmp.mipu().x());
                            rt.set_y(tmp.mipu().y());
                            rt.set_drewi(s_ob.wink());
                        }else
                        {
                            rt.set_bezug(WST_BEZUG_UNSEI);
                            if(Einstellung_dxf.drehtyp_L())
                            {
                                rt.set_x(w.laenge()-tmp.mipu().x());
                                rt.set_y(tmp.mipu().y());
                            }else //if(Einstellung_dxf.drehtyp_B())
                            {
                                rt.set_x(tmp.mipu().x());
                                rt.set_y(w.breite()-tmp.mipu().y());
                            }
                            //Der Winkel hau einen Werk zwischen 0 und 360°
                            //1° entspricht 181° usw.
                            //das heißt, der Winkel kann bei Bedarf gekürzt werden:
                            double winkel = s_ob.wink();
                            if(winkel > 180)
                            {
                                winkel = winkel -180;
                            }
                            //Auf die Unterseite drehen, weil Drehen um L/2
                            //Bei drehen um B/2 verhällt sich der winkel genauso:
                            winkel = 180 - winkel;
                            rt.set_drewi(winkel);
                        }
                        rt.set_rad(b_OL.rad());
                        w.neue_bearbeitung(rt.text());
                        geo.clear();
                    }
                }
                //------------------------------
            }
        }
        geo.clear();
        //------------------------------Fräsung vertikal:
        punkt3d letztepos;
        bool konturanfang = true;
        for(uint i=0;i<block.count();i++)
        {
            double tolleranz = 0.1;
            uint sta = text_links(block.at(i),"|").toUInt();
            uint end = text_rechts(block.at(i),"|").toUInt();
            uint anz = end-sta;
            QString klasse;
            klasse = dxf_wert(tz_name.at(sta,anz), tz_wert.at(sta,anz),\
                              DXF_AC1009_KLASSE);
            if(klasse.contains(Einstellung_dxf_klassen.fraes_vert()))
            {
                QString posz;
                posz = text_mitte(klasse, Einstellung_dxf_klassen.fraes_vert(), \
                                  Einstellung_dxf.kenWKZnr());
                posz = text_rechts(posz, Einstellung_dxf.paramtren());
                posz.replace(Einstellung_dxf.dezitren(),".");
                double fraeserhoehe;
                double fti;
                fraeserhoehe = posz.toDouble();
                if(fraeserhoehe > 0)
                {
                    if(Einstellung_dxf.bezugTiFkonObSei())
                    {
                        fti = fraeserhoehe;
                        fraeserhoehe = w.dicke()-fraeserhoehe;
                    }else
                    {
                        fti = w.dicke()-fraeserhoehe;
                    }
                }else
                {
                    fti = fraeserhoehe * -1;
                    fti = fti + w.dicke();
                }
                QString werkznr;
                werkznr = text_rechts(klasse, Einstellung_dxf_klassen.fraes_vert());
                werkznr = text_rechts(werkznr, Einstellung_dxf.kenWKZnr());
                QString radkor = werkznr.at(werkznr.length()-1);
                werkznr = text_links(werkznr,radkor);
                if(radkor == Einstellung_dxf.kenRadKorLi())
                {
                    radkor = FRKOR_L;
                }else if(radkor == Einstellung_dxf.kenRadKorRe())
                {
                    radkor = FRKOR_R;
                }else
                {
                    radkor = FRKOR_M;
                }
                QString typ = dxf_wert(tz_name.at(sta,anz), tz_wert.at(sta,anz),\
                                       DXF_AC1009_NULL);
                if(typ == DXF_AC1009_STRECKE)
                {
                    //noch Z-Wert einarbeiten
                    //noch Fräser abfahren?
                    strecke s = dxf_strecke(tz_name.at(sta,anz), tz_wert.at(sta,anz), "AC1009");
                    if(konturanfang == true && i+1<block.count())
                    {
                        uint sta = text_links(block.at(i),"|").toUInt();
                        uint end = text_rechts(block.at(i),"|").toUInt();
                        uint anz = end-sta;
                        QString klasse2;
                        klasse2 = dxf_wert(tz_name.at(sta,anz), tz_wert.at(sta,anz),\
                                          DXF_AC1009_KLASSE);
                        if(klasse == klasse2)
                        {
                            QString typ = dxf_wert(tz_name.at(sta,anz), tz_wert.at(sta,anz),\
                                                   DXF_AC1009_NULL);
                            if(typ == DXF_AC1009_STRECKE)
                            {
                                strecke s2 = dxf_strecke(tz_name.at(sta,anz), tz_wert.at(sta,anz), "AC1009");
                                if(  cagleich(s.stapu(), s2.stapu(),0.1)  ||\
                                     cagleich(s.stapu(), s2.endpu(),0.1))
                                {
                                    s.richtung_unkehren();
                                }
                            }else if(typ == DXF_AC1009_BOGEN)
                            {
                                bogenac b2 = dxf_bogenac(tz_name.at(sta,anz), tz_wert.at(sta,anz), "AC1009");
                                if(  cagleich(s.stapu(), b2.spu(),0.1)  ||\
                                     cagleich(s.stapu(), b2.epu(),0.1))
                                {
                                    s.richtung_unkehren();
                                }
                            }
                        }
                    }
                    fraesergerade fg;
                    if(istOberseite)
                    {
                        if(cagleich(s.stapu(), letztepos, tolleranz))
                        {
                            konturanfang = false;
                        }else if(cagleich(s.endpu(), letztepos, tolleranz))
                        {
                            s.richtung_unkehren();
                            konturanfang = false;
                        }else
                        {
                            fraeseraufruf fa;
                            fa.set_wkznum(werkznr);
                            fa.set_tiefe(fti);
                            fa.set_radkor(radkor);
                            fa.set_x(s.stapu().x());
                            fa.set_y(s.stapu().y());
                            fa.set_z(fraeserhoehe);
                            w.neue_bearbeitung(fa.text());
                            konturanfang = true;
                        }
                        fg.set_bezug(WST_BEZUG_OBSEI);
                        fg.set_xs(s.stapu().x());
                        fg.set_ys(s.stapu().y());
                        fg.set_zs(fraeserhoehe);
                        fg.set_xe(s.endpu().x());
                        fg.set_ye(s.endpu().y());
                        fg.set_ze(fraeserhoehe);
                    }else
                    {
                        if(cagleich(s.stapu(), letztepos, tolleranz))
                        {
                            konturanfang = false;
                        }else if(cagleich(s.endpu(), letztepos, tolleranz))
                        {
                            s.richtung_unkehren();
                            konturanfang = false;
                        }else
                        {
                            fraeseraufruf fa;
                            fa.set_wkznum(werkznr);
                            fa.set_tiefe(fti);
                            fa.set_radkor(radkor);
                            fa.set_z(fraeserhoehe);
                            if(Einstellung_dxf.drehtyp_L())
                            {
                                fa.set_x(w.laenge()-s.stapu().x());
                                fa.set_y(s.stapu().y());
                            }else //if(Einstellung_dxf.drehtyp_B())
                            {
                                fa.set_x(s.stapu().x());
                                fa.set_y(w.breite()-s.stapu().y());
                            }
                            w.neue_bearbeitung(fa.text());
                            konturanfang = true;
                        }
                        fg.set_bezug(WST_BEZUG_UNSEI);
                        if(Einstellung_dxf.drehtyp_L())
                        {
                            fg.set_xs(w.laenge()-s.stapu().x());
                            fg.set_ys(s.stapu().y());
                            fg.set_zs(fraeserhoehe);
                            fg.set_xe(w.laenge()-s.endpu().x());
                            fg.set_ye(s.endpu().y());
                            fg.set_ze(fraeserhoehe);
                        }else //if(Einstellung_dxf.drehtyp_B())
                        {
                            fg.set_xs(s.stapu().x());
                            fg.set_ys(w.breite()-s.stapu().y());
                            fg.set_zs(fraeserhoehe);
                            fg.set_xe(s.endpu().x());
                            fg.set_ye(w.breite()-s.endpu().y());
                            fg.set_ze(fraeserhoehe);
                        }
                    }
                    w.neue_bearbeitung(fg.text());
                    letztepos = s.endpu();
                }else if(typ == DXF_AC1009_BOGEN)
                {
                    //noch Z-Wert einarbeiten
                    //noch Fräser abfahren?
                    bogenac b = dxf_bogenac(tz_name.at(sta,anz), tz_wert.at(sta,anz), "AC1009");
                    if(konturanfang == true && i+1<block.count())
                    {
                        uint sta = text_links(block.at(i),"|").toUInt();
                        uint end = text_rechts(block.at(i),"|").toUInt();
                        uint anz = end-sta;
                        QString klasse2;
                        klasse2 = dxf_wert(tz_name.at(sta,anz), tz_wert.at(sta,anz),\
                                          DXF_AC1009_KLASSE);
                        if(klasse == klasse2)
                        {
                            QString typ = dxf_wert(tz_name.at(sta,anz), tz_wert.at(sta,anz),\
                                                   DXF_AC1009_NULL);
                            if(typ == DXF_AC1009_STRECKE)
                            {
                                strecke s2 = dxf_strecke(tz_name.at(sta,anz), tz_wert.at(sta,anz), "AC1009");
                                if(  cagleich(b.spu(), s2.stapu(),0.1)  ||\
                                     cagleich(b.spu(), s2.endpu(),0.1))
                                {
                                    b.richtung_unkehren();
                                }
                            }else if(typ == DXF_AC1009_BOGEN)
                            {
                                bogenac b2 = dxf_bogenac(tz_name.at(sta,anz), tz_wert.at(sta,anz), "AC1009");
                                if(  cagleich(b.spu(), b2.spu(),0.1)  ||\
                                     cagleich(b.spu(), b2.epu(),0.1))
                                {
                                    b.richtung_unkehren();
                                }
                            }
                        }
                    }
                    fraeserbogen fb;
                    if(istOberseite)
                    {
                        if(cagleich(b.spu(), letztepos, tolleranz))
                        {
                            konturanfang = false;
                        }else if(cagleich(b.epu(), letztepos, tolleranz))
                        {
                            b.richtung_unkehren();
                            konturanfang = false;
                        }else
                        {
                            fraeseraufruf fa;
                            fa.set_wkznum(werkznr);
                            fa.set_tiefe(fti);
                            fa.set_radkor(radkor);
                            fa.set_x(b.spu().x());
                            fa.set_y(b.spu().y());
                            fa.set_z(fraeserhoehe);
                            w.neue_bearbeitung(fa.text());
                            konturanfang = true;
                        }
                        fb.set_bezug(WST_BEZUG_OBSEI);
                        fb.set_uzs(b.im_uzs());
                        fb.set_xs(b.spu().x());
                        fb.set_ys(b.spu().y());
                        fb.set_zs(fraeserhoehe);
                        fb.set_xe(b.epu().x());
                        fb.set_ye(b.epu().y());
                        fb.set_ze(fraeserhoehe);
                        fb.set_rad(b.rad());
                    }else
                    {
                        if(cagleich(b.spu(), letztepos, tolleranz))
                        {
                            konturanfang = false;
                        }else if(cagleich(b.epu(), letztepos, tolleranz))
                        {
                            b.richtung_unkehren();
                            konturanfang = false;
                        }else
                        {
                            fraeseraufruf fa;
                            fa.set_wkznum(werkznr);
                            fa.set_tiefe(fti);
                            fa.set_radkor(radkor);
                            fa.set_z(fraeserhoehe);
                            if(Einstellung_dxf.drehtyp_L())
                            {
                                fa.set_x(w.laenge()-b.spu().x());
                                fa.set_y(b.spu().y());
                            }else //if(Einstellung_dxf.drehtyp_B())
                            {
                                fa.set_x(b.spu().x());
                                fa.set_y(w.breite()-b.spu().y());
                            }
                            w.neue_bearbeitung(fa.text());
                            konturanfang = true;
                        }
                        fb.set_bezug(WST_BEZUG_UNSEI);
                        fb.set_uzs(!b.im_uzs());//reverse
                        if(Einstellung_dxf.drehtyp_L())
                        {
                            fb.set_xs(w.laenge()-b.spu().x());
                            fb.set_ys(b.spu().y());
                            fb.set_zs(fraeserhoehe);
                            fb.set_xe(w.laenge()-b.epu().x());
                            fb.set_ye(b.epu().y());
                            fb.set_ze(fraeserhoehe);
                        }else //if(Einstellung_dxf.drehtyp_B())
                        {
                            fb.set_xs(b.spu().x());
                            fb.set_ys(w.breite()-b.spu().y());
                            fb.set_zs(fraeserhoehe);
                            fb.set_xe(b.epu().x());
                            fb.set_ye(w.breite()-b.epu().y());
                            fb.set_ze(fraeserhoehe);
                        }
                        fb.set_rad(b.rad());
                    }
                    w.neue_bearbeitung(fb.text());
                    letztepos = b.epu();
                }
            }
        }
        geo.clear();
    }
    Wste.replace(Index, w);
    return 0;
}

void werkstuecke::set_fkon_gerade_laenge(double wert)
{
    Min_fkon_gerade_laenge = wert;
}
void werkstuecke::set_kurze_geraden_importieren(bool wert)
{
    Kurze_geraden_import = wert;
}
void werkstuecke::set_zugabe_gehrungen(double wert)
{
    Zugabe_gehrungen = wert;
}

//--------------------------------------------------get_xy:
bool werkstuecke::ist_bekannt(QString Werkstueckname)
{
    for(uint i=0; i<Namen.count() ;i++)
    {
        if(Werkstueckname == Namen.at(i))
        {
            return true;
        }
    }
    return false;
}
werkstueck* werkstuecke::wst(uint index)
{
    //übergibt eine Kopie des Wst
    //Änderungen an dieser Kopie werden nicht zurück in diese Instanz geschrieben.
    if(index >= 0 && index < Namen.count())
    {
        return &Wste[index];
    }else
    {
        //werkstueck w;   //leeres Wst
        return NULL;
    }
}
QString werkstuecke::name(uint index)
{
    if(index > 0 && index < Namen.count())
    {
        return Namen.at(index);
    }else
    {
        return "";
    }
}
QString werkstuecke::cad_fehler()
{
    QString msg;

    for(uint i=1; i<=anzahl() ;i++)
    {
        werkstueck teil = Wste.at(i-1);
        msg += teil.cad_fehler();
    }

    return msg;
}

//--------------------------------------------------Manipulationen:
void werkstuecke::clear()
{
    Namen.clear();
    Quellformate.clear();
    Wste.clear();
}
QString werkstuecke::stdnamen(text_zw namen_alt, text_zw namen_neu)
{
    QString baugruppenname; //Rückgabewert der Funktion
    //erster Durchlauf: Namen tauschen
    for(uint i = 0; i<Namen.count() ;i++)
    {
        QString tmp = Namen.at(i);
        for(uint ii=0; ii<namen_alt.count();ii++)
        {
            if(tmp.contains(namen_alt.at(ii)))
            {
                tmp.replace(namen_alt.at(ii), namen_neu.at(ii));
                Namen.edit(i, tmp);
                break;
            }
        }
    }

    //zweiter Durchlauf: Schranknummer löschen wenn möglich
    QString tmp = Namen.at(0);
    bool schranknummer_wurde_entfernt = false;//wird gebraucht als Prüfung für den 3. Durchlauf
    if(tmp.contains("_"))
    {
        tmp = text_links(tmp, "_");
        bool identisch = true;
        for(uint i = 1; i<Namen.count() ;i++)
        {
            if(  tmp != text_links(Namen.at(i), "_")  )
            {
                identisch = false;
                break;
            }
        }
        bool istbaugruppenname = false;
        if(tmp.at(0) == "S")//Schranknummer
        {
            if(tmp.at(1)=='0' || tmp.at(1)=='1' || tmp.at(1)=='2' || tmp.at(1)=='3' || tmp.at(1)=='4' || tmp.at(1)=='5' || tmp.at(1)=='6' || tmp.at(1)=='7' || tmp.at(1)=='8' || tmp.at(1)=='9')
            {
                istbaugruppenname = true;
            }
        }else if(tmp.at(0)=='#')//Baugruppenbezeichung
        {
            istbaugruppenname = true;
        }else if(tmp.at(0)=='@')//Baugruppenbezeichung nicht im Barcode
        {
            istbaugruppenname = true;
        }

        if(identisch == true && istbaugruppenname == true)
        {
            if(Namen.count() > 0)
            {
                baugruppenname = text_links(Namen.at(0),"_");
                if(baugruppenname.at(0)=='#')
                {
                    baugruppenname = text_rechts(baugruppenname, "#");
                }
            }
            for(uint i = 0; i<Namen.count() ;i++)
            {
                Namen.edit(  i, text_rechts(Namen.at(i),"_")  );
            }
            schranknummer_wurde_entfernt = true;

        }
    }

    //dritter Durchlauf: Nummer hinter Teilenamen löschen wenn möglich
    text_zw bekannte_namen;
    if(schranknummer_wurde_entfernt)
    {
        for(uint i = 0; i<Namen.count() ;i++)//Name für Name durchgehen
        {
            tmp = Namen.at(i);
            QString name_bis_ziffer ="";
            //Namen und Ziffer trennen:
            for(int ii=0; ii<tmp.count() ;ii++)//Namen zeichenweise durchgehen
            {
                if(!ist_ziffer(tmp.at(ii)))
                {
                    name_bis_ziffer += tmp.at(ii);
                }else
                {
                    break;
                }
            }
            //Prüfen, ob es diesen Namen bereits gibt:
            bool bekannt = false;
            for(uint iii=0; iii<bekannte_namen.count() ;iii++)//bekannte Namen nacheinander durchgehen
            {
                if(name_bis_ziffer.length() >0 && bekannte_namen.at(iii) == name_bis_ziffer)
                {
                    bekannt = true;
                    break;
                }
            }
            if(name_bis_ziffer.length() >0 && bekannt == false)//Wenn der Name noch nicht vergeben war
            {
                Namen.edit(i, name_bis_ziffer);
                bekannte_namen.add_hi(name_bis_ziffer);
            }
        }
    }

    //Nameninformatione in den einzenen werkstücken aktualisieren:
    for(uint i=0; i<Namen.count() ;i++)
    {
        werkstueck w = Wste.at(i);
        w.set_name(Namen.at(i));
        Wste.replace(i, w);
    }
    return baugruppenname;
}
void werkstuecke::sortieren()
{
    text_zw    tmp_Namen;
    text_zw    tmp_Quellformate;
    QVector<werkstueck> tmp_Wste;
    text_zw rankingList;
    rankingList.add_hi("Seite_li");
    rankingList.add_hi("Seite_re");
    rankingList.add_hi("Seite");
    rankingList.add_hi("MS_li");
    rankingList.add_hi("MS_re");
    rankingList.add_hi("MS");
    rankingList.add_hi("OB_li");
    rankingList.add_hi("OB_mi");
    rankingList.add_hi("OB_re");
    rankingList.add_hi("OB");
    rankingList.add_hi("UB_li");
    rankingList.add_hi("UB_mi");
    rankingList.add_hi("UB_re");
    rankingList.add_hi("UB");
    rankingList.add_hi("KB_ob");
    rankingList.add_hi("KB_li");
    rankingList.add_hi("KB_mi");
    rankingList.add_hi("KB_un");
    rankingList.add_hi("KB_re");
    rankingList.add_hi("KB");
    rankingList.add_hi("Trav_ob");
    rankingList.add_hi("Trav_un");
    rankingList.add_hi("Trav_vo");
    rankingList.add_hi("Trav_hi");
    rankingList.add_hi("Trav");
    rankingList.add_hi("Traver_ob");
    rankingList.add_hi("Traver_un");
    rankingList.add_hi("Traver_vo");
    rankingList.add_hi("Traver_hi");
    rankingList.add_hi("Traver");
    rankingList.add_hi("EB_ob");
    rankingList.add_hi("EB_li");
    rankingList.add_hi("EB_mi");
    rankingList.add_hi("EB_un");
    rankingList.add_hi("EB_re");
    rankingList.add_hi("EB");
    rankingList.add_hi("RW_ob");
    rankingList.add_hi("RW_li");
    rankingList.add_hi("RW_mi");
    rankingList.add_hi("RW_un");
    rankingList.add_hi("RW_re");
    rankingList.add_hi("RW");
    rankingList.add_hi("Tuer_li");
    rankingList.add_hi("Tuer_");
    rankingList.add_hi("Tuer_A");
    rankingList.add_hi("Tuer_B");
    rankingList.add_hi("Tuer_C");
    rankingList.add_hi("Tuer_D");
    rankingList.add_hi("Tuer_E");
    rankingList.add_hi("Tuer");
    rankingList.add_hi("Front_li");
    rankingList.add_hi("Front_");
    rankingList.add_hi("Front_A");
    rankingList.add_hi("Front_B");
    rankingList.add_hi("Front_C");
    rankingList.add_hi("Front_D");
    rankingList.add_hi("Front_E");
    rankingList.add_hi("Front");
    rankingList.add_hi("SF_A");
    rankingList.add_hi("SF_B");
    rankingList.add_hi("SF_C");
    rankingList.add_hi("SF_D");
    rankingList.add_hi("SF_E");
    rankingList.add_hi("SF");
    rankingList.add_hi("SS_A");
    rankingList.add_hi("SS_B");
    rankingList.add_hi("SS_C");
    rankingList.add_hi("SS_D");
    rankingList.add_hi("SS_E");
    rankingList.add_hi("SS");
    rankingList.add_hi("SV_A");
    rankingList.add_hi("SV_B");
    rankingList.add_hi("SV_C");
    rankingList.add_hi("SV_D");
    rankingList.add_hi("SV_E");
    rankingList.add_hi("SV");
    rankingList.add_hi("SH_A");
    rankingList.add_hi("SH_B");
    rankingList.add_hi("SH_C");
    rankingList.add_hi("SH_D");
    rankingList.add_hi("SH_E");
    rankingList.add_hi("SH");
    rankingList.add_hi("SB_A");
    rankingList.add_hi("SB_B");
    rankingList.add_hi("SB_C");
    rankingList.add_hi("SB_D");
    rankingList.add_hi("SB_E");
    rankingList.add_hi("SB");
    rankingList.add_hi("Sockel_li");
    rankingList.add_hi("Sockel_mi");
    rankingList.add_hi("Sockel_re");
    rankingList.add_hi("Sockel");
    text_zw kopiert;
    for(uint ii = 0; ii<Namen.count() ;ii++)
    {
        kopiert.add_hi("nein");
    }
    for(uint i = 0; i<rankingList.count() ;i++)
    {
        QString akt_ranking_name =rankingList.at(i);
        for(uint ii = 0; ii<Namen.count() ;ii++)
        {
            QString akt_wst_name = Namen.at(ii);
            if(kopiert.at(ii) != "ja")
            {
                if(akt_wst_name.contains(akt_ranking_name))
                {
                    //kopieren:
                    tmp_Namen.add_hi(akt_wst_name);
                    tmp_Quellformate.add_hi(Quellformate.at(ii));
                    werkstueck w = Wste.at(ii);
                    w.set_name(akt_wst_name);
                    tmp_Wste.append(w);
                    kopiert.edit(ii, "ja");
                }
            }
        }        
    }

    //2. Durchlauf. Jetzt kommen alle wst die nicht sortierbar waren:
    for(uint i = 0; i<Namen.count() ;i++)
    {
        QString akt_wst_name = Namen.at(i);
        if(kopiert.at(i) != "ja")
        {
            //kopieren:
            tmp_Namen.add_hi(akt_wst_name);
            tmp_Quellformate.add_hi(Quellformate.at(i));
            werkstueck w = Wste.at(i);
            w.set_name(akt_wst_name);
            tmp_Wste.append(w);
            kopiert.edit(i, "ja");
        }
    }
    Namen = tmp_Namen;
    Quellformate = tmp_Quellformate;
    Wste = tmp_Wste;
}

//--------------------------------------------------
//#######################################################################
//Private:
//#######################################################################
//--------------------------------------------------set_xy:

//--------------------------------------------------get_xy:
int werkstuecke::index(QString Werkstueckname)
{
    for(uint i=0; i<Namen.count() ;i++)
    {
        if(Namen.at(i)==Werkstueckname)
        {
            return i;
        }
    }
    return -1; //Wenn der Name nicht gefunden wurde
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
bool werkstuecke::ist_ziffer(const QChar zeichen)
{
    if(zeichen == '0' || zeichen == '1' || zeichen == '2' || zeichen == '2' || zeichen == '3' || zeichen == '4' || zeichen == '5' || zeichen == '6' || zeichen == '7' || zeichen == '8' || zeichen == '9')
    {
        return true;
    }else
    {
        return false;
    }
}

//--------------------------------------------------Manipulationen:
QString werkstuecke::var_einsetzen(werkstueck w, QString formel)
{
    if(formel.contains("'"))
    {
        formel.replace("'", ".");
    }
    if(formel.contains("B"))
    {
        formel.replace("B", w.breite_qstring());
    }
    if(formel.contains("L"))
    {
        formel.replace("L", w.laenge_qstring());
    }
    if(formel.contains("D"))
    {
        formel.replace("D", w.dicke_qstring());
    }
    return formel;
}

//--------------------------------------------------



