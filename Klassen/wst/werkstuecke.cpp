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
        Namen.zeile_anhaengen(Werkstueckname);
        Quellformate.zeile_anhaengen(Quellformat);
        werkstueck w(Werkstueckname);
        w.set_zugabe_gehrungen(Zugabe_gehrungen);
        Wste.append(w);
    }
    return false;
}
bool werkstuecke::import_fmc_oberseite(QString Werkstueckname, QString importtext)
{
    importtext = importtext.toUpper();
    uint Index = index(Werkstueckname);
    if(Index == 0)
    {
        neu(Werkstueckname, FMC);
        Index = index(Werkstueckname);
    }
    text_zeilenweise tz;
    tz.set_text(importtext);

    werkstueck w = Wste.at(Index-1);

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
        }else if(zeile.contains(FMC_KOMMENTAR))
        {
            i++;
            zeile = tz.zeile(i);
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
                    i=ii-1;
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
                        bo.set_x(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_BOHR_DM_Y)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bo.set_y(ausdruck_auswerten(tmp));
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
                    i=ii-1;
                    bo.set_tiefe(x1 + bohrtiefe);
                    bo.set_x(x1);
                    if(y1)
                    {
                        bo.set_y(y1);
                        w.neue_bearbeitung(bo.text());
                    }
                    if(y2)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y2);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_y(y1+y2);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(y3)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y3);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_y(y1+y2+y3);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(y4)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y4);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(y5)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y5);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4+y5);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(y6)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y6);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4+y5+y6);
                            w.neue_bearbeitung(bo.text());
                        }
                    }

                    if(x2 > 0)
                    {
                        bo.set_bezug(WST_BEZUG_RE);
                        bo.set_tiefe(w.laenge() - x2 + bohrtiefe);
                        bo.set_x(x2);

                        if(y1)
                        {
                            bo.set_y(y1);
                            w.neue_bearbeitung(bo.text());
                        }
                        if(y2)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y2);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_y(y1+y2);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(y3)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y3);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_y(y1+y2+y3);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(y4)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y4);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(y5)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y5);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4+y5);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(y6)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y6);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4+y5+y6);
                                w.neue_bearbeitung(bo.text());
                            }
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
                        double z = ausdruck_auswerten(tmp).toDouble();
                        bo.set_z(z);
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
            bo.set_bezug(WST_BEZUG_RE);
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

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    bo.set_tiefe(w.laenge() - x1 + bohrtiefe);
                    bo.set_x(x1);
                    if(y1)
                    {
                        bo.set_y(y1);
                        w.neue_bearbeitung(bo.text());
                    }
                    if(y2)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y2);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_y(y1+y2);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(y3)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y3);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_y(y1+y2+y3);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(y4)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y4);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(y5)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y5);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4+y5);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(y6)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y6);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4+y5+y6);
                            w.neue_bearbeitung(bo.text());
                        }
                    }

                    if(x2 >= 0)
                    {
                        bo.set_bezug(WST_BEZUG_LI);
                        bo.set_tiefe(x2 + bohrtiefe);
                        bo.set_x(x2);

                        if(y1)
                        {
                            bo.set_y(y1);
                            w.neue_bearbeitung(bo.text());
                        }
                        if(y2)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y2);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_y(y1+y2);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(y3)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y3);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_y(y1+y2+y3);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(y4)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y4);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(y5)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y5);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4+y5);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(y6)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y6);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4+y5+y6);
                                w.neue_bearbeitung(bo.text());
                            }
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
                        double z = ausdruck_auswerten(tmp).toDouble();
                        bo.set_z(z);
                    }else if(schluessel == FMC_HBEXP_X2)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        x2 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEXP_X1)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        x1 = ausdruck_auswerten(tmp).toDouble();
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
            bo.set_bezug(WST_BEZUG_VO);
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

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    bo.set_tiefe(y1 + bohrtiefe);
                    bo.set_y(y1);
                    if(x1)
                    {
                        bo.set_x(x1);
                        w.neue_bearbeitung(bo.text());
                    }
                    if(x2)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x2);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_x(x1+x2);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(x3)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x3);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_x(x1+x2+x3);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(x4)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x4);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_x(x1+x2+x3+x4);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(x5)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x5);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_x(x1+x2+x3+x4+x5);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(x6)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x6);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_x(x1+x2+x3+x4+x5+x6);
                            w.neue_bearbeitung(bo.text());
                        }
                    }

                    if(y2 > 0)
                    {
                        bo.set_bezug(WST_BEZUG_HI);
                        bo.set_tiefe(w.breite() - y2 + bohrtiefe);
                        bo.set_y(y2);

                        if(x1)
                        {
                            bo.set_x(x1);
                            w.neue_bearbeitung(bo.text());
                        }
                        if(x2)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x2);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_x(x1+x2);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(x3)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x3);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_x(x1+x2+x3);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(x4)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x4);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_x(x1+x2+x3+x4);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(x5)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x5);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_x(x1+x2+x3+x4+x5);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(x6)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x6);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_x(x1+x2+x3+x4+x5+x6);
                                w.neue_bearbeitung(bo.text());
                            }
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
                        double z = ausdruck_auswerten(tmp).toDouble();
                        bo.set_z(z);
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
            bo.set_bezug(WST_BEZUG_HI);
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

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    bo.set_tiefe(w.breite() - y1 + bohrtiefe);
                    bo.set_y(y1);
                    if(x1)
                    {
                        bo.set_x(x1);
                        w.neue_bearbeitung(bo.text());
                    }
                    if(x2)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x2);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_x(x1+x2);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(x3)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x3);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_x(x1+x2+x3);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(x4)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x4);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_x(x1+x2+x3+x4);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(x5)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x5);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_x(x1+x2+x3+x4+x5);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(x6)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x6);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_x(x1+x2+x3+x4+x5+x6);
                            w.neue_bearbeitung(bo.text());
                        }
                    }

                    if(y2 >= 0)
                    {
                        bo.set_bezug(WST_BEZUG_VO);
                        bo.set_tiefe(y2 + bohrtiefe);
                        bo.set_y(y2);

                        if(x1)
                        {
                            bo.set_x(x1);
                            w.neue_bearbeitung(bo.text());
                        }
                        if(x2)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x2);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_x(x1+x2);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(x3)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x3);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_x(x1+x2+x3);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(x4)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x4);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_x(x1+x2+x3+x4);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(x5)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x5);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_x(x1+x2+x3+x4+x5);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(x6)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x6);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_x(x1+x2+x3+x4+x5+x6);
                                w.neue_bearbeitung(bo.text());
                            }
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
                        double z = ausdruck_auswerten(tmp).toDouble();
                        bo.set_z(z);
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
            bo.set_bezug(WST_BEZUG_OBSEI);
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
                    i=ii-1;

                    bo.set_x(x1);

                    if(y1)
                    {
                        bo.set_y(y1);
                        w.neue_bearbeitung(bo.text());
                    }
                    if(y2)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y2);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_y(y1+y2);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(y3)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y3);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_y(y1+y2+y3);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(y4)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y4);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(y5)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y5);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4+y5);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(y6)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y6);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4+y5+y6);
                            w.neue_bearbeitung(bo.text());
                        }
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
                            if(kettenmass == false)
                            {
                                bo.set_y(y2);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_y(y1+y2);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(y3)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y3);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_y(y1+y2+y3);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(y4)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y4);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(y5)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y5);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4+y5);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(y6)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y6);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4+y5+y6);
                                w.neue_bearbeitung(bo.text());
                            }
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
            bo.set_bezug(WST_BEZUG_OBSEI);
            double y1 = 0;
            double y2 = -1;
            bool kettenmass = false;
            double x1 = 0;
            double x2 = 0;
            double x3 = 0;
            double x4 = 0;
            double x5 = 0;
            double x6 = 0;

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;

                    bo.set_y(y1);

                    if(x1)
                    {
                        bo.set_x(x1);
                        w.neue_bearbeitung(bo.text());
                    }
                    if(x2)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x2);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_x(x1+x2);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(x3)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x3);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_x(x1+x2+x3);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(x4)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x4);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_x(x1+x2+x3+x4);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(x5)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x5);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_x(x1+x2+x3+x4+x5);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(x6)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x6);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_x(x1+x2+x3+x4+x5+x6);
                            w.neue_bearbeitung(bo.text());
                        }
                    }

                    if(y2 > 0)
                    {
                        bo.set_y(y2);

                        if(x1)
                        {
                            bo.set_x(x1);
                            w.neue_bearbeitung(bo.text());
                        }
                        if(x2)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x2);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_x(x1+x2);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(x3)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x3);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_x(x1+x2+x3);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(x4)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x4);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_x(x1+x2+x3+x4);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(x5)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x5);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_x(x1+x2+x3+x4+x5);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(x6)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x6);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_x(x1+x2+x3+x4+x5+x6);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                    }

                    break;

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
            bo.set_bezug(WST_BEZUG_OBSEI);

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
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
                        bo.set_x(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_KTA_Y)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        bo.set_y(ausdruck_auswerten(tmp));
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
            rt.set_bezug(WST_BEZUG_OBSEI);

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
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
                        rt.set_x(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_RTA_Y)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        rt.set_y(ausdruck_auswerten(tmp));
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
                        rt.set_drewi(ausdruck_auswerten(tmp));
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
            n.set_bezug(WST_BEZUG_OBSEI);

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
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
                        n.set_xs(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_NUT_YS)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        n.set_ys(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_NUT_XE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        n.set_xe(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_NUT_YE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        n.set_ye(ausdruck_auswerten(tmp));
                    }
                }
            }
        }else if(zeile.contains(FMC_LORAE))
        {
            bohrung bo;
            bo.set_bezug(WST_BEZUG_OBSEI);
            double xs = 0;
            double xe = 0;
            double y1 = 0;
            double y2 = 0;
            double raster = 32;

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii;

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
            bo.set_bezug(WST_BEZUG_OBSEI);
            double xs = 0;
            double xm = 0;
            double y1 = 0;
            double y2 = 0;
            double raster = 32;

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;

                    double diff = xm - xs;
                    double xe = xm + diff;

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
            fraueseraufruf fa;
            fa.set_bezug(WST_BEZUG_OBSEI);

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    w.neue_bearbeitung(fa.text());
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
                        tmp = ausdruck_auswerten(tmp);
                        fa.set_x(tmp);
                    }else if(schluessel == FMC_FKON_Y)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        fa.set_y(tmp);
                    }else if(schluessel == FMC_FKON_Z)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        //werkstueck w = Wste.at(index-1);  //w ist bereits bekannt
                        double tiefe = w.dicke() - tmp.toDouble();
                        fa.set_tiefe(tiefe);//Tiefe, nicht Z-Wert!!
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
            fg.set_bezug(WST_BEZUG_OBSEI);

            //Startpunkt aus der vorherigen Bearbeitung heraus einlesen:
            text_zeilenweise bearb;
            bearb = w.bearb();
            text_zeilenweise letzte_bearb;
            letzte_bearb.set_trennzeichen(TRENNZ_BEARB_PARAM);
            letzte_bearb.set_text(bearb.zeile(bearb.zeilenanzahl()));
            if(letzte_bearb.zeile(1) == BEARBART_FRAESERAUFRUF)
            {
                fraueseraufruf tmp(letzte_bearb.text());
                fg.set_startpunkt(tmp.pos_vertikal());
            }else if(letzte_bearb.zeile(1) == BEARBART_FRAESERGERADE)
            {
                fraesergerade tmp(letzte_bearb.text());
                fg.set_startpunkt(tmp.ep());
            }else if(letzte_bearb.zeile(1) == BEARBART_FRAESERBOGEN)
            {
                fraeserbogen tmp(letzte_bearb.text());
                fg.set_startpunkt(tmp.ep());
            }

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
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
                        tmp = ausdruck_auswerten(tmp);
                        fg.set_xe(tmp);
                    }else if(schluessel == FMC_FKONG_YE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        fg.set_ye(tmp);
                    }else if(schluessel == FMC_FKONG_ZE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        if(tmp == "Z")
                        {
                            fg.set_ze(fg.zs());//Der Z-Wert gibt die Tiefe an
                        }else
                        {
                            tmp = var_einsetzen(w, tmp);
                            tmp = ausdruck_auswerten(tmp);
                            double tiefe = w.dicke() - tmp.toDouble();
                            fg.set_ze(tiefe);//Der Z-Wert gibt die Tiefe an
                        }
                    }
                }
            }
        }else if(zeile.contains(FMC_FKONBOGUZS)   || \
                 zeile.contains(FMC_FKONBOGGUZS)     )
        {
            fraeserbogen fb;
            fb.set_bezug(WST_BEZUG_OBSEI);

            if(zeile.contains(FMC_FKONBOGUZS))
            {
                fb.set_uzs(true);
            }else
            {
                fb.set_uzs(false);
            }

            //Startpunkt aus der vorherigen Bearbeitung heraus einlesen:
            text_zeilenweise bearb;
            bearb = w.bearb();
            text_zeilenweise letzte_bearb;
            letzte_bearb.set_trennzeichen(TRENNZ_BEARB_PARAM);
            letzte_bearb.set_text(bearb.zeile(bearb.zeilenanzahl()));
            if(letzte_bearb.zeile(1) == BEARBART_FRAESERAUFRUF)
            {
                fraueseraufruf tmp(letzte_bearb.text());
                fb.set_startpunkt(tmp.pos_vertikal());
            }else if(letzte_bearb.zeile(1) == BEARBART_FRAESERGERADE)
            {
                fraesergerade tmp(letzte_bearb.text());
                fb.set_startpunkt(tmp.ep());
            }else if(letzte_bearb.zeile(1) == BEARBART_FRAESERBOGEN)
            {
                fraeserbogen tmp(letzte_bearb.text());
                fb.set_startpunkt(tmp.ep());
            }

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
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
                        tmp = ausdruck_auswerten(tmp);
                        fb.set_xe(tmp);
                    }else if(schluessel == FMC_FKONBOG_YE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        fb.set_ye(tmp);
                    }else if(schluessel == FMC_FKONBOG_ZE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        if(tmp == "Z")
                        {
                            fb.set_ze(fb.zs());//Der Z-Wert gibt die Tiefe an
                        }else
                        {
                            tmp = var_einsetzen(w, tmp);
                            tmp = ausdruck_auswerten(tmp);
                            double tiefe = w.dicke() - tmp.toDouble();
                            fb.set_ze(tiefe);//Der Z-Wert gibt die Tiefe an
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
            fraueseraufruf fa;
            fraesergerade fg;
            fa.set_bezug(WST_BEZUG_OBSEI);
            fg.set_bezug(WST_BEZUG_OBSEI);

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
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
                        fa.set_x(tmp);
                        fg.set_xs(tmp);
                    }else if(schluessel == FMC_FALZ_YS)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        fa.set_y(tmp);
                        fg.set_ys(tmp);
                    }else if(schluessel == FMC_FALZ_XE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        fg.set_xe(tmp);
                    }else if(schluessel == FMC_FALZ_YE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        fg.set_ye(tmp);
                    }else if(schluessel == FMC_FALZ_Z)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        //werkstueck w = Wste.at(index-1);  //w ist bereits bekannt
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
            botopf.set_bezug(WST_BEZUG_OBSEI);
            boduebel.set_bezug(WST_BEZUG_OBSEI);

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

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;

                    if(seite == 1)
                    {
                        if(abst1 > 0)
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
                        if(abst2 > 0)
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
                        if(abst3 > 0)
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
                        if(abst4 > 0)
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
                        if(abst5 > 0)
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
                    }else if(seite == 2)
                    {

                    }else if(seite == 3)
                    {
                        if(abst1 > 0)
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
                        if(abst2 > 0)
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
                        if(abst3 > 0)
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
                        if(abst4 > 0)
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
                        if(abst5 > 0)
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
                    }else if(seite == 4)
                    {

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
            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    punkt3d sp, ep;
                    sp.set_x(spx);
                    sp.set_y(spy);
                    ep.set_x(epx);
                    ep.set_y(epy);
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
                            ge.set_bezug(WST_BEZUG_OBSEI);
                        }else//Spitze auf der Oberseite
                        {
                            ge.set_bezug(WST_BEZUG_UNSEI);
                        }
                    }else if(schluessel == FMC_GEHR_WKZNR)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        ge.set_wkznum(tmp);
                    }
                }
            }
        }

    }

    Wste.replace(Index-1, w);

    return 0;
}
bool werkstuecke::import_fmc_unterseite(QString Werkstueckname, QString importtext)
{
    importtext = importtext.toUpper();
    uint Index = index(Werkstueckname);
    if(Index == 0)
    {
        return 1;   //Die Bearbeitung soll nur auf die Unterseite importiert werden,
                    //wenn bereits die Bearbeitung auf der Oberseite importiert wurde
    }
    text_zeilenweise tz;
    tz.set_text(importtext);

    werkstueck w = Wste.at(Index-1);

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
                    i=ii-1;
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
                        double x = ausdruck_auswerten(tmp).toDouble();
                        x = w.laenge()-x;
                        bo.set_x(x);
                    }else if(schluessel == FMC_BOHR_DM_Y)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bo.set_y(ausdruck_auswerten(tmp));
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
                    i=ii-1;
                    bo.set_tiefe(x1 + bohrtiefe);
                    bo.set_x(x1);
                    if(y1)
                    {
                        bo.set_y(y1);
                        w.neue_bearbeitung(bo.text());
                    }
                    if(y2)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y2);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_y(y1+y2);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(y3)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y3);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_y(y1+y2+y3);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(y4)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y4);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(y5)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y5);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4+y5);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(y6)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y6);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4+y5+y6);
                            w.neue_bearbeitung(bo.text());
                        }
                    }

                    if(x2 > 0)
                    {
                        bo.set_bezug(WST_BEZUG_LI);//Bearbeitung von Unterseite auf Oberseite bringen (drehen um l/2)
                        bo.set_tiefe(w.laenge() - x2 + bohrtiefe);
                        bo.set_x(x2);

                        if(y1)
                        {
                            bo.set_y(y1);
                            w.neue_bearbeitung(bo.text());
                        }
                        if(y2)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y2);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_y(y1+y2);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(y3)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y3);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_y(y1+y2+y3);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(y4)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y4);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(y5)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y5);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4+y5);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(y6)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y6);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4+y5+y6);
                                w.neue_bearbeitung(bo.text());
                            }
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
                        double z = w.dicke() - ausdruck_auswerten(tmp).toDouble();//Umrechen auf Oberseite
                        bo.set_z(z);
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
            bo.set_bezug(WST_BEZUG_LI);//Bearbeitung von Unterseite auf Oberseite bringen (drehen um l/2)
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

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    bo.set_tiefe(w.laenge() - x1 + bohrtiefe);
                    bo.set_x(x1);
                    if(y1)
                    {
                        bo.set_y(y1);
                        w.neue_bearbeitung(bo.text());
                    }
                    if(y2)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y2);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_y(y1+y2);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(y3)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y3);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_y(y1+y2+y3);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(y4)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y4);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(y5)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y5);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4+y5);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(y6)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y6);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4+y5+y6);
                            w.neue_bearbeitung(bo.text());
                        }
                    }

                    if(x2 >= 0)
                    {
                        bo.set_bezug(WST_BEZUG_RE);//Bearbeitung von Unterseite auf Oberseite bringen (drehen um l/2)
                        bo.set_tiefe(x2 + bohrtiefe);
                        bo.set_x(x2);

                        if(y1)
                        {
                            bo.set_y(y1);
                            w.neue_bearbeitung(bo.text());
                        }
                        if(y2)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y2);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_y(y1+y2);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(y3)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y3);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_y(y1+y2+y3);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(y4)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y4);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(y5)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y5);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4+y5);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(y6)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y6);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4+y5+y6);
                                w.neue_bearbeitung(bo.text());
                            }
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
                        double z = w.dicke() - ausdruck_auswerten(tmp).toDouble();//Umrechen auf Oberseite
                        bo.set_z(z);
                    }else if(schluessel == FMC_HBEXP_X2)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        x2 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEXP_X1)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        x1 = ausdruck_auswerten(tmp).toDouble();
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
            bo.set_bezug(WST_BEZUG_VO);
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

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    bo.set_tiefe(y1 + bohrtiefe);
                    bo.set_y(y1);

                    if(x1)
                    {
                        bo.set_x(x1);
                        w.neue_bearbeitung(bo.text());
                    }
                    if(x2)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x2);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_x(x1+x2);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(x3)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x3);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_x(x1+x2+x3);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(x4)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x4);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_x(x1+x2+x3+x4);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(x5)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x5);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_x(x1+x2+x3+x4+x5);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(x6)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x6);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_x(x1+x2+x3+x4+x5+x6);
                            w.neue_bearbeitung(bo.text());
                        }
                    }

                    if(y2 > 0)
                    {
                        bo.set_bezug(WST_BEZUG_HI);
                        bo.set_tiefe(w.breite() - y2 + bohrtiefe);
                        bo.set_y(y2);

                        if(x1)
                        {
                            bo.set_x(x1);
                            w.neue_bearbeitung(bo.text());
                        }
                        if(x2)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x2);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_x(x1+x2);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(x3)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x3);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_x(x1+x2+x3);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(x4)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x4);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_x(x1+x2+x3+x4);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(x5)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x5);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_x(x1+x2+x3+x4+x5);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(x6)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x6);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_x(x1+x2+x3+x4+x5+x6);
                                w.neue_bearbeitung(bo.text());
                            }
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
                        double z = w.dicke() - ausdruck_auswerten(tmp).toDouble();//Umrechen auf Oberseite
                        bo.set_z(z);
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
                            x1 = w.laenge() - ausdruck_auswerten(tmp).toDouble();//Umrechen auf Oberseite
                        }
                    }else if(schluessel == FMC_HBEYP_X2)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x2 = w.laenge() - ausdruck_auswerten(tmp).toDouble();//Umrechen auf Oberseite
                        }
                    }else if(schluessel == FMC_HBEYP_X3)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x3 = w.laenge() - ausdruck_auswerten(tmp).toDouble();//Umrechen auf Oberseite
                        }
                    }else if(schluessel == FMC_HBEYP_X4)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x4 = w.laenge() - ausdruck_auswerten(tmp).toDouble();//Umrechen auf Oberseite
                        }
                    }else if(schluessel == FMC_HBEYP_X5)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x5 = w.laenge() - ausdruck_auswerten(tmp).toDouble();//Umrechen auf Oberseite
                        }
                    }else if(schluessel == FMC_HBEYP_X6)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x6 = w.laenge() - ausdruck_auswerten(tmp).toDouble();//Umrechen auf Oberseite
                        }
                    }
                }
            }
        }else if(zeile.contains(FMC_HBEYM))
        {
            bohrung bo;
            bo.set_bezug(WST_BEZUG_HI);
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

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    bo.set_tiefe(w.breite() - y1 + bohrtiefe);
                    bo.set_y(y1);

                    if(x1)
                    {
                        bo.set_x(x1);
                        w.neue_bearbeitung(bo.text());
                    }
                    if(x2)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x2);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_x(x1+x2);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(x3)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x3);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_x(x1+x2+x3);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(x4)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x4);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_x(x1+x2+x3+x4);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(x5)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x5);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_x(x1+x2+x3+x4+x5);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(x6)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x6);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_x(x1+x2+x3+x4+x5+x6);
                            w.neue_bearbeitung(bo.text());
                        }
                    }

                    if(y2 >= 0)
                    {
                        bo.set_bezug(WST_BEZUG_VO);
                        bo.set_tiefe(y2 + bohrtiefe);
                        bo.set_y(y2);

                        if(x1)
                        {
                            bo.set_x(x1);
                            w.neue_bearbeitung(bo.text());
                        }
                        if(x2)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x2);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_x(x1+x2);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(x3)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x3);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_x(x1+x2+x3);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(x4)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x4);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_x(x1+x2+x3+x4);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(x5)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x5);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_x(x1+x2+x3+x4+x5);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(x6)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x6);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_x(x1+x2+x3+x4+x5+x6);
                                w.neue_bearbeitung(bo.text());
                            }
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
                        double z = w.dicke() - ausdruck_auswerten(tmp).toDouble();//Umrechen auf Oberseite
                        bo.set_z(z);
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
                            x1 = w.laenge() - ausdruck_auswerten(tmp).toDouble();//Umrechen auf Oberseite
                        }
                    }else if(schluessel == FMC_HBEYP_X2)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x2 = w.laenge() - ausdruck_auswerten(tmp).toDouble();//Umrechen auf Oberseite
                        }
                    }else if(schluessel == FMC_HBEYP_X3)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x3 = w.laenge() - ausdruck_auswerten(tmp).toDouble();//Umrechen auf Oberseite
                        }
                    }else if(schluessel == FMC_HBEYP_X4)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x4 = w.laenge() - ausdruck_auswerten(tmp).toDouble();//Umrechen auf Oberseite
                        }
                    }else if(schluessel == FMC_HBEYP_X5)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x5 = w.laenge() - ausdruck_auswerten(tmp).toDouble();//Umrechen auf Oberseite
                        }
                    }else if(schluessel == FMC_HBEYP_X6)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x6 = w.laenge() - ausdruck_auswerten(tmp).toDouble();//Umrechen auf Oberseite
                        }
                    }
                }
            }
        }else if(zeile.contains(FMC_BOBIY))
        {
            bohrung bo;
            bo.set_bezug(WST_BEZUG_UNSEI);
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
                    i=ii-1;

                    bo.set_x(x1);

                    if(y1)
                    {
                        bo.set_y(y1);
                        w.neue_bearbeitung(bo.text());
                    }
                    if(y2)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y2);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_y(y1+y2);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(y3)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y3);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_y(y1+y2+y3);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(y4)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y4);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(y5)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y5);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4+y5);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(y6)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y6);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4+y5+y6);
                            w.neue_bearbeitung(bo.text());
                        }
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
                            if(kettenmass == false)
                            {
                                bo.set_y(y2);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_y(y1+y2);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(y3)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y3);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_y(y1+y2+y3);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(y4)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y4);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(y5)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y5);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4+y5);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(y6)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y6);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4+y5+y6);
                                w.neue_bearbeitung(bo.text());
                            }
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
                        tmp = ausdruck_auswerten(tmp);
                        x1 = w.laenge() - tmp.toDouble();
                    }else if(schluessel == FMC_BOBIY_X2)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        if(tmp.contains("X1"))
                        {
                            tmp.replace("X1",double_to_qstring(x1));
                        }
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        x2 = w.laenge() - tmp.toDouble();
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
            bo.set_bezug(WST_BEZUG_OBSEI);
            double y1 = 0;
            double y2 = -1;
            bool kettenmass = false;
            double x1 = 0;
            double x2 = 0;
            double x3 = 0;
            double x4 = 0;
            double x5 = 0;
            double x6 = 0;

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;

                    bo.set_y(y1);

                    if(x1)
                    {
                        bo.set_x(x1);
                        w.neue_bearbeitung(bo.text());
                    }
                    if(x2)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x2);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_x(x1+x2);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(x3)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x3);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_x(x1+x2+x3);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(x4)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x4);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_x(x1+x2+x3+x4);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(x5)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x5);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_x(x1+x2+x3+x4+x5);
                            w.neue_bearbeitung(bo.text());
                        }
                    }
                    if(x6)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x6);
                            w.neue_bearbeitung(bo.text());
                        }else
                        {
                            bo.set_x(x1+x2+x3+x4+x5+x6);
                            w.neue_bearbeitung(bo.text());
                        }
                    }

                    if(y2 > 0)
                    {
                        bo.set_y(y2);

                        if(x1)
                        {
                            bo.set_x(x1);
                            w.neue_bearbeitung(bo.text());
                        }
                        if(x2)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x2);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_x(x1+x2);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(x3)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x3);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_x(x1+x2+x3);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(x4)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x4);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_x(x1+x2+x3+x4);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(x5)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x5);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_x(x1+x2+x3+x4+x5);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                        if(x6)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x6);
                                w.neue_bearbeitung(bo.text());
                            }else
                            {
                                bo.set_x(x1+x2+x3+x4+x5+x6);
                                w.neue_bearbeitung(bo.text());
                            }
                        }
                    }

                    break;

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
                            tmp = ausdruck_auswerten(tmp);
                            x1 = w.laenge() - tmp.toDouble();
                        }
                    }else if(schluessel == FMC_BOBIX_X2)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            tmp = ausdruck_auswerten(tmp);
                            x2 = w.laenge() - tmp.toDouble();
                        }
                    }else if(schluessel == FMC_BOBIX_X3)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            tmp = ausdruck_auswerten(tmp);
                            x3 = w.laenge() - tmp.toDouble();
                        }
                    }else if(schluessel == FMC_BOBIX_X4)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            tmp = ausdruck_auswerten(tmp);
                            x4 = w.laenge() - tmp.toDouble();
                        }
                    }else if(schluessel == FMC_BOBIX_X5)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            tmp = ausdruck_auswerten(tmp);
                            x5 = w.laenge() - tmp.toDouble();
                        }
                    }else if(schluessel == FMC_BOBIX_X6)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            tmp = ausdruck_auswerten(tmp);
                            x6 = w.laenge() - tmp.toDouble();
                        }
                    }
                }
            }
        }else if(zeile.contains(FMC_KTA))
        {
            bohrung bo;
            bo.set_bezug(WST_BEZUG_UNSEI);

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
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
                        bo.set_dm(ausdruck_auswerten(tmp));
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
                        double x = ausdruck_auswerten(tmp).toDouble();
                        x = w.laenge()-x;
                        bo.set_x(x);
                    }else if(schluessel == FMC_KTA_Y)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        bo.set_y(ausdruck_auswerten(tmp));
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
            rt.set_bezug(WST_BEZUG_UNSEI);

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
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
                        double x = ausdruck_auswerten(tmp).toDouble();
                        x = w.laenge()-x;
                        rt.set_x(x);
                    }else if(schluessel == FMC_RTA_Y)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        rt.set_y(ausdruck_auswerten(tmp));
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
                        tmp = ausdruck_auswerten(tmp);
                        double winkel = tmp.toDouble();
                        //Der Winkel hau einen Werk zwischen 0 und 360°
                        //1° entspricht 181° usw.
                        //das heißt, der Winkel kann bei Bedarf gekürzt werden:
                        if(winkel > 180)
                        {
                            winkel = winkel -180;
                        }
                        //Auf die Unterseite drehen, weil Drehen um L/2
                        //Bei drehen um B/2 verhällt sich der winkel genauso:
                        winkel = 180 - winkel;
                        rt.set_drewi(winkel);
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
            n.set_bezug(WST_BEZUG_UNSEI);

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
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
                        double x = ausdruck_auswerten(tmp).toDouble();
                        x = w.laenge()-x;
                        n.set_xs(x);
                    }else if(schluessel == FMC_NUT_YS)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        n.set_ys(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_NUT_XE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        double x = ausdruck_auswerten(tmp).toDouble();
                        x = w.laenge()-x;
                        n.set_xe(x);
                    }else if(schluessel == FMC_NUT_YE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        n.set_ye(ausdruck_auswerten(tmp));
                    }
                }
            }
        }else if(zeile.contains(FMC_LORAE))
        {
            bohrung bo;
            bo.set_bezug(WST_BEZUG_UNSEI);
            double xs = 0;
            double xe = 0;
            double y1 = 0;
            double y2 = 0;
            double raster = 32;

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;

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
                        xs = w.laenge()-xs;
                    }else if(schluessel == FMC_LORAE_XE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        xe = ausdruck_auswerten(tmp).toDouble();
                        xe = w.laenge()-xe;
                    }else if(schluessel == FMC_LORAE_Y1)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        y1 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_LORAE_Y2)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
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
            bo.set_bezug(WST_BEZUG_UNSEI);
            double xs = 0;
            double xm = 0;
            double y1 = 0;
            double y2 = 0;
            double raster = 32;

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;

                    double diff = xm - xs;
                    double xe = xm + diff;

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
                        xs = w.laenge()-xs;
                    }else if(schluessel == FMC_LORAM_XM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        xm = ausdruck_auswerten(tmp).toDouble();
                        xm = w.laenge()-xm;
                    }else if(schluessel == FMC_LORAM_Y1)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        y1 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_LORAM_Y2)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
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
            fraueseraufruf fa;
            fa.set_bezug(WST_BEZUG_UNSEI);

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    w.neue_bearbeitung(fa.text());
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
                        tmp = ausdruck_auswerten(tmp);
                        double x = tmp.toDouble();
                        x = w.laenge()-x;
                        fa.set_x(x);
                    }else if(schluessel == FMC_FKON_Y)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        fa.set_y(tmp);
                    }else if(schluessel == FMC_FKON_Z)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        werkstueck w = Wste.at(Index-1);
                        double tiefe = w.dicke() - tmp.toDouble();
                        fa.set_tiefe(tiefe);//Tiefe, nicht Z-Wert!!
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
            fg.set_bezug(WST_BEZUG_UNSEI);

            //Startpunkt aus der vorherigen Bearbeitung heraus einlesen:
            text_zeilenweise bearb;
            bearb = w.bearb();
            text_zeilenweise letzte_bearb;
            letzte_bearb.set_trennzeichen(TRENNZ_BEARB_PARAM);
            letzte_bearb.set_text(bearb.zeile(bearb.zeilenanzahl()));
            if(letzte_bearb.zeile(1) == BEARBART_FRAESERAUFRUF)
            {
                fraueseraufruf tmp(letzte_bearb.text());
                fg.set_startpunkt(tmp.pos_vertikal());
            }else if(letzte_bearb.zeile(1) == BEARBART_FRAESERGERADE)
            {
                fraesergerade tmp(letzte_bearb.text());
                fg.set_startpunkt(tmp.ep());
            }else if(letzte_bearb.zeile(1) == BEARBART_FRAESERBOGEN)
            {
                fraeserbogen tmp(letzte_bearb.text());
                fg.set_startpunkt(tmp.ep());
            }

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    if(fg.laenge_2d() > Min_fkon_gerade_laenge || \
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
                        tmp = ausdruck_auswerten(tmp);
                        double x = tmp.toDouble();
                        x = w.laenge()-x;
                        fg.set_xe(x);
                    }else if(schluessel == FMC_FKONG_YE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        fg.set_ye(tmp);
                    }else if(schluessel == FMC_FKONG_ZE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        if(tmp == "Z")
                        {
                            fg.set_ze(fg.zs());//Der Z-Wert gibt die Tiefe an
                        }else
                        {
                            tmp = var_einsetzen(w, tmp);
                            tmp = ausdruck_auswerten(tmp);
                            //werkstueck w = Wste.at(index-1); //w ist bereits bekannt
                            double tiefe = w.dicke() - tmp.toDouble();
                            fg.set_ze(tiefe);//Der Z-Wert gibt die Tiefe an
                        }
                    }
                }
            }
        }else if(zeile.contains(FMC_FKONBOGUZS)   || \
                 zeile.contains(FMC_FKONBOGGUZS)     )
        {
            fraeserbogen fb;
            fb.set_bezug(WST_BEZUG_UNSEI);

            if(zeile.contains(FMC_FKONBOGUZS))
            {
                fb.set_uzs(true);
            }else
            {
                fb.set_uzs(false);
            }

            //Startpunkt aus der vorherigen Bearbeitung heraus einlesen:
            text_zeilenweise bearb;
            bearb = w.bearb();
            text_zeilenweise letzte_bearb;
            letzte_bearb.set_trennzeichen(TRENNZ_BEARB_PARAM);
            letzte_bearb.set_text(bearb.zeile(bearb.zeilenanzahl()));
            if(letzte_bearb.zeile(1) == BEARBART_FRAESERAUFRUF)
            {
                fraueseraufruf tmp(letzte_bearb.text());
                fb.set_startpunkt(tmp.pos_vertikal());
            }else if(letzte_bearb.zeile(1) == BEARBART_FRAESERGERADE)
            {
                fraesergerade tmp(letzte_bearb.text());
                fb.set_startpunkt(tmp.ep());
            }else if(letzte_bearb.zeile(1) == BEARBART_FRAESERBOGEN)
            {
                fraeserbogen tmp(letzte_bearb.text());
                fb.set_startpunkt(tmp.ep());
            }

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
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
                        tmp = ausdruck_auswerten(tmp);
                        double x = tmp.toDouble();
                        x = w.laenge()-x;
                        fb.set_xe(x);
                    }else if(schluessel == FMC_FKONBOG_YE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        fb.set_ye(tmp);
                    }else if(schluessel == FMC_FKONBOG_ZE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        if(tmp == "Z")
                        {
                            fb.set_ze(fb.zs());//Der Z-Wert gibt die Tiefe an
                        }else
                        {
                            tmp = var_einsetzen(w, tmp);
                            tmp = ausdruck_auswerten(tmp);
                            double tiefe = w.dicke() - tmp.toDouble();
                            fb.set_ze(tiefe);//Der Z-Wert gibt die Tiefe an
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
            fraueseraufruf fa;
            fraesergerade fg;
            fa.set_bezug(WST_BEZUG_UNSEI);
            fg.set_bezug(WST_BEZUG_UNSEI);

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
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
                        double x = tmp.toDouble();
                        x = w.laenge()-x;
                        fa.set_x(x);
                        fg.set_xs(x);
                    }else if(schluessel == FMC_FALZ_YS)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        fa.set_y(tmp);
                        fg.set_ys(tmp);
                    }else if(schluessel == FMC_FALZ_XE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        double x = tmp.toDouble();
                        x = w.laenge()-x;
                        fg.set_xe(x);
                    }else if(schluessel == FMC_FALZ_YE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        fg.set_ye(tmp);
                    }else if(schluessel == FMC_FALZ_Z)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        //werkstueck w = Wste.at(index-1);  //w ist bereits bekannt
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

        }else if(zeile.contains(FMC_GEHR))
        {
            gehrung ge;
            double spx = 0;
            double spy = 0;
            double epx = 0;
            double epy = 0;
            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    punkt3d sp, ep;
                    sp.set_x(spx);
                    sp.set_y(spy);
                    ep.set_x(epx);
                    ep.set_y(epy);
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
                        spx = w.laenge()-spx;
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
                        epx = w.laenge()-epx;
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
                        //Hier muss ggf korrigiert werden (Drehen um L/2)
                        //Wenn die Werte später mal gebraucht werden
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        ge.set_winkel(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_GEHR_BEZUG)
                    {
                        //Hier muss ggf korrigiert werden (Drehen um L/2)
                        //Wenn die Werte später mal gebraucht werden
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp).toDouble();
                        if(tmp == 1)//Spitze auf der Unterseite
                        {
                            ge.set_bezug(WST_BEZUG_OBSEI);
                        }else//Spitze auf der Oberseite
                        {
                            ge.set_bezug(WST_BEZUG_UNSEI);
                        }
                    }else if(schluessel == FMC_GEHR_WKZNR)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        ge.set_wkznum(tmp);
                    }
                }
            }
        }

    }

    Wste.replace(Index-1, w);

    return 0;
}
QString werkstuecke::dxf_wert(QString namen, QString werte, QString gesucht)
{
    text_zeilenweise tz_name;
    text_zeilenweise tz_wert;
    tz_name.set_text(namen);
    tz_wert.set_text(werte);
    QString ret;
    for(uint i=1; i<=tz_name.zeilenanzahl() ;i++)
    {
        if(tz_name.zeile(i) == gesucht)
        {
            ret = tz_wert.zeile(i);
            break;
        }
    }
    return ret;
}
bool werkstuecke::import_dxf(QString Werkstueckname, QString importtext, bool istOberseite)
{
    uint Index = index(Werkstueckname);
    if(Index == 0)
    {
        neu(Werkstueckname, DXF);
        Index = index(Werkstueckname);
    }
    text_zeilenweise tz, tz_name, tz_wert;
    tz.set_text(importtext);
    werkstueck w = Wste.at(Index-1);

    //tz_name und tz_wert mit Daten füllen:
    bool schalter = true;
    for(uint i=1; i<tz.zeilenanzahl() ;i++)
    {
        if(schalter == true)
        {
            tz_name.zeile_anhaengen(tz.zeile(i));
        }else
        {
            tz_wert.zeile_anhaengen(tz.zeile(i));
        }
        schalter = !schalter;
    }

    //DXF-Version prüfen:
    QString dxf_version;
    for(uint i=1; i<=tz.zeilenanzahl() ;i++)
    {
        QString zeile = tz.zeile(i);
        if(zeile.contains(DXF_VERSION))
        {
            dxf_version = tz.zeile(i+2);
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
        for(uint i=1; i<=tz_name.zeilenanzahl() ;i++)
        {
            if(tz_name.zeile(i).toInt() == 2)// A name Attribute tag, Block name, and so on. Also used to identify a DXF section or table name
            {
                if(tz_wert.zeile(i) == "ENTITIES")
                {
                    i_start = i;
                }
            }
            if(i_start > 0 && tz_name.zeile(i).toInt() == 0)
            {
                if(tz_wert.zeile(i) == DXF_AC1009_EOF)
                {
                    i_ende = i;
                    break;//for i
                }
            }
        }
        //------------------------------Unterblöcke ermitteln:
        text_zeilenweise block;
        //Ersten Block finden:
        for(uint i=i_start; i<=i_ende ;i++)
        {
            if(tz_name.zeile(i) == DXF_AC1009_NULL)
            {
                QString start = int_to_qstring(i_start);
                QString ende = int_to_qstring(i);
                QString tren = "|";
                block.set_text(start+tren+ende);
                break;
            }
        }
        //restliche Blöcke finden:
        for(uint i=i_start; i<=i_ende ;i++)
        {
            if(tz_name.zeile(i) == DXF_AC1009_NULL)
            {
                QString tren = "|";
                QString start = text_rechts(block.zeile(block.zeilenanzahl()),tren);
                QString ende = int_to_qstring(i);
                block.zeile_anhaengen(start+tren+ende);
            }
        }
        block.zeile_loeschen(block.zeilenanzahl());
        block.zeile_loeschen(1);
        block.zeile_loeschen(1);
        //------------------------------Werkstück-Größe bestimmen:
        for(uint i=1;i<=block.zeilenanzahl();i++)
        {
            uint sta = text_links(block.zeile(i),"|").toUInt();
            uint end = text_rechts(block.zeile(i),"|").toUInt();
            uint anz = end-sta;
            QString klasse;
            klasse = dxf_wert(tz_name.zeilen(sta,anz), tz_wert.zeilen(sta,anz),\
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
                QString x = dxf_wert(tz_name.zeilen(sta,anz), tz_wert.zeilen(sta,anz),\
                                     DXF_AC1009_WST_X);
                if(x.toDouble() > w.laenge())
                {
                    w.set_laenge(x);
                }
                QString y = dxf_wert(tz_name.zeilen(sta,anz), tz_wert.zeilen(sta,anz),\
                                     DXF_AC1009_WST_Y);
                if(y.toDouble() > w.breite())
                {
                    w.set_breite(y);
                }
            }
        }
        //------------------------------Bohrungen vertikal:
        for(uint i=1;i<=block.zeilenanzahl();i++)
        {
            uint sta = text_links(block.zeile(i),"|").toUInt();
            uint end = text_rechts(block.zeile(i),"|").toUInt();
            uint anz = end-sta;
            QString klasse;
            klasse = dxf_wert(tz_name.zeilen(sta,anz), tz_wert.zeilen(sta,anz),\
                              DXF_AC1009_KLASSE);
            if(klasse.contains(Einstellung_dxf_klassen.bohr_vert()))
            {
                QString typ = dxf_wert(tz_name.zeilen(sta,anz), tz_wert.zeilen(sta,anz),\
                                       DXF_AC1009_NULL);
                if(typ == DXF_AC1009_KREIS)
                {
                    bohrung bo;
                    bo.set_afb("1");
                    QString r = dxf_wert(tz_name.zeilen(sta,anz), tz_wert.zeilen(sta,anz),\
                                         DXF_AC1009_KREIS_RAD);
                    bo.set_dm(r.toDouble()*2);
                    QString ti;
                    ti = text_rechts(klasse, Einstellung_dxf_klassen.bohr_vert());
                    ti = text_rechts(ti, Einstellung_dxf.paramtren());
                    ti.replace(Einstellung_dxf.dezitren(),".");
                    bo.set_tiefe(ti);
                    QString x = dxf_wert(tz_name.zeilen(sta,anz), tz_wert.zeilen(sta,anz),\
                                         DXF_AC1009_KREIS_X);
                    QString y = dxf_wert(tz_name.zeilen(sta,anz), tz_wert.zeilen(sta,anz),\
                                         DXF_AC1009_KREIS_Y);
                    if(istOberseite)
                    {
                        bo.set_bezug(WST_BEZUG_OBSEI);
                        bo.set_x(x);
                        bo.set_y(y);
                    }else
                    {
                        bo.set_bezug(WST_BEZUG_UNSEI);
                        if(Einstellung_dxf.drehtyp_L())
                        {
                            bo.set_x(w.laenge()-x.toDouble());
                            bo.set_y(y);
                        }else //if(Einstellung_dxf.drehtyp_B())
                        {
                            bo.set_x(x);
                            bo.set_y(w.breite()-y.toDouble());
                        }
                    }
                    w.neue_bearbeitung(bo.text());
                }
            }
        }
    }
    Wste.replace(Index-1, w);
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
    for(uint i=1; i<=Namen.zeilenanzahl() ;i++)
    {
        if(Werkstueckname == Namen.zeile(i))
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
    if(index > 0 && index <= Namen.zeilenanzahl())
    {
        return &Wste[index-1];
    }else
    {
        //werkstueck w;   //leeres Wst
        return NULL;
    }
}
QString werkstuecke::name(uint index)
{
    if(index > 0 && index <= Namen.zeilenanzahl())
    {
        return Namen.zeile(index);
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
QString werkstuecke::stdnamen(text_zeilenweise namen_alt, text_zeilenweise namen_neu)
{
    QString baugruppenname; //Rückgabewert der Funktion
    //erster Durchlauf: Namen tauschen
    for(uint i = 1; i<=Namen.zeilenanzahl() ;i++)
    {
        QString tmp = Namen.zeile(i);
        for(uint ii=1; ii<=namen_alt.zeilenanzahl();ii++)
        {
            if(tmp.contains(namen_alt.zeile(ii)))
            {
                tmp.replace(namen_alt.zeile(ii), namen_neu.zeile(ii));
                Namen.zeile_ersaetzen(i, tmp);
                break;
            }
        }
    }
    //zweiter Durchlauf: Schranknummer löschen wenn möglich
    QString tmp = Namen.zeile(1);
    bool schranknummer_wurde_entfernt = false;//wird gebraucht als Prüfung für den 3. Durchlauf
    if(tmp.contains("_"))
    {
        tmp = text_links(tmp, "_");
        bool identisch = true;
        for(uint i = 2; i<=Namen.zeilenanzahl() ;i++)
        {
            if(  tmp != text_links(Namen.zeile(i), "_")  )
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
            if(Namen.zeilenanzahl() > 0)
            {
                baugruppenname = text_links(Namen.zeile(1),"_");
                if(baugruppenname.at(0)=='#')
                {
                    baugruppenname = text_rechts(baugruppenname, "#");
                }
            }
            for(uint i = 1; i<=Namen.zeilenanzahl() ;i++)
            {
                Namen.zeile_ersaetzen(  i, text_rechts(Namen.zeile(i),"_")  );
            }
            schranknummer_wurde_entfernt = true;

        }
    }
    //dritter Durchlauf: Nummer hinter Teilenamen löschen wenn möglich
    text_zeilenweise bekannte_namen;
    if(schranknummer_wurde_entfernt)
    {
        for(uint i = 1; i<=Namen.zeilenanzahl() ;i++)//Name für Name durchgehen
        {
            tmp = Namen.zeile(i);
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
            for(uint iii=1; iii<=bekannte_namen.zeilenanzahl() ;iii++)//bekannte Namen nacheinander durchgehen
            {
                if(name_bis_ziffer.length() >0 && bekannte_namen.zeile(iii) == name_bis_ziffer)
                {
                    bekannt = true;
                    break;
                }
            }
            if(name_bis_ziffer.length() >0 && bekannt == false)//Wenn der Name noch nicht vergeben war
            {
                Namen.zeile_ersaetzen(i, name_bis_ziffer);
                bekannte_namen.zeile_anhaengen(name_bis_ziffer);
            }
        }
    }

    //Nameninformatione in den einzenen werkstücken aktualisieren:
    for(uint i=1; i<=Namen.zeilenanzahl() ;i++)
    {
        werkstueck w = Wste.at(i-1);
        w.set_name(Namen.zeile(i));
        Wste.replace(i-1, w);
    }
    return baugruppenname;
}
void werkstuecke::sortieren()
{
    text_zeilenweise    tmp_Namen;
    text_zeilenweise    tmp_Quellformate;
    QVector<werkstueck> tmp_Wste;
    text_zeilenweise rankingList;
    rankingList.zeile_anhaengen("Seite_li");
    rankingList.zeile_anhaengen("Seite_re");
    rankingList.zeile_anhaengen("Seite");
    rankingList.zeile_anhaengen("MS_li");
    rankingList.zeile_anhaengen("MS_re");
    rankingList.zeile_anhaengen("MS");
    rankingList.zeile_anhaengen("OB_li");
    rankingList.zeile_anhaengen("OB_mi");
    rankingList.zeile_anhaengen("OB_re");
    rankingList.zeile_anhaengen("OB");
    rankingList.zeile_anhaengen("UB_li");
    rankingList.zeile_anhaengen("UB_mi");
    rankingList.zeile_anhaengen("UB_re");
    rankingList.zeile_anhaengen("UB");
    rankingList.zeile_anhaengen("KB_ob");
    rankingList.zeile_anhaengen("KB_li");
    rankingList.zeile_anhaengen("KB_mi");
    rankingList.zeile_anhaengen("KB_un");
    rankingList.zeile_anhaengen("KB_re");
    rankingList.zeile_anhaengen("KB");
    rankingList.zeile_anhaengen("Trav_ob");
    rankingList.zeile_anhaengen("Trav_un");
    rankingList.zeile_anhaengen("Trav_vo");
    rankingList.zeile_anhaengen("Trav_hi");
    rankingList.zeile_anhaengen("Trav");
    rankingList.zeile_anhaengen("Traver_ob");
    rankingList.zeile_anhaengen("Traver_un");
    rankingList.zeile_anhaengen("Traver_vo");
    rankingList.zeile_anhaengen("Traver_hi");
    rankingList.zeile_anhaengen("Traver");
    rankingList.zeile_anhaengen("EB_ob");
    rankingList.zeile_anhaengen("EB_li");
    rankingList.zeile_anhaengen("EB_mi");
    rankingList.zeile_anhaengen("EB_un");
    rankingList.zeile_anhaengen("EB_re");
    rankingList.zeile_anhaengen("EB");
    rankingList.zeile_anhaengen("RW_ob");
    rankingList.zeile_anhaengen("RW_li");
    rankingList.zeile_anhaengen("RW_mi");
    rankingList.zeile_anhaengen("RW_un");
    rankingList.zeile_anhaengen("RW_re");
    rankingList.zeile_anhaengen("RW");
    rankingList.zeile_anhaengen("Tuer_li");
    rankingList.zeile_anhaengen("Tuer_");
    rankingList.zeile_anhaengen("Tuer_A");
    rankingList.zeile_anhaengen("Tuer_B");
    rankingList.zeile_anhaengen("Tuer_C");
    rankingList.zeile_anhaengen("Tuer_D");
    rankingList.zeile_anhaengen("Tuer_E");
    rankingList.zeile_anhaengen("Tuer");
    rankingList.zeile_anhaengen("Front_li");
    rankingList.zeile_anhaengen("Front_");
    rankingList.zeile_anhaengen("Front_A");
    rankingList.zeile_anhaengen("Front_B");
    rankingList.zeile_anhaengen("Front_C");
    rankingList.zeile_anhaengen("Front_D");
    rankingList.zeile_anhaengen("Front_E");
    rankingList.zeile_anhaengen("Front");
    rankingList.zeile_anhaengen("SF_A");
    rankingList.zeile_anhaengen("SF_B");
    rankingList.zeile_anhaengen("SF_C");
    rankingList.zeile_anhaengen("SF_D");
    rankingList.zeile_anhaengen("SF_E");
    rankingList.zeile_anhaengen("SF");
    rankingList.zeile_anhaengen("SS_A");
    rankingList.zeile_anhaengen("SS_B");
    rankingList.zeile_anhaengen("SS_C");
    rankingList.zeile_anhaengen("SS_D");
    rankingList.zeile_anhaengen("SS_E");
    rankingList.zeile_anhaengen("SS");
    rankingList.zeile_anhaengen("SV_A");
    rankingList.zeile_anhaengen("SV_B");
    rankingList.zeile_anhaengen("SV_C");
    rankingList.zeile_anhaengen("SV_D");
    rankingList.zeile_anhaengen("SV_E");
    rankingList.zeile_anhaengen("SV");
    rankingList.zeile_anhaengen("SH_A");
    rankingList.zeile_anhaengen("SH_B");
    rankingList.zeile_anhaengen("SH_C");
    rankingList.zeile_anhaengen("SH_D");
    rankingList.zeile_anhaengen("SH_E");
    rankingList.zeile_anhaengen("SH");
    rankingList.zeile_anhaengen("SB_A");
    rankingList.zeile_anhaengen("SB_B");
    rankingList.zeile_anhaengen("SB_C");
    rankingList.zeile_anhaengen("SB_D");
    rankingList.zeile_anhaengen("SB_E");
    rankingList.zeile_anhaengen("SB");
    rankingList.zeile_anhaengen("Sockel_li");
    rankingList.zeile_anhaengen("Sockel_mi");
    rankingList.zeile_anhaengen("Sockel_re");
    rankingList.zeile_anhaengen("Sockel");
    text_zeilenweise kopiert;
    for(uint ii = 1; ii<=Namen.zeilenanzahl() ;ii++)
    {
        kopiert.zeile_anhaengen("nein");
    }
    for(uint i = 1; i<=rankingList.zeilenanzahl() ;i++)
    {
        QString akt_ranking_name =rankingList.zeile(i);
        for(uint ii = 1; ii<=Namen.zeilenanzahl() ;ii++)
        {
            QString akt_wst_name = Namen.zeile(ii);
            if(kopiert.zeile(ii) != "ja")
            {
                if(akt_wst_name.contains(akt_ranking_name))
                {
                    //kopieren:
                    tmp_Namen.zeile_anhaengen(akt_wst_name);
                    tmp_Quellformate.zeile_anhaengen(Quellformate.zeile(ii));
                    werkstueck w = Wste.at(ii-1);
                    w.set_name(akt_wst_name);
                    tmp_Wste.append(w);
                    kopiert.zeile_ersaetzen(ii, "ja");
                }
            }
        }        
    }
    //2. Durchlauf. Jetzt kommen alle wst die nicht sortierbar waren:
    for(uint i = 1; i<=Namen.zeilenanzahl() ;i++)
    {
        QString akt_wst_name = Namen.zeile(i);
        if(kopiert.zeile(i) != "ja")
        {
            //kopieren:
            tmp_Namen.zeile_anhaengen(akt_wst_name);
            tmp_Quellformate.zeile_anhaengen(Quellformate.zeile(i));
            werkstueck w = Wste.at(i-1);
            w.set_name(akt_wst_name);
            tmp_Wste.append(w);
            kopiert.zeile_ersaetzen(i, "ja");
        }
    }
    Namen = tmp_Namen;
    Quellformate = tmp_Quellformate;
    Wste = tmp_Wste;
}
/*
void werkstuecke::ersetzen(werkstueck w, uint index)
{
    if(index > 0 && index <= Namen.zeilenanzahl())
    {
        Wste.replace(index-1, w);
    }
}
*/
//--------------------------------------------------
//#######################################################################
//Private:
//#######################################################################
//--------------------------------------------------set_xy:

//--------------------------------------------------get_xy:
uint werkstuecke::index(QString Werkstueckname)
{
    for(uint i=1; i<=Namen.zeilenanzahl() ;i++)
    {
        if(Namen.zeile(i)==Werkstueckname)
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



